glabel menu_character_select_loop
/* 08C924 8008BD24 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 08C928 8008BD28 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08C92C 8008BD2C 0C022C83 */  jal   draw_character_select_text
/* 08C930 8008BD30 AFA40030 */   sw    $a0, 0x30($sp)
/* 08C934 8008BD34 8FA40030 */  lw    $a0, 0x30($sp)
/* 08C938 8008BD38 0C02305A */  jal   func_8008C168
/* 08C93C 8008BD3C 00000000 */   nop   
/* 08C940 8008BD40 0C02393B */  jal   func_8008E4EC
/* 08C944 8008BD44 00000000 */   nop   
/* 08C948 8008BD48 3C028012 */  lui   $v0, %hi(D_801263DC) # $v0, 0x8012
/* 08C94C 8008BD4C 3C048012 */  lui   $a0, %hi(D_801263E0) # $a0, 0x8012
/* 08C950 8008BD50 248463E0 */  addiu $a0, %lo(D_801263E0) # addiu $a0, $a0, 0x63e0
/* 08C954 8008BD54 244263DC */  addiu $v0, %lo(D_801263DC) # addiu $v0, $v0, 0x63dc
/* 08C958 8008BD58 240A0001 */  li    $t2, 1
/* 08C95C 8008BD5C 24030002 */  li    $v1, 2
.L8008BD60:
/* 08C960 8008BD60 804E0000 */  lb    $t6, ($v0)
/* 08C964 8008BD64 00000000 */  nop   
/* 08C968 8008BD68 154E0002 */  bne   $t2, $t6, .L8008BD74
/* 08C96C 8008BD6C 00000000 */   nop   
/* 08C970 8008BD70 A0430000 */  sb    $v1, ($v0)
.L8008BD74:
/* 08C974 8008BD74 24420001 */  addiu $v0, $v0, 1
/* 08C978 8008BD78 0044082B */  sltu  $at, $v0, $a0
/* 08C97C 8008BD7C 1420FFF8 */  bnez  $at, .L8008BD60
/* 08C980 8008BD80 00000000 */   nop   
/* 08C984 8008BD84 3C03800E */  lui   $v1, %hi(gMenuDelay) # $v1, 0x800e
/* 08C988 8008BD88 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 08C98C 8008BD8C 2463F47C */  addiu $v1, %lo(gMenuDelay) # addiu $v1, $v1, -0xb84
/* 08C990 8008BD90 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
/* 08C994 8008BD94 8C620000 */  lw    $v0, ($v1)
/* 08C998 8008BD98 3C0F8012 */  lui   $t7, %hi(gActivePlayersArray) # $t7, 0x8012
/* 08C99C 8008BD9C 1440001B */  bnez  $v0, .L8008BE0C
/* 08C9A0 8008BDA0 3C188012 */   lui   $t8, %hi(gActivePlayersArray+1) # $t8, 0x8012
/* 08C9A4 8008BDA4 3C198012 */  lui   $t9, %hi(gActivePlayersArray+2) # $t9, 0x8012
/* 08C9A8 8008BDA8 3C0C8012 */  lui   $t4, %hi(gActivePlayersArray+3) # $t4, 0x8012
/* 08C9AC 8008BDAC 818C63D7 */  lb    $t4, %lo(gActivePlayersArray+3)($t4)
/* 08C9B0 8008BDB0 833963D6 */  lb    $t9, %lo(gActivePlayersArray+2)($t9)
/* 08C9B4 8008BDB4 81EF63D4 */  lb    $t7, %lo(gActivePlayersArray)($t7)
/* 08C9B8 8008BDB8 831863D5 */  lb    $t8, %lo(gActivePlayersArray+1)($t8)
/* 08C9BC 8008BDBC A3AC0023 */  sb    $t4, 0x23($sp)
/* 08C9C0 8008BDC0 A3B90022 */  sb    $t9, 0x22($sp)
/* 08C9C4 8008BDC4 A3AF0020 */  sb    $t7, 0x20($sp)
/* 08C9C8 8008BDC8 0C022CD6 */  jal   func_8008B358
/* 08C9CC 8008BDCC A3B80021 */   sb    $t8, 0x21($sp)
/* 08C9D0 8008BDD0 3C0D800E */  lui   $t5, %hi(gNumberOfActivePlayers) # $t5, 0x800e
/* 08C9D4 8008BDD4 3C0E800E */  lui   $t6, %hi(gNumberOfReadyPlayers) # $t6, 0x800e
/* 08C9D8 8008BDD8 8DCEF480 */  lw    $t6, %lo(gNumberOfReadyPlayers)($t6)
/* 08C9DC 8008BDDC 8DADF4BC */  lw    $t5, %lo(gNumberOfActivePlayers)($t5)
/* 08C9E0 8008BDE0 00000000 */  nop   
/* 08C9E4 8008BDE4 15AE0005 */  bne   $t5, $t6, .L8008BDFC
/* 08C9E8 8008BDE8 00000000 */   nop   
/* 08C9EC 8008BDEC 0C022D32 */  jal   func_8008B4C8
/* 08C9F0 8008BDF0 00000000 */   nop   
/* 08C9F4 8008BDF4 10000078 */  b     .L8008BFD8
/* 08C9F8 8008BDF8 00001025 */   move  $v0, $zero
.L8008BDFC:
/* 08C9FC 8008BDFC 0C022DD6 */  jal   func_8008B758
/* 08CA00 8008BE00 27A40020 */   addiu $a0, $sp, 0x20
/* 08CA04 8008BE04 10000074 */  b     .L8008BFD8
/* 08CA08 8008BE08 00001025 */   move  $v0, $zero
.L8008BE0C:
/* 08CA0C 8008BE0C 18400060 */  blez  $v0, .L8008BF90
/* 08CA10 8008BE10 00000000 */   nop   
/* 08CA14 8008BE14 8FAF0030 */  lw    $t7, 0x30($sp)
/* 08CA18 8008BE18 3C0C800E */  lui   $t4, %hi(D_800DFFD0) # $t4, 0x800e
/* 08CA1C 8008BE1C 004FC021 */  addu  $t8, $v0, $t7
/* 08CA20 8008BE20 2B01001F */  slti  $at, $t8, 0x1f
/* 08CA24 8008BE24 1420006B */  bnez  $at, .L8008BFD4
/* 08CA28 8008BE28 AC780000 */   sw    $t8, ($v1)
/* 08CA2C 8008BE2C 8D8CFFD0 */  lw    $t4, %lo(D_800DFFD0)($t4)
/* 08CA30 8008BE30 00005825 */  move  $t3, $zero
/* 08CA34 8008BE34 15800007 */  bnez  $t4, .L8008BE54
/* 08CA38 8008BE38 3C0D800E */   lui   $t5, %hi(gActiveMagicCodes) # $t5, 0x800e
/* 08CA3C 8008BE3C 8DADFD98 */  lw    $t5, %lo(gActiveMagicCodes)($t5)
/* 08CA40 8008BE40 01405825 */  move  $t3, $t2
/* 08CA44 8008BE44 000D71C0 */  sll   $t6, $t5, 7
/* 08CA48 8008BE48 05C10002 */  bgez  $t6, .L8008BE54
/* 08CA4C 8008BE4C 00000000 */   nop   
/* 08CA50 8008BE50 254B0001 */  addiu $t3, $t2, 1
.L8008BE54:
/* 08CA54 8008BE54 0C02304A */  jal   func_8008C128
/* 08CA58 8008BE58 AFAB0024 */   sw    $t3, 0x24($sp)
/* 08CA5C 8008BE5C 3C038012 */  lui   $v1, %hi(gActivePlayersArray) # $v1, 0x8012
/* 08CA60 8008BE60 3C078012 */  lui   $a3, %hi(gPlayersCharacterArray) # $a3, 0x8012
/* 08CA64 8008BE64 3C068012 */  lui   $a2, %hi(D_801263CC) # $a2, 0x8012
/* 08CA68 8008BE68 3C058012 */  lui   $a1, %hi(gCharacterIdSlots) # $a1, 0x8012
/* 08CA6C 8008BE6C 8FAB0024 */  lw    $t3, 0x24($sp)
/* 08CA70 8008BE70 00002025 */  move  $a0, $zero
/* 08CA74 8008BE74 24A563F0 */  addiu $a1, %lo(gCharacterIdSlots) # addiu $a1, $a1, 0x63f0
/* 08CA78 8008BE78 24C663CC */  addiu $a2, %lo(D_801263CC) # addiu $a2, $a2, 0x63cc
/* 08CA7C 8008BE7C 24E763E8 */  addiu $a3, %lo(gPlayersCharacterArray) # addiu $a3, $a3, 0x63e8
/* 08CA80 8008BE80 246363D4 */  addiu $v1, %lo(gActivePlayersArray) # addiu $v1, $v1, 0x63d4
/* 08CA84 8008BE84 00001025 */  move  $v0, $zero
/* 08CA88 8008BE88 24090004 */  li    $t1, 4
/* 08CA8C 8008BE8C 2408000E */  li    $t0, 14
.L8008BE90:
/* 08CA90 8008BE90 806F0000 */  lb    $t7, ($v1)
/* 08CA94 8008BE94 00E2C821 */  addu  $t9, $a3, $v0
/* 08CA98 8008BE98 11E0000B */  beqz  $t7, .L8008BEC8
/* 08CA9C 8008BE9C 00000000 */   nop   
/* 08CAA0 8008BEA0 832C0000 */  lb    $t4, ($t9)
/* 08CAA4 8008BEA4 8CD80000 */  lw    $t8, ($a2)
/* 08CAA8 8008BEA8 01880019 */  multu $t4, $t0
/* 08CAAC 8008BEAC 00A4C821 */  addu  $t9, $a1, $a0
/* 08CAB0 8008BEB0 24840001 */  addiu $a0, $a0, 1
/* 08CAB4 8008BEB4 00006812 */  mflo  $t5
/* 08CAB8 8008BEB8 030D7021 */  addu  $t6, $t8, $t5
/* 08CABC 8008BEBC 85CF000C */  lh    $t7, 0xc($t6)
/* 08CAC0 8008BEC0 00000000 */  nop   
/* 08CAC4 8008BEC4 A32F0000 */  sb    $t7, ($t9)
.L8008BEC8:
/* 08CAC8 8008BEC8 24420001 */  addiu $v0, $v0, 1
/* 08CACC 8008BECC 1449FFF0 */  bne   $v0, $t1, .L8008BE90
/* 08CAD0 8008BED0 24630001 */   addiu $v1, $v1, 1
/* 08CAD4 8008BED4 0C022ECF */  jal   randomize_ai_racer_slots
/* 08CAD8 8008BED8 AFAB0024 */   sw    $t3, 0x24($sp)
/* 08CADC 8008BEDC 3C048012 */  lui   $a0, %hi(gActivePlayersArray) # $a0, 0x8012
/* 08CAE0 8008BEE0 0C01A916 */  jal   assign_player_ids
/* 08CAE4 8008BEE4 248463D4 */   addiu $a0, %lo(gActivePlayersArray) # addiu $a0, $a0, 0x63d4
/* 08CAE8 8008BEE8 3C0C800E */  lui   $t4, %hi(gNumberOfActivePlayers) # $t4, 0x800e
/* 08CAEC 8008BEEC 8FAB0024 */  lw    $t3, 0x24($sp)
/* 08CAF0 8008BEF0 8D8CF4BC */  lw    $t4, %lo(gNumberOfActivePlayers)($t4)
/* 08CAF4 8008BEF4 240A0001 */  li    $t2, 1
/* 08CAF8 8008BEF8 3C01800E */  lui   $at, %hi(gIsInTracksMode) # $at, 0x800e
/* 08CAFC 8008BEFC AC2AF4B8 */  sw    $t2, %lo(gIsInTracksMode)($at)
/* 08CB00 8008BF00 016C082A */  slt   $at, $t3, $t4
/* 08CB04 8008BF04 14200018 */  bnez  $at, .L8008BF68
/* 08CB08 8008BF08 00000000 */   nop   
/* 08CB0C 8008BF0C 0C0002C6 */  jal   func_80000B18
/* 08CB10 8008BF10 00000000 */   nop   
/* 08CB14 8008BF14 24040027 */  li    $a0, 39
/* 08CB18 8008BF18 2405FFFF */  li    $a1, -1
/* 08CB1C 8008BF1C 0C01B8BA */  jal   load_level_for_menu
/* 08CB20 8008BF20 00003025 */   move  $a2, $zero
/* 08CB24 8008BF24 3C18800E */  lui   $t8, %hi(gNumberOfActivePlayers) # $t8, 0x800e
/* 08CB28 8008BF28 8F18F4BC */  lw    $t8, %lo(gNumberOfActivePlayers)($t8)
/* 08CB2C 8008BF2C 240A0001 */  li    $t2, 1
/* 08CB30 8008BF30 15580009 */  bne   $t2, $t8, .L8008BF58
/* 08CB34 8008BF34 3C0D800E */   lui   $t5, %hi(gPlayerHasSeenCautionMenu) # $t5, 0x800e
/* 08CB38 8008BF38 8DADF498 */  lw    $t5, %lo(gPlayerHasSeenCautionMenu)($t5)
/* 08CB3C 8008BF3C 00000000 */  nop   
/* 08CB40 8008BF40 15A00005 */  bnez  $t5, .L8008BF58
/* 08CB44 8008BF44 00000000 */   nop   
/* 08CB48 8008BF48 0C0204F4 */  jal   menu_init
/* 08CB4C 8008BF4C 2404001C */   li    $a0, 28
/* 08CB50 8008BF50 10000021 */  b     .L8008BFD8
/* 08CB54 8008BF54 00001025 */   move  $v0, $zero
.L8008BF58:
/* 08CB58 8008BF58 0C0204F4 */  jal   menu_init
/* 08CB5C 8008BF5C 24040013 */   li    $a0, 19
/* 08CB60 8008BF60 1000001D */  b     .L8008BFD8
/* 08CB64 8008BF64 00001025 */   move  $v0, $zero
.L8008BF68:
/* 08CB68 8008BF68 0C0002CA */  jal   func_80000B28
/* 08CB6C 8008BF6C 00000000 */   nop   
/* 08CB70 8008BF70 0C020A2E */  jal   func_800828B8
/* 08CB74 8008BF74 00000000 */   nop   
/* 08CB78 8008BF78 0C01B96F */  jal   func_8006E5BC
/* 08CB7C 8008BF7C 00000000 */   nop   
/* 08CB80 8008BF80 0C0204F4 */  jal   menu_init
/* 08CB84 8008BF84 2404000F */   li    $a0, 15
/* 08CB88 8008BF88 10000013 */  b     .L8008BFD8
/* 08CB8C 8008BF8C 00001025 */   move  $v0, $zero
.L8008BF90:
/* 08CB90 8008BF90 04410010 */  bgez  $v0, .L8008BFD4
/* 08CB94 8008BF94 00000000 */   nop   
/* 08CB98 8008BF98 8FAE0030 */  lw    $t6, 0x30($sp)
/* 08CB9C 8008BF9C 00000000 */  nop   
/* 08CBA0 8008BFA0 004E7823 */  subu  $t7, $v0, $t6
/* 08CBA4 8008BFA4 29E1FFE2 */  slti  $at, $t7, -0x1e
/* 08CBA8 8008BFA8 1020000A */  beqz  $at, .L8008BFD4
/* 08CBAC 8008BFAC AC6F0000 */   sw    $t7, ($v1)
/* 08CBB0 8008BFB0 0C0002CA */  jal   func_80000B28
/* 08CBB4 8008BFB4 00000000 */   nop   
/* 08CBB8 8008BFB8 0C02304A */  jal   func_8008C128
/* 08CBBC 8008BFBC 00000000 */   nop   
/* 08CBC0 8008BFC0 240A0001 */  li    $t2, 1
/* 08CBC4 8008BFC4 3C01800E */  lui   $at, %hi(gNumberOfActivePlayers) # $at, 0x800e
/* 08CBC8 8008BFC8 AC2AF4BC */  sw    $t2, %lo(gNumberOfActivePlayers)($at)
/* 08CBCC 8008BFCC 0C0204F4 */  jal   menu_init
/* 08CBD0 8008BFD0 00002025 */   move  $a0, $zero
.L8008BFD4:
/* 08CBD4 8008BFD4 00001025 */  move  $v0, $zero
.L8008BFD8:
/* 08CBD8 8008BFD8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08CBDC 8008BFDC 27BD0030 */  addiu $sp, $sp, 0x30
/* 08CBE0 8008BFE0 03E00008 */  jr    $ra
/* 08CBE4 8008BFE4 00000000 */   nop   

