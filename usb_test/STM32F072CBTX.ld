ENTRY(ResetHandler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x8000000,  LENGTH = 128K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 16K
}

__needed_heap_size__ = 0x200;
__needed_stack_size__ = 0x400;

SECTIONS
{
    .isr_vectors :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vectors))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);

        *(.text)
        *(.text*)

        *(.glue_7)
        *(.glue_7t)

        KEEP(*(.eh_frame))

        KEEP(*(.init))
        KEEP(*(.fini))

        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        . = ALIGN(4);
    } > FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .ARM.extab :
    {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } > FLASH

    .ARM :
    {
        . = ALIGN(4);
        *(.ARM.exidx*)
        . = ALIGN(4);
    } > FLASH

    .preinit_array     :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } > FLASH

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .fini_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;

        *(vtable)

        *(.data)
        *(.data*)

        *(.RamFunc)
        *(.RamFunc*)

        KEEP(*(.jcr*))

        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT > FLASH

    __data_load_start__ = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    __stack_end__ = ORIGIN(RAM) + LENGTH(RAM);

    ASSERT(__needed_heap_size__ + __needed_stack_size__ <= LENGTH(RAM) - SIZEOF(.data) - SIZEOF(.bss), "Not enough space in RAM for heap and stack.")

    /* Remove information from the compiler libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 :
    {
        *(.ARM.attributes)
    }
}
