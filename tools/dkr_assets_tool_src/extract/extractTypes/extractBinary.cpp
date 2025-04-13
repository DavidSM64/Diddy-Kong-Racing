#include "extractBinary.h"

using namespace DkrAssetsTool;

ExtractBinary::ExtractBinary(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    if(_info.is_asset()) {
        _extract_as_asset();
    } else {
        _extract_as_code();
    }
}
ExtractBinary::~ExtractBinary() {
}

void ExtractBinary::_extract_as_asset() {
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Asset Binary", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_path("/raw", _info.get_filename(".bin"));
    jsonFile.set_string("/type", "Binary");
    
    jsonFile.save();
    
    _info.write_rom_data_to_file(_outRawFilepath);
}

void ExtractBinary::_extract_as_code() {
    fs::path _outFilepath = _settings.pathToRepo / _info.get_out_filepath(".bin");
    DebugHelper::info_custom("Extracting Code Binary", YELLOW_TEXT, _outFilepath);
    _info.write_rom_data_to_file(_outFilepath);
}
