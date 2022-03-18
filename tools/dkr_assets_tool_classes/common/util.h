#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "../libs/json.hpp"
#include "../libs/n64graphics.h"
#include "../libs/DKRCompression.h"

#include "util/fileHelper.h"
#include "util/jsonHelper.h"
#include "util/enumHelper.h"

uint32_t get_big_endian_word(std::vector<uint8_t> &data, int offset);
void write_big_endian_word(std::vector<uint8_t> &data, int offset, uint32_t value);
uint16_t get_big_endian_halfword(std::vector<uint8_t> &data, int offset);
void write_big_endian_halfword(std::vector<uint8_t> &data, int offset, uint16_t value);
int16_t get_big_endian_halfword_signed(std::vector<uint8_t> &data, int offset);
float get_big_endian_float(std::vector<uint8_t> &data, int offset);
void write_big_endian_float(std::vector<uint8_t> &data, int offset, float value);
std::string get_ascii(std::vector<uint8_t> &data, int offset);
void write_ascii(std::vector<uint8_t> &data, std::string value);
int insert_ascii(std::vector<uint8_t> &data, int offset, std::string value);
std::vector<std::string> get_multiple_ascii(std::vector<uint8_t> &data, int offset, int count);

std::vector<uint8_t> decompress_dkr_gzip(std::vector<uint8_t> &compressedData);
std::vector<uint8_t> compress_dkr_gzip(std::vector<uint8_t> &uncompressedData);

int align16(int val);
std::string to_hex(uint32_t value);

std::string upper_snake_case_to_pascal_case(std::string input);

void print_data(std::vector<uint8_t> &data, int offset, int length);
