#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"

extern "C" void* __vt__9CSoundPcs[];
extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);

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
    unsigned int* table;
    const unsigned int* desc0;
    const unsigned int* desc1;
    const unsigned int* desc2;
    const unsigned int* desc3;

    *reinterpret_cast<unsigned int*>(&SoundPcs) = reinterpret_cast<unsigned int>(__vt__9CSoundPcs);
    table = &m_table__9CSoundPcs[1];
    desc0 = m_table_desc0__9CSoundPcs;
    desc1 = m_table_desc1__9CSoundPcs;
    desc2 = m_table_desc2__9CSoundPcs;
    desc3 = m_table_desc3__9CSoundPcs;
    table[0] = desc0[0];
    table[1] = desc0[1];
    table[2] = desc0[2];
    table[3] = desc1[0];
    table[4] = desc1[1];
    table[5] = desc1[2];
    table[6] = desc2[0];
    table[7] = desc2[1];
    table[8] = desc2[2];
    table[11] = desc3[0];
    table[12] = desc3[1];
    table[13] = desc3[2];
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
