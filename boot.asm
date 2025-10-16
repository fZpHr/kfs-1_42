extern kernel_main

; Déclare des constantes pour l'entête multiboot
%define ALIGN    (1 << 0)         ; align loaded modules on page boundaries
%define MEMINFO  (1 << 1)         ; provide memory map
%define FLAGS    (ALIGN | MEMINFO); multiboot flag field
%define MAGIC    0x1BADB002       ; magic number for bootloader to find header
%define CHECKSUM -(MAGIC + FLAGS) ; checksum for multiboot header

; Section multiboot header, align 4 bytes
section .multiboot align=4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Section bss pour la pile, alignée à 16 bytes
section .bss align=16
stack_bottom:
    resb 16384      ; réserve 16 KiB pour la pile
stack_top:

; Section code texte (exécutable)
section .text
global _start
_start:
    ; Initialiser esp à la fin de la pile (pile descendante)
    mov esp, stack_top

    ; Appeler la fonction kernel_main
    call kernel_main

    ; Boucle infinie: désactive les interruptions, halt et jump
    cli
.halt_loop:
    hlt
    jmp .halt_loop

; Définit la taille de _start (utile pour le debug)
; NASM ne supporte pas directement .size, 
; mais tu peux faire ça dans le linker script ou avec des symboles si nécessaire
