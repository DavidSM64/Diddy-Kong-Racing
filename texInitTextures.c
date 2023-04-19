#include "ctx.c"

void texInitTextures(void) {
    s32 *temp_v0;
    s32 *var_v0;
    s32 var_t3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u32 *var_v0_2;

    gTextureCache = allocate_from_main_pool_safe(0x15E0, 0xFF00FFFFU);
    gCiPalettes = allocate_from_main_pool_safe(0x280, 0xFF00FFFFU);
    gNumberOfLoadedTextures = 0;
    gCiPalettesSize = 0;
    D_80126320->unk0 = load_asset_section_from_rom(5U);
    D_80126320->unk4 = load_asset_section_from_rom(3U);
    var_v1 = 0;
    if (*D_80126320->unk0 != -1) {
        var_v0 = D_80126320->unk0;
        do {
            var_v1 += 1;
            var_v0 += 4;
        } while (var_v0->unk4 != -1);
    }
    D_80126338->unk0 = var_v1 - 1;
    var_v1_2 = 0;
    if (*D_80126320->unk4 != (u32) -1) {
        var_v0_2 = D_80126320->unk4;
        do {
            var_v1_2 += 1;
            var_v0_2 += 4;
        } while (var_v0_2->unk4 != -1);
    }
    D_80126338->unk4 = (s32) (var_v1_2 - 1);
    gSpriteCache = allocate_from_main_pool_safe(0x320, 0xFF00FFFFU);
    gCurrentSprite = allocate_from_main_pool_safe(0x200, 0xFF00FFFFU);
    D_80126358 = 0;
    temp_v0 = load_asset_section_from_rom(0xDU);
    gSpriteOffsetTable = temp_v0;
    D_80126354 = 0;
    var_v1_3 = 0;
    if (temp_v0[0] != -1) {
        var_t3 = 1;
        do {
            D_80126354 = var_t3;
            var_v1_3 = var_t3;
            var_t3 = var_v1_3 + 1;
        } while (temp_v0[var_t3] != -1);
    }
    D_80126354 = var_v1_3 - 1;
    gTempTextureHeader = allocate_from_main_pool_safe(0x28, 0xFF00FFFFU);
    D_80126344 = 0;
}
