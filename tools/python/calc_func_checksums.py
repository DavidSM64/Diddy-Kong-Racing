import re
import os
import sys

from file_util import FileUtil

VERSION = sys.argv[1]

BUILD_DIR = 'build/' + VERSION
MAP_FILEPATH = BUILD_DIR + '/dkr.map'
ROM_FILEPATH = BUILD_DIR + '/dkr.z64'

FUNCTIONS_TO_CALC = [
    # function         checksum variable        func size variable
    ('func_80019808', 'gFunc80019808Checksum', 'gFunc80019808Length'),
    ('func_80024D54', 'gFunc80024D54Checksum', 'gFunc80024D54Length'),
    ('func_8003B4BC', 'gFunc8003B4BCChecksum', 'gFunc8003B4BCLength'),
    ('func_80068158', 'gFunc80068158Checksum', 'gFunc80068158Length')
]

def getMatches(string, regex):
    out = []
    matches = re.finditer(regex, string, re.MULTILINE)
    for matchNum, match in enumerate(matches, start=1):
        start = match.start()
        end = match.end()
        out.append((string[start:end], match.groups(), (start, end)))
    return out

rom = FileUtil.get_bytes_from_file(ROM_FILEPATH)
mapFile = {}
RAM_TO_ROM = None

def write_word_to_rom(romOffset, value):
    global rom
    rom[romOffset + 0] = (value >> 24) & 0xFF
    rom[romOffset + 1] = (value >> 16) & 0xFF
    rom[romOffset + 2] = (value >> 8) & 0xFF
    rom[romOffset + 3] = value & 0xFF
    
def calculate_checksum_for_function(funcLabel, varLabel, funcSizeLabel):
    if funcLabel not in mapFile:
        raise Exception('Label "' + funcLabel + '" does not exist in the map file!')
    if varLabel not in mapFile:
        raise Exception('Label "' + varLabel + '" does not exist in the map file!')
    if funcSizeLabel not in mapFile:
        raise Exception('Label "' + funcSizeLabel + '" does not exist in the map file!')
    funcEntry = mapFile[funcLabel]
    funcAddress = funcEntry['value']
    funcLength = funcEntry['length']
    funcRomOffset = funcAddress - RAM_TO_ROM
    count = 0
    for i in range(0, funcLength):
        count += rom[funcRomOffset + i]
    # Save function checksum.
    varEntry = mapFile[varLabel]
    varAddress = varEntry['value']
    varRomOffset = varAddress - RAM_TO_ROM
    write_word_to_rom(varRomOffset, count)
    # Save function size.
    sizeEntry = mapFile[funcSizeLabel]
    sizeAddress = sizeEntry['value']
    sizeRomOffset = sizeAddress - RAM_TO_ROM
    write_word_to_rom(sizeRomOffset, funcLength)

def calculate_matches():
    global mapFile, RAM_TO_ROM
    REGEX_MAP_GET_LABEL = r"[ ]*?0x[0-9A-Fa-f]{8}([0-9A-Fa-f]{8})[ ]*?([_A-Za-z0-9]+)"
    mapText = FileUtil.get_text_from_file(MAP_FILEPATH)
    mapMatches = getMatches(mapText, REGEX_MAP_GET_LABEL)
    for i in range(0, len(mapMatches) - 1):
        match = mapMatches[i]
        labelValue = match[1]
        value = int(labelValue[0], 16)
        length = int(mapMatches[i + 1][1][0], 16) - value
        mapFile[labelValue[1]] = { "value": value, "length": length }
    RAM_TO_ROM = mapFile['__RAM_TO_ROM']['value']

def main():
    calculate_matches()
    for entry in FUNCTIONS_TO_CALC:
        calculate_checksum_for_function(entry[0], entry[1], entry[2])
    FileUtil.write_bytes_to_file(ROM_FILEPATH, rom)

main()
