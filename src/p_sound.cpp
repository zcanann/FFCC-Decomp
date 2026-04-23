#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"

extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);
extern char __RTTI__8CManager[];
extern char __RTTI__8CProcess[];

const char s_CSoundPcs_801DB4E8[] = "CSoundPcs";
CSoundPcsTable m_table__9CSoundPcs = {
    const_cast<char*>(s_CSoundPcs_801DB4E8),
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
        0x25,
        0,
        0,
        0,
        0,
        0x44,
        1,
    }
};
unsigned int CSoundPcs_RTTI_base__9CSoundPcs[3] = {reinterpret_cast<unsigned int>(__RTTI__8CManager), 0, 0};
unsigned int CSoundPcs_RTTI__9CSoundPcs[5] = {
    reinterpret_cast<unsigned int>(__RTTI__8CManager), 0, reinterpret_cast<unsigned int>(__RTTI__8CProcess), 0, 0
};

CSoundPcs SoundPcs;

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
 * PAL Address: 0x800d87f0
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSoundPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(&m_table__9CSoundPcs) + (index * 0x15C));
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
 * PAL Address: 0x800d880c
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSoundPcs::Init()
{
}

inline CSoundPcs::CSoundPcs()
{
    static unsigned int desc0[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CSoundPcsFv)};
    static unsigned int desc1[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CSoundPcsFv)};
    static unsigned int desc2[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CSoundPcsFv)};
    static unsigned int desc3[] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CSoundPcsFv)};
    unsigned int* table = reinterpret_cast<unsigned int*>(&m_table__9CSoundPcs);

    table[1] = desc0[0];
    table[2] = desc0[1];
    table[3] = desc0[2];
    table[4] = desc1[0];
    table[5] = desc1[1];
    table[6] = desc1[2];
    table[7] = desc2[0];
    table[8] = desc2[1];
    table[9] = desc2[2];
    table[12] = desc3[0];
    table[13] = desc3[1];
    table[14] = desc3[2];
}
