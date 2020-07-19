import re
import sys
from file_util import FileUtil

SRC_DIRECTORY = './src'
FUNCTION_REGEX = r'([/][*]([^*]|([*][^/]))*[*][/][\n]\s*)?(void|s64|s32|s16|s8|u64|u32|u16|u8|f32|f64)(\s|[*])*([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{'
GLOBAL_ASM_REGEX = r'GLOBAL_ASM[(]\"[^/]*/[^/]*/[^/]*/([a-zA-Z0-9_]*).s\"[)]'
WIP_REGEX = r'#if(.|\n)*?(GLOBAL_ASM[(]([^)]*)[)])(.|\n)*?#else(.|\n)*?#endif'

CODE_START = 0x80000400
CODE_END = 0x800D75F4
CODE_SIZE = CODE_END - CODE_START

class DkrMapFile:
    def __init__(self):
        with open('./build/dkr.map', 'r') as mapFile:
            self.functionSizes = {}
            functions = []
            lines = mapFile.read().split('\n')
            for line in lines:
                if line.startswith('                0x00000000'):
                    if '=' in line:
                        line = line[0:line.find('=')-1]
                    address = int(line[26:26+8], 16)
                    if address >= CODE_START and address < CODE_END:
                        symbol = line[line.rfind(' ')+1:]
                        functions.append((symbol, address))
            functions.sort(key=lambda x:x[1]) # Sort by RAM address
            for i in range(0, len(functions) - 1):
                self.functionSizes[functions[i][0]] = functions[i + 1][1] - functions[i][1]
            self.functionSizes[functions[len(functions) - 1][0]] = CODE_END - 0x800D7570 
            self.numFunctions = len(functions)

MAP_FILE = DkrMapFile()

class ScoreFileMatch:
    def __init__(self, comment, functionName):
        self.comment = comment
        self.functionName = functionName
        self.isDocumented = (comment != None) and not functionName.startswith("func_")
        self.size = MAP_FILE.functionSizes[functionName]
    
class ScoreFile:
    def __init__(self, filepath):
        self.functions = []
        self.unfinishedSize = 0
        self.numGlobalAsms = 0
        self.path = filepath
        self.read_file()
        self.get_matches()
        #print(self.path, len(self.functions), self.numGlobalAsms, self.get_number_of_documented_functions())
    
    def read_file(self):
        with open(self.path, "r") as inFile:
            self.text = inFile.read()
            self.text = re.sub(WIP_REGEX, r"GLOBAL_ASM(\3)", self.text)
            
    def get_matches(self):
        matches = re.finditer(FUNCTION_REGEX, self.text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            groups = match.groups()
            self.functions.append(ScoreFileMatch(groups[0], groups[5]))
            
        matches = re.finditer(GLOBAL_ASM_REGEX, self.text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            groups = match.groups()
            self.numGlobalAsms += 1
            try:
                self.unfinishedSize += MAP_FILE.functionSizes[groups[0]]
            except Exception:
                pass
        
    def get_number_of_documented_functions(self):
        count = 0
        for func in self.functions:
            if func.isDocumented:
                count += 1
        return count
        
    def get_size_of_functions(self):
        size = 0
        for func in self.functions:
            size += func.size
        return size
        
    def get_size_of_documented_functions(self):
        size = 0
        for func in self.functions:
            if func.isDocumented:
                size += func.size
        return size

def main():
    showTopFiles = 0

    numArgs = len(sys.argv)
    for i in range(1, numArgs):
        arg = sys.argv[i].lower()
        print('Argument:', sys.argv[i])
        if arg.startswith("--top"):
            num = arg[5:]
            if num == "":
                showTopFiles = 10 # 10 is the default
            else:
                showTopFiles = int(num)

    scoreFiles = []
    srcFilenames = FileUtil.get_filenames_from_directory_recursive(SRC_DIRECTORY, extensions=('.c'))
    totalNumberOfDecompiledFunctions = 0
    totalNumberOfDocumentedFunctions = 0
    totalNumberOfGlobalAsms = 0
    totalSizeOfDecompiledFunctions = 0
    totalSizeOfDocumentedFunctions = 0
    for filename in srcFilenames:
        scoreFile = ScoreFile(SRC_DIRECTORY + '/' + filename)
        totalNumberOfDecompiledFunctions += len(scoreFile.functions)
        totalNumberOfGlobalAsms += scoreFile.numGlobalAsms
        totalNumberOfDocumentedFunctions += scoreFile.get_number_of_documented_functions()
        totalSizeOfDecompiledFunctions += scoreFile.get_size_of_functions()
        totalSizeOfDocumentedFunctions += scoreFile.get_size_of_documented_functions()
        scoreFiles.append(scoreFile)
    totalNumberOfFunctions = MAP_FILE.numFunctions
    
    adventureOnePercentage = (totalSizeOfDecompiledFunctions / CODE_SIZE) * 100
    adventureTwoPercentage = (totalSizeOfDocumentedFunctions / CODE_SIZE) * 100
    
    print('=========================================')
    print(' ADVENTURE ONE (ASM -> C Decompilation)')
    print(' ----------- {:5.2f}% Complete -----------'.format(adventureOnePercentage))
    print(' # Decompiled functions: ' + str(totalNumberOfDecompiledFunctions))
    print(' # GLOBAL_ASM remaining: ' + str(totalNumberOfGlobalAsms))
    print('=========================================')
    print(' ADVENTURE TWO (Cleanup & Documentation)')
    print(' ----------- {:5.2f}% Complete -----------'.format(adventureTwoPercentage))
    print(' # Documented functions:   ' + str(totalNumberOfDocumentedFunctions))
    print(' # Undocumented remaining: ' + str(totalNumberOfFunctions - totalNumberOfDocumentedFunctions))
    print('=========================================')
    
    if showTopFiles > 0:
        if showTopFiles > len(scoreFiles):
            showTopFiles = len(scoreFiles)
        print('======= TOP FILES ======== |  TODO  |  DONE  |')
        files = []
        for file in scoreFiles:
            files.append([file.path, file.unfinishedSize, file.get_size_of_functions()])
        files.sort(key=lambda x:x[1], reverse=True) # Sort by Size, Largest to Smallest
        for i in range(0, showTopFiles):
            percentageRemaining = (files[i][1] / CODE_SIZE) * 100
            percentageDone = (files[i][2] / CODE_SIZE) * 100
            funcName = files[i][0][12:]
            print("", funcName, (" " * (24 - len(funcName))), "| {:5.2f}% | {:5.2f}% |".format(percentageRemaining, percentageDone))
    

main()
