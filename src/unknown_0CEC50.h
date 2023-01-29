#ifndef _UNKNOWN_0CEC50_H_
#define _UNKNOWN_0CEC50_H_

#include "types.h"
#include "structs.h"

//Takes a char pointer, the string to populate it with, and the length of that string.
//Example:
//_bcmp(&gameName, "DKRACING-ADV", strlen("DKRACING-ADV"));
s32 _bcmp(u8 *stringToPopulate, char *string, u32 stringLen);

#endif
