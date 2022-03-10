#include "build_levelheader.h"

#define GET_UNKNOWN_VALUE(name, index) get_int_from_json(srcPath, "unknownData", name, index)
#define GET_UNKNOWN_VALUES(out, start, end, name)         \
    for(int i = start; i < end; i++) {               \
        out[i] = GET_UNKNOWN_VALUE(name, i - start); \
    }

BuildLevelHeader::BuildLevelHeader(std::string srcPath, std::string dstPath) {
    std::vector<uint8_t> out(SIZEOF_LEVEL_HEADER);
    
    out[0] = get_enum_value_from_string("World", get_string_from_json(srcPath, "world"));
    out[1] = get_int_from_json(srcPath, "unknownData", "unk1");
    out[2] = get_int_from_json(srcPath, "unknownData", "unk2");
    out[3] = get_int_from_json(srcPath, "unknownData", "unk3");
    GET_UNKNOWN_VALUES(out, 4, 8, "unk4");
    write_big_endian_float(out, 8, get_float_from_json(srcPath, "ceiling-height"));
    GET_UNKNOWN_VALUES(out, 0xC, 0x34, "unkC");
    write_big_endian_halfword(out, 0x34, get_index_from_build_id("ASSET_LEVEL_MODELS", get_string_from_json(srcPath, "model")));
    write_big_endian_halfword(out, 0x36, get_int_from_json(srcPath, "collectables"));
    write_big_endian_halfword(out, 0x38, get_int_from_json(srcPath, "skybox"));
    write_big_endian_halfword(out, 0x3A, get_int_from_json(srcPath, "fog", "unk3A"));
    write_big_endian_halfword(out, 0x3C, get_int_from_json(srcPath, "fog", "unk3C"));
    write_big_endian_halfword(out, 0x3E, get_int_from_json(srcPath, "fog", "red"));
    write_big_endian_halfword(out, 0x40, get_int_from_json(srcPath, "fog", "green"));
    write_big_endian_halfword(out, 0x42, get_int_from_json(srcPath, "fog", "blue"));
    GET_UNKNOWN_VALUES(out, 0x44, 0x4B, "unk44");
    out[0x4B] = get_int_from_json(srcPath, "number-laps");
    out[0x4C] = get_enum_value_from_string("RaceType", get_string_from_json(srcPath, "race-type"));
    out[0x4D] = get_enum_value_from_string("Vehicle", get_string_from_json(srcPath, "default-vehicle"));
    int avaliableVehicles = 0;
    for(int i = 0; i < get_array_length_from_json(srcPath, "available-vehicles"); i++) {
        avaliableVehicles |= 1 << get_enum_value_from_string("Vehicle", get_string_from_json(srcPath, "available-vehicles", i));
    }
    out[0x4E] = avaliableVehicles;
    GET_UNKNOWN_VALUES(out, 0x4F, 0x52, "unk4F");
    out[0x52] = get_int_from_json(srcPath, "music");
    out[0x53] = get_int_from_json(srcPath, "unknownData", "unk53");
    write_big_endian_halfword(out, 0x54, get_int_from_json(srcPath, "instruments"));
    GET_UNKNOWN_VALUES(out, 0x56, 0x74, "unk56");
    for(int i = 0; i < 7; i++) {
        write_big_endian_word(out, 0x74 + (i * 4), get_int_from_json(srcPath, "unknownData", "unk74", i));
    }
    write_big_endian_halfword(out, 0x90, get_int_from_json(srcPath, "unknownData", "weather", "unk90"));
    write_big_endian_halfword(out, 0x92, get_int_from_json(srcPath, "unknownData", "weather", "unk92"));
    out[0x94] = get_int_from_json(srcPath, "unknownData", "weather", "unk94");
    out[0x95] = get_int_from_json(srcPath, "unknownData", "weather", "unk95");
    write_big_endian_halfword(out, 0x96, get_int_from_json(srcPath, "unknownData", "weather", "unk96"));
    write_big_endian_halfword(out, 0x98, get_int_from_json(srcPath, "unknownData", "weather", "unk98"));
    write_big_endian_halfword(out, 0x9A, get_int_from_json(srcPath, "unknownData", "weather", "unk9A"));
    out[0x9C] = get_int_from_json(srcPath, "fov");
    out[0x9D] = get_int_from_json(srcPath, "backgroundColor", "red");
    out[0x9E] = get_int_from_json(srcPath, "backgroundColor", "green");
    out[0x9F] = get_int_from_json(srcPath, "backgroundColor", "blue");
    GET_UNKNOWN_VALUES(out, 0xA0, 0xA4, "unkA0");
    write_big_endian_word(out, 0xA4, get_int_from_json(srcPath, "unknownData", "unkA4"));
    write_big_endian_halfword(out, 0xA8, get_int_from_json(srcPath, "unknownData", "unkA8"));
    write_big_endian_halfword(out, 0xAA, get_int_from_json(srcPath, "unknownData", "unkAA"));
    int pulsatingLights = -1;
    if(json_has_key(srcPath, "pulsating-lights")) {
        pulsatingLights = get_index_from_build_id("ASSET_MISC", get_string_from_json(srcPath, "pulsating-lights"));
    }
    write_big_endian_word(out, 0xAC, pulsatingLights);
    GET_UNKNOWN_VALUES(out, 0xB0, 0xC4, "unkB0");
    write_big_endian_word(out, 0xC4, get_int_from_json(srcPath, "unknownData", "unkC4"));
    
    write_binary_file(out, dstPath);
}

BuildLevelHeader::~BuildLevelHeader() {
    
}
