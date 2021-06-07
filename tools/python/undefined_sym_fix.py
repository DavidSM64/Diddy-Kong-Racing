import subprocess
import sys
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

#fixBadLabel()
fixDoubleLoads()

