#include "builder.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

#include "helpers/assetsHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

#include "misc/globalSettings.h"

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

using namespace DkrAssetsTool;

// Hope this doesn't cause too much cringe.
#define BUILDER_ARGS BuildInfo &info
#define BUILDER_LAMDA(classConstructorCode) [](BUILDER_ARGS) { classConstructorCode(info); }

typedef std::function<void(BUILDER_ARGS)> BuilderFunction;

std::unordered_map<std::string, BuilderFunction> builderMap = {
    {                      "Binary", BUILDER_LAMDA(BuildBinary::build)           },
    {                       "Fonts", BUILDER_LAMDA(BuildFonts::build)            },
    { "LevelObjectTranslationTable", BUILDER_LAMDA(BuildLOTT::build)             },
    {                     "Texture", BUILDER_LAMDA(BuildTexture::build)          },
    {              "LevelObjectMap", BUILDER_LAMDA(BuildObjectMap::build)        },
    {                  "LevelModel", BUILDER_LAMDA(BuildLevelModel::build)       },
    {                 "LevelHeader", BUILDER_LAMDA(BuildLevelHeader::build)      },
    {                "ObjectHeader", BUILDER_LAMDA(BuildObjectHeader::build)     },
    {                 "ObjectModel", BUILDER_LAMDA(BuildObjectModel::build)      },
    {             "ObjectAnimation", BUILDER_LAMDA(BuildObjectAnimation::build)  },
    {                     "TTGhost", BUILDER_LAMDA(BuildTTGhost::build)          },
    {                    "GameText", BUILDER_LAMDA(BuildGameText::build)         },
    {                    "MenuText", BUILDER_LAMDA(BuildMenuText::build)         },
    {               "Miscellaneous", BUILDER_LAMDA(BuildMisc::build)             },
    {                      "Sprite", BUILDER_LAMDA(BuildSprite::build)           },
    {                       "Audio", BUILDER_LAMDA(BuildAudio::build)            },
    {                    "Particle", BUILDER_LAMDA(BuildParticle::build)         },
    {            "ParticleBehavior", BUILDER_LAMDA(BuildParticleBehavior::build) },
};

// Build all assets.
void AssetBuilder::build_all(const fs::path &dstPath) {
    //settings.pathToAssets /= GlobalSettings::get_value<std::string>("dkr_version", "us_1.0") + "/";
    
    size_t bufferSize = 10 * 1024 * 1024; // 10 MB for testing purposes.
    std::shared_ptr<uint8_t[]> outAssetsBinary(new uint8_t[bufferSize], std::default_delete<uint8_t[]>());
    
    size_t outAssetsAllocatedSize = 0;
    
    JsonFile &mainJson = AssetsHelper::get_main_json();
    
    DebugHelper::info("Number of asset sections = ", mainJson.length_of_array("/assets/order"));
    
    // TODO: FINISH ME!
    
    FileHelper::write_binary_file(outAssetsBinary.get(), outAssetsAllocatedSize, dstPath, true);
}

void AssetBuilder::build(const fs::path &srcPath, const fs::path &dstPath) {
    //settings.pathToAssets /= GlobalSettings::get_value<std::string>("dkr_version", "us_1.0") + "/";
    
    // Make sure the input file is a JSON file.
    DebugHelper::assert_(StringHelper::ends_with(srcPath, ".json"), "(DkrAssetBuilder::DkrAssetBuilder) Input file is not a JSON file! Input file = \"", srcPath, "\"");
    
    
    auto tryGetJsonFile = JsonHelper::get_file(srcPath);
    
    // Get the file, and throw an error if it doesn't exist.
    DebugHelper::assert_(tryGetJsonFile.has_value(), "(DkrAssetBuilder::DkrAssetBuilder) Could not find input file \"", srcPath, "\"");
    
    JsonFile &jsonFile = tryGetJsonFile.value();
    
    fs::path localDirectory = FileHelper::get_directory(srcPath);
    
    BuildInfo info(&jsonFile, dstPath, localDirectory);
    
    // Make sure the json file has the "type" key.
    DebugHelper::assert_(jsonFile.has("/type"), "(DkrAssetBuilder::DkrAssetBuilder) Input JSON file does not have a \"type\"! Input file = \"", srcPath, "\"");
    
    std::string type = jsonFile.get_string("/type");
    
    // Check to make sure the builderMap has the given type.
    if(builderMap.find(type) == builderMap.end()) {
        // For now this is a warning, but maybe make it an error instead?
        DebugHelper::warn("The input type \"", type, "\" is currently not implemented.");
        return;
    }
    
    // Call the class constructor of a type.
    builderMap[type](info);
}
