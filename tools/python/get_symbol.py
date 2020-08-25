import sys
import re

from file_util import FileUtil

SYMBOLS_TEXT_FILENAME = 'undefined_syms.txt'

symbol_define_regex = r'([_0-9A-Za-z]*)\s*=\s*([_0-9A-Za-z]*)\s*;'

def main():
    if len(sys.argv) != 2:
        show_help()
        return
    print_symbol(int(sys.argv[1], 16))

def print_symbol(ramAddress):
    lines = FileUtil.get_text_from_file(SYMBOLS_TEXT_FILENAME).split('\n')
    foundSymbol = False
    for line in lines:
        matches = re.match(symbol_define_regex, line)
        if matches is None:
            continue
        address = int(matches[2], 16)
        if address == ramAddress:
            symbol = matches[1]
            print(matches[2] + ' = ' + matches[1])
            foundSymbol = True
            break
    if not foundSymbol:
        print('No symbol was found for the address "' + hex(ramAddress) + '"')
        
    
def show_help():
    print("Usage: ./get_symbol <RAM Address>")
    
##################################################################################

main()
