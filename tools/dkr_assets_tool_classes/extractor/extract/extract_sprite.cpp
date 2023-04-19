#include "extract_sprite.h"

ExtractSprite::ExtractSprite(std::string key, std::vector<uint8_t> data, std::string outFilepath, 
json::JSON &configJSON) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "Sprites";
    out["start-texture"] = get_build_id_from_section("ASSET_TEXTURES_2D", get_big_endian_halfword(data, 0));
    //out["number-of-frames"] = get_big_endian_halfword(data, 2);
    out["unk4"] = get_big_endian_halfword(data, 4);
    out["unk6"] = get_big_endian_halfword(data, 6);
    out["frame-tex-count"] = json::Array();
    
    int count = get_big_endian_halfword(data, 2);
    int curOffset = 0x0D;

    for(int i = 0; i < count; i++) {
        out["frame-tex-count"].append(data[curOffset] - data[curOffset - 1]);
        curOffset++;
    }
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractSprite::~ExtractSprite(){
}
