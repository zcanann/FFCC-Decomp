#include "ffcc/p_light.h"

#include "ffcc/graphic.h"

#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>
#include <math.h>
#include <string.h>

#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"

extern "C" void __ct__Q29CLightPcs6CLightFv(void*);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* Free__7CMemoryFPv(CMemory*, void*);
extern "C" int __cntlzw(unsigned int);

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801EA460;

extern unsigned int lbl_801EA298[];
extern unsigned int lbl_801EA2A4[];
extern unsigned int lbl_801EA2B0[];
extern unsigned int lbl_801EA2BC[];
extern unsigned int lbl_801EA2C8[];
extern unsigned int lbl_801EA2D4[];

extern unsigned int DAT_8032fc0c;
extern unsigned int DAT_8032fc08;
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
extern float FLOAT_8032fc80;
extern float FLOAT_8032fc84;
extern float FLOAT_8032fc94;
extern double DOUBLE_8032fc48;
extern double DOUBLE_8032fc50;
extern double DOUBLE_8032fc58;
extern double DOUBLE_8032fc68;
extern double DAT_8032ec20;
extern void* DAT_80238030;
extern float DAT_801ea430;
extern void* GraphicsPcs;

extern "C" void setViewport__11CGraphicPcsFv(void*);

extern class CCameraPcs {
public:
    Mtx m_cameraMatrix;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    float _236_4_;
    float _240_4_;
    float _244_4_;
} CameraPcs;

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
 * PAL Address: 0x8004a348
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __sinit_p_light_cpp(void)
{
    char* lightBase = reinterpret_cast<char*>(&LightPcs);

    *reinterpret_cast<void**>(lightBase) = &__vt__8CManager;
    *reinterpret_cast<void**>(lightBase) = &lbl_801E8668;
    *reinterpret_cast<void**>(lightBase) = &lbl_801EA460;

    __construct_array(lightBase + 0xbc, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, 0xb0, 8);
    __construct_array(lightBase + 0x63c, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, 0xb0, 0x20);
    __construct_array(lightBase + 0x1c3c, (ConstructorDestructor)__ct__Q29CLightPcs10CBumpLightFv, 0, 0x138, 0x20);

    unsigned int a0 = lbl_801EA298[0];
    unsigned int a1 = lbl_801EA298[1];
    unsigned int a2 = lbl_801EA298[2];
    unsigned int b0 = lbl_801EA2A4[0];
    unsigned int b1 = lbl_801EA2A4[1];
    unsigned int b2 = lbl_801EA2A4[2];
    unsigned int c0 = lbl_801EA2B0[0];
    unsigned int c1 = lbl_801EA2B0[1];
    unsigned int c2 = lbl_801EA2B0[2];
    unsigned int d0 = lbl_801EA2BC[0];
    unsigned int d1 = lbl_801EA2BC[1];
    unsigned int d2 = lbl_801EA2BC[2];
    unsigned int e0 = lbl_801EA2C8[0];
    unsigned int e1 = lbl_801EA2C8[1];
    unsigned int e2 = lbl_801EA2C8[2];

    unsigned char* table = reinterpret_cast<unsigned char*>(lbl_801EA2D4);
    *reinterpret_cast<unsigned int*>(table + 0x04) = a0;
    *reinterpret_cast<unsigned int*>(table + 0x08) = a1;
    *reinterpret_cast<unsigned int*>(table + 0x0c) = a2;
    *reinterpret_cast<unsigned int*>(table + 0x10) = b0;
    *reinterpret_cast<unsigned int*>(table + 0x14) = b1;
    *reinterpret_cast<unsigned int*>(table + 0x18) = b2;
    *reinterpret_cast<unsigned int*>(table + 0x1c) = c0;
    *reinterpret_cast<unsigned int*>(table + 0x20) = c1;
    *reinterpret_cast<unsigned int*>(table + 0x24) = c2;
    *reinterpret_cast<unsigned int*>(table + 0x30) = d0;
    *reinterpret_cast<unsigned int*>(table + 0x34) = d1;
    *reinterpret_cast<unsigned int*>(table + 0x38) = d2;
    *reinterpret_cast<unsigned int*>(table + 0x44) = e0;
    *reinterpret_cast<unsigned int*>(table + 0x48) = e1;
    *reinterpret_cast<unsigned int*>(table + 0x4c) = e2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CLightPcs()
{
	// TODO
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
    char* self = (char*)this;
    float zero = FLOAT_8032fc14;
    float one = FLOAT_8032fc2c;
    u8 mask0 = (u8)(-(((u32)__cntlzw(0)) >> 5) & 0x3f);
    u8 mask1 = (u8)(-(((u32)__cntlzw(1)) >> 5) & 0x3f);
    u8 mask2 = (u8)(-(((u32)__cntlzw(2)) >> 5) & 0x3f);

    *(u8*)(self + 0x433c) = 0x3f;
    *(u8*)(self + 0x433d) = 0x3f;
    *(u8*)(self + 0x433e) = 0x3f;
    *(u8*)(self + 0x433f) = 0xff;
    *(u8*)(self + 0x4340) = mask0;
    *(u8*)(self + 0x4341) = mask0;
    *(u8*)(self + 0x4342) = mask0;
    *(u8*)(self + 0x4343) = 0xff;
    *(u8*)(self + 0x4344) = mask1;
    *(u8*)(self + 0x4345) = mask1;
    *(u8*)(self + 0x4346) = mask1;
    *(u8*)(self + 0x4347) = 0xff;
    *(u8*)(self + 0x4348) = mask2;
    *(u8*)(self + 0x4349) = mask2;
    *(u8*)(self + 0x434a) = mask2;
    *(u8*)(self + 0x434b) = 0xff;
    *(float*)(self + 0x434c) = zero;
    *(float*)(self + 0x4350) = zero;
    *(float*)(self + 0x4354) = one;
    *(float*)(self + 0x4358) = zero;
    *(float*)(self + 0x435c) = zero;
    *(float*)(self + 0x4360) = one;
    *(float*)(self + 0x4364) = zero;
    *(float*)(self + 0x4368) = zero;
    *(float*)(self + 0x436c) = one;
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
    return (int)lbl_801EA2D4 + (index * 0x15c);
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
    int i = 2;
    char* ptr = (char*)this;

    do {
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
        i--;
    } while (i != 0);
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
    char* bump = (char*)this + 0x63c;
    for (u32 i = 0; i < 8; i++) {
        if (*(u32*)(bump + 0xb4) != 0) {
            Free__7CMemoryFPv(&Memory, *(void**)(bump + 0xb4));
            *(u32*)(bump + 0xb4) = 0;
            *(u8*)(bump + 0xb0) = 0;
            *(u8*)(bump + 0xb1) = 0;
        }
        bump += 0x138;
    }

    char* light = (char*)this + 0xbc;
    for (u32 i = 0; i < 8; i++) {
        if (*(u32*)(light + 0xb4) != 0) {
            Free__7CMemoryFPv(&Memory, *(void**)(light + 0xb4));
            *(u32*)(light + 0xb4) = 0;
            *(u8*)(light + 0xb0) = 0;
            *(u8*)(light + 0xb1) = 0;
        }
        light += 0x138;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::DestroyBumpLightAll(CLightPcs::TARGET)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::calc()
{
	// TODO
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
    char* light = (char*)this + 0x63c;

    PSMTXCopy(CameraPcs.m_cameraMatrix, mtx);
    for (u32 i = 0; i < *(u32*)((char*)this + 0xb8); i++) {
        if (*(u8*)(light + 0x4f) == 0) {
            PSMTXMultVec(mtx, (Vec*)(light + 4), &vec);
            GXInitLightPos((GXLightObj*)(light + 0x6c), vec.x, vec.y, vec.z);

            if (*(u8*)(light + 0x4e) == 0) {
                PSMTXMultVecSR(mtx, (Vec*)(light + 0x38), &vec);
                GXInitLightDir((GXLightObj*)(light + 0x6c), vec.x, vec.y, vec.z);
            } else {
                GXInitLightDir((GXLightObj*)(light + 0x6c), *(float*)(light + 0x38), *(float*)(light + 0x3c),
                               *(float*)(light + 0x40));
            }

            float cutoff = FLOAT_8032fc74;
            if (*(u32*)light == 1) {
                cutoff = FLOAT_8032fc94 * *(float*)(light + 0x44);
            }

            GXInitLightSpot((GXLightObj*)(light + 0x6c), cutoff, (GXSpotFn)*(u8*)(light + 0x4d));
            GXInitLightAttnK((GXLightObj*)(light + 0x6c), FLOAT_8032fc84 / *(float*)(light + 0x20),
                             FLOAT_8032fc84 / *(float*)(light + 0x1c), FLOAT_8032fc84 / *(float*)(light + 0x1c));
        } else {
            PSMTXMultVecSR(mtx, (Vec*)(light + 0x38), &vec);
            GXInitSpecularDir((GXLightObj*)(light + 0x6c), vec.x, vec.y, vec.z);
            GXInitLightAttn((GXLightObj*)(light + 0x6c), FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc1c,
                            *(float*)(light + 0x48) * FLOAT_8032fc18, FLOAT_8032fc14,
                            FLOAT_8032fc1c - (*(float*)(light + 0x48) * FLOAT_8032fc18));
        }

        light += 0xb0;
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
    float radius = *(float*)((char*)light + 0x1c);
    float maxDist = *(float*)((char*)light + 0x20);
    float intensity = *(float*)((char*)light + 0x28);
    unsigned int colorMask = 0x01010101;

    if (maxDist >= FLOAT_8032fc14) {
        maxDist = radius;
    }

    float absRadius = radius;
    if (radius < FLOAT_8032fc14) {
        absRadius = -radius;
    }

    if (*(int*)((char*)light + 0x50) == 0) {
        reinterpret_cast<unsigned char*>(&colorMask)[0] = 0;
    }
    if (*(int*)((char*)light + 0x54) == 0) {
        reinterpret_cast<unsigned char*>(&colorMask)[1] = 0;
    }
    if (*(int*)((char*)light + 0x58) == 0) {
        reinterpret_cast<unsigned char*>(&colorMask)[2] = 0;
    }

    int index = *(int*)((char*)this + 0xb8);
    *(int*)((char*)this + 0xb8) = index + 1;

    unsigned int* dst = (unsigned int*)((char*)this + 0x63c + index * 0xb0);
    unsigned int* src = (unsigned int*)light;
    for (int i = 0; i < 0x2c; i++) {
        dst[i] = src[i];
    }

    float atten = absRadius * FLOAT_8032fc18 * intensity;
    float radiusSq = radius * radius;
    dst[8] = *(unsigned int*)&maxDist;
    dst[9] = *(unsigned int*)&atten;
    dst[0x18] = colorMask;
    dst[0x2b] = *(unsigned int*)&radiusSq;
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
    char* base = (char*)this + (int)target * 0x9c0;
    char* slot = 0;

    for (int i = 0; i < 8; i++) {
        char* entry = base + i * 0x138 + 0x1c3c;
        if (*(u8*)(entry + 0xb0) == 0) {
            slot = entry;
            break;
        }
    }

    if (slot == 0) {
        if (System.m_execParam != 0) {
            System.Printf((char*)"BUMP LIGHT FULL\n");
        }
        return 0;
    }

    memcpy(slot, srcLight, 0xb0);

    float* fslot = (float*)slot;
    if (fslot[8] >= fslot[7]) {
        fslot[8] = fslot[7];
    }

    fslot[0x2b] = fslot[7] * fslot[7];
    fslot[9] = fslot[7];
    if (fslot[9] < FLOAT_8032fc14) {
        fslot[9] = -fslot[9];
    }
    fslot[9] = fslot[9] * FLOAT_8032fc18 * fslot[10];

    slot[0x63] = 1;
    slot[0x62] = 1;
    slot[0x61] = 1;
    slot[0x60] = 1;

    if (*(u32*)(slot + 0x50) == 0) {
        slot[0x60] = 0;
    }
    if (*(u32*)(slot + 0x54) == 0) {
        slot[0x61] = 0;
    }
    if (*(u32*)(slot + 0x58) == 0) {
        slot[0x62] = 0;
    }

    slot[0xb2] = (char)target;
    *(u32*)(slot + 0xb0) = 1;
    slot[0xb3] = (char)count;

    int texSize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    *(u32*)(slot + 0xb4) = (u32)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
        &Memory, texSize * count, stage, s_p_light_cpp, 0x13b, 0);

    char* texObj = slot + 0xb8;
    int texOffset = 0;
    for (int i = 0; i < count; i++) {
        GXInitTexObj((GXTexObj*)texObj, (void*)(*(u32*)(slot + 0xb4) + texOffset), (u16)0x40, (u16)0x40, (GXTexFmt)3,
                     (GXTexWrapMode)0, (GXTexWrapMode)0, (u8)0);
        texOffset += texSize;
        texObj += 0x20;
    }

    return (CLightPcs::CBumpLight*)slot;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetMapColorAlpha(float (*) [4], _GXColor, _GXColor, unsigned char, float, float, float, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetAmbient(_GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetAmbientAlpha(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetNumDiffuse(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetDiffuseColor(unsigned long, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::EnableLight(int, int)
{
	// TODO
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
    char* light = (char*)this + idx * 0xb0 + 0xbc;
    Mtx cam;
    Vec tmp;
    Vec lightDir;

    lightDir.x = CameraPcs._236_4_;
    lightDir.y = CameraPcs._240_4_;
    lightDir.z = CameraPcs._244_4_;

    if (mode == 0) {
        lightDir.x = dir->x;
        lightDir.y = dir->y;
        lightDir.z = dir->z;
    }

    GXInitLightColor((GXLightObj*)(light + 0x6c), color);
    PSMTXCopy(CameraPcs.m_cameraMatrix, cam);

    tmp.x = FLOAT_8032fc70 * -lightDir.x;
    tmp.y = FLOAT_8032fc70 * -lightDir.y;
    tmp.z = FLOAT_8032fc70 * -lightDir.z;
    PSMTXMultVec(cam, &tmp, &tmp);
    GXInitLightPos((GXLightObj*)(light + 0x6c), tmp.x, tmp.y, tmp.z);

    PSMTXMultVecSR(cam, &lightDir, &lightDir);
    GXInitLightDir((GXLightObj*)(light + 0x6c), lightDir.x, lightDir.y, lightDir.z);

    GXInitLightSpot((GXLightObj*)(light + 0x6c), FLOAT_8032fc74, (GXSpotFn)4);
    GXInitLightAttnK((GXLightObj*)(light + 0x6c), FLOAT_8032fc14, FLOAT_8032fc78, FLOAT_8032fc14);
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
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::InsertOctTree(CLightPcs::TARGET, COctTree&)
{
	// TODO
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
    if (*(int*)((char*)this + 0xb4) == 0) {
        return;
    }

    _GXColor chanAmb;
    _GXColor chanMat;
    _GXColor chanAmb2;
    _GXColor chanMat2;

    unsigned char u0 = *(unsigned char*)((char*)this + 0x68);
    unsigned char u1 = *(unsigned char*)((char*)this + 0x69);
    unsigned char u2 = *(unsigned char*)((char*)this + 0x6a);
    unsigned char u3 = *(unsigned char*)((char*)this + 0x6b);

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
    if (*(char*)((char*)this + 0xb1) == 1) {
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
        C_MTXLookAt(lookAt, &eye, &up, (Vec*)((char*)this + 0x38));

        Vec camPos;
        camPos.x = CameraPcs._224_4_;
        camPos.y = CameraPcs._228_4_;
        camPos.z = CameraPcs._232_4_;

        Vec lightPos;
        PSVECSubtract((Vec*)((char*)this + 0x10), &camPos, &lightPos);
        PSVECNormalize(&lightPos, &lightPos);

        Vec nrm;
        PSVECNormalize((Vec*)((char*)this + 0x38), &nrm);

        Vec diff;
        PSVECSubtract(&lightPos, &nrm, &diff);

        float scale = FLOAT_8032fc1c;
        if (*(char*)((char*)this + 0xb2) == 1) {
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
        eyeDir.x = *(float*)((char*)this + 0x38);
        eyeDir.y = *(float*)((char*)this + 0x3c);
        eyeDir.z = *(float*)((char*)this + 0x40);
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

    for (int i = 0; i < (int)(unsigned int)*(unsigned char*)((char*)this + 0xb3); i++) {
        int texBase = *(int*)((char*)this + 0xb4);
        GXLightObj lightObj;
        GXInitSpecularDir(&lightObj, eyeDir.x, eyeDir.y, eyeDir.z);

        _GXColor lightColor;
        *reinterpret_cast<unsigned int*>(&lightColor) = packedColor;
        GXInitLightColor(&lightObj, lightColor);

        if (*(char*)((char*)this + 0xb2) == 1) {
            double d0 = (double)FLOAT_8032fc14;
            double d1 = (double)(*(float*)((char*)this + 0x48) * FLOAT_8032fc18);
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
                                dist0 = DAT_8032ec20;
                            }
                        } else {
                            dist0 = DAT_8032ec20;
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
                                dist1 = DAT_8032ec20;
                            }
                        } else {
                            dist1 = DAT_8032ec20;
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
    setViewport__11CGraphicPcsFv(GraphicsPcs);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetTexCopySrc(0, 0, 0x40, 0x40);
    GXSetTexCopyDst((u16)0x40, (u16)0x40, GX_TF_I8, GX_FALSE);
    GXCopyTex(DAT_80238030, GX_TRUE);
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
    PSMTXCopy(CameraPcs.m_cameraMatrix, cam);
    Mtx* out = (Mtx*)((char*)this + 0x30);

    if (mode == 0) {
        if (scale == nullptr ||
            ((FLOAT_8032fc14 == scale[0]) && (FLOAT_8032fc14 == scale[1]) && (FLOAT_8032fc14 == scale[2]))) {
            PSMTXConcat(cam, *input, *out);
        } else {
            Mtx tmp;
            PSMTXCopy(*input, tmp);
            Vec camPos;
            camPos.x = CameraPcs._224_4_;
            camPos.y = CameraPcs._228_4_;
            camPos.z = CameraPcs._232_4_;
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

    if ((bump != nullptr) && (*(char*)((char*)bump + 0xb0) != 0)) {
        Mtx* bumpMat0 = (Mtx*)((char*)this + 4);
        Mtx* bumpMat1 = (Mtx*)((char*)this + 0x34);

        if (*(char*)((char*)bump + 0xb1) == 1) {
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

            double camX = (double)CameraPcs._224_4_;
            double camZ = (double)CameraPcs._232_4_;
            PSMTXIdentity(*(Mtx*)((char*)this + 100));

            float f0 = FLOAT_8032fc24;
            float f1 = FLOAT_8032fc14;
            *(float*)((char*)this + 100) = FLOAT_8032fc24;
            float f2 = FLOAT_8032fc18;
            *(float*)((char*)this + 0x7c) = f0;
            float f3 = FLOAT_8032fc20;
            *(float*)((char*)this + 0x8c) = f1;
            *(float*)((char*)this + 0x78) = f1;
            *(float*)((char*)this + 0x88) = f1;
            *(float*)((char*)this + 0x70) =
                -(f0 * (float)(camX + (double)*(float*)((char*)bump + 0x2c)) - f2);
            *(float*)((char*)this + 0x80) =
                -(f0 * (float)(camZ + (double)*(float*)((char*)bump + 0x30)) - f2);
            *(float*)((char*)this + 0x90) = f1;
            *(float*)((char*)this + 0xa4) = f3;
            *(float*)((char*)this + 0x94) = f3;
            *(float*)((char*)this + 0xa8) = f1;
            *(float*)((char*)this + 0xa0) = f1;
            *(float*)((char*)this + 0x9c) = f1;
            *(float*)((char*)this + 0x98) = f1;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CBumpLight::CBumpLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::CBumpLight::SetTexture(_GXTexMapID, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CLight::CLight()
{
	// TODO
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
