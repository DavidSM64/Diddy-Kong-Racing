#pragma once

#include <optional>

#include "helpers/fileHelper.h"

#include "builder/buildInfo.h"

#include "fileTypes/textureInfo.hpp"

namespace DkrAssetsTool {

class BuildModelMaterial {
public:
    BuildModelMaterial();
    BuildModelMaterial(fs::path texturePath); // Path to texture.
    
    void write_to(DkrTextureInfo *outTexInfo, BuildInfo &info);
    
    std::optional<fs::path> get_texture_path();
    bool has_texture() const;
    bool is_texture_animated();
    bool is_texture_double_sided();
    
    void get_texture_width_and_height(int &outWidth, int &outHeight);
    
private:
    std::optional<fs::path> _texturePath;
    std::optional<bool> _isTextureAnimated = std::nullopt;
    std::optional<bool> _isTextureDoubleSided = std::nullopt;
};

}
