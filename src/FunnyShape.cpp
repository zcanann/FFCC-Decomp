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
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::RenderShape(FS_tagOAN3_SHAPE*, Vec2d&, float)
{
	// TODO
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
