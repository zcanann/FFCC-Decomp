#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/mem_funcs.h"

#define cps               ((unsigned char*)src)
#define cpd               ((unsigned char*)dst)
#define lps               ((unsigned long*)src)
#define lpd               ((unsigned long*)dst)
#define deref_auto_inc(p) *++(p)

void __copy_longs_aligned(void* dst, const void* src, size_t n)
{
	unsigned long i;
	unsigned long v;
	const unsigned char* src8;
	unsigned char* dst8;
	const unsigned long* src32;
	unsigned long* dst32;

	i = (-(unsigned long)dst) & 3;
	src8 = ((const unsigned char*)src) - 1;
	dst8 = ((unsigned char*)dst) - 1;

	if (i) {
		n -= i;
		do
			*++dst8 = *++src8;
		while (--i);
	}

	src32 = ((const unsigned long*)(src8 + 1)) - 1;
	dst32 = ((unsigned long*)(dst8 + 1)) - 1;

	i = n >> 5;
	if (i)
		do {
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
			v = *++src32;
			*++dst32 = v;
		} while (--i);

	i = (n & 31) >> 2;
	if (i)
		do {
			v = *++src32;
			*++dst32 = v;
		} while (--i);

	src8 = ((const unsigned char*)(src32 + 1)) - 1;
	dst8 = ((unsigned char*)(dst32 + 1)) - 1;

	n &= 3;
	if (n)
		do
			*++dst8 = *++src8;
		while (--n);
}

void __copy_longs_rev_aligned(void* dst, const void* src, size_t n)
{
	unsigned long i;
	unsigned long v;
	const unsigned char* src8;
	unsigned char* dst8;
	const unsigned long* src32;
	unsigned long* dst32;

	src8 = ((const unsigned char*)src) + n;
	dst8 = ((unsigned char*)dst) + n;

	i = ((unsigned long)dst8) & 3;
	if (i) {
		n -= i;
		do
			*--dst8 = *--src8;
		while (--i);
	}

	src32 = (const unsigned long*)src8;
	dst32 = (unsigned long*)dst8;

	i = n >> 5;
	if (i)
		do {
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
			v = *--src32;
			*--dst32 = v;
		} while (--i);

	i = (n & 31) >> 2;
	if (i)
		do {
			v = *--src32;
			*--dst32 = v;
		} while (--i);

	src8 = (const unsigned char*)src32;
	dst8 = (unsigned char*)dst32;

	n &= 3;
	if (n)
		do
			*--dst8 = *--src8;
		while (--n);
}

void __copy_longs_unaligned(void* dst, const void* src, size_t n)
{
	unsigned long i, v1, v2;
	unsigned int src_offset, left_shift, right_shift;

	i = (-(unsigned long)dst) & 3;

	cps = ((unsigned char*)src) - 1;
	cpd = ((unsigned char*)dst) - 1;

	if (i) {
		n -= i;

		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--i);
	}

	src_offset = ((unsigned int)(cps + 1)) & 3;

	left_shift  = src_offset << 3;
	right_shift = 32 - left_shift;

	cps -= src_offset;

	lps = ((unsigned long*)(cps + 1)) - 1;
	lpd = ((unsigned long*)(cpd + 1)) - 1;

	i = n >> 3;

	v1 = deref_auto_inc(lps);

	do {
		v2                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
		v1                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v2 << left_shift) | (v1 >> right_shift);
	} while (--i);

	if (n & 4) {
		v2                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
	}

	cps = ((unsigned char*)(lps + 1)) - 1;
	cpd = ((unsigned char*)(lpd + 1)) - 1;

	n &= 3;

	if (n) {
		cps -= 4 - src_offset;
		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--n);
	}

	return;
}

void __copy_longs_rev_unaligned(void* dst, const void* src, size_t n)
{
	unsigned long i, v1, v2;
	unsigned int src_offset, left_shift, right_shift;

	cps = ((unsigned char*)src) + n;
	cpd = ((unsigned char*)dst) + n;

	i = ((unsigned long)cpd) & 3;

	if (i) {
		n -= i;

		do
			*--cpd = *--cps;
		while (--i);
	}

	src_offset = ((unsigned int)cps) & 3;

	left_shift  = src_offset << 3;
	right_shift = 32 - left_shift;

	cps += 4 - src_offset;

	i = n >> 3;

	v1 = *--lps;

	do {
		v2     = *--lps;
		*--lpd = (v2 << left_shift) | (v1 >> right_shift);
		v1     = *--lps;
		*--lpd = (v1 << left_shift) | (v2 >> right_shift);
	} while (--i);

	if (n & 4) {
		v2     = *--lps;
		*--lpd = (v2 << left_shift) | (v1 >> right_shift);
	}

	n &= 3;

	if (n) {
		cps += src_offset;
		do
			*--cpd = *--cps;
		while (--n);
	}

	return;
}
