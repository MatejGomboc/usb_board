#include <cstdint>

extern int __DATA_START_SYMBOL__;
extern int __DATA_END_SYMBOL__;
extern int __DATA_FLASH_START_SYMBOL__;

extern int __BSS_START_SYMBOL__;
extern int __BSS_END_SYMBOL__;

extern int __GLOBAL_STACK_BOTTOM_SYMBOL__;
extern int __GLOBAL_STACK_SIZE_SYMBOL__;
extern int __GLOBAL_STACK_TOP_SYMBOL__;

extern int __PROCESS_STACK_BOTTOM_SYMBOL__;
extern int __PROCESS_STACK_SIZE_SYMBOL__;
extern int __PROCESS_STACK_TOP_SYMBOL__;

extern int __MAIN_STACK_BOTTOM_SYMBOL__;
extern int __MAIN_STACK_SIZE_SYMBOL__;
extern int __MAIN_STACK_TOP_SYMBOL__;

extern uint32_t* const __DATA_START__{ reinterpret_cast<uint32_t*>(&__DATA_START_SYMBOL__) };
extern uint32_t* const __DATA_END__{ reinterpret_cast<uint32_t*>(&__DATA_END_SYMBOL__) };
extern uint32_t* const __DATA_FLASH_START__{ reinterpret_cast<uint32_t*>(&__DATA_FLASH_START_SYMBOL__) };

extern uint32_t* const __BSS_START__{ reinterpret_cast<uint32_t*>(&__BSS_START_SYMBOL__) };
extern uint32_t* const __BSS_END__{ reinterpret_cast<uint32_t*>(&__BSS_END_SYMBOL__) };

extern uint32_t* const __GLOBAL_STACK_BOTTOM__{ reinterpret_cast<uint32_t*>(&__GLOBAL_STACK_BOTTOM_SYMBOL__) };
extern const uint32_t __GLOBAL_STACK_SIZE__{ reinterpret_cast<uint32_t>(&__GLOBAL_STACK_SIZE_SYMBOL__) };
extern uint32_t* const __GLOBAL_STACK_TOP__{ reinterpret_cast<uint32_t*>(&__GLOBAL_STACK_TOP_SYMBOL__) };

extern uint32_t* const __PROCESS_STACK_BOTTOM__{ reinterpret_cast<uint32_t*>(&__PROCESS_STACK_BOTTOM_SYMBOL__) };
extern const uint32_t __PROCESS_STACK_SIZE__{ reinterpret_cast<uint32_t>(&__PROCESS_STACK_SIZE_SYMBOL__) };
extern uint32_t* const __PROCESS_STACK_TOP__{ reinterpret_cast<uint32_t*>(&__PROCESS_STACK_TOP_SYMBOL__) };

extern uint32_t* const __MAIN_STACK_BOTTOM__{ reinterpret_cast<uint32_t*>(&__MAIN_STACK_BOTTOM_SYMBOL__) };
extern const uint32_t __MAIN_STACK_SIZE__{ reinterpret_cast<uint32_t>(&__MAIN_STACK_SIZE_SYMBOL__) };
extern uint32_t* const __MAIN_STACK_TOP__{ reinterpret_cast<uint32_t*>(&__MAIN_STACK_TOP_SYMBOL__) };
