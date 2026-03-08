#include "ffcc/p_sample.h"

extern unsigned int PTR_PTR_s_CSamplePcs_801e8644[];

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
	*reinterpret_cast<unsigned int*>(&SamplePcs) = (unsigned int)&PTR_PTR_s_CSamplePcs_801e8644;
	((unsigned int*)m_table__10CSamplePcs)[1] = m_table_desc0__10CSamplePcs[0];
	((unsigned int*)m_table__10CSamplePcs)[2] = m_table_desc0__10CSamplePcs[1];
	((unsigned int*)m_table__10CSamplePcs)[3] = m_table_desc0__10CSamplePcs[2];
	((unsigned int*)m_table__10CSamplePcs)[4] = m_table_desc1__10CSamplePcs[0];
	((unsigned int*)m_table__10CSamplePcs)[5] = m_table_desc1__10CSamplePcs[1];
	((unsigned int*)m_table__10CSamplePcs)[6] = m_table_desc1__10CSamplePcs[2];
	((unsigned int*)m_table__10CSamplePcs)[7] = m_table_desc2__10CSamplePcs[0];
	((unsigned int*)m_table__10CSamplePcs)[8] = m_table_desc2__10CSamplePcs[1];
	((unsigned int*)m_table__10CSamplePcs)[9] = m_table_desc2__10CSamplePcs[2];
	((unsigned int*)m_table__10CSamplePcs)[12] = m_table_desc3__10CSamplePcs[0];
	((unsigned int*)m_table__10CSamplePcs)[13] = m_table_desc3__10CSamplePcs[1];
	((unsigned int*)m_table__10CSamplePcs)[14] = m_table_desc3__10CSamplePcs[2];
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
