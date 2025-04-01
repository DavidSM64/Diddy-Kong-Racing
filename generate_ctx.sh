#!/bin/bash

if [ $# -eq 0 ]; then
    .venv/bin/python3 tools/python/m2ctx.py
else
    find include/ src/ libultra/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
    .venv/bin/python3 tools/m2ctx.py ctx_includes.c
fi
