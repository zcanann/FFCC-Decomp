extern "C" {
#include "global.h"
#include "fixmath.h"

s16 FixMul(s16 a, s16 b)
{
    s32 v = a * b;

    v /= 256;
    return v;
}

s16 FixDiv(s16 a, s16 b)
{
    return (a << 8) / b;
}

s16 FixInv(s16 a)
{
    s32 n = 0x10000;

    return n / a;
}

s16 AngleDiff(s16 a, s16 b)
{
    s32 d = (a - b) & 0xFFFF;

    if (d > 0x8000)
        return d - 0x10000;
    return d;
}

s16 TurnToward(s16 from, s16 to, s16 max)
{
    s16 d = AngleDiff(to, from);

    if (d > 0) {
        if (d > max)
            return max;
        return d;
    }
    if (d < 0) {
        max = -max;
        if (d < max)
            return max;
        return d;
    }
    return 0;
}

s16 FixLerp(s16 a, s16 b, s16 t)
{
    return a + (((s16)(b - a) * t) >> 8);
}
}
