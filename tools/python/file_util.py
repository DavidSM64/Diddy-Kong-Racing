from os import chdir, listdir, remove
from os.path import dirname, isfile, isdir, join, realpath

class FileUtil:
    @staticmethod
    def getListOfFiles(dirName, extensions=None):
        # create a list of file and sub directories 
        # names in the given directory 
        listOfFile = listdir(dirName)
        allFiles = list()
        # Iterate over all the entries
        for entry in listOfFile:
            # Create full path
            fullPath = join(dirName, entry)
            # If entry is a directory then get the list of files in this directory 
            if isdir(fullPath):
                allFiles = allFiles + FileUtil.getListOfFiles(fullPath)
            else:
                if extensions is None:
                    allFiles.append(fullPath)
                else:
                    if fullPath.endswith(extensions):
                        allFiles.append(fullPath)
                    
        return allFiles

    @staticmethod
    def get_filenames_from_directory(directory, extensions=None):
        if extensions is None:
            return [f for f in listdir(directory) if isfile(join(directory, f))]
        else:
            return [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(extensions)]

    @staticmethod
    def get_filenames_from_directory_recursive(directory, extensions=None, subDirectory=''):
        filenames = []
        for f in listdir(directory):
            if isfile(join(directory, f)) and (extensions is None or f.endswith(extensions)):
                filenames.append(((subDirectory + '/') if subDirectory != '' else '') + f)
            elif isdir(join(directory, f)):
                if subDirectory == '':
                    filenames += FileUtil.get_filenames_from_directory_recursive(join(directory, f), extensions, f)
                else:
                    filenames += FileUtil.get_filenames_from_directory_recursive(join(directory, f), extensions, subDirectory + '/' + f)
        return filenames
    
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
    
    @staticmethod
    def set_working_dir_to_project_base():
        chdir(join(dirname(realpath(__file__)), '../..'))
