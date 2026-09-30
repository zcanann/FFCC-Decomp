#include "global.h"
#include "random.h"

void sgenrand(u32 seed)
{
    s32 i;

    for (i = 0; i < MT_N; i++) {
        gMtState[i] = seed & 0xFFFF0000;
        seed = 69069 * seed + 1;
        gMtState[i] |= (seed & 0xFFFF0000) >> 16;
        seed = 69069 * seed + 1;
    }
    gMtIndex = MT_N;
}

void lsgenrand(u32 *seeds)
{
    s32 i;

    for (i = 0; i < MT_N; i++)
        gMtState[i] = seeds[i];
    gMtIndex = MT_N;
}

u32 genrand(void)
{
    u32 y;
    s32 kk;

    if (gMtIndex >= MT_N) {
        if (gMtIndex == MT_N + 1)
            sgenrand(4357);
        for (kk = 0; kk < MT_N - MT_M; kk++) {
            y = (gMtState[kk] & 0x80000000) | (gMtState[kk + 1] & 0x7FFFFFFF);
            gMtState[kk] = gMtState[kk + MT_M] ^ (y >> 1) ^ gMtMag01[y & 1];
        }
        for (; kk < MT_N - 1; kk++) {
            y = (gMtState[kk] & 0x80000000) | (gMtState[kk + 1] & 0x7FFFFFFF);
            gMtState[kk] = gMtState[kk + (MT_M - MT_N)] ^ (y >> 1) ^ gMtMag01[y & 1];
        }
        y = (gMtState[MT_N - 1] & 0x80000000) | (gMtState[0] & 0x7FFFFFFF);
        gMtState[MT_N - 1] = gMtState[MT_M - 1] ^ (y >> 1) ^ gMtMag01[y & 1];
        gMtIndex = 0;
    }
    y = gMtState[gMtIndex++];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return y;
}
