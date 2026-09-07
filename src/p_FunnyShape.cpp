#include "ffcc/p_FunnyShape.h"
#include "ffcc/ptrarray.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_usb.h"
extern "C" {
extern const f32 kFunnyShapeNdcMax = 1.0f;
extern const f32 kFunnyShapeNdcMin = -1.0f;
extern const f32 kFunnyShapeOrthoFarZ = 100.0f;
extern const f32 kFunnyShapeViewportOrigin = 0.0f;
extern const f32 kFunnyShapeViewportWidth = 640.0f;
extern const f32 kFunnyShapeViewportHeight = 448.0f;
}
static const char s_funnyShapeSpinner[5] = "|/-\\";
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/mtx.h"

#include <string.h>

static const char s_CFunnyShapePcsViewer[] = "CFunnyShapePcs(VIEWER)";
extern "C" const Vec s_funnyEye = {0.0f, 0.0f, 4.0f};
extern "C" const Vec s_funnyAt = {0.0f, 0.0f, 0.0f};
extern "C" const Vec s_funnyUp = {0.0f, 1.0f, 0.0f};
static const char s_CFunnyShapePcs[] = "CFunnyShapePcs";
extern "C" const char sFunnyShapePcsManagerClassName[] = "CManager";
extern "C" const char sFunnyShapePcsProcessClassName[] = "CProcess";
static const char s_funnyShapeFmt[] = "FunnyShape [%c]";
static const char s_CPtrArray_OSFS_TEXTURE_ST_801D7E44[] = "CPtrArray<OSFS_TEXTURE_ST *>";
static const char s_CPtrArray_GXTexObj[] = "CPtrArray<_GXTexObj *>";

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

/*
 * --INFO--
 * PAL Address: 0x8004E5E4
 * PAL Size: 184b
 * EN Address: 0x8005B6E4
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::Init()
{
    GXColor* colors = m_viewerState.m_colors;
    Vec* positions = m_viewerState.m_positions;

    colors[0].r = 0x7F;
    colors[0].g = 0x7F;
    colors[0].b = 0x7F;
    colors[0].a = 0xFF;

    for (int i = 0; i < 3; i++) {
        u8 shade = (i == 0) ? 0x3F : 0;

        colors[i + 1].r = shade;
        colors[i + 1].g = shade;
        colors[i + 1].b = shade;
        colors[i + 1].a = 0xFF;

        positions[i].x = kFunnyShapeViewportOrigin;
        positions[i].y = kFunnyShapeViewportOrigin;
        positions[i].z = kFunnyShapeNdcMin;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004E5E0
 * PAL Size: 4b
 * EN Address: 0x8005B7D0
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::Quit()
{
}

/*
 * --INFO--
 * PAL Address: 0x8004E5CC
 * PAL Size: 20b
 * EN Address: 0x8005B7D4
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
int CFunnyShapePcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x8004E524
 * PAL Size: 168b
 * EN Address: 0x8005B7E8
 * EN Size: 220b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::createViewer()
{
    m_viewerStage = Memory.CreateStage(0x200000, const_cast<char*>(s_CFunnyShapePcs), 0);
    USBPcs.IsBigAlloc(1);

    GXColor clearColor;
    clearColor.r = 0x40;
    clearColor.g = 0x40;
    clearColor.b = 0x40;
    clearColor.a = 0xFF;
    GXSetCopyClear(clearColor, 0xFFFFFF);

    memset(&m_displayPending, 0, sizeof(m_displayPending));
    m_usbStreamData.CreateBuffer();
    m_displayTextureEnabled = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004E48C
 * PAL Size: 152b
 * EN Address: 0x8005B8C4
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::destroyViewer()
{
    USBPcs.IsBigAlloc(0);

    GXColor clearColor;
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;
    clearColor.a = 0;
    GXSetCopyClear(clearColor, 0xFFFFFF);

    m_textureHeaders.DeleteAndRemoveAll();
    m_textureObjects.DeleteAndRemoveAll();

    m_usbStreamData.DeleteBuffer();
    m_funnyShape.~CFunnyShape();
    Memory.DestroyStage(m_viewerStage);
}

/*
 * --INFO--
 * PAL Address: 0x8004E420
 * PAL Size: 108b
 * EN Address: 0x8005B994
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::calcViewer()
{
    if (m_usbStreamData.IsUSBStreamDataDone()) {
        SetUSBData();
        m_usbStreamData.SetUSBStreamDataDone();
    }

    if (m_funnyShape.m_textureCount == 0 || m_funnyShape.m_anm.anmData == 0) {
        return;
    }

    m_funnyShape.Update();
}

/*
 * --INFO--
 * PAL Address: 0x8004E210
 * PAL Size: 528b
 * EN Address: 0x8005BA0C
 * EN Size: 564b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::drawViewer()
{
    Mtx44 projection;
    Mtx44 view;
    Point3d eye = {0.0f, 0.0f, 4.0f};
    Point3d at = {0.0f, 0.0f, 0.0f};
    Vec up = {0.0f, 1.0f, 0.0f};
    C_MTXOrtho(projection, kFunnyShapeNdcMax, kFunnyShapeNdcMin,
               kFunnyShapeNdcMin, kFunnyShapeNdcMax,
               kFunnyShapeNdcMax, kFunnyShapeOrthoFarZ);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    C_MTXLookAt(view, &eye, &up, &at);
    GXLoadPosMtxImm(view, GX_PNMTX0);

    GXClearVtxDesc();
    GXSetNumChans(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    if ((m_displayPending.flags & 1) != 0) {
        m_funnyShape.RenderTexture();
    }
    if ((m_displayPending.flags & 4) != 0) {
        m_funnyShape.RenderShape();
    }
    if ((m_displayPending.flags & 8) != 0) {
        m_funnyShape.Render();
    }

    static char* pFan = const_cast<char*>(s_funnyShapeSpinner);
    static int alive = 0;

    alive++;
    if (alive > 100000) {
        alive = 0;
    }

    GXSetViewport(kFunnyShapeViewportOrigin, kFunnyShapeViewportOrigin,
                  kFunnyShapeViewportWidth, kFunnyShapeViewportHeight,
                  kFunnyShapeViewportOrigin, kFunnyShapeNdcMax);
    {
        int frame = alive >> 4;
        Graphic.Printf(const_cast<char*>(s_funnyShapeFmt), pFan[frame % 4]);
    }
}

#pragma pool_data off
CFunnyShapePcs FunnyShapePcs;
CProcessCallbackTable CFunnyShapePcs::m_table = {
    const_cast<char*>(s_CFunnyShapePcsViewer),
    static_cast<CProcessCallback>(&CFunnyShapePcs::createViewer),
    static_cast<CProcessCallback>(&CFunnyShapePcs::destroyViewer),
    {
        {static_cast<CProcessCallback>(&CFunnyShapePcs::calcViewer), 0x21, 0},
        {static_cast<CProcessCallback>(&CFunnyShapePcs::drawViewer), 0x42, 1},
    },
};
