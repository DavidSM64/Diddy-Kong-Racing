#include "extract_config.h"

ConfigRange::ConfigRange(int start, int size, ConfigRangeType type, std::vector<std::string> properties){
    rangeStart = start;
    rangeSize = size;
    rangeType = type;
    rangeProperties = properties;
}

ConfigRange::~ConfigRange(){
}

int ConfigRange::get_start(){
    return rangeStart;
}
int ConfigRange::get_size(){
    return rangeSize;
}
ConfigRangeType ConfigRange::get_type(){
    return rangeType;
}
std::string ConfigRange::get_property(int propertyIndex){
    if(propertyIndex >= rangeProperties.size()) {
        return "";
    }
    return rangeProperties[propertyIndex];
}

/**********************************************/

Config::Config(std::string directory, std::string filename){
    std::cout << "Reading config \"" << filename << "\"" << std::endl;
    this->directory = directory;
    currentRangeOffset = 0;
    
    std::string text = read_file(directory + '/' + filename);
    
    parse(text);
}

Config::~Config(){
}

bool Config::is_supported() {
    return !notSupported;
}
std::string Config::get_name(){
    return name;
}
std::string Config::get_md5(){
    return md5;
}
std::string Config::get_subfolder(){
    return subfolder;
}
int Config::get_size() {
    return currentRangeOffset;
}
int Config::get_number_of_ranges(){
    return ranges.size();
}
ConfigRange Config::get_range(int index){
    return ranges[index];
}

void Config::parse(std::string text){
    std::regex regex_property("^\\s*([0-9a-zA-Z\\-]+)\\s*:\\s*[\"]([^\"]*)[\"]\\s*$");
    std::regex regex_range("^\\s*\\[\\s*(0x[0-9a-fA-F]+)\\s*\\]\\s*:\\s*(.*)$");
    
    std::istringstream f(text);
    std::string line;
    std::smatch match;
    while (std::getline(f, line)) {
        line = strip_comments(line);
        
        if(line.length() < 1) {
            continue;
        }
        if (std::regex_search(line, match, regex_property)) {
            parse_property(match[1], match[2]);
            continue;
        }
        if (std::regex_search(line, match, regex_range)) {
            parse_range(match[1], match[2]);
            continue;
        }
        
        std::cout << "Invalid line: " << line << std::endl;
        throw 1;
    }
}

void Config::parse_property(std::string name, std::string value){
    name = get_lowercase(trim(name));
    
    if(name == "config-name") {
        this->name = value;
        return;
    } else if (name == "subfolder") {
        this->subfolder = value;
        return;
    } else if (name == "checksum-md5") {
        this->md5 = value;
        return;
    } else if (name == "not-supported") {
        this->notSupported = get_lowercase(trim(value)) == "true";
        return;
    } else if (name == "include") {
        std::string text = read_file(this->directory + '/' + value);
        parse(text);
        return;
    }
    
    return;
}

void Config::parse_range(std::string rangeSize, std::string rangeProperties) {
    int size = std::stoi(rangeSize, 0, 16);
    
    std::vector<std::string> properties = split_string(rangeProperties, ',');
    
    for(size_t i = 0; i < properties.size(); i++) {
        // Remove surrounding whitespace
        properties[i] = trim(properties[i]);
        // Remove doublequotes
        properties[i] = trim(properties[i].substr(1, properties[i].size() - 2));
    }
    
    ConfigRangeType type = get_range_type(properties[0]);
    ranges.push_back(ConfigRange(currentRangeOffset, size, type, properties));
    currentRangeOffset += size;
}

ConfigRangeType Config::get_range_type(std::string typeString) {
    std::string type = get_lowercase(trim(typeString));
    
    if(type == "binary")     return ConfigRangeType::BINARY;
    if(type == "noextract")  return ConfigRangeType::NOEXTRACT;
    if(type == "compressed") return ConfigRangeType::COMPRESSED;
    if(type == "texture")    return ConfigRangeType::TEXTURE;
    
    std::cout << "Unknown extraction type: " << type << std::endl;
    throw 1;
    return ConfigRangeType::UNDEFINED;
}

std::string Config::read_file(std::string filename) {
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;
}
 
std::string Config::trim(std::string input) {
   size_t b = input.find_first_not_of(' ');
   if (b == std::string::npos) b = 0;
   return input.substr(b, input.find_last_not_of(' ') + 1 - b);
}
 
std::string Config::strip_comments(std::string input) {
   return trim(input.substr(0, input.find_first_of("#")));
}

std::vector<std::string> Config::split_string(std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string Config::get_lowercase(std::string input) {
    std::string output = input;
    for(auto& element : output) {
        element = std::tolower(element);
    }
    return output;
}

/**********************************************/
