
CFLAGS=-ffreestanding -O2 -Wall -Wextra

all: os-image

os-image: boot/boot.bin kernel.bin
	cat $^ > os-image

boot/boot.bin: boot/boot.s
	nasm -f bin $< -o $@

kernel.bin: kernel_entry.o kernel/kernel.o kernel/system_calls.o kernel/process.o memory/memory.o
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel/kernel_entry.s
	nasm -f elf $< -o $@

kernel/kernel.o: kernel/kernel.c
	gcc $(CFLAGS) -c $< -o $@

kernel/system_calls.o: kernel/system_calls.c
	gcc $(CFLAGS) -c $< -o $@

kernel/process.o: kernel/process.c
	gcc $(CFLAGS) -c $< -o $@

memory/memory.o: memory/memory.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o boot/*.bin kernel/*.o memory/*.o os-image
