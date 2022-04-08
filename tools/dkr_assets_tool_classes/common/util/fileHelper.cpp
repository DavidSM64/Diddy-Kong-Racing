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
        display_error_and_abort("Error: Path \"", path, "\" does not exist!");
    }
}

bool path_is_directory(std::string strPath) {
    fs::path path(strPath);
    std::error_code ec;
    return fs::is_directory(path, ec);
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

std::vector<std::string> get_filenames_from_directory_without_extension(std::string dirPath, std::string extension) {
    std::vector<std::string> out;
    for (const auto &file : fs::recursive_directory_iterator(dirPath)) {
        std::string path = file.path();
        if(!ends_with(path, extension)) {
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


void copy_file(std::string srcPath, std::string dstPath) {
    fs::copy(srcPath, dstPath, fs::copy_options::overwrite_existing);
}

void recursively_copy_directory(std::string srcPath, std::string dstPath) {
    fs::copy(srcPath, dstPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void delete_directory(std::string dirPath) {
    if(path_exists(dirPath)) {
        fs::remove_all(dirPath);
    }
}

void delete_path(std::string path) {
    if(path_exists(path)) {
        if(path_is_directory(path)) {
            fs::remove_all(path);
        } else {
            fs::remove(path);
        }
    }
}

std::string replace_extension(std::string path, std::string newExtension) {
    return path.substr(0, path.rfind(".")) + newExtension;
}

bool starts_with(const std::string &a, const std::string &b) {
    return a.rfind(b, 0) == 0;
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

std::string calculate_md5(std::vector<uint8_t> &bytes) {
    uint8_t buffer[0x4000];
    uint8_t digest[MD5_DIGEST_LENGTH];

    std::stringstream ss;

    MD5_CTX md5Context;

    MD5_Init(&md5Context);
    MD5_Update(&md5Context, &bytes[0], bytes.size()); 
    int res = MD5_Final(digest, &md5Context);

    if(res == 0) {
        return "";
    }

    // set up stringstream format
    ss << std::hex << std::setfill('0');


    for(uint8_t uc: digest) {
        ss << std::setw(2) << (int)uc;
    }

    return ss.str();
}

std::string calculate_file_md5(std::string filepath) {
    std::vector<uint8_t> bytes = read_binary_file(filepath);
    return calculate_md5(bytes);
}


