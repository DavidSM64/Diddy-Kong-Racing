glabel func_8001E93C
/* 01F53C 8001E93C 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 01F540 8001E940 3C0E8012 */  lui   $t6, %hi(D_8011AE7E) # $t6, 0x8012
/* 01F544 8001E944 81CEAE7E */  lb    $t6, %lo(D_8011AE7E)($t6)
/* 01F548 8001E948 AFBF0024 */  sw    $ra, 0x24($sp)
/* 01F54C 8001E94C AFB30020 */  sw    $s3, 0x20($sp)
/* 01F550 8001E950 AFB2001C */  sw    $s2, 0x1c($sp)
/* 01F554 8001E954 AFB10018 */  sw    $s1, 0x18($sp)
/* 01F558 8001E958 11C00023 */  beqz  $t6, .L8001E9E8
/* 01F55C 8001E95C AFB00014 */   sw    $s0, 0x14($sp)
/* 01F560 8001E960 3C048012 */  lui   $a0, %hi(D_8011AE78) # $a0, 0x8012
/* 01F564 8001E964 8484AE78 */  lh    $a0, %lo(D_8011AE78)($a0)
/* 01F568 8001E968 00009825 */  move  $s3, $zero
/* 01F56C 8001E96C 1880001E */  blez  $a0, .L8001E9E8
/* 01F570 8001E970 00008825 */   move  $s1, $zero
/* 01F574 8001E974 3C0D8012 */  lui   $t5, %hi(D_8011AE74) # $t5, 0x8012
/* 01F578 8001E978 25ADAE74 */  addiu $t5, %lo(D_8011AE74) # addiu $t5, $t5, -0x518c
/* 01F57C 8001E97C 24100014 */  li    $s0, 20
.L8001E980:
/* 01F580 8001E980 8DAF0000 */  lw    $t7, ($t5)
/* 01F584 8001E984 00000000 */  nop   
/* 01F588 8001E988 01F1C021 */  addu  $t8, $t7, $s1
/* 01F58C 8001E98C 8F020000 */  lw    $v0, ($t8)
/* 01F590 8001E990 00000000 */  nop   
/* 01F594 8001E994 8C430064 */  lw    $v1, 0x64($v0)
/* 01F598 8001E998 8C48003C */  lw    $t0, 0x3c($v0)
/* 01F59C 8001E99C 1060000E */  beqz  $v1, .L8001E9D8
/* 01F5A0 8001E9A0 00000000 */   nop   
/* 01F5A4 8001E9A4 81190021 */  lb    $t9, 0x21($t0)
/* 01F5A8 8001E9A8 00000000 */  nop   
/* 01F5AC 8001E9AC 1219000A */  beq   $s0, $t9, .L8001E9D8
/* 01F5B0 8001E9B0 00000000 */   nop   
/* 01F5B4 8001E9B4 00602025 */  move  $a0, $v1
/* 01F5B8 8001E9B8 0C003FEE */  jal   free_object
/* 01F5BC 8001E9BC AFA2003C */   sw    $v0, 0x3c($sp)
/* 01F5C0 8001E9C0 8FA2003C */  lw    $v0, 0x3c($sp)
/* 01F5C4 8001E9C4 3C048012 */  lui   $a0, %hi(D_8011AE78) # $a0, 0x8012
/* 01F5C8 8001E9C8 AC400064 */  sw    $zero, 0x64($v0)
/* 01F5CC 8001E9CC 3C0D8012 */  lui   $t5, %hi(D_8011AE74) # $t5, 0x8012
/* 01F5D0 8001E9D0 8484AE78 */  lh    $a0, %lo(D_8011AE78)($a0)
/* 01F5D4 8001E9D4 25ADAE74 */  addiu $t5, %lo(D_8011AE74) # addiu $t5, $t5, -0x518c
.L8001E9D8:
/* 01F5D8 8001E9D8 26730001 */  addiu $s3, $s3, 1
/* 01F5DC 8001E9DC 0264082A */  slt   $at, $s3, $a0
/* 01F5E0 8001E9E0 1420FFE7 */  bnez  $at, .L8001E980
/* 01F5E4 8001E9E4 26310004 */   addiu $s1, $s1, 4
.L8001E9E8:
/* 01F5E8 8001E9E8 3C028012 */  lui   $v0, %hi(D_8011AD3E) # $v0, 0x8012
/* 01F5EC 8001E9EC 2442AD3E */  addiu $v0, %lo(D_8011AD3E) # addiu $v0, $v0, -0x52c2
/* 01F5F0 8001E9F0 804E0000 */  lb    $t6, ($v0)
/* 01F5F4 8001E9F4 24100014 */  li    $s0, 20
/* 01F5F8 8001E9F8 29C10015 */  slti  $at, $t6, 0x15
/* 01F5FC 8001E9FC 14200002 */  bnez  $at, .L8001EA08
/* 01F600 8001EA00 00009825 */   move  $s3, $zero
/* 01F604 8001EA04 A0400000 */  sb    $zero, ($v0)
.L8001EA08:
/* 01F608 8001EA08 0C007931 */  jal   func_8001E4C4
/* 01F60C 8001EA0C 00000000 */   nop   
/* 01F610 8001EA10 3C068012 */  lui   $a2, %hi(gObjectCount) # $a2, 0x8012
/* 01F614 8001EA14 8CC6AE5C */  lw    $a2, %lo(gObjectCount)($a2)
/* 01F618 8001EA18 3C0D8012 */  lui   $t5, %hi(D_8011AE74) # $t5, 0x8012
/* 01F61C 8001EA1C 18C00023 */  blez  $a2, .L8001EAAC
/* 01F620 8001EA20 25ADAE74 */   addiu $t5, %lo(D_8011AE74) # addiu $t5, $t5, -0x518c
/* 01F624 8001EA24 3C058012 */  lui   $a1, %hi(gObjPtrList) # $a1, 0x8012
/* 01F628 8001EA28 3C0B8012 */  lui   $t3, %hi(D_8011ADD8) # $t3, 0x8012
/* 01F62C 8001EA2C 3C098012 */  lui   $t1, %hi(gCutsceneID) # $t1, 0x8012
/* 01F630 8001EA30 8CA5AE58 */  lw    $a1, %lo(gObjPtrList)($a1)
/* 01F634 8001EA34 2529AE7A */  addiu $t1, %lo(gCutsceneID) # addiu $t1, $t1, -0x5186
/* 01F638 8001EA38 256BADD8 */  addiu $t3, %lo(D_8011ADD8) # addiu $t3, $t3, -0x5228
/* 01F63C 8001EA3C 00005025 */  move  $t2, $zero
/* 01F640 8001EA40 00063880 */  sll   $a3, $a2, 2
/* 01F644 8001EA44 24080053 */  li    $t0, 83
.L8001EA48:
/* 01F648 8001EA48 8CA20000 */  lw    $v0, ($a1)
/* 01F64C 8001EA4C 254A0004 */  addiu $t2, $t2, 4
/* 01F650 8001EA50 10400014 */  beqz  $v0, .L8001EAA4
/* 01F654 8001EA54 0147082A */   slt   $at, $t2, $a3
/* 01F658 8001EA58 844F0006 */  lh    $t7, 6($v0)
/* 01F65C 8001EA5C 00000000 */  nop   
/* 01F660 8001EA60 31F88000 */  andi  $t8, $t7, 0x8000
/* 01F664 8001EA64 1700000F */  bnez  $t8, .L8001EAA4
/* 01F668 8001EA68 00000000 */   nop   
/* 01F66C 8001EA6C 84590048 */  lh    $t9, 0x48($v0)
/* 01F670 8001EA70 00000000 */  nop   
/* 01F674 8001EA74 1519000B */  bne   $t0, $t9, .L8001EAA4
/* 01F678 8001EA78 00000000 */   nop   
/* 01F67C 8001EA7C 8C43003C */  lw    $v1, 0x3c($v0)
/* 01F680 8001EA80 852E0000 */  lh    $t6, ($t1)
/* 01F684 8001EA84 80640009 */  lb    $a0, 9($v1)
/* 01F688 8001EA88 00137880 */  sll   $t7, $s3, 2
/* 01F68C 8001EA8C 11C40003 */  beq   $t6, $a0, .L8001EA9C
/* 01F690 8001EA90 016FC021 */   addu  $t8, $t3, $t7
/* 01F694 8001EA94 16040003 */  bne   $s0, $a0, .L8001EAA4
/* 01F698 8001EA98 00000000 */   nop   
.L8001EA9C:
/* 01F69C 8001EA9C AF020000 */  sw    $v0, ($t8)
/* 01F6A0 8001EAA0 26730001 */  addiu $s3, $s3, 1
.L8001EAA4:
/* 01F6A4 8001EAA4 1420FFE8 */  bnez  $at, .L8001EA48
/* 01F6A8 8001EAA8 24A50004 */   addiu $a1, $a1, 4
.L8001EAAC:
/* 01F6AC 8001EAAC 3C018012 */  lui   $at, %hi(D_8011AE00) # $at, 0x8012
/* 01F6B0 8001EAB0 A033AE00 */  sb    $s3, %lo(D_8011AE00)($at)
/* 01F6B4 8001EAB4 24120001 */  li    $s2, 1
/* 01F6B8 8001EAB8 3C018012 */  lui   $at, %hi(D_8011AE01) # $at, 0x8012
/* 01F6BC 8001EABC A032AE01 */  sb    $s2, %lo(D_8011AE01)($at)
/* 01F6C0 8001EAC0 3C0C8012 */  lui   $t4, %hi(gObjectListStart) # $t4, 0x8012
/* 01F6C4 8001EAC4 8D8CAE60 */  lw    $t4, %lo(gObjectListStart)($t4)
/* 01F6C8 8001EAC8 3C018012 */  lui   $at, %hi(D_8011AE78) # $at, 0x8012
/* 01F6CC 8001EACC A420AE78 */  sh    $zero, %lo(D_8011AE78)($at)
/* 01F6D0 8001EAD0 0186082A */  slt   $at, $t4, $a2
/* 01F6D4 8001EAD4 1020001E */  beqz  $at, .L8001EB50
/* 01F6D8 8001EAD8 00009825 */   move  $s3, $zero
/* 01F6DC 8001EADC 3C038012 */  lui   $v1, %hi(gObjPtrList) # $v1, 0x8012
/* 01F6E0 8001EAE0 2463AE58 */  addiu $v1, %lo(gObjPtrList) # addiu $v1, $v1, -0x51a8
/* 01F6E4 8001EAE4 000C5080 */  sll   $t2, $t4, 2
/* 01F6E8 8001EAE8 24040031 */  li    $a0, 49
.L8001EAEC:
/* 01F6EC 8001EAEC 8C790000 */  lw    $t9, ($v1)
/* 01F6F0 8001EAF0 258C0001 */  addiu $t4, $t4, 1
/* 01F6F4 8001EAF4 032A7021 */  addu  $t6, $t9, $t2
/* 01F6F8 8001EAF8 8DC20000 */  lw    $v0, ($t6)
/* 01F6FC 8001EAFC 00000000 */  nop   
/* 01F700 8001EB00 10400011 */  beqz  $v0, .L8001EB48
/* 01F704 8001EB04 0186082A */   slt   $at, $t4, $a2
/* 01F708 8001EB08 844F0006 */  lh    $t7, 6($v0)
/* 01F70C 8001EB0C 00000000 */  nop   
/* 01F710 8001EB10 31F88000 */  andi  $t8, $t7, 0x8000
/* 01F714 8001EB14 1700000C */  bnez  $t8, .L8001EB48
/* 01F718 8001EB18 0186082A */   slt   $at, $t4, $a2
/* 01F71C 8001EB1C 84590048 */  lh    $t9, 0x48($v0)
/* 01F720 8001EB20 00137880 */  sll   $t7, $s3, 2
/* 01F724 8001EB24 14990008 */  bne   $a0, $t9, .L8001EB48
/* 01F728 8001EB28 0186082A */   slt   $at, $t4, $a2
/* 01F72C 8001EB2C 8DAE0000 */  lw    $t6, ($t5)
/* 01F730 8001EB30 3C068012 */  lui   $a2, %hi(gObjectCount) # $a2, 0x8012
/* 01F734 8001EB34 01CFC021 */  addu  $t8, $t6, $t7
/* 01F738 8001EB38 AF020000 */  sw    $v0, ($t8)
/* 01F73C 8001EB3C 8CC6AE5C */  lw    $a2, %lo(gObjectCount)($a2)
/* 01F740 8001EB40 26730001 */  addiu $s3, $s3, 1
/* 01F744 8001EB44 0186082A */  slt   $at, $t4, $a2
.L8001EB48:
/* 01F748 8001EB48 1420FFE8 */  bnez  $at, .L8001EAEC
/* 01F74C 8001EB4C 254A0004 */   addiu $t2, $t2, 4
.L8001EB50:
/* 01F750 8001EB50 00006025 */  move  $t4, $zero
/* 01F754 8001EB54 267FFFFF */  addiu $ra, $s3, -1
/* 01F758 8001EB58 24110002 */  li    $s1, 2
.L8001EB5C:
/* 01F75C 8001EB5C 1BE00041 */  blez  $ra, .L8001EC64
/* 01F760 8001EB60 02405825 */   move  $t3, $s2
/* 01F764 8001EB64 00005025 */  move  $t2, $zero
.L8001EB68:
/* 01F768 8001EB68 8DB90000 */  lw    $t9, ($t5)
/* 01F76C 8001EB6C 258C0001 */  addiu $t4, $t4, 1
/* 01F770 8001EB70 032A2821 */  addu  $a1, $t9, $t2
/* 01F774 8001EB74 8CA60000 */  lw    $a2, ($a1)
/* 01F778 8001EB78 8CA70004 */  lw    $a3, 4($a1)
/* 01F77C 8001EB7C 8CC9003C */  lw    $t1, 0x3c($a2)
/* 01F780 8001EB80 8CE4003C */  lw    $a0, 0x3c($a3)
/* 01F784 8001EB84 812E0021 */  lb    $t6, 0x21($t1)
/* 01F788 8001EB88 81220010 */  lb    $v0, 0x10($t1)
/* 01F78C 8001EB8C 80830010 */  lb    $v1, 0x10($a0)
/* 01F790 8001EB90 160E0004 */  bne   $s0, $t6, .L8001EBA4
/* 01F794 8001EB94 00000000 */   nop   
/* 01F798 8001EB98 2442FE70 */  addiu $v0, $v0, -0x190
/* 01F79C 8001EB9C 00027C00 */  sll   $t7, $v0, 0x10
/* 01F7A0 8001EBA0 000F1403 */  sra   $v0, $t7, 0x10
.L8001EBA4:
/* 01F7A4 8001EBA4 80990021 */  lb    $t9, 0x21($a0)
/* 01F7A8 8001EBA8 00000000 */  nop   
/* 01F7AC 8001EBAC 16190005 */  bne   $s0, $t9, .L8001EBC4
/* 01F7B0 8001EBB0 0062082A */   slt   $at, $v1, $v0
/* 01F7B4 8001EBB4 2463FE70 */  addiu $v1, $v1, -0x190
/* 01F7B8 8001EBB8 00037400 */  sll   $t6, $v1, 0x10
/* 01F7BC 8001EBBC 000E1C03 */  sra   $v1, $t6, 0x10
/* 01F7C0 8001EBC0 0062082A */  slt   $at, $v1, $v0
.L8001EBC4:
/* 01F7C4 8001EBC4 10200007 */  beqz  $at, .L8001EBE4
/* 01F7C8 8001EBC8 00000000 */   nop   
/* 01F7CC 8001EBCC ACA70000 */  sw    $a3, ($a1)
/* 01F7D0 8001EBD0 8DB80000 */  lw    $t8, ($t5)
/* 01F7D4 8001EBD4 00005825 */  move  $t3, $zero
/* 01F7D8 8001EBD8 030AC821 */  addu  $t9, $t8, $t2
/* 01F7DC 8001EBDC 1000001E */  b     .L8001EC58
/* 01F7E0 8001EBE0 AF260004 */   sw    $a2, 4($t9)
.L8001EBE4:
/* 01F7E4 8001EBE4 1443001C */  bne   $v0, $v1, .L8001EC58
/* 01F7E8 8001EBE8 00000000 */   nop   
/* 01F7EC 8001EBEC 80820011 */  lb    $v0, 0x11($a0)
/* 01F7F0 8001EBF0 81230011 */  lb    $v1, 0x11($t1)
/* 01F7F4 8001EBF4 00000000 */  nop   
/* 01F7F8 8001EBF8 0043082A */  slt   $at, $v0, $v1
/* 01F7FC 8001EBFC 10200007 */  beqz  $at, .L8001EC1C
/* 01F800 8001EC00 00000000 */   nop   
/* 01F804 8001EC04 ACA70000 */  sw    $a3, ($a1)
/* 01F808 8001EC08 8DAE0000 */  lw    $t6, ($t5)
/* 01F80C 8001EC0C 00005825 */  move  $t3, $zero
/* 01F810 8001EC10 01CA7821 */  addu  $t7, $t6, $t2
/* 01F814 8001EC14 10000010 */  b     .L8001EC58
/* 01F818 8001EC18 ADE60004 */   sw    $a2, 4($t7)
.L8001EC1C:
/* 01F81C 8001EC1C 1443000E */  bne   $v0, $v1, .L8001EC58
/* 01F820 8001EC20 00000000 */   nop   
/* 01F824 8001EC24 8CF80078 */  lw    $t8, 0x78($a3)
/* 01F828 8001EC28 00000000 */  nop   
/* 01F82C 8001EC2C 12580005 */  beq   $s2, $t8, .L8001EC44
/* 01F830 8001EC30 00000000 */   nop   
/* 01F834 8001EC34 8CD90078 */  lw    $t9, 0x78($a2)
/* 01F838 8001EC38 00000000 */  nop   
/* 01F83C 8001EC3C 16390006 */  bne   $s1, $t9, .L8001EC58
/* 01F840 8001EC40 00000000 */   nop   
.L8001EC44:
/* 01F844 8001EC44 ACA70000 */  sw    $a3, ($a1)
/* 01F848 8001EC48 8DAE0000 */  lw    $t6, ($t5)
/* 01F84C 8001EC4C 00005825 */  move  $t3, $zero
/* 01F850 8001EC50 01CA7821 */  addu  $t7, $t6, $t2
/* 01F854 8001EC54 ADE60004 */  sw    $a2, 4($t7)
.L8001EC58:
/* 01F858 8001EC58 159FFFC3 */  bne   $t4, $ra, .L8001EB68
/* 01F85C 8001EC5C 254A0004 */   addiu $t2, $t2, 4
/* 01F860 8001EC60 00006025 */  move  $t4, $zero
.L8001EC64:
/* 01F864 8001EC64 1160FFBD */  beqz  $t3, .L8001EB5C
/* 01F868 8001EC68 00000000 */   nop   
/* 01F86C 8001EC6C 1A600071 */  blez  $s3, .L8001EE34
/* 01F870 8001EC70 2404FF9B */   li    $a0, -101
/* 01F874 8001EC74 32620003 */  andi  $v0, $s3, 3
/* 01F878 8001EC78 1040001A */  beqz  $v0, .L8001ECE4
/* 01F87C 8001EC7C 00401825 */   move  $v1, $v0
/* 01F880 8001EC80 8FA20028 */  lw    $v0, 0x28($sp)
/* 01F884 8001EC84 000C5080 */  sll   $t2, $t4, 2
.L8001EC88:
/* 01F888 8001EC88 8DB80000 */  lw    $t8, ($t5)
/* 01F88C 8001EC8C 258C0001 */  addiu $t4, $t4, 1
/* 01F890 8001EC90 030AC821 */  addu  $t9, $t8, $t2
/* 01F894 8001EC94 8F2E0000 */  lw    $t6, ($t9)
/* 01F898 8001EC98 00000000 */  nop   
/* 01F89C 8001EC9C 8DC9003C */  lw    $t1, 0x3c($t6)
/* 01F8A0 8001ECA0 00000000 */  nop   
/* 01F8A4 8001ECA4 812F0010 */  lb    $t7, 0x10($t1)
/* 01F8A8 8001ECA8 01204025 */  move  $t0, $t1
/* 01F8AC 8001ECAC 108F0003 */  beq   $a0, $t7, .L8001ECBC
/* 01F8B0 8001ECB0 00000000 */   nop   
/* 01F8B4 8001ECB4 81240010 */  lb    $a0, 0x10($t1)
/* 01F8B8 8001ECB8 00001025 */  move  $v0, $zero
.L8001ECBC:
/* 01F8BC 8001ECBC A1020011 */  sb    $v0, 0x11($t0)
/* 01F8C0 8001ECC0 8DB80000 */  lw    $t8, ($t5)
/* 01F8C4 8001ECC4 24420001 */  addiu $v0, $v0, 1
/* 01F8C8 8001ECC8 030AC821 */  addu  $t9, $t8, $t2
/* 01F8CC 8001ECCC 8F2E0000 */  lw    $t6, ($t9)
/* 01F8D0 8001ECD0 254A0004 */  addiu $t2, $t2, 4
/* 01F8D4 8001ECD4 146CFFEC */  bne   $v1, $t4, .L8001EC88
/* 01F8D8 8001ECD8 ADC00078 */   sw    $zero, 0x78($t6)
/* 01F8DC 8001ECDC 11930055 */  beq   $t4, $s3, .L8001EE34
/* 01F8E0 8001ECE0 AFA20028 */   sw    $v0, 0x28($sp)
.L8001ECE4:
/* 01F8E4 8001ECE4 8FA20028 */  lw    $v0, 0x28($sp)
/* 01F8E8 8001ECE8 000C5080 */  sll   $t2, $t4, 2
/* 01F8EC 8001ECEC 00132880 */  sll   $a1, $s3, 2
.L8001ECF0:
/* 01F8F0 8001ECF0 8DAF0000 */  lw    $t7, ($t5)
/* 01F8F4 8001ECF4 00000000 */  nop   
/* 01F8F8 8001ECF8 01EAC021 */  addu  $t8, $t7, $t2
/* 01F8FC 8001ECFC 8F190000 */  lw    $t9, ($t8)
/* 01F900 8001ED00 00000000 */  nop   
/* 01F904 8001ED04 8F29003C */  lw    $t1, 0x3c($t9)
/* 01F908 8001ED08 00000000 */  nop   
/* 01F90C 8001ED0C 812E0010 */  lb    $t6, 0x10($t1)
/* 01F910 8001ED10 01204025 */  move  $t0, $t1
/* 01F914 8001ED14 108E0003 */  beq   $a0, $t6, .L8001ED24
/* 01F918 8001ED18 00000000 */   nop   
/* 01F91C 8001ED1C 81240010 */  lb    $a0, 0x10($t1)
/* 01F920 8001ED20 00001025 */  move  $v0, $zero
.L8001ED24:
/* 01F924 8001ED24 A1020011 */  sb    $v0, 0x11($t0)
/* 01F928 8001ED28 8DAF0000 */  lw    $t7, ($t5)
/* 01F92C 8001ED2C 24420001 */  addiu $v0, $v0, 1
/* 01F930 8001ED30 01EAC021 */  addu  $t8, $t7, $t2
/* 01F934 8001ED34 8F190000 */  lw    $t9, ($t8)
/* 01F938 8001ED38 00000000 */  nop   
/* 01F93C 8001ED3C AF200078 */  sw    $zero, 0x78($t9)
/* 01F940 8001ED40 8DAE0000 */  lw    $t6, ($t5)
/* 01F944 8001ED44 00000000 */  nop   
/* 01F948 8001ED48 01CA7821 */  addu  $t7, $t6, $t2
/* 01F94C 8001ED4C 8DF80004 */  lw    $t8, 4($t7)
/* 01F950 8001ED50 00000000 */  nop   
/* 01F954 8001ED54 8F08003C */  lw    $t0, 0x3c($t8)
/* 01F958 8001ED58 00000000 */  nop   
/* 01F95C 8001ED5C 81030010 */  lb    $v1, 0x10($t0)
/* 01F960 8001ED60 00000000 */  nop   
/* 01F964 8001ED64 10830003 */  beq   $a0, $v1, .L8001ED74
/* 01F968 8001ED68 00000000 */   nop   
/* 01F96C 8001ED6C 00602025 */  move  $a0, $v1
/* 01F970 8001ED70 00001025 */  move  $v0, $zero
.L8001ED74:
/* 01F974 8001ED74 A1020011 */  sb    $v0, 0x11($t0)
/* 01F978 8001ED78 8DB90000 */  lw    $t9, ($t5)
/* 01F97C 8001ED7C 24420001 */  addiu $v0, $v0, 1
/* 01F980 8001ED80 032A7021 */  addu  $t6, $t9, $t2
/* 01F984 8001ED84 8DCF0004 */  lw    $t7, 4($t6)
/* 01F988 8001ED88 00000000 */  nop   
/* 01F98C 8001ED8C ADE00078 */  sw    $zero, 0x78($t7)
/* 01F990 8001ED90 8DB80000 */  lw    $t8, ($t5)
/* 01F994 8001ED94 00000000 */  nop   
/* 01F998 8001ED98 030AC821 */  addu  $t9, $t8, $t2
/* 01F99C 8001ED9C 8F2E0008 */  lw    $t6, 8($t9)
/* 01F9A0 8001EDA0 00000000 */  nop   
/* 01F9A4 8001EDA4 8DC8003C */  lw    $t0, 0x3c($t6)
/* 01F9A8 8001EDA8 00000000 */  nop   
/* 01F9AC 8001EDAC 81030010 */  lb    $v1, 0x10($t0)
/* 01F9B0 8001EDB0 00000000 */  nop   
/* 01F9B4 8001EDB4 10830003 */  beq   $a0, $v1, .L8001EDC4
/* 01F9B8 8001EDB8 00000000 */   nop   
/* 01F9BC 8001EDBC 00602025 */  move  $a0, $v1
/* 01F9C0 8001EDC0 00001025 */  move  $v0, $zero
.L8001EDC4:
/* 01F9C4 8001EDC4 A1020011 */  sb    $v0, 0x11($t0)
/* 01F9C8 8001EDC8 8DAF0000 */  lw    $t7, ($t5)
/* 01F9CC 8001EDCC 24420001 */  addiu $v0, $v0, 1
/* 01F9D0 8001EDD0 01EAC021 */  addu  $t8, $t7, $t2
/* 01F9D4 8001EDD4 8F190008 */  lw    $t9, 8($t8)
/* 01F9D8 8001EDD8 00000000 */  nop   
/* 01F9DC 8001EDDC AF200078 */  sw    $zero, 0x78($t9)
/* 01F9E0 8001EDE0 8DAE0000 */  lw    $t6, ($t5)
/* 01F9E4 8001EDE4 00000000 */  nop   
/* 01F9E8 8001EDE8 01CA7821 */  addu  $t7, $t6, $t2
/* 01F9EC 8001EDEC 8DF8000C */  lw    $t8, 0xc($t7)
/* 01F9F0 8001EDF0 00000000 */  nop   
/* 01F9F4 8001EDF4 8F08003C */  lw    $t0, 0x3c($t8)
/* 01F9F8 8001EDF8 00000000 */  nop   
/* 01F9FC 8001EDFC 81030010 */  lb    $v1, 0x10($t0)
/* 01FA00 8001EE00 00000000 */  nop   
/* 01FA04 8001EE04 10830003 */  beq   $a0, $v1, .L8001EE14
/* 01FA08 8001EE08 00000000 */   nop   
/* 01FA0C 8001EE0C 00602025 */  move  $a0, $v1
/* 01FA10 8001EE10 00001025 */  move  $v0, $zero
.L8001EE14:
/* 01FA14 8001EE14 A1020011 */  sb    $v0, 0x11($t0)
/* 01FA18 8001EE18 8DB90000 */  lw    $t9, ($t5)
/* 01FA1C 8001EE1C 24420001 */  addiu $v0, $v0, 1
/* 01FA20 8001EE20 032A7021 */  addu  $t6, $t9, $t2
/* 01FA24 8001EE24 8DCF000C */  lw    $t7, 0xc($t6)
/* 01FA28 8001EE28 254A0010 */  addiu $t2, $t2, 0x10
/* 01FA2C 8001EE2C 1545FFB0 */  bne   $t2, $a1, .L8001ECF0
/* 01FA30 8001EE30 ADE00078 */   sw    $zero, 0x78($t7)
.L8001EE34:
/* 01FA34 8001EE34 3C188012 */  lui   $t8, %hi(D_8011AE7E) # $t8, 0x8012
/* 01FA38 8001EE38 8318AE7E */  lb    $t8, %lo(D_8011AE7E)($t8)
/* 01FA3C 8001EE3C 3C018012 */  lui   $at, %hi(D_8011AE78) # $at, 0x8012
/* 01FA40 8001EE40 13000003 */  beqz  $t8, .L8001EE50
/* 01FA44 8001EE44 A433AE78 */   sh    $s3, %lo(D_8011AE78)($at)
/* 01FA48 8001EE48 0C007B9D */  jal   func_8001EE74
/* 01FA4C 8001EE4C 00000000 */   nop   
.L8001EE50:
/* 01FA50 8001EE50 8FBF0024 */  lw    $ra, 0x24($sp)
/* 01FA54 8001EE54 3C018012 */  lui   $at, %hi(D_8011AE7E) # $at, 0x8012
/* 01FA58 8001EE58 8FB00014 */  lw    $s0, 0x14($sp)
/* 01FA5C 8001EE5C 8FB10018 */  lw    $s1, 0x18($sp)
/* 01FA60 8001EE60 8FB2001C */  lw    $s2, 0x1c($sp)
/* 01FA64 8001EE64 8FB30020 */  lw    $s3, 0x20($sp)
/* 01FA68 8001EE68 A020AE7E */  sb    $zero, %lo(D_8011AE7E)($at)
/* 01FA6C 8001EE6C 03E00008 */  jr    $ra
/* 01FA70 8001EE70 27BD0050 */   addiu $sp, $sp, 0x50

