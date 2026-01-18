import re
import sys
import argparse
import os
from file_util import FileUtil
from score_display import ScoreDisplay
from score_treemap import ScoreTreemap

ASM_FOLDERS = [
    './asm',
    './src/hasm',
    './libultra/src/gu',
    './libultra/src/libc',
    './libultra/src/os',
]

BLACKLIST = [
    '/nonmatchings/',
    '/assets/',
    '/boot/',
    '/data/',
    '/header.s',
    '/llmuldiv_gcc.s',
    '/libm_vals.s'
]

BLACKLIST_C = [
    'math_util.c',
    'collision.c',
    'kdebugserver.c',
]

# Version configuration
VALID_VERSIONS = ['us.v77', 'pal.v77', 'jpn.v79', 'us.v80', 'pal.v80']

# Name filtering configuration
BLACKLIST_NAMES = ['if', 'else', 'switch', 'while', 'for']
WHITELIST_JPN_NAMES = ['func_80082BC8_837C8', 'func_800C6464_C7064', 'func_800C663C_C723C',
    'func_800C67F4_C73F4', 'func_800C6870_C7470', 'func_800C68CC_C74CC', 'fontCreateDisplayList',
    'func_800C7744_C8344', 'func_800C7804_C8404', 'fontConvertString', 'func_800C78E0_C84E0']
WHITELIST_V79_NAMES = ['dmacopy_internal', 'rumble_enable']

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
GLABEL_REGEX = r'(?i)\b(?:glabel|leaf|xleaf)\s*(?:\()?([0-9A-Za-z_]+)(?:\))?'

for filename in filelist:
    with open(filename, 'r') as asmFile:
        text = asmFile.read()
        matches = re.finditer(GLABEL_REGEX, text, re.MULTILINE)
        for matchNum, match in enumerate(matches, start=1):
            name = match.group(1)
            if name and name not in ASM_LABELS:
                ASM_LABELS.append(name)

BUILD_DIRECTORY = './build'
SRC_DIRECTORY = './src'
LIB_SRC_DIRECTORY = './libultra/src'
FUNCTION_REGEX = r'^(?<!static\s)(?:(\/[*][*!][*]*\n(?:[^\/]*\n)+?\s*[*]\/\n)(?:\s*)*?)?(?:\s*UNUSED\s+)?([^\s]+)\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{'
GLOBAL_ASM_REGEX = r'\#pragma\sGLOBAL_ASM[(]".*(?=\/)\/([^.]+).s"[)]'
WIP_REGEX = r'ifdef\s+(?:NON_MATCHING|NON_EQUIVALENT)(?:.|\n)*?\#else\s*(\#pragma\sGLOBAL_ASM[(][^)]*[)])(.|\n)*?'
NON_MATCHING_REGEX = re.compile(r'^#ifdef +NON_MATCHING(?:.|\n)*?(?:\s*UNUSED\s+)?\S+\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{', re.MULTILINE)
NON_EQUVIALENT_REGEX = re.compile(r'^#ifdef +NON_EQUIVALENT(?:.|\n)*?(?:\s*UNUSED\s+)?\S+\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{', re.MULTILINE)

class DkrMapFile:
    def __init__(self, version="us.v77"):
        self.version = version
        self.code_start = 0
        self.code_end = 0
        self.code_size = 0
        self.functionSizes = {}

        map_file_path, actual_version = self.find_map_file(version)
        if not map_file_path:
            print("You must build a rom before it can be scored!")
            sys.exit()

        self.load_map_file(map_file_path)

        if actual_version != self.version:
            self.version = actual_version

    def find_map_file(self, version):
        map_file_path = f'{BUILD_DIRECTORY}/dkr.{version}.map'

        if os.path.exists(map_file_path):
            return map_file_path, version

        # If default version not found, try other valid versions
        if version == 'us.v77':
            for v in VALID_VERSIONS:
                if v != version:
                    alt_path = f'{BUILD_DIRECTORY}/dkr.{v}.map'
                    if os.path.exists(alt_path):
                        return alt_path, v

        return None, None

    def load_map_file(self, map_file_path):
        try:
            with open(map_file_path, 'r') as mapFile:
                functions = []
                lines = mapFile.read().split('\n')

                # First pass: Find code start and code end
                for line in lines:
                    if 'main_TEXT_START = .' in line:
                        parts = line.strip().split()
                        if len(parts) >= 2:
                            try:
                                self.code_start = int(parts[0], 16)
                            except ValueError:
                                pass
                    # End code size at the start of ucode text address instead
                    elif 'aspMainTextStart' in line:
                        parts = line.strip().split()
                        if len(parts) >= 2:
                            try:
                                self.code_end = int(parts[0], 16)
                            except ValueError:
                                pass

                if self.code_start == 0 or self.code_end == 0:
                    print("Error: Could not parse code boundaries from map file")
                    sys.exit()

                self.code_size = self.code_end - self.code_start

                # Second pass: Extract functions
                last_symbol = None
                last_address = 0
                symbol_addresses = {}

                for line in lines:
                    lineSet = 0
                    if line.startswith('                0x00000000'):
                        lineSet = 26
                    elif line.startswith('                0x8'):
                        lineSet = 18

                    if lineSet != 0:
                        if '=' in line:
                            line = line[0:line.find('=') - 1]
                        try:
                            address = int(line[lineSet:lineSet+8], 16)
                        except ValueError:
                            # no or incorrect address, skip
                            continue

                        if address >= self.code_start and address < self.code_end:
                            symbol = line[line.rfind(' ')+1:]
                            if (not symbol.startswith(".L") and not symbol.startswith("L800")
                                and not self.contains_forbidden_func(symbol)):
                                # Store symbol with its address
                                symbol_addresses[symbol] = address
                                functions.append((symbol, address))

                # Sort functions by address
                functions.sort(key=lambda x: x[1])

                # For each symbol, find the next symbol's address to calculate size
                sorted_symbols = [f[0] for f in functions]
                sorted_addresses = [f[1] for f in functions]

                for i in range(len(sorted_symbols)):
                    symbol = sorted_symbols[i]
                    address = sorted_addresses[i]

                    # Find next symbol address (excluding aliases that start with '_' and have same address)
                    next_address = self.code_end  # Default to code end if last symbol

                    for j in range(i + 1, len(sorted_addresses)):
                        # Check if this is a different function (not an alias)
                        if sorted_addresses[j] > address:
                            next_address = sorted_addresses[j]
                            break

                    self.functionSizes[symbol] = next_address - address

                self.numFunctions = len(functions)

        except FileNotFoundError:
            print("You must build a rom before it can be scored!")
            sys.exit()
        except Exception as e:
            print(f"Error loading map file: {e}")
            sys.exit()

    def contains_forbidden_func(self, string):
        forbidden = ['blkclr', 'cosf', 'sinf', '.']
        for f in forbidden:
            if f in string:
                return True
        return False

class ScoreFileMatch:
    def __init__(self, comment, functionName, version, map_file):
        self.comment = comment
        self.functionName = functionName
        self.version = version
        self.isProperlyNamed = not functionName.startswith("func_")
        self.isDocumented = (comment != None) and self.isProperlyNamed
        if functionName in map_file.functionSizes:
            self.size = map_file.functionSizes[functionName]
        else:
            self.size = 0

class ScoreFile:
    def __init__(self, filepath, version, map_file):
        self.functions = []
        self.unfinishedSize = 0
        self.numGlobalAsms = 0
        self.path = filepath
        self.version = version
        self.map_file = map_file
        self.read_file()
        self.get_matches()

    def read_file(self):
        with open(self.path, "r") as inFile:
            self.text = inFile.read()
            self.nonMatchings = re.findall(NON_MATCHING_REGEX, self.text)
            self.nonMatchingsSizes = 0
            for nonMatching in self.nonMatchings:
                if nonMatching in self.map_file.functionSizes:
                    self.nonMatchingsSizes += self.map_file.functionSizes[nonMatching]
            self.numNonMatchings = len(self.nonMatchings)
            all_nonEquivalents = re.findall(NON_EQUVIALENT_REGEX, self.text)
            # Filter out the ones based on version-specific rules
            self.nonEquivalents = []
            for ne in all_nonEquivalents:
                if not self.should_filter_name(ne):
                    self.nonEquivalents.append(ne)

            self.nonEquivalentsSizes = 0
            for nonEquivalent in self.nonEquivalents:
                if nonEquivalent in self.map_file.functionSizes:
                    self.nonEquivalentsSizes += self.map_file.functionSizes[nonEquivalent]
            self.numNonEquivalents = len(self.nonEquivalents)
            self.text = re.sub(WIP_REGEX, r"GLOBAL_ASM(\1)", self.text)

    def should_filter_name(self, func_name):
        if func_name in BLACKLIST_NAMES:
            return True

        # Apply version-specific whitelists
        version_parts = self.version.split('.')
        region = version_parts[0]
        ver_num = version_parts[1]

        # Japanese name check
        if region == 'jpn' and func_name in WHITELIST_JPN_NAMES:
            return False

        # Version 79 and above check
        if ver_num in ['v79', 'v80'] and func_name in WHITELIST_V79_NAMES:
            return False

        # Filter out if one of them is not set
        if region != 'jpn' and func_name in WHITELIST_JPN_NAMES:
            return True

        if ver_num not in ['v79', 'v80'] and func_name in WHITELIST_V79_NAMES:
            return True

        return False

    def get_matches(self):
        matches = re.finditer(FUNCTION_REGEX, self.text, re.MULTILINE)
        # Filter out the ones based on version-specific rules
        filtered_matches = []
        for match in matches:
            func_name = match.groups()[2]
            if not self.should_filter_name(func_name):
                filtered_matches.append(match)

        for matchNum, match in enumerate(filtered_matches, start=1):
            groups = match.groups()
            self.functions.append(ScoreFileMatch(groups[0], groups[2], self.version, self.map_file))
        matches = re.finditer(GLOBAL_ASM_REGEX, self.text, re.MULTILINE)
        # Filter out the ones based on version-specific rules
        filtered_matches = []
        for match in matches:
            func_name = match.groups()[0]
            if not self.should_filter_name(func_name):
                filtered_matches.append(match)

        for matchNum, match in enumerate(filtered_matches, start=1):
            groups = match.groups()
            self.numGlobalAsms += 1
            try:
                if groups[0] in self.map_file.functionSizes:
                    self.unfinishedSize += self.map_file.functionSizes[groups[0]]
            except Exception as e:
                pass

    def get_number_of_functions(self):
        return len(self.functions)

    def get_number_of_documented_functions(self):
        count = 0
        for func in self.functions:
            if func.isDocumented:
                count += 1
        return count

    def get_number_of_properly_named_functions(self):
        count = 0
        for func in self.functions:
            if func.isProperlyNamed:
                count += 1
        return count

    def get_number_of_functions_with_comments(self):
        count = 0
        for func in self.functions:
            if func.comment != None:
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
    parser.add_argument("--treemap", help="(Optional) Generates a treemap .html file", nargs='?', const="treemap.html", metavar="path/to/treemap-file.html")
    parser.add_argument("-v", "--version", help="(Optional) Select version", choices=VALID_VERSIONS, default="us.v77")
    args = parser.parse_args()
    adventureSelect = 3 # Show both adventures by default
    if args.adventure != None:
        adventureSelect = int(args.adventure)
    if args.top != None:
        showTopFiles = int(args.top)

    MAP_FILE = DkrMapFile(args.version)
    selectedVersion = MAP_FILE.version
    codeSize = MAP_FILE.code_size

    scoreFiles = []
    totalNumberOfDecompiledFunctions = 0
    totalNumberOfDocumentedFunctions = 0
    totalNumberOfProperlyNamedFunctions = 0
    totalNumberOfCommentedFunctions = 0
    totalNumberOfGlobalAsms = 0
    totalNumberOfNonMatching = 0
    totalNumberOfNonEquivalent = 0
    totalSizeOfDecompiledFunctions = 0
    totalSizeOfDecompiledAndNonMatchingFunctions = 0
    totalSizeOfDocumentedFunctions = 0
    ignoreNumberDocumentedFunctions = 0
    ignoreSizeDocumentedFunctions = 0

    srcFilenames = FileUtil.get_filenames_from_directory_recursive(SRC_DIRECTORY, extensions=('.c'))
    filtered_src_filenames = []

    for filename in srcFilenames:
        skipThis = False
        for blackListEntry in BLACKLIST_C:
            if blackListEntry in filename:
                skipThis = True
                break
        if not skipThis:
            filtered_src_filenames.append(filename)

    for filename in filtered_src_filenames:
        # Get score properties of dkr functions.
        scoreFile = ScoreFile(SRC_DIRECTORY + '/' + filename, selectedVersion, MAP_FILE)
        totalNumberOfDecompiledFunctions += len(scoreFile.functions)
        totalNumberOfGlobalAsms += scoreFile.numGlobalAsms
        totalNumberOfNonMatching += scoreFile.numNonMatchings
        totalNumberOfNonEquivalent += scoreFile.numNonEquivalents
        totalNumberOfDocumentedFunctions += scoreFile.get_number_of_documented_functions()
        totalNumberOfCommentedFunctions += scoreFile.get_number_of_functions_with_comments()
        totalNumberOfProperlyNamedFunctions += scoreFile.get_number_of_properly_named_functions()
        totalSizeOfDecompiledFunctions += scoreFile.get_size_of_functions()
        totalSizeOfDecompiledAndNonMatchingFunctions += scoreFile.get_size_of_functions_with_nonmatching()
        totalSizeOfDocumentedFunctions += scoreFile.get_size_of_documented_functions()
        scoreFiles.append(scoreFile)

    # Get score properties of libultra functions.
    srcFilenames = FileUtil.get_filenames_from_directory_recursive(LIB_SRC_DIRECTORY, extensions=('.c'))
    filtered_lib_filenames = []

    for filename in srcFilenames:
        skipThis = False
        for blackListEntry in BLACKLIST_C:
            if blackListEntry in filename:
                skipThis = True
                break
        if not skipThis:
            filtered_lib_filenames.append(filename)

    for filename in filtered_lib_filenames:
        scoreFile = ScoreFile(LIB_SRC_DIRECTORY + '/' + filename, selectedVersion, MAP_FILE)
        totalNumberOfDecompiledFunctions += len(scoreFile.functions)
        totalNumberOfGlobalAsms += scoreFile.numGlobalAsms
        ignoreNumberDocumentedFunctions += scoreFile.get_number_of_functions()
        totalSizeOfDecompiledFunctions += scoreFile.get_size_of_functions()
        totalSizeOfDecompiledAndNonMatchingFunctions += scoreFile.get_size_of_functions_with_nonmatching()
        ignoreSizeDocumentedFunctions += scoreFile.get_size_of_functions()
        scoreFiles.append(scoreFile)

    for asm_function in ASM_LABELS:
        if asm_function in MAP_FILE.functionSizes:
            totalNumberOfDecompiledFunctions += 1 # Consider hand written asm as "decompiled"
            asmFuncSize = MAP_FILE.functionSizes[asm_function]
            totalSizeOfDecompiledFunctions += asmFuncSize
            totalSizeOfDecompiledAndNonMatchingFunctions += asmFuncSize

    totalNumberOfFunctions = totalNumberOfDecompiledFunctions + totalNumberOfGlobalAsms
    adventureOnePercentage = (totalSizeOfDecompiledFunctions / codeSize) * 100
    adventureOnePercentageWithNonMatching = (totalSizeOfDecompiledAndNonMatchingFunctions / codeSize) * 100
    adventureTwoPercentage = (totalSizeOfDocumentedFunctions / (codeSize - ignoreSizeDocumentedFunctions)) * 100

    if args.summary:
        print(f"Decomp progress [{selectedVersion}]: {adventureOnePercentage:5.2f}%")
        print(f"Documentation progress: {adventureTwoPercentage:5.2f}%")
        sys.exit(0)

    if args.treemap:
        scoreTreemap = ScoreTreemap(MAP_FILE)
        output_path = args.treemap if args.treemap != "" else "treemap.html"
        scoreTreemap.generateTreemap(
            scoreFiles,
            output_path,
            selectedVersion,
            codeSize
        )
        sys.exit(0)

    displayedNumberOfDocumentedFunctions = totalNumberOfFunctions - ignoreNumberDocumentedFunctions

    scoreDisplay = ScoreDisplay()
    print(scoreDisplay.getDisplay(adventureOnePercentage, adventureOnePercentageWithNonMatching, adventureTwoPercentage, adventureSelect, selectedVersion, totalNumberOfDecompiledFunctions, totalNumberOfGlobalAsms, totalNumberOfNonMatching, totalNumberOfNonEquivalent, totalNumberOfDocumentedFunctions, displayedNumberOfDocumentedFunctions - totalNumberOfDocumentedFunctions, displayedNumberOfDocumentedFunctions - totalNumberOfProperlyNamedFunctions, displayedNumberOfDocumentedFunctions - totalNumberOfCommentedFunctions))

    if showTopFiles > 0:
        if showTopFiles > len(scoreFiles):
            showTopFiles = len(scoreFiles)
        print('======= TOP FILES ======== |  TODO  |  DONE  |')
        files = []
        for file in scoreFiles:
            files.append([file.path, file.unfinishedSize, file.get_size_of_functions()])
        files.sort(key=lambda x:x[1], reverse=True) # Sort by Size, Largest to Smallest
        for i in range(0, showTopFiles):
            percentageRemaining = (files[i][1] / codeSize) * 100
            percentageDone = (files[i][2] / codeSize) * 100
            funcName = files[i][0]
            if '/' in funcName:
                funcName = funcName[funcName.rindex('/') + 1:]
            print("", funcName, (" " * (24 - len(funcName))), "| {:5.2f}% | {:5.2f}% |".format(percentageRemaining, percentageDone))

main()
