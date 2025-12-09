/* 
    Define a macro for signed multiplication of two registers, storing the result in a destination register
    This is similar to the MUL instruction but is mult instead of multu.
*/
#define MULS(rd, rs, rt) \
    mult   rs, rt; \
    mflo   rd