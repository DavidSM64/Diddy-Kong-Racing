import re

class ConfigRange:
    def __init__(self, size, type, properties):
        self.size = size
        self.type = type.lower()
        self.properties = properties
        
    def get_range_string(self, start):
        return "{:06x}".format(start) + '-' + "{:06x}".format(start + self.size)
    
    def __repr__(self):
        return "{:06x}".format(self.size) + ', ' + self.type + ', ' + str(self.properties)

class Config:
    def __init__(self, directory, filename):
        with open(directory + '/' + filename, 'r') as configFile:
            self.text = configFile.read()
            self.directory = directory
            self.ranges = []
            self.name = ''
            self.md5 = ''
            self.subfolder = ''
            self.notSupported = False
            if not self._parse(self.text):
                raise Exception('Error: ' + self.parseError)
            #print(self.name)
            #print(self.md5)
            #print(str(self.ranges))
        
    def _parse(self, text):
        regex_property = r'^\s*([0-9a-zA-Z\-]+)\s*:\s*["]([^"]*)["]\s*$'
        regex_range = r'^\s*\[\s*(0x[0-9a-fA-F]+)\s*\]\s*:\s*(.*)$'
        for line in text.split('\n'):
            line = line.strip() # remove leading and trailing whitespace
            line = line.partition('#')[0] # remove comments
            if len(line) > 0:
                matches = self._parse_test_re(regex_property, line)
                if matches is not None:
                    self._parse_property(matches)
                    continue
                matches = self._parse_test_re(regex_range, line)
                if matches is not None:
                    #print(matches)
                    self._parse_range(matches)
                    continue
                self.parseError = 'Invalid line "' + line + '"'
                return False
        return True
    
    def _parse_property(self, matches):
        propertyName = matches[0]
        propertyValue = matches[1]
        if propertyName == 'config-name':
            self.name = propertyValue
        elif propertyName == 'subfolder':
            self.subfolder = propertyValue
        elif propertyName == 'checksum-md5':
            self.md5 = propertyValue
        elif propertyName == 'not-supported':
            self.notSupported = (propertyValue.lower() == 'true')
        elif propertyName == 'include':
            with open(self.directory + '/' + propertyValue, 'r') as includeFile:
                self._parse(includeFile.read())
        else:
            print('Unknown property "' + propertyName + '" with value "' + propertyValue + '"')
            
    def _parse_range(self, matches):
        rangeSize = int(matches[0], 0)
        rangeProperties = matches[1].split(',')
        
        for i in range(0, len(rangeProperties)):
            rangeProperties[i] = rangeProperties[i].strip() # remove leading and trailing whitespace
            rangeProperties[i] = self._parse_range_property(rangeProperties[i])
            
        self.ranges.append(ConfigRange(rangeSize, rangeProperties[0], rangeProperties[1:]))
            
    def _parse_range_property(self, property):
        if property.startswith('"'): # string
            return property[1:-1]
        else:
            return int(property, 0)
              
    def _parse_test_re(self, regex, line):
        matches = re.match(regex, line)
        if matches is not None:
            return matches.groups()
        return None
