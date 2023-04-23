#ifndef CONFIG_H
#define CONFIG_H

// Can be TITLE, CHARACTER or MENU.
#define SKIP_TITLE 1
#define SKIP_CHARACTER 2
#define SKIP_MENU 3

/* ------------------------Standard----------------------- */
#define NO_ANTIPIRACY // Disable all the anti tamperment measures in the ROM
#define SKIP_WARNING_SCREEN // Remove the pak warning screen.
#define NUM_RACERS_1P 8                     // Default is 8
#define NUM_RACERS_2P 8                     // Default is 6
#define NUM_RACERS_3P 4                     // Default is 4
#define NUM_RACERS_4P 4                     // Default is 4

/* -------------------------Debug------------------------- */
#define PUPPYPRINT_DEBUG                    // Enable debug features
#define SKIP_INTRO SKIP_TITLE               // Skip the boot screen, making getting ingame faster.
#define DEFAULT_CHARACTER 7                 // If you skip character select, pick a default character.
#define UNLOCK_ALL                          // Unlock all characters, tracks and adventure 2.
//#define DISABLE_AUDIO                       // Disable all ingame audio, and prevent the RSP from working on audio tasks.

/* -------------------------Memory------------------------ */
//#define EXPANSION_PAK_REQUIRED              // Enable expansion pak requirement
//#define EXPANSION_PAK_SUPPORT               // Allow the game to use the expansion pak if it's inserted. Disabling this will move Framebuffers to expansion RAM for extra performance.
//#define FORCE_4MB_MEMORY                    // Pretend the expansion pak is not installed. 

/* -----------------------Performance--------------------- */
// These tweaks can be used to improve performance
#define FIFO_UCODE                          // Allow usage of the faster FIFO microcode. Emulators will still use xbus. Requires 96KB memory to work.
// #define DISABLE_MULTIPLAYER_CUTBACKS        // Disable the measures Rare took to improve performance in multiplayer. Performance will suffer.
#define TRIPLE_BUFFERING                    // Uses more memory, but provides a much smoother gameplay experience. You may struggle to fit this in 4MB.
#define SCREEN_WIDTH            304         // Default width is 320. Recommended to be 304 for 4MB users.
#define SCREEN_WIDTH_16_10      360         // Default width is 384. Recommended to be 360 for 4MB users.
#define SCREEN_WIDTH_WIDE       408         // Default width is 424. Recommended to be 408 for 4MB users.
#define SCREEN_HEIGHT           224         // Default height is 240. Recommended to be 224 for 4MB users.





// Don't touch any of this below.

#ifdef SKIP_WARNING_SCREEN
#define CAUTIONSTATUS 1
#else
#define CAUTIONSTATUS 0
#endif
#ifndef NON_MATCHING
#define NON_MATCHING
#endif

#ifdef TRIPLE_BUFFERING
#define NUM_FRAMEBUFFERS 3
#else
#define NUM_FRAMEBUFFERS 2
#endif

#ifdef EXPANSION_PAK_REQUIRED
#define EXPANSION_PAK_SUPPORT
#endif

#endif // CONFIG_H
