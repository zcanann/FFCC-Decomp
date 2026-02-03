#include "string.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/mem_funcs.h"

void* memmove(void* dst, const void* src, size_t n)
{
	unsigned char* csrc;
	unsigned char* cdst;

	int reverse = (unsigned int)src < (unsigned int)dst;

	if (n >= 32) {
		if (((unsigned int)dst ^ (unsigned int)src) & 3) {
			if (!reverse) {
				__copy_longs_unaligned(dst, src, n);
			} else {
				__copy_longs_rev_unaligned(dst, src, n);
			}
		} else {
			if (!reverse) {
				__copy_longs_aligned(dst, src, n);
			} else {
				__copy_longs_rev_aligned(dst, src, n);
			}
		}

		return dst;
	} else {
		if (!reverse) {
			csrc = ((unsigned char*)src) - 1;
			cdst = ((unsigned char*)dst) - 1;
			n++;

			while (--n > 0) {
				*++cdst = *++csrc;
			}
		} else {
			csrc = (unsigned char*)src + n;
			cdst = (unsigned char*)dst + n;
			n++;

			while (--n > 0) {
				*--cdst = *--csrc;
			}
		}
	}

	return dst;
}

void* memchr(const void* ptr, int ch, size_t count)
{
	const unsigned char* p;

	unsigned long v = (ch & 0xff);

	for (p = (unsigned char*)ptr - 1, count++; --count;)
		if ((*++p & 0xff) == v)
			return (void*)p;

	return NULL;
}

unsigned char* __memrchr(unsigned char* s, int c, size_t n){ // credit to CelestialAmber
    int n_count;
	size_t char_check;
    
    char_check = (unsigned char)c;
    s = &s[n];
    n_count = n + 1;
	
    while(--n_count){
		if(*--s == char_check){
            return s;
        }
    }
	
	return 0;
}

int memcmp(const void* lhs, const void* rhs, size_t count)
{
	const unsigned char* p1;
	const unsigned char* p2;

	for (p1 = (const unsigned char*)lhs - 1, p2 = (const unsigned char*)rhs - 1,
	    count++;
	     --count;)
		if (*++p1 != *++p2)
			return ((*p1 < *p2) ? -1 : +1);

	return 0;
}

void* memcpy(void* dst, const void* src, size_t count)
{
	unsigned char* srcPtr;
	unsigned char* dstPtr;
	int n;

	if (dst <= src) {
		srcPtr = (unsigned char*)src - 1;
		dstPtr = (unsigned char*)dst - 1;
		n = count + 1;
		while (--n != 0) {
			*++dstPtr = *++srcPtr;
		}
	} else {
		srcPtr = (unsigned char*)src + count;
		dstPtr = (unsigned char*)dst + count;
		n = count + 1;
		while (--n != 0) {
			*--dstPtr = *--srcPtr;
		}
	}
	return dst;
}

void __fill_mem(void* dst, unsigned char c, size_t count)
{
	unsigned int fillValue;
	unsigned int* wordPtr;
	unsigned char* bytePtr;
	unsigned int alignBytes;
	unsigned int words;

	fillValue = (unsigned int)c;
	bytePtr = (unsigned char*)dst - 1;

	if (count > 31) {
		alignBytes = (~(unsigned int)bytePtr) & 3;
		if (alignBytes != 0) {
			count -= alignBytes;
			do {
				*++bytePtr = c;
				alignBytes--;
			} while (alignBytes != 0);
		}

		if (fillValue != 0) {
			fillValue = fillValue | (fillValue << 8) | (fillValue << 24) | (fillValue << 16);
		}

		wordPtr = (unsigned int*)(bytePtr - 3);
		for (words = count >> 5; words != 0; words--) {
			wordPtr[1] = fillValue;
			wordPtr[2] = fillValue;
			wordPtr[3] = fillValue;
			wordPtr[4] = fillValue;
			wordPtr[5] = fillValue;
			wordPtr[6] = fillValue;
			wordPtr[7] = fillValue;
			wordPtr += 8;
			*wordPtr = fillValue;
		}

		for (words = (count >> 2) & 7; words != 0; words--) {
			*++wordPtr = fillValue;
		}

		bytePtr = (unsigned char*)((int)wordPtr + 3);
		count = count & 3;
	}

	if (count != 0) {
		do {
			*++bytePtr = (unsigned char)fillValue;
			count--;
		} while (count != 0);
	}
}

void* memset(void* dst, int c, size_t count)
{
	__fill_mem(dst, (unsigned char)c, count);
	return dst;
}
