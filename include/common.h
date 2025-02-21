#ifndef COMMON_H
#define COMMON_H

#define VERSION_77 77 // NA / PAL V1
#define VERSION_79 79 // Japan
#define VERSION_80 80 // NA / PAL V1.1

#define REGION_NA  1
#define REGION_PAL 2
#define REGION_JP  3

#if   defined(VERSION_us_v77)
#define Func80019808Checksum 0x35281
#define ViewportFuncChecksum 0x585E
#define TractionTableChecksum 0x1C65B
#define ObjLoopGoldenBalloonChecksum 0xA597
#define VERSION VERSION_77
#define REGION REGION_NA
#elif defined(VERSION_pal_v77)
#define Func80019808Checksum 0x34E72
#define ViewportFuncChecksum 0x59E5
#define TractionTableChecksum 0x1C38F
#define ObjLoopGoldenBalloonChecksum 0xA6FF
#define VERSION VERSION_77
#define REGION REGION_PAL
#elif defined(VERSION_jpn_v79)
#define Func80019808Checksum 0x34EA6
#define ViewportFuncChecksum 0x592D
#define TractionTableChecksum 0x1C9EC
#define ObjLoopGoldenBalloonChecksum 0xA7C5
#define VERSION VERSION_79
#define REGION REGION_JP
#elif defined(VERSION_us_v80)
#define Func80019808Checksum 0x34B94
#define ViewportFuncChecksum 0x5881
#define TractionTableChecksum 0x1CA13
#define ObjLoopGoldenBalloonChecksum 0xA745
#define VERSION VERSION_80
#define REGION REGION_NA
#elif defined(VERSION_pal_v80)
#define Func80019808Checksum 0x3507C
#define ViewportFuncChecksum 0x580A
#define TractionTableChecksum 0x1CE40
#define ObjLoopGoldenBalloonChecksum 0xA6AF
#define VERSION VERSION_80
#define REGION REGION_PAL
#else
// Default to NA V1 if somehow we don't have a proper define.
#define Func80019808Checksum 0x35281
#define ViewportFuncChecksum 0x585E
#define TractionTableChecksum 0x1C65B
#define ObjLoopGoldenBalloonChecksum 0xA597
#define VERSION VERSION_77
#define REGION REGION_NA
#endif

#endif // COMMON_H
