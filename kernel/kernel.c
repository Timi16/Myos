// kernel/kernel.c
#include "kernel.h"

void print(const char* str, int row, int col);
void init_tasks(void);
void task1(void);
void task2(void);

#define VIDEO_MEMORY 0xB8000

typedef struct {
    unsigned int esp;
} task_t;

task_t tasks[2];
int current_task = 0;

void kernel_main(void) {
    print("MyOS: Kernel Started", 0, 0);
    init_tasks();
    while (1) {
        // Simple round-robin scheduler
        current_task = (current_task + 1) % 2;
        __asm__ volatile("mov %0, %%esp" : : "r" (tasks[current_task].esp));
    }
}

void print(const char* str, int row, int col) {
    volatile char* video = (volatile char*)(VIDEO_MEMORY + (row * 80 + col) * 2);
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07;
    }
}

void init_tasks(void) {
    tasks[0].esp = (unsigned int)task1 + 4096;
    tasks[1].esp = (unsigned int)task2 + 4096;

    // Initialize stacks for each task
    __asm__ volatile("mov %0, %%esp" : : "r" (tasks[0].esp));
}

void task1(void) {
    while (1) {
        print("Task 1 running...", 2, 0);
    }
}

void task2(void) {
    while (1) {
        print("Task 2 running...", 3, 0);
    }
}
