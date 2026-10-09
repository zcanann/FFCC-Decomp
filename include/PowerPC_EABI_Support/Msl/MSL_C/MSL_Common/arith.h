#ifndef _MSL_COMMON_ARITH_H
#define _MSL_COMMON_ARITH_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int quot; /* quotient */
	int rem;  /* remainder */
} div_t;

int abs(int value);
#ifdef __MWERKS__
#define abs(n) __abs(n)
#endif
div_t div(int numerator, int denominator);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_ARITH_H */
