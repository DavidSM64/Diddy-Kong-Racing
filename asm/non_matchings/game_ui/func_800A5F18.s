.rdata
glabel D_800E8688
.asciz "RACE"
.ascii "\0\0\0" # padding
glabel D_800E8690
.asciz "LAP"
glabel D_800E8694
.asciz "DID NOT FINISH"
.ascii "\0" # padding

.text
glabel func_800A5F18
/* 0A6B18 800A5F18 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0A6B1C 800A5F1C 3C078012 */  lui   $a3, %hi(gCurrentHud) # $a3, 0x8012
/* 0A6B20 800A5F20 8CE76CDC */  lw    $a3, %lo(gCurrentHud)($a3)
/* 0A6B24 800A5F24 AFA40028 */  sw    $a0, 0x28($sp)
/* 0A6B28 800A5F28 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0A6B2C 800A5F2C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6B30 800A5F30 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A6B34 800A5F34 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A6B38 800A5F38 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A6B3C 800A5F3C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A6B40 800A5F40 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6B44 800A5F44 0C02A980 */  jal   func_800AA600
/* 0A6B48 800A5F48 24E705E0 */   addiu $a3, $a3, 0x5e0
/* 0A6B4C 800A5F4C 3C078012 */  lui   $a3, %hi(gCurrentHud) # $a3, 0x8012
/* 0A6B50 800A5F50 8CE76CDC */  lw    $a3, %lo(gCurrentHud)($a3)
/* 0A6B54 800A5F54 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6B58 800A5F58 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A6B5C 800A5F5C 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A6B60 800A5F60 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A6B64 800A5F64 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A6B68 800A5F68 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6B6C 800A5F6C 0C02A980 */  jal   func_800AA600
/* 0A6B70 800A5F70 24E70600 */   addiu $a3, $a3, 0x600
/* 0A6B74 800A5F74 0C01AF66 */  jal   get_current_level_race_type
/* 0A6B78 800A5F78 00000000 */   nop   
/* 0A6B7C 800A5F7C 304E0040 */  andi  $t6, $v0, 0x40
/* 0A6B80 800A5F80 15C000B1 */  bnez  $t6, .L800A6248
/* 0A6B84 800A5F84 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A6B88 800A5F88 0C027B20 */  jal   is_in_two_player_adventure
/* 0A6B8C 800A5F8C 00000000 */   nop   
/* 0A6B90 800A5F90 144000AD */  bnez  $v0, .L800A6248
/* 0A6B94 800A5F94 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A6B98 800A5F98 0C006E9D */  jal   get_racer_objects
/* 0A6B9C 800A5F9C 27A40024 */   addiu $a0, $sp, 0x24
/* 0A6BA0 800A5FA0 3C0F8012 */  lui   $t7, %hi(gNumActivePlayers) # $t7, 0x8012
/* 0A6BA4 800A5FA4 91EF6D37 */  lbu   $t7, %lo(gNumActivePlayers)($t7)
/* 0A6BA8 800A5FA8 00000000 */  nop   
/* 0A6BAC 800A5FAC 29E10002 */  slti  $at, $t7, 2
/* 0A6BB0 800A5FB0 142000A5 */  bnez  $at, .L800A6248
/* 0A6BB4 800A5FB4 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A6BB8 800A5FB8 0C027B20 */  jal   is_in_two_player_adventure
/* 0A6BBC 800A5FBC 00000000 */   nop   
/* 0A6BC0 800A5FC0 10400005 */  beqz  $v0, .L800A5FD8
/* 0A6BC4 800A5FC4 00000000 */   nop   
/* 0A6BC8 800A5FC8 0C01BAAC */  jal   is_postrace_viewport_active
/* 0A6BCC 800A5FCC 00000000 */   nop   
/* 0A6BD0 800A5FD0 1440009D */  bnez  $v0, .L800A6248
/* 0A6BD4 800A5FD4 8FBF001C */   lw    $ra, 0x1c($sp)
.L800A5FD8:
/* 0A6BD8 800A5FD8 0C0310BB */  jal   set_text_font
/* 0A6BDC 800A5FDC 00002025 */   move  $a0, $zero
/* 0A6BE0 800A5FE0 8FB90028 */  lw    $t9, 0x28($sp)
/* 0A6BE4 800A5FE4 8FB80024 */  lw    $t8, 0x24($sp)
/* 0A6BE8 800A5FE8 872801AC */  lh    $t0, 0x1ac($t9)
/* 0A6BEC 800A5FEC 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A6BF0 800A5FF0 13080078 */  beq   $t8, $t0, .L800A61D4
/* 0A6BF4 800A5FF4 3C01420C */   li    $at, 0x420C0000 # 35.000000
/* 0A6BF8 800A5FF8 240900FF */  li    $t1, 255
/* 0A6BFC 800A5FFC AFA90010 */  sw    $t1, 0x10($sp)
/* 0A6C00 800A6000 240400FF */  li    $a0, 255
/* 0A6C04 800A6004 240500FF */  li    $a1, 255
/* 0A6C08 800A6008 240600FF */  li    $a2, 255
/* 0A6C0C 800A600C 0C0310E1 */  jal   set_text_colour
/* 0A6C10 800A6010 00003825 */   move  $a3, $zero
/* 0A6C14 800A6014 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A6C18 800A6018 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A6C1C 800A601C 3C014220 */  li    $at, 0x42200000 # 40.000000
/* 0A6C20 800A6020 44813000 */  mtc1  $at, $f6
/* 0A6C24 800A6024 C444016C */  lwc1  $f4, 0x16c($v0)
/* 0A6C28 800A6028 C4500170 */  lwc1  $f16, 0x170($v0)
/* 0A6C2C 800A602C 46062201 */  sub.s $f8, $f4, $f6
/* 0A6C30 800A6030 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6C34 800A6034 444AF800 */  cfc1  $t2, $31
/* 0A6C38 800A6038 3C07800F */  lui   $a3, %hi(D_800E8688) # $a3, 0x800f
/* 0A6C3C 800A603C 35410003 */  ori   $at, $t2, 3
/* 0A6C40 800A6040 38210002 */  xori  $at, $at, 2
/* 0A6C44 800A6044 44C1F800 */  ctc1  $at, $31
/* 0A6C48 800A6048 24E78688 */  addiu $a3, %lo(D_800E8688) # addiu $a3, $a3, -0x7978
/* 0A6C4C 800A604C 460042A4 */  cvt.w.s $f10, $f8
/* 0A6C50 800A6050 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6C54 800A6054 44CAF800 */  ctc1  $t2, $31
/* 0A6C58 800A6058 44055000 */  mfc1  $a1, $f10
/* 0A6C5C 800A605C AFA00010 */  sw    $zero, 0x10($sp)
/* 0A6C60 800A6060 444BF800 */  cfc1  $t3, $31
/* 0A6C64 800A6064 00000000 */  nop   
/* 0A6C68 800A6068 35610003 */  ori   $at, $t3, 3
/* 0A6C6C 800A606C 38210002 */  xori  $at, $at, 2
/* 0A6C70 800A6070 44C1F800 */  ctc1  $at, $31
/* 0A6C74 800A6074 00000000 */  nop   
/* 0A6C78 800A6078 460084A4 */  cvt.w.s $f18, $f16
/* 0A6C7C 800A607C 44069000 */  mfc1  $a2, $f18
/* 0A6C80 800A6080 44CBF800 */  ctc1  $t3, $31
/* 0A6C84 800A6084 0C031110 */  jal   draw_text
/* 0A6C88 800A6088 00000000 */   nop   
/* 0A6C8C 800A608C 444CF800 */  cfc1  $t4, $31
/* 0A6C90 800A6090 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A6C94 800A6094 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A6C98 800A6098 35810003 */  ori   $at, $t4, 3
/* 0A6C9C 800A609C 38210002 */  xori  $at, $at, 2
/* 0A6CA0 800A60A0 44C1F800 */  ctc1  $at, $31
/* 0A6CA4 800A60A4 C444016C */  lwc1  $f4, 0x16c($v0)
/* 0A6CA8 800A60A8 C4480170 */  lwc1  $f8, 0x170($v0)
/* 0A6CAC 800A60AC 460021A4 */  cvt.w.s $f6, $f4
/* 0A6CB0 800A60B0 804E017C */  lb    $t6, 0x17c($v0)
/* 0A6CB4 800A60B4 44CCF800 */  ctc1  $t4, $31
/* 0A6CB8 800A60B8 8046017A */  lb    $a2, 0x17a($v0)
/* 0A6CBC 800A60BC 8047017B */  lb    $a3, 0x17b($v0)
/* 0A6CC0 800A60C0 444DF800 */  cfc1  $t5, $31
/* 0A6CC4 800A60C4 44043000 */  mfc1  $a0, $f6
/* 0A6CC8 800A60C8 35A10003 */  ori   $at, $t5, 3
/* 0A6CCC 800A60CC 38210002 */  xori  $at, $at, 2
/* 0A6CD0 800A60D0 44C1F800 */  ctc1  $at, $31
/* 0A6CD4 800A60D4 240F0001 */  li    $t7, 1
/* 0A6CD8 800A60D8 460042A4 */  cvt.w.s $f10, $f8
/* 0A6CDC 800A60DC AFAF0014 */  sw    $t7, 0x14($sp)
/* 0A6CE0 800A60E0 44055000 */  mfc1  $a1, $f10
/* 0A6CE4 800A60E4 44CDF800 */  ctc1  $t5, $31
/* 0A6CE8 800A60E8 0C029FEF */  jal   func_800A7FBC
/* 0A6CEC 800A60EC AFAE0010 */   sw    $t6, 0x10($sp)
/* 0A6CF0 800A60F0 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A6CF4 800A60F4 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A6CF8 800A60F8 3C014220 */  li    $at, 0x42200000 # 40.000000
/* 0A6CFC 800A60FC 44819000 */  mtc1  $at, $f18
/* 0A6D00 800A6100 C45002EC */  lwc1  $f16, 0x2ec($v0)
/* 0A6D04 800A6104 C44802F0 */  lwc1  $f8, 0x2f0($v0)
/* 0A6D08 800A6108 46128101 */  sub.s $f4, $f16, $f18
/* 0A6D0C 800A610C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6D10 800A6110 4459F800 */  cfc1  $t9, $31
/* 0A6D14 800A6114 3C07800F */  lui   $a3, %hi(D_800E8690) # $a3, 0x800f
/* 0A6D18 800A6118 37210003 */  ori   $at, $t9, 3
/* 0A6D1C 800A611C 38210002 */  xori  $at, $at, 2
/* 0A6D20 800A6120 44C1F800 */  ctc1  $at, $31
/* 0A6D24 800A6124 24E78690 */  addiu $a3, %lo(D_800E8690) # addiu $a3, $a3, -0x7970
/* 0A6D28 800A6128 460021A4 */  cvt.w.s $f6, $f4
/* 0A6D2C 800A612C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6D30 800A6130 44D9F800 */  ctc1  $t9, $31
/* 0A6D34 800A6134 44053000 */  mfc1  $a1, $f6
/* 0A6D38 800A6138 AFA00010 */  sw    $zero, 0x10($sp)
/* 0A6D3C 800A613C 4458F800 */  cfc1  $t8, $31
/* 0A6D40 800A6140 00000000 */  nop   
/* 0A6D44 800A6144 37010003 */  ori   $at, $t8, 3
/* 0A6D48 800A6148 38210002 */  xori  $at, $at, 2
/* 0A6D4C 800A614C 44C1F800 */  ctc1  $at, $31
/* 0A6D50 800A6150 00000000 */  nop   
/* 0A6D54 800A6154 460042A4 */  cvt.w.s $f10, $f8
/* 0A6D58 800A6158 44065000 */  mfc1  $a2, $f10
/* 0A6D5C 800A615C 44D8F800 */  ctc1  $t8, $31
/* 0A6D60 800A6160 0C031110 */  jal   draw_text
/* 0A6D64 800A6164 00000000 */   nop   
/* 0A6D68 800A6168 4448F800 */  cfc1  $t0, $31
/* 0A6D6C 800A616C 3C028012 */  lui   $v0, %hi(gCurrentHud) # $v0, 0x8012
/* 0A6D70 800A6170 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A6D74 800A6174 35010003 */  ori   $at, $t0, 3
/* 0A6D78 800A6178 38210002 */  xori  $at, $at, 2
/* 0A6D7C 800A617C 44C1F800 */  ctc1  $at, $31
/* 0A6D80 800A6180 C45002EC */  lwc1  $f16, 0x2ec($v0)
/* 0A6D84 800A6184 C44402F0 */  lwc1  $f4, 0x2f0($v0)
/* 0A6D88 800A6188 460084A4 */  cvt.w.s $f18, $f16
/* 0A6D8C 800A618C 804A02FC */  lb    $t2, 0x2fc($v0)
/* 0A6D90 800A6190 44C8F800 */  ctc1  $t0, $31
/* 0A6D94 800A6194 804602FA */  lb    $a2, 0x2fa($v0)
/* 0A6D98 800A6198 804702FB */  lb    $a3, 0x2fb($v0)
/* 0A6D9C 800A619C 4449F800 */  cfc1  $t1, $31
/* 0A6DA0 800A61A0 44049000 */  mfc1  $a0, $f18
/* 0A6DA4 800A61A4 35210003 */  ori   $at, $t1, 3
/* 0A6DA8 800A61A8 38210002 */  xori  $at, $at, 2
/* 0A6DAC 800A61AC 44C1F800 */  ctc1  $at, $31
/* 0A6DB0 800A61B0 240B0001 */  li    $t3, 1
/* 0A6DB4 800A61B4 460021A4 */  cvt.w.s $f6, $f4
/* 0A6DB8 800A61B8 AFAB0014 */  sw    $t3, 0x14($sp)
/* 0A6DBC 800A61BC 44053000 */  mfc1  $a1, $f6
/* 0A6DC0 800A61C0 44C9F800 */  ctc1  $t1, $31
/* 0A6DC4 800A61C4 0C029FEF */  jal   func_800A7FBC
/* 0A6DC8 800A61C8 AFAA0010 */   sw    $t2, 0x10($sp)
/* 0A6DCC 800A61CC 1000001E */  b     .L800A6248
/* 0A6DD0 800A61D0 8FBF001C */   lw    $ra, 0x1c($sp)
.L800A61D4:
/* 0A6DD4 800A61D4 8C426CDC */  lw    $v0, %lo(gCurrentHud)($v0)
/* 0A6DD8 800A61D8 44815000 */  mtc1  $at, $f10
/* 0A6DDC 800A61DC C448016C */  lwc1  $f8, 0x16c($v0)
/* 0A6DE0 800A61E0 C4440170 */  lwc1  $f4, 0x170($v0)
/* 0A6DE4 800A61E4 460A4401 */  sub.s $f16, $f8, $f10
/* 0A6DE8 800A61E8 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A6DEC 800A61EC 444CF800 */  cfc1  $t4, $31
/* 0A6DF0 800A61F0 3C07800F */  lui   $a3, %hi(D_800E8694) # $a3, 0x800f
/* 0A6DF4 800A61F4 35810003 */  ori   $at, $t4, 3
/* 0A6DF8 800A61F8 38210002 */  xori  $at, $at, 2
/* 0A6DFC 800A61FC 44C1F800 */  ctc1  $at, $31
/* 0A6E00 800A6200 24E78694 */  addiu $a3, %lo(D_800E8694) # addiu $a3, $a3, -0x796c
/* 0A6E04 800A6204 460084A4 */  cvt.w.s $f18, $f16
/* 0A6E08 800A6208 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A6E0C 800A620C 44CCF800 */  ctc1  $t4, $31
/* 0A6E10 800A6210 44059000 */  mfc1  $a1, $f18
/* 0A6E14 800A6214 AFA00010 */  sw    $zero, 0x10($sp)
/* 0A6E18 800A6218 444DF800 */  cfc1  $t5, $31
/* 0A6E1C 800A621C 00000000 */  nop   
/* 0A6E20 800A6220 35A10003 */  ori   $at, $t5, 3
/* 0A6E24 800A6224 38210002 */  xori  $at, $at, 2
/* 0A6E28 800A6228 44C1F800 */  ctc1  $at, $31
/* 0A6E2C 800A622C 00000000 */  nop   
/* 0A6E30 800A6230 460021A4 */  cvt.w.s $f6, $f4
/* 0A6E34 800A6234 44063000 */  mfc1  $a2, $f6
/* 0A6E38 800A6238 44CDF800 */  ctc1  $t5, $31
/* 0A6E3C 800A623C 0C031110 */  jal   draw_text
/* 0A6E40 800A6240 00000000 */   nop   
/* 0A6E44 800A6244 8FBF001C */  lw    $ra, 0x1c($sp)
.L800A6248:
/* 0A6E48 800A6248 27BD0028 */  addiu $sp, $sp, 0x28
/* 0A6E4C 800A624C 03E00008 */  jr    $ra
/* 0A6E50 800A6250 00000000 */   nop   

