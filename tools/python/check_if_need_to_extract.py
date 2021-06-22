import argparse
import hashlib
import subprocess
from file_util import FileUtil

parser = argparse.ArgumentParser(description="")
parser.add_argument("version", help="DKR version.", choices=['us_1.0'])
args = parser.parse_args()

version = args.version

extractConfigsDirectory = './extract-ver'
assetsDirectory = './assets'
ucodeDirectory = './assets'
extractConfigFilename = extractConfigsDirectory + '/' + version + '.config.json'
configChecksumFilename = extractConfigFilename + '.md5'

needToExtract = False

if not FileUtil.does_file_exist(assetsDirectory):
    needToExtract = True
elif not FileUtil.does_file_exist(ucodeDirectory):
    needToExtract = True
elif not FileUtil.does_file_exist(configChecksumFilename):
    needToExtract = True
else:
    md5Calculated = hashlib.md5(FileUtil.get_bytes_from_file(extractConfigFilename)).hexdigest()
    md5Saved = FileUtil.get_text_from_file(configChecksumFilename)
    if md5Calculated != md5Saved:
        needToExtract = True

if needToExtract:
    md5Calculated = hashlib.md5(FileUtil.get_bytes_from_file(extractConfigFilename)).hexdigest()
    FileUtil.write_text_to_file(configChecksumFilename, md5Calculated)
    subprocess.run(['./extract.sh', version])
    