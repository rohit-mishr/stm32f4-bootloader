#include <stdint.h>

/* 1. Import the variables we defined in the Linker Script */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Prototype for our main function */
int main(void);

/* 2. The Reset Handler (The very first function that runs) */
void Reset_Handler(void) {
    /* Step A: Copy the initialized variables (.data) from Flash to RAM */
    uint32_t *src = &_sidata;
    uint32_t *dest = &_sdata;
    while (dest < &_edata) {
        *dest++ = *src++;
    }

    /* Step B: Zero out the uninitialized variables (.bss) in RAM */
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }

    /* Step C: Jump to the main application */
    main();

    /* Safety trap: if main() ever accidentally returns, freeze here */
    while (1);
}

/* 3. The Vector Table */
/* We use a compiler attribute to force this array into the ".isr_vector" section */
__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,       /* Address 0x00: The Initial Stack Pointer */
    (uint32_t *)Reset_Handler   /* Address 0x04: The Reset Handler address */
};