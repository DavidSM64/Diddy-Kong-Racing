#!/bin/sh

# Make the m2cfiles dir if it doesn't already exist
mkdir -p m2cfiles

# Find all .s files in the asm directory and its subdirectories
find asm/nonmatchings -type f -name "*.s" | while read ASMFILE; do
    # Extract the filename without extension and path
    FILENAME=$(basename "$ASMFILE" .s)

    echo "Processing $FILENAME from $ASMFILE"

    # Create the output file with the required header
    echo '#include "../ctx.c"\n' > "m2cfiles/$FILENAME.c"

    # Run the m2c command with the extracted filename
    .venv/bin/python3 tools/m2c/m2c.py --target mips-ido-c --pointer-style right --context ctx.c -f "$FILENAME" "$ASMFILE" >> "m2cfiles/$FILENAME.c"

    echo "Created m2cfiles/$FILENAME.c"
done
