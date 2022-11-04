/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AB1F0 */

#include "weather.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "PR/libultra.h"
#include "camera.h"
#include "unknown_0255E0.h"
#include "unknown_008C40.h"
#include "textures_sprites.h"

/************ .data ************/

unk800E2850 D_800E2850[3] = {
    { 0,  0x40, (TextureHeader *)0, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0, 0x100, (TextureHeader *)1, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0,  0x08, (TextureHeader *)2, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
};

s32 *D_800E28D4 = 0;

unk800E2850 D_800E28D8 = { NULL, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Not sure about typing for the following.
Vertex *D_800E2904 = 0;
s32 D_800E2908 = 0;
s32 *D_800E290C = NULL;
s32 *D_800E2910 = NULL;
Vertex *D_800E2914[2] = { NULL, NULL };
s32 *D_800E291C = NULL; // List of Ids
s32 D_800E2920 = 0;

Gfx D_800E2928[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

unk800E2980 D_800E2980[2] = {
    { 1, 0xFFFF, 0xC090, 3.0f, 0.0f },
    { 0,      0,      0, 0.0f, 0.0f },
};

unk800E2980 D_800E29A0[4] = {
    { 3, 0xFFFF, 0x0090, 0.75f,  -32.0f },
    { 2, 0x0050, 0xFF60,  0.8f,  -96.0f },
    { 2, 0x00FF, 0x0090, 0.75f, -192.0f },
    { 0,      0,      0,  0.0f,    0.0f },
};

unk800E2980 D_800E29E0[5] = {
    { 3, 0xFF80, 0x1490, 0.65f,  -64.0f },
    { 2, 0xFFFF, 0xFF90,  1.0f, -128.0f },
    { 3, 0xFFFF, 0x8090,  0.5f, -176.0f },
    { 3, 0xFF28, 0x2890, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f },
};

unk800E2980 D_800E2A30[5] = {
    { 3, 0xFF80, 0xFF80,  0.5f,  -64.0f },
    { 1, 0xFFFF, 0xC090, 0.75f, -128.0f },
    { 2, 0xFF28, 0x0080,  0.6f, -176.0f },
    { 1, 0xFFC0, 0xFF90, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f },
};

s32 D_800E2A80 = 0;
s32 D_800E2A84 = 1;
s32 D_800E2A88 = 0;
f32 D_800E2A8C = -200.0f;
f32 D_800E2A90 = 200.0f;
f32 D_800E2A94 = 200.0f;
f32 D_800E2A98 = 200.0f;
f32 D_800E2A9C = 200.0f;
f32 D_800E2AA0 = -200.0f;
f32 D_800E2AA4 = -200.0f;
f32 D_800E2AA8 = -200.0f;

Vertex D_800E2AAC[16] = {
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
    { 0, 0, 0, 255, 255, 255, 255 },
};

unk800E2B4C D_800E2B4C[8] = {
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
};

unk800E2C2C gRainGfx[2] = {
    { 0, 0, 0x400, 0x400, 0x000A, 0xFFC4, NULL, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0xFF, 0x80, 0x00 },
    { 0, 0, 0x600, 0x600, 0x0020, 0xFF40, NULL, 0xFF, 0xFF, 0xFF, 0x00, 0x80, 0xFF, 0xFF, 0x00 }
};

s32 gWeatherType = WEATHER_SNOW;
s32 gLightningFrequency = 65536;
s32 D_800E2C64 = 0;
s32 D_800E2C68 = 65536;
s32 D_800E2C6C = 65536;
s32 D_800E2C70 = 0;
s32 D_800E2C74 = 65536;
s32 D_800E2C78 = 0;
s32 gLightningTimer = 0;
s32 gThunderTimer = 0;
s32 D_800E2C84 = 0;
s32 gRainOverlayUnusedValue = 0; // Set, but never read.
Sprite *gRainSplashGfx = 0;
s32 D_800E2C90 = 0;
s32 gWeatherSoundMask = 0;


FadeTransition D_800E2C98 = FADE_TRANSITION(0x40, FADE_COLOR_WHITE, 5, 2);

/*******************************/

/************ .bss ************/

s32 D_80127BB0;
s32 D_80127BB4;
s32 D_80127BB8[16];
unk80127BF8 D_80127BF8;
s32 D_80127C00;
s32 D_80127C04;
s32 D_80127C08;
Gfx *gWeatherDisplayListHead;
Mtx *D_80127C10;
VertexList *D_80127C14;
TriangleList *D_80127C18;
ObjectSegment *D_80127C1C;
Matrix *D_80127C20;
s32 D_80127C24;
s32 D_80127C28;
Matrix *D_80127C2C;
s32 D_80127C30[4];
Object *D_80127C40[16];

/******************************/

void func_800AB1F0(void) {
    D_800E28D8.unk0 = 0;
    D_800E28D8.unk4 = 0;
    D_800E28D4 = 0;
    D_80127BB0 = 0;
    D_80127C00 = 6;
    D_80127C00 <<= 2;
    D_80127C04 = D_80127C00 >> 1;
    D_800E2914[0] = 0;
    D_800E2914[1] = 0;
    D_800E290C = 0;
    D_80127BF8.unk0 = -1;
    D_80127BF8.unk2 = -0x200;
    D_800E2A80 = 0;
    D_800E2A84 = 1;
    D_800E2A88 = 0;
    if (D_800E291C == NULL) {
        D_800E291C = (s32 *)load_asset_section_from_rom(ASSET_WEATHER_PARTICLES);
        D_800E2920 = 0;
        while ((s32)D_800E291C[D_800E2920] != -1) {
            D_800E2920++;
        }
    }
    D_80127C08 = 0;
}

void func_800AB308(s16 arg0, s16 arg1) {
    if (D_80127BF8.unk2 < D_80127BF8.unk0) {
        D_80127BF8.unk0 = arg0;
        D_80127BF8.unk2 = arg1;
    } else {
        D_80127BF8.unk0 = arg1;
        D_80127BF8.unk2 = arg0;
    }
}

#define FREE_MEM(mem)                   \
    tempMem = (s32 *)mem;               \
    if (tempMem != 0) {                 \
        free_from_memory_pool(tempMem); \
        mem = NULL;                     \
    }

#define FREE_TEX(tex)                   \
    tempTex = tex;                      \
    if (tempTex != 0) {                 \
        free_texture(tempTex);          \
        tex = NULL;                     \
    }

/**
 * Free the weather assets from memory.
 * If it's raining, then free those too.
 */
void free_weather_memory(void) {
    TextureHeader *tempTex;
    s32 *tempMem;

    FREE_MEM(D_800E290C);
    FREE_MEM(D_800E2914[0]);
    FREE_MEM(D_800E2914[1]);
    FREE_MEM(D_800E28D4);
    FREE_MEM(D_800E28D8.unk0);
    FREE_TEX(D_800E28D8.unk8);
    FREE_MEM(D_800E2910);

    D_800E2A88 = 0;
    D_800E2A80 = 0;
    D_800E2A84 = 1;
    if (gWeatherType != WEATHER_SNOW) {
        free_rain_memory();
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800AB4A8.s")

void func_800ABB34(void) {
    s32 temp_v0;
    s32 phi_s1;
    s32 i;

    temp_v0 = 0x10000 / D_800E28D8.unk4;
    phi_s1 = 0;

    for(i = 0; i < D_800E28D8.unk4; i++) {
        D_800E28D8.unk0[i].unk0 = func_8007082C(phi_s1 & 0xFFFF) << 3;
        D_800E28D8.unk0[i].unk4 = 0xFFFC0000;
        D_800E28D8.unk0[i].unk8 = func_80070830(phi_s1 & 0xFFFF) << 1;
        phi_s1 += temp_v0;
    }

    D_800E28D8.unk8 = load_texture(*D_800E291C);
}


void func_800ABC5C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if ((arg5 > 0) && ((arg0 != D_80127BB8[5]) || (arg1 != D_80127BB8[8]) || (arg2 != D_80127BB8[11])
        || (arg3 != D_80127BB8[0]) || (arg4 != D_80127BB8[12]))) {
        D_80127BB8[5] = arg0;
        D_80127BB8[8] = arg1;
        D_80127BB8[11] = arg2;
        D_80127BB8[4] = (s32) ((s32) (arg0 - D_80127BB8[3]) / arg5);
        D_80127BB8[7] = (s32) ((s32) (arg1 - D_80127BB8[6]) / arg5);
        D_80127BB8[10] = (s32) ((s32) (arg2 - D_80127BB8[9]) / arg5);
        if (gWeatherType == WEATHER_SNOW) {
            D_80127BB8[1] = (s32) ((s32) (arg3 - D_80127BB8[0]) / arg5);
            D_80127BB8[13] = (s32) ((s32) (arg4 - D_80127BB8[12]) / arg5);
            D_80127BB8[2] = arg3;
            D_80127BB8[14] = arg4;
            D_80127BB8[15] = arg5;
            return;
        }
        D_80127BB8[0] = arg3;
        D_80127BB8[12] = arg4;
        D_80127BB8[15] = 0;
        func_800AD2C4(arg3 + 1, arg4 + 1, (f32) arg5 / 60.0f);
    }
}

/**
 * The root function for handling all weather.
 * Decide whether to perform rain or snow logic, execute it, then set it to render right after.
 */
void process_weather(Gfx **currDisplayList, Mtx **currHudMat, VertexList **currHudVerts, TriangleList **currHudTris, s32 updateRate) {
    UNUSED s32 unused;
    gWeatherDisplayListHead = *currDisplayList;
    D_80127C10 = *currHudMat;
    D_80127C14 = *currHudVerts;
    D_80127C18 = *currHudTris;
    D_80127C1C = func_80069D20();
    D_80127C20 = func_80069DBC();
    if (gWeatherType != WEATHER_SNOW) {
        handle_weather_rain(updateRate);
    } else {
        if (D_80127BB8[15] > 0) {
            if (updateRate < D_80127BB8[15]) {
                D_80127BB8[0] += D_80127BB8[1] * updateRate;
                D_80127BB8[3] += D_80127BB8[4] * updateRate;
                D_80127BB8[6] += D_80127BB8[7] * updateRate;
                D_80127BB8[9] += D_80127BB8[10] * updateRate;
                D_80127BB8[12] += D_80127BB8[13] * updateRate;
                D_80127BB8[15] -= updateRate;
            } else {
                D_80127BB8[0] = D_80127BB8[2];
                D_80127BB8[3] = D_80127BB8[5];
                D_80127BB8[6] = D_80127BB8[8];
                D_80127BB8[9] = D_80127BB8[11];
                D_80127BB8[12] = D_80127BB8[14];
                D_80127BB8[15] = 0;
            }
        }
        D_80127BB4 = (D_80127BB0 * D_80127BB8[0]) >> (unused = 16);
        D_80127BF8.unk4 = (D_80127BF8.unk0 + ((D_80127BF8.unk2 - D_80127BF8.unk0) * D_80127BB8[12])) >> (unused = 16);

        func_800AC0C8(updateRate, &D_80127BF8); // This is the snow physics that makes it move
        if ((D_80127BB4 > 0) && (D_80127BF8.unk4 < D_80127BF8.unk0)) {
            D_800E2904 = D_800E2914[D_80127C08];
            func_800AC21C(); // Both of these funcs are needed to render.
            func_800AC5A4();
            D_80127C08 = 1 - D_80127C08;
        }
    }
    *currDisplayList = gWeatherDisplayListHead;
    *currHudMat = D_80127C10;
    *currHudVerts = D_80127C14;
    *currHudTris = D_80127C18;
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800AC0C8.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AC21C.s")

#ifdef NON_MATCHING
// render_falling_snow
void func_800AC5A4(void) {
    s32 sp34;
    Matrix *mtx;
    Vertex *temp;

    if (D_800E28D8.unk8 != NULL) {
        D_80127C00 = 4;
        D_80127C04 = 2;
        sp34 = 0;
        if (D_800E2908 >= 4) {
            mtx = OS_PHYSICAL_TO_K0(func_80069DB0());
            gSPMatrix(gWeatherDisplayListHead++, mtx, G_MTX_DKR_INDEX_0);
            gDkrInsertMatrix(gWeatherDisplayListHead++, G_MTX_DKR_INDEX_0, 0);
            func_8007B4C8(&gWeatherDisplayListHead, D_800E28D8.unk8, 2U);
            while (D_80127C00 + sp34 < D_800E2908) {
                temp = &D_800E2904[sp34];
                gSPVertexDKR(gWeatherDisplayListHead++, OS_PHYSICAL_TO_K0(temp), D_80127C00, 0);
                gSPPolygon(gWeatherDisplayListHead++, OS_PHYSICAL_TO_K0(D_800E290C), D_80127C04, 1);
                sp34+=D_80127C00;
                
            }
            temp = &D_800E2904[sp34];
            gSPVertexDKR(gWeatherDisplayListHead++, OS_PHYSICAL_TO_K0(temp), (D_800E2908 - sp34), 0);
            gSPPolygon(gWeatherDisplayListHead++, OS_PHYSICAL_TO_K0(D_800E290C), ((s32) (D_800E2908 - sp34) >> 1), 1);
        }
    }
}

// Unused
void func_800AC850(void) {
    D_800E2A84 = 1;
}

// Unused
void func_800AC860(void) {
    if (D_800E2A80 != 0) {
        D_800E2A84 = 0;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/game_ui/func_800AC5A4.s")
#endif

void func_800AC880(s32 arg0) {
    if (arg0 == D_800E2A80) {
        D_800E2A80 = 0;
        D_800E2A84 = 1;
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800AC8A8.s")
GLOBAL_ASM("asm/non_matchings/game_ui/func_800ACA20.s")

void func_800ACF60(Object *arg0) {
    if (D_800E2A88 < 0x10) {
        D_80127C40[D_800E2A88] = arg0;
        D_800E2A88++;
    }
}

void func_800ACF98(Object* arg0) {
    s32 i;
    s32 isFound = FALSE;

    for (i = 0; i < D_800E2A88 && !isFound; i++) {
        if (D_80127C40[i] == arg0) {
            isFound = TRUE;
        }
    }

    if (isFound) {
        D_800E2A88--;
        i--;
        for (; i < D_800E2A88; i++) {
            D_80127C40[i] = D_80127C40[i + 1];
        }
    }

}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800AD030.s")

void func_800AD144(s32 arg0, s32 arg1) {
    gLightningFrequency = arg0;
    D_800E2C64 = 0;
    D_800E2C68 = gLightningFrequency;
    D_800E2C6C = arg1;
    D_800E2C70 = 0;
    D_800E2C74 = D_800E2C6C;
    D_800E2C78 = 0;
    gLightningTimer = 0;
    gThunderTimer = 0;
    D_800E2C84 = 0;
    D_800E2C90 = 0;
    gRainGfx[0].tex = load_texture(D_800E291C[1]);
    gRainGfx[1].tex = load_texture(D_800E291C[1]);
    gRainSplashGfx = (Sprite *)func_8007C12C(D_800E291C[3], 0);
    gWeatherType = WEATHER_RAIN;
}

/**
 * Free the rain overlay and splash asset data from memory.
 * Clear the soundmask too, stopping any ongoing audio.
 */
void free_rain_memory(void) {
    if (gRainGfx[0].tex != NULL) {
        free_texture(gRainGfx[0].tex);
        gRainOverlayUnusedValue = 0;
    }

    if (gRainGfx[1].tex != NULL) {
        free_texture(gRainGfx[1].tex);
        gRainOverlayUnusedValue = 0;
    }

    if (gRainSplashGfx != NULL) {
        free_sprite(gRainSplashGfx);
        gRainSplashGfx = 0;
    }

    if (gWeatherSoundMask) {
        func_800096F8(gWeatherSoundMask);
        gWeatherSoundMask = 0;
    }

    gWeatherType = WEATHER_SNOW;
}

void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2) {
    D_800E2C78 = osTvType == TV_TYPE_PAL ? 50.0 * arg2 : 60.0 * arg2;
    D_800E2C68 = arg0;
    D_800E2C64 = (D_800E2C68 - gLightningFrequency) / D_800E2C78;
    D_800E2C74 = arg1;
    D_800E2C70 = (D_800E2C74 - D_800E2C6C) / D_800E2C78;
}

void func_800AD40C(void) {
    s32 a, b;
    if (gWeatherType != WEATHER_SNOW && get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) {
        a = ((gLightningFrequency * -38) >> 16) + 1018;
        b = ((gLightningFrequency * -20) >> 16) + 1023;
        func_80030664(0, a, b, 0x1CU, 0xFU, 0x24U);
    }
}

// Unused.
void func_800AD4AC(s32 arg0) {
    D_800E2C6C = arg0;
}

/**
 * When active, (Single player only) Call all the functions related to the behaviour and rendering of
 * rain, and if necessary, thunder.
 */
void handle_weather_rain(s32 updateRate) {
    s32 i;

    if ((get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER) && (gWeatherType != WEATHER_SNOW)) {
        if (D_800E2C78 > 0) {
            if (updateRate < D_800E2C78) {
                D_800E2C78 -= updateRate;
                gLightningFrequency += D_800E2C64 * updateRate;
                D_800E2C6C += D_800E2C70 * updateRate;
            } else {
                D_800E2C78 = 0;
                gLightningFrequency = D_800E2C68;
                D_800E2C6C = D_800E2C74;
            }
        }
        handle_rain_sound(updateRate);
        render_rain_splashes(updateRate);
        handle_rain_lightning(updateRate);
        if (gLightningFrequency >= 256) {
            func_80067F2C(&gWeatherDisplayListHead, &D_80127C10);
            for(i = 0; i < 2; i++) {
                render_rain_overlay(&gRainGfx[i], updateRate);
            }
            gDPSetPrimColor(gWeatherDisplayListHead++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gWeatherDisplayListHead++, 255, 255, 255, 0);
            func_8007B3D0(&gWeatherDisplayListHead); // Pipesync and some stuff idk yet
            func_800682AC(&gWeatherDisplayListHead); // Looks to create a viewport scissor.
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/render_rain_splashes.s")

/**
 * On a randomly set timer, based on the weather intensity, count down and make the sound of thunder.
 * Set a second timer, that then counts down to zero and creates a flash of lightning in the form of a screen transition.
 * Afterwards, set the thunder timer back.
 */
void handle_rain_lightning(s32 updateRate) {
    if (gThunderTimer > 0) {
        gThunderTimer -= updateRate;
        if (gThunderTimer <= 0) {
            if (D_800E2C6C >= 32769 && func_800C018C() == 0) {
                func_800C01D8(&D_800E2C98);
            }
            play_sound_global(SOUND_LIGHTNING, NULL);
            gThunderTimer = 0;
        }
    } else if (gLightningFrequency >= 48000) {
        if (gLightningTimer > 0) {
            gLightningTimer -= updateRate;
            return;
        }
        play_sound_global(SOUND_THUNDER, NULL);
        gThunderTimer = 600 - ((s32) (gLightningFrequency + -48000) >> 5);
        gLightningTimer = get_random_number_from_range(900, 1140) - ((s32) (gLightningFrequency + -48000) >> 5);
    }
}

/**
 * Emit looping rain sound, using the camera position and direction as reference.
 */
void handle_rain_sound(UNUSED s32 updateRate) {
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 length;
    f32 cosOffset;
    f32 sineOffset;

    length = 1152.0f - (f32) (gLightningFrequency >> 6);
    cosOffset = cosine_s(D_80127C1C->trans.y_rotation) * length;
    sineOffset = sine_s(D_80127C1C->trans.y_rotation) * length;
    xPos = D_80127C1C->trans.x_position + (sineOffset - cosOffset);
    yPos = D_80127C1C->trans.y_position;
    zPos = D_80127C1C->trans.z_position + (-sineOffset - cosOffset);
    if (gWeatherSoundMask) {
        update_spatial_audio_position(gWeatherSoundMask, xPos, yPos, zPos);
    } else {
        func_80009558(SOUND_RAIN, xPos, yPos, zPos, 1, &gWeatherSoundMask);
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/render_rain_overlay.s")
