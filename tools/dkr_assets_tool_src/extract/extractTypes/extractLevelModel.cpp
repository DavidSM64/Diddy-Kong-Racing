#include "extractLevelModel.h"

using namespace DkrAssetsTool;

#include <vector>
#include <string>

#include "helpers/debugHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/c/cContext.h"

ExtractLevelModel::ExtractLevelModel(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Level Model", YELLOW_TEXT, _outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "LevelModel");
    
    std::string _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    jsonFile.set_path("/raw", _info.get_filename(".bin"));
    _info.write_rom_data_to_file(_outRawFilepath);
    
    jsonFile.save();
}

ExtractLevelModel::~ExtractLevelModel() {
}
