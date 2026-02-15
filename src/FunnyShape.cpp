#include "ffcc/FunnyShape.h"
#include "ffcc/gxfunc.h"
#include "types.h"

#include <dolphin/gx.h>
#include <string.h>

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern u32 DAT_8032fd60;
extern float FLOAT_8032fd6c;
extern float FLOAT_8032fd90;
extern float FLOAT_8032fd94;

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

    for (s32 i = 0; i < 0x10; i++) {
        u32 offs = static_cast<u32>(i) * 4;
        PtrAt(this, 0x6014 + offs) = 0;
        PtrAt(this, 0x6054 + offs) = 0;
        PtrAt(this, 0x6094 + offs) = 0;
    }

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
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::InitAnmWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::Update()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::Render()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::RenderTexture()
{
	// TODO
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
    if ((U32At(this, 0x60D4) != 0) && (PtrAt(this, 0x6010) != 0)) {
        struct Vec2dPair {
            float x;
            float y;
        };

        u32 color = DAT_8032fd60;
        Vec2dPair origin;
        origin.x = FLOAT_8032fd90;
        origin.y = FLOAT_8032fd94;

        GXClearVtxDesc();
        GXSetVtxDesc(static_cast<GXAttr>(9), static_cast<GXAttrType>(1));
        GXSetVtxDesc(static_cast<GXAttr>(0xB), static_cast<GXAttrType>(1));
        GXSetVtxDesc(static_cast<GXAttr>(0xD), static_cast<GXAttrType>(1));
        GXSetVtxAttrFmt(static_cast<GXVtxFmt>(0), static_cast<GXAttr>(9), static_cast<GXCompCnt>(1), static_cast<GXCompType>(4), 0);
        GXSetVtxAttrFmt(static_cast<GXVtxFmt>(0), static_cast<GXAttr>(0xB), static_cast<GXCompCnt>(1), static_cast<GXCompType>(5), 0);
        GXSetVtxAttrFmt(static_cast<GXVtxFmt>(0), static_cast<GXAttr>(0xD), static_cast<GXCompCnt>(1), static_cast<GXCompType>(4), 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTexCoordGen2(static_cast<GXTexCoordID>(0), static_cast<GXTexGenType>(1), static_cast<GXTexGenSrc>(4),
                          static_cast<u32>(0x3C), static_cast<GXBool>(0), static_cast<u32>(0x7D));
        _GXSetTevOrder(static_cast<GXTevStageID>(0), static_cast<GXTexCoordID>(0), static_cast<GXTexMapID>(0),
                       static_cast<GXChannelID>(4));
        _GXSetBlendMode(static_cast<GXBlendMode>(1), static_cast<GXBlendFactor>(4), static_cast<GXBlendFactor>(2),
                        static_cast<GXLogicOp>(3));
        GXLoadTexObj(reinterpret_cast<_GXTexObj*>(PtrAt(this, 0x6014)), static_cast<GXTexMapID>(0));
        GXSetNumChans(1);
        GXSetChanCtrl(static_cast<GXChannelID>(0), static_cast<GXBool>(0), static_cast<GXColorSrc>(0), static_cast<GXColorSrc>(1),
                      static_cast<u32>(0), static_cast<GXDiffuseFn>(2), static_cast<GXAttnFn>(1));
        GXSetChanCtrl(static_cast<GXChannelID>(2), static_cast<GXBool>(0), static_cast<GXColorSrc>(0), static_cast<GXColorSrc>(1),
                      static_cast<u32>(0), static_cast<GXDiffuseFn>(0), static_cast<GXAttnFn>(2));
        GXSetNumTevStages(1);
        _GXSetTevOrder(static_cast<GXTevStageID>(0), static_cast<GXTexCoordID>(0), static_cast<GXTexMapID>(0),
                       static_cast<GXChannelID>(4));
        _GXSetTevColorIn(static_cast<GXTevStageID>(0), static_cast<GXTevColorArg>(0xF), static_cast<GXTevColorArg>(8),
                         static_cast<GXTevColorArg>(0xA), static_cast<GXTevColorArg>(0xF));
        _GXSetTevColorOp(static_cast<GXTevStageID>(0), static_cast<GXTevOp>(0), static_cast<GXTevBias>(0),
                         static_cast<GXTevScale>(0), 1, static_cast<GXTevRegID>(0));
        _GXSetTevAlphaIn(static_cast<GXTevStageID>(0), static_cast<GXTevAlphaArg>(7), static_cast<GXTevAlphaArg>(4),
                         static_cast<GXTevAlphaArg>(5), static_cast<GXTevAlphaArg>(7));
        _GXSetTevAlphaOp(static_cast<GXTevStageID>(0), static_cast<GXTevOp>(0), static_cast<GXTevBias>(0),
                         static_cast<GXTevScale>(1), 1, static_cast<GXTevRegID>(0));
        _GXSetAlphaCompare(static_cast<GXCompare>(7), 0, static_cast<GXAlphaOp>(0), static_cast<GXCompare>(7), 0);
        GXSetZMode(static_cast<GXBool>(1), static_cast<GXCompare>(3), static_cast<GXBool>(0));
        GXSetChanAmbColor(static_cast<GXChannelID>(0), *reinterpret_cast<_GXColor*>(&color));
        GXSetChanMatColor(static_cast<GXChannelID>(0), *reinterpret_cast<_GXColor*>(&color));
        RenderShape(reinterpret_cast<FS_tagOAN3_SHAPE*>(PtrAt(this, 0x6010)), *reinterpret_cast<Vec2d*>(&origin), FLOAT_8032fd6c);
    }
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
