#include "ffcc/p_sound.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"

extern "C" void create__9CSoundPcsFv(CSoundPcs*);
extern "C" void destroy__9CSoundPcsFv(CSoundPcs*);
extern "C" void calc__9CSoundPcsFv(CSoundPcs*);
extern "C" void draw__9CSoundPcsFv(CSoundPcs*);

const char s_CSoundPcs_801DB4E8[] = "CSoundPcs";
unsigned int m_table__9CSoundPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CSoundPcs_801DB4E8)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x25, 0, 0, 0, 0, 0x44, 1
};
static const unsigned int sSoundTableInitData[] = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CSoundPcsFv),
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CSoundPcsFv),
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CSoundPcsFv),
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CSoundPcsFv),
};

CSoundPcs SoundPcs;

struct SoundTableInit {
    SoundTableInit()
    {
        unsigned int* table = &m_table__9CSoundPcs[1];

        table[0] = sSoundTableInitData[0];
        table[1] = sSoundTableInitData[1];
        table[2] = sSoundTableInitData[2];
        table[3] = sSoundTableInitData[3];
        table[4] = sSoundTableInitData[4];
        table[5] = sSoundTableInitData[5];
        table[6] = sSoundTableInitData[6];
        table[7] = sSoundTableInitData[7];
        table[8] = sSoundTableInitData[8];
        table[11] = sSoundTableInitData[9];
        table[12] = sSoundTableInitData[10];
        table[13] = sSoundTableInitData[11];
    }
};

static SoundTableInit sSoundTableInit;

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
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table__9CSoundPcs) + (index * 0x15C));
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
