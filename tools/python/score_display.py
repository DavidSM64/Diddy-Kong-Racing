import json
import argparse

def readScoreDisplayJson(filename='./tools/python/score_progress.json'):
    with open(filename, 'r') as inFile:
        return json.loads(inFile.read())
        
TOTAL_NUMBER_OF_BALLOONS = 47
TOTAL_NUMBER_OF_KEYS = 4
TOTAL_NUMBER_OF_TT_AMULETS = 4
TOTAL_NUMBER_OF_WIZPIG_AMULETS = 4
TOTAL_NUMBER_OF_TROPHIES = 5

DEFAULT_MAX_LENGTH = 42

class ScoreDisplay:
    def __init__(self):
        self.progressNodes = readScoreDisplayJson()
        
    def getStatus(self, percentage):
        if percentage >= 100.0:
            return {
                "Balloon": TOTAL_NUMBER_OF_BALLOONS,
                "Key": TOTAL_NUMBER_OF_KEYS,
                "TTAmulet": TOTAL_NUMBER_OF_TT_AMULETS,
                "WizpigAmulet": TOTAL_NUMBER_OF_WIZPIG_AMULETS,
                "Trophy": TOTAL_NUMBER_OF_TROPHIES,
                "Msg": "COMPLETED!"
            }
        out = {
            "Balloon": 0,
            "Key": 0,
            "TTAmulet": 0,
            "WizpigAmulet": 0,
            "Trophy": 0,
            "Msg": 'Not Started'
        }
        if percentage <= 0.0:
            return out
        numberOfCompletedNodes = int((percentage / 100.0) * len(self.progressNodes))
        currentNodeProgress = ((percentage / 100.0) * len(self.progressNodes)) - numberOfCompletedNodes
        for i in range(0, numberOfCompletedNodes):
            rewards = self.progressNodes[i]["rewards"]
            for reward in rewards:
                out[reward] += rewards[reward]
        out['Msg'] = self.progressNodes[numberOfCompletedNodes]['msg']
        nodeType = self.progressNodes[numberOfCompletedNodes]['type']
        #if nodeType != 'Task':
        #    out['Msg'] += '\n'
        if nodeType == 'Race':
            out['Msg'] += ' (Lap ' + str(int(currentNodeProgress*3)+1) + '/3)'
        elif nodeType == 'Collecting':
            collectingName = self.progressNodes[numberOfCompletedNodes]['collecting']['name']
            collectingMax = self.progressNodes[numberOfCompletedNodes]['collecting']['max']
            out['Msg'] += ' (' + str(int(currentNodeProgress * collectingMax)) + '/' + str(collectingMax) + ' ' + collectingName + 's)'
        elif nodeType == 'SilverCoinsRace':
            out['Msg'] += ' (' + str(int(currentNodeProgress*9)) + '/8 silver coins)'
        elif nodeType == 'TrophyRace':
            if currentNodeProgress < 0.25:
                out['Msg'] += ' (Round One)'
            elif currentNodeProgress < 0.50:
                out['Msg'] += ' (Round Two)'
            elif currentNodeProgress < 0.75:
                out['Msg'] += ' (Round Three)'
            elif currentNodeProgress < 1.00:
                out['Msg'] += ' (Round Four)'
        elif nodeType == 'Battle':
            if currentNodeProgress < 0.34:
                out['Msg'] += ' (3 opponents remain)'
            elif currentNodeProgress < 0.67:
                out['Msg'] += ' (2 opponents remain)'
            elif currentNodeProgress < 1.00:
                out['Msg'] += ' (1 opponent remains)'
        return out
        
    def makeLine(self, char, length, title=None):
        if title == None:
            return ' ' + (char * length) + ' \n'
        else:
            lineSideLength = (length - len(title) - 2) // 2
            leftLength = lineSideLength
            rightLength = lineSideLength
            if (leftLength + rightLength + len(title) + 2) < length:
                rightLength += 1
            if leftLength + rightLength <= 0:
                if leftLength + rightLength == 0:
                    return '  ' + title + ' \n'
                else:
                    return ' ' + title + ' \n'
            else:
                return ' ' + (char * leftLength) + ' ' + title + ' ' + (char * rightLength) + ' \n'
        
    def getGameStatusDisplay(self, status, dashLen):
        out = ''
        out += self.makeLine('-', dashLen, 'Game Status')
        firstStatusLine = ''
        secondStatusLine = ''
        firstStatusLine += 'Balloons: {:}/{:},'.format(status['Balloon'], TOTAL_NUMBER_OF_BALLOONS)
        firstStatusLine += ' Keys: {:}/{:},'.format(status['Key'], TOTAL_NUMBER_OF_KEYS)
        firstStatusLine += ' Trophies: {:}/{:}'.format(status['Trophy'], TOTAL_NUMBER_OF_TROPHIES)
        secondStatusLine += 'T.T. Amulets: {:}/{:},'.format(status['TTAmulet'], TOTAL_NUMBER_OF_TT_AMULETS)
        secondStatusLine += ' Wizpig Amulets: {:}/{:}'.format(status['WizpigAmulet'], TOTAL_NUMBER_OF_WIZPIG_AMULETS)
        out += self.makeLine(' ', dashLen, firstStatusLine)
        out += self.makeLine(' ', dashLen, secondStatusLine)
        out += self.makeLine('-', dashLen)
        out += self.makeLine(' ', dashLen, status['Msg'])
        return [out, dashLen]
    
    def getDisplay(self, advOnePer, advTwoPer, showFlags=3, totalDecompFunctions=0, totalGlobalAsm=0, totalNonMatching=0, totalDocumented=0, totalUndocumented=0):
        advOneStatus = self.getStatus(advOnePer)
        advTwoStatus = self.getStatus(advTwoPer)
        if showFlags == 3:
            dashLen = max(len(advOneStatus['Msg']), len(advTwoStatus['Msg']), DEFAULT_MAX_LENGTH)
        elif showFlags == 1:
            dashLen = max(len(advOneStatus['Msg']), DEFAULT_MAX_LENGTH)
        elif showFlags == 2:
            dashLen = max(len(advTwoStatus['Msg']), DEFAULT_MAX_LENGTH)
        else:
            dashLen = DEFAULT_MAX_LENGTH
        advOneGameStatusDisplay = self.getGameStatusDisplay(advOneStatus, dashLen)
        advTwoGameStatusDisplay = self.getGameStatusDisplay(advTwoStatus, dashLen)
        out = ''
        if showFlags & 1:
            out += self.makeLine('=', dashLen)
            out += self.makeLine(' ', dashLen, 'ADVENTURE ONE (ASM -> C Decompilation)')
            if advOnePer >= 100.0:
                out += self.makeLine('-', dashLen, '{:5.1f}% Complete'.format(advOnePer))
            else:
                out += self.makeLine('-', dashLen, '{:5.2f}% Complete'.format(advOnePer))
            out += self.makeLine(' ', dashLen, '# Decompiled functions: ' + str(totalDecompFunctions))
            out += self.makeLine(' ', dashLen, '# GLOBAL_ASM remaining: ' + str(totalGlobalAsm))
            out += self.makeLine(' ', dashLen, '# NON_MATCHING functions: ' + str(totalNonMatching))
            out += advOneGameStatusDisplay[0]
        if showFlags & 2:
            out += self.makeLine('=', dashLen)
            out += self.makeLine(' ', dashLen, '  ADVENTURE TWO (Cleanup & Documentation)')
            if advTwoPer >= 100.0:
                out += self.makeLine('-', dashLen, '{:5.1f}% Complete'.format(advTwoPer))
            else:
                out += self.makeLine('-', dashLen, '{:5.2f}% Complete'.format(advTwoPer))
            out += self.makeLine(' ', dashLen, '# Documented functions: ' + str(totalDocumented))
            out += self.makeLine(' ', dashLen, '# Undocumented remaining: ' + str(totalUndocumented))
            out += advTwoGameStatusDisplay[0]
        out += self.makeLine('=', dashLen)[:-1]
        return out
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("adventureOnePercentage", help="Value within [0.0, 100.0] that describes how complete the decomp is.")
    parser.add_argument("adventureTwoPercentage", help="Value within [0.0, 100.0] that describes how complete the documentation is.")
    parser.add_argument("-a", "--adventure", help="(Optional) Only shows adventure 1 or 2 based on passed in value.", choices=['1', '2'])
    args = parser.parse_args()
    adventureSelect = 3 # Show both adventures by default
    if args.adventure != None:
        adventureSelect = int(args.adventure)
    scoreDisplay = ScoreDisplay()
    print(scoreDisplay.getDisplay(float(args.adventureOnePercentage), float(args.adventureTwoPercentage), adventureSelect))
    