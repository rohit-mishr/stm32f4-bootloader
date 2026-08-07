#include <stdint.h>

// We will assume the main application firmware is flashed starting at Sector 2
#define MAIN_APP_START_ADDRESS 0x08008000
#define SCB_VTOR_ADDRESS       0xE000ED08
// RCC (Reset and Clock Control) Base Address
#define RCC_BASE       0x40023800
#define GPIOA_BASE 0x40020000

// RCC Enable Registers (Base + Offset)
#define RCC_AHB1ENR    *(volatile uint32_t*)(RCC_BASE + 0x30)
#define RCC_APB1ENR    *(volatile uint32_t*)(RCC_BASE + 0x40)

#define MODER_A *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define AFRL_A *(volatile uint32_t*)(GPIOA_BASE + 0x20)

#define USART2_BASE 0x40004400
#define USART_SR *(volatile uint32_t*)(USART2_BASE)
#define TXE ((USART_SR>>7)&(1<<0))
#define RXNE ((USART_SR>>5)&(1<<0))
#define USART_DR *(volatile uint32_t*)(USART2_BASE + 0x04)
#define USART_BRR *(volatile uint32_t*)(USART2_BASE + 0x08)
#define USART_CR1 *(volatile uint32_t*)( USART2_BASE + 0x0C)


void bootloader_uart_init(void) {
    // ==========================================
    // STEP 1: ENABLE CLOCKS
    // ==========================================
    
    // Enable the clock for GPIOA (AHB1 Bus, Bit 0)
    RCC_AHB1ENR |= (1 << 0);
    
    // Enable the clock for USART2 (APB1 Bus, Bit 17)
    RCC_APB1ENR |= (1 << 17);
    
    
    // ==========================================
    // STEP 2: CONFIGURE GPIO 
    MODER_A &= ~((3UL<<4)|(3UL<<6));
    AFRL_A &= ~((15UL<<8)|(15UL<<12));
    MODER_A |= ((2UL<<4) | (2UL<<6));
    AFRL_A |= ((7UL<<8)|(7UL<<12));
    // ==========================================
     // configure the usart2

     // seetting baudrate 
     USART_BRR = 0x008B;

     // setting the enable bits
     USART_CR1 |= ((1<<13)|(1<<3)|(1<<2));

}

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

void usart_send_char(uint8_t data) {
    // 1. Wait for TXE to be 1
    // 2. Write 'data' to USART_DR
    while(!TXE);
    USART_DR = data;

}

uint8_t usart_receive_char(void) {
    // 1. Wait for RXNE to be 1
    // 2. Return the value in USART_DR
    while(!RXNE);
    return (uint8_t)(USART_DR&0xFF);
}

int main(void) {
    // 1. TODO: Initialize Clocks and UART
    // 2. TODO: Check if the user is requesting a firmware update
    
    // 3. TODO: De-initialize clocks and UART before jumping
    
    // 4. Jump to the main application
    // Temporary Hardware Test Loop

    jump_to_application();
    
    // The CPU has left the bootloader. It will never reach this while loop.
    while (1) {
    }
    
    return 0;
}