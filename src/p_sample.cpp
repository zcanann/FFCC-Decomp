#include "ffcc/p_sample.h"

extern const char s_CSamplePcs_801D6CC8[];
extern "C" void create__10CSamplePcsFv(CSamplePcs*);
extern "C" void destroy__10CSamplePcsFv(CSamplePcs*);
extern "C" void func0__10CSamplePcsFv(CSamplePcs*);
extern "C" void func1__10CSamplePcsFv(CSamplePcs*);

static unsigned int m_table_desc__10CSamplePcs[4][3] = {
    {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__10CSamplePcsFv)},
    {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__10CSamplePcsFv)},
    {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func0__10CSamplePcsFv)},
    {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func1__10CSamplePcsFv)},
};

CSamplePcsTable m_table__10CSamplePcs = {
    const_cast<char*>(s_CSamplePcs_801D6CC8),
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x10,
        0,
        0,
        0,
        0,
        0x10,
        1,
    },
};

CSamplePcs SamplePcs;

/*
 * --INFO--
 * PAL Address: 0x8001FE74
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onScriptChanging(char*)
{
}

/*
 * --INFO--
 * PAL Address: 0x8001FE78
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onScriptChanged(char*, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8001FE7C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onMapChanging(int, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8001FE80
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProcess::onMapChanged(int, int, int)
{
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
 * PAL Address: 0x8001FE94
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSamplePcs::GetTable(unsigned long index)
{
	return (int)(reinterpret_cast<unsigned char*>(&m_table__10CSamplePcs) + index * 0x15C);
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
 * PAL Address: 0x8001FEB0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CSamplePcs::CSamplePcs()
{
	unsigned int* table = reinterpret_cast<unsigned int*>(&m_table__10CSamplePcs);
	const unsigned int* desc = &m_table_desc__10CSamplePcs[0][0];

	table[1] = desc[0];
	table[2] = desc[1];
	table[3] = desc[2];
	table[4] = desc[3];
	table[5] = desc[4];
	table[6] = desc[5];
	table[7] = desc[6];
	table[8] = desc[7];
	table[9] = desc[8];
	table[12] = desc[9];
	table[13] = desc[10];
	table[14] = desc[11];
}
