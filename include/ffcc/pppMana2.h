#ifndef _PPP_MANA2_H_
#define _PPP_MANA2_H_

#include "ffcc/chara.h"

#include <dolphin/mtx.h>

struct Vec;
struct Vec2d;
struct _GXColor;
struct VMana2;
struct pppMana2;
struct pppMana2UnkB;
struct pppMana2UnkC {
    s32* m_serializedDataOffsets;
};

void Mana2_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*)[4], void*, unsigned long, _GXColor*, S16Vec2d*, CChara::CNode*);
void MakeWave(Vec*, unsigned short*, float*, Vec*, float, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructMana2(pppMana2*, pppMana2UnkC*);
void pppDestructMana2(pppMana2*, pppMana2UnkC*);
void pppFrameMana2(pppMana2*, pppMana2UnkB*, pppMana2UnkC*);
void pppRenderMana2(pppMana2*, pppMana2UnkB*, pppMana2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MANA2_H_
