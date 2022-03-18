#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../libs/n64graphics.h"

#define TEX_HEADER_SIZE 0x20

#define TEX_FORMAT_RGBA32 0
#define TEX_FORMAT_RGBA16 1
#define TEX_FORMAT_I8     2
#define TEX_FORMAT_I4     3
#define TEX_FORMAT_IA16   4
#define TEX_FORMAT_IA8    5
#define TEX_FORMAT_IA4    6
#define TEX_FORMAT_CI4    7
#define TEX_FORMAT_CI8    8

std::string get_texture_format_string(int format);
int get_texture_format_from_string(std::string format);
void deinterlace(std::vector<uint8_t>& texData, int texDataOffset, int width, int height, int bitDepth, int bufferSize);
void flip_texture_vertically(std::vector<uint8_t> &data, int dataOffset, int width, int height, int format);
int get_texture_size(int width, int height, int format);
std::vector<uint8_t> load_texture_from_png(std::string filepath, int textureFormat, int* width, int* height);
