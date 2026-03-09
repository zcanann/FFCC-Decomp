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
	unsigned int* src;
	unsigned int* table;
	unsigned int d1;
	unsigned int d2;
	unsigned int d3;
	unsigned int d4;
	unsigned int d5;
	unsigned int d6;
	unsigned int d7;
	unsigned int d8;
	unsigned int d9;
	unsigned int d10;
	unsigned int d11;
	unsigned int d0;

	*reinterpret_cast<void**>(&SamplePcs) = __vt__10CSamplePcs;
	src = m_table_desc0__10CSamplePcs;
	table = reinterpret_cast<unsigned int*>(m_table__10CSamplePcs);
	d1 = src[1];
	d2 = src[2];
	d3 = src[3];
	d4 = src[4];
	d5 = src[5];
	d6 = src[6];
	d7 = src[7];
	d8 = src[8];
	d9 = src[9];
	d10 = src[10];
	d11 = src[11];
	d0 = src[0];
	table[2] = d1;
	table[1] = d0;
	table[3] = d2;
	table[4] = d3;
	table[5] = d4;
	table[6] = d5;
	table[7] = d6;
	table[8] = d7;
	table[9] = d8;
	table[12] = d9;
	table[13] = d10;
	table[14] = d11;
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
