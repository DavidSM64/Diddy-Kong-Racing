#include "extractObjectModel.h"

using namespace DkrAssetsTool;

#include "helpers/jsonHelper.h"

ExtractObjectModel::ExtractObjectModel(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Object Model", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_path("/raw", _info.get_filename(".bin"));
    jsonFile.set_string("/type", "ObjectModel");
    
    jsonFile.save();
    
    _info.write_rom_data_to_file(_outRawFilepath);
}

ExtractObjectModel::~ExtractObjectModel() {
}
