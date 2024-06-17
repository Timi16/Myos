
CC = clang
LD = /data/data/com.termux/files/usr/bin/ld 
ASM = /data/data/com.termux/files/usr/bin/nasm 
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T kernel/linker.ld

all: build/os-image.bin

build/bootloader.bin: boot/bootloader.asm
	$(ASM) -f bin $< -o $@

build/kernel.o: kernel/kernel.c kernel/kernel.h
	$(CC) $(CFLAGS) -target i686-elf -c $< -o $@

build/kernel.bin: build/kernel.o
	$(LD) $(LDFLAGS) $< -o $@

build/os-image.bin: build/bootloader.bin build/kernel.bin
	cat $^ > $@

clean:
	rm -f build/*.bin build/*.o

run: all
	qemu-system-i386 -drive format=raw,file=build/os-image.bin
