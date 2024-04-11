#include "extractParticleBehavior.h"

#include "helpers/jsonHelper.h"

ExtractParticleBehavior::ExtractParticleBehavior(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Particle Behavior", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_path("/raw", _info.get_filename(".bin"));
    jsonFile.set_string("/type", "ParticleBehavior");
    
    jsonFile.save();
    
    _info.write_rom_data_to_file(_outRawFilepath);
}

ExtractParticleBehavior::~ExtractParticleBehavior() {
}
