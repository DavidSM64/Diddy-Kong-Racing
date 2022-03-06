#include "extract_levelheader.h"

ExtractLevelHeader::ExtractLevelHeader(std::string key, std::vector<uint8_t> data, std::string outFilepath) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "LevelHeaders";
    out["unknownData"] = json::Object();
    out["world"] = get_enum_string_from_value("World", (int8_t)data[0]); 
    out["unknownData"]["unk1"] = data[1];
    out["unknownData"]["unk2"] = data[2];
    out["unknownData"]["unk3"] = data[3];
    out["unknownData"]["unk4"] = json::Array();
    for(int i = 4; i < 8; i++) {
        out["unknownData"]["unk4"].append(data[i]);
    }
    out["ceiling-height"] = get_big_endian_float(data, 8);
    out["unknownData"]["unkC"] = json::Array();
    for(int i = 0xC; i < 0x34; i++) {
        out["unknownData"]["unkC"].append(data[i]);
    }
    int modelId = get_big_endian_halfword(data, 0x34);
    out["model"] = get_build_id_from_section("ASSET_LEVEL_MODELS", modelId);
    out["collectables"] = get_big_endian_halfword(data, 0x36);
    out["skybox"] = get_big_endian_halfword(data, 0x38);
    out["fog"] = json::Object();
    out["fog"]["unk3A"] = get_big_endian_halfword(data, 0x3A);
    out["fog"]["unk3C"] = get_big_endian_halfword(data, 0x3C);
    out["fog"]["red"] = get_big_endian_halfword(data, 0x3E);
    out["fog"]["green"] = get_big_endian_halfword(data, 0x40);
    out["fog"]["blue"] = get_big_endian_halfword(data, 0x42);
    for(int i = 0x44; i < 0x4B; i++) {
        out["unknownData"]["unk44"].append(data[i]);
    }
    out["number-laps"] = data[0x4B];
    out["race-type"] = get_enum_string_from_value("RaceType", data[0x4C]);
    out["default-vehicle"] = get_enum_string_from_value("Vehicle", data[0x4D]);
    out["available-vehicles"] = json::Array();
    int avaliableVehicles = data[0x4E];
    for(int i = 0; i < 3; i++) {
        if(avaliableVehicles & (1 << i)) {
            out["available-vehicles"].append(get_enum_string_from_value("Vehicle", i));
        }
    }
    out["unknownData"]["unk4F"] = json::Array();
    for(int i = 0x4F; i < 0x52; i++) {
        out["unknownData"]["unk4F"].append(data[i]);
    }
    out["music"] = data[0x52];
    out["unknownData"]["unk53"] = data[0x53];
    out["instruments"] = get_big_endian_halfword(data, 0x54);
    out["unknownData"]["unk56"] = json::Array();
    for(int i = 0x56; i < 0x74; i++) {
        out["unknownData"]["unk56"].append(data[i]);
    }
    out["unknownData"]["unk74"] = json::Array();
    for(int i = 0; i < 7; i++) {
        int ptr = get_big_endian_word(data, 0x74 + (i*4));
        out["unknownData"]["unk74"].append(ptr);
    }
    out["unknownData"]["weather"] = json::Object();
    out["unknownData"]["weather"]["unk90"] = (int)get_big_endian_halfword(data, 0x90);
    out["unknownData"]["weather"]["unk92"] = (int)get_big_endian_halfword(data, 0x92);
    out["unknownData"]["weather"]["unk94"] = data[0x94];
    out["unknownData"]["weather"]["unk95"] = data[0x95];
    out["unknownData"]["weather"]["unk96"] = (int)get_big_endian_halfword(data, 0x96);
    out["unknownData"]["weather"]["unk98"] = (int)get_big_endian_halfword(data, 0x98);
    out["unknownData"]["weather"]["unk9A"] = (int)get_big_endian_halfword(data, 0x9A);
    out["fov"] = data[0x9C];
    out["backgroundColor"] = json::Object();
    out["backgroundColor"]["red"] = data[0x9D];
    out["backgroundColor"]["green"] = data[0x9E];
    out["backgroundColor"]["blue"] = data[0x9F];
    out["unknownData"]["unkA0"] = json::Array();
    for(int i = 0xA0; i < 0xA4; i++) {
        out["unknownData"]["unkA0"].append(data[i]);
    }
    out["unknownData"]["unkA4"] = (int)get_big_endian_word(data, 0xA4);
    out["unknownData"]["unkA8"] = (int)get_big_endian_halfword(data, 0xA8);
    out["unknownData"]["unkAA"] = (int)get_big_endian_halfword(data, 0xAA);
    int pulsatingLightsOffset = (int)get_big_endian_word(data, 0xAC); 
    if(pulsatingLightsOffset != -1) {
        out["pulsating-lights"] = get_build_id_from_section("ASSET_MISC", pulsatingLightsOffset); 
    }
    out["unknownData"]["unkB0"] = json::Array();
    for(int i = 0xB0; i < 0xC4; i++) {
        out["unknownData"]["unkB0"].append(data[i]);
    }
    out["unknownData"]["unkC4"] = (int)get_big_endian_word(data, 0xC4);
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractLevelHeader::~ExtractLevelHeader(){
}
