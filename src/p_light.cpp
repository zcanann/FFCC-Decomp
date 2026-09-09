#include "ffcc/p_light.h"

#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_camera.h"
#include "ffcc/mapocttree.h"

#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>
#include <math.h>
#include <string.h>

extern const _GXColor kLightDefaultMaterialColor;
extern const _GXColor kBumpLightMapColor;
extern const float kLightDefaultAttenFalloff;
extern const float kLightZero;
extern const float kLightHalf;
extern const float kLightOne;
extern const float kBumpTexMtxScale;
extern const float kBumpTexScrollScale;
extern const float kBumpLightMapTexSize;
extern const float kLightNegativeOne;
extern const float kBumpLightMapOrthoFarZ;
extern const float kBumpLightViewZOffset;
extern const float kBumpLightTargetScale;
extern const float kBumpLightMapCoordScale;
extern const float kBumpLightMapGridStep;
extern const float kBumpLightNormalDivisor;
extern const double kLightHalfD;
extern const double kLightThreeD;
extern const double kLightZeroD;
extern const float kBumpLightMapVertexZ;
extern const double kLightU32ToDoubleBias;
extern const float kDiffuseLightDistanceScale;
extern const float kLightFullSpotCutoffDeg;
extern const float kDiffuseLightAttnK1;
extern const float kLightAlphaScale;
extern const float kMapLightAttenMax;
extern const float kLightAttnScale;
extern const float kMapLightAttnNegScale;
extern const float kMapLightAttnNegFineScale;
extern const float kLightAnimPhaseStep;
extern const float kLightRadToDeg;
float sLightAnimPhase;

static inline void setchanctrl(CLightPcs::TARGET, unsigned long);

static const char sLightPcsClassName[] = "CLightPcs";
static const char sLightManagerClassName[] = "CManager";
static const char sLightProcessClassName[] = "CProcess";
static const char sLightTextureFullMsg[0x18] =
    "\x83\x89\x83\x43\x83\x67\x82\xAA\x91\xAB\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x81\x42\x0A";

inline CLightPcs::CLightPcs()
{
}

CLightPcs LightPcs;

CProcessCallbackTable CLightPcs::m_table = {
    const_cast<char*>(sLightPcsClassName),
    static_cast<CProcessCallback>(&CLightPcs::create),
    static_cast<CProcessCallback>(&CLightPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CLightPcs::calc), 0x1C, 0},
        {static_cast<CProcessCallback>(&CLightPcs::draw), 0x2A, 0},
        {static_cast<CProcessCallback>(&CLightPcs::MakeLightMap), 0x2D, 1},
    },
};

_GXColor s_ambientAlphaColor;
static const char s_p_light_cpp[] = "p_light.cpp";

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 556b
 * EN Address: 0x800568fc
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CLightPcs::CLight::Set(CLightPcs::CLight* light)
{
    *this = *light;

    if (m_attenFalloff >= kLightDefaultAttenFalloff) {
        m_attenFalloff = m_attenRadius;
    }

    m_unkAC = m_attenRadius * m_attenRadius;
    m_range = m_attenRadius;
    if (m_range < kLightZero) {
        m_range = -m_range;
    }
    float range = m_range * kLightHalf;
    m_range = range * m_radius;

    m_targetEnable[3] = 1;
    m_targetEnable[2] = 1;
    m_targetEnable[1] = 1;
    m_targetEnable[0] = 1;
    if (*(u32*)&m_targetColor[0] == 0) {
        m_targetEnable[0] = 0;
    }
    if (*(u32*)&m_targetColor[1] == 0) {
        m_targetEnable[1] = 0;
    }
    if (*(u32*)&m_targetColor[2] == 0) {
        m_targetEnable[2] = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004A294
 * PAL Size: 180b
 * EN Address: 0x800542B0
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::Init()
{
    m_mapLightColor[0].r = 0x3F;
    m_mapLightColor[0].g = 0x3F;
    m_mapLightColor[0].b = 0x3F;
    m_mapLightColor[0].a = 0xFF;

    float lightRange = kLightNegativeOne;
    float lightParam = kLightZero;

    for (int i = 0; i < 3; i++) {
        unsigned char color = (i == 0) ? 0x3F : 0;
        m_mapLightColor[i + 1].r = color;
        m_mapLightColor[i + 1].g = color;
        m_mapLightColor[i + 1].b = color;
        m_mapLightColor[i + 1].a = 0xFF;
        m_mapLightParams[i].x = lightParam;
        m_mapLightParams[i].y = lightParam;
        m_mapLightParams[i].z = lightRange;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004a27c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CLightPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x8004a1e4
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::create()
{
    for (int i = 0; i < 0x20; i++) {
        m_bumpLights[0][i].m_hasTexture = 0;
        m_bumpLights[0][i].m_textureData = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004a11c
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::destroy()
{
    DestroyBumpLightAll(static_cast<TARGET>(1));
    DestroyBumpLightAll(static_cast<TARGET>(0));
}

/*
 * --INFO--
 * PAL Address: 0x8004a094
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::DestroyBumpLightAll(CLightPcs::TARGET target)
{
    for (u32 i = 0; i < 8; i++) {
        if (m_bumpLights[target][i].m_textureData != 0) {
            bool hasTexture = m_bumpLights[target][i].m_textureData != 0;
            if (hasTexture) {
                Memory.Free(m_bumpLights[target][i].m_textureData);
                m_bumpLights[target][i].m_textureData = 0;
            }

            m_bumpLights[target][i].m_hasTexture = 0;
            m_bumpLights[target][i].m_useViewSpace = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::calc()
{
    m_sceneLightCount = 0;
    sLightAnimPhase += kLightAnimPhaseStep;
}

/*
 * --INFO--
 * PAL Address: 0x80049ED4
 * PAL Size: 420b
 * EN Address: 0x80054580
 * EN Size: 476b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::draw()
{
    Mtx mtx;
    Vec vec;

    PSMTXCopy(CameraPcs.m_cameraMatrix, mtx);
    CLight* light = m_sceneLights;
    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if (light->m_specularMode == 0) {
            if (light->m_directionMode != 0) {
                PSMTXMultVec(mtx, &light->m_position, &vec);
                GXInitLightPos(&light->m_gxLightObj, vec.x, vec.y, vec.z);
                GXInitLightDir(&light->m_gxLightObj, light->m_direction.x, light->m_direction.y, light->m_direction.z);
            } else {
                PSMTXMultVec(mtx, &light->m_position, &vec);
                GXInitLightPos(&light->m_gxLightObj, vec.x, vec.y, vec.z);
                PSMTXMultVecSR(mtx, &light->m_direction, &vec);
                GXInitLightDir(&light->m_gxLightObj, vec.x, vec.y, vec.z);
            }

            float cutoff;
            if (static_cast<int>(light->m_type) == 1) {
                cutoff = kLightRadToDeg * light->m_spotScale;
            } else {
                cutoff = kLightFullSpotCutoffDeg;
            }

            GXInitLightSpot(&light->m_gxLightObj, cutoff, (GXSpotFn)light->m_unk4D);
            GXInitLightAttnK(&light->m_gxLightObj, kLightAttnScale / light->m_attenFalloff,
                             kLightAttnScale / light->m_attenRadius, kLightAttnScale / light->m_attenRadius);
        } else {
            PSMTXMultVecSR(mtx, &light->m_direction, &vec);
            GXInitSpecularDir(&light->m_gxLightObj, vec.x, vec.y, vec.z);
            GXInitLightAttn(&light->m_gxLightObj, kLightZero, kLightZero, kLightOne,
                            light->m_specularScale * kLightHalf, kLightZero,
                            kLightOne - (light->m_specularScale * kLightHalf));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80049acc
 * PAL Size: 1032b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::Add(CLightPcs::CLight* light)
{
    CLight sceneLight;
    CLight* sp = &sceneLight;
    sp->Set(light);

    u32 idx = m_sceneLightCount;
    m_sceneLightCount = idx + 1;
    CLight* dst = &m_sceneLights[idx];
    *dst = sceneLight;
}

/*
 * --INFO--
 * PAL Address: 0x8004975C
 * PAL Size: 880b
 * EN Address: 0x80054A94
 * EN Size: 376b
 * JP Address: TODO
 * JP Size: TODO
 */
CLightPcs::CBumpLight* CLightPcs::AddBump(CLightPcs::CLight* srcLight, CLightPcs::TARGET target,
                                          CMemory::CStage* stage, int count)
{
    CBumpLight* bumpLight = GetFreeBumpLight(target);

    if (bumpLight == 0) {
        if (static_cast<u32>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(sLightTextureFullMsg));
        }
        return 0;
    }

    bumpLight->Set(srcLight);

    bumpLight->m_target = target;
    bumpLight->m_hasTexture = 1;
    bumpLight->m_textureCount = count;

    int texSize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    bumpLight->m_textureData =
        static_cast<u8*>(Memory._Alloc(texSize * count, stage, const_cast<char*>(s_p_light_cpp), 0x13b, 0));

    for (int i = 0; i < count; i++) {
        GXInitTexObj(&bumpLight->m_textures[i], bumpLight->m_textureData + i * texSize, (u16)0x40, (u16)0x40,
                     (GXTexFmt)3, (GXTexWrapMode)0, (GXTexWrapMode)0, (u8)0);
    }

    return bumpLight;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: 0x80054a34
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CLightPcs::CBumpLight* CLightPcs::GetFreeBumpLight(CLightPcs::TARGET target)
{
    for (int i = 0; i < 8; i++) {
        if (m_bumpLights[target][i].m_hasTexture == 0) {
            return &m_bumpLights[target][i];
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 28b
 * EN Address: 0x8005475c
 * EN Size: 28b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CLightPcs::Clear()
{
    m_numDiffuse = 0;
    m_loadedLightCount = 0;
    m_loadedLightMask = 0;
    m_sceneLightCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800494A4
 * PAL Size: 696b
 * EN Address: 0x80054C0C
 * EN Size: 784b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetMapColorAlpha(float (*) [4], _GXColor mapColor, _GXColor ambColor, unsigned char enable, float atten,
                                 float dist, float spot, unsigned char alpha)
{
    static _GXColor mcol = {0xFF, 0xFF, 0xFF, 0};

    GXSetChanMatColor((GXChannelID)4, mapColor);
    GXSetChanAmbColor((GXChannelID)4, ambColor);

    if ((enable != 0) && (alpha != 0) && (atten < kMapLightAttenMax)) {
        Mtx cam;
        Vec eyePos;
        Vec eyeDir;
        Vec transformedPos;
        Vec transformedDir;

        PSMTXCopy(CameraPcs.m_cameraMatrix, cam);

        eyePos.x = CameraPcs.m_positionX;
        eyePos.y = CameraPcs.m_positionY;
        eyePos.z = CameraPcs.m_positionZ;
        eyeDir.x = CameraPcs.m_directionX;
        eyeDir.y = CameraPcs.m_directionY;
        eyeDir.z = CameraPcs.m_directionZ;

        PSMTXMultVec(cam, &eyePos, &transformedPos);
        GXInitLightPos(&m_mapLightObj, transformedPos.x, transformedPos.y, transformedPos.z);

        PSMTXMultVecSR(cam, &eyeDir, &transformedDir);
        GXInitLightDir(&m_mapLightObj, transformedDir.x, transformedDir.y, transformedDir.z);
        GXInitLightSpot(&m_mapLightObj, spot, (GXSpotFn)4);
        GXInitLightAttnK(&m_mapLightObj, kLightAttnScale / dist, kMapLightAttnNegScale / atten, kMapLightAttnNegFineScale / atten);

        mcol.a = alpha;
        GXInitLightColor(&m_mapLightObj, mcol);

        if (m_loadedLightCount >= 8) {
            m_loadedLightCount = 7;
        }

        int lightIdMask = 1 << m_loadedLightCount;
        GXLoadLightObjImm(&m_mapLightObj, (GXLightID)lightIdMask);
        MaterialMan.SetForceBlendAlpha(0);
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, m_loadedLightMask, (GXDiffuseFn)2,
                      (GXAttnFn)1);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, lightIdMask, (GXDiffuseFn)0, (GXAttnFn)1);
        m_loadedLightCount += 1;
    } else {
        MaterialMan.SetForceBlendAlpha(ambColor.a);
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, m_loadedLightMask, (GXDiffuseFn)2,
                      (GXAttnFn)1);
        if (ambColor.a == 0xFF) {
            GXSetChanCtrl((GXChannelID)2, (u8)0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        } else {
            GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80049474
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetAmbient(_GXColor color)
{
    GXSetChanAmbColor((GXChannelID)4, color);
}

/*
 * --INFO--
 * PAL Address: 0x80049428
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetAmbientAlpha(float alpha)
{
    const float& alphaScale = kLightAlphaScale;
    float scaled = alphaScale * alpha;
    s_ambientAlphaColor.a = (u8)(int)scaled;
    GXSetChanAmbColor((GXChannelID)2, s_ambientAlphaColor);
}

/*
 * --INFO--
 * PAL Address: 0x80049420
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetNumDiffuse(unsigned long count)
{
    m_numDiffuse = count;
}

/*
 * --INFO--
 * PAL Address: 0x800493e4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetDiffuseColor(unsigned long idx, _GXColor color)
{
    GXInitLightColor(&m_diffuseLights[idx].m_gxLightObj, color);
}

/*
 * --INFO--
 * PAL Address: 0x8004934c
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::EnableLight(int param_1, int param_2)
{
    int enabled = param_1;
    int colorSrcParam = param_2;
    unsigned int light_mask;

    if (enabled != 0) {
        light_mask = m_loadedLightMask;
    } else {
        light_mask = 0;
    }

    GXSetChanCtrl((GXChannelID)0, enabled ? GX_TRUE : GX_FALSE, (GXColorSrc)0,
                  colorSrcParam ? GX_SRC_REG : GX_SRC_VTX, light_mask, (GXDiffuseFn)2, (GXAttnFn)1);
    GXSetChanCtrl((GXChannelID)2, enabled ? GX_TRUE : GX_FALSE, (GXColorSrc)0,
                  colorSrcParam ? GX_SRC_REG : GX_SRC_VTX, 0, (GXDiffuseFn)0, (GXAttnFn)2);
}

/*
 * --INFO--
 * PAL Address: 0x800491F8
 * PAL Size: 340b
 * EN Address: 0x8005515C
 * EN Size: 412b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetDiffuse(unsigned long idx, _GXColor color, Vec* dir, int mode)
{
    CLight* light = &m_diffuseLights[idx];
    Mtx cam;
    Vec lightDir;
    float dirX;
    float dirY;
    float dirZ;

    if (mode != 0) {
        dirX = CameraPcs.m_directionX;
        dirY = CameraPcs.m_directionY;
        dirZ = CameraPcs.m_directionZ;
    } else {
        dirX = dir->x;
        dirY = dir->y;
        dirZ = dir->z;
    }

    GXInitLightColor(&light->m_gxLightObj, color);
    PSMTXCopy(CameraPcs.m_cameraMatrix, cam);

    lightDir.x = kDiffuseLightDistanceScale * -dirX;
    lightDir.y = kDiffuseLightDistanceScale * -dirY;
    lightDir.z = kDiffuseLightDistanceScale * -dirZ;
    PSMTXMultVec(cam, &lightDir, &lightDir);
    GXInitLightPos(&light->m_gxLightObj, lightDir.x, lightDir.y, lightDir.z);

    lightDir.x = dirX;
    lightDir.y = dirY;
    lightDir.z = dirZ;
    PSMTXMultVecSR(cam, &lightDir, &lightDir);
    GXInitLightDir(&light->m_gxLightObj, lightDir.x, lightDir.y, lightDir.z);

    GXInitLightSpot(&light->m_gxLightObj, kLightFullSpotCutoffDeg, (GXSpotFn)4);
    GXInitLightAttnK(&light->m_gxLightObj, kLightZero, kDiffuseLightAttnK1, kLightZero);
}

/*
 * --INFO--
 * PAL Address: 0x80048FE0
 * PAL Size: 536b
 * EN Address: 0x800552F8
 * EN Size: 432b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetPosition(CLightPcs::TARGET target, Vec* pos, unsigned long mask)
{
    m_loadedLightCount = m_numDiffuse;
    m_loadedLightMask = 0;

    if (mask == 0) {
        setchanctrl(target, m_loadedLightMask);
        return;
    }

    m_loadedLightMask = (1 << m_loadedLightCount) - 1;

    CLight* diffuseLight = m_diffuseLights;
    for (u32 i = 0; i < m_numDiffuse; i++, diffuseLight++) {
        GXLoadLightObjImm(&diffuseLight->m_gxLightObj, (GXLightID)(1 << i));
    }

    if (pos != nullptr) {
        CLight* sceneLight = m_sceneLights;
        for (u32 i = 0; i < m_sceneLightCount; i++, sceneLight++) {
            if ((sceneLight->m_targetEnable[target] != 0) && ((sceneLight->m_partMask & mask) != 0) &&
                ((double)PSVECSquareDistance(pos, &sceneLight->m_position) <
                 (double)sceneLight->m_unkAC)) {
                GXInitLightColor(&sceneLight->m_gxLightObj, sceneLight->m_targetColor[target]);
                GXLoadLightObjImm(&sceneLight->m_gxLightObj, (GXLightID)(1 << m_loadedLightCount));
                m_loadedLightMask |= 1 << m_loadedLightCount;
                m_loadedLightCount += 1;
                if (m_loadedLightCount >= 8) {
                    break;
                }
            }
        }
    }

    setchanctrl(target, m_loadedLightMask);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x800554A8
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void setchanctrl(CLightPcs::TARGET target, unsigned long chanMask)
{
    GXSetNumChans(1);
    if ((int)target != 1) {
        GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, chanMask, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);

        GXSetChanMatColor(GX_COLOR0A0, kLightDefaultMaterialColor);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80048ef8
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetBit32(CLightPcs::TARGET target, unsigned long* bits)
{
    CLight* light = m_sceneLights;

    m_loadedLightCount = 0;
    m_loadedLightMask = 0;

    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if ((light->m_targetEnable[target] != 0) &&
            (((1 << (i & 0x1f)) & *(u32*)((char*)bits + ((i >> 3) & 0x1ffffffc))) != 0))
        {
            GXInitLightColor(&light->m_gxLightObj, light->m_targetColor[target]);
            GXLoadLightObjImm(&light->m_gxLightObj, (GXLightID)(1 << m_loadedLightCount));
            m_loadedLightMask |= 1 << m_loadedLightCount;
            m_loadedLightCount += 1;

            if (m_loadedLightCount >= 8) {
                return;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80048d3c
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetPart(CLightPcs::TARGET target, void* part, unsigned char mode)
{
    if (mode == 0) {
        GXSetNumChans((u8)1);
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        return;
    }

    GXAttnFn attnFn = (GXAttnFn)1;
    CLight* light = m_sceneLights;
    m_loadedLightCount = 0;
    m_loadedLightMask = 0;

    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if ((light->m_targetEnable[target] != 0) && (light->m_part == part)) {
            _GXColor lightColor = light->m_targetColor[target];
            GXInitLightColor(&light->m_gxLightObj, lightColor);
            GXLoadLightObjImm(&light->m_gxLightObj, (GXLightID)(1 << m_loadedLightCount));

            if (light->m_specularMode != 0) {
                attnFn = (GXAttnFn)0;
            }

            m_loadedLightMask |= 1 << m_loadedLightCount;
            m_loadedLightCount += 1;
            if (m_loadedLightCount >= 8) {
                break;
            }
        }
    }

    GXSetNumChans((u8)1);
    if (mode == 1) {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, m_loadedLightMask, (GXDiffuseFn)2, attnFn);
    } else {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, m_loadedLightMask, (GXDiffuseFn)2, attnFn);
    }
    GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
}

/*
 * --INFO--
 * PAL Address: 0x80048CBC
 * PAL Size: 128b
 * EN Address: 0x8005587C
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::InsertOctTree(CLightPcs::TARGET target, COctTree& octTree)
{
    octTree.ClearLight();
    CLight* light = m_sceneLights;
    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if (light->m_targetEnable[target] != 0) {
            octTree.InsertLight(i, light->m_position, light->m_range, light->m_partMask);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CLightPcs::SetForEmissionModel(CLightPcs::TARGET target, void* part)
{
    GXAttnFn attnFn = GX_AF_SPOT;
    CLight* light = m_sceneLights;
    m_loadedLightCount = 0;
    m_loadedLightMask = 0;

    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if ((light->m_targetEnable[target] != 0) && (light->m_part == part)) {
            GXInitLightColor(&light->m_gxLightObj, light->m_targetColor[target]);
            GXLoadLightObjImm(&light->m_gxLightObj, (GXLightID)(1 << m_loadedLightCount));

            if (light->m_specularMode != 0) {
                attnFn = GX_AF_NONE;
            }

            m_loadedLightMask |= 1 << m_loadedLightCount;
            m_loadedLightCount += 1;
            if (m_loadedLightCount >= 8) {
                break;
            }
        }
    }

    GXSetNumChans(GX_TRUE);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, m_loadedLightMask, GX_DF_CLAMP, attnFn);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_SPEC);
}

/*
 * --INFO--
 * PAL Address: 0x80048644
 * PAL Size: 1656b
 * EN Address: 0x80055908
 * EN Size: 1608b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::CBumpLight::MakeLightMap()
{
    if (m_textureData == 0) {
        return;
    }

    _GXColor lightColor = kBumpLightMapColor;
    _GXColor chanAmb;
    _GXColor chanMat;
    _GXColor chanAmb2;
    _GXColor chanMat2;

    unsigned char u0 = m_bumpShade[0];
    signed char u1 = m_bumpShade[1];
    signed char u2 = m_bumpShade[2];
    signed char u3 = m_bumpShade[3];

    chanAmb.a = u0;
    chanAmb.b = u0;
    chanAmb.g = u0;
    chanAmb.r = u0;
    chanMat.a = u1;
    chanMat.b = u1;
    chanMat.g = u1;
    chanMat.r = u1;
    chanAmb2.a = u2;
    chanAmb2.b = u2;
    chanAmb2.g = u2;
    chanAmb2.r = u2;
    chanMat2.a = u3;
    chanMat2.b = u3;
    chanMat2.g = u3;
    chanMat2.r = u3;

    GXSetChanAmbColor((GXChannelID)0, chanAmb);
    GXSetChanMatColor((GXChannelID)0, chanMat);
    GXSetChanAmbColor((GXChannelID)2, chanAmb2);
    GXSetChanMatColor((GXChannelID)2, chanMat2);

    Vec eyeDir;
    if (m_useViewSpace == 1) {
        Mtx tmp;
        PSMTXIdentity(tmp);
        PSMTXTrans(tmp, kLightZero, kLightZero, kBumpLightViewZOffset);
        GXLoadPosMtxImm(tmp, 0);
        PSMTXIdentity(tmp);
        GXLoadNrmMtxImm(tmp, 0);

        Vec eye;
        Vec up;
        eye.z = kLightZero;
        eye.y = kLightZero;
        eye.x = kLightZero;
        up.x = kLightZero;
        up.y = kLightOne;
        up.z = kLightZero;

        Mtx lookAt;
        C_MTXLookAt(lookAt, &eye, &up, &m_direction);

        Vec camPos;
        camPos.x = CameraPcs.m_positionX;
        camPos.y = CameraPcs.m_positionY;
        camPos.z = CameraPcs.m_positionZ;

        Vec lightPos;
        PSVECSubtract(&m_targetPosition, &camPos, &lightPos);
        PSVECNormalize(&lightPos, &lightPos);

        Vec nrm;
        PSVECNormalize(&m_direction, &nrm);

        Vec diff;
        PSVECSubtract(&lightPos, &nrm, &diff);

        float scale;
        if (m_target == 1) {
            scale = kBumpLightTargetScale;
        } else {
            scale = kLightOne;
        }
        PSVECScale(&diff, &diff, scale);
        PSVECAdd(&nrm, &diff, &nrm);
        PSVECNormalize(&nrm, &nrm);

        PSMTXMultVecSR(lookAt, &nrm, &eyeDir);
    } else {
        Mtx tmp;
        PSMTXIdentity(tmp);
        GXLoadPosMtxImm(tmp, 0);
        GXLoadNrmMtxImm(tmp, 0);
        eyeDir.x = m_direction.x;
        eyeDir.y = m_direction.y;
        eyeDir.z = m_direction.z;
    }

    int copySize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    static float tParam[4] = {48.0f, 128.0f, 256.0f, 512.0f};

    for (int i = 0; i < (int)(unsigned int)m_textureCount; i++) {
        u8* texDst = m_textureData + i * copySize;
        GXLightObj lightObj;
        GXInitSpecularDir(&lightObj, eyeDir.x, eyeDir.y, eyeDir.z);

        GXInitLightColor(&lightObj, lightColor);

        if (m_target == 1) {
            float d1 = m_specularScale * kLightHalf;
            GXInitLightAttn(&lightObj, kLightZero, kLightZero, kLightOne, d1, kLightZero,
                            kLightOne - d1);
        } else {
            float d1 = tParam[i] * kLightHalf;
            GXInitLightAttn(&lightObj, kLightZero, kLightZero, kLightOne, d1, kLightZero,
                            kLightOne - d1);
        }

        GXLoadLightObjImm(&lightObj, (GXLightID)1);

        float dInv = kBumpLightNormalDivisor;
        float dW = kBumpLightMapVertexZ;
        u32 y = 0;
        do {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 0x42);

            float fy = (float)y;
            float dFactor = kBumpLightMapCoordScale;
            float dHalf = kLightOne;
            float dScale = kBumpLightMapGridStep;
            for (u32 x = 0; x < 0x21; x++) {
                float t0 = dFactor * fy;
                float x0 = t0 * dScale - dHalf;
                float xd0 = x0 / dInv;
                float tz = dFactor * (float)x;
                float z0 = tz * dScale - dHalf;
                float zd = z0 / dInv;
                float t1 = dFactor * (float)(y + 1);
                float x1 = t1 * dScale - dHalf;
                float xd1 = x1 / dInv;
                float dist0 = z0 * z0 + x0 * x0;
                if (dist0 < dHalf) {
                    dist0 = sqrtf(dHalf - dist0);
                } else {
                    dist0 = kLightZero;
                }

                float dist1 = z0 * z0 + x1 * x1;
                GXPosition3f32(x0, z0, dW);
                GXNormal3f32(xd0, zd, dist0);

                if (dist1 < dHalf) {
                    dist1 = sqrtf(dHalf - dist1);
                } else {
                    dist1 = kLightZero;
                }

                GXPosition3f32(x1, z0, dW);
                GXNormal3f32(xd1, zd, dist1);
            }

            y++;
        } while (y < 0x20);

        GXSetTexCopySrc(0, 0, 0x40, 0x40);
        GXSetTexCopyDst((unsigned short)0x40, (unsigned short)0x40, (GXTexFmt)3, (unsigned char)0);
        GXCopyTex(texDst, 1);
        GXPixModeSync();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::MakeLightMap()
{
    Mtx44 projection;

    GXSetCullMode(GX_CULL_BACK);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetColorUpdate(GX_TRUE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetViewport(kLightZero, kLightZero, kBumpLightMapTexSize, kBumpLightMapTexSize, kLightZero, kLightOne);
    GXSetScissor(0, 0, 0x40, 0x40);
    C_MTXOrtho(projection, kLightNegativeOne, kLightOne, kLightNegativeOne, kLightOne, kLightOne,
               kBumpLightMapOrthoFarZ);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_NONE, GX_AF_SPEC);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetAlphaUpdate(GX_TRUE);

    for (u32 target = 0; target < 4; target++) {
        u32 i = 0;
        do {
            if (m_bumpLights[target][i].m_hasTexture != 0) {
                m_bumpLights[target][i].MakeLightMap();
            }
            i++;
        } while (i < 8);
    }

    Graphic.SetStdPixelFmt();
    GraphicPcs.setViewport();
    PSMTX44Copy(CameraPcs.m_screenMatrix, projection);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetTexCopySrc(0, 0, 0x40, 0x40);
    GXSetTexCopyDst((u16)0x40, (u16)0x40, GX_TF_IA8, GX_FALSE);
    GXCopyTex(Graphic.m_scratchTextureBuffer, GX_TRUE);
}

/*
 * --INFO--
 * PAL Address: 0x80047EE0
 * PAL Size: 1180b
 * EN Address: 0x80056270
 * EN Size: 1324b
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetBumpTexMatirx(float (*mat)[4], CLightPcs::CBumpLight* bump, Vec* vec, unsigned char mode)
{
    Mtx cam;
    PSMTXCopy(CameraPcs.m_cameraMatrix, cam);
    Mtx texMtx;
    Mtx out;
    Mtx nrm;
    Mtx posOnly;

    if (mode != 0) {
        Vec pos;
        pos.x = mat[0][3];
        pos.y = mat[1][3];
        pos.z = mat[2][3];
        PSMTXMultVec(cam, &pos, &pos);

        if (mode == 1) {
            cam[0][1] = kLightZero;
            cam[0][0] = kLightOne;
            cam[0][2] = kLightZero;
            cam[1][0] = kLightZero;
            cam[1][1] = kLightOne;
            cam[1][2] = kLightZero;
            cam[2][0] = kLightZero;
            cam[2][1] = kLightZero;
            cam[2][2] = kLightOne;
        } else if (mode == 2) {
            Vec xAxis;
            Vec yAxis;
            yAxis.x = cam[0][1];
            yAxis.y = cam[1][1];
            yAxis.z = cam[2][1];
            PSVECNormalize(&yAxis, &yAxis);
            cam[0][1] = yAxis.x;
            cam[1][1] = yAxis.y;
            cam[2][1] = yAxis.z;
            xAxis.x = yAxis.y;
            xAxis.y = -yAxis.x;
            xAxis.z = kLightZero;
            PSVECNormalize(&xAxis, &xAxis);
            cam[0][0] = xAxis.x;
            cam[1][0] = xAxis.y;
            cam[2][0] = xAxis.z;
            Vec zAxis;
            PSVECCrossProduct(&xAxis, &yAxis, &zAxis);
            PSVECNormalize(&zAxis, &zAxis);
            cam[0][2] = zAxis.x;
            cam[1][2] = zAxis.y;
            cam[2][2] = zAxis.z;
        }

        PSMTXConcat(cam, mat, out);
        out[0][3] = pos.x;
        out[1][3] = pos.y;
        out[2][3] = pos.z;
    } else {
        if (vec != nullptr &&
            ((kLightZero != vec->x) || (kLightZero != vec->y) || (kLightZero != vec->z))) {
            Mtx tmp;
            PSMTXCopy(mat, tmp);
            Vec camPos;
            camPos.x = CameraPcs.m_positionX;
            camPos.y = CameraPcs.m_positionY;
            camPos.z = CameraPcs.m_positionZ;
            Vec objPos;
            objPos.x = tmp[0][3];
            objPos.y = tmp[1][3];
            objPos.z = tmp[2][3];
            PSVECSubtract(&camPos, &objPos, &camPos);
            camPos.x = camPos.x * vec->x;
            camPos.y = camPos.y * vec->y;
            camPos.z = camPos.z * vec->z;
            PSMTXMultVecSR(cam, &camPos, &camPos);
            PSMTXConcat(cam, tmp, out);
            out[0][3] += camPos.x;
            out[1][3] += camPos.y;
            out[2][3] += camPos.z;
        } else {
            PSMTXConcat(cam, mat, out);
        }
    }

    GXLoadPosMtxImm(out, 0);

    nrm[0][0] = out[0][0];
    nrm[1][0] = out[1][0];
    nrm[2][0] = out[2][0];
    nrm[0][1] = out[0][1];
    nrm[1][1] = out[1][1];
    nrm[2][1] = out[2][1];
    nrm[0][2] = out[0][2];
    nrm[1][2] = out[1][2];
    nrm[2][2] = out[2][2];
    nrm[0][3] = 0.0f;
    nrm[1][3] = 0.0f;
    nrm[2][3] = 0.0f;
    GXLoadNrmMtxImm(nrm, 0);

    if ((bump != nullptr) && (bump->m_hasTexture != 0)) {
        if (bump->m_useViewSpace == 1) {
            PSMTXTrans(texMtx, kLightHalf, kLightHalf, kLightZero);
            PSMTXConcat(texMtx, nrm, m_bumpTexMtx0);
            PSMTXScale(texMtx, kBumpTexMtxScale, kBumpTexMtxScale, kBumpTexMtxScale);
            PSMTXConcat(m_bumpTexMtx0, texMtx, m_bumpTexMtx0);
            PSMTXCopy(out, posOnly);
            posOnly[0][3] = kLightZero;
            posOnly[1][3] = kLightZero;
            posOnly[2][3] = kLightZero;
            PSMTXConcat(posOnly, texMtx, m_bumpTexMtx1);
        } else {
            PSMTXIdentity(nrm);
            PSMTXTrans(texMtx, kLightHalf, kLightHalf, kLightZero);
            PSMTXConcat(texMtx, nrm, m_bumpTexMtx0);
            PSMTXScale(texMtx, kBumpTexMtxScale, kBumpTexMtxScale, kBumpTexMtxScale);
            PSMTXConcat(m_bumpTexMtx0, texMtx, m_bumpTexMtx0);

            float camX = CameraPcs.m_positionX;
            float camZ = CameraPcs.m_positionZ;
            PSMTXIdentity(m_bumpTexMtx2);

            float half = kLightHalf;
            float zero = kLightZero;
            float scrollScale = kBumpTexScrollScale;
            m_bumpTexMtx2[0][0] = scrollScale;
            m_bumpTexMtx2[1][2] = scrollScale;
            m_bumpTexMtx2[2][2] = zero;
            m_bumpTexMtx2[1][1] = zero;
            m_bumpTexMtx2[2][1] = zero;
            m_bumpTexMtx2[0][3] =
                -(scrollScale * (camX + bump->m_offsetX) - half);
            m_bumpTexMtx2[1][3] =
                -(scrollScale * (camZ + bump->m_offsetZ) - half);
            m_bumpTexMtx2[2][3] = zero;
            m_bumpIndTexMtx[1][1] = kBumpTexMtxScale;
            m_bumpIndTexMtx[0][0] = kBumpTexMtxScale;
            m_bumpIndTexMtx[1][2] = zero;
            m_bumpIndTexMtx[1][0] = zero;
            m_bumpIndTexMtx[0][2] = zero;
            m_bumpIndTexMtx[0][1] = zero;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80047e84
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CLightPcs::CBumpLight::CBumpLight()
    : CLight()
{
    m_radius = kLightOne;
    m_hasTexture = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80047e54
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::CBumpLight::SetTexture(_GXTexMapID texMapID, int textureIdx)
{
    GXLoadTexObj(&m_textures[textureIdx], texMapID);
}

/*
 * --INFO--
 * PAL Address: 0x80047e00
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CLightPcs::CLight::CLight()
{
    m_radius = kLightOne;
    m_offsetZ = kLightZero;
    m_offsetX = kLightZero;
    m_attenFalloff = kLightDefaultAttenFalloff;
    m_directionMode = 0;
    m_spotFn = 0;
    m_unk4D = 4;
    m_specularMode = 0;
    m_partMask = -1;
    m_part = 0;
    *(u32*)&m_targetColor[0] = 0;
    *(u32*)&m_targetColor[1] = 0;
    *(u32*)&m_targetColor[2] = 0;
    *(u32*)&m_targetColor[3] = 0;
}

extern const _GXColor kLightDefaultMaterialColor = {0xFF, 0xFF, 0xFF, 0xFF};
extern const _GXColor kBumpLightMapColor = {0x88, 0x88, 0x88, 0xFF};
extern const float kLightDefaultAttenFalloff = 100000000.0f;
extern const float kLightZero = 0.0f;
extern const float kLightHalf = 0.5f;
extern const float kLightOne = 1.0f;
extern const float kBumpTexMtxScale = 0.4f;
extern const float kBumpTexScrollScale = 0.005f;
extern const float kBumpLightMapTexSize = 64.0f;
extern const float kLightNegativeOne = -1.0f;
extern const float kBumpLightMapOrthoFarZ = 15.0f;
extern const float kBumpLightViewZOffset = -4.0f;
extern const float kBumpLightTargetScale = 8.0f;
extern const float kBumpLightMapCoordScale = 2.0f;
extern const float kBumpLightMapGridStep = 0.03125f;
extern const float kBumpLightNormalDivisor = 0.8f;
extern const double kLightHalfD = 0.5;
extern const double kLightThreeD = 3.0;
extern const double kLightZeroD = 0.0;
extern const float kBumpLightMapVertexZ = -2.0f;
extern const double kLightU32ToDoubleBias = 4503599627370496.0;
extern const float kDiffuseLightDistanceScale = 100000.0f;
extern const float kLightFullSpotCutoffDeg = 360.0f;
extern const float kDiffuseLightAttnK1 = 4.999999873689376e-06f;
extern const float kLightAlphaScale = 255.0f;
extern const float kMapLightAttenMax = 999999986991104.0f;
extern const float kLightAttnScale = 0.125f;
extern const float kMapLightAttnNegScale = -0.125f;
extern const float kMapLightAttnNegFineScale = -0.015625f;
extern const float kLightAnimPhaseStep = 0.1f;
extern const float kLightRadToDeg = 57.29578f;

#pragma pool_data off
