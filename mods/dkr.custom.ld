SECTIONS
{
    __romPos = 0;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        build/asm/header.s.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    boot_ROM_START = __romPos;
    boot_VRAM = ADDR(.boot);
    .boot : AT(boot_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        boot_DATA_START = .;
        build/assets/boot.bin.o(.data);
        boot_DATA_END = .;
        boot_DATA_SIZE = ABSOLUTE(boot_DATA_END - boot_DATA_START);
    }
    __romPos += SIZEOF(.boot);
    boot_ROM_END = __romPos;
    boot_VRAM_END = .;

    main_ROM_START = __romPos;
    main_VRAM = ADDR(.main);
    .main 0x80000400 : AT(main_ROM_START) SUBALIGN(16)
    {
        /* Text */
        FILL(0x00000000);
        main_TEXT_START = .;
        build/src/hasm/entrypoint.s.o(.text);
        build/src*.o(.text);
        build/libultra/src*.o(.text);
        build/asm/data/aspMain.s.o(.text);
        build/asm/data/rspboot.s.o(.text);
        build/asm/data/f3ddkr_dram.s.o(.text);
        build/asm/data/f3ddkr_fifo.s.o(.text);
        build/asm/data/f3ddkr_xbus.s.o(.text);
        build/asm/data/ucode_unknown_2.s.o(.text);
        /* Data */
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        build/src*.o(.data*);
        build/libultra/src*.o(.data);
        build/asm/data/aspMain.s.o(.data);
        build/asm/data/f3ddkr_dram.s.o(.data);
        build/asm/data/f3ddkr_fifo.s.o(.data);
        build/asm/data/f3ddkr_xbus.s.o(.data);
        build/asm/data/ucode_unknown_2.s.o(.data);
        /* Rodata */
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_RODATA_START = .;
        build/src*.o(.rodata*);
        build/libultra/src*.o(.rodata*);
        . = ALIGN(., 16);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
    }
    main_bss_VRAM = ADDR(.main_bss);
    .main_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        main_BSS_START = .;

        build/src*.o(.*bss*);
        build/libultra/src*.o(.*bss*);
        . = ALIGN(., 16);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }
    __romPos += SIZEOF(.main);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    main_ROM_END = __romPos;
    main_VRAM_END = .;

    assets_ROM_START = __romPos;
    assets_VRAM = ADDR(.assets);
    .assets main_VRAM_END : AT(assets_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        assets_DATA_START = .;
        build/assets/assets.bin.o(.data);
        assets_DATA_END = .;
        assets_DATA_SIZE = ABSOLUTE(assets_DATA_END - assets_DATA_START);
    }
    __romPos += SIZEOF(.assets);
    assets_ROM_END = __romPos;
    assets_VRAM_END = .;

    .strtab 0 :
    {
        *(.strtab);
    }
    .symtab 0 :
    {
        *(.symtab);
    }
    .shstrtab 0 :
    {
        *(.shstrtab);
    }
    .pdr 0 :
    {
        *(.pdr);
    }
    .debug 0 :
    {
        *(.debug);
    }
    .line 0 :
    {
        *(.line);
    }
    .debug_srcinfo 0 :
    {
        *(.debug_srcinfo);
    }
    .debug_sfnames 0 :
    {
        *(.debug_sfnames);
    }
    .debug_aranges 0 :
    {
        *(.debug_aranges);
    }
    .debug_pubnames 0 :
    {
        *(.debug_pubnames);
    }
    .debug_info 0 :
    {
        *(.debug_info);
    }
    .debug_abbrev 0 :
    {
        *(.debug_abbrev);
    }
    .debug_line 0 :
    {
        *(.debug_line);
    }
    .debug_line_end 0 :
    {
        *(.debug_line_end);
    }
    .debug_frame 0 :
    {
        *(.debug_frame);
    }
    .debug_str 0 :
    {
        *(.debug_str);
    }
    .debug_loc 0 :
    {
        *(.debug_loc);
    }
    .debug_macinfo 0 :
    {
        *(.debug_macinfo);
    }
    .debug_weaknames 0 :
    {
        *(.debug_weaknames);
    }
    .debug_funcnames 0 :
    {
        *(.debug_funcnames);
    }
    .debug_typenames 0 :
    {
        *(.debug_typenames);
    }
    .debug_varnames 0 :
    {
        *(.debug_varnames);
    }
    .debug_pubtypes 0 :
    {
        *(.debug_pubtypes);
    }
    .debug_ranges 0 :
    {
        *(.debug_ranges);
    }
    .debug_addr 0 :
    {
        *(.debug_addr);
    }
    .debug_line_str 0 :
    {
        *(.debug_line_str);
    }
    .debug_loclists 0 :
    {
        *(.debug_loclists);
    }
    .debug_macro 0 :
    {
        *(.debug_macro);
    }
    .debug_names 0 :
    {
        *(.debug_names);
    }
    .debug_rnglists 0 :
    {
        *(.debug_rnglists);
    }
    .debug_str_offsets 0 :
    {
        *(.debug_str_offsets);
    }
    .debug_sup 0 :
    {
        *(.debug_sup);
    }
    .gnu.attributes 0 :
    {
        *(.gnu.attributes);
    }
    .note 0 :
    {
        *(.note);
    }
    .comment 0 :
    {
        *(.comment);
    }

    /DISCARD/ :
    {
        *(.reginfo);
        *(.MIPS.abiflags);
        *(.MIPS.options);
        *(.note.gnu.build-id);
        *(.interp);
        *(.eh_frame);
        *(.mdebug);
        *(.mdebug.abi32);
        *(*);
    }
}
