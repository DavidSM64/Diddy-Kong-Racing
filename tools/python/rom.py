import hashlib

from file_util import FileUtil

class ROM:
    def __init__(self, filename):
        with open(filename, 'rb') as romFile:
            self.fixedRomEndianess = False
            self.bytearray = romFile.read()
            self.bytes = list(self.bytearray)
            self.size = len(self.bytes)
            self._test_endianness()
            self.md5 = hashlib.md5(self.bytearray).hexdigest()
        if self.fixedRomEndianess: 
            FileUtil.delete_file(filename)
            # Save the ROM as big-endian
            with open(filename[:-4] + '.z64', 'wb') as romFile:
                romFile.write(self.bytearray)
            
    def get_bytes_from_range(self, start, end):
        return self.bytes[start:end]
            
    # Check and correct mixed/little endian ROMs
    def _test_endianness(self):
        if self.bytes[0] == 0x80 and self.bytes[1] == 0x37:
            self.endianness = 'big'
        elif self.bytes[0] == 0x37 and self.bytes[1] == 0x80:
            self.endianness = 'mixed'
        elif self.bytes[0] == 0x40 and self.bytes[1] == 0x12:
            self.endianness = 'little'
        
        # Convert mixed/little endian to big endian.
        # This is kinda slow, and should be avoided if possible.
        if self.endianness == 'mixed':
            print('Converting mixed-endian (byte-swapped) to big-endian...')
            for i in range(0, len(self.bytes), 2):
                temp = self.bytes[i]
                self.bytes[i] = self.bytes[i + 1]
                self.bytes[i + 1] = temp
            self.bytearray = bytearray(self.bytes)
            self.endianness = 'big'
            self.fixedRomEndianess = True
            pass
        elif self.endianness == 'little':
            print('Converting little-endian to big-endian...')
            temp = [0, 0, 0, 0]
            for i in range(0, len(self.bytes), 4):
                temp[0] = self.bytes[i]
                temp[1] = self.bytes[i + 1]
                temp[2] = self.bytes[i + 2]
                temp[3] = self.bytes[i + 3]
                self.bytes[i]     = temp[3]
                self.bytes[i + 1] = temp[2]
                self.bytes[i + 2] = temp[1]
                self.bytes[i + 3] = temp[0]
            self.bytearray = bytearray(self.bytes)
            self.endianness = 'big'
            self.fixedRomEndianess = True
