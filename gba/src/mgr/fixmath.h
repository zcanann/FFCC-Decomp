#ifndef GUARD_FIXMATH_H
#define GUARD_FIXMATH_H

#include "global.h"

/* Sine of a 16-bit angle, indexed by angle >> 5; cosine is at +0x200 */
extern s16 gSinTable[];

/* 8.8 fixed point helpers and 16-bit angles */
s16 FixMul(s16 a, s16 b);
s16 FixDiv(s16 a, s16 b);
s16 FixInv(s16 a);
s16 AngleDiff(s16 a, s16 b);
s16 TurnToward(s16 from, s16 to, s16 max);
s16 FixLerp(s16 a, s16 b, s16 t);

#endif
