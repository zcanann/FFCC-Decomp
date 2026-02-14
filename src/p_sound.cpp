#include "ffcc/p_sound.h"

#include "ffcc/sound.h"

extern unsigned char CFlat[];
extern unsigned int lbl_80210580[];
extern unsigned int lbl_8021058C[];
extern unsigned int lbl_80210598[];
extern unsigned int lbl_802105A4[];
extern unsigned char lbl_802105B0[];
extern unsigned int lbl_8021072C[];
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
    unsigned int* a = lbl_80210580;
    unsigned int* b = lbl_8021058C;
    unsigned int* table = (unsigned int*)lbl_802105B0;
    unsigned int* c = lbl_80210598;
    unsigned int* d = lbl_802105A4;

    unsigned int a1 = a[1];
    unsigned int a2 = a[2];
    unsigned int b0 = b[0];
    unsigned int b1 = b[1];
    unsigned int b2 = b[2];
    unsigned int c0 = c[0];
    unsigned int c1 = c[1];
    unsigned int c2 = c[2];
    unsigned int d0 = d[0];
    unsigned int d1 = d[1];
    unsigned int d2 = d[2];
    unsigned int a0 = a[0];

    lbl_8032EDE0 = (unsigned int)&lbl_8021072C;
    table[1] = a0;
    table[2] = a1;
    table[3] = a2;
    table[4] = b0;
    table[5] = b1;
    table[6] = b2;
    table[7] = c0;
    table[8] = c1;
    table[9] = c2;
    table[12] = d0;
    table[13] = d1;
    table[14] = d2;
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
    return lbl_802105B0 + (index * 0x15C);
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
