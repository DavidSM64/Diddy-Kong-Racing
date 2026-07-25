import re
import sys
import argparse
import os
from file_util import FileUtil
from score_display import ScoreDisplay

ASM_FOLDERS = [
    './asm',
    './src/hasm',
]

LIB_ASM_FOLDERS = [
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
    '/libm_vals.s'
]

BLACKLIST_C = [
    'math_util.c',
    'collision.c',
    'kdebugserver.c',
    'libgcc.c',
]

VALID_VERSIONS = ['us.v77', 'pal.v77', 'jpn.v79', 'us.v80', 'pal.v80']
BUILD_DIRECTORY = './build'
SRC_DIRECTORY = './src'
LIB_SRC_DIRECTORY = './libultra/src'

# Regex patterns
FUNCTION_REGEX = r'^(?<!static\s)(?:(\/[*][*!][*]*\n(?:[^\/]*\n)+?\s*[*]\/\n)(?:\s*)*?)?(?:\s*UNUSED\s+)?([^\s]+)\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{'
GLOBAL_ASM_REGEX = r'\#pragma\sGLOBAL_ASM[(]".*(?=\/)\/([^.]+).s"[)]'
WIP_REGEX = r'ifdef\s+(?:NON_MATCHING|NON_EQUIVALENT)(?:.|\n)*?\#else\s*(\#pragma\sGLOBAL_ASM[(][^)]*[)])(.|\n)*?'
NON_MATCHING_REGEX = re.compile(r'^#ifdef +NON_MATCHING(?:.|\n)*?(?:\s*UNUSED\s+)?\S+\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{', re.MULTILINE)
NON_EQUVIALENT_REGEX = re.compile(r'^#ifdef +NON_EQUIVALENT(?:.|\n)*?(?:\s*UNUSED\s+)?\S+\s(?:\s|[*])*?([0-9A-Za-z_]+)\s*[(][^)]*[)]\s*{', re.MULTILINE)

# Name filters
BLACKLIST_NAMES = ['if', 'else', 'switch', 'while', 'for']
BLACKLIST_JPN_NAMES = ['load_font', 'unload_font']
WHITELIST_JPN_NAMES = [
    'func_80082BC8_837C8', 'func_800C6464_C7064', 'func_800C663C_C723C',
    'func_800C67F4_C73F4', 'func_800C6870_C7470', 'func_800C68CC_C74CC',
    'fontCreateDisplayList', 'func_800C7744_C8344', 'func_800C7804_C8404',
    'fontConvertString', 'func_800C78E0_C84E0'
]
WHITELIST_V79_NAMES = ['dmacopy_internal', 'rumble_enable']

class ScoreUtil:
    @staticmethod
    def build_asm_filelist(include_lib=True):
        filelist = []
        sources = []

        # Main ASM folders
        for asm_dir in ASM_FOLDERS:
            if os.path.exists(asm_dir):
                for root, _, files in os.walk(asm_dir):
                    for file in files:
                        full_path = os.path.join(root, file)
                        if any(blacklist in full_path for blacklist in BLACKLIST):
                            continue
                        if full_path.endswith('.s'):
                            filelist.append(full_path)
                            sources.append('main')

        # Libultra ASM folders
        if include_lib:
            for asm_dir in LIB_ASM_FOLDERS:
                if os.path.exists(asm_dir):
                    for root, _, files in os.walk(asm_dir):
                        for file in files:
                            full_path = os.path.join(root, file)
                            if full_path.endswith('.s'):
                                filelist.append(full_path)
                                sources.append('lib')

        return filelist, sources

    @staticmethod
    def build_asm_labels(filelist, sources):
        labels = []
        label_sources = []
        label_regex = r'(?i)\b(?:glabel|leaf|xleaf)\s*(?:\()?([0-9A-Za-z_]+)(?:\))?'

        for idx, filename in enumerate(filelist):
            with open(filename, 'r') as asm_file:
                text = asm_file.read()
                for match in re.finditer(label_regex, text, re.MULTILINE):
                    name = match.group(1)
                    if name and name not in labels:
                        labels.append(name)
                        label_sources.append(sources[idx])

        return labels, label_sources

    @staticmethod
    def filter_filenames(filenames, blacklist):
        return [f for f in filenames if not any(black in f for black in blacklist)]


class DkrMapFile:
    def __init__(self, version="us.v77"):
        self.version = version
        self.code_start = 0
        self.code_end = 0
        self.code_size = 0
        self.function_sizes = {}
        self.function_sources = {}

        map_file_path, actual_version = self._find_map_file(version)
        if not map_file_path:
            print("You must build a rom before it can be scored!")
            sys.exit()

        self._load_map_file(map_file_path)
        self.version = actual_version

    def _find_map_file(self, version):
        map_path = f'{BUILD_DIRECTORY}/dkr.{version}.map'
        if os.path.exists(map_path):
            return map_path, version

        # Try alternate versions
        if version == 'us.v77':
            for v in VALID_VERSIONS:
                if v != version:
                    alt_path = f'{BUILD_DIRECTORY}/dkr.{v}.map'
                    if os.path.exists(alt_path):
                        return alt_path, v

        return None, None

    def _load_map_file(self, map_file_path):
        try:
            with open(map_file_path, 'r') as map_file:
                lines = map_file.read().split('\n')
                functions = []
                current_obj = None

                # First pass: Find code boundaries
                for line in lines:
                    if 'main_TEXT_START = .' in line:
                        parts = line.strip().split()
                        if len(parts) >= 2:
                            try:
                                self.code_start = int(parts[0], 16)
                            except ValueError:
                                pass
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

                # Second pass: Parse symbols and track object files
                for line in lines:
                    # Track current object file from section headers
                    if '.text' in line and 'build/' in line:
                        for part in line.split():
                            if part.endswith('.o') or part.endswith('.c.o'):
                                current_obj = part
                                break

                    # Parse function symbols
                    line_set = 0
                    if line.startswith('                0x00000000'):
                        line_set = 26
                    elif line.startswith('                0x8'):
                        line_set = 18

                    if line_set != 0:
                        if '=' in line:
                            line = line[:line.find('=') - 1]

                        try:
                            address = int(line[line_set:line_set + 8], 16)
                        except ValueError:
                            continue

                        if self.code_start <= address < self.code_end:
                            symbol = line[line.rfind(' ') + 1:]
                            if (not symbol.startswith((".L", "L800")) and
                                not self._is_forbidden(symbol)):
                                if current_obj:
                                    self.function_sources[symbol] = current_obj
                                functions.append((symbol, address))

                # Sort and calculate sizes
                functions.sort(key=lambda x: x[1])
                symbols = [f[0] for f in functions]
                addresses = [f[1] for f in functions]

                for i, symbol in enumerate(symbols):
                    next_address = self.code_end
                    for j in range(i + 1, len(addresses)):
                        if addresses[j] > addresses[i]:
                            next_address = addresses[j]
                            break
                    self.function_sizes[symbol] = next_address - addresses[i]

        except FileNotFoundError:
            print("You must build a rom before it can be scored!")
            sys.exit()
        except Exception as e:
            print(f"Error loading map file: {e}")
            sys.exit()

    @staticmethod
    def _is_forbidden(string):
        forbidden = ['blkclr', 'cosf', 'sinf', '.']
        return any(f in string for f in forbidden)

    def is_libultra_function(self, func_name):
        obj_file = self.function_sources.get(func_name)
        return obj_file and 'libultra' in obj_file

class FunctionMatch:
    def __init__(self, comment, function_name, version, map_file):
        self.comment = comment
        self.function_name = function_name
        self.version = version
        self.is_properly_named = not function_name.startswith("func_")
        self.is_documented = comment is not None and self.is_properly_named
        self.size = map_file.function_sizes.get(function_name, 0)


class ScoreFile:
    def __init__(self, filepath, version, map_file):
        self.filepath = filepath
        self.version = version
        self.map_file = map_file
        self.functions = []
        self.num_global_asms = 0
        self.non_matchings = []
        self.non_equivalents = []
        self._load_file()

    def _load_file(self):
        with open(self.filepath, "r") as in_file:
            text = in_file.read()

            # Extract non-matchings
            self.non_matchings = re.findall(NON_MATCHING_REGEX, text)
            self.num_non_matchings = len(self.non_matchings)

            # Extract non-equivalents (filtered by version)
            all_non_equiv = re.findall(NON_EQUVIALENT_REGEX, text)
            self.non_equivalents = [ne for ne in all_non_equiv
                                    if not self._filter_by_version(ne)]
            self.num_non_equivalents = len(self.non_equivalents)

            # Replace WIP blocks with GLOBAL_ASM
            text = re.sub(WIP_REGEX, r"GLOBAL_ASM(\1)", text)

            # Track GLOBAL_ASM size from the modified text
            self.global_asm_size = 0
            for match in re.finditer(GLOBAL_ASM_REGEX, text, re.MULTILINE):
                func_name = match.groups()[0]
                if not self._filter_by_version(func_name):
                    self.global_asm_size += self.map_file.function_sizes.get(func_name, 0)

            # Extract functions
            matches = re.finditer(FUNCTION_REGEX, text, re.MULTILINE)
            self.functions = []
            seen = set()
            for match in matches:
                comment, _, func_name = match.groups()
                if (func_name not in seen and
                    not self._filter_by_version(func_name)):
                    seen.add(func_name)
                    self.functions.append(
                        FunctionMatch(comment, func_name, self.version, self.map_file)
                    )

            # Extract GLOBAL_ASM
            matches = re.finditer(GLOBAL_ASM_REGEX, text, re.MULTILINE)
            self.num_global_asms = 0
            seen = set()
            for match in matches:
                func_name = match.groups()[0]
                if func_name not in seen and not self._filter_by_version(func_name):
                    seen.add(func_name)
                    self.num_global_asms += 1

    def _filter_by_version(self, func_name):
        if func_name in BLACKLIST_NAMES:
            return True

        region, ver_num = self.version.split('.')

        # Japanese-specific
        if region == 'jpn':
            if func_name in BLACKLIST_JPN_NAMES:
                return True
            if func_name in WHITELIST_JPN_NAMES:
                return False
        elif func_name in WHITELIST_JPN_NAMES:
            return True

        # Version 79+ whitelist
        if ver_num in ['v79', 'v80']:
            if func_name in WHITELIST_V79_NAMES:
                return False
        elif func_name in WHITELIST_V79_NAMES:
            return True

        return False

    def function_count(self):
        return len(self.functions)

    def documented_count(self):
        return sum(1 for f in self.functions if f.is_documented)

    def properly_named_count(self):
        return sum(1 for f in self.functions if f.is_properly_named)

    def commented_count(self):
        return sum(1 for f in self.functions if f.comment is not None)

    def total_size(self):
        return sum(f.size for f in self.functions)

    def documented_size(self):
        return sum(f.size for f in self.functions if f.is_documented)

    def size_with_nonmatching(self):
        return self.total_size() + self._non_matching_size()

    def _non_matching_size(self):
        return sum(self.map_file.function_sizes.get(f, 0)
                   for f in self.non_matchings)

    def _non_equivalent_size(self):
        return sum(self.map_file.function_sizes.get(f, 0)
                   for f in self.non_equivalents)

def main():
    parser = argparse.ArgumentParser(description="DKR Decompilation Score Tool")
    parser.add_argument("-t", "--top", help="Shows the top N files remaining", nargs='?', const=10, type=int, default=0)
    parser.add_argument("-a", "--adventure", help="Only shows adventure 1 or 2", choices=['1', '2'])
    parser.add_argument("-s", "--summary", help="Only prints the percentages", action='store_true')
    parser.add_argument("--treemap", help="Generates a treemap .html file", nargs='?', const="treemap.html", metavar="path/to/treemap-file.html")
    parser.add_argument("-v", "--version", help="Select version", choices=VALID_VERSIONS, default="us.v77")
    parser.add_argument("--nolib", help="Exclude libultra code from scoring", action='store_true')
    args = parser.parse_args()

    include_lib = not args.nolib
    adventure_select = 3 if args.adventure is None else int(args.adventure)
    show_top_files = args.top or 0

    # Build ASM lists
    asm_filelist, asm_sources = ScoreUtil.build_asm_filelist(include_lib)
    asm_labels, asm_label_sources = ScoreUtil.build_asm_labels(asm_filelist, asm_sources)

    # Load map file
    map_file = DkrMapFile(args.version)
    selected_version = map_file.version

    score_files = []

    # Adventure one counters
    adv1 = {
        'decompiled': 0,
        'handwritten_asms': 0,
        'global_asms': 0,
        'non_matching': 0,
        'non_equivalent': 0,
        'size': 0,
        'size_with_nonmatching': 0,
    }

    # Adventure two counters
    adv2 = {
        'total': 0,
        'documented': 0,
        'properly_named': 0,
        'commented': 0,
        'size_documented': 0,
    }

    # Core size tracking
    sizes = {
        'decompiled': 0,
        'countable': 0,
        'global_asm': 0,
    }

    def process_score_file(score_file, is_lib=False):
        # Track functions in this file
        for func in score_file.functions:
            if func.function_name in map_file.function_sizes:
                sizes['countable'] += map_file.function_sizes[func.function_name]

        # Decompiled size (C functions)
        decompiled_size = score_file.total_size()
        sizes['decompiled'] += decompiled_size
        sizes['global_asm'] += score_file.global_asm_size
        adv1['size'] += decompiled_size
        adv1['size_with_nonmatching'] += score_file.size_with_nonmatching()

        # Adventure one counts
        adv1['decompiled'] += score_file.function_count()
        adv1['global_asms'] += score_file.num_global_asms
        adv1['non_matching'] += score_file.num_non_matchings
        adv1['non_equivalent'] += score_file.num_non_equivalents

        # Adventure two counts
        if not is_lib:
            adv2['total'] += score_file.function_count()
            adv2['documented'] += score_file.documented_count()
            adv2['commented'] += score_file.commented_count()
            adv2['properly_named'] += score_file.properly_named_count()
            adv2['size_documented'] += score_file.documented_size()

    # Process main C files
    src_files = FileUtil.get_filenames_from_directory_recursive(SRC_DIRECTORY, extensions=('.c'))
    for filename in ScoreUtil.filter_filenames(src_files, BLACKLIST_C):
        score_file = ScoreFile(f'{SRC_DIRECTORY}/{filename}', selected_version, map_file)
        process_score_file(score_file, is_lib=False)
        score_files.append(score_file)

    # Process libultra C files
    lib_files = FileUtil.get_filenames_from_directory_recursive(LIB_SRC_DIRECTORY, extensions=('.c'))
    for filename in ScoreUtil.filter_filenames(lib_files, BLACKLIST_C):
        score_file = ScoreFile(f'{LIB_SRC_DIRECTORY}/{filename}', selected_version, map_file)
        if include_lib:
            process_score_file(score_file, is_lib=True)
        score_files.append(score_file)

    # Process ASM files
    lib_asm_labels = {asm_labels[i] for i in range(len(asm_labels)) if asm_label_sources[i] == 'lib'}

    for asm_function in asm_labels:
        if asm_function in map_file.function_sizes:
            asm_size = map_file.function_sizes[asm_function]
            is_lib = asm_function in lib_asm_labels

            sizes['countable'] += asm_size

            # Only include non-libultra ASM in decompiled size
            if not (is_lib and not include_lib):
                adv1['handwritten_asms'] += 1
                adv1['size'] += asm_size
                adv1['size_with_nonmatching'] += asm_size
                sizes['decompiled'] += asm_size

    # Denominator: Total functions in source files
    code_size_for_adv1 = sizes['countable']

    # Numerator: Decompiled functions minus GLOBAL_ASM
    adv1_size = sizes['decompiled'] - sizes['global_asm']
    adv1_size = max(0, adv1_size)

    # Adventure one percentage
    adventure_one_pct = (adv1_size / code_size_for_adv1 * 100) if code_size_for_adv1 > 0 else 0.0
    adventure_one_pct_nonmatch = adventure_one_pct

    # Adventure two: documentation progress (non-libultra only)
    main_code_size = sum(size for func, size in map_file.function_sizes.items()
                         if not map_file.is_libultra_function(func))
    adventure_two_pct = (adv2['size_documented'] / main_code_size * 100) if main_code_size > 0 else 100.0

    # Display counts
    total_undocumented = adv2['total'] - adv2['documented']
    total_func_named = adv2['total'] - adv2['properly_named']
    total_uncommented = adv2['total'] - adv2['commented']

    # Handle output modes
    if args.summary:
        lib_status = " (excluding libultra)" if args.nolib else ""
        print(f"Decomp progress [{selected_version}]{lib_status}: {adventure_one_pct:5.2f}%")
        print(f"Documentation progress: {adventure_two_pct:5.2f}%")
        return

    if args.treemap:
        from score_treemap import ScoreTreemap
        treemap = ScoreTreemap(map_file)
        output_path = args.treemap if args.treemap != "" else "treemap.html"
        treemap.generateTreemap(score_files, output_path, selected_version,
                                code_size_for_adv1, args.nolib)
        return

    if show_top_files > 0:
        from score_top import ScoreTop
        top = ScoreTop(map_file)
        top.display_top_files(score_files, show_top_files, args.nolib)
        return

    # Display the main scoreboard
    display = ScoreDisplay()
    print(display.getDisplay(
        adventure_one_pct,
        adventure_one_pct_nonmatch,
        adventure_two_pct,
        adventure_select,
        selected_version,
        adv1['decompiled'],
        adv1['handwritten_asms'],
        adv1['global_asms'],
        adv1['non_matching'],
        adv1['non_equivalent'],
        adv2['documented'],
        total_undocumented,
        total_func_named,
        total_uncommented
    ))

if __name__ == "__main__":
    main()
