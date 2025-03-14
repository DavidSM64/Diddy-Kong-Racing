#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 osPfsFileState(OSPfs* pfs, s32 file_no, OSPfsState* state) {
    s32 ret;
    int pages;
    __OSInode inode;
    __OSDir dir;
    __OSInodeUnit next_page;
#if BUILD_VERSION < VERSION_J
    int j;
#endif
    u8 bank;
#if BUILD_VERSION < VERSION_J
    u8 start_page;
#endif

    if (file_no >= pfs->dir_size || file_no < 0) {
        return PFS_ERR_INVALID;
    }

    PFS_CHECK_STATUS();
#if BUILD_VERSION >= VERSION_J
    ERRCK(__osCheckId(pfs));
#else
    PFS_CHECK_ID();
#endif
    SET_ACTIVEBANK_TO_ZERO();

    ERRCK(__osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8*)&dir));

    if (dir.company_code == 0 || dir.game_code == 0) {
        return PFS_ERR_INVALID;
    }

#if BUILD_VERSION >= VERSION_J
    pages = 0;
    next_page = dir.start_page;
    bank = 0xFF;

    while (TRUE) {
        if (next_page.ipage < pfs->inode_start_page) {
            break;
        } else if (next_page.inode_t.bank != bank) {
            bank = next_page.inode_t.bank;
            ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
        }

        pages++;
        next_page = inode.inode_page[next_page.inode_t.page];
    }

    if (next_page.ipage != PFS_EOF) {
        return PFS_ERR_INCONSISTENT;
    }

    state->file_size = pages * (PFS_ONE_PAGE * BLOCKSIZE);
    state->company_code = dir.company_code;
    state->game_code = dir.game_code;
    bcopy(&dir.game_name, state->game_name, PFS_FILE_NAME_LEN);
    bcopy(&dir.ext_name, state->ext_name, PFS_FILE_EXT_LEN);

    ret = __osPfsGetStatus(pfs->queue, pfs->channel);
    return ret;
#else
    if (dir.start_page.ipage < pfs->inode_start_page) {
        return PFS_ERR_INCONSISTENT;
    }

    pages = 0;
    start_page = dir.start_page.inode_t.page;
    bank = dir.start_page.inode_t.bank;

    while (bank < pfs->banks) {
        ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
        next_page = inode.inode_page[start_page];
        pages++;

        while (next_page.ipage >= pfs->inode_start_page) {
            pages++;
            next_page = inode.inode_page[next_page.inode_t.page];
            if (next_page.inode_t.bank != bank) {
                bank = next_page.inode_t.bank;
                start_page = next_page.inode_t.page;
                break;
            }
        }

        if (next_page.ipage == PFS_EOF) {
            break;
        }
    }
    
    if (next_page.ipage != PFS_EOF) {
        return PFS_ERR_INCONSISTENT;
    }

    state->file_size = pages * (PFS_ONE_PAGE * BLOCKSIZE);
    state->company_code = dir.company_code;
    state->game_code = dir.game_code;

    for (j = 0; j < ARRLEN(state->game_name); j++) {
        state->game_name[j] = dir.game_name[j];
    }

    for (j = 0; j < ARRLEN(state->ext_name); j++) {
        state->ext_name[j] = dir.ext_name[j];
    }

    return 0;
#endif
}
