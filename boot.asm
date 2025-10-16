; boot.asm
BITS 32
GLOBAL start
SECTION .multiboot
align 4

; Multiboot header (magic, flags, checksum)
MBALIGN     equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

multiboot_header:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

SECTION .text
start:
    extern kernel_main
    cli
    call kernel_main
    hlt
