#ifndef _PPP_MANA2_H_
#define _PPP_MANA2_H_

#include "ffcc/chara.h"
#include "ffcc/pppVec.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct Vec;
struct _GXColor;
struct _pppCtrlTable;
struct pppMana2;
struct CTexture;
struct CGObject;

struct Mana2DataOffsets {
    s32 m_unusedOffset;
    s32 m_setupOffset;
    s32 m_workOffset;
};

struct pppMana2Step {
    u8 m_pad00[0x4];
    s32 m_sourceTextureIds[6];
    u8 m_type;
    u8 m_pad1D[0x7];
    s32 m_envTextureId0;
    s32 m_envTextureId1;
    u8 m_pad2C[0x4];
    float m_waterScale;
    float m_rippleHeight;
    u8 m_rippleLevel;
};

struct VMana2 {
    CGObject* m_object;
    void* m_manager;
    CTexture* m_sourceTextures[6];
    GXTexObj* m_baseParaboloidTexObjs;
    void* m_paraboloidMap;
    GXTexObj* m_generatedTexObj0;
    GXTexObj* m_generatedTexObj1;
    void* m_generatedTexture0;
    void* m_generatedTexture1;
    GXColor m_runtimeColor;
    Vec* m_positions;
    Vec* m_normals;
    Vec* m_reflectionVec;
    float* m_waterHeightA;
    float* m_waterHeightB;
    u16* m_indices;
    Vec2d* m_texCoord0;
    Vec2d* m_texCoord1;
    GXColor* m_colors;
    void** m_displayListCopies;
    Vec* m_meshReflectionVec;
    GXColor* m_meshColors;
    S16Vec2d* m_meshTexCoords;
    pppMana2Step* m_step;
    GXTexObj* m_sourceTexObjs;
    CTexture* m_envTexture0;
    CTexture* m_envTexture1;
    Mtx m_waterMtx;
    Mtx m_reflectionMtx;
    u8 m_waterAlpha;
    u8 _padE1[3];
    u32 m_paraboloidMapSize;
    u32 m_displayListSize;
    u8 m_paraboloidReady;
};

void MakeWave(Vec*, unsigned short*, float*, Vec, float, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructMana2(pppMana2*, _pppCtrlTable*);
void pppDestructMana2(pppMana2*, _pppCtrlTable*);
void pppFrameMana2(pppMana2*, pppMana2Step*, _pppCtrlTable*);
void pppRenderMana2(pppMana2*, pppMana2Step*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MANA2_H_
