# This script gets called when the build is complete.
# $1 = Output directory (build/us_1.0)

# Take the first megabyte of the rom file, and copy it to a new file called "dkr_code.bin"
head -c 1048576 $1/dkr.z64 > $1/dkr_code.bin
