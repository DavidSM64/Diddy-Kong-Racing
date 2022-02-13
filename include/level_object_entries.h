#ifndef _LEVEL_OBJECT_ENTRIES_H_
#define _LEVEL_OBJECT_ENTRIES_H_

/* Size: 8 bytes. Shared across every entry. */
typedef struct LevelObjectEntryCommon {
    u8 object_id; // 9-bit object ID to load (uses size's MSB).
    u8 size; // 7-bit total entry length (MSB is used in object_id).
    s16 x, y, z; // Position in level
} LevelObjectEntryCommon;

typedef struct LevelObjectEntry_1 {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_1;

typedef struct LevelObjectEntry_Scenery {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
} LevelObjectEntry_Scenery;

typedef struct LevelObjectEntry_3 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_3;

typedef struct LevelObjectEntry_4 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_4;

typedef struct LevelObjectEntry_5 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_5;

typedef struct LevelObjectEntry_6 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_6;

typedef struct LevelObjectEntry_7 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_7;

typedef struct LevelObjectEntry_8 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_8;

typedef struct LevelObjectEntry_9 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_9;

typedef struct LevelObjectEntry_10 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_10;

typedef struct LevelObjectEntry_11 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_11;

typedef struct LevelObjectEntry_12 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_12;

typedef struct LevelObjectEntry_13 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_13;

typedef struct LevelObjectEntry_14 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_14;

typedef struct LevelObjectEntry_15 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_15;

typedef struct LevelObjectEntry_16 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_16;

#define BALLOON_TYPE_BOOST   0
#define BALLOON_TYPE_MISSILE 1
#define BALLOON_TYPE_TRAP    2
#define BALLOON_TYPE_SHIELD  3
#define BALLOON_TYPE_MAGNET  4

typedef struct LevelObjectEntry_WeaponBalloon {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8; // Unused?
    /* 0x09 */ u8 balloonType; 
    /* 0x0A */ u8 scale; // This is divided by 64 to get actual scale.
} LevelObjectEntry_WeaponBalloon;

typedef struct LevelObjectEntry_18 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_18;

typedef struct LevelObjectEntry_19 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_19;

typedef struct LevelObjectEntry_22 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_22;

typedef struct LevelObjectEntry_23 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_23;

typedef struct LevelObjectEntry_25 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_25;

typedef struct LevelObjectEntry_26 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_26;

typedef struct LevelObjectEntry_27 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_27;

typedef struct LevelObjectEntry_Torch_Mist {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
} LevelObjectEntry_Torch_Mist;

typedef struct LevelObjectEntry_29 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_29;

typedef struct LevelObjectEntry_30 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_30;

typedef struct LevelObjectEntry_31 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_31;

typedef struct LevelObjectEntry_32 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_32;

typedef struct LevelObjectEntry_33 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_33;

typedef struct LevelObjectEntry_36 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_36;

typedef struct LevelObjectEntry_37 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_37;

typedef struct LevelObjectEntry_38 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_38;

typedef struct LevelObjectEntry_39 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_39;

typedef struct LevelObjectEntry_40 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_40;

typedef struct LevelObjectEntry_41 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_41;

typedef struct LevelObjectEntry_43 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_43;

typedef struct LevelObjectEntry_44 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_44;

typedef struct LevelObjectEntry_45 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_45;

typedef struct LevelObjectEntry_46 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_46;

typedef struct LevelObjectEntry_47 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_47;

typedef struct LevelObjectEntry_49 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_49;

typedef struct LevelObjectEntry_52 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_52;

typedef struct LevelObjectEntry_55 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_55;

typedef struct LevelObjectEntry_57 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_57;

typedef struct LevelObjectEntry_58 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_58;

typedef struct LevelObjectEntry_59 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_59;

typedef struct LevelObjectEntry_61 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_61;

typedef struct LevelObjectEntry_62 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_62;

typedef struct LevelObjectEntry_64 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_64;

typedef struct LevelObjectEntry_65 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_65;

typedef struct LevelObjectEntry_66 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_66;

typedef struct LevelObjectEntry_67 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_67;

typedef struct LevelObjectEntry_68 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_68;

typedef struct LevelObjectEntry_69 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_69;

typedef struct LevelObjectEntry_70 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_70;

typedef struct LevelObjectEntry_71 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_71;

typedef struct LevelObjectEntry_72 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_72;

typedef struct LevelObjectEntry_73 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_73;

typedef struct LevelObjectEntry_74 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_74;

typedef struct LevelObjectEntry_75 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_75;

typedef struct LevelObjectEntry_76 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_76;

typedef struct LevelObjectEntry_77 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_77;

typedef struct LevelObjectEntry_Laserbolt {
    /* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Laserbolt;

typedef struct LevelObjectEntry_Lasergun {
    /* 0x00 */ LevelObjectEntryCommon common;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ s8 unkA;
    /* 0x0B */ s8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
} LevelObjectEntry_Lasergun;

typedef struct LevelObjectEntry_82 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_82;

typedef struct LevelObjectEntry_83 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_83;

typedef struct LevelObjectEntry_84 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_84;

typedef struct LevelObjectEntry_88 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_88;

typedef struct LevelObjectEntry_89 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_89;

typedef struct LevelObjectEntry_90 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_90;

typedef struct LevelObjectEntry_93 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_93;

typedef struct LevelObjectEntry_94 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_94;

typedef struct LevelObjectEntry_95 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_95;

typedef struct LevelObjectEntry_96 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_96;

typedef struct LevelObjectEntry_97 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_97;

typedef struct LevelObjectEntry_98 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_98;

typedef struct LevelObjectEntry_99 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_99;

typedef struct LevelObjectEntry_100 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_100;

typedef struct LevelObjectEntry_101 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_101;

typedef struct LevelObjectEntry_102 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_102;

typedef struct LevelObjectEntry_103 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_103;

typedef struct LevelObjectEntry_104 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_104;

typedef struct LevelObjectEntry_105 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_105;

typedef struct LevelObjectEntry_Fireball_Octoweapon {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_Fireball_Octoweapon;

typedef struct LevelObjectEntry_109 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_109;

typedef struct LevelObjectEntry_110 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_110;

typedef struct LevelObjectEntry_111 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_111;

typedef struct LevelObjectEntry_112 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_112;

typedef struct LevelObjectEntry_116 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_116;

typedef struct LevelObjectEntry_117 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_117;

typedef struct LevelObjectEntry_118 {
/* 0x00 */ LevelObjectEntryCommon common;
} LevelObjectEntry_118;

#endif
