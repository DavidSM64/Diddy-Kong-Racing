#include "fileHelper.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

#include "helpers/debugHelper.h"

std::vector<uint8_t> FileHelper::read_binary_file(const fs::path &filename) {
    DebugHelper::assert(path_exists(filename), "(FileHelper::read_binary_file) Path ", filename, " does not exist!");
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
    DebugHelper::assert(path_exists(filename), "(FileHelper::read_text_file) Path ", filename, " does not exist!");
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = std::min((size_t)t.tellg(), maxSize);
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);
    return buffer;
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
    write_binary_file((const char*)&data[0], data.size(), filepath, ensurePathExists);
}

void FileHelper::write_binary_file(uint8_t *data, size_t dataSize, const fs::path &filepath, bool ensurePathExists) {
    write_binary_file((const char*)data, dataSize, filepath, ensurePathExists);
}

void FileHelper::write_binary_file(const char *data, size_t dataSize, const fs::path &filepath, bool ensurePathExists) {
    if(ensurePathExists) {
        write_folder_if_it_does_not_exist(filepath);
    }
    std::ofstream wf(filepath.c_str(), std::ios::out | std::ios::binary);
    wf.write(data, dataSize);
    wf.close();
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

std::vector<fs::path> FileHelper::get_files_from_directory_with_extension(const fs::path &dirPath, std::string extension, bool recursive) {
    std::vector<fs::path> out;
    try {
        if(recursive) {
            for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
                if(StringHelper::ends_with(file.path(), extension)) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(StringHelper::ends_with(file.path(), extension)) {
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
                if(!StringHelper::ends_with(file.path(), extension)) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(!StringHelper::ends_with(file.path(), extension)) {
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
    } catch(fs::filesystem_error const&) {
        DebugHelper::error("Could not find the directory ", dirPath);
    }
    return out;
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
                if(StringHelper::ends_with(file.path(), extension)) {
                    if(!file.is_directory()) {
                        out.push_back(file);
                    }
                }
            }
        } else {
            for (const auto &file : fs::directory_iterator(dirPath)) {
                if(StringHelper::ends_with(file.path(), extension)) {
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

fs::path FileHelper::get_directory(const fs::path &path) {
    return path.parent_path();
}

void FileHelper::delete_directory(const fs::path &path) {
    if(fs::exists(path)) {
        fs::remove_all(path);
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
    if((!folderPath.empty()) && !StringHelper::ends_with(folderPath, "/")) {
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
    strftime(&out[0], out.size(), "%FT%TZ", gmtime(&t));
    out.pop_back(); // Removes the null terminator from the string.
    
    return out;
}

void FileHelper::insert_timestamps_from_directory(const fs::path &dirPath, std::unordered_map<fs::path, std::string> &timestamps) {
    // TODO: Make this multithreaded?
    for (const auto &filepath : fs::recursive_directory_iterator(dirPath)) {
        timestamps[filepath] = get_last_modified_timestamp(filepath);
    }
}
