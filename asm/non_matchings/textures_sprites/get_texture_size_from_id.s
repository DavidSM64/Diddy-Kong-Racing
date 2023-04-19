glabel get_texture_size_from_id
/* 07D17C 8007C57C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 07D180 8007C580 240E0004 */  li    $t6, 4
/* 07D184 8007C584 308F8000 */  andi  $t7, $a0, 0x8000
/* 07D188 8007C588 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07D18C 8007C58C AFAE0018 */  sw    $t6, 0x18($sp)
/* 07D190 8007C590 11E00006 */  beqz  $t7, .L8007C5AC
/* 07D194 8007C594 00001025 */   move  $v0, $zero
/* 07D198 8007C598 24180002 */  li    $t8, 2
/* 07D19C 8007C59C 30997FFF */  andi  $t9, $a0, 0x7fff
/* 07D1A0 8007C5A0 AFB80018 */  sw    $t8, 0x18($sp)
/* 07D1A4 8007C5A4 24020001 */  li    $v0, 1
/* 07D1A8 8007C5A8 03202025 */  move  $a0, $t9
.L8007C5AC:
/* 07D1AC 8007C5AC 00021880 */  sll   $v1, $v0, 2
/* 07D1B0 8007C5B0 3C088012 */  lui   $t0, %hi(gTextureAssetID) # $t0, 0x8012
/* 07D1B4 8007C5B4 01034021 */  addu  $t0, $t0, $v1
/* 07D1B8 8007C5B8 8D086338 */  lw    $t0, %lo(gTextureAssetID)($t0)
/* 07D1BC 8007C5BC 00000000 */  nop   
/* 07D1C0 8007C5C0 0088082A */  slt   $at, $a0, $t0
/* 07D1C4 8007C5C4 10200003 */  beqz  $at, .L8007C5D4
/* 07D1C8 8007C5C8 00000000 */   nop   
/* 07D1CC 8007C5CC 04810003 */  bgez  $a0, .L8007C5DC
/* 07D1D0 8007C5D0 3C098012 */   lui   $t1, %hi(gTextureAssetTable) # $t1, 0x8012
.L8007C5D4:
/* 07D1D4 8007C5D4 1000001E */  b     .L8007C650
/* 07D1D8 8007C5D8 00001025 */   move  $v0, $zero
.L8007C5DC:
/* 07D1DC 8007C5DC 01234821 */  addu  $t1, $t1, $v1
/* 07D1E0 8007C5E0 8D296320 */  lw    $t1, %lo(gTextureAssetTable)($t1)
/* 07D1E4 8007C5E4 00045080 */  sll   $t2, $a0, 2
/* 07D1E8 8007C5E8 3C058012 */  lui   $a1, %hi(gTempTextureHeader) # $a1, 0x8012
/* 07D1EC 8007C5EC 8CA5636C */  lw    $a1, %lo(gTempTextureHeader)($a1)
/* 07D1F0 8007C5F0 012A1021 */  addu  $v0, $t1, $t2
/* 07D1F4 8007C5F4 8C460000 */  lw    $a2, ($v0)
/* 07D1F8 8007C5F8 8C4B0004 */  lw    $t3, 4($v0)
/* 07D1FC 8007C5FC 90AC001D */  lbu   $t4, 0x1d($a1)
/* 07D200 8007C600 8FA40018 */  lw    $a0, 0x18($sp)
/* 07D204 8007C604 1180000A */  beqz  $t4, .L8007C630
/* 07D208 8007C608 01663823 */   subu  $a3, $t3, $a2
/* 07D20C 8007C60C 0C01DB9A */  jal   load_asset_to_address
/* 07D210 8007C610 24070028 */   li    $a3, 40
/* 07D214 8007C614 3C038012 */  lui   $v1, %hi(gTempTextureHeader) # $v1, 0x8012
/* 07D218 8007C618 8C63636C */  lw    $v1, %lo(gTempTextureHeader)($v1)
/* 07D21C 8007C61C 0C03186B */  jal   byteswap32
/* 07D220 8007C620 24640020 */   addiu $a0, $v1, 0x20
/* 07D224 8007C624 3C058012 */  lui   $a1, %hi(gTempTextureHeader) # $a1, 0x8012
/* 07D228 8007C628 8CA5636C */  lw    $a1, %lo(gTempTextureHeader)($a1)
/* 07D22C 8007C62C 00403825 */  move  $a3, $v0
.L8007C630:
/* 07D230 8007C630 94A30012 */  lhu   $v1, 0x12($a1)
/* 07D234 8007C634 00000000 */  nop   
/* 07D238 8007C638 00036A03 */  sra   $t5, $v1, 8
/* 07D23C 8007C63C 31AEFFFF */  andi  $t6, $t5, 0xffff
/* 07D240 8007C640 000E7880 */  sll   $t7, $t6, 2
/* 07D244 8007C644 01EE7823 */  subu  $t7, $t7, $t6
/* 07D248 8007C648 000F7940 */  sll   $t7, $t7, 5
/* 07D24C 8007C64C 01E71021 */  addu  $v0, $t7, $a3
.L8007C650:
/* 07D250 8007C650 8FBF0014 */  lw    $ra, 0x14($sp)
/* 07D254 8007C654 27BD0028 */  addiu $sp, $sp, 0x28
/* 07D258 8007C658 03E00008 */  jr    $ra
/* 07D25C 8007C65C 00000000 */   nop   



