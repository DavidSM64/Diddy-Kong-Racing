/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80071D30 */

#include "libultra_internal.h"
#include "controller.h"
#include "siint.h"

#define MOTOR_RAM_ADDRESS 0x400
#define MOTOR_DATA_ADDRESS 0x600
#define MOTOR_DEFAULT_BANK 128

static void _MakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata);
OSPifRam _MotorStopData[MAXCONTROLLERS];
OSPifRam _MotorStartData[MAXCONTROLLERS];
u8 _motorstopbuf[BLOCKSIZE];
u8 _motorstartbuf[BLOCKSIZE];
/* Official name: nosMotorStop */
s32 osMotorStop(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    __osSiGetAccess();

    __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
    __osSiRawStartDma(OS_WRITE, &_MotorStopData[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = (u8 *)&__osPfsPifRam;

    if (pfs->channel != 0)
        for (i = 0; i < pfs->channel; i++)
            ptr++;

    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != 0)
        ret = PFS_ERR_CONTRFAIL;
    __osSiRelAccess();
    return ret;
}

s32 osMotorStart(OSPfs *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;

    __osSiGetAccess();

    __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
    __osSiRawStartDma(OS_WRITE, &_MotorStartData[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    ptr = (u8 *)&__osPfsPifRam;

    if (pfs->channel != 0)
        for (i = 0; i < pfs->channel; i++)
            ptr++;

    ramreadformat = *(__OSContRamReadFormat *)ptr;
    ret = CHNL_ERR(ramreadformat);
    if (ret == 0 && ramreadformat.datacrc != 0xEB)
        ret = PFS_ERR_CONTRFAIL;
    __osSiRelAccess();
    return ret;
}

static void _MakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata) {
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)mdata->ramarray;
    for (i = 0; i < ARRLEN(mdata->ramarray); i++)
        mdata->ramarray[i] = 0;
    mdata->pifstatus = CONT_CMD_EXE;
    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_MEMPACK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_MEMPACK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_MEMPACK;

    ramreadformat.address = (address << 0x5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;
    for (i = 0; i < ARRLEN(ramreadformat.data); i++)
        ramreadformat.data[i] = *buffer++;

    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}

/* Official name: nosMotorInit */
s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel) {
    int i;
    s32 ret;
    u8 temp[BLOCKSIZE];
    pfs->queue = mq;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = MOTOR_DEFAULT_BANK;

    for (i = 0; i < ARRLEN(temp); i++)
        temp[i] = MOTOR_DEFAULT_BANK;

    ret = __osContRamWrite(mq, channel, MOTOR_RAM_ADDRESS, temp, FALSE);

    if (ret == PFS_ERR_NEW_PACK)
        ret = __osContRamWrite(mq, channel, MOTOR_RAM_ADDRESS, temp, FALSE);

    if (ret != 0)
        return ret;

    ret = __osContRamRead(mq, channel, MOTOR_RAM_ADDRESS, temp);

    if (ret != 0)
        return ret;

    if (temp[ARRLEN(temp) - 1] != MOTOR_DEFAULT_BANK) {
        return PFS_ERR_DEVICE;
    }

    for (i = 0; i < ARRLEN(_motorstartbuf); i++) {
        _motorstartbuf[i] = 1;
        _motorstopbuf[i] = 0;
    }

    _MakeMotorData(channel, MOTOR_DATA_ADDRESS, _motorstartbuf, &_MotorStartData[channel]);
    _MakeMotorData(channel, MOTOR_DATA_ADDRESS, _motorstopbuf, &_MotorStopData[channel]);

    return 0;
}
