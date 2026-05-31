#include "ffcc/p_light.h"

#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_camera.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapocttree.h"

#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>
#include <math.h>
#include <string.h>

extern const _GXColor kBumpLightMapColor;
extern const _GXColor kLightDefaultMaterialColor;
extern float FLOAT_8032fc10;
extern float FLOAT_8032fc14;
extern float FLOAT_8032fc18;
extern float FLOAT_8032fc1c;
extern float FLOAT_8032fc20;
extern float FLOAT_8032fc24;
extern float FLOAT_8032fc28;
extern float FLOAT_8032fc2c;
extern float FLOAT_8032fc30;
extern float FLOAT_8032fc34;
extern float FLOAT_8032fc38;
extern float FLOAT_8032fc3c;
extern float FLOAT_8032fc40;
extern float FLOAT_8032fc44;
extern float FLOAT_8032fc60;
extern const float FLOAT_8032fc70 = 100000.0f;
extern const float FLOAT_8032fc74 = 360.0f;
extern const float FLOAT_8032fc78 = 0.000005f;
extern const float FLOAT_8032fc7c = 255.0f;
extern const float FLOAT_8032fc80 = 999999986991104.0f;
extern const float FLOAT_8032fc84 = 0.125f;
extern const float FLOAT_8032fc90;
extern float FLOAT_8032fc88;
extern float FLOAT_8032fc8c;
extern float FLOAT_8032fc94;
float FLOAT_8032ed10;
extern const double DOUBLE_8032fc68 = 4503599627370496.0;
extern _GXColor s_mapLightAlphaColor;

static inline float CameraPosX() { return CameraPcs.m_positionX; }
static inline float CameraPosY() { return CameraPcs.m_positionY; }
static inline float CameraPosZ() { return CameraPcs.m_positionZ; }
static inline float CameraDirX() { return CameraPcs.m_directionX; }
static inline float CameraDirY() { return CameraPcs.m_directionY; }
static inline float CameraDirZ() { return CameraPcs.m_directionZ; }
static inline MtxPtr CameraMatrix() { return CameraPcs.m_cameraMatrix; }

extern const char sLightPcsClassName[] = "CLightPcs";
extern const char sLightManagerClassName[] = "CManager";
extern const char sLightProcessClassName[] = "CProcess";
extern "C" const char sLightTextureFullMsg[0x18] =
    "\x83\x89\x83\x43\x83\x67\x82\xAA\x91\xAB\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x81\x42\x0A";

unsigned int CLightPcs::m_table_desc0[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CLightPcsFv)};
unsigned int CLightPcs::m_table_desc1[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CLightPcsFv)};
unsigned int CLightPcs::m_table_desc2[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CLightPcsFv)};
unsigned int CLightPcs::m_table_desc3[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CLightPcsFv)};
unsigned int CLightPcs::m_table_desc4[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(MakeLightMap__9CLightPcsFv)};
unsigned int CLightPcs::m_table[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(sLightPcsClassName)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1C, 0, 0, 0, 0, 0x2A, 0, 0, 0,
    0, 0x2D, 1
};

CLightPcs LightPcs;
_GXColor s_ambientAlphaColor;
extern const char s_p_light_cpp[] = "p_light.cpp";

static inline double U32ToDouble(unsigned int value)
{
    union {
        unsigned long long u;
        double d;
    } conv;

    conv.u = 0x4330000000000000ULL | (unsigned long long)value;
    return conv.d - DOUBLE_8032fc68;
}

/*
 * --INFO--
 * PAL Address: 0x8004a294
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::Init()
{
    m_mapLightColor[0].r = 0x3F;
    m_mapLightColor[0].g = 0x3F;
    m_mapLightColor[0].b = 0x3F;
    m_mapLightColor[0].a = 0xFF;

    float lightRange = FLOAT_8032fc2c;
    float lightParam = FLOAT_8032fc14;

    for (int i = 0; i < 3; i++) {
        unsigned char color = (i == 0) ? 0x3F : 0;
        m_mapLightColor[i + 1].r = color;
        m_mapLightColor[i + 1].g = color;
        m_mapLightColor[i + 1].b = color;
        m_mapLightColor[i + 1].a = 0xFF;
        m_mapLightParams[i * 3 + 0] = lightParam;
        m_mapLightParams[i * 3 + 1] = lightParam;
        m_mapLightParams[i * 3 + 2] = lightRange;
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
    return (int)m_table + (index * 0x15c);
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
    char* ptr = (char*)this;

    for (int i = 2; i != 0; i--) {
        *(u8*)(ptr + 0x1CEC) = 0;
        *(u32*)(ptr + 0x1CF0) = 0;
        *(u8*)(ptr + 0x1E24) = 0;
        *(u32*)(ptr + 0x1E28) = 0;
        *(u8*)(ptr + 0x1F5C) = 0;
        *(u32*)(ptr + 0x1F60) = 0;
        *(u8*)(ptr + 0x2094) = 0;
        *(u32*)(ptr + 0x2098) = 0;
        *(u8*)(ptr + 0x21CC) = 0;
        *(u32*)(ptr + 0x21D0) = 0;
        *(u8*)(ptr + 0x2304) = 0;
        *(u32*)(ptr + 0x2308) = 0;
        *(u8*)(ptr + 0x243C) = 0;
        *(u32*)(ptr + 0x2440) = 0;
        *(u8*)(ptr + 0x2574) = 0;
        *(u32*)(ptr + 0x2578) = 0;
        *(u8*)(ptr + 0x26AC) = 0;
        *(u32*)(ptr + 0x26B0) = 0;
        *(u8*)(ptr + 0x27E4) = 0;
        *(u32*)(ptr + 0x27E8) = 0;
        *(u8*)(ptr + 0x291C) = 0;
        *(u32*)(ptr + 0x2920) = 0;
        *(u8*)(ptr + 0x2A54) = 0;
        *(u32*)(ptr + 0x2A58) = 0;
        *(u8*)(ptr + 0x2B8C) = 0;
        *(u32*)(ptr + 0x2B90) = 0;
        *(u8*)(ptr + 0x2CC4) = 0;
        *(u32*)(ptr + 0x2CC8) = 0;
        *(u8*)(ptr + 0x2DFC) = 0;
        *(u32*)(ptr + 0x2E00) = 0;
        *(u8*)(ptr + 0x2F34) = 0;
        *(u32*)(ptr + 0x2F38) = 0;

        ptr += 0x1380;
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
    u32 i = 0;
    do {
        if (m_bumpLights[i + 8].m_textureData != 0) {
            bool hasTexture = m_bumpLights[i + 8].m_textureData != 0;
            if (hasTexture) {
                Memory.Free(m_bumpLights[i + 8].m_textureData);
                m_bumpLights[i + 8].m_textureData = 0;
            }
            m_bumpLights[i + 8].m_hasTexture = 0;
            m_bumpLights[i + 8].m_useViewSpace = 0;
        }
        i++;
    } while (i < 8);

    i = 0;
    do {
        if (m_bumpLights[i].m_textureData != 0) {
            bool hasTexture = m_bumpLights[i].m_textureData != 0;
            if (hasTexture) {
                Memory.Free(m_bumpLights[i].m_textureData);
                m_bumpLights[i].m_textureData = 0;
            }
            m_bumpLights[i].m_hasTexture = 0;
            m_bumpLights[i].m_useViewSpace = 0;
        }
        i++;
    } while (i < 8);
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
    CBumpLight* bumpLights = m_bumpLights;
    CBumpLight* light = &bumpLights[static_cast<int>(target) * 8];

    for (u32 i = 0; i < 8; i++) {
        if (light[i].m_textureData != 0) {
            bool hasTexture = light[i].m_textureData != 0;
            if (hasTexture) {
                Memory.Free(light[i].m_textureData);
                light[i].m_textureData = 0;
            }

            light[i].m_hasTexture = 0;
            light[i].m_useViewSpace = 0;
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
    FLOAT_8032ed10 = FLOAT_8032ed10 + FLOAT_8032fc90;
}

/*
 * --INFO--
 * PAL Address: 0x80049ed4
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::draw()
{
    Mtx mtx;
    Vec vec;

    PSMTXCopy(CameraMatrix(), mtx);
    CLight* light = m_sceneLights;
    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if (light->m_specularMode == 0) {
            if (light->m_directionMode != 0) {
                PSMTXMultVec(mtx, reinterpret_cast<Vec*>(&light->m_position), &vec);
                GXInitLightPos(&light->m_gxLightObj, vec.x, vec.y, vec.z);
                GXInitLightDir(&light->m_gxLightObj, light->m_direction.x, light->m_direction.y, light->m_direction.z);
            } else {
                PSMTXMultVec(mtx, reinterpret_cast<Vec*>(&light->m_position), &vec);
                GXInitLightPos(&light->m_gxLightObj, vec.x, vec.y, vec.z);
                PSMTXMultVecSR(mtx, reinterpret_cast<Vec*>(&light->m_direction), &vec);
                GXInitLightDir(&light->m_gxLightObj, vec.x, vec.y, vec.z);
            }

            float cutoff;
            if (static_cast<int>(light->m_type) == 1) {
                cutoff = FLOAT_8032fc94 * light->m_spotScale;
            } else {
                cutoff = FLOAT_8032fc74;
            }

            GXInitLightSpot(&light->m_gxLightObj, cutoff, (GXSpotFn)light->m_unk4D);
            GXInitLightAttnK(&light->m_gxLightObj, FLOAT_8032fc84 / light->m_attenFalloff,
                             FLOAT_8032fc84 / light->m_attenRadius, FLOAT_8032fc84 / light->m_attenRadius);
        } else {
            PSMTXMultVecSR(mtx, reinterpret_cast<Vec*>(&light->m_direction), &vec);
            GXInitSpecularDir(&light->m_gxLightObj, vec.x, vec.y, vec.z);
            GXInitLightAttn(&light->m_gxLightObj, FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc1c,
                            light->m_specularScale * FLOAT_8032fc18, FLOAT_8032fc14,
                            FLOAT_8032fc1c - (light->m_specularScale * FLOAT_8032fc18));
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
    sceneLight = *light;
    float attenRadius = sceneLight.m_attenRadius;
    if (sceneLight.m_attenFalloff >= FLOAT_8032fc10) {
        sceneLight.m_attenFalloff = attenRadius;
    }

    sceneLight.m_unkAC = sceneLight.m_attenRadius * sceneLight.m_attenRadius;
    if (attenRadius < FLOAT_8032fc14) {
        attenRadius = -attenRadius;
    }
    sceneLight.m_range = attenRadius * FLOAT_8032fc18 * sceneLight.m_radius;

    sceneLight.m_targetEnable[3] = 1;
    sceneLight.m_targetEnable[2] = 1;
    sceneLight.m_targetEnable[1] = 1;
    sceneLight.m_targetEnable[0] = 1;
    if (*(u32*)&sceneLight.m_targetColor[0] == 0) {
        sceneLight.m_targetEnable[0] = 0;
    }
    if (*(u32*)&sceneLight.m_targetColor[1] == 0) {
        sceneLight.m_targetEnable[1] = 0;
    }
    if (*(u32*)&sceneLight.m_targetColor[2] == 0) {
        sceneLight.m_targetEnable[2] = 0;
    }

    u32 idx = m_sceneLightCount;
    m_sceneLightCount = idx + 1;
    CLight* dst = &m_sceneLights[idx];
    *dst = sceneLight;
}

/*
 * --INFO--
 * PAL Address: 0x8004975c
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CLightPcs::CBumpLight* CLightPcs::AddBump(CLightPcs::CLight* srcLight, CLightPcs::TARGET target,
                                          CMemory::CStage* stage, int count)
{
    float minFalloff = FLOAT_8032fc10;
    CBumpLight* bumpLight = 0;
    CBumpLight* bumpLights = &m_bumpLights[target * 8];

    for (int i = 0; i < 8; i++) {
        if (!bumpLights[i].m_hasTexture) {
            bumpLight = &bumpLights[i];
            break;
        }
    }

    if (bumpLight == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(sLightTextureFullMsg));
        }
        return 0;
    }

    *static_cast<CLight*>(bumpLight) = *srcLight;

    if (minFalloff <= bumpLight->m_attenFalloff) {
        bumpLight->m_attenFalloff = bumpLight->m_attenRadius;
    }

    bumpLight->m_unkAC = bumpLight->m_attenRadius * bumpLight->m_attenRadius;
    bumpLight->m_range = bumpLight->m_attenRadius;
    if (bumpLight->m_range < FLOAT_8032fc14) {
        bumpLight->m_range = -bumpLight->m_range;
    }
    bumpLight->m_range = bumpLight->m_range * FLOAT_8032fc18 * bumpLight->m_radius;

    bumpLight->m_targetEnable[3] = 1;
    bumpLight->m_targetEnable[2] = 1;
    bumpLight->m_targetEnable[1] = 1;
    bumpLight->m_targetEnable[0] = 1;

    if (*(u32*)&bumpLight->m_targetColor[0] == 0) {
        bumpLight->m_targetEnable[0] = 0;
    }
    if (*(u32*)&bumpLight->m_targetColor[1] == 0) {
        bumpLight->m_targetEnable[1] = 0;
    }
    if (*(u32*)&bumpLight->m_targetColor[2] == 0) {
        bumpLight->m_targetEnable[2] = 0;
    }

    bumpLight->m_target = target;
    bumpLight->m_hasTexture = 1;
    bumpLight->m_textureCount = count;

    int texSize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    bumpLight->m_textureData =
        static_cast<u8*>(Memory._Alloc(texSize * count, stage, const_cast<char*>(s_p_light_cpp), 0x13b, 0));

    int texOffset = 0;
    for (int i = 0; i < count; i++) {
        GXInitTexObj(&bumpLight->m_textures[i], bumpLight->m_textureData + texOffset, (u16)0x40, (u16)0x40,
                     (GXTexFmt)3, (GXTexWrapMode)0, (GXTexWrapMode)0, (u8)0);
        texOffset += texSize;
    }

    return bumpLight;
}

/*
 * --INFO--
 * PAL Address: 0x800494a4
 * PAL Size: 696b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetMapColorAlpha(float (*) [4], _GXColor mapColor, _GXColor ambColor, unsigned char enable, float atten,
                                 float dist, float spot, unsigned char alpha)
{
    GXSetChanMatColor((GXChannelID)4, mapColor);
    GXSetChanAmbColor((GXChannelID)4, ambColor);

    if ((enable != 0) && (alpha != 0) && (atten < FLOAT_8032fc80)) {
        Mtx cam;
        Vec eyePos;
        Vec eyeDir;
        Vec transformedPos;
        Vec transformedDir;

        PSMTXCopy(CameraMatrix(), cam);

        eyePos.x = CameraPosX();
        eyePos.y = CameraPosY();
        eyePos.z = CameraPosZ();
        eyeDir.x = CameraDirX();
        eyeDir.y = CameraDirY();
        eyeDir.z = CameraDirZ();

        PSMTXMultVec(cam, &eyePos, &transformedPos);
        GXInitLightPos(&m_mapLightObj, transformedPos.x, transformedPos.y, transformedPos.z);

        PSMTXMultVecSR(cam, &eyeDir, &transformedDir);
        GXInitLightDir(&m_mapLightObj, transformedDir.x, transformedDir.y, transformedDir.z);
        GXInitLightSpot(&m_mapLightObj, spot, (GXSpotFn)4);
        GXInitLightAttnK(&m_mapLightObj, FLOAT_8032fc84 / dist, FLOAT_8032fc88 / atten, FLOAT_8032fc8c / atten);

        s_mapLightAlphaColor.a = alpha;
        GXInitLightColor(&m_mapLightObj, s_mapLightAlphaColor);

        if (m_loadedLightCount >= 8) {
            m_loadedLightCount = 7;
        }

        int lightIdMask = 1 << m_loadedLightCount;
        GXLoadLightObjImm(&m_mapLightObj, (GXLightID)lightIdMask);
        reinterpret_cast<unsigned char*>(&MaterialMan)[519] = 0;
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, m_loadedLightMask, (GXDiffuseFn)2,
                      (GXAttnFn)1);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, lightIdMask, (GXDiffuseFn)0, (GXAttnFn)1);
        m_loadedLightCount += 1;
    } else {
        reinterpret_cast<unsigned char*>(&MaterialMan)[519] = ambColor.a;
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
    float scaled = FLOAT_8032fc7c * alpha;
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
 * PAL Address: 0x800491f8
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
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
        dirX = CameraDirX();
        dirY = CameraDirY();
        dirZ = CameraDirZ();
    } else {
        dirX = dir->x;
        dirY = dir->y;
        dirZ = dir->z;
    }

    GXInitLightColor(&light->m_gxLightObj, color);
    PSMTXCopy(CameraMatrix(), cam);

    lightDir.x = FLOAT_8032fc70 * -dirX;
    lightDir.y = FLOAT_8032fc70 * -dirY;
    lightDir.z = FLOAT_8032fc70 * -dirZ;
    PSMTXMultVec(cam, &lightDir, &lightDir);
    GXInitLightPos(&light->m_gxLightObj, lightDir.x, lightDir.y, lightDir.z);

    lightDir.x = dirX;
    lightDir.y = dirY;
    lightDir.z = dirZ;
    PSMTXMultVecSR(cam, &lightDir, &lightDir);
    GXInitLightDir(&light->m_gxLightObj, lightDir.x, lightDir.y, lightDir.z);

    GXInitLightSpot(&light->m_gxLightObj, FLOAT_8032fc74, (GXSpotFn)4);
    GXInitLightAttnK(&light->m_gxLightObj, FLOAT_8032fc14, FLOAT_8032fc78, FLOAT_8032fc14);
}

/*
 * --INFO--
 * PAL Address: 0x80048fe0
 * PAL Size: 536b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetPosition(CLightPcs::TARGET target, Vec* pos, unsigned long mask)
{
    char* lightPcs = (char*)this;
    *(u32*)(lightPcs + 0xb0) = *(u32*)(lightPcs + 0xac);
    *(u32*)(lightPcs + 0xb4) = 0;

    if (mask == 0) {
        unsigned long chanMask = *(u32*)(lightPcs + 0xb4);
        GXSetNumChans((u8)1);
        if ((int)target != 1) {
            GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, chanMask, (GXDiffuseFn)2, (GXAttnFn)1);
            GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);

            GXSetChanMatColor((GXChannelID)4, kLightDefaultMaterialColor);
        }
        return;
    }

    char* lightSlot = lightPcs + 0xbc;
    *(u32*)(lightPcs + 0xb4) = (1 << *(u32*)(lightPcs + 0xb0)) - 1;

    for (u32 i = 0; i < *(u32*)(lightPcs + 0xac); i++, lightSlot += 0xb0) {
        GXLoadLightObjImm((GXLightObj*)(lightSlot + 0x6c), (GXLightID)(1 << i));
    }

    if (pos != nullptr) {
        char* bumpSlot = lightPcs + 0x63c;
        for (u32 i = 0; i < *(u32*)(lightPcs + 0xb8); i++, bumpSlot += 0xb0) {
            if ((*(u8*)((int)target + (int)bumpSlot + 0x60) != 0) && ((*(u32*)(bumpSlot + 0x34) & mask) != 0) &&
                ((double)PSVECSquareDistance(pos, (Vec*)(bumpSlot + 4)) < (double)*(float*)(bumpSlot + 0xac))) {
                CLight* light = reinterpret_cast<CLight*>(bumpSlot);
                GXInitLightColor(&light->m_gxLightObj, light->m_targetColor[target]);
                GXLoadLightObjImm((GXLightObj*)(bumpSlot + 0x6c), (GXLightID)(1 << *(u32*)(lightPcs + 0xb0)));
                *(u32*)(lightPcs + 0xb4) |= 1 << *(u32*)(lightPcs + 0xb0);
                *(u32*)(lightPcs + 0xb0) += 1;
                if (*(u32*)(lightPcs + 0xb0) >= 8) {
                    break;
                }
            }
        }
    }

    unsigned long chanMask = *(u32*)(lightPcs + 0xb4);
    GXSetNumChans((u8)1);
    if ((int)target != 1) {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, chanMask, (GXDiffuseFn)2, (GXAttnFn)1);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);

        GXSetChanMatColor((GXChannelID)4, kLightDefaultMaterialColor);
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
    char* lightPcs = (char*)this;
    char* bumpSlot = lightPcs + 0x63c;

    *(u32*)(lightPcs + 0xb0) = 0;
    *(u32*)(lightPcs + 0xb4) = 0;

    for (u32 i = 0; i < *(u32*)(lightPcs + 0xb8); i++, bumpSlot += 0xb0) {
        if ((*(u8*)((int)target + (int)bumpSlot + 0x60) != 0) &&
            (((1 << (i & 0x1f)) & *(u32*)((char*)bits + ((i >> 3) & 0x1ffffffc))) != 0))
        {
            CLight* light = reinterpret_cast<CLight*>(bumpSlot);
            GXInitLightColor(&light->m_gxLightObj, light->m_targetColor[target]);
            GXLoadLightObjImm((GXLightObj*)(bumpSlot + 0x6c), (GXLightID)(1 << *(u32*)(lightPcs + 0xb0)));
            *(u32*)(lightPcs + 0xb4) |= 1 << *(u32*)(lightPcs + 0xb0);
            *(u32*)(lightPcs + 0xb0) += 1;

            if (*(u32*)(lightPcs + 0xb0) >= 8) {
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
 * PAL Address: 0x80048cbc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::InsertOctTree(CLightPcs::TARGET target, COctTree& octTree)
{
    octTree.ClearLight();
    CLight* light = m_sceneLights;
    for (u32 i = 0; i < m_sceneLightCount; i++, light++) {
        if (light->m_targetEnable[target] != 0) {
            octTree.InsertLight(i, *reinterpret_cast<Vec*>(&light->m_position), light->m_range, light->m_partMask);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80048644
 * PAL Size: 1656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::CBumpLight::MakeLightMap()
{
    if (m_textureData == 0) {
        return;
    }

    _GXColor chanAmb;
    _GXColor chanMat;
    _GXColor chanAmb2;
    _GXColor chanMat2;
    _GXColor lightColor = kBumpLightMapColor;

    unsigned char u0 = m_bumpShade[0];
    unsigned char u1 = m_bumpShade[1];
    unsigned char u2 = m_bumpShade[2];
    unsigned char u3 = m_bumpShade[3];

    chanAmb.r = u0;
    chanAmb.g = u0;
    chanAmb.b = u0;
    chanAmb.a = u0;
    chanMat.r = u1;
    chanMat.g = u1;
    chanMat.b = u1;
    chanMat.a = u1;
    chanAmb2.r = u2;
    chanAmb2.g = u2;
    chanAmb2.b = u2;
    chanAmb2.a = u2;
    chanMat2.r = u3;
    chanMat2.g = u3;
    chanMat2.b = u3;
    chanMat2.a = u3;

    GXSetChanAmbColor((GXChannelID)0, chanAmb);
    GXSetChanMatColor((GXChannelID)0, chanMat);
    GXSetChanAmbColor((GXChannelID)2, chanAmb2);
    GXSetChanMatColor((GXChannelID)2, chanMat2);

    Vec eyeDir;
    if (m_useViewSpace == 1) {
        Mtx tmp;
        PSMTXIdentity(tmp);
        PSMTXTrans(tmp, FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc34);
        GXLoadPosMtxImm(tmp, 0);
        PSMTXIdentity(tmp);
        GXLoadNrmMtxImm(tmp, 0);

        Vec eye;
        Vec up;
        eye.x = FLOAT_8032fc14;
        eye.y = FLOAT_8032fc14;
        eye.z = FLOAT_8032fc14;
        up.x = FLOAT_8032fc14;
        up.y = FLOAT_8032fc1c;
        up.z = FLOAT_8032fc14;

        Mtx lookAt;
        C_MTXLookAt(lookAt, &eye, &up, reinterpret_cast<Vec*>(&m_direction));

        Vec camPos;
        camPos.x = CameraPosX();
        camPos.y = CameraPosY();
        camPos.z = CameraPosZ();

        Vec lightPos;
        PSVECSubtract(reinterpret_cast<Vec*>(&m_targetPosition), &camPos, &lightPos);
        PSVECNormalize(&lightPos, &lightPos);

        Vec nrm;
        PSVECNormalize(reinterpret_cast<Vec*>(&m_direction), &nrm);

        Vec diff;
        PSVECSubtract(&lightPos, &nrm, &diff);

        float scale = FLOAT_8032fc1c;
        if (m_target == 1) {
            scale = FLOAT_8032fc38;
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
    float dScale = FLOAT_8032fc40;
    float dHalf = FLOAT_8032fc1c;
    static float tParam[4] = {48.0f, 128.0f, 256.0f, 512.0f};
    float* lightScale = tParam;
    float dFactor = FLOAT_8032fc3c;
    float dInv = FLOAT_8032fc44;
    int offset = 0;
    float dW = FLOAT_8032fc60;

    for (int i = 0; i < (int)(unsigned int)m_textureCount; i++) {
        int texBase = (int)m_textureData;
        GXLightObj lightObj;
        GXInitSpecularDir(&lightObj, eyeDir.x, eyeDir.y, eyeDir.z);

        GXInitLightColor(&lightObj, lightColor);

        if (m_target == 1) {
            double d0 = (double)FLOAT_8032fc14;
            double d1 = (double)(m_specularScale * FLOAT_8032fc18);
            GXInitLightAttn(&lightObj, (float)d0, (float)d0, FLOAT_8032fc1c, (float)d1, (float)d0,
                            (float)((double)FLOAT_8032fc1c - d1));
        } else {
            double d0 = (double)FLOAT_8032fc14;
            double d1 = (double)(*lightScale * FLOAT_8032fc18);
            GXInitLightAttn(&lightObj, (float)d0, (float)d0, FLOAT_8032fc1c, (float)d1, (float)d0,
                            (float)((double)FLOAT_8032fc1c - d1));
        }

        GXLoadLightObjImm(&lightObj, (GXLightID)1);

        unsigned int y = 0;
        do {
            unsigned int yBase = y;
            GXBegin((GXPrimitive)0x98, (GXVtxFmt)0, 0x42);

            float x0 = dFactor * (float)U32ToDouble(yBase) * dScale - dHalf;
            float dx0 = x0;
            float x1 = dFactor * (float)U32ToDouble(yBase + 1) * dScale - dHalf;
            float dx1 = x1;

            int inner = 0x21;
            unsigned int x = 0;
            do {
                float z0 = dFactor * (float)U32ToDouble(x) * dScale - dHalf;
                float dz0 = z0;
                float dist0 = dx0 * dx0 + dz0 * dz0;
                if (dHalf <= dist0) {
                    dist0 = FLOAT_8032fc14;
                } else {
                    dist0 = sqrtf(dHalf - dist0);
                }

                GXWGFifo.f32 = x0;
                float dist1 = dx1 * dx1 + dz0 * dz0;
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = dW;
                GXWGFifo.f32 = dx0 / dInv;
                GXWGFifo.f32 = dz0 / dInv;
                GXWGFifo.f32 = dist0;

                if (dHalf <= dist1) {
                    dist1 = FLOAT_8032fc14;
                } else {
                    dist1 = sqrtf(dHalf - dist1);
                }

                GXWGFifo.f32 = x1;
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = dW;
                GXWGFifo.f32 = dx1 / dInv;
                GXWGFifo.f32 = dz0 / dInv;
                GXWGFifo.f32 = dist1;

                inner--;
                x++;
            } while (inner != 0);

            y = yBase + 1;
        } while (y < 0x20);

        GXSetTexCopySrc(0, 0, 0x40, 0x40);
        GXSetTexCopyDst((unsigned short)0x40, (unsigned short)0x40, (GXTexFmt)3, (unsigned char)0);
        GXCopyTex(reinterpret_cast<void*>(texBase + offset), 1);
        GXPixModeSync();

        offset += copySize;
        lightScale++;
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
    GXSetViewport(FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc28, FLOAT_8032fc28, FLOAT_8032fc14, FLOAT_8032fc1c);
    GXSetScissor(0, 0, 0x40, 0x40);
    C_MTXOrtho(projection, FLOAT_8032fc2c, FLOAT_8032fc1c, FLOAT_8032fc2c, FLOAT_8032fc1c, FLOAT_8032fc1c,
               FLOAT_8032fc30);
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

    u32 target = 0;
    char* lightTarget = (char*)this;
    do {
        u32 i = 0;
        char* bump = lightTarget;
        do {
            if (*(u8*)(bump + 0x1cec) != 0) {
                ((CLightPcs::CBumpLight*)(bump + 0x1c3c))->MakeLightMap();
            }
            i++;
            bump += 0x138;
        } while (i < 8);
        target++;
        lightTarget += 0x9c0;
    } while (target < 4);

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
 * PAL Address: 0x80047ee0
 * PAL Size: 1180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetBumpTexMatirx(float (*mat)[4], CLightPcs::CBumpLight* bump, Vec* vec, unsigned char mode)
{
    Mtx cam;
    PSMTXCopy(CameraMatrix(), cam);
    Mtx out;

    if (mode != 0) {
        Vec pos;
        pos.x = mat[0][3];
        pos.y = mat[1][3];
        pos.z = mat[2][3];
        PSMTXMultVec(cam, &pos, &pos);

        if (mode == 1) {
            cam[0][1] = FLOAT_8032fc14;
            cam[0][0] = FLOAT_8032fc1c;
            cam[0][2] = FLOAT_8032fc14;
            cam[1][0] = FLOAT_8032fc14;
            cam[1][1] = FLOAT_8032fc1c;
            cam[1][2] = FLOAT_8032fc14;
            cam[2][0] = FLOAT_8032fc14;
            cam[2][1] = FLOAT_8032fc14;
            cam[2][2] = FLOAT_8032fc1c;
        } else if (mode == 2) {
            Vec yAxis;
            yAxis.x = cam[0][1];
            yAxis.y = cam[1][1];
            yAxis.z = cam[2][1];
            PSVECNormalize(&yAxis, &yAxis);
            Vec xAxis;
            xAxis.y = -yAxis.x;
            cam[0][1] = yAxis.x;
            cam[1][1] = yAxis.y;
            cam[2][1] = yAxis.z;
            xAxis.x = yAxis.y;
            xAxis.z = FLOAT_8032fc14;
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
        if (vec == nullptr ||
            ((FLOAT_8032fc14 == vec->x) && (FLOAT_8032fc14 == vec->y) && (FLOAT_8032fc14 == vec->z))) {
            PSMTXConcat(cam, mat, out);
        } else {
            Mtx tmp;
            PSMTXCopy(mat, tmp);
            Vec camPos;
            camPos.x = CameraPosX();
            camPos.y = CameraPosY();
            camPos.z = CameraPosZ();
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
        }
    }

    GXLoadPosMtxImm(out, 0);

    Mtx nrm;
    nrm[0][0] = out[0][0];
    nrm[1][0] = out[1][0];
    nrm[2][0] = out[2][0];
    nrm[0][1] = out[0][1];
    nrm[1][1] = out[1][1];
    nrm[2][1] = out[2][1];
    nrm[0][2] = out[0][2];
    nrm[1][2] = out[1][2];
    nrm[2][2] = out[2][2];
    nrm[0][3] = FLOAT_8032fc14;
    nrm[1][3] = FLOAT_8032fc14;
    nrm[2][3] = FLOAT_8032fc14;
    GXLoadNrmMtxImm(nrm, 0);

    if ((bump != nullptr) && (bump->m_hasTexture != 0)) {
        Mtx* bumpMat0 = &m_bumpTexMtx0;
        Mtx* bumpMat1 = &m_bumpTexMtx1;
        Mtx texMtx;

        if (bump->m_useViewSpace == 1) {
            PSMTXTrans(texMtx, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(texMtx, nrm, *bumpMat0);
            PSMTXScale(texMtx, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, texMtx, *bumpMat0);
            Mtx posOnly;
            PSMTXCopy(out, posOnly);
            posOnly[0][3] = FLOAT_8032fc14;
            posOnly[1][3] = FLOAT_8032fc14;
            posOnly[2][3] = FLOAT_8032fc14;
            PSMTXConcat(posOnly, texMtx, *bumpMat1);
        } else {
            PSMTXIdentity(nrm);
            PSMTXTrans(texMtx, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(texMtx, nrm, *bumpMat0);
            PSMTXScale(texMtx, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, texMtx, *bumpMat0);

            double camX = (double)CameraPosX();
            double camZ = (double)CameraPosZ();
            PSMTXIdentity(reinterpret_cast<float(*)[4]>(m_bumpTexScratch));
            float* scratch = m_bumpTexScratch;

            float f0 = FLOAT_8032fc24;
            float f1 = FLOAT_8032fc14;
            scratch[0] = FLOAT_8032fc24;
            float f2 = FLOAT_8032fc18;
            scratch[6] = f0;
            float f3 = FLOAT_8032fc20;
            scratch[10] = f1;
            scratch[5] = f1;
            scratch[9] = f1;
            scratch[3] =
                -(f0 * (float)(camX + (double)bump->m_offsetX) - f2);
            scratch[7] =
                -(f0 * (float)(camZ + (double)bump->m_offsetZ) - f2);
            scratch[11] = f1;
            scratch[16] = f3;
            scratch[12] = f3;
            scratch[17] = f1;
            scratch[15] = f1;
            scratch[14] = f1;
            scratch[13] = f1;
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
    float radius = FLOAT_8032fc1c;

    m_radius = radius;
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
    float radius = FLOAT_8032fc1c;
    float f2 = FLOAT_8032fc14;

    m_radius = radius;
    float f1 = FLOAT_8032fc10;
    m_offsetZ = f2;
    m_offsetX = f2;
    m_attenFalloff = f1;
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
