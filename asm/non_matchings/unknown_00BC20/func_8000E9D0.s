glabel func_8000E9D0
/* 00F5D0 8000E9D0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 00F5D4 8000E9D4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 00F5D8 8000E9D8 848E0006 */  lh    $t6, 6($a0)
/* 00F5DC 8000E9DC 00802825 */  move  $a1, $a0
/* 00F5E0 8000E9E0 35CF8000 */  ori   $t7, $t6, 0x8000
/* 00F5E4 8000E9E4 A48F0006 */  sh    $t7, 6($a0)
/* 00F5E8 8000E9E8 8484002C */  lh    $a0, 0x2c($a0)
/* 00F5EC 8000E9EC AFA50018 */  sw    $a1, 0x18($sp)
/* 00F5F0 8000E9F0 3498C000 */  ori   $t8, $a0, 0xc000
/* 00F5F4 8000E9F4 0018CC00 */  sll   $t9, $t8, 0x10
/* 00F5F8 8000E9F8 0C00916D */  jal   func_800245B4
/* 00F5FC 8000E9FC 00192403 */   sra   $a0, $t9, 0x10
/* 00F600 8000EA00 3C028012 */  lui   $v0, %hi(objCount) # $v0, 0x8012
/* 00F604 8000EA04 2442AE5C */  addiu $v0, %lo(objCount) # addiu $v0, $v0, -0x51a4
/* 00F608 8000EA08 8C4A0000 */  lw    $t2, ($v0)
/* 00F60C 8000EA0C 3C098012 */  lui   $t1, %hi(objPtrList) # $t1, 0x8012
/* 00F610 8000EA10 8D29AE58 */  lw    $t1, %lo(objPtrList)($t1)
/* 00F614 8000EA14 8FA50018 */  lw    $a1, 0x18($sp)
/* 00F618 8000EA18 000A5880 */  sll   $t3, $t2, 2
/* 00F61C 8000EA1C 012B6021 */  addu  $t4, $t1, $t3
/* 00F620 8000EA20 AD850000 */  sw    $a1, ($t4)
/* 00F624 8000EA24 8C4D0000 */  lw    $t5, ($v0)
/* 00F628 8000EA28 00000000 */  nop   
/* 00F62C 8000EA2C 25AE0001 */  addiu $t6, $t5, 1
/* 00F630 8000EA30 AC4E0000 */  sw    $t6, ($v0)
/* 00F634 8000EA34 3C028012 */  lui   $v0, %hi(D_8011AE64) # $v0, 0x8012
/* 00F638 8000EA38 2442AE64 */  addiu $v0, %lo(D_8011AE64) # addiu $v0, $v0, -0x519c
/* 00F63C 8000EA3C 8C4F0000 */  lw    $t7, ($v0)
/* 00F640 8000EA40 8FBF0014 */  lw    $ra, 0x14($sp)
/* 00F644 8000EA44 25F80001 */  addiu $t8, $t7, 1
/* 00F648 8000EA48 AC580000 */  sw    $t8, ($v0)
/* 00F64C 8000EA4C 03E00008 */  jr    $ra
/* 00F650 8000EA50 27BD0018 */   addiu $sp, $sp, 0x18

