#!/usr/bin/python3

import sys
import os
import zlib

def crc32(data: bytes) -> int:
    return zlib.crc32(data) & 0xFFFFFFFF

def N64GetCIC(data: bytes) -> int:
    crc = crc32(data)
    return {
        0x6170A4A1: 6101,
        0x90BB6CB5: 6102,
        0x0B050EE0: 6103,
        0x98BC2C86: 6105,
        0xACC8580A: 6106,
    }.get(crc, 0)

# Extract a boot bin from the given rom, provided the setup is correct
def boot_extract(input_file, output_file="boot_custom.bin"):
    mods_missing = True
    cictype = 6103

    if not (os.path.isfile(input_file)):
        print(input_file + " cannot be found. Check the spelling in your input.")
        return

    if not (input_file.endswith(".z64")):
        print("ROM file must be .z64. Use https://hack64.net/tools/swapper.php to convert.")
        return
    
    with open(input_file, "rb") as f:
        f.seek(0x40)
        data = f.read(0xFC0)

    if os.path.isdir("mods"):
        print("Mods folder detected, outputting there.")
        output_file = "./mods/boot_custom.bin"
        mods_missing = False
        cictype = N64GetCIC(data)
        if (cictype == 0):
            if data.find(b"Libdragon IPL3"):
                print("CIC: Libdragon")
            else:
                print("Unknown CIC, assume 6102 just in case, but don't assume the CIC itself is valid.")
            cictype = 6102
        else:
            print("CIC: " + str(cictype))
        #if os.path.isfile("Makefile"):
        #    print("Makefile detected, modifying CIC type.")
        #    with open("Makefile", 'r') as f:
        #        lines = f.readlines()
        #    with open("Makefile", 'w') as f:
        #        for line in lines:
        #            if line.startswith("BOOT_CIC ?="):
        #                f.write("BOOT_CIC ?= " + str(cictype) + "\n")
        #            else:
        #                f.write(line)
        if os.path.isfile("./build/asm/header.s.o"):
            os.remove("./build/asm/header.s.o")


    with open(output_file, "wb") as f:
        f.write(data)

    if (mods_missing == True):
        print("Finished! Copy boot_custom.bin to the mods folder and change BOOT_CIC in the makefile")
    else:
        print("Finished!")

# Read the current custom boot bin and return its CIC
def boot_write():
    if not os.path.isdir("mods"):
        print("0")
        return
    if not os.path.isfile("mods/boot_custom.bin"):
        print("0")
        return
    with open("./mods/boot_custom.bin", "rb") as f:
        data = f.read(0xFC0)
        cictype = N64GetCIC(data)
        if (cictype == 0):
            cictype = 6102
        print(cictype)

if (len(sys.argv) > 1):
    boot_extract(sys.argv[1])
else:
    boot_write()