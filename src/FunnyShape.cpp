#include "ffcc/FunnyShape.h"
#include "ffcc/gxfunc.h"
#include "types.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

#include <math.h>
#include <string.h>

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" s32 rand();

extern "C" u32 DAT_8032fd58;
extern "C" u32 DAT_8032fd5c;
extern "C" u32 DAT_8032fd60;
extern "C" double DOUBLE_8032fd88;
extern "C" float FLOAT_8032fd64;
extern "C" float FLOAT_8032fd68;
extern "C" float FLOAT_8032fd6c;
extern "C" float FLOAT_8032fd70;
extern "C" float FLOAT_8032fd74;
extern "C" float FLOAT_8032fd78;
extern "C" float FLOAT_8032fd7c;
extern "C" float FLOAT_8032fd80;
extern "C" float FLOAT_8032fd90;
extern "C" float FLOAT_8032fd94;
extern "C" float FLOAT_8032fd98;
extern "C" float FLOAT_8032fd9c;
extern "C" float FLOAT_8032fda0;
extern "C" float FLOAT_8032fda4;
extern "C" float FLOAT_8032fda8;

namespace {
static inline u8* Ptr(CFunnyShape* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline void*& PtrAt(CFunnyShape* self, u32 offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline u32& U32At(CFunnyShape* self, u32 offset)
{
    return *reinterpret_cast<u32*>(Ptr(self, offset));
}

static inline s16 S16At(const u8* p, u32 offset)
{
    return *reinterpret_cast<const s16*>(p + offset);
}

static inline u32 U32At(const u8* p, u32 offset)
{
    return *reinterpret_cast<const u32*>(p + offset);
}

static inline s32 Div16Floor(s16 x)
{
    return (x >> 4) + ((x < 0) && ((x & 0xF) != 0));
}

static inline void WriteVertex(float px, float py, float pz, u32 color, float tu, float tv)
{
    GXWGFifo.f32 = px;
    GXWGFifo.f32 = py;
    GXWGFifo.f32 = pz;
    GXWGFifo.u32 = color;
    GXWGFifo.f32 = tu;
    GXWGFifo.f32 = tv;
}

static inline GXColor ToGXColor(u32 color)
{
    GXColor out;
    memcpy(&out, &color, sizeof(out));
    return out;
}
}

/*
 * --INFO--
 * PAL Address: 0x80051e4c
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFunnyShape::CFunnyShape()
{
    PtrAt(this, 0x6010) = 0;
    memset(this, 0, 0x6000);
    memset(Ptr(this, 0x6000), 0, 0x10);
    memset(Ptr(this, 0x60D8), 0, 0x10);
    memset(Ptr(this, 0x6014), 0, 0x40);

    CFunnyShape* p = this;
    s32 i = 2;
    do {
        PtrAt(p, 0x6094) = 0;
        PtrAt(p, 0x6014) = 0;
        PtrAt(p, 0x6054) = 0;
        PtrAt(p, 0x6098) = 0;
        PtrAt(p, 0x6018) = 0;
        PtrAt(p, 0x6058) = 0;
        PtrAt(p, 0x609C) = 0;
        PtrAt(p, 0x601C) = 0;
        PtrAt(p, 0x605C) = 0;
        PtrAt(p, 0x60A0) = 0;
        PtrAt(p, 0x6020) = 0;
        PtrAt(p, 0x6060) = 0;
        PtrAt(p, 0x60A4) = 0;
        PtrAt(p, 0x6024) = 0;
        PtrAt(p, 0x6064) = 0;
        PtrAt(p, 0x60A8) = 0;
        PtrAt(p, 0x6028) = 0;
        PtrAt(p, 0x6068) = 0;
        PtrAt(p, 0x60AC) = 0;
        PtrAt(p, 0x602C) = 0;
        PtrAt(p, 0x606C) = 0;
        PtrAt(p, 0x60B0) = 0;
        PtrAt(p, 0x6030) = 0;
        PtrAt(p, 0x6070) = 0;
        p = reinterpret_cast<CFunnyShape*>(Ptr(p, 0x20));
        i--;
    } while (i != 0);

    U32At(this, 0x60D4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80051d80
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFunnyShape::~CFunnyShape()
{
    if (PtrAt(this, 0x6010) != 0) {
        __dla__FPv(PtrAt(this, 0x6010));
        PtrAt(this, 0x6010) = 0;
    }

    if (PtrAt(this, 0x600C) != 0) {
        __dla__FPv(PtrAt(this, 0x600C));
        PtrAt(this, 0x600C) = 0;
    }

    for (s32 i = 0; i < 0x10; i++) {
        u32 offs = static_cast<u32>(i) * 4;
        if (PtrAt(this, 0x6094 + offs) != 0) {
            __dla__FPv(PtrAt(this, 0x6094 + offs));
            PtrAt(this, 0x6094 + offs) = 0;
        }

        if (PtrAt(this, 0x6014 + offs) != 0) {
            __dl__FPv(PtrAt(this, 0x6014 + offs));
            PtrAt(this, 0x6014 + offs) = 0;
        }

        if (PtrAt(this, 0x6054 + offs) != 0) {
            __dl__FPv(PtrAt(this, 0x6054 + offs));
            PtrAt(this, 0x6054 + offs) = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051d80
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CFunnyShape* dtor_80051D80(CFunnyShape* funnyShape, short shouldDelete)
{
    if (funnyShape != 0) {
        if (PtrAt(funnyShape, 0x6010) != 0) {
            __dla__FPv(PtrAt(funnyShape, 0x6010));
            PtrAt(funnyShape, 0x6010) = 0;
        }

        if (PtrAt(funnyShape, 0x600C) != 0) {
            __dla__FPv(PtrAt(funnyShape, 0x600C));
            PtrAt(funnyShape, 0x600C) = 0;
        }

        for (s32 i = 0; i < 0x10; i++) {
            u32 offs = static_cast<u32>(i) * 4;
            if (PtrAt(funnyShape, 0x6094 + offs) != 0) {
                __dla__FPv(PtrAt(funnyShape, 0x6094 + offs));
                PtrAt(funnyShape, 0x6094 + offs) = 0;
            }

            if (PtrAt(funnyShape, 0x6014 + offs) != 0) {
                __dl__FPv(PtrAt(funnyShape, 0x6014 + offs));
                PtrAt(funnyShape, 0x6014 + offs) = 0;
            }

            if (PtrAt(funnyShape, 0x6054 + offs) != 0) {
                __dl__FPv(PtrAt(funnyShape, 0x6054 + offs));
                PtrAt(funnyShape, 0x6054 + offs) = 0;
            }
        }

        if (shouldDelete > 0) {
            __dl__FPv(funnyShape);
        }
    }

    return funnyShape;
}

/*
 * --INFO--
 * PAL Address: 0x80051b8c
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::InitAnmWork()
{
    const u32 flags = U32At(this, 0);
    const float zero = FLOAT_8032fd6c;
    const float angleMul = FLOAT_8032fda4;
    const float angleDiv = FLOAT_8032fda8;
    u8* entry = Ptr(this, 0x30);

    for (s32 i = 0; i < 0x200; i++) {
        *reinterpret_cast<s32*>(entry) = i;
        *reinterpret_cast<void**>(entry + 4) = PtrAt(this, 0xC);

        s32 r = rand();
        const s16 range = *reinterpret_cast<s16*>(Ptr(this, 0x2A));
        *reinterpret_cast<float*>(entry + 8) = static_cast<float>(r - (r / range) * range);

        r = rand();
        *reinterpret_cast<float*>(entry + 0xC) = static_cast<float>(r - (r / range) * range);
        *reinterpret_cast<float*>(entry + 0x10) = zero;

        r = rand();
        const s16 shapeCount = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(PtrAt(this, 0xC)) + 6);
        *reinterpret_cast<s16*>(entry + 0x14) = static_cast<s16>(r - (r / shapeCount) * shapeCount);
        *reinterpret_cast<s16*>(entry + 0x16) = 2;
        *reinterpret_cast<float*>(entry + 0x20) = zero;
        *reinterpret_cast<float*>(entry + 0x24) = zero;

        r = rand();
        s32 q = r / 0x168 + (r >> 0x1F);
        q = r + (q - (q >> 0x1F)) * -0x168;
        *reinterpret_cast<float*>(entry + 0x28) = (angleMul * static_cast<float>(q)) / angleDiv;

        u32 u = static_cast<u32>(rand());
        if (((u & 1) ^ (u >> 0x1F)) != (u >> 0x1F)) {
            *reinterpret_cast<float*>(entry + 8) *= FLOAT_8032fd80;
        }

        u = static_cast<u32>(rand());
        if (((u & 1) ^ (u >> 0x1F)) != (u >> 0x1F)) {
            *reinterpret_cast<float*>(entry + 0xC) *= FLOAT_8032fd80;
        }

        if ((flags & 0x80) == 0) {
            *reinterpret_cast<s16*>(entry + 0x14) = 0;
            *reinterpret_cast<float*>(entry + 8) = zero;
            *reinterpret_cast<float*>(entry + 0xC) = zero;
        }

        entry += 0x30;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051968
 * PAL Size: 548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::Update()
{
    if ((Ptr(this, 0x60D4)[0] == 0) || (PtrAt(this, 0xC) == 0)) {
        return;
    }

    const u32 noSpread = (((U32At(this, 0) >> 7) & 1) ^ 1);
    const s16 count = *reinterpret_cast<s16*>(Ptr(this, 0x28));
    u8* entry = Ptr(this, 0x30);

    for (s16 i = 0; i < count; i++) {
        *reinterpret_cast<s16*>(entry + 0x16) = static_cast<s16>(*reinterpret_cast<s16*>(entry + 0x16) - 0x200);
        if (*reinterpret_cast<s16*>(entry + 0x16) < 1) {
            *reinterpret_cast<s16*>(entry + 0x14) = static_cast<s16>(*reinterpret_cast<s16*>(entry + 0x14) + 1);
            if (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(PtrAt(this, 0xC)) + 6) <=
                *reinterpret_cast<s16*>(entry + 0x14)) {
                *reinterpret_cast<s16*>(entry + 0x14) = 0;

                s32 r = rand();
                const s16 range = *reinterpret_cast<s16*>(Ptr(this, 0x2A));
                *reinterpret_cast<float*>(entry + 8) = static_cast<float>(r - (r / range) * range);

                r = rand();
                *reinterpret_cast<float*>(entry + 0xC) = static_cast<float>(r - (r / range) * range);
                *reinterpret_cast<float*>(entry + 0x10) = FLOAT_8032fd6c;
                *reinterpret_cast<s16*>(entry + 0x16) = 2;
                *reinterpret_cast<float*>(entry + 0x20) = FLOAT_8032fd6c;
                *reinterpret_cast<float*>(entry + 0x24) = FLOAT_8032fd6c;

                r = rand();
                s32 q = r / 0x168 + (r >> 0x1F);
                q = r + (q - (q >> 0x1F)) * -0x168;
                *reinterpret_cast<float*>(entry + 0x28) =
                    (FLOAT_8032fda4 * static_cast<float>(q)) / FLOAT_8032fda8;

                u32 u = static_cast<u32>(rand());
                if (((u & 1) ^ (u >> 0x1F)) != (u >> 0x1F)) {
                    *reinterpret_cast<float*>(entry + 8) *= FLOAT_8032fd80;
                }

                u = static_cast<u32>(rand());
                if (((u & 1) ^ (u >> 0x1F)) != (u >> 0x1F)) {
                    *reinterpret_cast<float*>(entry + 0xC) *= FLOAT_8032fd80;
                }

                if (noSpread != 0) {
                    *reinterpret_cast<s16*>(entry + 0x14) = 0;
                    *reinterpret_cast<float*>(entry + 8) = FLOAT_8032fd6c;
                    *reinterpret_cast<float*>(entry + 0xC) = FLOAT_8032fd6c;
                }
            }

            *reinterpret_cast<s16*>(entry + 0x16) = *reinterpret_cast<s16*>(
                reinterpret_cast<u8*>(PtrAt(this, 0xC)) + *reinterpret_cast<s16*>(entry + 0x14) * 8 + 0x12);
        }

        if (noSpread != 0) {
            return;
        }

        entry += 0x30;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051664
 * PAL Size: 772b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::Render()
{
    if ((Ptr(this, 0x60D4)[0] == 0) || (PtrAt(this, 0x6010) == 0)) {
        return;
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 2, 3);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(PtrAt(this, 0x6014)), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetNumTevStages(1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetChanAmbColor(GX_COLOR0A0, ToGXColor(DAT_8032fd60));
    GXSetChanMatColor(GX_COLOR0A0, ToGXColor(DAT_8032fd60));

    s32 count = 1;
    if ((U32At(this, 0) & 0x80) != 0) {
        count = *reinterpret_cast<s16*>(Ptr(this, 0x28));
    }

    u8* entry = Ptr(this, 0x30);
    u8* anm = reinterpret_cast<u8*>(PtrAt(this, 0x6010));
    for (s32 i = 0; i < count; i++) {
        Vec2d pos;
        pos.x = FLOAT_8032fd9c + *reinterpret_cast<float*>(entry + 8);
        pos.y = FLOAT_8032fda0 + *reinterpret_cast<float*>(entry + 0xC);

        const s16 shapeIndex = *reinterpret_cast<s16*>(entry + 0x14);
        const s32 shapeOffset = *reinterpret_cast<s32*>(anm + 0x10 + shapeIndex * 8);
        RenderShape(reinterpret_cast<FS_tagOAN3_SHAPE*>(anm + shapeOffset), pos, *reinterpret_cast<float*>(entry + 0x28));

        entry += 0x30;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005137c
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::RenderTexture()
{
    if (Ptr(this, 0x60D4)[0] == 0) {
        return;
    }

    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetChanAmbColor(GX_COLOR0A0, ToGXColor(DAT_8032fd58));
    GXSetChanMatColor(GX_COLOR0A0, ToGXColor(DAT_8032fd58));
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 2, 3);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(PtrAt(this, 0x6014)), GX_TEXMAP0);

    const u8* texData = reinterpret_cast<const u8*>(PtrAt(this, 0x6054));
    const float width = static_cast<float>(*reinterpret_cast<const s16*>(texData + 4));
    const float height = static_cast<float>(*reinterpret_cast<const s16*>(texData + 6));
    GXSetViewport(FLOAT_8032fd98, FLOAT_8032fd98, width, height, FLOAT_8032fd6c, FLOAT_8032fd74);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 4);
    WriteVertex(FLOAT_8032fd80, FLOAT_8032fd74, FLOAT_8032fd6c, DAT_8032fd5c, FLOAT_8032fd6c, FLOAT_8032fd74);
    WriteVertex(FLOAT_8032fd74, FLOAT_8032fd74, FLOAT_8032fd6c, DAT_8032fd5c, FLOAT_8032fd74, FLOAT_8032fd74);
    WriteVertex(FLOAT_8032fd74, FLOAT_8032fd80, FLOAT_8032fd6c, DAT_8032fd5c, FLOAT_8032fd74, FLOAT_8032fd6c);
    WriteVertex(FLOAT_8032fd80, FLOAT_8032fd80, FLOAT_8032fd6c, DAT_8032fd5c, FLOAT_8032fd6c, FLOAT_8032fd6c);
}

/*
 * --INFO--
 * PAL Address: 0x80051110
 * PAL Size: 620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::RenderShape()
{
    if ((Ptr(this, 0x60D4)[0] == 0) || (PtrAt(this, 0x6010) == 0)) {
        return;
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 2, 3);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(PtrAt(this, 0x6014)), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetNumTevStages(1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetChanAmbColor(GX_COLOR0A0, ToGXColor(DAT_8032fd60));
    GXSetChanMatColor(GX_COLOR0A0, ToGXColor(DAT_8032fd60));

    Vec2d offset;
    offset.x = FLOAT_8032fd90;
    offset.y = FLOAT_8032fd94;
    RenderShape(reinterpret_cast<FS_tagOAN3_SHAPE*>(PtrAt(this, 0x6010)), offset, FLOAT_8032fd6c);
}

/*
 * --INFO--
 * PAL Address: 0x800510b0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::ClearAnmData()
{
    if (PtrAt(this, 0x600C) != 0) {
        __dla__FPv(PtrAt(this, 0x600C));
        PtrAt(this, 0x600C) = 0;
    }

    memset(this, 0, 0x30);
    memset(Ptr(this, 0x6000), 0, 0x10);
}

/*
 * --INFO--
 * PAL Address: 0x80051020
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::ClearTextureData()
{
    U32At(this, 0x60D4) = 0;
    u8* iter = reinterpret_cast<u8*>(this);
    for (s32 i = 0; i < 0x10; i++) {
        void** texData = reinterpret_cast<void**>(iter + 0x6094);
        if (*texData != 0) {
            __dla__FPv(*texData);
            *texData = 0;
        }

        void** texObj = reinterpret_cast<void**>(iter + 0x6014);
        if (*texObj != 0) {
            __dl__FPv(*texObj);
            *texObj = 0;
        }

        void** rawData = reinterpret_cast<void**>(iter + 0x6054);
        if (*rawData != 0) {
            __dl__FPv(*rawData);
            *rawData = 0;
        }
        iter += 4;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005051c
 * PAL Size: 2820b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShape::RenderShape(FS_tagOAN3_SHAPE* shape, Vec2d offset, float angle)
{
    const u8* shapeData = reinterpret_cast<const u8*>(shape);
    const float* offsetXY = reinterpret_cast<const float*>(&offset);
    const u16 flags = *reinterpret_cast<const u16*>(shapeData);
    const s16 count = *reinterpret_cast<const s16*>(shapeData + 2);
    s32 packedStride = 0;
    s32 rotatedStride = 0;

    for (s16 i = 0; i < count; i++) {
        u32 color;
        float p0x;
        float p0y;
        float p0z;
        float p1x;
        float p1y;
        float p1z;
        float p2x;
        float p2y;
        float p2z;
        float p3x;
        float p3y;
        float p3z;
        float u0;
        float v0;
        float u1;
        float v1;

        if ((flags & 8) == 0) {
            const u8* entry = shapeData + packedStride;
            const u32 texIndex = entry[0x30];
            const s8 numTex = *reinterpret_cast<s8*>(Ptr(this, 0x60D4));
            if ((s32)texIndex < (s32)numTex) {
                GXLoadTexObj(reinterpret_cast<GXTexObj*>(PtrAt(this, 0x14 + texIndex * 4)), GX_TEXMAP0);
            }

            const s8 blendMode = *reinterpret_cast<const s8*>(entry + 0x1C);
            if (blendMode == 'H') {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 1, 3);
            } else if (blendMode == 'B') {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3, 4, 1, 3);
            } else if (blendMode == -0x78) {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 3);
            }

            const s32 x0 = Div16Floor(S16At(entry, 0x20));
            const s32 y0 = Div16Floor(S16At(entry, 0x22));
            const s32 x1 = Div16Floor(S16At(entry, 0x24));
            const s32 y1 = Div16Floor(S16At(entry, 0x26));
            GXSetViewport(offsetXY[0] + static_cast<float>(x0 * 2), offsetXY[1] + static_cast<float>(y0 * 2),
                          static_cast<float>((x1 - x0) * 2), static_cast<float>((y1 - y0) * 2),
                          FLOAT_8032fd6c, FLOAT_8032fd74);

            const s16 texX = S16At(entry, 0x28);
            const s16 texY = S16At(entry, 0x2A);
            const s16 texW = S16At(entry, 0x2C);
            const s16 texH = S16At(entry, 0x2E);
            u0 = static_cast<float>(texX) / FLOAT_8032fd78;
            v0 = FLOAT_8032fd74 - static_cast<float>(texY) / FLOAT_8032fd78;
            u1 = u0 + static_cast<float>(texW) / FLOAT_8032fd78;
            v1 = v0 - static_cast<float>(texH) / FLOAT_8032fd78;

            p0x = FLOAT_8032fd80;
            p0y = FLOAT_8032fd74;
            p0z = FLOAT_8032fd6c;
            p1x = FLOAT_8032fd6c;
            p1y = FLOAT_8032fd74;
            p1z = FLOAT_8032fd6c;
            p2x = FLOAT_8032fd6c;
            p2y = FLOAT_8032fd6c;
            p2z = FLOAT_8032fd80;
            p3x = FLOAT_8032fd80;
            p3y = FLOAT_8032fd6c;
            p3z = FLOAT_8032fd80;
            color = U32At(entry, 0x18);
        } else {
            const u8* entry = shapeData + rotatedStride;
            const u32 texIndex = entry[0x38];
            const s8 numTex = *reinterpret_cast<s8*>(Ptr(this, 0x60D4));
            float minX = FLOAT_8032fd64;
            float maxX = FLOAT_8032fd68;
            float minY = FLOAT_8032fd64;
            float maxY = FLOAT_8032fd68;
            float drawAngle = angle;
            if ((s32)texIndex < (s32)numTex) {
                GXLoadTexObj(reinterpret_cast<GXTexObj*>(PtrAt(this, 0x14 + texIndex * 4)), GX_TEXMAP0);
            }

            const s8 blendMode = *reinterpret_cast<const s8*>(entry + 0x1C);
            if (blendMode == 'H') {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 1, 3);
            } else if (blendMode == 'B') {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3, 1, 1, 3);
            } else if (blendMode == -0x78) {
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 3);
            }

            if ((U32At(this, 0) & 0x100) == 0) {
                drawAngle = FLOAT_8032fd6c;
            }

            const float sinA = static_cast<float>(sin(drawAngle));
            const float cosA = static_cast<float>(cos(drawAngle));
            const float x0 = static_cast<float>(Div16Floor(S16At(entry, 0x20)));
            const float y0 = static_cast<float>(Div16Floor(S16At(entry, 0x22)));
            const float x1 = static_cast<float>(Div16Floor(S16At(entry, 0x24)));
            const float y1 = static_cast<float>(Div16Floor(S16At(entry, 0x26)));
            const float x2 = static_cast<float>(Div16Floor(S16At(entry, 0x28)));
            const float y2 = static_cast<float>(Div16Floor(S16At(entry, 0x2A)));
            const float x3 = static_cast<float>(Div16Floor(S16At(entry, 0x2C)));
            const float y3 = static_cast<float>(Div16Floor(S16At(entry, 0x2E)));
            const float rx0 = x0 * cosA - y0 * sinA;
            const float ry0 = x0 * sinA + y0 * cosA;
            const float rx1 = x1 * cosA - y1 * sinA;
            const float ry1 = x1 * sinA + y1 * cosA;
            const float rx2 = x2 * cosA - y2 * sinA;
            const float ry2 = x2 * sinA + y2 * cosA;
            const float rx3 = x3 * cosA - y3 * sinA;
            const float ry3 = x3 * sinA + y3 * cosA;

            if (rx0 < minX) {
                minX = rx0;
            }
            if (rx1 < minX) {
                minX = rx1;
            }
            if (rx2 < minX) {
                minX = rx2;
            }
            if (rx3 < minX) {
                minX = rx3;
            }
            if (ry0 < minY) {
                minY = ry0;
            }
            if (ry1 < minY) {
                minY = ry1;
            }
            if (ry2 < minY) {
                minY = ry2;
            }
            if (ry3 < minY) {
                minY = ry3;
            }

            maxX = rx0;
            if (maxX < rx1) {
                maxX = rx1;
            }
            if (maxX < rx2) {
                maxX = rx2;
            }
            if (maxX < rx3) {
                maxX = rx3;
            }
            maxY = ry0;
            if (maxY < ry1) {
                maxY = ry1;
            }
            if (maxY < ry2) {
                maxY = ry2;
            }
            if (maxY < ry3) {
                maxY = ry3;
            }

            const float viewportScale = FLOAT_8032fd70;
            const float viewportW = viewportScale * (maxX - minX);
            const float viewportH = viewportScale * (maxY - minY);
            GXSetViewport(viewportScale * minX + offsetXY[0], viewportScale * minY + offsetXY[1], viewportW,
                          viewportH, FLOAT_8032fd6c, FLOAT_8032fd74);

            const s16 texX = S16At(entry, 0x30);
            const s16 texY = S16At(entry, 0x32);
            const s16 texW = S16At(entry, 0x34);
            const s16 texH = S16At(entry, 0x36);
            const float padScale = FLOAT_8032fd7c;
            const float padW = viewportW * padScale * padScale;
            const float padH = viewportH * padScale * padScale;
            const float viewMaxX = maxX - padW;
            const float viewMaxY = maxY - padH;
            const float invPadH = FLOAT_8032fd74 / padH;
            const float invPadW = -(FLOAT_8032fd74 / padW);

            u0 = static_cast<float>(texX) / FLOAT_8032fd78;
            v0 = FLOAT_8032fd74 - static_cast<float>(texY) / FLOAT_8032fd78;
            u1 = u0 + static_cast<float>(texW) / FLOAT_8032fd78;
            v1 = v0 - static_cast<float>(texH) / FLOAT_8032fd78;

            p0x = invPadW * (rx0 - viewMaxX);
            p0y = invPadH * (ry0 - viewMaxY);
            p0z = FLOAT_8032fd6c;
            p1x = invPadW * (rx1 - viewMaxX);
            p1y = invPadH * (ry1 - viewMaxY);
            p1z = FLOAT_8032fd6c;
            p2x = invPadW * (rx3 - viewMaxX);
            p2y = invPadH * (ry3 - viewMaxY);
            p2z = FLOAT_8032fd6c;
            p3x = invPadW * (rx2 - viewMaxX);
            p3y = invPadH * (ry2 - viewMaxY);
            p3z = FLOAT_8032fd6c;
            color = U32At(entry, 0x18);
        }

        DCStoreRange(&color, 4);
        GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 4);
        WriteVertex(p0x, p0y, p0z, color, u0, v0);
        WriteVertex(p1x, p1y, p1z, color, u1, v0);
        WriteVertex(p2x, p2y, p2z, color, u1, v1);
        WriteVertex(p3x, p3y, p3z, color, u0, v1);

        packedStride += 0x24;
        rotatedStride += 0x2C;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::SetDefaultStage()
{
	// TODO
}
