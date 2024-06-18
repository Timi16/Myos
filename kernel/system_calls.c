// system_calls.c
#include "system_calls.h"
#include "kernel.h"

void handle_system_call(int call_number) {
    switch (call_number) {
        case 1:
            print_string("System Call 1 Executed\n");
            break;
        case 2:
            print_string("System Call 2 Executed\n");
            break;
        default:
            print_string("Unknown System Call\n");
            break;
    }
}

void init_system_calls() {
    // Placeholder for system call initialization
    print_string("System Calls Ready\n");
}
