/************************************************************************
 Copyright (C) 1998,1999 NINTENDO Co,Ltd,
 Copyright (C) 1998,1999 MONEGI CORPORATION,
	All Rights Reserved
This program is a trade secret of NINTENDO Co,Ltd and MONEGI Corp. 
and it is not to be reproduced, published, disclosed to others, copied,
adapted, distributed, or displayed without the prior authorization of 
NINTENDO Co,Ltd. and MONEGI Corp. Licensee agrees to attach or embed 
this Notice on all copies of the program, including partial copies or 
modified versions thereof.
*************************************************************************/
/************************************************************************
 $Date: 1999/07/06 13:21:13 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/

#ifndef __ASM_H__
#define __ASM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define _MIPS_ISA_MIPS1	1	/* R2/3K */
#define _MIPS_ISA_MIPS2	2	/* R4K/6K */
#define _MIPS_ISA_MIPS3	3	/* R4K */
#define _MIPS_ISA_MIPS4	4	/* TFP */

#define _MIPS_SIM_ABI32		1	/* MIPS MSIG calling convention */
#define _MIPS_SIM_NABI32	2	/* MIPS new 32-bit abi */
		/* NABI32 is 64bit calling convention but 32bit type sizes) */
#define _MIPS_SIM_ABI64		3	/* MIPS 64 calling convention */

#define	LEAF(x)						\
	.globl	x;					\
	.ent	x,0;					\
x:;							\
	.frame	sp,0,ra

#define	XLEAF(x)					\
	.global x;

#define	END(proc)					\
	.end	proc

#define	ABS(x, y)					\
	.globl	x;					\
	x	=	y
	
#define	EXPORT(x)					\
	.globl	x;					\
x:
/*
#define WEAK(x, y) \
	.weak x; \
	.set x,y;
*/

#define WEAK(x, y)

#define STAY1(stmnt) .set noreorder; stmnt; .set reorder;
#define STAY2(stmnt, arg1) .set noreorder; stmnt, arg1; .set reorder;
#define STAY3(stmnt, arg1, arg2) .set noreorder; stmnt, arg1, arg2; .set reorder;
#define NOP .set noreorder; nop; .set reorder;
#define CACHE(op, reg) .set noreorder; cache op, reg; .set reorder;

#ifdef __cplusplus
}
#endif

#endif /* !__ASM_H__ */
