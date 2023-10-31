.global vectors_table
.section .vectors_table, "ax", %progbits
.type vectors_table, %object

vectors_table:
    .word __GLOBAL_STACK_TOP_SYMBOL__
    .word resetIsr
    .word nmiIsr
    .word hardFaultIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word svcIsr
    .word unhandledIrqIsr
    .word unhandledIrqIsr
    .word pendSvIsr
    .word sysTickIsr
    .word wwdgIrqIsr
    .word pvdVddio2IrqIsr
    .word rtcIrqIsr
    .word flashIrqIsr
    .word rccCrsIrqIsr
    .word exti_0_1_IrqIsr
    .word exti_2_3_IrqIsr
    .word exti_4_15_IrqIsr
    .word tscIrqIsr
    .word dma1Channel_1_IrqIsr
    .word dma1Channel_2_3_IrqIsr
    .word dma1Channel_4_5_6_7_IrqIsr
    .word adc1CompIrqIsr
    .word tim1BrkUpTrgComIrqIsr
    .word tim1CcIrqIsr
    .word tim2IrqIsr
    .word tim3IrqIsr
    .word tim6DacIrqIsr
    .word tim7IrqIsr
    .word tim14IrqIsr
    .word tim15IrqIsr
    .word tim16IrqIsr
    .word tim17IrqIsr
    .word i2c1IrqIsr
    .word i2c2IrqIsr
    .word spi1IrqIsr
    .word spi2IrqIsr
    .word usart_1_IrqIsr
    .word usart_2_IrqIsr
    .word usart_3_4_IrqIsr
    .word cecCanIrqIsr
    .word usbIrqIsr

.weak wwdgIrqIsr
.thumb_set wwdgIrqIsr, unhandledIrqIsr

.weak pvdVddio2IrqIsr
.thumb_set pvdVddio2IrqIsr, unhandledIrqIsr

.weak rtcIrqIsr
.thumb_set rtcIrqIsr, unhandledIrqIsr

.weak flashIrqIsr
.thumb_set flashIrqIsr, unhandledIrqIsr

.weak rccCrsIrqIsr
.thumb_set rccCrsIrqIsr, unhandledIrqIsr

.weak exti_0_1_IrqIsr
.thumb_set exti_0_1_IrqIsr, unhandledIrqIsr

.weak exti_2_3_IrqIsr
.thumb_set exti_2_3_IrqIsr, unhandledIrqIsr

.weak exti_4_15_IrqIsr
.thumb_set exti_4_15_IrqIsr, unhandledIrqIsr

.weak tscIrqIsr
.thumb_set tscIrqIsr, unhandledIrqIsr

.weak dma1Channel_1_IrqIsr
.thumb_set dma1Channel_1_IrqIsr, unhandledIrqIsr

.weak dma1Channel_2_3_IrqIsr
.thumb_set dma1Channel_2_3_IrqIsr, unhandledIrqIsr

.weak dma1Channel_4_5_6_7_IrqIsr
.thumb_set dma1Channel_4_5_6_7_IrqIsr, unhandledIrqIsr

.weak adc1CompIrqIsr
.thumb_set adc1CompIrqIsr, unhandledIrqIsr

.weak tim1BrkUpTrgComIrqIsr
.thumb_set tim1BrkUpTrgComIrqIsr, unhandledIrqIsr

.weak tim1CcIrqIsr
.thumb_set tim1CcIrqIsr, unhandledIrqIsr

.weak tim2IrqIsr
.thumb_set tim2IrqIsr, unhandledIrqIsr

.weak tim3IrqIsr
.thumb_set tim3IrqIsr, unhandledIrqIsr

.weak tim6DacIrqIsr
.thumb_set tim6DacIrqIsr, unhandledIrqIsr

.weak tim7IrqIsr
.thumb_set tim7IrqIsr, unhandledIrqIsr

.weak tim14IrqIsr
.thumb_set tim14IrqIsr, unhandledIrqIsr

.weak tim15IrqIsr
.thumb_set tim15IrqIsr, unhandledIrqIsr

.weak tim16IrqIsr
.thumb_set tim16IrqIsr, unhandledIrqIsr

.weak tim17IrqIsr
.thumb_set tim17IrqIsr, unhandledIrqIsr

.weak i2c1IrqIsr
.thumb_set i2c1IrqIsr, unhandledIrqIsr

.weak i2c2IrqIsrs
.thumb_set i2c2IrqIsr, unhandledIrqIsr

.weak spi1IrqIsr
.thumb_set spi1IrqIsr, unhandledIrqIsr

.weak spi2IrqIsr
.thumb_set spi2IrqIsr, unhandledIrqIsr

.weak usart_1_IrqIsr
.thumb_set usart_1_IrqIsr, unhandledIrqIsr

.weak usart_2_IrqIsr
.thumb_set usart_2_IrqIsr, unhandledIrqIsr

.weak usart_3_4_IrqIsr
.thumb_set usart_3_4_IrqIsr, unhandledIrqIsr

.weak cecCanIrqIsr
.thumb_set cecCanIrqIsr, unhandledIrqIsr

.weak usbIrqIsr
.thumb_set usbIrqIsr, unhandledIrqIsr
