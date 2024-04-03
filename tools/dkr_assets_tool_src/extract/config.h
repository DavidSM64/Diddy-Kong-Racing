#pragma once

#include <map>
#include <vector>
#include <string>

#include "helpers/jsonHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"


/*******************************************************/

struct DkrExtractCodeSectionFile {
    std::string filename;
    uint32_t length;
};

struct DkrExtractCodeSection {
    std::string type;
    fs::path folder; // directory to extract to
    std::vector<DkrExtractCodeSectionFile> files;
};

/*******************************************************/

struct DkrExtractAssetSectionFileMenuText {
    std::string language;
};

struct DkrExtractAssetSectionFileTexture {
    bool flipTex = false; // Should the texture be flipped vertically? (No by default)
};

struct DkrExtractAssetSectionFileMisc {
    std::string miscType; // Defaults to "Binary"
};

// TODO: Refactor this into a union.
struct DkrExtractAssetSectionFileSpecific { // section specific info
    DkrExtractAssetSectionFileTexture texture;
    DkrExtractAssetSectionFileMenuText menuText;
    DkrExtractAssetSectionFileMisc misc;
};

struct DkrExtractAssetSection;

struct DkrExtractAssetSectionFile {
    // Pointer to the section this belong to. Wish this was a reference instead, but it ended up being a big hassle.
    struct DkrExtractAssetSection *section = nullptr; 
    int index;
    std::string buildId; // Id for the file.
    std::string filename;
    fs::path folder; // directory to extract to
    DkrExtractAssetSectionFileSpecific specific;
};

/************************/

struct DkrExtractTexturesSection {
    bool flipTexturesByDefault;
};

struct DkrExtractTableSection {
    std::string forSection;
};

struct DkrExtractFontsSection {
    std::vector<std::string> fontNames;
};

struct DkrExtractMenuTextSection {
    // Set in extractor.c
    size_t numberOfTextEntries; // Number of entries per each language. 
    // Set in config.c
    std::vector<std::string> languageOrder;
    std::vector<std::string> menuTextBuildIds;
};

// TODO: Refactor this into a union.
struct DkrExtractAssetSectionSpecific { // section specific info
    DkrExtractTexturesSection textures;
    DkrExtractTableSection tableData;
    DkrExtractFontsSection fonts;
    DkrExtractMenuTextSection menuText;
};

struct DeferInfo {
    std::string fromSection;
    std::string idPostfix;
    std::string outputPath;
};

struct DkrExtractAssetSection {
    std::string buildId; // Id for the section.
    std::string type;
    fs::path folder; // directory to extract to
    int table;
    int group; // Extraction group. (Need to delay some groups to make sure things are in the correct order).
    std::string filesDefaultFolder;
    std::string defaultBuildIdPrefix;
    DkrExtractAssetSectionSpecific specific;
    std::vector<DkrExtractAssetSectionFile> files;
    bool isDeferred;
    DeferInfo deferInfo;
    
    // May return null
    DkrExtractAssetSectionFile *get_asset_section_file(int index);
    // May return null
    DkrExtractAssetSectionFile *get_single_file();
};

/*******************************************************/

class DkrExtractConfig {
public:
    DkrExtractConfig(std::string filepath);
    ~DkrExtractConfig();
    
    std::string get_dkr_version();
    std::string get_name();
    std::string get_md5();
    int get_revision();
    bool is_valid();
    void parse();
    
    std::vector<DkrExtractCodeSection> codeSections;
    std::vector<DkrExtractAssetSection> assetSections;
    
    std::string get_build_id_of_section(int sectionIndex);
    
    // Use AssetsHelper::get_build_id_of_index() instead.
    //std::string get_build_id_of_file_from_section(std::string sectionBuildId, int fileIndex=-1);
    
    std::string get_folder_path_to_section(std::string sectionBuildId);
    std::string get_path_to_file(std::string sectionBuildId, int fileIndex=-1);
    
    // Retrives the build id of the section that the table represents.
    std::string get_build_id_of_section_from_table_id(std::string tableBuildId);
    
    void get_default_object_entries_order_array(std::vector<std::string> &out);
private:
    JsonFile *_configJson;
    bool _isValid;
    fs::path _filepath;
    bool _load_config();
    
    void _parse_code_sections();
    void _parse_asset_sections();
    
    std::unordered_map<std::string, int> _sectionIdToIndex;
    void _populate_sectionIdToIndex_map();
};
