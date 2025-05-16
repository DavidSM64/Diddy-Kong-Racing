#include "extractParticle.h"

#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractParticle::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Particle", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_path("/raw", info.get_filename(".bin"));
    jsonFile.set_string("/type", "Particle");
    
    info.write_json_file();
    info.write_raw_data_file();
}
