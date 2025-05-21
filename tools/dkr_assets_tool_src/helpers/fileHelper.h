#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <optional>

#include "stringHelper.h"
#include "debugHelper.h"

#include "libs/bytes_view.hpp"

#include <filesystem>
namespace fs = std::filesystem;

namespace DkrAssetsTool {

// Using path as a key doesn't seem to work on raspberry pi OS?
struct PathHash {
    std::size_t operator()(const std::filesystem::path& p) const {
        return std::filesystem::hash_value(p);
    }
};

namespace FileHelper {
    std::vector<uint8_t> read_binary_file(const fs::path& filename);
    std::string read_text_file(const fs::path& filepath, size_t maxSize = SIZE_MAX);

    std::vector<uint8_t> read_bytes_from_file(const fs::path& filename, size_t offset, size_t numberOfBytes);
    std::string read_ascii_from_binary_file(const fs::path& filename, size_t offset, size_t length);

    void write_text_file(const std::string& text, const fs::path& filepath, bool ensurePathExists = false);
    // Only writes if the contents of the file have been changed.
    void write_text_file_if_changed(const std::string& text, const fs::path& filepath, bool ensurePathExists = false);

    void write_folder_if_it_does_not_exist(const fs::path& path);

    void write_empty_file(const fs::path& filepath, bool ensurePathExists = false);
    void write_binary_file(std::vector<uint8_t>& data, const fs::path& filepath, bool ensurePathExists = false);
    void write_binary_file(const char* data, size_t dataSize, const fs::path& filepath, bool ensurePathExists = false);
    void write_binary_file(const uint8_t* data, size_t dataSize, const fs::path& filepath, bool ensurePathExists = false);
    void write_binary_file(const BytesView& data, const fs::path& filepath, bool ensurePathExists = false);

    bool path_exists(const fs::path& path);
    bool is_zip_file(const fs::path& path);

    std::string get_sha1_of_file(const fs::path& path);

    std::vector<fs::path> get_files_from_directory(const fs::path& dirPath, bool recursive = true);
    std::vector<fs::path> get_files_from_directory_that_start_with(const fs::path& dirPath, std::string prefix, bool recursive = true);
    std::vector<fs::path> get_files_from_directory_with_extension(const fs::path& dirPath, std::string extension, bool recursive = true);
    std::vector<fs::path> get_files_from_directory_excluding_extension(const fs::path& dirPath, std::string extension, bool recursive = true);
    std::vector<fs::path> get_folders_from_directory(const fs::path& dirPath, bool recursive = true);
    
    size_t count_files_with_extension(const fs::path& dirPath, std::string extension, bool recursive = true);

    bool does_folder_contain_paths(const fs::path& dirPath, const std::vector<fs::path>& paths);

    void append_files_from_directory(const fs::path& dirPath, std::vector<fs::path>& out, bool recursive = true);
    void append_files_from_directory_relative(const fs::path& dirPath, std::vector<fs::path>& out, bool recursive = true);
    void append_files_from_directory_with_extension(const fs::path& dirPath, std::string extension, std::vector<fs::path>& out, bool recursive = true);

    fs::path get_filename_from_path(const fs::path& path, bool exclude_extension = false);

    bool does_filename_equal(const fs::path& path, std::string filename, bool exclude_extension = false);
    
    // Returns the full path, whether filepath is relative or absolute. Returns std::nullopt if the file does not exist.
    std::optional<fs::path> determine_full_filepath(fs::path filepath, fs::path localDirectory);

    fs::path get_working_directory();
    fs::path get_directory(const fs::path& path);

    void delete_directory(const fs::path& path);
    void delete_file(const fs::path& path);

    void rename(const fs::path& oldPath, const fs::path& newPath);
    void copy(const fs::path& oldPath, const fs::path& newPath, bool recursive = false);

    void format_folder_string(fs::path& folderPath);

    size_t align16(size_t size);

    void byteswap(std::vector<uint8_t>& bytes);
    // Converts between big and little endian
    void endianswap(std::vector<uint8_t>& bytes);

    std::string get_last_modified_timestamp(const fs::path& path);
    void insert_timestamps_from_directory(const fs::path& dirPath, std::unordered_map<fs::path, std::string, PathHash>& timestamps);
    void update_timestamp(const fs::path& path);

    bool are_files_the_same(const fs::path& file1, const fs::path& file2);
    bool are_files_the_same(const fs::path& file1, const fs::path& file2, std::optional<std::string>& outNotTrueReason);
}
}