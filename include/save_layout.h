#ifndef _SAVE_LAYOUT_H_
#define _SAVE_LAYOUT_H_

#include "types.h"
#include "structs.h"
#include "macros.h"
#include "PR/os_cont.h"

/**
 * File contains the struct and macro definitions for the save layout for DKR.
*/

#define NUMBER_OF_SAVE_FILES 3

#define TT_COURSES          \
    unsigned courseAL : 1;  \
    unsigned courseFC : 1;  \
    unsigned courseJF : 1;  \
    unsigned courseHTV : 1; \
                            \
    unsigned courseWB : 1;  \
    unsigned courseCI : 1;  \
    unsigned coursePL : 1;  \
    unsigned courseTC : 1;  \
                            \
    unsigned courseEP : 1;  \
    unsigned courseWC : 1;  \
    unsigned courseSV : 1;  \
    unsigned courseFV : 1;  \
                            \
    unsigned courseBC : 1;  \
    unsigned courseGV : 1;  \
    unsigned courseWP : 1;  \
    unsigned courseHW : 1;  \
                            \
    unsigned courseSA : 1;  \
    unsigned courseDMC : 1; \
    unsigned courseSC : 1;  \
    unsigned courseSPA : 1;

#define SAVE_COURSES                        \
    unsigned courseBluey1 : 2;              \
    unsigned courseFossilCanyon : 2;        \
    unsigned coursePirateLagoon : 2;        \
    unsigned courseAncientLake : 2;         \
    unsigned courseWalrusCove : 2;          \
    unsigned courseHotTopVolcano : 2;       \
    unsigned courseWhaleBay : 2;            \
    unsigned courseSnowballValley : 2;      \
    unsigned courseCrescentIsland : 2;      \
    unsigned courseFireMountain : 2;        \
    unsigned courseEverfrostPeak : 2;       \
    unsigned courseSpaceportAlpha : 2;      \
    unsigned courseSpacedustAlley : 2;      \
    unsigned courseGreenwoodVillage : 2;    \
    unsigned courseBoulderCanyon : 2;       \
    unsigned courseWindmillPlains : 2;      \
    unsigned courseSmokeyCastle : 2;        \
    unsigned courseDarkwaterBeach : 2;      \
    unsigned courseIciclePyramid : 2;       \
    unsigned courseFrostyVillage : 2;       \
    unsigned courseJungleFalls : 2;         \
    unsigned courseTreasureCaves : 2;       \
    unsigned courseHauntedWoods : 2;        \
    unsigned courseDarkmoonCaverns : 2;     \
    unsigned courseStarCity : 2;            \
    unsigned courseWizpig1 : 2;             \
    unsigned courseTricky1 : 2;             \
    unsigned courseBubbler1 : 2;            \
    unsigned courseSmokey1 : 2;             \
    unsigned courseTricky2 : 2;             \
    unsigned courseBluey2 : 2;              \
    unsigned courseBubbler2 : 2;            \
    unsigned courseSmokey2 : 2;             \
    unsigned courseWizpig2 : 2;

enum CourseRecordNames {
    COURSE_FC_CAR,
    COURSE_FC_HOVER,
    COURSE_FC_PLANE,
    COURSE_PL_HOVER,
    COURSE_AL_CAR,
    COURSE_AL_HOVER,
    COURSE_AL_PLANE,
    COURSE_WC_CAR,
    COURSE_WC_HOVER,
    COURSE_HTV_HOVER,
    COURSE_HTV_PLANE,
    COURSE_WB_HOVER,
    COURSE_SV_CAR,
    COURSE_SV_HOVER,
    COURSE_CI_CAR,
    COURSE_CI_HOVER,
    COURSE_EP_CAR,
    COURSE_EP_HOVER,
    COURSE_EP_PLANE,
    COURSE_SPA_CAR,
    COURSE_SPA_HOVER,
    COURSE_SPA_PLANE,
    COURSE_SA_CAR,
    COURSE_SA_HOVER,
    COURSE_SA_PLANE,
    COURSE_GV_CAR,
    COURSE_GV_HOVER,
    COURSE_BC_HOVER,
    COURSE_WP_CAR,
    COURSE_WP_HOVER,
    COURSE_WP_PLANE,
    COURSE_FV_CAR,
    COURSE_FV_HOVER,
    COURSE_FV_PLANE,
    COURSE_JF_CAR,
    COURSE_JF_HOVER,
    COURSE_JF_PLANE,
    COURSE_TC_CAR,
    COURSE_TC_HOVER,
    COURSE_TC_PLANE,
    COURSE_HW_CAR,
    COURSE_HW_HOVER,
    COURSE_DMC_CAR,
    COURSE_DMC_HOVER,
    COURSE_SC_CAR,
    COURSE_SC_HOVER,
    COURSE_SC_PLANE,

    COURSE_RECORD_TOTAL
};

typedef struct SaveConfig {
    unsigned unlockedAdv2 : 1;
    unsigned unlockedDrumstick : 1;
    unsigned language : 2;
    TT_COURSES
    unsigned subtitles : 1;
    unsigned unk0 : 31;
    // unsigned checksum : 8; // For some reason, the struct becomes 12 bytes if this is there.
} SaveConfig;

typedef struct SaveFile {
    unsigned checksum : 16;
    SAVE_COURSES
    unsigned tajFlags : 6;

    unsigned trophy1 : 2;
    unsigned trophy2 : 2;
    unsigned trophy3 : 2;
    unsigned trophy4 : 2;
    unsigned trophy5 : 2;

    unsigned bossWizpig1 : 1;
    unsigned bossTricky1 : 1;
    unsigned bossBubbler1 : 1;
    unsigned bossBluey1 : 1;
    unsigned bossSmokey1 : 1;
    unsigned bossWizpig2 : 1;
    unsigned bossTricky2 : 1;
    unsigned bossBubbler2 : 1;
    unsigned bossBluey2 : 1;
    unsigned bossSmokey2 : 1;
    unsigned bossUnused1 : 1;
    unsigned bossUnused2 : 1;

    unsigned balloonsTotal : 7;
    unsigned balloonsWorld1 : 7; // Dino Domain
    unsigned balloonsWorld2 : 7; // Sherbet Island
    unsigned balloonsWorld3 : 7; // Snowflake Mountain
    unsigned balloonsWorld4 : 7; // Dragon Forest
    unsigned balloonsWorld5 : 7; // Future Fun Land

    unsigned amuletTT : 3;
    unsigned amuletWizpig : 3;

    unsigned flagsWorld0 : 16; // Hub, balloons
    unsigned flagsWorld1 : 16; // Dino Domain
    unsigned flagsWorld2 : 16; // Sherbet Island
    unsigned flagsWorld3 : 16; // Snowflake Mountain
    unsigned flagsWorld4 : 16; // Dragon Forest
    unsigned flagsWorld5 : 16; // Future Fun Land

    unsigned keyWorld0 : 1; // Hub world, unused
    unsigned keyWorld1 : 1; // Dino Domain
    unsigned keyWorld2 : 1; // Snowflake Mountain
    unsigned keyWorld3 : 1; // Sherbet Island
    unsigned keyWorld4 : 1; // Dragon Forest
    unsigned keyWorld5 : 1; // Future Fun Land, unused
    unsigned keyWorld6 : 1; // Unused
    unsigned keyWorld7 : 1; // Unused

    unsigned sceneLighthouse : 1;
    unsigned sceneTTHelp : 1;
    unsigned sceneAdv2 : 1;
    unsigned sceneWorld1Boss1 : 1;
    unsigned sceneWorld2Boss1 : 1;
    unsigned sceneWorld3Boss1 : 1;
    unsigned sceneWorld4Boss1 : 1;
    unsigned sceneWorld5Boss1 : 1;
    unsigned sceneWorld1Boss2 : 1;
    unsigned sceneWorld2Boss2 : 1;
    unsigned sceneWorld3Boss2 : 1;
    unsigned sceneWorld4Boss2 : 1;
    unsigned sceneWorld5Boss2 : 1;
    unsigned sceneWizpigFace : 1;
    unsigned sceneWorld1Key : 1;
    unsigned sceneWorld2Key : 1;
    unsigned sceneWorld3Key : 1;
    unsigned sceneWorld4Key : 1;
    unsigned sceneWorld5Key : 1; // Unused

    unsigned name : 15;
} SaveFile;

typedef struct CourseRecords {
    u16 checksum;
    u16 padding;
    u32 courseTime[COURSE_RECORD_TOTAL];
} CourseRecords;

typedef struct SaveBuffer {
    SaveFile gameSave[NUMBER_OF_SAVE_FILES];
    SaveConfig config;
    CourseRecords fastLaps;
    CourseRecords courseTimes;
} SaveBuffer ALIGNED8;

// Eeprom works in 8 byte blocks, so divide by 8 for those functions.
#define BLOCK_SIZE(x)           (x / sizeof(u64))
#define SAVE_START              (0)
#define CONFIG_START            (SAVE_START + (sizeof(SaveFile) * NUMBER_OF_SAVE_FILES))
#define FASTEST_LAPS_START      (CONFIG_START + sizeof(SaveConfig))
#define COURSE_TIMES_START      (FASTEST_LAPS_START + sizeof(CourseRecords))
#define SAVE_SIZE               (sizeof(SaveBuffer))

#endif
