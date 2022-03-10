#include "enumHelper.h"

bool is_string_integer(const std::string &s){
    return std::regex_match(s, std::regex("[(-|+)]?[0-9]+"));
}

bool hasLoadedEnums = false;
std::map<std::string, int> enums;
std::map<std::string, std::vector<std::string>> enumKeys;

int evalulate_enum(std::string &enumValue) {
    int attempts = 0;
    std::regex enumNameRegex("([^0-9|^&~+\\-\\/*\\s]+)");
    std::smatch sm;

    // Replaces all enum strings with their defined values. E.g. "VEHICLE_PLANE" should get replaced with "2".
    while (regex_search(enumValue, sm, enumNameRegex) && attempts++ < 100) {
        std::string foundEnum = sm[1];
        if(enums.find(foundEnum) == enums.end()) {
            std::cout << "Error: Could not find enum value \"" << foundEnum << "\". Make sure it is defined!" << std::endl;
            throw 1;
        }
        std::string newValue = std::to_string(enums[foundEnum]);
        int pos = sm.position(1);
        enumValue.replace(pos, pos + foundEnum.length(), newValue);
    }

    try {
        return calculator::eval(enumValue);
    } catch (calculator::error& e) {
        std::cerr << e.what() << std::endl;
        throw 1;
    }
}

void get_enum_values(std::string enumName, std::string enumValuesText) {
    std::vector<std::string> names;

    std::regex enumValueRegex("\\s*([_A-Za-z][_A-Za-z0-9]*)(?:\\s*=\\s*([^,]*)[,]?.*)?");
    std::smatch sm;
    std::string text = enumValuesText;
    int currentValue = 0; // Enums start off at 0.
    while (regex_search(text, sm, enumValueRegex)) {
        std::string enumValueName = sm[1];
        std::string enumValue     = sm[2];
        names.push_back(enumValueName);
        if(!enumValue.empty()) {
            currentValue = evalulate_enum(enumValue);
        }
        enums[enumValueName] = currentValue++;
        
        //std::cout << enumValueName << " = " << enums[enumValueName] << std::endl;
        text = sm.suffix();
    }
    enumKeys[enumName] = names;
}

void write_ascii_to_cache(std::vector<uint8_t> &cache, std::string &text) {
    int textLength = text.length();
    if(textLength > 255) {  // Assumption: All labels are under 256 characters.
        textLength = 255;    
    }
    cache.push_back(textLength);
    for(int i = 0; i < text.length(); i++) {
        cache.push_back((uint8_t)text.at(i));
    }
    cache.push_back(0); // Push back null terminator
}
void write_int_to_cache(std::vector<uint8_t> &cache, int value) {
    int pos = cache.size();
    for(int i = 0; i < 4; i++) cache.push_back(0);
    *((int*)(&cache[pos])) = value;
}
std::string read_ascii_from_cache(std::vector<uint8_t> &cache, int &offset) {
    int pos = offset;
    int strLength = cache[pos];
    offset += cache[pos] + 2;
    return std::string((char*)&cache[pos + 1]);
}
int read_int_from_cache(std::vector<uint8_t> &cache, int &offset) {
    int value = *((int*)(&cache[offset]));
    offset += 4;
    return value;
}

void save_enums_cache() {
    std::vector<uint8_t> cache;
    
    for(auto& keyValuePair : enumKeys) {
        std::string enumName = keyValuePair.first;
        int numberOfValues = keyValuePair.second.size();
        //std::cout << enumName << " has " << numberOfValues << " values" << std::endl;
        write_ascii_to_cache(cache, enumName);
        write_int_to_cache(cache, numberOfValues);
        for(std::string enumValueName : keyValuePair.second) {
            write_ascii_to_cache(cache, enumValueName);
            write_int_to_cache(cache, enums[enumValueName]);
        }
    }

    write_binary_file(cache, ENUMS_CACHE_PATH);
}

#define READ_STRING() read_ascii_from_cache(cache, offset)
#define READ_INT() read_int_from_cache(cache, offset)

void load_enums_cache() {
    std::vector<uint8_t> cache = read_binary_file(ENUMS_CACHE_PATH);
    int offset = 0;
    int len = cache.size();

    while(offset != len) {
        std::string enumName = READ_STRING();
        int numberOfValues = READ_INT();
        std::vector<std::string> names;
        for(int i = 0; i < numberOfValues; i++) {
            std::string enumValueName = READ_STRING();
            int enumValue = READ_INT();
            names.push_back(enumValueName);
            enums[enumValueName] = enumValue;
        }
        enumKeys[enumName] = names;
    }
}

void make_sure_enums_are_loaded() {
    if(hasLoadedEnums) {
        return;
    }

    if(path_exists(ENUMS_CACHE_PATH)) {
        load_enums_cache();
    } else {
        // Generate enums map
        std::string assetsFolderPath = get_asset_folder_path();
        std::string enumsIncludeText = read_text_file(assetsFolderPath + "/../include/enums.h");
        std::regex enumRegex("enum ([^\\s{]+)\\s*[{]((?:.*\\n)*?)[}]");
        std::smatch sm;
        std::string text = enumsIncludeText;
        while (regex_search(text, sm, enumRegex)) {
            std::string enumName = sm[1];
            std::string enumValuesText = sm[2];
            get_enum_values(enumName, enumValuesText);
            text = sm.suffix();
        }
        save_enums_cache();
    }
    hasLoadedEnums = true;
}

std::string get_enum_string_from_value(std::string enumName, int value) {
    make_sure_enums_are_loaded();
    for (std::string &key : enumKeys[enumName]) {
        if(enums[key] == value) {
            return key;
        }
    }
    return "null";
}

int get_enum_value_from_string(std::string enumName, std::string value) {
    make_sure_enums_are_loaded();
    return enums[value];
}

std::vector<std::string> get_enum_keys(std::string enumName) {
    make_sure_enums_are_loaded();
    return enumKeys[enumName];
}
