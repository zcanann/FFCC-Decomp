#ifndef _PPP_YMMANA_H_
#define _PPP_YMMANA_H_

#include "ffcc/chara.h"
#include "ffcc/pppVec.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct _pppCtrlTable;
struct PYmMana;
struct CTexture;
struct CGObject;

struct YmManaDataOffsets {
    s32 m_unusedOffset;
    s32 m_setupOffset;
    s32 m_workOffset;
};

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
    float m_rippleLevel;
    u8 m_map21Flag;
    u8 m_pad39[3];
    GXColor m_baseColor;
};

struct VYmMana {
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
    S16Vec2d* m_meshTexCoords0;
    S16Vec2d* m_meshTexCoords1;
    pppYmManaStep* m_step;
    GXTexObj* m_captureTexObjs;
    CTexture* m_envTexture0;
    CTexture* m_envTexture1;
    u8 _pad84[4];
    Mtx m_waterMtx;
    Mtx m_reflectionMtx;
    u8 m_manaAlpha;
    u8 _padE9[3];
    u32 m_paraboloidMapSize;
    u32 m_displayListSize;
    u8 m_paraboloidReady;
    u8 _padF5[3];
    CGObject* m_attachedObject;
    GXColor m_shadowColor;
    GXColor m_baseColor;
};


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
