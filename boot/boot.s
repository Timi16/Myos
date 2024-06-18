; boot.s
[org 0x7c00]          ; BIOS loads the bootloader at address 0x7c00
mov ah, 0x0e          ; BIOS teletype function (print char to screen)
mov al, 'L'           ; Character to print
int 0x10              ; BIOS interrupt

mov al, 'o'
int 0x10

mov al, 'a'
int 0x10

mov al, 'd'
int 0x10

; Load the kernel into memory
mov bx, 0x1000        ; Address to load the kernel (0x1000)
mov dh, 15            ; Number of sectors to read
mov dl, 0             ; Drive number (0x00 for the first floppy disk)
mov ah, 0x02          ; BIOS read sector function
int 0x13              ; BIOS interrupt

jmp 0x1000:0000       ; Jump to kernel

times 510 - ($ - $$) db 0 ; Fill the rest of the 512-byte boot sector with zeros
dw 0xaa55                 ; Boot signature
