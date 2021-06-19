import sys

from file_util import FileUtil

ASM_DIR = './asm'
LIB_ASM_DIR = './lib/asm'
SRC_DIR = './src'
LIB_SRC_DIR = './lib/src'

if len(sys.argv) < 2:
    print('Usage: rename_file.py old_symbol new_symbol')

oldSymbol = sys.argv[1]
newSymbol = sys.argv[2]

def find_and_rename(directory, paths):
    for name in paths:
        path = directory + '/' + name
        if oldSymbol in path:
            newPath = path.replace(oldSymbol, newSymbol)
            try:
                FileUtil.rename_file(path, newPath)
                print('Renamed "' + path + '" to "' + newPath + '"')
            except FileNotFoundError:
                pass

asmDirectories = FileUtil.get_directories_from_directory_recursive(ASM_DIR)
asmFiles = FileUtil.get_filenames_from_directory_recursive(ASM_DIR)
libAsmDirectories = FileUtil.get_directories_from_directory_recursive(LIB_ASM_DIR)
libAsmFiles = FileUtil.get_filenames_from_directory_recursive(ASM_DIR)
srcFiles = FileUtil.get_filenames_from_directory_recursive(SRC_DIR)
libSrcFiles = FileUtil.get_filenames_from_directory_recursive(LIB_SRC_DIR)

find_and_rename(ASM_DIR, asmDirectories + asmFiles)
find_and_rename(LIB_ASM_DIR, libAsmDirectories + libAsmFiles)
find_and_rename(SRC_DIR, srcFiles)
find_and_rename(LIB_SRC_DIR, libSrcFiles)
