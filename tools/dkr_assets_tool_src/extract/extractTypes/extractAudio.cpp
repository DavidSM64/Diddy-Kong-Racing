#include "extractAudio.h"

#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractAudio::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Audio", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    jsonFile.set_string("/type", "Audio");
    
    if(info.get_data_size() == 0) { // File 12 is empty for some reason. ¯\_(ツ)_/¯
        jsonFile.set_null("/raw");
    } else {
        jsonFile.set_path("/raw", info.get_filename(".bin"));
        info.write_raw_data_file();
    }
    
    info.write_json_file();
}
