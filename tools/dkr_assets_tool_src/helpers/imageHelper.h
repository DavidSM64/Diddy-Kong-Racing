#pragma once

#include "helpers/fileHelper.h"

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>

class N64Image {
public:
    N64Image(fs::path filepath, std::string &format, bool alignData=false); // Load image from filepath (Currently only .png is supported)
    N64Image(int width, int height, std::string &format, bool alignData=false); // Create new image
    ~N64Image();
    
    void write_from(uint8_t *inData, size_t dataLength);
    void copy_to(uint8_t *out);

    void interlace();
    void flip_vertically();
    size_t size();
    std::string get_format();
    bool is_4bit_format();
    
    int get_width();
    int get_height();
    int get_bit_depth();
    
    uint8_t *get_img_as_rgba32(); // Note: pointer must be freed by caller!
    uint8_t *get_img_as_ia16();   // Note: pointer must be freed by caller!
    
    void save(fs::path finalFilepath); // Saves image (as .png) to the filepath.
private:
    int _width;
    int _height;
    std::string _format;
    
    std::vector<uint8_t> _data;
};

/**
 * Singleton class that deals with N64 image formats and with saving/loading images.
 */
class ImageHelper {
public:
    static ImageHelper& get() {
        static ImageHelper instance;
        return instance;
    }
    
    static N64Image load_image(fs::path filepath, std::string format="RGBA16");
    static int bytes_in_format(std::string &format);
    static size_t image_size(int width, int height, std::string &format);
    static size_t image_size(fs::path filepath, std::string &format); // Get byte-size of .png image
    
};
