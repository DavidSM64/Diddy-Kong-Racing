#include "extractor.h"

#include <functional>

#include "helpers/stringHelper.h"
#include "helpers/jsonHelper.h"
#include "misc/constants.hpp"

#include "helpers/c/cStructHelper.h"
#include "helpers/c/cEnumsHelper.h"

#include "libs/ThreadPool.h"

// Extract types
#include "extractTypes/extractAudio.h"
#include "extractTypes/extractBinary.h"
#include "extractTypes/extractTexture.h"
#include "extractTypes/extractFonts.h"
#include "extractTypes/extractGameText.h"
#include "extractTypes/extractLevelName.h"
#include "extractTypes/extractLevelModel.h"
#include "extractTypes/extractLevelHeader.h"
#include "extractTypes/extractLevelObjectTranslationTable.h"
#include "extractTypes/extractMenuText.h"
#include "extractTypes/extractObjectAnimation.h"
#include "extractTypes/extractObjectHeader.h"
#include "extractTypes/extractObjectMap.h"
#include "extractTypes/extractObjectModel.h"
#include "extractTypes/extractParticle.h"
#include "extractTypes/extractParticleBehavior.h"
#include "extractTypes/extractSprite.h"
#include "extractTypes/extractTTGhost.h"
#include "extractTypes/extractMisc.h"

/************************ Hope this part doesn't cause too much cringe. **************************/

#define EXTRACTOR_ARGS DkrAssetsSettings &settings, ExtractInfo &info
#define EXTRACTOR_LAMDA(classConstructorCode) [](EXTRACTOR_ARGS) { classConstructorCode(settings, info); }

typedef std::function<void(EXTRACTOR_ARGS)> ExtractorFunction;

// Put type with the extract class here!
std::unordered_map<std::string, ExtractorFunction> extractorMap = {
    {                      "Binary", EXTRACTOR_LAMDA(ExtractBinary)           },
    {                       "Fonts", EXTRACTOR_LAMDA(ExtractFonts)            },
    { "LevelObjectTranslationTable", EXTRACTOR_LAMDA(ExtractLOTT)             },
    {                     "Texture", EXTRACTOR_LAMDA(ExtractTexture)          },
    {              "LevelObjectMap", EXTRACTOR_LAMDA(ExtractObjectMap)        },
    {                  "LevelModel", EXTRACTOR_LAMDA(ExtractLevelModel)       },
    {                 "LevelHeader", EXTRACTOR_LAMDA(ExtractLevelHeader)      },
    {                "ObjectHeader", EXTRACTOR_LAMDA(ExtractObjectHeader)     },
    {                 "ObjectModel", EXTRACTOR_LAMDA(ExtractObjectModel)      },
    {             "ObjectAnimation", EXTRACTOR_LAMDA(ExtractObjectAnimation)  },
    {                     "TTGhost", EXTRACTOR_LAMDA(ExtractTTGhost)          },
    {                    "GameText", EXTRACTOR_LAMDA(ExtractGameText)         },
    {                    "MenuText", EXTRACTOR_LAMDA(ExtractMenuText)         },
    {               "Miscellaneous", EXTRACTOR_LAMDA(ExtractMisc)             },
    {                      "Sprite", EXTRACTOR_LAMDA(ExtractSprite)           },
    {                       "Audio", EXTRACTOR_LAMDA(ExtractAudio)            },
    {                    "Particle", EXTRACTOR_LAMDA(ExtractParticle)         },
    {            "ParticleBehavior", EXTRACTOR_LAMDA(ExtractParticleBehavior) },
};

/*************************************************************************************************/

DkrExtract::DkrExtract(DkrAssetsSettings &settings) : _settings(settings) {
    fs::path pathToVanillaAssets = _settings.pathToAssets / ".vanilla/";
    _settings.pathToAssets = pathToVanillaAssets / (settings.dkrVersion + "/");
    
    // First find config
    DebugHelper::info_verbose("Finding config...");
    _find_config();
    if(_config == nullptr) {
        DebugHelper::error("Could not find a config file for DKR version: ", _settings.dkrVersion);
    }
    
    // Then find a valid rom.
    DebugHelper::info_verbose("Finding ROM...");
    _find_rom(_settings.pathToBaseroms, true);
    if(_rom == nullptr) {
        // If no rom was found in the baseroms directory, then try the root directory (non-recursively).
        _find_rom(_settings.pathToRepo, false);
    }
    
    if(_rom == nullptr) {
        DebugHelper::error("Could not find a valid ROM file for DKR version: ", _settings.dkrVersion);
    }
    
    DebugHelper::info_verbose("Parsing config...");
    // Parse the config. (Wanted to make sure there was a ROM before parsing the config)
    _config->parse();
    
    // Preload structs & enums into context.
    _preload_c_context();
    
    DebugHelper::info_verbose("Extracting...");
    // Finally, run the extraction!
    _extract();
}

DkrExtract::~DkrExtract() {
    if(_config != nullptr) {
        delete _config;
    }
    if(_rom != nullptr) {
        delete _rom;
    }
}

void DkrExtract::_find_config() {
    std::vector<fs::path> configFiles = FileHelper::get_files_from_directory_with_extension(_settings.pathToConfigs, ".config.json", false);
    DebugHelper::info_verbose("Number of configs: ", configFiles.size());
    for(size_t i = 0; i < configFiles.size(); i++) {
        _config = new DkrExtractConfig(configFiles[i]);
        if(_config->get_dkr_version() == _settings.dkrVersion) {
            DebugHelper::info("Using config file: ", configFiles[i]);
            return;
        }
        delete _config;
    }
    _config = nullptr; // Could not find the config.
}

void DkrExtract::_find_rom(const std::string &directory, bool recursive) {
    std::vector<fs::path> romFiles = FileHelper::get_files_from_directory(directory, recursive);
    for(size_t i = 0; i < romFiles.size(); i++) {
        _rom = new DkrExtractROM(romFiles[i]);
        if(_rom->is_valid() && _config->get_md5() == _rom->get_calculated_md5()) {
            DebugHelper::info("Using ROM file: ", romFiles[i]);
            return;
        }
        delete _rom;
    }
    _rom = nullptr; // Could not find a rom.
}

void DkrExtract::_extract() {
    DebugHelper::DebugTimer timer;
    uint32_t romOffset = 0;
    DebugHelper::info_verbose("Getting code sections...");
    _get_code_extractions(romOffset);
    DebugHelper::info_verbose("Getting asset sections...");
    _get_asset_extractions(romOffset);
    DebugHelper::info_verbose("Creating main json file...");
    _generate_main_json_file();
    DebugHelper::info_verbose("Creating obj-behavior-to-entry json file...");
    _generate_obj_behavior_to_entry_json_file();
    DebugHelper::info_verbose("Took ", timer.elapsed(), " to initialize extract info.");
    
    DebugHelper::DebugTimer timer2;
    
    // extractions should be sorted by the group number.
    for (auto &pair : extractions) {
        std::vector<ExtractInfo> &extracts = pair.second;
        bool errorOccured = false;
        std::exception_ptr ex;
        {
            ThreadPool pool(_settings.threadCount);
            for(ExtractInfo &info : extracts) {
                std::string type = info.get_type();
                // Check to make sure the builderMap has the given type.
                if(extractorMap.find(type) == extractorMap.end()) {
                    // For now this is a warning, but maybe make it an error instead?
                    DebugHelper::warn("The input type \"", type, "\" is currently not implemented.");
                    continue;
                }
                pool.enqueue([this, type, &info = info, &errorOccured = errorOccured, &ex = ex] {
                    if(errorOccured) {
                        return;
                    }
                    // Call the class constructor of a type.
                    try {
                        extractorMap[type](_settings, (ExtractInfo &)info);
                    } catch (...) {
                        errorOccured = true;
                        ex = std::current_exception();
                    }
                });
                if(errorOccured) {
                    break;
                }
            }
        }
        if(errorOccured) {
            std::rethrow_exception(ex);
        }
        
        // ThreadPool's destructor will join the threads.
    }
    DebugHelper::info_verbose("Took ", timer.elapsed(), " to extract all assets.");
}

// Group defaults to 0 if not specified.
void DkrExtract::_add_new_extraction(ExtractInfo &newExtract, int group) {
    // Make sure the group exists in the map
    if(extractions.find(group) == extractions.end()) {
        extractions[group] = std::vector<ExtractInfo>(); // New group
    }
    extractions[group].push_back(newExtract);
}

void DkrExtract::_get_code_extractions(uint32_t &romOffset) {
    for(DkrExtractCodeSection &codeSection : _config->codeSections) {
        for(DkrExtractCodeSectionFile &codeFile : codeSection.files) {
            if(codeSection.type == "NoExtract") {
                DebugHelper::info_verbose(DebugHelper::to_hex(romOffset), ",", codeSection.type, ",\"", codeFile.filename, "\",", DebugHelper::to_hex(codeFile.length));
                romOffset += codeFile.length;
                continue;
            }
            ExtractInfo newExtract(codeSection.type, codeFile.filename, codeSection.folder, _rom, _config, &_c_context, romOffset, codeFile.length, 0);
            _add_new_extraction(newExtract);
            DebugHelper::info_verbose(DebugHelper::to_hex(romOffset), ",", codeSection.type, ",\"", codeFile.filename, "\",\"", codeSection.folder, "\",", DebugHelper::to_hex(codeFile.length));
            romOffset += codeFile.length;
        }
    }
}

// Note: sectionFile could be null.
void DkrExtract::_get_asset_section_file_info(DkrExtractAssetSection *assetSection, DkrExtractAssetSectionFile *sectionFile, size_t fileNum, uint32_t romOffset, size_t length) {
    std::string filename = "";
    std::string buildId = "";
    std::string folder = "";
    if(sectionFile != nullptr) {
        filename = sectionFile->filename;
        buildId = sectionFile->buildId;
        folder = sectionFile->folder;
    }
    if(buildId.empty()) {
        buildId = assetSection->buildId + "_" + std::to_string(fileNum);
    }
    if(filename.empty()) {
        filename = buildId;
        StringHelper::make_lowercase(filename);
    }
    if(folder.empty()) {
        folder = assetSection->filesDefaultFolder;
    }
    
    ExtractInfo newExtract(assetSection->type, filename, folder, _rom, _config, &_c_context, romOffset, length, fileNum, assetSection);
    
    if(assetSection->type == "Texture") {
        newExtract.set_tag("flipTex", (sectionFile != nullptr) ? sectionFile->specific.texture.flipTex : assetSection->specific.textures.flipTexturesByDefault);
    } else if(assetSection->type == "MenuText") {
        newExtract.set_tag("language", sectionFile->specific.menuText.language);
    } else if(assetSection->type == "Miscellaneous") {
        // miscType set to "Binary" if the file was not specified.
        newExtract.set_tag("miscType", (sectionFile != nullptr) ? sectionFile->specific.misc.miscType : "Binary");
    }
    
    if(assetSection->isDeferred) {
        // This will be extracted as a part of another file.
        DeferredExtractions::get().add_extraction(assetSection->buildId, newExtract);
        return;
    }
    
    _add_new_extraction(newExtract, assetSection->group);
}

void DkrExtract::_get_asset_files_from_table(DkrExtractAssetSection *assetSection, int sectionOffset, int tableSectionOffset) {
    DebugHelper::info_verbose("Section offset = ", DebugHelper::to_hex(sectionOffset));
    
    // Get the table type from a section type name.
    DkrAssetTableType tableType = AssetTable::table_type_from_section_type(assetSection->type);
    
    AssetTable assetSectionTable(_rom, tableSectionOffset, tableType);
    
    if(tableType == DkrAssetTableType::MenuTextTable) {
        // First entry determines the number of text entries for each language.
        assetSection->specific.menuText.numberOfTextEntries = _rom->get_s32(tableSectionOffset);
    }
    
    size_t numFilesInSection = assetSectionTable.size();
    
    for(size_t fileIndex = 0; fileIndex < numFilesInSection; fileIndex++) {
        uint32_t offset = sectionOffset + assetSectionTable.get_entry_offset(fileIndex);
        uint32_t fileLength = assetSectionTable.get_entry_size(fileIndex);
        _get_asset_section_file_info(assetSection, assetSection->get_asset_section_file(fileIndex), fileIndex, offset, fileLength);
    }
    
    _generate_section_json_file(assetSection, &assetSectionTable);
}

void DkrExtract::_get_single_asset_info(DkrExtractAssetSection *assetSection, uint32_t romOffset, size_t length) {
    DkrExtractAssetSectionFile *sectionFile = assetSection->get_single_file();
    
    std::string filename = "";
    std::string buildId = "";
    std::string folder = "";
    if(sectionFile != nullptr) {
        filename = sectionFile->filename;
        buildId = sectionFile->buildId;
        folder = sectionFile->folder;
    }
    if(buildId.empty()) {
        buildId = assetSection->buildId;
    }
    if(filename.empty()) {
        filename = buildId;
        StringHelper::make_lowercase(filename);
    }
    if(folder.empty()) {
        folder = assetSection->filesDefaultFolder;
    }
    
    ExtractInfo newExtract(assetSection->type, filename, folder, _rom, _config, &_c_context, romOffset, length, 0, assetSection);
    
    if(assetSection->isDeferred) {
        // This will be extracted as a part of another file.
        DeferredExtractions::get().add_extraction(assetSection->buildId, newExtract);
        return;
    }
    
    _add_new_extraction(newExtract, assetSection->group);
}

void DkrExtract::_get_asset_extractions(uint32_t &romOffset) {
    AssetTable mainAssetsTable(_rom, romOffset, DkrAssetTableType::FixedTable);
    
    size_t numAssetSections = mainAssetsTable.size();
    
    // Assets start past the main table. 
    romOffset += (numAssetSections + 2) * 4; 
    
    DebugHelper::assert_(_config->assetSections.size() == numAssetSections, 
        "(DkrExtract::_get_asset_extractions) Number of assets in config does not match the ROM! Num assets in config: ", 
        _config->assetSections.size(), ", in ROM: ", numAssetSections);
    
    for(size_t sectionIndex = 0; sectionIndex < numAssetSections; sectionIndex++) {
        DkrExtractAssetSection *assetSection = &_config->assetSections[sectionIndex];
        
        if(assetSection->type == "Empty") {
            // Don't bother extracting empty sections.
            continue;
        }
        
        int sectionOffset = romOffset + mainAssetsTable.get_entry_offset(sectionIndex);
        
        if(assetSection->table != -1) {
            int tableSectionOffset = romOffset + mainAssetsTable.get_entry_offset(assetSection->table);
            _get_asset_files_from_table(assetSection, sectionOffset, tableSectionOffset);
            continue;
        }
        
        if(assetSection->type == "Table") {
            continue;
        }
        
        size_t sectionLength = mainAssetsTable.get_entry_offset(sectionIndex + 1) - mainAssetsTable.get_entry_offset(sectionIndex);
        _get_single_asset_info(assetSection, sectionOffset, sectionLength);
        _generate_section_json_file(assetSection);
    }
}

// sectionTable is nullptr when the asset section doesn't have a table (Is a single file)
void DkrExtract::_generate_section_json_file(DkrExtractAssetSection *assetSection, AssetTable *sectionTable) {
    if(assetSection->isDeferred) {
        return;
    }
    
    std::string buildIdAsFilename = assetSection->buildId;
    StringHelper::make_lowercase(buildIdAsFilename);
    fs::path outFilename = _settings.pathToAssets / (buildIdAsFilename + ".meta.json");
    
    WritableJsonFile jsonFile(outFilename);
    
    jsonFile.set_string("/folder", assetSection->folder);
    jsonFile.set_string("/type", assetSection->type);
    
    if(assetSection->type == "MenuText") {
        std::string orderPtr = "/menu-text-build-ids";
        size_t numIds = assetSection->specific.menuText.menuTextBuildIds.size();
        for(size_t i = 0; i < numIds; i++) {
            jsonFile.set_string(orderPtr + "/" + std::to_string(i), assetSection->specific.menuText.menuTextBuildIds[i]);
        }
    }
    
    if(sectionTable == nullptr) {
        // This section does not have a table.
        DkrExtractAssetSectionFile *sectionFile = assetSection->get_single_file();
        if(sectionFile == nullptr) {
            jsonFile.set_string("/filename", buildIdAsFilename + ".json");
        } else {
            jsonFile.set_string("/filename", sectionFile->filename + ".json");
        }
        jsonFile.save();
        return;
    }
    
    // This section has a table.
    jsonFile.set_string("/table", _config->get_build_id_of_section(assetSection->table));
    
    std::string orderPtr = "/files/order/";
    std::string sectionsPtr = "/files/sections/";
    
    for(size_t i = 0; i < sectionTable->size(); i++) {
        DkrExtractAssetSectionFile *sectionFile = assetSection->get_asset_section_file(i);
        std::string fileBuildId;
        fs::path fileFilepath;
        if(sectionFile == nullptr) {
            fileBuildId = assetSection->buildId + "_" + std::to_string(i);
            std::string temp = fileBuildId + ".json";
            StringHelper::make_lowercase(temp);
            fileFilepath = temp;
            if(!assetSection->filesDefaultFolder.empty()) {
                fileFilepath = assetSection->filesDefaultFolder / fileFilepath;
            }
        } else {
            fileBuildId = sectionFile->buildId;
            fileFilepath = sectionFile->filename + ".json";
            if(!sectionFile->folder.empty()) {
                fileFilepath = sectionFile->folder / fileFilepath;
            } else if(!assetSection->filesDefaultFolder.empty()) {
                fileFilepath = assetSection->filesDefaultFolder / fileFilepath;
            }
        }
        
        jsonFile.set_string(orderPtr + std::to_string(i), fileBuildId);
        jsonFile.set_string(sectionsPtr + fileBuildId + "/filename", fileFilepath);
    }
    
    jsonFile.save();
}

// Creates the "assets.meta.json" file
void DkrExtract::_generate_main_json_file() {
    fs::path outFilename = _settings.pathToAssets / "assets.meta.json";
    WritableJsonFile jsonFile(outFilename);
    
    jsonFile.set_int("/@revision", DKRAT_REVISION_MAJOR);
    jsonFile.set_int("/@revision-minor", DKRAT_REVISION_MINOR);
    jsonFile.set_string("/@version", _settings.dkrVersion);
    
    for(size_t i = 0; i < _config->assetSections.size(); i++) {
        DkrExtractAssetSection *assetSection = &_config->assetSections[i];
        
        jsonFile.set_string("/assets/order/" + std::to_string(i), assetSection->buildId);
        std::string sectionStr = "/assets/sections/" + assetSection->buildId;
        
        if(assetSection->type == "Table") {
            std::string forId = _config->get_build_id_of_section_from_table_id(assetSection->buildId);
            jsonFile.set_string(sectionStr + "/for", forId);
        } else if (assetSection->type == "Empty") {
            // Do nothing.
        } else {
            std::string filename = assetSection->buildId;
            if(assetSection->isDeferred) {
                jsonFile.set_bool(sectionStr + "/deferred", true);
                jsonFile.set_string(sectionStr + "/defer-info/from-section", assetSection->deferInfo.fromSection);
                jsonFile.set_string(sectionStr + "/defer-info/id-postfix", assetSection->deferInfo.idPostfix);
                jsonFile.set_string(sectionStr + "/defer-info/output-path", assetSection->deferInfo.outputPath);
            } else {
                StringHelper::make_lowercase(filename);
                filename += ".meta.json";
                jsonFile.set_string(sectionStr + "/filename", filename);
            }
        }
        jsonFile.set_string(sectionStr + "/type", assetSection->type);
    }
    
    jsonFile.save();
}

void DkrExtract::_generate_obj_behavior_to_entry_json_file() {
    fs::path outFilename = _settings.pathToAssets / "objects/obj_beh_to_entry.meta.json";
    WritableJsonFile jsonFile(outFilename);
    
    CEnum *objBehaviors = _c_context.get_enum("ObjectBehaviours");
    
    std::vector<std::string> defaultObjEntriesOrder;
    _config->get_default_object_entries_order_array(defaultObjEntriesOrder);
    
    for(int i = 0; i < 128; i++) {
        std::string symbol;
        DebugHelper::assert_(objBehaviors->get_symbol_of_value(i, symbol),
            "(DkrExtract::_generate_obj_behavior_to_entry_json_file) Could not get a symbol for the value ", i, " in the ObjectBehaviors enum.");
        
        
        CStruct *entryStruct = _c_context.get_struct(defaultObjEntriesOrder[i]);
        DebugHelper::assert_(entryStruct != nullptr, 
            "(DkrExtract::_generate_obj_behavior_to_entry_json_file) Could not find struct \"", defaultObjEntriesOrder[i], "\"");
        
        jsonFile.set_string("/" + symbol, defaultObjEntriesOrder[i]);
    }
    
    jsonFile.save();
}

// Preload structs & enums into context.
void DkrExtract::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all structs from these files.
    fs::path structPaths[] = {
        includeFolder / "level_object_entries.h",
    };
    
    for(fs::path &structPath : structPaths) {
        CStructHelper::load_structs_from_file(&_c_context, structPath);
    }
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "enums.h",
        includeFolder / "object_behaviors.h",
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
    
}
