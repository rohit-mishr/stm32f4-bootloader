# 1. Define our target executable and its source files 
# (We will write main.c shortly)
add_executable(bootloader
    main.c
    startup.c
)

# 2. Point to our custom linker script (We will write this next)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.ld)

# 3. Pass critical flags to the Linker phase
# 3. Pass critical flags to the Linker phase
target_link_options(bootloader PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/bootloader.map
    -Wl,--no-warn-rwx-segments
    -nostdlib
)

# 4. Post-Build Actions: Run objcopy to generate the .bin file, and run size
add_custom_command(TARGET bootloader POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:bootloader> ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:bootloader>
)