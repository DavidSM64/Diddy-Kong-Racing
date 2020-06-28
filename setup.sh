#!/bin/bash

# Check if the baseroms directory exists.
BASEROMS_DIR="./baseroms/"
if [ ! -d "$BASEROMS_DIR" ]; then
    echo "/baseroms/ directory was not found. Was it deleted?"
    exit 1
fi

# If the assets directory already exists, then the repo is already setup
# TODO: add a `--force` option
ASSETS_DIR="./assets/"
if [ -d "$ASSETS_DIR" ]; then
    echo "Decomp is already setup, delete the /assets/ folder if you wish to continue"
    exit 1
fi

# Check if gcc is installed
# TODO: Automatically install gcc
if ! command -v gcc > /dev/null; then
    echo 'gcc is not installed!' 
    exit 2
fi

# Check if make is installed
# TODO: Automatically install make
if ! command -v make > /dev/null; then
    echo 'make is not installed!' 
    exit 3
fi

# Check if python3 is installed
# TODO: Automatically install python3
if ! command -v python3 > /dev/null; then
    echo 'python3 is not installed!' 
    exit 4
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
            exit 5
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
if ./extract.sh; then 
    echo 'Setup complete!'

    echo '---------------------------------------'
    echo '             Hello there!              '
    echo '     I am the genie of the decomp.     '
    echo '        I am here to help you.         '
    echo '              Good luck!               '
    echo '---------------------------------------'
fi
