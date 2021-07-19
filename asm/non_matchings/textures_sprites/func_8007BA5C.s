glabel func_8007BA5C
/* 07C65C 8007BA5C 27BDFF90 */  addiu $sp, $sp, -0x70
/* 07C660 8007BA60 10E0000D */  beqz  $a3, .L8007BA98
/* 07C664 8007BA64 AFA60078 */   sw    $a2, 0x78($sp)
/* 07C668 8007BA68 94AE0012 */  lhu   $t6, 0x12($a1)
/* 07C66C 8007BA6C 00000000 */  nop   
/* 07C670 8007BA70 000E7A00 */  sll   $t7, $t6, 8
/* 07C674 8007BA74 00EF082A */  slt   $at, $a3, $t7
/* 07C678 8007BA78 10200007 */  beqz  $at, .L8007BA98
/* 07C67C 8007BA7C 00000000 */   nop   
/* 07C680 8007BA80 84B90016 */  lh    $t9, 0x16($a1)
/* 07C684 8007BA84 0007C403 */  sra   $t8, $a3, 0x10
/* 07C688 8007BA88 03190019 */  multu $t8, $t9
/* 07C68C 8007BA8C 00007012 */  mflo  $t6
/* 07C690 8007BA90 00AE2821 */  addu  $a1, $a1, $t6
/* 07C694 8007BA94 00000000 */  nop   
.L8007BA98:
/* 07C698 8007BA98 90AF0000 */  lbu   $t7, ($a1)
/* 07C69C 8007BA9C 24010040 */  li    $at, 64
/* 07C6A0 8007BAA0 15E10073 */  bne   $t7, $at, .L8007BC70
/* 07C6A4 8007BAA4 3C06B700 */   lui   $a2, 0xb700
/* 07C6A8 8007BAA8 8C820000 */  lw    $v0, ($a0)
/* 07C6AC 8007BAAC 3C098000 */  lui   $t1, 0x8000
/* 07C6B0 8007BAB0 24580008 */  addiu $t8, $v0, 8
/* 07C6B4 8007BAB4 AC980000 */  sw    $t8, ($a0)
/* 07C6B8 8007BAB8 00A9C821 */  addu  $t9, $a1, $t1
/* 07C6BC 8007BABC 3C07FD10 */  lui   $a3, 0xfd10
/* 07C6C0 8007BAC0 272E0020 */  addiu $t6, $t9, 0x20
/* 07C6C4 8007BAC4 AC4E0004 */  sw    $t6, 4($v0)
/* 07C6C8 8007BAC8 AC470000 */  sw    $a3, ($v0)
/* 07C6CC 8007BACC 8C820000 */  lw    $v0, ($a0)
/* 07C6D0 8007BAD0 3C190701 */  lui   $t9, (0x07010060 >> 16) # lui $t9, 0x701
/* 07C6D4 8007BAD4 244F0008 */  addiu $t7, $v0, 8
/* 07C6D8 8007BAD8 AC8F0000 */  sw    $t7, ($a0)
/* 07C6DC 8007BADC 3C18F510 */  lui   $t8, (0xF5100100 >> 16) # lui $t8, 0xf510
/* 07C6E0 8007BAE0 37180100 */  ori   $t8, (0xF5100100 & 0xFFFF) # ori $t8, $t8, 0x100
/* 07C6E4 8007BAE4 37390060 */  ori   $t9, (0x07010060 & 0xFFFF) # ori $t9, $t9, 0x60
/* 07C6E8 8007BAE8 AC590004 */  sw    $t9, 4($v0)
/* 07C6EC 8007BAEC AC580000 */  sw    $t8, ($v0)
/* 07C6F0 8007BAF0 8C820000 */  lw    $v0, ($a0)
/* 07C6F4 8007BAF4 3C0AE600 */  lui   $t2, 0xe600
/* 07C6F8 8007BAF8 244E0008 */  addiu $t6, $v0, 8
/* 07C6FC 8007BAFC AC8E0000 */  sw    $t6, ($a0)
/* 07C700 8007BB00 AC400004 */  sw    $zero, 4($v0)
/* 07C704 8007BB04 AC4A0000 */  sw    $t2, ($v0)
/* 07C708 8007BB08 8C820000 */  lw    $v0, ($a0)
/* 07C70C 8007BB0C 3C18073F */  lui   $t8, (0x073FF080 >> 16) # lui $t8, 0x73f
/* 07C710 8007BB10 244F0008 */  addiu $t7, $v0, 8
/* 07C714 8007BB14 AC8F0000 */  sw    $t7, ($a0)
/* 07C718 8007BB18 3C0BF300 */  lui   $t3, 0xf300
/* 07C71C 8007BB1C 3718F080 */  ori   $t8, (0x073FF080 & 0xFFFF) # ori $t8, $t8, 0xf080
/* 07C720 8007BB20 AC580004 */  sw    $t8, 4($v0)
/* 07C724 8007BB24 AC4B0000 */  sw    $t3, ($v0)
/* 07C728 8007BB28 8C820000 */  lw    $v0, ($a0)
/* 07C72C 8007BB2C 3C08E700 */  lui   $t0, 0xe700
/* 07C730 8007BB30 24590008 */  addiu $t9, $v0, 8
/* 07C734 8007BB34 AC990000 */  sw    $t9, ($a0)
/* 07C738 8007BB38 AC400004 */  sw    $zero, 4($v0)
/* 07C73C 8007BB3C AC480000 */  sw    $t0, ($v0)
/* 07C740 8007BB40 8C820000 */  lw    $v0, ($a0)
/* 07C744 8007BB44 3C190101 */  lui   $t9, (0x01010060 >> 16) # lui $t9, 0x101
/* 07C748 8007BB48 AFA20050 */  sw    $v0, 0x50($sp)
/* 07C74C 8007BB4C 244E0008 */  addiu $t6, $v0, 8
/* 07C750 8007BB50 AC8E0000 */  sw    $t6, ($a0)
/* 07C754 8007BB54 8FB80050 */  lw    $t8, 0x50($sp)
/* 07C758 8007BB58 3C0FF510 */  lui   $t7, (0xF5102100 >> 16) # lui $t7, 0xf510
/* 07C75C 8007BB5C 35EF2100 */  ori   $t7, (0xF5102100 & 0xFFFF) # ori $t7, $t7, 0x2100
/* 07C760 8007BB60 37390060 */  ori   $t9, (0x01010060 & 0xFFFF) # ori $t9, $t9, 0x60
/* 07C764 8007BB64 AF190004 */  sw    $t9, 4($t8)
/* 07C768 8007BB68 AF0F0000 */  sw    $t7, ($t8)
/* 07C76C 8007BB6C 8C820000 */  lw    $v0, ($a0)
/* 07C770 8007BB70 3C19010F */  lui   $t9, (0x010FC03C >> 16) # lui $t9, 0x10f
/* 07C774 8007BB74 AFA2004C */  sw    $v0, 0x4c($sp)
/* 07C778 8007BB78 244E0008 */  addiu $t6, $v0, 8
/* 07C77C 8007BB7C AC8E0000 */  sw    $t6, ($a0)
/* 07C780 8007BB80 8FAF004C */  lw    $t7, 0x4c($sp)
/* 07C784 8007BB84 3739C03C */  ori   $t9, (0x010FC03C & 0xFFFF) # ori $t9, $t9, 0xc03c
/* 07C788 8007BB88 3C0CF200 */  lui   $t4, 0xf200
/* 07C78C 8007BB8C ADEC0000 */  sw    $t4, ($t7)
/* 07C790 8007BB90 ADF90004 */  sw    $t9, 4($t7)
/* 07C794 8007BB94 8C820000 */  lw    $v0, ($a0)
/* 07C798 8007BB98 00A97021 */  addu  $t6, $a1, $t1
/* 07C79C 8007BB9C 24580008 */  addiu $t8, $v0, 8
/* 07C7A0 8007BBA0 AC980000 */  sw    $t8, ($a0)
/* 07C7A4 8007BBA4 AC470000 */  sw    $a3, ($v0)
/* 07C7A8 8007BBA8 8FAD0078 */  lw    $t5, 0x78($sp)
/* 07C7AC 8007BBAC 25D90820 */  addiu $t9, $t6, 0x820
/* 07C7B0 8007BBB0 AC590004 */  sw    $t9, 4($v0)
/* 07C7B4 8007BBB4 8C820000 */  lw    $v0, ($a0)
/* 07C7B8 8007BBB8 3C0E0701 */  lui   $t6, (0x07010060 >> 16) # lui $t6, 0x701
/* 07C7BC 8007BBBC 244F0008 */  addiu $t7, $v0, 8
/* 07C7C0 8007BBC0 AC8F0000 */  sw    $t7, ($a0)
/* 07C7C4 8007BBC4 35CE0060 */  ori   $t6, (0x07010060 & 0xFFFF) # ori $t6, $t6, 0x60
/* 07C7C8 8007BBC8 3C18F510 */  lui   $t8, 0xf510
/* 07C7CC 8007BBCC AC580000 */  sw    $t8, ($v0)
/* 07C7D0 8007BBD0 AC4E0004 */  sw    $t6, 4($v0)
/* 07C7D4 8007BBD4 8C820000 */  lw    $v0, ($a0)
/* 07C7D8 8007BBD8 3C0E073F */  lui   $t6, (0x073FF080 >> 16) # lui $t6, 0x73f
/* 07C7DC 8007BBDC 24590008 */  addiu $t9, $v0, 8
/* 07C7E0 8007BBE0 AC990000 */  sw    $t9, ($a0)
/* 07C7E4 8007BBE4 AC400004 */  sw    $zero, 4($v0)
/* 07C7E8 8007BBE8 AC4A0000 */  sw    $t2, ($v0)
/* 07C7EC 8007BBEC 8C820000 */  lw    $v0, ($a0)
/* 07C7F0 8007BBF0 35CEF080 */  ori   $t6, (0x073FF080 & 0xFFFF) # ori $t6, $t6, 0xf080
/* 07C7F4 8007BBF4 AFA2003C */  sw    $v0, 0x3c($sp)
/* 07C7F8 8007BBF8 244F0008 */  addiu $t7, $v0, 8
/* 07C7FC 8007BBFC AC8F0000 */  sw    $t7, ($a0)
/* 07C800 8007BC00 8FB8003C */  lw    $t8, 0x3c($sp)
/* 07C804 8007BC04 00000000 */  nop   
/* 07C808 8007BC08 AF0B0000 */  sw    $t3, ($t8)
/* 07C80C 8007BC0C AF0E0004 */  sw    $t6, 4($t8)
/* 07C810 8007BC10 8C820000 */  lw    $v0, ($a0)
/* 07C814 8007BC14 3C18F510 */  lui   $t8, (0xF5102000 >> 16) # lui $t8, 0xf510
/* 07C818 8007BC18 AFA20038 */  sw    $v0, 0x38($sp)
/* 07C81C 8007BC1C 24590008 */  addiu $t9, $v0, 8
/* 07C820 8007BC20 AC990000 */  sw    $t9, ($a0)
/* 07C824 8007BC24 8FAF0038 */  lw    $t7, 0x38($sp)
/* 07C828 8007BC28 3C190001 */  lui   $t9, (0x00010060 >> 16) # lui $t9, 1
/* 07C82C 8007BC2C ADE80000 */  sw    $t0, ($t7)
/* 07C830 8007BC30 ADE00004 */  sw    $zero, 4($t7)
/* 07C834 8007BC34 8C820000 */  lw    $v0, ($a0)
/* 07C838 8007BC38 37390060 */  ori   $t9, (0x00010060 & 0xFFFF) # ori $t9, $t9, 0x60
/* 07C83C 8007BC3C 244E0008 */  addiu $t6, $v0, 8
/* 07C840 8007BC40 AC8E0000 */  sw    $t6, ($a0)
/* 07C844 8007BC44 37182000 */  ori   $t8, (0xF5102000 & 0xFFFF) # ori $t8, $t8, 0x2000
/* 07C848 8007BC48 AC580000 */  sw    $t8, ($v0)
/* 07C84C 8007BC4C AC590004 */  sw    $t9, 4($v0)
/* 07C850 8007BC50 8C820000 */  lw    $v0, ($a0)
/* 07C854 8007BC54 3C0E000F */  lui   $t6, (0x000FC03C >> 16) # lui $t6, 0xf
/* 07C858 8007BC58 244F0008 */  addiu $t7, $v0, 8
/* 07C85C 8007BC5C AC8F0000 */  sw    $t7, ($a0)
/* 07C860 8007BC60 35CEC03C */  ori   $t6, (0x000FC03C & 0xFFFF) # ori $t6, $t6, 0xc03c
/* 07C864 8007BC64 AC4E0004 */  sw    $t6, 4($v0)
/* 07C868 8007BC68 10000079 */  b     .L8007BE50
/* 07C86C 8007BC6C AC4C0000 */   sw    $t4, ($v0)
.L8007BC70:
/* 07C870 8007BC70 8C820000 */  lw    $v0, ($a0)
/* 07C874 8007BC74 3C098000 */  lui   $t1, 0x8000
/* 07C878 8007BC78 24580008 */  addiu $t8, $v0, 8
/* 07C87C 8007BC7C AC980000 */  sw    $t8, ($a0)
/* 07C880 8007BC80 00A9C821 */  addu  $t9, $a1, $t1
/* 07C884 8007BC84 3C07FD10 */  lui   $a3, 0xfd10
/* 07C888 8007BC88 272F0020 */  addiu $t7, $t9, 0x20
/* 07C88C 8007BC8C AC4F0004 */  sw    $t7, 4($v0)
/* 07C890 8007BC90 AC470000 */  sw    $a3, ($v0)
/* 07C894 8007BC94 8C820000 */  lw    $v0, ($a0)
/* 07C898 8007BC98 3C190701 */  lui   $t9, (0x07014050 >> 16) # lui $t9, 0x701
/* 07C89C 8007BC9C 244E0008 */  addiu $t6, $v0, 8
/* 07C8A0 8007BCA0 AC8E0000 */  sw    $t6, ($a0)
/* 07C8A4 8007BCA4 3C18F510 */  lui   $t8, (0xF5100100 >> 16) # lui $t8, 0xf510
/* 07C8A8 8007BCA8 37180100 */  ori   $t8, (0xF5100100 & 0xFFFF) # ori $t8, $t8, 0x100
/* 07C8AC 8007BCAC 37394050 */  ori   $t9, (0x07014050 & 0xFFFF) # ori $t9, $t9, 0x4050
/* 07C8B0 8007BCB0 AC590004 */  sw    $t9, 4($v0)
/* 07C8B4 8007BCB4 AC580000 */  sw    $t8, ($v0)
/* 07C8B8 8007BCB8 8C820000 */  lw    $v0, ($a0)
/* 07C8BC 8007BCBC 3C0AE600 */  lui   $t2, 0xe600
/* 07C8C0 8007BCC0 244F0008 */  addiu $t7, $v0, 8
/* 07C8C4 8007BCC4 AC8F0000 */  sw    $t7, ($a0)
/* 07C8C8 8007BCC8 AC400004 */  sw    $zero, 4($v0)
/* 07C8CC 8007BCCC AC4A0000 */  sw    $t2, ($v0)
/* 07C8D0 8007BCD0 8C820000 */  lw    $v0, ($a0)
/* 07C8D4 8007BCD4 3C0BF300 */  lui   $t3, 0xf300
/* 07C8D8 8007BCD8 244E0008 */  addiu $t6, $v0, 8
/* 07C8DC 8007BCDC AC8E0000 */  sw    $t6, ($a0)
/* 07C8E0 8007BCE0 3C18073F */  lui   $t8, (0x073FF100 >> 16) # lui $t8, 0x73f
/* 07C8E4 8007BCE4 AC4B0000 */  sw    $t3, ($v0)
/* 07C8E8 8007BCE8 8FAD0078 */  lw    $t5, 0x78($sp)
/* 07C8EC 8007BCEC 3718F100 */  ori   $t8, (0x073FF100 & 0xFFFF) # ori $t8, $t8, 0xf100
/* 07C8F0 8007BCF0 AC580004 */  sw    $t8, 4($v0)
/* 07C8F4 8007BCF4 8C820000 */  lw    $v0, ($a0)
/* 07C8F8 8007BCF8 3C08E700 */  lui   $t0, 0xe700
/* 07C8FC 8007BCFC AFA2001C */  sw    $v0, 0x1c($sp)
/* 07C900 8007BD00 24590008 */  addiu $t9, $v0, 8
/* 07C904 8007BD04 AC990000 */  sw    $t9, ($a0)
/* 07C908 8007BD08 8FAF001C */  lw    $t7, 0x1c($sp)
/* 07C90C 8007BD0C 3C18F510 */  lui   $t8, (0xF5101100 >> 16) # lui $t8, 0xf510
/* 07C910 8007BD10 ADE80000 */  sw    $t0, ($t7)
/* 07C914 8007BD14 ADE00004 */  sw    $zero, 4($t7)
/* 07C918 8007BD18 8C820000 */  lw    $v0, ($a0)
/* 07C91C 8007BD1C 3C0F0101 */  lui   $t7, (0x01014050 >> 16) # lui $t7, 0x101
/* 07C920 8007BD20 AFA20018 */  sw    $v0, 0x18($sp)
/* 07C924 8007BD24 244E0008 */  addiu $t6, $v0, 8
/* 07C928 8007BD28 AC8E0000 */  sw    $t6, ($a0)
/* 07C92C 8007BD2C 8FB90018 */  lw    $t9, 0x18($sp)
/* 07C930 8007BD30 35EF4050 */  ori   $t7, (0x01014050 & 0xFFFF) # ori $t7, $t7, 0x4050
/* 07C934 8007BD34 37181100 */  ori   $t8, (0xF5101100 & 0xFFFF) # ori $t8, $t8, 0x1100
/* 07C938 8007BD38 AF380000 */  sw    $t8, ($t9)
/* 07C93C 8007BD3C AF2F0004 */  sw    $t7, 4($t9)
/* 07C940 8007BD40 8C820000 */  lw    $v0, ($a0)
/* 07C944 8007BD44 3C0CF200 */  lui   $t4, 0xf200
/* 07C948 8007BD48 AFA20014 */  sw    $v0, 0x14($sp)
/* 07C94C 8007BD4C 244E0008 */  addiu $t6, $v0, 8
/* 07C950 8007BD50 AC8E0000 */  sw    $t6, ($a0)
/* 07C954 8007BD54 8FB80014 */  lw    $t8, 0x14($sp)
/* 07C958 8007BD58 3C0F0107 */  lui   $t7, (0x0107C07C >> 16) # lui $t7, 0x107
/* 07C95C 8007BD5C AF0C0000 */  sw    $t4, ($t8)
/* 07C960 8007BD60 8FB90014 */  lw    $t9, 0x14($sp)
/* 07C964 8007BD64 35EFC07C */  ori   $t7, (0x0107C07C & 0xFFFF) # ori $t7, $t7, 0xc07c
/* 07C968 8007BD68 AF2F0004 */  sw    $t7, 4($t9)
/* 07C96C 8007BD6C 8C820000 */  lw    $v0, ($a0)
/* 07C970 8007BD70 00A9C021 */  addu  $t8, $a1, $t1
/* 07C974 8007BD74 244E0008 */  addiu $t6, $v0, 8
/* 07C978 8007BD78 AC8E0000 */  sw    $t6, ($a0)
/* 07C97C 8007BD7C 270F0820 */  addiu $t7, $t8, 0x820
/* 07C980 8007BD80 AC4F0004 */  sw    $t7, 4($v0)
/* 07C984 8007BD84 AC470000 */  sw    $a3, ($v0)
/* 07C988 8007BD88 8C820000 */  lw    $v0, ($a0)
/* 07C98C 8007BD8C 3C180701 */  lui   $t8, (0x07014050 >> 16) # lui $t8, 0x701
/* 07C990 8007BD90 24590008 */  addiu $t9, $v0, 8
/* 07C994 8007BD94 AC990000 */  sw    $t9, ($a0)
/* 07C998 8007BD98 37184050 */  ori   $t8, (0x07014050 & 0xFFFF) # ori $t8, $t8, 0x4050
/* 07C99C 8007BD9C 3C0EF510 */  lui   $t6, 0xf510
/* 07C9A0 8007BDA0 AC4E0000 */  sw    $t6, ($v0)
/* 07C9A4 8007BDA4 AC580004 */  sw    $t8, 4($v0)
/* 07C9A8 8007BDA8 8C820000 */  lw    $v0, ($a0)
/* 07C9AC 8007BDAC 3C18073F */  lui   $t8, (0x073FF100 >> 16) # lui $t8, 0x73f
/* 07C9B0 8007BDB0 244F0008 */  addiu $t7, $v0, 8
/* 07C9B4 8007BDB4 AC8F0000 */  sw    $t7, ($a0)
/* 07C9B8 8007BDB8 AC400004 */  sw    $zero, 4($v0)
/* 07C9BC 8007BDBC AC4A0000 */  sw    $t2, ($v0)
/* 07C9C0 8007BDC0 8C820000 */  lw    $v0, ($a0)
/* 07C9C4 8007BDC4 3718F100 */  ori   $t8, (0x073FF100 & 0xFFFF) # ori $t8, $t8, 0xf100
/* 07C9C8 8007BDC8 AFA20004 */  sw    $v0, 4($sp)
/* 07C9CC 8007BDCC 24590008 */  addiu $t9, $v0, 8
/* 07C9D0 8007BDD0 AC990000 */  sw    $t9, ($a0)
/* 07C9D4 8007BDD4 8FAE0004 */  lw    $t6, 4($sp)
/* 07C9D8 8007BDD8 00000000 */  nop   
/* 07C9DC 8007BDDC ADCB0000 */  sw    $t3, ($t6)
/* 07C9E0 8007BDE0 8FAF0004 */  lw    $t7, 4($sp)
/* 07C9E4 8007BDE4 00000000 */  nop   
/* 07C9E8 8007BDE8 ADF80004 */  sw    $t8, 4($t7)
/* 07C9EC 8007BDEC 8C820000 */  lw    $v0, ($a0)
/* 07C9F0 8007BDF0 00000000 */  nop   
/* 07C9F4 8007BDF4 AFA20000 */  sw    $v0, ($sp)
/* 07C9F8 8007BDF8 24590008 */  addiu $t9, $v0, 8
/* 07C9FC 8007BDFC AC990000 */  sw    $t9, ($a0)
/* 07CA00 8007BE00 8FAE0000 */  lw    $t6, ($sp)
/* 07CA04 8007BE04 3C19F510 */  lui   $t9, (0xF5101000 >> 16) # lui $t9, 0xf510
/* 07CA08 8007BE08 ADC80000 */  sw    $t0, ($t6)
/* 07CA0C 8007BE0C 8FB80000 */  lw    $t8, ($sp)
/* 07CA10 8007BE10 3C0E0001 */  lui   $t6, (0x00014050 >> 16) # lui $t6, 1
/* 07CA14 8007BE14 AF000004 */  sw    $zero, 4($t8)
/* 07CA18 8007BE18 8C820000 */  lw    $v0, ($a0)
/* 07CA1C 8007BE1C 35CE4050 */  ori   $t6, (0x00014050 & 0xFFFF) # ori $t6, $t6, 0x4050
/* 07CA20 8007BE20 244F0008 */  addiu $t7, $v0, 8
/* 07CA24 8007BE24 AC8F0000 */  sw    $t7, ($a0)
/* 07CA28 8007BE28 37391000 */  ori   $t9, (0xF5101000 & 0xFFFF) # ori $t9, $t9, 0x1000
/* 07CA2C 8007BE2C AC590000 */  sw    $t9, ($v0)
/* 07CA30 8007BE30 AC4E0004 */  sw    $t6, 4($v0)
/* 07CA34 8007BE34 8C820000 */  lw    $v0, ($a0)
/* 07CA38 8007BE38 3C0F0007 */  lui   $t7, (0x0007C07C >> 16) # lui $t7, 7
/* 07CA3C 8007BE3C 24580008 */  addiu $t8, $v0, 8
/* 07CA40 8007BE40 AC980000 */  sw    $t8, ($a0)
/* 07CA44 8007BE44 35EFC07C */  ori   $t7, (0x0007C07C & 0xFFFF) # ori $t7, $t7, 0xc07c
/* 07CA48 8007BE48 AC4F0004 */  sw    $t7, 4($v0)
/* 07CA4C 8007BE4C AC4C0000 */  sw    $t4, ($v0)
.L8007BE50:
/* 07CA50 8007BE50 8C820000 */  lw    $v0, ($a0)
/* 07CA54 8007BE54 3C018012 */  lui   $at, %hi(D_8012637C) # $at, 0x8012
/* 07CA58 8007BE58 24590008 */  addiu $t9, $v0, 8
/* 07CA5C 8007BE5C AC990000 */  sw    $t9, ($a0)
/* 07CA60 8007BE60 AC400004 */  sw    $zero, 4($v0)
/* 07CA64 8007BE64 AC480000 */  sw    $t0, ($v0)
/* 07CA68 8007BE68 AC20637C */  sw    $zero, %lo(D_8012637C)($at)
/* 07CA6C 8007BE6C 8C820000 */  lw    $v0, ($a0)
/* 07CA70 8007BE70 31AE001F */  andi  $t6, $t5, 0x1f
/* 07CA74 8007BE74 24580008 */  addiu $t8, $v0, 8
/* 07CA78 8007BE78 AC980000 */  sw    $t8, ($a0)
/* 07CA7C 8007BE7C 3C0F0001 */  lui   $t7, 1
/* 07CA80 8007BE80 31D90002 */  andi  $t9, $t6, 2
/* 07CA84 8007BE84 01C06825 */  move  $t5, $t6
/* 07CA88 8007BE88 AC4F0004 */  sw    $t7, 4($v0)
/* 07CA8C 8007BE8C 13200008 */  beqz  $t9, .L8007BEB0
/* 07CA90 8007BE90 AC460000 */   sw    $a2, ($v0)
/* 07CA94 8007BE94 8C820000 */  lw    $v0, ($a0)
/* 07CA98 8007BE98 24180001 */  li    $t8, 1
/* 07CA9C 8007BE9C 244E0008 */  addiu $t6, $v0, 8
/* 07CAA0 8007BEA0 AC8E0000 */  sw    $t6, ($a0)
/* 07CAA4 8007BEA4 AC580004 */  sw    $t8, 4($v0)
/* 07CAA8 8007BEA8 10000008 */  b     .L8007BECC
/* 07CAAC 8007BEAC AC460000 */   sw    $a2, ($v0)
.L8007BEB0:
/* 07CAB0 8007BEB0 8C820000 */  lw    $v0, ($a0)
/* 07CAB4 8007BEB4 3C19B600 */  lui   $t9, 0xb600
/* 07CAB8 8007BEB8 244F0008 */  addiu $t7, $v0, 8
/* 07CABC 8007BEBC AC8F0000 */  sw    $t7, ($a0)
/* 07CAC0 8007BEC0 240E0001 */  li    $t6, 1
/* 07CAC4 8007BEC4 AC4E0004 */  sw    $t6, 4($v0)
/* 07CAC8 8007BEC8 AC590000 */  sw    $t9, ($v0)
.L8007BECC:
/* 07CACC 8007BECC 24180001 */  li    $t8, 1
/* 07CAD0 8007BED0 3C018012 */  lui   $at, %hi(D_80126382) # $at, 0x8012
/* 07CAD4 8007BED4 A4386382 */  sh    $t8, %lo(D_80126382)($at)
/* 07CAD8 8007BED8 3C018012 */  lui   $at, %hi(D_80126374) # $at, 0x8012
/* 07CADC 8007BEDC AC206374 */  sw    $zero, %lo(D_80126374)($at)
/* 07CAE0 8007BEE0 8C820000 */  lw    $v0, ($a0)
/* 07CAE4 8007BEE4 3C190702 */  lui   $t9, (0x07020010 >> 16) # lui $t9, 0x702
/* 07CAE8 8007BEE8 244F0008 */  addiu $t7, $v0, 8
/* 07CAEC 8007BEEC AC8F0000 */  sw    $t7, ($a0)
/* 07CAF0 8007BEF0 3C0F800E */  lui   $t7, %hi(D_800DF1A8) # $t7, 0x800e
/* 07CAF4 8007BEF4 37390010 */  ori   $t9, (0x07020010 & 0xFFFF) # ori $t9, $t9, 0x10
/* 07CAF8 8007BEF8 3C018000 */  lui   $at, 0x8000
/* 07CAFC 8007BEFC 000D7100 */  sll   $t6, $t5, 4
/* 07CB00 8007BF00 01C1C021 */  addu  $t8, $t6, $at
/* 07CB04 8007BF04 25EFF1A8 */  addiu $t7, %lo(D_800DF1A8) # addiu $t7, $t7, -0xe58
/* 07CB08 8007BF08 AC590000 */  sw    $t9, ($v0)
/* 07CB0C 8007BF0C 030FC821 */  addu  $t9, $t8, $t7
/* 07CB10 8007BF10 27BD0070 */  addiu $sp, $sp, 0x70
/* 07CB14 8007BF14 03E00008 */  jr    $ra
/* 07CB18 8007BF18 AC590004 */   sw    $t9, 4($v0)

