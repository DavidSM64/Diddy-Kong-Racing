#!/bin/bash

shopt -s globstar

if [ "$#" -ne "2" ];
then
    echo "usage: $0 old_name new_name"
    exit 1
fi

#echo "Replace $1 with $2?"
#read
<<<<<<< HEAD
ofiles=$(grep -rl "$1" build/**/*.o)
rm -v $ofiles
grep -rl "$1" asm/**/*.s src/**/*.{c,h} lib/**/*.{c,s} include/*.h data/dkr.data.s undefined_syms.txt | xargs sed -i "s/\b$1\b/$2/g"
=======
grep -rl "$1" asm/**/*.s src/**/*.{c,h} lib/**/*.{c,s} include/*.h data/dkr.data.s undefined_syms.txt | xargs sed -i "s/\b$1\b/$2/g"

# This removes all the .o files that use the old name.
grep -rl "$1" build/**/*.o | xargs rm
>>>>>>> b1b1e461a6aa490d7355c207a9a9530181aa8fd7
