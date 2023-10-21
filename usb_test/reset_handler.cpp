#include <cstdint>

extern uint32_t* const __DATA_START__;
extern uint32_t* const __DATA_END__;
extern uint32_t* const __DATA_FLASH_START__;

extern uint32_t* const __BSS_START__;
extern uint32_t* const __BSS_END__;

extern void (* const __INIT_ARRAY_START__[])();
extern void (* const __INIT_ARRAY_END__[])();

extern "C" void resetHandler()
{
    // copy the initialized global variables to RAM
    for (int32_t offset = 0; offset < __DATA_END__ - __DATA_START__; offset++) {
        uint32_t* addr_flash = __DATA_FLASH_START__ + offset;
        uint32_t* addr_ram = __DATA_START__ + offset;
        *addr_ram = *addr_flash;
    }

    // fill uninitialized variables in RAM with zeros
    for (uint32_t* addr = __BSS_START__; addr < __BSS_END__; addr++) {
        *addr = 0;
    }

    // initialize static objects by calling their constructors
    for (int32_t i = 0; i < __INIT_ARRAY_END__ - __INIT_ARRAY_START__; i++) {
        __INIT_ARRAY_START__[i]();
    }

    // call the main function
    asm volatile ("bl main");
}
