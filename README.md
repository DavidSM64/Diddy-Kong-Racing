# Diddy Kong Racing

This repo contains a work-in-progress decompilation of Diddy Kong Racing for the N64. You will need to have a original copy of the ROM.

Currently, only the US 1.0 version of the game is supported. US 1.1, EU 1.0, EU 1.1, and JP are not supported at this time.

---

## Setup

1. Place the ROM file within the `baseroms` directory.  
    **a.** Any DKR ROM should work as long as it is US 1.0.  
    **b.** The name of the ROM file does not matter. It will be detected automatically from an md5 checksum.  
    **c.** If you use a byte-swapped or little-endian ROM, then it will automatically be converted to a big-endian (.z64) ROM file.  
2. Install the latest version of python 3 and binutils.  
    **a.** Arch users should install: `mips64-elf-binutils`  
    **b.** Ubuntu/Debian users should install: `binutils-mips-linux-gnu`  
    **c.** RHEL/CentOS/Fedora users should install: `gcc-mips64-linux-gnu`  
3. Finally, run `./setup.sh` in the main directory.  
    **a.** All of the tools within `/tools/` will be built.  
    **b.** Assets from the original DKR rom will be extracted into the generated `/assets/` folder.  
    **c.** Lastly, the linker file `dkr.ld` will be generated  
  
If you see the message `Setup complete!`, then you are ready to build.

## Build

To build the ROM, you just simply type in `make` in the main directory. You should see an `OK` at the end of the build if it worked correctly. The generated ROM file should appear in the generated `/build/` folder. 

## Scripts

This repo provides some useful scripts that should be kept in mind when working on this repo.

---

#### `./generate_ld.sh`

This script will generate the linker file `dkr.ld`, which is used for building. You will need to call this when you add or remove files from the `/asm/` directory.

---

#### `./extract.sh`

This script will extract all the assets from the DKR ROM and place them into `/assets/` folder according to the extract-config file within the `/extract-ver/` folder. You will need to run this every time you update one of the `.extract-config` files.

Note 1: You do not need to call `./generate_ld.sh`, since that is done automatically from this script.
Note 2: The `/assets/` folder will get deleted if it already exists, so don't put anything important in there! 

---

#### `./rename_symbol.sh <old_symbol> <new_symbol>`

This script will rename an existing symbol within `undefined_syms.txt` and all the `.s` files within the `/asm/` directory.

Example: `./rename_symbol.sh D_A4001000 SP_IMEM`

---

#### `./get_symbol.sh <ram_address>`

Will return the symbol associated with the RAM address within `undefined_syms.txt`. The RAM address must be in base 16. The `0x` prefix is not required.

Example: 
```
./get_symbol.sh 0xA4001000
0xA4001000 = SP_IMEM
```

---

## TODO list

TODO: Add more things to the TODO list.

### Major

What should be focused on.

* Determine and integrate the compiler used for the game.
* Determine all of the assets used, instead of just having unknown `.bin` files.

### Minor

What can be done, but not essential.

* Split the asm files into smaller ones. This has been partially done, but nowhere near complete.
* Determine the compression format used for levels and objects.

### Future

These features won't be complete anytime soon.

* Make the ROM shiftable.
* Add support for the other 4 versions.