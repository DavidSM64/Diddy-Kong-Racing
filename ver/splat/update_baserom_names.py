# The purpose of this script is to update the `target_path` field of `options` in the YAML config file,
#     so that users can use any filename for their roms instead of having to name them `baserom.us.v1.z64` etc.
#     The ROM file is detected from it's SHA1 hash.

import os
import argparse
import yaml
import hashlib

CURRENT_DIR = os.path.dirname(__file__)

def get_sha1_hash(directoryPath):
    sha1 = hashlib.sha1()
    with open(directoryPath, 'rb') as file:
        while chunk := file.read(8192):
            sha1.update(chunk)
    return sha1.hexdigest()

def get_all_files_from_directory(directoryPath):
    return [os.path.join(directoryPath, f) for f in os.listdir(directoryPath) if os.path.isfile(os.path.join(directoryPath, f))]

def get_files_with_extension(directoryPath, extension):
    yaml_files = []
    for root, dirs, files in os.walk(directoryPath):
        for file in files:
            if file.endswith(extension):
                yaml_files.append(os.path.join(root, file))
    return yaml_files

def get_yaml_files(directoryPath):
    return get_files_with_extension(directoryPath, '.yaml')
    
def update_yaml_file(yamlFilePath):
    yamlData = yaml.safe_load(open(yamlFilePath, 'r'))
    yamlOptions = yamlData['options']
    yamlSha1 = yamlData['sha1']
    basepath = os.path.join(CURRENT_DIR, yamlOptions['base_path']) # Not going to override base_path, so this should be fine.
    target_path_dir = os.path.dirname(yamlOptions['target_path'])
    target_path_basename = os.path.basename(yamlOptions['target_path'])
    target_folder = os.path.join(basepath, target_path_dir)
    target_path_full = os.path.join(target_folder, target_path_basename)
    target_folder_files = get_all_files_from_directory(target_folder)
    for file in target_folder_files:
        if get_sha1_hash(file) == yamlSha1:
            if os.path.basename(file) != target_path_basename:
                print(f'Baserom file "{os.path.basename(file)}" renamed to "{target_path_basename}"')
                os.rename(file, target_path_full) 
                return

def main():
    parser = argparse.ArgumentParser(description='Updates the target_path option for the yaml files.') 
    parser.add_argument('yamlFile', nargs='?', default='all', help='Optional file argument (default: "all")')
    args = parser.parse_args()
    
    if args.yamlFile == "all":
        yamlFilePaths = get_yaml_files(CURRENT_DIR)
    else:
        yamlFilePaths = [ os.path.join(CURRENT_DIR, args.yamlFile) ]
    
    for filePath in yamlFilePaths:
        update_yaml_file(filePath)

if __name__ == '__main__':
    main()
