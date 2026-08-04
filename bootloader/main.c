#include <stdint.h>

// RCC Registers
#define RCC_BASE       0x40023800
#define RCC_AHB1ENR    *(volatile uint32_t*)(RCC_BASE + 0x30)

// GPIOA Registers
#define GPIOA_BASE     0x40020000
#define GPIOA_MODER    *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define GPIOA_ODR      *(volatile uint32_t*)(GPIOA_BASE + 0x14)

int main(void) {
    // 1. Enable GPIOA Clock
    RCC_AHB1ENR |= (1 << 0);
    
    // 2. Set PA5 as Output (Bits 10:11 = 01)
    // First, clear the two bits just to be safe
    GPIOA_MODER &= ~(3 << 10); 
    // Then set bit 10 to 1
    GPIOA_MODER |= (1 << 10);  
    
    // 3. Infinite Blinky Loop
    while (1) {
        // Toggle PA5
        GPIOA_ODR ^= (1 << 5);
        
        // Dumb Delay Loop (MUST be volatile!)
        for (volatile uint32_t i = 0; i < 500000; i++) {
            // Do nothing, just burn CPU cycles
        }
    }
    
    return 0;
}