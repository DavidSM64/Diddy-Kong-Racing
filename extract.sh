echo 'Extracting Assets...'
if ! ./tools/dkr_extractor ./extract-ver ./baseroms .; then
    exit 1
fi

# Generate the linker file (dkr.ld)
python3 ./tools/python/generate_ld.py

exit 0