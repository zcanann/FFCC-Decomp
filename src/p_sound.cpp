#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"

CSoundPcs SoundPcs;
extern "C" void* __vt__9CSoundPcs[];
extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
extern "C" void LoadBlock__6CSoundFv(CSound*);
extern "C" void CancelLoadWaveASync__6CSoundFv(CSound*);
extern "C" void StopStream__6CSoundFv(CSound*);
extern "C" void StopAndFreeAllSe__6CSoundFi(CSound*, int);
extern "C" void FreeBlock__6CSoundFv(CSound*);
extern "C" void Frame__6CSoundFv(CSound*);
extern "C" void Draw__6CSoundFv(CSound*);
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
    *reinterpret_cast<void**>(&SoundPcs) = __vt__9CSoundPcs;
    unsigned int* table = (unsigned int*)m_table__9CSoundPcs;

    table[1] = m_table_desc0__9CSoundPcs[0];
    table[2] = m_table_desc0__9CSoundPcs[1];
    table[3] = m_table_desc0__9CSoundPcs[2];
    table[4] = m_table_desc1__9CSoundPcs[0];
    table[5] = m_table_desc1__9CSoundPcs[1];
    table[6] = m_table_desc1__9CSoundPcs[2];
    table[7] = m_table_desc2__9CSoundPcs[0];
    table[8] = m_table_desc2__9CSoundPcs[1];
    table[9] = m_table_desc2__9CSoundPcs[2];
    table[12] = m_table_desc3__9CSoundPcs[0];
    table[13] = m_table_desc3__9CSoundPcs[1];
    table[14] = m_table_desc3__9CSoundPcs[2];
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
