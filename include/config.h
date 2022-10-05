#ifndef CONFIG_H
#define CONFIG_H

// Can be TITLE, CHARACTER or MENU.
#define SKIP_TITLE 1
#define SKIP_CHARACTER 2
#define SKIP_MENU 3

/// Optional toggles.
#define DISABLE_AA
#define PUPPYPRINT_DEBUG
#define SKIP_INTRO SKIP_TITLE
#define DEFAULT_CHARACTER 7
#define NUM_RACERS 8
// #define EXPANSION_PAK
#define DISABLE_ANTI_TAMPER
#define UNLOCK_ALL
#define NUM_FRAMEBUFFERS 2
#define FIFO_UCODE
// #define DISABLE_AUDIO

#define SCREEN_WIDTH 304
#define SCREEN_HEIGHT 224
#define HIGH_RES_SCREEN_WIDTH 640
#define HIGH_RES_SCREEN_HEIGHT 480





// Don't touch any of this below.

#ifdef DISABLE_AA
#define AA_DEF 0
#define RD_DEF 0
#else
#define AA_DEF AA_EN
#define RD_DEF IM_RD
#endif

#ifdef EXPANSION_PAK
    #define RAM_END 0x80800000
#else
    #define RAM_END 0x80400000
#endif

#endif // CONFIG_H
