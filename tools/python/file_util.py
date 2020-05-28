from os import listdir, remove
from os.path import isfile, join

class FileUtil:
    @staticmethod
    def get_filenames_from_directory(directory, extensions=None):
        if extensions is None:
            return [f for f in listdir(directory) if isfile(join(directory, f))]
        else:
            return [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(extensions)]
    
    @staticmethod
    def get_text_from_file(filename):
        with open(filename, 'r') as inFile:
            return inFile.read()
            
    @staticmethod
    def write_text_to_file(filename, text):
        with open(filename, 'w') as outFile:
            outFile.write(text)
            
    @staticmethod
    def delete_file(filename):
        remove(filename)
    
