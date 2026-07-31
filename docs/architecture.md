\# Architecture Design Document: Industrial IoT Edge Node (V1)



\## 1. Product Overview

The Industrial IoT Edge Node (V1) is a tethered, continuous condition-monitoring device designed for industrial machinery. It interfaces with a single SPI-based accelerometer to capture high-frequency vibration data, calculates time-domain features (RMS and Peak Acceleration) locally, and communicates these metrics over a generic serial transport (UART) to a host gateway.



\## 2. System Requirements

\### 2.1 Functional Requirements

\* \*\*Data Acquisition:\*\* Sample a 3-axis SPI accelerometer at a deterministic, timer-driven interval using DMA.

\* \*\*Local Processing:\*\* Calculate RMS and Peak Acceleration over a defined sample window.

\* \*\*Threshold Monitoring:\*\* Compare calculated metrics against configurable Warning and Critical thresholds.

\* \*\*Host Communication:\*\* Transmit periodic health heartbeats and asynchronous alarm events to a host via a decoupled Communication Service layer.

\* \*\*Configuration Storage:\*\* Store Node ID, sampling intervals, and threshold values in non-volatile memory.

\* \*\*Health Monitoring:\*\* Utilize an independent hardware watchdog (IWDG) fed by a dedicated Health Monitor task that verifies the execution state of all tasks.



\### 2.2 Non-Functional Requirements

\* \*\*Reliability:\*\* The firmware must recover autonomously from locked peripheral buses or task starvation.

\* \*\*Modularity:\*\* The transport layer must be decoupled from the application logic to allow future migration to RS-485 or CAN.

\* \*\*Maintainability:\*\* Strict adherence to MISRA-C principles (where practical) and no dynamic memory allocation (`malloc`/`free`) after RTOS initialization.



\## 3. Software Architecture Diagram

```text

\[ Application Layer ]

&#x20;     │

&#x20;     ├─ Sensor Manager (Thresholds, State)

&#x20;     └─ Telemetry Manager (Formatting)

&#x20;     │

\[ Middleware / Services Layer ]

&#x20;     │

&#x20;     ├─ RTOS (FreeRTOS Core \& IPC)

&#x20;     ├─ Health Monitor (Watchdog, Task Stalls)

&#x20;     ├─ Configuration Manager (Flash KV Store)

&#x20;     ├─ Diagnostics Manager (Fault Flags)

&#x20;     └─ Protocol Layer (Packetization, Queues)

&#x20;     │

\[ Component Driver Layer ] 

&#x20;     │

&#x20;     └─ SPI Accelerometer Driver

&#x20;     │

\[ Hardware Driver Layer ] 

&#x20;     │

&#x20;     ├─ SPI Driver

&#x20;     └─ Transport Driver (UART)

&#x20;     │

\[ Hardware Abstraction (BSP) ]

&#x20;     │

&#x20;     └─ DMA, GPIO, NVIC, RCC, Flash Control

