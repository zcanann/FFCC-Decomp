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

struct pppYmManaStep {
    u8 m_pad00[4];
    s32 m_sourceTextureId2;
    s32 m_sourceTextureId1;
    s32 m_sourceTextureId0;
    s32 m_sourceTextureId3;
    s32 m_sourceTextureId4;
    s32 m_sourceTextureId5;
    u8 m_type;
    u8 m_pad1D[7];
    s32 m_envTextureId0;
    s32 m_envTextureId1;
    float m_waterScale;
    float m_waterOffset;
    u32 m_rippleLevel;
    u8 m_map21Flag;
    u8 m_pad39[3];
    GXColor m_baseColor;
};

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
void pppFrameYmMana(PYmMana*, pppYmManaStep*, _pppCtrlTable*);
void pppRenderYmMana(PYmMana*, pppYmManaStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMANA_H_
