# chavo-rkt-startup
C++ program for Windows that sets system volume to 100% every second and plays "El Chavo RKT Saturado" in a loop. It´s ideal for adding to `shell:startup`.

## How to use
Just download from [Releases](https://github.com/agopdev/chavo-rkt-startup/releases/latest) the one that matches with the desired architecture, then run `chavo-rkt-startup_xXX.exe` on any Windows machine. If you want to stop it, you will need to use the **Task Manager**.

## Use another audio
You can put another **wav** file inside `assets` with the same name `audio.wav` and then compile.

## Compile it yourself
If you want to compile the program yourself, use `MinGW`.

I'm using `WSL2 Debian Bookworm`, so I've installed it with:
```bash
$ sudo apt update

$ sudo apt install mingw-w64 && sudo apt install g++-mingw-w64-x86-64-posix
```

### Create build dir
```bash
$ mkdir -p ./build/output
```

Then I compiled:

### For 32-bit (x86)
```bash
$ i686-w64-mingw32-windres ./src/resources.rc -O coff -o ./build/resources.res && i686-w64-mingw32-g++ -o ./build/output/chavo-rkt-startup_x86.exe ./src/main.cpp ./build/resources.res -lole32 -lwinmm -static-libstdc++ -static-libgcc -static -mwindows
```

### For 64-bit (x86_64)
```bash
$ x86_64-w64-mingw32-windres ./src/resources.rc -O coff -o ./build/resources.res && x86_64-w64-mingw32-g++ -o ./build/output/chavo-rkt-startup_x86_64.exe ./src/main.cpp ./build/resources.res -lole32 -lwinmm -static-libstdc++ -static-libgcc -static -mwindows
```

You'll find `chavo-rkt-startup_xXX.exe` inside `build/output`