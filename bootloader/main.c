#include <stdint.h>

// We will assume the main application firmware is flashed starting at Sector 2
#define MAIN_APP_START_ADDRESS 0x08008000
#define SCB_VTOR_ADDRESS       0xE000ED08

void jump_to_application(void) {
    // Step A: Read the main application's Stack Pointer
    uint32_t app_msp_value = *(volatile uint32_t*)MAIN_APP_START_ADDRESS;
    
    // Step B: Read the main application's Reset Handler
    uint32_t app_jump_address = *(volatile uint32_t*)(MAIN_APP_START_ADDRESS + 4);
    
    // Step C: Cast to a C function pointer
    void (*app_reset_handler)(void) = (void (*)(void))app_jump_address;
    
    //Step D : set the vtor to the main app's address
    *(volatile uint32_t*)SCB_VTOR_ADDRESS = MAIN_APP_START_ADDRESS;
    
    // Step E: Physically set the ARM CPU's Main Stack Pointer (MSP)
    __asm volatile("msr msp, %0" : : "r" (app_msp_value));

    // Step F: Jump! 
    app_reset_handler();
}

int main(void) {
    // 1. TODO: Initialize Clocks and UART
    // 2. TODO: Check if the user is requesting a firmware update
    
    // 3. TODO: De-initialize clocks and UART before jumping
    
    // 4. Jump to the main application
    jump_to_application();
    
    // The CPU has left the bootloader. It will never reach this while loop.
    while (1) {
    }
    
    return 0;
}