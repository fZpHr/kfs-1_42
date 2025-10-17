# KFS-1

## Usefull links
- https://wiki.osdev.org/GCC_Cross-Compiler

- https://wiki.osdev.org/Bare_Bones

## General informations

This projects sets a bunch of files that will compile a flat binary and turn it into an iso image to boot with grub. This will be the bare minimum of a kernel that is bootable and will print a few things on the screen.

The `Makefile` will be use to compile a freestanding multi-boot binary, then create an iso image to run the bootable program.

The `grub.cfg` file is used to tell grub where to find the binary to launch and will be packaged in an iso file created with `grub-mkrescue`. It will then be launch with qemu.

The `linker.ld` file tells the linker how to arrange the final binary and
which symbol to use as the program entry point.

The `boot.asm` file is the assembly bootstrap: it prepares minimal CPU state
and transfers control to the kernel's C entry point.

The `kernel.c` file contains the freestanding C entry and the basic kernel
logic that runs after the bootstrap.