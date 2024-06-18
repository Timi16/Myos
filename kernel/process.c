// process.c
#include "process.h"
#include "kernel.h"

typedef struct {
    unsigned int esp;
    unsigned int eip;
} process_control_block_t;

process_control_block_t pcb1, pcb2;
process_control_block_t* current_pcb;

void dummy_process_1() {
    while (1) {
        print_string("Process 1 Running\n");
        for (volatile int i = 0; i < 10000000; i++);  // Delay loop
        __asm__("int $32");
    }
}

void dummy_process_2() {
    while (1) {
        print_string("Process 2 Running\n");
        for (volatile int i = 0; i < 10000000; i++);  // Delay loop
        __asm__("int $32");
    }
}

void start_process() {
    pcb1.esp = 0x90000;
    pcb1.eip = (unsigned int)dummy_process_1;

    pcb2.esp = 0x91000;
    pcb2.eip = (unsigned int)dummy_process_2;

    current_pcb = &pcb1;

    __asm__("mov %0, %%esp" : : "r"(current_pcb->esp));
    __asm__("jmp *%0" : : "r"(current_pcb->eip));
}

void switch_process() {
    if (current_pcb == &pcb1) {
        current_pcb = &pcb2;
    } else {
        current_pcb = &pcb1;
    }
    __asm__("mov %0, %%esp" : : "r"(current_pcb->esp));
    __asm__("jmp *%0" : : "r"(current_pcb->eip));
}

void init_process_management() {
    // Initialize timer interrupt for process switching
    // Placeholder for timer initialization
    start_process();
}
