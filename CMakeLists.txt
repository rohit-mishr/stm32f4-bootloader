# 1. Require a modern CMake version
cmake_minimum_required(VERSION 3.20)

# 2. Define the project name and the languages we are using (C and Assembly)
project(IndustrialEdgeNode LANGUAGES C ASM)

# 3. Prevent beginners from doing "in-source" builds (messing up the source folders)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are forbidden. Please create a 'build' folder and run CMake from there.")
endif()

# 4. Global Compiler Definitions (Applies to all sub-folders)
# Define the STM32F446xx flag so the ST HAL headers know which exact chip we are using
add_compile_definitions(STM32F446xx)

# 5. Tell CMake to go look inside these folders for more CMake instructions
# (We will create these next)
add_subdirectory(bootloader)