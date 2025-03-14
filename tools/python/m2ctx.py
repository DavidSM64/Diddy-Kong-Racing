#!/usr/bin/env python3

import os, subprocess, sys, re, time
from datetime import date
from pathlib import Path

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../../"
src_dir = root_dir + "src/"
lib_dir = root_dir + "lib/"

VERSION = "us_1.0"

ignoreFiles = ["include/sys/regdef.h"]

search_folders = ["include/", "src/"]

# Needed for StereoPanMode
includeFiles = ['lib/src/audio/synstartvoiceparam.h']

hack_directives_into_singleline = ['DRAW_TABLE_ENTRY', 'DRAW_TABLE_GROUP']

# From: https://stackoverflow.com/a/18381470
# Removes all single line & multi-line comments from a C file.
def remove_comments(string):
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    # first group captures quoted strings (double or single)
    # second group captures comments (//single-line or /* multi-line */)
    regex = re.compile(pattern, re.MULTILINE|re.DOTALL)
    def _replacer(match):
        # if the 2nd group (capturing comments) is not None,
        # it means we have captured a non-quoted (real) comment string.
        if match.group(2) is not None:
            return "" # so we will return empty to remove the comment
        else: # otherwise, we will return the 1st group
            return match.group(1) # captured quoted-string
    return regex.sub(_replacer, string)

def regex_get_matches(text, regex):
    return re.finditer(regex, text, re.MULTILINE)

# Cleans output to reduce filesize.
cleanupUselessDefinesRegex = r"#if.*\n#(?:else|define).*\n#endif.*\n"
def cleanup(out):
    defs = regex_get_matches(out, cleanupUselessDefinesRegex)
    for remove in defs:
        out = out.replace(remove.group(0), '')
    out = out.replace('\t', ' ') # Replace tabs with spaces.
    out = re.sub(r"\n\n+", "\n", out)
    out = re.sub(r"  +", " ", out)
    return out

# Removes trailing commas from enums, which create warnings on decomp.me
fixEnumsRegex = r"enum.*{((?:[^}]*\n)*.*)}"
def fix_enums(text):
    matches = regex_get_matches(text, fixEnumsRegex)
    try:
        for matchNum, match in enumerate(matches, start=1):
            groupOne = match.group(1)
            if groupOne != None and groupOne.endswith(",\n"):
                newGroup = groupOne[0:-2] + "\n"
                text = text.replace(groupOne, newGroup)
    except TypeError:
        pass
    return text

# Fixes up a string to make it look nice. Also removes some unnecessary stuff.
def cleanup_string(text):
    return ' '.join(text.strip()
        .replace('UNUSED', '')
        .replace('extern', '')
        .replace('__stdcall', '')
        .replace('\t', '    ')
        .replace('\n', ' ')
        .split())

# Returns the arguments for a function in a nice clean way.
def get_cleaned_args(argsString):
    args = cleanup_string(argsString).split(',')
    cleanedArgs = []
    for arg in args:
        arg = cleanup_string(arg)
        if '*' in arg:
            arg = arg[0:arg.rfind('*')+1]
            firstAsterisk = arg.find('*')
            cleanedArgs.append(cleanup_string(arg[0:firstAsterisk] + ' ' + arg[firstAsterisk:]))
        else:
            if ' ' in arg:
                cleanedArgs.append(' '.join(arg.split()[0:-1]))
            else:
                cleanedArgs.append(arg)
    return ', '.join(cleanedArgs)

# Collects functions in a file from a given regex
def collect_func_from_regex(filename, filetext, regex, data):
    defs = regex_get_matches(filetext, regex)
    for match in defs:
        typeAndName = cleanup_string(match.group(1)).split()
        funcType = cleanup_string(' '.join(typeAndName[0:-1]))
        if funcType == 'return' or funcType == "else" or funcType.startswith('INCONSISTENT'):
            continue; # Skip false matches
        funcName = cleanup_string(typeAndName[-1])
        args = get_cleaned_args(match.group(2))
        if funcName not in data:
            data[funcName] = { "type": funcType, "args": args, "filename": cleanup_string(filename) }
        else:
            if data[funcName]["type"] != funcType or data[funcName]["args"] != args:
                print("Function doesn't match for", funcName)
                print("[Current] type:", data[funcName]["type"], "| args:", data[funcName]["args"], "| filename:", data[funcName]["filename"])
                print("[This]    type:", funcType, "| args:", args, "| filename:", filename)

regex_func_def   = r"^(?!\s*if\s+)([ \t]*(?:[A-Za-z0-9_*])+[ \t]+(?:[A-Za-z0-9_* ])+)[(]((?:[^)]|\n)*?)[)]\s*[{]"
regex_func_proto = r"^([ \t]*(?:[A-Za-z0-9_*])+[ \t]+(?:[A-Za-z0-9_* ])+)[(]((?:[^)]|\n)*?)[)]\s*[;]"

# Collects both prototypes & definitions in a file.
def collect_function_prototypes(filename, filetext, data):
    collect_func_from_regex(filename, filetext, regex_func_proto, data) # First get Prototypes
    collect_func_from_regex(filename, filetext, regex_func_def, data) # Then get definitions.

# Only used for single line typedef (not structs or enums)
typedefRegex_1 = r"typedef[\t ]+(([A-Za-z_0-9 ]+)[ \t])+[ *\t]*([A-Za-z_0-9]+)(?:[\[][^\]]*[\]])*[ \t]*;"
# Used for typedefs for function pointers.
typedefRegex_2 = r"typedef[\t ]+(([A-Za-z_0-9 ]+)[ \t])+[ *\t]*(?:[(][* ]*([^)]+)[)][ \t]*[(][* ]*([^)]*)[)][^;]*)[ \t]*;"

# Get argument types for function pointers.
def get_typedef_funcpointer_arg_types(text):
    out = []
    args = cleanup_string(text).split(",")
    for arg in args:
        arg = cleanup_string(arg.replace('*', '')) # Don't need pointers, just the name.
        if ' ' in arg:
            out.append(arg.split()[0])
        else:
            out.append(arg)
    return out
    

# Get all the typedefs in the file (Not including structs, unions, or enums)
def collect_typedefs(filename, filetext, data):
    defs = regex_get_matches(filetext, typedefRegex_1)
    for match in defs:
        newType = match.group(3)
        if newType is None:
            newType = match.group(2)
        checkType = cleanup_string(match.group(1).replace('*','')) # Don't need pointers, just the name.
        data[newType] = {
            "kind": "typedef",
            "checkType": checkType,
            "value": match.group(0)
        }
    defs = regex_get_matches(filetext, typedefRegex_2)
    for match in defs:
        newType = match.group(3)
        checkType = cleanup_string(match.group(1).replace('*','')) # Don't need pointers, just the name.
        data[newType] = {
            "kind": "typedef",
            "checkType": checkType,
            "checkArgs": get_typedef_funcpointer_arg_types(match.group(4)),
            "value": match.group(0)
        }

# This regex extracts the type from a member.
structMemTypeRegex = r"[ \t]*(?:/[*][^*]*?[*]/)?[ \t]*?((?:[A-Za-z0-9_]+[ *\t]+(?=[^{ ]))+)[ \t*]*(?:(?:(?:[A-Za-z0-9_*]+)(?:[ \t*]*[\[][^]]*[\]])?[ \t]*)|(?:[^\n;]*));"
# Get all the types that are in the struct
def get_struct_types(structText):
    defs = regex_get_matches(structText, structMemTypeRegex)
    types = []
    for mem in defs:
        memType = mem.group(1).replace('*','').strip() # Don't need pointers, just the name.
        types.append(memType)
        if memType.startswith("struct "):
            types.append(memType[7:]) # Might as well include both as a precaution.
    return types

# Gets a struct/union from a file.
def collect_struct(filetext, data, structName, startIndex, index):
    nest = 1
    while(True):
        nextOpen = filetext.find('{', index)
        nextClose = filetext.find('}', index)
        if nextOpen == -1 and nextClose != -1:
            nest -= 1
            index = nextClose + 1
            if nest == 0:
                break
            continue
        if nextOpen < nextClose:
            nest += 1
            index = nextOpen + 1
        else:
            nest -= 1
            index = nextClose + 1
            if nest == 0:
                break
    endIndex = filetext.find('\n', index)
    while(filetext[index] == ' ' or filetext[index] == '\t'):
        index += 1
    structTypeName = ''
    while(filetext[index] != ';' or filetext[index] == ' ' or filetext[index] == '\t'):
        structTypeName += filetext[index]
        index += 1
    structText = filetext[startIndex:endIndex].replace('\t', '    ')
    if len(structTypeName) < 1:
        #print('Structure', structName, 'is not typedef!')
        data['struct ' + structName] = {
            'kind': "struct",
            'value': structText,
            'types': get_struct_types(structText)
        }
    else:
        data[structTypeName] = {
            'kind': "struct",
            'value': structText,
            'types': get_struct_types(structText)
        }

structRegex = r"^(?:typedef\s*)?(?:struct|union)\s*([^\s]*)?\s*{"
# Get all the structs & unions from a file
def collect_structs(filename, filetext, data):
    defs = regex_get_matches(filetext, structRegex)
    for st in defs:
        collect_struct(filetext, data, st.group(1), st.start(0), st.end(0))

enumsRegex = r"^(?:typedef\s*)?(?:enum)\s*([^\s]*)?\s*{(?:[^}]|\n)*}\s*([^\s;]*)\s*;"
# Get all the enums from a file
def collect_enums(filename, filetext, data):
    defs = regex_get_matches(filetext, enumsRegex)
    for enum in defs:
        try:
            enumName = enum.group(2)
            if len(enumName) < 1:
                enumName = "enum " + enum.group(1)
        except IndexError:
            enumName = "enum " + enum.group(1)
        if filename == "src/video.h":
            if len(enumName) < 1:
                print("Could not find an enum name for: ", enum.group(0))
                exit()
        data[enumName] = {
            "kind": "enum",
            "value": enum.group(0)
        }
        
def should_directive_be_in_singleline_category(direct):
    directText = direct.group(0)
    
    for hackDir in hack_directives_into_singleline:
        if directText.startswith('#define ' + hackDir):
            return True
    
    return direct.group(1) is None
    

definesRegex = r"(^#\s*define.*\\(?:\n.*\\)*\n.*$)|(^#(?!include)(?!undef).*$)"
# Get all the preprocessor directives in a file, except for #include and #undef
def collect_directives(filename, filetext, data):
    defs = regex_get_matches(filetext, definesRegex)
    for direct in defs:
        if should_directive_be_in_singleline_category(direct): 
            data['singleline'].append(direct.group(0))
        data['all'].append(direct.group(0))

# Return the end position of a string
def find_end(text, findStr):
    return text.find(findStr) + len(findStr)

# Returns the lines that contain the symbols of a section
def get_map_section_text(mapText, sectionSearch):
    start = find_end(mapText, sectionSearch)
    if mapText.find("\n", start + 1) > mapText.find("(", start + 1):
        return ""
    start = mapText.find("\n", start + 1)
    end = mapText.find("(", start)
    end = mapText.rfind("\n", start, end)
    return mapText[start:end]

symbolsSectionTextRegex = r"\s*[^\s]+\s*([A-Za-z0-9_]+)"
# Returns the symbols of a section in the map file
def get_symbols_from_section_text(sectionText):
    out = []
    defs = regex_get_matches(sectionText, symbolsSectionTextRegex)
    for var in defs:
        out.append(var.group(1))
    return out

# Get all the variable symbols of a filename from the dkr.map file.
def get_variable_symbols_from_map(filename, mapText):
    sectionSearch = "build/" + VERSION + "/" + filename[:-2] + ".o"

    bssSectionText = get_map_section_text(mapText, sectionSearch + "(.bss)")
    dataSectionText = get_map_section_text(mapText, sectionSearch + "(.data)")
    rodataSectionText = get_map_section_text(mapText, sectionSearch + "(.rodata)")

    return {
        "bss": get_symbols_from_section_text(bssSectionText),
        "data": get_symbols_from_section_text(dataSectionText),
        "rodata": get_symbols_from_section_text(rodataSectionText)   
    }

# Gets the variable and it's value from the file.
def get_variable_text(filename, filetext, symbol, isRodata):
    match = re.search(r"[ *]" + symbol + "[^A-Za-z_0-9]", filetext) # Doing regex for every variable is slow, but is needed.
    if match is None:
        if not isRodata:
            print("Warning: \"" + symbol + "\" is not defined in \"" + filename + "\"")
        return ""
    start = match.start()
    start = filetext.rfind("\n", 0, start) + 1
    end = filetext.find(";", start) + 1

    return filetext[start:end]
    
# Gets all the variables in a file.
def collect_variables(filename, filetext, mapText, data):
    if not filename.endswith('.c'): # Only want .c files.
        return
    variables = get_variable_symbols_from_map(filename, mapText)
    for var in variables["bss"]:
        data[var] = get_variable_text(filename, filetext, var, False)
    for var in variables["data"]:
        data[var] = get_variable_text(filename, filetext, var, False)
    for var in variables["rodata"]:
        data[var] = get_variable_text(filename, filetext, var, True)

# Loads the dkr.map file from the build folder.
def load_map():
    try:
        return open(root_dir + "/build/" + VERSION + "/dkr.map", "r").read()
    except FileNotFoundError:
        print("Error: dkr.map could not be found. Please build the rom first, then run this script.")
        exit() 
    
# Get all the relevant data from the files.
def collect(filenames):
    data = {
        'functions': {},
        'variables': {},
        'types': {}, # typedefs, structs, unions, enums
        'directives': {
            'singleline': [],
            'all': []
        }
    }

    mapText = load_map()
    
    filepaths = filenames.split('\n') + includeFiles

    for filename in filepaths:
        if (len(filename) < 1) or (not os.path.isfile(filename)) or (filename in ignoreFiles):
            continue
        filetext = open(filename, 'r').read()
        filetext = remove_comments(filetext)
        collect_directives(filename, filetext, data['directives'])         # Gets directives (Except #include & #undef)
        collect_typedefs(filename, filetext, data['types'])                # Gets typedefs
        collect_structs(filename, filetext, data['types'])                 # Gets structs/unions
        collect_enums(filename, filetext, data['types'])                   # Gets enums
        collect_variables(filename, filetext, mapText, data['variables'])  # Get variables
        collect_function_prototypes(filename, filetext, data['functions']) # Get function prototypes
    return data

# Writes a typedef/struct/union/enum to the output file
def write_single_type(types, name, addedTypes, nameStack):
    out = ''
    if name in nameStack:
        print("Circular reference! value:", name, "| nameStack:", nameStack)
        return out
    nameStack.append(name)
    if name not in addedTypes:
        kind = types[name]['kind']
        if kind == "typedef":
            checkType = types[name]['checkType']
            if checkType in types:
                out += write_single_type(types, checkType, addedTypes, nameStack)
            if 'checkArgs' in types[name]:
                checkArgs = types[name]['checkArgs']
                for argType in checkArgs:
                    if argType in types:
                        out += write_single_type(types, argType, addedTypes, nameStack)
            out += types[name]['value'] + "\n"
        elif kind == "struct":
            structTypes = types[name]['types']
            for memType in structTypes:
                if memType in types and memType not in nameStack:
                    if memType != "Object" and memType != "Particle": # This is a hack, due to circular referencing making things difficult. :/
                        out += write_single_type(types, memType, addedTypes, nameStack)
            out += types[name]['value'] + "\n"
        elif kind == "enum":
            out += types[name]['value'] + "\n"
        addedTypes[name] = 1
    nameStack.pop()
    return out


# Writes all the typedef/struct/union/enum to the output file
def write_output_types(types):
    out = ''
    out += 'struct Object;\n' # This is a hack, due to circular referencing making things difficult. :/
    addedTypes = {}
    for name in types.keys():
        nameStack = []
        out += write_single_type(types, name, addedTypes, nameStack)
    return out + '\n'

# Writes all the function prototypes to the output file
def write_output_functions(funcs):
    out = ''
    for name in funcs.keys():
        out += funcs[name]['type'] + ' ' + name + '(' + funcs[name]['args'] + ');\n'
    return out + '\n'

# Writes all the preprocessor directives to the output file
def write_output_directives(directives):
    directives['singleline'].append('#define NULL 0\n') # Hack, since cleanup() will remove the original NULL definition.
    return [ '\n'.join(directives['singleline']) + '\n', '\n'.join(directives['all']) + '\n' ]

# Writes a variable to the output file
def write_output_variable(key, variables, varKeys, doneKeys):
    if key in doneKeys:
        return ""
    out = ""
    text = variables[key]
    for key2 in varKeys:
        if len(variables[key2]) < 1:
            continue
        if key == key2:
            continue
        if key2 in text:
            out += write_output_variable(key2, variables, varKeys, doneKeys)
    out += text.replace('UNUSED', '') + '\n'
    doneKeys[key] = 1
    return out

# Writes all the variables to the output file
def write_output_variables(variables):
    out = ''
    doneKeys = {}
    varKeys = variables.keys()
    for key in varKeys:
        if len(variables[key]) < 1:
            continue
        out += write_output_variable(key, variables, varKeys, doneKeys)
    return out + '\n'

# Preprocess everything, since mips2c doesn't like the preprocessor.
def preprocess_all(directivesText):
    open("__temp.c", "w").write(directivesText)
    cpp_command = ["gcc", "-E", "-P", "-undef", "-D_LANGUAGE_C", "-D__sgi", "-DNON_MATCHING", "-D_Static_assert(x, y)=", "-D__attribute__(x)=", "__temp.c"]
    out = subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
    os.remove("__temp.c")
    return out

# Preprocess everything but the #defines.
def preprocess_directives(directivesText):
    open("__temp.c", "w").write(directivesText)
    cpp_command = ["gcc", "-E", "-P", "-fdirectives-only", "-undef", "-D_LANGUAGE_C", "-D__sgi", "-DNON_MATCHING", "-D_Static_assert(x, y)=", "-D__attribute__(x)=", "__temp.c"]
    out = subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
    os.remove("__temp.c")
    return out

# Creates the output file text.
def write_output(data):
    header = '/*** DKR decomp context file (Automatically generated by m2ctx.py [' + date.today().strftime("%Y/%m/%d") + ']) ***/\n\n'
    out = ''
    directives = write_output_directives(data['directives'])
    out += directives[0] # Only add single-line directives at first for preprocessing.
    out += write_output_types(data['types'])
    out += write_output_variables(data['variables'])
    out += write_output_functions(data['functions'])
    out = fix_enums(out) # Fixes trailing commas in enums, which gets rid of a warning.
    out = cleanup(out) # Removes useless stuff
    out = preprocess_all(out) # Preprocesses everything, removing all the directives.
    out = preprocess_directives(directives[1]) + out # Add the defines back in.
    return header + out
    
# Uses the `find` program to return the filenames in the specified folders.
def find_files():
    find_command = ["find"] + search_folders + ["-type", "f", "-name", "*.[ch]"]
    try:
        return subprocess.check_output(find_command, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n"
            + cpp_command,
            file=sys.stderr,
        )
        sys.exit(1)
    

def main():
    print("Generating context file...")
    
    data = collect(find_files())

    with open(os.path.join(root_dir, "ctx.c"), "w", encoding="UTF-8") as f:
        f.write(write_output(data))
    print("Done! Generated as ctx.c")


if __name__ == "__main__":
    main()
