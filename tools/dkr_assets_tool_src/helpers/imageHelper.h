#pragma once

#include "helpers/fileHelper.h"

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>

namespace DkrAssetsTool {
class N64Image {
public:
    // TODO: Move to MathHelper?
    struct Region {
        int x0, y0, x1, y1;
    };

    N64Image(fs::path filepath, std::string format, bool alignData=false); // Load image from filepath (Currently only .png is supported)
    N64Image(int width=0, int height=0, std::string format="I4", bool alignData=false); // Create new image
    ~N64Image();
    
    void write_from(const uint8_t *inData, size_t dataLength);
    void copy_to(uint8_t *out);
    
    // src format is assumed to be the same as this one.
    void write_data_to_region(const uint8_t *in, size_t inWidth, N64Image::Region region);
    void copy_data_from_region(uint8_t *out, size_t outWidth, N64Image::Region region);

    void interlace();
    void flip_vertically();
    size_t size();
    std::string get_format();
    bool is_4bit_format();
    
    int get_width();
    int get_height();
    int get_bit_depth();
    
    // TODO: Refactor to use something other than raw pointers.
    uint8_t *get_img_as_rgba32(); // Note: pointer must be freed by caller!
    uint8_t *get_img_as_ia16();   // Note: pointer must be freed by caller!
    
    void save(fs::path finalFilepath); // Saves image (as .png) to the filepath.
private:
    int _width;
    int _height;
    std::string _format;
    
    std::vector<uint8_t> _data;
    
    void _prep_region_copy(size_t &srcWidth, size_t &bytesToCopyPerLine, size_t &imgWidthInBytes, size_t &xOffsetInBytes, N64Image::Region &region);
};

/**
 * Deals with N64 image formats and with saving/loading images.
 */
namespace ImageHelper {
    N64Image load_image(fs::path filepath, std::string format="RGBA16");
    int bytes_in_format(std::string &format);
    size_t image_size(int width, int height, std::string &format);
    size_t image_size(fs::path filepath, std::string &format); // Get byte-size of .png image
    void get_width_and_height(fs::path filepath, int &outWidth, int &outHeight); // Get width and height of a .png image
    
    std::optional<fs::path> guess_associated_json_file(fs::path imgFilepath);
    void guess_texture_wrap_mode(fs::path filepath, std::string &outWrapS, std::string &outWrapT);
    void guess_texture_format_and_render_mode(fs::path filepath, std::string &outFormat, std::string &outRenderMode, bool ignoreTextureSize=false);
    bool guess_if_texture_is_animated(fs::path imgFilepath);
    float guess_animated_texture_timing(fs::path imgFilepath); // Returns time to advance texture in seconds.
    
    std::vector<fs::path> get_multiple_textures_from_one(fs::path imgFilepath);
}
}
