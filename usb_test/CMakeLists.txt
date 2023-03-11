cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi.cmake)

project(usb_test LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 18)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${CMAKE_PROJECT_NAME}
    isr_vectors.s
    reset_handler.s
    default_handler.cpp
    main.cpp
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:
        -mcpu=cortex-m0
        -x assembler-with-cpp
        --specs=nano.specs
        -mfloat-abi=soft
        -mthumb
    >

    $<$<COMPILE_LANGUAGE:C>:
        -mcpu=cortex-m0
        -std=gnu18
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Release>:-Os>
        -ffunction-sections
        -fdata-sections
        -fno-strict-aliasing
        -Wall
        -Wextra
        -pedantic
        -pedantic-errors
        -Wmissing-include-dirs
        -Wconversion
        -fPIC
        -fstack-usage
        --specs=nano.specs
        -mfloat-abi=soft
        -mthumb
    >

    $<$<COMPILE_LANGUAGE:CXX>:
        -mcpu=cortex-m0
        -std=gnu++20
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Release>:-Os>
        -ffunction-sections
        -fdata-sections
        -fno-strict-aliasing
        -fno-exceptions
        -fno-rtti
        -fno-threadsafe-statics
        -fno-use-cxa-atexit
        -Wall
        -Wextra
        -pedantic
        -pedantic-errors
        -Wmissing-include-dirs
        -Wconversion
        -fPIC
        -fstack-usage
        --specs=nano.specs
        -mfloat-abi=soft
        -mthumb
    >
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0
    -T${CMAKE_SOURCE_DIR}/STM32F072CBTX.ld
    --specs=nosys.specs
    #-Wl,-Map="${CMAKE_PROJECT_NAME}.map"
    -Wl,--cref
    -Wl,--gc-sections
    -static
    --specs=nano.specs
    -mfloat-abi=soft
    -mthumb
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)
