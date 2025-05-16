#include "imageHelper.h"

using namespace DkrAssetsTool;

#include <cstring> // for memcpy
#include <algorithm>
#include <unordered_map>

#include "fileHelper.h"
#include "debugHelper.h"
#include "libs/n64graphics/n64graphics.h"
#include "libs/stb_image.h"
#include "helpers/dataHelper.h"

N64Image::N64Image(fs::path filepath, std::string format, bool alignData) : _format(format) {
    bool isColourImage = (format == "RGBA16") || (format == "RGBA32") || (format == "CI4") || (format == "CI8");
    
    DebugHelper::assert(StringHelper::ends_with(filepath, ".png"), 
        "Only .png images are supported! Invalid image path: ", filepath);

    void *imgData; // Can be either rgba* or ia* n64graphics types.
    
    // Load image from a .png file, getting the width and height as well.
    if(isColourImage) {
        imgData = (void *)png2rgba(filepath.c_str(), &_width, &_height);
    } else {
        imgData = (void *)png2ia(filepath.c_str(), &_width, &_height);
    }
    
    DebugHelper::assert(imgData != nullptr, "(N64Image::N64Image) Could not load image: ", filepath);
    
    size_t size = ImageHelper::image_size(_width, _height, _format);
    
    if(alignData) {
        size = DataHelper::align16(size);
    }
    
    // Make sure the internal data buffer is large enough.
    _data.resize(size);
    
    // Convert n64graphics data type to _data. 
    if(isColourImage) {
        rgba2raw(&_data[0], (rgba*)imgData, _width, _height, get_bit_depth());
    } else if(format == "I4" || format == "I8") {
        i2raw(&_data[0], (ia*)imgData, _width, _height, get_bit_depth());
    } else {
        ia2raw(&_data[0], (ia*)imgData, _width, _height, get_bit_depth());
    }
    
}

N64Image::N64Image(int width, int height, std::string format, bool alignData) : _width(width), _height(height), _format(format) {
    int size = width * height;
    switch(ImageHelper::bytes_in_format(_format)) {
        case 0: // 4-bit format
            size /= 2;
            break;
        case 2: // 16-bit format
            size *= 2;
            break;
        case 4: // 32-bit format
            size *= 4;
            break;
    }
    
    if(alignData) {
        size = DataHelper::align16(size);
    }
    
    _data.resize(size); // Should fill the data with zeroes.
}

N64Image::~N64Image() {
}

void N64Image::write_from(const uint8_t *inData, size_t dataLength) {
    memcpy(&_data[0], inData, dataLength);
}

void N64Image::copy_to(uint8_t *out) {
    memcpy(out, &_data[0], size());
}

void N64Image::_prep_region_copy(size_t &srcWidth, size_t &bytesToCopyPerLine, size_t &imgWidthInBytes, size_t &xOffsetInBytes, N64Image::Region &region) {
    // Make sure the region doesn't extend beyond the image.
    region.x0 = std::clamp<int>(region.x0, 0, _width);
    region.x1 = std::clamp<int>(region.x1, 0, _width);
    region.y0 = std::clamp<int>(region.y0, 0, _height);
    region.y1 = std::clamp<int>(region.y1, 0, _height);
    
    int regionWidth = region.x1 - region.x0;
    int regionHeight = region.y1 - region.y0;
    
    if(regionWidth <= 0 || regionHeight <= 0) {
        return;
    }
    
    size_t bitDepth = get_bit_depth();
    size_t bytesPerPixel = bitDepth / 8;
    xOffsetInBytes = region.x0;
    imgWidthInBytes = _width;
    bytesToCopyPerLine = regionWidth;
    
    if(bitDepth == 4) {
        srcWidth /= 2;
        bytesToCopyPerLine /= 2;
        xOffsetInBytes /= 2;
        imgWidthInBytes /= 2;
    } else {
        srcWidth *= bytesPerPixel;
        bytesToCopyPerLine *= bytesPerPixel;
        xOffsetInBytes *= bytesPerPixel;
        imgWidthInBytes *= bytesPerPixel;
    }
}

// in format is assumed to be the same as this image.
void N64Image::write_data_to_region(const uint8_t *in, size_t inWidth, N64Image::Region region) {
    size_t bytesToCopyPerLine, imgWidthInBytes, xOffsetInBytes;
    _prep_region_copy(inWidth, bytesToCopyPerLine, imgWidthInBytes, xOffsetInBytes, region);
    
    int regionHeight = region.y1 - region.y0;
    for(int line = 0; line < regionHeight; line++) {
        const uint8_t *src = in + (line * inWidth);
        uint8_t *dst = _data.data() + ((region.y0 + line) * imgWidthInBytes) + xOffsetInBytes;
        memcpy(dst, src, bytesToCopyPerLine);
    }
}

// out format is assumed to be the same as this image.
void N64Image::copy_data_from_region(uint8_t *out, size_t outWidth, N64Image::Region region) {
    size_t bytesToCopyPerLine, imgWidthInBytes, xOffsetInBytes;
    _prep_region_copy(outWidth, bytesToCopyPerLine, imgWidthInBytes, xOffsetInBytes, region);
    
    int regionHeight = region.y1 - region.y0;
    for(int line = 0; line < regionHeight; line++) {
        uint8_t *dst = out + (line * outWidth);
        const uint8_t *src = _data.data() + ((region.y0 + line) * imgWidthInBytes) + xOffsetInBytes;
        memcpy(dst, src, bytesToCopyPerLine);
    }
}

void N64Image::interlace() {
    int bitDepth = get_bit_depth();
    int bytesPerPixel = bitDepth / 8;
    int bufferSize = (bitDepth == 32) ? 8 : 4;
    int bytesPerRow = _width;
    
    uint8_t* temp = new uint8_t[bufferSize];
    
    if(bitDepth == 4) {
        bytesPerRow /= 2;
    } else {
        bytesPerRow *= bytesPerPixel;
    }
    
    int stride = bufferSize * 2;
    int swapsPerRow = bytesPerRow / stride;
    
    // Only want to do the swaps on odd-number lines.
    for(int row = 1; row < _height; row+=2) {
        int offset = row * bytesPerRow;
        
        for(int swap = 0; swap < swapsPerRow; swap++) {
            for(int j = 0; j < bufferSize; j++) {
                temp[j] = _data[offset + j];
                _data[offset + j] = _data[(offset + j + bufferSize)];
                _data[(offset + j + bufferSize)] = temp[j];
            }
            
            offset += stride;
        }
    }
    
    delete[] temp;
}

void N64Image::flip_vertically() {
    int numBytesPerLine = _width; // Convert width into number of bytes per line.
    switch(ImageHelper::bytes_in_format(_format)) {
        case 0:
            numBytesPerLine /= 2; // 2 pixels per byte
            break;
        case 2:
            numBytesPerLine *= 2; // 2 bytes per pixel
            break;
        case 4:
            numBytesPerLine *= 4; // 4 bytes per pixel
            break;
            // Don't need to do anything for the 8-bit formats.
    }
    for(int y = 0; y < _height / 2; y++) {
        for(int x = 0; x < numBytesPerLine; x++) {
            uint8_t temp = _data[y * numBytesPerLine + x];
            _data[y * numBytesPerLine + x] = _data[((_height - y - 1) * numBytesPerLine + x)];
            _data[((_height - y - 1) * numBytesPerLine + x)] = temp;
        }
    }
}

size_t N64Image::size() {
    return _data.size();
}

std::string N64Image::get_format() {
    return _format;
}

int N64Image::get_width() {
    return _width;
}

int N64Image::get_height() {
    return _height;
}

int N64Image::get_bit_depth() {
    int byteSize = ImageHelper::bytes_in_format(_format);
    switch(byteSize) {
        case 4:
            return 32;
        case 2:
            return 16;
        case 1:
            return 8;
        default:
            return 4;
    }
}

bool N64Image::is_4bit_format() {
    return get_bit_depth() == 4;
}

// TODO: Figure out a better way to implement this.
uint8_t *N64Image::get_img_as_rgba32() {
    if (_format == "RGBA16") {
        return reinterpret_cast<uint8_t*>(raw2rgba(&_data[0], _width, _height, 16));
    }
    
    uint8_t *out = new uint8_t[_width * _height * 4]; 
    
    if(_format == "RGBA32") {
        memcpy(out, &_data[0], _data.size());
    } else if (_format == "IA16") {
        for(size_t i = 0; i < _data.size(); i += 2) {
            int outIndex = i * 2;
            int intensity = _data[i];
            int alpha = _data[i + 1];
            out[outIndex + 0] = intensity;
            out[outIndex + 1] = intensity;
            out[outIndex + 2] = intensity;
            out[outIndex + 3] = alpha;
        }
    } else if (_format == "IA8") {
        for(size_t i = 0; i < _data.size(); i++) {
            int outIndex = i * 4;
            int intensity = (_data[i] >> 4) & 0xF;
            int alpha = _data[i] & 0xF;
            out[outIndex + 0] = intensity;
            out[outIndex + 1] = intensity;
            out[outIndex + 2] = intensity;
            out[outIndex + 3] = alpha;
        }
    } else if (_format == "IA4") {
        for(size_t i = 0; i < _data.size(); i++) {
            for(size_t j = 0; j < 2; j++) { // Two pixels per byte.
                int outIndex = (i * 8) + (j * 4);
                int pixelValue = _data[i] >> (j * 4);
                int intensity = (pixelValue >> 1) & 7;
                int alpha = pixelValue & 1;
                out[outIndex + 0] = intensity;
                out[outIndex + 1] = intensity;
                out[outIndex + 2] = intensity;
                out[outIndex + 3] = alpha;
            }
        }
    } else if (_format == "I8") {
        for(size_t i = 0; i < _data.size(); i++) {
            int outIndex = i * 4;
            int intensity = _data[i];
            out[outIndex + 0] = intensity;
            out[outIndex + 1] = intensity;
            out[outIndex + 2] = intensity;
            out[outIndex + 3] = 255;
        }
    } else if (_format == "I4") {
        for(size_t i = 0; i < _data.size(); i++) {
            for(size_t j = 0; j < 2; j++) { // Two pixels per byte.
                int outIndex = (i * 8) + (j * 4);
                int intensity = _data[i] >> (j * 4);
                out[outIndex + 0] = intensity;
                out[outIndex + 1] = intensity;
                out[outIndex + 2] = intensity;
                out[outIndex + 3] = 255;
            }
        }
    } else {
        // TODO: Support CI4/CI8
        DebugHelper::error("(N64Image::get_img_as_rgba32) Format \"", _format, "\" is currently not supported.");
    }
    
    return out;
}

// TODO: Figure out a better way to implement this.
uint8_t *N64Image::get_img_as_ia16() {
    if(_format == "IA8") {
        return reinterpret_cast<uint8_t*>(raw2ia(&_data[0], _width, _height, 8));
    } else if(_format == "IA4") {
        return reinterpret_cast<uint8_t*>(raw2ia(&_data[0], _width, _height, 4));
    } else if(_format == "I8") {
        return reinterpret_cast<uint8_t*>(raw2i(&_data[0], _width, _height, 8));
    } else if(_format == "I4") {
        return reinterpret_cast<uint8_t*>(raw2i(&_data[0], _width, _height, 4));
    }
    
    uint8_t *out = new uint8_t[_width * _height * 2];
    
    if(_format == "IA16") {
        memcpy(out, &_data[0], _data.size());
    } else if (_format == "RGBA32") {
        for(size_t i = 0; i < _data.size(); i += 4) {
            int outIndex = i / 2;
            int red   = _data[i + 0];
            int green = _data[i + 1];
            int blue  = _data[i + 2];
            int alpha = _data[i + 3];
            
            out[outIndex + 0] = (red + green + blue) / 3;
            out[outIndex + 1] = alpha;
        }
    } else if (_format == "RGBA16") {
        for(size_t i = 0; i < _data.size(); i += 2) {
            int outIndex = i;
            int red   = ((_data[i] >> 3) & 0x1F);
            int green = (((_data[i] & 7) << 2) | ((_data[i + 1] >> 6) & 0x3)) & 0x1F;
            int blue  = (_data[i + 1] >> 1) & 0x1F;
            int alpha = _data[i + 1] & 1;
            
            out[outIndex + 0] = (red + green + blue) / 3;
            out[outIndex + 1] = alpha;
        }
    } else {
        // TODO: Support CI4/CI8
        DebugHelper::error("(N64Image::get_img_as_ia16) Format \"", _format, "\" is currently not supported.");
    }
    
    return out;
}

void N64Image::save(fs::path finalFilepath) {
    if(_format == "CI4" || _format == "CI8") {
        DebugHelper::error("(N64Image::save) Format \"", _format, "\" is currently not supported.");
    }
    
    // Make sure the folder of the final filepath exists, so it doesn't cause an error.
    FileHelper::write_folder_if_it_does_not_exist(finalFilepath);
    
    uint8_t *imgData;
    if(_format == "RGBA32" || _format == "RGBA16") {
        // Save RGBA image.
        imgData = get_img_as_rgba32();
        
        int result = rgba2png(finalFilepath.c_str(), reinterpret_cast<rgba*>(imgData), _width, _height); // Save RGBA data as a .png file.
        DebugHelper::assert(result == 1, "(N64Image::save) stbi_write_png returned ", result, ". Could not save image ", finalFilepath);
        DebugHelper::assert(FileHelper::path_exists(finalFilepath), "(N64Image::save) Image ", finalFilepath, " could not be saved.");
    } else {
        // Save IA image.
        imgData = get_img_as_ia16();
        int result = ia2png(finalFilepath.c_str(), reinterpret_cast<ia*>(imgData), _width, _height); // Save IA data as a .png file.
        DebugHelper::assert(result == 1, "(N64Image::save) stbi_write_png returned ", result, ". Could not save image ", finalFilepath);
        DebugHelper::assert(FileHelper::path_exists(finalFilepath), "(N64Image::save) Image ", finalFilepath, " could not be saved.");
    }
    delete[] imgData;
}

/**********************************************/

N64Image ImageHelper::load_image(fs::path filepath, std::string format) {
    return N64Image(filepath, format);
}

std::unordered_map<std::string, int> bytesInFormatMap = {
    {"RGBA32", 4},
    {"RGBA16", 2},
    {"I8", 1},
    {"I4", 0},
    {"IA16", 2},
    {"IA8", 1},
    {"IA4", 0},
    {"CI8", 1},
    {"CI4", 0}
};

int ImageHelper::bytes_in_format(std::string &format) {
    if(format.empty()) {
        DebugHelper::error("(ImageHelper::bytes_in_format) Format string empty!");
    }
    auto it = bytesInFormatMap.find(format);
    if(it != bytesInFormatMap.end()) {
        return it->second;
    }
    DebugHelper::error("(ImageHelper::bytes_in_format) Invalid format string \"", format, "\"");
    return -1;
}

size_t ImageHelper::image_size(int width, int height, std::string &format) {
    int bytesPerFormat = ImageHelper::bytes_in_format(format);
    switch(bytesPerFormat) {
        default: // 8-bit format.
            return width * height;
        case 0: // 4-bit format
            return (width * height) / 2;
        case 2: // 16-bit format
            return width * height * 2;
        case 4: // 32-bit format
            return width * height * 4;
    }
}

size_t ImageHelper::image_size(fs::path filepath, std::string &format) {
    int width, height, channels;
    int gotInfo = stbi_info(filepath.generic_string().c_str(), &width, &height, &channels);
    DebugHelper::assert_(gotInfo, "(ImageHelper::image_size) ", filepath, " could not be loaded!");
    return image_size(width, height, format);
}

void ImageHelper::get_width_and_height(fs::path filepath, int &outWidth, int &outHeight) {
    int channels;
    int gotInfo = stbi_info(filepath.generic_string().c_str(), &outWidth, &outHeight, &channels);
    DebugHelper::assert_(gotInfo, "(ImageHelper::get_width_and_height) ", filepath, " could not be loaded!");
}

