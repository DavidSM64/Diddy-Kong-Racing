/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6F30 */

#include "os.h"
#include "PRinternal/osint.h"
#include "osint_debug.h"

void __assertBreak(void);

void __assert(const char* exp, const char* filename, int line) {
#ifndef _FINALROM
    osSyncPrintf("\nASSERTION FAULT: %s, %d: \"%s\"\n", filename, line, exp);
    __assertBreak; // Doesn't actually do anything, but is needed for matching
#endif
}
