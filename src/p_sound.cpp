#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"

CSoundPcs SoundPcs;
extern "C" void* __vt__9CSoundPcs[];
extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
extern "C" void LoadBlock__6CSoundFv(void*);
extern "C" void CancelLoadWaveASync__6CSoundFv(void*);
extern "C" void StopStream__6CSoundFv(void*);
extern "C" void StopAndFreeAllSe__6CSoundFi(void*, int);
extern "C" void FreeBlock__6CSoundFv(void*);
extern "C" void Frame__6CSoundFv(void*);
extern "C" void Draw__6CSoundFv(void*);
char s_CSoundPcs_801DB4E8[] = "CSoundPcs";
unsigned int m_table_desc0__9CSoundPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CSoundPcsFv)};
unsigned int m_table_desc1__9CSoundPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CSoundPcsFv)};
unsigned int m_table_desc2__9CSoundPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CSoundPcsFv)};
unsigned int m_table_desc3__9CSoundPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CSoundPcsFv)};
unsigned int m_table__9CSoundPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(s_CSoundPcs_801DB4E8), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x25, 0, 0, 0, 0, 0x44, 1
};

/*
 * --INFO--
 * PAL Address: 0x800d880c
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_sound_cpp(void)
{
	struct DescBlock {
		unsigned int d[12];
	};
	DescBlock* src;
	unsigned int* table;
	unsigned int d0;
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

	*reinterpret_cast<void**>(&SoundPcs) = __vt__9CSoundPcs;
	src = reinterpret_cast<DescBlock*>(m_table_desc0__9CSoundPcs);
	table = reinterpret_cast<unsigned int*>(m_table__9CSoundPcs);

	d1 = src->d[1];
	d2 = src->d[2];
	d3 = src->d[3];
	d4 = src->d[4];
	d5 = src->d[5];
	d6 = src->d[6];
	d7 = src->d[7];
	d8 = src->d[8];
	d9 = src->d[9];
	d10 = src->d[10];
	d11 = src->d[11];
	d0 = src->d[0];

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
 * PAL Address: 0x800d8808
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::Init()
{
}

/*
 * --INFO--
 * PAL Address: 0x800d8804
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::Quit()
{
}

/*
 * --INFO--
 * PAL Address: 0x800d87f0
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CSoundPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<unsigned char*>(m_table__9CSoundPcs) + (index * 0x15C);
}

/*
 * --INFO--
 * PAL Address: 0x800d87ec
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::create()
{
}

/*
 * --INFO--
 * PAL Address: 0x800d87c4
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::createLoad()
{
    LoadBlock__6CSoundFv(&Sound);
}

/*
 * --INFO--
 * PAL Address: 0x800d8774
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::destroy()
{
    CancelLoadWaveASync__6CSoundFv(&Sound);
    StopStream__6CSoundFv(&Sound);
    StopAndFreeAllSe__6CSoundFi(&Sound, 1);
    FreeBlock__6CSoundFv(&Sound);
}

/*
 * --INFO--
 * PAL Address: 0x800d874c
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::calc()
{
    Frame__6CSoundFv(&Sound);
}

/*
 * --INFO--
 * PAL Address: 0x800d8710
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::draw()
{
    if ((*(unsigned int*)(CFlat + 0x129C) & 0x400000) != 0) {
        Draw__6CSoundFv(&Sound);
    }
}
