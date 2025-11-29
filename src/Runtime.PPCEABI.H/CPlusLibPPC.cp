#include "PowerPC_EABI_Support/Runtime/CPlusLibPPC.h"

extern "C" void* __copy(char *dest, char *src, unsigned int size) {
	char *p;
	
	if (dest && size) {
		p = dest;
		do {
			*p = *src;
			++p;
			++src;
			--size;
		} while (size);
	}
	
	return(dest);
}