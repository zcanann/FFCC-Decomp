#include "ffcc/FunnyShape.h"
#include "ffcc/gxfunc.h"
#include "types.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

const GXColor kFunnyShapeTextureChanColor = { 0x80, 0x80, 0x80, 0x80 };
const GXColor kFunnyShapeTextureColor = { 0x80, 0x80, 0x80, 0x80 };
const GXColor kFunnyShapeRenderColor = { 0x80, 0x80, 0x80, 0x80 };
static const float kFunnyShapeBoundsMaxInitial = 1000.0f;
static const float kFunnyShapeBoundsMinInitial = -1000.0f;
static const float kFunnyShapeZero = 0.0f;
static const float kFunnyShapeViewportScale = 2.0f;
static const float kFunnyShapeOne = 1.0f;
static const float kFunnyShapeTexCoordDivisor = 4096.0f;
static const float kFunnyShapePaddingScale = 0.5f;
static const float kFunnyShapeNegativeOne = -1.0f;
static const float kFunnyShapeUnusedZero = 0.0f;
static const float kFunnyShapeDefaultOffsetX = 480.0f;
static const float kFunnyShapeDefaultOffsetY = 336.0f;
static const float kFunnyShapeTextureViewportOrigin = 20.0f;
static const float kFunnyShapePi = 3.14f;
static const float kFunnyShapeHalfTurnDegrees = 180.0f;
extern const char sDebugSpinnerText[5] ATTRIBUTE_ALIGN(8);
extern const float kPppHeapUseRateDivisor;

namespace {
static inline u8* Ptr(void* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
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
    return x / 16;
}

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline float RotateShapeX(const u8* entry, u32 xOffset, u32 yOffset, float angle)
{
    float sinA = static_cast<float>(sin(angle));
    float cosA = static_cast<float>(cos(angle));
    float cx = static_cast<float>(Div16Floor(S16At(entry, xOffset)));
    float cy = static_cast<float>(Div16Floor(S16At(entry, yOffset)));
    return cx * cosA - cy * sinA;
}

static inline float RotateShapeY(const u8* entry, u32 xOffset, u32 yOffset, float angle)
{
    float cosA = static_cast<float>(cos(angle));
    float sinA = static_cast<float>(sin(angle));
    float cx = static_cast<float>(Div16Floor(S16At(entry, xOffset)));
    float cy = static_cast<float>(Div16Floor(S16At(entry, yOffset)));
    return cx * sinA + cy * cosA;
}

static inline void WriteVertex(const float* pos, u32 color, const float* tex)
{
    GXWGFifo.f32 = pos[0];
    GXWGFifo.f32 = pos[1];
    GXWGFifo.f32 = pos[2];
    GXWGFifo.u32 = color;
    GXWGFifo.f32 = tex[0];
    GXWGFifo.f32 = tex[1];
}

static inline GXColor ToGXColor(u32 color)
{
    GXColor out;
    memcpy(&out, &color, sizeof(out));
    return out;
}

static inline void* AnimData(CFunnyShape* self)
{
    return self->m_anm.anmData;
}

static inline u32 ShapeFlags(CFunnyShape* self)
{
    return self->m_displayCurrent.flags;
}

static inline s16 ShapeCount(CFunnyShape* self)
{
    return self->m_displayCurrent.unk28;
}

static inline s16 ShapeRange(CFunnyShape* self)
{
    return self->m_displayCurrent.unk2A;
}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 540b
 * EN Address: 0x8005f81c
 * EN Size: 628b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFunnyShape::SetDefaultStage()
{
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
#pragma push
#pragma opt_common_subs off
void CFunnyShape::RenderShape(FS_tagOAN3_SHAPE* shape, Vec2d offset, float angle)
{
    const u8* shapeData = reinterpret_cast<const u8*>(shape);
    const float* offsetXY = reinterpret_cast<const float*>(&offset);
    s32 packedStride = 0;
    s32 rotatedStride = 0;

    for (s32 i = 0; i < *reinterpret_cast<const s16*>(shapeData + 2); i++) {
        u32 color;
        float tex[4][2];
        float pos[4][3];
        float u0;
        float v0;
        float u1;
        float v1;

        if ((*reinterpret_cast<const u16*>(shapeData) & 8) != 0) {
            const u8* entry = (shapeData + 0x10) + rotatedStride;
            const u8 texIndex = entry[0x28];
            const s8 numTex = m_textureCount;
            float minX = kFunnyShapeBoundsMaxInitial;
            float maxX = kFunnyShapeBoundsMinInitial;
            float minY = minX;
            float maxY = maxX;
            if ((s32)numTex > (s32)texIndex) {
                GXLoadTexObj(reinterpret_cast<GXTexObj*>(m_texObjData[texIndex]), GX_TEXMAP0);
            }

            const u8 blendMode = *reinterpret_cast<const u8*>(entry + 0xC);
            if (blendMode == 0x48) {
                _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_COPY);
            } else if (blendMode == 0x42) {
                _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_COPY);
            } else if (blendMode == 0x88) {
                _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
            }

            if ((ShapeFlags(this) & 0x100) == 0) {
                angle = kFunnyShapeZero;
            }

            const float rx0 = RotateShapeX(entry, 0x10, 0x12, angle);
            const float ry0 = RotateShapeY(entry, 0x10, 0x12, angle);
            const float rx1 = RotateShapeX(entry, 0x14, 0x16, angle);
            const float ry1 = RotateShapeY(entry, 0x14, 0x16, angle);
            const float rx2 = RotateShapeX(entry, 0x18, 0x1A, angle);
            const float ry2 = RotateShapeY(entry, 0x18, 0x1A, angle);
            const float rx3 = RotateShapeX(entry, 0x1C, 0x1E, angle);
            const float ry3 = RotateShapeY(entry, 0x1C, 0x1E, angle);

            if (minX > rx0) {
                minX = rx0;
            }
            if (minX > rx1) {
                minX = rx1;
            }
            if (minX > rx2) {
                minX = rx2;
            }
            if (minX > rx3) {
                minX = rx3;
            }
            if (minY > ry0) {
                minY = ry0;
            }
            if (minY > ry1) {
                minY = ry1;
            }
            if (minY > ry2) {
                minY = ry2;
            }
            if (minY > ry3) {
                minY = ry3;
            }

            if (maxX < rx0) {
                maxX = rx0;
            }
            if (maxX < rx1) {
                maxX = rx1;
            }
            if (maxX < rx2) {
                maxX = rx2;
            }
            if (maxX < rx3) {
                maxX = rx3;
            }
            if (maxY < ry0) {
                maxY = ry0;
            }
            if (maxY < ry1) {
                maxY = ry1;
            }
            if (maxY < ry2) {
                maxY = ry2;
            }
            if (maxY < ry3) {
                maxY = ry3;
            }

            const float viewportScale = kFunnyShapeViewportScale;
            const float viewportW = viewportScale * (maxX - minX);
            const float viewportH = viewportScale * (maxY - minY);
            GXSetViewport(viewportScale * minX + offsetXY[0], viewportScale * minY + offsetXY[1], viewportW,
                          viewportH, kFunnyShapeZero, kFunnyShapeOne);

            const u16 texX = S16At(entry, 0x20);
            const s16 texY = S16At(entry, 0x22);
            const u16 texW = S16At(entry, 0x24);
            const u16 texH = S16At(entry, 0x26);
            u0 = static_cast<float>(texX) / kFunnyShapeTexCoordDivisor;
            v0 = kFunnyShapeOne - static_cast<float>(texY) / kFunnyShapeTexCoordDivisor;
            u1 = u0 + static_cast<float>(texW) / kFunnyShapeTexCoordDivisor;
            v1 = v0 - static_cast<float>(texH) / kFunnyShapeTexCoordDivisor;

            const float padScale = kFunnyShapePaddingScale;
            const float padW = viewportW * padScale * padScale;
            const float padH = viewportH * padScale * padScale;
            const float viewMaxX = maxX - padW;
            const float viewMaxY = maxY - padH;
            const float invPadH = kFunnyShapeOne / padH;
            const float invPadW = -(kFunnyShapeOne / padW);

            pos[0][2] = kFunnyShapeZero;
            pos[1][2] = kFunnyShapeZero;
            pos[2][2] = kFunnyShapeZero;
            pos[3][2] = kFunnyShapeZero;
            pos[0][0] = invPadW * (rx0 - viewMaxX);
            pos[1][0] = invPadW * (rx1 - viewMaxX);
            pos[2][0] = invPadW * (rx3 - viewMaxX);
            pos[3][0] = invPadW * (rx2 - viewMaxX);
            pos[0][1] = invPadH * (ry0 - viewMaxY);
            pos[1][1] = invPadH * (ry1 - viewMaxY);
            pos[2][1] = invPadH * (ry3 - viewMaxY);
            pos[3][1] = invPadH * (ry2 - viewMaxY);
            memcpy(&color, entry + 0x8, sizeof(color));
            *reinterpret_cast<GXColor*>(&color) = *reinterpret_cast<const GXColor*>(entry + 0x8);
        } else {
            const u8* entry = shapeData + 0x10 + packedStride;
            const u8 texIndex = entry[0x20];
            const s8 numTex = m_textureCount;
            if ((s32)numTex > (s32)texIndex) {
                GXLoadTexObj(reinterpret_cast<GXTexObj*>(m_texObjData[texIndex]), GX_TEXMAP0);
            }

            const u8 blendMode = *reinterpret_cast<const u8*>(entry + 0xC);
            if (blendMode == 0x48) {
                _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_COPY);
            } else if (blendMode == 0x42) {
                _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_COPY);
            } else if (blendMode == 0x88) {
                _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
            }

            const u32 x0 = Div16Floor(S16At(entry, 0x10));
            const s32 y0 = Div16Floor(S16At(entry, 0x12));
            const s32 x1 = Div16Floor(S16At(entry, 0x14));
            const s32 y1 = Div16Floor(S16At(entry, 0x16));
            GXSetViewport(offsetXY[0] + static_cast<float>(x0 * 2), offsetXY[1] + static_cast<float>(y0 * 2),
                          static_cast<float>((x1 - x0) * 2), static_cast<float>((y1 - y0) * 2),
                          kFunnyShapeZero, kFunnyShapeOne);

            const s16 texX = S16At(entry, 0x18);
            const s16 texY = S16At(entry, 0x1A);
            const s16 texW = S16At(entry, 0x1C);
            const s16 texH = S16At(entry, 0x1E);
            u0 = static_cast<float>(texX) / kFunnyShapeTexCoordDivisor;
            v0 = kFunnyShapeOne - static_cast<float>(texY) / kFunnyShapeTexCoordDivisor;
            u1 = u0 + static_cast<float>(texW) / kFunnyShapeTexCoordDivisor;
            v1 = v0 - static_cast<float>(texH) / kFunnyShapeTexCoordDivisor;

            pos[0][0] = kFunnyShapeNegativeOne;
            pos[0][1] = kFunnyShapeOne;
            pos[0][2] = kFunnyShapeZero;
            pos[1][0] = kFunnyShapeOne;
            pos[1][1] = kFunnyShapeOne;
            pos[1][2] = kFunnyShapeZero;
            pos[2][0] = kFunnyShapeOne;
            pos[2][1] = kFunnyShapeNegativeOne;
            pos[2][2] = kFunnyShapeZero;
            pos[3][0] = kFunnyShapeNegativeOne;
            pos[3][1] = kFunnyShapeNegativeOne;
            pos[3][2] = kFunnyShapeZero;
            memcpy(&color, entry + 0x8, sizeof(color));
            *reinterpret_cast<GXColor*>(&color) = *reinterpret_cast<const GXColor*>(entry + 0x8);
        }

        tex[0][0] = u0;
        tex[0][1] = v0;
        tex[1][0] = u1;
        tex[1][1] = v0;
        tex[2][0] = u1;
        tex[2][1] = v1;
        tex[3][0] = u0;
        tex[3][1] = v1;

        DCStoreRange(&color, 4);
        GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 4);
        WriteVertex(pos[0], color, tex[0]);
        WriteVertex(pos[1], color, tex[1]);
        WriteVertex(pos[2], color, tex[2]);
        WriteVertex(pos[3], color, tex[3]);

        packedStride += 0x24;
        rotatedStride += 0x2C;
    }
}
#pragma pop

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFunnyShape::ClearShapeData()
{
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CFunnyShape::Create()
{
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
    m_textureCount = 0;
    CFunnyShape* iter = this;
    for (s32 i = 0; i < 0x10; i++) {
        if (iter->m_textureData[0] != 0) {
            delete[] static_cast<u8*>(iter->m_textureData[0]);
            iter->m_textureData[0] = 0;
        }

        if (iter->m_texObjData[0] != 0) {
            delete static_cast<GXTexObj*>(iter->m_texObjData[0]);
            iter->m_texObjData[0] = 0;
        }

        if (iter->m_textureHeaders[0] != 0) {
            delete iter->m_textureHeaders[0];
            iter->m_textureHeaders[0] = 0;
        }
        iter = reinterpret_cast<CFunnyShape*>(Ptr(iter, 4));
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
    if (m_anm.anmData != 0) {
        delete[] static_cast<u8*>(m_anm.anmData);
        m_anm.anmData = 0;
    }

    memset(this, 0, sizeof(CFunnyShapeAnmWork));
    memset(&m_anm, 0, sizeof(OSFS_ANM_ST));
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
    if ((m_textureCount == 0) || (m_meshData == 0)) {
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
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_SRCCLR, GX_LO_COPY);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(m_texObjData[0]), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXColor color = kFunnyShapeRenderColor;
    GXSetChanAmbColor(GX_COLOR0, color);
    GXSetChanMatColor(GX_COLOR0, color);

    Vec2d offsetCopy;
    offsetCopy.x = kFunnyShapeDefaultOffsetX;
    offsetCopy.y = kFunnyShapeDefaultOffsetY;
    FS_tagOAN3_SHAPE* shape = reinterpret_cast<FS_tagOAN3_SHAPE*>(m_meshData);
    RenderShape(shape, offsetCopy, 0.0f);
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
    if (m_textureCount == 0) {
        return;
    }

    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXColor chanColor = kFunnyShapeTextureChanColor;
    GXSetChanAmbColor(GX_COLOR0, chanColor);
    GXColor matColor = chanColor;
    GXSetChanMatColor(GX_COLOR0, matColor);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXColor color = kFunnyShapeTextureColor;
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_SRCCLR, GX_LO_COPY);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(m_texObjData[0]), GX_TEXMAP0);

    const s16 width = m_textureHeaders[0]->width;
    const s16 height = m_textureHeaders[0]->height;
    GXSetViewport(LoadFloat(kFunnyShapeTextureViewportOrigin), LoadFloat(kFunnyShapeTextureViewportOrigin),
                  static_cast<float>(width), static_cast<float>(height), kFunnyShapeZero, kFunnyShapeOne);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 4);
    const u32 colorWord = *reinterpret_cast<u32*>(&color);
    float negOne = kFunnyShapeNegativeOne;
    float one = kFunnyShapeOne;
    float zero = kFunnyShapeZero;
    GXWGFifo.f32 = negOne;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = zero;
    GXWGFifo.u32 = colorWord;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = zero;
    GXWGFifo.u32 = colorWord;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = negOne;
    GXWGFifo.f32 = zero;
    GXWGFifo.u32 = colorWord;
    GXWGFifo.f32 = one;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = negOne;
    GXWGFifo.f32 = negOne;
    GXWGFifo.f32 = zero;
    GXWGFifo.u32 = colorWord;
    GXWGFifo.f32 = zero;
    GXWGFifo.f32 = zero;
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
    if ((m_textureCount == 0) || (AnimData(this) == 0)) {
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
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_SRCCLR, GX_LO_COPY);
    GXLoadTexObj(reinterpret_cast<GXTexObj*>(m_texObjData[0]), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    GXColor color = kFunnyShapeRenderColor;
    GXSetChanAmbColor(GX_COLOR0, color);
    GXSetChanMatColor(GX_COLOR0, color);

    CFunnyShapeAnmWork* work;
    s32 count;
    if ((ShapeFlags(this) & 0x80) != 0) {
        count = ShapeCount(this);
    } else {
        count = 1;
    }

    work = m_anmWork;
    const float baseX = 320.0f;
    const float baseY = 224.0f;

    for (s32 i = 0; i < count; i++) {
        Vec2d posCopy;
        posCopy.x = baseX + work->x;
        posCopy.y = baseY + work->y;

        u8* animData = reinterpret_cast<u8*>(AnimData(this));
        s16 frame = work->frame;
        FS_tagOAN3_SHAPE* shape = reinterpret_cast<FS_tagOAN3_SHAPE*>(animData + *reinterpret_cast<u16*>(animData + 0x10 + frame * 8));
        RenderShape(shape, posCopy, work->angle);
        work++;
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
    if ((m_textureCount == 0) || (AnimData(this) == 0)) {
        return;
    }

    CFunnyShapeAnmWork* work = m_anmWork;
    const bool noSpread = ((ShapeFlags(this) & 0x80) == 0);
    for (s32 i = 0; i < ShapeCount(this); i++) {
        work->delay = static_cast<s16>(work->delay - 0x200);
        if (work->delay <= 0) {
            work->frame = static_cast<s16>(work->frame + 1);
            if (work->frame >= *reinterpret_cast<s16*>(reinterpret_cast<u8*>(AnimData(this)) + 6)) {
                work->frame = 0;

                s32 r = rand();
                work->x = static_cast<float>(r % ShapeRange(this));

                r = rand();
                work->y = static_cast<float>(r % ShapeRange(this));
                work->z = kFunnyShapeZero;
                work->delay = 0x200;
                work->viewportY = kFunnyShapeZero;
                work->viewportX = kFunnyShapeZero;

                r = rand();
                work->angle = static_cast<float>(r - (r / 0x168) * 0x168);
                work->angle = (kFunnyShapePi * work->angle) / kFunnyShapeHalfTurnDegrees;

                r = rand();
                if ((r % 2) != 0) {
                    work->x *= kFunnyShapeNegativeOne;
                }

                r = rand();
                if ((r % 2) != 0) {
                    work->y *= kFunnyShapeNegativeOne;
                }

                if (noSpread != 0) {
                    work->frame = 0;
                    work->y = kFunnyShapeZero;
                    work->x = kFunnyShapeZero;
                }
            }

            const u8* frameData = reinterpret_cast<const u8*>(AnimData(this)) + 0x10;
            s16 frame = work->frame;
            frameData += frame * 8;
            work->delay = *reinterpret_cast<const s16*>(frameData + 2);
        }

        if (noSpread != 0) {
            return;
        }

        work++;
    }
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
    const bool noSpread = (ShapeFlags(this) & 0x80) == 0;
    CFunnyShapeAnmWork* work = m_anmWork;

    for (s32 i = 0; i < 0x200; i++) {
        work->index = i;
        work->animData = AnimData(this);

        s32 r = rand();
        work->x = static_cast<float>(r - (r / ShapeRange(this)) * ShapeRange(this));

        r = rand();
        work->y = static_cast<float>(r - (r / ShapeRange(this)) * ShapeRange(this));
        work->z = kFunnyShapeZero;

        r = rand();
        const s16 shapeCount = *reinterpret_cast<s16*>(reinterpret_cast<u8*>(AnimData(this)) + 6);
        const s32 shapeDiv = r / shapeCount;
        work->frame = static_cast<s16>(r - shapeDiv * shapeCount);
        work->delay = 0x200;
        work->viewportY = kFunnyShapeZero;
        work->viewportX = kFunnyShapeZero;

        r = rand();
        work->angle = static_cast<float>(r % 0x168);
        work->angle = (kFunnyShapePi * work->angle) / kFunnyShapeHalfTurnDegrees;

        r = rand();
        if ((r % 2) != 0) {
            work->x *= kFunnyShapeNegativeOne;
        }

        r = rand();
        if ((r % 2) != 0) {
            work->y *= kFunnyShapeNegativeOne;
        }

        if (noSpread != 0) {
            work->frame = 0;
            work->y = kFunnyShapeZero;
            work->x = kFunnyShapeZero;
        }

        work++;
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
CFunnyShape::~CFunnyShape()
{
    if (m_meshData != 0) {
        delete[] static_cast<u8*>(m_meshData);
        m_meshData = 0;
    }

    if (m_anm.anmData != 0) {
        delete[] static_cast<u8*>(m_anm.anmData);
        m_anm.anmData = 0;
    }

    CFunnyShape* iter = this;
    s32 i = 0;
    do {
        if (iter->m_textureData[0] != 0) {
            delete[] static_cast<u8*>(iter->m_textureData[0]);
            iter->m_textureData[0] = 0;
        }

        if (iter->m_texObjData[0] != 0) {
            delete static_cast<GXTexObj*>(iter->m_texObjData[0]);
            iter->m_texObjData[0] = 0;
        }

        if (iter->m_textureHeaders[0] != 0) {
            delete iter->m_textureHeaders[0];
            iter->m_textureHeaders[0] = 0;
        }

        i++;
        iter = reinterpret_cast<CFunnyShape*>(Ptr(iter, 4));
    } while (i < 0x10);
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
    m_meshData = 0;
    memset(this, 0, sizeof(m_anmWork));
    memset(&m_anm, 0, sizeof(OSFS_ANM_ST));
    memset(&m_shape, 0, sizeof(OSFS_SHAPE_ST));
    memset(&m_displayCurrent, 0, sizeof(FS_DISPLAY_STATUS));

    CFunnyShape* p = this;
    for (s32 i = 2; i != 0; i--) {
        p->m_textureData[0] = 0;
        p->m_texObjData[0] = 0;
        p->m_textureHeaders[0] = 0;
        p->m_textureData[1] = 0;
        p->m_texObjData[1] = 0;
        p->m_textureHeaders[1] = 0;
        p->m_textureData[2] = 0;
        p->m_texObjData[2] = 0;
        p->m_textureHeaders[2] = 0;
        p->m_textureData[3] = 0;
        p->m_texObjData[3] = 0;
        p->m_textureHeaders[3] = 0;
        p->m_textureData[4] = 0;
        p->m_texObjData[4] = 0;
        p->m_textureHeaders[4] = 0;
        p->m_textureData[5] = 0;
        p->m_texObjData[5] = 0;
        p->m_textureHeaders[5] = 0;
        p->m_textureData[6] = 0;
        p->m_texObjData[6] = 0;
        p->m_textureHeaders[6] = 0;
        p->m_textureData[7] = 0;
        p->m_texObjData[7] = 0;
        p->m_textureHeaders[7] = 0;
        p = reinterpret_cast<CFunnyShape*>(Ptr(p, 0x20));
    }

    m_textureCount = 0;
}

extern const char sDebugSpinnerText[5] ATTRIBUTE_ALIGN(8) = "|/-\\";
extern const float kPppHeapUseRateDivisor = 100.0f;
