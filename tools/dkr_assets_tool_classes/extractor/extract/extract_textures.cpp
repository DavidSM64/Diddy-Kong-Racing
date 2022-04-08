#include "extract_textures.h"

ExtractTextures::ExtractTextures(std::string key, std::vector<uint8_t> data, std::string outFilepath,
    std::unordered_map<std::string, std::string> *tags) 
: Extract(key, data, outFilepath) {
    std::string directory = get_directory_from_full_path(outFilepath);
    std::string filename = get_filename_from_full_path(outFilepath, true);
    ensure_that_path_exists(directory + "/img/");
    
    json::JSON out = json::Object();
    int format = data[2] & 0xF;
    int numberOfTextures = data[0x12];
    
    out["type"] = "Textures";
    out["width"] = data[0];
    out["height"] = data[1];
    out["format"] = get_texture_format_string(format);
    out["tex-type"] = (data[2] >> 4) & 0xF;
    
    if(tags != nullptr) {
        out["flipped-image"] = (*tags)["flip-texture_" + key] == "true";
    }
    
    if(data[3] != 0 || data[4] != 0) {
        out["sprite-x"] = data[3];
        out["sprite-y"] = data[4];
    }
    
    int flags = get_big_endian_halfword(data, 6);
    
    out["flags"] = json::Object();
    
    // TODO: Figure out all the flags
    out["flags"]["flag-01"]    = flags & 0x0001 ?    true : false;
    out["flags"]["flag-04"]    = flags & 0x0004 ?    true : false;
    out["flags"]["flag-10"]    = flags & 0x0010 ?    true : false;
    out["flags"]["wrap-s"]     = flags & 0x0040 ? "Clamp" : "Wrap";
    out["flags"]["wrap-t"]     = flags & 0x0080 ? "Clamp" : "Wrap";
    out["flags"]["interlaced"] = flags & 0x0400 ?    true : false;
    
    if(format == TEX_FORMAT_CI4 || format == TEX_FORMAT_CI8) {
        // TODO: Replace integer offset with label.
        out["palette-offset"] = get_big_endian_halfword(data, 8);
    }
    
    out["frame-count"] = numberOfTextures;
    
    if(numberOfTextures > 1) {
        out["frame-advance-delay"] = get_big_endian_halfword(data, 0x14);
    }
    
    out["compressed"] = data[0x1D] != 0;
    
    out["img"] = "img/" + filename + ".png";

    out["write-size"] = (get_big_endian_halfword(data, 0x16) != 0);
    
    write_images(directory + "/" + out["img"].ToString(), data, out);
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractTextures::~ExtractTextures(){
}

void deinterlace_texture(std::vector<uint8_t>& texData, int width, int height, int format) {
    switch(format) {
        case TEX_FORMAT_RGBA32:
        {
            deinterlace(texData, 0, width, height, 32, 8);
            return;
        }
        case TEX_FORMAT_RGBA16:
        case TEX_FORMAT_IA16:
        {
            deinterlace(texData, 0, width, height, 16, 4);
            return;
        }
        case TEX_FORMAT_I8:
        case TEX_FORMAT_IA8:
        {
            deinterlace(texData, 0, width, height, 8, 4);
            return;
        }
        case TEX_FORMAT_I4:
        case TEX_FORMAT_IA4:
        {
            deinterlace(texData, 0, width, height, 4, 4);
            return;
        }
    }
}

void ExtractTextures::write_images(std::string outImagePath, std::vector<uint8_t> &data, json::JSON &out) {
    std::vector<uint8_t> texData;
    
    if(out["compressed"].ToBool()) {
        std::vector<uint8_t> compressedData(data.begin() + TEX_HEADER_SIZE, data.end());
        texData = decompress_dkr_gzip(compressedData);
    } else {
        texData = data;
    }
    
    int numberOfTextures = out["frame-count"].ToInt();
    int width = out["width"].ToInt();
    int height = out["height"].ToInt();
    int format = get_texture_format_from_string(out["format"].ToString());
    bool isInterlaced = out["flags"]["interlaced"].ToBool();
    bool shouldFlip = out["flipped-image"].ToBool();
    
    std::vector<uint8_t> combinedTexturesData;
    int dataOffset = 0;
    
    if(numberOfTextures > 1) {
        for(int i = 0; i < numberOfTextures; i++){
            int textureSize = get_texture_size(width, height, format);
            
            std::vector<uint8_t> texDataPart(texData.begin() + dataOffset + TEX_HEADER_SIZE, texData.begin() + dataOffset + textureSize);
            
            // Deinterlacing must come before flipping the texture.
            if(isInterlaced) {
                deinterlace_texture(texDataPart, width, height, format);
            }
            if(shouldFlip) {
                flip_texture_vertically(texDataPart, 0, width, height, format);
            }
            
            combinedTexturesData.insert(combinedTexturesData.end(), texDataPart.begin(), texDataPart.end());
            
            dataOffset += textureSize;
        }
    } else {
        combinedTexturesData = std::vector<uint8_t>(texData.begin() + TEX_HEADER_SIZE, texData.end());
        
        // Deinterlacing must come before flipping the texture.
        if(isInterlaced) {
            deinterlace_texture(combinedTexturesData, width, height, format);
        }
        if(shouldFlip) {
            flip_texture_vertically(combinedTexturesData, 0, width, height, format);
        }
    }
    
    int totalHeight = height * numberOfTextures;
    
    switch(format) {
        case TEX_FORMAT_RGBA32:
        {
            rgba2png(outImagePath.c_str(), (const rgba*)&combinedTexturesData[0], width, totalHeight);
            break;
        }
        case TEX_FORMAT_RGBA16:
        {
            rgba *outTex = raw2rgba(&combinedTexturesData[0], width, totalHeight, 16);
            rgba2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_I8:
        {
            ia *outTex = raw2i(&combinedTexturesData[0], width, totalHeight, 8);
            ia2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_I4:
        {
            ia *outTex = raw2i(&combinedTexturesData[0], width, totalHeight, 4);
            ia2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_IA16:
        {
            ia *outTex = raw2ia(&combinedTexturesData[0], width, totalHeight, 16);
            ia2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_IA8:
        {
            ia *outTex = raw2ia(&combinedTexturesData[0], width, totalHeight, 8);
            ia2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_IA4:
        {
            ia *outTex = raw2ia(&combinedTexturesData[0], width, totalHeight, 4);
            ia2png(outImagePath.c_str(), outTex, width, totalHeight);
            break;
        }
        case TEX_FORMAT_CI4:
        case TEX_FORMAT_CI8:
        {
            display_error_and_abort("CI texture formats are not currently supported.");
        }
        default: // Invalid texture format
        {
            display_error_and_abort("Unknown texture format ", format);
        }
    }
}





