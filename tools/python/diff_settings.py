#!/usr/bin/env python3

def add_custom_arguments(parser):
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument('-jp', dest='version', action='store_const', const='jp',
            help="Set version to JP.")
    group.add_argument('-us', dest='version', action='store_const', const='us',
            help="Set version to US.")
    group.add_argument('-eu', dest='version', action='store_const', const='eu',
            help="Set version to EU.")

def apply(config, args):
    version = 'us_1.0' # Right now only us_1.0 is supported
    config['mapfile'] = f'build/' + version + '/dkr.map'
    config['myimg'] = f'build/' + version + '/dkr.z64'
    config['baseimg'] = find_baserom(version)
    config['source_directories'] = ['src']

########################################################################################

from os import listdir
from os.path import isfile, join

CRCS = {
    'us_1.0': (0x53D440E7, 0x7519B011)
}

def get_filenames_from_directory(directory, extensions=None):
        if extensions is None:
            return [f for f in listdir(directory) if isfile(join(directory, f))]
        else:
            return [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(extensions)]

def get_rom_crcs(romPath):
    with open(romPath, 'rb') as inFile:
        rom = inFile.read()
        crc1 = int.from_bytes(rom[0x10:0x14], "big")
        crc2 = int.from_bytes(rom[0x14:0x18], "big")
        return (crc1, crc2)

def find_baserom(version):
    romFiles = get_filenames_from_directory('baseroms/', ('.z64',))
    for romFilename in romFiles:
        romFilepath = 'baseroms/' + romFilename
        if get_rom_crcs(romFilepath) == CRCS[version]:
            return romFilepath
    raise Exception('Could not find a rom file for the version: "' + version + '"')

########################################################################################
