glabel func_800A7A60
/* 0A8660 800A7A60 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0A8664 800A7A64 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0A8668 800A7A68 8C830064 */  lw    $v1, 0x64($a0)
/* 0A866C 800A7A6C 00000000 */  nop   
/* 0A8670 800A7A70 8C6E0140 */  lw    $t6, 0x140($v1)
/* 0A8674 800A7A74 00000000 */  nop   
/* 0A8678 800A7A78 11C00038 */  beqz  $t6, .L800A7B5C
/* 0A867C 800A7A7C 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A8680 800A7A80 0C019888 */  jal   get_object_render_stack_pos
/* 0A8684 800A7A84 AFA30024 */   sw    $v1, 0x24($sp)
/* 0A8688 800A7A88 8FA30024 */  lw    $v1, 0x24($sp)
/* 0A868C 800A7A8C 3C078012 */  lui   $a3, %hi(D_80126CDC) # $a3, 0x8012
/* 0A8690 800A7A90 846F0000 */  lh    $t7, ($v1)
/* 0A8694 800A7A94 00000000 */  nop   
/* 0A8698 800A7A98 144F0030 */  bne   $v0, $t7, .L800A7B5C
/* 0A869C 800A7A9C 8FBF001C */   lw    $ra, 0x1c($sp)
/* 0A86A0 800A7AA0 8C780140 */  lw    $t8, 0x140($v1)
/* 0A86A4 800A7AA4 8CE76CDC */  lw    $a3, %lo(D_80126CDC)($a3)
/* 0A86A8 800A7AA8 C704000C */  lwc1  $f4, 0xc($t8)
/* 0A86AC 800A7AAC 84E60226 */  lh    $a2, 0x226($a3)
/* 0A86B0 800A7AB0 E4E4022C */  swc1  $f4, 0x22c($a3)
/* 0A86B4 800A7AB4 8C790140 */  lw    $t9, 0x140($v1)
/* 0A86B8 800A7AB8 3C098012 */  lui   $t1, %hi(D_80126CF4) # $t1, 0x8012
/* 0A86BC 800A7ABC C7260010 */  lwc1  $f6, 0x10($t9)
/* 0A86C0 800A7AC0 00065080 */  sll   $t2, $a2, 2
/* 0A86C4 800A7AC4 E4E60230 */  swc1  $f6, 0x230($a3)
/* 0A86C8 800A7AC8 8C680140 */  lw    $t0, 0x140($v1)
/* 0A86CC 800A7ACC 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A86D0 800A7AD0 C5080014 */  lwc1  $f8, 0x14($t0)
/* 0A86D4 800A7AD4 3C0C8012 */  lui   $t4, %hi(D_80126CD8) # $t4, 0x8012
/* 0A86D8 800A7AD8 E4E80234 */  swc1  $f8, 0x234($a3)
/* 0A86DC 800A7ADC 8D296CF4 */  lw    $t1, %lo(D_80126CF4)($t1)
/* 0A86E0 800A7AE0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A86E4 800A7AE4 012A5821 */  addu  $t3, $t1, $t2
/* 0A86E8 800A7AE8 8D620000 */  lw    $v0, ($t3)
/* 0A86EC 800A7AEC 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A86F0 800A7AF0 10400019 */  beqz  $v0, .L800A7B58
/* 0A86F4 800A7AF4 24E70220 */   addiu $a3, $a3, 0x220
/* 0A86F8 800A7AF8 8D8C6CD8 */  lw    $t4, %lo(D_80126CD8)($t4)
/* 0A86FC 800A7AFC 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A8700 800A7B00 01866821 */  addu  $t5, $t4, $a2
/* 0A8704 800A7B04 A1A00000 */  sb    $zero, ($t5)
/* 0A8708 800A7B08 AFA70028 */  sw    $a3, 0x28($sp)
/* 0A870C 800A7B0C 0C019B37 */  jal   func_80066CDC
/* 0A8710 800A7B10 AFA2002C */   sw    $v0, 0x2c($sp)
/* 0A8714 800A7B14 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A8718 800A7B18 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A871C 800A7B1C 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A8720 800A7B20 0C01A102 */  jal   func_80068408
/* 0A8724 800A7B24 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A8728 800A7B28 8FA2002C */  lw    $v0, 0x2c($sp)
/* 0A872C 800A7B2C 8FA70028 */  lw    $a3, 0x28($sp)
/* 0A8730 800A7B30 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A8734 800A7B34 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A8738 800A7B38 3C068012 */  lui   $a2, %hi(gHUDCurrTriList) # $a2, 0x8012
/* 0A873C 800A7B3C 240E0100 */  li    $t6, 256
/* 0A8740 800A7B40 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0A8744 800A7B44 24C66D04 */  addiu $a2, %lo(gHUDCurrTriList) # addiu $a2, $a2, 0x6d04
/* 0A8748 800A7B48 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A874C 800A7B4C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A8750 800A7B50 0C01A145 */  jal   render_sprite_billboard
/* 0A8754 800A7B54 AFA20010 */   sw    $v0, 0x10($sp)
.L800A7B58:
/* 0A8758 800A7B58 8FBF001C */  lw    $ra, 0x1c($sp)
.L800A7B5C:
/* 0A875C 800A7B5C 27BD0030 */  addiu $sp, $sp, 0x30
/* 0A8760 800A7B60 03E00008 */  jr    $ra
/* 0A8764 800A7B64 00000000 */   nop   

