#include "ffcc/KeLns.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * PAL Address: 0x8008ed14
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void KeLnsLp_Init(_KeLnsLp* kelnsLp)
{
	pppUnitMatrix(kelnsLp->matrix);
	kelnsLp->field_0x9c = 1.0f;
}
