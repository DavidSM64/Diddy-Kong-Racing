#include "builder.h"

using namespace DkrAssetsTool;

#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

#include "builder/buildInfo.h"

#include "buildTypes/buildAudio.h"
#include "buildTypes/buildBinary.h"
#include "buildTypes/buildTexture.h"
#include "buildTypes/buildFonts.h"
#include "buildTypes/buildGameText.h"
#include "buildTypes/buildLevelModel.h"
#include "buildTypes/buildLevelHeader.h"
#include "buildTypes/buildLevelObjectTranslationTable.h"
#include "buildTypes/buildMenuText.h"
#include "buildTypes/buildObjectAnimation.h"
#include "buildTypes/buildObjectHeader.h"
#include "buildTypes/buildObjectMap.h"
#include "buildTypes/buildObjectModel.h"
#include "buildTypes/buildParticle.h"
#include "buildTypes/buildParticleBehavior.h"
#include "buildTypes/buildSprite.h"
#include "buildTypes/buildTTGhost.h"
#include "buildTypes/buildMisc.h"

// Hope this doesn't cause too much cringe.
#define BUILDER_ARGS DkrAssetsSettings &settings, BuildInfo &info
#define BUILDER_LAMDA(classConstructorCode) [](BUILDER_ARGS) { classConstructorCode(settings, info); }

typedef std::function<void(BUILDER_ARGS)> BuilderFunction;

// Put build class constructors here with the type in the JSON file!
std::unordered_map<std::string, BuilderFunction> builderMap = {
    {                      "Binary", BUILDER_LAMDA(BuildBinary)           },
    {                       "Fonts", BUILDER_LAMDA(BuildFonts)            },
    { "LevelObjectTranslationTable", BUILDER_LAMDA(BuildLOTT)             },
    {                     "Texture", BUILDER_LAMDA(BuildTexture)          },
    {              "LevelObjectMap", BUILDER_LAMDA(BuildObjectMap)        },
    {                  "LevelModel", BUILDER_LAMDA(BuildLevelModel)       },
    {                 "LevelHeader", BUILDER_LAMDA(BuildLevelHeader)      },
    {                "ObjectHeader", BUILDER_LAMDA(BuildObjectHeader)     },
    {                 "ObjectModel", BUILDER_LAMDA(BuildObjectModel)      },
    {             "ObjectAnimation", BUILDER_LAMDA(BuildObjectAnimation)  },
    {                     "TTGhost", BUILDER_LAMDA(BuildTTGhost)          },
    {                    "GameText", BUILDER_LAMDA(BuildGameText)         },
    {                    "MenuText", BUILDER_LAMDA(BuildMenuText)         },
    {               "Miscellaneous", BUILDER_LAMDA(BuildMisc)             },
    {                      "Sprite", BUILDER_LAMDA(BuildSprite)           },
    {                       "Audio", BUILDER_LAMDA(BuildAudio)            },
    {                    "Particle", BUILDER_LAMDA(BuildParticle)         },
    {            "ParticleBehavior", BUILDER_LAMDA(BuildParticleBehavior) },
};

// Build all assets.
DkrAssetBuilder::DkrAssetBuilder(DkrAssetsSettings &settings, const fs::path &dstPath) {
    settings.pathToAssets /= settings.dkrVersion + "/";
    
    size_t bufferSize = 10 * 1024 * 1024; // 10 MB for testing purposes.
    std::shared_ptr<uint8_t[]> outAssetsBinary(new uint8_t[bufferSize], std::default_delete<uint8_t[]>());
    
    size_t outAssetsAllocatedSize = 0;
    
    JsonFile *mainJson = AssetsHelper::get().get_main_json(settings);
    
    DebugHelper::assert_(mainJson != nullptr, "(DkrAssetBuilder::DkrAssetBuilder) Could not get the main assets json file!");
    
    DebugHelper::info("Number of asset sections = ", mainJson->length_of_array("/assets/order"));
    
    // TODO: FINISH ME!
    
    FileHelper::write_binary_file(outAssetsBinary.get(), outAssetsAllocatedSize, dstPath, true);
}

DkrAssetBuilder::DkrAssetBuilder(DkrAssetsSettings &settings, const fs::path &srcPath, const fs::path &dstPath) {
    settings.pathToAssets /= settings.dkrVersion + "/";
    
    // Make sure the input file is a JSON file.
    DebugHelper::assert_(StringHelper::ends_with(srcPath, ".json"), "(DkrAssetBuilder::DkrAssetBuilder) Input file is not a JSON file! Input file = \"", srcPath, "\"");
    
    JsonFile *jsonFile;
    
    // Get the file, and throw an error if it doesn't exist.
    DebugHelper::assert_(JsonHelper::get().get_file(srcPath, &jsonFile), "(DkrAssetBuilder::DkrAssetBuilder) Could not find input file \"", srcPath, "\"");
    
    fs::path localDirectory = FileHelper::get_directory(srcPath);
    
    BuildInfo info(jsonFile, dstPath, localDirectory);
    
    // Make sure the json file has the "type" key.
    DebugHelper::assert_(jsonFile->has("/type"), "(DkrAssetBuilder::DkrAssetBuilder) Input JSON file does not have a \"type\"! Input file = \"", srcPath, "\"");
    
    std::string type = jsonFile->get_string("/type");
    
    // Check to make sure the builderMap has the given type.
    if(builderMap.find(type) == builderMap.end()) {
        // For now this is a warning, but maybe make it an error instead?
        DebugHelper::warn("The input type \"", type, "\" is currently not implemented.");
        return;
    }
    
    // Call the class constructor of a type.
    builderMap[type](settings, info);
}

DkrAssetBuilder::~DkrAssetBuilder() {
}
