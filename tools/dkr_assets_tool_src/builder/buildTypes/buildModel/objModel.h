#pragma once

#include "helpers/fileHelper.h"

#include "buildModel.h"

namespace DkrAssetsTool {

class ObjBuildModel : public BuildModel {
public:
    ObjBuildModel(fs::path filepath, DkrAssetsSettings &settings);
private:

};

}