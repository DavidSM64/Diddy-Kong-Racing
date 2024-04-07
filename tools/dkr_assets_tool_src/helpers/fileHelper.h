#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "stringHelper.h"
#include "debugHelper.h"

#include <filesystem>
namespace fs = std::filesystem;

class FileHelper {
public:
    static std::vector<uint8_t> read_binary_file(const fs::path &filename);
    static std::string read_text_file(const fs::path &filepath, size_t maxSize=SIZE_MAX);
    
    static void write_text_file(const std::string &text, const fs::path &filepath, bool ensurePathExists=false);
    // Only writes if the contents of the file have been changed.
    static void write_text_file_if_changed(const std::string &text, const fs::path &filepath, bool ensurePathExists=false);
    
    static void write_folder_if_it_does_not_exist(const fs::path &path);
    
    static void write_empty_file(const fs::path &filepath, bool ensurePathExists=false);
    static void write_binary_file(std::vector<uint8_t> &data, const fs::path &filepath, bool ensurePathExists=false);
    static void write_binary_file(uint8_t *data, size_t dataSize, const fs::path &filepath, bool ensurePathExists=false);
    static void write_binary_file(const char *data, size_t dataSize, const fs::path &filepath, bool ensurePathExists=false);
    
    static bool path_exists(const fs::path &path);
    static bool is_zip_file(const fs::path &path);
    
    static std::vector<fs::path> get_files_from_directory(const fs::path &dirPath, bool recursive=true);
    static std::vector<fs::path> get_files_from_directory_with_extension(const fs::path &dirPath, std::string extension, bool recursive=true);
    static std::vector<fs::path> get_files_from_directory_excluding_extension(const fs::path &dirPath, std::string extension, bool recursive=true);
    static std::vector<fs::path> get_folders_from_directory(const fs::path &dirPath, bool recursive=true);
    
    static void append_files_from_directory(const fs::path &dirPath, std::vector<fs::path> &out, bool recursive=true);
    static void append_files_from_directory_relative(const fs::path &dirPath, std::vector<fs::path> &out, bool recursive=true);
    static void append_files_from_directory_with_extension(const fs::path &dirPath, std::string extension, std::vector<fs::path> &out, bool recursive=true);
    
    static fs::path get_filename_from_path(const fs::path &path, bool exclude_extension = false);
    
    static bool does_filename_equal(const fs::path &path, std::string filename, bool exclude_extension = false);
    
    static fs::path get_directory(const fs::path &path);
    
    static void delete_directory(const fs::path &path);
    
    static void rename(const fs::path &oldPath, const fs::path &newPath);
    static void copy(const fs::path &oldPath, const fs::path &newPath, bool recursive = false);
    
    static void format_folder_string(fs::path &folderPath);
    
    static size_t align16(size_t size);
    
    static void byteswap(std::vector<uint8_t> &bytes);
    // Converts between big and little endian
    static void endianswap(std::vector<uint8_t> &bytes);
    
    static std::string get_last_modified_timestamp(const fs::path &path);
    static void insert_timestamps_from_directory(const fs::path &dirPath, std::unordered_map<fs::path, std::string> &timestamps);
private:
    
};
