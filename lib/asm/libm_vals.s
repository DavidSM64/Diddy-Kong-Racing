/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800E0000 */
/* RODATA ONLY try a randomly high RAM_POS to see if it works. */
	.rdata
	.align 4
	.globl __libm_qnan_f
__libm_qnan_f:
	.word   0x7F810000
