#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 osPfsNumFiles(OSPfs* pfs, s32* max_files, s32* files_used) {
    int j;
    s32 ret;
    __OSDir dir;
    int files = 0;

    PFS_CHECK_STATUS();
#if BUILD_VERSION >= VERSION_J
    ERRCK(__osCheckId(pfs));
#else
    PFS_CHECK_ID();
#endif
    SET_ACTIVEBANK_TO_ZERO();

    for (j = 0; j < pfs->dir_size; j++) {
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + j, (u8*)&dir));

        if (dir.company_code != 0 && dir.game_code != 0) {
            files++;
        }
    }
    *files_used = files;
    *max_files = pfs->dir_size;

#if BUILD_VERSION >= VERSION_J
    ret = __osPfsGetStatus(pfs->queue, pfs->channel);
    return ret;
#else
    return 0;
#endif
}
