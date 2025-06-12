#include "buildModelMaterial.h"

#include "helpers/debugHelper.h"
#include "helpers/imageHelper.h"

#include "libs/bytes_view.hpp"

#include "builder/buildTypes/buildTexture.h"

using namespace DkrAssetsTool;

BuildModelMaterial::BuildModelMaterial() : _texturePath(std::nullopt), _name("") {
}

BuildModelMaterial::BuildModelMaterial(fs::path texturePath, std::string name) : _texturePath(texturePath), _name(name) {
}

BuildModelMaterial::BuildModelMaterial(uint8_t *imgData, size_t imgDataLength, std::string mimeType, std::string name) : 
    _imgData(imgData), _imgDataLength(imgDataLength), _mimeType(mimeType), _name(name) {}
    
void BuildModelMaterial::write_to(DkrTextureInfo *outTexInfo, BuildInfo &info) {
    int width, height;
    get_texture_width_and_height(width, height);
    
    DebugHelper::assert_((width > 0) && (width < 255), 
        "(BuildModelMaterial::write_to) Invalid width of ", width, " for material \"", _name, "\"");
    
    DebugHelper::assert_((height > 0) && (height < 255), 
        "(BuildModelMaterial::write_to) Invalid height of ", height, " for material \"", _name, "\"");
    
    outTexInfo->width = width;
    outTexInfo->height = height;
    outTexInfo->format = 0x11; // 0x11 = Opaque RGBA16 texture. Might not be used in-game?
    if(is_embedded()) {
        outTexInfo->id = BuildTexture::build_deferred(info, _imgData.value(), _imgDataLength, _mimeType, _name, _buildTextureInfo);
    } else {
        outTexInfo->id = BuildTexture::build_deferred(info, _texturePath.value(), _buildTextureInfo);
    }
}

bool BuildModelMaterial::has_texture() const {
    return _texturePath.has_value() || _imgData.has_value();
}

bool BuildModelMaterial::is_texture_animated() {
    if(!_texturePath.has_value()) {
        return false;
    }
    if(!_isTextureAnimated.has_value()) {
        _isTextureAnimated = ImageHelper::guess_if_texture_is_animated(_texturePath.value());
    }
    return _isTextureAnimated.value();
}

bool BuildModelMaterial::is_texture_double_sided() {
    if(!_isTextureDoubleSided.has_value()) {
        if(!_texturePath.has_value()) {
            return false;
        }
        _isTextureDoubleSided = ImageHelper::guess_if_texture_double_sided(_texturePath.value());
    }
    return _isTextureDoubleSided.value();
}

bool BuildModelMaterial::is_embedded() const {
    return _imgData.has_value();
}

std::optional<uint8_t*> BuildModelMaterial::get_embedded_data(size_t &outLength, std::string &outMimeType) const {
    if(!_imgData.has_value()) {
        outLength = 0;
        outMimeType = "";
        return std::nullopt;
    }
    outLength = _imgDataLength;
    outMimeType = _mimeType;
    return _imgData;
}

std::string BuildModelMaterial::get_name() const {
    return _name;
}
    
void BuildModelMaterial::get_texture_width_and_height(int &outWidth, int &outHeight) {
    if(is_embedded()) {
        DebugHelper::assert_(_mimeType == "image/png",
            "(BuildModelMaterial::get_texture_width_and_height) Sorry, only embedded png images are supported at the moment!");
        bool isPngData = (_imgData.value()[1] == 'P') && (_imgData.value()[2] == 'N') && (_imgData.value()[3] == 'G');
        DebugHelper::assert_(isPngData,
            "(BuildModelMaterial::get_texture_width_and_height) embedded image data for material ", _name, " was NOT a .png image.");
        
        // Only need to see the two u32s at offsets 0x10 and 0x14 in the png data.
        std::vector<uint8_t> imgDataAsVector(_imgData.value() + 0x10, _imgData.value() + 0x18);
        BytesView view(imgDataAsVector);
        outWidth = view.get_u32_be(0);
        outHeight = view.get_u32_be(4);
        return;
    }
    
    if(!_texturePath.has_value()) {
        outWidth = 0;
        outHeight = 0;
        return;
    }
    
    ImageHelper::get_width_and_height(_texturePath.value(), outWidth, outHeight);
}
    
void BuildModelMaterial::set_wrap_mode(std::string wrapS, std::string wrapT) {
    _buildTextureInfo.wrapS = wrapS;
    _buildTextureInfo.wrapT = wrapT;
}

void BuildModelMaterial::set_format(std::string format) {
    _buildTextureInfo.format = format;
}

void BuildModelMaterial::set_rendermode(std::string renderMode) {
    _buildTextureInfo.renderMode = renderMode;
}

void BuildModelMaterial::set_flip_vertically(bool shouldFlipVertically) {
    _buildTextureInfo.shouldFlip = shouldFlipVertically;
}

void BuildModelMaterial::set_double_sided(bool doubleSided) {
    _isTextureDoubleSided = doubleSided;
}

void BuildModelMaterial::set_flag(uint32_t flag) {
    _renderFlags |= flag;
}

bool BuildModelMaterial::has_render_flags() const {
    return _renderFlags != 0;
}

uint32_t BuildModelMaterial::get_render_flags() const {
    return _renderFlags;
}
