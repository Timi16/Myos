// kernel.c
#include "kernel.h"
#include "system_calls.h"
#include "process.h"
#include "memory.h"

#define VIDEO_MEMORY 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void print_string(const char* str) {
    static int row = 0;
    static int col = 0;
    unsigned short* VideoMemory = (unsigned short*)VIDEO_MEMORY;
    while (*str) {
        if (*str == '\n') {
            row++;
            col = 0;
        } else {
            VideoMemory[row * VGA_WIDTH + col] = (*str | 0x0700);
            col++;
            if (col >= VGA_WIDTH) {
                col = 0;
                row++;
            }
        }
        str++;
    }
}

void kernel_main() {
    print_string("Kernel Initialized\n");

    init_system_calls();
    print_string("System Calls Initialized\n");

    init_process_management();
    print_string("Process Management Initialized\n");

    init_memory_management();
    print_string("Memory Management Initialized\n");

    // Infinite loop to keep the kernel running
    while (1) {
        __asm__("hlt");
    }
}
