#include "extract_levelheader.h"

// Extracts a bitfield as an array of enum value strings.
json::JSON extract_enum_values(std::vector<uint8_t> &data, int offset, int numBytes, std::string enumName) {
    json::JSON values = json::Array();
    int bitflags = 0;
    for(int i = 0; i < numBytes; i++) {
        bitflags |= data[offset + i] << (8 * i);
    }
    for(int i = 0; bitflags != 0; i++) {
        if(bitflags & 1) {
            values.append(get_enum_string_from_value(enumName, i));
        }
        bitflags >>= 1;
    }
    return values;
}

ExtractLevelHeader::ExtractLevelHeader(std::string key, std::vector<uint8_t> data, std::string outFilepath) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "LevelHeaders";
    out["unknown-data"] = json::Object();

    // World ID
    out["world"] = get_enum_string_from_value("World", (int8_t)data[0]);

    out["unknown-data"]["unk1"] = data[1];
    out["unknown-data"]["unk2"] = data[2];
    out["unknown-data"]["unk3"] = data[3];
    out["unknown-data"]["unk4"] = json::Array();
    for(int i = 4; i < 8; i++) {
        out["unknown-data"]["unk4"].append(data[i]);
    }

    // Ceiling height for planes
    out["ceiling-height"] = get_big_endian_float(data, 8);

    out["unknown-data"]["unkC"] = json::Array();
    for(int i = 0xC; i < 0x34; i++) {
        out["unknown-data"]["unkC"].append(data[i]);
    }
    
    // Track Model ID to use
    int modelId = get_big_endian_halfword(data, 0x34);
    out["model"] = get_build_id_from_section("ASSET_LEVEL_MODELS", modelId);

    // Collectables bitflags (bananas, balloons, etc)
    out["collectables"] = get_big_endian_halfword(data, 0x36);

    // Skydome object model ID
    out["skybox"] = get_big_endian_halfword(data, 0x38);

    // Fog
    out["fog"] = json::Object();
    out["fog"]["range"] = json::Object();
    out["fog"]["range"]["min"] = get_big_endian_halfword(data, 0x3A);
    out["fog"]["range"]["max"] = get_big_endian_halfword(data, 0x3C);
    out["fog"]["colour"] = json::Object();
    out["fog"]["colour"]["red"] = get_big_endian_halfword(data, 0x3E);
    out["fog"]["colour"]["green"] = get_big_endian_halfword(data, 0x40);
    out["fog"]["colour"]["blue"] = get_big_endian_halfword(data, 0x42);

    for(int i = 0x44; i < 0x4B; i++) {
        out["unknown-data"]["unk44"].append(data[i]);
    }
    
    // Number of laps to complete the race
    out["number-laps"] = data[0x4B];

    // Type of race (standard, boss race, hub world, etc.
    out["race-type"] = get_enum_string_from_value("RaceType", data[0x4C]);

    // Default vehicle used for this track. (Either Car, Hovercraft, or Plane)
    out["default-vehicle"] = get_enum_string_from_value("Vehicle", data[0x4D]);

    // Which vehicles can be used in this track (Either Car, Hovercraft, or Plane)
    out["available-vehicles"] = extract_enum_values(data, 0x4E, 1, "Vehicle");

    out["unknown-data"]["unk4F"] = json::Array();
    for(int i = 0x4F; i < 0x52; i++) {
        out["unknown-data"]["unk4F"].append(data[i]);
    }
    out["music"] = data[0x52];
    out["unknown-data"]["unk53"] = data[0x53];
    out["instruments"] = get_big_endian_halfword(data, 0x54);
    out["unknown-data"]["unk56"] = json::Array();
    for(int i = 0x56; i < 0x74; i++) {
        out["unknown-data"]["unk56"].append(data[i]);
    }
    out["unknown-data"]["unk74"] = json::Array();
    for(int i = 0; i < 7; i++) {
        int ptr = get_big_endian_word(data, 0x74 + (i*4));
        out["unknown-data"]["unk74"].append(ptr);
    }
    out["unknown-data"]["weather"] = json::Object();
    out["unknown-data"]["weather"]["particle-density"] = (int)get_big_endian_halfword(data, 0x90);
    out["unknown-data"]["weather"]["type"] = (int)get_big_endian_halfword(data, 0x92);
    out["unknown-data"]["weather"]["intensity"] = data[0x94];
    out["unknown-data"]["weather"]["opacity"] = data[0x95];
    out["unknown-data"]["weather"]["x-velocity"] = (int)get_big_endian_halfword(data, 0x96);
    out["unknown-data"]["weather"]["y-velocity"] = (int)get_big_endian_halfword(data, 0x98);
    out["unknown-data"]["weather"]["z-velocity"] = (int)get_big_endian_halfword(data, 0x9A);
    out["fov"] = data[0x9C];
    out["background-colour"] = json::Object();
    out["background-colour"]["red"] = data[0x9D];
    out["background-colour"]["green"] = data[0x9E];
    out["background-colour"]["blue"] = data[0x9F];
    out["unknown-data"]["unkA0"] = json::Array();
    for(int i = 0xA0; i < 0xA4; i++) {
        out["unknown-data"]["unkA0"].append(data[i]);
    }
    out["unknown-data"]["unkA4"] = (int)get_big_endian_word(data, 0xA4);
    out["unknown-data"]["unkA8"] = (int)get_big_endian_halfword(data, 0xA8);
    out["unknown-data"]["unkAA"] = (int)get_big_endian_halfword(data, 0xAA);
    int pulsatingLightsOffset = (int)get_big_endian_word(data, 0xAC); 
    if(pulsatingLightsOffset != -1) {
        out["pulsating-lights"] = get_build_id_from_section("ASSET_MISC", pulsatingLightsOffset); 
    }
    out["unknown-data"]["unkB0"] = json::Array();
    for(int i = 0xB0; i < 0xC4; i++) {
        out["unknown-data"]["unkB0"].append(data[i]);
    }
    out["unknown-data"]["unkC4"] = (int)get_big_endian_word(data, 0xC4);
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractLevelHeader::~ExtractLevelHeader(){
}
