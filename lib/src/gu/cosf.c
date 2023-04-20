/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4AB0 */

#include "types.h"
#include "macros.h"
#include "guint.h"

extern du P_cosf[];
extern du rpi_cosf;
extern du pihi_cosf;
extern du pilo_cosf;
extern fu zero_cosf;
extern fu __libm_qnan_f;

f32 cosf(f32 x) {
	f64 dx;  // double x
	f64 xsq; // x squared
	f64 poly;
	f64 dn;
	f32 xabs;
	s32 n;
	f64 result;
	s32 ix; // int x
	s32 xpt;
	
	ix = *(s32 *) &x;
	xpt = (ix >> 22) & 0x1FF;

	if (xpt < 310) {
		if (0 < x) {
			xabs = x;
		} else {
			xabs = -x;
		}

		dx = xabs;
		dn = dx * rpi_cosf.d + 0.5f;

		if (0 <= dn) {
			n = dn + 0.5f;
		} else {
			n = dn - 0.5f;
		}

		dn = n;
		dx -= (dn - 0.5f) * pihi_cosf.d;
		dx -= (dn - 0.5f) * pilo_cosf.d;
		xsq = dx * dx;

		poly = (((((P_cosf[4].d * xsq) + P_cosf[3].d) * xsq) + P_cosf[2].d) * xsq) + P_cosf[1].d;

		result = ((dx * xsq) * poly) + dx;

		if ((n & 1) == 0) {
			return result;
		} else {
			return -(f32) result;
		}
	}

	if (x != x) {
		return __libm_qnan_f.f;
	}

	return zero_cosf.f;
}
