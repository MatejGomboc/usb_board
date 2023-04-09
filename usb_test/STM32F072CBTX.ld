MEMORY {
    FLASH  (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 16K
}

OUTPUT_FORMAT("elf32-littlearm")

ENTRY(resetHandler)

SECTIONS {
    .isr_vectors : {
        . = ALIGN(4);
        KEEP(*(.isr_vectors));
        . = ALIGN(4);
    } > FLASH

    .text : {
        . = ALIGN(4);
        __text_start = .;

        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)
        *(.gnu.linkonce.t.*)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        __text_end = .;
    } > FLASH

    .rodata : {
        . = ALIGN(4);
        __rodata_start = .;

        *(.rodata)
        *(.rodata*)
        *(.gnu.linkonce.r.*)

        . = ALIGN(4);
        __rodata_end = .;
    } > FLASH

    .ARM.extab : {
        *(.ARM.extab*)
        *(.gnu.linkonce.armextab.*)
    } > FLASH

    .ARM : {
        __exidx_start = .;
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH

    .preinit_array : {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > FLASH

    .init_array : {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > FLASH

	.fini_array : {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > FLASH

    __data_flash_start = LOADADDR(.data);

    .data : {
        . = ALIGN(4);
        __data_start = .;

        *(.data)
        *(.data*)
        *(.RamFunc)
        *(.RamFunc*)

        . = ALIGN(4);
        __data_end = .;
    } > RAM AT> FLASH

    .bss : {
        . = ALIGN(4);
        __bss_start = .;
        __bss_start__ = __bss_start;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        __bss_end = .;
        __bss_end__ = __bss_end;

        PROVIDE(end = .);
        PROVIDE(_end = .);
    } > RAM

    __stack_start = ORIGIN(RAM) + SIZEOF(.data) + SIZEOF(.bss);
    __stack_end = ORIGIN(RAM) + LENGTH(RAM);
    __stack_size = LENGTH(RAM) - SIZEOF(.data) - SIZEOF(.bss);

    /DISCARD/ : {
        libc.a(*)
        libm.a(*)
        libgcc.a(*)
    }

    .ARM.attributes 0 : {
        *(.ARM.attributes)
    }
}
