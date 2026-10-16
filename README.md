# trocador_zero

Launcher para Windows que abre o ZeroBot e, depois de alguns segundos, sobrescreve o `lib.lua` dele
com o `lib.lua` deste repositório.

O `lib.lua` daqui é o mesmo do ZeroBot sem as linhas que desativam `os.execute`, `io.popen` e
`os.remove`. Com a troca, os scripts voltam a poder usar essas funções.

> **Aviso:** projeto pessoal e experimental, sem garantia de nenhum tipo. Não use em produção. Quem
> usar assume todo o risco; o autor não se responsabiliza por nenhum dano, perda de dados, banimento
> de conta ou qualquer outra consequência do uso deste código.

## Uso

1. Coloque `launcher.exe` e `lib.lua` na mesma pasta.
2. Rode `launcher.exe` uma vez. Se não existir `config.ini`, ele cria um com valores padrão.
3. Ajuste o `config.ini` e rode de novo.

```ini
path_zerobot=C:\caminho\para\ZeroBotLauncher.exe
path_lib_zero=C:\Users\SEU_USUARIO\Documents\Zerobot\Scripts\core\lib.lua
path_lib_new=lib.lua
time=5000
```

| Chave | O que é |
| --- | --- |
| `path_zerobot` | executável do ZeroBot que o launcher abre |
| `path_lib_zero` | `lib.lua` do ZeroBot que vai ser sobrescrito |
| `path_lib_new` | `lib.lua` que entra no lugar; caminho relativo é resolvido a partir da pasta do `launcher.exe` |
| `time` | espera em milissegundos entre abrir o ZeroBot e copiar o arquivo |

O `config.ini` é local de cada máquina e fica fora do git.

## Compilar

Com MinGW:

```sh
gcc trocador.c -o launcher.exe
```

O `launcher.exe` do repositório foi gerado com MinGW GCC 6.3 e depende de `libgcc_s_dw2-1.dll`.
Para não depender da DLL, compile com `-static-libgcc`.
