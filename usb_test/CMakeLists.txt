cmake_minimum_required(VERSION 3.24.2)

project(usb_test LANGUAGES ASM C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    vectors_table.cpp
    reset_isr.cpp
    fault_isrs.cpp
    utils.hpp
    cortexm0/exceptions.hpp
    cortexm0/special_regs.hpp
    cortexm0/nvic.hpp
    cortexm0/scb.hpp
    cortexm0/systick.hpp
    rtos/isrs.cpp
    rtos/isrs.hpp
    rtos/kernel.cpp
    rtos/kernel.hpp
    rtos/svc_numbers.hpp
    rtos/threads.cpp
    rtos/threads.hpp
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    MAX_NUM_OF_THREADS=4
    SYSTICK_PERIOD_CYCLES=1000
    MAIN_THREAD_STACK_SIZE=0x400
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:
        -mcpu=cortex-m0
        -mthumb
        -fstack-usage
        -Wmissing-include-dirs
        -masm-syntax-unified
    >

    $<$<COMPILE_LANGUAGE:C>:
        -mcpu=cortex-m0
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
        -ffreestanding
        -masm-syntax-unified
    >

    $<$<COMPILE_LANGUAGE:CXX>:
        -mcpu=cortex-m0
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
        -ffreestanding
        -fno-threadsafe-statics
        -masm-syntax-unified
    >
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0
    -T${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.ld
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -nostdlib
    -Wl,--cref
    -Wl,--gc-sections
    -static
    -Wl,--print-memory-usage
    -mfloat-abi=soft
    -mthumb
    -Wl,--defsym=__PROCESS_STACK_SIZE_SYMBOL__=0x3000
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} -A ${CMAKE_PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} --gap-fill 0 -O binary -S ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJDUMP} -S -d -l -C -z ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.asm
)
