#include "imageHelper.h"

using namespace DkrAssetsTool;

#include <cstring> // for memcpy
#include <algorithm>
#include <unordered_map>
#include <map>

#include "jsonHelper.h"
#include "fileHelper.h"
#include "debugHelper.h"
#include "libs/n64graphics/n64graphics.h"
#include "libs/stb_image.h"
#include "helpers/dataHelper.h"
#include "misc/globalSettings.h"
#include "fileTypes/texture.hpp"

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

// If a texture uses multiple images, it will have a number at the end like "_2".
// so this function should remove that so we can find the correct json file.
fs::path strip_postfix_number(fs::path path) {
    std::string filename = path.filename().stem().generic_string();
    
    int offset = filename.size() - 1;
    while((offset >= 0) && ((filename[offset] >= '0') && (filename[offset] <= '9'))) {
        offset--;
    }
    
    if(filename[offset] != '_') {
        return path;
    }
    
    if((offset > 0) && (offset < filename.size() - 1)) {
        fs::path outPath = path.parent_path() / filename.substr(0, offset);
        outPath.replace_extension(path.extension()); // Add the extension back in.
        return outPath;
    }
    
    return path;
}

int get_postfix_number(fs::path path) {
    std::string filename = path.filename().stem().generic_string();
    
    int offset = filename.size() - 1;
    while((offset >= 0) && ((filename[offset] >= '0') && (filename[offset] <= '9'))) {
        offset--;
    }
    
    if(filename[offset] != '_') {
        return -1;
    }
    
    if((offset > 0) && (offset < filename.size() - 1)) {
        return std::stoi(filename.substr(offset + 1));
    }
    
    return -1;
}

std::optional<fs::path> ImageHelper::guess_associated_json_file(fs::path imgFilepath) {
    fs::path filepath = imgFilepath;
    filepath.replace_extension(".json");
    if(FileHelper::path_exists(filepath)) {
        return filepath;
    }
    filepath = strip_postfix_number(filepath);
    if(FileHelper::path_exists(filepath)) {
        return filepath;
    }
    return std::nullopt;
}

void ImageHelper::guess_texture_wrap_mode(fs::path filepath, std::string &outWrapS, std::string &outWrapT) {
    // Use "wrap" as the default.
    outWrapS = "wrap";
    outWrapT = "wrap";
    
    // Check to see if there is an accompanying json file with the image file.
    // That json file more than likely has a format/render-mode associated with it.
    std::optional<fs::path> jsonFilepath = guess_associated_json_file(filepath);
    
    if(jsonFilepath.has_value()) {
        JsonFile &jsonFile = JsonHelper::get_file_or_error(jsonFilepath.value(), 
            "Could not load json file ", jsonFilepath.value());
        
        outWrapS = jsonFile.get_string_lowercase("/flags/wrap-s", "wrap");
        outWrapT = jsonFile.get_string_lowercase("/flags/wrap-t", "wrap");
    }
}
    
void ImageHelper::guess_texture_format_and_render_mode(fs::path filepath, std::string &outFormat, std::string &outRenderMode, bool ignoreTextureSize) {
    outFormat = "";
    outRenderMode = "";

    // Check to see if there is an accompanying json file with the image file.
    // That json file more than likely has a format/render-mode associated with it.
    std::optional<fs::path> jsonFilepath = guess_associated_json_file(filepath);
    
    if(jsonFilepath.has_value()) {
        JsonFile &jsonFile = JsonHelper::get_file_or_error(jsonFilepath.value(), 
            "Could not load json file ", jsonFilepath.value());
        
        outFormat = jsonFile.get_string("/format");
        outRenderMode = jsonFile.get_string("/render-mode");
    }

    if(!outFormat.empty() && !outRenderMode.empty()) {
        return;
    } 
    
    // Check and see if the image has the format in the filename. Example: `tex.rgba16.png`
    
    if(outFormat.empty()) {
        std::vector<std::string> filenameSplit;
        std::string filenameAsString = filepath.filename().generic_string();
        StringHelper::split(filenameAsString, '.', filenameSplit); // Split filename using the dots.
        for(size_t i = 1; i < filenameSplit.size() - 1; i++) {
            std::string &filenamePart = filenameSplit[i];
            StringHelper::make_uppercase(filenamePart);
            if(DataHelper::vector_has(TEXTURE_FORMAT_INT_TO_STRING, filenamePart)) {
                outFormat = filenamePart;
                break;
            }
        }
    }

    // Load the image and take a guess from the pixels.
    
    int imgWidth, imgHeight;
    
    rgba *data = (rgba*)png2rgba(filepath.c_str(), &imgWidth, &imgHeight);
    
    int numberOfPixels = imgWidth * imgHeight;
    
    bool isTransparent = false;
    bool isSemiTransparent = false;
    bool hasColor = false;
    
    for(int y = 0; y < imgHeight; y++) {
        for(int x = 0; x < imgWidth; x++) {
            int i = (y * imgWidth) + x;
            bool isGray = (data[i].red == data[i].green) && (data[i].green == data[i].blue);
            
            hasColor = hasColor || !isGray;
            isTransparent = isTransparent || (data[i].alpha < 255);
            isSemiTransparent = isSemiTransparent || (isTransparent && (data[i].alpha > 0));
        }
    }
    
    if(outFormat.empty()) {
        if(hasColor) {
            // Color image (RGBA16, RGBA32)
            if(!ignoreTextureSize && (numberOfPixels > 32*32)) {
                // Can't use 32-bit formats at this point
                if(numberOfPixels > 64*32) {
                    DebugHelper::error("(ImageHelper::guess_texture_format_and_render_mode) ", 
                        filepath.filename(), " is too large for a colored image!");
                } else {
                    outFormat = "RGBA16";
                }
            } else {
                outFormat = (isSemiTransparent ? "RGBA32" : "RGBA16");
            }
        } else {
            // Grayscale image (I4, IA4, I8, IA8, IA16)
            if(!ignoreTextureSize && (numberOfPixels > 64*32)) {
                // Can't use 16-bit formats at this point
                if(numberOfPixels > 64*64) {
                    // Can't use 8-bit formats at this point.
                    if(numberOfPixels > 128*64) {
                        DebugHelper::error("(ImageHelper::guess_texture_format_and_render_mode) ", 
                            filepath.filename(), " is too large for a grayscale image!");
                    } else {
                        outFormat = (isTransparent ? "IA4" : "I4");
                    }
                } else {
                    outFormat = (isTransparent ? "IA8" : "I8");
                }
            } else {
                outFormat = (isTransparent ? "IA16" : "I8");
            }
        }
    }
    
    if(outRenderMode.empty()) {
        outRenderMode = (isTransparent ? "TRANSPARENT" : "OPAQUE");
    }
}

bool ImageHelper::guess_if_texture_is_animated(fs::path imgFilepath) {
    // Check to see if there is an accompanying json file with the image file.
    std::optional<fs::path> jsonFilepath = guess_associated_json_file(imgFilepath);
    
    if(jsonFilepath.has_value()) {
        JsonFile &jsonFile = JsonHelper::get_file_or_error(jsonFilepath.value(), 
            "Could not load json file ", jsonFilepath.value());
        return jsonFile.length_of_array("/images") > 1;
    }
    
    // Check if there exist multiple texture paths based off the imgFilepath provided.
    return get_multiple_textures_from_one(imgFilepath).size() > 1;
}

bool ImageHelper::guess_if_texture_double_sided(fs::path filepath) {
    // Check to see if there is an accompanying json file with the image file.
    // That json file more than likely has a format/render-mode associated with it.
    std::optional<fs::path> jsonFilepath = guess_associated_json_file(filepath);
    
    if(jsonFilepath.has_value()) {
        JsonFile &jsonFile = JsonHelper::get_file_or_error(jsonFilepath.value(), 
            "Could not load json file ", jsonFilepath.value());
        return jsonFile.get_bool("/doubleSided", false);
    }
    
    return false;
}

float ImageHelper::guess_animated_texture_timing(fs::path imgFilepath) {
    // Check to see if there is an accompanying json file with the image file.
    std::optional<fs::path> jsonFilepath = guess_associated_json_file(imgFilepath);
    
    if(jsonFilepath.has_value()) {
        JsonFile &jsonFile = JsonHelper::get_file_or_error(jsonFilepath.value(), 
            "Could not load json file ", jsonFilepath.value());
        return jsonFile.get_float("/frame-advance-delay", 1.0f);
    }
    
    // Use 1 second as the default timing.
    return (float)GlobalSettings::get_value<double>("/build/default-frame-advance-delay", 1.0);
}

// Returns a list of paths of .png images (for animated textures)
std::vector<fs::path> ImageHelper::get_multiple_textures_from_one(fs::path imgFilepath) {
    fs::path filepath = strip_postfix_number(imgFilepath);
    
    if(filepath == imgFilepath) {
        return { imgFilepath };
    }
    
    std::string prefix = filepath.filename().stem().generic_string();
    std::vector<fs::path> paths = FileHelper::get_files_from_directory_that_start_with(imgFilepath.parent_path(), prefix, false);
    
    std::map<int, fs::path> order;
    
    for(fs::path &p : paths) {
        int index = get_postfix_number(p);
        if(index >= 0) {
            order[index] = p;
        }
    }
    
    if(order.size() == 0) {
        return { imgFilepath };
    }
    
    std::vector<fs::path> out;
    out.reserve(order.size());
    
    for(auto& pair : order) {
        out.emplace_back(pair.second);
    }
    
    return out;
}

