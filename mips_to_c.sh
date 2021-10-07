#!/bin/sh

ASMFILE=$(find . -type f -name "*$1.s")
python3 ../mips_to_c/mips_to_c.py --context ctx.c -f $1 $ASMFILE > $1.c