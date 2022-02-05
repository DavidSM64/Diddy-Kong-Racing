#!/usr/bin/env python3
import argparse
import re
import os

from file_util import FileUtil

# This script converts all symbol names between US and UK english.

REGEX_MAP_SYMBOL = r"[ ]{16}0x[0-9A-Fa-f]{16}[ ]{16}([a-zA-Z_][a-zA-Z0-9_]*)\n"

TERMINAL_COLOR_RED = "\033[31m"
TERMINAL_COLOR_GREEN = "\033[32m"
TERMINAL_COLOR_YELLOW = "\033[33m"
TERMINAL_COLOR_RESET = "\033[0m"

# Note: All names MUST be lowercase
diffMap = [
    { "us": "color",  "uk": "colour" },
    { "us": "gray",   "uk": "grey" },
    { "us": "dialog", "uk": "dialogue" },
]

def precheckForErrors(version):
    versionBuildPath = 'build/' + version
    if not FileUtil.does_file_exist(versionBuildPath):
        print('Error: "' + versionBuildPath + '" could not be found. You should have an OK build before running this script!')
        return None
    symMapPath = versionBuildPath + '/dkr.map'
    if not FileUtil.does_file_exist(symMapPath):
        print('Error: "' + symMapPath + '" could not be found. Make sure this script is running from the root directory of the repo.')
        return None
    return symMapPath

def getSymbolsFromMapText(symMapText):
    symbols = set()

    matches = re.finditer(REGEX_MAP_SYMBOL, symMapText, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        symbols.add(match.group(1))

    return list(symbols)

def getReplaceProperties(string, diffMapIndex, symbol, index, convertTo):
    #print(string, symbol, index)
    subsymbol = symbol[index:index+len(string)]
    replaceWith = subsymbol
    if subsymbol.islower():
        replaceWith = diffMap[diffMapIndex][convertTo].lower()
    elif subsymbol.isupper():
        replaceWith = diffMap[diffMapIndex][convertTo].upper()
    elif subsymbol.istitle():
        replaceWith = diffMap[diffMapIndex][convertTo].title()

    return {
        "subsymbol": subsymbol,
        "replaceWith": replaceWith
    }

def filterOutSymbols(symbols, convertTo):
    convertFrom = 'us' if (convertTo == 'uk') else 'uk'

    validSymbols = {}

    for symbol in symbols:
        lowerSymbol = symbol.lower()
        #for diff in diffMap:
        for i in range(0, len(diffMap)):
            #check = diff[convertFrom]
            check = diffMap[i][convertFrom]
            if check in lowerSymbol:
                checkIndex = lowerSymbol.index(check)

                # Checks to make sure a short word did not sneak in.
                try:
                    if len(check) < len(diffMap[i][convertTo]) and lowerSymbol.index(diffMap[i][convertTo]) == checkIndex:
                        continue
                except:
                    pass

                if symbol not in validSymbols:
                    validSymbols[symbol] = []

                validSymbols[symbol].append(getReplaceProperties(check, i, symbol, checkIndex, convertTo))

    return validSymbols

def validateReplaces(symbolReplaces):
    validatedReplaces = []

    if len(symbolReplaces) == 0:
        return validatedReplaces

    print("Enter 'y' or nothing to accept change, 'n' to discard change, 'x' to abort")

    for symbol in symbolReplaces:
        #entry = symbolReplaces[symbol][0]
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

def convertName(convertTo, version):
    #print("Parameters: " + convertTo + ", " + version)
    print(TERMINAL_COLOR_YELLOW + "Converting to " + convertTo + " english; DKR version: " + version + TERMINAL_COLOR_RESET)
    symMapPath = precheckForErrors(version)
    if symMapPath is None:
        return
    symMapText = FileUtil.get_text_from_file(symMapPath)
    symbols = getSymbolsFromMapText(symMapText)
    symbolReplaces = filterOutSymbols(symbols, convertTo)
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
    parser = argparse.ArgumentParser(description="Converts all symbol names between US and UK naming.")
    parser.add_argument("-c", "--convertTo", help="Either 'uk' or 'us'", choices=['uk', 'us'], default='uk')
    parser.add_argument("-v", "--version", help="DKR Version", 
        choices=['us_1.0', 'us_1.1', 'eu_1.0', 'eu_1.1', 'jp'], default='us_1.0')
    args = parser.parse_args()
    convertName(args.convertTo, args.version)

if __name__ == "__main__":
    main()
