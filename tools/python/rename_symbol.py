import sys
import re

from file_util import FileUtil

ASM_DIR = './asm'
SYMBOL_MIN_LENGTH = 4
SYMBOLS_TEXT_FILENAME = 'undefined_syms.txt'

def main():
    if len(sys.argv) != 3:
        show_help()
        return
    old_symbol = sys.argv[1]
    new_symbol = sys.argv[2]
    if len(old_symbol) < SYMBOL_MIN_LENGTH or len(new_symbol) < SYMBOL_MIN_LENGTH:
        show_help()
        return
    replace_symbol(old_symbol, new_symbol)

def show_help():
    print("Usage: ./rename_symbol <Old Symbol> <New Symbol>")
    print("The symbols must be at-least {0} characters long.".format(SYMBOL_MIN_LENGTH))
    
def get_regex(symbol):
    return r'(?<=[^_0-9A-Za-z])' + symbol + r'(?=[^_0-9A-Za-z])'
    
def replace_symbol(old, new):
    replaceRegex = get_regex(old)
    
    # Replace symbol in undefined_syms.txt
    undefined_symbols = FileUtil.get_text_from_file(SYMBOLS_TEXT_FILENAME)
    undefined_symbols = re.sub(replaceRegex, new, undefined_symbols)
    FileUtil.write_text_to_file(SYMBOLS_TEXT_FILENAME, undefined_symbols)
    
    # Replace symbol in .s files in the ./asm directory
    asmFilenames = FileUtil.get_filenames_from_directory(ASM_DIR, ('.s',))
    for asmFilename in asmFilenames:
        asm = FileUtil.get_text_from_file(ASM_DIR + '/' + asmFilename)
        asm = re.sub(replaceRegex, new, asm)
        FileUtil.write_text_to_file(ASM_DIR + '/' + asmFilename, asm)
    
    print('Successfully replaced symbol "' + old + '" with "' + new + '"')
    
    
##################################################################################

main()
