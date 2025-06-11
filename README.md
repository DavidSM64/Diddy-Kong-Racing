# Diddy Kong Racing

This repo contains a work-in-progress decompilation of Diddy Kong Racing for the N64. You will need to have a original copy of the ROM to extract the game's assets.

All versions are supported, and the US 1.0 version (SHA1 = 0cb115d8716dbbc2922fda38e533b9fe63bb9670) of the game is the default if not specified.

<!-- README_SCORE_SUMMARY_BEGIN -->
As of June 11, 2025, this is our current score:

&emsp;&emsp;&emsp;&emsp;Decomp progress: 91.33%

&emsp;&emsp;&emsp;&emsp;Documentation progress: 59.40%
<!-- README_SCORE_SUMMARY_END -->

---

## Dependencies

* `gcc`, Version 8.0 or higher
* `make`, Version 4.2 or higher
* `python3`
* `libpcre2-dev` and `libpcre2-8-0` (Not technically required, but will speedup extracting/building some assets.)
* `gcc-mips-linux-gnu` is optionally used if compiling NON_MATCHING with COMPILER=gcc

`sudo apt install build-essential pkg-config git python3 python3-pip binutils-mips-linux-gnu python3-venv libpcre2-dev libpcre2-8-0`

## Setup / Building
1. Install the dependencies
2. Place the ROM file within the `baseroms` directory.  
    **a.** The name of the ROM file does not matter. It will be detected automatically from an sha1 checksum.  
3. Grab tools: `git submodule update --init --recursive`
4. Run `make setup` to install the IDO compiler, python venv, and packages required.
5. Run `make extract` to run splat to extract all required files from the baserom.
6. Run `make` in the main directory.  
    **a.** Use the `-jN` argument to use `N` number of threads to speed up building. For example, if you have a system with 4 cores / 4 threads, you should do `make -j4`.

### Building on macOS
1. Use homebrew to install dependencies: `brew install make`
2. Place the ROM file within the `baseroms` directory. See [Setup](#setup--building) above for more info.
3. Run `gmake` from the main directory. Note that macOS built-in `make` will not work since it does not meet the version requirements.

### Building other versions
To build other versions of the ROM, just specifcy the region and version in the make command. All examples are below:
Baserom|REGION|VERSION|Command
---|--|---|-
US 1.0 | US | v77 | `make REGION=US VERSION=v77`
PAL 1.0 | PAL | v77 | `make REGION=PAL VERSION=v77`
JPN 1.0 | JPN | v79 | `make REGION=JPN VERSION=v79`
US 1.1 | US | v80 | `make REGION=US VERSION=v80`
PAL 1.1 | PAL | v80 | `make REGION=PAL VERSION=v80`  

## Modding
If you are modifying the code in the repo, then you should add `NON_MATCHING=1` to the make command.  
Example: `make NON_MATCHING=1 -j4`  
  
The `NON_MATCHING` define will include the functions that don't exactly match one-to-one, but should be no different functionality-wise. If you do notice any bugs that occur in a `NON_MATCHING` build that are not in the vanilla game, then please file an issue describing the bug. It would be helpful if you can track down which function is causing the bug, but that is not required.

## Style Guide

The style guide for the project can be found here: https://docs.google.com/document/d/1euQf8nwynGcCZL1MfoMaLs-XRvx3ejjj8fIfykUZ-NQ

If you see variables/functions/structs/etc. that doesn't follow these rules, then file an issue and we'll try to fix them.

## Scripts

There are some useful scripts that should be kept in mind when working on this repo.

---

#### `./extract.sh <version>`

This script will extract all the assets from a DKR ROM and place them into `/assets/` folder according to the config file within the `/extract-ver/` folder. The version parameter should either be `us_1.0`, `us_1.1`, `eu_1.0`, `eu_1.1`, or `jp`.

Example: `./extract.sh us_1.0`

---

#### `./diff.sh <function_name>`

Compares the assembly output of a function from a built ROM to the base ROM. Useful for decompiling.

Example: `./diff.sh menu_init`

---

#### `./rename.sh <old_name> <new_name>`

This script will rename an existing symbol, file name, and/or folder name within the repo with a new one.

Example: `./rename.sh D_A4001000 SP_IMEM`

---

#### `./score.sh`

Prints out the current completion percentage of the decomp. You do need to have an `OK` build for this to work properly.

The scoring is split into 2 sections: 
1. Assembly to C Decompilation (Adventure One)
2. Cleanup and Documentation (Adventure Two)

Show scores for Adventure One & Adventure Two: `./score.sh`  
Show score for Adventure One only: `./score.sh -a 1`  
Show score for Adventure Two only: `./score.sh -a 2`  
Show top 10 files remaining: `./score.sh -t 10`  

To make progress in Adventure 2, a function must be properly named (must not start with `func_`) and also include a doxygen comment above it.

For example:
```c
/**
 * Returns 1 if Drumstick is avaliable to use, or 0 if not.
 */
s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
```

<!-- README_SCORE_BEGIN -->
As of June 11, 2025, this is our current score:
```
 =====================================================================
                ADVENTURE ONE (ASM -> C Decompilation)
 --------------- 91.33% Complete (92.11% NON_MATCHING) ---------------
                     # Decompiled functions: 1914
                      # GLOBAL_ASM remaining: 36
                      # NON_MATCHING functions: 4
                  # NON_EQUIVALENT WIP functions: 29
 ---------------------------- Game Status ----------------------------
               Balloons: 43/47, Keys: 4/4, Trophies: 4/5
                T.T. Amulets: 4/4, Wizpig Amulets: 4/4
 ---------------------------------------------------------------------
 We are collecting silver coins in Spacedust Alley. (2/8 silver coins)
 =====================================================================
                 ADVENTURE TWO (Cleanup & Documentation)
 -------------------------- 59.40% Complete --------------------------
                     # Documented functions: 1208
                     # Undocumented remaining: 445
 ---------------------------- Game Status ----------------------------
               Balloons: 29/47, Keys: 3/4, Trophies: 2/5
                T.T. Amulets: 3/4, Wizpig Amulets: 2/4
 ---------------------------------------------------------------------
 We are collecting silver coins in Treasure Caves. (1/8 silver coins)
 =====================================================================
```
<!-- README_SCORE_END -->
