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
        build/src/hasm*.o(.text);
        build/libultra/src*.o(.text);
        build/asm/data/ucode_audio.s.o(.text);
        build/asm/data/ucode_boot.s.o(.text);
        build/asm/data/ucode_f3ddkr_dram.s.o(.text);
        build/asm/data/ucode_f3ddkr_fifo.s.o(.text);
        build/asm/data/ucode_f3ddkr_xbus.s.o(.text);
        build/asm/data/ucode_unknown_2.s.o(.text);
        /* Data */
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        build/src/hasm/entrypoint.s.o(.data);
        build/src*.o(.data*);
        build/src/hasm*.o(.data*);
        build/libultra/src*.o(.data);
        build/asm/data/data_audio.s.o(.data);
        build/asm/data/data_f3ddkr_dram.s.o(.data);
        build/asm/data/data_f3ddkr_fifo.s.o(.data);
        build/asm/data/data_f3ddkr_xbus.s.o(.data);
        build/asm/data/data_unknown_2.s.o(.data);
        /* Rodata */
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_RODATA_START = .;
        build/src/hasm/entrypoint.s.o(.rodata);
        build/src*.o(.rodata*);
        build/src/hasm*.o(.rodata*);
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
        /* This hacky override is needed for the game to boot currently. TODO: fix bss.*/
        build/src/audio_spatial.c.o(.bss);
        build/src/objects.c.o(.bss);

        build/src*.o(.*bss*);
        build/src/hasm*.o(.*bss*);
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

    /DISCARD/ :
    {
        *(*);
    }
}
