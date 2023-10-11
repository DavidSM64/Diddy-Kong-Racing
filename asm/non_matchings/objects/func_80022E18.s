glabel func_80022E18
/* 023A18 80022E18 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 023A1C 80022E1C AFBF0014 */  sw    $ra, 0x14($sp)
/* 023A20 80022E20 0C01AF6C */  jal   get_current_level_header
/* 023A24 80022E24 AFA40030 */   sw    $a0, 0x30($sp)
/* 023A28 80022E28 240E0005 */  li    $t6, 5
/* 023A2C 80022E2C A04E004C */  sb    $t6, 0x4c($v0)
/* 023A30 80022E30 3C0F8012 */  lui   $t7, %hi(D_8011AEF8) # $t7, 0x8012
/* 023A34 80022E34 81EFAEF8 */  lb    $t7, %lo(D_8011AEF8)($t7)
/* 023A38 80022E38 3C188012 */  lui   $t8, %hi(D_8011AEFC) # $t8, 0x8012
/* 023A3C 80022E3C A04F0052 */  sb    $t7, 0x52($v0)
/* 023A40 80022E40 8F18AEFC */  lw    $t8, %lo(D_8011AEFC)($t8)
/* 023A44 80022E44 24040001 */  li    $a0, 1
/* 023A48 80022E48 0C02AC6B */  jal   func_800AB1AC
/* 023A4C 80022E4C A4580054 */   sh    $t8, 0x54($v0)
/* 023A50 80022E50 3C078012 */  lui   $a3, %hi(gRacers) # $a3, 0x8012
/* 023A54 80022E54 3C068012 */  lui   $a2, %hi(gNumRacers) # $a2, 0x8012
/* 023A58 80022E58 00002825 */  move  $a1, $zero
/* 023A5C 80022E5C 24C6AEF0 */  addiu $a2, %lo(gNumRacers) # addiu $a2, $a2, -0x5110
/* 023A60 80022E60 24E7AEE4 */  addiu $a3, %lo(gRacers) # addiu $a3, $a3, -0x511c
/* 023A64 80022E64 00001025 */  move  $v0, $zero
.L80022E68:
/* 023A68 80022E68 8CF90000 */  lw    $t9, ($a3)
/* 023A6C 80022E6C 24A50001 */  addiu $a1, $a1, 1
/* 023A70 80022E70 03224021 */  addu  $t0, $t9, $v0
/* 023A74 80022E74 8D090000 */  lw    $t1, ($t0)
/* 023A78 80022E78 24420004 */  addiu $v0, $v0, 4
/* 023A7C 80022E7C 8D230064 */  lw    $v1, 0x64($t1)
/* 023A80 80022E80 00000000 */  nop   
/* 023A84 80022E84 A06001D8 */  sb    $zero, 0x1d8($v1)
/* 023A88 80022E88 A0600193 */  sb    $zero, 0x193($v1)
/* 023A8C 80022E8C A0600192 */  sb    $zero, 0x192($v1)
/* 023A90 80022E90 A4600190 */  sh    $zero, 0x190($v1)
/* 023A94 80022E94 8CCA0000 */  lw    $t2, ($a2)
/* 023A98 80022E98 00000000 */  nop   
/* 023A9C 80022E9C 00AA082A */  slt   $at, $a1, $t2
/* 023AA0 80022EA0 1420FFF1 */  bnez  $at, .L80022E68
/* 023AA4 80022EA4 00000000 */   nop   
/* 023AA8 80022EA8 8CEB0000 */  lw    $t3, ($a3)
/* 023AAC 80022EAC 00000000 */  nop   
/* 023AB0 80022EB0 8D640004 */  lw    $a0, 4($t3)
/* 023AB4 80022EB4 0C003FEE */  jal   free_object
/* 023AB8 80022EB8 00000000 */   nop   
/* 023ABC 80022EBC 3C078012 */  lui   $a3, %hi(gRacers) # $a3, 0x8012
/* 023AC0 80022EC0 24E7AEE4 */  addiu $a3, %lo(gRacers) # addiu $a3, $a3, -0x511c
/* 023AC4 80022EC4 8CEC0000 */  lw    $t4, ($a3)
/* 023AC8 80022EC8 3C0E8012 */  lui   $t6, %hi(gRacersByPosition) # $t6, 0x8012
/* 023ACC 80022ECC 8DCEAEE8 */  lw    $t6, %lo(gRacersByPosition)($t6)
/* 023AD0 80022ED0 8D8D0000 */  lw    $t5, ($t4)
/* 023AD4 80022ED4 3C068012 */  lui   $a2, %hi(gNumRacers) # $a2, 0x8012
/* 023AD8 80022ED8 24C6AEF0 */  addiu $a2, %lo(gNumRacers) # addiu $a2, $a2, -0x5110
/* 023ADC 80022EDC 240F0001 */  li    $t7, 1
/* 023AE0 80022EE0 ADCD0000 */  sw    $t5, ($t6)
/* 023AE4 80022EE4 ACCF0000 */  sw    $t7, ($a2)
/* 023AE8 80022EE8 3C058012 */  lui   $a1, %hi(D_8011AE60) # $a1, 0x8012
/* 023AEC 80022EEC 3C038012 */  lui   $v1, %hi(gObjectCount) # $v1, 0x8012
/* 023AF0 80022EF0 8C63AE5C */  lw    $v1, %lo(gObjectCount)($v1)
/* 023AF4 80022EF4 8CA5AE60 */  lw    $a1, %lo(D_8011AE60)($a1)
/* 023AF8 80022EF8 3C188012 */  lui   $t8, %hi(gObjPtrList) # $t8, 0x8012
/* 023AFC 80022EFC 00A3082A */  slt   $at, $a1, $v1
/* 023B00 80022F00 10200013 */  beqz  $at, .L80022F50
/* 023B04 80022F04 00051080 */   sll   $v0, $a1, 2
/* 023B08 80022F08 8F18AE58 */  lw    $t8, %lo(gObjPtrList)($t8)
/* 023B0C 80022F0C 00033080 */  sll   $a2, $v1, 2
/* 023B10 80022F10 2405003E */  li    $a1, 62
/* 023B14 80022F14 03022021 */  addu  $a0, $t8, $v0
.L80022F18:
/* 023B18 80022F18 8C830000 */  lw    $v1, ($a0)
/* 023B1C 80022F1C 24420004 */  addiu $v0, $v0, 4
/* 023B20 80022F20 84790006 */  lh    $t9, 6($v1)
/* 023B24 80022F24 0046082A */  slt   $at, $v0, $a2
/* 023B28 80022F28 33288000 */  andi  $t0, $t9, 0x8000
/* 023B2C 80022F2C 15000006 */  bnez  $t0, .L80022F48
/* 023B30 80022F30 00000000 */   nop   
/* 023B34 80022F34 84690048 */  lh    $t1, 0x48($v1)
/* 023B38 80022F38 00000000 */  nop   
/* 023B3C 80022F3C 14A90002 */  bne   $a1, $t1, .L80022F48
/* 023B40 80022F40 00000000 */   nop   
/* 023B44 80022F44 AFA3001C */  sw    $v1, 0x1c($sp)
.L80022F48:
/* 023B48 80022F48 1420FFF3 */  bnez  $at, .L80022F18
/* 023B4C 80022F4C 24840004 */   addiu $a0, $a0, 4
.L80022F50:
/* 023B50 80022F50 8CEA0000 */  lw    $t2, ($a3)
/* 023B54 80022F54 00000000 */  nop   
/* 023B58 80022F58 8D4B0000 */  lw    $t3, ($t2)
/* 023B5C 80022F5C 00000000 */  nop   
/* 023B60 80022F60 8D630064 */  lw    $v1, 0x64($t3)
/* 023B64 80022F64 00000000 */  nop   
/* 023B68 80022F68 8C64015C */  lw    $a0, 0x15c($v1)
/* 023B6C 80022F6C 00000000 */  nop   
/* 023B70 80022F70 10800007 */  beqz  $a0, .L80022F90
/* 023B74 80022F74 8FAC0030 */   lw    $t4, 0x30($sp)
/* 023B78 80022F78 0C003FEE */  jal   free_object
/* 023B7C 80022F7C AFA30024 */   sw    $v1, 0x24($sp)
/* 023B80 80022F80 8FA30024 */  lw    $v1, 0x24($sp)
/* 023B84 80022F84 00000000 */  nop   
/* 023B88 80022F88 AC60015C */  sw    $zero, 0x15c($v1)
/* 023B8C 80022F8C 8FAC0030 */  lw    $t4, 0x30($sp)
.L80022F90:
/* 023B90 80022F90 00000000 */  nop   
/* 023B94 80022F94 1580002C */  bnez  $t4, .L80023048
/* 023B98 80022F98 00000000 */   nop   
/* 023B9C 80022F9C 846D01AC */  lh    $t5, 0x1ac($v1)
/* 023BA0 80022FA0 24010001 */  li    $at, 1
/* 023BA4 80022FA4 15A1001F */  bne   $t5, $at, .L80023024
/* 023BA8 80022FA8 00000000 */   nop   
/* 023BAC 80022FAC 0C01BAA4 */  jal   get_settings
/* 023BB0 80022FB0 AFA30024 */   sw    $v1, 0x24($sp)
/* 023BB4 80022FB4 8FA30024 */  lw    $v1, 0x24($sp)
/* 023BB8 80022FB8 94580014 */  lhu   $t8, 0x14($v0)
/* 023BBC 80022FBC 806701D6 */  lb    $a3, 0x1d6($v1)
/* 023BC0 80022FC0 240F0001 */  li    $t7, 1
/* 023BC4 80022FC4 24EE0003 */  addiu $t6, $a3, 3
/* 023BC8 80022FC8 01CF2804 */  sllv  $a1, $t7, $t6
/* 023BCC 80022FCC 0305C824 */  and   $t9, $t8, $a1
/* 023BD0 80022FD0 13200005 */  beqz  $t9, .L80022FE8
/* 023BD4 80022FD4 00403025 */   move  $a2, $v0
/* 023BD8 80022FD8 0C0274CC */  jal   set_next_taj_challenge_menu
/* 023BDC 80022FDC 24040005 */   li    $a0, 5
/* 023BE0 80022FE0 10000013 */  b     .L80023030
/* 023BE4 80022FE4 8FAB001C */   lw    $t3, 0x1c($sp)
.L80022FE8:
/* 023BE8 80022FE8 24E40006 */  addiu $a0, $a3, 6
/* 023BEC 80022FEC AFA5002C */  sw    $a1, 0x2c($sp)
/* 023BF0 80022FF0 0C0274CC */  jal   set_next_taj_challenge_menu
/* 023BF4 80022FF4 AFA60020 */   sw    $a2, 0x20($sp)
/* 023BF8 80022FF8 8FA60020 */  lw    $a2, 0x20($sp)
/* 023BFC 80022FFC 8FA5002C */  lw    $a1, 0x2c($sp)
/* 023C00 80023000 94C80014 */  lhu   $t0, 0x14($a2)
/* 023C04 80023004 00000000 */  nop   
/* 023C08 80023008 01054825 */  or    $t1, $t0, $a1
/* 023C0C 8002300C 0C027068 */  jal   get_save_file_index
/* 023C10 80023010 A4C90014 */   sh    $t1, 0x14($a2)
/* 023C14 80023014 0C01BB12 */  jal   safe_mark_write_save_file
/* 023C18 80023018 00402025 */   move  $a0, $v0
/* 023C1C 8002301C 10000004 */  b     .L80023030
/* 023C20 80023020 8FAB001C */   lw    $t3, 0x1c($sp)
.L80023024:
/* 023C24 80023024 0C0274CC */  jal   set_next_taj_challenge_menu
/* 023C28 80023028 24040004 */   li    $a0, 4
/* 023C2C 8002302C 8FAB001C */  lw    $t3, 0x1c($sp)
.L80023030:
/* 023C30 80023030 240A001F */  li    $t2, 31
/* 023C34 80023034 24040002 */  li    $a0, 2
/* 023C38 80023038 0C01486E */  jal   set_taj_status
/* 023C3C 8002303C AD6A0078 */   sw    $t2, 0x78($t3)
/* 023C40 80023040 10000016 */  b     .L8002309C
/* 023C44 80023044 00000000 */   nop   
.L80023048:
/* 023C48 80023048 0C0002CA */  jal   func_80000B28
/* 023C4C 8002304C 00000000 */   nop   
/* 023C50 80023050 0C000611 */  jal   func_80001844
/* 023C54 80023054 00000000 */   nop   
/* 023C58 80023058 0C0274CC */  jal   set_next_taj_challenge_menu
/* 023C5C 8002305C 00002025 */   move  $a0, $zero
/* 023C60 80023060 0C00205A */  jal   func_80008168
/* 023C64 80023064 00000000 */   nop   
/* 023C68 80023068 8FAC0030 */  lw    $t4, 0x30($sp)
/* 023C6C 8002306C 24010002 */  li    $at, 2
/* 023C70 80023070 15810003 */  bne   $t4, $at, .L80023080
/* 023C74 80023074 00000000 */   nop   
/* 023C78 80023078 0C030C7B */  jal   set_current_text
/* 023C7C 8002307C 00002025 */   move  $a0, $zero
.L80023080:
/* 023C80 80023080 3C018012 */  lui   $at, %hi(D_8011ADB0) # $at, 0x8012
/* 023C84 80023084 AC20ADB0 */  sw    $zero, %lo(D_8011ADB0)($at)
/* 023C88 80023088 8FAF001C */  lw    $t7, 0x1c($sp)
/* 023C8C 8002308C 3C018012 */  lui   $at, %hi(gRaceStartCountdown) # $at, 0x8012
/* 023C90 80023090 AC20ADB8 */  sw    $zero, %lo(gRaceStartCountdown)($at)
/* 023C94 80023094 240D0014 */  li    $t5, 20
/* 023C98 80023098 ADED0078 */  sw    $t5, 0x78($t7)
.L8002309C:
/* 023C9C 8002309C 0C0002CA */  jal   func_80000B28
/* 023CA0 800230A0 00000000 */   nop   
/* 023CA4 800230A4 0C0282DD */  jal   func_800A0B74
/* 023CA8 800230A8 00000000 */   nop   
/* 023CAC 800230AC 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 023CB0 800230B0 44816000 */  mtc1  $at, $f12
/* 023CB4 800230B4 0C01AF44 */  jal   start_level_music
/* 023CB8 800230B8 00000000 */   nop   
/* 023CBC 800230BC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 023CC0 800230C0 3C018012 */  lui   $at, %hi(gIsTajChallenge) # $at, 0x8012
/* 023CC4 800230C4 A020AEF6 */  sb    $zero, %lo(gIsTajChallenge)($at)
/* 023CC8 800230C8 03E00008 */  jr    $ra
/* 023CCC 800230CC 27BD0030 */   addiu $sp, $sp, 0x30

