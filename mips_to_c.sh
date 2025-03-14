#!/bin/sh

#Make the m2cfiles dir if it doesn't already exist
mkdir -p m2cfiles

ASMFILE=$(find asm -type f -name "*$1.s")
echo '#include "../ctx.c"\n' > m2cfiles/$1.c
.venv/bin/python3 tools/m2c/m2c.py --target mips-ido-c --pointer-style right --context ctx.c -f $1 $ASMFILE >> m2cfiles/$1.c