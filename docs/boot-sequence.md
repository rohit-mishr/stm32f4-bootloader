\# Boot Sequence \& System State



\## 1. Boot Flow

1\. \*\*Hardware Reset:\*\* Cortex-M4 loads initial SP and PC from Sector 0 (Bootloader).

2\. \*\*Bootloader Execution:\*\* 

&#x20;   \* Configures minimal clocks.

&#x20;   \* Calculates CRC-32 (IEEE 802.3) of the Application Sector.

&#x20;   \* Updates Vector Table Offset Register (VTOR) to `0x08008000`.

&#x20;   \* De-initializes peripherals and jumps to Application reset handler.

3\. \*\*Application C-Startup:\*\* Initializes `.data` and `.bss` segments, calls `main()`.

4\. \*\*RTOS Handoff:\*\* Executes Initialization Sequence, calls `vTaskStartScheduler()`.



\## 2. Startup \& Initialization Sequence

1\. \*\*Clock \& Power:\*\* Read `RCC\_CSR` for reset reason, initialize 180 MHz clock.

2\. \*\*BSP Init:\*\* Initialize GPIO, SPI, UART, DMA (Interrupts OFF).

3\. \*\*Services Init:\*\* Init Configuration Manager (read Flash) and Diagnostics Manager.

4\. \*\*RTOS Primitives:\*\* Create all FreeRTOS Queues, Mutexes, and Event Groups.

5\. \*\*Task Creation:\*\* Instantiate System Manager, Health Monitor, Acquisition, Processing, Comm.

6\. \*\*Start Scheduler:\*\* Enable NVIC lines, start FreeRTOS.



\## 3. System State Machine (System Manager)

| State | Description | Next State |

|---|---|---|

| \*\*BOOTING\*\* | Hardware handoff from Bootloader to Application. | INITIALIZING |

| \*\*INITIALIZING\*\* | Drivers, services, and RTOS queues are being created. | SELF TEST |

| \*\*SELF TEST\*\* | Sensor WHO\_AM\_I, Flash CRC, Comm loopback verification. | RUNNING or FAULT |

| \*\*RUNNING\*\* | Normal DMA acquisition, processing, and protocol transmission. | WARNING or FAULT |

| \*\*WARNING\*\* | Degraded operation (e.g., dropped packet). System continues running. | RUNNING or FAULT |

| \*\*FAULT\*\* | Fatal error. Non-essential tasks suspended. | RECOVERY |

| \*\*RECOVERY\*\* | Attempt forceful reset of locked peripherals. | INITIALIZING or HW Reset |



\## 4. Error Recovery Strategy

\* \*\*SPI Lockup:\*\* System Manager enters FAULT, toggles sensor HW reset pin, re-inits SPI via RCC, returns to RUNNING.

\* \*\*UART Timeout:\*\* Drop packet, increment Comm Failure counter, apply exponential backoff.

\* \*\*Task Starvation:\*\* Health monitor stops feeding IWDG. Hardware resets MCU. Next boot logs IWDG reset reason.

