#include "ffcc/ptrarray.h"
#include "ffcc/materialman.h"
#include "ffcc/game.h"
#include "ffcc/map.h"
#include "ffcc/mapobj.h"
#include "ffcc/mapocttree.h"
#include "ffcc/pad.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"
#include "ffcc/vector.h"
#include "ffcc/graphic.h"
#include "ffcc/p_camera.h"
#include "ffcc/gxfunc.h"

#include <dolphin/mtx.h>

#include <string.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

CMaterialMan MaterialMan;
CMaterial* g_drawMaterial;

inline void* operator new(unsigned long, void* p)
{
    return p;
}

static inline void _GXSetTevOp(int stage, int mode)
{
    _GXSetTevOp((_GXTevStageID)stage, (_GXTevMode)mode);
}

static inline void _GXSetTevSwapMode(int stage, int rasSel, int texSel)
{
    _GXSetTevSwapMode((_GXTevStageID)stage, (_GXTevSwapSel)rasSel, (_GXTevSwapSel)texSel);
}

static inline void _GXSetAlphaCompare(int comp0, int ref0, int op, int comp1, int ref1)
{
    _GXSetAlphaCompare((_GXCompare)comp0, (unsigned char)ref0, (_GXAlphaOp)op, (_GXCompare)comp1, (unsigned char)ref1);
}

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

struct ShadowCandidate
{
    CMapShadow* shadow;
    float distance;
    int index;
};

static inline CLightPcs::CBumpLight* GetMapBumpLight(int bumpIndex)
{
    return LightPcs.GetBumpLight(static_cast<CLightPcs::TARGET>(1), bumpIndex);
}

static inline void ReleaseRefNonNull(CRef* object)
{
    if (object->DecRef() == 0) {
        delete object;
    }
}

static inline void ReleaseRef(CRef* object)
{
    if (object == 0) {
        return;
    }

    ReleaseRefNonNull(object);
}

static inline int HighestSetBit(unsigned int value)
{
    for (int bit = 31; bit >= 0; bit--) {
        if ((value & (1u << bit)) != 0) {
            return bit;
        }
    }
    return -1;
}

static inline CMaterial* AllocMaterial()
{
    return new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", 0xCFF) CMaterial;
}

static inline void AddTextureIndex(CMaterial* material, CChunkFile& chunkFile)
{
    material->AddTextureIdx(chunkFile);
}

static inline CMapKeyFrame* AllocMapKeyFrame(int line)
{
    return new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", line) CMapKeyFrame();
}

static inline void SetMaterialColor(CMaterial* material, unsigned int rgba)
{
    material->SetMaterialColor(rgba);
}
}

/*
 * --INFO--
 * PAL Address: 0x80041F28
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetButtonDown(long padIndex)
{
    bool shouldZero = false;
    unsigned int result;

    if (m_debugPadLock == 0) {
        if (padIndex != 0) {
            goto read_slot;
        }
        if (m_debugPadPort == -1) {
            goto read_slot;
        }
    }

    shouldZero = true;
read_slot:
    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].buttonDown[0];
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004F400
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMaterialMan::CMaterialMan()
    : m_color213()
{
}

/*
 * --INFO--
 * PAL Address: 0x80043A28
 * PAL Size: 80b
 * EN Address: 0x800468D4
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::Init()
{
	m_materialStage = Memory.CreateStage(0x20000, const_cast<char*>("CMaterial.material"), 0);
	m_fullShadowTevColor = 0x30;
}

/*
 * --INFO--
 * PAL Address: 0x800439F8
 * PAL Size: 48b
 * EN Address: 0x80046924
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::Quit()
{
	Memory.DestroyStage(m_materialStage);
}

/*
 * --INFO--
 * PAL Address: 0x800436AC
 * PAL Size: 844b
 * EN Address: 0x8004695C
 * EN Size: 896b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetBlendMode(CMaterialSet* materialSet, int materialIndex)
{
    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = materials->GetAt(materialIndex);

    unsigned char fogEnable = material->m_fogEnable;
    if ((static_cast<int>(Game.m_currentSceneId) == 3) && (MapMng.m_fogEnable == 0)) {
        fogEnable = 0;
    }

    unsigned char blendMode = material->m_blendMode;
    if (m_blendOverrideMode != 0xFF) {
        if (blendMode == 0) {
            blendMode = 5;
        } else if (blendMode == 4) {
            blendMode = 1;
        }
    }

    if ((m_blendMode == blendMode) && (m_fogEnable == fogEnable)) {
        return;
    }

    m_blendMode = blendMode;
    m_fogEnable = fogEnable;

    switch (m_blendMode) {
    case 0:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        _GXSetAlphaCompare(6, 0xC0, 0, 7, 0xFF);
        GXSetZCompLoc(0);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 1:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 2:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 1);
        return;

    case 3:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 1);
        return;

    case 4:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 5:
        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        _GXSetAlphaCompare(6, 1, 0, 7, 0xFF);
        GXSetZCompLoc(0);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    default:
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80043268
 * PAL Size: 1092b
 * EN Address: 0x80046CDC
 * EN Size: 1072b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_st(int mode, _GXTevScale tevScale)
{
    float indMtx[6];

    GXSetIndTexMtx((GXIndTexMtxID)1, reinterpret_cast<const float(*)[3]>(indMtx), 0);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(static_cast<GXIndTexStageID>(0),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale(static_cast<GXIndTexStageID>(0),
                          static_cast<GXIndTexScale>(static_cast<u8>(g_drawMaterial->m_texShiftU)),
                          static_cast<GXIndTexScale>(static_cast<u8>(g_drawMaterial->m_texShiftV)));

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, tevScale, 1,
        GX_TEVPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    if (mode != 0) {
        return;
    }

    GXSetTevIndirect((GXTevStageID)1, (GXIndTexStageID)0, (GXIndTexFormat)0, (GXIndTexBiasSel)3, (GXIndTexMtxID)5,
                     (GXIndTexWrap)6, (GXIndTexWrap)6, GX_FALSE, GX_FALSE, (GXIndTexAlphaSel)0);
    GXSetTevIndirect((GXTevStageID)2, (GXIndTexStageID)0, (GXIndTexFormat)0, (GXIndTexBiasSel)3, (GXIndTexMtxID)9,
                     (GXIndTexWrap)6, (GXIndTexWrap)6, GX_TRUE, GX_FALSE, (GXIndTexAlphaSel)0);
    GXSetTevIndirect((GXTevStageID)3, (GXIndTexStageID)0, (GXIndTexFormat)0, (GXIndTexBiasSel)0, (GXIndTexMtxID)0,
                     (GXIndTexWrap)0, (GXIndTexWrap)0, GX_TRUE, GX_FALSE, (GXIndTexAlphaSel)0);

    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[1]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1] | 0x100), GX_COLOR_NULL);
    _GXSetTevOp(m_numTevStage, 4);
    IncNumTevStage();

    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[2]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1] | 0x100), GX_COLOR_NULL);
    _GXSetTevOp(m_numTevStage, 4);
    IncNumTevStage();

    if (g_drawMaterial->m_bumpLightDirect == 0) {
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[3]),
            static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        IncNumTevStage();
        return;
    }

    int hasProjTex = g_drawMaterial->m_textureIndices[3] >= 0;
    if (hasProjTex != 0) {
        GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[6]), GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY,
                          GX_FALSE, GX_PTIDENTITY);
    }

    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[3]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
    _GXSetTevColorIn(
        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C1, GX_CC_TEXA,
        static_cast<_GXTevColorArg>(hasProjTex ? (_GXTevColorArg)0xF : (_GXTevColorArg)0));
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
        static_cast<_GXTevRegID>(hasProjTex != 0));
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();

    if (hasProjTex == 0) {
        return;
    }

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[6]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[3]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_CPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042F14
 * PAL Size: 852b
 * EN Address: 0x80047154
 * EN Size: 812b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_water(_GXTevScale tevScale)
{
    float warpMtx[6];

    GXSetIndTexMtx((GXIndTexMtxID)1, LightPcs.GetBumpIndTexMtx(), 0);
    warpMtx[0] = 0.1f;
    warpMtx[1] = 0.0f;
    warpMtx[2] = 0.0f;
    warpMtx[3] = 0.0f;
    warpMtx[4] = 0.1f;
    warpMtx[5] = 0.0f;
    GXSetIndTexMtx((GXIndTexMtxID)2, reinterpret_cast<const float(*)[3]>(warpMtx), 1);
    GXSetNumIndStages(2);

    GXSetTevDirect((GXTevStageID)m_numTevStage);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, tevScale, 1,
        GX_TEVPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetIndTexOrder(static_cast<GXIndTexStageID>(0),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale((GXIndTexStageID)0, (GXIndTexScale)0, (GXIndTexScale)0);
    GXSetIndTexOrder(static_cast<GXIndTexStageID>(1),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale((GXIndTexStageID)1, (GXIndTexScale)0, (GXIndTexScale)0);

    GXSetTevIndBumpXYZ((GXTevStageID)m_numTevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[3]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();

    GXSetTevIndBumpXYZ((GXTevStageID)m_numTevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[4]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_CPREV, GX_CC_ONE, GX_CC_TEXA);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();

    GXSetTevIndWarp((GXTevStageID)m_numTevStage, (GXIndTexStageID)1, GX_TRUE, GX_FALSE, (GXIndTexMtxID)2);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[5]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[2]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_TEXC, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042C60
 * PAL Size: 692b
 * EN Address: 0x80047480
 * EN Size: 664b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_spec_col_water(_GXTevScale tevScale)
{
    float warpMtx[6];

    GXSetIndTexMtx((GXIndTexMtxID)1, LightPcs.GetBumpIndTexMtx(), 0);
    warpMtx[0] = 0.1f;
    warpMtx[1] = 0.0f;
    warpMtx[2] = 0.0f;
    warpMtx[3] = 0.0f;
    warpMtx[4] = 0.1f;
    warpMtx[5] = 0.0f;
    GXSetIndTexMtx((GXIndTexMtxID)2, reinterpret_cast<const float(*)[3]>(warpMtx), 1);
    GXSetNumIndStages(2);

    GXSetTevDirect((GXTevStageID)m_numTevStage);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, tevScale, 1,
        GX_TEVPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetIndTexOrder(static_cast<GXIndTexStageID>(0),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale((GXIndTexStageID)0, (GXIndTexScale)0, (GXIndTexScale)0);
    GXSetIndTexOrder(static_cast<GXIndTexStageID>(1),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale((GXIndTexStageID)1, (GXIndTexScale)0, (GXIndTexScale)0);

    GXSetTevIndBumpXYZ((GXTevStageID)m_numTevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[4]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C1, GX_CC_TEXA, GX_CC_CPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();

    GXSetTevIndWarp((GXTevStageID)m_numTevStage, (GXIndTexStageID)1, GX_TRUE, GX_FALSE, (GXIndTexMtxID)2);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[5]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[2]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_TEXC, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042B58
 * PAL Size: 264b
 * EN Address: 0x80047718
 * EN Size: 252b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_jimen(_GXTevScale)
{
    GXSetIndTexMtx((GXIndTexMtxID)1, LightPcs.GetBumpIndTexMtx(), 0);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(static_cast<GXIndTexStageID>(0),
                     static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]),
                     static_cast<GXTexMapID>(m_bumpTexMapIds[0]));
    GXSetIndTexCoordScale((GXIndTexStageID)0, (GXIndTexScale)0, (GXIndTexScale)0);

    GXSetTevIndBumpXYZ((GXTevStageID)m_numTevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_bumpTexCoordIds[4]),
        static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C1, GX_CC_TEXA, GX_CC_CPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    m_numTevStage =
        (((m_numTevStage) & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x80042814
 * PAL Size: 836b
 * EN Address: 0x80047814
 * EN Size: 868b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_lightmap(long index)
{
    if ((m_shadowKColorMask & (1 << index)) != 0) {
        GXColor kcolor;
        kcolor.r = 0;
        kcolor.g = 0;
        kcolor.b = 0;
        kcolor.a = m_shadowKColorIds[index];
        GXSetTevKColor(static_cast<GXTevKColorID>(index), kcolor);

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index]), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG1);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index] + 1), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), static_cast<GXTevKColorSel>(index + 0x1C));
        _GXSetTevOrder(static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_C1, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    } else {
        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index]), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    }
}

/*
 * --INFO--
 * PAL Address: 0x800424D0
 * PAL Size: 836b
 * EN Address: 0x80047B78
 * EN Size: 868b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_shadow(long index)
{
    if ((m_shadowKColorMask & (1 << index)) != 0) {
        GXColor kcolor;
        kcolor.r = 0;
        kcolor.g = 0;
        kcolor.b = 0;
        kcolor.a = m_shadowKColorIds[index];
        GXSetTevKColor(static_cast<GXTevKColorID>(index), kcolor);

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index]), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG1);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index] + 1), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), static_cast<GXTevKColorSel>(index + 0x1C));
        _GXSetTevOrder(static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_C1, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    } else {
        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_shadowTexCoordIds[index]),
            static_cast<_GXTexMapID>(m_shadowTexMapIds[index]), GX_COLOR_NULL);
        _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        _GXSetTevColorOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        _GXSetTevAlphaOp(
            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80042454
 * PAL Size: 124b
 * EN Address: 0x80047EDC
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_stdShadow(unsigned long materialFlag)
{
    if ((materialFlag & 0x10) == 0) {
        return;
    }

    for (int i = 0; i < m_shadowMaterialCount; i++) {
        if (m_shadowMaterialType[i] != 0) {
            addtev_lightmap(i);
        } else {
            addtev_shadow(i);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80042180
 * PAL Size: 724b
 * EN Address: 0x80047F64
 * EN Size: 744b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_full_shadow(long index)
{
    GXLoadTexMtxImm(m_fullScreenShadowMtx0, m_fullScreenShadowTexMtxIds0[0], GX_MTX3x4);
    GXLoadTexObj(m_fullScreenShadowTexObj0, static_cast<GXTexMapID>(m_fullScreenShadowTexMapIds0[0]));
    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_fullScreenShadowTexCoordIds0[0]),
                      GX_TG_MTX3x4,
                      GX_TG_POS,
                      m_fullScreenShadowTexMtxIds0[0],
                      GX_FALSE,
                      0x7D);

    GXLoadTexMtxImm(m_fullScreenShadowMtx1, m_fullScreenShadowTexMtxIds1[0], GX_MTX3x4);
    GXLoadTexObj(m_fullScreenShadowTexObj1, static_cast<GXTexMapID>(m_fullScreenShadowTexMapIds1[0]));
    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_fullScreenShadowTexCoordIds1[0]),
                      GX_TG_MTX3x4,
                      GX_TG_POS,
                      m_fullScreenShadowTexMtxIds1[0],
                      GX_FALSE,
                      0x7D);

    GXColor tevColor;
    tevColor.r = 0;
    tevColor.g = 0;
    tevColor.b = 0;
    tevColor.a = static_cast<unsigned char>(m_fullShadowTevColor);
    GXSetTevColor(static_cast<GXTevRegID>(1), tevColor);

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage),
        static_cast<_GXTexCoordID>(m_fullScreenShadowTexCoordIds1[index]),
        static_cast<_GXTexMapID>(m_fullScreenShadowTexMapIds1[index]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        static_cast<_GXTevStageID>(m_numTevStage),
        static_cast<_GXTexCoordID>(m_fullScreenShadowTexCoordIds0[index]),
        static_cast<_GXTexMapID>(m_fullScreenShadowTexMapIds0[index]), GX_COLOR_NULL);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_C0, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_ZERO, GX_CC_C0, GX_CC_ZERO);
    _GXSetTevColorOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevAlphaIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(
        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042010
 * PAL Size: 368b
 * EN Address: 0x8004824C
 * EN Size: 740b
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_common_subs off
void CMaterialMan::SetUnderWaterTex()
{
    int x = 0;
    int y = 0;
    int width = 0x280;
    int height = 0x1C0;

    m_underWaterTexture = Graphic.GetBackBufferRect(x, y, width, height, 1);
    if (m_underWaterTexture == 0) {
        return;
    }

    Mtx44 screenMtx;
    Mtx matrixB;
    Mtx matrixA;
    PSMTXIdentity(matrixA);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    PSMTXCopy(CameraPcs.m_cameraMatrix, matrixB);

    matrixA[0][0] = screenMtx[0][0];
    matrixA[1][0] = screenMtx[1][0];
    matrixA[2][0] = screenMtx[2][0];
    matrixA[0][1] = screenMtx[0][1];
    matrixA[1][1] = screenMtx[1][1];
    matrixA[2][1] = screenMtx[2][1];
    matrixA[0][2] = screenMtx[0][2];
    matrixA[1][2] = screenMtx[1][2];
    matrixA[2][2] = screenMtx[2][2];
    matrixA[0][0] *= (320.0f / static_cast<float>(width));
    matrixA[1][1] *= -(224.0f / static_cast<float>(height));
    matrixA[0][2] = -0.5f;
    matrixA[1][2] = -0.5f;
    matrixA[2][2] = -1.0f;

    PSMTXConcat(matrixA, matrixB, m_underWaterTexMtx);
}
#pragma opt_common_subs reset

/*
 * --INFO--
 * PAL Address: 0x8003FDF0
 * PAL Size: 8504b
 * EN Address: 0x80048530
 * EN Size: 9316b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterial(CMaterialSet* materialSet, int materialIndex, int setVtxDesc, _GXTevScale tevScale)
{
    static int bTest;
    static char init;
    static int bTest2;
    static char init2;

    SetStdEnv();

    CMaterial* material = materialSet->m_materials.GetAt(materialIndex);
    g_drawMaterial = material;
    int isStd1000 = 0;

    if (material->m_bumpLight != 0) {
        if (material->m_materialType == 3) {
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
            material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));
            unsigned int tevBit = m_curEnvTevBit;
            tevBit &= material->m_tevBit;
            if (m_activeEnvTevBit != tevBit) {
                m_activeEnvTevBit = tevBit;
                if ((tevBit & 2) != 0) {
                    IncTexMapIdCur();
                }
                IncTexMapIdCur();
                m_activeEnvTevBit = tevBit;
                m_bumpTexMapIds[0] = IncTexMapIdCur();
                m_bumpTexMapIds[1] = IncTexMapIdCur();
                m_bumpTexMtxIds[0] = IncTexMtxCur();
                m_bumpTexMtxIds[3] = IncTexMtxCur();
                IncTexCoordIdCur();
                m_bumpTexCoordIds[0] = IncTexCoordIdCur();
                m_bumpTexCoordIds[4] = IncTexCoordIdCur();
                m_bumpTexCoordIds[3] = IncTexCoordIdCur();
                material->m_bumpLight->SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), 0);

                Mtx scaleMtx;
                PSMTXScale(scaleMtx, material->m_scaleU, material->m_scaleV, 1.0f);
                scaleMtx[0][3] = material->m_textureData.m_texScroll[1].m_u0;
                scaleMtx[1][3] = material->m_textureData.m_texScroll[1].m_v0;
                GXLoadTexMtxImm(scaleMtx, m_bumpTexMtxIds[0], GX_MTX2x4);
                GXLoadTexMtxImm(LightPcs.m_bumpTexMtx2, m_bumpTexMtxIds[3], GX_MTX2x4);

                if ((tevBit & 0x20) != 0) {
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, m_texScroll0TexMtx, GX_FALSE, 0x7D);
                } else {
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                }
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, m_bumpTexMtxIds[0], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[4]), GX_TG_MTX2x4, GX_TG_POS, m_bumpTexMtxIds[3], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[3]), GX_TG_MTX2x4, GX_TG_NRM, 0x3C, GX_FALSE, 0x7D);
                m_numTevStage = 0;

                if (material->m_unkA5 != 0) {
                    GXColor tevColor = *reinterpret_cast<GXColor*>(reinterpret_cast<char*>(material->m_bumpLight) + 0x54);
                    GXSetTevColor(GX_TEVREG1, tevColor);
                } else {
                    GXColor tevColor = *reinterpret_cast<GXColor*>(&material->m_materialColor);
                    GXSetTevColor(GX_TEVREG1, tevColor);
                }

                if ((tevBit & 0x20000) != 0) {
                    if (m_vtxDescMode != 2) {
                        GXClearVtxDesc();
                        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                        m_vtxDescMode = 2;
                    }
                    int texCoordId;
                    if ((tevBit & 0x40) != 0) {
                        texCoordId = m_texScroll1TexCoord;
                    } else {
                        texCoordId = IncTexCoordIdCur();
                        GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordId), GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
                    }
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage),
                        static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                        tevScale, 1, GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                        static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                        tevScale, 1, GX_TEVREG2);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                        static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR_NULL);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_C2, GX_CC_TEXA, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    addtev_bump_jimen(tevScale);
                } else {
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage),
                        static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                        tevScale, 1, GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    addtev_bump_jimen(tevScale);

                    if ((tevBit & 2) != 0) {
                        if (m_vtxDescMode != 2) {
                            GXClearVtxDesc();
                            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                            m_vtxDescMode = 2;
                        }
                        int texCoordId;
                        if ((tevBit & 0x40) != 0) {
                            texCoordId = m_texScroll1TexCoord;
                        } else {
                            texCoordId = IncTexCoordIdCur();
                            GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordId), GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
                        }
                        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                        _GXSetTevOrder(
                            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                            static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
                        _GXSetTevColorIn(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC,
                            GX_CC_ZERO);
                        _GXSetTevColorOp(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                            tevScale, 1, GX_TEVREG2);
                        _GXSetTevAlphaIn(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_APREV);
                        _GXSetTevAlphaOp(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                            GX_TEVPREV);
                        _GXSetTevSwapMode(m_numTevStage, 0, 0);
                        IncNumTevStage();
                        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                        _GXSetTevOrder(
                            static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                            static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR_NULL);
                        _GXSetTevColorIn(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_C2, GX_CC_TEXA, GX_CC_ZERO);
                        _GXSetTevColorOp(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                            GX_TEVPREV);
                        _GXSetTevAlphaIn(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_APREV);
                        _GXSetTevAlphaOp(
                            static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                            GX_TEVPREV);
                        _GXSetTevSwapMode(m_numTevStage, 0, 0);
                        IncNumTevStage();
                    } else {
                        if (m_vtxDescMode != 0) {
                            GXClearVtxDesc();
                            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                            m_vtxDescMode = 0;
                        }
                    }
                }
                addtev_stdShadow(tevBit);
                if ((tevBit & 0x80) != 0) {
                    m_fullScreenShadowTexMapIds0[0] = IncTexMapIdCur();
                    m_fullScreenShadowTexMtxIds0[0] = IncTexMtxCur();
                    m_fullScreenShadowTexCoordIds0[0] = IncTexCoordIdCur();
                    m_fullScreenShadowTexMapIds1[0] = IncTexMapIdCur();
                    m_fullScreenShadowTexMtxIds1[0] = IncTexMtxCur();
                    m_fullScreenShadowTexCoordIds1[0] = IncTexCoordIdCur();
                    addtev_full_shadow(0);
                }
                GXSetNumTexGens(m_texCoordIdCur & 0xFF);
                GXSetNumTevStages(m_numTevStage & 0xFF);
                return;
            }
            material->m_bumpLight->SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), 0);
            return;
        }
        if (material->m_materialType == 2) {
            if (m_vtxDescMode != 0) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
            material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));
            unsigned int tevBit = m_curEnvTevBit;
            tevBit &= material->m_tevBit;
            if (m_activeEnvTevBit != tevBit) {
                m_activeEnvTevBit = tevBit;
                m_bumpTexMapIds[0] = m_texMapIdCur + 1;
                m_bumpTexMapIds[1] = m_texMapIdCur + 2;
                m_bumpTexMapIds[2] = m_texMapIdCur + 3;
                m_bumpTexMtxIds[0] = IncTexMtxCur();
                m_bumpTexMtxIds[3] = IncTexMtxCur();
                m_bumpTexMtxIds[4] = IncTexMtxCur();
                IncTexCoordIdCur();
                m_bumpTexCoordIds[0] = IncTexCoordIdCur();
                m_bumpTexCoordIds[4] = IncTexCoordIdCur();
                m_bumpTexCoordIds[3] = IncTexCoordIdCur();
                m_bumpTexCoordIds[5] = IncTexCoordIdCur();
                material->m_bumpLight->SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), 0);
                GXLoadTexObj(m_underWaterTexture, static_cast<GXTexMapID>(m_bumpTexMapIds[2]));

                Mtx scaleMtx;
                PSMTXScale(scaleMtx, material->m_scaleU, material->m_scaleV, 1.0f);
                scaleMtx[0][3] = material->m_textureData.m_texScroll[1].m_u0;
                scaleMtx[1][3] = material->m_textureData.m_texScroll[1].m_v0;
                GXLoadTexMtxImm(scaleMtx, m_bumpTexMtxIds[0], GX_MTX2x4);
                GXLoadTexMtxImm(LightPcs.m_bumpTexMtx2, m_bumpTexMtxIds[3], GX_MTX2x4);
                GXLoadTexMtxImm(m_underWaterTexMtx, m_bumpTexMtxIds[4], GX_MTX3x4);

                if ((tevBit & 0x20) != 0) {
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, m_texScroll0TexMtx, GX_FALSE, 0x7D);
                } else {
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                }
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, m_bumpTexMtxIds[0], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[4]), GX_TG_MTX2x4, GX_TG_POS, m_bumpTexMtxIds[3], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[3]), GX_TG_MTX2x4, GX_TG_NRM, 0x3C, GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[5]), GX_TG_MTX3x4, GX_TG_POS, m_bumpTexMtxIds[4], GX_FALSE, 0x7D);
                m_numTevStage = 0;

                if ((tevBit & 0x80000) != 0) {
                    if (material->m_unkA5 != 0) {
                        GXColor tevColor = *reinterpret_cast<GXColor*>(reinterpret_cast<char*>(material->m_bumpLight) + 0x54);
                        GXSetTevColor(GX_TEVREG1, tevColor);
                    } else {
                        GXColor tevColor = *reinterpret_cast<GXColor*>(&material->m_materialColor);
                        GXSetTevColor(GX_TEVREG1, tevColor);
                    }
                    addtev_bump_spec_col_water(tevScale);
                } else {
                    addtev_bump_water(tevScale);
                }
                addtev_stdShadow(tevBit);
                GXSetNumTexGens(m_texCoordIdCur & 0xFF);
                GXSetNumTevStages(m_numTevStage & 0xFF);
                return;
            }
            material->m_bumpLight->SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), 0);
            GXLoadTexObj(m_underWaterTexture, static_cast<GXTexMapID>(m_bumpTexMapIds[2]));
            return;
        }
        if ((m_curEnvTevBit & material->m_tevBit & 0x1000) != 0) {
            isStd1000 = 1;
        } else {
            if (m_vtxDescMode != 1) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NBT, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 1;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 0x12);
            material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));
            unsigned int tevBit = m_curEnvTevBit;
            tevBit &= material->m_tevBit;
            if (m_activeEnvTevBit != tevBit) {
                unsigned int scrollSel = tevBit & 0x60;
                m_activeEnvTevBit = tevBit;
                switch (scrollSel) {
                case 0:
                    IncTexCoordIdCur();
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                    m_bumpTexCoordIds[0] = m_texCoordIdCurShadow;
                    break;
                case 0x20:
                    m_texCoordIdCurShadow = m_texScroll0TexCoord;
                    m_bumpTexCoordIds[0] = IncTexCoordIdCur();
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                    break;
                case 0x40:
                    m_bumpTexCoordIds[0] = m_texScroll1TexCoord;
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, MaterialMan.m_texScroll1TexMtx, GX_FALSE, 0x7D);
                    m_texCoordIdCurShadow = IncTexCoordIdCur();
                    GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                    break;
                case 0x60:
                    m_texCoordIdCurShadow = m_texScroll0TexCoord;
                    m_bumpTexCoordIds[0] = m_texScroll1TexCoord;
                    break;
                }
                m_bumpTexMapIds[0] = m_texMapIdCur + 1;
                m_bumpTexMapIds[1] = m_texMapIdCur + 2;
                m_bumpTexMtxIds[2] = IncTexMtxCur();
                m_bumpTexMtxIds[1] = IncTexMtxCur();
                m_bumpTexCoordIds[1] = IncTexCoordIdCur();
                m_bumpTexCoordIds[2] = IncTexCoordIdCur();
                m_bumpTexCoordIds[3] = IncTexCoordIdCur();
                if (0 <= g_drawMaterial->m_textureIndices[3]) {
                    m_bumpTexMapIds[3] = m_texMapIdCur + 3;
                    m_bumpTexCoordIds[6] = IncTexCoordIdCur();
                }
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[1]), GX_TG_MTX2x4, GX_TG_BINRM, m_bumpTexMtxIds[1], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[2]), GX_TG_MTX2x4, GX_TG_TANGENT, m_bumpTexMtxIds[1], GX_FALSE, 0x7D);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[3]), GX_TG_MTX2x4, GX_TG_NRM, m_bumpTexMtxIds[2], GX_FALSE, 0x7D);
                GXLoadTexMtxImm(LightPcs.m_bumpTexMtx0, m_bumpTexMtxIds[2], GX_MTX2x4);
                GXLoadTexMtxImm(LightPcs.m_bumpTexMtx1, m_bumpTexMtxIds[1], GX_MTX2x4);
                GXSetCurrentMtx(0);
                m_numTevStage = 0;
                addtev_bump_st(setVtxDesc, tevScale);
                addtev_stdShadow(tevBit);
                GXSetNumTexGens(m_texCoordIdCur & 0xFF);
                GXSetNumTevStages(m_numTevStage & 0xFF);
            }
            unsigned int scrollSel = tevBit & 0x60;
            switch (scrollSel) {
            case 0x20:
                m_texCoordIdCurShadow = m_texScroll0TexCoord;
                m_bumpTexCoordIds[0] = IncTexCoordIdCur();
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                break;
            case 0x40:
                m_bumpTexCoordIds[0] = m_texScroll1TexCoord;
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[0]), GX_TG_MTX2x4, GX_TG_TEX0, MaterialMan.m_texScroll1TexMtx, GX_FALSE, 0x7D);
                m_texCoordIdCurShadow = IncTexCoordIdCur();
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                break;
            }
            material->m_bumpLight->SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[1]), material->m_unk36);
            if (g_drawMaterial->m_bumpLightDirect != 1) {
                return;
            }
            if (material->m_unkA5 != 0) {
                GXColor tevColor = *reinterpret_cast<GXColor*>(reinterpret_cast<char*>(material->m_bumpLight) + 0x54);
                GXSetTevColor(GX_TEVREG1, tevColor);
            } else {
                GXColor tevColor = *reinterpret_cast<GXColor*>(&material->m_materialColor);
                GXSetTevColor(GX_TEVREG1, tevColor);
            }
            if (material->m_textureIndices[3] < 0) {
                return;
            }
            TextureMan.SetTexture(static_cast<_GXTexMapID>(m_bumpTexMapIds[3]), g_drawMaterial->m_textureData.m_textures[3]);
            return;
        }
    }

    if (isStd1000) {
        GXSetArray(GX_VA_NRM, m_geometryArraySource, 0x12);
    } else {
        GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
    }
    material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));
    unsigned int tevBit = m_curEnvTevBit;
    tevBit &= material->m_tevBit;
    if (m_activeEnvTevBit == tevBit) {
        return;
    }
    m_activeEnvTevBit = tevBit;
    GXSetNumIndStages(0);
    if ((tevBit & 1) != 0) {
        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(0, 4);
        m_numTevStage = 1;
    } else {
        if ((tevBit & 0x200) != 0) {
            IncTexMapIdCur();
            GXColor tevColor2;
            tevColor2.r = 0xFF;
            tevColor2.g = 0xFF;
            tevColor2.b = 0;
            tevColor2.a = 0;
            GXColor tevColor3;
            tevColor3.r = 0;
            tevColor3.g = 0;
            tevColor3.b = 0xFF;
            tevColor3.a = 0xFF;
            GXSetTevColor(GX_TEVREG1, tevColor2);
            GXSetTevColor(static_cast<GXTevRegID>(3), tevColor3);
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
            _GXSetTevSwapMode(0, 0, 1);
            _GXSetTevOrder(
                GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR_NULL);
            GXSetTevDirect(GX_TEVSTAGE1);
            _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(1, 0, 2);
            _GXSetTevOrder(
                GX_TEVSTAGE1, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow + 1), GX_COLOR_NULL);
            GXSetTevDirect(GX_TEVSTAGE2);
            _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevColorOp(
                GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, tevScale, 1, GX_TEVPREV);
            _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(2, 0, 0);
            _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            m_numTevStage = 3;
        } else {
            GXSetTevDirect(GX_TEVSTAGE0);
            if ((tevBit & 0x20) != 0) {
                _GXSetTevOrder(
                    GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                    static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
            } else {
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                _GXSetTevOrder(
                    GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                    static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
            }
            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(
                GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, tevScale, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(0, 0, 0);
            m_numTevStage = 1;
        }
    }

    if (tevBit != 0) {
        if ((tevBit & 2) != 0) {
            if (m_vtxDescMode != 2) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                m_vtxDescMode = 2;
            }
            int texCoordId;
            if ((tevBit & 0x40) != 0) {
                texCoordId = m_texScroll1TexCoord;
            } else {
                IncTexCoordIdCur();
                texCoordId = m_texCoordIdCur;
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordId), GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
            }
            m_numTevStage = 1;
            IncTexMtxCur();
            IncTexMapIdCur();
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(
                static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
            _GXSetTevColorIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                tevScale, 1, GX_TEVREG1);
            _GXSetTevAlphaIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            _GXSetTevAlphaOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(
                static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR_NULL);
            _GXSetTevColorIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_C1, GX_CC_TEXA, GX_CC_ZERO);
            _GXSetTevColorOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            _GXSetTevAlphaOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
        } else {
            if (m_vtxDescMode != 0) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0;
            }
        }
        if ((tevBit & 0x8000) != 0) {
            m_activeEnvTevBit = 0xFFFFFFFF;
            GXColor kColor;
            kColor.r = material->m_shadowKColorId;
            kColor.g = 0;
            kColor.b = 0;
            kColor.a = 0;
            GXSetTevColor(static_cast<GXTevRegID>(3), kColor);
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            if ((tevBit & 0x20) == 0) {
                _GXSetTevOrder(
                    static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                    static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
            } else {
                _GXSetTevOrder(
                    static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                    static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
            }
            _GXSetTevColorIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO,
                tevScale, 1, GX_TEVREG1);
            _GXSetTevAlphaIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            _GXSetTevAlphaOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            _GXSetTevColorIn(static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_C1, GX_CC_A2, GX_CC_ZERO);
            _GXSetTevColorOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            _GXSetTevAlphaOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
        }
        if ((tevBit & 0x10000) != 0) {
            GXSetNumTevStages(1);
            _GXSetTevOp(0, 4);
            return;
        }
        if ((tevBit & 0x40000) != 0) {
            m_numTevStage = 0;
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXLoadTexMtxImm(m_objTextureMtx, 0x1E, GX_MTX3x4);
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(0), GX_TG_MTX3x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
            GXLoadTexObj(m_manaParaboloidTexObj0, static_cast<GXTexMapID>(0));
            GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevOp(0, 0);
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);
            return;
        }
        if ((tevBit & 0x1000) != 0) {
            if (isStd1000) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NBT, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0xFF;
            }
            IncTexMapIdCur();
            *reinterpret_cast<int*>(&m_pad0CC) = m_texMapIdCur;
            IncTexCoordIdCur();
            *reinterpret_cast<int*>(&m_pad0D4) = m_texCoordIdCur;
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(*reinterpret_cast<int*>(&m_pad0D4)), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            if (m_manaParaboloidTexObj0 != 0) {
                GXLoadTexObj(m_manaParaboloidTexObj0, static_cast<GXTexMapID>(*reinterpret_cast<int*>(&m_pad0CC)));
            }
            GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(
                static_cast<_GXTevStageID>(m_numTevStage),
                static_cast<_GXTexCoordID>(*reinterpret_cast<int*>(&m_pad0D4)),
                static_cast<_GXTexMapID>(*reinterpret_cast<int*>(&m_pad0CC)), GX_COLOR0A0);
            if (m_manaParaboloidTexObj0 != 0) {
                _GXSetTevColorIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CC_TEXC, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            } else {
                _GXSetTevColorIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            }
            _GXSetTevColorOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(
                static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_RASA, GX_CA_APREV, GX_CA_ZERO);
            _GXSetTevAlphaOp(
                static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
        }
        if ((tevBit & 0x2000) != 0 && m_manaParaboloidTexObj0 != 0 && m_manaParaboloidTexObj1 != 0) {
            if (init == 0) {
                bTest = 0;
                init = 1;
            }
            if (init2 == 0) {
                bTest2 = 0;
                init2 = 1;
            }
            unsigned int buttons = Pad.GetButtonDown(0);
            if ((buttons & 0x100) != 0) {
                bTest = 0;
            }
            if ((buttons & 0x200) != 0) {
                bTest2 = 0;
            }
            GXSetNumChans(1);
            GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
            _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
            m_numTevStage = 0;
            unsigned int alpha = m_manaAlpha;
            unsigned int alphaInv = 0xFFFFFF00 | m_manaAlpha;
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
            _GXSetTevSwapMode(m_numTevStage, 0, 1);
            _GXSetTevOrder(
                static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCur),
                static_cast<_GXTexMapID>(m_texMapIdCur), GX_COLOR0A0);
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCur), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            GXLoadTexObj(m_manaParaboloidTexObj1, static_cast<GXTexMapID>(m_texMapIdCur));
            IncTexCoordIdCur();
            IncTexMapIdCur();
            GXColor kColor0 = *reinterpret_cast<GXColor*>(&alpha);
            GXSetTevKColor(GX_KCOLOR0, kColor0);
            GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K0_A);
            if (bTest != 0) {
                _GXSetTevColorIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASA);
                _GXSetTevColorOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                _GXSetTevAlphaIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                _GXSetTevAlphaOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                if (bTest2 == 2) {
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_RASA, GX_CC_ONE, GX_CC_ONE);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_RASA, GX_CA_KONST, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                }
                IncNumTevStage();
            } else {
                _GXSetTevColorIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CC_RASC, GX_CC_KONST, GX_CC_TEXC, GX_CC_ZERO);
                _GXSetTevColorOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVREG0);
                _GXSetTevAlphaIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                _GXSetTevAlphaOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
                IncNumTevStage();
                GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                _GXSetTevSwapMode(m_numTevStage, 0, 1);
                _GXSetTevOrder(
                    static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(m_texCoordIdCur),
                    static_cast<_GXTexMapID>(m_texMapIdCur), GX_COLOR0A0);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCur), GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
                GXLoadTexObj(m_manaParaboloidTexObj0, static_cast<GXTexMapID>(m_texMapIdCur));
                IncTexCoordIdCur();
                IncTexMapIdCur();
                GXColor kColor1 = *reinterpret_cast<GXColor*>(&alphaInv);
                GXSetTevKColor(GX_KCOLOR1, kColor1);
                GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K1);
                GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K1_A);
                _GXSetTevColorIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CC_KONST, GX_CC_RASA, GX_CC_TEXC, GX_CC_ZERO);
                _GXSetTevColorOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_COMP_BGR24_GT, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVREG1);
                _GXSetTevAlphaIn(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                _GXSetTevAlphaOp(
                    static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG1);
                IncNumTevStage();
                GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                _GXSetTevSwapMode(m_numTevStage, 0, 1);
                _GXSetTevOrder(static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                if (bTest2 == 0) {
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C0, GX_CC_ONE, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_RASA, GX_CA_KONST, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                } else if (bTest2 == 1) {
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_ONE, GX_CC_C0, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                } else if (bTest2 == 2) {
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_ONE, GX_CC_C1, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_RASA, GX_CA_KONST, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                } else {
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_C0, GX_CC_C1, GX_CC_RASA, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                }
                IncNumTevStage();
                if (bTest2 == 0) {
                    GXColor kColor3 = *reinterpret_cast<GXColor*>(&alpha);
                    GXSetTevKColor(GX_KCOLOR3, kColor3);
                    GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K3);
                    GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K3_A);
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    _GXSetTevOrder(static_cast<_GXTevStageID>(m_numTevStage), GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_C1, GX_CC_ONE, GX_CC_CPREV);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    IncNumTevStage();
                }
            }
        }
        addtev_stdShadow(tevBit);
        if ((tevBit & 0x80) != 0) {
            IncTexMapIdCur();
            m_fullScreenShadowTexMapIds0[0] = m_texMapIdCur;
            IncTexMtxCur();
            m_fullScreenShadowTexMtxIds0[0] = m_texMtxCur;
            IncTexCoordIdCur();
            m_fullScreenShadowTexCoordIds0[0] = m_texCoordIdCur;
            IncTexMapIdCur();
            m_fullScreenShadowTexMapIds1[0] = m_texMapIdCur;
            IncTexMtxCur();
            m_fullScreenShadowTexMtxIds1[0] = m_texMtxCur;
            IncTexCoordIdCur();
            m_fullScreenShadowTexCoordIds1[0] = m_texCoordIdCur;
            addtev_full_shadow(0);
        }
    } else {
        if (m_vtxDescMode != 0) {
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
            m_vtxDescMode = 0;
        }
    }
    GXSetNumTexGens(((m_texCoordIdCur & 0xFF) + 1) & 0xFF);
    GXSetNumTevStages(m_numTevStage & 0xFF);
}

/*
 * --INFO--
 * PAL Address: 0x8003FB4C
 * PAL Size: 676b
 * EN Address: 0x8004A994
 * EN Size: 720b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterialCharaShadow(CMaterial* material)
{
    unsigned int tevBit = material->m_tevBit;
    CLightPcs::CBumpLight* bumpLight = material->m_bumpLight;

    if (bumpLight != 0) {
        unsigned char materialType = material->m_materialType;
        if ((materialType == 3) || (materialType == 2)) {
            if ((tevBit & 0x20002) != 0) {
                if (m_vtxDescMode != 2) {
                    GXClearVtxDesc();
                    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                    m_vtxDescMode = 2;
                }
                GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
            } else {
                if (m_vtxDescMode != 0) {
                    GXClearVtxDesc();
                    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    m_vtxDescMode = 0;
                }
                GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
            }
        } else {
            if (m_vtxDescMode != 1) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NBT, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 1;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 0x12);
        }
    } else {
        if ((tevBit & 0x20002) != 0) {
            if (m_vtxDescMode != 2) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                m_vtxDescMode = 2;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
        } else if ((tevBit & 1) != 0) {
            if (m_vtxDescMode != 3) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                m_vtxDescMode = 3;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
        } else {
            if (m_vtxDescMode != 0) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0;
            }
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003F07C
 * PAL Size: 2768b
 * EN Address: 0x8004AC64
 * EN Size: 2784b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterialPart(CMaterialSet* materialSet, int materialIndex, int setVtxDesc)
{
    int stdTexMapId = m_stdTexMapId;
    m_texMapIdCur = stdTexMapId;
    m_texMapIdCurShadow = stdTexMapId;
    int stdTexMtx = m_stdTexMtx;
    m_texMtxCur = stdTexMtx;
    m_texMtxCurShadow = stdTexMtx;
    int stdTexCoordId = m_stdTexCoordId;
    m_texCoordIdCur = stdTexCoordId;
    m_texCoordIdCurShadow = stdTexCoordId;
    m_curEnvTevBit = m_stdEnvTevBit;

    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = materials->GetAt(materialIndex);
    material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));

    unsigned int tevBit = m_curEnvTevBit;
    tevBit &= material->m_tevBit;
    if (m_activeEnvTevBit != tevBit) {
        m_activeEnvTevBit = tevBit;
        GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);

    if ((tevBit & 0x400) != 0) {
        if ((tevBit & 0x20) != 0) {
            m_texCoordIdCur = m_texCoordIdCur - 1;
            _GXSetTevOrder(
                GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
        } else {
            GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                              static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
            _GXSetTevOrder(
                GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
        }
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1, GX_TEVPREV);
        _GXSetTevSwapMode(0, 0, 0);
        m_numTevStage = 1;

        if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
            m_vtxDescMode = 0;
        }
    } else {
        if ((tevBit & 1) != 0) {
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1, GX_TEVPREV);
            _GXSetTevSwapMode(0, 0, 0);
            m_numTevStage = 1;

            if ((m_vtxDescMode != 3) && (setVtxDesc != 0)) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                m_vtxDescMode = 3;
            }

            GXSetNumTexGens(0);
            GXSetNumTevStages(1);
            return;
        }

        if ((tevBit & 0x200) != 0) {
            GXColor tevColor3;
            GXColor tevColor2;
            tevColor2.r = 0xFF;
            tevColor2.g = 0xFF;
            tevColor2.b = 0;
            tevColor2.a = 0;
            tevColor3.r = 0;
            tevColor3.g = 0;
            tevColor3.b = 0xFF;
            tevColor3.a = 0xFF;
            m_texMapIdCur = m_texMapIdCur + 1;
            GXSetTevColor(static_cast<_GXTevRegID>(2), tevColor2);
            GXSetTevColor(static_cast<_GXTevRegID>(3), tevColor3);

            if ((tevBit & 0x20) != 0) {
                m_texCoordIdCur = m_texCoordIdCur - 1;
                m_texCoordIdCurShadow = m_texScroll0TexCoord;
            } else {
                GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                  static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
            }

            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
            _GXSetTevSwapMode(0, 0, 1);
            _GXSetTevOrder(
                GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR_NULL);

            GXSetTevDirect(GX_TEVSTAGE1);
            _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(1, 0, 2);
            _GXSetTevOrder(
                GX_TEVSTAGE1, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                static_cast<_GXTexMapID>(m_texMapIdCurShadow + 1), GX_COLOR_NULL);

            GXSetTevDirect(GX_TEVSTAGE2);
            _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
            _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1, GX_TEVPREV);
            _GXSetTevSwapMode(2, 0, 0);
            _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

            m_numTevStage = 3;
            if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0;
            }
        } else {
            if ((tevBit & 0x800) != 0) {
                if ((tevBit & 0x20) != 0) {
                    m_texCoordIdCur = m_texCoordIdCur - 1;
                    _GXSetTevOrder(
                        GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                } else {
                    GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                      static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
                    _GXSetTevOrder(
                        GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                }

                _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_RED);
                _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1, GX_TEVPREV);
                _GXSetTevSwapMode(0, 0, 1);
                m_numTevStage = 1;

                if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
                    GXClearVtxDesc();
                    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    m_vtxDescMode = 0;
                }
            } else {
                if ((tevBit & 0x20) != 0) {
                    m_texCoordIdCur = m_texCoordIdCur - 1;
                    _GXSetTevOrder(
                        GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                } else {
                    GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                      static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
                    _GXSetTevOrder(
                        GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                        static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
                }

                _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, 1, GX_TEVPREV);
                _GXSetTevSwapMode(0, 0, 0);
                m_numTevStage = 1;

                if (tevBit != 0) {
                if ((tevBit & 2) != 0) {
                    if ((m_vtxDescMode != 2) && (setVtxDesc != 0)) {
                        GXClearVtxDesc();
                        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
                        m_vtxDescMode = 2;
                    }

                    int texCoordId;
                    if ((tevBit & 0x40) != 0) {
                        texCoordId = m_texScroll1TexCoord;
                    } else {
                        m_texCoordIdCur = m_texCoordIdCur + 1;
                        texCoordId = m_texCoordIdCur;
                        GXSetTexCoordGen2(static_cast<_GXTexCoordID>(texCoordId), static_cast<_GXTexGenType>(1),
                                          static_cast<_GXTexGenSrc>(5), 0x3C, 0, 0x7D);
                    }

                    m_numTevStage = 1;
                    GXSetTevDirect(static_cast<_GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                        static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1,
                        GX_TEVREG0);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(
                        m_numTevStage, 0, 0);
                    m_numTevStage =
                        ((m_numTevStage & 0xFF) + 1) & 0xFF;

                    GXSetTevDirect(static_cast<_GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        static_cast<_GXTevStageID>(m_numTevStage), static_cast<_GXTexCoordID>(texCoordId),
                        static_cast<_GXTexMapID>((m_texMapIdCurShadow & 0xFF) + 1), GX_COLOR_NULL);
                    _GXSetTevColorIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CC_CPREV, GX_CC_C0, GX_CC_TEXA, GX_CC_ZERO);
                    _GXSetTevColorOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    _GXSetTevAlphaOp(
                        static_cast<_GXTevStageID>(m_numTevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevSwapMode(
                        m_numTevStage, 0, 0);
                    m_numTevStage =
                        ((m_numTevStage & 0xFF) + 1) & 0xFF;
                } else {
                    if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
                        GXClearVtxDesc();
                        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                        m_vtxDescMode = 0;
                    }
                }
                } else {
                    if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
                        GXClearVtxDesc();
                        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                        m_vtxDescMode = 0;
                    }
                }
            }
        }
    }

        GXSetNumTexGens(((m_texCoordIdCur & 0xFF) + 1) & 0xFF);
        GXSetNumTevStages(m_numTevStage & 0xFF);
        return;
    }

    if ((tevBit & 0x200) != 0) {
        _GXSetTevOrder(
            GX_TEVSTAGE1, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
            static_cast<_GXTexMapID>(m_texMapIdCurShadow + 1), GX_COLOR_NULL);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003EBA0
 * PAL Size: 1244b
 * EN Address: 0x8004B744
 * EN Size: 1292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterialMenu(CMaterialSet* materialSet, int materialIndex, int setVtxDesc)
{
    SetStdEnv();

    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = materials->GetAt(materialIndex);
    material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));

    unsigned int tevBit = m_curEnvTevBit;
    tevBit &= material->m_tevBit;
    if (m_activeEnvTevBit != tevBit) {
        m_activeEnvTevBit = tevBit;
        GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);

    if ((tevBit & 0x200) != 0) {
        GXColor tevColor3;
        GXColor tevColor2;
        tevColor2.r = 0xFF;
        tevColor2.g = 0xFF;
        tevColor2.b = 0;
        tevColor2.a = 0;
        tevColor3.r = 0;
        tevColor3.g = 0;
        tevColor3.b = 0xFF;
        tevColor3.a = 0xFF;
        GXSetTevColor(GX_TEVREG1, tevColor2);
        GXSetTevColor(static_cast<GXTevRegID>(3), tevColor3);

        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
        _GXSetTevSwapMode(0, 0, 1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

        GXSetTevDirect(GX_TEVSTAGE1);
        _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(1, 0, 2);
        _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);

        GXSetTevDirect(GX_TEVSTAGE2);
        _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        _GXSetTevSwapMode(2, 0, 0);
        _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

        m_numTevStage = 3;
        if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
            m_vtxDescMode = 0;
        }
    } else {
        if ((tevBit & 0x800) != 0) {
            if ((tevBit & 0x20) != 0) {
                m_texCoordIdCur = m_texCoordIdCur - 1;
                _GXSetTevOrder(
                    GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texScroll0TexCoord),
                    static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
            } else {
                GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                  GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(
                    GX_TEVSTAGE0, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                    static_cast<_GXTexMapID>(m_texMapIdCurShadow), GX_COLOR0A0);
            }

            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_RED);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            _GXSetTevSwapMode(0, 0, 1);
            m_numTevStage = 1;

            if ((m_vtxDescMode != 0) && (setVtxDesc != 0)) {
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                m_vtxDescMode = 0;
            }
        }
    }

        GXSetNumTexGens(static_cast<unsigned char>((m_texCoordIdCur & 0xFF) + 1));
        GXSetNumTevStages(static_cast<unsigned char>(m_numTevStage & 0xFF));
        return;
    }

    if ((tevBit & 0x200) != 0) {
        _GXSetTevOrder(
            GX_TEVSTAGE1, static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
            static_cast<_GXTexMapID>(m_texMapIdCurShadow + 1), GX_COLOR_NULL);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003EB24
 * PAL Size: 124b
 * EN Address: 0x8004BC50
 * EN Size: 148b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetObjMatrix(float (*mtxA) [4], float (*mtxB) [4])
{
    Mtx tmp0;
    Mtx tmp1;

    PSMTXConcat(mtxA, mtxB, tmp0);
    GXLoadPosMtxImm(tmp0, GX_PNMTX0);
    PSMTXCopy(tmp0, tmp1);
    tmp1[0][3] = 0.0f;
    tmp1[1][3] = 0.0f;
    tmp1[2][3] = 0.0f;
    GXLoadNrmMtxImm(tmp1, GX_PNMTX0);
    PSMTXCopy(tmp1, m_objTextureMtx);
}

/*
 * --INFO--
 * PAL Address: 0x8003E9A8
 * PAL Size: 380b
 * EN Address: 0x8004BCE4
 * EN Size: 384b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetTexScroll(float u0, float v0, float u1, float v1)
{
    if (((static_cast<unsigned int>(m_texMtxCur) & 0xFF) < 0x3C) &&
        ((static_cast<unsigned int>(m_texCoordIdCur) & 0xFF) < 8)) {
        m_curEnvTevBit |= 0x20;

        Mtx texMtx;
        PSMTXIdentity(texMtx);
        texMtx[0][3] = u0;
        texMtx[1][3] = v0;

        m_texScroll0TexMtx = m_texMtxCur;
        m_texScroll0TexCoord = m_texCoordIdCur;
        GXLoadTexMtxImm(texMtx, m_texMtxCur, GX_MTX2x4);

        int texMtxCur = m_texMtxCur;
        m_texMtxCur = texMtxCur + 3;

        int texCoordCur = m_texCoordIdCur;
        m_texCoordIdCur = texCoordCur + 1;
        GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordCur), GX_TG_MTX2x4, GX_TG_TEX0, texMtxCur, GX_FALSE,
                          0x7D);

        if ((0.0f != u1) || (0.0f != v1)) {
            m_curEnvTevBit |= 0x40;

            PSMTXIdentity(texMtx);
            texMtx[0][3] = u1;
            texMtx[1][3] = v1;

            m_texScroll1TexMtx = m_texMtxCur;
            m_texScroll1TexCoord = m_texCoordIdCur;
            GXLoadTexMtxImm(texMtx, m_texMtxCur, GX_MTX2x4);

            texMtxCur = m_texMtxCur;
            m_texMtxCur = texMtxCur + 3;

            texCoordCur = m_texCoordIdCur;
            m_texCoordIdCur = texCoordCur + 1;
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordCur), GX_TG_MTX2x4, GX_TG_TEX0, texMtxCur, GX_FALSE,
                              0x7D);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003E904
 * PAL Size: 164b
 * EN Address: 0x8004BE64
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetFullScreenShadow(CFullScreenShadow& shadow, float (*viewMtx)[4], long flags)
{
    int cameraEnable = CameraPcs.m_fullScreenShadowEnabled;
    if (cameraEnable != 0) {
        m_curEnvTevBit |= 0x80;

        PSMTXConcat(shadow.m_shadowTexMtx, viewMtx, m_fullScreenShadowMtx0);
        m_fullScreenShadowTexObj0 = &shadow.m_texObjs[flags];

        PSMTXConcat(shadow.m_depthMtx, viewMtx, m_fullScreenShadowMtx1);
        m_fullScreenShadowTexObj1 = &shadow.m_texObjs[flags] + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003E71C
 * PAL Size: 488b
 * EN Address: 0x8004BF10
 * EN Size: 544b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadow(CMapShadow& shadow, float (*viewMtx) [4], int shadowIndex, unsigned long materialFlag)
{
    CMaterialSet* materialSet = MapMng.m_materialSet;
    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = materials->GetAt(shadow.m_materialIndex);

    unsigned long useShadowBit32 = materialFlag & (material->m_tevBit & 0x8000);
    if (useShadowBit32 != 0) {
        if (m_shadowTextureCount >= 4) {
            return;
        }
    } else if (m_shadowTextureCount >= 5) {
        return;
    }

    if ((static_cast<unsigned long>(m_texMapIdCur & 0xFF) < 8) &&
        (static_cast<unsigned long>(m_texMtxCur & 0xFF) < 0x3C) &&
        (static_cast<unsigned long>(m_texCoordIdCur & 0xFF) < 8)) {
        m_curEnvTevBit |= 0x10;
        m_shadowMaterialType[m_shadowMaterialCount] = shadow.m_shadowMaterialType;
        m_shadowIndices[m_shadowMaterialCount] = static_cast<unsigned char>(shadowIndex);
        m_shadowTexMapIds[m_shadowMaterialCount] = m_texMapIdCur;
        m_shadowTexMtxIds[m_shadowMaterialCount] = m_texMtxCur;
        m_shadowTexCoordIds[m_shadowMaterialCount] = m_texCoordIdCur;

        Mtx texMtx;
        PSMTXConcat(shadow.m_shadowMtx, viewMtx, texMtx);
        GXLoadTexMtxImm(texMtx, m_texMtxCur, GX_MTX3x4);

        int texMtxCur = m_texMtxCur;
        m_texMtxCur = texMtxCur + 3;

        int texCoordCur = m_texCoordIdCur;
        m_texCoordIdCur = texCoordCur + 1;
        GXSetTexCoordGen2(static_cast<GXTexCoordID>(texCoordCur), GX_TG_MTX3x4, GX_TG_POS, texMtxCur, GX_FALSE,
                          GX_PTIDENTITY);

        int texMapCur = m_texMapIdCur;
        m_texMapIdCur = texMapCur + 1;
        TextureMan.SetTexture(static_cast<_GXTexMapID>(texMapCur), material->m_textureData.m_textures[0]);

        if (useShadowBit32 != 0) {
            texMapCur = m_texMapIdCur;
            m_texMapIdCur = texMapCur + 1;
            TextureMan.SetTexture(static_cast<_GXTexMapID>(texMapCur), material->m_textureData.m_textures[1]);
            m_shadowKColorIds[m_shadowMaterialCount] = material->m_shadowKColorId;
            m_shadowKColorMask |= (1 << m_shadowMaterialCount);
            m_shadowTextureCount = m_shadowTextureCount + 1;
        }

        m_shadowMaterialCount = m_shadowMaterialCount + 1;
        m_shadowTextureCount = m_shadowTextureCount + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003E660
 * PAL Size: 188b
 * EN Address: 0x8004C130
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadowBit32(CMapShadow::TARGET target, unsigned long* shadowBit32, float (*viewMtx) [4])
{
    unsigned int i = 0;
    CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
    for (; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = mapShadowArray->GetAt(i);

        if (shadow->m_targetEnabled[static_cast<int>(target)] == 0) {
            continue;
        }

        if ((shadow->m_materialMode == 1) || ((shadowBit32[i >> 5] & (1u << (i & 0x1F))) != 0)) {
            SetShadow(*shadow, viewMtx, static_cast<int>(i), 0xFFFFFFFF);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003E394
 * PAL Size: 716b
 * EN Address: 0x8004C200
 * EN Size: 860b
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_common_subs off
void CMaterialMan::SetPosition(
    CMapShadow::TARGET target,
    Vec* position,
    float rangeXZ,
    float rangeY,
    float (*viewMtx)[4],
    int ignoreFrustumCheck)
{
    float searchBoundStorage[6];
    CBound& searchBound = *reinterpret_cast<CBound*>(searchBoundStorage);
    searchBound.m_min.x = position->x - rangeXZ;
    searchBound.m_max.x = position->x + rangeXZ;
    searchBound.m_min.z = position->z - rangeXZ;
    searchBound.m_max.z = position->z + rangeXZ;
    searchBound.m_min.y = position->y;
    searchBound.m_max.y = position->y + rangeY;

    if (target == static_cast<CMapShadow::TARGET>(0)) {
        ShadowCandidate shadowCandidates[128];
        ShadowCandidate* candidateWrite = shadowCandidates;
        CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
        int candidateCount = 0;

        int idx;
        for (unsigned int i = 0; (idx = i) < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
            CMapShadow* shadow = mapShadowArray->GetAt(idx);

            if (shadow->m_targetEnabled[static_cast<int>(target)] == 0) {
                continue;
            }

            Vec shadowPos;
            shadowPos.x = shadow->m_modelA->m_worldMtx[0][3];
            shadowPos.y = shadow->m_modelA->m_worldMtx[1][3];
            shadowPos.z = shadow->m_modelA->m_worldMtx[2][3];

            Mtx scaledShadowMtx;
            PSMTXScaleApply(
                shadow->m_shadowMtx,
                scaledShadowMtx,
                5.0f,
                5.0f,
                1.0f);

            if (shadow->m_materialMode == 1) {
                SetShadow(*shadow, viewMtx, i, 0);
                continue;
            }

            Vec delta;
            if (ignoreFrustumCheck == 0) {
                goto frustumCheck;
            }

        writeCandidate:
            PSVECSubtract(&shadowPos, position, &delta);
            candidateWrite->distance = PSVECSquareMag(&delta);
            candidateWrite->shadow = shadow;
            candidateWrite->index = i;
            candidateWrite++;
            candidateCount++;
            continue;

        frustumCheck:
            if ((shadow->m_yFilterMode == 1) && (position->y < shadowPos.y)) {
                continue;
            }
            if ((shadow->m_yFilterMode == 2) && (position->y > shadowPos.y)) {
                continue;
            }
            if (reinterpret_cast<CBound*>(searchBoundStorage)
                    ->CheckFrustum(shadowPos, scaledShadowMtx, -100000000.0f) != 0) {
                goto writeCandidate;
            }
        }

        float maxDist = 20000000000000.0f;
        float candidateDist;
        ShadowCandidate* nearest = 0;
        float nearestDist = 100000000000000000000.0f;
        ShadowCandidate* candidateRead = shadowCandidates;
        for (int i = 0; i < candidateCount; i++) {
            candidateDist = candidateRead->distance;
            if (nearestDist > candidateDist) {
                nearestDist = candidateDist;
                nearest = candidateRead;
            }
            candidateRead++;
        }

        if (nearest != 0) {
            nearest->distance = maxDist;
            SetShadow(*nearest->shadow, viewMtx, nearest->index, 0xFFFFFFFF);
        }
    } else {
        unsigned int i = 0;
        int idx;
        CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
        for (; (idx = i) < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
            CMapShadow* shadow = mapShadowArray->GetAt(idx);

            if (shadow->m_targetEnabled[static_cast<int>(target)] == 0) {
                continue;
            }

            Vec shadowPos;
            shadowPos.x = shadow->m_modelA->m_worldMtx[0][3];
            shadowPos.y = shadow->m_modelA->m_worldMtx[1][3];
            shadowPos.z = shadow->m_modelA->m_worldMtx[2][3];

            Mtx scaledShadowMtx;
            PSMTXScaleApply(
                shadow->m_shadowMtx,
                scaledShadowMtx,
                5.0f,
                5.0f,
                1.0f);

            if ((shadow->m_materialMode == 1) ||
                (reinterpret_cast<CBound*>(searchBoundStorage)
                     ->CheckFrustum(shadowPos, scaledShadowMtx, -100000000.0f) != 0)) {
                SetShadow(*shadow, viewMtx, i, 0);
            }
        }
    }
}
#pragma opt_common_subs reset

/*
 * --INFO--
 * PAL Address: 0x8003E14C
 * PAL Size: 584b
 * EN Address: 0x8004C55C
 * EN Size: 708b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::GetCharaShadow(
    int maxShadows,
    CMaterial** materialsOut,
    float (**shadowMtxOut)[4],
    Vec* position,
    float rangeXZ,
    float rangeY,
    int ignoreFrustumCheck)
{
    float searchBoundStorage[6];
    CBound& searchBound = *reinterpret_cast<CBound*>(searchBoundStorage);
    searchBound.m_min.x = position->x - rangeXZ;
    searchBound.m_max.x = position->x + rangeXZ;
    searchBound.m_min.z = position->z - rangeXZ;
    searchBound.m_max.z = position->z + rangeXZ;
    searchBound.m_min.y = position->y;
    searchBound.m_max.y = position->y + rangeY;

    CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();

    ShadowCandidate shadowCandidates[128];
    ShadowCandidate* candidateWrite = shadowCandidates;
    int outputCount = 0;
    int candidateCount = 0;

    int idx;
    for (unsigned int i = 0; (idx = i) < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = mapShadowArray->GetAt(idx);
        if (shadow->m_targetEnabled[0] == 0) {
            continue;
        }

        Vec shadowPos;
        shadowPos.x = shadow->m_modelA->m_worldMtx[0][3];
        shadowPos.y = shadow->m_modelA->m_worldMtx[1][3];
        shadowPos.z = shadow->m_modelA->m_worldMtx[2][3];

        Mtx scaledShadowMtx;
        PSMTXScaleApply(
            shadow->m_shadowMtx,
            scaledShadowMtx,
            5.0f,
            5.0f,
            1.0f);

        if (shadow->m_materialMode == 1) {
            if (outputCount < maxShadows) {
                materialsOut[outputCount] = MapMng.m_materialSet->m_materials.GetAt(shadow->m_materialIndex);
                shadowMtxOut[outputCount++] = shadow->m_shadowMtx;
            }
            continue;
        }

        if (ignoreFrustumCheck == 0) {
            goto frustumCheck;
        }

    writeCandidate:
        {
            Vec delta;
            PSVECSubtract(&shadowPos, position, &delta);
            candidateWrite->distance = PSVECSquareMag(&delta);
            candidateWrite->shadow = shadow;
            candidateWrite->index = i;
            candidateWrite++;
            candidateCount++;
        }
        continue;

    frustumCheck:
        if ((shadow->m_yFilterMode == 1) && (position->y < shadowPos.y)) {
            continue;
        }
        if ((shadow->m_yFilterMode == 2) && (position->y > shadowPos.y)) {
            continue;
        }
        if (reinterpret_cast<CBound*>(searchBoundStorage)
                ->CheckFrustum(shadowPos, scaledShadowMtx, -100000000.0f) != 0) {
            goto writeCandidate;
        }
    }

    int outputOffset = outputCount * 4;

    ShadowCandidate* candidateRead = shadowCandidates;
    float maxDist = 20000000000000.0f;
    float candidateDist;
    ShadowCandidate* nearest = 0;
    float nearestDist = 100000000000000000000.0f;
    for (int i = 0; i < candidateCount; i++) {
        candidateDist = candidateRead->distance;
        if (nearestDist > candidateDist) {
            nearestDist = candidateDist;
            nearest = candidateRead;
        }
        candidateRead++;
    }

    if (nearest != 0) {
        nearest->distance = maxDist;
        if (outputCount < maxShadows) {
            *reinterpret_cast<CMaterial**>(Ptr(materialsOut, outputOffset)) = MapMng.m_materialSet->m_materials.GetAt(nearest->shadow->m_materialIndex);
            outputCount++;
            *reinterpret_cast<float (**)[4]>(Ptr(shadowMtxOut, outputOffset)) = nearest->shadow->m_shadowMtx;
        }
    }

    return outputCount;
}

/*
 * --INFO--
 * PAL Address: 0x8003E058
 * PAL Size: 244b
 * EN Address: 0x8004C820
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadowBound(CMapShadow::TARGET target, CBound* bound, float (*viewMtx) [4])
{
    CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();

    for (long i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = mapShadowArray->GetAt(i);

        if (shadow->m_targetEnabled[static_cast<int>(target)] == 0) {
            continue;
        }

        Vec position;
        Mtx scaledShadowMtx;

        position.x = shadow->m_modelA->m_worldMtx[0][3];
        position.y = shadow->m_modelA->m_worldMtx[1][3];
        position.z = shadow->m_modelA->m_worldMtx[2][3];
        PSMTXScaleApply(shadow->m_shadowMtx, scaledShadowMtx, 5.0f,
                        5.0f, 1.0f);

        if ((shadow->m_materialMode == 1) ||
            (bound->CheckFrustum(position, scaledShadowMtx, -100000000.0f) != 0)) {
            SetShadow(*shadow, viewMtx, i, 0xFFFFFFFF);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003DDC4
 * PAL Size: 660b
 * EN Address: 0x8004C944
 * EN Size: 704b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::InitVtxFmt(
    int formatFlags, _GXCompType positionType, int positionFrac, _GXCompType colorType, int colorFrac,
    _GXCompType texCoordType, int texCoordFrac)
{
    if ((formatFlags & 1) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)0, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)0, (_GXAttr)10, (_GXCompCnt)0, colorType, colorFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)0, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
        GXSetVtxAttrFmt((_GXVtxFmt)0, (_GXAttr)13, (_GXCompCnt)1, texCoordType, texCoordFrac);
    }
    if ((formatFlags & 2) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)1, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)1, (_GXAttr)0x19, (_GXCompCnt)1, colorType, colorFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)1, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
        GXSetVtxAttrFmt((_GXVtxFmt)1, (_GXAttr)13, (_GXCompCnt)1, texCoordType, texCoordFrac);
    }
    if ((formatFlags & 4) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)2, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)2, (_GXAttr)10, (_GXCompCnt)0, colorType, colorFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)2, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
        GXSetVtxAttrFmt((_GXVtxFmt)2, (_GXAttr)13, (_GXCompCnt)1, texCoordType, texCoordFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)2, (_GXAttr)14, (_GXCompCnt)1, texCoordType, texCoordFrac);
    }
    if ((formatFlags & 8) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)3, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)3, (_GXAttr)10, (_GXCompCnt)0, colorType, colorFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)3, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
    }
    if ((formatFlags & 0x10) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)4, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)4, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
        GXSetVtxAttrFmt((_GXVtxFmt)4, (_GXAttr)13, (_GXCompCnt)1, texCoordType, texCoordFrac);
    }
    if ((formatFlags & 0x20) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)5, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
    }
    if ((formatFlags & 0x40) != 0) {
        GXSetVtxAttrFmt((_GXVtxFmt)6, (_GXAttr)9, (_GXCompCnt)1, positionType, positionFrac);
        GXSetVtxAttrFmt((_GXVtxFmt)6, (_GXAttr)11, (_GXCompCnt)1, (_GXCompType)5, 0);
    }

    m_activeEnvTevBit = 0xFFFFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x80041F8C
 * PAL Size: 24b
 * EN Address: 0x8004EB54
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::IncNumTevStage()
{
    m_numTevStage = ((m_numTevStage & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EB7C
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::GetTexMtxCur()
{
    return m_texMtxCur;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EB84
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::GetTexCoordIdCur()
{
    return m_texCoordIdCur;
}

/*
 * --INFO--
 * PAL Address: 0x80041FA4
 * PAL Size: 20b
 * EN Address: 0x8004EB8C
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::IncTexCoordIdCur()
{
    int texCoordId = m_texCoordIdCur;
    m_texCoordIdCur = texCoordId + 1;
    return texCoordId;
}

/*
 * --INFO--
 * PAL Address: 0x80041FB8
 * PAL Size: 20b
 * EN Address: 0x8004EBB0
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::IncTexMtxCur()
{
    int texMtx = m_texMtxCur;
    m_texMtxCur = texMtx + 3;
    return texMtx;
}

/*
 * --INFO--
 * PAL Address: 0x80041FCC
 * PAL Size: 20b
 * EN Address: 0x8004EBD4
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::IncTexMapIdCur()
{
    int texMapId = m_texMapIdCur;
    m_texMapIdCur = texMapId + 1;
    return texMapId;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EBF8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMaterialMan::GetTexMapIdCur()
{
    return m_texMapIdCur;
}

/*
 * --INFO--
 * PAL Address: 0x80041FE0
 * PAL Size: 48b
 * EN Address: 0x8004EC00
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::SetStdEnv()
{
    int stdValue = m_stdTexMapId;

    m_texMapIdCur = stdValue;
    m_texMapIdCurShadow = stdValue;
    stdValue = m_stdTexMtx;
    m_texMtxCur = stdValue;
    m_texMtxCurShadow = stdValue;
    stdValue = m_stdTexCoordId;
    m_texCoordIdCur = stdValue;
    m_texCoordIdCurShadow = stdValue;
    m_curEnvTevBit = m_stdEnvTevBit;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EC30
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::DecTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EC54
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::SetTevBit(CMaterialMan::TEV_BIT)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EC80
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::ErrorTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004ECAC
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::ErrorTexMtxCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004ECD8
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialMan::ErrorTexMapIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003C500
 * PAL Size: 364b
 * EN Address: 0x8004ED04
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CTexScroll::~CTexScroll()
{
    if (m_type0 == 2) {
        CMapKeyFrame* keyFrame = m_uKeyFrame;
        if (keyFrame != 0) {
            delete keyFrame;
            m_uKeyFrame = 0;
        }
    }

    if (m_type1 == 2) {
        CMapKeyFrame* keyFrame = m_vKeyFrame;
        if (keyFrame != 0) {
            delete keyFrame;
            m_vKeyFrame = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C66C
 * PAL Size: 36b
 * EN Address: 0x8004EDA8
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CTexScroll::CTexScroll()
{
    float zero = 0.0f;
    m_v0 = zero;
    m_u0 = zero;
    m_v1 = zero;
    m_u1 = zero;
    m_type1 = 0;
    m_type0 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003DD14
 * PAL Size: 176b
 * EN Address: 0x8004CD34
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterial::CMaterial()
{
    memset(m_name, 0, sizeof(m_name));
    m_pdtSlotIndex = -1;
    m_blendMode = 4;
    m_fogEnable = 1;
    m_materialType = 0;
    m_shadowKColorId = 0;
    m_textureData.m_textures[0] = 0;
    m_textureData.m_textures[1] = 0;
    m_textureData.m_textures[2] = 0;
    m_textureData.m_textures[3] = 0;
    m_texShiftU = 0;
    m_texShiftV = 0;
    m_unk36 = 0;
    m_unkA5 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003DC38
 * PAL Size: 220b
 * EN Address: 0x8004CE64
 * EN Size: 196b
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterial::~CMaterial()
{
    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        CTexture* texture = m_textureData.m_textures[i];
        if (texture != 0) {
            ReleaseRefNonNull(texture);
            m_textureData.m_textures[i] = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003DC10
 * PAL Size: 40b
 * EN Address: 0x8004CF28
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterial::Create(unsigned long tag, CMaterialMan::TEV_BIT tevBit)
{
    m_tevBit = static_cast<unsigned long>(tevBit);
    float scale = 1.0f;
    m_bumpLight = 0;
    m_textureCount = 0;
    m_scaleV = scale;
    m_scaleU = scale;
    m_singleTextureFlag = 0;
    m_textureCount = static_cast<unsigned short>(tag);
}

/*
 * --INFO--
 * PAL Address: 0x8003DA38
 * PAL Size: 472b
 * EN Address: 0x8004CF5C
 * EN Size: 608b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterial::Set(_GXTexMapID texMapId)
{
    register int curTexMap = texMapId;
    Mtx texMtx;
    PSMTXIdentity(texMtx);

    int hasDualScroll = 0;
    if ((m_textureCount == 2) &&
        (0.0f == GetTexScroll(0)->m_u0) &&
        (0.0f == GetTexScroll(0)->m_v0) &&
        ((0.0f != GetTexScroll(1)->m_u0) ||
         (0.0f != GetTexScroll(1)->m_v0))) {
        hasDualScroll = 1;
    }

    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        if ((m_textureData.m_textures[i] != 0) &&
            ((m_singleTextureFlag == 0) || (i <= 0))) {
            TextureMan.SetTexture(static_cast<_GXTexMapID>(curTexMap), m_textureData.m_textures[i]);
            curTexMap++;

            if ((GetTexScroll(i)->m_u0 != 0.0f) ||
                ((GetTexScroll(i)->m_v0 != 0.0f) || hasDualScroll)) {
                if (i == 0) {
                    MaterialMan.m_curEnvTevBit |= 0x20;
                    MaterialMan.m_texScroll0TexMtx = MaterialMan.m_texMtxCur;
                    MaterialMan.m_texScroll0TexCoord = MaterialMan.m_texCoordIdCur;
                    texMtx[0][3] = GetTexScroll(i)->m_u0;
                    texMtx[1][3] = GetTexScroll(i)->m_v0;
                    GXLoadTexMtxImm(texMtx, MaterialMan.m_texMtxCur, GX_MTX2x4);
                    int texMtx0 = MaterialMan.m_texMtxCur;
                    int texCoord0 = MaterialMan.m_texCoordIdCur;
                    MaterialMan.m_texMtxCur += 3;
                    MaterialMan.m_texCoordIdCur += 1;
                    GXSetTexCoordGen2(
                        static_cast<GXTexCoordID>(texCoord0),
                        GX_TG_MTX2x4,
                        GX_TG_TEX0,
                        texMtx0,
                        GX_FALSE,
                        0x7D);
                } else {
                    MaterialMan.m_curEnvTevBit |= 0x40;
                    MaterialMan.m_texScroll1TexMtx = MaterialMan.m_texMtxCur;
                    MaterialMan.m_texScroll1TexCoord = MaterialMan.m_texCoordIdCur;
                    texMtx[0][3] = GetTexScroll(i)->m_u0;
                    texMtx[1][3] = GetTexScroll(i)->m_v0;
                    GXLoadTexMtxImm(texMtx, MaterialMan.m_texMtxCur, GX_MTX2x4);
                    int texMtx1 = MaterialMan.m_texMtxCur;
                    int texCoord1 = MaterialMan.m_texCoordIdCur;
                    MaterialMan.m_texMtxCur += 3;
                    MaterialMan.m_texCoordIdCur += 1;
                    GXSetTexCoordGen2(
                        static_cast<GXTexCoordID>(texCoord1),
                        GX_TG_MTX2x4,
                        GX_TG_TEX1,
                        texMtx1,
                        GX_FALSE,
                        0x7D);
                }
            }
        }
    }

    return curTexMap;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004D1BC
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::CacheLoadTexture(CAmemCacheSet* amemCacheSet)
{
    for (int i = 0; i < GetNumTexture(); i++) {
        CTexture* texture = GetTexture(i);
        if (texture != 0) {
            texture->CacheLoadTexture(amemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004D230
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::CacheUnLoadTexture(CAmemCacheSet* amemCacheSet)
{
    for (int i = 0; i < GetNumTexture(); i++) {
        CTexture* texture = GetTexture(i);
        if (texture != 0) {
            texture->CacheUnLoadTexture(amemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004D2A4
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::CacheRefCnt0UpTexture(CAmemCacheSet* amemCacheSet)
{
    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        CTexture* texture = m_textureData.m_textures[i];
        if (texture != 0) {
            texture->CacheRefCnt0UpTexture(amemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004D318
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::CacheDumpTexture(CAmemCacheSet* amemCacheSet)
{
    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        CTexture* texture = m_textureData.m_textures[i];
        if (texture != 0) {
            texture->CacheUnLoadTexture(amemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003D9F0
 * PAL Size: 72b
 * EN Address: 0x8004D38C
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterial::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, MaterialMan.GetMemoryStage(), file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003D998
 * PAL Size: 88b
 * EN Address: 0x8004D3E0
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::CMaterialSet()
{
    m_materials.SetStage(MaterialMan.GetMemoryStage());
}

/*
 * --INFO--
 * PAL Address: 0x8003D8C0
 * PAL Size: 216b
 * EN Address: 0x8004D440
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::~CMaterialSet()
{
    for (unsigned long i = 0; i < static_cast<unsigned long>(m_materials.GetSize()); i++) {
        if (m_materials.GetAt(i) != 0) {
            delete m_materials.GetAt(i);
        }
    }
    m_materials.RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003D878
 * PAL Size: 72b
 * EN Address: 0x8004D52C
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterialSet::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, MaterialMan.GetMemoryStage(), file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003CDBC
 * PAL Size: 2748b
 * EN Address: 0x8004D5F0
 * EN Size: 3352b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::Create(CChunkFile& chunkFile, CTextureSet* textureSet, CMaterialMan::TEV_BIT tevBit,
                          CLightPcs::CBumpLight* bumpLights)
{
    enum {
        CHUNK_MATL = 0x4D41544C,
        CHUNK_TIDX = 0x54494458,
        CHUNK_NAME = 0x4E414D45,
        CHUNK_ATTR = 0x41545242,
        CHUNK_BUMP = 0x42554D50,
        CHUNK_JIME = 0x4A494D45,
        CHUNK_WATR = 0x57415452,
        CHUNK_FUR  = 0x46555220,
        CHUNK_TSCL = 0x5453434C,
        CHUNK_TSDT = 0x54534454,
        CHUNK_UFRM = 0x5546524D,
        CHUNK_VFRM = 0x5646524D,
        CHUNK_UKEY = 0x554B4559,
        CHUNK_VKEY = 0x564B4559,
    };

    CMaterial* material = 0;
    CChunkFile::CChunk chunk;
    unsigned long materialIndex;
    short bumpIndex;
    unsigned char bumpLightDirect;

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case CHUNK_MATL:
            break;
        default:
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk) != 0) {
            switch (chunk.m_id) {
            case CHUNK_TIDX: {
                {
                    unsigned long i;
                    int idx;
                    for (i = 0; (idx = i) < static_cast<unsigned long>(m_materials.GetSize()); i++) {
                        if (m_materials.GetAt(idx) == 0) {
                            goto slotFound;
                        }
                    }
                    i = m_materials.GetSize();
                slotFound:
                    materialIndex = i;
                }

                material = AllocMaterial();
                material->m_tevBit = static_cast<unsigned long>(tevBit);
                material->m_bumpLight = 0;
                material->m_textureCount = 0;
                material->m_scaleV = 1.0f;
                material->m_scaleU = 1.0f;
                material->m_singleTextureFlag = 0;
                material->m_textureCount = static_cast<unsigned short>(chunk.m_arg0);

                if (static_cast<int>(material->m_textureCount) == 0) {
                    material->m_tevBit |= 1;
                } else {
                    for (int i = 0; i < static_cast<int>(material->m_textureCount); i++) {
                        material->m_textureIndices[i] = static_cast<short>(chunkFile.Get4());
                    }
                    if (static_cast<int>(material->m_textureCount) == 2) {
                        material->m_tevBit |= 2;
                    }
                }

                AddMaterial(material, materialIndex);
            } break;
            case CHUNK_NAME: {
                material = m_materials.GetAt(materialIndex);
                strncpy(material->m_name, chunkFile.GetString(), 0x10);
            } break;
            case CHUNK_ATTR: {
                material = m_materials.GetAt(materialIndex);
                unsigned int flags = chunkFile.Get4();
                if ((flags & 1) != 0) {
                    material->m_tevBit |= 0x80;
                }
                if ((flags & 2) != 0) {
                    material->m_tevBit |= 0x10;
                }
                if ((flags & 4) != 0) {
                    material->m_tevBit |= 4;
                }
                if ((flags & 8) != 0) {
                    material->m_tevBit |= 0x100000;
                }

                material->m_blendMode = chunkFile.Get1();
                material->m_fogEnable = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                material->m_unkA6 = static_cast<unsigned char>(chunkFile.Get2());
                chunkFile.Get2();
                chunkFile.GetF4();
            } break;
            case CHUNK_BUMP: {
                if (chunk.m_version == 1) {
                    bumpLightDirect = chunkFile.Get1();
                    material->m_unkA5 = chunkFile.Get1();
                    chunkFile.Get2();
                } else {
                    bumpLightDirect = 0;
                }

                material = m_materials.GetAt(materialIndex);
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                bumpIndex = chunkFile.Get2();
                AddTextureIndex(material, chunkFile);
                material->m_scaleU = 1.0f / chunkFile.GetF4();
                material->m_scaleV = 1.0f / chunkFile.GetF4();
                material->m_unk36 = static_cast<unsigned char>(chunkFile.Get4());
                SetMaterialColor(material, chunkFile.Get4());
                material->m_materialType = 1;

                if (bumpLights != 0) {
                    material->m_bumpLight = bumpLights;
                    material->m_bumpLightDirect = 1;
                } else {
                    material->m_bumpLight = GetMapBumpLight(bumpIndex);
                    if (bumpLightDirect != 0) {
                        material->m_bumpLightDirect = 1;
                    } else {
                        material->m_bumpLightDirect = 0;
                    }
                }

                material->m_bumpLight->m_useViewSpace = material->m_materialType;
                material->m_tevBit |= 4;
            } break;
            case CHUNK_WATR: {
                material = m_materials.GetAt(materialIndex);
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                bumpIndex = chunkFile.Get2();
                unsigned char waterMode = chunkFile.Get1();
                material->m_unkA5 = chunkFile.Get1();
                material->m_scaleU = 1.0f / chunkFile.GetF4();
                material->m_scaleV = 1.0f / chunkFile.GetF4();
                material->m_materialType = 2;

                material->m_bumpLight = GetMapBumpLight(bumpIndex);
                material->m_bumpLight->m_useViewSpace = material->m_materialType;
                material->m_blendMode = 4;
                chunkFile.Get4();
                SetMaterialColor(material, chunkFile.Get4());

                if ((waterMode != 0) || (material->m_unkA5 != 0)) {
                    material->m_tevBit |= 0x80000;
                } else {
                    material->m_tevBit |= 8;
                }
            } break;
            case CHUNK_JIME: {
                material = m_materials.GetAt(materialIndex);
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                bumpIndex = chunkFile.Get2();
                material->m_unkA5 = chunkFile.Get1();
                if (chunkFile.Get1() != 0) {
                    material->m_tevBit |= 0x20000;
                }
                material->m_scaleU = 1.0f / chunkFile.GetF4();
                material->m_scaleV = 1.0f / chunkFile.GetF4();
                material->m_materialType = 3;

                material->m_bumpLight = GetMapBumpLight(bumpIndex);
                material->m_bumpLight->m_useViewSpace = material->m_materialType;
                material->m_tevBit |= 0x4000;
                chunkFile.Get4();
                SetMaterialColor(material, chunkFile.Get4());
                material->m_bumpLightDirect = 1;
            } break;
            case CHUNK_FUR: {
                material = m_materials.GetAt(materialIndex);
                AddTextureIndex(material, chunkFile);
                material->m_singleTextureFlag = 1;
            } break;
            case CHUNK_TSCL: {
                if (chunk.m_version == 1) {
                    CMapKeyFrame* keyFrameU = 0;
                    CMapKeyFrame* keyFrameV = 0;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk) != 0) {
                        switch (chunk.m_id) {
                        case CHUNK_TSDT: {
                            unsigned int slot = chunkFile.Get2() & 0xFFFF;
                            chunkFile.Get2();

                            if (keyFrameU != 0) {
                                chunkFile.GetF4();
                                material->GetTexScroll(slot)->m_uKeyFrame = keyFrameU;
                                material->GetTexScroll(slot)->m_type0 = 2;
                            } else {
                                material->GetTexScroll(slot)->m_u1 = chunkFile.GetF4();
                                if (material->GetTexScroll(slot)->m_u1 == 0.0f) {
                                    material->GetTexScroll(slot)->m_type0 = 0;
                                } else {
                                    material->GetTexScroll(slot)->m_type0 = 1;
                                }
                            }

                            if (keyFrameV != 0) {
                                chunkFile.GetF4();
                                material->GetTexScroll(slot)->m_vKeyFrame = keyFrameV;
                                material->GetTexScroll(slot)->m_type1 = 2;
                            } else {
                                material->GetTexScroll(slot)->m_v1 = chunkFile.GetF4();
                                if (material->GetTexScroll(slot)->m_v1 == 0.0f) {
                                    material->GetTexScroll(slot)->m_type1 = 0;
                                } else {
                                    material->GetTexScroll(slot)->m_type1 = 1;
                                }
                            }
                        } break;
                        case CHUNK_UFRM:
                            keyFrameU = AllocMapKeyFrame(0xDD3);
                            keyFrameU->ReadFrame(chunkFile, chunk.m_arg0);
                            break;
                        case CHUNK_UKEY:
                            keyFrameU->ReadKey(chunkFile, chunk.m_arg0);
                            break;
                        case CHUNK_VFRM:
                            keyFrameV = AllocMapKeyFrame(0xDDD);
                            keyFrameV->ReadFrame(chunkFile, chunk.m_arg0);
                            break;
                        case CHUNK_VKEY:
                            keyFrameV->ReadKey(chunkFile, chunk.m_arg0);
                            break;
                        }
                    }
                    chunkFile.PopChunk();
                } else {
                    unsigned int slot = chunkFile.Get2() & 0xFFFF;
                    chunkFile.Get2();
                    material->GetTexScroll(slot)->m_u1 = chunkFile.GetF4();
                    material->GetTexScroll(slot)->m_v1 = chunkFile.GetF4();
                    if (0.0f != material->GetTexScroll(slot)->m_u1) {
                        material->GetTexScroll(slot)->m_type0 = 1;
                    }
                    if (0.0f != material->GetTexScroll(slot)->m_v1) {
                        material->GetTexScroll(slot)->m_type1 = 1;
                    }
                }
            } break;
            }
        }
        chunkFile.PopChunk();
    }
    chunkFile.PopChunk();
    SetTextureSet(textureSet);
}

/*
 * --INFO--
 * PAL Address: 0x8003CA30
 * PAL Size: 908b
 * EN Address: 0x8004E308
 * EN Size: 656b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetTextureSet(CTextureSet* textureSet)
{
    register long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials.GetAt(materialIndex);
        if (material != 0) {
            if (static_cast<int>(material->GetNumTexture()) == 0) {
                material->SetTevBit(static_cast<CMaterialMan::TEV_BIT>(1));
            } else {
                for (int i = 0; i < material->GetNumTexture(); i++) {
                    ReleaseRef(material->m_textureData.m_textures[i]);
                    material->m_textureData.m_textures[i] = 0;

                    unsigned long textureIndex = static_cast<unsigned long>(material->m_textureIndices[i]);
                    if ((textureSet != 0) &&
                        (static_cast<long>(textureIndex) >= 0) &&
                        (textureIndex < static_cast<unsigned long>(textureSet->GetNumTexture()))) {
                        material->m_textureData.m_textures[i] =
                            textureSet->GetTexture(textureIndex);
                        if (material->m_textureData.m_textures[i] != 0) {
                            bool isIntensity = true;
                            material->m_textureData.m_textures[i]->AddRef();
                            unsigned int format = material->m_textureData.m_textures[i]->m_format;
                            if ((format != 9) && (format != 8)) {
                                isIntensity = false;
                            }
                            if (isIntensity) {
                                material->SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x200));
                            } else if (format == 1) {
                                material->SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x400));
                            }
                            if (static_cast<int>(material->m_textureData.m_textures[i]->m_isAlphaLut) != 0) {
                                material->SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x800));
                            }
                        }
                    } else {
                        material->m_textureData.m_textures[i] = 0;
                    }
                }

                if ((material->m_materialType != 0) &&
                    (material->GetNumTexture() >= 2) &&
                    (material->m_textureData.m_textures[0] != 0) &&
                    (material->m_textureData.m_textures[1] != 0)) {
                    material->m_texShiftU = static_cast<char>(HighestSetBit(
                        material->m_textureData.m_textures[0]->m_width /
                        material->m_textureData.m_textures[1]->m_width));
                    if (static_cast<unsigned char>(material->m_texShiftU) == 0xFF) {
                        material->m_texShiftU = 0;
                    }

                    material->m_texShiftV = static_cast<char>(HighestSetBit(
                        material->m_textureData.m_textures[0]->m_height /
                        material->m_textureData.m_textures[1]->m_height));
                    if (static_cast<unsigned char>(material->m_texShiftV) == 0xFF) {
                        material->m_texShiftV = 0;
                    }
                }
            }
        }

        materialIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C8D0
 * PAL Size: 352b
 * EN Address: 0x8004E598
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::Calc()
{
    register long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials.GetAt(materialIndex);
        if (material != 0) {
            int i = 0;
            do {
                CTexScroll* texScroll = material->GetTexScroll(i);
                if (texScroll->m_type0 == 1) {
                    texScroll->m_u0 = texScroll->m_u0 + texScroll->m_u1;
                    if (texScroll->m_u0 > 1.0f) {
                        texScroll->m_u0 = texScroll->m_u0 - 1.0f;
                    } else if (texScroll->m_u0 < 0.0f) {
                        texScroll->m_u0 = texScroll->m_u0 + 1.0f;
                    }
                } else if (texScroll->m_type0 == 2) {
                    texScroll->m_u0 = texScroll->m_uKeyFrame->Get();
                    texScroll->m_uKeyFrame->Calc();
                }

                if (texScroll->m_type1 == 1) {
                    texScroll->m_v0 = texScroll->m_v0 + texScroll->m_v1;
                    if (texScroll->m_v0 > 1.0f) {
                        texScroll->m_v0 = texScroll->m_v0 - 1.0f;
                    } else if (texScroll->m_v0 < 0.0f) {
                        texScroll->m_v0 = texScroll->m_v0 + 1.0f;
                    }
                } else if (texScroll->m_type1 == 2) {
                    texScroll->m_v0 = texScroll->m_vKeyFrame->Get();
                    texScroll->m_vKeyFrame->Calc();
                }

                i++;
            } while (i < 4);
        }

        materialIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C824
 * PAL Size: 172b
 * EN Address: 0x8004E630
 * EN Size: 188b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMaterialSet::FindTexName(char* textureName, long* textureIndexOut)
{
    long materialIndex = 0;

    while (materialIndex < static_cast<unsigned int>(m_materials.GetSize())) {
        CMaterial* material = m_materials.GetAt(materialIndex);
        if (material != 0) {
            for (int slot = 0; slot < static_cast<int>(material->m_textureCount); slot++) {
                if (material->m_textureData.m_textures[slot]->CheckName(textureName)) {
                    if (textureIndexOut != 0) {
                        *textureIndexOut = slot;
                    }
                    return materialIndex;
                }
            }
        }
        materialIndex++;
    }

    return static_cast<unsigned int>(-1);
}

/*
 * --INFO--
 * PAL Address: 0x8003C7A0
 * PAL Size: 132b
 * EN Address: 0x8004E6EC
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheLoadTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials.GetAt(static_cast<unsigned long>(materialIndex));
    if (material != 0) {
        material->CacheLoadTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C71C
 * PAL Size: 132b
 * EN Address: 0x8004E740
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheUnLoadTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials.GetAt(static_cast<unsigned long>(materialIndex));
    if (material != 0) {
        material->CacheUnLoadTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004E794
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterialSet::CacheRefCnt0UpTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials.GetAt(static_cast<unsigned long>(materialIndex));
    if (material != 0) {
        material->CacheRefCnt0UpTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C690
 * PAL Size: 140b
 * EN Address: 0x8004E83C
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMaterialSet::Find(char* name)
{
    unsigned long index = 0;

    while (index < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials.GetAt(index);
        if ((material != 0) && (strcmp(material->m_name, name) == 0)) {
            return index;
        }
        index++;
    }

    return 0xFFFFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x8003C2F0
 * PAL Size: 428b
 * EN Address: 0x8004E8CC
 * EN Size: 276b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetPartFromTextureSet(CTextureSet* textureSet, int pdtSlotIndex)
{
    u32 textureIndex = 0;

    while (textureIndex < static_cast<u32>(textureSet->GetNumTexture())) {
        CTexture* texture = textureSet->GetTexture(textureIndex);
        if (texture != 0) {
            u32 materialCount = static_cast<u32>(m_materials.GetSize());
            u32 materialIndex = textureIndex + 1;
            if ((materialIndex < materialCount) && (m_materials.GetAt(materialIndex) != 0)) {
                goto next;
            }

            CMaterial* newMaterial =
                new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", 0xEE4) CMaterial;

            float scale = 1.0f;
            newMaterial->m_tevBit = 0xFFF531F0;
            newMaterial->m_bumpLight = 0;
            newMaterial->m_textureCount = 0;
            newMaterial->m_scaleV = scale;
            newMaterial->m_scaleU = scale;
            newMaterial->m_singleTextureFlag = 0;
            newMaterial->m_textureCount = 1;
            newMaterial->m_textureIndices[0] = static_cast<short>(textureIndex);
            newMaterial->m_pdtSlotIndex = pdtSlotIndex;

            AddMaterial(newMaterial, materialIndex);
        }
next:
        textureIndex = textureIndex + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003C1B8
 * PAL Size: 312b
 * EN Address: 0x8004E9E0
 * EN Size: 296b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::ReleaseTag(CTextureSet* textureSet, int pdtSlotIndex, CAmemCacheSet* amemCacheSet)
{
    unsigned int index = 0;

    while (index < static_cast<unsigned int>(m_materials.GetSize())) {
        CMaterial* material = m_materials.GetAt(index);
        if ((material != 0) && (material->m_pdtSlotIndex == pdtSlotIndex)) {
            for (int i = 0; i < static_cast<int>(material->m_textureCount); i++) {
                CTexture* object = material->m_textureData.m_textures[i];
                if (object != 0) {
                    ReleaseRefNonNull(object);
                    material->m_textureData.m_textures[i] = 0;
                }

                textureSet->ReleaseTextureIdx(static_cast<int>(material->m_textureIndices[i]), amemCacheSet);
                material->m_textureData.m_textures[i] = 0;
            }

            if (material != 0) {
                ReleaseRefNonNull(material);
            }
            m_materials.SetAt(index, 0);
        }

        index++;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EDD8
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::IncNumTexture()
{
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EE90
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMaterial::SetTag(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMaterial::AddTextureIdx(CChunkFile& chunkFile)
{
    int index = GetNumTexture();
    m_textureCount = static_cast<unsigned short>(index + 1);
    m_textureIndices[index] = static_cast<short>(chunkFile.Get2());
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8004EDD0
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMemory::CStage* CMaterialMan::GetMemoryStage()
{
	return m_materialStage;
}
