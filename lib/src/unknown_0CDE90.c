/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD290 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "controller.h"

extern OSPifRam __osPfsPifRam; //__osPfsPifRam
extern u8 D_8012CD90; //__osContLastCmd
extern u8 __osMaxControllers;//__osMaxControllers
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CDE90/osPfsIsPlug.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CDE90/__osPfsRequestData.s")

void __osPfsGetInitData(u8 *pattern, OSContStatus *data)
{
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;
    bits = 0;
    ptr = (u8 *)&__osPfsPifRam;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(__OSContRequesFormat))
    {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0)
        {
            data->type = (requestformat.typel << 8) | (requestformat.typeh);
            data->status = requestformat.status;
            bits |= 1 << i;
        }
        data++;
    }
    *pattern = bits;
}
