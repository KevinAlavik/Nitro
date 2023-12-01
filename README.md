# Nitro
A kernel using the limine bootloader
Nitro comes with NitrOS, nsh (Nitro Shell), nighterm and egl. Nitro is a more serious kernel built with some features from [POS](https://github.com/kevinalavik/POS)

## TTY
Nitro and NitrOS is using [**nighterm**](https://github.com/kevinalavik/Nitro/tree/main/src/nighterm/nighterm.h) as a terminal / display manager.

## Nighterm (`src/nighterm/`)
Nighterm is the builtin terminal emulator for Nitro it has support for printing characters and loading fonts and some other good things (like storing thr text in a buffer snd refreshing the terminal easier)
## EGL (`src/egl/`)
**E**asy**G**raphics**L**ibrary, can be used to draw simple shapes and other GUI actions

## The idea..
I want to make a easy to use and easy to learn OS (built using the kernel) that you can do simple things in like: Programs, Text editing, Graphics, Shell, User accounts, File system shit 
