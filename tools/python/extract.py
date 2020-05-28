from os import makedirs
import shutil

from file_util import FileUtil
from extract_config import Config
from rom import ROM

##################################################################################

CONFIGS_DIRECTORY = './extract-ver'
CONFIGS_EXTENSION = 'extract-config'

DEFAULT_ROM_DIRECTORY = './baseroms'
ACCEPTED_ROM_EXTENSIONS = ('.z64', '.v64', '.n64')

ASSETS_DIRECTORY = './assets'
ASM_ASSETS_DIRECTORY = './asm/assets'

RESET_DIRECTORIES = ['/bin', '/text', '/ucode', '/level', '/object']

##################################################################################

romsDirectory = DEFAULT_ROM_DIRECTORY

roms = []
configs = []

##################################################################################

def main():
    global roms, configs
    print('Removing existing directories...')
    for dir in RESET_DIRECTORIES:
        try:
            shutil.rmtree(ASSETS_DIRECTORY + dir)
        except FileNotFoundError as error:
            pass
    get_roms()
    if(len(roms) > 0):
        print('Preparing Configs...')
        get_configs()
        if(len(configs) > 0):
            list_extraction_options()
        else:
            print('No proper configs found in: "' + CONFIGS_DIRECTORY + '"')
            print('The valid config file extension is: ' + CONFIGS_EXTENSION)
    else:
        print('No ROMs found in the directory: "' + romsDirectory + '"')
        print('The valid ROM file extensions are: ' + str(ACCEPTED_ROM_EXTENSIONS))
    
def get_configs():
    global configs
    configsFilenames = FileUtil.get_filenames_from_directory(CONFIGS_DIRECTORY)
    for configFilename in configsFilenames:
        with open(CONFIGS_DIRECTORY + '/' + configFilename, 'r') as configFile:
            configs.append(Config(configFile.read()))
    if(len(configs) > 0):
        print('Configs loaded!')
    
def get_roms():
    global roms
    print('Preparing ROMs...')
    romFilenames = FileUtil.get_filenames_from_directory(romsDirectory, ACCEPTED_ROM_EXTENSIONS)
    for romFilename in romFilenames:
        roms.append(ROM(romsDirectory + '/' + romFilename))
    if(len(roms) > 0):
        print('ROMs loaded!')

def ends_with_n64_extension(filename):
    return filename.endswith()
        
def list_extraction_options():
    for config in configs:
        configChecksum = config.md5
        foundROM = None
        for rom in roms:
            if rom.md5 == configChecksum:
                foundROM = rom
                break
        if foundROM is not None:
            print('Found ROM file for config "' + config.name + '"')
            extract_assets_from_rom(config, foundROM)
    print('Done!')
            
def check_if_config_sizes_are_valid(config, rom):
    romOffset = 0
    for romRange in config.ranges:
        romOffset += romRange.size
    if romOffset != rom.size:
        raise Exception('Error: Config does not add up to ROM size.\nROM size is ' + hex(rom.size) + '; Config ends at ' + hex(romOffset))
            
def extract_assets_from_rom(config, rom):
    if(config.notSupported):
        print('This version of the game is currently not supported.')
        return
    check_if_config_sizes_are_valid(config, rom)
    with open(ASM_ASSETS_DIRECTORY + '/assets.s', 'w') as assetsImportFile:
        assetsImportText = '# This file was generated from extract.py\n';
        assetsImportText += '# TODO: Add if/elif/else for other versions of dkr\n\n';
        romOffset = 0
        for romRange in config.ranges:
            rangeSize = romRange.size
            rangeStart = romOffset
            rangeEnd = romOffset + rangeSize
            # TODO: Add more types
            if romRange.type == 'binary':
                binaryName = romRange.properties[0]
                binaryExtractLocation = romRange.properties[1]
                outputFilename = binaryName + '.' + "{:06x}".format(rangeStart) + '.bin'
                outputDirectory = ASSETS_DIRECTORY + '/'
                if len(config.subfolder) > 0:
                    outputDirectory += config.subfolder + '/'
                outputDirectory += binaryExtractLocation + '/'
                data = rom.get_bytes_from_range(rangeStart, rangeEnd)
                write_data_to_file(romRange, rangeStart, outputDirectory, outputFilename, 'wb', data)
                if rangeStart > 0x1000: # Exclude boot.000040.bin from assets.s
                    assetsImportText += '.incbin "' + outputDirectory + outputFilename + '"\n'
            elif romRange.type == 'noextract':
                pass
            else:
                raise Exception('Invalid range type: "' + romRange.type + '"')
            romOffset += rangeSize
        assetsImportFile.write(assetsImportText)

def write_data_to_file(range, rangeStart, directory, filename, flags, data):
    try: 
        makedirs(directory)
    except OSError as error: 
        pass
    with open(directory + filename, flags) as outFile:
        if flags == 'wb':
            outFile.write(bytearray(data))
        elif  flags == 'w':
            outFile.write(data)
        print('Extracted ' + range.get_range_string(rangeStart) + ' to ' + directory + filename)
        

def _bytes_to_int32(arr, offset):
    return int.from_bytes(arr[offset:offset+4], byteorder='big')
    
##################################################################################

main()
