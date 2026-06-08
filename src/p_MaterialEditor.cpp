#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include "ffcc/p_camera.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
static const GXColor kMaterialEditorDefaultColorRgba = {0xFF, 0xFF, 0xFF, 0xFF};
static const float kMaterialEditorControlMaxInit = 10000.0f;
static const float kMaterialEditorControlMinInit = -10000.0f;
static const char sMaterialEditorSpinnerText[5] = "|/-\\";
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include <string.h>

extern "C" void createViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void destroyViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void calcViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void drawViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
static const char s_CMaterialEditorPcsViewer[] = "CMaterialEditorPcs(VIEWER)";
static const char s_CMaterialEditorPcs[] = "CMaterialEditorPcs";
static const char sMaterialEditorCManagerName[] = "CManager";
static const char sMaterialEditorCProcessName[] = "CProcess";
static const char s_MaterialEditorFmt[] = "MaterialEditor [%c]";

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

static CProcessTableCallback s_materialEditorTableDescCreateViewer = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__18CMaterialEditorPcsFv)};
static CProcessTableCallback s_materialEditorTableDescDestroyViewer = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__18CMaterialEditorPcsFv)};
static CProcessTableCallback s_materialEditorTableDescCalcViewer = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__18CMaterialEditorPcsFv)};
static CProcessTableCallback s_materialEditorTableDescDrawViewer = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__18CMaterialEditorPcsFv)};
CMaterialEditorPcs MaterialEditorPcs;
static char* q;

CProcessTable CMaterialEditorPcs::m_table = {
    const_cast<char*>(s_CMaterialEditorPcsViewer),
    {
        s_materialEditorTableDescCreateViewer.m_thisOffset,
        s_materialEditorTableDescCreateViewer.m_virtualOffset,
        s_materialEditorTableDescCreateViewer.m_function,
        s_materialEditorTableDescDestroyViewer.m_thisOffset,
        s_materialEditorTableDescDestroyViewer.m_virtualOffset,
        s_materialEditorTableDescDestroyViewer.m_function,
        s_materialEditorTableDescCalcViewer.m_thisOffset,
        s_materialEditorTableDescCalcViewer.m_virtualOffset,
        s_materialEditorTableDescCalcViewer.m_function,
        0x20,
        0,
        s_materialEditorTableDescDrawViewer.m_thisOffset,
        s_materialEditorTableDescDrawViewer.m_virtualOffset,
        s_materialEditorTableDescDrawViewer.m_function,
        0x41,
        1,
    },
};
static const double kMaterialEditorOneF64 = 1.0;
static const float kMaterialEditorOneF = 1.0f;
static const double kMaterialEditorS16ToDoubleBias = 4503601774854144.0;
static const float kMaterialEditorZeroF = 0.0f;
static const float kMaterialEditorNegativeOneF = -1.0f;

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline double LoadDouble(const double& value)
{
    return value;
}

static inline double S16ToDouble(s16 value)
{
    union {
        u32 words[2];
        double value;
    } conv;

    conv.words[0] = 0x43300000;
    conv.words[1] = static_cast<unsigned int>(value ^ 0x80000000U);
    return conv.value - kMaterialEditorS16ToDoubleBias;
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
void CMaterialEditorPcs::drawViewer()
{
    static char initialized;

    if (initialized == 0) {
        q = const_cast<char*>(sMaterialEditorSpinnerText);
        initialized = 1;
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
        RSDLISTITEM* listItem = reinterpret_cast<RSDLISTITEM*>(zlist->GetDataNext(&it));
        RSDITEM* model = listItem->rsdItem;

        GXSetArray(GX_VA_POS, model->ptr10, 0xC);
        GXSetArray(GX_VA_NRM, model->ptr14, 0xC);
        GXSetNumChans(1);
        GXClearVtxDesc();
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTevStages(1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        GXColor ambColor = kMaterialEditorDefaultColorRgba;
        GXColor matColor = kMaterialEditorDefaultColorRgba;
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
            for (u32 polyIndex = 0; polyIndex < model->countC; polyIndex++) {
#define polygon (&static_cast<MaterialEditorPolygon*>(model->ptr18)[polyIndex])
                if ((polygon->flags & 0x200) != 0) {
                    GXSetCullMode(GX_CULL_NONE);
                } else {
                    GXSetCullMode(GX_CULL_BACK);
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

                u16 flags = polygon->flags;
                switch (polygon->textureMarker) {
                case 'H':
                if (static_cast<s16>(m_loadedTextureCount) > polygon->textureIndex) {
                    s16* textureHeader = m_textureHeader[polygon->textureIndex];
                    float scaleU = static_cast<float>(LoadDouble(kMaterialEditorOneF64) / S16ToDouble(textureHeader[2]));
                    float scaleV = static_cast<float>(LoadDouble(kMaterialEditorOneF64) / S16ToDouble(textureHeader[3]));
                    MaterialEditorPolygon* pp = polygon;
                    s16 u = pp->u0;

                    if (u < 0) {
                        pp->texCoord[0][0] =
                            (scaleU * static_cast<float>(S16ToDouble(u))) + LoadFloat(kMaterialEditorOneF);
                    } else {
                        pp->texCoord[0][0] = scaleU * static_cast<float>(S16ToDouble(u));
                    }
                    pp = polygon;
                    u = pp->u1;
                    if (u < 0) {
                        pp->texCoord[1][0] =
                            (scaleU * static_cast<float>(S16ToDouble(u))) + LoadFloat(kMaterialEditorOneF);
                    } else {
                        pp->texCoord[1][0] = scaleU * static_cast<float>(S16ToDouble(u));
                    }
                    pp = polygon;
                    u = pp->u2;
                    if (u < 0) {
                        pp->texCoord[2][0] =
                            (scaleU * static_cast<float>(S16ToDouble(u))) + LoadFloat(kMaterialEditorOneF);
                    } else {
                        pp->texCoord[2][0] = scaleU * static_cast<float>(S16ToDouble(u));
                    }
                    pp = polygon;
                    u = pp->u3;
                    if (u < 0) {
                        pp->texCoord[3][0] =
                            (scaleU * static_cast<float>(S16ToDouble(u))) + LoadFloat(kMaterialEditorOneF);
                    } else {
                        pp->texCoord[3][0] = scaleU * static_cast<float>(S16ToDouble(u));
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

                    pp = polygon;
                    pp->texCoord[0][1] = -(scaleV * static_cast<float>(S16ToDouble(pp->v0)) - LoadFloat(kMaterialEditorOneF));
                    pp = polygon;
                    pp->texCoord[1][1] = -(scaleV * static_cast<float>(S16ToDouble(pp->v1)) - LoadFloat(kMaterialEditorOneF));
                    pp = polygon;
                    pp->texCoord[2][1] = -(scaleV * static_cast<float>(S16ToDouble(pp->v2)) - LoadFloat(kMaterialEditorOneF));
                    pp = polygon;
                    pp->texCoord[3][1] = -(scaleV * static_cast<float>(S16ToDouble(pp->v3)) - LoadFloat(kMaterialEditorOneF));
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
                        GXSetNumTevStages(3);
                        GXSetNumTexGens(1);

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

                u32 vertexIndex[8];
                u8 vertexCount = 3;
                MaterialEditorPolygon* poly = polygon;
                vertexIndex[4] = poly->index0;
                vertexIndex[5] = poly->index1;
                vertexIndex[6] = poly->index2;
                vertexIndex[0] = 0;
                vertexIndex[1] = 1;
                vertexIndex[2] = 2;

                if ((flags & 0xf) == 0) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
                }
                if ((flags & 0xf) == 1) {
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    vertexCount = 4;
                    vertexIndex[6] = polygon->index3;
                    vertexIndex[7] = polygon->index2;
                    vertexIndex[2] = 3;
                    vertexIndex[3] = 2;
                }

                u8 i = 0;
                while (i < vertexCount) {
                    GXWGFifo.u16 = static_cast<u16>((&vertexIndex[4])[i]);
                    GXWGFifo.u16 = static_cast<u16>((&vertexIndex[4])[i]);
                    GXWGFifo.u8 = static_cast<u8>(vertexIndex[i]);
                    GXWGFifo.u16 = static_cast<u16>(vertexIndex[i]);
                    i++;
                }
#undef polygon
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

    one = LoadFloat(kMaterialEditorOneF);
    rotationValue = LoadFloat(kMaterialEditorZeroF);
    srt.transZ = rotationValue;
    srt.transY = rotationValue;
    srt.transX = rotationValue;
    srt.rotZ = rotationValue;
    srt.rotY = rotationValue;
    srt.rotX = rotationValue;
    srt.scaleZ = one;
    srt.scaleY = one;
    srt.scaleX = one;
    srt.transX = m_usbTransform.m_cameraPosition.x;
    srt.transY = m_usbTransform.m_cameraPosition.y;
    srt.transZ = -m_usbTransform.m_cameraPosition.z;
    CameraPcs.SetViewerSRT(reinterpret_cast<const SRT*>(&srt));

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMatrix);

    m_unkMatrix.value[0][0] = m_usbTransform.m_viewMatrix[0][0];
    m_unkMatrix.value[0][1] = m_usbTransform.m_viewMatrix[0][1];
    m_unkMatrix.value[0][2] = m_usbTransform.m_viewMatrix[0][2];
    m_unkMatrix.value[0][3] = m_usbTransform.m_viewMatrix[0][3];
    m_unkMatrix.value[1][0] = m_usbTransform.m_viewMatrix[1][0];
    m_unkMatrix.value[1][1] = m_usbTransform.m_viewMatrix[1][1];
    m_unkMatrix.value[1][2] = m_usbTransform.m_viewMatrix[1][2];
    m_unkMatrix.value[1][3] = m_usbTransform.m_viewMatrix[1][3];
    m_unkMatrix.value[2][0] = m_usbTransform.m_viewMatrix[2][0];
    m_unkMatrix.value[2][1] = m_usbTransform.m_viewMatrix[2][1];
    m_unkMatrix.value[2][2] = m_usbTransform.m_viewMatrix[2][2];
    m_unkMatrix.value[2][3] = m_usbTransform.m_viewMatrix[2][3];

    PSMTXTranspose(m_unkMatrix.value, m_unkMatrix.value);

    m_unkMatrix.value[0][1] = -m_unkMatrix.value[0][1];
    m_unkMatrix.value[1][1] = -m_unkMatrix.value[1][1];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][0] = -m_unkMatrix.value[2][0];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][2] = -m_unkMatrix.value[2][2];

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[1][1] = kMaterialEditorNegativeOneF;
    PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[2][2] = kMaterialEditorNegativeOneF;
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

    unsigned int textureIndex;
    CMaterialEditorPcs* textureSlot = this;
    m_loadedTextureCount = static_cast<s8>(textureIndex = 0);
    do {
        MemFree(textureSlot->m_textureData[0]);
        MemFree(textureSlot->m_tlutData[0]);
        MemFree(textureSlot->m_texObj[0]);
        MemFree(textureSlot->m_tlutObj0[0]);
        MemFree(textureSlot->m_tlutObj1[0]);
        MemFree(textureSlot->m_textureHeader[0]);
        textureIndex += 1;
        textureSlot = reinterpret_cast<CMaterialEditorPcs*>(reinterpret_cast<char*>(textureSlot) + sizeof(void*));
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

    m_usbStreamState.m_stageDefault = reinterpret_cast<CMemory::CStage*>(1);
    m_displayTextureEnabled = 0;
    memset(&m_usbTransform, 0, sizeof(m_usbTransform));

    fVar1 = LoadFloat(kMaterialEditorOneF);
    m_usbTransform.m_modelMatrix[3][3] = fVar1;
    m_usbTransform.m_modelMatrix[2][2] = fVar1;
    m_usbTransform.m_modelMatrix[1][1] = fVar1;
    m_usbTransform.m_modelMatrix[0][0] = fVar1;

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
    return reinterpret_cast<int>(&CMaterialEditorPcs::m_table + index);
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
    CMaterialEditorPcs* textureSlot = this;
    m_loadedTextureCount = static_cast<s8>(textureIndex = 0);

    do {
        MemFree(textureSlot->m_textureData[0]);
        MemFree(textureSlot->m_tlutData[0]);
        MemFree(textureSlot->m_texObj[0]);
        MemFree(textureSlot->m_tlutObj0[0]);
        MemFree(textureSlot->m_tlutObj1[0]);
        MemFree(textureSlot->m_textureHeader[0]);
        textureIndex += 1;
        textureSlot = reinterpret_cast<CMaterialEditorPcs*>(reinterpret_cast<char*>(textureSlot) + sizeof(void*));
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
    int textureIndex;

    m_viewerLightColors[0].r = 0x7f;
    m_viewerLightColors[0].g = 0x7f;
    m_viewerLightColors[0].b = 0x7f;
    m_viewerLightColors[0].a = 0xff;

    float one = LoadFloat(kMaterialEditorOneF);
    float minusOne = LoadFloat(kMaterialEditorNegativeOneF);
    float zero = LoadFloat(kMaterialEditorZeroF);

    for (int i = 0; i < 3; i++) {
        u8 shade = (i == 0) ? 0x3f : 0;

        m_viewerLightColors[i + 1].r = shade;
        m_viewerLightColors[i + 1].g = shade;
        m_viewerLightColors[i + 1].b = shade;
        m_viewerLightColors[i + 1].a = 0xff;

        m_viewerLightDirs[i].x = zero;
        m_viewerLightDirs[i].y = zero;
        m_viewerLightDirs[i].z = minusOne;
    }

    m_viewerSrtPosition.z = zero;
    m_viewerSrtPosition.y = zero;
    m_viewerSrtPosition.x = zero;
    m_viewerSrtRotation.z = zero;
    m_viewerSrtRotation.y = zero;
    m_viewerSrtRotation.x = zero;
    m_viewerSrtScale.z = one;
    m_viewerSrtScale.y = one;
    m_viewerSrtScale.x = one;
    m_rsdIndex = 0;

    textureIndex = 0;
    while (textureIndex < 0x10) {
        m_textureData[textureIndex] = 0;
        m_tlutData[textureIndex] = 0;
        m_texObj[textureIndex] = 0;
        m_tlutObj0[textureIndex] = 0;
        m_tlutObj1[textureIndex] = 0;
        m_textureHeader[textureIndex] = 0;
        textureIndex++;
    }

    m_loadedTextureCount = 0;
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
