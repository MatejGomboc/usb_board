.syntax unified
.global resetHandler

/**
 * This code is called when the processor starts following a reset event. This
 * code only copies the global variables to RAM and sets the uninitialized
 * variables to 0.
 */
.section .text.resetHandler
.type resetHandler, %function
resetHandler:
// Copy the initialized global variables to RAM
    movs r0, #0
    ldr  r1, = __data_start
    ldr  r2, = __data_end
    ldr  r3, = __data_flash_start
    b    loopCopyData

copyData:
    ldr  r4, [r3, r0]
    str  r4, [r1, r0]
    adds r0, r0, #4

loopCopyData:
    adds r4, r1, r0
    cmp  r4, r2
    bcc  copyData

// Fill uninitialized variables with zeros
    movs r0, #0
    ldr  r1, = __bss_start
    ldr  r2, = __bss_end
    b    loopFillZeroBss

fillZeroBss:
    str  r0, [r1]
    adds r1, r1, #4

loopFillZeroBss:
    cmp  r1, r2
    bcc  fillZeroBss

// Call the main function
    bl   main
