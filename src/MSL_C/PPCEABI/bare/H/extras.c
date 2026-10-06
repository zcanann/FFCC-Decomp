#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ctype.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x801BB378
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
char* strlwr(char* str)
{
	char* p = str;
	while (*p != '\0') {
		*p = _tolower(*p);
		p++;
	}
	return str;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x801BB334
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
char* strupr(char* str)
{
	char* p = str;
	while (*p != '\0') {
		*p = _toupper(*p);
		p++;
	}
	return str;
}
