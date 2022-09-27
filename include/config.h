#ifndef CONFIG_H
#define CONFIG_H

// Can be TITLE, CHARACTER or MENU.
#define SKIP_TITLE 1
#define SKIP_CHARACTER 2
#define SKIP_MENU 3

/// Optional toggles.
#define DISABLE_AA
#define ENABLE_DEBUG_PROFILER
#define SKIP_INTRO SKIP_TITLE
#define DEFAULT_CHARACTER 7
#define NUM_RACERS 8
#define EXPANSION_PAK
#define DISABLE_ANTI_TAMPER
#define UNLOCK_ALL
#define NUM_FRAMEBUFFERS 2
#define FIFO_UCODE











#ifdef DISABLE_AA
#define AA_DEF 0
#define RD_DEF 0
#else
#define AA_DEF AA_EN
#define RD_DEF IM_RD
#endif

#endif // CONFIG_H
