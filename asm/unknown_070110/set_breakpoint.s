# void set_breakpoint(u32 addr); - Sets a breakpoint on physical address
glabel set_breakpoint
/* 0716D8 80070AD8 34840001 */  ori   $a0, $a0, 1 # SET WATCHLO_WTRAP ON - when set traps on stores to paddr;
/* 0716DC 80070ADC 40849000 */  mtc0  $a0, $18    # C0_WATCHLO
/* 0716E0 80070AE0 2408000F */  li    $t0, 15     # WATCHHI_VALIDMASK
/* 0716E4 80070AE4 40889800 */  mtc0  $t0, $19    # C0_WATCHHI
/* 0716E8 80070AE8 00000000 */  nop   
/* 0716EC 80070AEC 00000000 */  nop   
/* 0716F0 80070AF0 00000000 */  nop   
/* 0716F4 80070AF4 00000000 */  nop   
/* 0716F8 80070AF8 00000000 */  nop   
/* 0716FC 80070AFC 03E00008 */  jr    $ra
/* 071700 80070B00 00000000 */   nop   
