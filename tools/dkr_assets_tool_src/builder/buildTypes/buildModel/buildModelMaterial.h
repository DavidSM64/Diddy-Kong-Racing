#pragma once

#include <optional>

#include "helpers/fileHelper.h"

#include "builder/buildInfo.h"

#include "builder/buildTypes/buildTexture.h" // for DeferredTextureInfo

#include "fileTypes/textureInfo.hpp"

namespace DkrAssetsTool {

class BuildModelMaterial {
public:
    BuildModelMaterial();
    BuildModelMaterial(fs::path texturePath, std::string name); // Path to texture.
    BuildModelMaterial(uint8_t *imgData, size_t imgDataLength, std::string mimeType, std::string name); // Embedded texture
    
    void write_to(DkrTextureInfo *outTexInfo, BuildInfo &info);
    
    std::optional<fs::path> get_texture_path();
    bool has_texture() const;
    bool is_texture_animated();
    bool is_texture_double_sided();
    
    bool is_embedded() const;
    std::optional<uint8_t*> get_embedded_data(size_t &outLength, std::string &outMimeType) const;
    
    std::string get_name() const;
    
    void get_texture_width_and_height(int &outWidth, int &outHeight);
    
    void set_wrap_mode(std::string wrapS, std::string wrapT);
    void set_format(std::string format);
    void set_rendermode(std::string renderMode);
    void set_flip_vertically(bool shouldFlipVertically);
    void set_double_sided(bool doubleSided);
    
    void set_flag(uint32_t flag);
    bool has_render_flags() const;
    uint32_t get_render_flags() const;
    
private:
    uint32_t _renderFlags = 0;
    BuildTexture::DeferredTextureInfo _buildTextureInfo;
    std::optional<uint8_t*> _imgData = std::nullopt;
    size_t _imgDataLength = 0;
    std::string _mimeType = "";
    std::optional<fs::path> _texturePath = std::nullopt;
    std::optional<bool> _isTextureAnimated = std::nullopt;
    std::optional<bool> _isTextureDoubleSided = std::nullopt;
    std::string _name;
};

}
