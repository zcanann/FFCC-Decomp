#include "ffcc/p_light.h"

#include "ffcc/graphic.h"
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

#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"

extern "C" void create__9CLightPcsFv(CLightPcs*);
extern "C" void destroy__9CLightPcsFv(CLightPcs*);
extern "C" void calc__9CLightPcsFv(CLightPcs*);
extern "C" void draw__9CLightPcsFv(CLightPcs*);
extern "C" void MakeLightMap__9CLightPcsFv(CLightPcs*);
extern "C" void __ct__Q29CLightPcs6CLightFv(void*);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* Free__7CMemoryFPv(CMemory*, void*);
extern char s_CLightPcs_801D7C70[];
extern unsigned int DAT_8032fc0c;
extern unsigned int DAT_8032fc08;
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
extern float FLOAT_8032fc70;
extern float FLOAT_8032fc74;
extern float FLOAT_8032fc78;
extern float FLOAT_8032fc7c;
extern float FLOAT_8032fc80;
extern float FLOAT_8032fc84;
extern float FLOAT_8032fc90;
extern float FLOAT_8032fc88;
extern float FLOAT_8032fc8c;
extern float FLOAT_8032fc94;
extern float FLOAT_8032ed10;
extern double DOUBLE_8032fc48;
extern double DOUBLE_8032fc50;
extern double DOUBLE_8032fc58;
extern double DOUBLE_8032fc68;
extern float DAT_801ea430;
extern unsigned int DAT_8032e620;

extern "C" void setViewport__11CGraphicPcsFv(void*);

static inline float CameraPosX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE0); }
static inline float CameraPosY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE4); }
static inline float CameraPosZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE8); }
static inline float CameraDirX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xEC); }
static inline float CameraDirY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF0); }
static inline float CameraDirZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF4); }
static inline MtxPtr CameraMatrix() { return reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4); }

unsigned int m_table_desc0__9CLightPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CLightPcsFv)};
unsigned int m_table_desc1__9CLightPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CLightPcsFv)};
unsigned int m_table_desc2__9CLightPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CLightPcsFv)};
unsigned int m_table_desc3__9CLightPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CLightPcsFv)};
unsigned int m_table_desc4__9CLightPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(MakeLightMap__9CLightPcsFv)};
unsigned int m_table__9CLightPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(s_CLightPcs_801D7C70), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1C, 0, 0, 0, 0, 0x2A, 0, 0, 0,
    0, 0x2D, 1
};

CLightPcs LightPcs;
static char s_p_light_cpp[] = "p_light.cpp";

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
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CLightPcs()
{
    __construct_array(m_diffuseLights, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, sizeof(CLight), 8);
    __construct_array(m_sceneLights, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, sizeof(CLight), 0x20);
    __construct_array(m_bumpLights, (ConstructorDestructor)__ct__Q29CLightPcs10CBumpLightFv, 0, sizeof(CBumpLight), 0x20);

    unsigned int* table = m_table__9CLightPcs;

    table[0x004 / 4] = m_table_desc0__9CLightPcs[0];
    table[0x008 / 4] = m_table_desc0__9CLightPcs[1];
    table[0x00C / 4] = m_table_desc0__9CLightPcs[2];
    table[0x010 / 4] = m_table_desc1__9CLightPcs[0];
    table[0x014 / 4] = m_table_desc1__9CLightPcs[1];
    table[0x018 / 4] = m_table_desc1__9CLightPcs[2];
    table[0x01C / 4] = m_table_desc2__9CLightPcs[0];
    table[0x020 / 4] = m_table_desc2__9CLightPcs[1];
    table[0x024 / 4] = m_table_desc2__9CLightPcs[2];
    table[0x030 / 4] = m_table_desc3__9CLightPcs[0];
    table[0x034 / 4] = m_table_desc3__9CLightPcs[1];
    table[0x038 / 4] = m_table_desc3__9CLightPcs[2];
    table[0x044 / 4] = m_table_desc4__9CLightPcs[0];
    table[0x048 / 4] = m_table_desc4__9CLightPcs[1];
    table[0x04C / 4] = m_table_desc4__9CLightPcs[2];
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
    float fVar1;
    float fVar2;
    unsigned char bVar3;
    unsigned int uVar4;
    unsigned int uVar5;

    m_mapLightColor[0].r = 0x3F;
    uVar4 = __cntlzw(0);
    m_mapLightColor[0].g = 0x3F;
    fVar1 = FLOAT_8032fc14;
    m_mapLightColor[0].b = 0x3F;
    fVar2 = FLOAT_8032fc2c;
    uVar5 = __cntlzw(1);
    bVar3 = static_cast<unsigned char>(-((unsigned char)(uVar4 >> 5) & 1)) & 0x3F;
    m_mapLightColor[0].a = 0xFF;
    m_mapLightColor[1].r = bVar3;
    uVar4 = __cntlzw(2);
    m_mapLightColor[1].g = bVar3;
    m_mapLightColor[1].b = bVar3;
    bVar3 = static_cast<unsigned char>(-((unsigned char)(uVar5 >> 5) & 1)) & 0x3F;
    m_mapLightColor[1].a = 0xFF;
    m_mapLightParams[0] = fVar1;
    m_mapLightParams[1] = fVar1;
    m_mapLightParams[2] = fVar2;
    m_mapLightColor[2].r = bVar3;
    m_mapLightColor[2].g = bVar3;
    m_mapLightColor[2].b = bVar3;
    bVar3 = static_cast<unsigned char>(-((unsigned char)(uVar4 >> 5) & 1)) & 0x3F;
    m_mapLightColor[2].a = 0xFF;
    m_mapLightParams[3] = fVar1;
    m_mapLightParams[4] = fVar1;
    m_mapLightParams[5] = fVar2;
    m_mapLightColor[3].r = bVar3;
    m_mapLightColor[3].g = bVar3;
    m_mapLightColor[3].b = bVar3;
    m_mapLightColor[3].a = 0xFF;
    m_mapLightParams[6] = fVar1;
    m_mapLightParams[7] = fVar1;
    m_mapLightParams[8] = fVar2;
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
    return (int)m_table__9CLightPcs + (index * 0x15c);
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
    unsigned char* light = reinterpret_cast<unsigned char*>(this);
    for (unsigned int i = 0; i < 8; ++i) {
        void** ptr = reinterpret_cast<void**>(light + 0x26b0);
        if (*ptr != 0) {
            Free__7CMemoryFPv(&Memory, *ptr);
            *ptr = 0;
            light[0x26ac] = 0;
            light[0x26ad] = 0;
        }
        light += 0x138;
    }

    light = reinterpret_cast<unsigned char*>(this);
    for (unsigned int i = 0; i < 8; ++i) {
        void** ptr = reinterpret_cast<void**>(light + 0x1cf0);
        if (*ptr != 0) {
            Free__7CMemoryFPv(&Memory, *ptr);
            *ptr = 0;
            light[0x1cec] = 0;
            light[0x1ced] = 0;
        }
        light += 0x138;
    }
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
    char* light = reinterpret_cast<char*>(this) + (static_cast<int>(target) * 0x9c0);
    u32 i = 0;

    do {
        void* texture = *reinterpret_cast<void**>(light + 0x1cf0);
        if (texture != 0) {
            bool hasTexture = texture != 0;
            if (hasTexture) {
                Free__7CMemoryFPv(&Memory, texture);
                *reinterpret_cast<void**>(light + 0x1cf0) = 0;
            }

            light[0x1cec] = 0;
            light[0x1ced] = 0;
        }

        i++;
        light += 0x138;
    } while (i < 8);
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
    for (u32 i = 0; i < m_sceneLightCount; i++) {
        CLight* light = &m_sceneLights[i];
        if (light->m_specularMode == 0) {
            PSMTXMultVec(mtx, reinterpret_cast<Vec*>(&light->m_position), &vec);
            GXInitLightPos(&light->m_gxLightObj, vec.x, vec.y, vec.z);

            if (light->m_directionMode == 0) {
                PSMTXMultVecSR(mtx, reinterpret_cast<Vec*>(&light->m_direction), &vec);
                GXInitLightDir(&light->m_gxLightObj, vec.x, vec.y, vec.z);
            } else {
                GXInitLightDir(&light->m_gxLightObj, light->m_direction.x, light->m_direction.y, light->m_direction.z);
            }

            float cutoff = FLOAT_8032fc74;
            if (light->m_type == 1) {
                cutoff = FLOAT_8032fc94 * light->m_spotScale;
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
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Clear()
{
	// TODO
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
    CLight sceneLight = *light;
    float attenRadius = sceneLight.m_attenRadius;
    u8* targetEnable = reinterpret_cast<u8*>(&sceneLight.m_targetEnableMask);

    if (FLOAT_8032fc10 <= sceneLight.m_attenFalloff) {
        sceneLight.m_attenFalloff = attenRadius;
    }

    if (attenRadius < FLOAT_8032fc14) {
        attenRadius = -attenRadius;
    }
    sceneLight.m_range = attenRadius * FLOAT_8032fc18 * sceneLight.m_radius;

    sceneLight.m_targetEnableMask = 0x01010101;
    if (*(u32*)&sceneLight.m_targetColor[0] == 0) {
        targetEnable[0] = 0;
    }
    if (*(u32*)&sceneLight.m_targetColor[1] == 0) {
        targetEnable[1] = 0;
    }
    if (*(u32*)&sceneLight.m_targetColor[2] == 0) {
        targetEnable[2] = 0;
    }

    sceneLight.m_unkAC = sceneLight.m_attenRadius * sceneLight.m_attenRadius;
    m_sceneLights[m_sceneLightCount] = sceneLight;
    m_sceneLightCount += 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::GetFreeBumpLight(CLightPcs::TARGET)
{
	// TODO
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
    float threshold = FLOAT_8032fc10;
    int base = (int)this + (int)target * 0x9c0;
    int i = 0;
    int remaining = 8;
    int entry = base;
    u32* slot = 0;

    do {
        if (*(char*)(entry + 0x1cec) == '\0') {
            slot = (u32*)(base + i * 0x138 + 0x1c3c);
            break;
        }
        entry += 0x138;
        i += 1;
        remaining -= 1;
    } while (remaining != 0);

    if (slot == 0) {
        if (System.m_execParam != 0) {
            System.Printf((char*)"BUMP LIGHT FULL\n");
        }
        return 0;
    }

    u32* src = (u32*)srcLight;
    slot[0] = src[0];
    slot[1] = src[1];
    slot[2] = src[2];
    slot[3] = src[3];
    slot[4] = src[4];
    slot[5] = src[5];
    slot[6] = src[6];
    slot[7] = src[7];
    slot[8] = src[8];
    slot[9] = src[9];
    slot[10] = src[10];
    slot[11] = src[11];
    slot[12] = src[12];
    slot[13] = src[13];
    slot[14] = src[14];
    slot[15] = src[15];
    slot[16] = src[16];
    slot[17] = src[17];
    slot[18] = src[18];
    *(u8*)(slot + 19) = *(u8*)(src + 19);
    *(u8*)((char*)slot + 0x4d) = *(u8*)((char*)src + 0x4d);
    *(u8*)((char*)slot + 0x4e) = *(u8*)((char*)src + 0x4e);
    *(u8*)((char*)slot + 0x4f) = *(u8*)((char*)src + 0x4f);
    slot[20] = src[20];
    slot[21] = src[21];
    slot[22] = src[22];
    slot[23] = src[23];
    slot[24] = src[24];
    slot[25] = src[25];
    slot[26] = src[26];
    slot[27] = src[27];
    slot[28] = src[28];
    slot[29] = src[29];
    slot[30] = src[30];
    slot[31] = src[31];
    slot[32] = src[32];
    slot[33] = src[33];
    slot[34] = src[34];
    slot[35] = src[35];
    slot[36] = src[36];
    slot[37] = src[37];
    slot[38] = src[38];
    slot[39] = src[39];
    slot[40] = src[40];
    slot[41] = src[41];
    slot[42] = src[42];
    slot[43] = src[43];

    if (threshold <= reinterpret_cast<float*>(slot)[8]) {
        slot[8] = slot[7];
    }

    threshold = FLOAT_8032fc14;
    reinterpret_cast<float*>(slot)[43] = reinterpret_cast<float*>(slot)[7] * reinterpret_cast<float*>(slot)[7];
    slot[9] = slot[7];
    if (reinterpret_cast<float*>(slot)[9] < threshold) {
        reinterpret_cast<float*>(slot)[9] = -reinterpret_cast<float*>(slot)[9];
    }
    reinterpret_cast<float*>(slot)[9] =
        reinterpret_cast<float*>(slot)[9] * FLOAT_8032fc18 * reinterpret_cast<float*>(slot)[10];

    *(u8*)((char*)slot + 99) = 1;
    *(u8*)((char*)slot + 0x62) = 1;
    *(u8*)((char*)slot + 0x61) = 1;
    *(u8*)(slot + 24) = 1;

    if (slot[20] == 0) {
        *(u8*)(slot + 24) = 0;
    }
    if (slot[21] == 0) {
        *(u8*)((char*)slot + 0x61) = 0;
    }
    if (slot[22] == 0) {
        *(u8*)((char*)slot + 0x62) = 0;
    }

    *(char*)((char*)slot + 0xb2) = (char)target;
    *(u8*)(slot + 44) = 1;
    *(char*)((char*)slot + 0xb3) = (char)count;

    int texSize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    slot[45] = (u32)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, texSize * count, stage, s_p_light_cpp, 0x13b, 0);

    int texOffset = 0;
    u32* texObj = slot;
    for (i = 0; i < count; i++) {
        GXInitTexObj((GXTexObj*)(texObj + 46), (void*)(slot[45] + texOffset), (u16)0x40, (u16)0x40, (GXTexFmt)3,
                     (GXTexWrapMode)0, (GXTexWrapMode)0, (u8)0);
        texOffset += texSize;
        texObj += 8;
    }

    return (CLightPcs::CBumpLight*)slot;
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
    char* self = (char*)this;
    GXSetChanMatColor((GXChannelID)4, mapColor);
    GXSetChanAmbColor((GXChannelID)4, ambColor);

    if ((enable == 0) || (alpha == 0) || (FLOAT_8032fc80 <= atten)) {
        reinterpret_cast<unsigned char*>(&MaterialMan)[519] = ambColor.a;
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, *(u32*)(self + 0xb4), (GXDiffuseFn)2,
                      (GXAttnFn)1);
        if (ambColor.a == 0xFF) {
            GXSetChanCtrl((GXChannelID)2, (u8)0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        } else {
            GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        }
        return;
    }

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
    GXInitLightPos((GXLightObj*)(self + 0x4370), transformedPos.x, transformedPos.y, transformedPos.z);

    PSMTXMultVecSR(cam, &eyeDir, &transformedDir);
    GXInitLightDir((GXLightObj*)(self + 0x4370), transformedDir.x, transformedDir.y, transformedDir.z);
    GXInitLightSpot((GXLightObj*)(self + 0x4370), spot, (GXSpotFn)4);
    GXInitLightAttnK((GXLightObj*)(self + 0x4370), FLOAT_8032fc84 / dist, FLOAT_8032fc88 / atten, FLOAT_8032fc8c / atten);

    DAT_8032e620 = (DAT_8032e620 & 0xFFFFFF00) | alpha;
    _GXColor lightColor;
    *(u32*)&lightColor = DAT_8032e620;
    GXInitLightColor((GXLightObj*)(self + 0x4370), lightColor);

    if (*(u32*)(self + 0xb0) > 7) {
        *(u32*)(self + 0xb0) = 7;
    }

    int lightIdMask = 1 << *(u32*)(self + 0xb0);
    GXLoadLightObjImm((GXLightObj*)(self + 0x4370), (GXLightID)lightIdMask);
    reinterpret_cast<unsigned char*>(&MaterialMan)[519] = 0;
    GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, *(u32*)(self + 0xb4), (GXDiffuseFn)2,
                  (GXAttnFn)1);
    GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, lightIdMask, (GXDiffuseFn)0, (GXAttnFn)1);
    *(u32*)(self + 0xb0) += 1;
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
    _GXColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = (u8)(int)((double)FLOAT_8032fc7c * (double)alpha);
    GXSetChanAmbColor((GXChannelID)2, color);
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
    unsigned int light_mask;

    if (param_1 == 0) {
        light_mask = 0;
    } else {
        light_mask = m_loadedLightMask;
    }

    GXSetChanCtrl((GXChannelID)0, (u8)(((unsigned int)(-param_1 | param_1)) >> 0x1f), (GXColorSrc)0,
                  (GXColorSrc)(__cntlzw((unsigned int)param_2) >> 5), light_mask, (GXDiffuseFn)2,
                  (GXAttnFn)1);
    GXSetChanCtrl((GXChannelID)2, (u8)(((unsigned int)(-param_1 | param_1)) >> 0x1f), (GXColorSrc)0,
                  (GXColorSrc)(__cntlzw((unsigned int)param_2) >> 5), 0, (GXDiffuseFn)0,
                  (GXAttnFn)2);
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
    float dirX = CameraDirX();
    float dirY = CameraDirY();
    float dirZ = CameraDirZ();

    if (mode == 0) {
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

            _GXColor chanMat;
            *(u32*)&chanMat = DAT_8032fc08;
            GXSetChanMatColor((GXChannelID)4, chanMat);
        }
        return;
    }

    char* lightSlot = lightPcs + 0xbc;
    *(u32*)(lightPcs + 0xb4) = (1 << *(u32*)(lightPcs + 0xb0)) - 1;

    for (u32 i = 0; i < *(u32*)(lightPcs + 0xac); i++) {
        GXLoadLightObjImm((GXLightObj*)(lightSlot + 0x6c), (GXLightID)(1 << i));
        lightSlot += 0xb0;
    }

    if (pos != nullptr) {
        char* bumpSlot = lightPcs + 0x63c;
        for (u32 i = 0; i < *(u32*)(lightPcs + 0xb8); i++) {
            if ((*(char*)(bumpSlot + 0x60 + (int)target) != '\0') && ((*(u32*)(bumpSlot + 0x34) & mask) != 0) &&
                ((double)PSVECSquareDistance(pos, (Vec*)(bumpSlot + 4)) < (double)*(float*)(bumpSlot + 0xac))) {
                _GXColor lightColor;
                *(u32*)&lightColor = *(u32*)(bumpSlot + 0x50 + ((int)target * 4));
                GXInitLightColor((GXLightObj*)(bumpSlot + 0x6c), lightColor);
                GXLoadLightObjImm((GXLightObj*)(bumpSlot + 0x6c), (GXLightID)(1 << *(u32*)(lightPcs + 0xb0)));
                *(u32*)(lightPcs + 0xb4) |= 1 << *(u32*)(lightPcs + 0xb0);
                *(u32*)(lightPcs + 0xb0) += 1;
                if (*(u32*)(lightPcs + 0xb0) > 7) {
                    break;
                }
            }
            bumpSlot += 0xb0;
        }
    }

    unsigned long chanMask = *(u32*)(lightPcs + 0xb4);
    GXSetNumChans((u8)1);
    if ((int)target != 1) {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, chanMask, (GXDiffuseFn)2, (GXAttnFn)1);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);

        _GXColor chanMat;
        *(u32*)&chanMat = DAT_8032fc08;
        GXSetChanMatColor((GXChannelID)4, chanMat);
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
    u32 i;
    _GXColor lightColor;

    *(u32*)(lightPcs + 0xb0) = 0;
    *(u32*)(lightPcs + 0xb4) = 0;
    i = 0;

    do {
        if (*(u32*)(lightPcs + 0xb8) <= i) {
            return;
        }

        if ((*(char*)((int)target + (int)bumpSlot + 0x60) != '\0') &&
            (((1 << (i & 0x1f)) & *(u32*)((char*)bits + ((i >> 3) & 0x1ffffffc))) != 0))
        {
            *(u32*)&lightColor = *(u32*)(bumpSlot + 0x50 + ((int)target * 4));
            GXInitLightColor((GXLightObj*)(bumpSlot + 0x6c), lightColor);
            GXLoadLightObjImm((GXLightObj*)(bumpSlot + 0x6c), (GXLightID)(1 << *(u32*)(lightPcs + 0xb0)));
            *(u32*)(lightPcs + 0xb4) |= 1 << *(u32*)(lightPcs + 0xb0);
            *(u32*)(lightPcs + 0xb0) += 1;

            if (*(u32*)(lightPcs + 0xb0) > 7) {
                return;
            }
        }

        i += 1;
        bumpSlot += 0xb0;
    } while (true);
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
    char* lightPcs = (char*)this;

    if (mode == 0) {
        GXSetNumChans((u8)1);
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        GXSetChanCtrl((GXChannelID)2, (u8)1, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
        return;
    }

    char* bumpSlot = lightPcs + 0x63c;
    *(u32*)(lightPcs + 0xb0) = 0;
    *(u32*)(lightPcs + 0xb4) = 0;
    GXAttnFn attnFn = (GXAttnFn)1;

    for (u32 i = 0; i < *(u32*)(lightPcs + 0xb8); i++) {
        if ((*(char*)(bumpSlot + 0x60 + (int)target) != '\0') && (*(u32*)(bumpSlot + 0x64) == (u32)part)) {
            _GXColor lightColor;
            *(u32*)&lightColor = *(u32*)(bumpSlot + 0x50 + ((int)target * 4));
            GXInitLightColor((GXLightObj*)(bumpSlot + 0x6c), lightColor);
            GXLoadLightObjImm((GXLightObj*)(bumpSlot + 0x6c), (GXLightID)(1 << *(u32*)(lightPcs + 0xb0)));

            if (*(char*)(bumpSlot + 0x4f) != '\0') {
                attnFn = (GXAttnFn)0;
            }

            *(u32*)(lightPcs + 0xb4) |= 1 << *(u32*)(lightPcs + 0xb0);
            *(u32*)(lightPcs + 0xb0) += 1;
            if (*(u32*)(lightPcs + 0xb0) > 7) {
                break;
            }
        }
        bumpSlot += 0xb0;
    }

    GXSetNumChans((u8)1);
    if (mode == 1) {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)0, (GXColorSrc)1, *(u32*)(lightPcs + 0xb4), (GXDiffuseFn)2, attnFn);
    } else {
        GXSetChanCtrl((GXChannelID)0, (u8)1, (GXColorSrc)1, (GXColorSrc)0, *(u32*)(lightPcs + 0xb4), (GXDiffuseFn)2, attnFn);
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
    for (u32 i = 0; i < m_sceneLightCount; i++) {
        CLight* light = &m_sceneLights[i];
        if (((light->m_targetEnableMask >> (target * 8)) & 0xFF) != 0) {
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
    unsigned int packedColor = DAT_8032fc0c;
    double dScale = (double)FLOAT_8032fc40;
    double dHalf = (double)FLOAT_8032fc1c;
    float* lightScale = &DAT_801ea430;
    double dFactor = (double)FLOAT_8032fc3c;
    double dInv = (double)FLOAT_8032fc44;
    int offset = 0;
    double dW = (double)FLOAT_8032fc60;

    for (int i = 0; i < (int)(unsigned int)m_textureCount; i++) {
        int texBase = (int)m_textureData;
        GXLightObj lightObj;
        GXInitSpecularDir(&lightObj, eyeDir.x, eyeDir.y, eyeDir.z);

        _GXColor lightColor;
        *reinterpret_cast<unsigned int*>(&lightColor) = packedColor;
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

            float x0 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(yBase)) * dScale - dHalf));
            double dx0 = (double)x0;
            float x1 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(yBase + 1)) * dScale - dHalf));
            double dx1 = (double)x1;

            int inner = 0x21;
            unsigned int x = 0;
            do {
                float z0 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(x)) * dScale - dHalf));
                double dz0 = (double)z0;
                double dist0 = (double)(float)(dx0 * dx0 + (double)(float)(dz0 * dz0));
                if (dHalf <= dist0) {
                    dist0 = (double)FLOAT_8032fc14;
                } else {
                    float diff = (float)(dHalf - dist0);
                    dist0 = (double)diff;
                    if (dist0 <= (double)FLOAT_8032fc14) {
                        if (DOUBLE_8032fc58 <= dist0) {
                            unsigned int flags = (unsigned int)diff & 0x7f800000;
                            int classify;
                            if (flags == 0x7f800000) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 2;
                                } else {
                                    classify = 1;
                                }
                            } else if ((flags < 0x7f800000) && (flags == 0)) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 3;
                                } else {
                                    classify = 5;
                                }
                            } else {
                                classify = 4;
                            }
                            if (classify == 1) {
                                dist0 = NAN;
                            }
                        } else {
                            dist0 = NAN;
                        }
                    } else {
                        double inv = 1.0 / sqrt(dist0);
                        inv = DOUBLE_8032fc48 * inv * -(dist0 * inv * inv - DOUBLE_8032fc50);
                        inv = DOUBLE_8032fc48 * inv * -(dist0 * inv * inv - DOUBLE_8032fc50);
                        dist0 = (double)(float)(dist0 * DOUBLE_8032fc48 * inv *
                                               -(dist0 * inv * inv - DOUBLE_8032fc50));
                    }
                }

                GXWGFifo.f32 = x0;
                double dist1 = (double)(float)(dx1 * dx1 + (double)(float)(dz0 * dz0));
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = (float)dW;
                GXWGFifo.f32 = (float)(dx0 / dInv);
                GXWGFifo.f32 = (float)(dz0 / dInv);
                GXWGFifo.f32 = (float)dist0;

                if (dHalf <= dist1) {
                    dist1 = (double)FLOAT_8032fc14;
                } else {
                    float diff = (float)(dHalf - dist1);
                    dist1 = (double)diff;
                    if (dist1 <= (double)FLOAT_8032fc14) {
                        if (DOUBLE_8032fc58 <= dist1) {
                            unsigned int flags = (unsigned int)diff & 0x7f800000;
                            int classify;
                            if (flags == 0x7f800000) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 2;
                                } else {
                                    classify = 1;
                                }
                            } else if ((flags < 0x7f800000) && (flags == 0)) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 3;
                                } else {
                                    classify = 5;
                                }
                            } else {
                                classify = 4;
                            }
                            if (classify == 1) {
                                dist1 = NAN;
                            }
                        } else {
                            dist1 = NAN;
                        }
                    } else {
                        double inv = 1.0 / sqrt(dist1);
                        inv = DOUBLE_8032fc48 * inv * -(dist1 * inv * inv - DOUBLE_8032fc50);
                        inv = DOUBLE_8032fc48 * inv * -(dist1 * inv * inv - DOUBLE_8032fc50);
                        dist1 = (double)(float)(dist1 * DOUBLE_8032fc48 * inv *
                                               -(dist1 * inv * inv - DOUBLE_8032fc50));
                    }
                }

                GXWGFifo.f32 = x1;
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = (float)dW;
                GXWGFifo.f32 = (float)(dx1 / dInv);
                GXWGFifo.f32 = (float)(dz0 / dInv);
                GXWGFifo.f32 = (float)dist1;

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
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_SET);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
    GXSetColorUpdate(GX_TRUE);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetViewport(FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc28, FLOAT_8032fc28, FLOAT_8032fc14, FLOAT_8032fc1c);
    GXSetScissor(0, 0, 0x40, 0x40);
    C_MTXOrtho(projection, FLOAT_8032fc2c, FLOAT_8032fc1c, FLOAT_8032fc2c, FLOAT_8032fc1c, FLOAT_8032fc1c,
               FLOAT_8032fc30);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_NONE, GX_AF_SPEC);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
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

    char* lightTarget = (char*)this;
    for (u32 target = 0; target < 4; target++, lightTarget += 0x9c0) {
        char* bump = lightTarget;
        for (u32 i = 0; i < 8; i++, bump += 0x138) {
            if (*(u8*)(bump + 0x1cec) != 0) {
                ((CLightPcs::CBumpLight*)(bump + 0x1c3c))->MakeLightMap();
            }
        }
    }

    Graphic.SetStdPixelFmt();
    setViewport__11CGraphicPcsFv(&GraphicsPcs);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetTexCopySrc(0, 0, 0x40, 0x40);
    GXSetTexCopyDst((u16)0x40, (u16)0x40, GX_TF_I8, GX_FALSE);
    GXCopyTex(gRenderScratchTextureBuffer, GX_TRUE);
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
    Mtx* input = (Mtx*)mat;
    float* scale = (float*)vec;

    Mtx cam;
    PSMTXCopy(CameraMatrix(), cam);
    Mtx* out = &m_bumpTexMtx1;

    if (mode == 0) {
        if (scale == nullptr ||
            ((FLOAT_8032fc14 == scale[0]) && (FLOAT_8032fc14 == scale[1]) && (FLOAT_8032fc14 == scale[2]))) {
            PSMTXConcat(cam, *input, *out);
        } else {
            Mtx tmp;
            PSMTXCopy(*input, tmp);
            Vec camPos;
            camPos.x = CameraPosX();
            camPos.y = CameraPosY();
            camPos.z = CameraPosZ();
            Vec objPos;
            objPos.x = tmp[0][3];
            objPos.y = tmp[1][3];
            objPos.z = tmp[2][3];
            PSVECSubtract(&camPos, &objPos, &camPos);
            camPos.x = camPos.x * scale[0];
            camPos.y = camPos.y * scale[1];
            camPos.z = camPos.z * scale[2];
            PSMTXMultVecSR(cam, &camPos, &camPos);
            PSMTXConcat(cam, tmp, *out);
            (*out)[0][3] += camPos.x;
            (*out)[1][3] += camPos.y;
            (*out)[2][3] += camPos.z;
        }
    } else {
        Vec pos;
        pos.x = (*input)[0][3];
        pos.y = (*input)[1][3];
        pos.z = (*input)[2][3];
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

        PSMTXConcat(cam, *input, *out);
        (*out)[0][3] = pos.x;
        (*out)[1][3] = pos.y;
        (*out)[2][3] = pos.z;
    }

    GXLoadPosMtxImm(*out, 0);

    Mtx nrm;
    nrm[0][0] = (*out)[0][0];
    nrm[1][0] = (*out)[1][0];
    nrm[2][0] = (*out)[2][0];
    nrm[0][1] = (*out)[0][1];
    nrm[1][1] = (*out)[1][1];
    nrm[2][1] = (*out)[2][1];
    nrm[0][2] = (*out)[0][2];
    nrm[1][2] = (*out)[1][2];
    nrm[2][2] = (*out)[2][2];
    nrm[0][3] = FLOAT_8032fc14;
    nrm[1][3] = FLOAT_8032fc14;
    nrm[2][3] = FLOAT_8032fc14;
    GXLoadNrmMtxImm(nrm, 0);

    if ((bump != nullptr) && (bump->m_hasTexture != 0)) {
        Mtx* bumpMat0 = &m_bumpTexMtx0;
        Mtx* bumpMat1 = &m_bumpTexMtx1;

        if (bump->m_useViewSpace == 1) {
            Mtx tmp;
            PSMTXTrans(tmp, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(tmp, nrm, *bumpMat0);
            PSMTXScale(tmp, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, tmp, *bumpMat0);
            Mtx posOnly;
            PSMTXCopy(*out, posOnly);
            posOnly[0][3] = FLOAT_8032fc14;
            posOnly[1][3] = FLOAT_8032fc14;
            posOnly[2][3] = FLOAT_8032fc14;
            PSMTXConcat(posOnly, tmp, *bumpMat1);
        } else {
            Mtx tmp;
            Mtx ident;
            PSMTXIdentity(ident);
            PSMTXTrans(tmp, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(tmp, ident, *bumpMat0);
            PSMTXScale(tmp, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, tmp, *bumpMat0);

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
 * PAL Address: 0x80047e00
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CLightPcs::CLight::CLight()
{
    float f2 = FLOAT_8032fc14;

    m_radius = FLOAT_8032fc1c;
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
    m_radius = FLOAT_8032fc1c;
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
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::CLight::Set(CLightPcs::CLight*)
{
	// TODO
}
