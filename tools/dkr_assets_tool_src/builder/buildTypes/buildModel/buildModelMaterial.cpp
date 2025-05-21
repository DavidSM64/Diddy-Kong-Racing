#include "buildModelMaterial.h"

#include "helpers/debugHelper.h"
#include "helpers/imageHelper.h"

#include "builder/buildTypes/buildTexture.h"

using namespace DkrAssetsTool;

BuildModelMaterial::BuildModelMaterial() : _texturePath(std::nullopt) {
}

BuildModelMaterial::BuildModelMaterial(fs::path texturePath) : _texturePath(texturePath) {
}
    
void BuildModelMaterial::write_to(DkrTextureInfo *outTexInfo, BuildInfo &info) {
    DebugHelper::assert_(has_texture(), 
        "(BuildModelMaterial::write_to) Trying to write out to a DkrTextureInfo without a texture!");
        
    int width, height;
    
    ImageHelper::get_width_and_height(_texturePath.value(), width, height);
    
    DebugHelper::assert_((width > 0) && (width < 255), 
        "(BuildModelMaterial::write_to) Invalid width of ", width, " for texture ", _texturePath.value().filename());
    
    DebugHelper::assert_((height > 0) && (height < 255), 
        "(BuildModelMaterial::write_to) Invalid height of ", height, " for texture ", _texturePath.value().filename());
    
    outTexInfo->width = width;
    outTexInfo->height = height;
    outTexInfo->format = 0x11; // 0x11 = Opaque RGBA16 texture. TODO: Add support for more formats!
    outTexInfo->id = BuildTexture::build_deferred(info, _texturePath.value());
}

bool BuildModelMaterial::has_texture() const {
    return _texturePath.has_value();
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
    if(!_texturePath.has_value()) {
        return false;
    }
    if(!_isTextureDoubleSided.has_value()) {
        _isTextureDoubleSided = ImageHelper::guess_if_texture_double_sided(_texturePath.value());
    }
    return _isTextureDoubleSided.value();
}
    
void BuildModelMaterial::get_texture_width_and_height(int &outWidth, int &outHeight) {
    if(!_texturePath.has_value()) {
        outWidth = 0;
        outHeight = 0;
        return;
    }
    
    ImageHelper::get_width_and_height(_texturePath.value(), outWidth, outHeight);
}
