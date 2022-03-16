#include "fileHelper.h"

std::string assetsFolderPath = "";
std::string version = "";

bool is_asset_folder_path_defined() {
    return assetsFolderPath != "";
}

void set_assets_folder_path(std::string path) {
    assetsFolderPath = path;
}

std::string get_asset_folder_path() {
    return assetsFolderPath;
}

void set_version(std::string ver) {
    version = ver;
}

std::string get_version() {
    return version;
}

std::vector<uint8_t> read_binary_file(std::string filename) {
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

void write_binary_file(std::vector<uint8_t> &data, std::string filepath) {
    std::ofstream wf(filepath.c_str(), std::ios::out | std::ios::binary);
    wf.write((char *)&data[0], data.size());
    wf.close();
}

std::string read_text_file(std::string filename) {
    std::ifstream t(filename);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return buffer;
}

void write_text_file(std::string text, std::string filepath) {
    std::ofstream myfile;
    myfile.open(filepath);
    myfile << text;
    myfile.close();
}

bool path_exists(std::string path) {
    return fs::exists(path);
}

void path_must_exist(std::string path) {
    if(!fs::exists(path)) {
        std::cout << "Error: Path \"" << path << "\" does not exist!" << std::endl;
        throw 1;
    }
}

std::vector<std::string> get_filenames_from_directory(std::string dirPath) {
    std::vector<std::string> out;
    for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
        out.push_back(file.path());
    }
    return out;
}

std::vector<std::string> get_filenames_from_directory_only(std::string dirPath) {
    std::vector<std::string> out;
    for (const auto &file : fs::directory_iterator(dirPath)) {
        out.push_back(file.path());
    }
    return out;
}

std::vector<fs::path> get_filenames_from_directory_only_with_extension(std::string dirPath, std::string extension) {
    std::vector<fs::path> out;
    for (const auto &file : fs::directory_iterator(dirPath)) {
        fs::path path = file.path();
        if(ends_with(path, extension)) {
            out.push_back(path);
        }
    }
    return out;
}


std::vector<fs::path> get_folders_from_directory_only(std::string dirPath) {
    std::vector<fs::path> out;
    for (const auto &file : fs::directory_iterator(dirPath)) {
        if(file.is_directory()) {
            out.push_back(file.path());
        }
    }
    return out;
}

std::vector<std::string> get_filenames_from_directory_with_extension(std::string dirPath, std::string extension) {
    std::vector<std::string> out;
    for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
        std::string path = file.path();
        if(ends_with(path, extension)) {
            out.push_back(path);
        }
    }
    return out;
}

void create_directory(std::string directory) {
    if(!fs::is_directory(directory)) {
        fs::create_directories(directory);
    }
}

std::string get_filename_from_full_path(std::string path, bool excludeExtension) {
    size_t lastSlash = path.rfind("/");
    if (lastSlash != std::string::npos) {
        path = path.substr(lastSlash + 1);
    }
    if(excludeExtension) {
        size_t dot = path.find(".");
        if (dot != std::string::npos) {
            path = path.substr(0, dot);
        }
    }
    return path;
}

std::string get_directory_from_full_path(std::string path) {
    return path.substr(0, path.rfind("/"));
}

void ensure_that_path_exists(std::string path) {
    if(path_exists(path)) {
        return;
    }
    create_directory(get_directory_from_full_path(path));
}

void recursively_copy_directory(std::string srcPath, std::string dstPath) {
    fs::copy(srcPath, dstPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void delete_directory(std::string dirPath) {
    if(path_exists(dirPath)) {
        fs::remove_all(dirPath);
    }
}

std::string replace_extension(std::string path, std::string newExtension) {
    return path.substr(0, path.rfind(".")) + newExtension;
}

bool ends_with(const std::string &a, const std::string &b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

void make_lowercase(std::string& input) {
    for(char& character : input) {
        character = std::tolower(character);
    }
}

void make_uppercase(std::string& input) {
    for(char& character : input) {
        character = std::toupper(character);
    }
}

