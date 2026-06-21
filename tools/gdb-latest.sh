#!/bin/bash
set -e # Exit immediately if a command exits with a non-zero status.

# --- Configuration ---
SOURCE_DIR="$HOME/binutils-gdb"
BUILD_DIR="$SOURCE_DIR/build"
INSTALL_PREFIX="/usr/local"
PROGRAM_NAME_SUFFIX="-mips-release"

echo "--- 1. Installing Build Dependencies ---"
sudo apt update
sudo apt install -y build-essential texinfo libgmp-dev libmpfr-dev \
                    libmpc-dev python3-dev zlib1g-dev libexpat1-dev \
                    libxxhash-dev libdebuginfod-dev libelf-dev \
                    libncurses-dev git bison m4 flex libreadline-dev

echo "--- 2. Cloning or Updating GDB Source Code ---"
if [ ! -d "$SOURCE_DIR" ]; then
    git clone git://sourceware.org/git/binutils-gdb.git "$SOURCE_DIR"
fi
cd "$SOURCE_DIR"
git fetch --tags # Ensure we have all the latest tags

echo "--- 3. Finding and Checking Out the Latest Release Tag ---"
# Find the latest tag that starts with 'gdb-' using version-sort
LATEST_GDB_TAG=$(git tag -l 'gdb-*-release' | sort -V | tail -n 1)

if [ -z "$LATEST_GDB_TAG" ]; then
    echo "Could not find any GDB release tags. Aborting."
    exit 1
fi

echo "Found latest GDB release: $LATEST_GDB_TAG. Checking it out."
git checkout "$LATEST_GDB_TAG"

echo "--- 4. Configuring the Build ---"
# Create a clean build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

../configure \
    --prefix="$INSTALL_PREFIX" \
    --program-suffix="$PROGRAM_NAME_SUFFIX" \
    --disable-werror \
    --disable-maintainer-mode \
    --disable-dependency-tracking \
    --disable-silent-rules \
    --disable-gdbtk \
    --disable-shared \
    --with-pkgversion="GDB $LATEST_GDB_TAG (Ubuntu local build)" \
    --with-system-readline \
    --with-expat \
    --with-system-zlib \
    --without-guile \
    --with-debuginfod \
    --enable-tui \
    --with-lzma \
    --with-python=$(which python3) \
    --with-xxhash \
    --enable-64-bit-bfd \
    --enable-targets=all \
    --enable-obsolete \
    --disable-sim



echo "--- 5. Compiling GDB (this will take a while) ---"
make -j$(nproc)

echo "--- 6. Installing GDB ---"
sudo make install

echo "--- 7. Verifying Installation ---"
# We need to use the full name including the suffix
FULL_PROGRAM_NAME="gdb$PROGRAM_NAME_SUFFIX"
VERSION_INFO=$($FULL_PROGRAM_NAME --version | head -n 1)
echo "---------------------------------------------------------"
echo "Installation complete!"
echo "Your new GDB is available as '$FULL_PROGRAM_NAME'."
echo "Version Info: $VERSION_INFO"
echo "---------------------------------------------------------"
echo "Verifying MIPS architecture support..."
$FULL_PROGRAM_NAME -q --nx -ex "set architecture mips" -ex "show architecture"
$FULL_PROGRAM_NAME -q --nx -ex "set architecture mips:64" -ex "show architecture"
echo "---------------------------------------------------------"
echo "You can now use '$FULL_PROGRAM_NAME' for your MIPS debugging!"