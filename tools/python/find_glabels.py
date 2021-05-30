import re

from file_util import FileUtil

# Maximum number of lines between a glabel's upper/lower usage to look for.
MAX_LINE_DIFF = 10

LINE_START_REGEX = r'\n(/\* ([0-9A-F]{6}) [0-9A-F]{8} [0-9A-F]{8} \*/\s+|\.L80[0-9A-F]{6}:)?'
REG_REGEX = r'(\$(at|v[0-1]|a[0-3]|t[0-9]|s[0-7]|f[0-9]{1,2}|k[01]|gp|sp|fp|ra|zero))'
GLABEL_UPPER_REGEX = '(' + LINE_START_REGEX + r'lui\s+' + REG_REGEX + r',\s+(0x80[0-9a-f]{2}))'
#GLABEL_UPPER_REGEX = '(' + LINE_START_REGEX + r'li\s+' + REG_REGEX + r',\s+(0x80[0-9A-F]{2})0000\s+#[^\n]*)'
GLABEL_LOWER_LS_REGEX = r'[sl][bhwd](u|c1)?\s+' + REG_REGEX + r',\s+(-?0x[0-9a-f]{3,4})\(\4\)'
GLABEL_LOWER_ADDU_REGEX = r'addiu\s+' + REG_REGEX + r',\s+\4,\s+(-?0x[0-9a-f]{3,4})'
GLABEL_LOWER_REGEX = LINE_START_REGEX + '(' + GLABEL_LOWER_LS_REGEX + '|' + GLABEL_LOWER_ADDU_REGEX + ')'
GLABEL_REGEX_STR = GLABEL_UPPER_REGEX + '(' + LINE_START_REGEX + '[^\n]*){0,' + str(MAX_LINE_DIFF) + '}' + GLABEL_LOWER_REGEX
GLABEL_REGEX = re.compile(GLABEL_REGEX_STR)

UPPER_INSTR_REGEX_TMPL = r'(/\* %s[^\n#]*lui\s+)([^\n]*)'
LOWER_INSTR_LS_REGEX_TMPL = r'(/\* %s[^\n#]*[ls][bhwd](u|c1)?\s+' + REG_REGEX + r',\s+)-?0x[0-9a-f]{3,4}([^\n]*)'
LOWER_INSTR_ADDU_REGEX_TMPL = r'(/\* %s[^\n#]*addiu\s+' + REG_REGEX + r',\s+' + REG_REGEX + r',\s+)-?0x[0-9a-f]{3,4}'
LOWER_INSTR_ADDU_SAME_REGEX_TMPL = r'(/\* %s[^\n#]*)(addiu\s+' + REG_REGEX + r',\s+\3,\s+-?0x[0-9a-f]{3,4})'

IGNORE_GLABELS = ['D_800E389E', 'D_801264A1', 'D_800E1B84']

def _find_glabels(asm):
    glabels = []
    for file in FileUtil.get_filenames_from_directory_recursive('.', '.s'):
        contents = FileUtil.get_text_from_file(file)
        matches = GLABEL_REGEX.findall(contents)
        for match in matches:
            reg = match[3]
            offsets = (match[2], match[10])  # ROM offsets of the lui and [sl][bhw]
            glabel_upper = int(match[5], 16)  # upper immediate of glabel
            lower_group = 15 if match[15] else 18  # lower immediate of the glabel
            is_addu = lower_group == 18
            glabel_lower = int(match[lower_group], 16)
            glabel_lower &= 0xFFFF
            if glabel_lower & 0x8000:
                glabel_upper -= 1
            glabel = 'D_%08X' % (glabel_upper << 16 | glabel_lower)
            if glabel not in IGNORE_GLABELS:
                glabels.append((glabel, *offsets))
                # replace upper instruction
                contents = re.sub(UPPER_INSTR_REGEX_TMPL % offsets[0],
                                r'\1%s, %%hi(%s) # \2' % (reg, glabel),
                                contents)
                # replace lower instruction
                contents = re.sub(LOWER_INSTR_LS_REGEX_TMPL % offsets[1],
                                r'\1%%lo(%s)\5' % glabel,
                                contents)
                contents = re.sub(LOWER_INSTR_ADDU_SAME_REGEX_TMPL % offsets[1],
                                r'\1addiu \3, %%lo(%s) # \2' % glabel,
                                contents)
                contents = re.sub(LOWER_INSTR_ADDU_REGEX_TMPL % offsets[1],
                                r'\1%%lo(%s)' % glabel,
                                contents)
        if len(matches):
            FileUtil.write_text_to_file(file, contents)
    return glabels

def main():
    FileUtil.set_working_dir_to_project_base()
    contents = FileUtil.get_text_from_file('asm/non_matchings/unknown_005740/func_80005254.s')
    glabels = _find_glabels(contents)
    print('%d undeclared labels found:' % len(glabels))
    for glabel in glabels:
        print(glabel)

if __name__ == '__main__':
    main()
