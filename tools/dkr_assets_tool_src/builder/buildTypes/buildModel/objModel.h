#pragma once

#include "helpers/fileHelper.h"

#include "buildModel.h"

namespace DkrAssetsTool {

class ObjBuildModel : public BuildModel {
public:
    ObjBuildModel(fs::path filepath);
private:
    Vec2f _get_adjusted_uv(Vec2f uv, std::string materialId);
    void _parse_mtllib(fs::path pathToLib);
};

}