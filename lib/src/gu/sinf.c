/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4C20 */

#include "types.h"
#include "macros.h"
#include "guint.h"

extern du P_sinf[];
extern du rpi_sinf;
extern du pihi_sinf;
extern du pilo_sinf;
extern fu zero_sinf;
extern fu __libm_qnan_f;

f32 sinf(f32 x) {
	f64 dx;  // double x
	f64 xsq; // x squared
	f64 poly;
	f64 dn;
	s32 n;
	f64 result;
	s32 ix; // int x
	s32 xpt;

	ix = *(s32 *) &x;
	xpt = (ix >> 22) & 0x1FF;

	if (xpt < 255) {
		dx = x;
		if (xpt >= 230) {
			xsq = dx * dx;
			poly = (((((P_sinf[4].d * xsq) + P_sinf[3].d) * xsq) + P_sinf[2].d) * xsq) + P_sinf[1].d;
			result = ((dx * xsq) * poly) + dx;

			return result;
		} else {
			return x;
		}
	}

	if (xpt < 310) {
		dx = x;
		dn = dx * rpi_sinf.d;

		if (dn >= 0) {
			n = dn + 0.5;
		}
		else {
			n = dn - 0.5;
		}

		dn = n;
		dx -= dn * pihi_sinf.d;
		dx -= dn * pilo_sinf.d;
		xsq = dx * dx;
		poly = (((((P_sinf[4].d * xsq) + P_sinf[3].d) * xsq) + P_sinf[2].d) * xsq) + P_sinf[1].d;
		result = ((dx * xsq) * poly) + dx;

		if ((n & 1) == 0) {
			return result;
		}
		else {
			return -(f32) result;
		}
	}

	if (x != x) {
		return __libm_qnan_f.f;
	}

	return zero_sinf.f;
}
