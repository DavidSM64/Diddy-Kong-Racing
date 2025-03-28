#!/bin/bash

find include/ src/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
.venv/bin/python3 tools/m2ctx.py ctx_includes.c
