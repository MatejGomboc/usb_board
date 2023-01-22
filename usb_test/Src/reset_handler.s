.syntax unified
.cpu cortex-m0
.thumb

.section .text, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr r1, =__stack_end__
    ldr r2, =__data_start__
    ldr r3, =__data_end__
    subs r3, r2
    ble loop_set_data_done
loop_set_data:
    subs r3, #4
    ldr r0, [r1,r3]
    str r0, [r2,r3]
    bgt loop_set_data
loop_set_data_done:
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__
    movs r0, 0
    subs r2, r1
    ble loop_set_bss_done
loop_set_bss:
    subs r2, #4
    str r0, [r1, r2]
    bgt loop_set_bss
loop_set_bss_done:
    bl main
loop_forever:
    b loop_forever

.size Reset_Handler, . - Reset_Handler
