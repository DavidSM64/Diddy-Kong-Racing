#include "extractLevelModel.h"

#include "helpers/debugHelper.h"
#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractLevelModel::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Level Model", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "LevelModel");
    jsonFile.set_path("/raw", info.get_filename(".bin"));
    
    info.write_json_file();
    info.write_raw_data_file();
}
