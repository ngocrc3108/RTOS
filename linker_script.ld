MEMORY
{
    ROM (wx) : ORIGIN = 0x8000000, LENGTH = 64K
    RAM (!w) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .vector_table : ALIGN(4)
    {
        *(.vector_table)
    } > ROM
    .text : ALIGN(4)
    {
        *(.reset_handler)
        *(.text)
        . = ALIGN(4);
    } > ROM
    .data : ALIGN(4)
    {
        *(.data)
    } > RAM AT> ROM
    __data_start_address = LOADADDR(.data);
    __data_size = SIZEOF(.data);
    .bss : ALIGN(4)
    {
        __bss_start_address = .;
        *(.bss)
        . = ALIGN(4);
        __heap_start_address = .;
    } > RAM
    __bss_size = SIZEOF(.bss);
}