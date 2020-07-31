glabel __ull_rem
/* 0CF68C 800CEA8C AFA40000 */  sw    $a0, ($sp)
/* 0CF690 800CEA90 AFA50004 */  sw    $a1, 4($sp)
/* 0CF694 800CEA94 AFA60008 */  sw    $a2, 8($sp)
/* 0CF698 800CEA98 AFA7000C */  sw    $a3, 0xc($sp)
/* 0CF69C 800CEA9C DFAF0008 */  ld    $t7, 8($sp)
/* 0CF6A0 800CEAA0 DFAE0000 */  ld    $t6, ($sp)
/* 0CF6A4 800CEAA4 01CF001F */  ddivu $zero, $t6, $t7
/* 0CF6A8 800CEAA8 15E00002 */  bnez  $t7, .L800CEAB4
/* 0CF6AC 800CEAAC 00000000 */   nop   
/* 0CF6B0 800CEAB0 0007000D */  break 7
.L800CEAB4:
/* 0CF6B4 800CEAB4 00001010 */  mfhi  $v0
/* 0CF6B8 800CEAB8 0002183C */  dsll32 $v1, $v0, 0
/* 0CF6BC 800CEABC 0003183F */  dsra32 $v1, $v1, 0
/* 0CF6C0 800CEAC0 03E00008 */  jr    $ra
/* 0CF6C4 800CEAC4 0002103F */   dsra32 $v0, $v0, 0

