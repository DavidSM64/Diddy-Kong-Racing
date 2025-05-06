#!/bin/sh

# Allows custom diff arguments for the region and version being diffed. (ex. --REGION=us --VERSION=v80)
.venv/bin/python3 tools/asm-differ/diff.py -smwo3 --line-numbers --max-lines 2048 "$@"