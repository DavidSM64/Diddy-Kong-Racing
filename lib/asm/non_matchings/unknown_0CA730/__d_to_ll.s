/* Hacky workaround. This is required because after alSynSetPriority, the linker seems to have added a bunch of nops. */
glabel NOPSNEEDED
/* 0CA6F0 800C9AF0 00000000 */  nop   
/* 0CA6F4 800C9AF4 00000000 */  nop   
/* 0CA6F8 800C9AF8 00000000 */  nop   
/* 0CA6FC 800C9AFC 00000000 */  nop   
/* 0CA700 800C9B00 00000000 */  nop   
/* 0CA704 800C9B04 00000000 */  nop   
/* 0CA708 800C9B08 00000000 */  nop   
/* 0CA70C 800C9B0C 00000000 */  nop   
/* 0CA710 800C9B10 00000000 */  nop   
/* 0CA714 800C9B14 00000000 */  nop   
/* 0CA718 800C9B18 00000000 */  nop   
/* 0CA71C 800C9B1C 00000000 */  nop   
/* 0CA720 800C9B20 00000000 */  nop   
/* 0CA724 800C9B24 00000000 */  nop   
/* 0CA728 800C9B28 00000000 */  nop   
/* 0CA72C 800C9B2C 00000000 */  nop 

glabel __d_to_ll
/* 0CA730 800C9B30 46206109 */  trunc.l.d $f4, $f12
/* 0CA734 800C9B34 44222000 */  dmfc1 $v0, $f4
/* 0CA738 800C9B38 00000000 */  nop   
/* 0CA73C 800C9B3C 0002183C */  dsll32 $v1, $v0, 0
/* 0CA740 800C9B40 0003183F */  dsra32 $v1, $v1, 0
/* 0CA744 800C9B44 03E00008 */  jr    $ra
/* 0CA748 800C9B48 0002103F */   dsra32 $v0, $v0, 0
