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

def boot_extract(input_file, output_file="boot_custom.bin"):
    mods_missing = True
    cictype = 6103
    if not (input_file.endswith(".z64")):
        print("ROM file must be .z64. Use https://hack64.net/tools/swapper.php to convert.")
        return
    
    with open(input_file, "rb") as f:
        f.seek(0x40)
        data = f.read(0xFC0)

    if os.path.isdir('mods'):
        print("Mods folder detected, outputting there.")
        output_file = "./mods/boot_custom.bin"
        mods_missing = False
        cictype = N64GetCIC(data)
        if os.path.isfile("makefile"):
            print("Makefile detected, modifying CIC type.")
            with open("makefile", 'r') as f:
                lines = f.readlines()
            with open("makefile", 'w') as f:
                for line in lines:
                    if line.startswith("BOOT_CIC ?="):
                        f.write("BOOT_CIC ?= " + str(cictype) + "\n")
                    else:
                        f.write(line)


    with open(output_file, "wb") as f:
        f.write(data)

    if (mods_missing == True):
        print("Finished! Copy boot_custom.bin to the mods folder and change BOOT_CIC in the makefile")
    else:
        print("Finished!")

boot_extract(sys.argv[1])
