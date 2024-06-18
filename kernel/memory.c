// memory.c
#include "memory.h"
#include "kernel.h"

#define MEMORY_SIZE 1024 * 1024  // 1MB
unsigned char memory[MEMORY_SIZE];
unsigned int memory_index = 0;

void* simple_malloc(unsigned int size) {
    void* ptr = &memory[memory_index];
    memory_index += size;
    if (memory_index >= MEMORY_SIZE) {
        print_string("Out of Memory\n");
        return 0;
    }
    return ptr;
}

void init_memory_management() {
    // Initialize memory management here
    memory_index = 0;
    print_string("Memory Management Ready\n");
}
