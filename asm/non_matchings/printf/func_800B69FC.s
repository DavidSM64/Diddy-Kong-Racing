glabel func_800B69FC
/* 0B75FC 800B69FC 28A10040 */  slti  $at, $a1, 0x40
/* 0B7600 800B6A00 10200043 */  beqz  $at, .L800B6B10
/* 0B7604 800B6A04 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7608 800B6A08 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B760C 800B6A0C 8C6E0000 */  lw    $t6, ($v1)
/* 0B7610 800B6A10 3C0F8012 */  lui   $t7, %hi(D_80127CB8) # $t7, 0x8012
/* 0B7614 800B6A14 11C0003C */  beqz  $t6, .L800B6B08
/* 0B7618 800B6A18 00000000 */   nop   
/* 0B761C 800B6A1C 8DEF7CB8 */  lw    $t7, %lo(D_80127CB8)($t7)
/* 0B7620 800B6A20 3C19FD70 */  lui   $t9, 0xfd70
/* 0B7624 800B6A24 11E00037 */  beqz  $t7, .L800B6B04
/* 0B7628 800B6A28 3C0C8012 */   lui   $t4, %hi(gTexture0) # $t4, 0x8012
/* 0B762C 800B6A2C 8C820000 */  lw    $v0, ($a0)
/* 0B7630 800B6A30 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7634 800B6A34 24580008 */  addiu $t8, $v0, 8
/* 0B7638 800B6A38 AC980000 */  sw    $t8, ($a0)
/* 0B763C 800B6A3C AC590000 */  sw    $t9, ($v0)
/* 0B7640 800B6A40 8D8C7CA0 */  lw    $t4, %lo(gTexture0)($t4)
/* 0B7644 800B6A44 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B7648 800B6A48 01816821 */  addu  $t5, $t4, $at
/* 0B764C 800B6A4C AC4D0004 */  sw    $t5, 4($v0)
/* 0B7650 800B6A50 8C820000 */  lw    $v0, ($a0)
/* 0B7654 800B6A54 3C180708 */  lui   $t8, (0x07080200 >> 16) # lui $t8, 0x708
/* 0B7658 800B6A58 244E0008 */  addiu $t6, $v0, 8
/* 0B765C 800B6A5C AC8E0000 */  sw    $t6, ($a0)
/* 0B7660 800B6A60 37180200 */  ori   $t8, (0x07080200 & 0xFFFF) # ori $t8, $t8, 0x200
/* 0B7664 800B6A64 3C0FF570 */  lui   $t7, 0xf570
/* 0B7668 800B6A68 AC4F0000 */  sw    $t7, ($v0)
/* 0B766C 800B6A6C AC580004 */  sw    $t8, 4($v0)
/* 0B7670 800B6A70 8C820000 */  lw    $v0, ($a0)
/* 0B7674 800B6A74 3C0CE600 */  lui   $t4, 0xe600
/* 0B7678 800B6A78 24590008 */  addiu $t9, $v0, 8
/* 0B767C 800B6A7C AC990000 */  sw    $t9, ($a0)
/* 0B7680 800B6A80 AC400004 */  sw    $zero, 4($v0)
/* 0B7684 800B6A84 AC4C0000 */  sw    $t4, ($v0)
/* 0B7688 800B6A88 8C820000 */  lw    $v0, ($a0)
/* 0B768C 800B6A8C 3C0F0741 */  lui   $t7, (0x0741F056 >> 16) # lui $t7, 0x741
/* 0B7690 800B6A90 244D0008 */  addiu $t5, $v0, 8
/* 0B7694 800B6A94 AC8D0000 */  sw    $t5, ($a0)
/* 0B7698 800B6A98 35EFF056 */  ori   $t7, (0x0741F056 & 0xFFFF) # ori $t7, $t7, 0xf056
/* 0B769C 800B6A9C 3C0EF300 */  lui   $t6, 0xf300
/* 0B76A0 800B6AA0 AC4E0000 */  sw    $t6, ($v0)
/* 0B76A4 800B6AA4 AC4F0004 */  sw    $t7, 4($v0)
/* 0B76A8 800B6AA8 8C820000 */  lw    $v0, ($a0)
/* 0B76AC 800B6AAC 3C19E700 */  lui   $t9, 0xe700
/* 0B76B0 800B6AB0 24580008 */  addiu $t8, $v0, 8
/* 0B76B4 800B6AB4 AC980000 */  sw    $t8, ($a0)
/* 0B76B8 800B6AB8 AC400004 */  sw    $zero, 4($v0)
/* 0B76BC 800B6ABC AC590000 */  sw    $t9, ($v0)
/* 0B76C0 800B6AC0 8C820000 */  lw    $v0, ($a0)
/* 0B76C4 800B6AC4 3C0E0008 */  lui   $t6, (0x00080200 >> 16) # lui $t6, 8
/* 0B76C8 800B6AC8 244C0008 */  addiu $t4, $v0, 8
/* 0B76CC 800B6ACC AC8C0000 */  sw    $t4, ($a0)
/* 0B76D0 800B6AD0 3C0DF568 */  lui   $t5, (0xF5683000 >> 16) # lui $t5, 0xf568
/* 0B76D4 800B6AD4 35AD3000 */  ori   $t5, (0xF5683000 & 0xFFFF) # ori $t5, $t5, 0x3000
/* 0B76D8 800B6AD8 35CE0200 */  ori   $t6, (0x00080200 & 0xFFFF) # ori $t6, $t6, 0x200
/* 0B76DC 800B6ADC AC4E0004 */  sw    $t6, 4($v0)
/* 0B76E0 800B6AE0 AC4D0000 */  sw    $t5, ($v0)
/* 0B76E4 800B6AE4 8C820000 */  lw    $v0, ($a0)
/* 0B76E8 800B6AE8 3C19002F */  lui   $t9, (0x002FC028 >> 16) # lui $t9, 0x2f
/* 0B76EC 800B6AEC 244F0008 */  addiu $t7, $v0, 8
/* 0B76F0 800B6AF0 AC8F0000 */  sw    $t7, ($a0)
/* 0B76F4 800B6AF4 3739C028 */  ori   $t9, (0x002FC028 & 0xFFFF) # ori $t9, $t9, 0xc028
/* 0B76F8 800B6AF8 3C18F200 */  lui   $t8, 0xf200
/* 0B76FC 800B6AFC AC580000 */  sw    $t8, ($v0)
/* 0B7700 800B6B00 AC590004 */  sw    $t9, 4($v0)
.L800B6B04:
/* 0B7704 800B6B04 AC600000 */  sw    $zero, ($v1)
.L800B6B08:
/* 0B7708 800B6B08 1000008A */  b     .L800B6D34
/* 0B770C 800B6B0C 24A5FFDF */   addiu $a1, $a1, -0x21
.L800B6B10:
/* 0B7710 800B6B10 28A10060 */  slti  $at, $a1, 0x60
/* 0B7714 800B6B14 10200043 */  beqz  $at, .L800B6C24
/* 0B7718 800B6B18 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B771C 800B6B1C 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B7720 800B6B20 8C6C0000 */  lw    $t4, ($v1)
/* 0B7724 800B6B24 24060001 */  li    $a2, 1
/* 0B7728 800B6B28 10CC003C */  beq   $a2, $t4, .L800B6C1C
/* 0B772C 800B6B2C 3C0D8012 */   lui   $t5, %hi(D_80127CB8) # $t5, 0x8012
/* 0B7730 800B6B30 8DAD7CB8 */  lw    $t5, %lo(D_80127CB8)($t5)
/* 0B7734 800B6B34 3C0FFD70 */  lui   $t7, 0xfd70
/* 0B7738 800B6B38 11A00037 */  beqz  $t5, .L800B6C18
/* 0B773C 800B6B3C 3C188012 */   lui   $t8, %hi(gTexture1) # $t8, 0x8012
/* 0B7740 800B6B40 8C820000 */  lw    $v0, ($a0)
/* 0B7744 800B6B44 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7748 800B6B48 244E0008 */  addiu $t6, $v0, 8
/* 0B774C 800B6B4C AC8E0000 */  sw    $t6, ($a0)
/* 0B7750 800B6B50 AC4F0000 */  sw    $t7, ($v0)
/* 0B7754 800B6B54 8F187CA4 */  lw    $t8, %lo(gTexture1)($t8)
/* 0B7758 800B6B58 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B775C 800B6B5C 0301C821 */  addu  $t9, $t8, $at
/* 0B7760 800B6B60 AC590004 */  sw    $t9, 4($v0)
/* 0B7764 800B6B64 8C820000 */  lw    $v0, ($a0)
/* 0B7768 800B6B68 3C0E0708 */  lui   $t6, (0x07080200 >> 16) # lui $t6, 0x708
/* 0B776C 800B6B6C 244C0008 */  addiu $t4, $v0, 8
/* 0B7770 800B6B70 AC8C0000 */  sw    $t4, ($a0)
/* 0B7774 800B6B74 35CE0200 */  ori   $t6, (0x07080200 & 0xFFFF) # ori $t6, $t6, 0x200
/* 0B7778 800B6B78 3C0DF570 */  lui   $t5, 0xf570
/* 0B777C 800B6B7C AC4D0000 */  sw    $t5, ($v0)
/* 0B7780 800B6B80 AC4E0004 */  sw    $t6, 4($v0)
/* 0B7784 800B6B84 8C820000 */  lw    $v0, ($a0)
/* 0B7788 800B6B88 3C18E600 */  lui   $t8, 0xe600
/* 0B778C 800B6B8C 244F0008 */  addiu $t7, $v0, 8
/* 0B7790 800B6B90 AC8F0000 */  sw    $t7, ($a0)
/* 0B7794 800B6B94 AC400004 */  sw    $zero, 4($v0)
/* 0B7798 800B6B98 AC580000 */  sw    $t8, ($v0)
/* 0B779C 800B6B9C 8C820000 */  lw    $v0, ($a0)
/* 0B77A0 800B6BA0 3C0D0755 */  lui   $t5, (0x07553043 >> 16) # lui $t5, 0x755
/* 0B77A4 800B6BA4 24590008 */  addiu $t9, $v0, 8
/* 0B77A8 800B6BA8 AC990000 */  sw    $t9, ($a0)
/* 0B77AC 800B6BAC 35AD3043 */  ori   $t5, (0x07553043 & 0xFFFF) # ori $t5, $t5, 0x3043
/* 0B77B0 800B6BB0 3C0CF300 */  lui   $t4, 0xf300
/* 0B77B4 800B6BB4 AC4C0000 */  sw    $t4, ($v0)
/* 0B77B8 800B6BB8 AC4D0004 */  sw    $t5, 4($v0)
/* 0B77BC 800B6BBC 8C820000 */  lw    $v0, ($a0)
/* 0B77C0 800B6BC0 3C0FE700 */  lui   $t7, 0xe700
/* 0B77C4 800B6BC4 244E0008 */  addiu $t6, $v0, 8
/* 0B77C8 800B6BC8 AC8E0000 */  sw    $t6, ($a0)
/* 0B77CC 800B6BCC AC400004 */  sw    $zero, 4($v0)
/* 0B77D0 800B6BD0 AC4F0000 */  sw    $t7, ($v0)
/* 0B77D4 800B6BD4 8C820000 */  lw    $v0, ($a0)
/* 0B77D8 800B6BD8 3C0C0008 */  lui   $t4, (0x00080200 >> 16) # lui $t4, 8
/* 0B77DC 800B6BDC 24580008 */  addiu $t8, $v0, 8
/* 0B77E0 800B6BE0 AC980000 */  sw    $t8, ($a0)
/* 0B77E4 800B6BE4 3C19F568 */  lui   $t9, (0xF5683E00 >> 16) # lui $t9, 0xf568
/* 0B77E8 800B6BE8 37393E00 */  ori   $t9, (0xF5683E00 & 0xFFFF) # ori $t9, $t9, 0x3e00
/* 0B77EC 800B6BEC 358C0200 */  ori   $t4, (0x00080200 & 0xFFFF) # ori $t4, $t4, 0x200
/* 0B77F0 800B6BF0 AC4C0004 */  sw    $t4, 4($v0)
/* 0B77F4 800B6BF4 AC590000 */  sw    $t9, ($v0)
/* 0B77F8 800B6BF8 8C820000 */  lw    $v0, ($a0)
/* 0B77FC 800B6BFC 3C0F003D */  lui   $t7, (0x003DC028 >> 16) # lui $t7, 0x3d
/* 0B7800 800B6C00 244D0008 */  addiu $t5, $v0, 8
/* 0B7804 800B6C04 AC8D0000 */  sw    $t5, ($a0)
/* 0B7808 800B6C08 35EFC028 */  ori   $t7, (0x003DC028 & 0xFFFF) # ori $t7, $t7, 0xc028
/* 0B780C 800B6C0C 3C0EF200 */  lui   $t6, 0xf200
/* 0B7810 800B6C10 AC4E0000 */  sw    $t6, ($v0)
/* 0B7814 800B6C14 AC4F0004 */  sw    $t7, 4($v0)
.L800B6C18:
/* 0B7818 800B6C18 AC660000 */  sw    $a2, ($v1)
.L800B6C1C:
/* 0B781C 800B6C1C 10000045 */  b     .L800B6D34
/* 0B7820 800B6C20 24A5FFC0 */   addiu $a1, $a1, -0x40
.L800B6C24:
/* 0B7824 800B6C24 28A10080 */  slti  $at, $a1, 0x80
/* 0B7828 800B6C28 10200042 */  beqz  $at, .L800B6D34
/* 0B782C 800B6C2C 3C038012 */   lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7830 800B6C30 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B7834 800B6C34 8C780000 */  lw    $t8, ($v1)
/* 0B7838 800B6C38 24060002 */  li    $a2, 2
/* 0B783C 800B6C3C 10D8003D */  beq   $a2, $t8, .L800B6D34
/* 0B7840 800B6C40 24A5FFA0 */   addiu $a1, $a1, -0x60
/* 0B7844 800B6C44 3C198012 */  lui   $t9, %hi(D_80127CB8) # $t9, 0x8012
/* 0B7848 800B6C48 8F397CB8 */  lw    $t9, %lo(D_80127CB8)($t9)
/* 0B784C 800B6C4C 3C0DFD70 */  lui   $t5, 0xfd70
/* 0B7850 800B6C50 13200037 */  beqz  $t9, .L800B6D30
/* 0B7854 800B6C54 3C0E8012 */   lui   $t6, %hi(gTexture2) # $t6, 0x8012
/* 0B7858 800B6C58 8C820000 */  lw    $v0, ($a0)
/* 0B785C 800B6C5C 3C018000 */  lui   $at, (0x80000020 >> 16) # lui $at, 0x8000
/* 0B7860 800B6C60 244C0008 */  addiu $t4, $v0, 8
/* 0B7864 800B6C64 AC8C0000 */  sw    $t4, ($a0)
/* 0B7868 800B6C68 AC4D0000 */  sw    $t5, ($v0)
/* 0B786C 800B6C6C 8DCE7CA8 */  lw    $t6, %lo(gTexture2)($t6)
/* 0B7870 800B6C70 34210020 */  ori   $at, (0x80000020 & 0xFFFF) # ori $at, $at, 0x20
/* 0B7874 800B6C74 01C17821 */  addu  $t7, $t6, $at
/* 0B7878 800B6C78 AC4F0004 */  sw    $t7, 4($v0)
/* 0B787C 800B6C7C 8C820000 */  lw    $v0, ($a0)
/* 0B7880 800B6C80 3C0C0708 */  lui   $t4, (0x07080200 >> 16) # lui $t4, 0x708
/* 0B7884 800B6C84 24580008 */  addiu $t8, $v0, 8
/* 0B7888 800B6C88 AC980000 */  sw    $t8, ($a0)
/* 0B788C 800B6C8C 358C0200 */  ori   $t4, (0x07080200 & 0xFFFF) # ori $t4, $t4, 0x200
/* 0B7890 800B6C90 3C19F570 */  lui   $t9, 0xf570
/* 0B7894 800B6C94 AC590000 */  sw    $t9, ($v0)
/* 0B7898 800B6C98 AC4C0004 */  sw    $t4, 4($v0)
/* 0B789C 800B6C9C 8C820000 */  lw    $v0, ($a0)
/* 0B78A0 800B6CA0 3C0EE600 */  lui   $t6, 0xe600
/* 0B78A4 800B6CA4 244D0008 */  addiu $t5, $v0, 8
/* 0B78A8 800B6CA8 AC8D0000 */  sw    $t5, ($a0)
/* 0B78AC 800B6CAC AC400004 */  sw    $zero, 4($v0)
/* 0B78B0 800B6CB0 AC4E0000 */  sw    $t6, ($v0)
/* 0B78B4 800B6CB4 8C820000 */  lw    $v0, ($a0)
/* 0B78B8 800B6CB8 3C190741 */  lui   $t9, (0x0741F056 >> 16) # lui $t9, 0x741
/* 0B78BC 800B6CBC 244F0008 */  addiu $t7, $v0, 8
/* 0B78C0 800B6CC0 AC8F0000 */  sw    $t7, ($a0)
/* 0B78C4 800B6CC4 3739F056 */  ori   $t9, (0x0741F056 & 0xFFFF) # ori $t9, $t9, 0xf056
/* 0B78C8 800B6CC8 3C18F300 */  lui   $t8, 0xf300
/* 0B78CC 800B6CCC AC580000 */  sw    $t8, ($v0)
/* 0B78D0 800B6CD0 AC590004 */  sw    $t9, 4($v0)
/* 0B78D4 800B6CD4 8C820000 */  lw    $v0, ($a0)
/* 0B78D8 800B6CD8 3C0DE700 */  lui   $t5, 0xe700
/* 0B78DC 800B6CDC 244C0008 */  addiu $t4, $v0, 8
/* 0B78E0 800B6CE0 AC8C0000 */  sw    $t4, ($a0)
/* 0B78E4 800B6CE4 AC400004 */  sw    $zero, 4($v0)
/* 0B78E8 800B6CE8 AC4D0000 */  sw    $t5, ($v0)
/* 0B78EC 800B6CEC 8C820000 */  lw    $v0, ($a0)
/* 0B78F0 800B6CF0 3C180008 */  lui   $t8, (0x00080200 >> 16) # lui $t8, 8
/* 0B78F4 800B6CF4 244E0008 */  addiu $t6, $v0, 8
/* 0B78F8 800B6CF8 AC8E0000 */  sw    $t6, ($a0)
/* 0B78FC 800B6CFC 3C0FF568 */  lui   $t7, (0xF5683000 >> 16) # lui $t7, 0xf568
/* 0B7900 800B6D00 35EF3000 */  ori   $t7, (0xF5683000 & 0xFFFF) # ori $t7, $t7, 0x3000
/* 0B7904 800B6D04 37180200 */  ori   $t8, (0x00080200 & 0xFFFF) # ori $t8, $t8, 0x200
/* 0B7908 800B6D08 AC580004 */  sw    $t8, 4($v0)
/* 0B790C 800B6D0C AC4F0000 */  sw    $t7, ($v0)
/* 0B7910 800B6D10 8C820000 */  lw    $v0, ($a0)
/* 0B7914 800B6D14 3C0D002F */  lui   $t5, (0x002FC028 >> 16) # lui $t5, 0x2f
/* 0B7918 800B6D18 24590008 */  addiu $t9, $v0, 8
/* 0B791C 800B6D1C AC990000 */  sw    $t9, ($a0)
/* 0B7920 800B6D20 35ADC028 */  ori   $t5, (0x002FC028 & 0xFFFF) # ori $t5, $t5, 0xc028
/* 0B7924 800B6D24 3C0CF200 */  lui   $t4, 0xf200
/* 0B7928 800B6D28 AC4C0000 */  sw    $t4, ($v0)
/* 0B792C 800B6D2C AC4D0004 */  sw    $t5, 4($v0)
.L800B6D30:
/* 0B7930 800B6D30 AC660000 */  sw    $a2, ($v1)
.L800B6D34:
/* 0B7934 800B6D34 3C038012 */  lui   $v1, %hi(D_80127CCC) # $v1, 0x8012
/* 0B7938 800B6D38 24637CCC */  addiu $v1, %lo(D_80127CCC) # addiu $v1, $v1, 0x7ccc
/* 0B793C 800B6D3C 8C6E0000 */  lw    $t6, ($v1)
/* 0B7940 800B6D40 0005C040 */  sll   $t8, $a1, 1
/* 0B7944 800B6D44 3C0C800E */  lui   $t4, %hi(D_800E2EF4) # $t4, 0x800e
/* 0B7948 800B6D48 000E7980 */  sll   $t7, $t6, 6
/* 0B794C 800B6D4C 01F8C821 */  addu  $t9, $t7, $t8
/* 0B7950 800B6D50 258C2EF4 */  addiu $t4, %lo(D_800E2EF4) # addiu $t4, $t4, 0x2ef4
/* 0B7954 800B6D54 032C1021 */  addu  $v0, $t9, $t4
/* 0B7958 800B6D58 90460000 */  lbu   $a2, ($v0)
/* 0B795C 800B6D5C 904D0001 */  lbu   $t5, 1($v0)
/* 0B7960 800B6D60 3C0E8012 */  lui   $t6, %hi(D_80127CB8) # $t6, 0x8012
/* 0B7964 800B6D64 8DCE7CB8 */  lw    $t6, %lo(D_80127CB8)($t6)
/* 0B7968 800B6D68 01A63823 */  subu  $a3, $t5, $a2
/* 0B796C 800B6D6C 11C00036 */  beqz  $t6, .L800B6E48
/* 0B7970 800B6D70 24E70001 */   addiu $a3, $a3, 1
/* 0B7974 800B6D74 8C820000 */  lw    $v0, ($a0)
/* 0B7978 800B6D78 3C18FCFF */  lui   $t8, (0xFCFFFFFF >> 16) # lui $t8, 0xfcff
/* 0B797C 800B6D7C 244F0008 */  addiu $t7, $v0, 8
/* 0B7980 800B6D80 AC8F0000 */  sw    $t7, ($a0)
/* 0B7984 800B6D84 3C19FFFE */  lui   $t9, (0xFFFEF379 >> 16) # lui $t9, 0xfffe
/* 0B7988 800B6D88 3739F379 */  ori   $t9, (0xFFFEF379 & 0xFFFF) # ori $t9, $t9, 0xf379
/* 0B798C 800B6D8C 3718FFFF */  ori   $t8, (0xFCFFFFFF & 0xFFFF) # ori $t8, $t8, 0xffff
/* 0B7990 800B6D90 AC580000 */  sw    $t8, ($v0)
/* 0B7994 800B6D94 AC590004 */  sw    $t9, 4($v0)
/* 0B7998 800B6D98 8C820000 */  lw    $v0, ($a0)
/* 0B799C 800B6D9C 3C0A8012 */  lui   $t2, %hi(D_80127CAC) # $t2, 0x8012
/* 0B79A0 800B6DA0 244C0008 */  addiu $t4, $v0, 8
/* 0B79A4 800B6DA4 254A7CAC */  addiu $t2, %lo(D_80127CAC) # addiu $t2, $t2, 0x7cac
/* 0B79A8 800B6DA8 AC8C0000 */  sw    $t4, ($a0)
/* 0B79AC 800B6DAC 954D0000 */  lhu   $t5, ($t2)
/* 0B79B0 800B6DB0 3C0B8012 */  lui   $t3, %hi(D_80127CAE) # $t3, 0x8012
/* 0B79B4 800B6DB4 01A77021 */  addu  $t6, $t5, $a3
/* 0B79B8 800B6DB8 256B7CAE */  addiu $t3, %lo(D_80127CAE) # addiu $t3, $t3, 0x7cae
/* 0B79BC 800B6DBC 956D0000 */  lhu   $t5, ($t3)
/* 0B79C0 800B6DC0 000E7880 */  sll   $t7, $t6, 2
/* 0B79C4 800B6DC4 31F80FFF */  andi  $t8, $t7, 0xfff
/* 0B79C8 800B6DC8 0018CB00 */  sll   $t9, $t8, 0xc
/* 0B79CC 800B6DCC 25AE000A */  addiu $t6, $t5, 0xa
/* 0B79D0 800B6DD0 000E7880 */  sll   $t7, $t6, 2
/* 0B79D4 800B6DD4 3C01E400 */  lui   $at, 0xe400
/* 0B79D8 800B6DD8 03216025 */  or    $t4, $t9, $at
/* 0B79DC 800B6DDC 31F80FFF */  andi  $t8, $t7, 0xfff
/* 0B79E0 800B6DE0 0198C825 */  or    $t9, $t4, $t8
/* 0B79E4 800B6DE4 AC590000 */  sw    $t9, ($v0)
/* 0B79E8 800B6DE8 954D0000 */  lhu   $t5, ($t2)
/* 0B79EC 800B6DEC 95780000 */  lhu   $t8, ($t3)
/* 0B79F0 800B6DF0 000D7080 */  sll   $t6, $t5, 2
/* 0B79F4 800B6DF4 31CF0FFF */  andi  $t7, $t6, 0xfff
/* 0B79F8 800B6DF8 0018C880 */  sll   $t9, $t8, 2
/* 0B79FC 800B6DFC 332D0FFF */  andi  $t5, $t9, 0xfff
/* 0B7A00 800B6E00 000F6300 */  sll   $t4, $t7, 0xc
/* 0B7A04 800B6E04 018D7025 */  or    $t6, $t4, $t5
/* 0B7A08 800B6E08 AC4E0004 */  sw    $t6, 4($v0)
/* 0B7A0C 800B6E0C 8C820000 */  lw    $v0, ($a0)
/* 0B7A10 800B6E10 00066D40 */  sll   $t5, $a2, 0x15
/* 0B7A14 800B6E14 244F0008 */  addiu $t7, $v0, 8
/* 0B7A18 800B6E18 AC8F0000 */  sw    $t7, ($a0)
/* 0B7A1C 800B6E1C 3C18B300 */  lui   $t8, 0xb300
/* 0B7A20 800B6E20 AC580000 */  sw    $t8, ($v0)
/* 0B7A24 800B6E24 AC4D0004 */  sw    $t5, 4($v0)
/* 0B7A28 800B6E28 8C820000 */  lw    $v0, ($a0)
/* 0B7A2C 800B6E2C 3C180400 */  lui   $t8, (0x04000400 >> 16) # lui $t8, 0x400
/* 0B7A30 800B6E30 244E0008 */  addiu $t6, $v0, 8
/* 0B7A34 800B6E34 AC8E0000 */  sw    $t6, ($a0)
/* 0B7A38 800B6E38 37180400 */  ori   $t8, (0x04000400 & 0xFFFF) # ori $t8, $t8, 0x400
/* 0B7A3C 800B6E3C 3C0FB200 */  lui   $t7, 0xb200
/* 0B7A40 800B6E40 AC4F0000 */  sw    $t7, ($v0)
/* 0B7A44 800B6E44 AC580004 */  sw    $t8, 4($v0)
.L800B6E48:
/* 0B7A48 800B6E48 03E00008 */  jr    $ra
/* 0B7A4C 800B6E4C 00E01025 */   move  $v0, $a3

