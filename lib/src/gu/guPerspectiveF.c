/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CC920 */

#include "types.h"
#include "macros.h"
#include "libc/math.h"
#include "PR/gu.h"

void guPerspectiveF(Matrix mf, u16 *perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float cot;
    int i, j;

    guMtxIdentF(mf);

    fovy *= 3.1415926 / 180.0f;
    cot = cosf (fovy/2) / sinf (fovy/2);

    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = -1;
    mf[3][2] = (2 * near * far) / (near - far);
    mf[3][3] = 0;

    for (i=0; i<4; i++) {
        for (j=0; j<4; j++)
            mf[i][j] *= scale;
    }

    if (perspNorm != (u16 *) NULL) {
        if (near+far<=2.0f) {
            *perspNorm = (u16) 0xFFFF;
        } else {
            *perspNorm = (u16) ((2.0f*65536.0f)/(near+far));
        if (*perspNorm<=0)
            *perspNorm = (u16) 0x0001;
        }
    }
}

void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float aspect, float near, float far, float scale) {
    Matrix mf;

    guPerspectiveF(mf, perspNorm, fovy, aspect, near, far, scale);

    guMtxF2L(mf, m);
}
