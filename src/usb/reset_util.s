.text

glabel reboot_disable_interrupts
    mfc0 $t0, $12      # $t0 = status register flags
    andi $t0, $t0, 0xFFFE  # Disable interrupts flags
    jr $ra 
    mtc0 $t0, $12      # Write new status flags
