#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 1024
#define CONFIG_FILE "config.ini"

/* -------------------------------------------------- */

void trim_newline(char *str) {
    str[strcspn(str, "\r\n")] = 0;
}

/* -------------------------------------------------- */

void create_default_config() {
    FILE *f = fopen(CONFIG_FILE, "w");
    if (!f) return;

    fprintf(f,
        "path_zerobot=D:\\Clients\\ZeroLauncher\n"
        "path_lib_zero=C:\\Users\\user\\Documents\\Zerobot\\Scripts\\core\\lib.lua\n"
        "path_lib_new=lib.lua\n"
        "time=5000\n"
    );

    fclose(f);
}

/* -------------------------------------------------- */

void read_config(
    char *exe,
    char *old_lib,
    char *new_lib,
    int *time_ms
) {
    FILE *f = fopen(CONFIG_FILE, "r");

    if (!f) {
        printf("config.ini nao encontrado, criando...\n");
        create_default_config();
        f = fopen(CONFIG_FILE, "r");
        if (!f) {
            printf("Erro ao criar config.ini\n");
            exit(1);
        }
    }

    char line[2048];

    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);

        if (strncmp(line, "path_zerobot=", 13) == 0)
            strcpy(exe, line + 13);
        else if (strncmp(line, "path_lib_zero=", 14) == 0)
            strcpy(old_lib, line + 14);
        else if (strncmp(line, "path_lib_new=", 13) == 0)
            strcpy(new_lib, line + 13);
        else if (strncmp(line, "time=", 5) == 0)
            *time_ms = atoi(line + 5);
    }

    fclose(f);
}

/* -------------------------------------------------- */
/* Resolve caminhos relativos para a pasta do launcher */

void resolve_relative_path(char *out, const char *in) {
    char exe_dir[MAX_PATH_LEN];

    GetModuleFileName(NULL, exe_dir, MAX_PATH_LEN);

    char *last_slash = strrchr(exe_dir, '\\');
    if (last_slash)
        *(last_slash + 1) = '\0';

    /* Caminho absoluto */
    if (
        (strlen(in) > 1 && in[1] == ':') ||
        (in[0] == '\\' && in[1] == '\\') ||
        (in[0] == '/')
    ) {
        strcpy(out, in);
        return;
    }

    /* Remove ./ ou .\ */
    if (strncmp(in, "./", 2) == 0 || strncmp(in, ".\\", 2) == 0)
        in += 2;

    snprintf(out, MAX_PATH_LEN, "%s%s", exe_dir, in);
}

/* -------------------------------------------------- */

int main() {
    char path_exe[MAX_PATH_LEN] = {0};
    char path_old_raw[MAX_PATH_LEN] = {0};
    char path_new_raw[MAX_PATH_LEN] = {0};
    char path_old[MAX_PATH_LEN] = {0};
    char path_new[MAX_PATH_LEN] = {0};
    int time_ms = 0;

    read_config(path_exe, path_old_raw, path_new_raw, &time_ms);

    resolve_relative_path(path_old, path_old_raw);
    resolve_relative_path(path_new, path_new_raw);

    printf("Executavel   : %s\n", path_exe);
    printf("Lib antiga   : %s\n", path_old);
    printf("Lib nova     : %s\n", path_new);
    printf("Tempo espera : %d ms\n", time_ms);

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    if (!CreateProcess(
        path_exe,
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        printf("Erro ao iniciar executavel (%lu)\n", GetLastError());
        return 1;
    }

    printf("Executavel iniciado.\n");

    Sleep(time_ms);

    printf("Substituindo arquivo...\n");

    if (!CopyFile(
        path_new,   // origem (continua existindo)
        path_old,   // destino (conteúdo será sobrescrito)
        FALSE       // FALSE = permite sobrescrever
    )) {
        printf("Erro ao copiar arquivo (%lu)\n", GetLastError());
        return 1;
    }


    printf("Arquivo substituido com sucesso.\n");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
