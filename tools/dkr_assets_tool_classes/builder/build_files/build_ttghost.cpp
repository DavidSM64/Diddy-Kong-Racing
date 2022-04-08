#include "build_ttghost.h"

#include <chrono>

BuildTTGhost::BuildTTGhost(std::string srcPath, std::string dstPath) {
    int numberOfNodes = get_array_length_from_json(srcPath, "nodes");
    
    std::vector<uint8_t> out(align16(SIZEOF_TTGHOST_HEADER + numberOfNodes * SIZEOF_TTGHOST_NODE));
    
    // Write header
    out[0] = get_index_from_build_id("ASSET_LEVEL_HEADERS", get_string_from_json(srcPath, "header", "level")); // get_int_from_json(srcPath, "header", "level");
    out[1] = get_enum_value_from_string("Vehicle", get_string_from_json(srcPath, "header", "vehicle"));
    out[2] = 9; // Always 9?
    write_big_endian_halfword(out, 4, get_int_from_json(srcPath, "header", "time"));
    write_big_endian_halfword(out, 6, numberOfNodes);
    
    // Write the nodes
    for(int i = 0; i < numberOfNodes; i++) {
        int offset = (i * SIZEOF_TTGHOST_NODE) + SIZEOF_TTGHOST_HEADER;
        write_big_endian_halfword(out, offset,      get_int_from_json(srcPath, "nodes", i, "x"));
        write_big_endian_halfword(out, offset + 2,  get_int_from_json(srcPath, "nodes", i, "y"));
        write_big_endian_halfword(out, offset + 4,  get_int_from_json(srcPath, "nodes", i, "z"));
        // Yes, this order is correct.
        write_big_endian_halfword(out, offset + 6,  get_int_from_json(srcPath, "nodes", i, "rz"));
        write_big_endian_halfword(out, offset + 8,  get_int_from_json(srcPath, "nodes", i, "rx"));
        write_big_endian_halfword(out, offset + 10, get_int_from_json(srcPath, "nodes", i, "ry"));
    }
    
    write_binary_file(out, dstPath);
}

BuildTTGhost::~BuildTTGhost() {
}
