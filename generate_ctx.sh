#!/bin/bash

if [ $# -eq 0 ]; then
    .venv/bin/python3 tools/python/m2ctx.py
else
    find include/ src/ libultra/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
    .venv/bin/python3 tools/m2ctx.py ctx_includes.c
fi

#Forcefully fix issues in the ctx.c file in the hackiest way for now. These defines mess things up.
sed -i "/TT_COURSES$/d" ctx.c
sed -i "/SAVE_COURSES$/d" ctx.c

sed -i 's/ u32 courseTime\[COURSE_RECORD_TOTAL\];/ u32 courseTime[47];/' ctx.c
sed -i 's/ HudElement entry\[HUD_ELEMENT_COUNT\];/ HudElement entry[59];/' ctx.c
sed -i 's/ void \*entry\[HUD_ELEMENT_COUNT\];/ void \*entry\[59\];/' ctx.c
 