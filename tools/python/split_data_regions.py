import os
import re
from bisect import bisect
from collections import OrderedDict

from file_util import FileUtil

DATA_FILE_PATH = 'data/dkr.data.s'
GLABEL_REGEX = r'D_[0-9A-F]{8}'
GLABEL_DEF_REGEX = r'glabel (%s)' % GLABEL_REGEX
RODATA_START = 'D_800E49DC'  # i.e. the end of .data
BSS_START = 'D_800E98D0'  # i.e. the end of .rodata
# List of labels that are not used in the file they are defined in.
# This throws off the splitter algorithm, so the troublesome ones
# must be individually blacklisted for now.
IGNORE_GLABELS = ['D_800E0001', 'D_800E63E0', 'D_800E94D0']

def _rom_offset(vaddr):
    """
    Returns the ROM offset of the corresponding virtual address given.
    Parameters:
        vaddr: can be a string or integer. If string, it is assumed to be in
            hex.
    """
    if type(vaddr) == str:
        vaddr = int(vaddr, 16)
    return vaddr - 0x7FFFF400

def _get_glabels():
    """
    Returns all the glabel definitions in the data file, split into .data,
    .rodata, and .bss.
    """
    data_file = FileUtil.get_text_from_file(DATA_FILE_PATH)
    glabels = re.findall(GLABEL_DEF_REGEX, data_file)
    glabels = [glabel for glabel in glabels if glabel not in IGNORE_GLABELS]
    rodata_idx = glabels.index(RODATA_START)
    bss_idx = glabels.index(BSS_START)
    return glabels[:rodata_idx], glabels[rodata_idx:bss_idx], glabels[bss_idx:]

def _get_file_offset(file, contents):
    """
    Returns the ROM offset of the given file. Throws exception upon error.
    Parameters:
        file: filename. Must be a .c or .s file.
        contents: the contents of file.
    """
    if file.endswith('.c'):
        return _rom_offset(re.search('/\* RAM_POS: 0x([0-9A-F]{8}) \*/', contents)[1])
    elif file.endswith('.s'):
        return int(re.search('/\* ([0-9A-F]{6}) [0-9A-F]{8} [0-9A-F]{8} \*/', contents)[1], 16)
    else:
        raise exception('cannot find offset for file ' + file)

def _log_glabel_usage(glabels):
    """
    Returns:
        usage: A sorted map from glabel names to a sorted list of all the ROM
            addresses it is accessed from.
        c_file_offsets: A list of (filename, ROM offset) tuples from all the c
            files used.
    Parameters:
        glabels: output from _get_glabels.
    """
    usage = OrderedDict([(glabel, set()) for glabel in glabels])
    files = FileUtil.get_filenames_from_directory_recursive('.', ('.c', '.s'))
    c_file_offsets = []
    for file in files:
        contents = FileUtil.get_text_from_file(file)
        try:
            offset = _get_file_offset(file, contents)
            if file.endswith('.c'):
                c_file_offsets.append((file, offset))
            matches = re.findall(GLABEL_REGEX, contents)
            for glabel in matches:
                if glabel in usage:
                    usage[glabel].add(offset)
        except:
            pass
    for glabel in usage:
        usage[glabel] = sorted(list(usage[glabel]))
    c_file_offsets.sort(key=lambda f: f[1])
    return usage, c_file_offsets

def _filter_glabel_usage(glabel_usage):
    """
    Returns a sorted (by ROM offset) list of (glabel name, ROM offset), where
        the ROM offset is the estimated location the glabel is defined at. Note
        that this is an estimate; the algorithm used is greedy and may
        overpredict.
    Parameters:
        glabel_usage: output from _log_glabel_usage.
    """
    filtered_usage = []
    cur_offset = min(glabel_usage[next(iter(glabel_usage))])
    for glabel in glabel_usage:
        usage = glabel_usage[glabel]
        valid_offsets = usage[bisect(usage, cur_offset):]
        if len(valid_offsets) > 0:
            cur_offset = valid_offsets[0]
        filtered_usage.append((glabel, cur_offset))
    return filtered_usage

def _split_glabel_files(glabel_usage, c_file_offsets):
    """
    Returns a sorted (by file offset) list of (file name, file offset, glabel name)
        for every file, where glabel name is the name of the first glabel that
        lives within the ROM address domain of the corresponding file.
    Parameters:
        glabel_usage: output from _filter_glabel_usage.
        c_file_offsets: output from _log_glabel_usage.
    """
    file_splits = []
    glabel_idx = 0
    for i in range(len(c_file_offsets)):
        file = c_file_offsets[i]
        while glabel_idx < len(glabel_usage) and glabel_usage[glabel_idx][1] < file[1]:
            glabel_idx += 1
        if glabel_idx < len(glabel_usage) and i < len(c_file_offsets) - 1:
            glabel = glabel_usage[glabel_idx]
            glabel_name = glabel[0] if glabel[1] < c_file_offsets[i + 1][1] else None
        else:
            glabel_name = None
        file_splits.append((file[0], file[1], glabel_name))
    return file_splits

def main():
    FileUtil.set_working_dir_to_project_base()
    data_glabels, rodata_glabels, bss_glabels = _get_glabels()
    for section in [('.data', data_glabels), ('.rodata', rodata_glabels), ('.bss', bss_glabels)]:
        glabels = section[1]
        usage, c_file_offsets = _log_glabel_usage(glabels)
        filtered_usage = _filter_glabel_usage(usage)
        file_splits = _split_glabel_files(filtered_usage, c_file_offsets)
        print('File splits for %s:' % section[0])
        for split in file_splits:
            print('%s (%06X): %s' % split)
        print()

if __name__ == '__main__':
    main()
