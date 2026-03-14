#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"

CSoundPcs SoundPcs;
extern "C" void* __vt__9CSoundPcs[];
extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
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
    unsigned int* table = m_table__9CSoundPcs;
    unsigned int desc00 = m_table_desc0__9CSoundPcs[0];
    unsigned int desc01 = m_table_desc0__9CSoundPcs[1];
    unsigned int desc02 = m_table_desc0__9CSoundPcs[2];
    unsigned int desc10 = m_table_desc1__9CSoundPcs[0];
    unsigned int desc11 = m_table_desc1__9CSoundPcs[1];
    unsigned int desc12 = m_table_desc1__9CSoundPcs[2];
    unsigned int desc20 = m_table_desc2__9CSoundPcs[0];
    unsigned int desc21 = m_table_desc2__9CSoundPcs[1];
    unsigned int desc22 = m_table_desc2__9CSoundPcs[2];
    unsigned int desc30 = m_table_desc3__9CSoundPcs[0];
    unsigned int desc31 = m_table_desc3__9CSoundPcs[1];
    unsigned int desc32 = m_table_desc3__9CSoundPcs[2];

    *reinterpret_cast<unsigned int*>(&SoundPcs) = reinterpret_cast<unsigned int>(__vt__9CSoundPcs);
    table[1] = desc00;
    table[2] = desc01;
    table[3] = desc02;
    table[4] = desc10;
    table[5] = desc11;
    table[6] = desc12;
    table[7] = desc20;
    table[8] = desc21;
    table[9] = desc22;
    table[12] = desc30;
    table[13] = desc31;
    table[14] = desc32;
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
    Sound.LoadBlock();
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
    Sound.CancelLoadWaveASync();
    Sound.StopStream();
    Sound.StopAndFreeAllSe(1);
    Sound.FreeBlock();
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
    Sound.Frame();
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
        Sound.Draw();
    }
}
