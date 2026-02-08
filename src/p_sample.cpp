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
	unsigned int a0 = lbl_801E8498[0];
	unsigned int a1 = lbl_801E8498[1];
	unsigned int a2 = lbl_801E8498[2];
	unsigned int b0 = lbl_801E84A4[0];
	unsigned int b1 = lbl_801E84A4[1];
	unsigned int b2 = lbl_801E84A4[2];
	unsigned int c0 = lbl_801E84B0[0];
	unsigned int c1 = lbl_801E84B0[1];
	unsigned int c2 = lbl_801E84B0[2];
	unsigned int d0 = lbl_801E84BC[0];
	unsigned int d1 = lbl_801E84BC[1];
	unsigned int d2 = lbl_801E84BC[2];
	unsigned int* table = (unsigned int*)lbl_801E84C8;

	lbl_8032EC60 = (unsigned int)&lbl_801E8644;

	table[1] = a0;
	table[2] = a1;
	table[3] = a2;
	table[4] = b0;
	table[5] = b1;
	table[6] = b2;
	table[7] = c0;
	table[8] = c1;
	table[9] = c2;
	table[12] = d0;
	table[13] = d1;
	table[14] = d2;
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
