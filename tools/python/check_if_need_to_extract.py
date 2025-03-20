import argparse
import hashlib
import subprocess
import time
from file_util import FileUtil

parser = argparse.ArgumentParser(description="")
parser.add_argument("version", help="DKR version.", choices=['us_1.0'])
args = parser.parse_args()

version = args.version

extractConfigsDirectory = './extract-ver'
assetsDirectory = './assets/.vanilla'
extractConfigFilename = extractConfigsDirectory + '/' + version + '.config.json'
configChecksumFilename = extractConfigFilename + '.md5'

needToExtract = False

def do_extraction(reason):
    global needToExtract
    needToExtract = True
    print(reason)

if not FileUtil.does_file_exist(assetsDirectory):
    do_extraction("Extracting because /assets/.vanilla/ directory does not exist.")
elif not FileUtil.does_file_exist(configChecksumFilename):
    do_extraction('Extracting because "' + configChecksumFilename + '" does not exist.')
else:
    md5Calculated = hashlib.md5(FileUtil.get_bytes_from_file(extractConfigFilename)).hexdigest()
    md5Saved = FileUtil.get_text_from_file(configChecksumFilename)
    if md5Calculated != md5Saved:
        do_extraction('Extracting because "' + extractConfigFilename + '" has changed.')

def run_until_done(args, hide=False):
    if hide:
        subprocess.run(args, stdout=subprocess.DEVNULL)
    else:
        subprocess.run(args)

if needToExtract:
    md5Calculated = hashlib.md5(FileUtil.get_bytes_from_file(extractConfigFilename)).hexdigest()
    FileUtil.write_text_to_file(configChecksumFilename, md5Calculated)
    run_until_done(['./extract.sh', version], True)
    