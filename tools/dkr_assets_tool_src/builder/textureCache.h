#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <mutex>

namespace DkrAssetsTool {

class BuildTextureCache {
public:
    // Used in custom models to see if a texture already exists or not. Retruns std::nullopt if the texture does not exist.
    std::optional<size_t> get_index_of_texture_hash(std::string textureSha1);
    
    // Note: Will not overwrite a existing id if one already exists.
    void add_texture_to_sha1_cache(std::string textureSha1, size_t index);
    
private:
    // Key: sha1 hash of a image, Value: index of that texture in the ASSETS_TEXTURES_3D section.
    std::unordered_map<std::string, size_t> _textureCache;
    
    std::mutex _mutex;
};

}