#!/bin/bash

# If the assets directory already exists, then the repo is already setup
# TODO: add a `--force` option
ASSETS_DIR="./assets/"
if [ -d "$ASSETS_DIR" ]; then
    echo "Decomp is already setup, delete the /assets/ folder if you wish to continue"
    exit 1
fi

# Check if python3 is installed
# TODO: Automatically install python3
if ! command -v python3 > /dev/null; then
    echo 'python3 is not installed!' 
    exit 3
fi

# Check if binutils is installed
# TODO: Automatically install binutils
if ! command -v mips-linux-gnu-ld > /dev/null; then
    if ! command -v mips64-linux-gnu-ld > /dev/null; then
        if ! command -v mips64-elf-ld > /dev/null; then
            echo 'binutils is not installed!'
            echo 'Arch users should install: `mips64-elf-binutils`'
            echo 'Ubuntu/Debian should install: `binutils-mips-linux-gnu`'
            echo 'RHEL/CentOS/Fedora should install: `gcc-mips64-linux-gnu`'
            exit 4
        fi
    fi
fi

# build all the tools in the /tools/ directory
echo 'Building tools...'
cd tools
make
echo 'Tools built!'
cd ..

# Extract assets into the /assets/ directory
echo 'Extracting Assets...'
python3 ./tools/python/extract.py

# Generate the linker file (dkr.ld)
python3 ./tools/python/generate_ld.py

echo 'Setup complete!'

echo '---------------------------------------'
echo '             Hello there!              '
echo '     I am the genie of the decomp.     '
echo '        I am here to help you.         '
echo '              Good luck!               '
echo '---------------------------------------'
