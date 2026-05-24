#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include "ffcc/p_camera.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
extern "C" {
extern const unsigned int kMaterialEditorDefaultColorRgba = 0xFFFFFFFF;
extern const float kMaterialEditorControlMaxInit = 10000.0f;
extern const float kMaterialEditorControlMinInit = -10000.0f;
extern const char sMaterialEditorSpinnerText[5] = "|/-\\";
}
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include <string.h>

extern "C" void createViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void destroyViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void calcViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void drawViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern const char __RTTI__8CManager_8032E648[];
extern const char __RTTI__8CProcess_8032E650[];
extern "C" const char s_CMaterialEditorPcsViewer[] = "CMaterialEditorPcs(VIEWER)";
extern "C" const char s_CMaterialEditorPcs[] = "CMaterialEditorPcs";
extern "C" const char sMaterialEditorCManagerName[] = "CManager";
extern "C" const char sMaterialEditorCProcessName[] = "CProcess";
extern "C" const char s_MaterialEditorFmt[] = "MaterialEditor [%c]";

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

unsigned int CMaterialEditorPcs::m_table_desc0[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__18CMaterialEditorPcsFv)};
unsigned int CMaterialEditorPcs::m_table_desc1[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__18CMaterialEditorPcsFv)};
unsigned int CMaterialEditorPcs::m_table_desc2[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__18CMaterialEditorPcsFv)};
unsigned int CMaterialEditorPcs::m_table_desc3[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__18CMaterialEditorPcsFv)};

unsigned int CMaterialEditorPcs::m_table[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CMaterialEditorPcsViewer)),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(createViewer__18CMaterialEditorPcsFv),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(destroyViewer__18CMaterialEditorPcsFv),
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(calcViewer__18CMaterialEditorPcsFv),
    0x20,
    0,
    0,
    0xFFFFFFFF,
    reinterpret_cast<unsigned int>(drawViewer__18CMaterialEditorPcsFv),
    0x41,
    1
};
unsigned int s_CMaterialEditorPcsTablePad0[3] = {reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E648)), 0, 0};
unsigned int s_CMaterialEditorPcsTablePad1[5] = {reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E648)), 0, reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CProcess_8032E650)), 0, 0};
u8 gMaterialEditorPcsGuard[0xC];
CMaterialEditorPcs MaterialEditorPcs;


extern "C" const double DOUBLE_8032FCC0 = 1.0;
extern "C" const double DOUBLE_8032FCD0;
extern "C" const float FLOAT_8032FCC8 = 1.0f;
extern "C" const float FLOAT_8032FCD8;
extern "C" float FLOAT_8032FCDC;

static inline void WriteU32(void* base, unsigned int offset, unsigned int value) {
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

static inline void WriteF32(void* base, unsigned int offset, float value) {
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline double S16ToDouble(s16 value)
{
    union {
        unsigned long long bits;
        double value;
    } conv;

    conv.bits = 0x4330000000000000ULL | static_cast<unsigned int>(value ^ 0x80000000U);
    return conv.value - DOUBLE_8032FCD0;
}

/*
 * --INFO--
 * PAL Address: 0x8004b21c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::CreateBoundaryBox(Vec& minPos, Vec& maxPos, long count, const Vec* points)
{
    f32 maxInit = LoadFloat(kMaterialEditorControlMaxInit);
    minPos.x = minPos.y = minPos.z = maxInit;
    f32 minInit = LoadFloat(kMaterialEditorControlMinInit);
    maxPos.x = maxPos.y = maxPos.z = minInit;

    for (; count > 0; count--, points++) {
        const Vec& point = *points;
        if (minPos.x > point.x) {
            minPos.x = point.x;
        }
        if (minPos.y > point.y) {
            minPos.y = point.y;
        }
        if (minPos.z > point.z) {
            minPos.z = point.z;
        }
        if (maxPos.x < point.x) {
            maxPos.x = point.x;
        }
        if (maxPos.y < point.y) {
            maxPos.y = point.y;
        }
        if (maxPos.z < point.z) {
            maxPos.z = point.z;
        }
    }
}
/*
 * --INFO--
 * PAL Address: 0x8004b2cc
 * PAL Size: 3068b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct MaterialEditorPolygon {
    u16 flags;
    u16 blendMode;
    u32 _04;
    u16 index0;
    u16 index1;
    u16 index2;
    u16 index3;
    u16 _10;
    u16 _12;
    u16 _14;
    u16 _16;
    u8 _18;
    char textureMarker;
    u8 _1a[4];
    s16 textureIndex;
    s16 u0;
    s16 v0;
    s16 u1;
    s16 v1;
    s16 u2;
    s16 v2;
    s16 u3;
    s16 v3;
    u8 _30[0x20];
    float texCoord[4][2];
};

void CMaterialEditorPcs::drawViewer()
{
    static char* q;
    static int color;

    if (*reinterpret_cast<char*>(&color) == 0) {
        q = const_cast<char*>(sMaterialEditorSpinnerText);
        *reinterpret_cast<char*>(&color) = 1;
    }

    static int pFan = 0;
    pFan++;
    char fan = q[(pFan >> 4) % 4];
    Graphic.Printf(const_cast<char*>(s_MaterialEditorFmt), (int)fan);

    if (m_displayTextureEnabled != 0) {
        return;
    }

    ZLIST* zlist = &m_zlist1;
    _ZLISTITEM* it = zlist->m_root.m_previous;
    while (it != 0) {
        int* listData = reinterpret_cast<int*>(zlist->GetDataNext(&it));
        int model = *listData;

        GXSetArray(GX_VA_POS, *reinterpret_cast<void**>(model + 0x10), 0xC);
        GXSetArray(GX_VA_NRM, *reinterpret_cast<void**>(model + 0x14), 0xC);
        GXSetNumChans(1);
        GXClearVtxDesc();
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTevStages(1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        GXColor ambColor;
        *reinterpret_cast<u32*>(&ambColor) = kMaterialEditorDefaultColorRgba;
        GXColor matColor;
        *reinterpret_cast<u32*>(&matColor) = kMaterialEditorDefaultColorRgba;
        GXSetChanAmbColor(GX_COLOR0, ambColor);
        GXSetChanMatColor(GX_COLOR0, matColor);

        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

        for (int pass = 0; pass < 2; pass++) {
            unsigned char* polygons = reinterpret_cast<unsigned char*>(reinterpret_cast<RSDITEM*>(model)->ptr18);

            for (u32 polyIndex = 0, polygonOffset = 0; polyIndex < reinterpret_cast<RSDITEM*>(model)->countC;
                 polyIndex++, polygonOffset += sizeof(MaterialEditorPolygon)) {
                MaterialEditorPolygon* polygon = reinterpret_cast<MaterialEditorPolygon*>(polygons + polygonOffset);

                if ((polygon->flags & 0x200) == 0) {
                    GXSetCullMode(GX_CULL_BACK);
                } else {
                    GXSetCullMode(GX_CULL_NONE);
                }

                if (pass == 1) {
                    if ((polygon->flags & 0x400) == 0) {
                        continue;
                    }

                    u16 blendMode = polygon->blendMode;
                    int blend = 1;
                    int srcFactor = 1;
                    int dstFactor = 1;
                    int src = blendMode & 3;
                    int dst = (blendMode >> 2) & 3;

                    if ((src == 0) && (dst == 0)) {
                        srcFactor = 4;
                        dstFactor = 5;
                    } else if ((src == 0) && (dst == 2)) {
                        srcFactor = 4;
                        dstFactor = 1;
                    } else if ((src == 2) && (dst == 0)) {
                        blend = 3;
                        srcFactor = 1;
                        dstFactor = 1;
                    }

                    GXSetZCompLoc(GX_FALSE);
                    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
                    _GXSetBlendMode(static_cast<_GXBlendMode>(blend), static_cast<_GXBlendFactor>(srcFactor),
                                    static_cast<_GXBlendFactor>(dstFactor), GX_LO_COPY);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXSetCullMode(GX_CULL_NONE);
                } else if (pass == 0) {
                    if ((polygon->flags & 0x400) != 0) {
                        continue;
                    }

                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                    _GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_OR);
                }

                switch (polygon->textureMarker) {
                case 'H':
                if (polygon->textureIndex < static_cast<s16>(m_loadedTextureCount)) {
                    s16* textureHeader = m_textureHeader[polygon->textureIndex];
                    float scaleU = static_cast<float>(DOUBLE_8032FCC0 / S16ToDouble(textureHeader[2]));
                    float scaleV = static_cast<float>(DOUBLE_8032FCC0 / S16ToDouble(textureHeader[3]));

                    polygon->texCoord[0][0] = scaleU * static_cast<float>(polygon->u0);
                    if (polygon->u0 < 0) {
                        polygon->texCoord[0][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[1][0] = scaleU * static_cast<float>(polygon->u1);
                    if (polygon->u1 < 0) {
                        polygon->texCoord[1][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[2][0] = scaleU * static_cast<float>(polygon->u2);
                    if (polygon->u2 < 0) {
                        polygon->texCoord[2][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[3][0] = scaleU * static_cast<float>(polygon->u3);
                    if (polygon->u3 < 0) {
                        polygon->texCoord[3][0] += FLOAT_8032FCC8;
                    }

                    if (polygon->v0 < 0) {
                        polygon->v0 = -polygon->v0;
                    }
                    if (polygon->v1 < 0) {
                        polygon->v1 = -polygon->v1;
                    }
                    if (polygon->v2 < 0) {
                        polygon->v2 = -polygon->v2;
                    }
                    if (polygon->v3 < 0) {
                        polygon->v3 = -polygon->v3;
                    }

                    polygon->texCoord[0][1] = -(scaleV * static_cast<float>(polygon->v0) - FLOAT_8032FCC8);
                    polygon->texCoord[1][1] = -(scaleV * static_cast<float>(polygon->v1) - FLOAT_8032FCC8);
                    polygon->texCoord[2][1] = -(scaleV * static_cast<float>(polygon->v2) - FLOAT_8032FCC8);
                    polygon->texCoord[3][1] = -(scaleV * static_cast<float>(polygon->v3) - FLOAT_8032FCC8);
                    DCStoreRange(polygon, sizeof(MaterialEditorPolygon));

                    if (textureHeader[1] == 0x20) {
                        GXSetNumTevStages(1);
                        GXSetNumTexGens(1);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP0);
                        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
                    }

                    if ((textureHeader[1] == 4) || (textureHeader[1] == 8)) {
                        GXColor red;
                        GXColor blue;
                        red.r = 0xff;
                        red.g = 0xff;
                        red.b = 0;
                        red.a = 0;
                        blue.r = 0;
                        blue.g = 0;
                        blue.b = 0xff;
                        blue.a = 0xff;

                        GXSetNumTevStages(3);
                        GXSetNumTexGens(1);
                        GXSetTevColor(GX_TEVREG2, red);
                        GXSetTevColor(GX_TEVPREV, blue);
                        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetTevDirect(GX_TEVSTAGE0);
                        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
                        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
                        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                        GXSetTevDirect(GX_TEVSTAGE1);
                        _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
                        _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                        _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
                        _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
                        GXSetTevDirect(GX_TEVSTAGE2);
                        _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
                        _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
                        _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
                        _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);
                        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
                        _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                        GXInitTexObjTlut(m_texObj[polygon->textureIndex], 0);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP0);
                        GXInitTexObjTlut(m_texObj[polygon->textureIndex], 1);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP1);
                        GXLoadTlut(m_tlutObj0[polygon->textureIndex], 0);
                        GXLoadTlut(m_tlutObj1[polygon->textureIndex], 1);
                    }
                }
                }

                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetArray(GX_VA_CLR0, polygon->_30, 4);
                GXSetArray(GX_VA_TEX0, polygon->texCoord, 8);

                u32 vertexIndex[5];
                u32 quadIndex2;
                u32 quadIndex3;
                u32 quadColorIndex;
                u8 vertexCount = 3;
                vertexIndex[4] = polygon->index0;
                quadIndex2 = polygon->index1;
                quadIndex3 = polygon->index2;
                vertexIndex[0] = 0;
                vertexIndex[1] = 1;
                vertexIndex[2] = 2;

                if ((polygon->flags & 0xf) == 0) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
                }
                if ((polygon->flags & 0xf) == 1) {
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    vertexCount = 4;
                    quadIndex3 = polygon->index3;
                    quadColorIndex = polygon->index2;
                    vertexIndex[2] = 3;
                    vertexIndex[3] = 2;
                }

                for (u8 i = 0; i < vertexCount; i++) {
                    u32 index = (&vertexIndex[4])[i];
                    GXWGFifo.u16 = static_cast<u16>(index);
                    GXWGFifo.u16 = static_cast<u16>(index);
                    GXWGFifo.u8 = static_cast<u8>(vertexIndex[i]);
                    GXWGFifo.u16 = static_cast<u16>(vertexIndex[i]);
                }
            }
        }
    }
}
/*
 * --INFO--
 * PAL Address: 0x8004bec8
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::calcViewer()
{
    struct ViewerSRT {
        float transX;
        float transY;
        float transZ;
        float rotX;
        float rotY;
        float rotZ;
        float scaleX;
        float scaleY;
        float scaleZ;
    };

    Mtx cameraMatrix;
    ViewerSRT srt;
    Mtx scaleMatrix;
    float rotationValue;
    float one;

    USBPcs.mccReadData();

    int usbDone = m_usbStream.IsUSBStreamDataDone();
    if (usbDone != 0) {
        SetUSBData();
        m_usbStream.SetUSBStreamDataDone();
    }

    one = LoadFloat(FLOAT_8032FCC8);
    rotationValue = LoadFloat(FLOAT_8032FCD8);
    srt.transZ = rotationValue;
    srt.transY = rotationValue;
    srt.transX = rotationValue;
    srt.rotZ = rotationValue;
    srt.rotY = rotationValue;
    srt.rotX = rotationValue;
    srt.scaleZ = one;
    srt.scaleY = one;
    srt.scaleX = one;
    srt.transX = field268_0x15c.x;
    srt.transY = field268_0x15c.y;
    srt.transZ = -field268_0x15c.z;
    CameraPcs.SetViewerSRT(reinterpret_cast<const SRT*>(&srt));

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMatrix);

    m_unkMatrix.value[0][0] = field_0x12c;
    m_unkMatrix.value[0][1] = field_0x130;
    m_unkMatrix.value[0][2] = field_0x134;
    m_unkMatrix.value[0][3] = field_0x138;
    m_unkMatrix.value[1][0] = field_0x13c;
    m_unkMatrix.value[1][1] = field_0x140;
    m_unkMatrix.value[1][2] = field_0x144;
    m_unkMatrix.value[1][3] = field_0x148;
    m_unkMatrix.value[2][0] = field_0x14c;
    m_unkMatrix.value[2][1] = field_0x150;
    m_unkMatrix.value[2][2] = field_0x154;
    m_unkMatrix.value[2][3] = field_0x158;

    PSMTXTranspose(m_unkMatrix.value, m_unkMatrix.value);

    m_unkMatrix.value[0][1] = -m_unkMatrix.value[0][1];
    m_unkMatrix.value[1][1] = -m_unkMatrix.value[1][1];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][0] = -m_unkMatrix.value[2][0];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][2] = -m_unkMatrix.value[2][2];

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[1][1] = FLOAT_8032FCDC;
    PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[2][2] = FLOAT_8032FCDC;
    PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);

    PSMTXConcat(cameraMatrix, m_unkMatrix.value, cameraMatrix);
    GXLoadPosMtxImm(cameraMatrix, 0);
}
/*
 * --INFO--
 * PAL Address: 0x8004c098
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::ClearTextureData()
{
    unsigned int i = 0;

    m_loadedTextureCount = 0;

    do {
        MemFree(m_textureData[i]);
        MemFree(m_tlutData[i]);
        MemFree(m_texObj[i]);
        MemFree(m_tlutObj0[i]);
        MemFree(m_tlutObj1[i]);
        MemFree(m_textureHeader[i]);
        i += 1;
    } while (i < 0x10);
}
/*
 * --INFO--
 * PAL Address: 0x8004c138
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::destroyViewer()
{
    GXColor clear;

    USBPcs.IsBigAlloc(0);

    clear.r = 0;
    clear.g = 0;
    clear.b = 0;
    clear.a = 0;
    GXSetCopyClear(clear, 0xffffff);

    m_usbStream.DeleteBuffer();
    MemFree(reinterpret_cast<void*>(m_rsdIndex));
    m_loadedTextureCount = 0;

    unsigned int textureIndex = 0;
    do {
        MemFree(m_textureData[textureIndex]);
        MemFree(m_tlutData[textureIndex]);
        MemFree(m_texObj[textureIndex]);
        MemFree(m_tlutObj0[textureIndex]);
        MemFree(m_tlutObj1[textureIndex]);
        MemFree(m_textureHeader[textureIndex]);
        textureIndex += 1;
    } while (textureIndex < 0x10);

    Memory.DestroyStage(m_stage);
}
/*
 * --INFO--
 * PAL Address: 0x8004c234
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::createViewer()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(
        Memory.CreateStage(0x200000, const_cast<char*>(s_CMaterialEditorPcs), 0));
    GXColor clear;
    float fVar1;

    m_stage = stage;
    USBPcs.IsBigAlloc(1);

    clear.r = 0x40;
    clear.g = 0x40;
    clear.b = 0x40;
    clear.a = 0xff;
    GXSetCopyClear(clear, 0xffffff);

    WriteU32(self, 0x98, 1);
    m_displayTextureEnabled = 0;
    memset(self + 0xec, 0, 0x120);

    fVar1 = LoadFloat(FLOAT_8032FCC8);
    WriteF32(self, 0x128, fVar1);
    WriteF32(self, 0x114, fVar1);
    WriteF32(self, 0x100, fVar1);
    WriteF32(self, 0xec, fVar1);

    PSMTXIdentity(m_unkMatrix.value);
    m_usbStream.CreateBuffer();
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialEditorPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(CMaterialEditorPcs::m_table) + index * sizeof(m_table));
}
/*
 * --INFO--
 * PAL Address: 0x8004c314
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::Quit()
{
    unsigned int textureIndex;
    m_loadedTextureCount = static_cast<s8>(textureIndex = 0);

    do {
        MemFree(m_textureData[textureIndex]);
        MemFree(m_tlutData[textureIndex]);
        MemFree(m_texObj[textureIndex]);
        MemFree(m_tlutObj0[textureIndex]);
        MemFree(m_tlutObj1[textureIndex]);
        MemFree(m_textureHeader[textureIndex]);
        textureIndex += 1;
    } while (textureIndex < 0x10);

    if (m_rsdIndex != 0) {
        MemFree(reinterpret_cast<void*>(m_rsdIndex));
    }
}
/*
 * --INFO--
 * PAL Address: 0x8004c3c4
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::Init()
{
    unsigned char* self;
    int remaining;

    self = reinterpret_cast<unsigned char*>(this);
    self[0x8] = 0x7f;
    self[0x9] = 0x7f;
    self[0xa] = 0x7f;
    unsigned char level = static_cast<unsigned char>(-((__cntlzw(0) >> 5) & 1) & 0x3f);
    self[0xb] = 0xff;
    self[0xc] = level;
    self[0xd] = level;
    self[0xe] = level;
    level = static_cast<unsigned char>(-((__cntlzw(1) >> 5) & 1) & 0x3f);
    self[0xf] = 0xff;
    float zero = FLOAT_8032FCD8;
    float minusOne = FLOAT_8032FCDC;
    float one = FLOAT_8032FCC8;

    *reinterpret_cast<float*>(self + 0x18) = zero;
    *reinterpret_cast<float*>(self + 0x1c) = zero;
    *reinterpret_cast<float*>(self + 0x20) = minusOne;
    self[0x10] = level;
    self[0x11] = level;
    self[0x12] = level;
    level = static_cast<unsigned char>(-((__cntlzw(2) >> 5) & 1) & 0x3f);
    self[0x13] = 0xff;
    *reinterpret_cast<float*>(self + 0x24) = zero;
    *reinterpret_cast<float*>(self + 0x28) = zero;
    *reinterpret_cast<float*>(self + 0x2c) = minusOne;
    self[0x14] = level;
    self[0x15] = level;
    self[0x16] = level;
    self[0x17] = 0xff;
    *reinterpret_cast<float*>(self + 0x30) = zero;
    *reinterpret_cast<float*>(self + 0x34) = zero;
    *reinterpret_cast<float*>(self + 0x38) = minusOne;
    *reinterpret_cast<float*>(self + 0x44) = zero;
    *reinterpret_cast<float*>(self + 0x40) = zero;
    *reinterpret_cast<float*>(self + 0x3c) = zero;
    *reinterpret_cast<float*>(self + 0x50) = zero;
    *reinterpret_cast<float*>(self + 0x4c) = zero;
    *reinterpret_cast<float*>(self + 0x48) = zero;
    *reinterpret_cast<float*>(self + 0x5c) = one;
    *reinterpret_cast<float*>(self + 0x58) = one;
    *reinterpret_cast<float*>(self + 0x54) = one;
    *reinterpret_cast<u32*>(self + 0xbc) = 0;

    remaining = 2;
    while (remaining != 0) {
        *reinterpret_cast<u32*>(self + 0x2bc) = 0;
        *reinterpret_cast<u32*>(self + 0x2fc) = 0;
        *reinterpret_cast<u32*>(self + 0x23c) = 0;
        *reinterpret_cast<u32*>(self + 0x33c) = 0;
        *reinterpret_cast<u32*>(self + 0x37c) = 0;
        *reinterpret_cast<u32*>(self + 0x27c) = 0;
        *reinterpret_cast<u32*>(self + 0x2c0) = 0;
        *reinterpret_cast<u32*>(self + 0x300) = 0;
        *reinterpret_cast<u32*>(self + 0x240) = 0;
        *reinterpret_cast<u32*>(self + 0x340) = 0;
        *reinterpret_cast<u32*>(self + 0x380) = 0;
        *reinterpret_cast<u32*>(self + 0x280) = 0;
        *reinterpret_cast<u32*>(self + 0x2c4) = 0;
        *reinterpret_cast<u32*>(self + 0x304) = 0;
        *reinterpret_cast<u32*>(self + 0x244) = 0;
        *reinterpret_cast<u32*>(self + 0x344) = 0;
        *reinterpret_cast<u32*>(self + 0x384) = 0;
        *reinterpret_cast<u32*>(self + 0x284) = 0;
        *reinterpret_cast<u32*>(self + 0x2c8) = 0;
        *reinterpret_cast<u32*>(self + 0x308) = 0;
        *reinterpret_cast<u32*>(self + 0x248) = 0;
        *reinterpret_cast<u32*>(self + 0x348) = 0;
        *reinterpret_cast<u32*>(self + 0x388) = 0;
        *reinterpret_cast<u32*>(self + 0x288) = 0;
        *reinterpret_cast<u32*>(self + 0x2cc) = 0;
        *reinterpret_cast<u32*>(self + 0x30c) = 0;
        *reinterpret_cast<u32*>(self + 0x24c) = 0;
        *reinterpret_cast<u32*>(self + 0x34c) = 0;
        *reinterpret_cast<u32*>(self + 0x38c) = 0;
        *reinterpret_cast<u32*>(self + 0x28c) = 0;
        *reinterpret_cast<u32*>(self + 0x2d0) = 0;
        *reinterpret_cast<u32*>(self + 0x310) = 0;
        *reinterpret_cast<u32*>(self + 0x250) = 0;
        *reinterpret_cast<u32*>(self + 0x350) = 0;
        *reinterpret_cast<u32*>(self + 0x390) = 0;
        *reinterpret_cast<u32*>(self + 0x290) = 0;
        *reinterpret_cast<u32*>(self + 0x2d4) = 0;
        *reinterpret_cast<u32*>(self + 0x314) = 0;
        *reinterpret_cast<u32*>(self + 0x254) = 0;
        *reinterpret_cast<u32*>(self + 0x354) = 0;
        *reinterpret_cast<u32*>(self + 0x394) = 0;
        *reinterpret_cast<u32*>(self + 0x294) = 0;
        *reinterpret_cast<u32*>(self + 0x2d8) = 0;
        *reinterpret_cast<u32*>(self + 0x318) = 0;
        *reinterpret_cast<u32*>(self + 0x258) = 0;
        *reinterpret_cast<u32*>(self + 0x358) = 0;
        *reinterpret_cast<u32*>(self + 0x398) = 0;
        *reinterpret_cast<u32*>(self + 0x298) = 0;
        self += 0x20;
        remaining--;
    }

    reinterpret_cast<unsigned char*>(this)[0x3bc] = 0;
}
/*
 * --INFO--
 * PAL Address: 0x8004c6a0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialEditorPcs::~CMaterialEditorPcs()
{
}
