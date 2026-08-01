/* 1. Define the entry point for the microcontroller */
ENTRY(Reset_Handler)

/* 2. Define the end of RAM to set up the initial stack pointer */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* 3. The exact memory map of the STM32F446RE for our Bootloader */
MEMORY
{
  /* We get the full 128KB of RAM */
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 128K
  
  /* STRICT LIMIT: The bootloader ONLY gets Sector 0 (16KB) */
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 16K   
}

/* 4. Tell the linker how to arrange the code in memory */
SECTIONS
{
  /* The Vector Table MUST be at the very beginning of Flash (0x08000000) */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) 
    . = ALIGN(4);
  } >FLASH

  /* The actual C code goes next in Flash */
  .text :
  {
    . = ALIGN(4);
    *(.text)           
    *(.text*)          
    . = ALIGN(4);
    _etext = .;        
  } >FLASH

  /* Read-only data (like 'const' variables and strings) goes into Flash */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         
    *(.rodata*)        
    . = ALIGN(4);
  } >FLASH

  /* Get the physical address in Flash where the initial variable values are stored */
  _sidata = LOADADDR(.data);

  /* Initialized variables (.data) live in RAM, but their startup values are stored in Flash */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        
    *(.data)           
    *(.data*)          
    . = ALIGN(4);
    _edata = .;        
  } >RAM AT> FLASH

  /* Uninitialized variables (.bss) live in RAM and start as zero */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;         
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;         
  } >RAM
}