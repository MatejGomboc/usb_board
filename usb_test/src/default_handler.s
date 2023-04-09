.syntax unified
.global defaultHandler

/**
 * This code gets called when the processor receives an unexpected interrupt.
 * The code simply enters an infinite loop, preserving the system state for
 * inspection by a debugger.
 */
.section .text.defaultHandler, "ax", %progbits
.type defaultHandler, %function
defaultHandler:
    b defaultHandler
