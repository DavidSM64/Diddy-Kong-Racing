#include "extractAudio.h"

#include "helpers/jsonHelper.h"

ExtractAudio::ExtractAudio(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Audio", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    
    jsonFile.set_string("/type", "Audio");
    
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    
    if(_info.get_data_size() == 0) { // File 12 is empty for some reason. ¯\_(ツ)_/¯
        jsonFile.set_null("/raw");
    } else {
        jsonFile.set_path("/raw", _info.get_filename(".bin"));
        _info.write_rom_data_to_file(_outRawFilepath);
    }
    
    
    jsonFile.save();
    
}

ExtractAudio::~ExtractAudio() {
}
