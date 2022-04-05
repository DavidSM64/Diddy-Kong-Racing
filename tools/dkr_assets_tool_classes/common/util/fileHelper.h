#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <openssl/md5.h>

// C++17
#include <filesystem> 
namespace fs = std::filesystem;

#include "errorHelper.h"

bool is_asset_folder_path_defined();
void set_assets_folder_path(std::string path);
std::string get_asset_folder_path();
void set_version(std::string ver);
std::string get_version();

std::vector<uint8_t> read_binary_file(std::string filename);
void write_binary_file(std::vector<uint8_t> &data, std::string filepath);
std::string read_text_file(std::string filename);
void write_text_file(std::string text, std::string filepath);
bool path_exists(std::string path);
void path_must_exist(std::string path);
bool path_is_directory(std::string strPath);
std::vector<std::string> get_filenames_from_directory(std::string dirPath);
std::vector<std::string> get_filenames_from_directory_only(std::string dirPath);
std::vector<fs::path> get_filenames_from_directory_only_with_extension(std::string dirPath, std::string extension);
std::vector<fs::path> get_folders_from_directory_only(std::string dirPath);
std::vector<std::string> get_filenames_from_directory_with_extension(std::string dirPath, std::string extension);
std::vector<std::string> get_filenames_from_directory_without_extension(std::string dirPath, std::string extension);
void create_directory(std::string directory);
std::string get_filename_from_full_path(std::string path, bool excludeExtension);
std::string get_directory_from_full_path(std::string path);
void ensure_that_path_exists(std::string path);
void copy_file(std::string srcPath, std::string dstPath);
void recursively_copy_directory(std::string srcPath, std::string dstPath);
void delete_directory(std::string dirPath);
void delete_path(std::string dirPath);
std::string replace_extension(std::string path, std::string newExtension);
bool starts_with(const std::string &a, const std::string &b);
bool ends_with(const std::string &a, const std::string &b);
void make_lowercase(std::string &input);
void make_uppercase(std::string &input);

std::string calculate_md5(std::vector<uint8_t> &bytes);
std::string calculate_file_md5(std::string filepath);

