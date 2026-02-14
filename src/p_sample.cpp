#include "ffcc/p_sample.h"

extern unsigned int lbl_801E8498[];
extern unsigned int lbl_801E84A4[];
extern unsigned int lbl_801E84B0[];
extern unsigned int lbl_801E84BC[];
extern unsigned char lbl_801E84C8[];
extern unsigned int lbl_801E8644[];
extern unsigned int lbl_8032EC60;

/*
 * --INFO--
 * PAL Address: 0x8001FEAC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::Init()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FEA8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::Quit()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FE94
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSamplePcs::GetTable(unsigned long index)
{
	return (int)(lbl_801E84C8 + index * 0x15C);
}

/*
 * --INFO--
 * PAL Address: 0x8001FE90
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::create()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FE8C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::destroy()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FE88
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::func0()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FE84
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSamplePcs::func1()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001FEB0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_sample_cpp(void)
{
	lbl_8032EC60 = (unsigned int)&lbl_801E8644;
	((unsigned int*)lbl_801E84C8)[1] = lbl_801E8498[0];
	((unsigned int*)lbl_801E84C8)[2] = lbl_801E8498[1];
	((unsigned int*)lbl_801E84C8)[3] = lbl_801E8498[2];
	((unsigned int*)lbl_801E84C8)[4] = lbl_801E84A4[0];
	((unsigned int*)lbl_801E84C8)[5] = lbl_801E84A4[1];
	((unsigned int*)lbl_801E84C8)[6] = lbl_801E84A4[2];
	((unsigned int*)lbl_801E84C8)[7] = lbl_801E84B0[0];
	((unsigned int*)lbl_801E84C8)[8] = lbl_801E84B0[1];
	((unsigned int*)lbl_801E84C8)[9] = lbl_801E84B0[2];
	((unsigned int*)lbl_801E84C8)[12] = lbl_801E84BC[0];
	((unsigned int*)lbl_801E84C8)[13] = lbl_801E84BC[1];
	((unsigned int*)lbl_801E84C8)[14] = lbl_801E84BC[2];
}

/*
 * --INFO--
 * PAL Address: 0x8001fe74
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onScriptChanging(char*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001fe78
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onScriptChanged(char*, int)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001fe7c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onMapChanging(int, int)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8001fe80
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onMapChanged(int, int, int)
{
	return;
}
