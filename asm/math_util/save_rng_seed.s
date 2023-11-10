glabel save_rng_seed
/* 70518 8006F918 3C04800E */  lui        $a0, %hi(gCurrentRNGSeed)
/* 7051C 8006F91C 8C84D434 */  lw         $a0, %lo(gCurrentRNGSeed)($a0)
/* 70520 8006F920 3C01800E */  lui        $at, %hi(gPrevRNGSeed)
/* 70524 8006F924 03E00008 */  jr         $ra
/* 70528 8006F928 AC24D438 */   sw        $a0, %lo(gPrevRNGSeed)($at)