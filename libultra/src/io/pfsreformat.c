#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

s32 osPfsReFormat(OSPfs* pfs, OSMesgQueue* queue, int channel) {
    int j;
    int i;
    __OSInode inode;
    u8 tmp_data[32];
    u8* ptr;
    s32 ret;
    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);

    if (ret != 0) {
        return ret;
    }

    pfs->status ^= PFS_INITIALIZED;
    pfs->queue = queue;
    pfs->channel = channel;
    __osSiRelAccess();
    ERRCK(__osGetId(pfs));

    SET_ACTIVEBANK_TO_ZERO();

    for (j = 0; j < ARRLEN(tmp_data); j++) {
        tmp_data[j] = 0;
    }

    for (j = 0; j < pfs->dir_size; j++) {
        ERRCK(__osContRamWrite(queue, channel, pfs->dir_table + j, tmp_data, FALSE));
    }

    for (j = 0; j < pfs->inode_start_page; j++) {
        inode.inode_page[j].ipage = 0;
    }

    for (j = pfs->inode_start_page; j < ARRLEN(inode.inode_page); j++) {
        inode.inode_page[j].ipage = 3;
    }

    inode.inode_page[0].ipage = __osSumcalc((u8*)(inode.inode_page + pfs->inode_start_page),
                                            (ARRLEN(inode.inode_page) - pfs->inode_start_page) * sizeof(__OSInodeUnit));
    ptr = (u8*)&inode;

    for (j = 0; j < PFS_ONE_PAGE; j++) {
        ERRCK(__osContRamWrite(queue, channel, pfs->inode_table + j, ptr + j * BLOCKSIZE, FALSE));
        ERRCK(__osContRamWrite(queue, channel, pfs->minode_table + j, ptr + j * BLOCKSIZE, FALSE));
    }

    for (i = 1; i < pfs->banks; i++) {
        for (j = 1; j < ARRLEN(inode.inode_page); j++) {
            inode.inode_page[j].ipage = 3;
        }

        inode.inode_page[0].ipage =
            __osSumcalc((u8*)(inode.inode_page + 1), (ARRLEN(inode.inode_page) - 1) * sizeof(__OSInodeUnit));
        ptr = (u8*)&inode;

        for (j = 0; j < PFS_ONE_PAGE; j++) {
            ERRCK(
                __osContRamWrite(queue, channel, pfs->inode_table + i * PFS_ONE_PAGE + j, ptr + j * BLOCKSIZE, FALSE));
            ERRCK(
                __osContRamWrite(queue, channel, pfs->minode_table + i * PFS_ONE_PAGE + j, ptr + j * BLOCKSIZE, FALSE));
        }
    }

    return 0;
}
