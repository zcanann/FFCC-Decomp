#include "ffcc/p_sound.h"

extern unsigned char CFlat[];
extern unsigned int lbl_80210580[];
extern unsigned int lbl_8021058C[];
extern unsigned int lbl_80210598[];
extern unsigned int lbl_802105A4[];
extern unsigned char lbl_802105B0[];
extern unsigned int lbl_8021072C[];
extern unsigned int lbl_8032EDE0;
class CSound;
extern CSound Sound[];
extern "C" {
void LoadBlock__6CSoundFv(CSound*);
void CancelLoadWaveASync__6CSoundFv(CSound*);
void StopStream__6CSoundFv(CSound*);
void StopAndFreeAllSe__6CSoundFi(CSound*, int);
void FreeBlock__6CSoundFv(CSound*);
void Frame__6CSoundFv(CSound*);
void Draw__6CSoundFv(CSound*);
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
extern "C" void __sinit_p_sound_cpp(void)
{
    unsigned int* table = (unsigned int*)lbl_802105B0;

    lbl_8032EDE0 = (unsigned int)&lbl_8021072C;

    table[1] = lbl_80210580[0];
    table[2] = lbl_80210580[1];
    table[3] = lbl_80210580[2];
    table[4] = lbl_8021058C[0];
    table[5] = lbl_8021058C[1];
    table[6] = lbl_8021058C[2];
    table[7] = lbl_80210598[0];
    table[8] = lbl_80210598[1];
    table[9] = lbl_80210598[2];
    table[12] = lbl_802105A4[0];
    table[13] = lbl_802105A4[1];
    table[14] = lbl_802105A4[2];
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
    LoadBlock__6CSoundFv(Sound);
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
    CancelLoadWaveASync__6CSoundFv(Sound);
    StopStream__6CSoundFv(Sound);
    StopAndFreeAllSe__6CSoundFi(Sound, 1);
    FreeBlock__6CSoundFv(Sound);
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
    Frame__6CSoundFv(Sound);
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
        Draw__6CSoundFv(Sound);
    }
}
