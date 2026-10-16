# trocador_zero

[![GitHub release](https://img.shields.io/github/v/release/christmattos/trocador_zero)](https://github.com/christmattos/trocador_zero/releases)

trocador_zero is a small Windows launcher for ZeroBot. It starts ZeroBot and then replaces its `lib.lua`, so scripts can use `os.execute`, `io.popen` and `os.remove` again.

## Features

- Replaces ZeroBot's `lib.lua` after a configurable delay
- Re-enables `os.execute`, `io.popen` and `os.remove`, which the stock `lib.lua` disables
- Plain `config.ini`, created on first run

## Downloads

- [Windows](https://github.com/christmattos/trocador_zero/releases)

The release only contains `launcher.exe`. You also need [`lib.lua`](lib.lua) from this repository.

## Usage

1. Put `launcher.exe` and `lib.lua` in the same folder.
2. Run `launcher.exe` from that folder. It creates `config.ini` on the first run.
3. Edit `config.ini` and run it again.

The original `lib.lua` is overwritten and no backup is made.

## Configuration

```ini
path_zerobot=C:\path\to\ZeroBotLauncher.exe
path_lib_zero=C:\Users\YOUR_USER\Documents\Zerobot\Scripts\core\lib.lua
path_lib_new=lib.lua
time=5000
```

- `path_zerobot`: ZeroBot executable to start
- `path_lib_zero`: ZeroBot's `lib.lua`, the file that gets overwritten
- `path_lib_new`: the replacement `lib.lua`
- `time`: delay in milliseconds between starting ZeroBot and copying the file

Relative paths in `path_lib_zero` and `path_lib_new` are resolved from the folder of `launcher.exe`.

## Building

Requires MinGW. The release is built with GCC 16 for 64-bit Windows.

```sh
gcc -static-libgcc trocador.c -o launcher.exe
```

## Disclaimer

This is a personal, experimental project, provided as is and without warranty of any kind. Do not use it in production. You use it at your own risk: the author is not responsible for any damage, data loss, account ban or other consequence of using this code.
