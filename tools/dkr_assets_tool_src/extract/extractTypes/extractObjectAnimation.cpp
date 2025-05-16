#include "extractObjectAnimation.h"

#include "helpers/assetsHelper.h"
#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractObjectAnimation::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Object Animation", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_path("/raw", info.get_filename(".bin"));
    jsonFile.set_string("/type", "ObjectAnimation");
    
    ExtractInfo &objectAnimationIds = DeferredExtractions::get_extraction("ASSET_ANIMATION_IDS", 0);
    
    const BytesView &idsView = objectAnimationIds.get_view();
    size_t fileIndex = info.get_file_index();
    
    size_t modelIndex = 0;
    while(modelIndex < (idsView.size() / 2) - 1) {
        int16_t value = idsView.get_s16_be(modelIndex*2);
        int16_t nextValue = idsView.get_s16_be(modelIndex*2 + 2);
        if((fileIndex >= value) && (fileIndex < nextValue)) {
            // Found the correct modelIndex.
            break;
        }
        modelIndex++;
    }
    
    std::string forModel = AssetsHelper::get_build_id_of_index("ASSET_OBJECT_MODELS", modelIndex);
    
    jsonFile.set_string("/for-model", forModel);
    
    info.write_json_file();
    info.write_raw_data_file();
}
