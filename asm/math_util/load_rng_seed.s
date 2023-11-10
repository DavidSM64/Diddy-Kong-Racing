glabel load_rng_seed
/* 7052C 8006F92C 3C04800E */  lui        $a0, %hi(gPrevRNGSeed)
/* 70530 8006F930 8C84D438 */  lw         $a0, %lo(gPrevRNGSeed)($a0)
/* 70534 8006F934 3C01800E */  lui        $at, %hi(gCurrentRNGSeed)
/* 70538 8006F938 03E00008 */  jr         $ra
/* 7053C 8006F93C AC24D434 */   sw        $a0, %lo(gCurrentRNGSeed)($at)