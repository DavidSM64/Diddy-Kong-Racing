#include "jsonHelper.h"

std::string assetsFolderPath = "";
bool hasLoadedAssetsJson = false;
json::JSON assetsJson;

std::string lastSectionName = "";
json::JSON *lastSection;
std::unordered_map<std::string, json::JSON> sectionCache;

std::string lastJsonFileName = "";
json::JSON *lastJsonFile;
std::unordered_map<std::string, json::JSON> jsonFileCache;

#define ASSETS_FILENAME "assets.json"

json::JSON load_assets_json(std::string assetsFolder, std::string jsonName) {
    std::string jsonFilepath = assetsFolder + "/" + jsonName;
    return json::JSON::Load(read_text_file(jsonFilepath));
}

void write_json(json::JSON &jsonData, std::string filename) {
    std::ofstream myfile;
    myfile.open(filename);
    myfile << jsonData;
    myfile.close();
}

void setAssetsFolderPath(std::string path) {
    assetsFolderPath = path;
}

void make_sure_assets_json_is_loaded() {
    if(hasLoadedAssetsJson) {
        return;
    }
    if(assetsFolderPath == "") {
        std::cout << "assetsFolderPath not defined! Make sure setAssetsFolderPath() is called somewhere!" << std::endl;
        throw 1;
    }
    assetsJson = load_assets_json(assetsFolderPath, ASSETS_FILENAME);
    hasLoadedAssetsJson = true;
}

json::JSON *get_section_json(std::string sectionName) {
    make_sure_assets_json_is_loaded();
    if(sectionName == lastSectionName) {
        return lastSection;
    } else if(sectionCache.find(sectionName) == sectionCache.end()) {
        // section not found in cache, so it needs to be loaded/defined!
        json::JSON assetSection = assetsJson["assets"]["sections"][sectionName];
        if(assetSection.JSONType() == json::JSON::Class::String) {
            std::string sectionJsonLocalPath = assetsJson["assets"]["sections"][sectionName].ToString();
            make_lowercase(sectionJsonLocalPath);
            sectionCache[sectionName] = json::JSON::Load(read_text_file(assetsFolderPath + "/" + sectionJsonLocalPath));
        } else {
            sectionCache[sectionName] = assetSection;
        }
    }
    lastSectionName = sectionName;
    lastSection = &sectionCache[sectionName];
    return lastSection;
}

std::string get_build_id_from_section(std::string sectionName, int index) {
    json::JSON *sectionJson = get_section_json(sectionName);
    if(sectionJson->IsNull()) {
        return "null";
    }
    return (*sectionJson)["files"]["order"][index].ToString(); 
}

int get_index_of_string_from_json_array(json::JSON &jsonArray, std::string value) {
    for(int i = 0; i < jsonArray.length(); i++) {
        if(jsonArray[i].ToString() == value) {
            return i;
        }
    }
    return -1;
}

int get_index_from_build_id(std::string sectionName, std::string buildId) {
    json::JSON *sectionJson = get_section_json(sectionName);
    return get_index_of_string_from_json_array((*sectionJson)["files"]["order"], buildId);
}

int get_tex_2d_index_from_build_id(std::string texBuildId) {
    return get_index_from_build_id("ASSET_TEXTURES_2D", texBuildId);
}

std::vector<std::string> get_order(json::JSON orderJson) {
    std::vector<std::string> out;
    for(auto &entry : orderJson.ArrayRange()) {
        out.push_back(entry.ToString());
    }
    return out;
}

std::vector<std::string> get_section_order(std::string sectionName) {
    json::JSON *sectionJson = get_section_json(sectionName);
    return get_order((*sectionJson)["files"]["order"]);
}
std::vector<std::string> get_assets_order() {
    make_sure_assets_json_is_loaded();
    return get_order(assetsJson["assets"]["order"]);
}

std::string get_filename_from_section_entry(std::string sectionName, std::string entryName) {
    json::JSON *sectionJson = get_section_json(sectionName);
    return (*sectionJson)["files"]["sections"][entryName]["filename"].ToString();
}


int get_asset_count() {
    make_sure_assets_json_is_loaded();
    return assetsJson["assets"]["order"].length();
}

#define JSON_IS_TYPE(jsonObj, type) jsonObj.JSONType() == json::JSON::Class::type
#define JSON_IS_OBJECT(jsonObj) JSON_IS_TYPE(jsonObj, Object)
#define JSON_IS_ARRAY(jsonObj) JSON_IS_TYPE(jsonObj, Array)
#define JSON_IS_STRING(jsonObj) JSON_IS_TYPE(jsonObj, String)

bool does_json_array_contain_string(json::JSON &arrayJson, std::string value) {
    for(json::JSON &childJson : arrayJson.ArrayRange()) {
        if(JSON_IS_STRING(childJson)) {
            if(childJson.ToString() == value) return true;
        }
    }
    return false;
}

void recursively_combine_json(json::JSON &mainJson, json::JSON &addJson) {
    if(JSON_IS_OBJECT(mainJson) && JSON_IS_OBJECT(addJson)) {
        for(auto &keyValuePair : addJson.ObjectRange()) {
            std::string key = keyValuePair.first;
            json::JSON newJson = keyValuePair.second;
            if(!mainJson.hasKey(key)) {
                mainJson[key] = newJson;
                continue;            
            }
            if(JSON_IS_OBJECT(newJson)) {
                recursively_combine_json(mainJson[key], newJson);
                continue;
            }
            if(JSON_IS_ARRAY(newJson)) {
                for(json::JSON &orderEntry : newJson.ArrayRange()) {
                    // "order" is a special case, where the array should be a set.
                    if(key == "order" && does_json_array_contain_string(mainJson[key], orderEntry.ToString())) { 
                        // Order already has the value in its array, so just ignore it.
                        continue; 
                    } 
                    mainJson[key].append(orderEntry.ToString());
                }
                continue;
            }
            // Not an object or array, so just overwrite the value.
            mainJson[key] = newJson;
        }
    }
}

void combine_json_files(std::string src1Path, std::string src2Path, std::string outputPath) {
    json::JSON mainJson = json::JSON::Load(read_text_file(src1Path));
    json::JSON addJson = json::JSON::Load(read_text_file(src2Path));
    recursively_combine_json(mainJson, addJson);
    write_json(mainJson, outputPath);
}

json::JSON *load_json_file(std::string filename) {
    if(filename == lastJsonFileName) {
        return lastJsonFile;
    } else if(jsonFileCache.find(filename) == jsonFileCache.end()) {
        // file not found in cache, so it needs to be loaded!
        jsonFileCache[filename] = json::JSON::Load(read_text_file(filename));
    }
    lastJsonFileName = filename;
    lastJsonFile = &jsonFileCache[filename];
    return lastJsonFile;
}

std::string get_source_section_for_table(std::string tableSectionName) {
    json::JSON *tableSection = get_section_json(tableSectionName);
    return (*tableSection)["for"].ToString();
}



