#!/usr/bin/env bash

shopt -s globstar

if [ "$#" -lt "2" ];
then
    echo "usage: $0 old_name new_name"
    exit 1
fi

if [ "$#" -gt "2" ];
then
    # If the 3rd argument is "--check", then make sure the new symbol doesn't already exist!
    if [ "$3" == "--check" ];
    then
        if grep -rlq "$2" asm/**/*.s src/**/*.{c,h} libultra/**/*.{c,s} include/*.h undefined_syms.txt dkr.ld;
        then
            echo "$2 already exist"
            exit 1
        fi
    fi
fi

# Rename all instances within text files.
grep -rl "$1" asm/**/*.s src/**/*.{c,h} lib/**/*.{c,s} include/*.h undefined_syms.txt dkr.ld | xargs sed -i "s/\b$1\b/$2/g"

# Rename filenames & directories.
python3 ./tools/python/rename_file.py "$1" "$2"

# This removes all the .o files that use the old name.
grep -rl "$1" build/**/*.o | xargs rm
