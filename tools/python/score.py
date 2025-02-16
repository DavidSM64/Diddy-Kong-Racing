import re
import sys
import argparse
import time
import os
from file_util import FileUtil
from score_display import ScoreDisplay

ASM_FOLDERS = [
    './asm',
    './lib/asm',
]

BLACKLIST = [
    '/non_matchings/'
]

BLACKLIST_C = [
    'math_util.c',
    'collision.c',
]

filelist = []

for asmDir in ASM_FOLDERS:
    for root, dirs, files in os.walk(asmDir):
        for file in files:
            fullPath = os.path.join(root,file)
            skipThis = False
            for blackListEntry in BLACKLIST:
                if blackListEntry in fullPath:
                    skipThis = True
                    break
            if not skipThis and fullPath.endswith('.s'):
                filelist.append(fullPath)

# These will automatically be added to the adventure one percentage.
ASM_LABELS = []
GLABEL_REGEX = r'glabel ([0-9A-Za-z_]+)'
for filename in filelist:
    with open(filename, 'r') as asmFile:
        text = asmFile.read()
        matches = re.finditer(GLABEL_REGEX, text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            glabel = match.groups()[0]
            if not glabel in ASM_LABELS:
                ASM_LABELS.append(glabel)

BUILD_DIRECTORY = './build/us_1.0'
SRC_DIRECTORY = './src'
LIB_SRC_DIRECTORY = './lib/src'
FUNCTION_REGEX = r'^(?<!static\s)(?:(\/[*][*!][*]*\n(?:[^/]*\n)+?\s*[*]\/\n)(?:\s*)*?)?(?:\s*UNUSED\s+)?([^\s]+)\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{'
GLOBAL_ASM_REGEX = r'GLOBAL_ASM[(]".*(?=\/)\/([^.]+).s"[)]'
WIP_REGEX = r'#ifdef\s+(?:NON_MATCHING|NON_EQUIVALENT)(?:.|\n)*?#else\s*(GLOBAL_ASM[(][^)]*[)])(.|\n)*?#endif'
NON_MATCHING_REGEX = re.compile(r'^#ifdef[ ]+NON_MATCHING(?:.|\n)*?(?:\s*UNUSED\s+)?(?:[^\s]+)\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{', re.MULTILINE)
NON_EQUVIALENT_REGEX = re.compile(r'^#ifdef[ ]+NON_EQUIVALENT', re.MULTILINE)

CODE_START = 0x80000400
CODE_END = 0x800D75F4
CODE_SIZE = CODE_END - CODE_START

class DkrMapFile:
    def __init__(self):
        try:
            with open(BUILD_DIRECTORY + '/dkr.map', 'r') as mapFile:
                self.functionSizes = {}
                functions = []
                lines = mapFile.read().split('\n')
                for line in lines:
                    if line.startswith('                0x8'):
                        if '=' in line:
                            line = line[0:line.find('=')-1]
                        address = int(line[18:18+8], 16)
                        if address >= CODE_START and address < CODE_END:
                            symbol = line[line.rfind(' ')+1:]
                            functions.append((symbol, address))
                functions.sort(key=lambda x:x[1]) # Sort by RAM address
                for i in range(0, len(functions) - 1):
                    self.functionSizes[functions[i][0]] = functions[i + 1][1] - functions[i][1]
                self.functionSizes[functions[len(functions) - 1][0]] = CODE_END - 0x800D7570 
                self.numFunctions = len(functions)
        except FileNotFoundError:
            print("You must build a rom before it can be scored!")
            sys.exit()

MAP_FILE = DkrMapFile()

NOT_FUNCTION_NAMES = ['if', 'else', 'switch', 'while', 'for']

class ScoreFileMatch:
    def __init__(self, comment, functionName):
        self.comment = comment
        self.functionName = functionName
        self.isDocumented = (comment != None) and not functionName.startswith("func_")
        if functionName in MAP_FILE.functionSizes:
            self.size = MAP_FILE.functionSizes[functionName]
        else:
            self.size = 0
    
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
            self.nonMatchings = re.findall(NON_MATCHING_REGEX, self.text)
            self.nonMatchingsSizes = 0
            for nonMatching in self.nonMatchings:
                self.nonMatchingsSizes += MAP_FILE.functionSizes[nonMatching]
            self.numNonMatchings = len(self.nonMatchings)
            self.numNonEquivalents = len(re.findall(NON_EQUVIALENT_REGEX, self.text))
            self.text = re.sub(WIP_REGEX, r"GLOBAL_ASM(\1)", self.text)
            
    def get_matches(self):
        matches = re.finditer(FUNCTION_REGEX, self.text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            groups = match.groups()
            if groups[2] not in NOT_FUNCTION_NAMES:
                self.functions.append(ScoreFileMatch(groups[0], groups[2]))
        matches = re.finditer(GLOBAL_ASM_REGEX, self.text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            groups = match.groups()
            self.numGlobalAsms += 1
            try:
                self.unfinishedSize += MAP_FILE.functionSizes[groups[0]]
            except Exception:
                pass
    
    def get_number_of_functions(self):
        return len(self.functions)

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
        
    def get_size_of_functions_with_nonmatching(self):
        return self.get_size_of_functions() + self.nonMatchingsSizes
        
    def get_size_of_documented_functions(self):
        size = 0
        for func in self.functions:
            if func.isDocumented:
                size += func.size
        return size

def main():
    showTopFiles = 0
    
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("-t", "--top", help="(Optional) Shows the top N files remaining.")
    parser.add_argument("-a", "--adventure", help="(Optional) Only shows adventure 1 or 2 based on passed in value.", choices=['1', '2'])
    parser.add_argument("-s", "--summary", help="(Optional) Only prints the percentages for adventure 1 and 2", action='store_true')
    args = parser.parse_args()
    adventureSelect = 3 # Show both adventures by default
    if args.adventure != None:
        adventureSelect = int(args.adventure)
    if args.top != None:
        showTopFiles = int(args.top)

    scoreFiles = []
    totalNumberOfDecompiledFunctions = 0
    totalNumberOfDocumentedFunctions = 0
    totalNumberOfGlobalAsms = 0
    totalNumberOfNonMatching = 0
    totalNumberOfNonEquivalent = 0
    totalSizeOfDecompiledFunctions = 0
    totalSizeOfDecompiledAndNonMatchingFunctions = 0
    totalSizeOfDocumentedFunctions = 0
    ignoreNumberDocumentedFunctions = 0
    ignoreSizeDocumentedFunctions = 0
    
    srcFilenames = FileUtil.get_filenames_from_directory_recursive(SRC_DIRECTORY, extensions=('.c'))
    for filename in srcFilenames:
        skipThis = False
        for blackListEntry in BLACKLIST_C:
            if blackListEntry in filename:
                skipThis = True
                break
        if not skipThis:
            # Get score properties of dkr functions.
            scoreFile = ScoreFile(SRC_DIRECTORY + '/' + filename)
            totalNumberOfDecompiledFunctions += len(scoreFile.functions)
            totalNumberOfGlobalAsms += scoreFile.numGlobalAsms
            totalNumberOfNonMatching += scoreFile.numNonMatchings
            totalNumberOfNonEquivalent += scoreFile.numNonEquivalents
            totalNumberOfDocumentedFunctions += scoreFile.get_number_of_documented_functions()
            totalSizeOfDecompiledFunctions += scoreFile.get_size_of_functions()
            totalSizeOfDecompiledAndNonMatchingFunctions += scoreFile.get_size_of_functions_with_nonmatching()
            totalSizeOfDocumentedFunctions += scoreFile.get_size_of_documented_functions()
            scoreFiles.append(scoreFile)
    # Get score properties of libultra functions.
    srcFilenames = FileUtil.get_filenames_from_directory_recursive(LIB_SRC_DIRECTORY, extensions=('.c'))
    for filename in srcFilenames:
        scoreFile = ScoreFile(LIB_SRC_DIRECTORY + '/' + filename)
        totalNumberOfDecompiledFunctions += len(scoreFile.functions)
        totalNumberOfGlobalAsms += scoreFile.numGlobalAsms
        #totalNumberOfDocumentedFunctions += scoreFile.get_number_of_documented_functions()
        ignoreNumberDocumentedFunctions += scoreFile.get_number_of_functions()
        totalSizeOfDecompiledFunctions += scoreFile.get_size_of_functions()
        totalSizeOfDecompiledAndNonMatchingFunctions += scoreFile.get_size_of_functions_with_nonmatching()
        #totalSizeOfDocumentedFunctions += scoreFile.get_size_of_documented_functions()
        ignoreSizeDocumentedFunctions += scoreFile.get_size_of_functions()
        scoreFiles.append(scoreFile)
    
    
    totalNumberOfFunctions = totalNumberOfDecompiledFunctions + totalNumberOfGlobalAsms
    for asm_function in ASM_LABELS:
        if asm_function in MAP_FILE.functionSizes:
            asmFuncSize = MAP_FILE.functionSizes[asm_function]
            totalSizeOfDecompiledFunctions += asmFuncSize
            totalSizeOfDecompiledAndNonMatchingFunctions += asmFuncSize
    
    adventureOnePercentage = (totalSizeOfDecompiledFunctions / CODE_SIZE) * 100
    adventureOnePercentageWithNonMatching = (totalSizeOfDecompiledAndNonMatchingFunctions / CODE_SIZE) * 100
    adventureTwoPercentage = (totalSizeOfDocumentedFunctions / (CODE_SIZE - ignoreSizeDocumentedFunctions)) * 100
    
    if args.summary:
        print(f"Decomp progress: {adventureOnePercentage:5.2f}%")
        print(f"Documentation progress: {adventureTwoPercentage:5.2f}%")
        sys.exit(0)
    scoreDisplay = ScoreDisplay()
    print(scoreDisplay.getDisplay(adventureOnePercentage, adventureOnePercentageWithNonMatching, adventureTwoPercentage, adventureSelect, totalNumberOfDecompiledFunctions, totalNumberOfGlobalAsms, totalNumberOfNonMatching, totalNumberOfNonEquivalent, totalNumberOfDocumentedFunctions, (totalNumberOfFunctions - ignoreNumberDocumentedFunctions) - totalNumberOfDocumentedFunctions))
    
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
            funcName = files[i][0]
            if '/' in funcName:
                funcName = funcName[funcName.rindex('/') + 1:]
            print("", funcName, (" " * (24 - len(funcName))), "| {:5.2f}% | {:5.2f}% |".format(percentageRemaining, percentageDone))
    

main()
