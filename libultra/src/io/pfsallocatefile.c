#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/rmon.h"

#define ROUND_UP_DIVIDE(numerator, denominator) (((numerator) + (denominator)-1) / (denominator))

#if BUILD_VERSION >= VERSION_J

s32 osPfsAllocateFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name, int file_size_in_bytes,
                      s32* file_no) {
    int start_page;
    int decleared;
    int last_page;
    int old_last_page = 0;
    s32 ret = 0;
    int file_size_in_pages;
    __OSInode inode;
    __OSInode backup_inode;
    __OSDir dir;
    u8 bank;
    u8 old_bank = 0;
    int firsttime = 0;
    s32 bytes;
    __OSInodeUnit fpage;

    if (company_code == 0 || game_code == 0) {
        return PFS_ERR_INVALID;
    }

    file_size_in_pages = ROUND_UP_DIVIDE(file_size_in_bytes, BLOCKSIZE * PFS_ONE_PAGE);

    if (((ret = osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, file_no)) != 0) &&
        ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (*file_no != -1) {
        return PFS_ERR_EXIST;
    }

    ret = osPfsFreeBlocks(pfs, &bytes);

    if (file_size_in_bytes > bytes) {
        return PFS_DATA_FULL;
    }

    if (file_size_in_pages == 0) {
        return PFS_ERR_INVALID;
    }

    if (((ret = osPfsFindFile(pfs, 0, 0, NULL, NULL, file_no)) != 0) && ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (*file_no == -1) {
        return PFS_DIR_FULL;
    }

    for (bank = 0; bank < pfs->banks; bank++) {
        ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
        ERRCK(__osPfsDeclearPage(pfs, &inode, file_size_in_pages, &start_page, bank, &decleared, &last_page));

        if (start_page != -1) {
            if (firsttime == 0) {
                fpage.inode_t.page = start_page;
                fpage.inode_t.bank = bank;
            } else {
                backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                ERRCK(__osPfsRWInode(pfs, &backup_inode, PFS_WRITE, old_bank));
            }

            if (file_size_in_pages > decleared) {
                bcopy(&inode, &backup_inode, sizeof(__OSInode));
                old_last_page = last_page;
                old_bank = bank;
                file_size_in_pages -= decleared;
                firsttime++;
            } else {
                file_size_in_pages = 0;
                ERRCK(__osPfsRWInode(pfs, &inode, PFS_WRITE, bank));
                break;
            }
        }
    }

    if (file_size_in_pages > 0 || start_page == -1) {
        return PFS_ERR_INCONSISTENT;
    }

    dir.start_page = fpage;
    dir.company_code = company_code;
    dir.game_code = game_code;
    dir.data_sum = 0;

    bcopy(game_name, dir.game_name, PFS_FILE_NAME_LEN);
    bcopy(ext_name, dir.ext_name, PFS_FILE_EXT_LEN);

    ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + *file_no, (u8*)&dir, FALSE);
    return ret;
}

s32 __osPfsDeclearPage(OSPfs* pfs, __OSInode* inode, int file_size_in_pages, int* first_page, u8 bank, int* decleared,
                       int* last_page) {
    int j;
    int spage;
    int old_page;
    s32 ret = 0;
    int offset = bank > 0 ? 1 : pfs->inode_start_page;

    for (j = offset; j < ARRLEN(inode->inode_page); j++) {
        if (inode->inode_page[j].ipage == 3) {
            break;
        }
    }

    if (j == ARRLEN(inode->inode_page)) {
        *first_page = -1;
        return ret;
    }

    spage = j;
    *decleared = 1;
    old_page = j;
    j++;

    while (file_size_in_pages > *decleared && j < ARRLEN(inode->inode_page)) {
        if (inode->inode_page[j].ipage == 3) {
            inode->inode_page[old_page].inode_t.bank = bank;
            inode->inode_page[old_page].inode_t.page = j;
            old_page = j;
            (*decleared)++;
        }
        j++;
    }

    *first_page = spage;

    if (j == ARRLEN(inode->inode_page) && file_size_in_pages > *decleared) {
        *last_page = old_page;
    } else {
        inode->inode_page[old_page].ipage = 1;
        *last_page = 0;
    }

    return ret;
}

#else

static s32 __osClearPage(OSPfs *pfs, int page_num, u8 *data, u8 bank);

s32 osPfsAllocateFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name, int file_size_in_bytes,
                      s32* file_no) {
    int start_page;
    int decleared;
    int last_page;
    int old_last_page = 0;
    int j;
    s32 ret = 0;
    int file_size_in_pages;
    __OSInode inode;
    __OSInode backup_inode;
    __OSDir dir;
    u8 bank;
    u8 old_bank = 0;
    int firsttime = 0;
    s32 bytes;
    __OSInodeUnit fpage;

    if (company_code == 0 || game_code == 0) {
        return PFS_ERR_INVALID;
    }

    file_size_in_pages = ROUND_UP_DIVIDE(file_size_in_bytes, BLOCKSIZE * PFS_ONE_PAGE);

    if ((pfs->status & PFS_INITIALIZED) == FALSE) {
        return PFS_ERR_INVALID;
    }

    PFS_CHECK_ID();

    if (((ret = osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, file_no)) != 0) &&
        ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (*file_no != -1) {
        return PFS_ERR_EXIST;
    }

    ret = osPfsFreeBlocks(pfs, &bytes);

    if (file_size_in_bytes > bytes) {
        return PFS_DATA_FULL;
    }

    if (file_size_in_pages != 0) {

        if (((ret = osPfsFindFile(pfs, 0, 0, NULL, NULL, file_no)) != 0) && ret != PFS_ERR_INVALID) {
            return ret;
        }

        if (*file_no == -1) {
            return PFS_DIR_FULL;
        }

        for (bank = 0; bank < pfs->banks; bank++) {
            ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
            ERRCK(__osPfsDeclearPage(pfs, &inode, file_size_in_pages, &start_page, bank, &decleared, &last_page));

            if (start_page != -1) {
                if (firsttime == 0) {
                    fpage.inode_t.page = start_page;
                    fpage.inode_t.bank = bank;
                } else {
                    backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                    backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                    ERRCK(__osPfsRWInode(pfs, &backup_inode, PFS_WRITE, old_bank));
                }

                for (j = 0; j < ARRLEN(inode.inode_page); j++) {
                    backup_inode.inode_page[j].ipage = inode.inode_page[j].ipage;
                }
                old_last_page = last_page;
                old_bank = bank;
                firsttime++;
                if (file_size_in_pages > decleared) {
                    file_size_in_pages = file_size_in_pages - decleared;
                } else {
                    file_size_in_pages = 0;
                    break;
                }
            }
        }

        if (file_size_in_pages > 0 || start_page == -1) {
            return PFS_ERR_INCONSISTENT;
        }
        
        backup_inode.inode_page[old_last_page].inode_t.bank = bank;
        backup_inode.inode_page[old_last_page].inode_t.page = start_page;
        ERRCK(__osPfsRWInode(pfs, &backup_inode, PFS_WRITE, old_bank));

        dir.start_page = fpage;
        dir.company_code = company_code;
        dir.game_code = game_code;
        dir.data_sum = 0;

        for (j = 0; j < ARRLEN(dir.game_name); j++)
            dir.game_name[j] = *game_name++;
        for (j = 0; j < ARRLEN(dir.ext_name); j++)
            dir.ext_name[j] = *ext_name++;

        ERRCK(__osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + *file_no, (u8*)&dir, FALSE));
        return ret;
    } else {
        return PFS_ERR_INVALID;
    }
}

s32 __osPfsDeclearPage(OSPfs* pfs, __OSInode* inode, int file_size_in_pages, int* first_page, u8 bank, int* decleared,
                       int* last_page) {
    int j;
    int spage;
    int old_page;
    u8 tmp_data[BLOCKSIZE];
    int i;
    s32 ret = 0;
    int offset = bank > 0 ? 1 : pfs->inode_start_page;

    for (j = offset; j < ARRLEN(inode->inode_page); j++) {
        if (inode->inode_page[j].ipage == 3) {
            break;
        }
    }

    if (j == ARRLEN(inode->inode_page)) {
        *first_page = -1;
        return ret;
    }
    
    for (i = 0; i < ARRLEN(tmp_data); i++) {
        tmp_data[i] = 0;
    }

    spage = j;
    *decleared = 1;
    old_page = j;
    j++;

    while (file_size_in_pages > *decleared && j < ARRLEN(inode->inode_page)) {
        if (inode->inode_page[j].ipage == 3) {
            inode->inode_page[old_page].inode_t.bank = bank;
            inode->inode_page[old_page].inode_t.page = j;
            ERRCK(__osClearPage(pfs, old_page, (u8*)tmp_data, bank));
            old_page = j;
            (*decleared)++;
        }
        j++;
    }

    *first_page = spage;

    if (j == ARRLEN(inode->inode_page) && file_size_in_pages > *decleared) {
        *last_page = old_page;
        return ret;
    } else {
        inode->inode_page[old_page].ipage = 1;
        ret = __osClearPage(pfs, old_page, (u8*)tmp_data, bank);
        *last_page = 0;
        return ret;
    }
}

static s32 __osClearPage(OSPfs *pfs, int page_no, u8 *data, u8 bank)
{
    int i;
    s32 ret;
    ret = 0;
    pfs->activebank = bank;
    ERRCK(__osPfsSelectBank(pfs));
    for (i = 0; i < PFS_ONE_PAGE; i++) {
        ret = __osContRamWrite(pfs->queue, pfs->channel, page_no * PFS_ONE_PAGE + i, data, FALSE);
        if (ret != 0) {
            break;
        }
    }
    pfs->activebank = 0;
    ret = __osPfsSelectBank(pfs);
    return ret;
}

#endif

#ifdef _DEBUG
s32 __osDumpInode(OSPfs* pfs) {
    int j;
    __OSInode inode;
    s32 ret = 0;
    __OSDir dir;
    u8 bank;
#if BUILD_VERSION >= VERSION_J
    u8 startbank = PFS_ID_BANK_256K;
#endif

    rmonPrintf("INODE:\n");

#if BUILD_VERSION >= VERSION_J
    for (bank = startbank; bank < pfs->banks; bank++) {
#else
    for (bank = 0; bank < pfs->banks; bank++) {
#endif
        rmonPrintf("\nBank %d:\n", bank);
        ret = __osPfsRWInode(pfs, &inode, PFS_READ, bank);
        for (j = 0; j < PFS_INODE_SIZE_PER_PAGE; j++) {
            rmonPrintf("%x ", inode.inode_page[j].ipage);
        }
    }

    rmonPrintf("dir_size %d %d\n", pfs->dir_size, pfs->inode_start_page);

    for (j = 0; j < pfs->dir_size; j++) {
        __osContRamRead(pfs->queue, pfs->channel, (u16)(pfs->dir_table + (int)j), (u8*)&dir);
        rmonPrintf("file %d game_code %d page %x c_code %d sum %d\n", j, dir.game_code, dir.start_page.ipage,
                   dir.company_code, dir.data_sum);
    }
    rmonPrintf("End of Dump\n");
    return ret;
}
#endif
