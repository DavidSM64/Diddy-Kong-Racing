# Diddy Kong Racing

This repo contains a decompilation of Diddy Kong Racing for the N64. You will need to have a original copy of the ROM to extract the game's assets.

All versions are supported, and the US 1.0 version (SHA1 = 0cb115d8716dbbc2922fda38e533b9fe63bb9670) of the game is the default if not specified.

<!-- README_SCORE_SUMMARY_BEGIN -->
As of July 25, 2026, this is our current score:

&emsp;&emsp;&emsp;&emsp;Decomp progress [us.v77]: 100.00%

&emsp;&emsp;&emsp;&emsp;Documentation progress: 66.58%
<!-- README_SCORE_SUMMARY_END -->

---


## Setup


### Dependencies

<details>

<summary> Ubuntu / Debian based Linux distros </summary>

`sudo apt install build-essential libssl-dev pkg-config git curl python3 python3-pip binutils-mips-linux-gnu gcc-mips-linux-gnu python3-venv libpcre2-dev libpcre2-8-0`

- `build-essential` / `pkg-config` are helper packages needed for make.
- `git` is used for version control.
- `curl` downloads the IDO recomp during setup.
- `python3` is needed to run python scripts
- `libpcre2-dev` and `libpcre2-8-0` are not technically required, but will speedup extracting/building some assets significantly.
- `gcc-mips-linux-gnu` is used when compiling a non-matching build with `COMPILER=gcc`.

</details>

<details>

<summary> Fedora based Linux distros </summary>

Most dependencies should already be installed by default (in fedora 44). Only thing needed was pcre2.

`sudo dnf install pcre2 pcre2-devel`

</details>


<details>

<summary> Arch based Linux distros </summary>

`sudo pacman -Syu --needed base-devel pkgconf git python python-pip python-virtualenv pcre2 yay`

For binutils you should install this package from the AUR: https://aur.archlinux.org/packages/mips64-elf-binutils

- `base-devel` / `pkgconf` are helper packages needed for make.
- `git` is used for version control.
- `python` is needed to run python scripts
- `pcre2` is not technically required, but will speedup extracting/building some assets significantly.
- `yay` is not required, but is useful for installing packages from the AUR like the binutils.
    - `yay -Syu mips64-elf-binutils`

    
</details>

<details>

<summary> MacOS </summary>

1. Install homebrew from here: https://brew.sh/
2. Install make and pcre2 using homebrew: `brew install make pcre2`
3. When running make, you MUST use `gmake` not `make`
    - For example, instead of doing `make setup` you would use `gmake setup`.
    
</details>

<details>

<summary> Windows </summary>

Windows is not natively supported. We recommend using a linux distro under the Windows Subsystem for Linux (WSL)

</details>

### Notes
- gcc needs to be version 8.0 or higher.
- make needs to be version 4.2 or higher.

### Building

1. Install the dependencies above for your system. Click on the text to reveal the instructions.
2. Place the ROM file within the `baseroms` directory.  
   **a.** The name of the ROM file does not matter. It will be detected automatically from an sha1 checksum.
3. Grab tools: `git submodule update --init --recursive`
4. Run `make setup` to install the IDO compiler, python venv, and packages required.
5. Run `make extract` to run splat to extract all required files from the baserom.
6. Run `make` in the main directory.  
   **a.** Use the `-jN` argument to use `N` number of threads to speed up building. For example, if you have a system with 4 cores / 4 threads, you should do `make -j4`.

The resulting ROM is written to `build/dkr.<region>.<version>.z64`. Run that ROM in a compatible Nintendo 64 emulator or on supported hardware; this repository does not produce a native desktop executable.

Note: If you are on MacOS, remember to use `gmake` instead of `make`!

---

### Building other versions

To build another version of the ROM, pass the same region and version to both the extraction and build commands:

Baserom|REGION|VERSION|Extraction|Build
---|--|---|---|-
US 1.0 | US | v77 | `make cleanextract REGION=us VERSION=v77` | `make REGION=us VERSION=v77`
PAL 1.0 | PAL | v77 | `make cleanextract REGION=pal VERSION=v77` | `make REGION=pal VERSION=v77`
JPN 1.0 | JPN | v79 | `make cleanextract REGION=jpn VERSION=v79` | `make REGION=jpn VERSION=v79`
US 1.1 | US | v80 | `make cleanextract REGION=us VERSION=v80` | `make REGION=us VERSION=v80`
PAL 1.1 | PAL | v80 | `make cleanextract REGION=pal VERSION=v80` | `make REGION=pal VERSION=v80`

## Modding

If you are modifying the code in the repo, then you should add `NON_MATCHING=1` to the make command:

```sh
make clean
make NON_MATCHING=1 -j4
```

The `NON_MATCHING` define will include the functions that don't exactly match one-to-one, but should be no different functionality-wise. If you do notice any bugs that occur in a `NON_MATCHING` build that are not in the vanilla game, then please file an issue describing the bug. It would be helpful if you can track down which function is causing the bug, but that is not required.

To compile the game code with GCC instead of IDO, use a MIPS cross-compiler:

```sh
make clean
make COMPILER=gcc -j4
```

`COMPILER=gcc` automatically enables `NON_MATCHING`. It requires a compatible MIPS GCC in your `PATH`; the host GCC or Clang compiler is only used for syntax checks. There is no Clang target compiler option.

Always run `make clean` when switching between matching, `NON_MATCHING`, and GCC builds because they share the `build` directory.

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
Show score for another version (default: us.v77): `./score.sh -v VERSION`  
Show score percentage summary: `./score.sh -s`  
Show score without libultra progress in Adventure One: `./score.sh --nolib`  
Show top files remaining (default: 10): `./score.sh -t TOP`  
Show treemap view in a file (default: treemap.html): `./score.sh --treemap TREEMAP`  

To make progress in Adventure 2, a function must be properly named (must not start with `func_`) and also include a doxygen comment above it.

For example:

```c
/**
 * Returns 1 if Drumstick is available to use, or 0 if not.
 */
s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
```

<!-- README_SCORE_BEGIN -->
As of July 25, 2026, this is our current score:
```
 ===========================================
 ADVENTURE ONE (ASM -> C Decompilation) [us.v77]
 ------------- 100.0% Complete -------------
        # Decompiled functions: 1864
       # Handwritten ASM functions: 85
          # GLOBAL_ASM remaining: 0
         # NON_MATCHING functions: 0
      # NON_EQUIVALENT WIP functions: 0
 --------------- Game Status ---------------
  Balloons: 47/47, Keys: 4/4, Trophies: 5/5
   T.T. Amulets: 4/4, Wizpig Amulets: 4/4
 -------------------------------------------
                 COMPLETED!
 ===========================================
    ADVENTURE TWO (Cleanup & Documentation)
 ------------- 66.58% Complete -------------
        # Documented functions: 1280
        # Undocumented remaining: 294
       # Functions named `func_*`: 147
      # Functions without comments: 294
 --------------- Game Status ---------------
  Balloons: 31/47, Keys: 3/4, Trophies: 3/5
   T.T. Amulets: 3/4, Wizpig Amulets: 3/4
 -------------------------------------------
 We are racing in Windmill Plains. (Lap 3/3)
 ===========================================
```
<!-- README_SCORE_END -->
