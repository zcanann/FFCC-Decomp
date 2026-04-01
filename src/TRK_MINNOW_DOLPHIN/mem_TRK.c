/**
 * mem_TRK.c
 * Description:
 */

#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"

#pragma dont_inline on
/* 8036F580-8036F638 369EC0 00B8+00 0/0 1/1 0/0 .text            TRK_fill_mem */
void TRK_fill_mem(void* dst, int val, u32 n) {
    u32 i;
    u32 v;
    u8* p8;
    u32* p32;

    v = (u8)val;
    p8 = (u8*)dst - 1;

    if (n > 0x1F) {
        i = (~(u32)p8) & 3;

        if (i != 0) {
            n -= i;

            do {
                i--;
                p8++;
                *p8 = (u8)v;
            } while (i != 0);
        }

        if (v != 0) {
            v = v | v << 8 | v << 24 | v << 16;
        }

        p32 = (u32*)(p8 - 3);
        for (i = n >> 5; i != 0; i--) {
            p32[1] = v;
            p32[2] = v;
            p32[3] = v;
            p32[4] = v;
            p32[5] = v;
            p32[6] = v;
            p32[7] = v;
            p32 += 8;
            *p32 = v;
        }

        for (i = (n >> 2) & 7; i != 0; i--) {
            p32++;
            *p32 = v;
        }

        p8 = (u8*)p32 + 3;
        n &= 3;
    }

    if (n != 0)
        do {
            n--;
            p8++;
            *p8 = (u8)v;
        } while (n != 0);
}
#pragma dont_inline reset

/* 800035C0-800035E4 0004C0 0024+00 0/0 12/12 0/0 .init            TRK_memcpy */
__declspec(section ".init") void* TRK_memcpy(void* dst, const void* src, unsigned int n) {
    const unsigned char* s = (const unsigned char*)src - 1;
    unsigned char* d = (unsigned char*)dst - 1;

    n++;
    while (--n != 0)
        *++d = *++s;
    return dst;
}

/* 80003590-800035C0 000490 0030+00 0/0 1/1 0/0 .init            TRK_memset */
__declspec(section ".init") void* TRK_memset(void* dst, int val, unsigned int n) {
    TRK_fill_mem(dst, val, n);

    return dst;
}
