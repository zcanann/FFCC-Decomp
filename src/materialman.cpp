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

extern const float kTextureOne;
extern const float kTextureZero;
extern const float kMaterialWarpCoeff;

extern const float kMaterialShadowScale;
extern const float kMaterialShadowBoundsRadius;
extern const float kMaterialNearestDistanceInit;
extern const float kMaterialMaxDistance;
extern const float kMaterialProjectionWidthScale;
extern const float kMaterialProjectionHeightScale;
extern const float kMaterialProjectionCenter;
extern const float kMaterialProjectionDepthScale;

static const char s_CMaterialSet[] = "CMaterialSet";
namespace {
static const char s_materialman_cpp[] = "materialman.cpp";
}
static const char s_materialStageName[] = "CMaterial.material";
static const char s_CMaterial[] = "CMaterial";
static const char s_CMaterialMan[] = "CMaterialMan";
static const char s_CManager[] = "CManager";
namespace {
static const char s_ptrarray_grow_error[] = {
    0x83, 0x6f, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x90, 0xac, 0x92, 0xb7, 0x82, 0xaa,
    0x95, 0x73, 0x8b, 0x96, 0x89, 0xc2, 0x82, 0xc5, 0x82, 0xb7, 0x81, 0x42, 0x0a, 0x00,
};
static const char s_collection_ptrarray_h[] = "collection_ptrarray.h";
}
static const char s_CPtrArray_CMaterial[] = "CPtrArray<CMaterial *>";

static inline void _GXSetTevOrder(int stage, int coord, int map, int channel)
{
    _GXSetTevOrder((_GXTevStageID)stage, (_GXTexCoordID)coord, (_GXTexMapID)map, (_GXChannelID)channel);
}

static inline void _GXSetTevColorIn(int stage, int a, int b, int c, int d)
{
    _GXSetTevColorIn((_GXTevStageID)stage, (_GXTevColorArg)a, (_GXTevColorArg)b, (_GXTevColorArg)c, (_GXTevColorArg)d);
}

static inline void _GXSetTevAlphaIn(int stage, int a, int b, int c, int d)
{
    _GXSetTevAlphaIn((_GXTevStageID)stage, (_GXTevAlphaArg)a, (_GXTevAlphaArg)b, (_GXTevAlphaArg)c, (_GXTevAlphaArg)d);
}

static inline void _GXSetTevColorOp(int stage, int op, int bias, int scale, int clamp, int outReg)
{
    _GXSetTevColorOp((_GXTevStageID)stage, (_GXTevOp)op, (_GXTevBias)bias, (_GXTevScale)scale, (unsigned char)clamp, (_GXTevRegID)outReg);
}

static inline void _GXSetTevAlphaOp(int stage, int op, int bias, int scale, int clamp, int outReg)
{
    _GXSetTevAlphaOp((_GXTevStageID)stage, (_GXTevOp)op, (_GXTevBias)bias, (_GXTevScale)scale, (unsigned char)clamp, (_GXTevRegID)outReg);
}

static inline void _GXSetTevOp(int stage, int mode)
{
    _GXSetTevOp((_GXTevStageID)stage, (_GXTevMode)mode);
}

static inline void _GXSetTevSwapMode(int stage, int rasSel, int texSel)
{
    _GXSetTevSwapMode((_GXTevStageID)stage, (_GXTevSwapSel)rasSel, (_GXTevSwapSel)texSel);
}

static inline void _GXSetTevSwapModeTable(int table, int red, int green, int blue, int alpha)
{
    _GXSetTevSwapModeTable((_GXTevSwapSel)table, (_GXTevColorChan)red, (_GXTevColorChan)green, (_GXTevColorChan)blue, (_GXTevColorChan)alpha);
}

static inline void _GXSetBlendMode(int mode, int srcFactor, int dstFactor, int logicOp)
{
    _GXSetBlendMode((_GXBlendMode)mode, (_GXBlendFactor)srcFactor, (_GXBlendFactor)dstFactor, (_GXLogicOp)logicOp);
}

static inline void _GXSetAlphaCompare(int comp0, int ref0, int op, int comp1, int ref1)
{
    _GXSetAlphaCompare((_GXCompare)comp0, (unsigned char)ref0, (_GXAlphaOp)op, (_GXCompare)comp1, (unsigned char)ref1);
}

#pragma dont_inline on
template <>
CPtrArray<CMaterial*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}
#pragma dont_inline reset

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
    return LightPcs.GetBumpLight(static_cast<CLightPcs::TARGET>(1), 0) + bumpIndex;
}

static void ReleaseRefNonNull(CRef* object)
{
    if (object->DecRef() == 0) {
        delete object;
    }
}

static void ReleaseRef(CRef* object)
{
    if (object == 0) {
        return;
    }

    ReleaseRefNonNull(object);
}

static int HighestSetBit(unsigned int value)
{
    for (int bit = 31; bit >= 0; bit--) {
        if ((value & (1u << bit)) != 0) {
            return bit;
        }
    }
    return -1;
}

static CMaterial* AllocMaterial()
{
    return new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", 0xCFF) CMaterial;
}

static void AddTextureIndex(CMaterial* material, CChunkFile& chunkFile)
{
    material->AddTextureIdx(chunkFile);
}

static CMapKeyFrame* AllocMapKeyFrame(int line)
{
    return new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", line) CMapKeyFrame();
}

static void SetMaterialColor(CMaterial* material, unsigned int rgba)
{
    material->SetMaterialColor(rgba);
}
}

#pragma dont_inline on
template <>
CPtrArray<CMaterial*>::~CPtrArray()
{
    RemoveAll();
}

template <>
void CPtrArray<CMaterial*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template <>
void CPtrArray<CMaterial*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

template <>
int CPtrArray<CMaterial*>::Add(CMaterial* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
}

template <>
int CPtrArray<CMaterial*>::setSize(unsigned long size)
{
    CMaterial** newItems;

    if (m_size < size) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_ptrarray_grow_error));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMaterial**>(
            Memory._Alloc(m_size << 2, m_stage, const_cast<char*>(s_collection_ptrarray_h), 0xFA, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }
        m_items = newItems;
    }
    return 1;
}

template <>
void CPtrArray<CMaterial*>::SetAt(unsigned long index, CMaterial* item)
{
    m_items[index] = item;
}

#pragma dont_inline on
template <>
CMaterial* CPtrArray<CMaterial*>::operator[](unsigned long index)
{
    return GetAt(index);
}
#pragma dont_inline reset

template <>
CMaterial* CPtrArray<CMaterial*>::GetAt(unsigned long index)
{
    return m_items[index];
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80041f28
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short CPad::GetButtonDown(long padIndex)
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
 * Address:	TODO
 * Size:	TODO
 */
void chkbit32(unsigned long*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void getHsb(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialMan::CMaterialMan()
    : m_color213()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::Init()
{
	m_materialStage = Memory.CreateStage(0x20000, const_cast<char*>(s_materialStageName), 0);
	m_fullShadowTevColor = 0x30;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::Quit()
{
	Memory.DestroyStage(m_materialStage);
}

/*
 * --INFO--
 * PAL Address: 0x800436ac
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetBlendMode(CMaterialSet* materialSet, int materialIndex)
{
    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = (*materials)[materialIndex];

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
        _GXSetTevSwapModeTable(
            0, 0, 1, 2, 3);
        _GXSetBlendMode(1, 1, 5, 5);
        _GXSetAlphaCompare(6, 0xC0, 0, 7, 0xFF);
        GXSetZCompLoc(0);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 1:
        _GXSetTevSwapModeTable(
            0, 0, 1, 2, 3);
        _GXSetBlendMode(1, 4, 5, 5);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 2:
        _GXSetTevSwapModeTable(
            0, 0, 1, 2, 3);
        _GXSetBlendMode(1, 4, 1, 5);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 1);
        return;

    case 3:
        _GXSetTevSwapModeTable(
            0, 3, 3, 3, 3);
        _GXSetBlendMode(3, 4, 1, 5);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 1);
        return;

    case 4:
        _GXSetTevSwapModeTable(
            0, 0, 1, 2, 3);
        _GXSetBlendMode(0, 1, 5, 5);
        _GXSetAlphaCompare(7, 0, 0, 7, 0xFF);
        GXSetZCompLoc(1);
        Graphic.SetFog(m_fogEnable, 0);
        return;

    case 5:
        _GXSetTevSwapModeTable(
            0, 0, 1, 2, 3);
        _GXSetBlendMode(1, 4, 5, 5);
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
 * EN Address: TODO
 * EN Size: TODO
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
        m_numTevStage, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 8, 10, 0xF);
    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1,
                                                                                          0);
    _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                           4, 5, 7);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
        m_numTevStage, m_bumpTexCoordIds[1], m_bumpTexMapIds[1] | 0x100, 0xFF);
    _GXSetTevOp(m_numTevStage, 4);
    IncNumTevStage();

    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[2], m_bumpTexMapIds[1] | 0x100, 0xFF);
    _GXSetTevOp(m_numTevStage, 4);
    IncNumTevStage();

    if (g_drawMaterial->m_bumpLightDirect == 0) {
        _GXSetTevOrder(
            m_numTevStage, m_bumpTexCoordIds[3], m_bumpTexMapIds[1], 0xFF);
        _GXSetTevColorIn(m_numTevStage,
                                                                                                              0xF, 0,
                                                                                                              8, 9);
        _GXSetTevAlphaIn(m_numTevStage,
                                                                                                              7, 7, 7,
                                                                                                              0);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 1, 1,
                                                                                              0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1,
                                                                                              0);
        IncNumTevStage();
        return;
    }

    int hasProjTex = g_drawMaterial->m_textureIndices[3] >= 0;
    if (hasProjTex != 0) {
        GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_bumpTexCoordIds[6]), GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY,
                          GX_FALSE, GX_PTIDENTITY);
    }

    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[3], m_bumpTexMapIds[1], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 4, 9, hasProjTex ? 0xF : 0);
    _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                           7, 7, 0);
    _GXSetTevColorOp(
        m_numTevStage, 0, 0, 0, 1, hasProjTex != 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();

    if (hasProjTex == 0) {
        return;
    }

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[6], m_bumpTexMapIds[3], 0xFF);
    _GXSetTevColorIn(m_numTevStage,
                                                                                                          0xF, 2, 8,
                                                                                                          0);
    _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                          7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80042f14
 * PAL Size: 852b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_water(_GXTevScale tevScale)
{
    float warpMtx[6];

    GXSetIndTexMtx((GXIndTexMtxID)1, LightPcs.GetBumpIndTexMtx(), 0);
    warpMtx[0] = kMaterialWarpCoeff;
    warpMtx[1] = kTextureZero;
    warpMtx[2] = kTextureZero;
    warpMtx[3] = kTextureZero;
    warpMtx[4] = kMaterialWarpCoeff;
    warpMtx[5] = kTextureZero;
    GXSetIndTexMtx((GXIndTexMtxID)2, reinterpret_cast<const float(*)[3]>(warpMtx), 1);
    GXSetNumIndStages(2);

    GXSetTevDirect((GXTevStageID)m_numTevStage);
    _GXSetTevOrder(
        m_numTevStage, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 8, 10, 0xF);
    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1,
                                                                                          0);
    _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                           4, 5, 7);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
        m_numTevStage, m_bumpTexCoordIds[3], m_bumpTexMapIds[1], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 0, 8, 0xF);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();

    GXSetTevIndBumpXYZ((GXTevStageID)m_numTevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[4], m_bumpTexMapIds[1], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 0, 0xC, 9);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();

    GXSetTevIndWarp((GXTevStageID)m_numTevStage, (GXIndTexStageID)1, GX_TRUE, GX_FALSE, (GXIndTexMtxID)2);
    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[5], m_bumpTexMapIds[2], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 8, 0, 1, 0xF);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042c60
 * PAL Size: 692b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_spec_col_water(_GXTevScale tevScale)
{
    float warpMtx[6];

    GXSetIndTexMtx((GXIndTexMtxID)1, LightPcs.GetBumpIndTexMtx(), 0);
    warpMtx[0] = kMaterialWarpCoeff;
    warpMtx[1] = kTextureZero;
    warpMtx[2] = kTextureZero;
    warpMtx[3] = kTextureZero;
    warpMtx[4] = kMaterialWarpCoeff;
    warpMtx[5] = kTextureZero;
    GXSetIndTexMtx((GXIndTexMtxID)2, reinterpret_cast<const float(*)[3]>(warpMtx), 1);
    GXSetNumIndStages(2);

    GXSetTevDirect((GXTevStageID)m_numTevStage);
    _GXSetTevOrder(
        m_numTevStage, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 8, 10, 0xF);
    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1,
                                                                                          0);
    _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                           4, 5, 7);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
        m_numTevStage, m_bumpTexCoordIds[4], m_bumpTexMapIds[1], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 4, 9, 0);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();

    GXSetTevIndWarp((GXTevStageID)m_numTevStage, (GXIndTexStageID)1, GX_TRUE, GX_FALSE, (GXIndTexMtxID)2);
    _GXSetTevOrder(
        m_numTevStage, m_bumpTexCoordIds[5], m_bumpTexMapIds[2], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 8, 0, 1, 0xF);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042b58
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
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
        m_numTevStage, m_bumpTexCoordIds[4], m_bumpTexMapIds[1], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 4, 9, 0);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    m_numTevStage =
        (((m_numTevStage) & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x80042814
 * PAL Size: 836b
 * EN Address: TODO
 * EN Size: TODO
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
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index], 0xFF);
        _GXSetTevColorIn(m_numTevStage, 0xF,
                                                                                                              8, 9, 0);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 2);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index] + 1, 0xFF);
        _GXSetTevColorIn(m_numTevStage, 0xF,
                                                                                                              8, 9, 0);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), static_cast<GXTevKColorSel>(index + 0x1C));
        _GXSetTevOrder(m_numTevStage, 0xFF, 0xFF, 0xFF);
        _GXSetTevColorIn(m_numTevStage, 4, 0,
                                                                                                              0xE, 0xF);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    } else {
        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index], 0xFF);
        _GXSetTevColorIn(m_numTevStage,
                                                                                                              0xF, 8,
                                                                                                              9, 0);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                              7, 7,
                                                                                                              0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    }
}

/*
 * --INFO--
 * PAL Address: 0x800424d0
 * PAL Size: 836b
 * EN Address: TODO
 * EN Size: TODO
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
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index], 0xFF);
        _GXSetTevColorIn(m_numTevStage, 0,
                                                                                                              8, 9,
                                                                                                              0xF);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 2);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index] + 1, 0xFF);
        _GXSetTevColorIn(m_numTevStage, 0, 8,
                                                                                                              9, 0xF);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();

        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), static_cast<GXTevKColorSel>(index + 0x1C));
        _GXSetTevOrder(m_numTevStage, 0xFF, 0xFF, 0xFF);
        _GXSetTevColorIn(m_numTevStage, 4, 0,
                                                                                                              0xE, 0xF);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7, 7,
                                                                                                              7, 0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    } else {
        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
        _GXSetTevOrder(
            m_numTevStage, m_shadowTexCoordIds[index],
            m_shadowTexMapIds[index], 0xFF);
        _GXSetTevColorIn(m_numTevStage,
                                                                                                              0, 8,
                                                                                                              9, 0xF);
        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn(m_numTevStage, 7,
                                                                                                              7, 7,
                                                                                                              0);
        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(m_numTevStage, 0, 0);
        IncNumTevStage();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80042454
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
        m_numTevStage, m_fullScreenShadowTexCoordIds1[index],
        m_fullScreenShadowTexMapIds1[index], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 0xF, 0xF, 0xF, 8);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 1);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(
        m_numTevStage, m_fullScreenShadowTexCoordIds0[index],
        m_fullScreenShadowTexMapIds0[index], 0xFF);
    _GXSetTevColorIn(
        m_numTevStage, 2, 8, 3, 0xF);
    _GXSetTevColorOp(m_numTevStage, 8, 0, 0, 1, 1);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();

    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
    _GXSetTevOrder(m_numTevStage, 0xFF, 0xFF, 4);
    _GXSetTevColorIn(
        m_numTevStage, 0, 0xF, 2, 0xF);
    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn(
        m_numTevStage, 7, 7, 7, 0);
    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
    _GXSetTevSwapMode(m_numTevStage, 0, 0);
    IncNumTevStage();
}

/*
 * --INFO--
 * PAL Address: 0x80042010
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
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
    matrixA[1][1] = screenMtx[1][1];
    matrixA[0][2] = screenMtx[0][2];
    matrixA[1][2] = screenMtx[1][2];
    matrixA[2][2] = screenMtx[2][2];
    matrixA[1][0] = screenMtx[1][0];
    matrixA[2][0] = screenMtx[2][0];
    matrixA[0][1] = screenMtx[0][1];
    matrixA[2][1] = screenMtx[2][1];
    matrixA[0][0] *= (kMaterialProjectionWidthScale / static_cast<float>(width));
    matrixA[1][1] *= -(kMaterialProjectionHeightScale / static_cast<float>(height));
    matrixA[0][2] = kMaterialProjectionCenter;
    matrixA[1][2] = kMaterialProjectionCenter;
    matrixA[2][2] = kMaterialProjectionDepthScale;

    PSMTXConcat(matrixA, matrixB, m_underWaterTexMtx);
}

/*
 * --INFO--
 * PAL Address: 0x8003fdf0
 * PAL Size: 8504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterial(CMaterialSet* materialSet, int materialIndex, int setVtxDesc, _GXTevScale tevScale)
{
    static int bTest;
    static char init;
    static int bTest2;
    static char init2;

    int isStd1000 = 0;
    SetStdEnv();

    CMaterial* material = materialSet->m_materials[materialIndex];
    g_drawMaterial = material;

    if (material->m_bumpLight != 0) {
        if (material->m_materialType == 3) {
            GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
            material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));
            unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
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
                PSMTXScale(scaleMtx, material->m_scaleU, material->m_scaleV, kTextureOne);
                scaleMtx[0][3] = material->m_textureData.m_texScroll[1].m_u0;
                scaleMtx[1][3] = material->m_textureData.m_texScroll[1].m_v0;
                GXLoadTexMtxImm(scaleMtx, m_bumpTexMtxIds[0], GX_MTX2x4);
                GXLoadTexMtxImm(reinterpret_cast<float(*)[4]>(LightPcs.m_bumpTexScratch), m_bumpTexMtxIds[3], GX_MTX2x4);

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
                    _GXSetTevOrder(m_numTevStage, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
                    _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 4, 5, 7);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 4);
                    _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 3);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 0xFF);
                    _GXSetTevColorIn(m_numTevStage, 0, 6, 9, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    IncNumTevStage();
                    addtev_bump_jimen(tevScale);
                } else {
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(m_numTevStage, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
                    _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 4, 5, 7);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
                        _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 4);
                        _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
                        _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 3);
                        _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
                        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                        _GXSetTevSwapMode(m_numTevStage, 0, 0);
                        IncNumTevStage();
                        GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                        _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 0xFF);
                        _GXSetTevColorIn(m_numTevStage, 0, 6, 9, 0xF);
                        _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                        _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
                        _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
            unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
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
                PSMTXScale(scaleMtx, material->m_scaleU, material->m_scaleV, kTextureOne);
                scaleMtx[0][3] = material->m_textureData.m_texScroll[1].m_u0;
                scaleMtx[1][3] = material->m_textureData.m_texScroll[1].m_v0;
                GXLoadTexMtxImm(scaleMtx, m_bumpTexMtxIds[0], GX_MTX2x4);
                GXLoadTexMtxImm(reinterpret_cast<float(*)[4]>(LightPcs.m_bumpTexScratch), m_bumpTexMtxIds[3], GX_MTX2x4);
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
            unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
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
    unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
    if (m_activeEnvTevBit == tevBit) {
        return;
    }
    m_activeEnvTevBit = tevBit;
    GXSetNumIndStages(0);
    if ((tevBit & 1) != 0) {
        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevOrder(0, 0xFF, 0xFF, 4);
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
            GXSetTevColor(GX_TEVREG2, tevColor2);
            GXSetTevColor(static_cast<GXTevRegID>(3), tevColor3);
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            _GXSetTevSwapModeTable(1, 0, 3, 3, 3);
            _GXSetTevSwapModeTable(2, 2, 2, 2, 3);
            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(0, 0xF, 8, 4, 0xF);
            _GXSetTevColorOp(0, 0, 0, 0, 0, 0);
            _GXSetTevSwapMode(0, 0, 1);
            _GXSetTevOrder(0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 0xFF);
            GXSetTevDirect(GX_TEVSTAGE1);
            _GXSetTevColorIn(1, 0xF, 8, 6, 0);
            _GXSetTevAlphaIn(1, 7, 6, 4, 7);
            _GXSetTevColorOp(1, 0, 0, 0, 1, 0);
            _GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
            _GXSetTevSwapMode(1, 0, 2);
            _GXSetTevOrder(1, m_texCoordIdCurShadow, m_texMapIdCurShadow + 1, 0xFF);
            GXSetTevDirect(GX_TEVSTAGE2);
            _GXSetTevColorIn(2, 0xF, 0, 10, 0xF);
            _GXSetTevAlphaIn(2, 7, 0, 5, 7);
            _GXSetTevColorOp(2, 0, 0, tevScale, 1, 0);
            _GXSetTevAlphaOp(2, 0, 0, 0, 1, 0);
            _GXSetTevSwapMode(2, 0, 0);
            _GXSetTevOrder(2, 0xFF, 0xFF, 4);
            m_numTevStage = 3;
        } else {
            GXSetTevDirect(GX_TEVSTAGE0);
            if ((tevBit & 0x20) != 0) {
                _GXSetTevOrder(0, m_texScroll0TexCoord, m_texMapIdCurShadow, 4);
            } else {
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCurShadow), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
                _GXSetTevOrder(0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
            }
            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(0, 0xF, 8, 10, 0xF);
            _GXSetTevColorOp(0, 0, 0, tevScale, 1, 0);
            _GXSetTevAlphaIn(0, 7, 4, 5, 7);
            _GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
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
            _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 4);
            _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
            _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 2);
            _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
            _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(m_numTevStage, texCoordId, (m_texMapIdCurShadow & 0xFF) + 1, 0xFF);
            _GXSetTevColorIn(m_numTevStage, 0, 4, 9, 0xF);
            _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
            _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
                _GXSetTevOrder(m_numTevStage, m_texCoordIdCurShadow, (m_texMapIdCurShadow & 0xFF) + 1, 4);
            } else {
                _GXSetTevOrder(m_numTevStage, m_texScroll0TexCoord, (m_texMapIdCurShadow & 0xFF) + 1, 4);
            }
            _GXSetTevColorIn(m_numTevStage, 0xF, 8, 10, 0xF);
            _GXSetTevColorOp(m_numTevStage, 0, 0, tevScale, 1, 2);
            _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
            _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
            _GXSetTevSwapMode(m_numTevStage, 0, 0);
            IncNumTevStage();
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevOrder(m_numTevStage, 0xFF, 0xFF, 0xFF);
            _GXSetTevColorIn(m_numTevStage, 0, 4, 7, 0xF);
            _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 0);
            _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
            _GXSetTevOrder(0, 0, 0, 4);
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
            _GXSetTevOrder(m_numTevStage, *reinterpret_cast<int*>(&m_pad0D4), *reinterpret_cast<int*>(&m_pad0CC), 4);
            if (m_manaParaboloidTexObj0 != 0) {
                _GXSetTevColorIn(m_numTevStage, 8, 8, 0, 0xF);
            } else {
                _GXSetTevColorIn(m_numTevStage, 0xF, 0xF, 0xF, 0);
            }
            _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(m_numTevStage, 7, 5, 0, 7);
            _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
            _GXSetBlendMode(1, 4, 5, 0xF);
            m_numTevStage = 0;
            unsigned int alpha = m_manaAlpha;
            unsigned int alphaInv = 0xFFFFFF00 | m_manaAlpha;
            GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
            _GXSetTevSwapModeTable(1, 0, 1, 2, 0);
            _GXSetTevSwapMode(m_numTevStage, 0, 1);
            _GXSetTevOrder(m_numTevStage, m_texCoordIdCur, m_texMapIdCur, 4);
            GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCur), GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            GXLoadTexObj(m_manaParaboloidTexObj1, static_cast<GXTexMapID>(m_texMapIdCur));
            IncTexCoordIdCur();
            IncTexMapIdCur();
            GXColor kColor0 = *reinterpret_cast<GXColor*>(&alpha);
            GXSetTevKColor(GX_KCOLOR0, kColor0);
            GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K0_A);
            if (bTest != 0) {
                _GXSetTevColorIn(m_numTevStage, 0xF, 0xF, 0xF, 0xB);
                _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 5);
                _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                if (bTest2 == 2) {
                    _GXSetTevColorIn(m_numTevStage, 0xF, 0xB, 0xC, 0xC);
                    _GXSetTevColorOp(m_numTevStage, 1, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 5, 6, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 1, 0, 0, 1, 0);
                }
                IncNumTevStage();
            } else {
                _GXSetTevColorIn(m_numTevStage, 10, 0xE, 8, 0xF);
                _GXSetTevColorOp(m_numTevStage, 8, 0, 0, 1, 1);
                _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 6);
                _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 1);
                IncNumTevStage();
                GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                _GXSetTevSwapMode(m_numTevStage, 0, 1);
                _GXSetTevOrder(m_numTevStage, m_texCoordIdCur, m_texMapIdCur, 4);
                GXSetTexCoordGen2(static_cast<GXTexCoordID>(m_texCoordIdCur), GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
                GXLoadTexObj(m_manaParaboloidTexObj0, static_cast<GXTexMapID>(m_texMapIdCur));
                IncTexCoordIdCur();
                IncTexMapIdCur();
                GXColor kColor1 = *reinterpret_cast<GXColor*>(&alphaInv);
                GXSetTevKColor(GX_KCOLOR1, kColor1);
                GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K1);
                GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K1_A);
                _GXSetTevColorIn(m_numTevStage, 0xE, 0xB, 8, 0xF);
                _GXSetTevColorOp(m_numTevStage, 0xC, 0, 0, 1, 2);
                _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 6);
                _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 2);
                IncNumTevStage();
                GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                _GXSetTevSwapMode(m_numTevStage, 0, 1);
                _GXSetTevOrder(m_numTevStage, 0, 0, 4);
                if (bTest2 == 0) {
                    _GXSetTevColorIn(m_numTevStage, 0xF, 2, 0xC, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 5, 6, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 1, 0, 0, 1, 0);
                } else if (bTest2 == 1) {
                    _GXSetTevColorIn(m_numTevStage, 0xF, 0xC, 2, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 6, 6, 7);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                } else if (bTest2 == 2) {
                    _GXSetTevColorIn(m_numTevStage, 0xF, 0xC, 4, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 5, 6, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 1, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 6, 6, 7);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                } else {
                    _GXSetTevColorIn(m_numTevStage, 2, 4, 0xB, 0xF);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 2, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
                }
                IncNumTevStage();
                if (bTest2 == 0) {
                    GXColor kColor3 = *reinterpret_cast<GXColor*>(&alpha);
                    GXSetTevKColor(GX_KCOLOR3, kColor3);
                    GXSetTevKColorSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KCSEL_K3);
                    GXSetTevKAlphaSel(static_cast<GXTevStageID>(m_numTevStage), GX_TEV_KASEL_K3_A);
                    GXSetTevDirect(static_cast<GXTevStageID>(m_numTevStage));
                    _GXSetTevSwapMode(m_numTevStage, 0, 0);
                    _GXSetTevOrder(m_numTevStage, 0, 0, 4);
                    _GXSetTevColorIn(m_numTevStage, 0xF, 4, 0xC, 0);
                    _GXSetTevColorOp(m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevAlphaIn(m_numTevStage, 7, 7, 7, 6);
                    _GXSetTevAlphaOp(m_numTevStage, 0, 0, 0, 1, 0);
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
 * PAL Address: 0x8003fb4c
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
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
 * PAL Address: 0x8003f07c
 * PAL Size: 2768b
 * EN Address: TODO
 * EN Size: TODO
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
    CMaterial* material = (*materials)[materialIndex];
    material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));

    unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
    if (m_activeEnvTevBit != tevBit) {
        m_activeEnvTevBit = tevBit;
        GXSetArray(GX_VA_NRM, m_geometryArraySource, 6);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);

    if ((tevBit & 0x400) != 0) {
        if ((tevBit & 0x20) != 0) {
            m_texCoordIdCur = m_texCoordIdCur - 1;
            _GXSetTevOrder(
                0, m_texScroll0TexCoord, m_texMapIdCurShadow, 4);
        } else {
            GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                              static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
            _GXSetTevOrder(
                0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
        }
        _GXSetTevColorIn(0, 0xF, 0xC, 0xA, 0xF);
        _GXSetTevColorOp(0, 0, 0, 1, 1, 0);
        _GXSetTevAlphaIn(0, 7, 4, 5, 7);
        _GXSetTevAlphaOp(0, 0, 0, 2, 1, 0);
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
            _GXSetTevOrder(0, 0xFF, 0xFF, 4);
            _GXSetTevColorIn(
                0, 0xF, 0xC, 0xA, 0xF);
            _GXSetTevColorOp(0, 0, 0, 1, 1, 0);
            _GXSetTevAlphaIn(
                0, 7, 6, 5, 7);
            _GXSetTevAlphaOp(0, 0, 0, 2, 1, 0);
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

            _GXSetTevSwapModeTable(
                1, 0, 3, 3, 3);
            _GXSetTevSwapModeTable(
                2, 2, 2, 2, 3);

            GXSetTevDirect(GX_TEVSTAGE0);
            _GXSetTevColorIn(
                0, 0xF, 8, 4, 0xF);
            _GXSetTevColorOp(0, 0, 0, 0, 0, 0);
            _GXSetTevSwapMode(0, 0, 1);
            _GXSetTevOrder(
                0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 0xFF);

            GXSetTevDirect(GX_TEVSTAGE1);
            _GXSetTevColorIn(
                1, 0xF, 8, 6, 0);
            _GXSetTevAlphaIn(
                1, 7, 6, 4, 7);
            _GXSetTevColorOp(1, 0, 0, 0, 1, 0);
            _GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
            _GXSetTevSwapMode(1, 0, 2);
            _GXSetTevOrder(
                1, m_texCoordIdCurShadow, m_texMapIdCurShadow + 1, 0xFF);

            GXSetTevDirect(GX_TEVSTAGE2);
            _GXSetTevColorIn(
                2, 0xF, 0, 0xA, 0xF);
            _GXSetTevAlphaIn(
                2, 7, 0, 5, 7);
            _GXSetTevColorOp(2, 0, 0, 1, 1, 0);
            _GXSetTevAlphaOp(2, 0, 0, 2, 1, 0);
            _GXSetTevSwapMode(2, 0, 0);
            _GXSetTevOrder(2, 0xFF, 0xFF, 4);

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
                        0, m_texScroll0TexCoord, m_texMapIdCurShadow, 4);
                } else {
                    GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                      static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
                    _GXSetTevOrder(
                        0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
                }

                _GXSetTevSwapModeTable(
                    1, 3, 3, 3, 0);
                _GXSetTevColorIn(
                    0, 0xF, 8, 0xA, 0xF);
                _GXSetTevColorOp(
                    0, 0, 0, 1, 1, 0);
                _GXSetTevAlphaIn(
                    0, 7, 4, 5, 7);
                _GXSetTevAlphaOp(
                    0, 0, 0, 2, 1, 0);
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
                        0, m_texScroll0TexCoord, m_texMapIdCurShadow, 4);
                } else {
                    GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                      static_cast<_GXTexGenType>(1), static_cast<_GXTexGenSrc>(4), 0x3C, 0, 0x7D);
                    _GXSetTevOrder(
                        0, m_texCoordIdCurShadow, m_texMapIdCurShadow, 4);
                }

                _GXSetTevColorIn(
                    0, 0xF, 8, 0xA, 0xF);
                _GXSetTevColorOp(
                    0, 0, 0, 1, 1, 0);
                _GXSetTevAlphaIn(
                    0, 7, 4, 5, 7);
                _GXSetTevAlphaOp(
                    0, 0, 0, 2, 1, 0);
                _GXSetTevSwapMode(0, 0, 0);
                m_numTevStage = 1;

                if ((tevBit != 0) && ((tevBit & 2) != 0)) {
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
                        m_numTevStage, texCoordId,
                        (m_texMapIdCurShadow & 0xFF) + 1, 4);
                    _GXSetTevColorIn(
                        m_numTevStage, 0xF, 8, 0xA, 0xF);
                    _GXSetTevColorOp(
                        m_numTevStage, 0, 0, 1, 1, 1);
                    _GXSetTevAlphaIn(
                        m_numTevStage, 7, 7, 7, 0);
                    _GXSetTevAlphaOp(
                        m_numTevStage, 0, 0, 0, 1, 0);
                    _GXSetTevSwapMode(
                        m_numTevStage, 0, 0);
                    m_numTevStage =
                        ((m_numTevStage & 0xFF) + 1) & 0xFF;

                    GXSetTevDirect(static_cast<_GXTevStageID>(m_numTevStage));
                    _GXSetTevOrder(
                        m_numTevStage, texCoordId,
                        (m_texMapIdCurShadow & 0xFF) + 1, 0xFF);
                    _GXSetTevColorIn(
                        m_numTevStage, 0, 2, 9, 0xF);
                    _GXSetTevColorOp(
                        m_numTevStage, 0, 0, 1, 1, 0);
                    _GXSetTevAlphaIn(
                        m_numTevStage, 7, 7, 7, 0);
                    _GXSetTevAlphaOp(
                        m_numTevStage, 0, 0, 0, 1, 0);
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
            }
        }
    }

        GXSetNumTexGens(((m_texCoordIdCur & 0xFF) + 1) & 0xFF);
        GXSetNumTevStages(m_numTevStage & 0xFF);
        return;
    }

    if ((tevBit & 0x200) != 0) {
        _GXSetTevOrder(
            1, m_texCoordIdCurShadow, m_texMapIdCurShadow + 1, 0xFF);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003eba0
 * PAL Size: 1244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetMaterialMenu(CMaterialSet* materialSet, int materialIndex, int setVtxDesc)
{
    SetStdEnv();

    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = (*materials)[materialIndex];
    material->Set(static_cast<_GXTexMapID>(m_texMapIdCur));

    unsigned int tevBit = m_curEnvTevBit & material->m_tevBit;
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

        _GXSetTevSwapModeTable(
            1, 0, 3, 3, 3);
        _GXSetTevSwapModeTable(
            2, 2, 2, 2, 3);

        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevColorIn(
            0, 0xF, 8, 4, 0xF);
        _GXSetTevColorOp(0, 0, 0, 0, 0, 0);
        _GXSetTevSwapMode(0, 0, 1);
        _GXSetTevOrder(0, 0, 0, 0xFF);

        GXSetTevDirect(GX_TEVSTAGE1);
        _GXSetTevColorIn(
            1, 0xF, 8, 6, 0);
        _GXSetTevAlphaIn(
            1, 7, 6, 4, 7);
        _GXSetTevColorOp(1, 0, 0, 0, 1, 0);
        _GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(1, 0, 2);
        _GXSetTevOrder(1, 0, 1, 0xFF);

        GXSetTevDirect(GX_TEVSTAGE2);
        _GXSetTevColorIn(
            2, 0xF, 0, 10, 0xF);
        _GXSetTevAlphaIn(
            2, 7, 0, 5, 7);
        _GXSetTevColorOp(2, 0, 0, 0, 1, 0);
        _GXSetTevAlphaOp(2, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode(2, 0, 0);
        _GXSetTevOrder(2, 0xFF, 0xFF, 4);

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
                    0,
                    m_texScroll0TexCoord,
                    m_texMapIdCurShadow,
                    4);
            } else {
                GXSetTexCoordGen2(static_cast<_GXTexCoordID>(m_texCoordIdCurShadow),
                                  GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(
                    0,
                    m_texCoordIdCurShadow,
                    m_texMapIdCurShadow,
                    4);
            }

            _GXSetTevSwapModeTable(
                1, 3, 3, 3, 0);
            _GXSetTevColorIn(
                0, 0xF, 8, 10, 0xF);
            _GXSetTevColorOp(0, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(
                0, 7, 4, 5, 7);
            _GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
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
            1,
            m_texCoordIdCurShadow,
            m_texMapIdCurShadow + 1,
            0xFF);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003eb24
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
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
    tmp1[0][3] = kTextureZero;
    tmp1[1][3] = kTextureZero;
    tmp1[2][3] = kTextureZero;
    GXLoadNrmMtxImm(tmp1, GX_PNMTX0);
    PSMTXCopy(tmp1, m_objTextureMtx);
}

/*
 * --INFO--
 * PAL Address: 0x8003e9a8
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
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

        if ((kTextureZero != u1) || (kTextureZero != v1)) {
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
 * PAL Address: 0x8003e904
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
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
 * PAL Address: 0x8003e71c
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadow(CMapShadow& shadow, float (*viewMtx) [4], int shadowIndex, unsigned long materialFlag)
{
    CMaterialSet* materialSet = MapMng.m_materialSet;
    CPtrArray<CMaterial*>* materials = &materialSet->m_materials;
    CMaterial* material = (*materials)[shadow.m_materialIndex];

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
 * PAL Address: 0x8003e660
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadowBit32(CMapShadow::TARGET target, unsigned long* shadowBit32, float (*viewMtx) [4])
{
    CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = (*mapShadowArray)[i];

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
 * PAL Address: 0x8003e394
 * PAL Size: 716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
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
        CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
        ShadowCandidate shadowCandidates[128];
        ShadowCandidate* candidateWrite = shadowCandidates;
        int candidateCount = 0;

        for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
            CMapShadow* shadow = (*mapShadowArray)[i];

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
                kMaterialShadowScale,
                kMaterialShadowScale,
                kTextureOne);

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
                    ->CheckFrustum(shadowPos, scaledShadowMtx, kMaterialShadowBoundsRadius) != 0) {
                goto writeCandidate;
            }
        }

        float maxDist = kMaterialMaxDistance;
        float candidateDist;
        ShadowCandidate* nearest = 0;
        float nearestDist = kMaterialNearestDistanceInit;
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
        CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();
        for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
            CMapShadow* shadow = (*mapShadowArray)[i];

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
                kMaterialShadowScale,
                kMaterialShadowScale,
                kTextureOne);

            if ((shadow->m_materialMode == 1) ||
                (reinterpret_cast<CBound*>(searchBoundStorage)
                     ->CheckFrustum(shadowPos, scaledShadowMtx, kMaterialShadowBoundsRadius) != 0)) {
                SetShadow(*shadow, viewMtx, i, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003e14c
 * PAL Size: 584b
 * EN Address: TODO
 * EN Size: TODO
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
    CMaterial** materialWrite = materialsOut;
    int candidateCount = 0;
    int outputCount = 0;
    int outputOffset = 0;

    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = (*mapShadowArray)[i];
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
            kMaterialShadowScale,
            kMaterialShadowScale,
            kTextureOne);

        if (shadow->m_materialMode == 1) {
            if (outputCount < maxShadows) {
                *materialWrite++ = MapMng.m_materialSet->m_materials[shadow->m_materialIndex];
                shadowMtxOut[outputOffset] = shadow->m_shadowMtx;
                outputCount++;
                outputOffset++;
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
                ->CheckFrustum(shadowPos, scaledShadowMtx, kMaterialShadowBoundsRadius) != 0) {
            goto writeCandidate;
        }
    }

    ShadowCandidate* nearest = 0;
    float nearestDist = kMaterialNearestDistanceInit;
    ShadowCandidate* candidateRead = shadowCandidates;
    for (int i = 0; i < candidateCount; i++) {
        float candidateDist = candidateRead->distance;
        if (nearestDist > candidateDist) {
            nearestDist = candidateDist;
            nearest = candidateRead;
        }
        candidateRead++;
    }

    if (nearest != 0) {
        nearest->distance = kMaterialMaxDistance;
        if (outputCount < maxShadows) {
            CMapShadow* nearestShadow = nearest->shadow;
            materialsOut[outputCount] = MapMng.m_materialSet->m_materials[nearestShadow->m_materialIndex];
            shadowMtxOut[outputOffset] = nearestShadow->m_shadowMtx;
            outputCount++;
            outputOffset++;
        }
    }

    return outputCount;
}

/*
 * --INFO--
 * PAL Address: 0x8003e058
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadowBound(CMapShadow::TARGET target, CBound* bound, float (*viewMtx) [4])
{
    CPtrArray<CMapShadow*>* mapShadowArray = &MapMng.GetMapShadowArray();

    for (long i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = (*mapShadowArray)[i];

        if (shadow->m_targetEnabled[static_cast<int>(target)] == 0) {
            continue;
        }

        Vec position;
        Mtx scaledShadowMtx;

        position.x = shadow->m_modelA->m_worldMtx[0][3];
        position.y = shadow->m_modelA->m_worldMtx[1][3];
        position.z = shadow->m_modelA->m_worldMtx[2][3];
        PSMTXScaleApply(shadow->m_shadowMtx, scaledShadowMtx, kMaterialShadowScale,
                        kMaterialShadowScale, kTextureOne);

        if ((shadow->m_materialMode == 1) ||
            (bound->CheckFrustum(position, scaledShadowMtx, kMaterialShadowBoundsRadius) != 0)) {
            SetShadow(*shadow, viewMtx, i, 0xFFFFFFFF);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003ddc4
 * PAL Size: 660b
 * EN Address: TODO
 * EN Size: TODO
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
 * PAL Address: 0x80041f8c
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::IncNumTevStage()
{
    m_numTevStage = ((m_numTevStage & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialMan::GetTexMtxCur()
{
    return m_texMtxCur;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialMan::GetTexCoordIdCur()
{
    return m_texCoordIdCur;
}

/*
 * --INFO--
 * PAL Address: 0x80041fa4
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexCoordIdCur()
{
    int texCoordId = m_texCoordIdCur;
    m_texCoordIdCur = texCoordId + 1;
    return texCoordId;
}

/*
 * --INFO--
 * PAL Address: 0x80041fb8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexMtxCur()
{
    int texMtx = m_texMtxCur;
    m_texMtxCur = texMtx + 3;
    return texMtx;
}

/*
 * --INFO--
 * PAL Address: 0x80041fcc
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexMapIdCur()
{
    int texMapId = m_texMapIdCur;
    m_texMapIdCur = texMapId + 1;
    return texMapId;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialMan::GetTexMapIdCur()
{
    return m_texMapIdCur;
}

/*
 * --INFO--
 * PAL Address: 0x80041fe0
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetStdEnv()
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::DecTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetTevBit(CMaterialMan::TEV_BIT)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexMtxCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexMapIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexScroll::~CTexScroll()
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
 * PAL Address: 0x8003c66c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexScroll::CTexScroll()
{
    float zero = kTextureZero;
    m_v0 = zero;
    m_u0 = zero;
    m_v1 = zero;
    m_u1 = zero;
    m_type1 = 0;
    m_type0 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003dc38
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
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
 * PAL Address: 0x8003dd14
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CMemory::CStage* CMaterialMan::GetMemoryStage()
{
	return m_materialStage;
}

/*
 * --INFO--
 * PAL Address: 0x8003cdbc
 * PAL Size: 2748b
 * EN Address: TODO
 * EN Size: TODO
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

    CMaterial* material;
    CChunkFile::CChunk chunk;
    unsigned long materialIndex = 0;

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
                    for (i = 0; i < static_cast<unsigned long>(m_materials.GetSize()); i++) {
                        if (m_materials[i] == 0) {
                            break;
                        }
                    }
                    materialIndex = i;
                }

                material = AllocMaterial();
                material->m_tevBit = static_cast<unsigned long>(tevBit);
                material->m_bumpLight = 0;
                material->m_textureCount = 0;
                material->m_scaleV = kTextureOne;
                material->m_scaleU = kTextureOne;
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

                if (materialIndex >= static_cast<unsigned long>(m_materials.GetSize())) {
                    m_materials.Add(material);
                } else {
                    m_materials.SetAt(materialIndex, material);
                }
            } break;
            case CHUNK_NAME: {
                material = m_materials[materialIndex];
                strncpy(material->m_name, chunkFile.GetString(), 0x10);
            } break;
            case CHUNK_ATTR: {
                material = m_materials[materialIndex];
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
                unsigned char bumpLightDirect = 0;
                if (chunk.m_version == 1) {
                    bumpLightDirect = chunkFile.Get1();
                    material->m_unkA5 = chunkFile.Get1();
                    chunkFile.Get2();
                }

                material = m_materials[materialIndex];
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                short bumpIndex = chunkFile.Get2();
                AddTextureIndex(material, chunkFile);
                material->m_scaleU = kTextureOne / chunkFile.GetF4();
                material->m_scaleV = kTextureOne / chunkFile.GetF4();
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
                material = m_materials[materialIndex];
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                short bumpIndex = chunkFile.Get2();
                unsigned char waterMode = chunkFile.Get1();
                material->m_unkA5 = chunkFile.Get1();
                material->m_scaleU = kTextureOne / chunkFile.GetF4();
                material->m_scaleV = kTextureOne / chunkFile.GetF4();
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
                material = m_materials[materialIndex];
                AddTextureIndex(material, chunkFile);
                AddTextureIndex(material, chunkFile);
                short bumpIndex = chunkFile.Get2();
                material->m_unkA5 = chunkFile.Get1();
                if (chunkFile.Get1() != 0) {
                    material->m_tevBit |= 0x20000;
                }
                material->m_scaleU = kTextureOne / chunkFile.GetF4();
                material->m_scaleV = kTextureOne / chunkFile.GetF4();
                material->m_materialType = 3;

                material->m_bumpLight = GetMapBumpLight(bumpIndex);
                material->m_bumpLight->m_useViewSpace = material->m_materialType;
                material->m_tevBit |= 0x4000;
                chunkFile.Get4();
                SetMaterialColor(material, chunkFile.Get4());
                material->m_bumpLightDirect = 1;
            } break;
            case CHUNK_FUR: {
                material = m_materials[materialIndex];
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
                                material->GetTexScroll(slot)->m_type0 =
                                    (material->GetTexScroll(slot)->m_u1 == kTextureZero) ? 0 : 1;
                            }

                            if (keyFrameV != 0) {
                                chunkFile.GetF4();
                                material->GetTexScroll(slot)->m_vKeyFrame = keyFrameV;
                                material->GetTexScroll(slot)->m_type1 = 2;
                            } else {
                                material->GetTexScroll(slot)->m_v1 = chunkFile.GetF4();
                                material->GetTexScroll(slot)->m_type1 =
                                    (material->GetTexScroll(slot)->m_v1 == kTextureZero) ? 0 : 1;
                            }
                        } break;
                        case CHUNK_UFRM:
                            keyFrameU = AllocMapKeyFrame(0xDD3);
                            keyFrameU->ReadFrame(chunkFile, 0);
                            break;
                        case CHUNK_UKEY:
                            keyFrameU->ReadKey(chunkFile, chunk.m_arg0);
                            break;
                        case CHUNK_VFRM:
                            keyFrameV = AllocMapKeyFrame(0xDDD);
                            keyFrameV->ReadFrame(chunkFile, 0);
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
                    if (kTextureZero != material->GetTexScroll(slot)->m_u1) {
                        material->GetTexScroll(slot)->m_type0 = 1;
                    }
                    if (kTextureZero != material->GetTexScroll(slot)->m_v1) {
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
 * PAL Address: 0x8003ca30
 * PAL Size: 908b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetTextureSet(CTextureSet* textureSet)
{
    register long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials[materialIndex];
        if (material != 0) {
            if (static_cast<int>(material->m_textureCount) == 0) {
                material->m_tevBit |= 1;
            } else {
                for (int i = 0; i < material->m_textureCount; i++) {
                    ReleaseRef(material->m_textureData.m_textures[i]);
                    material->m_textureData.m_textures[i] = 0;

                    if (textureSet != 0) {
                        unsigned long textureIndex = static_cast<unsigned long>(material->m_textureIndices[i]);
                        if ((static_cast<long>(textureIndex) >= 0) &&
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
                                    material->m_tevBit |= 0x200;
                                } else if (format == 1) {
                                    material->m_tevBit |= 0x400;
                                }
                                if (static_cast<int>(material->m_textureData.m_textures[i]->m_isAlphaLut) != 0) {
                                    material->m_tevBit |= 0x800;
                                }
                            }
                        }
                    }
                }

                if ((material->m_materialType != 0) &&
                    (material->m_textureCount >= 2) &&
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
 * PAL Address: 0x8003c2f0
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
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
            if ((materialIndex < materialCount) && (m_materials[materialIndex] != 0)) {
                goto next;
            }

            CMaterial* newMaterial =
                new (MaterialMan.GetMemoryStage(), (char*)"materialman.cpp", 0xEE4) CMaterial;

            float scale = kTextureOne;
            newMaterial->m_tevBit = 0xFFF531F0;
            newMaterial->m_bumpLight = 0;
            newMaterial->m_textureCount = 0;
            newMaterial->m_scaleV = scale;
            newMaterial->m_scaleU = scale;
            newMaterial->m_singleTextureFlag = 0;
            newMaterial->m_textureCount = 1;
            newMaterial->m_textureIndices[0] = static_cast<short>(textureIndex);
            newMaterial->m_pdtSlotIndex = pdtSlotIndex;

            if (materialIndex >= static_cast<u32>(m_materials.GetSize())) {
                m_materials.Add(newMaterial);
            } else {
                m_materials.SetAt(materialIndex, newMaterial);
            }
        }
next:
        textureIndex = textureIndex + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003dc10
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterial::Create(unsigned long tag, CMaterialMan::TEV_BIT tevBit)
{
    m_tevBit = static_cast<unsigned long>(tevBit);
    float scale = kTextureOne;
    m_bumpLight = 0;
    m_textureCount = 0;
    m_scaleV = scale;
    m_scaleU = scale;
    m_singleTextureFlag = 0;
    m_textureCount = static_cast<unsigned short>(tag);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMaterial::IncNumTexture()
{
}

/*
 * --INFO--
 * PAL Address: 0x8003c1b8
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::ReleaseTag(CTextureSet* textureSet, int pdtSlotIndex, CAmemCacheSet* amemCacheSet)
{
    unsigned int index = 0;

    while (index < static_cast<unsigned int>(m_materials.GetSize())) {
        CMaterial* material = m_materials[index];
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialSet::AddMaterial(CMaterial*, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003d9f0
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterial::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, MaterialMan.GetMemoryStage(), file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003d878
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterialSet::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, MaterialMan.GetMemoryStage(), file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003d8c0
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::~CMaterialSet()
{
    for (unsigned long i = 0; i < static_cast<unsigned long>(m_materials.GetSize()); i++) {
        if (m_materials[i] != 0) {
            delete m_materials[i];
        }
    }
    m_materials.RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003d998
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::CMaterialSet()
{
    m_materials.SetStage(MaterialMan.GetMemoryStage());
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMaterial::CacheDumpTexture(CAmemCacheSet* amemCacheSet)
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
 * Address: TODO
 * Size: TODO
 */
void CMaterial::CacheRefCnt0UpTexture(CAmemCacheSet* amemCacheSet)
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
 * Address: TODO
 * Size: TODO
 */
void CMaterial::CacheUnLoadTexture(CAmemCacheSet* amemCacheSet)
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
 * Address: TODO
 * Size: TODO
 */
void CMaterial::CacheLoadTexture(CAmemCacheSet* amemCacheSet)
{
    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        CTexture* texture = m_textureData.m_textures[i];
        if (texture != 0) {
            texture->CacheLoadTexture(amemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c71c
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheDumpTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials[static_cast<unsigned long>(materialIndex)];
    if (material != 0) {
        material->CacheUnLoadTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMaterialSet::CacheRefCnt0UpTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials[static_cast<unsigned long>(materialIndex)];
    if (material != 0) {
        material->CacheRefCnt0UpTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMaterialSet::CacheUnLoadTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials[static_cast<unsigned long>(materialIndex)];
    if (material != 0) {
        material->CacheUnLoadTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c7a0
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheLoadTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    CMaterial* material =
        m_materials[static_cast<unsigned long>(materialIndex)];
    if (material != 0) {
        material->CacheLoadTexture(amemCacheSet);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c824
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMaterialSet::FindTexName(char* textureName, long* textureIndexOut)
{
    long materialIndex = 0;

    while (materialIndex < static_cast<unsigned int>(m_materials.GetSize())) {
        CMaterial* material = m_materials[materialIndex];
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
 * PAL Address: 0x8003c8d0
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::Calc()
{
    register long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials[materialIndex];
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
 * PAL Address: 0x8003c690
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMaterialSet::Find(char* name)
{
    unsigned long index = 0;

    while (index < static_cast<unsigned long>(m_materials.GetSize())) {
        CMaterial* material = m_materials[index];
        if ((material != 0) && (strcmp(material->m_name, name) == 0)) {
            return index;
        }
        index++;
    }

    return 0xFFFFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x8003da38
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
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
        (kTextureZero == GetTexScroll(0)->m_u0) &&
        (kTextureZero == GetTexScroll(0)->m_v0) &&
        ((kTextureZero != GetTexScroll(1)->m_u0) ||
         (kTextureZero != GetTexScroll(1)->m_v0))) {
        hasDualScroll = 1;
    }

    for (int i = 0; i < static_cast<int>(m_textureCount); i++) {
        if ((m_textureData.m_textures[i] != 0) &&
            ((m_singleTextureFlag == 0) || (i <= 0))) {
            TextureMan.SetTexture(static_cast<_GXTexMapID>(curTexMap), m_textureData.m_textures[i]);
            curTexMap++;

            if ((GetTexScroll(i)->m_u0 != kTextureZero) ||
                ((GetTexScroll(i)->m_v0 != kTextureZero) || hasDualScroll)) {
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
 * Address:	TODO
 * Size:	TODO
 */
inline void CMaterial::SetTevBit(CMaterialMan::TEV_BIT)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMaterial::GetNumTexture()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
    int index = GetTextureCount();
    m_textureCount = static_cast<unsigned short>(index + 1);
    m_textureIndices[index] = static_cast<short>(chunkFile.Get2());
}

extern const float kMaterialShadowScale = 5.0f;
extern const float kMaterialShadowBoundsRadius = -100000000.0f;
extern const float kMaterialNearestDistanceInit = 100000000000000000000.0f;
extern const float kMaterialMaxDistance = 20000000000000.0f;
extern const float kMaterialProjectionWidthScale = 320.0f;
extern const float kMaterialProjectionHeightScale = 224.0f;
extern const float kMaterialProjectionCenter = -0.5f;
extern const float kMaterialProjectionDepthScale = -1.0f;
