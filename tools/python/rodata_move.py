import os
import re
import argparse
from file_util import FileUtil

C_RODATA_REGEX = r"/[*]+[ ]*[.]rodata[ ]*[*]+/(?:.*\n)+/[*]{33}/"
C_STRING_REGEX = r"const[ ]+char[ ]+(D_[0-9A-Fa-f]{8})[[][^]]*[]][ ]*=[ ]*(\"[^\"]*\")[ ]*;"
C_FLOAT_REGEX = r".*(D_[0-9A-Fa-f]{8})[ ]*=[ ]*{[ ]*([-]?[0-9]+.[0-9]+)[f]?[ ]*}.*"
C_JMPTABLE_REGEX = r"(?:(?:D_)|0x)[0-9A-Fa-f]{8}"

# Debugging variables
NO_OUTPUT = False               # If True, then no files will be changed.
ONLY_THE_FIRST_ASM_FILE = False # If True, then only one asm file will be changed.

def getMatches(string, regex):
    out = []
    matches = re.finditer(regex, string, re.MULTILINE)
    for matchNum, match in enumerate(matches, start=1):
        start = match.start()
        end = match.end()
        out.append((string[start:end], match.groups(), (start, end)))
    return out
    
def getLineType(line):
    if line.lower().startswith('const char '):
        return 1 # Literal string
    elif line.lower().startswith('const floatliteral '):
        return 2 # Literal float
    elif line.lower().startswith('const doubleliteral '):
        return 3 # Literal double
    elif line.lower().startswith('};'):
        return 4 # Jump Table bottom
    elif line.lower().startswith('const u32 '):
        return 5 # Jump Table top
    else:
        return 0
        
def getAsmFileReferenceForLabel(filename, label):
    searchLabel = 'asm/non_matchings/'+filename
    possibleFiles = []
    search = os.popen('fgrep -r "' + label + '"').read().split('\n')
    for line in search:
        if searchLabel in line:
            asmfilePath = line.split(':')[0]
            if asmfilePath not in possibleFiles:
                possibleFiles.append(asmfilePath)
    if len(possibleFiles) > 1:
        raise Exception('Cannot determine asm file for label: ' + label)
    elif len(possibleFiles) == 0:
        raise Exception(label + ' has no asm files associated with it!')
    return possibleFiles[0]
    
def adjustAsmFile(asmFilepath, refs):
    with open(asmFilepath, 'r') as inFile:
        asmFile = inFile.read()
        if '.late_rodata' in asmFile:
            raise Exception('Cannot add to file "' + asmFilepath + '" since it already has .late_rodata in it!')
        asmLines = asmFile.split('\n')
        replaces = []
        
        rodata = ''
        lateRodata = ''
        
        for index, ref in enumerate(refs):
            if ref[0] == 'asciz':
                rodata += 'glabel ' + ref[1] + '\n'
                rodata += '.' + ref[0] + ' ' + ref[2] + '\n'
            elif ref[0] == 'double' or ref[0] == 'float':
                lateRodata += '.' + ref[0] + ' ' + ref[2] + '\n'
            elif ref[0] == 'table':
                replaces.append((ref[1], 'jpt' + ref[1][1:]))
                tblWords = '.word L' + ref[2][0]
                for word in ref[2][1:]:
                    tblWords += ', L' + word
                doneWords = []
                for word in ref[2]:
                    if word in doneWords:
                        continue
                    for i in range(0, len(asmLines)):
                        line = asmLines[i]
                        if line.startswith('/* '):
                            lineParts = line.split(' ')
                            if lineParts[2] == word:
                                asmLines.insert(i, 'glabel L' + word)
                                break
                    doneWords.append(word)
                lateRodata += tblWords + '\n'
            if index < len(refs) - 1 and ref[0] != 'double' and refs[index + 1][0] == 'double':
                addPadding = False
                if ref[0] == 'float':
                    addPadding = ref[1].endswith('0') or ref[1].endswith('8')
                elif ref[0] == 'table':
                    tableSizeAlignment = len(ref[2]) % 4
                    if ref[1].endswith('0') or ref[1].endswith('8'):
                        addPadding = tableSizeAlignment == 1 or tableSizeAlignment == 3
                    else:
                        addPadding = tableSizeAlignment == 0 or tableSizeAlignment == 2
                if addPadding:
                    lateRodata += '.word 0 # Padding\n' # Insert padding before the next double.
        outData = ''
        if len(rodata) > 0:
            outData += '.rdata\n' + rodata + '\n'
        if len(lateRodata) > 0:
            outData += '.late_rodata\n' + lateRodata + '\n'
        asmLines.insert(0, outData + '.text');
        asmOut = '\n'.join(asmLines)
        for rep in replaces:
            asmOut = asmOut.replace(rep[0], rep[1])
        # print(asmOut)
        if not NO_OUTPUT:
            with open(asmFilepath, 'w') as outFile:
                outFile.write(asmOut)
    #print(asmFilepath)
    #print(refs)

def convertFile(cFilepath):
    filename = cFilepath[cFilepath.rindex('/') + 1:-2]
    print(filename)
    with open(cFilepath, 'r') as inFile:
        cFile = inFile.read()
        match = getMatches(cFile, C_RODATA_REGEX)
        if len(match) == 0:
            print('No .rodata in file "' + cFilepath + '"')
            return
        rodataPart = match[0][0]
        rodataSection = match[0][2]
        rodataLines = rodataPart.split('\n')
        tableBottom = -1
        hasProcessed = False
        stoppedPremature = False
        curLine = len(rodataLines) - 1
        bottomLine = curLine
        asmData = []
        for line in reversed(rodataLines):
            lineType = getLineType(line)
            if lineType == 0:
                pass
            elif lineType == 1: # Literal string
                try:
                    strMatch = getMatches(line, C_STRING_REGEX)[0]
                    strLabel = strMatch[1][0]
                    strValue = strMatch[1][1]
                    # Check if the string has a reference somewhere
                    getAsmFileReferenceForLabel(filename, strLabel) 
                    hasProcessed = True
                    bottomLine = curLine
                    asmData.insert(0, ('asciz', strLabel, strValue, bottomLine))
                except:
                    print('Currently cannot process literal string: ')
                    print(line)
                    stoppedPremature = True
                    break
            elif lineType == 2: # Literal float
                floatMatch = getMatches(line, C_FLOAT_REGEX)[0]
                floatLabel = floatMatch[1][0]
                floatValue = floatMatch[1][1]
                if floatValue == '0.0':
                    print('File boundary hit!')
                    stoppedPremature = True
                    break
                hasProcessed = True
                bottomLine = curLine
                asmData.insert(0, ('float', floatLabel, floatValue, bottomLine))
            elif lineType == 3: # Literal double
                floatMatch = getMatches(line, C_FLOAT_REGEX)[0]
                floatLabel = floatMatch[1][0]
                floatValue = floatMatch[1][1]
                if floatValue == '0.0':
                    print('File boundary hit!')
                    stoppedPremature = True
                    break
                hasProcessed = True
                bottomLine = curLine
                asmData.insert(0, ('double', floatLabel, floatValue, bottomLine))
            elif lineType == 4: # Jump table bottom
                tableBottom = curLine
            elif lineType == 5: # Jump table top
                tblMatch = getMatches('\n'.join(rodataLines[curLine:tableBottom+1]), C_JMPTABLE_REGEX)
                tblLabel = tblMatch[0][0]
                tblValues = []
                for val in range(1, len(tblMatch)):
                    tblValues.append(tblMatch[val][0][2:])
                hasProcessed = True
                bottomLine = curLine
                asmData.insert(0, ('table', tblLabel, tblValues, bottomLine))
                tableBottom = -1
            else:
                print(line)
            curLine -= 1
        asmRefs = {}
        asmBottomLine = 999999
        for i in reversed(range(0, len(asmData))):
            data = asmData[i]
            try:
                ref = getAsmFileReferenceForLabel(filename, data[1])
                if ref not in asmRefs:
                    asmRefs[ref] = []
                asmRefs[ref].append(data)
                asmBottomLine = min(asmBottomLine, data[3])
            except Exception as e:
                # raise e
                print(e)
                if asmBottomLine != 999999:
                    print(bottomLine, asmBottomLine)
                    bottomLine = asmBottomLine
                stoppedPremature = True
                break
        for asmFilepath in asmRefs:
            print('Processing: ' + asmFilepath)
            asmRefs[asmFilepath].reverse()
            asmBottomLine = 999999
            adjustAsmFile(asmFilepath, asmRefs[asmFilepath])
            for ref in asmRefs[asmFilepath]:
                asmBottomLine = min(asmBottomLine, ref[3])
            if ONLY_THE_FIRST_ASM_FILE:
                print(bottomLine, asmBottomLine)
                bottomLine = asmBottomLine
                stoppedPremature = True
                break
            # print(asmRefs)
        if hasProcessed and not NO_OUTPUT:
            newRodata = '\n'.join(rodataLines[0:bottomLine] + rodataLines[-2:])
            newFileText = cFile[:rodataSection[0]] + (newRodata if stoppedPremature else '') + cFile[rodataSection[1]:]
            with open(cFilepath, 'w') as outFile:
                outFile.write(newFileText)
                print('Changes were made to ' + cFilepath)
        else:
            print('No changes were made to ' + cFilepath)


parser = argparse.ArgumentParser(description="")
parser.add_argument("file", help=".c file that contains rodata to move.")
parser.add_argument("-s", "--single", help="Only do one ASM function in the file", action='store_true')
args = parser.parse_args()

if args.single is not None and args.single:
    ONLY_THE_FIRST_ASM_FILE = True

if args.file.endswith('.c'):
    convertFile(args.file)
else:
    raise Exception('The file must be a .c file.')
      
# files = FileUtil.get_filenames_from_directory('src', ('.c',))
# 