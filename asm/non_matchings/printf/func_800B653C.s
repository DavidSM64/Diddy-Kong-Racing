.late_rodata
glabel jpt_800E8E58
.word L800B6658, L800B6740, L800B6614, L800B6634, L800B66CC

.text
glabel func_800B653C
/* 0B713C 800B653C 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0B7140 800B6540 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0B7144 800B6544 AFBE0040 */  sw    $fp, 0x40($sp)
/* 0B7148 800B6548 AFB7003C */  sw    $s7, 0x3c($sp)
/* 0B714C 800B654C AFB60038 */  sw    $s6, 0x38($sp)
/* 0B7150 800B6550 AFB50034 */  sw    $s5, 0x34($sp)
/* 0B7154 800B6554 AFB40030 */  sw    $s4, 0x30($sp)
/* 0B7158 800B6558 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0B715C 800B655C AFB20028 */  sw    $s2, 0x28($sp)
/* 0B7160 800B6560 AFB10024 */  sw    $s1, 0x24($sp)
/* 0B7164 800B6564 AFB00020 */  sw    $s0, 0x20($sp)
/* 0B7168 800B6568 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0B716C 800B656C 90B10000 */  lbu   $s1, ($a1)
/* 0B7170 800B6570 0080A825 */  move  $s5, $a0
/* 0B7174 800B6574 122000EB */  beqz  $s1, .L800B6924
/* 0B7178 800B6578 24B00001 */   addiu $s0, $a1, 1
/* 0B717C 800B657C 3C1E8012 */  lui   $fp, %hi(gDebugTextOn) # $fp, 0x8012
/* 0B7180 800B6580 3C178012 */  lui   $s7, %hi(D_80127CB2) # $s7, 0x8012
/* 0B7184 800B6584 3C168012 */  lui   $s6, %hi(D_80127CB0) # $s6, 0x8012
/* 0B7188 800B6588 3C148012 */  lui   $s4, %hi(gDebugTextY) # $s4, 0x8012
/* 0B718C 800B658C 3C128012 */  lui   $s2, %hi(gDebugTextX) # $s2, 0x8012
/* 0B7190 800B6590 26527CAC */  addiu $s2, %lo(gDebugTextX) # addiu $s2, $s2, 0x7cac
/* 0B7194 800B6594 26947CAE */  addiu $s4, %lo(gDebugTextY) # addiu $s4, $s4, 0x7cae
/* 0B7198 800B6598 26D67CB0 */  addiu $s6, %lo(D_80127CB0) # addiu $s6, $s6, 0x7cb0
/* 0B719C 800B659C 26F77CB2 */  addiu $s7, %lo(D_80127CB2) # addiu $s7, $s7, 0x7cb2
/* 0B71A0 800B65A0 27DE7CB8 */  addiu $fp, %lo(gDebugTextOn) # addiu $fp, $fp, 0x7cb8
/* 0B71A4 800B65A4 2A21000B */  slti  $at, $s1, 0xb
.L800B65A8:
/* 0B71A8 800B65A8 14200012 */  bnez  $at, .L800B65F4
/* 0B71AC 800B65AC 00009825 */   move  $s3, $zero
/* 0B71B0 800B65B0 2A210021 */  slti  $at, $s1, 0x21
/* 0B71B4 800B65B4 1420000A */  bnez  $at, .L800B65E0
/* 0B71B8 800B65B8 262EFF7F */   addiu $t6, $s1, -0x81
/* 0B71BC 800B65BC 2DC10005 */  sltiu $at, $t6, 5
/* 0B71C0 800B65C0 102000AE */  beqz  $at, .L800B687C
/* 0B71C4 800B65C4 000E7080 */   sll   $t6, $t6, 2
/* 0B71C8 800B65C8 3C01800F */  lui   $at, %hi(jpt_800E8E58) # $at, 0x800f
/* 0B71CC 800B65CC 002E0821 */  addu  $at, $at, $t6
/* 0B71D0 800B65D0 8C2E8E58 */  lw    $t6, %lo(jpt_800E8E58)($at)
/* 0B71D4 800B65D4 00000000 */  nop   
/* 0B71D8 800B65D8 01C00008 */  jr    $t6
/* 0B71DC 800B65DC 00000000 */   nop   
.L800B65E0:
/* 0B71E0 800B65E0 24010020 */  li    $at, 32
/* 0B71E4 800B65E4 12210077 */  beq   $s1, $at, .L800B67C4
/* 0B71E8 800B65E8 24130006 */   li    $s3, 6
/* 0B71EC 800B65EC 100000A4 */  b     .L800B6880
/* 0B71F0 800B65F0 02A02025 */   move  $a0, $s5
.L800B65F4:
/* 0B71F4 800B65F4 24010009 */  li    $at, 9
/* 0B71F8 800B65F8 12210090 */  beq   $s1, $at, .L800B683C
/* 0B71FC 800B65FC 3C038012 */   lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7200 800B6600 2401000A */  li    $at, 10
/* 0B7204 800B6604 12210076 */  beq   $s1, $at, .L800B67E0
/* 0B7208 800B6608 00000000 */   nop   
/* 0B720C 800B660C 1000009C */  b     .L800B6880
/* 0B7210 800B6610 02A02025 */   move  $a0, $s5
glabel L800B6614
/* 0B7214 800B6614 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B7218 800B6618 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B721C 800B661C 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B7220 800B6620 AC207CB4 */  sw    $zero, %lo(D_80127CB4)($at)
/* 0B7224 800B6624 96440000 */  lhu   $a0, ($s2)
/* 0B7228 800B6628 00001825 */  move  $v1, $zero
/* 0B722C 800B662C 1000009D */  b     .L800B68A4
/* 0B7230 800B6630 24A5FFF0 */   addiu $a1, $a1, -0x10
glabel L800B6634
/* 0B7234 800B6634 240F0001 */  li    $t7, 1
/* 0B7238 800B6638 3C018012 */  lui   $at, %hi(D_80127CB4) # $at, 0x8012
/* 0B723C 800B663C 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B7240 800B6640 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B7244 800B6644 AC2F7CB4 */  sw    $t7, %lo(D_80127CB4)($at)
/* 0B7248 800B6648 96440000 */  lhu   $a0, ($s2)
/* 0B724C 800B664C 24030001 */  li    $v1, 1
/* 0B7250 800B6650 10000094 */  b     .L800B68A4
/* 0B7254 800B6654 24A5FFF0 */   addiu $a1, $a1, -0x10
glabel L800B6658
/* 0B7258 800B6658 8FD80000 */  lw    $t8, ($fp)
/* 0B725C 800B665C 92040000 */  lbu   $a0, ($s0)
/* 0B7260 800B6660 92050001 */  lbu   $a1, 1($s0)
/* 0B7264 800B6664 92060002 */  lbu   $a2, 2($s0)
/* 0B7268 800B6668 92070003 */  lbu   $a3, 3($s0)
/* 0B726C 800B666C 13000010 */  beqz  $t8, .L800B66B0
/* 0B7270 800B6670 26100004 */   addiu $s0, $s0, 4
/* 0B7274 800B6674 8EA30000 */  lw    $v1, ($s5)
/* 0B7278 800B6678 30AB00FF */  andi  $t3, $a1, 0xff
/* 0B727C 800B667C 24790008 */  addiu $t9, $v1, 8
/* 0B7280 800B6680 AEB90000 */  sw    $t9, ($s5)
/* 0B7284 800B6684 000B6400 */  sll   $t4, $t3, 0x10
/* 0B7288 800B6688 00045600 */  sll   $t2, $a0, 0x18
/* 0B728C 800B668C 30CE00FF */  andi  $t6, $a2, 0xff
/* 0B7290 800B6690 000E7A00 */  sll   $t7, $t6, 8
/* 0B7294 800B6694 014C6825 */  or    $t5, $t2, $t4
/* 0B7298 800B6698 3C08FB00 */  lui   $t0, 0xfb00
/* 0B729C 800B669C 01AFC025 */  or    $t8, $t5, $t7
/* 0B72A0 800B66A0 30F900FF */  andi  $t9, $a3, 0xff
/* 0B72A4 800B66A4 AC680000 */  sw    $t0, ($v1)
/* 0B72A8 800B66A8 03194025 */  or    $t0, $t8, $t9
/* 0B72AC 800B66AC AC680004 */  sw    $t0, 4($v1)
.L800B66B0:
/* 0B72B0 800B66B0 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B72B4 800B66B4 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B72B8 800B66B8 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B72BC 800B66BC 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B72C0 800B66C0 96440000 */  lhu   $a0, ($s2)
/* 0B72C4 800B66C4 10000077 */  b     .L800B68A4
/* 0B72C8 800B66C8 24A5FFF0 */   addiu $a1, $a1, -0x10
glabel L800B66CC
/* 0B72CC 800B66CC 8FC90000 */  lw    $t1, ($fp)
/* 0B72D0 800B66D0 92040000 */  lbu   $a0, ($s0)
/* 0B72D4 800B66D4 92050001 */  lbu   $a1, 1($s0)
/* 0B72D8 800B66D8 92060002 */  lbu   $a2, 2($s0)
/* 0B72DC 800B66DC 92070003 */  lbu   $a3, 3($s0)
/* 0B72E0 800B66E0 15200010 */  bnez  $t1, .L800B6724
/* 0B72E4 800B66E4 26100004 */   addiu $s0, $s0, 4
/* 0B72E8 800B66E8 8EA30000 */  lw    $v1, ($s5)
/* 0B72EC 800B66EC 30AD00FF */  andi  $t5, $a1, 0xff
/* 0B72F0 800B66F0 246B0008 */  addiu $t3, $v1, 8
/* 0B72F4 800B66F4 AEAB0000 */  sw    $t3, ($s5)
/* 0B72F8 800B66F8 000D7C00 */  sll   $t7, $t5, 0x10
/* 0B72FC 800B66FC 00047600 */  sll   $t6, $a0, 0x18
/* 0B7300 800B6700 30D900FF */  andi  $t9, $a2, 0xff
/* 0B7304 800B6704 00194200 */  sll   $t0, $t9, 8
/* 0B7308 800B6708 01CFC025 */  or    $t8, $t6, $t7
/* 0B730C 800B670C 3C0AFA00 */  lui   $t2, 0xfa00
/* 0B7310 800B6710 03084825 */  or    $t1, $t8, $t0
/* 0B7314 800B6714 30EB00FF */  andi  $t3, $a3, 0xff
/* 0B7318 800B6718 AC6A0000 */  sw    $t2, ($v1)
/* 0B731C 800B671C 012B5025 */  or    $t2, $t1, $t3
/* 0B7320 800B6720 AC6A0004 */  sw    $t2, 4($v1)
.L800B6724:
/* 0B7324 800B6724 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B7328 800B6728 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B732C 800B672C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7330 800B6730 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7334 800B6734 96440000 */  lhu   $a0, ($s2)
/* 0B7338 800B6738 1000005A */  b     .L800B68A4
/* 0B733C 800B673C 24A5FFF0 */   addiu $a1, $a1, -0x10
glabel L800B6740
/* 0B7340 800B6740 8FCC0000 */  lw    $t4, ($fp)
/* 0B7344 800B6744 02A02025 */  move  $a0, $s5
/* 0B7348 800B6748 15800008 */  bnez  $t4, .L800B676C
/* 0B734C 800B674C 00000000 */   nop   
/* 0B7350 800B6750 968D0000 */  lhu   $t5, ($s4)
/* 0B7354 800B6754 96C50000 */  lhu   $a1, ($s6)
/* 0B7358 800B6758 96E60000 */  lhu   $a2, ($s7)
/* 0B735C 800B675C 96470000 */  lhu   $a3, ($s2)
/* 0B7360 800B6760 25AE000A */  addiu $t6, $t5, 0xa
/* 0B7364 800B6764 0C02DA57 */  jal   debug_text_background
/* 0B7368 800B6768 AFAE0010 */   sw    $t6, 0x10($sp)
.L800B676C:
/* 0B736C 800B676C 92190000 */  lbu   $t9, ($s0)
/* 0B7370 800B6770 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B7374 800B6774 A6590000 */  sh    $t9, ($s2)
/* 0B7378 800B6778 92180001 */  lbu   $t8, 1($s0)
/* 0B737C 800B677C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7380 800B6780 00184200 */  sll   $t0, $t8, 8
/* 0B7384 800B6784 03284825 */  or    $t1, $t9, $t0
/* 0B7388 800B6788 A6490000 */  sh    $t1, ($s2)
/* 0B738C 800B678C 920A0002 */  lbu   $t2, 2($s0)
/* 0B7390 800B6790 3124FFFF */  andi  $a0, $t1, 0xffff
/* 0B7394 800B6794 A68A0000 */  sh    $t2, ($s4)
/* 0B7398 800B6798 920C0003 */  lbu   $t4, 3($s0)
/* 0B739C 800B679C A6C40000 */  sh    $a0, ($s6)
/* 0B73A0 800B67A0 000C6A00 */  sll   $t5, $t4, 8
/* 0B73A4 800B67A4 014D7825 */  or    $t7, $t2, $t5
/* 0B73A8 800B67A8 A68F0000 */  sh    $t7, ($s4)
/* 0B73AC 800B67AC A6EF0000 */  sh    $t7, ($s7)
/* 0B73B0 800B67B0 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B73B4 800B67B4 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B73B8 800B67B8 26100004 */  addiu $s0, $s0, 4
/* 0B73BC 800B67BC 10000039 */  b     .L800B68A4
/* 0B73C0 800B67C0 24A5FFF0 */   addiu $a1, $a1, -0x10
.L800B67C4:
/* 0B73C4 800B67C4 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B73C8 800B67C8 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B73CC 800B67CC 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B73D0 800B67D0 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B73D4 800B67D4 96440000 */  lhu   $a0, ($s2)
/* 0B73D8 800B67D8 10000032 */  b     .L800B68A4
/* 0B73DC 800B67DC 24A5FFF0 */   addiu $a1, $a1, -0x10
.L800B67E0:
/* 0B73E0 800B67E0 8FD80000 */  lw    $t8, ($fp)
/* 0B73E4 800B67E4 02A02025 */  move  $a0, $s5
/* 0B73E8 800B67E8 17000008 */  bnez  $t8, .L800B680C
/* 0B73EC 800B67EC 00000000 */   nop   
/* 0B73F0 800B67F0 96990000 */  lhu   $t9, ($s4)
/* 0B73F4 800B67F4 96C50000 */  lhu   $a1, ($s6)
/* 0B73F8 800B67F8 96E60000 */  lhu   $a2, ($s7)
/* 0B73FC 800B67FC 96470000 */  lhu   $a3, ($s2)
/* 0B7400 800B6800 2728000A */  addiu $t0, $t9, 0xa
/* 0B7404 800B6804 0C02DA57 */  jal   debug_text_background
/* 0B7408 800B6808 AFA80010 */   sw    $t0, 0x10($sp)
.L800B680C:
/* 0B740C 800B680C 0C02DBC1 */  jal   debug_text_newline
/* 0B7410 800B6810 00000000 */   nop   
/* 0B7414 800B6814 96440000 */  lhu   $a0, ($s2)
/* 0B7418 800B6818 96890000 */  lhu   $t1, ($s4)
/* 0B741C 800B681C 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B7420 800B6820 A6C40000 */  sh    $a0, ($s6)
/* 0B7424 800B6824 A6E90000 */  sh    $t1, ($s7)
/* 0B7428 800B6828 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B742C 800B682C 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7430 800B6830 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7434 800B6834 1000001B */  b     .L800B68A4
/* 0B7438 800B6838 24A5FFF0 */   addiu $a1, $a1, -0x10
.L800B683C:
/* 0B743C 800B683C 96440000 */  lhu   $a0, ($s2)
/* 0B7440 800B6840 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B7444 800B6844 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B7448 800B6848 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B744C 800B684C 04810004 */  bgez  $a0, .L800B6860
/* 0B7450 800B6850 3082001F */   andi  $v0, $a0, 0x1f
/* 0B7454 800B6854 10400002 */  beqz  $v0, .L800B6860
/* 0B7458 800B6858 00000000 */   nop   
/* 0B745C 800B685C 2442FFE0 */  addiu $v0, $v0, -0x20
.L800B6860:
/* 0B7460 800B6860 14400003 */  bnez  $v0, .L800B6870
/* 0B7464 800B6864 24A5FFF0 */   addiu $a1, $a1, -0x10
/* 0B7468 800B6868 1000000E */  b     .L800B68A4
/* 0B746C 800B686C 24130020 */   li    $s3, 32
.L800B6870:
/* 0B7470 800B6870 240B0020 */  li    $t3, 32
/* 0B7474 800B6874 1000000B */  b     .L800B68A4
/* 0B7478 800B6878 01629823 */   subu  $s3, $t3, $v0
.L800B687C:
/* 0B747C 800B687C 02A02025 */  move  $a0, $s5
.L800B6880:
/* 0B7480 800B6880 0C02DA7F */  jal   debug_text_character
/* 0B7484 800B6884 02202825 */   move  $a1, $s1
/* 0B7488 800B6888 3C058012 */  lui   $a1, %hi(gDebugScreenWidth) # $a1, 0x8012
/* 0B748C 800B688C 94A57CD0 */  lhu   $a1, %lo(gDebugScreenWidth)($a1)
/* 0B7490 800B6890 3C038012 */  lui   $v1, %hi(D_80127CB4) # $v1, 0x8012
/* 0B7494 800B6894 8C637CB4 */  lw    $v1, %lo(D_80127CB4)($v1)
/* 0B7498 800B6898 96440000 */  lhu   $a0, ($s2)
/* 0B749C 800B689C 00409825 */  move  $s3, $v0
/* 0B74A0 800B68A0 24A5FFF0 */  addiu $a1, $a1, -0x10
.L800B68A4:
/* 0B74A4 800B68A4 10600006 */  beqz  $v1, .L800B68C0
/* 0B74A8 800B68A8 2A210020 */   slti  $at, $s1, 0x20
/* 0B74AC 800B68AC 14200004 */  bnez  $at, .L800B68C0
/* 0B74B0 800B68B0 2A210080 */   slti  $at, $s1, 0x80
/* 0B74B4 800B68B4 10200003 */  beqz  $at, .L800B68C4
/* 0B74B8 800B68B8 00936021 */   addu  $t4, $a0, $s3
/* 0B74BC 800B68BC 24130007 */  li    $s3, 7
.L800B68C0:
/* 0B74C0 800B68C0 00936021 */  addu  $t4, $a0, $s3
.L800B68C4:
/* 0B74C4 800B68C4 3187FFFF */  andi  $a3, $t4, 0xffff
/* 0B74C8 800B68C8 00A7082A */  slt   $at, $a1, $a3
/* 0B74CC 800B68CC 10200011 */  beqz  $at, .L800B6914
/* 0B74D0 800B68D0 A64C0000 */   sh    $t4, ($s2)
/* 0B74D4 800B68D4 8FCA0000 */  lw    $t2, ($fp)
/* 0B74D8 800B68D8 02A02025 */  move  $a0, $s5
/* 0B74DC 800B68DC 15400007 */  bnez  $t2, .L800B68FC
/* 0B74E0 800B68E0 00000000 */   nop   
/* 0B74E4 800B68E4 968D0000 */  lhu   $t5, ($s4)
/* 0B74E8 800B68E8 96C50000 */  lhu   $a1, ($s6)
/* 0B74EC 800B68EC 96E60000 */  lhu   $a2, ($s7)
/* 0B74F0 800B68F0 25AE000A */  addiu $t6, $t5, 0xa
/* 0B74F4 800B68F4 0C02DA57 */  jal   debug_text_background
/* 0B74F8 800B68F8 AFAE0010 */   sw    $t6, 0x10($sp)
.L800B68FC:
/* 0B74FC 800B68FC 0C02DBC1 */  jal   debug_text_newline
/* 0B7500 800B6900 00000000 */   nop   
/* 0B7504 800B6904 964F0000 */  lhu   $t7, ($s2)
/* 0B7508 800B6908 96980000 */  lhu   $t8, ($s4)
/* 0B750C 800B690C A6CF0000 */  sh    $t7, ($s6)
/* 0B7510 800B6910 A6F80000 */  sh    $t8, ($s7)
.L800B6914:
/* 0B7514 800B6914 92110000 */  lbu   $s1, ($s0)
/* 0B7518 800B6918 26100001 */  addiu $s0, $s0, 1
/* 0B751C 800B691C 1620FF22 */  bnez  $s1, .L800B65A8
/* 0B7520 800B6920 2A21000B */   slti  $at, $s1, 0xb
.L800B6924:
/* 0B7524 800B6924 8FB9004C */  lw    $t9, 0x4c($sp)
/* 0B7528 800B6928 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0B752C 800B692C 02191023 */  subu  $v0, $s0, $t9
/* 0B7530 800B6930 8FB00020 */  lw    $s0, 0x20($sp)
/* 0B7534 800B6934 8FB10024 */  lw    $s1, 0x24($sp)
/* 0B7538 800B6938 8FB20028 */  lw    $s2, 0x28($sp)
/* 0B753C 800B693C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0B7540 800B6940 8FB40030 */  lw    $s4, 0x30($sp)
/* 0B7544 800B6944 8FB50034 */  lw    $s5, 0x34($sp)
/* 0B7548 800B6948 8FB60038 */  lw    $s6, 0x38($sp)
/* 0B754C 800B694C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0B7550 800B6950 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0B7554 800B6954 03E00008 */  jr    $ra
/* 0B7558 800B6958 27BD0050 */   addiu $sp, $sp, 0x50

