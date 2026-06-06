#include "ffcc/ptrarray.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/p_FunnyShape.h"
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

extern "C" void createViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void destroyViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void calcViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void drawViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
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

namespace {
static inline CUSBStreamData* UsbStream(CFunnyShapePcs* self)
{
    return &self->m_usbStreamData;
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self)
{
    return &self->m_funnyShape;
}

static inline CPtrArray<OSFS_TEXTURE_ST*>* TextureHeaders(CFunnyShapePcs* self)
{
    return &self->m_textureHeaders;
}

static inline CPtrArray<_GXTexObj*>* TextureObjects(CFunnyShapePcs* self)
{
    return &self->m_textureObjects;
}

static inline CFunnyShapeViewerState* ViewerState(CFunnyShapePcs* self)
{
    return &self->m_viewerState;
}

static inline float LoadFloat(const float& value)
{
    return value;
}
} // namespace

/*
 * --INFO--
 * PAL Address: 0x8004e210
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
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
    C_MTXOrtho(projection, LoadFloat(kFunnyShapeNdcMax), LoadFloat(kFunnyShapeNdcMin),
               LoadFloat(kFunnyShapeNdcMin), LoadFloat(kFunnyShapeNdcMax),
               LoadFloat(kFunnyShapeNdcMax), LoadFloat(kFunnyShapeOrthoFarZ));
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    C_MTXLookAt(view, &eye, &up, &at);
    GXLoadPosMtxImm(view, GX_PNMTX0);

    GXClearVtxDesc();
    GXSetNumChans(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    if ((m_displayPending.flags & 1) != 0) {
        FunnyShape(this)->RenderTexture();
    }
    if ((m_displayPending.flags & 4) != 0) {
        FunnyShape(this)->RenderShape();
    }
    if ((m_displayPending.flags & 8) != 0) {
        FunnyShape(this)->Render();
    }

    static char* pFan = const_cast<char*>(s_funnyShapeSpinner);
    static int alive = 0;

    alive++;
    if (alive > 100000) {
        alive = 0;
    }

    GXSetViewport(LoadFloat(kFunnyShapeViewportOrigin), LoadFloat(kFunnyShapeViewportOrigin),
                  LoadFloat(kFunnyShapeViewportWidth), LoadFloat(kFunnyShapeViewportHeight),
                  LoadFloat(kFunnyShapeViewportOrigin), LoadFloat(kFunnyShapeNdcMax));
    {
        int frame = alive >> 4;
        Graphic.Printf(const_cast<char*>(s_funnyShapeFmt), pFan[frame % 4]);
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::calcViewer()
{
    if (UsbStream(this)->IsUSBStreamDataDone()) {
        SetUSBData();
        UsbStream(this)->SetUSBStreamDataDone();
    }

    if (m_funnyShape.m_textureCount == 0 || m_funnyShape.m_anm.anmData == 0) {
        return;
    }

    FunnyShape(this)->Update();
}

/*
 * --INFO--
 * PAL Address: 0x8004e48c
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
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

    TextureHeaders(this)->DeleteAndRemoveAll();
    TextureObjects(this)->DeleteAndRemoveAll();

    UsbStream(this)->DeleteBuffer();
    FunnyShape(this)->~CFunnyShape();
    Memory.DestroyStage(m_viewerStage);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
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
    UsbStream(this)->CreateBuffer();
    m_displayTextureEnabled = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e5cc
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFunnyShapePcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::Quit()
{
}

/*
 * --INFO--
 * PAL Address: 0x8004e5e4
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFunnyShapePcs::Init()
{
    GXColor* colors = ViewerState(this)->m_colors;
    Vec* positions = ViewerState(this)->m_positions;

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

        positions[i].x = LoadFloat(kFunnyShapeViewportOrigin);
        positions[i].y = LoadFloat(kFunnyShapeViewportOrigin);
        positions[i].z = LoadFloat(kFunnyShapeNdcMin);
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
inline CFunnyShapePcs::CFunnyShapePcs()
{
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
CFunnyShapePcs::~CFunnyShapePcs()
{
}

static CProcessTableCallback s_tableDesc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__14CFunnyShapePcsFv)};
static CProcessTableCallback s_tableDesc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__14CFunnyShapePcsFv)};
static CProcessTableCallback s_tableDesc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__14CFunnyShapePcsFv)};
static CProcessTableCallback s_tableDesc3 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__14CFunnyShapePcsFv)};
CFunnyShapePcs FunnyShapePcs;
CProcessTable CFunnyShapePcs::m_table = {
    const_cast<char*>(s_CFunnyShapePcsViewer),
    {
        s_tableDesc0.m_thisOffset,
        s_tableDesc0.m_virtualOffset,
        s_tableDesc0.m_function,
        s_tableDesc1.m_thisOffset,
        s_tableDesc1.m_virtualOffset,
        s_tableDesc1.m_function,
        s_tableDesc2.m_thisOffset,
        s_tableDesc2.m_virtualOffset,
        s_tableDesc2.m_function,
        0x21,
        0,
        s_tableDesc3.m_thisOffset,
        s_tableDesc3.m_virtualOffset,
        s_tableDesc3.m_function,
        0x42,
        1,
    },
};
