#include "os.h"
#include "PRinternal/osint.h"
#include "osint_debug.h"


/************ .rodata ************/

const char D_800E8E70[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8EA0[] = "\nAssertion failed: '%s' in file %s, line %d\n";

/*********************************/

void __assertBreak(void);

void __assert(const char* exp, const char* filename, int line) {
#ifndef _FINALROM
    osSyncPrintf("\nASSERTION FAULT: %s, %d: \"%s\"\n", filename, line, exp);
    __assertBreak; // Doesn't actually do anything, but is needed for matching
#endif
}
