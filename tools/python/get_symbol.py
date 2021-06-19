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
    symbol, address = find_pairing(sys.argv[1])
    if symbol is None or address is None:
        if is_address(sys.argv[1]):
            print('No symbol was found for the address 0x%08X' % int(sys.argv[1], 16))
        else:
            print('No address was found for the symbol "%s"' % sys.argv[1])
    else:
        print('0x%08X = %s' % (address, symbol))

def find_pairing(sym_or_addr):
    symbol = None
    address = None
    if is_address(sym_or_addr):
        address = int(sym_or_addr, 16)
    else:
        symbol = sym_or_addr
    try:
        lines = FileUtil.get_text_from_file(SYMBOLS_TEXT_FILENAME).split('\n')
    except:
        print('Couldn\'t open file ' + SYMBOLS_TEXT_FILENAME)
        return
    for line in lines:
        matches = re.match(symbol_define_regex, line)
        if matches is None:
            continue
        cur_addr = int(matches[1], 16)
        cur_sym = matches[2]
        if cur_addr == address:
            return cur_sym, address
        elif cur_sym == symbol:
            return symbol, cur_addr
    return None, None

def is_address(symbol):
    try:
        int(symbol, 16)
        return True
    except:
        return False

def show_help():
    print("Usage: ./get_symbol <RAM Address or symbol>")
    
##################################################################################

main()
