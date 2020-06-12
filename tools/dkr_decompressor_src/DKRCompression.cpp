#include "DKRCompression.h"

DKRCompression::DKRCompression()
{
    compressed.SetGame(DKR);
}

DKRCompression::~DKRCompression(void)
{
}

std::vector<uint8_t> DKRCompression::compressBuffer(std::vector<uint8_t>& data) 
{
    int uncompressedSize = data.size();
    int compressedSize = 0;
    
    uint8_t* compressed = dkr_gzip_compress(&data[0], uncompressedSize, 9, &compressedSize);
    
    std::vector<uint8_t> dkr_compressed(compressed + 10, compressed + compressedSize - 8);
    
    dkr_compressed.insert(dkr_compressed.begin(), 0x09); // gzip compression level?
    dkr_compressed.insert(dkr_compressed.begin(), (uncompressedSize >> 24) & 0xFF);
    dkr_compressed.insert(dkr_compressed.begin(), (uncompressedSize >> 16) & 0xFF);
    dkr_compressed.insert(dkr_compressed.begin(), (uncompressedSize >> 8) & 0xFF);
    dkr_compressed.insert(dkr_compressed.begin(), uncompressedSize & 0xFF);
    
    while((dkr_compressed.size() & 0xF) != 0) {
        dkr_compressed.push_back(0); // Pad out compressed file to be 16-byte aligned.
    }
    
    return dkr_compressed;
}

std::vector<uint8_t> DKRCompression::decompressBuffer(std::vector<uint8_t>& data) 
{
    compressed.SetCompressedBuffer(&data[0], data.size());
    
    int fileSize = 0, fileSizeCompressed = 0;
    uint8_t* decompressed = compressed.OutputDecompressedBuffer(fileSize, fileSizeCompressed);
    if(decompressed == NULL) {
        std::cout << "Error decompressing input" << std::endl;
        throw 1;
    }
    std::vector<uint8_t> out(decompressed, decompressed + fileSize);
    delete[] decompressed;
    
    return out;
}

bool DKRCompression::writeBinaryFile(std::vector<uint8_t>& output, std::string filename)
{
    try 
    {
        std::ofstream wf(filename.c_str(), std::ios::out | std::ios::binary);
        for(int i = 0; i < output.size(); i++)
            wf.write((char *)&output[i], 1);
        wf.close();
    } 
    catch (int e)
    {
        return false;
    }
    return true;
}

bool DKRCompression::readBinaryFile(std::vector<uint8_t>& input, std::string filename)
{
    try 
    {
        std::ifstream is;
        is.open(filename.c_str(), std::ios::binary);
        is.seekg(0, std::ios::end);
        size_t filesize = is.tellg();
        is.seekg(0, std::ios::beg);
        input.resize(filesize);
        is.read((char *)input.data(), filesize);
        is.close();
    } 
    catch (int e)
    {
        return false;
    }
    return true;
}