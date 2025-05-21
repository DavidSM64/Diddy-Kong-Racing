#include "fileHelper.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <optional>
#include <mutex>

#include "helpers/debugHelper.h"

#include "libs/sha1.hpp"

using namespace DkrAssetsTool;

std::vector<uint8_t> FileHelper::read_binary_file(const fs::path &filename) {
    DebugHelper::assert_(path_exists(filename), "(FileHelper::read_binary_file) Path ", filename, " does not exist!");
    std::ifstream is;
    is.open(filename.c_str(), std::ios::binary);
    is.seekg(0, std::ios::end);
    size_t filesize = is.tellg();
    is.seekg(0, std::ios::beg);
    std::vector<uint8_t> bytes(filesize);
    is.read((char *)bytes.data(), filesize);
    is.close();
    return bytes;
}

std::string FileHelper::read_text_file(const fs::path &filename, size_t maxSize) {
    DebugHelper::assert_(path_exists(filename), "(FileHelper::read_text_file) Path ", filename, " does not exist!");
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = std::min((size_t)t.tellg(), maxSize);
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);
    return buffer;
}

std::vector<uint8_t> FileHelper::read_bytes_from_file(const std::filesystem::path& filename, size_t offset, size_t numberOfBytes) {
    std::vector<uint8_t> buffer(numberOfBytes);
    std::ifstream file(filename, std::ios::binary);

    DebugHelper::assert_(file.is_open(), "Could not open file ", filename);

    file.seekg(offset);
    file.read(reinterpret_cast<char*>(buffer.data()), numberOfBytes);

    // Adjust the buffer size in case we read less than the requested number of bytes
    buffer.resize(file.gcount());
    return buffer;
}

std::string FileHelper::read_ascii_from_binary_file(const fs::path& filename, size_t offset, size_t length) {
    std::ifstream file(filename, std::ios::binary);
    DebugHelper::assert_(file.is_open(), "Could not open file ", filename);
    file.seekg(offset, std::ios::beg);

    std::vector<char> buffer(length);
    file.read(buffer.data(), length);

    file.close();
    return std::string(buffer.begin(), buffer.end());
}

void FileHelper::write_text_file(const std::string &text, const fs::path &filepath, bool ensurePathExists) {
    if(ensurePathExists) {
        write_folder_if_it_does_not_exist(filepath);
    }
    std::ofstream myfile;
    myfile.open(filepath);
    myfile << text;
    myfile.close();
}

void FileHelper::write_text_file_if_changed(const std::string &text, const fs::path &filepath, bool ensurePathExists) {
    if(FileHelper::path_exists(filepath)) {
        // TODO: Is there a faster way to do this?
        std::string savedText = FileHelper::read_text_file(filepath);
        if(text == savedText) {
            return; // Text is exactly the same, so return early.
        }
    }
    if(ensurePathExists) {
        write_folder_if_it_does_not_exist(filepath);
    }
    std::ofstream myfile;
    myfile.open(filepath);
    myfile << text;
    myfile.close();
}


void FileHelper::write_folder_if_it_does_not_exist(const fs::path &path) {
    fs::path dirPath = path;
    if (dirPath.has_filename()) {
        dirPath = dirPath.parent_path();
    }
    if(dirPath.empty()) {
        return;
    }
    if (!fs::exists(dirPath)) {
        fs::create_directories(dirPath);
    }
}

const char *EMPTY_DATA = "";

void FileHelper::write_empty_file(const fs::path &filepath, bool ensurePathExists) {
    write_binary_file(EMPTY_DATA, 0, filepath, ensurePathExists);
}
    
void FileHelper::write_binary_file(std::vector<uint8_t> &data, const fs::path &filepath, bool ensurePathExists) {
    if (data.size() == 0) {
        write_empty_file(filepath, ensurePathExists);
        return;
    }
    write_binary_file((const char*)&data[0], data.size(), filepath, ensurePathExists);
}

void FileHelper::write_binary_file(const char *data, size_t dataSize, const fs::path &filepath, bool ensurePathExists) {
    if(ensurePathExists) {
        write_folder_if_it_does_not_exist(filepath);
    }
    std::ofstream wf(filepath.c_str(), std::ios::out | std::ios::binary);
    wf.write(data, dataSize);
    wf.close();
}

void FileHelper::write_binary_file(const uint8_t* data, size_t dataSize, const fs::path& filepath, bool ensurePathExists) {
    // The const char cast is needed to prevent this function from calling itself lol.
    write_binary_file((const char*)data, dataSize, filepath, ensurePathExists);
}

void FileHelper::write_binary_file(const BytesView& data, const fs::path& filepath, bool ensurePathExists) {
    write_binary_file((const char*)data.data(), data.size(), filepath, ensurePathExists);
}

bool FileHelper::path_exists(const fs::path &path) {
    return fs::exists(path);
}

bool FileHelper::is_zip_file(const fs::path &path) {
    if(!FileHelper::path_exists(path) || fs::is_directory(path)) {
        return false;
    }
    
    try {
        std::ifstream data(path, std::ios::binary);
        char buffer[4];
        data.read(buffer, 4);
        data.close();
        uint32_t signature = *(reinterpret_cast<uint32_t*>(buffer));
        return signature == 0x04034B50 || // Little Endian
               signature == 0x504B0304;   // Big Endian
    } catch (...) {
        // TODO: Check for the actual error.
    }
    
    return false;
}

// mutex to help prevent possible data-races.
std::mutex _sha1CacheMutex;
std::unordered_map<fs::path, std::string> _fileSha1Cache;

std::string FileHelper::get_sha1_of_file(const fs::path& path) {
    _sha1CacheMutex.lock();
    if(_fileSha1Cache.find(path) != _fileSha1Cache.end()) {
        _sha1CacheMutex.unlock();
        // Found in cache.
        return _fileSha1Cache[path];
    }
    // Not in cache, so must calculate the result.
    SHA1 sha1;
    _fileSha1Cache[path] = sha1.from_file(path.generic_string());
    _sha1CacheMutex.unlock();
    return _fileSha1Cache[path];
}

std::vector<fs::path> FileHelper::get_files_from_directory(const fs::path &dirPath, bool recursive) {
    std::vector<fs::path> out;
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    out.push_back(file);
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    out.push_back(file);
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
    return out;
}

std::vector<fs::path> FileHelper::get_files_from_directory_that_start_with(const fs::path& dirPath, std::string prefix, bool recursive) {
    std::vector<fs::path> out;
    try {
        if (recursive) {
            for (const auto& file : fs::recursive_directory_iterator(dirPath)) {
                if (StringHelper::starts_with(file.path().filename().generic_string(), prefix)) {
                    out.push_back(file);
                }
            }
        } else {
            for (const auto& file : fs::directory_iterator(dirPath)) {
                if (StringHelper::starts_with(file.path().filename().generic_string(), prefix)) {
                    out.push_back(file);
                }
            }
        }
    } catch (fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
    return out;
}

std::vector<fs::path> FileHelper::get_files_from_directory_with_extension(const fs::path &dirPath, std::string extension, bool recursive) {
    std::vector<fs::path> out;
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(file.path().extension() == extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(file.path().extension() == extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
    return out;
}

std::vector<fs::path> FileHelper::get_files_from_directory_excluding_extension(const fs::path &dirPath, std::string extension, bool recursive) {
    std::vector<fs::path> out;
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(file.path().extension() != extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(file.path().extension() != extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
    return out;
}

std::vector<fs::path> FileHelper::get_folders_from_directory(const fs::path &dirPath, bool recursive) {
    std::vector<fs::path> out;
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(file.is_directory()) {
                    out.push_back(file);
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(file.is_directory()) {
                    out.push_back(file);
                }
            }
        }
    } catch(fs::filesystem_error const& e) {
        DebugHelper::error(e.what());
    }
    return out;
}


size_t count_files_with_extension(const fs::path& dirPath, std::string extension, bool recursive) {
    if (extension[0] != '.')
        extension = "." + extension;

    size_t count = 0;

    try {
        if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
            DebugHelper::error("Could not find the directory ", dirPath);
            return 0;
        }

        if(recursive) {
            for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
                if (entry.is_regular_file() && entry.path().extension() == extension) {
                    ++count;
                }
            }
        } else {
            for (const auto& entry : fs::directory_iterator(dirPath)) {
                if (entry.is_regular_file() && entry.path().extension() == extension) {
                    ++count;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        DebugHelper::error(e.what());
    }

    return count;
}

bool FileHelper::does_folder_contain_paths(const fs::path& dirPath, const std::vector<fs::path>& paths) {
    for (auto& subPath : paths) {
        if (!path_exists(dirPath / subPath)) {
            // At-least one path does not exist.
            return false;
        }
    }

    // All paths exist
    return true;
}

void FileHelper::append_files_from_directory(const fs::path &dirPath, std::vector<fs::path> &out, bool recursive) {
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    out.push_back(file);
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    out.push_back(file);
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
}

void FileHelper::append_files_from_directory_relative(const fs::path &dirPath, std::vector<fs::path> &out, bool recursive) {
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    fs::path p = std::filesystem::relative(file, dirPath);
                    if(!p.empty()) {
                        out.push_back(p);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(!file.is_directory()) {
                    fs::path p = std::filesystem::relative(file, dirPath);
                    if(!p.empty()) {
                        out.push_back(p);
                    }
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
}

void FileHelper::append_files_from_directory_with_extension(const fs::path &dirPath, std::string extension, std::vector<fs::path> &out, bool recursive) {
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(file.path().extension() == extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(file.path().extension() == extension) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        }
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
}

fs::path FileHelper::get_filename_from_path(const fs::path &path, bool exclude_extension) {
    if(exclude_extension) {
        return path.stem().string();
    } else {
        return path.filename().string();
    }
}

bool FileHelper::does_filename_equal(const fs::path &path, std::string filename, bool exclude_extension) {
    if(exclude_extension) {
        return path.stem().string() == filename;
    } else {
        return path.filename().string() == filename;
    }
}

// Returns the full path, whether filepath is relative or absolute. Returns std::nullopt if the file does not exist.
std::optional<fs::path> FileHelper::determine_full_filepath(fs::path filepath, fs::path localDirectory) {
    if(filepath.is_absolute() && path_exists(filepath)) {
        return filepath;
    } else if(filepath.is_relative() && path_exists(localDirectory / filepath)) {
        return localDirectory / filepath;
    }
    // Last ditch effort and see if the file exists in the localDirectory itself, ignoring whatever path it had before.
    if(path_exists(localDirectory / filepath.filename())) {
        return localDirectory / filepath.filename();
    }
    return std::nullopt;
}

fs::path FileHelper::get_working_directory() {
    return fs::current_path();
}

fs::path FileHelper::get_directory(const fs::path &path) {
    return path.parent_path();
}

void FileHelper::delete_directory(const fs::path &path) {
    if(fs::exists(path)) {
        fs::remove_all(path);
    }
}

void FileHelper::delete_file(const fs::path &path) {
    if(fs::exists(path)) {
        fs::remove(path);
    }
}

void FileHelper::rename(const fs::path &oldPath, const fs::path &newPath) {
    fs::rename(oldPath, newPath);
}

void FileHelper::copy(const fs::path &oldPath, const fs::path &newPath, bool recursive) {
    write_folder_if_it_does_not_exist(newPath);
    
    fs::copy_options options = (recursive) ? fs::copy_options::recursive : fs::copy_options::none;
    options |= fs::copy_options::overwrite_existing;
    
    fs::copy(oldPath, newPath, options);
}

void FileHelper::format_folder_string(fs::path &folderPath) {
    if((!folderPath.empty()) && !StringHelper::ends_with(folderPath.generic_string(), "/")) {
        folderPath += "/";
    }
}

size_t FileHelper::align16(size_t size) {
    return (size + 15) & ~0xF;
}

void FileHelper::byteswap(std::vector<uint8_t> &bytes) {
    size_t numBytes = bytes.size();
    for(size_t i = 0; i < numBytes; i += 2) {
        uint8_t temp = bytes[i];
        bytes[i] = bytes[i + 1];
        bytes[i + 1] = temp;
    }
}

void FileHelper::endianswap(std::vector<uint8_t> &bytes) {
    size_t numBytes = bytes.size();
    uint8_t temp[4];
    for(size_t i = 0; i < numBytes; i += 4) {
        temp[0] = bytes[i + 0];
        temp[1] = bytes[i + 1];
        temp[2] = bytes[i + 2];
        temp[3] = bytes[i + 3];
        bytes[i + 0] = temp[3];
        bytes[i + 1] = temp[2];
        bytes[i + 2] = temp[1];
        bytes[i + 3] = temp[0];
    }
}

std::string FileHelper::get_last_modified_timestamp(const fs::path &path) {
    fs::file_time_type ftime = fs::last_write_time(path);
    
    // Unfortunately, this is the only way that works in C++17.
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>
        (ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    std::time_t t = std::chrono::system_clock::to_time_t(sctp);
    
    std::string out(21, '\0');

    struct tm tmStruct;
#ifdef _WIN32 // Windows
    gmtime_s(&tmStruct, &t);
#else // Linux
    gmtime_r(&t, &tmStruct);
#endif

    strftime(&out[0], out.size(), "%FT%TZ", &tmStruct);
    out.pop_back(); // Removes the null terminator from the string.
    
    return out;
}

void FileHelper::insert_timestamps_from_directory(const fs::path &dirPath, std::unordered_map<fs::path, std::string, PathHash> &timestamps) {
    // TODO: Make this multithreaded?
    for (const auto &filepath : fs::recursive_directory_iterator(dirPath)) {
        timestamps[filepath] = get_last_modified_timestamp(filepath);
    }
}

bool FileHelper::are_files_the_same(const fs::path& file1, const fs::path& file2) {
    std::optional<std::string> noReason = std::nullopt;
    return FileHelper::are_files_the_same(file1, file2, noReason);
}

bool FileHelper::are_files_the_same(const fs::path& file1, const fs::path& file2, std::optional<std::string> &outNotTrueReason) {
    std::stringstream ss;

    // Check if both files exist
    if (!fs::exists(file1)) {
        if (outNotTrueReason.has_value()) {
            ss << file1 << " does not exist!";
            outNotTrueReason.value() = ss.str();
        }
        return false;
    }
    if (!fs::exists(file2)) {
        if (outNotTrueReason.has_value()) {
            ss << file2 << " does not exist!";
            outNotTrueReason.value() = ss.str();
        }
        return false;
    }

    // Check if file sizes are the same
    if (fs::file_size(file1) != fs::file_size(file2)) {
        if (outNotTrueReason.has_value()) {
            ss << "Files are not the same size!";
            ss << std::hex;
            ss << " sizeof(" << file1 << ") = 0x" << fs::file_size(file1);
            ss << ", sizeof(" << file2 << ") = 0x" << fs::file_size(file2);
            ss << std::dec;
            outNotTrueReason.value() = ss.str();
        }
        return false;
    }

    // Open files for reading in binary mode
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    // Compare contents byte by byte
    char ch1, ch2;
    size_t byteOffset = 0;
    while (f1.get(ch1) && f2.get(ch2)) {
        if (ch1 != ch2) {
            if (outNotTrueReason.has_value()) {
                ss << "File bytes do not match! At byte offset ";
                ss << std::hex << "0x" << byteOffset << std::dec;
                outNotTrueReason.value() = ss.str();
            }
            return false;
        }
        byteOffset++;
    }
    return true;
}
