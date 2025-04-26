#include "config_old.h"

using namespace DkrAssetsTool;

#define INVALID_CONFIG_STR "<INVALID CONFIG>"
#define INVALID_CONFIG_INT -1

DkrExtractConfig::DkrExtractConfig(std::string filepath){
    _filepath = filepath;
    _tryGetConfigJson = JsonHelper::get_file(_filepath);
    _isValid = _tryGetConfigJson.has_value();
    if(_isValid) {
        _configJson = &_tryGetConfigJson.value().get();
    } else {
        _configJson = nullptr;
    }
}

DkrExtractConfig::~DkrExtractConfig() {
}  

bool DkrExtractConfig::is_valid() {
    return _isValid;
}  

std::string DkrExtractConfig::get_dkr_version() {
    if(!_isValid) {
        return INVALID_CONFIG_STR;
    }
    return _configJson->get_string("/subfolder");
}

std::string DkrExtractConfig::get_name() {
    if(!_isValid) {
        return INVALID_CONFIG_STR;
    }
    return _configJson->get_string("/config-name");
}

std::string DkrExtractConfig::get_md5() {
    if(!_isValid) {
        return INVALID_CONFIG_STR;
    }
    return _configJson->get_string("/checksum-md5");
}

int DkrExtractConfig::get_revision() {
    if(!_isValid) {
        return INVALID_CONFIG_INT;
    }
    return _configJson->get_int("/revision");
}

void DkrExtractConfig::parse() {
    DebugHelper::DebugTimer timer;
    _parse_code_sections();
    _parse_asset_sections();
    DebugHelper::info_verbose("Took ", timer.elapsed(), " to parse config file");
}

std::string DkrExtractConfig::get_build_id_of_section(int sectionIndex) {
    return assetSections[sectionIndex].buildId;
}


// Use AssetsHelper::get_build_id_of_index() instead.
/*
std::string DkrExtractConfig::get_build_id_of_file_from_section(std::string sectionBuildId, int fileIndex) {
    // Make sure the build ID is valid.
    DebugHelper::assert(_sectionIdToIndex.find(sectionBuildId) != _sectionIdToIndex.end(), 
        "(DkrExtractConfig::get_build_id_of_file_from_section) Section Build ID \"", sectionBuildId, "\" was not defined.");
    
    DkrExtractAssetSection &assetSection = assetSections[_sectionIdToIndex[sectionBuildId]];
    DkrExtractAssetSectionFile *file;
    
    if(fileIndex >= 0) {
        file = assetSection.get_asset_section_file(fileIndex);
    } else {
        file = assetSection.get_single_file();
    }
    
    if(file != nullptr) {
        return file->buildId;
    }
    
    // file is null, so get a generic id.
    if(fileIndex >= 0) {
        return sectionBuildId + "_" + std::to_string(fileIndex);
    } else {
        return sectionBuildId; // Single files just use the build id of the section.
    }
}
*/

// Returns the build id of the section that the table belongs to. Throws an error if it doesn't exist.
std::string DkrExtractConfig::get_build_id_of_section_from_table_id(std::string tableBuildId) {
    // Make sure the build ID is valid.
    DebugHelper::assert(_sectionIdToIndex.find(tableBuildId) != _sectionIdToIndex.end(), 
        "(DkrExtractConfig::get_build_id_of_section_from_table_id) Table Build ID \"", tableBuildId, "\" was not defined.");
    
    int tableIndex = _sectionIdToIndex[tableBuildId];
    
    for(size_t i = 0; i < assetSections.size(); i++) {
        if(assetSections[i].table == tableIndex) {
            return assetSections[i].buildId;
        }
    }
    
    DebugHelper::error("(DkrExtractConfig::get_build_id_of_section_from_table_id) Could not find a section that uses the table \"", 
        tableBuildId, "\"");
    
    return std::string();
}

std::string DkrExtractConfig::get_folder_path_to_section(std::string sectionBuildId) {
    // Make sure the build ID is valid.
    DebugHelper::assert(_sectionIdToIndex.find(sectionBuildId) != _sectionIdToIndex.end(), 
        "(DkrExtractConfig::get_build_id_of_file_from_section) Section Build ID \"", sectionBuildId, "\" was not defined.");
    
    DkrExtractAssetSection &assetSection = assetSections[_sectionIdToIndex[sectionBuildId]];
    return assetSection.folder;
}

std::string DkrExtractConfig::get_path_to_file(std::string sectionBuildId, int fileIndex) {
     // Make sure the build ID is valid.
    DebugHelper::assert(_sectionIdToIndex.find(sectionBuildId) != _sectionIdToIndex.end(), 
        "(DkrExtractConfig::get_build_id_of_file_from_section) Section Build ID \"", sectionBuildId, "\" was not defined.");
    
    DkrExtractAssetSection &assetSection = assetSections[_sectionIdToIndex[sectionBuildId]];
    DkrExtractAssetSectionFile *file;
    
    if(fileIndex >= 0) {
        file = assetSection.get_asset_section_file(fileIndex);
    } else {
        file = assetSection.get_single_file();
    }
    
    DebugHelper::assert(file != nullptr, "(std::string get_path_to_file) File ", fileIndex, " was not specified.");
    
    return assetSection.folder / file->folder / file->filename;
}

// May return nullptr
DkrExtractAssetSectionFile *DkrExtractAssetSection::get_asset_section_file(int index) {
    for(DkrExtractAssetSectionFile &file : files) {
        if(file.index == index) {
            return &file;
        }
    }
    return nullptr;
}

// May return nullptr
DkrExtractAssetSectionFile *DkrExtractAssetSection::get_single_file() {
    DebugHelper::assert(files.size() < 2, "(DkrExtractAssetSection::get_single_file) Section \"", type, "\" has more than one file!");
    
    if(files.empty()) {
        return nullptr;
    }
    
    return &files[0];
}

void DkrExtractConfig::get_default_object_entries_order_array(std::vector<std::string> &out) {
    size_t len = _configJson->length_of_array("/assets/misc/default-object-entries-order");
    for(size_t i = 0; i < len; i++) {
        out.push_back(_configJson->get_string("/assets/misc/default-object-entries-order/" + std::to_string(i)));
    }
}

void DkrExtractConfig::_parse_code_sections() {
    int numOfCodeSections = _configJson->length_of_array("/code/sections");
    for(int i = 0; i < numOfCodeSections; i++) {
        DkrExtractCodeSection codeSection;
        codeSection.type = _configJson->get_string("/code/sections/" + std::to_string(i) + "/type");
        codeSection.folder = _configJson->get_string("/code/sections/" + std::to_string(i) + "/folder");
        FileHelper::format_folder_string(codeSection.folder);
        DebugHelper::info_verbose("code section: ", codeSection.type, ", ", codeSection.folder);
            
        int numOfCodeFilesInSection = _configJson->length_of_array("/code/sections/" + std::to_string(i) + "/files");
        for(int j = 0; j < numOfCodeFilesInSection; j++) {
            DkrExtractCodeSectionFile codeFile;
            codeFile.filename = _configJson->get_string("/code/sections/" + std::to_string(i) + "/files/" + std::to_string(j) + "/filename");
            std::string lengthAsHex = _configJson->get_string("/code/sections/" + std::to_string(i) + "/files/" + std::to_string(j) + "/length");
            codeFile.length = std::stoi(lengthAsHex, 0, 16);
            DebugHelper::info_verbose("  code file: ", codeFile.filename, ", ", DebugHelper::to_hex(codeFile.length));
            codeSection.files.push_back(codeFile);
        }
        
        codeSections.push_back(codeSection);
    }
}

void DkrExtractConfig::_parse_asset_sections() {
    int numOfAssetSections = _configJson->length_of_array("/assets/sections");
    for(int i = 0; i < numOfAssetSections; i++) {
        DkrExtractAssetSection assetSection;
        
        assetSection.buildId = _configJson->get_string("/assets/sections/" + std::to_string(i) + "/build-id");
        assetSection.type = _configJson->get_string("/assets/sections/" + std::to_string(i) + "/type");
        assetSection.folder = _configJson->get_path("/assets/sections/" + std::to_string(i) + "/folder");
        assetSection.table = _configJson->get_int("/assets/sections/" + std::to_string(i) + "/table");
        
        assetSection.isDeferred = _configJson->get_bool("/assets/sections/" + std::to_string(i) + "/defer", false);
        
        if(assetSection.isDeferred) {
            std::string deferInfoPtr = "/assets/sections/" + std::to_string(i) + "/defer-info";
            assetSection.deferInfo.fromSection = _configJson->get_string(deferInfoPtr + "/from-section");
            assetSection.deferInfo.idPostfix = _configJson->get_string(deferInfoPtr + "/id-postfix");
            assetSection.deferInfo.outputPath = _configJson->get_path(deferInfoPtr + "/output-path");
        }
        
        // Defaults to group 0 if not specified.
        assetSection.group = _configJson->get_int("/assets/sections/" + std::to_string(i) + "/group", 0);
        
        assetSection.filesDefaultFolder = _configJson->get_path("/assets/sections/" + std::to_string(i) + "/files-default-folder");
        assetSection.defaultBuildIdPrefix = _configJson->get_string("/assets/sections/" + std::to_string(i) + "/default-build-id-prefix");
        
        bool isTexture = (assetSection.type == "Texture");
        bool isTable = (assetSection.type == "Table");
        bool isFonts = (assetSection.type == "Fonts");
        bool isMenuText = (assetSection.type == "MenuText");
        bool isMisc = (assetSection.type == "Miscellaneous");
        
        if(isTexture) {
            assetSection.specific.textures.flipTexturesByDefault = _configJson->get_bool( "/assets/sections/" + std::to_string(i) + "/flip-textures-by-default");
        } else if(isTable) {
            assetSection.specific.tableData.forSection = _configJson->get_string( "/assets/sections/" + std::to_string(i) + "/for");
        } else if(isFonts) {
            _configJson->get_array<std::string>( "/assets/sections/" + std::to_string(i) + "/font-names", assetSection.specific.fonts.fontNames);
        } else if(isMenuText) {
            _configJson->get_array<std::string>( "/assets/sections/" + std::to_string(i) + "/language-order", assetSection.specific.menuText.languageOrder);
            _configJson->get_array<std::string>( "/assets/sections/" + std::to_string(i) + "/menu-text-build-ids", assetSection.specific.menuText.menuTextBuildIds);
        }
        
        DebugHelper::info_verbose("asset section: ", assetSection.buildId, ",", 
                                                    assetSection.type, ",", 
                                                    assetSection.folder, ",", 
                                                    assetSection.table, ",", 
                                                    assetSection.filesDefaultFolder, ",", 
                                                    assetSection.defaultBuildIdPrefix);
                                                    
        if(_configJson->has("/assets/sections/" + std::to_string(i) + "/files")) {
            int numOfAssetFilesInSection = _configJson->length_of_array("/assets/sections/" + std::to_string(i) + "/files");
            for(int j = 0; j < numOfAssetFilesInSection; j++) {
                
                std::string filePtr = "/assets/sections/" + std::to_string(i) + "/files/" + std::to_string(j);
                
                DkrExtractAssetSectionFile assetFile;
                assetFile.section = &assetSection;
                assetFile.index = _configJson->get_int(filePtr + "/index", -1);
                assetFile.filename = _configJson->get_string(filePtr + "/filename", "");
                assetFile.buildId = _configJson->get_string(filePtr + "/build-id", "");
                assetFile.folder = _configJson->get_path(filePtr + "/folder", "");
                
                if(isTexture) {
                    assetFile.specific.texture.flipTex = _configJson->get_bool(filePtr + "/flip-tex", assetSection.specific.textures.flipTexturesByDefault);
                } else if(isMenuText) {
                    assetFile.specific.menuText.language = _configJson->get_string("/assets/sections/" + std::to_string(i) + "/language-order/" + std::to_string(j));
                } else if(isMisc) {
                    // Set to "Binary" by default if not specified.
                    assetFile.specific.misc.miscType = _configJson->get_string(filePtr + "/misc-type", "Binary");
                }
                
                DebugHelper::info_verbose("  asset file: ", assetFile.index, ",", assetFile.filename, ",", assetFile.buildId, ",", assetFile.folder);
                assetSection.files.push_back(assetFile);
            }
        }
        
        assetSections.push_back(assetSection);
    }
    _populate_sectionIdToIndex_map();
}

void DkrExtractConfig::_populate_sectionIdToIndex_map() {
    for(size_t i = 0; i < assetSections.size(); i++) {
        DkrExtractAssetSection &assetSection = assetSections[i];
        _sectionIdToIndex[assetSection.buildId] = i;
    }
}

