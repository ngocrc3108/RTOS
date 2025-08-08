SECTIONS
{
    . = 0x8000000;
    .vector_table :
    {
        *(.vector_table)
    }
    .text :
    {
        . = ALIGN(4);
        *(.reset_handler)
        *(.text)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
}