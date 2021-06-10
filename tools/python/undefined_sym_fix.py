import subprocess
import sys
import re
import subprocess
import argparse

def fixBadLabel():
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

def load_syms():
    with open('undefined_syms.txt', 'r') as inFile:
        return inFile.read().split('\n')

def save_syms(syms):
    with open('undefined_syms.txt', 'w') as outFile:
        outFile.write('\n'.join(syms))

def check_is_double(symbol, address):
    command = subprocess.run(['fgrep', '-ri', symbol], capture_output=True)
    outLines = command.stdout.decode("utf-8").split('\n')
    for outLine in outLines:
        if 'lwc1' in outLine:
            newSym = 'D_' + hex(address - 4)[2:].upper() + ' + 4'
            subprocess.run(['./rename_sym.sh', symbol, newSym])
            return True
    return False
    
def fixDoubleLoads():
    syms = load_syms()
    target = len(syms)
    i = 0
    while i < target:
        sym = syms[i]
        if sym.startswith('D_'):
            symSplit = sym.split(' = ')
            symbol = symSplit[0]
            address = int(symSplit[1][2:-1], 16)
            if address >= 0x800E4BFC and address < 0x800E9BA0 and ((address & 4) != 0):
                if check_is_double(symbol, address):
                    syms.pop(i)
                    target -= 1
                    continue
        i += 1
    save_syms(syms)

def getMatches(string, regex):
    out = []
    matches = re.finditer(regex, string, re.MULTILINE)
    for matchNum, match in enumerate(matches, start=1):
        start = match.start()
        end = match.end()
        out.append((string[start:end], match.groups(), (start, end)))
    return out
    
FILE_REGEX = r"(?:lib/)?(?:(?:src/)|(?:asm/non_matchings/))([^/.]*)"
def getFiles(symbol):
    command = subprocess.run(['fgrep', '-ri', symbol], capture_output=True)
    outLines = command.stdout.decode("utf-8").split('\n')
    fileNames = []
    for outLine in outLines:
        if 'src' in outLine or 'asm' in outLine:
            match = getMatches(outLine, FILE_REGEX)[0][1][0]
            if match not in fileNames:
                fileNames.append(match)
    return fileNames
    
def getBss():
    currentFile = ''
    out = []
    syms = load_syms()
    for sym in syms:
        if ' = ' in sym:
            symSplit = sym.split(' = ')
            symbol = symSplit[0]
            address = int(symSplit[1][2:-1], 16)
            if address >= 0x80115CE8 and address <= 0x8012D3F0:
                try:
                    files = getFiles(symbol)
                    if currentFile not in files:
                        if len(files) == 1:
                            if currentFile != '':
                                out.append('\n')
                            currentFile = files[0]
                            out.append(currentFile)
                        else:
                            print(symbol, files, 'Cannot tell which file to use!')
                except IndexError:
                    print('Error with symbol: ' + symbol)
                out.append(sym)
    with open('bss.txt', 'w') as outFile:
        outFile.write('\n'.join(out))
    

fixBadLabel()
#fixDoubleLoads()
#getBss()

