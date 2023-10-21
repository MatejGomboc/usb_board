.global vectors_table
.section .vectors_table, "ax", %progbits
.type vectors_table, %object

vectors_table:
    .word __STACK_END__
    .word resetHandler
    .word nmiHandler
    .word hardFaultHandler
    .word defaultHandler
    .word defaultHandler
    .word defaultHandler
    .word defaultHandler
    .word defaultHandler
    .word defaultHandler
    .word defaultHandler
    .word svcHandler
    .word defaultHandler
    .word defaultHandler
    .word pendSvHandler
    .word sysTickHandler
    .word wwdgIrqHandler
    .word pvdVddio2IrqHandler
    .word rtcIrqHandler
    .word flashIrqHandler
    .word rccCrsIrqHandler
    .word exti_0_1_IrqHandler
    .word exti_2_3_IrqHandler
    .word exti_4_15_IrqHandler
    .word tscIrqHandler
    .word dma1Channel_1_IrqHandler
    .word dma1Channel_2_3_IrqHandler
    .word dma1Channel_4_5_6_7_IrqHandler
    .word adc1CompIrqHandler
    .word tim1BrkUpTrgComIrqHandler
    .word tim1CcIrqHandler
    .word tim2IrqHandler
    .word tim3IrqHandler
    .word tim6DacIrqHandler
    .word tim7IrqHandler
    .word tim14IrqHandler
    .word tim15IrqHandler
    .word tim16IrqHandler
    .word tim17IrqHandler
    .word i2c1IrqHandler
    .word i2c2IrqHandler
    .word spi1IrqHandler
    .word spi2IrqHandler
    .word usart_1_IrqHandler
    .word usart_2_IrqHandler
    .word usart_3_4_IrqHandler
    .word cecCanIrqHandler
    .word usbIrqHandler

.weak nmiHandler
.thumb_set nmiHandler, defaultHandler

.weak hardFaultHandler
.thumb_set hardFaultHandler, defaultHandler

.weak svcHandler
.thumb_set svcHandler, defaultHandler

.weak pendSvHandler
.thumb_set pendSvHandler, defaultHandler

.weak sysTickHandler
.thumb_set sysTickHandler, defaultHandler

.weak wwdgIrqHandler
.thumb_set wwdgIrqHandler, defaultHandler

.weak pvdVddio2IrqHandler
.thumb_set pvdVddio2IrqHandler, defaultHandler

.weak rtcIrqHandler
.thumb_set rtcIrqHandler, defaultHandler

.weak flashIrqHandler
.thumb_set flashIrqHandler, defaultHandler

.weak rccCrsIrqHandler
.thumb_set rccCrsIrqHandler, defaultHandler

.weak exti_0_1_IrqHandler
.thumb_set exti_0_1_IrqHandler, defaultHandler

.weak exti_2_3_IrqHandler
.thumb_set exti_2_3_IrqHandler, defaultHandler

.weak exti_4_15_IrqHandler
.thumb_set exti_4_15_IrqHandler, defaultHandler

.weak tscIrqHandler
.thumb_set tscIrqHandler, defaultHandler

.weak dma1Channel_1_IrqHandler
.thumb_set dma1Channel_1_IrqHandler, defaultHandler

.weak dma1Channel_2_3_IrqHandler
.thumb_set dma1Channel_2_3_IrqHandler, defaultHandler

.weak dma1Channel_4_5_6_7_IrqHandler
.thumb_set dma1Channel_4_5_6_7_IrqHandler, defaultHandler

.weak adc1CompIrqHandler
.thumb_set adc1CompIrqHandler, defaultHandler

.weak tim1BrkUpTrgComIrqHandler
.thumb_set tim1BrkUpTrgComIrqHandler, defaultHandler

.weak tim1CcIrqHandler
.thumb_set tim1CcIrqHandler, defaultHandler

.weak tim2IrqHandler
.thumb_set tim2IrqHandler, defaultHandler

.weak tim3IrqHandler
.thumb_set tim3IrqHandler, defaultHandler

.weak tim6DacIrqHandler
.thumb_set tim6DacIrqHandler, defaultHandler

.weak tim7IrqHandler
.thumb_set tim7IrqHandler, defaultHandler

.weak tim14IrqHandler
.thumb_set tim14IrqHandler, defaultHandler

.weak tim15IrqHandler
.thumb_set tim15IrqHandler, defaultHandler

.weak tim16IrqHandler
.thumb_set tim16IrqHandler, defaultHandler

.weak tim17IrqHandler
.thumb_set tim17IrqHandler, defaultHandler

.weak i2c1IrqHandler
.thumb_set i2c1IrqHandler, defaultHandler

.weak i2c2IrqHandlers
.thumb_set i2c2IrqHandler, defaultHandler

.weak spi1IrqHandler
.thumb_set spi1IrqHandler, defaultHandler

.weak spi2IrqHandler
.thumb_set spi2IrqHandler, defaultHandler

.weak usart_1_IrqHandler
.thumb_set usart_1_IrqHandler, defaultHandler

.weak usart_2_IrqHandler
.thumb_set usart_2_IrqHandler, defaultHandler

.weak usart_3_4_IrqHandler
.thumb_set usart_3_4_IrqHandler, defaultHandler

.weak cecCanIrqHandler
.thumb_set cecCanIrqHandler, defaultHandler

.weak usbIrqHandler
.thumb_set usbIrqHandler, defaultHandler
