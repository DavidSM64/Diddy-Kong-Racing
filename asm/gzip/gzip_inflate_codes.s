glabel gzip_inflate_codes /* Official name: inflate_codes */
/* 0C7C40 800C7040 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0C7C44 800C7044 3C0B800F */  lui   $t3, %hi(gzip_mask_bits) # $t3, 0x800f
/* 0C7C48 800C7048 AFB20008 */  sw    $s2, 8($sp)
/* 0C7C4C 800C704C AFB10004 */  sw    $s1, 4($sp)
/* 0C7C50 800C7050 AFB00000 */  sw    $s0, ($sp)
/* 0C7C54 800C7054 256B948C */  addiu $t3, %lo(gzip_mask_bits) # addiu $t3, $t3, -0x6b74
/* 0C7C58 800C7058 00061040 */  sll   $v0, $a2, 1
/* 0C7C5C 800C705C 00074040 */  sll   $t0, $a3, 1
/* 0C7C60 800C7060 3C12800E */  lui   $s2, %hi(gzip_inflate_input) # $s2, 0x800e
/* 0C7C64 800C7064 3C11800E */  lui   $s1, %hi(gzip_inflate_output) # $s1, 0x800e
/* 0C7C68 800C7068 3C198013 */  lui   $t9, %hi(gzip_bit_buffer) # $t9, 0x8013
/* 0C7C6C 800C706C 3C108013 */  lui   $s0, %hi(gzip_num_bits) # $s0, 0x8013
/* 0C7C70 800C7070 01621821 */  addu  $v1, $t3, $v0
/* 0C7C74 800C7074 01684821 */  addu  $t1, $t3, $t0
/* 0C7C78 800C7078 8E523768 */  lw    $s2, %lo(gzip_inflate_input)($s2)
/* 0C7C7C 800C707C 8E31376C */  lw    $s1, %lo(gzip_inflate_output)($s1)
/* 0C7C80 800C7080 8F39AAD0 */  lw    $t9, %lo(gzip_bit_buffer)($t9)
/* 0C7C84 800C7084 8E10AAD4 */  lw    $s0, %lo(gzip_num_bits)($s0)
/* 0C7C88 800C7088 946D0000 */  lhu   $t5, ($v1)
/* 0C7C8C 800C708C 952C0000 */  lhu   $t4, ($t1)
.L800C7090:
/* 0C7C90 800C7090 0206082B */  sltu  $at, $s0, $a2
.L800C7094:
/* 0C7C94 800C7094 50200009 */  beql  $at, $zero, .L800C70BC
/* 0C7C98 800C7098 032D1024 */   and   $v0, $t9, $t5
.L800C709C:
/* 0C7C9C 800C709C 92420000 */  lbu   $v0, ($s2)
/* 0C7CA0 800C70A0 26520001 */  addiu $s2, $s2, 1
/* 0C7CA4 800C70A4 02021004 */  sllv  $v0, $v0, $s0
/* 0C7CA8 800C70A8 26100008 */  addiu $s0, $s0, 8
/* 0C7CAC 800C70AC 0206082A */  slt   $at, $s0, $a2
/* 0C7CB0 800C70B0 1420FFFA */  bnez  $at, .L800C709C
/* 0C7CB4 800C70B4 0322C825 */   or    $t9, $t9, $v0
/* 0C7CB8 800C70B8 032D1024 */  and   $v0, $t9, $t5
.L800C70BC:
/* 0C7CBC 800C70BC 000210C0 */  sll   $v0, $v0, 3
/* 0C7CC0 800C70C0 00827821 */  addu  $t7, $a0, $v0
/* 0C7CC4 800C70C4 91F80000 */  lbu   $t8, ($t7)
/* 0C7CC8 800C70C8 2B010011 */  slti  $at, $t8, 0x11
/* 0C7CCC 800C70CC 5420001A */  bnezl $at, .L800C7138
/* 0C7CD0 800C70D0 91E20001 */   lbu   $v0, 1($t7)
/* 0C7CD4 800C70D4 81E30001 */  lb    $v1, 1($t7)
.L800C70D8:
/* 0C7CD8 800C70D8 2318FFF0 */  addi  $t8, $t8, -0x10
/* 0C7CDC 800C70DC 02038022 */  sub   $s0, $s0, $v1
/* 0C7CE0 800C70E0 0218082B */  sltu  $at, $s0, $t8
/* 0C7CE4 800C70E4 10200008 */  beqz  $at, .L800C7108
/* 0C7CE8 800C70E8 0079C806 */   srlv  $t9, $t9, $v1
.L800C70EC:
/* 0C7CEC 800C70EC 92420000 */  lbu   $v0, ($s2)
/* 0C7CF0 800C70F0 26520001 */  addiu $s2, $s2, 1
/* 0C7CF4 800C70F4 02021004 */  sllv  $v0, $v0, $s0
/* 0C7CF8 800C70F8 26100008 */  addiu $s0, $s0, 8
/* 0C7CFC 800C70FC 0218082A */  slt   $at, $s0, $t8
/* 0C7D00 800C7100 1420FFFA */  bnez  $at, .L800C70EC
/* 0C7D04 800C7104 0322C825 */   or    $t9, $t9, $v0
.L800C7108:
/* 0C7D08 800C7108 00181040 */  sll   $v0, $t8, 1
/* 0C7D0C 800C710C 004B1021 */  addu  $v0, $v0, $t3
/* 0C7D10 800C7110 94490000 */  lhu   $t1, ($v0)
/* 0C7D14 800C7114 8DE80004 */  lw    $t0, 4($t7)
/* 0C7D18 800C7118 01394824 */  and   $t1, $t1, $t9
/* 0C7D1C 800C711C 000948C0 */  sll   $t1, $t1, 3
/* 0C7D20 800C7120 01097820 */  add   $t7, $t0, $t1
/* 0C7D24 800C7124 91F80000 */  lbu   $t8, ($t7)
/* 0C7D28 800C7128 2F010011 */  sltiu $at, $t8, 0x11
/* 0C7D2C 800C712C 5020FFEA */  beql  $at, $zero, .L800C70D8
/* 0C7D30 800C7130 81E30001 */   lb    $v1, 1($t7)
/* 0C7D34 800C7134 91E20001 */  lbu   $v0, 1($t7)
.L800C7138:
/* 0C7D38 800C7138 24010010 */  li    $at, 16
/* 0C7D3C 800C713C 0059C806 */  srlv  $t9, $t9, $v0
/* 0C7D40 800C7140 17010005 */  bne   $t8, $at, .L800C7158
/* 0C7D44 800C7144 02028022 */   sub   $s0, $s0, $v0
/* 0C7D48 800C7148 95E20004 */  lhu   $v0, 4($t7)
/* 0C7D4C 800C714C 26310001 */  addiu $s1, $s1, 1
/* 0C7D50 800C7150 08031C24 */  j     .L800C7090
/* 0C7D54 800C7154 A222FFFF */   sb    $v0, -1($s1)
.L800C7158:
/* 0C7D58 800C7158 2401000F */  li    $at, 15
/* 0C7D5C 800C715C 13010068 */  beq   $t8, $at, .L800C7300
/* 0C7D60 800C7160 0218082B */   sltu  $at, $s0, $t8
/* 0C7D64 800C7164 50200009 */  beql  $at, $zero, .L800C718C
/* 0C7D68 800C7168 00181040 */   sll   $v0, $t8, 1
.L800C716C:
/* 0C7D6C 800C716C 92420000 */  lbu   $v0, ($s2)
/* 0C7D70 800C7170 26520001 */  addiu $s2, $s2, 1
/* 0C7D74 800C7174 02021004 */  sllv  $v0, $v0, $s0
/* 0C7D78 800C7178 26100008 */  addiu $s0, $s0, 8
/* 0C7D7C 800C717C 0218082A */  slt   $at, $s0, $t8
/* 0C7D80 800C7180 1420FFFA */  bnez  $at, .L800C716C
/* 0C7D84 800C7184 0322C825 */   or    $t9, $t9, $v0
/* 0C7D88 800C7188 00181040 */  sll   $v0, $t8, 1
.L800C718C:
/* 0C7D8C 800C718C 004B1021 */  addu  $v0, $v0, $t3
/* 0C7D90 800C7190 94490000 */  lhu   $t1, ($v0)
/* 0C7D94 800C7194 95E80004 */  lhu   $t0, 4($t7)
/* 0C7D98 800C7198 02188022 */  sub   $s0, $s0, $t8
/* 0C7D9C 800C719C 0207082B */  sltu  $at, $s0, $a3
/* 0C7DA0 800C71A0 01394824 */  and   $t1, $t1, $t9
/* 0C7DA4 800C71A4 0319C806 */  srlv  $t9, $t9, $t8
/* 0C7DA8 800C71A8 10200008 */  beqz  $at, .L800C71CC
/* 0C7DAC 800C71AC 01097021 */   addu  $t6, $t0, $t1
.L800C71B0:
/* 0C7DB0 800C71B0 92420000 */  lbu   $v0, ($s2)
/* 0C7DB4 800C71B4 26520001 */  addiu $s2, $s2, 1
/* 0C7DB8 800C71B8 02021004 */  sllv  $v0, $v0, $s0
/* 0C7DBC 800C71BC 26100008 */  addiu $s0, $s0, 8
/* 0C7DC0 800C71C0 0207082A */  slt   $at, $s0, $a3
/* 0C7DC4 800C71C4 1420FFFA */  bnez  $at, .L800C71B0
/* 0C7DC8 800C71C8 0322C825 */   or    $t9, $t9, $v0
.L800C71CC:
/* 0C7DCC 800C71CC 01991024 */  and   $v0, $t4, $t9
/* 0C7DD0 800C71D0 000210C0 */  sll   $v0, $v0, 3
/* 0C7DD4 800C71D4 00A27821 */  addu  $t7, $a1, $v0
/* 0C7DD8 800C71D8 91F80000 */  lbu   $t8, ($t7)
/* 0C7DDC 800C71DC 2B010011 */  slti  $at, $t8, 0x11
/* 0C7DE0 800C71E0 5420001A */  bnezl $at, .L800C724C
/* 0C7DE4 800C71E4 91E20001 */   lbu   $v0, 1($t7)
/* 0C7DE8 800C71E8 91E80001 */  lbu   $t0, 1($t7)
.L800C71EC:
/* 0C7DEC 800C71EC 2318FFF0 */  addi  $t8, $t8, -0x10
/* 0C7DF0 800C71F0 02088022 */  sub   $s0, $s0, $t0
/* 0C7DF4 800C71F4 0218082B */  sltu  $at, $s0, $t8
/* 0C7DF8 800C71F8 10200008 */  beqz  $at, .L800C721C
/* 0C7DFC 800C71FC 0119C806 */   srlv  $t9, $t9, $t0
.L800C7200:
/* 0C7E00 800C7200 92420000 */  lbu   $v0, ($s2)
/* 0C7E04 800C7204 26520001 */  addiu $s2, $s2, 1
/* 0C7E08 800C7208 02021004 */  sllv  $v0, $v0, $s0
/* 0C7E0C 800C720C 26100008 */  addiu $s0, $s0, 8
/* 0C7E10 800C7210 0218082A */  slt   $at, $s0, $t8
/* 0C7E14 800C7214 1420FFFA */  bnez  $at, .L800C7200
/* 0C7E18 800C7218 0322C825 */   or    $t9, $t9, $v0
.L800C721C:
/* 0C7E1C 800C721C 00181040 */  sll   $v0, $t8, 1
/* 0C7E20 800C7220 004B1021 */  addu  $v0, $v0, $t3
/* 0C7E24 800C7224 94490000 */  lhu   $t1, ($v0)
/* 0C7E28 800C7228 8DE80004 */  lw    $t0, 4($t7)
/* 0C7E2C 800C722C 01394824 */  and   $t1, $t1, $t9
/* 0C7E30 800C7230 000948C0 */  sll   $t1, $t1, 3
/* 0C7E34 800C7234 01097821 */  addu  $t7, $t0, $t1
/* 0C7E38 800C7238 91F80000 */  lbu   $t8, ($t7)
/* 0C7E3C 800C723C 2F010011 */  sltiu $at, $t8, 0x11
/* 0C7E40 800C7240 5020FFEA */  beql  $at, $zero, .L800C71EC
/* 0C7E44 800C7244 91E80001 */   lbu   $t0, 1($t7)
/* 0C7E48 800C7248 91E20001 */  lbu   $v0, 1($t7)
.L800C724C:
/* 0C7E4C 800C724C 02028022 */  sub   $s0, $s0, $v0
/* 0C7E50 800C7250 0218082B */  sltu  $at, $s0, $t8
/* 0C7E54 800C7254 10200008 */  beqz  $at, .L800C7278
/* 0C7E58 800C7258 0059C806 */   srlv  $t9, $t9, $v0
.L800C725C:
/* 0C7E5C 800C725C 92420000 */  lbu   $v0, ($s2)
/* 0C7E60 800C7260 26520001 */  addiu $s2, $s2, 1
/* 0C7E64 800C7264 02021004 */  sllv  $v0, $v0, $s0
/* 0C7E68 800C7268 26100008 */  addiu $s0, $s0, 8
/* 0C7E6C 800C726C 0218082A */  slt   $at, $s0, $t8
/* 0C7E70 800C7270 1420FFFA */  bnez  $at, .L800C725C
/* 0C7E74 800C7274 0322C825 */   or    $t9, $t9, $v0
.L800C7278:
/* 0C7E78 800C7278 00181040 */  sll   $v0, $t8, 1
/* 0C7E7C 800C727C 004B1021 */  addu  $v0, $v0, $t3
/* 0C7E80 800C7280 94490000 */  lhu   $t1, ($v0)
/* 0C7E84 800C7284 95E30004 */  lhu   $v1, 4($t7)
/* 0C7E88 800C7288 31C20003 */  andi  $v0, $t6, 3
/* 0C7E8C 800C728C 01394824 */  and   $t1, $t1, $t9
/* 0C7E90 800C7290 02234022 */  sub   $t0, $s1, $v1
/* 0C7E94 800C7294 01094022 */  sub   $t0, $t0, $t1
/* 0C7E98 800C7298 0319C806 */  srlv  $t9, $t9, $t8
/* 0C7E9C 800C729C 1040000A */  beqz  $v0, .L800C72C8
/* 0C7EA0 800C72A0 02188022 */   sub   $s0, $s0, $t8
/* 0C7EA4 800C72A4 01C27022 */  sub   $t6, $t6, $v0
.L800C72A8:
/* 0C7EA8 800C72A8 910A0000 */  lbu   $t2, ($t0)
/* 0C7EAC 800C72AC 2042FFFF */  addi  $v0, $v0, -1
/* 0C7EB0 800C72B0 21080001 */  addi  $t0, $t0, 1
/* 0C7EB4 800C72B4 22310001 */  addi  $s1, $s1, 1
/* 0C7EB8 800C72B8 1440FFFB */  bnez  $v0, .L800C72A8
/* 0C7EBC 800C72BC A22AFFFF */   sb    $t2, -1($s1)
/* 0C7EC0 800C72C0 51C0FF74 */  beql  $t6, $zero, .L800C7094
/* 0C7EC4 800C72C4 0206082B */   sltu  $at, $s0, $a2
.L800C72C8:
/* 0C7EC8 800C72C8 91020000 */  lbu   $v0, ($t0)
/* 0C7ECC 800C72CC 25CEFFFC */  addiu $t6, $t6, -4
/* 0C7ED0 800C72D0 25080004 */  addiu $t0, $t0, 4
/* 0C7ED4 800C72D4 A2220000 */  sb    $v0, ($s1)
/* 0C7ED8 800C72D8 9103FFFD */  lbu   $v1, -3($t0)
/* 0C7EDC 800C72DC 26310004 */  addiu $s1, $s1, 4
/* 0C7EE0 800C72E0 A223FFFD */  sb    $v1, -3($s1)
/* 0C7EE4 800C72E4 9109FFFE */  lbu   $t1, -2($t0)
/* 0C7EE8 800C72E8 A229FFFE */  sb    $t1, -2($s1)
/* 0C7EEC 800C72EC 910AFFFF */  lbu   $t2, -1($t0)
/* 0C7EF0 800C72F0 15C0FFF5 */  bnez  $t6, .L800C72C8
/* 0C7EF4 800C72F4 A22AFFFF */   sb    $t2, -1($s1)
/* 0C7EF8 800C72F8 08031C24 */  j     .L800C7090
/* 0C7EFC 800C72FC 00000000 */   nop   
.L800C7300:
/* 0C7F00 800C7300 3C01800E */  lui   $at, %hi(gzip_inflate_input) # $at, 0x800e
/* 0C7F04 800C7304 AC323768 */  sw    $s2, %lo(gzip_inflate_input)($at)
/* 0C7F08 800C7308 3C01800E */  lui   $at, %hi(gzip_inflate_output) # $at, 0x800e
/* 0C7F0C 800C730C AC31376C */  sw    $s1, %lo(gzip_inflate_output)($at)
/* 0C7F10 800C7310 3C018013 */  lui   $at, %hi(gzip_bit_buffer) # $at, 0x8013
/* 0C7F14 800C7314 AC39AAD0 */  sw    $t9, %lo(gzip_bit_buffer)($at)
/* 0C7F18 800C7318 3C018013 */  lui   $at, %hi(gzip_num_bits) # $at, 0x8013
/* 0C7F1C 800C731C AC30AAD4 */  sw    $s0, %lo(gzip_num_bits)($at)
/* 0C7F20 800C7320 8FB20008 */  lw    $s2, 8($sp)
/* 0C7F24 800C7324 8FB10004 */  lw    $s1, 4($sp)
/* 0C7F28 800C7328 8FB00000 */  lw    $s0, ($sp)
/* 0C7F2C 800C732C 03E00008 */  jr    $ra
/* 0C7F30 800C7330 27BD0010 */   addiu $sp, $sp, 0x10
/* 0C7F34 800C7334 00000000 */  nop   
/* 0C7F38 800C7338 00000000 */  nop   
/* 0C7F3C 800C733C 00000000 */  nop   

