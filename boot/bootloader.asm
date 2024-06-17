; boot/bootloader.asm
[BITS 16]
[ORG 0x7C00]

start:
    cli
    mov ax, 0x07C0
    add ax, 288
    mov ss, ax
    mov sp, 4096
    mov ax, 0x07C0
    mov ds, ax

    mov si, welcome_msg
    call print_string

    ; Load kernel (assuming kernel.bin is at sector 2)
    mov bx, 0x1000    ; Load address for kernel
    mov dh, 15        ; Number of sectors to load
    call load_kernel

    jmp 0x1000:0

print_string:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print_string
done:
    ret

load_kernel:
    mov ah, 0x02
    mov al, dh
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13
    jc load_kernel
    ret

welcome_msg db 'Booting MyOS...', 0

times 510-($-$$) db 0
dw 0xAA55
