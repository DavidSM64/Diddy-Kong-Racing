echo 'Extracting Assets...'
./tools/dkr_extractor ./extract-ver ./baseroms .

# Generate the linker file (dkr.ld)
python3 ./tools/python/generate_ld.py