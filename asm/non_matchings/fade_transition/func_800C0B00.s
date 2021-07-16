glabel func_800C0B00
/* 0C1700 800C0B00 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0C1704 800C0B04 00051880 */  sll   $v1, $a1, 2
/* 0C1708 800C0B08 00054880 */  sll   $t1, $a1, 2
/* 0C170C 800C0B0C 01254823 */  subu  $t1, $t1, $a1
/* 0C1710 800C0B10 00651821 */  addu  $v1, $v1, $a1
/* 0C1714 800C0B14 AFB00018 */  sw    $s0, 0x18($sp)
/* 0C1718 800C0B18 00031840 */  sll   $v1, $v1, 1
/* 0C171C 800C0B1C 00094880 */  sll   $t1, $t1, 2
/* 0C1720 800C0B20 00064100 */  sll   $t0, $a2, 4
/* 0C1724 800C0B24 00A08025 */  move  $s0, $a1
/* 0C1728 800C0B28 00687021 */  addu  $t6, $v1, $t0
/* 0C172C 800C0B2C 0009C080 */  sll   $t8, $t1, 2
/* 0C1730 800C0B30 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C1734 800C0B34 AFB20020 */  sw    $s2, 0x20($sp)
/* 0C1738 800C0B38 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0C173C 800C0B3C AFA40050 */  sw    $a0, 0x50($sp)
/* 0C1740 800C0B40 0309C023 */  subu  $t8, $t8, $t1
/* 0C1744 800C0B44 000E7840 */  sll   $t7, $t6, 1
/* 0C1748 800C0B48 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 0C174C 800C0B4C 00C08825 */  move  $s1, $a2
/* 0C1750 800C0B50 00E09025 */  move  $s2, $a3
/* 0C1754 800C0B54 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 0C1758 800C0B58 01F82021 */  addu  $a0, $t7, $t8
/* 0C175C 800C0B5C AFA8002C */  sw    $t0, 0x2c($sp)
/* 0C1760 800C0B60 AFA90028 */  sw    $t1, 0x28($sp)
/* 0C1764 800C0B64 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0C1768 800C0B68 AFA30030 */   sw    $v1, 0x30($sp)
/* 0C176C 800C0B6C 8FA30030 */  lw    $v1, 0x30($sp)
/* 0C1770 800C0B70 3C04800E */  lui   $a0, %hi(D_800E31C0) # $a0, 0x800e
/* 0C1774 800C0B74 248431C0 */  addiu $a0, %lo(D_800E31C0) # addiu $a0, $a0, 0x31c0
/* 0C1778 800C0B78 AC820000 */  sw    $v0, ($a0)
/* 0C177C 800C0B7C 3C01800E */  lui   $at, %hi(D_800E31C0+4) # $at, 0x800e
/* 0C1780 800C0B80 00436021 */  addu  $t4, $v0, $v1
/* 0C1784 800C0B84 AC2C31C4 */  sw    $t4, %lo(D_800E31C0+4)($at)
/* 0C1788 800C0B88 8C8D0004 */  lw    $t5, 4($a0)
/* 0C178C 800C0B8C 3C05800E */  lui   $a1, %hi(D_800E31C8) # $a1, 0x800e
/* 0C1790 800C0B90 3C01800E */  lui   $at, %hi(D_800E31C8+4) # $at, 0x800e
/* 0C1794 800C0B94 01A37021 */  addu  $t6, $t5, $v1
/* 0C1798 800C0B98 24A531C8 */  addiu $a1, %lo(D_800E31C8) # addiu $a1, $a1, 0x31c8
/* 0C179C 800C0B9C AC2E31C8 */  sw    $t6, %lo(D_800E31C8)($at)
/* 0C17A0 800C0BA0 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0C17A4 800C0BA4 8CAF0000 */  lw    $t7, ($a1)
/* 0C17A8 800C0BA8 3C068013 */  lui   $a2, %hi(D_8012A770) # $a2, 0x8013
/* 0C17AC 800C0BAC 01E8C021 */  addu  $t8, $t7, $t0
/* 0C17B0 800C0BB0 AC3831CC */  sw    $t8, %lo(D_800E31C8+4)($at)
/* 0C17B4 800C0BB4 8CB90004 */  lw    $t9, 4($a1)
/* 0C17B8 800C0BB8 3C018013 */  lui   $at, %hi(D_8012A770) # $at, 0x8013
/* 0C17BC 800C0BBC 03286021 */  addu  $t4, $t9, $t0
/* 0C17C0 800C0BC0 24C6A770 */  addiu $a2, %lo(D_8012A770) # addiu $a2, $a2, -0x5890
/* 0C17C4 800C0BC4 AC2CA770 */  sw    $t4, %lo(D_8012A770)($at)
/* 0C17C8 800C0BC8 8FA90028 */  lw    $t1, 0x28($sp)
/* 0C17CC 800C0BCC 8CCD0000 */  lw    $t5, ($a2)
/* 0C17D0 800C0BD0 3C0B8013 */  lui   $t3, %hi(D_8012A774) # $t3, 0x8013
/* 0C17D4 800C0BD4 3C018013 */  lui   $at, %hi(D_8012A774) # $at, 0x8013
/* 0C17D8 800C0BD8 01A97021 */  addu  $t6, $t5, $t1
/* 0C17DC 800C0BDC 256BA774 */  addiu $t3, %lo(D_8012A774) # addiu $t3, $t3, -0x588c
/* 0C17E0 800C0BE0 AC2EA774 */  sw    $t6, %lo(D_8012A774)($at)
/* 0C17E4 800C0BE4 8D6F0000 */  lw    $t7, ($t3)
/* 0C17E8 800C0BE8 8FB90050 */  lw    $t9, 0x50($sp)
/* 0C17EC 800C0BEC 3C018013 */  lui   $at, %hi(D_8012A778) # $at, 0x8013
/* 0C17F0 800C0BF0 01E9C021 */  addu  $t8, $t7, $t1
/* 0C17F4 800C0BF4 AC38A778 */  sw    $t8, %lo(D_8012A778)($at)
/* 0C17F8 800C0BF8 932C0000 */  lbu   $t4, ($t9)
/* 0C17FC 800C0BFC 8FA20060 */  lw    $v0, 0x60($sp)
/* 0C1800 800C0C00 318D0080 */  andi  $t5, $t4, 0x80
/* 0C1804 800C0C04 11A00008 */  beqz  $t5, .L800C0C28
/* 0C1808 800C0C08 3C09800E */   lui   $t1, %hi(D_800E31B0) # $t1, 0x800e
/* 0C180C 800C0C0C 8FAE0064 */  lw    $t6, 0x64($sp)
/* 0C1810 800C0C10 AFA20064 */  sw    $v0, 0x64($sp)
/* 0C1814 800C0C14 8FA20068 */  lw    $v0, 0x68($sp)
/* 0C1818 800C0C18 8FAF006C */  lw    $t7, 0x6c($sp)
/* 0C181C 800C0C1C AFAE0060 */  sw    $t6, 0x60($sp)
/* 0C1820 800C0C20 AFA2006C */  sw    $v0, 0x6c($sp)
/* 0C1824 800C0C24 AFAF0068 */  sw    $t7, 0x68($sp)
.L800C0C28:
/* 0C1828 800C0C28 1A00008C */  blez  $s0, .L800C0E5C
/* 0C182C 800C0C2C 00005025 */   move  $t2, $zero
/* 0C1830 800C0C30 3C038013 */  lui   $v1, %hi(D_8012A778) # $v1, 0x8013
/* 0C1834 800C0C34 8FA40060 */  lw    $a0, 0x60($sp)
/* 0C1838 800C0C38 8FA70068 */  lw    $a3, 0x68($sp)
/* 0C183C 800C0C3C 8FA50064 */  lw    $a1, 0x64($sp)
/* 0C1840 800C0C40 8FA8006C */  lw    $t0, 0x6c($sp)
/* 0C1844 800C0C44 2463A778 */  addiu $v1, %lo(D_8012A778) # addiu $v1, $v1, -0x5888
/* 0C1848 800C0C48 00001025 */  move  $v0, $zero
/* 0C184C 800C0C4C 252931B0 */  addiu $t1, %lo(D_800E31B0) # addiu $t1, $t1, 0x31b0
.L800C0C50:
/* 0C1850 800C0C50 90980000 */  lbu   $t8, ($a0)
/* 0C1854 800C0C54 8CCE0000 */  lw    $t6, ($a2)
/* 0C1858 800C0C58 0018C840 */  sll   $t9, $t8, 1
/* 0C185C 800C0C5C 02596021 */  addu  $t4, $s2, $t9
/* 0C1860 800C0C60 858D0000 */  lh    $t5, ($t4)
/* 0C1864 800C0C64 01C27821 */  addu  $t7, $t6, $v0
/* 0C1868 800C0C68 448D2000 */  mtc1  $t5, $f4
/* 0C186C 800C0C6C 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C1870 800C0C70 468021A0 */  cvt.s.w $f6, $f4
/* 0C1874 800C0C74 E5E60000 */  swc1  $f6, ($t7)
/* 0C1878 800C0C78 90980000 */  lbu   $t8, ($a0)
/* 0C187C 800C0C7C 8CCE0000 */  lw    $t6, ($a2)
/* 0C1880 800C0C80 0018C840 */  sll   $t9, $t8, 1
/* 0C1884 800C0C84 02596021 */  addu  $t4, $s2, $t9
/* 0C1888 800C0C88 858D0002 */  lh    $t5, 2($t4)
/* 0C188C 800C0C8C 01C27821 */  addu  $t7, $t6, $v0
/* 0C1890 800C0C90 448D4000 */  mtc1  $t5, $f8
/* 0C1894 800C0C94 00000000 */  nop   
/* 0C1898 800C0C98 468042A0 */  cvt.s.w $f10, $f8
/* 0C189C 800C0C9C E5EA0004 */  swc1  $f10, 4($t7)
/* 0C18A0 800C0CA0 90F80000 */  lbu   $t8, ($a3)
/* 0C18A4 800C0CA4 00000000 */  nop   
/* 0C18A8 800C0CA8 44988000 */  mtc1  $t8, $f16
/* 0C18AC 800C0CAC 07010004 */  bgez  $t8, .L800C0CC0
/* 0C18B0 800C0CB0 468084A0 */   cvt.s.w $f18, $f16
/* 0C18B4 800C0CB4 44812000 */  mtc1  $at, $f4
/* 0C18B8 800C0CB8 00000000 */  nop   
/* 0C18BC 800C0CBC 46049480 */  add.s $f18, $f18, $f4
.L800C0CC0:
/* 0C18C0 800C0CC0 8CD90000 */  lw    $t9, ($a2)
/* 0C18C4 800C0CC4 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C18C8 800C0CC8 03226021 */  addu  $t4, $t9, $v0
/* 0C18CC 800C0CCC E5920008 */  swc1  $f18, 8($t4)
/* 0C18D0 800C0CD0 90AD0000 */  lbu   $t5, ($a1)
/* 0C18D4 800C0CD4 8C790000 */  lw    $t9, ($v1)
/* 0C18D8 800C0CD8 000D7040 */  sll   $t6, $t5, 1
/* 0C18DC 800C0CDC 024E7821 */  addu  $t7, $s2, $t6
/* 0C18E0 800C0CE0 85F80000 */  lh    $t8, ($t7)
/* 0C18E4 800C0CE4 03226021 */  addu  $t4, $t9, $v0
/* 0C18E8 800C0CE8 44983000 */  mtc1  $t8, $f6
/* 0C18EC 800C0CEC 00000000 */  nop   
/* 0C18F0 800C0CF0 46803220 */  cvt.s.w $f8, $f6
/* 0C18F4 800C0CF4 E5880000 */  swc1  $f8, ($t4)
/* 0C18F8 800C0CF8 90AD0000 */  lbu   $t5, ($a1)
/* 0C18FC 800C0CFC 8C790000 */  lw    $t9, ($v1)
/* 0C1900 800C0D00 000D7040 */  sll   $t6, $t5, 1
/* 0C1904 800C0D04 024E7821 */  addu  $t7, $s2, $t6
/* 0C1908 800C0D08 85F80002 */  lh    $t8, 2($t7)
/* 0C190C 800C0D0C 03226021 */  addu  $t4, $t9, $v0
/* 0C1910 800C0D10 44985000 */  mtc1  $t8, $f10
/* 0C1914 800C0D14 00000000 */  nop   
/* 0C1918 800C0D18 46805420 */  cvt.s.w $f16, $f10
/* 0C191C 800C0D1C E5900004 */  swc1  $f16, 4($t4)
/* 0C1920 800C0D20 910D0000 */  lbu   $t5, ($t0)
/* 0C1924 800C0D24 00000000 */  nop   
/* 0C1928 800C0D28 448D2000 */  mtc1  $t5, $f4
/* 0C192C 800C0D2C 05A10004 */  bgez  $t5, .L800C0D40
/* 0C1930 800C0D30 468024A0 */   cvt.s.w $f18, $f4
/* 0C1934 800C0D34 44813000 */  mtc1  $at, $f6
/* 0C1938 800C0D38 00000000 */  nop   
/* 0C193C 800C0D3C 46069480 */  add.s $f18, $f18, $f6
.L800C0D40:
/* 0C1940 800C0D40 8C6E0000 */  lw    $t6, ($v1)
/* 0C1944 800C0D44 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C1948 800C0D48 01C27821 */  addu  $t7, $t6, $v0
/* 0C194C 800C0D4C E5F20008 */  swc1  $f18, 8($t7)
/* 0C1950 800C0D50 8CCC0000 */  lw    $t4, ($a2)
/* 0C1954 800C0D54 8C780000 */  lw    $t8, ($v1)
/* 0C1958 800C0D58 952E0000 */  lhu   $t6, ($t1)
/* 0C195C 800C0D5C 01826821 */  addu  $t5, $t4, $v0
/* 0C1960 800C0D60 0302C821 */  addu  $t9, $t8, $v0
/* 0C1964 800C0D64 C7280000 */  lwc1  $f8, ($t9)
/* 0C1968 800C0D68 C5AA0000 */  lwc1  $f10, ($t5)
/* 0C196C 800C0D6C 448E2000 */  mtc1  $t6, $f4
/* 0C1970 800C0D70 460A4401 */  sub.s $f16, $f8, $f10
/* 0C1974 800C0D74 05C10004 */  bgez  $t6, .L800C0D88
/* 0C1978 800C0D78 468021A0 */   cvt.s.w $f6, $f4
/* 0C197C 800C0D7C 44819000 */  mtc1  $at, $f18
/* 0C1980 800C0D80 00000000 */  nop   
/* 0C1984 800C0D84 46123180 */  add.s $f6, $f6, $f18
.L800C0D88:
/* 0C1988 800C0D88 00000000 */  nop   
/* 0C198C 800C0D8C 46068203 */  div.s $f8, $f16, $f6
/* 0C1990 800C0D90 8D6F0000 */  lw    $t7, ($t3)
/* 0C1994 800C0D94 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C1998 800C0D98 01E2C021 */  addu  $t8, $t7, $v0
/* 0C199C 800C0D9C E7080000 */  swc1  $f8, ($t8)
/* 0C19A0 800C0DA0 8CCD0000 */  lw    $t5, ($a2)
/* 0C19A4 800C0DA4 8C790000 */  lw    $t9, ($v1)
/* 0C19A8 800C0DA8 952F0000 */  lhu   $t7, ($t1)
/* 0C19AC 800C0DAC 01A27021 */  addu  $t6, $t5, $v0
/* 0C19B0 800C0DB0 03226021 */  addu  $t4, $t9, $v0
/* 0C19B4 800C0DB4 C58A0004 */  lwc1  $f10, 4($t4)
/* 0C19B8 800C0DB8 C5C40004 */  lwc1  $f4, 4($t6)
/* 0C19BC 800C0DBC 448F8000 */  mtc1  $t7, $f16
/* 0C19C0 800C0DC0 46045481 */  sub.s $f18, $f10, $f4
/* 0C19C4 800C0DC4 05E10004 */  bgez  $t7, .L800C0DD8
/* 0C19C8 800C0DC8 468081A0 */   cvt.s.w $f6, $f16
/* 0C19CC 800C0DCC 44814000 */  mtc1  $at, $f8
/* 0C19D0 800C0DD0 00000000 */  nop   
/* 0C19D4 800C0DD4 46083180 */  add.s $f6, $f6, $f8
.L800C0DD8:
/* 0C19D8 800C0DD8 00000000 */  nop   
/* 0C19DC 800C0DDC 46069283 */  div.s $f10, $f18, $f6
/* 0C19E0 800C0DE0 8D780000 */  lw    $t8, ($t3)
/* 0C19E4 800C0DE4 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C19E8 800C0DE8 0302C821 */  addu  $t9, $t8, $v0
/* 0C19EC 800C0DEC E72A0004 */  swc1  $f10, 4($t9)
/* 0C19F0 800C0DF0 8CCE0000 */  lw    $t6, ($a2)
/* 0C19F4 800C0DF4 8C6C0000 */  lw    $t4, ($v1)
/* 0C19F8 800C0DF8 95380000 */  lhu   $t8, ($t1)
/* 0C19FC 800C0DFC 01C27821 */  addu  $t7, $t6, $v0
/* 0C1A00 800C0E00 01826821 */  addu  $t5, $t4, $v0
/* 0C1A04 800C0E04 C5A40008 */  lwc1  $f4, 8($t5)
/* 0C1A08 800C0E08 C5F00008 */  lwc1  $f16, 8($t7)
/* 0C1A0C 800C0E0C 44989000 */  mtc1  $t8, $f18
/* 0C1A10 800C0E10 46102201 */  sub.s $f8, $f4, $f16
/* 0C1A14 800C0E14 07010004 */  bgez  $t8, .L800C0E28
/* 0C1A18 800C0E18 468091A0 */   cvt.s.w $f6, $f18
/* 0C1A1C 800C0E1C 44815000 */  mtc1  $at, $f10
/* 0C1A20 800C0E20 00000000 */  nop   
/* 0C1A24 800C0E24 460A3180 */  add.s $f6, $f6, $f10
.L800C0E28:
/* 0C1A28 800C0E28 00000000 */  nop   
/* 0C1A2C 800C0E2C 46064103 */  div.s $f4, $f8, $f6
/* 0C1A30 800C0E30 8D790000 */  lw    $t9, ($t3)
/* 0C1A34 800C0E34 254A0001 */  addiu $t2, $t2, 1
/* 0C1A38 800C0E38 03226021 */  addu  $t4, $t9, $v0
/* 0C1A3C 800C0E3C 2442000C */  addiu $v0, $v0, 0xc
/* 0C1A40 800C0E40 24840001 */  addiu $a0, $a0, 1
/* 0C1A44 800C0E44 24E70001 */  addiu $a3, $a3, 1
/* 0C1A48 800C0E48 24A50001 */  addiu $a1, $a1, 1
/* 0C1A4C 800C0E4C 25080001 */  addiu $t0, $t0, 1
/* 0C1A50 800C0E50 1550FF7F */  bne   $t2, $s0, .L800C0C50
/* 0C1A54 800C0E54 E5840008 */   swc1  $f4, 8($t4)
/* 0C1A58 800C0E58 00005025 */  move  $t2, $zero
.L800C0E5C:
/* 0C1A5C 800C0E5C 3C088013 */  lui   $t0, %hi(gCurFadeBlue) # $t0, 0x8013
/* 0C1A60 800C0E60 3C078013 */  lui   $a3, %hi(gCurFadeGreen) # $a3, 0x8013
/* 0C1A64 800C0E64 3C068013 */  lui   $a2, %hi(gCurFadeRed) # $a2, 0x8013
/* 0C1A68 800C0E68 24C6A734 */  addiu $a2, %lo(gCurFadeRed) # addiu $a2, $a2, -0x58cc
/* 0C1A6C 800C0E6C 24E7A735 */  addiu $a3, %lo(gCurFadeGreen) # addiu $a3, $a3, -0x58cb
/* 0C1A70 800C0E70 2508A736 */  addiu $t0, %lo(gCurFadeBlue) # addiu $t0, $t0, -0x58ca
/* 0C1A74 800C0E74 2404FFF0 */  li    $a0, -16
.L800C0E78:
/* 0C1A78 800C0E78 1A000065 */  blez  $s0, .L800C1010
/* 0C1A7C 800C0E7C 00002825 */   move  $a1, $zero
/* 0C1A80 800C0E80 3C0E800E */  lui   $t6, %hi(D_800E31C0) # $t6, 0x800e
/* 0C1A84 800C0E84 25CE31C0 */  addiu $t6, %lo(D_800E31C0) # addiu $t6, $t6, 0x31c0
/* 0C1A88 800C0E88 000A6880 */  sll   $t5, $t2, 2
/* 0C1A8C 800C0E8C 320B0003 */  andi  $t3, $s0, 3
/* 0C1A90 800C0E90 11600017 */  beqz  $t3, .L800C0EF0
/* 0C1A94 800C0E94 01AE1821 */   addu  $v1, $t5, $t6
/* 0C1A98 800C0E98 00001025 */  move  $v0, $zero
/* 0C1A9C 800C0E9C 000210C0 */  sll   $v0, $v0, 3
/* 0C1AA0 800C0EA0 01604825 */  move  $t1, $t3
.L800C0EA4:
/* 0C1AA4 800C0EA4 8C6F0000 */  lw    $t7, ($v1)
/* 0C1AA8 800C0EA8 24A50001 */  addiu $a1, $a1, 1
/* 0C1AAC 800C0EAC 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1AB0 800C0EB0 A7040004 */  sh    $a0, 4($t8)
/* 0C1AB4 800C0EB4 8C6C0000 */  lw    $t4, ($v1)
/* 0C1AB8 800C0EB8 90D90000 */  lbu   $t9, ($a2)
/* 0C1ABC 800C0EBC 01826821 */  addu  $t5, $t4, $v0
/* 0C1AC0 800C0EC0 A1B90006 */  sb    $t9, 6($t5)
/* 0C1AC4 800C0EC4 8C6F0000 */  lw    $t7, ($v1)
/* 0C1AC8 800C0EC8 90EE0000 */  lbu   $t6, ($a3)
/* 0C1ACC 800C0ECC 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1AD0 800C0ED0 A30E0007 */  sb    $t6, 7($t8)
/* 0C1AD4 800C0ED4 8C790000 */  lw    $t9, ($v1)
/* 0C1AD8 800C0ED8 910C0000 */  lbu   $t4, ($t0)
/* 0C1ADC 800C0EDC 03226821 */  addu  $t5, $t9, $v0
/* 0C1AE0 800C0EE0 2442000A */  addiu $v0, $v0, 0xa
/* 0C1AE4 800C0EE4 1525FFEF */  bne   $t1, $a1, .L800C0EA4
/* 0C1AE8 800C0EE8 A1AC0008 */   sb    $t4, 8($t5)
/* 0C1AEC 800C0EEC 10B00048 */  beq   $a1, $s0, .L800C1010
.L800C0EF0:
/* 0C1AF0 800C0EF0 00051080 */   sll   $v0, $a1, 2
/* 0C1AF4 800C0EF4 00104880 */  sll   $t1, $s0, 2
/* 0C1AF8 800C0EF8 01304821 */  addu  $t1, $t1, $s0
/* 0C1AFC 800C0EFC 00451021 */  addu  $v0, $v0, $a1
/* 0C1B00 800C0F00 00021040 */  sll   $v0, $v0, 1
/* 0C1B04 800C0F04 00094840 */  sll   $t1, $t1, 1
.L800C0F08:
/* 0C1B08 800C0F08 8C6F0000 */  lw    $t7, ($v1)
/* 0C1B0C 800C0F0C 00000000 */  nop   
/* 0C1B10 800C0F10 01E27021 */  addu  $t6, $t7, $v0
/* 0C1B14 800C0F14 A5C40004 */  sh    $a0, 4($t6)
/* 0C1B18 800C0F18 8C790000 */  lw    $t9, ($v1)
/* 0C1B1C 800C0F1C 90D80000 */  lbu   $t8, ($a2)
/* 0C1B20 800C0F20 03226021 */  addu  $t4, $t9, $v0
/* 0C1B24 800C0F24 A1980006 */  sb    $t8, 6($t4)
/* 0C1B28 800C0F28 8C6F0000 */  lw    $t7, ($v1)
/* 0C1B2C 800C0F2C 90ED0000 */  lbu   $t5, ($a3)
/* 0C1B30 800C0F30 01E27021 */  addu  $t6, $t7, $v0
/* 0C1B34 800C0F34 A1CD0007 */  sb    $t5, 7($t6)
/* 0C1B38 800C0F38 8C780000 */  lw    $t8, ($v1)
/* 0C1B3C 800C0F3C 91190000 */  lbu   $t9, ($t0)
/* 0C1B40 800C0F40 03026021 */  addu  $t4, $t8, $v0
/* 0C1B44 800C0F44 A1990008 */  sb    $t9, 8($t4)
/* 0C1B48 800C0F48 8C6F0000 */  lw    $t7, ($v1)
/* 0C1B4C 800C0F4C 00000000 */  nop   
/* 0C1B50 800C0F50 01E26821 */  addu  $t5, $t7, $v0
/* 0C1B54 800C0F54 A5A4000E */  sh    $a0, 0xe($t5)
/* 0C1B58 800C0F58 8C780000 */  lw    $t8, ($v1)
/* 0C1B5C 800C0F5C 90CE0000 */  lbu   $t6, ($a2)
/* 0C1B60 800C0F60 0302C821 */  addu  $t9, $t8, $v0
/* 0C1B64 800C0F64 A32E0010 */  sb    $t6, 0x10($t9)
/* 0C1B68 800C0F68 8C6F0000 */  lw    $t7, ($v1)
/* 0C1B6C 800C0F6C 90EC0000 */  lbu   $t4, ($a3)
/* 0C1B70 800C0F70 01E26821 */  addu  $t5, $t7, $v0
/* 0C1B74 800C0F74 A1AC0011 */  sb    $t4, 0x11($t5)
/* 0C1B78 800C0F78 8C6E0000 */  lw    $t6, ($v1)
/* 0C1B7C 800C0F7C 91180000 */  lbu   $t8, ($t0)
/* 0C1B80 800C0F80 01C2C821 */  addu  $t9, $t6, $v0
/* 0C1B84 800C0F84 A3380012 */  sb    $t8, 0x12($t9)
/* 0C1B88 800C0F88 8C6F0000 */  lw    $t7, ($v1)
/* 0C1B8C 800C0F8C 00000000 */  nop   
/* 0C1B90 800C0F90 01E26021 */  addu  $t4, $t7, $v0
/* 0C1B94 800C0F94 A5840018 */  sh    $a0, 0x18($t4)
/* 0C1B98 800C0F98 8C6E0000 */  lw    $t6, ($v1)
/* 0C1B9C 800C0F9C 90CD0000 */  lbu   $t5, ($a2)
/* 0C1BA0 800C0FA0 01C2C021 */  addu  $t8, $t6, $v0
/* 0C1BA4 800C0FA4 A30D001A */  sb    $t5, 0x1a($t8)
/* 0C1BA8 800C0FA8 8C6F0000 */  lw    $t7, ($v1)
/* 0C1BAC 800C0FAC 90F90000 */  lbu   $t9, ($a3)
/* 0C1BB0 800C0FB0 01E26021 */  addu  $t4, $t7, $v0
/* 0C1BB4 800C0FB4 A199001B */  sb    $t9, 0x1b($t4)
/* 0C1BB8 800C0FB8 8C6D0000 */  lw    $t5, ($v1)
/* 0C1BBC 800C0FBC 910E0000 */  lbu   $t6, ($t0)
/* 0C1BC0 800C0FC0 01A2C021 */  addu  $t8, $t5, $v0
/* 0C1BC4 800C0FC4 A30E001C */  sb    $t6, 0x1c($t8)
/* 0C1BC8 800C0FC8 8C6F0000 */  lw    $t7, ($v1)
/* 0C1BCC 800C0FCC 00000000 */  nop   
/* 0C1BD0 800C0FD0 01E2C821 */  addu  $t9, $t7, $v0
/* 0C1BD4 800C0FD4 A7240022 */  sh    $a0, 0x22($t9)
/* 0C1BD8 800C0FD8 8C6D0000 */  lw    $t5, ($v1)
/* 0C1BDC 800C0FDC 90CC0000 */  lbu   $t4, ($a2)
/* 0C1BE0 800C0FE0 01A27021 */  addu  $t6, $t5, $v0
/* 0C1BE4 800C0FE4 A1CC0024 */  sb    $t4, 0x24($t6)
/* 0C1BE8 800C0FE8 8C6F0000 */  lw    $t7, ($v1)
/* 0C1BEC 800C0FEC 90F80000 */  lbu   $t8, ($a3)
/* 0C1BF0 800C0FF0 01E2C821 */  addu  $t9, $t7, $v0
/* 0C1BF4 800C0FF4 A3380025 */  sb    $t8, 0x25($t9)
/* 0C1BF8 800C0FF8 8C6C0000 */  lw    $t4, ($v1)
/* 0C1BFC 800C0FFC 910D0000 */  lbu   $t5, ($t0)
/* 0C1C00 800C1000 01827021 */  addu  $t6, $t4, $v0
/* 0C1C04 800C1004 24420028 */  addiu $v0, $v0, 0x28
/* 0C1C08 800C1008 1449FFBF */  bne   $v0, $t1, .L800C0F08
/* 0C1C0C 800C100C A1CD0026 */   sb    $t5, 0x26($t6)
.L800C1010:
/* 0C1C10 800C1010 254A0001 */  addiu $t2, $t2, 1
/* 0C1C14 800C1014 29410002 */  slti  $at, $t2, 2
/* 0C1C18 800C1018 1420FF97 */  bnez  $at, .L800C0E78
/* 0C1C1C 800C101C 00000000 */   nop   
/* 0C1C20 800C1020 8FA70070 */  lw    $a3, 0x70($sp)
/* 0C1C24 800C1024 00005025 */  move  $t2, $zero
/* 0C1C28 800C1028 24080002 */  li    $t0, 2
/* 0C1C2C 800C102C 24060040 */  li    $a2, 64
.L800C1030:
/* 0C1C30 800C1030 1A200031 */  blez  $s1, .L800C10F8
/* 0C1C34 800C1034 00002825 */   move  $a1, $zero
/* 0C1C38 800C1038 3C18800E */  lui   $t8, %hi(D_800E31C8) # $t8, 0x800e
/* 0C1C3C 800C103C 271831C8 */  addiu $t8, %lo(D_800E31C8) # addiu $t8, $t8, 0x31c8
/* 0C1C40 800C1040 000A7880 */  sll   $t7, $t2, 2
/* 0C1C44 800C1044 01F81821 */  addu  $v1, $t7, $t8
/* 0C1C48 800C1048 00001025 */  move  $v0, $zero
/* 0C1C4C 800C104C 00E02025 */  move  $a0, $a3
.L800C1050:
/* 0C1C50 800C1050 8C790000 */  lw    $t9, ($v1)
/* 0C1C54 800C1054 24A50001 */  addiu $a1, $a1, 1
/* 0C1C58 800C1058 03226021 */  addu  $t4, $t9, $v0
/* 0C1C5C 800C105C A1860000 */  sb    $a2, ($t4)
/* 0C1C60 800C1060 8C6E0000 */  lw    $t6, ($v1)
/* 0C1C64 800C1064 908D0000 */  lbu   $t5, ($a0)
/* 0C1C68 800C1068 01C27821 */  addu  $t7, $t6, $v0
/* 0C1C6C 800C106C A1ED0001 */  sb    $t5, 1($t7)
/* 0C1C70 800C1070 8C780000 */  lw    $t8, ($v1)
/* 0C1C74 800C1074 24840003 */  addiu $a0, $a0, 3
/* 0C1C78 800C1078 0302C821 */  addu  $t9, $t8, $v0
/* 0C1C7C 800C107C A7200004 */  sh    $zero, 4($t9)
/* 0C1C80 800C1080 8C6C0000 */  lw    $t4, ($v1)
/* 0C1C84 800C1084 00000000 */  nop   
/* 0C1C88 800C1088 01827021 */  addu  $t6, $t4, $v0
/* 0C1C8C 800C108C A5C00006 */  sh    $zero, 6($t6)
/* 0C1C90 800C1090 8C6F0000 */  lw    $t7, ($v1)
/* 0C1C94 800C1094 908DFFFE */  lbu   $t5, -2($a0)
/* 0C1C98 800C1098 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1C9C 800C109C A30D0002 */  sb    $t5, 2($t8)
/* 0C1CA0 800C10A0 8C790000 */  lw    $t9, ($v1)
/* 0C1CA4 800C10A4 00000000 */  nop   
/* 0C1CA8 800C10A8 03226021 */  addu  $t4, $t9, $v0
/* 0C1CAC 800C10AC A5800008 */  sh    $zero, 8($t4)
/* 0C1CB0 800C10B0 8C6E0000 */  lw    $t6, ($v1)
/* 0C1CB4 800C10B4 00000000 */  nop   
/* 0C1CB8 800C10B8 01C27821 */  addu  $t7, $t6, $v0
/* 0C1CBC 800C10BC A5E0000A */  sh    $zero, 0xa($t7)
/* 0C1CC0 800C10C0 8C780000 */  lw    $t8, ($v1)
/* 0C1CC4 800C10C4 908DFFFF */  lbu   $t5, -1($a0)
/* 0C1CC8 800C10C8 0302C821 */  addu  $t9, $t8, $v0
/* 0C1CCC 800C10CC A32D0003 */  sb    $t5, 3($t9)
/* 0C1CD0 800C10D0 8C6C0000 */  lw    $t4, ($v1)
/* 0C1CD4 800C10D4 00000000 */  nop   
/* 0C1CD8 800C10D8 01827021 */  addu  $t6, $t4, $v0
/* 0C1CDC 800C10DC A5C0000C */  sh    $zero, 0xc($t6)
/* 0C1CE0 800C10E0 8C6F0000 */  lw    $t7, ($v1)
/* 0C1CE4 800C10E4 00000000 */  nop   
/* 0C1CE8 800C10E8 01E2C021 */  addu  $t8, $t7, $v0
/* 0C1CEC 800C10EC 24420010 */  addiu $v0, $v0, 0x10
/* 0C1CF0 800C10F0 14B1FFD7 */  bne   $a1, $s1, .L800C1050
/* 0C1CF4 800C10F4 A700000E */   sh    $zero, 0xe($t8)
.L800C10F8:
/* 0C1CF8 800C10F8 254A0001 */  addiu $t2, $t2, 1
/* 0C1CFC 800C10FC 1548FFCC */  bne   $t2, $t0, .L800C1030
/* 0C1D00 800C1100 00000000 */   nop   
/* 0C1D04 800C1104 240D0001 */  li    $t5, 1
/* 0C1D08 800C1108 3C01800E */  lui   $at, %hi(D_800E31AC) # $at, 0x800e
/* 0C1D0C 800C110C AC2D31AC */  sw    $t5, %lo(D_800E31AC)($at)
/* 0C1D10 800C1110 3C018013 */  lui   $at, %hi(D_8012A77C) # $at, 0x8013
/* 0C1D14 800C1114 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C1D18 800C1118 AC30A77C */  sw    $s0, %lo(D_8012A77C)($at)
/* 0C1D1C 800C111C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0C1D20 800C1120 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0C1D24 800C1124 8FB20020 */  lw    $s2, 0x20($sp)
/* 0C1D28 800C1128 03E00008 */  jr    $ra
/* 0C1D2C 800C112C 27BD0050 */   addiu $sp, $sp, 0x50

