#include "build_sprite.h"

#define SIZEOF_SPRITE_HEADER 12

BuildSprite::BuildSprite(std::string srcPath, std::string dstPath) {
    int numberOfFrames = get_array_length_from_json(srcPath, "frame-tex-count");
    
    std::vector<uint8_t> out(align16(SIZEOF_SPRITE_HEADER + numberOfFrames + 1));
    
    // Write header
    write_big_endian_halfword(out, 0, get_tex_2d_index_from_build_id(get_string_from_json(srcPath, "start-texture")));
    write_big_endian_halfword(out, 2, numberOfFrames);
    write_big_endian_halfword(out, 4, get_int_from_json(srcPath, "unk4"));
    write_big_endian_halfword(out, 6, get_int_from_json(srcPath, "unk6"));
    // The word at offset 8 is always zero in the rom.
    
    int texOffset = 0;
    
    for(int i = 0; i < numberOfFrames + 1; i++) {
        out[SIZEOF_SPRITE_HEADER + i] = texOffset;
        texOffset += get_int_from_json(srcPath, "frame-tex-count", i);
    }
    
    write_binary_file(out, dstPath);
}

BuildSprite::~BuildSprite() {
    
}
