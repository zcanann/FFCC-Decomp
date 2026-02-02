

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */

extern double __ieee754_sqrt(double x);

double sqrt(double x)
{
	return __ieee754_sqrt(x);
}