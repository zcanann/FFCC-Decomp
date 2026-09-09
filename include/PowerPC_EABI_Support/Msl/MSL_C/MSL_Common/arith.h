#ifndef _MSL_COMMON_ARITH_H
#define _MSL_COMMON_ARITH_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int quot; /* quotient */
	int rem;  /* remainder */
} div_t;

#ifdef __MWERKS__
inline int abs(int value) { return __abs(value); }
#else
int abs(int value);
#endif
div_t div(int numerator, int denominator);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_ARITH_H */
