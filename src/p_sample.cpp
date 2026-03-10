#include "ffcc/p_sample.h"

CSamplePcs SamplePcs;
extern "C" void* __vt__10CSamplePcs[];
extern "C" void create__10CSamplePcsFv(CSamplePcs*);
extern "C" void destroy__10CSamplePcsFv(CSamplePcs*);
extern "C" void func0__10CSamplePcsFv(CSamplePcs*);
extern "C" void func1__10CSamplePcsFv(CSamplePcs*);
static unsigned int m_table_desc__10CSamplePcs[12] = {
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(create__10CSamplePcsFv),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(destroy__10CSamplePcsFv),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(func0__10CSamplePcsFv),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(func1__10CSamplePcsFv),
};
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
	unsigned int* desc;
	unsigned int* d0;
	unsigned int* d1;
	unsigned int* d2;
	unsigned int* d3;
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
	unsigned int d0v;
	unsigned int d1v;
	unsigned int d2v;

	*reinterpret_cast<void**>(&SamplePcs) = __vt__10CSamplePcs;
	desc = m_table_desc__10CSamplePcs;
	d0 = desc;
	d1 = desc + 3;
	d2 = desc + 6;
	d3 = desc + 9;
	table = reinterpret_cast<unsigned int*>(m_table__10CSamplePcs);

	a0 = d0[0];
	a1 = d0[1];
	a2 = d0[2];
	b0 = d1[0];
	b1 = d1[1];
	b2 = d1[2];
	c0 = d2[0];
	c1 = d2[1];
	c2 = d2[2];
	d0v = d3[0];
	d1v = d3[1];
	d2v = d3[2];

	table[1] = a0;
	table[2] = a1;
	table[3] = a2;
	table[4] = b0;
	table[5] = b1;
	table[6] = b2;
	table[7] = c0;
	table[8] = c1;
	table[9] = c2;
	table[12] = d0v;
	table[13] = d1v;
	table[14] = d2v;
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
