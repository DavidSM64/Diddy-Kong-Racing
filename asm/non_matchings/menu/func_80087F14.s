glabel func_80087F14
/* 088B14 80087F14 27BDFF70 */  addiu $sp, $sp, -0x90
/* 088B18 80087F18 AFB40030 */  sw    $s4, 0x30($sp)
/* 088B1C 80087F1C AFB3002C */  sw    $s3, 0x2c($sp)
/* 088B20 80087F20 AFB20028 */  sw    $s2, 0x28($sp)
/* 088B24 80087F24 AFB00020 */  sw    $s0, 0x20($sp)
/* 088B28 80087F28 AFBE0040 */  sw    $fp, 0x40($sp)
/* 088B2C 80087F2C AFB7003C */  sw    $s7, 0x3c($sp)
/* 088B30 80087F30 AFB60038 */  sw    $s6, 0x38($sp)
/* 088B34 80087F34 AFB50034 */  sw    $s5, 0x34($sp)
/* 088B38 80087F38 AFB10024 */  sw    $s1, 0x24($sp)
/* 088B3C 80087F3C 3C108012 */  lui   $s0, %hi(sControllerPakIssueNotFound) # $s0, 0x8012
/* 088B40 80087F40 3C128012 */  lui   $s2, %hi(sControllerPakFatalErrorFound) # $s2, 0x8012
/* 088B44 80087F44 3C138012 */  lui   $s3, %hi(sControllerPakNoFreeSpace) # $s3, 0x8012
/* 088B48 80087F48 3C148012 */  lui   $s4, %hi(sControllerPakBadData) # $s4, 0x8012
/* 088B4C 80087F4C AFBF0044 */  sw    $ra, 0x44($sp)
/* 088B50 80087F50 AFA40090 */  sw    $a0, 0x90($sp)
/* 088B54 80087F54 AFA50094 */  sw    $a1, 0x94($sp)
/* 088B58 80087F58 0000B025 */  move  $s6, $zero
/* 088B5C 80087F5C 0000B825 */  move  $s7, $zero
/* 088B60 80087F60 00001825 */  move  $v1, $zero
/* 088B64 80087F64 0000F025 */  move  $fp, $zero
/* 088B68 80087F68 26946A3C */  addiu $s4, %lo(sControllerPakBadData) # addiu $s4, $s4, 0x6a3c
/* 088B6C 80087F6C 26736A38 */  addiu $s3, %lo(sControllerPakNoFreeSpace) # addiu $s3, $s3, 0x6a38
/* 088B70 80087F70 26526A34 */  addiu $s2, %lo(sControllerPakFatalErrorFound) # addiu $s2, $s2, 0x6a34
/* 088B74 80087F74 26106A30 */  addiu $s0, %lo(sControllerPakIssueNotFound) # addiu $s0, $s0, 0x6a30
/* 088B78 80087F78 00008825 */  move  $s1, $zero
/* 088B7C 80087F7C 24150001 */  li    $s5, 1
.L80087F80:
/* 088B80 80087F80 A2400000 */  sb    $zero, ($s2)
/* 088B84 80087F84 A2600000 */  sb    $zero, ($s3)
/* 088B88 80087F88 A2800000 */  sb    $zero, ($s4)
/* 088B8C 80087F8C 02202025 */  move  $a0, $s1
/* 088B90 80087F90 27A50074 */  addiu $a1, $sp, 0x74
/* 088B94 80087F94 27A60070 */  addiu $a2, $sp, 0x70
/* 088B98 80087F98 0C01D865 */  jal   get_free_space
/* 088B9C 80087F9C AFA30064 */   sw    $v1, 0x64($sp)
/* 088BA0 80087FA0 8FA30064 */  lw    $v1, 0x64($sp)
/* 088BA4 80087FA4 14400012 */  bnez  $v0, .L80087FF0
/* 088BA8 80087FA8 304A00FF */   andi  $t2, $v0, 0xff
/* 088BAC 80087FAC 8FAE0074 */  lw    $t6, 0x74($sp)
/* 088BB0 80087FB0 A2150000 */  sb    $s5, ($s0)
/* 088BB4 80087FB4 11C00005 */  beqz  $t6, .L80087FCC
/* 088BB8 80087FB8 3C188012 */   lui   $t8, %hi(sControllerPakDataPresent) # $t8, 0x8012
/* 088BBC 80087FBC 8FAF0070 */  lw    $t7, 0x70($sp)
/* 088BC0 80087FC0 00000000 */  nop   
/* 088BC4 80087FC4 15E00008 */  bnez  $t7, .L80087FE8
/* 088BC8 80087FC8 00000000 */   nop   
.L80087FCC:
/* 088BCC 80087FCC A2750000 */  sb    $s5, ($s3)
/* 088BD0 80087FD0 0311C021 */  addu  $t8, $t8, $s1
/* 088BD4 80087FD4 93186A60 */  lbu   $t8, %lo(sControllerPakDataPresent)($t8)
/* 088BD8 80087FD8 00000000 */  nop   
/* 088BDC 80087FDC 17000002 */  bnez  $t8, .L80087FE8
/* 088BE0 80087FE0 00000000 */   nop   
/* 088BE4 80087FE4 26F70001 */  addiu $s7, $s7, 1
.L80087FE8:
/* 088BE8 80087FE8 10000014 */  b     .L8008803C
/* 088BEC 80087FEC 27DE0001 */   addiu $fp, $fp, 1
.L80087FF0:
/* 088BF0 80087FF0 24010009 */  li    $at, 9
/* 088BF4 80087FF4 15410003 */  bne   $t2, $at, .L80088004
/* 088BF8 80087FF8 A2000000 */   sb    $zero, ($s0)
/* 088BFC 80087FFC A2950000 */  sb    $s5, ($s4)
/* 088C00 80088000 24630001 */  addiu $v1, $v1, 1
.L80088004:
/* 088C04 80088004 24010002 */  li    $at, 2
/* 088C08 80088008 15410007 */  bne   $t2, $at, .L80088028
/* 088C0C 8008800C 02202025 */   move  $a0, $s1
/* 088C10 80088010 AFA30064 */  sw    $v1, 0x64($sp)
/* 088C14 80088014 0C01D74E */  jal   repair_controller_pak
/* 088C18 80088018 AFAA0078 */   sw    $t2, 0x78($sp)
/* 088C1C 8008801C 8FA30064 */  lw    $v1, 0x64($sp)
/* 088C20 80088020 8FAA0078 */  lw    $t2, 0x78($sp)
/* 088C24 80088024 00000000 */  nop   
.L80088028:
/* 088C28 80088028 24010003 */  li    $at, 3
/* 088C2C 8008802C 15410003 */  bne   $t2, $at, .L8008803C
/* 088C30 80088030 00000000 */   nop   
/* 088C34 80088034 A2550000 */  sb    $s5, ($s2)
/* 088C38 80088038 26D60001 */  addiu $s6, $s6, 1
.L8008803C:
/* 088C3C 8008803C 26310001 */  addiu $s1, $s1, 1
/* 088C40 80088040 26520001 */  addiu $s2, $s2, 1
/* 088C44 80088044 26730001 */  addiu $s3, $s3, 1
/* 088C48 80088048 26940001 */  addiu $s4, $s4, 1
/* 088C4C 8008804C 1A20FFCC */  blez  $s1, .L80087F80
/* 088C50 80088050 26100001 */   addiu $s0, $s0, 1
/* 088C54 80088054 13C00007 */  beqz  $fp, .L80088074
/* 088C58 80088058 00000000 */   nop   
/* 088C5C 8008805C 16C00005 */  bnez  $s6, .L80088074
/* 088C60 80088060 00000000 */   nop   
/* 088C64 80088064 16E00003 */  bnez  $s7, .L80088074
/* 088C68 80088068 00000000 */   nop   
/* 088C6C 8008806C 10600003 */  beqz  $v1, .L8008807C
/* 088C70 80088070 24050010 */   li    $a1, 16
.L80088074:
/* 088C74 80088074 100000A1 */  b     .L800882FC
/* 088C78 80088078 24020001 */   li    $v0, 1
.L8008807C:
/* 088C7C 8008807C 8FB90090 */  lw    $t9, 0x90($sp)
/* 088C80 80088080 3C068012 */  lui   $a2, %hi(sCurrentControllerPakAllFileNames) # $a2, 0x8012
/* 088C84 80088084 8F220000 */  lw    $v0, ($t9)
/* 088C88 80088088 24C66AE0 */  addiu $a2, %lo(sCurrentControllerPakAllFileNames) # addiu $a2, $a2, 0x6ae0
/* 088C8C 8008808C 0441000F */  bgez  $v0, .L800880CC
/* 088C90 80088090 00408825 */   move  $s1, $v0
/* 088C94 80088094 3C0E8012 */  lui   $t6, %hi(sControllerPakIssueNotFound) # $t6, 0x8012
/* 088C98 80088098 25CE6A30 */  addiu $t6, %lo(sControllerPakIssueNotFound) # addiu $t6, $t6, 0x6a30
/* 088C9C 8008809C 022E8021 */  addu  $s0, $s1, $t6
.L800880A0:
/* 088CA0 800880A0 26310001 */  addiu $s1, $s1, 1
/* 088CA4 800880A4 1A200003 */  blez  $s1, .L800880B4
/* 088CA8 800880A8 26100001 */   addiu $s0, $s0, 1
/* 088CAC 800880AC 2631FFFF */  addiu $s1, $s1, -1
/* 088CB0 800880B0 2610FFFF */  addiu $s0, $s0, -1
.L800880B4:
/* 088CB4 800880B4 920F0000 */  lbu   $t7, ($s0)
/* 088CB8 800880B8 00000000 */  nop   
/* 088CBC 800880BC 11E0FFF8 */  beqz  $t7, .L800880A0
/* 088CC0 800880C0 00000000 */   nop   
/* 088CC4 800880C4 10000024 */  b     .L80088158
/* 088CC8 800880C8 8FAF0090 */   lw    $t7, 0x90($sp)
.L800880CC:
/* 088CCC 800880CC 3C188012 */  lui   $t8, %hi(sControllerPakIssueNotFound) # $t8, 0x8012
/* 088CD0 800880D0 0302C021 */  addu  $t8, $t8, $v0
/* 088CD4 800880D4 93186A30 */  lbu   $t8, %lo(sControllerPakIssueNotFound)($t8)
/* 088CD8 800880D8 8FB90094 */  lw    $t9, 0x94($sp)
/* 088CDC 800880DC 13000002 */  beqz  $t8, .L800880E8
/* 088CE0 800880E0 3C0E8012 */   lui   $t6, %hi(sControllerPakIssueNotFound) # $t6, 0x8012
/* 088CE4 800880E4 1B20000D */  blez  $t9, .L8008811C
.L800880E8:
/* 088CE8 800880E8 25CE6A30 */   addiu $t6, %lo(sControllerPakIssueNotFound) # addiu $t6, $t6, 0x6a30
/* 088CEC 800880EC 022E8021 */  addu  $s0, $s1, $t6
.L800880F0:
/* 088CF0 800880F0 26310001 */  addiu $s1, $s1, 1
/* 088CF4 800880F4 1A200003 */  blez  $s1, .L80088104
/* 088CF8 800880F8 26100001 */   addiu $s0, $s0, 1
/* 088CFC 800880FC 2631FFFF */  addiu $s1, $s1, -1
/* 088D00 80088100 2610FFFF */  addiu $s0, $s0, -1
.L80088104:
/* 088D04 80088104 920F0000 */  lbu   $t7, ($s0)
/* 088D08 80088108 00000000 */  nop   
/* 088D0C 8008810C 11E0FFF8 */  beqz  $t7, .L800880F0
/* 088D10 80088110 00000000 */   nop   
/* 088D14 80088114 10000010 */  b     .L80088158
/* 088D18 80088118 8FAF0090 */   lw    $t7, 0x90($sp)
.L8008811C:
/* 088D1C 8008811C 8FB80094 */  lw    $t8, 0x94($sp)
/* 088D20 80088120 3C198012 */  lui   $t9, %hi(sControllerPakIssueNotFound) # $t9, 0x8012
/* 088D24 80088124 0701000B */  bgez  $t8, .L80088154
/* 088D28 80088128 27396A30 */   addiu $t9, %lo(sControllerPakIssueNotFound) # addiu $t9, $t9, 0x6a30
/* 088D2C 8008812C 02398021 */  addu  $s0, $s1, $t9
.L80088130:
/* 088D30 80088130 2631FFFF */  addiu $s1, $s1, -1
/* 088D34 80088134 06210003 */  bgez  $s1, .L80088144
/* 088D38 80088138 2610FFFF */   addiu $s0, $s0, -1
/* 088D3C 8008813C 26310001 */  addiu $s1, $s1, 1
/* 088D40 80088140 26100001 */  addiu $s0, $s0, 1
.L80088144:
/* 088D44 80088144 920E0000 */  lbu   $t6, ($s0)
/* 088D48 80088148 00000000 */  nop   
/* 088D4C 8008814C 11C0FFF8 */  beqz  $t6, .L80088130
/* 088D50 80088150 00000000 */   nop   
.L80088154:
/* 088D54 80088154 8FAF0090 */  lw    $t7, 0x90($sp)
.L80088158:
/* 088D58 80088158 3C188012 */  lui   $t8, %hi(sCurrentControllerPakAllFileSizes) # $t8, 0x8012
/* 088D5C 8008815C 3C198012 */  lui   $t9, %hi(sCurrentControllerPakAllFileTypes) # $t9, 0x8012
/* 088D60 80088160 27396B60 */  addiu $t9, %lo(sCurrentControllerPakAllFileTypes) # addiu $t9, $t9, 0x6b60
/* 088D64 80088164 27186B70 */  addiu $t8, %lo(sCurrentControllerPakAllFileSizes) # addiu $t8, $t8, 0x6b70
/* 088D68 80088168 3C078012 */  lui   $a3, %hi(sCurrentControllerPakAllFileExtensions) # $a3, 0x8012
/* 088D6C 8008816C ADF10000 */  sw    $s1, ($t7)
/* 088D70 80088170 AFB90014 */  sw    $t9, 0x14($sp)
/* 088D74 80088174 AFB80010 */  sw    $t8, 0x10($sp)
/* 088D78 80088178 24E76B20 */  addiu $a3, %lo(sCurrentControllerPakAllFileExtensions) # addiu $a3, $a3, 0x6b20
/* 088D7C 8008817C 0C01D798 */  jal   get_controller_pak_file_list
/* 088D80 80088180 02202025 */   move  $a0, $s1
/* 088D84 80088184 1440005C */  bnez  $v0, .L800882F8
/* 088D88 80088188 00405025 */   move  $t2, $v0
/* 088D8C 8008818C 3C098012 */  lui   $t1, %hi(sCurrentControllerPakAllFileSizes) # $t1, 0x8012
/* 088D90 80088190 3C088012 */  lui   $t0, %hi(sCurrentControllerPakAllFileNames) # $t0, 0x8012
/* 088D94 80088194 3C058012 */  lui   $a1, %hi(gBootPakData) # $a1, 0x8012
/* 088D98 80088198 3C1F8012 */  lui   $ra, %hi(sCurrentControllerPakAllFileNames) # $ra, 0x8012
/* 088D9C 8008819C 27FF6AE0 */  addiu $ra, %lo(sCurrentControllerPakAllFileNames) # addiu $ra, $ra, 0x6ae0
/* 088DA0 800881A0 24A56AA0 */  addiu $a1, %lo(gBootPakData) # addiu $a1, $a1, 0x6aa0
/* 088DA4 800881A4 25086AE0 */  addiu $t0, %lo(sCurrentControllerPakAllFileNames) # addiu $t0, $t0, 0x6ae0
/* 088DA8 800881A8 25296B70 */  addiu $t1, %lo(sCurrentControllerPakAllFileSizes) # addiu $t1, $t1, 0x6b70
/* 088DAC 800881AC 00005825 */  move  $t3, $zero
/* 088DB0 800881B0 240D002D */  li    $t5, 45
/* 088DB4 800881B4 240C002E */  li    $t4, 46
.L800881B8:
/* 088DB8 800881B8 8D2E0000 */  lw    $t6, ($t1)
/* 088DBC 800881BC 8D070000 */  lw    $a3, ($t0)
/* 088DC0 800881C0 000E7A02 */  srl   $t7, $t6, 8
/* 088DC4 800881C4 AD2F0000 */  sw    $t7, ($t1)
/* 088DC8 800881C8 10E00030 */  beqz  $a3, .L8008828C
/* 088DCC 800881CC 00002025 */   move  $a0, $zero
/* 088DD0 800881D0 90F90000 */  lbu   $t9, ($a3)
/* 088DD4 800881D4 3C188012 */  lui   $t8, %hi(sCurrentControllerPakAllFileExtensions) # $t8, 0x8012
/* 088DD8 800881D8 27186B20 */  addiu $t8, %lo(sCurrentControllerPakAllFileExtensions) # addiu $t8, $t8, 0x6b20
/* 088DDC 800881DC 00001025 */  move  $v0, $zero
/* 088DE0 800881E0 1320000D */  beqz  $t9, .L80088218
/* 088DE4 800881E4 01783021 */   addu  $a2, $t3, $t8
/* 088DE8 800881E8 332300FF */  andi  $v1, $t9, 0xff
.L800881EC:
/* 088DEC 800881EC 8CAE0000 */  lw    $t6, ($a1)
/* 088DF0 800881F0 24420001 */  addiu $v0, $v0, 1
/* 088DF4 800881F4 01C47821 */  addu  $t7, $t6, $a0
/* 088DF8 800881F8 A1E30000 */  sb    $v1, ($t7)
/* 088DFC 800881FC 8D180000 */  lw    $t8, ($t0)
/* 088E00 80088200 24840001 */  addiu $a0, $a0, 1
/* 088E04 80088204 0302C821 */  addu  $t9, $t8, $v0
/* 088E08 80088208 93230000 */  lbu   $v1, ($t9)
/* 088E0C 8008820C 00000000 */  nop   
/* 088E10 80088210 1460FFF6 */  bnez  $v1, .L800881EC
/* 088E14 80088214 00000000 */   nop   
.L80088218:
/* 088E18 80088218 8CC70000 */  lw    $a3, ($a2)
/* 088E1C 8008821C 00000000 */  nop   
/* 088E20 80088220 10E0001A */  beqz  $a3, .L8008828C
/* 088E24 80088224 00000000 */   nop   
/* 088E28 80088228 90EE0000 */  lbu   $t6, ($a3)
/* 088E2C 8008822C 00000000 */  nop   
/* 088E30 80088230 11C00016 */  beqz  $t6, .L8008828C
/* 088E34 80088234 00000000 */   nop   
/* 088E38 80088238 8CAF0000 */  lw    $t7, ($a1)
/* 088E3C 8008823C 00001025 */  move  $v0, $zero
/* 088E40 80088240 01E4C021 */  addu  $t8, $t7, $a0
/* 088E44 80088244 A30C0000 */  sb    $t4, ($t8)
/* 088E48 80088248 8CC70000 */  lw    $a3, ($a2)
/* 088E4C 8008824C 24840001 */  addiu $a0, $a0, 1
/* 088E50 80088250 90F90000 */  lbu   $t9, ($a3)
/* 088E54 80088254 00000000 */  nop   
/* 088E58 80088258 1320000C */  beqz  $t9, .L8008828C
/* 088E5C 8008825C 332300FF */   andi  $v1, $t9, 0xff
.L80088260:
/* 088E60 80088260 8CAE0000 */  lw    $t6, ($a1)
/* 088E64 80088264 24420001 */  addiu $v0, $v0, 1
/* 088E68 80088268 01C47821 */  addu  $t7, $t6, $a0
/* 088E6C 8008826C A1E30000 */  sb    $v1, ($t7)
/* 088E70 80088270 8CD80000 */  lw    $t8, ($a2)
/* 088E74 80088274 24840001 */  addiu $a0, $a0, 1
/* 088E78 80088278 0302C821 */  addu  $t9, $t8, $v0
/* 088E7C 8008827C 93230000 */  lbu   $v1, ($t9)
/* 088E80 80088280 00000000 */  nop   
/* 088E84 80088284 1460FFF6 */  bnez  $v1, .L80088260
/* 088E88 80088288 00000000 */   nop   
.L8008828C:
/* 088E8C 8008828C 14800006 */  bnez  $a0, .L800882A8
/* 088E90 80088290 256B0004 */   addiu $t3, $t3, 4
/* 088E94 80088294 8CAE0000 */  lw    $t6, ($a1)
/* 088E98 80088298 00000000 */  nop   
/* 088E9C 8008829C 01C47821 */  addu  $t7, $t6, $a0
/* 088EA0 800882A0 A1ED0000 */  sb    $t5, ($t7)
/* 088EA4 800882A4 24840001 */  addiu $a0, $a0, 1
.L800882A8:
/* 088EA8 800882A8 8CB80000 */  lw    $t8, ($a1)
/* 088EAC 800882AC 24A50004 */  addiu $a1, $a1, 4
/* 088EB0 800882B0 0304C821 */  addu  $t9, $t8, $a0
/* 088EB4 800882B4 25290004 */  addiu $t1, $t1, 4
/* 088EB8 800882B8 25080004 */  addiu $t0, $t0, 4
/* 088EBC 800882BC 14BFFFBE */  bne   $a1, $ra, .L800881B8
/* 088EC0 800882C0 A3200000 */   sb    $zero, ($t9)
/* 088EC4 800882C4 0C01D859 */  jal   cpak_free_files
/* 088EC8 800882C8 AFAA0078 */   sw    $t2, 0x78($sp)
/* 088ECC 800882CC 8FAE0090 */  lw    $t6, 0x90($sp)
/* 088ED0 800882D0 3C108012 */  lui   $s0, %hi(sCurrentControllerPakFreeSpace) # $s0, 0x8012
/* 088ED4 800882D4 26106BB0 */  addiu $s0, %lo(sCurrentControllerPakFreeSpace) # addiu $s0, $s0, 0x6bb0
/* 088ED8 800882D8 8DC40000 */  lw    $a0, ($t6)
/* 088EDC 800882DC 02002825 */  move  $a1, $s0
/* 088EE0 800882E0 0C01D865 */  jal   get_free_space
/* 088EE4 800882E4 00003025 */   move  $a2, $zero
/* 088EE8 800882E8 8E0F0000 */  lw    $t7, ($s0)
/* 088EEC 800882EC 8FAA0078 */  lw    $t2, 0x78($sp)
/* 088EF0 800882F0 000FC202 */  srl   $t8, $t7, 8
/* 088EF4 800882F4 AE180000 */  sw    $t8, ($s0)
.L800882F8:
/* 088EF8 800882F8 01401025 */  move  $v0, $t2
.L800882FC:
/* 088EFC 800882FC 8FBF0044 */  lw    $ra, 0x44($sp)
/* 088F00 80088300 8FB00020 */  lw    $s0, 0x20($sp)
/* 088F04 80088304 8FB10024 */  lw    $s1, 0x24($sp)
/* 088F08 80088308 8FB20028 */  lw    $s2, 0x28($sp)
/* 088F0C 8008830C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 088F10 80088310 8FB40030 */  lw    $s4, 0x30($sp)
/* 088F14 80088314 8FB50034 */  lw    $s5, 0x34($sp)
/* 088F18 80088318 8FB60038 */  lw    $s6, 0x38($sp)
/* 088F1C 8008831C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 088F20 80088320 8FBE0040 */  lw    $fp, 0x40($sp)
/* 088F24 80088324 03E00008 */  jr    $ra
/* 088F28 80088328 27BD0090 */   addiu $sp, $sp, 0x90

