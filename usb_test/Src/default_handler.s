.syntax unified
.global Default_Handler

/**
 * This code gets called when the processor receives an unexpected interrupt.
 * The code simply enters an infinite loop, preserving the system state for
 * inspection by a debugger.
 */
.section .text.Default_Handler, "ax", %progbits
.type Default_Handler, %function
Default_Handler:
Infinite_Loop:
    b Infinite_Loop
