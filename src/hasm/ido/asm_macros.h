/* 
    Define a macro for signed multiplication of two registers, storing the result in a destination register
    This is similar to the MUL instruction but is mult instead of multu.
*/
#define MULS(rd, rs, rt) \
    mult   rs, rt; \
    mflo   rd \

/* 
    I think they accidentally used mul instead of mult.
    This causes issues if they rd and rs are different registers as
    rs would get overwritten by the mult instruction.
    It also wastes and extra instruction with the extra mflo at the end.
*/
#define MUL(rd, rs, rt) \
    mul    rs, rt; \
    mflo   rd /* (mul pseudo-op already does this, but original has it) */ \