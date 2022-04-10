#!/bin/bash

if [[ $# == 0 || (($1 != "us_1.0") && ($1 != "us_1.1") && ($1 != "eu_1.0") && ($1 != "eu_1.1") && ($1 != "jp"))]]; then
    echo 'No valid version specified, defaulting to us_1.0...'
    VER="us_1.0"
else
    VER=$1
fi

echo 'Extracting Assets...'

# Remove assets directory if it exists.
ASSETS_DIR="./assets/vanilla/$VER"
if [ -d "$ASSETS_DIR" ]; then
    rm -r $ASSETS_DIR
fi

# Remove ucode directory if it exists.
UCODE_DIR="./ucode/$VER"
if [ -d "$UCODE_DIR" ]; then
    rm -r $UCODE_DIR
fi

if ! ./tools/dkr_assets_tool -bc "$VER" ./include/enums.h ; then
    exit 1
fi
if ! ./tools/dkr_assets_tool -e "$VER" ./assets ./extract-ver ./baseroms . ; then
    exit 1
fi

echo 'Done.'

exit 0
