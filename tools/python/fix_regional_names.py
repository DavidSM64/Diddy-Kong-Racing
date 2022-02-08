#!/usr/bin/env python3
import argparse
import json
import re
import os

from file_util import FileUtil

# Make sure this gets run in the project's base directory.
FileUtil.set_working_dir_to_project_base()

# This script converts all symbol names between US and UK english.

REGEX_MAP_SYMBOL = r"[ ]{16}0x[0-9A-Fa-f]{16}[ ]{16}([a-zA-Z_][a-zA-Z0-9_]*)\n"

TERMINAL_COLOR_RED = "\033[31m"
TERMINAL_COLOR_GREEN = "\033[32m"
TERMINAL_COLOR_YELLOW = "\033[33m"
TERMINAL_COLOR_RESET = "\033[0m"

REGIONAL_NAMES_JSON_PATH = 'tools/python/regional_names.json'

# Note: All words MUST be lowercase
diffMap = json.loads(FileUtil.get_text_from_file(REGIONAL_NAMES_JSON_PATH))['diffMap']
convertRegion = 'to_uk'

def precheckForErrors(version):
    versionBuildPath = 'build/' + version
    if not FileUtil.does_file_exist(versionBuildPath):
        print('Error: "' + versionBuildPath + '" could not be found. You should have an OK build before running this script!')
        return None
    return versionBuildPath + '/dkr.map'

def filterSymMapText(symMapText):
    newSymMapText = ''

    lines = symMapText.split('\n')

    state = 0 
        # 0 = Looking for .main section
        # 1 = Looking for file section
        # 2 = Processing file section

    for i in range(0, len(lines)):
        line = lines[i]
        if state == 0 and line.startswith('.main'):
            state = 1
        elif state == 1:
            if line.startswith(' build/') and '/lib/' not in line:
                    state = 2
        elif state == 2:
            if line.startswith(' build/') and '/lib/' in line:
                    state = 1
                    continue
            if line.startswith('/DISCARD/'):
                break
            newSymMapText += line + '\n'
    return newSymMapText

def getSymbolsFromMapText(symMapText):
    symbols = set()

    matches = re.finditer(REGEX_MAP_SYMBOL, symMapText, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        symbols.add(match.group(1))

    return list(symbols)

def getReplaceProperties(subsymbol, convertTo):
    replaceWith = subsymbol
    if subsymbol.islower():
        replaceWith = convertTo.lower()
    elif subsymbol.isupper():
        replaceWith = convertTo.upper()
    elif subsymbol.istitle():
        replaceWith = convertTo.title()

    return {
        "subsymbol": subsymbol,
        "replaceWith": replaceWith
    }

def breakDownSymbol(symbolName):
    form = 'unknown'

    if symbolName.islower():
        form = 'snakeLower'
    elif symbolName.isupper():
        form = 'snakeUpper'
    elif symbolName[0].islower():
        form = 'camelCase'
    elif symbolName[0].isupper():
        form = 'pascalCase'

    if form == 'unknown':
        return None

    parts = []

    if form == 'snakeLower' or form == 'snakeUpper':
        parts = symbolName.split('_')
    elif form == 'camelCase' or form == 'pascalCase':
        start = 0
        for i in range(1, len(symbolName)):
            if symbolName[i].isupper():
                parts.append(symbolName[start:i])
                start = i
        parts.append(symbolName[start:])

    return parts

def filterOutSymbols(symbols):
    validSymbols = {}

    for symbol in symbols:
        symbolParts = breakDownSymbol(symbol)

        if symbolParts is None:
            # Symbol can't be processed, so just skip it.
            continue

        for part in symbolParts:
            lowerPart = part.lower()
            if lowerPart in diffMap[convertRegion]:
                if symbol not in validSymbols:
                    validSymbols[symbol] = []
                validSymbols[symbol].append(getReplaceProperties(part, diffMap[convertRegion][lowerPart]))

    return validSymbols

def validateReplaces(symbolReplaces):
    validatedReplaces = []

    if len(symbolReplaces) == 0:
        return validatedReplaces

    print(TERMINAL_COLOR_YELLOW + "Enter 'y' or nothing to accept change, 'n' to discard change, 'x' to abort" + TERMINAL_COLOR_RESET)

    for symbol in symbolReplaces:
        oldSymbol = symbol
        for entry in symbolReplaces[symbol]:
            oldWord = entry["subsymbol"]
            index = symbol.index(oldWord)
            newWord = entry["replaceWith"]
            symbol = symbol[0:index] + newWord + symbol[index+len(oldWord):]
        while(True):
            inputText = 'Replace "' + oldSymbol + '" with "' + symbol + '"? '
            response = input(inputText).lower()
            if len(response) == 0 or response.startswith('y'):
                validatedReplaces.append({"old": oldSymbol, "new": symbol});
                print("\033[1A\033[" + str(len(inputText)) + "C" + TERMINAL_COLOR_GREEN + "Change Accepted" + TERMINAL_COLOR_RESET)
                break
            elif response.startswith('n'):
                print("\033[1A\033[" + str(len(inputText)) + "C" + TERMINAL_COLOR_RED + "Change Discarded" + TERMINAL_COLOR_RESET)
                break
            elif response.startswith('x'):
                return None # None means aborted
        
    return validatedReplaces 

def convertName(version):
    symMapPath = precheckForErrors(version)
    if symMapPath is None:
        return
    symMapText = filterSymMapText(FileUtil.get_text_from_file(symMapPath))
    symbols = getSymbolsFromMapText(symMapText)
    symbolReplaces = filterOutSymbols(symbols)
    validReplaces = validateReplaces(symbolReplaces)
    if validReplaces is None:
        print("Name conversion has been aborted. No changes were made.")
        return
    if len(validReplaces) == 0:
        print("No symbols can be converted. No changes were made.")
        return
    for entry in validReplaces:
        os.system('./rename.sh ' + entry["old"] + ' ' + entry["new"])
    os.system('make clean')
    print(str(len(validReplaces)) + " symbols were replaced.")

def main():
    global convertRegion
    parser = argparse.ArgumentParser(description="Converts all symbol names between US and UK naming.")
    parser.add_argument("-c", "--convertTo", help="Either 'uk' or 'us'", choices=['uk', 'us'], default='uk')
    parser.add_argument("-v", "--version", help="DKR Version", 
        choices=['us_1.0', 'us_1.1', 'eu_1.0', 'eu_1.1', 'jp'], default='us_1.0')
    args = parser.parse_args()

    if args.convertTo == 'uk':
        convertRegion = 'to_uk'
    else:
        convertRegion = 'to_us'

    convertName(args.version)

if __name__ == "__main__":
    main()

