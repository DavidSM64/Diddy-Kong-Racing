#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// C++17
#include <filesystem> 
namespace fs = std::filesystem;

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
std::vector<std::string> get_filenames_from_directory(std::string dirPath);
std::vector<std::string> get_filenames_from_directory_only(std::string dirPath);
std::vector<fs::path> get_filenames_from_directory_only_with_extension(std::string dirPath, std::string extension);
std::vector<fs::path> get_folders_from_directory_only(std::string dirPath);
std::vector<std::string> get_filenames_from_directory_with_extension(std::string dirPath, std::string extension);
void create_directory(std::string directory);
std::string get_filename_from_full_path(std::string path, bool excludeExtension);
std::string get_directory_from_full_path(std::string path);
void ensure_that_path_exists(std::string path);
void recursively_copy_directory(std::string srcPath, std::string dstPath);
void delete_directory(std::string dirPath);
std::string replace_extension(std::string path, std::string newExtension);
bool ends_with(const std::string &a, const std::string &b);
void make_lowercase(std::string &input);
void make_uppercase(std::string &input);

