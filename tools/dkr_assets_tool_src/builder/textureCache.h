#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <mutex>

namespace DkrAssetsTool {

class BuildTextureCache {
public:
    // Used in custom models to see if a texture already exists or not. Retruns std::nullopt if the texture does not exist.
    std::optional<std::string> get_build_id_of_texture_hash(std::string textureSha1);
    
    // Note: Will not overwrite a existing id if one already exists.
    void add_texture_to_sha1_cache(std::string textureSha1, std::string buildId);
    
private:
    // Key: sha1 hash of a image, Value: Build id of that image.
    std::unordered_map<std::string, std::string> _textureCache;
    
    std::mutex _mutex;
};

}