cmake_minimum_required(VERSION 3.24.2)

project(usb_test LANGUAGES ASM C CXX)

add_executable(${CMAKE_PROJECT_NAME}
    vectors_table.s
    reset_handler.cpp
    default_handler.cpp
    main.cpp
    utils.hpp
    cortexm0_exceptions.hpp
    cortexm0_special_regs.hpp
    cortexm0_nvic.hpp
    cortexm0_scb.hpp
    cortexm0_sys_tick.hpp
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:
        -mcpu=cortex-m0
        -march=armv6-m
        -mthumb
        -fstack-usage
        -Wmissing-include-dirs
        -masm-syntax-unified
    >

    $<$<COMPILE_LANGUAGE:C>:
        -mcpu=cortex-m0
        -march=armv6-m
        -std=gnu18
        -ffunction-sections
        -fdata-sections
        -Wall
        -Wextra
        -pedantic
        -Wmissing-include-dirs
        -Wswitch-enum
        -Wconversion
        -fstack-usage
        -nostdlib
        -mfloat-abi=soft
        -mthumb
        -Wshadow
        -Wno-unused-variable
        -ffreestanding
        -Wno-unused-parameter
        -Wuseless-cast
        -Wsuggest-override
        -masm-syntax-unified
    >

    $<$<COMPILE_LANGUAGE:CXX>:
        -mcpu=cortex-m0
        -march=armv6-m
        -std=gnu++20
        -ffunction-sections
        -fdata-sections
        -fno-exceptions
        -fno-rtti
        -fno-use-cxa-atexit
        -Wall
        -Wextra
        -pedantic
        -Wmissing-include-dirs
        -Wswitch-enum
        -Wconversion
        -fstack-usage
        -nostdlib
        -mfloat-abi=soft
        -mthumb
        -Wshadow
        -Wno-unused-variable
        -ffreestanding
        -fno-threadsafe-statics
        -Wno-unused-parameter
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override
        -masm-syntax-unified
    >
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0
    -march=armv6-m
    -T${CMAKE_SOURCE_DIR}/STM32F072CBTX.ld
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -nostdlib
    -Wl,--cref
    -Wl,--gc-sections
    -static
    -Wl,--print-memory-usage
    -ffreestanding
    -mthumb
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} -A ${CMAKE_PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} --gap-fill 0 -O binary -S ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJDUMP} -S -d -l -C -z ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.asm
)
