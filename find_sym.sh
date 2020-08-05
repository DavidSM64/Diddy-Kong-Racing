#!/bin/bash

shopt -s globstar

if [ "$#" -ne "1" ];
then
    echo "usage: $0 name"
    exit 1
fi

#echo "Replace $1 with $2?"
#read
grep -r "$1" asm/**/*.s src/**/*.c lib/**/*.{c,s} include/*.h data/dkr.data.s undefined_syms.txt 