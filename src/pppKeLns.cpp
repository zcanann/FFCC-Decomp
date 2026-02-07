#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"

extern float lbl_803305E0;

/*
 * --INFO--
 * PAL Address: 0x800957d4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeLnsLpCon(void* basePtr, void* dataPtr)
{
    void* entry = *(void**)((char*)dataPtr + 0xC);
    _KeLnsLp* kelnsLp = (_KeLnsLp*)((char*)basePtr + *(unsigned int*)entry + 0x80);

    KeLnsLp_Init(kelnsLp);
    *(float*)((char*)kelnsLp + 0x8C) = lbl_803305E0;
    *(float*)((char*)kelnsLp + 0x98) = lbl_803305E0;
}

/*
 * --INFO--
 * PAL Address: 0x800957b4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeLnsLpCon2(void* basePtr, void* dataPtr)
{
    void* entry = *(void**)((char*)dataPtr + 0xC);
    float zero = lbl_803305E0;
    _KeLnsLp* kelnsLp = (_KeLnsLp*)((char*)basePtr + *(unsigned int*)entry + 0x80);

    *(float*)((char*)kelnsLp + 0x8C) = zero;
    *(float*)((char*)kelnsLp + 0x98) = zero;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpDraw(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsCon(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsDraw(void)
{
	return;
}
