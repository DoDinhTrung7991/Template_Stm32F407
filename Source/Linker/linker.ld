ENTRY(Reset_Handler)

_Min_heap_size = 0x200;
_Min_stack_size = 0x400;

MEMORY
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 1024K /* 1MB FLASH size */
    SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K  /* 128KB SRAM */
    CCMRAM (rwx): ORIGIN = 0x10000000, LENGTH = 64K /* 64KB CCMRAM */
}

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    _sidata = _etext;

    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(COMMON)
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    _sccm_lma = _sidata + SIZEOF(.data);
    _ccmram_sidata = _sccm_lma;

    .ccmram_data : AT(_sccm_lma)
    {
        _ccmram_sdata = .;
        *(.ccmram_data*)
        . = ALIGN(4);
        _ccmram_edata = .;
    } > CCMRAM

    .ccmram_bss (NOLOAD):
    {
        _ccmram_sbss = .;
        *(.ccmram_bss*)
        . = ALIGN(4);
        _ccmram_ebss = .;
    } > CCMRAM

    .heap (NOLOAD):
    {
        _heap_start = .;
        . += _Min_heap_size;
        . = ALIGN(8);
        _heap_end = .;
    } > SRAM

    .stack (NOLOAD):
    {
        _estack = ORIGIN(SRAM) + LENGTH(SRAM);
        _stack_start = _estack - _Min_stack_size;
        . = _stack_start;
        . += _Min_stack_size;
    } > SRAM
}

ASSERT(_heap_end <= _stack_start, "Heap and stack collision")
ASSERT((SIZEOF(.isr_vector) + SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.ccmram_data)) <= LENGTH(FLASH), "Not enough FLASH")
ASSERT((SIZEOF(.data) + SIZEOF(.bss) + _Min_heap_size + _Min_stack_size) <= LENGTH(SRAM), "Not enough SRAM")
ASSERT((SIZEOF(.ccmram_data) + SIZEOF(.ccmram_bss)) <= LENGTH(CCMRAM), "Not enough CCMRAM")
