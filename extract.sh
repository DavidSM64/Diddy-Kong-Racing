echo 'Extracting Assets...'
python3 ./tools/python/extract.py
# Generate the linker file (dkr.ld)
python3 ./tools/python/generate_ld.py