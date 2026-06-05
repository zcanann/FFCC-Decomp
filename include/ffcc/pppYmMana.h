#ifndef _PPP_YMMANA_H_
#define _PPP_YMMANA_H_

#include "ffcc/chara.h"
#include "ffcc/pppVec.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct _pppCtrlTable;
struct PYmMana;
struct VYmMana;
struct CTexture;
struct CGObject;
struct pppYmManaUnkB;

void SetEnvMap(PYmMana*, VYmMana*);
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel*, void*, void*, int);
void Chara_DrawShadowMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*)[4], void*, unsigned long, _GXColor*, S16Vec2d*, S16Vec2d*, CChara::CNode*, PYmMana*, VYmMana*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMana(PYmMana*, _pppCtrlTable*);
void pppDestructYmMana(PYmMana*, _pppCtrlTable*);
void pppFrameYmMana(PYmMana*, pppYmManaUnkB*, _pppCtrlTable*);
void pppRenderYmMana(PYmMana*, pppYmManaUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMANA_H_
