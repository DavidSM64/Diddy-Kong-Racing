#include "extractParticleBehavior.h"

#include "helpers/jsonHelper.h"

using namespace DkrAssetsTool;

void ExtractParticleBehavior::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Particle Behavior", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_path("/raw", info.get_filename(".bin"));
    jsonFile.set_string("/type", "ParticleBehavior");
    
    info.write_json_file();
    info.write_raw_data_file();
}
