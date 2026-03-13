#include "ffcc/p_sample.h"

extern "C" void* __vt__10CSamplePcs[];

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
	return (int)(m_table__10CSamplePcs + index * 0x15C);
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
	unsigned int* desc0;
	unsigned int* desc1;
	unsigned int* desc3;
	unsigned int* desc2;
	unsigned int* table;
	unsigned int a0;
	unsigned int a1;
	unsigned int a2;
	unsigned int b0;
	unsigned int b1;
	unsigned int b2;
	unsigned int c0;
	unsigned int c1;
	unsigned int c2;
	unsigned int d0;
	unsigned int d1;
	unsigned int d2;

	*reinterpret_cast<void**>(&SamplePcs) = __vt__10CSamplePcs;
	desc0 = m_table_desc0__10CSamplePcs;
	desc1 = m_table_desc1__10CSamplePcs;
	desc3 = m_table_desc3__10CSamplePcs;
	desc2 = m_table_desc2__10CSamplePcs;
	table = reinterpret_cast<unsigned int*>(m_table__10CSamplePcs);

	a0 = desc0[0];
	a1 = desc0[1];
	a2 = desc0[2];
	b0 = desc1[0];
	b1 = desc1[1];
	b2 = desc1[2];
	d0 = desc3[0];
	d1 = desc3[1];
	d2 = desc3[2];
	c0 = desc2[0];
	c1 = desc2[1];
	c2 = desc2[2];

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
