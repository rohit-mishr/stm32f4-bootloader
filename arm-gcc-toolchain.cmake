# 1. Tell CMake we are cross-compiling (not building for the host OS)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 2. Specify the exact cross-compilers to use
# (Assumes arm-none-eabi-gcc is installed and in your system PATH)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

# 3. Define the specific hardware flags for the STM32F446RE (Cortex-M4 with FPU)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

# 4. Apply these hardware flags to all C, C++, and Assembly compilations
set(CMAKE_C_FLAGS "${MCU_FLAGS}" CACHE INTERNAL "C Compiler flags")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS}" CACHE INTERNAL "C++ Compiler flags")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS}" CACHE INTERNAL "ASM Compiler flags")

# 5. Tell CMake not to look for standard OS libraries (like Windows/Linux API)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)