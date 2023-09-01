glabel update_spatial_audio_position
/* 00A2D8 800096D8 44856000 */  mtc1  $a1, $f12
/* 00A2DC 800096DC 44867000 */  mtc1  $a2, $f14
/* 00A2E0 800096E0 AFA7000C */  sw    $a3, 0xc($sp)
/* 00A2E4 800096E4 E48C0000 */  swc1  $f12, ($a0)
/* 00A2E8 800096E8 E48E0004 */  swc1  $f14, 4($a0)
/* 00A2EC 800096EC C7A4000C */  lwc1  $f4, 0xc($sp)
/* 00A2F0 800096F0 03E00008 */  jr    $ra
/* 00A2F4 800096F4 E4840008 */   swc1  $f4, 8($a0)

