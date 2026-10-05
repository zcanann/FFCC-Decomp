#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"


/*
 * --INFO--
 * PAL Address: 0x801BC434
 * PAL Size: 32b
 * EN Address: 0x801BB314
 * EN Size: 32b
 * JP Address: TODO
 * JP Size: TODO
 */
double sqrt(double x)
{
	return __ieee754_sqrt(x);
}
