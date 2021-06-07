import sys
import re

from file_util import FileUtil

SYMBOLS_TEXT_FILENAME = 'build/us_1.0/dkr.map'

symbol_define_regex = r'\s*(0x[0-9a-f]{16})\s*([_0-9A-Za-z]*)'

def main():
    FileUtil.set_working_dir_to_project_base()
    if len(sys.argv) != 2:
        show_help()
        return
    print_symbol(int(sys.argv[1], 16))

def print_symbol(ramAddress):
    try:
        lines = FileUtil.get_text_from_file(SYMBOLS_TEXT_FILENAME).split('\n')
    except:
        print('Couldn\'t open file ' + SYMBOLS_TEXT_FILENAME)
        return
    foundSymbol = False
    for line in lines:
        matches = re.match(symbol_define_regex, line)
        if matches is None:
            continue
        address = int(matches[1], 16)
        if address == ramAddress:
            symbol = matches[2]
            print('0x%08X = %s' % (address, symbol))
            foundSymbol = True
            break
    if not foundSymbol:
        print('No symbol was found for the address "' + hex(ramAddress) + '"')
        
    
def show_help():
    print("Usage: ./get_symbol <RAM Address>")
    
##################################################################################

main()
