#include "ffcc/p_sound.h"

#include "ffcc/sound.h"

extern unsigned char CFlat[];
extern unsigned int lbl_80210580[];
extern unsigned int lbl_8021058C[];
extern unsigned int lbl_80210598[];
extern unsigned int lbl_802105A4[];
extern unsigned int lbl_802105B0[];
extern unsigned int lbl_8021072C;
extern unsigned int lbl_8032EDE0;

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
    unsigned int a0 = lbl_80210580[0];
    unsigned int a1 = lbl_80210580[1];
    unsigned int a2 = lbl_80210580[2];
    unsigned int b0 = lbl_8021058C[0];
    unsigned int b1 = lbl_8021058C[1];
    unsigned int b2 = lbl_8021058C[2];
    unsigned int c0 = lbl_80210598[0];
    unsigned int c1 = lbl_80210598[1];
    unsigned int c2 = lbl_80210598[2];
    unsigned int d0 = lbl_802105A4[0];
    unsigned int d1 = lbl_802105A4[1];
    unsigned int d2 = lbl_802105A4[2];

    lbl_8032EDE0 = reinterpret_cast<unsigned int>(&lbl_8021072C);

    lbl_802105B0[1] = a0;
    lbl_802105B0[2] = a1;
    lbl_802105B0[3] = a2;
    lbl_802105B0[4] = b0;
    lbl_802105B0[5] = b1;
    lbl_802105B0[6] = b2;
    lbl_802105B0[7] = c0;
    lbl_802105B0[8] = c1;
    lbl_802105B0[9] = c2;
    lbl_802105B0[12] = d0;
    lbl_802105B0[13] = d1;
    lbl_802105B0[14] = d2;
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
    return reinterpret_cast<unsigned char*>(lbl_802105B0) + (index * 0x15C);
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
