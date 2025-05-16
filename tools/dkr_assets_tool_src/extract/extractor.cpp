#include "extractor.h"

#include <functional>
#include <optional>
#include <any>
#include <algorithm>

#include "helpers/stringHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/jsonHelper.h"
#include "misc/constants.hpp"
#include "misc/globalSettings.h"

#include "helpers/c/cStructHelper.h"
#include "helpers/c/cEnumsHelper.h"
#include "helpers/c/cHeader.h"

#include "libs/ThreadPool.h"

#include "assetTable.h"
#include "config.h"
#include "stats.h"

// Extract types
#include "extractTypes/extractAudio.h"
#include "extractTypes/extractBinary.h"
#include "extractTypes/extractTexture.h"
#include "extractTypes/extractFonts.h"
#include "extractTypes/extractJpFonts.h"
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

using namespace DkrAssetsTool;

/*************************************************************************************************/

#define EXTRACTOR_ARGS ExtractInfo &info
#define EXTRACTOR_LAMDA(extractFunction) [](EXTRACTOR_ARGS) { extractFunction(info); }
typedef std::function<void(EXTRACTOR_ARGS)> ExtractorFunction;

std::unordered_map<std::string, ExtractorFunction> EXTRACTOR_MAP = {
    {                      "Binary", EXTRACTOR_LAMDA(ExtractBinary::extract)           },
    {                       "Fonts", EXTRACTOR_LAMDA(ExtractFonts::extract)            },
    {                     "JPFonts", EXTRACTOR_LAMDA(ExtractJPFonts::extract)          },
    { "LevelObjectTranslationTable", EXTRACTOR_LAMDA(ExtractLOTT::extract)             },
    {                     "Texture", EXTRACTOR_LAMDA(ExtractTexture::extract)          },
    {              "LevelObjectMap", EXTRACTOR_LAMDA(ExtractObjectMap::extract)        },
    {                  "LevelModel", EXTRACTOR_LAMDA(ExtractLevelModel::extract)       },
    {                 "LevelHeader", EXTRACTOR_LAMDA(ExtractLevelHeader::extract)      },
    {                "ObjectHeader", EXTRACTOR_LAMDA(ExtractObjectHeader::extract)     },
    {                 "ObjectModel", EXTRACTOR_LAMDA(ExtractObjectModel::extract)      },
    {             "ObjectAnimation", EXTRACTOR_LAMDA(ExtractObjectAnimation::extract)  },
    {                     "TTGhost", EXTRACTOR_LAMDA(ExtractTTGhost::extract)          },
    {                    "GameText", EXTRACTOR_LAMDA(ExtractGameText::extract)         },
    {                    "MenuText", EXTRACTOR_LAMDA(ExtractMenuText::extract)         },
    {               "Miscellaneous", EXTRACTOR_LAMDA(ExtractMisc::extract)             },
    {                      "Sprite", EXTRACTOR_LAMDA(ExtractSprite::extract)           },
    {                       "Audio", EXTRACTOR_LAMDA(ExtractAudio::extract)            },
    {                    "Particle", EXTRACTOR_LAMDA(ExtractParticle::extract)         },
    {            "ParticleBehavior", EXTRACTOR_LAMDA(ExtractParticleBehavior::extract) },
};

std::unordered_map<std::string, size_t> VERSION_TO_NUMBER = {
    {     "v77", 77 },
    {  "us.v77", 77 },
    { "pal.v77", 77 },
    {     "v79", 79 },
    { "jpn.v79", 79 },
    {     "v80", 80 },
    {  "us.v80", 80 },
    { "pal.v80", 80 },
};

/*************************************************************************************************/

void generate_section_json_file(const AssetExtractConfig &config, const ExtractStats &stats, int sectionIndex, fs::path filepath) {
    std::string configSectionPtr = "/sections/" + std::to_string(sectionIndex);
    
    std::string type = config.get<std::string>(configSectionPtr + "/default-type", "Binary");
    std::string folder = config.get<std::string>(configSectionPtr + "/folder", "");
    std::string sectionBuildId = config.get<std::string>(configSectionPtr + "/build-id", "");
    
    WritableJsonFile jsonFile(filepath);
    jsonFile.set_string("/type", type);
    jsonFile.set_string("/folder", folder);
    
    if(type == "MenuText") {
        // Copy menu-text-build-ids from the config to the section json.
        const JsonFile &configJson = config.get_config_json();
        std::vector<std::string> menuTextBuildIds;
        configJson.get_array<std::string>("/file-type-attributes/MenuText/menu-text-build-ids", menuTextBuildIds);
        int numberOfMenuTextEntries = stats.get_tag<int>("menuTextCount", 0);
        menuTextBuildIds.resize(numberOfMenuTextEntries); // Removes the added entries from v79 if this happens to be v77.
        jsonFile.set_array<std::string>("/menu-text-build-ids", menuTextBuildIds);
    }
    
    auto tryGetSectionFilesFromStats = stats.get_section_info(sectionBuildId);
    
    if(tryGetSectionFilesFromStats.has_value()) {
        const std::vector<ExtractStatInfo> &sectionFilesInfo = tryGetSectionFilesFromStats.value();
        
        size_t numberOfFiles = sectionFilesInfo.size();
        
        if(numberOfFiles == 1) {
            jsonFile.set_string("/filename", sectionFilesInfo[0].localPath);
        } else {
            for(size_t i = 0; i < numberOfFiles; i++) {
                const ExtractStatInfo &info = sectionFilesInfo[i];
                
                jsonFile.set_string("/files/order/" + std::to_string(i), info.buildId);
                jsonFile.set_string("/files/sections/" + info.buildId + "/filename", info.localPath);
            }
        }
    }
    
    jsonFile.save();
}

void generate_main_json_file(const AssetExtractConfig &config, const ExtractStats &stats) {
    fs::path outFilename = GlobalSettings::get_decomp_path_to_vanilla_assets() / "assets.meta.json";
    WritableJsonFile jsonFile(outFilename);
    
    jsonFile.set_int("/@dkrat-version/release", DKRAT_VERSION_RELEASE);
    jsonFile.set_int("/@dkrat-version/major", DKRAT_VERSION_MAJOR);
    jsonFile.set_int("/@dkrat-version/minor", DKRAT_VERSION_MINOR);
    jsonFile.set_string("/@dkr-version", GlobalSettings::get_dkr_version());
    
    size_t numberOfSections = config.number_of_sections();
    
    DebugHelper::info("numberOfSections = ", numberOfSections);
    
    for(size_t i = 0; i < numberOfSections; i++) {
        std::string configSectionPtr = "/sections/" + std::to_string(i);
        std::string sectionBuildId = config.get<std::string>(configSectionPtr + "/build-id", "");
        std::string sectionType = config.get<std::string>(configSectionPtr + "/default-type", "Binary");
        
        jsonFile.set_string("/assets/order/" + std::to_string(i), sectionBuildId);
        
        std::string outSectionPtr = "/assets/sections/" + sectionBuildId;
        jsonFile.set_string(outSectionPtr + "/type", sectionType);
        if(sectionType == "Table") {
            std::string forId = config.get<std::string>(configSectionPtr + "/for", "");
            jsonFile.set_string(outSectionPtr + "/for", forId);
        } else if (sectionType == "ObjectAnimationIdsTable") {
            jsonFile.set_string(outSectionPtr + "/for", "ASSET_OBJECT_ANIMATIONS");
            bool isDeferred = config.get<bool>(configSectionPtr + "/defer", false);
            jsonFile.set_bool(outSectionPtr + "/deferred", isDeferred);
        }  else if (sectionType == "Empty") {
            // Do nothing.
        } else {
            std::string filename = sectionBuildId;
            bool isDeferred = config.get<bool>(configSectionPtr + "/defer", false);
            if(isDeferred) {
                // Copy info from config to the main json.
                std::string fromSection = config.get<std::string>(configSectionPtr + "/defer-info/from-section", "");
                std::string idPostfix = config.get<std::string>(configSectionPtr + "/defer-info/id-postfix", "_UNK");
                std::string outputPath = config.get<std::string>(configSectionPtr + "/defer-info/output-path", ".");
                jsonFile.set_bool(outSectionPtr + "/deferred", true);
                jsonFile.set_string(outSectionPtr + "/defer-info/from-section", fromSection);
                jsonFile.set_string(outSectionPtr + "/defer-info/id-postfix", idPostfix);
                jsonFile.set_string(outSectionPtr + "/defer-info/output-path", outputPath);
            } else {
                StringHelper::make_lowercase(filename);
                filename += ".meta.json";
                jsonFile.set_string(outSectionPtr + "/filename", filename);
                generate_section_json_file(config, stats, i, GlobalSettings::get_decomp_path_to_vanilla_assets() / filename);
            }
        }
    }
    
    jsonFile.save();
}

/*************************************************************************************************/

fs::path get_valid_baserom(const AssetExtractConfig &config) {
    std::vector<fs::path> baseromFiles = FileHelper::get_files_from_directory(GlobalSettings::get_decomp_path("baseroms_subpath", "baseroms/"));
    for(fs::path &filepath : baseromFiles) {
        if(config.is_input_file_valid(filepath)) {
            return filepath;
        }
    }
    
    DebugHelper::error("No valid ROM file found for the DKR version \"", GlobalSettings::get_dkr_version(), "\"");
    
    return "";
}

size_t figure_out_correct_config_entry_index(std::vector<size_t> &fileEntryIndices, const AssetExtractConfig &config, std::string sectionPtr, size_t dkrVersionNumber,
    std::vector<size_t> foundIndices) {
    std::string filesPtr = "/files";
    std::string sectionBuildId = config.get<std::string>(sectionPtr + "/build-id", "");
    
    while(true) {
        bool redoLoop = false;
        for(size_t i = 0; i < fileEntryIndices.size(); i++) {
            std::string filePtr = filesPtr + "/" + std::to_string(fileEntryIndices[i]);
            std::string fileDkrVersion = config.get<std::string>(filePtr + "/version", "v77"); // Either v77 (default), v79, or v80
            size_t fileVersionNumber = VERSION_TO_NUMBER[fileDkrVersion];
            std::string filename = config.get<std::string>(filePtr + "/filename", "");
            
            bool erase = false;
            
            if(fileVersionNumber > dkrVersionNumber) {
                // Don't use this file if it is from a future version of DKR.
                erase = true;
            } else if(DataHelper::vector_has(foundIndices, fileEntryIndices[i])) {
                // Don't use this file if it has been used before.
                erase = true;
            } else {
                std::string fileType = config.get<std::string>(filePtr + "/type", "Binary");
                std::string sectionType = config.get<std::string>(sectionPtr + "/default-type", "Binary");
                
                if(fileType != sectionType) {
                    // Don't use the file if it doesn't match the section's type
                    erase = true;
                } else if(fileType == "Texture") {
                    // This part is necessary, because TEX2D and TEX3D assets use the same "Texture" type.
                    std::string fileBuildId = config.get<std::string>(filePtr + "/build-id", "");
                    if(sectionBuildId == "ASSET_TEXTURES_2D" && StringHelper::has(fileBuildId, "TEX3D")) {
                        // Don't include TEX3D textures in the TEX2D section.
                        erase = true;
                    } else if(sectionBuildId == "ASSET_TEXTURES_3D" && StringHelper::has(fileBuildId, "TEX2D")) {
                        // Don't include TEX2D textures in the TEX3D section.
                        erase = true;
                    }
                }
            }
            
            if(erase) {
                fileEntryIndices.erase(fileEntryIndices.begin() + i);
                redoLoop = true; // Go through the array again just to be sure.
                i--;
            }
        }
        
        if(!redoLoop) {
            break;
        }
    }
    
    DebugHelper::assert_(fileEntryIndices.size() > 0, 
        "(figure_out_correct_config_entry_index) Uh, oh. Got rid of all the entries for ", sectionBuildId);
    
    return fileEntryIndices[0];
}

/*************************************************************************************************/

void AssetExtractor::extract_all() {
    std::string dkrVersion = GlobalSettings::get_dkr_version();
    size_t dkrVersionNumber = VERSION_TO_NUMBER[dkrVersion];
    
    // Load up the config file. (Done automatically in the constructor using GlobalSettings)
    AssetExtractConfig config;
    
    // Setup stats so that extractions can get certain information. (Mainly for file-index to build-id conversions)
    ExtractStats stats;
    
    // Get the appropriate rom, given the DKR version.
    fs::path baseromPath = get_valid_baserom(config);
    
    // Load the data from the rom.
    config.load_input_file(baseromPath);
    
    size_t numberOfSections = config.number_of_sections();
    
    // Load c context with necessary enums and structs
    CContext cContext;
    fs::path includeFolder = GlobalSettings::get_decomp_path("include_subpath", "include/");
    CEnumsHelper::load_enums_from_file(cContext, includeFolder / "enums.h");
    CEnumsHelper::load_enums_from_file(cContext, includeFolder / "object_behaviors.h");
    CStructHelper::load_structs_from_file(cContext, includeFolder / "level_object_entries.h");
    
    config.init_obj_beh_to_entry_map(cContext);
    
    const BytesView &assetsView = config.get_rom_assets_view();
    
    AssetTable mainTable(assetsView, DkrAssetTableType::FixedTable);
    
    DebugHelper::assert_(mainTable.number_of_entries() == numberOfSections,
        "(AssetExtractor::extract_all) The number of asset sections in the config does not match the rom!");
    
    size_t mainTableBytesSize = mainTable.total_size();
    
    std::vector<BytesView> sectionViews(numberOfSections);
    
    // First pass to get the views for all sections.
    for(size_t i = 0; i < numberOfSections; i++) {
        sectionViews[i] = assetsView.get_sub_view(mainTable.get_entry_offset(i) + mainTableBytesSize, mainTable.get_entry_size(i));
    }
    
    std::map<int, std::vector<ExtractInfo>> extractions;
    
    // Second pass to get the extractions.
    for(size_t i = 0; i < numberOfSections; i++) {
        std::string sectionPtr = "/sections/" + std::to_string(i);
        std::string sectionType = config.get<std::string>(sectionPtr + "/default-type", "Binary"); // Section is treated as raw binary unless you specify a type.
        
        if(sectionType == "Empty" || sectionType == "Table") {
            continue; // ignore empty and table sections for now.
        }
        
        std::string sectionBuildId = config.get<std::string>(sectionPtr + "/build-id", "");
        std::string sectionFolder = config.get<std::string>(sectionPtr + "/folder", "");
        bool sectionIsDeferred = config.get<bool>(sectionPtr + "/defer", false);
        int groupNumber = config.get<int>(sectionPtr + "/group", 0); // Defaults to group 0. Smaller group numbers get extracted first.
        
        DebugHelper::assert_(!sectionBuildId.empty(), 
            "(AssetExtractor::extract_all) Section ", i, " does NOT have a build id!");
        
        // Check if this asset section has an associated table section.
        std::optional<size_t> tableIndex = config.get_section_table_index(sectionBuildId);
        
        if(!tableIndex.has_value()) {
            // No table, so the section is a single extraction.
            std::string sectionSha1 = DataHelper::make_sha1_hash_of_bytes(sectionViews[i]);
            
            std::vector<size_t> fileIndices = config.get_file_indices_from_sha1(sectionSha1);
            
            DebugHelper::assert_(fileIndices.size() >= 1, 
                "(AssetExtractor::extract_all) Could not find a file for section ", sectionBuildId, ", sha1 = ", sectionSha1);
            
            std::string filePtr = "/files/" + std::to_string(fileIndices[0]);
            std::string filename = config.get<std::string>(filePtr + "/filename", "");
            std::string folder = config.get<std::string>(filePtr + "/folder", "");
            std::string type = config.get<std::string>(filePtr + "/type", "");
            
            std::string localPath = filename + ".json";
            
            if(!folder.empty()) {
                localPath = folder + "/" + localPath;
            }
            
            if(!sectionFolder.empty()) {
                folder = sectionFolder + "/" + folder;
            }
            
            if(type.empty()) {
                type = sectionType;
            }
            
            if(extractions.find(groupNumber) == extractions.end()) {
                extractions[groupNumber] = std::vector<ExtractInfo>();
                extractions[groupNumber].reserve(8192); // Arbitrary allocation amount, trying to prevent many reallocations. Size is about ~2.5 MB per group.
            }
            
            if(sectionIsDeferred) {
                DeferredExtractions::add_extraction(sectionBuildId, 
                    ExtractInfo(type, sectionBuildId, filename, folder, sectionViews[i], config, sectionPtr, cContext, 0, stats));
            } else if(type != "NoExtract") {
                extractions[groupNumber].emplace_back(type, sectionBuildId, filename, folder, 
                    sectionViews[i], config, sectionPtr, cContext, 0, stats);
            }
            
            fs::path outputJsonPath = (GlobalSettings::get_decomp_path_to_vanilla_assets() / folder) / (filename + ".json");
            
            // Add info to stats
            stats.add_info(sectionBuildId, { sectionBuildId, outputJsonPath, localPath });
            
            continue;
        }
        
        // Has a table, so multiple files need to be extracted.
        std::string tableSectionPtr = "/sections/" + std::to_string(tableIndex.value());
        std::string tableBuildId = config.get<std::string>(tableSectionPtr + "/build-id", "");
        //DebugHelper::info(sectionBuildId, " table is ", tableBuildId);
        DkrAssetTableType tableType = AssetTable::table_type_from_section_type(sectionType);
        AssetTable sectionTable(sectionViews[tableIndex.value()], tableType);
        size_t numberOfEntriesInTable = sectionTable.number_of_entries();
        std::vector<size_t> foundIndices;
        
        if(sectionBuildId == "ASSET_MENU_TEXT") {
            stats.set_tag("menuTextCount", sectionViews[tableIndex.value()].get_s32_be(0));
        }
        
        for(size_t entryIndex = 0; entryIndex < numberOfEntriesInTable; entryIndex++) {
            size_t entryOffset = sectionTable.get_entry_offset(entryIndex) & 0x7FFFFFFF; // GameText uses highest bit to determine if dialog or textbox.
            size_t entrySize = sectionTable.get_entry_size(entryIndex);
            
            BytesView fileView = sectionViews[i].get_sub_view(entryOffset, entrySize);
            std::string fileViewSha1 = DataHelper::make_sha1_hash_of_bytes(fileView);
            
            std::vector<size_t> fileEntryIndices = config.get_file_indices_from_sha1(fileViewSha1);
            
            DebugHelper::assert_(fileEntryIndices.size() > 0,
                "(AssetExtractor::extract_all) Could not find a file for entry ", entryIndex, " for section ", sectionBuildId, "; The hash was ", fileViewSha1);
            
            size_t fileEntryIndexValue;

            if(fileEntryIndices.size() == 1) {
                fileEntryIndexValue = fileEntryIndices[0];
            } else {
                //DebugHelper::info("Finding file entry for index ", entryIndex, " for section ", sectionBuildId, "; The hash was ", fileViewSha1);
                // fileEntryIndices.size() is greater than 1, gotta pick the correct file.
                fileEntryIndexValue = figure_out_correct_config_entry_index(fileEntryIndices, config, sectionPtr, dkrVersionNumber, foundIndices);
            }
    
            foundIndices.emplace_back(fileEntryIndexValue);
            
            std::string filePtr = "/files/" + std::to_string(fileEntryIndexValue);
            std::string filename = config.get<std::string>(filePtr + "/filename", "");
            std::string fileBuildId = config.get<std::string>(filePtr + "/build-id", "");
            std::string folder = config.get<std::string>(filePtr + "/folder", "");
            std::string type = config.get<std::string>(filePtr + "/type", "");
            
            std::string localPath = filename + ".json";
            
            if(!folder.empty()) {
                localPath = folder + "/" + localPath;
            }
            
            if(!sectionFolder.empty()) {
                folder = sectionFolder + "/" + folder;
            }
            
            if(sectionIsDeferred) {
                DeferredExtractions::add_extraction(sectionBuildId, 
                    ExtractInfo(type, fileBuildId, filename, folder, fileView, config, sectionPtr, cContext, entryIndex, stats));
            } else {
                extractions[groupNumber].emplace_back(type, fileBuildId, filename, folder, 
                    fileView, config, sectionPtr, cContext, entryIndex, stats);
                if(type == "GameText") {
                    bool isDialog = sectionTable.get_entry_offset(entryIndex) & 0x80000000;
                    extractions[groupNumber].back().set_tag("isDialog", std::any(isDialog));
                }
                
            }
            
            fs::path outputJsonPath = (GlobalSettings::get_decomp_path_to_vanilla_assets() / folder) / (filename + ".json");
            
            // Add info to stats
            stats.add_info(sectionBuildId, { fileBuildId, outputJsonPath, localPath });
        }
    }
    
    generate_main_json_file(config, stats);
     
    size_t threadCount = GlobalSettings::get_max_thread_count();
    bool multithreaded = threadCount != 1;
    DebugHelper::info_verbose("Using ", threadCount, " thread", (multithreaded ? "s" : ""));
    
    // Run the extraction!
    // extractions should be sorted by the group number.
    for (auto &pair : extractions) {
        std::vector<ExtractInfo> &extracts = pair.second;
        bool errorOccured = false;
        if(multithreaded) {
            // Multi-threaded version (better for performance)
            std::exception_ptr ex;
            {
                ThreadPool pool(threadCount);
                for(ExtractInfo &info : extracts) {
                    std::string type = info.get_type();
                    // Check to make sure the builderMap has the given type.
                    if(EXTRACTOR_MAP.find(type) == EXTRACTOR_MAP.end()) {
                        DebugHelper::warn("The input type \"", type, "\" is currently not implemented. Extracting as a raw binary file instead.");
                        EXTRACTOR_MAP["Binary"]((ExtractInfo &)info);
                        continue;
                    }
                    pool.enqueue([type, &info = info, &errorOccured = errorOccured, &ex = ex] {
                        if(errorOccured) {
                            return;
                        }
                        // Call the class constructor of a type.
                        try {
                            EXTRACTOR_MAP[type]((ExtractInfo &)info);
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
            // ThreadPool's destructor will join the threads.
            if(errorOccured) {
                std::rethrow_exception(ex);
            }
        } else {
            // Single-threaded version (better for debugging)
            for(ExtractInfo &info : extracts) {
                std::string type = info.get_type();
                // Check to make sure the builderMap has the given type.
                if(EXTRACTOR_MAP.find(type) == EXTRACTOR_MAP.end()) {
                    DebugHelper::warn("The input type \"", type, "\" is currently not implemented. Extracting as a raw binary file instead.");
                    EXTRACTOR_MAP["Binary"]((ExtractInfo &)info);
                    continue;
                }
                EXTRACTOR_MAP[type]((ExtractInfo &)info);
            }
        }
    }
}

/*************************************************************************************************/

void AssetExtractor::extract(const fs::path &srcPath, const fs::path &dstPath) {
    DebugHelper::error("TODO: Single file extract is currently not implemented.");
}
