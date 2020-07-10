# Diddy Kong Racing

This repo contains a work-in-progress decompilation of Diddy Kong Racing for the N64. You will need to have a original copy of the ROM to extract the game's assets.

Currently, only the US 1.0 version of the game is supported. US 1.1, EU 1.0, EU 1.1, and JP are not supported at this time.

---

## Dependencies

* `gcc`
* `make`
* `python3 (latest version)`
* `binutils-mips`
* `libssl-dev`

### Debian / Ubuntu

`sudo apt install build-essential pkg-config git binutils-mips-linux-gnu python3 libssl-dev`

#### qemu-irix

Download qemu-irix `.deb` package here: https://github.com/n64decomp/qemu-irix/releases

Then install it by running `sudo dpkg -i qemu-irix-2.11.0-2169-g32ab296eef_amd64.deb`

## Setup
1. Place the ROM file within the `baseroms` directory.  
    **a.** Any DKR ROM should work as long as it is US 1.0.  
    **b.** The name of the ROM file does not matter. It will be detected automatically from an md5 checksum.  
    **c.** If you use a byte-swapped or little-endian ROM, then it will automatically be converted to a big-endian (.z64) ROM file.  
2. Run `./setup.sh` in the main directory.  
    **a.** All of the tools within `/tools/` will be built.  
    **b.** Assets from the original DKR rom will be extracted into the generated `/assets/` folder.  
    **c.** Lastly, the linker file `dkr.ld` will be generated  
  
If you see the message `Setup complete!`, then you are ready to build.

## Build

To build the ROM, you just simply type in `make` in the main directory. You should see an `OK` at the end of the build if it worked correctly. The generated ROM file should appear in the `/build/` folder. 

## Assets

See the [ASSETS_README.md](ASSETS_README.md) file for more information on the assets within this decompilation.

## Scripts

There are some useful scripts that should be kept in mind when working on this repo.

---

#### `./generate_ld.sh`

This script will generate the linker file `dkr.ld`, which is used for building. You will need to call this when you add or remove files from the `/asm/` or `/src/` directories.

---

#### `./extract.sh`

This script will extract all the assets from the DKR ROM and place them into `/assets/` folder according to the extract-config file within the `/extract-ver/` folder. You will need to run this every time you update one of the `.extract-config` files.

Note 1: You do not need to call `./generate_ld.sh`, since that is done automatically from this script.  
Note 2: The `/assets/` folder will get deleted if it already exists, so don't put anything important in there! 

---

#### `./rename_sym.sh <old_symbol> <new_symbol>`

This script will rename an existing symbol within the repo with a new one.

Example: `./rename_sym.sh D_A4001000 SP_IMEM`

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

* Decompiling the asm files into matching c files.
* Split the asm files into smaller ones. This has been partially done, but nowhere near complete.

### Minor

What can be done, but not essential.

* Create file formats for all the assets files, instead of just having .bin files.
* Figuring out the unknown .bin files within the /assets/bin/ directory.

### Future

These features won't be complete anytime soon.

* Make the ROM shiftable.
* Add support for the other 4 versions.
