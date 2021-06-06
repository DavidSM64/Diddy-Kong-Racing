import subprocess
import sys
import argparse

parser = argparse.ArgumentParser(description="")
parser.add_argument("baseLabel", help="Base label")
parser.add_argument("badLabel", help="Bad label")
args = parser.parse_args()

baseAddress = int(args.baseLabel[-8:], 16)
badAddress = int(args.badLabel[-8:], 16)

if baseAddress >= badAddress:
    raise Exception('baseLabel should be smaller! base = ' + hex(baseAddress) + ', bad = ' + hex(badAddress))

newLabel = args.baseLabel + '+' + str(badAddress-baseAddress)

subprocess.run(['./rename_sym.sh', args.badLabel, newLabel])
