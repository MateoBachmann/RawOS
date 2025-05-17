; Multiboot Header
section .multiboot
    align 4
    dd 0x1BADB002          ; magic
    dd 0x0                 ; flags
    dd -0x1BADB002         ; checksum (negativ von magic + flags)

section .text
    global _start
    extern kernel_main     ; <<< das hier hinzufügen!

_start:
    call kernel_main
    cli
    hlt
