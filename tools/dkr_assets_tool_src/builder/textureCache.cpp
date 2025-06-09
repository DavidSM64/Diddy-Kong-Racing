#include "textureCache.h"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

std::optional<size_t> BuildTextureCache::get_index_of_texture_hash(std::string textureSha1) {
    _mutex.lock();
    if(_textureCache.find(textureSha1) == _textureCache.end()) {
        _mutex.unlock();
        return std::nullopt;
    }
    size_t result = _textureCache.at(textureSha1);
    _mutex.unlock();
    return result;
}

void BuildTextureCache::add_texture_to_sha1_cache(std::string textureSha1, size_t index) {
    _mutex.lock();
    if(_textureCache.find(textureSha1) != _textureCache.end()) {
        _mutex.unlock();
        return; // If an entry already exists, then exit early to not overwrite it.
    }
    _textureCache[textureSha1] = index;
    _mutex.unlock();
}
