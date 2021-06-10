import subprocess
import sys

syms = None

def main():
    load_syms()
    index = 0
    while index < len(syms):
        index = test_index(index)
    print('Done!')

def load_syms():
    global syms
    with open('undefined_syms.txt', 'r') as inFile:
        syms = inFile.read().split('\n')

def save_syms():
    with open('undefined_syms.txt', 'w') as outFile:
        outFile.write('\n'.join(syms))

def test_index(index):
    val = syms.pop(index)
    save_syms()
    command = subprocess.run(['make', 'clean'], capture_output=True)
    command = subprocess.run(['make', '-j12'], capture_output=True)
    out = str(command.stdout)[-5:]
    if out.startswith('OK'):
        print(val + ' is NOT needed! Removing!')
        return index
    else:
        print(val + ' is needed! Keeping!')
        syms.insert(index, val)
        save_syms()
        return index + 1
    
main()
