/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2480 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

#define PI_Q_BUF_LEN 1
extern u32 __osPiAccessQueueEnabled;
extern OSMesg piAccessBuf[PI_Q_BUF_LEN];
extern OSMesgQueue __osPiAccessQueue;
void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, piAccessBuf, PI_Q_BUF_LEN);
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osPiAccessQueueEnabled)
        __osPiCreateAccessQueue();
    osRecvMesg(&__osPiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

/**********************************************************************/

// Please move these later!
#include "lib/src/gu/guint.h"
// Used with cosf

/* coefficients for polynomial approximation of cos on +/- pi/2 */

const du	P_cosf[] =
{
{{0x3ff00000,	0x00000000}},
{{0xbfc55554,	0xbc83656d}},
{{0x3f8110ed,	0x3804c2a0}},
{{0xbf29f6ff,	0xeea56814}},
{{0x3ec5dbdf,	0x0e314bfe}},
};

const du	rpi_cosf =
{{0x3fd45f30,	0x6dc9c883}};

const du	pihi_cosf =
{{0x400921fb,	0x50000000}};

const du	pilo_cosf =
{{0x3e6110b4,	0x611a6263}};

const fu	zero_cosf = {0x00000000};

const int COSF_FILE_PADDING[3] = { 0 };

// Used with sinf
/* coefficients for polynomial approximation of sin on +/- pi/2 */

const du	P_sinf[] =
{
{{0x3ff00000,	0x00000000}},
{{0xbfc55554,	0xbc83656d}},
{{0x3f8110ed,	0x3804c2a0}},
{{0xbf29f6ff,	0xeea56814}},
{{0x3ec5dbdf,	0x0e314bfe}},
};

const du	rpi_sinf =
{{0x3fd45f30,	0x6dc9c883}};

const du	pihi_sinf =
{{0x400921fb,	0x50000000}};

const du	pilo_sinf =
{{0x3e6110b4,	0x611a6263}};

const fu	zero_sinf = {0x00000000};

const int SINF_FILE_PADDING[3] = { 0 };

// Used with _Litob
char ldigs[] = "0123456789abcdef"; // lowercase hex digits
char udigs[] = "0123456789ABCDEF"; // uppercase hex digits

// Powers for _Ldtob
const double pows[] = {10e0L, 10e1L, 10e3L, 10e7L, 10e15L, 10e31L, 10e63L, 10e127L, 10e255L};

const char Ldtob_NaN[] = "NaN";
const char Ldtob_Inf[] = "Inf";

//_Genld
const char _Genld_0_string[] = "0";

//_Ldtob
const double _Ldtob_1e8[] = {1.0e8};

//sinf and cosf - supposed to be defined by libm_vals.s
const fu __libm_qnan_f = { 0x7f810000 };
