#ifndef _MATH_H
#define _MATH_H

#define M_PI 3.141592653589793

#ifndef _MATH_INLINE
#define _MATH_INLINE static inline
#endif

extern int __float_nan[];
extern int __float_huge[];
extern int __double_huge[];

#define INFINITY (*(float*)__float_huge)
#define NAN (*(float*)__float_nan)
#define HUGE_VAL (*(double*)__double_huge)

#ifdef __MWERKS__
extern inline double sqrt(double x)
{
    if (x > 0.0) {
        double guess = __frsqrte(x); /* returns an approximation to    */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 8 sig bits            */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 16 sig bits            */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 32 sig bits            */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have > 53 sig bits        */
        return x * guess;
    }
    else if (x == 0)
        return 0;
    else if (x)
        return NAN;

    return INFINITY;
}

extern inline float sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;
    union {
        float f;
        unsigned long bits;
    } bits;
    int fpclass;

    if (x > 0.0f) {
        double guess = __frsqrte((double)x); // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
        x = (float)(x * guess);
        return x;
    }

    if ((double)x < 0.0) {
        x = NAN;
        return x;
    }

    bits.f = x;
    switch (bits.bits & 0x7f800000) {
    case 0x7f800000:
        if ((bits.bits & 0x7fffff) != 0) {
            fpclass = 1;
        } else {
            fpclass = 2;
        }
        break;
    case 0:
        if ((bits.bits & 0x7fffff) != 0) {
            fpclass = 5;
        } else {
            fpclass = 3;
        }
        break;
    default:
        fpclass = 4;
        break;
    }

    if (fpclass == 1) {
        x = NAN;
    }

    return x;
}
#else
double sqrt(double x);
float sqrtf(float x);
#endif

double atan(double x);
double copysign(double x, double y);
double cos(double x);
double floor(double x);
double frexp(double x, int *exp);
double ldexp(double x, int exp);
double modf(double x, double *intpart);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan2(double y, double x);
double fmod(double x, double y);
double log(double x);
double pow(double x, double y);
float tanf(float x);

#ifdef __MWERKS__
extern inline double fabs(double x)
{
    return __fabs(x);
}
#else
double fabs(double x);
#endif

_MATH_INLINE float fabsf(float x)
{
    return (float)fabs((double)x);
}
_MATH_INLINE float sinf(float x)
{
    return (float)sin((double)x);
}
_MATH_INLINE float cosf(float x)
{
    return (float)cos((double)x);
}
_MATH_INLINE float atan2f(float y, float x)
{
    return (float)atan2((double)y, (double)x);
}
_MATH_INLINE float atanf(float x)
{
    return (float)atan((double)x);
}
_MATH_INLINE float asinf(float x)
{
    return (float)asin((double)x);
}
_MATH_INLINE float acosf(float x)
{
    return (float)acos((double)x);
}

_MATH_INLINE float fmodf(float x, float m)
{
    return (float)fmod((double)x, (double)m);
}

_MATH_INLINE float floorf(float x)
{
    return floor(x);
}

_MATH_INLINE float powf(float __x, float __y)
{
    return pow(__x, __y);
}

#endif
