#include "textureCache.h"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

std::optional<std::string> BuildTextureCache::get_build_id_of_texture_hash(std::string textureSha1) {
    _mutex.lock();
    if(_textureCache.find(textureSha1) == _textureCache.end()) {
        _mutex.unlock();
        return std::nullopt;
    }
    std::string result = _textureCache.at(textureSha1);
    _mutex.unlock();
    return result;
}

void BuildTextureCache::add_texture_to_sha1_cache(std::string textureSha1, std::string buildId) {
    _mutex.lock();
    if(_textureCache.find(textureSha1) != _textureCache.end()) {
        _mutex.unlock();
        return; // If an entry already exists, then exit early to not overwrite it.
    }
    _textureCache[textureSha1] = buildId;
    _mutex.unlock();
}
