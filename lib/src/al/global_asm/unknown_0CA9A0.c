/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CA0D0 */

#include "types.h"
#include "macros.h"

#define EQPOWER_LENGTH 128
s16 eqpower[ EQPOWER_LENGTH ] = {
    32767,  32764,  32757,  32744,  32727,  32704,
    32677,  32644,  32607,  32564,  32517,  32464,
    32407,  32344,  32277,  32205,  32127,  32045,
    31958,  31866,  31770,  31668,  31561,  31450,
    31334,  31213,  31087,  30957,  30822,  30682,
    30537,  30388,  30234,  30075,  29912,  29744,
    29572,  29395,  29214,  29028,  28838,  28643,
    28444,  28241,  28033,  27821,  27605,  27385,
    27160,  26931,  26698,  26461,  26220,  25975,
    25726,  25473,  25216,  24956,  24691,  24423,
    24151,  23875,  23596,  23313,  23026,  22736,
    22442,  22145,  21845,  21541,  21234,  20924,
    20610,  20294,  19974,  19651,  19325,  18997,
    18665,  18331,  17993,  17653,  17310,  16965,
    16617,  16266,  15913,  15558,  15200,  14840,
    14477,  14113,  13746,  13377,  13006,  12633,
    12258,  11881,  11503,  11122,  10740,  10357,
    9971,   9584,   9196,   8806,   8415,   8023,
    7630,   7235,   6839,   6442,   6044,   5646,
    5246,   4845,   4444,   4042,   3640,   3237,
    2833,   2429,   2025,   1620,   1216,    810,
    405,      0
};

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alEnvMixerPull.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alEnvmixerParam.s")
//Called by alEnvMixerPull
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CAC5C.s")
//Called by func_800CAC5C
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CB2D4.s")
//_getVol?
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CB498.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alLoadParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alRaw16Pull.s")
//Called by alAdpcmPull. _decodeChunk?
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CBAC0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alAdpcmPull.s")
