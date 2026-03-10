#include "ffcc/p_sample.h"

CSamplePcs SamplePcs;
extern "C" void* __vt__10CSamplePcs[];
extern "C" void create__10CSamplePcsFv(CSamplePcs*);
extern "C" void destroy__10CSamplePcsFv(CSamplePcs*);
extern "C" void func0__10CSamplePcsFv(CSamplePcs*);
extern "C" void func1__10CSamplePcsFv(CSamplePcs*);
unsigned int m_table_desc0__10CSamplePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CSamplePcsFv)};
unsigned int m_table_desc1__10CSamplePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CSamplePcsFv)};
unsigned int m_table_desc2__10CSamplePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func0__10CSamplePcsFv)};
unsigned int m_table_desc3__10CSamplePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func1__10CSamplePcsFv)};
unsigned char m_table__10CSamplePcs[0x15C];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSamplePcs::CSamplePcs() {}

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
	unsigned int* desc2;
	unsigned int* desc3;
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
	desc2 = m_table_desc2__10CSamplePcs;
	desc3 = m_table_desc3__10CSamplePcs;
	table = reinterpret_cast<unsigned int*>(m_table__10CSamplePcs);

	a0 = desc0[0];
	a1 = desc0[1];
	a2 = desc0[2];
	b0 = desc1[0];
	b1 = desc1[1];
	b2 = desc1[2];
	c0 = desc2[0];
	c1 = desc2[1];
	c2 = desc2[2];
	d0 = desc3[0];
	d1 = desc3[1];
	d2 = desc3[2];

	table[17] = a0;
	table[18] = a1;
	table[19] = a2;
	table[20] = b0;
	table[21] = b1;
	table[22] = b2;
	table[23] = c0;
	table[24] = c1;
	table[25] = c2;
	table[30] = d0;
	table[31] = d1;
	table[32] = d2;
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
