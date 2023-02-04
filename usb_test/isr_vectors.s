.syntax unified
.cpu cortex-m0
.thumb

.section .isr_vectors, "a", %progbits
.global isr_vectors
.type isr_vectors, %object
isr_vectors:
    .word __stack_end__
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word SVC_Handler
    .word Default_Handler
    .word Default_Handler
    .word PendSV_Handler
    .word SysTick_Handler
    .word WWDG_IRQHandler                /* Window Watchdog interrupt                             */
    .word PVD_IRQHandler                 /* PVD and VDDIO2 supply comparator interrupt            */
    .word RTC_IRQHandler                 /* RTC interrupts                                        */
    .word FLASH_IRQHandler               /* Flash global interrupt                                */
    .word RCC_CRS_IRQHandler             /* RCC and CRS global interrupts                         */
    .word EXTI0_1_IRQHandler             /* EXTI Line[1:0] interrupts                             */
    .word EXTI2_3_IRQHandler             /* EXTI Line[3:2] interrupts                             */
    .word EXTI4_15_IRQHandler            /* EXTI Line15 and EXTI4 interrupts                      */
    .word TSC_IRQHandler                 /* Touch sensing interrupt                               */
    .word DMA1_CH1_IRQHandler            /* DMA1 channel 1 interrupt                              */
    .word Default_Handler
    .word Default_Handler
    .word ADC_COMP_IRQHandler            /* ADC and comparator interrupts                         */
    .word TIM1_BRK_UP_TRG_COM_IRQHandler /* TIM1 break, update, trigger and commutation interrupt */
    .word TIM1_CC_IRQHandler             /* TIM1 Capture Compare interrupt                        */
    .word TIM2_IRQHandler                /* TIM2 global interrupt                                 */
    .word TIM3_IRQHandler                /* TIM3 global interrupt                                 */
    .word TIM6_DAC_IRQHandler            /* TIM6 global interrupt and DAC underrun interrupt      */
    .word TIM7_IRQHandler                /* TIM7 global interrupt                                 */
    .word TIM14_IRQHandler               /* TIM14 global interrupt                                */
    .word TIM15_IRQHandler               /* TIM15 global interrupt                                */
    .word TIM16_IRQHandler               /* TIM16 global interrupt                                */
    .word TIM17_IRQHandler               /* TIM17 global interrupt                                */
    .word I2C1_IRQHandler                /* I2C1 global interrupt                                 */
    .word I2C2_IRQHandler                /* I2C2 global interrupt                                 */
    .word SPI1_IRQHandler                /* SPI1_global_interrupt                                 */
    .word SPI2_IRQHandler                /* SPI2 global interrupt                                 */
    .word USART1_IRQHandler              /* USART1 global interrupt                               */
    .word USART2_IRQHandler              /* USART2 global interrupt                               */
    .word USART3_4_IRQHandler            /* USART3 and USART4 global interrupt                    */
    .word CEC_CAN_IRQHandler             /* CEC and CAN global interrupt                          */
    .word USB_IRQHandler                 /* USB global interrupt                                  */

.size isr_vectors, . - isr_vectors

.weak NMI_Handler
.thumb_set NMI_Handler, Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler

.weak SVC_Handler
.thumb_set SVC_Handler, Default_Handler

.weak PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler

.weak WWDG_IRQHandler
.thumb_set WWDG_IRQHandler, Default_Handler

.weak PVD_IRQHandler
.thumb_set PVD_IRQHandler, Default_Handler

.weak RTC_IRQHandler
.thumb_set RTC_IRQHandler, Default_Handler

.weak FLASH_IRQHandler
.thumb_set FLASH_IRQHandler, Default_Handler

.weak RCC_CRS_IRQHandler
.thumb_set RCC_CRS_IRQHandler, Default_Handler

.weak EXTI0_1_IRQHandler
.thumb_set EXTI0_1_IRQHandler, Default_Handler

.weak EXTI2_3_IRQHandler
.thumb_set EXTI2_3_IRQHandler, Default_Handler

.weak EXTI4_15_IRQHandler
.thumb_set EXTI4_15_IRQHandler, Default_Handler

.weak TSC_IRQHandler
.thumb_set TSC_IRQHandler, Default_Handler

.weak DMA1_CH1_IRQHandler
.thumb_set DMA1_CH1_IRQHandler, Default_Handler

.weak ADC_COMP_IRQHandler
.thumb_set ADC_COMP_IRQHandler, Default_Handler

.weak TIM1_BRK_UP_TRG_COM_IRQHandler
.thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler, Default_Handler

.weak TIM1_CC_IRQHandler
.thumb_set TIM1_CC_IRQHandler, Default_Handler

.weak TIM2_IRQHandler
.thumb_set TIM2_IRQHandler, Default_Handler

.weak TIM3_IRQHandler
.thumb_set TIM3_IRQHandler, Default_Handler

.weak TIM6_DAC_IRQHandler
.thumb_set TIM6_DAC_IRQHandler, Default_Handler

.weak TIM7_IRQHandler
.thumb_set TIM7_IRQHandler, Default_Handler

.weak TIM14_IRQHandler
.thumb_set TIM14_IRQHandler, Default_Handler

.weak TIM15_IRQHandler
.thumb_set TIM15_IRQHandler, Default_Handler

.weak TIM16_IRQHandler
.thumb_set TIM16_IRQHandler, Default_Handler

.weak TIM17_IRQHandler
.thumb_set TIM17_IRQHandler, Default_Handler

.weak I2C1_IRQHandler
.thumb_set I2C1_IRQHandler, Default_Handler

.weak I2C2_IRQHandler
.thumb_set I2C2_IRQHandler, Default_Handler

.weak SPI1_IRQHandler
.thumb_set SPI1_IRQHandler, Default_Handler

.weak SPI2_IRQHandler
.thumb_set SPI2_IRQHandler, Default_Handler

.weak USART1_IRQHandler
.thumb_set USART1_IRQHandler, Default_Handler

.weak USART2_IRQHandler
.thumb_set USART2_IRQHandler, Default_Handler

.weak USART3_4_IRQHandler
.thumb_set USART3_4_IRQHandler, Default_Handler

.weak CEC_CAN_IRQHandler
.thumb_set CEC_CAN_IRQHandler, Default_Handler

.weak USB_IRQHandler
.thumb_set USB_IRQHandler, Default_Handler
