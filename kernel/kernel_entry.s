; kernel_entry.s
[extern kernel_main]

section .text
    global _start
_start:
    ; Set up stack
    mov esp, 0x90000

    ; Call kernel main
    call kernel_main

    ; Halt the CPU
.hang:
    hlt
    jmp .hang
