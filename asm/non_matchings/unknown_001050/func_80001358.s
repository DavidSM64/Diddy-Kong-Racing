glabel func_80001358
/* 001F58 80001358 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 001F5C 8000135C 308700FF */  andi  $a3, $a0, 0xff
/* 001F60 80001360 24010064 */  li    $at, 100
/* 001F64 80001364 AFBF0014 */  sw    $ra, 0x14($sp)
/* 001F68 80001368 AFA40020 */  sw    $a0, 0x20($sp)
/* 001F6C 8000136C AFA50024 */  sw    $a1, 0x24($sp)
/* 001F70 80001370 10E10013 */  beq   $a3, $at, .L800013C0
/* 001F74 80001374 AFA60028 */   sw    $a2, 0x28($sp)
/* 001F78 80001378 3C04800E */  lui   $a0, %hi(gMusicPlayer) # $a0, 0x800e
/* 001F7C 8000137C 8C84C630 */  lw    $a0, %lo(gMusicPlayer)($a0)
/* 001F80 80001380 30E500FF */  andi  $a1, $a3, 0xff
/* 001F84 80001384 0C031E68 */  jal   alCSPGetChlVol
/* 001F88 80001388 A3A70023 */   sb    $a3, 0x23($sp)
/* 001F8C 8000138C 8FAE0028 */  lw    $t6, 0x28($sp)
/* 001F90 80001390 93A70023 */  lbu   $a3, 0x23($sp)
/* 001F94 80001394 004E1821 */  addu  $v1, $v0, $t6
/* 001F98 80001398 306F00FF */  andi  $t7, $v1, 0xff
/* 001F9C 8000139C 29E10080 */  slti  $at, $t7, 0x80
/* 001FA0 800013A0 14200002 */  bnez  $at, .L800013AC
/* 001FA4 800013A4 306600FF */   andi  $a2, $v1, 0xff
/* 001FA8 800013A8 2406007F */  li    $a2, 127
.L800013AC:
/* 001FAC 800013AC 3C04800E */  lui   $a0, %hi(gMusicPlayer) # $a0, 0x800e
/* 001FB0 800013B0 8C84C630 */  lw    $a0, %lo(gMusicPlayer)($a0)
/* 001FB4 800013B4 30E500FF */  andi  $a1, $a3, 0xff
/* 001FB8 800013B8 0C031E50 */  jal   alCSPSetChlVol
/* 001FBC 800013BC A3A6001F */   sb    $a2, 0x1f($sp)
.L800013C0:
/* 001FC0 800013C0 93B80027 */  lbu   $t8, 0x27($sp)
/* 001FC4 800013C4 24010064 */  li    $at, 100
/* 001FC8 800013C8 13010014 */  beq   $t8, $at, .L8000141C
/* 001FCC 800013CC 3C04800E */   lui   $a0, %hi(gMusicPlayer) # $a0, 0x800e
/* 001FD0 800013D0 8C84C630 */  lw    $a0, %lo(gMusicPlayer)($a0)
/* 001FD4 800013D4 0C031E68 */  jal   alCSPGetChlVol
/* 001FD8 800013D8 03002825 */   move  $a1, $t8
/* 001FDC 800013DC 8FB90028 */  lw    $t9, 0x28($sp)
/* 001FE0 800013E0 93A50027 */  lbu   $a1, 0x27($sp)
/* 001FE4 800013E4 0322082A */  slt   $at, $t9, $v0
/* 001FE8 800013E8 10200005 */  beqz  $at, .L80001400
/* 001FEC 800013EC 3C04800E */   lui   $a0, %hi(gMusicPlayer) # $a0, 0x800e
/* 001FF0 800013F0 00593023 */  subu  $a2, $v0, $t9
/* 001FF4 800013F4 30C800FF */  andi  $t0, $a2, 0xff
/* 001FF8 800013F8 10000002 */  b     .L80001404
/* 001FFC 800013FC 01003025 */   move  $a2, $t0
.L80001400:
/* 002000 80001400 00003025 */  move  $a2, $zero
.L80001404:
/* 002004 80001404 8C84C630 */  lw    $a0, %lo(gMusicPlayer)($a0)
/* 002008 80001408 0C031E50 */  jal   alCSPSetChlVol
/* 00200C 8000140C A3A6001E */   sb    $a2, 0x1e($sp)
/* 002010 80001410 93A2001E */  lbu   $v0, 0x1e($sp)
/* 002014 80001414 10000007 */  b     .L80001434
/* 002018 80001418 8FBF0014 */   lw    $ra, 0x14($sp)
.L8000141C:
/* 00201C 8000141C 93A9001F */  lbu   $t1, 0x1f($sp)
/* 002020 80001420 240A007F */  li    $t2, 127
/* 002024 80001424 01491023 */  subu  $v0, $t2, $t1
/* 002028 80001428 304B00FF */  andi  $t3, $v0, 0xff
/* 00202C 8000142C 01601025 */  move  $v0, $t3
/* 002030 80001430 8FBF0014 */  lw    $ra, 0x14($sp)
.L80001434:
/* 002034 80001434 27BD0020 */  addiu $sp, $sp, 0x20
/* 002038 80001438 03E00008 */  jr    $ra
/* 00203C 8000143C 00000000 */   nop   
