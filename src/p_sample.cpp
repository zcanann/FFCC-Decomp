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
	unsigned int* table;
	unsigned int* table0;
	unsigned int* table1;
	unsigned int* table2;
	unsigned int* table3;

	*reinterpret_cast<void**>(&SamplePcs) = __vt__10CSamplePcs;
	table = reinterpret_cast<unsigned int*>(m_table__10CSamplePcs);
	table0 = m_table_desc0__10CSamplePcs;
	table1 = m_table_desc1__10CSamplePcs;
	table2 = m_table_desc2__10CSamplePcs;
	table3 = m_table_desc3__10CSamplePcs;

	table[1] = table0[0];
	table[2] = table0[1];
	table[3] = table0[2];
	table[4] = table1[0];
	table[5] = table1[1];
	table[6] = table1[2];
	table[7] = table2[0];
	table[8] = table2[1];
	table[9] = table2[2];
	table[12] = table3[0];
	table[13] = table3[1];
	table[14] = table3[2];
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
