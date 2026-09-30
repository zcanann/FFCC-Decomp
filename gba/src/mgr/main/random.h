#ifndef GUARD_RANDOM_H
#define GUARD_RANDOM_H

#include "global.h"

/* Mersenne Twister (MT19937) */
#define MT_N 624
#define MT_M 397

extern u32 gMtState[MT_N];
extern s32 gMtIndex;
extern const u32 gMtMag01[2];

void sgenrand(u32 seed);
void lsgenrand(u32 *seeds);
u32 genrand(void);

#endif
