#include "ffcc/KeLns.h"
#include "ffcc/pppPart.h"

extern "C" const float lbl_803305E8;

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
	kelnsLp->field_0x9c = lbl_803305E8;
}
