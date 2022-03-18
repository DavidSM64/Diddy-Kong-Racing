#include "rom.h"

ROM::ROM(std::string filename){
    if(!readROMFile(filename)) {
        // ROM failed to load.
        throw 1;
    }
    romFilename = filename;
    
    test_endianness();
    calculate_md5();
}

ROM::~ROM(){
}

std::vector<uint8_t> ROM::get_bytes_from_range(int start, int numBytes){
    std::vector<uint8_t> subVector(numBytes);
    std::copy(bytes.begin() + start, bytes.begin() + start + numBytes, subVector.begin());
    return subVector;
}

uint8_t ROM::get_byte(int romOffset){
    return bytes[romOffset];
}

uint32_t ROM::get_uint(int romOffset){
    return (bytes[romOffset] << 24) | (bytes[romOffset + 1] << 16) | (bytes[romOffset + 2] << 8) | bytes[romOffset + 3];
}

std::string ROM::get_md5(){
    return md5;
}

int ROM::get_size(){
    return bytes.size();
}

bool ROM::is_valid() {
    return isValid;
}

void ROM::test_endianness(){
    bool convertedToBigEndian = false;
    isValid = true;
    if(bytes[0] == 0x80 && bytes[1] == 0x37) { // Big endian
        // Do nothing
    } else if(bytes[0] == 0x37 && bytes[1] == 0x80) { // Mixed endian (byteswapped)
        // Mixed endian, convert to big endian
        int numBytes = get_size();
        for(int i = 0; i < numBytes; i+=2) {
            uint8_t temp = bytes[i];
            bytes[i] = bytes[i + 1];
            bytes[i + 1] = temp;
        }
        convertedToBigEndian = true;
    } else if(bytes[0] == 0x40 && bytes[1] == 0x12) { // Little endian
        // Little endian, convert to big endian
        int numBytes = get_size();
        uint8_t temp[4];
        for(int i = 0; i < numBytes; i+=4) {
            temp[0] = bytes[i + 0];
            temp[1] = bytes[i + 1];
            temp[2] = bytes[i + 2];
            temp[3] = bytes[i + 3];
            bytes[i + 0] = temp[3];
            bytes[i + 1] = temp[2];
            bytes[i + 2] = temp[1];
            bytes[i + 3] = temp[0];
        }
        convertedToBigEndian = true;
    } else {
        isValid = false;
        return;
    }
    
    if(convertedToBigEndian) { // Overwrite ROM file
        fs::remove(fs::path(romFilename)); // Delete old romfile
        std::string z64Filename = romFilename.substr(0, romFilename.length() - 4) + ".z64";
        if(!writeROMFile(z64Filename)) { // Save new big-endian rom.
            // ROM failed to save.
            isValid = false;
            return;
        }
    }
}

void ROM::calculate_md5() {
    uint8_t buffer[0x4000];
    uint8_t digest[MD5_DIGEST_LENGTH];

    std::stringstream ss;

    MD5_CTX md5Context;

    MD5_Init(&md5Context);
    MD5_Update(&md5Context, &bytes[0], bytes.size()); 
    int res = MD5_Final(digest, &md5Context);

    if(res == 0){ // hash failed or raise an exception
        md5 = "";
        return;
    }

    // set up stringstream format
    ss << std::hex << std::setfill('0');


    for(uint8_t uc: digest) {
        ss << std::setw(2) << (int)uc;
    }

    md5 = ss.str();
}

bool ROM::readROMFile(std::string filename) {
    try 
    {
        std::ifstream is;
        is.open(filename.c_str(), std::ios::binary);
        is.seekg(0, std::ios::end);
        size_t filesize = is.tellg();
        is.seekg(0, std::ios::beg);
        bytes.resize(filesize);
        is.read((char *)bytes.data(), filesize);
        is.close();
    } 
    catch (int e)
    {
        return false;
    }
    return true;
}

bool ROM::writeROMFile(std::string filename) {
    try 
    {
        std::ofstream wf(filename.c_str(), std::ios::out | std::ios::binary);
        for(int i = 0; i < bytes.size(); i++)
            wf.write((char *)&bytes[i], 1);
        wf.close();
    } 
    catch (int e)
    {
        return false;
    }
    return true;
}