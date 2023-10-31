#pragma once

#include <cstdint>

extern uint32_t* const __DATA_START__;
extern uint32_t* const __DATA_END__;
extern uint32_t* const __DATA_FLASH_START__;

extern uint32_t* const __BSS_START__;
extern uint32_t* const __BSS_END__;

extern void (* const __INIT_ARRAY_START__[])();
extern void (* const __INIT_ARRAY_END__[])();

extern uint32_t* const __GLOBAL_STACK_BOTTOM__;
extern const uint32_t __GLOBAL_STACK_SIZE__;
extern uint32_t* const __GLOBAL_STACK_TOP__;

extern uint32_t* const __PROCESS_STACK_BOTTOM__;
extern const uint32_t __PROCESS_STACK_SIZE__;
extern uint32_t* const __PROCESS_STACK_TOP__;

extern uint32_t* const __MAIN_STACK_BOTTOM__;
extern const uint32_t __MAIN_STACK_SIZE__;
extern uint32_t* const __MAIN_STACK_TOP__;

extern int main();
