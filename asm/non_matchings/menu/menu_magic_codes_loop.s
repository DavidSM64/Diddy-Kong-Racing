glabel menu_magic_codes_loop
/* 08A8D8 80089CD8 27BDFFA0 */  addiu $sp, $sp, -0x60
/* 08A8DC 80089CDC 3C0B8012 */  lui   $t3, %hi(D_801263D8) # $t3, 0x8012
/* 08A8E0 80089CE0 256B63D8 */  addiu $t3, %lo(D_801263D8) # addiu $t3, $t3, 0x63d8
/* 08A8E4 80089CE4 8D620000 */  lw    $v0, ($t3)
/* 08A8E8 80089CE8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08A8EC 80089CEC AFA0004C */  sw    $zero, 0x4c($sp)
/* 08A8F0 80089CF0 AFA00048 */  sw    $zero, 0x48($sp)
/* 08A8F4 80089CF4 AFA00040 */  sw    $zero, 0x40($sp)
/* 08A8F8 80089CF8 00003825 */  move  $a3, $zero
/* 08A8FC 80089CFC AFA0003C */  sw    $zero, 0x3c($sp)
/* 08A900 80089D00 AFA00038 */  sw    $zero, 0x38($sp)
/* 08A904 80089D04 10400005 */  beqz  $v0, .L80089D1C
/* 08A908 80089D08 AFA00034 */   sw    $zero, 0x34($sp)
/* 08A90C 80089D0C 00447023 */  subu  $t6, $v0, $a0
/* 08A910 80089D10 05C10002 */  bgez  $t6, .L80089D1C
/* 08A914 80089D14 AD6E0000 */   sw    $t6, ($t3)
/* 08A918 80089D18 AD600000 */  sw    $zero, ($t3)
.L80089D1C:
/* 08A91C 80089D1C 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08A920 80089D20 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08A924 80089D24 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 08A928 80089D28 1040000F */  beqz  $v0, .L80089D68
/* 08A92C 80089D2C 246363BC */   addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 08A930 80089D30 18400008 */  blez  $v0, .L80089D54
/* 08A934 80089D34 0044C823 */   subu  $t9, $v0, $a0
/* 08A938 80089D38 0044C021 */  addu  $t8, $v0, $a0
/* 08A93C 80089D3C 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08A940 80089D40 AC38F47C */  sw    $t8, %lo(gMenuDelay)($at)
/* 08A944 80089D44 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08A948 80089D48 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08A94C 80089D4C 10000007 */  b     .L80089D6C
/* 08A950 80089D50 8C6E0000 */   lw    $t6, ($v1)
.L80089D54:
/* 08A954 80089D54 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08A958 80089D58 AC39F47C */  sw    $t9, %lo(gMenuDelay)($at)
/* 08A95C 80089D5C 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08A960 80089D60 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08A964 80089D64 00000000 */  nop   
.L80089D68:
/* 08A968 80089D68 8C6E0000 */  lw    $t6, ($v1)
.L80089D6C:
/* 08A96C 80089D6C 2841FFED */  slti  $at, $v0, -0x13
/* 08A970 80089D70 01C47821 */  addu  $t7, $t6, $a0
/* 08A974 80089D74 31F8003F */  andi  $t8, $t7, 0x3f
/* 08A978 80089D78 14200009 */  bnez  $at, .L80089DA0
/* 08A97C 80089D7C AC780000 */   sw    $t8, ($v1)
/* 08A980 80089D80 28410014 */  slti  $at, $v0, 0x14
/* 08A984 80089D84 10200006 */  beqz  $at, .L80089DA0
/* 08A988 80089D88 00000000 */   nop   
/* 08A98C 80089D8C 0C0225A9 */  jal   render_magic_codes_ui
/* 08A990 80089D90 AFA70044 */   sw    $a3, 0x44($sp)
/* 08A994 80089D94 3C0B8012 */  lui   $t3, %hi(D_801263D8) # $t3, 0x8012
/* 08A998 80089D98 8FA70044 */  lw    $a3, 0x44($sp)
/* 08A99C 80089D9C 256B63D8 */  addiu $t3, %lo(D_801263D8) # addiu $t3, $t3, 0x63d8
.L80089DA0:
/* 08A9A0 80089DA0 3C198012 */  lui   $t9, %hi(gIgnorePlayerInput) # $t9, 0x8012
/* 08A9A4 80089DA4 8F3963C4 */  lw    $t9, %lo(gIgnorePlayerInput)($t9)
/* 08A9A8 80089DA8 00005025 */  move  $t2, $zero
/* 08A9AC 80089DAC 00004025 */  move  $t0, $zero
/* 08A9B0 80089DB0 17200025 */  bnez  $t9, .L80089E48
/* 08A9B4 80089DB4 00004825 */   move  $t1, $zero
/* 08A9B8 80089DB8 3C0E800E */  lui   $t6, %hi(gMenuDelay) # $t6, 0x800e
/* 08A9BC 80089DBC 8DCEF47C */  lw    $t6, %lo(gMenuDelay)($t6)
/* 08A9C0 80089DC0 00003025 */  move  $a2, $zero
/* 08A9C4 80089DC4 15C00020 */  bnez  $t6, .L80089E48
/* 08A9C8 80089DC8 3C038012 */   lui   $v1, %hi(gControllersXAxisDirection) # $v1, 0x8012
/* 08A9CC 80089DCC 3C058012 */  lui   $a1, %hi(gControllersYAxisDirection) # $a1, 0x8012
/* 08A9D0 80089DD0 24A56464 */  addiu $a1, %lo(gControllersYAxisDirection) # addiu $a1, $a1, 0x6464
/* 08A9D4 80089DD4 2463645C */  addiu $v1, %lo(gControllersXAxisDirection) # addiu $v1, $v1, 0x645c
.L80089DD8:
/* 08A9D8 80089DD8 00C02025 */  move  $a0, $a2
/* 08A9DC 80089DDC AFA30020 */  sw    $v1, 0x20($sp)
/* 08A9E0 80089DE0 AFA5001C */  sw    $a1, 0x1c($sp)
/* 08A9E4 80089DE4 AFA6005C */  sw    $a2, 0x5c($sp)
/* 08A9E8 80089DE8 AFA70044 */  sw    $a3, 0x44($sp)
/* 08A9EC 80089DEC AFA80054 */  sw    $t0, 0x54($sp)
/* 08A9F0 80089DF0 AFA90050 */  sw    $t1, 0x50($sp)
/* 08A9F4 80089DF4 0C01A955 */  jal   get_buttons_pressed_from_player
/* 08A9F8 80089DF8 AFAA0058 */   sw    $t2, 0x58($sp)
/* 08A9FC 80089DFC 8FA30020 */  lw    $v1, 0x20($sp)
/* 08AA00 80089E00 8FA5001C */  lw    $a1, 0x1c($sp)
/* 08AA04 80089E04 8FA6005C */  lw    $a2, 0x5c($sp)
/* 08AA08 80089E08 8FA80054 */  lw    $t0, 0x54($sp)
/* 08AA0C 80089E0C 8FA90050 */  lw    $t1, 0x50($sp)
/* 08AA10 80089E10 8FAA0058 */  lw    $t2, 0x58($sp)
/* 08AA14 80089E14 806F0000 */  lb    $t7, ($v1)
/* 08AA18 80089E18 80B80000 */  lb    $t8, ($a1)
/* 08AA1C 80089E1C 24010004 */  li    $at, 4
/* 08AA20 80089E20 8FA70044 */  lw    $a3, 0x44($sp)
/* 08AA24 80089E24 24C60001 */  addiu $a2, $a2, 1
/* 08AA28 80089E28 24630001 */  addiu $v1, $v1, 1
/* 08AA2C 80089E2C 24A50001 */  addiu $a1, $a1, 1
/* 08AA30 80089E30 01425025 */  or    $t2, $t2, $v0
/* 08AA34 80089E34 010F4021 */  addu  $t0, $t0, $t7
/* 08AA38 80089E38 14C1FFE7 */  bne   $a2, $at, .L80089DD8
/* 08AA3C 80089E3C 01384821 */   addu  $t1, $t1, $t8
/* 08AA40 80089E40 3C0B8012 */  lui   $t3, %hi(D_801263D8) # $t3, 0x8012
/* 08AA44 80089E44 256B63D8 */  addiu $t3, %lo(D_801263D8) # addiu $t3, $t3, 0x63d8
.L80089E48:
/* 08AA48 80089E48 3C0D8012 */  lui   $t5, %hi(gOptionsMenuItemIndex) # $t5, 0x8012
/* 08AA4C 80089E4C 25AD6C46 */  addiu $t5, %lo(gOptionsMenuItemIndex) # addiu $t5, $t5, 0x6c46
/* 08AA50 80089E50 85A20000 */  lh    $v0, ($t5)
/* 08AA54 80089E54 24010004 */  li    $at, 4
/* 08AA58 80089E58 14410009 */  bne   $v0, $at, .L80089E80
/* 08AA5C 80089E5C 240C0005 */   li    $t4, 5
/* 08AA60 80089E60 8D790000 */  lw    $t9, ($t3)
/* 08AA64 80089E64 314E9000 */  andi  $t6, $t2, 0x9000
/* 08AA68 80089E68 13200003 */  beqz  $t9, .L80089E78
/* 08AA6C 80089E6C 00000000 */   nop   
/* 08AA70 80089E70 11C00155 */  beqz  $t6, .L8008A3C8
/* 08AA74 80089E74 8FAF003C */   lw    $t7, 0x3c($sp)
.L80089E78:
/* 08AA78 80089E78 10000152 */  b     .L8008A3C4
/* 08AA7C 80089E7C A5A00000 */   sh    $zero, ($t5)
.L80089E80:
/* 08AA80 80089E80 158200CD */  bne   $t4, $v0, .L8008A1B8
/* 08AA84 80089E84 241F0006 */   li    $ra, 6
/* 08AA88 80089E88 3C028012 */  lui   $v0, %hi(gCheatInputCurrentColumn) # $v0, 0x8012
/* 08AA8C 80089E8C 24426C42 */  addiu $v0, %lo(gCheatInputCurrentColumn) # addiu $v0, $v0, 0x6c42
/* 08AA90 80089E90 84430000 */  lh    $v1, ($v0)
/* 08AA94 80089E94 3C058012 */  lui   $a1, %hi(gCheatInputCurrentRow) # $a1, 0x8012
/* 08AA98 80089E98 24A56C40 */  addiu $a1, %lo(gCheatInputCurrentRow) # addiu $a1, $a1, 0x6c40
/* 08AA9C 80089E9C 84A40000 */  lh    $a0, ($a1)
/* 08AAA0 80089EA0 306F000F */  andi  $t7, $v1, 0xf
/* 08AAA4 80089EA4 000FC100 */  sll   $t8, $t7, 4
/* 08AAA8 80089EA8 0501000A */  bgez  $t0, .L80089ED4
/* 08AAAC 80089EAC 03043025 */   or    $a2, $t8, $a0
/* 08AAB0 80089EB0 2479FFFF */  addiu $t9, $v1, -1
/* 08AAB4 80089EB4 A4590000 */  sh    $t9, ($v0)
/* 08AAB8 80089EB8 84430000 */  lh    $v1, ($v0)
/* 08AABC 80089EBC 241F0006 */  li    $ra, 6
/* 08AAC0 80089EC0 04610004 */  bgez  $v1, .L80089ED4
/* 08AAC4 80089EC4 00000000 */   nop   
/* 08AAC8 80089EC8 A45F0000 */  sh    $ra, ($v0)
/* 08AACC 80089ECC 84430000 */  lh    $v1, ($v0)
/* 08AAD0 80089ED0 00000000 */  nop   
.L80089ED4:
/* 08AAD4 80089ED4 1900000B */  blez  $t0, .L80089F04
/* 08AAD8 80089ED8 241F0006 */   li    $ra, 6
/* 08AADC 80089EDC 246E0001 */  addiu $t6, $v1, 1
/* 08AAE0 80089EE0 A44E0000 */  sh    $t6, ($v0)
/* 08AAE4 80089EE4 84430000 */  lh    $v1, ($v0)
/* 08AAE8 80089EE8 00000000 */  nop   
/* 08AAEC 80089EEC 28610007 */  slti  $at, $v1, 7
/* 08AAF0 80089EF0 14200004 */  bnez  $at, .L80089F04
/* 08AAF4 80089EF4 00000000 */   nop   
/* 08AAF8 80089EF8 A4400000 */  sh    $zero, ($v0)
/* 08AAFC 80089EFC 84430000 */  lh    $v1, ($v0)
/* 08AB00 80089F00 00000000 */  nop   
.L80089F04:
/* 08AB04 80089F04 3062000F */  andi  $v0, $v1, 0xf
/* 08AB08 80089F08 00027900 */  sll   $t7, $v0, 4
/* 08AB0C 80089F0C 0521000B */  bgez  $t1, .L80089F3C
/* 08AB10 80089F10 01E01025 */   move  $v0, $t7
/* 08AB14 80089F14 24980001 */  addiu $t8, $a0, 1
/* 08AB18 80089F18 A4B80000 */  sh    $t8, ($a1)
/* 08AB1C 80089F1C 84A40000 */  lh    $a0, ($a1)
/* 08AB20 80089F20 00000000 */  nop   
/* 08AB24 80089F24 28810004 */  slti  $at, $a0, 4
/* 08AB28 80089F28 14200004 */  bnez  $at, .L80089F3C
/* 08AB2C 80089F2C 00000000 */   nop   
/* 08AB30 80089F30 A4A00000 */  sh    $zero, ($a1)
/* 08AB34 80089F34 84A40000 */  lh    $a0, ($a1)
/* 08AB38 80089F38 00000000 */  nop   
.L80089F3C:
/* 08AB3C 80089F3C 1920000A */  blez  $t1, .L80089F68
/* 08AB40 80089F40 31588000 */   andi  $t8, $t2, 0x8000
/* 08AB44 80089F44 2499FFFF */  addiu $t9, $a0, -1
/* 08AB48 80089F48 A4B90000 */  sh    $t9, ($a1)
/* 08AB4C 80089F4C 84A40000 */  lh    $a0, ($a1)
/* 08AB50 80089F50 24080003 */  li    $t0, 3
/* 08AB54 80089F54 04810005 */  bgez  $a0, .L80089F6C
/* 08AB58 80089F58 00447025 */   or    $t6, $v0, $a0
/* 08AB5C 80089F5C A4A80000 */  sh    $t0, ($a1)
/* 08AB60 80089F60 84A40000 */  lh    $a0, ($a1)
/* 08AB64 80089F64 00000000 */  nop   
.L80089F68:
/* 08AB68 80089F68 00447025 */  or    $t6, $v0, $a0
.L80089F6C:
/* 08AB6C 80089F6C 10CE0003 */  beq   $a2, $t6, .L80089F7C
/* 08AB70 80089F70 24080003 */   li    $t0, 3
/* 08AB74 80089F74 240F0001 */  li    $t7, 1
/* 08AB78 80089F78 AFAF0034 */  sw    $t7, 0x34($sp)
.L80089F7C:
/* 08AB7C 80089F7C 13000020 */  beqz  $t8, .L8008A000
/* 08AB80 80089F80 00002825 */   move  $a1, $zero
/* 08AB84 80089F84 15040005 */  bne   $t0, $a0, .L80089F9C
/* 08AB88 80089F88 00000000 */   nop   
/* 08AB8C 80089F8C 15830003 */  bne   $t4, $v1, .L80089F9C
/* 08AB90 80089F90 24190001 */   li    $t9, 1
/* 08AB94 80089F94 1000001A */  b     .L8008A000
/* 08AB98 80089F98 AFB9004C */   sw    $t9, 0x4c($sp)
.L80089F9C:
/* 08AB9C 80089F9C 15040005 */  bne   $t0, $a0, .L80089FB4
/* 08ABA0 80089FA0 3C068012 */   lui   $a2, %hi(gCheatInputStringLength) # $a2, 0x8012
/* 08ABA4 80089FA4 17E30003 */  bne   $ra, $v1, .L80089FB4
/* 08ABA8 80089FA8 240E0001 */   li    $t6, 1
/* 08ABAC 80089FAC 10000014 */  b     .L8008A000
/* 08ABB0 80089FB0 AFAE0048 */   sw    $t6, 0x48($sp)
.L80089FB4:
/* 08ABB4 80089FB4 24C66C44 */  addiu $a2, %lo(gCheatInputStringLength) # addiu $a2, $a2, 0x6c44
/* 08ABB8 80089FB8 84C20000 */  lh    $v0, ($a2)
/* 08ABBC 80089FBC 240F0001 */  li    $t7, 1
/* 08ABC0 80089FC0 28410013 */  slti  $at, $v0, 0x13
/* 08ABC4 80089FC4 1020000E */  beqz  $at, .L8008A000
/* 08ABC8 80089FC8 0004C0C0 */   sll   $t8, $a0, 3
/* 08ABCC 80089FCC 0304C023 */  subu  $t8, $t8, $a0
/* 08ABD0 80089FD0 0303C821 */  addu  $t9, $t8, $v1
/* 08ABD4 80089FD4 3C018012 */  lui   $at, %hi(D_80126C58) # $at, 0x8012
/* 08ABD8 80089FD8 AFAF0038 */  sw    $t7, 0x38($sp)
/* 08ABDC 80089FDC 00220821 */  addu  $at, $at, $v0
/* 08ABE0 80089FE0 272E0041 */  addiu $t6, $t9, 0x41
/* 08ABE4 80089FE4 A02E6C58 */  sb    $t6, %lo(D_80126C58)($at)
/* 08ABE8 80089FE8 244F0001 */  addiu $t7, $v0, 1
/* 08ABEC 80089FEC A4CF0000 */  sh    $t7, ($a2)
/* 08ABF0 80089FF0 84D80000 */  lh    $t8, ($a2)
/* 08ABF4 80089FF4 3C018012 */  lui   $at, %hi(D_80126C58) # $at, 0x8012
/* 08ABF8 80089FF8 00380821 */  addu  $at, $at, $t8
/* 08ABFC 80089FFC A0206C58 */  sb    $zero, %lo(D_80126C58)($at)
.L8008A000:
/* 08AC00 8008A000 3C068012 */  lui   $a2, %hi(gCheatInputStringLength) # $a2, 0x8012
/* 08AC04 8008A004 31594000 */  andi  $t9, $t2, 0x4000
/* 08AC08 8008A008 13200008 */  beqz  $t9, .L8008A02C
/* 08AC0C 8008A00C 24C66C44 */   addiu $a2, %lo(gCheatInputStringLength) # addiu $a2, $a2, 0x6c44
/* 08AC10 8008A010 84CE0000 */  lh    $t6, ($a2)
/* 08AC14 8008A014 240F0001 */  li    $t7, 1
/* 08AC18 8008A018 19C00003 */  blez  $t6, .L8008A028
/* 08AC1C 8008A01C 00000000 */   nop   
/* 08AC20 8008A020 10000002 */  b     .L8008A02C
/* 08AC24 8008A024 AFAF004C */   sw    $t7, 0x4c($sp)
.L8008A028:
/* 08AC28 8008A028 A5A00000 */  sh    $zero, ($t5)
.L8008A02C:
/* 08AC2C 8008A02C 31581000 */  andi  $t8, $t2, 0x1000
/* 08AC30 8008A030 13000002 */  beqz  $t8, .L8008A03C
/* 08AC34 8008A034 24190001 */   li    $t9, 1
/* 08AC38 8008A038 AFB90048 */  sw    $t9, 0x48($sp)
.L8008A03C:
/* 08AC3C 8008A03C 8FAE004C */  lw    $t6, 0x4c($sp)
/* 08AC40 8008A040 240400AE */  li    $a0, 174
/* 08AC44 8008A044 11C00011 */  beqz  $t6, .L8008A08C
/* 08AC48 8008A048 8FB90048 */   lw    $t9, 0x48($sp)
/* 08AC4C 8008A04C 0C000741 */  jal   func_80001D04
/* 08AC50 8008A050 AFA70044 */   sw    $a3, 0x44($sp)
/* 08AC54 8008A054 3C068012 */  lui   $a2, %hi(gCheatInputStringLength) # $a2, 0x8012
/* 08AC58 8008A058 24C66C44 */  addiu $a2, %lo(gCheatInputStringLength) # addiu $a2, $a2, 0x6c44
/* 08AC5C 8008A05C 84C20000 */  lh    $v0, ($a2)
/* 08AC60 8008A060 8FA70044 */  lw    $a3, 0x44($sp)
/* 08AC64 8008A064 3C0D8012 */  lui   $t5, %hi(gOptionsMenuItemIndex) # $t5, 0x8012
/* 08AC68 8008A068 18400007 */  blez  $v0, .L8008A088
/* 08AC6C 8008A06C 25AD6C46 */   addiu $t5, %lo(gOptionsMenuItemIndex) # addiu $t5, $t5, 0x6c46
/* 08AC70 8008A070 244FFFFF */  addiu $t7, $v0, -1
/* 08AC74 8008A074 A4CF0000 */  sh    $t7, ($a2)
/* 08AC78 8008A078 84D80000 */  lh    $t8, ($a2)
/* 08AC7C 8008A07C 3C018012 */  lui   $at, %hi(D_80126C58) # $at, 0x8012
/* 08AC80 8008A080 00380821 */  addu  $at, $at, $t8
/* 08AC84 8008A084 A0206C58 */  sb    $zero, %lo(D_80126C58)($at)
.L8008A088:
/* 08AC88 8008A088 8FB90048 */  lw    $t9, 0x48($sp)
.L8008A08C:
/* 08AC8C 8008A08C 00000000 */  nop   
/* 08AC90 8008A090 132000CD */  beqz  $t9, .L8008A3C8
/* 08AC94 8008A094 8FAF003C */   lw    $t7, 0x3c($sp)
/* 08AC98 8008A098 84CF0000 */  lh    $t7, ($a2)
/* 08AC9C 8008A09C 240E0001 */  li    $t6, 1
/* 08ACA0 8008A0A0 15E00003 */  bnez  $t7, .L8008A0B0
/* 08ACA4 8008A0A4 AFAE0038 */   sw    $t6, 0x38($sp)
/* 08ACA8 8008A0A8 100000C6 */  b     .L8008A3C4
/* 08ACAC 8008A0AC A5A00000 */   sh    $zero, ($t5)
.L8008A0B0:
/* 08ACB0 8008A0B0 3C0B8012 */  lui   $t3, %hi(D_80126C4C) # $t3, 0x8012
/* 08ACB4 8008A0B4 3C098012 */  lui   $t1, %hi(gCheatsAssetData) # $t1, 0x8012
/* 08ACB8 8008A0B8 8D296C30 */  lw    $t1, %lo(gCheatsAssetData)($t1)
/* 08ACBC 8008A0BC 256B6C4C */  addiu $t3, %lo(D_80126C4C) # addiu $t3, $t3, 0x6c4c
/* 08ACC0 8008A0C0 A5600000 */  sh    $zero, ($t3)
/* 08ACC4 8008A0C4 3C0A8012 */  lui   $t2, %hi(gNumberOfCheats) # $t2, 0x8012
/* 08ACC8 8008A0C8 8D4A6C38 */  lw    $t2, %lo(gNumberOfCheats)($t2)
/* 08ACCC 8008A0CC 85680000 */  lh    $t0, ($t3)
/* 08ACD0 8008A0D0 000AC040 */  sll   $t8, $t2, 1
/* 08ACD4 8008A0D4 0118082A */  slt   $at, $t0, $t8
/* 08ACD8 8008A0D8 03005025 */  move  $t2, $t8
/* 08ACDC 8008A0DC 1020001F */  beqz  $at, .L8008A15C
/* 08ACE0 8008A0E0 252C0002 */   addiu $t4, $t1, 2
/* 08ACE4 8008A0E4 0008C840 */  sll   $t9, $t0, 1
.L8008A0E8:
/* 08ACE8 8008A0E8 01997021 */  addu  $t6, $t4, $t9
/* 08ACEC 8008A0EC 95CF0000 */  lhu   $t7, ($t6)
/* 08ACF0 8008A0F0 3C058012 */  lui   $a1, %hi(D_80126C57) # $a1, 0x8012
/* 08ACF4 8008A0F4 01E91021 */  addu  $v0, $t7, $t1
/* 08ACF8 8008A0F8 24070001 */  li    $a3, 1
/* 08ACFC 8008A0FC 2444FFFF */  addiu $a0, $v0, -1
/* 08AD00 8008A100 24A56C57 */  addiu $a1, %lo(D_80126C57) # addiu $a1, $a1, 0x6c57
.L8008A104:
/* 08AD04 8008A104 90820001 */  lbu   $v0, 1($a0)
/* 08AD08 8008A108 90A30001 */  lbu   $v1, 1($a1)
/* 08AD0C 8008A10C 24840001 */  addiu $a0, $a0, 1
/* 08AD10 8008A110 10430002 */  beq   $v0, $v1, .L8008A11C
/* 08AD14 8008A114 24A50001 */   addiu $a1, $a1, 1
/* 08AD18 8008A118 00003825 */  move  $a3, $zero
.L8008A11C:
/* 08AD1C 8008A11C 10E00005 */  beqz  $a3, .L8008A134
/* 08AD20 8008A120 00000000 */   nop   
/* 08AD24 8008A124 10400003 */  beqz  $v0, .L8008A134
/* 08AD28 8008A128 00000000 */   nop   
/* 08AD2C 8008A12C 1460FFF5 */  bnez  $v1, .L8008A104
/* 08AD30 8008A130 00000000 */   nop   
.L8008A134:
/* 08AD34 8008A134 14E00004 */  bnez  $a3, .L8008A148
/* 08AD38 8008A138 25180002 */   addiu $t8, $t0, 2
/* 08AD3C 8008A13C A5780000 */  sh    $t8, ($t3)
/* 08AD40 8008A140 85680000 */  lh    $t0, ($t3)
/* 08AD44 8008A144 00000000 */  nop   
.L8008A148:
/* 08AD48 8008A148 010A082A */  slt   $at, $t0, $t2
/* 08AD4C 8008A14C 10200003 */  beqz  $at, .L8008A15C
/* 08AD50 8008A150 00000000 */   nop   
/* 08AD54 8008A154 10E0FFE4 */  beqz  $a3, .L8008A0E8
/* 08AD58 8008A158 0008C840 */   sll   $t9, $t0, 1
.L8008A15C:
/* 08AD5C 8008A15C 14E00003 */  bnez  $a3, .L8008A16C
/* 08AD60 8008A160 2419FFFF */   li    $t9, -1
/* 08AD64 8008A164 1000000E */  b     .L8008A1A0
/* 08AD68 8008A168 A5790000 */   sh    $t9, ($t3)
.L8008A16C:
/* 08AD6C 8008A16C 3C03800E */  lui   $v1, %hi(gUnlockedMagicCodes) # $v1, 0x800e
/* 08AD70 8008A170 2463FD9C */  addiu $v1, %lo(gUnlockedMagicCodes) # addiu $v1, $v1, -0x264
/* 08AD74 8008A174 8C780000 */  lw    $t8, ($v1)
/* 08AD78 8008A178 00087043 */  sra   $t6, $t0, 1
/* 08AD7C 8008A17C 240F0001 */  li    $t7, 1
/* 08AD80 8008A180 01CF1004 */  sllv  $v0, $t7, $t6
/* 08AD84 8008A184 0302C825 */  or    $t9, $t8, $v0
/* 08AD88 8008A188 AC790000 */  sw    $t9, ($v1)
/* 08AD8C 8008A18C 3C0F800E */  lui   $t7, %hi(gActiveMagicCodes) # $t7, 0x800e
/* 08AD90 8008A190 8DEFFD98 */  lw    $t7, %lo(gActiveMagicCodes)($t7)
/* 08AD94 8008A194 3C01800E */  lui   $at, %hi(gActiveMagicCodes) # $at, 0x800e
/* 08AD98 8008A198 01E27025 */  or    $t6, $t7, $v0
/* 08AD9C 8008A19C AC2EFD98 */  sw    $t6, %lo(gActiveMagicCodes)($at)
.L8008A1A0:
/* 08ADA0 8008A1A0 24180004 */  li    $t8, 4
/* 08ADA4 8008A1A4 A5B80000 */  sh    $t8, ($t5)
/* 08ADA8 8008A1A8 241900F0 */  li    $t9, 240
/* 08ADAC 8008A1AC 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 08ADB0 8008A1B0 10000084 */  b     .L8008A3C4
/* 08ADB4 8008A1B4 AC3963D8 */   sw    $t9, %lo(D_801263D8)($at)
.L8008A1B8:
/* 08ADB8 8008A1B8 17E20009 */  bne   $ra, $v0, .L8008A1E0
/* 08ADBC 8008A1BC 3C048012 */   lui   $a0, %hi(D_801263E0) # $a0, 0x8012
/* 08ADC0 8008A1C0 8D6F0000 */  lw    $t7, ($t3)
/* 08ADC4 8008A1C4 314E9000 */  andi  $t6, $t2, 0x9000
/* 08ADC8 8008A1C8 11E00003 */  beqz  $t7, .L8008A1D8
/* 08ADCC 8008A1CC 24180001 */   li    $t8, 1
/* 08ADD0 8008A1D0 11C0007D */  beqz  $t6, .L8008A3C8
/* 08ADD4 8008A1D4 8FAF003C */   lw    $t7, 0x3c($sp)
.L8008A1D8:
/* 08ADD8 8008A1D8 1000007A */  b     .L8008A3C4
/* 08ADDC 8008A1DC A5B80000 */   sh    $t8, ($t5)
.L8008A1E0:
/* 08ADE0 8008A1E0 248463E0 */  addiu $a0, %lo(D_801263E0) # addiu $a0, $a0, 0x63e0
/* 08ADE4 8008A1E4 8C830000 */  lw    $v1, ($a0)
/* 08ADE8 8008A1E8 31599000 */  andi  $t9, $t2, 0x9000
/* 08ADEC 8008A1EC 1060002C */  beqz  $v1, .L8008A2A0
/* 08ADF0 8008A1F0 31589000 */   andi  $t8, $t2, 0x9000
/* 08ADF4 8008A1F4 13200015 */  beqz  $t9, .L8008A24C
/* 08ADF8 8008A1F8 314E4000 */   andi  $t6, $t2, 0x4000
/* 08ADFC 8008A1FC 24010001 */  li    $at, 1
/* 08AE00 8008A200 1461000E */  bne   $v1, $at, .L8008A23C
/* 08AE04 8008A204 240F0001 */   li    $t7, 1
/* 08AE08 8008A208 3C03800E */  lui   $v1, %hi(gUnlockedMagicCodes) # $v1, 0x800e
/* 08AE0C 8008A20C 3C01800E */  lui   $at, %hi(gActiveMagicCodes) # $at, 0x800e
/* 08AE10 8008A210 2463FD9C */  addiu $v1, %lo(gUnlockedMagicCodes) # addiu $v1, $v1, -0x264
/* 08AE14 8008A214 AC20FD98 */  sw    $zero, %lo(gActiveMagicCodes)($at)
/* 08AE18 8008A218 8C6E0000 */  lw    $t6, ($v1)
/* 08AE1C 8008A21C A5BF0000 */  sh    $ra, ($t5)
/* 08AE20 8008A220 31D80003 */  andi  $t8, $t6, 3
/* 08AE24 8008A224 AC780000 */  sw    $t8, ($v1)
/* 08AE28 8008A228 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 08AE2C 8008A22C 241900F0 */  li    $t9, 240
/* 08AE30 8008A230 AFAF0038 */  sw    $t7, 0x38($sp)
/* 08AE34 8008A234 10000003 */  b     .L8008A244
/* 08AE38 8008A238 AC3963D8 */   sw    $t9, %lo(D_801263D8)($at)
.L8008A23C:
/* 08AE3C 8008A23C 240F0001 */  li    $t7, 1
/* 08AE40 8008A240 AFAF003C */  sw    $t7, 0x3c($sp)
.L8008A244:
/* 08AE44 8008A244 1000005F */  b     .L8008A3C4
/* 08AE48 8008A248 AC800000 */   sw    $zero, ($a0)
.L8008A24C:
/* 08AE4C 8008A24C 11C00004 */  beqz  $t6, .L8008A260
/* 08AE50 8008A250 24180001 */   li    $t8, 1
/* 08AE54 8008A254 AFB8003C */  sw    $t8, 0x3c($sp)
/* 08AE58 8008A258 1000005A */  b     .L8008A3C4
/* 08AE5C 8008A25C AC800000 */   sw    $zero, ($a0)
.L8008A260:
/* 08AE60 8008A260 05210007 */  bgez  $t1, .L8008A280
/* 08AE64 8008A264 24010001 */   li    $at, 1
/* 08AE68 8008A268 14610005 */  bne   $v1, $at, .L8008A280
/* 08AE6C 8008A26C 24190001 */   li    $t9, 1
/* 08AE70 8008A270 240F0002 */  li    $t7, 2
/* 08AE74 8008A274 AFB90034 */  sw    $t9, 0x34($sp)
/* 08AE78 8008A278 10000052 */  b     .L8008A3C4
/* 08AE7C 8008A27C AC8F0000 */   sw    $t7, ($a0)
.L8008A280:
/* 08AE80 8008A280 19200050 */  blez  $t1, .L8008A3C4
/* 08AE84 8008A284 24010002 */   li    $at, 2
/* 08AE88 8008A288 1461004E */  bne   $v1, $at, .L8008A3C4
/* 08AE8C 8008A28C 240E0001 */   li    $t6, 1
/* 08AE90 8008A290 24180001 */  li    $t8, 1
/* 08AE94 8008A294 AFAE0034 */  sw    $t6, 0x34($sp)
/* 08AE98 8008A298 1000004A */  b     .L8008A3C4
/* 08AE9C 8008A29C AC980000 */   sw    $t8, ($a0)
.L8008A2A0:
/* 08AEA0 8008A2A0 0521000B */  bgez  $t1, .L8008A2D0
/* 08AEA4 8008A2A4 00403025 */   move  $a2, $v0
/* 08AEA8 8008A2A8 24590001 */  addiu $t9, $v0, 1
/* 08AEAC 8008A2AC A5B90000 */  sh    $t9, ($t5)
/* 08AEB0 8008A2B0 85A20000 */  lh    $v0, ($t5)
/* 08AEB4 8008A2B4 24080003 */  li    $t0, 3
/* 08AEB8 8008A2B8 28410004 */  slti  $at, $v0, 4
/* 08AEBC 8008A2BC 14200004 */  bnez  $at, .L8008A2D0
/* 08AEC0 8008A2C0 00000000 */   nop   
/* 08AEC4 8008A2C4 A5A80000 */  sh    $t0, ($t5)
/* 08AEC8 8008A2C8 85A20000 */  lh    $v0, ($t5)
/* 08AECC 8008A2CC 00000000 */  nop   
.L8008A2D0:
/* 08AED0 8008A2D0 1920000A */  blez  $t1, .L8008A2FC
/* 08AED4 8008A2D4 24080003 */   li    $t0, 3
/* 08AED8 8008A2D8 244FFFFF */  addiu $t7, $v0, -1
/* 08AEDC 8008A2DC A5AF0000 */  sh    $t7, ($t5)
/* 08AEE0 8008A2E0 85A20000 */  lh    $v0, ($t5)
/* 08AEE4 8008A2E4 00000000 */  nop   
/* 08AEE8 8008A2E8 04410004 */  bgez  $v0, .L8008A2FC
/* 08AEEC 8008A2EC 00000000 */   nop   
/* 08AEF0 8008A2F0 A5A00000 */  sh    $zero, ($t5)
/* 08AEF4 8008A2F4 85A20000 */  lh    $v0, ($t5)
/* 08AEF8 8008A2F8 00000000 */  nop   
.L8008A2FC:
/* 08AEFC 8008A2FC 10C20002 */  beq   $a2, $v0, .L8008A308
/* 08AF00 8008A300 240E0001 */   li    $t6, 1
/* 08AF04 8008A304 AFAE0034 */  sw    $t6, 0x34($sp)
.L8008A308:
/* 08AF08 8008A308 1300001D */  beqz  $t8, .L8008A380
/* 08AF0C 8008A30C 24190001 */   li    $t9, 1
/* 08AF10 8008A310 15020004 */  bne   $t0, $v0, .L8008A324
/* 08AF14 8008A314 AFB90038 */   sw    $t9, 0x38($sp)
/* 08AF18 8008A318 240FFFFF */  li    $t7, -1
/* 08AF1C 8008A31C 10000018 */  b     .L8008A380
/* 08AF20 8008A320 AFAF0040 */   sw    $t7, 0x40($sp)
.L8008A324:
/* 08AF24 8008A324 1440000D */  bnez  $v0, .L8008A35C
/* 08AF28 8008A328 3C058012 */   lui   $a1, %hi(gCheatInputCurrentRow) # $a1, 0x8012
/* 08AF2C 8008A32C 3C028012 */  lui   $v0, %hi(gCheatInputCurrentColumn) # $v0, 0x8012
/* 08AF30 8008A330 3C068012 */  lui   $a2, %hi(gCheatInputStringLength) # $a2, 0x8012
/* 08AF34 8008A334 24C66C44 */  addiu $a2, %lo(gCheatInputStringLength) # addiu $a2, $a2, 0x6c44
/* 08AF38 8008A338 24426C42 */  addiu $v0, %lo(gCheatInputCurrentColumn) # addiu $v0, $v0, 0x6c42
/* 08AF3C 8008A33C 24A56C40 */  addiu $a1, %lo(gCheatInputCurrentRow) # addiu $a1, $a1, 0x6c40
/* 08AF40 8008A340 A4A00000 */  sh    $zero, ($a1)
/* 08AF44 8008A344 A4400000 */  sh    $zero, ($v0)
/* 08AF48 8008A348 A4C00000 */  sh    $zero, ($a2)
/* 08AF4C 8008A34C 3C018012 */  lui   $at, %hi(D_80126C58) # $at, 0x8012
/* 08AF50 8008A350 A0206C58 */  sb    $zero, %lo(D_80126C58)($at)
/* 08AF54 8008A354 1000000A */  b     .L8008A380
/* 08AF58 8008A358 A5AC0000 */   sh    $t4, ($t5)
.L8008A35C:
/* 08AF5C 8008A35C 24010001 */  li    $at, 1
/* 08AF60 8008A360 14410003 */  bne   $v0, $at, .L8008A370
/* 08AF64 8008A364 240E0002 */   li    $t6, 2
/* 08AF68 8008A368 10000005 */  b     .L8008A380
/* 08AF6C 8008A36C AC8E0000 */   sw    $t6, ($a0)
.L8008A370:
/* 08AF70 8008A370 24010002 */  li    $at, 2
/* 08AF74 8008A374 14410002 */  bne   $v0, $at, .L8008A380
/* 08AF78 8008A378 24180001 */   li    $t8, 1
/* 08AF7C 8008A37C AFB80040 */  sw    $t8, 0x40($sp)
.L8008A380:
/* 08AF80 8008A380 31594000 */  andi  $t9, $t2, 0x4000
/* 08AF84 8008A384 13200002 */  beqz  $t9, .L8008A390
/* 08AF88 8008A388 240FFFFF */   li    $t7, -1
/* 08AF8C 8008A38C AFAF0040 */  sw    $t7, 0x40($sp)
.L8008A390:
/* 08AF90 8008A390 8FAE0040 */  lw    $t6, 0x40($sp)
/* 08AF94 8008A394 00000000 */  nop   
/* 08AF98 8008A398 11C0000B */  beqz  $t6, .L8008A3C8
/* 08AF9C 8008A39C 8FAF003C */   lw    $t7, 0x3c($sp)
/* 08AFA0 8008A3A0 05C10003 */  bgez  $t6, .L8008A3B0
/* 08AFA4 8008A3A4 3C01800E */   lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08AFA8 8008A3A8 24180001 */  li    $t8, 1
/* 08AFAC 8008A3AC AFB8003C */  sw    $t8, 0x3c($sp)
.L8008A3B0:
/* 08AFB0 8008A3B0 8FB90040 */  lw    $t9, 0x40($sp)
/* 08AFB4 8008A3B4 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08AFB8 8008A3B8 2484F774 */  addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08AFBC 8008A3BC 0C030076 */  jal   func_800C01D8
/* 08AFC0 8008A3C0 AC39F47C */   sw    $t9, %lo(gMenuDelay)($at)
.L8008A3C4:
/* 08AFC4 8008A3C4 8FAF003C */  lw    $t7, 0x3c($sp)
.L8008A3C8:
/* 08AFC8 8008A3C8 00000000 */  nop   
/* 08AFCC 8008A3CC 11E00005 */  beqz  $t7, .L8008A3E4
/* 08AFD0 8008A3D0 24040241 */   li    $a0, 577
/* 08AFD4 8008A3D4 0C000741 */  jal   func_80001D04
/* 08AFD8 8008A3D8 00002825 */   move  $a1, $zero
/* 08AFDC 8008A3DC 1000000D */  b     .L8008A414
/* 08AFE0 8008A3E0 00000000 */   nop   
.L8008A3E4:
/* 08AFE4 8008A3E4 8FAE0038 */  lw    $t6, 0x38($sp)
/* 08AFE8 8008A3E8 8FB80034 */  lw    $t8, 0x34($sp)
/* 08AFEC 8008A3EC 11C00005 */  beqz  $t6, .L8008A404
/* 08AFF0 8008A3F0 240400EF */   li    $a0, 239
/* 08AFF4 8008A3F4 0C000741 */  jal   func_80001D04
/* 08AFF8 8008A3F8 00002825 */   move  $a1, $zero
/* 08AFFC 8008A3FC 10000005 */  b     .L8008A414
/* 08B000 8008A400 00000000 */   nop   
.L8008A404:
/* 08B004 8008A404 13000003 */  beqz  $t8, .L8008A414
/* 08B008 8008A408 240400EB */   li    $a0, 235
/* 08B00C 8008A40C 0C000741 */  jal   func_80001D04
/* 08B010 8008A410 00002825 */   move  $a1, $zero
.L8008A414:
/* 08B014 8008A414 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08B018 8008A418 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08B01C 8008A41C 3C018012 */  lui   $at, %hi(gIgnorePlayerInput) # $at, 0x8012
/* 08B020 8008A420 AC2063C4 */  sw    $zero, %lo(gIgnorePlayerInput)($at)
/* 08B024 8008A424 2841FFE2 */  slti  $at, $v0, -0x1e
/* 08B028 8008A428 14200003 */  bnez  $at, .L8008A438
/* 08B02C 8008A42C 2841001F */   slti  $at, $v0, 0x1f
/* 08B030 8008A430 14200022 */  bnez  $at, .L8008A4BC
/* 08B034 8008A434 8FBF0014 */   lw    $ra, 0x14($sp)
.L8008A438:
/* 08B038 8008A438 0C022932 */  jal   func_8008A4C8
/* 08B03C 8008A43C 00000000 */   nop   
/* 08B040 8008A440 3C19800E */  lui   $t9, %hi(gMenuDelay) # $t9, 0x800e
/* 08B044 8008A444 8F39F47C */  lw    $t9, %lo(gMenuDelay)($t9)
/* 08B048 8008A448 3C0F800E */  lui   $t7, %hi(gActiveMagicCodes) # $t7, 0x800e
/* 08B04C 8008A44C 07210018 */  bgez  $t9, .L8008A4B0
/* 08B050 8008A450 00000000 */   nop   
/* 08B054 8008A454 8DEFFD98 */  lw    $t7, %lo(gActiveMagicCodes)($t7)
/* 08B058 8008A458 00000000 */  nop   
/* 08B05C 8008A45C 31EE0400 */  andi  $t6, $t7, 0x400
/* 08B060 8008A460 11C0000F */  beqz  $t6, .L8008A4A0
/* 08B064 8008A464 00000000 */   nop   
/* 08B068 8008A468 0C0002CA */  jal   func_80000B28
/* 08B06C 8008A46C 00000000 */   nop   
/* 08B070 8008A470 24180001 */  li    $t8, 1
/* 08B074 8008A474 3C01800E */  lui   $at, %hi(gViewingCreditsFromCheat) # $at, 0x800e
/* 08B078 8008A478 AC381B4C */  sw    $t8, %lo(gViewingCreditsFromCheat)($at)
/* 08B07C 8008A47C 0C0204F4 */  jal   menu_init
/* 08B080 8008A480 24040019 */   li    $a0, 25
/* 08B084 8008A484 3C19800E */  lui   $t9, %hi(gActiveMagicCodes) # $t9, 0x800e
/* 08B088 8008A488 8F39FD98 */  lw    $t9, %lo(gActiveMagicCodes)($t9)
/* 08B08C 8008A48C 2401FBFF */  li    $at, -1025
/* 08B090 8008A490 03217824 */  and   $t7, $t9, $at
/* 08B094 8008A494 3C01800E */  lui   $at, %hi(gActiveMagicCodes) # $at, 0x800e
/* 08B098 8008A498 10000007 */  b     .L8008A4B8
/* 08B09C 8008A49C AC2FFD98 */   sw    $t7, %lo(gActiveMagicCodes)($at)
.L8008A4A0:
/* 08B0A0 8008A4A0 0C0204F4 */  jal   menu_init
/* 08B0A4 8008A4A4 2404000C */   li    $a0, 12
/* 08B0A8 8008A4A8 10000004 */  b     .L8008A4BC
/* 08B0AC 8008A4AC 8FBF0014 */   lw    $ra, 0x14($sp)
.L8008A4B0:
/* 08B0B0 8008A4B0 0C0204F4 */  jal   menu_init
/* 08B0B4 8008A4B4 2404000B */   li    $a0, 11
.L8008A4B8:
/* 08B0B8 8008A4B8 8FBF0014 */  lw    $ra, 0x14($sp)
.L8008A4BC:
/* 08B0BC 8008A4BC 27BD0060 */  addiu $sp, $sp, 0x60
/* 08B0C0 8008A4C0 03E00008 */  jr    $ra
/* 08B0C4 8008A4C4 00001025 */   move  $v0, $zero

