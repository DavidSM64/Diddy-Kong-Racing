#!/bin/bash

find include/ src/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
python3 tools/python/m2ctx.py ctx_includes.c

echo '#define NULL (void *)0' >> ctx.c