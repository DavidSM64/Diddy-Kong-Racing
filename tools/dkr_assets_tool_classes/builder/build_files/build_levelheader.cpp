#include "build_levelheader.h"

#define GET_UNKNOWN_VALUE(name, index) get_int_from_json(srcPath, "unknown-data", name, index)
#define GET_UNKNOWN_VALUES(out, start, end, name)         \
    for(int i = start; i < end; i++) {               \
        out[i] = GET_UNKNOWN_VALUE(name, i - start); \
    }

int get_bitfield_from_enum_values(std::string &srcPath, std::string propertyName, std::string enumName) {
    int numEntries = get_array_length_from_json(srcPath, propertyName);
    int out = 0;
    for(int i = 0; i < numEntries; i++) {
        out |= 1 << get_enum_value_from_string(enumName, get_string_from_json(srcPath, propertyName, i));
    }
    return out;
}

BuildLevelHeader::BuildLevelHeader(std::string srcPath, std::string dstPath) {
    std::vector<uint8_t> out(SIZEOF_LEVEL_HEADER);

    // World ID
    out[0] = get_enum_value_from_string("World", get_string_from_json(srcPath, "world"));

    out[1] = get_int_from_json(srcPath, "unknown-data", "unk1");
    out[2] = get_int_from_json(srcPath, "unknown-data", "unk2");
    out[3] = get_int_from_json(srcPath, "unknown-data", "unk3");
    GET_UNKNOWN_VALUES(out, 4, 8, "unk4");

    // Ceiling height for planes
    write_big_endian_float(out, 8, get_float_from_json(srcPath, "ceiling-height"));

    GET_UNKNOWN_VALUES(out, 0xC, 0x34, "unkC");

    // Track ID to use
    write_big_endian_halfword(out, 0x34, get_index_from_build_id("ASSET_LEVEL_MODELS", get_string_from_json(srcPath, "model")));

    // Collectables bitflags (bananas, balloons, etc)
    write_big_endian_halfword(out, 0x36, get_int_from_json(srcPath, "collectables"));

    // Skydome object model ID
    write_big_endian_halfword(out, 0x38, get_int_from_json(srcPath, "skybox"));

    // Fog
    write_big_endian_halfword(out, 0x3A, get_int_from_json(srcPath, "fog", "range", "min"));
    write_big_endian_halfword(out, 0x3C, get_int_from_json(srcPath, "fog", "range", "max"));
    write_big_endian_halfword(out, 0x3E, get_int_from_json(srcPath, "fog", "colour", "red"));
    write_big_endian_halfword(out, 0x40, get_int_from_json(srcPath, "fog", "colour", "green"));
    write_big_endian_halfword(out, 0x42, get_int_from_json(srcPath, "fog", "colour", "blue"));

    GET_UNKNOWN_VALUES(out, 0x44, 0x4B, "unk44");

    // Number of laps to complete the race.
    out[0x4B] = get_int_from_json(srcPath, "number-laps");

    // Type of race (standard, boss race, hub world, etc.
    out[0x4C] = get_enum_value_from_string("RaceType", get_string_from_json(srcPath, "race-type"));

    // Default vehicle used for this track. (Either Car, Hovercraft, or Plane)
    out[0x4D] = get_enum_value_from_string("Vehicle", get_string_from_json(srcPath, "default-vehicle"));

    // Which vehicles can be used in this track (Either Car, Hovercraft, or Plane)
    out[0x4E] = get_bitfield_from_enum_values(srcPath, "available-vehicles", "Vehicle");
    GET_UNKNOWN_VALUES(out, 0x4F, 0x52, "unk4F");

    // Music ID to use for this track
    out[0x52] = get_int_from_json(srcPath, "music");

    // Unknown, but *probably* related to audio.
    out[0x53] = get_int_from_json(srcPath, "unknown-data", "unk53");

    // Instruments bitflags. Most levels have 0xFFFF, except for the central hub which is 0xB
    write_big_endian_halfword(out, 0x54, get_int_from_json(srcPath, "instruments"));

    GET_UNKNOWN_VALUES(out, 0x56, 0x74, "unk56");
    for(int i = 0; i < 7; i++) {
        write_big_endian_word(out, 0x74 + (i * 4), get_int_from_json(srcPath, "unknown-data", "unk74", i));
    }

    // Weather values currently unknown.
    write_big_endian_halfword(out, 0x90, get_int_from_json(srcPath, "unknown-data", "weather", "particle-density"));
    write_big_endian_halfword(out, 0x92, get_int_from_json(srcPath, "unknown-data", "weather", "type"));
    out[0x94] = get_int_from_json(srcPath, "unknown-data", "weather", "intensity");
    out[0x95] = get_int_from_json(srcPath, "unknown-data", "weather", "opacity");
    write_big_endian_halfword(out, 0x96, get_int_from_json(srcPath, "unknown-data", "weather", "x-velocity"));
    write_big_endian_halfword(out, 0x98, get_int_from_json(srcPath, "unknown-data", "weather", "y-velocity"));
    write_big_endian_halfword(out, 0x9A, get_int_from_json(srcPath, "unknown-data", "weather", "z-velocity"));

    // Field of view
    out[0x9C] = get_int_from_json(srcPath, "fov");

    // Background clear color
    out[0x9D] = get_int_from_json(srcPath, "background-colour", "red");
    out[0x9E] = get_int_from_json(srcPath, "background-colour", "green");
    out[0x9F] = get_int_from_json(srcPath, "background-colour", "blue");

    GET_UNKNOWN_VALUES(out, 0xA0, 0xA4, "unkA0");
    write_big_endian_word(out, 0xA4, get_int_from_json(srcPath, "unknown-data", "unkA4"));
    write_big_endian_halfword(out, 0xA8, get_int_from_json(srcPath, "unknown-data", "unkA8"));
    write_big_endian_halfword(out, 0xAA, get_int_from_json(srcPath, "unknown-data", "unkAA"));

    // Pulsating lights are only used in spaceport alpha
    int pulsatingLights = -1;
    if(json_has_key(srcPath, "pulsating-lights")) {
        pulsatingLights = get_index_from_build_id("ASSET_MISC", get_string_from_json(srcPath, "pulsating-lights"));
    }
    write_big_endian_word(out, 0xAC, pulsatingLights);

    GET_UNKNOWN_VALUES(out, 0xB0, 0xC4, "unkB0");
    write_big_endian_word(out, 0xC4, get_int_from_json(srcPath, "unknown-data", "unkC4"));

    write_binary_file(out, dstPath);
}

BuildLevelHeader::~BuildLevelHeader() {

}
