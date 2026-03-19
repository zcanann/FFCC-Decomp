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
    *reinterpret_cast<void**>(&SoundPcs) = __vt__9CSoundPcs;
    m_table__9CSoundPcs[1] = m_table_desc0__9CSoundPcs[0];
    m_table__9CSoundPcs[2] = m_table_desc0__9CSoundPcs[1];
    m_table__9CSoundPcs[3] = m_table_desc0__9CSoundPcs[2];
    m_table__9CSoundPcs[4] = m_table_desc1__9CSoundPcs[0];
    m_table__9CSoundPcs[5] = m_table_desc1__9CSoundPcs[1];
    m_table__9CSoundPcs[6] = m_table_desc1__9CSoundPcs[2];
    m_table__9CSoundPcs[7] = m_table_desc2__9CSoundPcs[0];
    m_table__9CSoundPcs[8] = m_table_desc2__9CSoundPcs[1];
    m_table__9CSoundPcs[9] = m_table_desc2__9CSoundPcs[2];
    m_table__9CSoundPcs[12] = m_table_desc3__9CSoundPcs[0];
    m_table__9CSoundPcs[13] = m_table_desc3__9CSoundPcs[1];
    m_table__9CSoundPcs[14] = m_table_desc3__9CSoundPcs[2];
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
