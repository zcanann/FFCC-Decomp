#include "ffcc/p_FunnyShape.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_usb.h"
extern "C" {
extern const f32 kFunnyShapeNdcMax;
extern const f32 kFunnyShapeNdcMin;
extern const f32 kFunnyShapeOrthoFarZ;
extern const f32 kFunnyShapeViewportOrigin;
extern const f32 kFunnyShapeViewportWidth;
extern const f32 kFunnyShapeViewportHeight;
}
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/mtx.h"

#include <string.h>

extern "C" void createViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void destroyViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void calcViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void drawViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" const char s_CFunnyShapePcsViewer[] = "CFunnyShapePcs(VIEWER)";
extern "C" const Vec s_funnyEye = {0.0f, 0.0f, 4.0f};
extern "C" const Vec s_funnyAt = {0.0f, 0.0f, 0.0f};
extern "C" const Vec s_funnyUp = {0.0f, 1.0f, 0.0f};
const char s_CFunnyShapePcs[] = "CFunnyShapePcs";
static const char sFunnyShapePcsManagerClassName[] = "CManager";
static const char sFunnyShapePcsProcessClassName[] = "CProcess";
static const char s_funnyShapeFmt[] = "FunnyShape [%c]";
static const char s_CPtrArray_OSFS_TEXTURE_ST_801D7E44[] = "CPtrArray<OSFS_TEXTURE_ST *>";
static const char s_CPtrArray_GXTexObj[] = "CPtrArray<_GXTexObj *>";
extern const char __RTTI__8CManager_8032E660[];
extern const char __RTTI__8CProcess_8032E668[];
extern "C" const char s_funnyShapeSpinner[5];

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

namespace {
struct CFunnyShapeViewerState {
    GXColor m_colors[4];
    Vec m_positions[3];
};

static inline CUSBStreamData* UsbStream(CFunnyShapePcs* self)
{
    return reinterpret_cast<CUSBStreamData*>(&self->m_usbStreamDataStorage);
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self)
{
    return &self->m_funnyShape;
}

static inline CPtrArray<OSFS_TEXTURE_ST*>* TextureHeaders(CFunnyShapePcs* self)
{
    return &self->m_texturePtrArray;
}

static inline CPtrArray<_GXTexObj*>* TextureObjects(CFunnyShapePcs* self)
{
    return &self->m_gxTexObjPtrArray;
}

static inline CFunnyShapeViewerState* ViewerState(CFunnyShapePcs* self)
{
    return reinterpret_cast<CFunnyShapeViewerState*>(self->m_viewerState);
}
} // namespace

template <class T>
CPtrArray<T>::CPtrArray()
{
    numItems = 0;
    size = 0;
    defaultSize = 0x10;
    items = 0;
    stage = 0;
    growCapacity = 1;
}

template <class T>
CPtrArray<T>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8004e7ac
 * PAL Size: 76b
 */
template <>
void CPtrArray<_GXTexObj*>::RemoveAll();

/*
 * --INFO--
 * PAL Address: 0x8004e7f8
 * PAL Size: 76b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::RemoveAll();

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
    C_MTXOrtho(projection, kFunnyShapeNdcMax, kFunnyShapeNdcMin, kFunnyShapeNdcMin, kFunnyShapeNdcMax, kFunnyShapeNdcMax, kFunnyShapeOrthoFarZ);
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

    GXSetViewport(kFunnyShapeViewportOrigin, kFunnyShapeViewportOrigin, kFunnyShapeViewportWidth, kFunnyShapeViewportHeight, kFunnyShapeViewportOrigin, kFunnyShapeNdcMax);
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
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table) + index * sizeof(m_table));
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

        positions[i].x = kFunnyShapeViewportOrigin;
        positions[i].y = kFunnyShapeViewportOrigin;
        positions[i].z = kFunnyShapeNdcMin;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll();

/*
 * --INFO--
 * PAL Address: 0x8004e724
 * PAL Size: 136b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::DeleteAndRemoveAll();

/*
 * --INFO--
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(size); i++) {
        _GXTexObj* item = items[i];
        if (item != 0) {
            delete item;
            items[i] = 0;
        }
    }
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8004e724
 * PAL Size: 136b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::DeleteAndRemoveAll()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(size); i++) {
        OSFS_TEXTURE_ST* item = items[i];
        if (item != 0) {
            delete item;
            items[i] = 0;
        }
    }
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8004e7ac
 * PAL Size: 76b
 */
template <>
void CPtrArray<_GXTexObj*>::RemoveAll()
{
    if (items != 0) {
        delete[] items;
        items = 0;
    }
    numItems = 0;
    size = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e7f8
 * PAL Size: 76b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::RemoveAll()
{
    if (items != 0) {
        delete[] items;
        items = 0;
    }
    numItems = 0;
    size = 0;
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
inline CFunnyShapePcs::CFunnyShapePcs()
{
}

unsigned int CFunnyShapePcs::m_table_desc0[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__14CFunnyShapePcsFv)};
unsigned int CFunnyShapePcs::m_table_desc1[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__14CFunnyShapePcsFv)};
unsigned int CFunnyShapePcs::m_table_desc2[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__14CFunnyShapePcsFv)};
unsigned int CFunnyShapePcs::m_table_desc3[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__14CFunnyShapePcsFv)};
CFunnyShapePcs FunnyShapePcs;
unsigned int CFunnyShapePcs::m_table[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CFunnyShapePcsViewer)),
    m_table_desc0[0],
    m_table_desc0[1],
    m_table_desc0[2],
    m_table_desc1[0],
    m_table_desc1[1],
    m_table_desc1[2],
    m_table_desc2[0],
    m_table_desc2[1],
    m_table_desc2[2],
    0x21,
    0,
    m_table_desc3[0],
    m_table_desc3[1],
    m_table_desc3[2],
    0x42, 1
};
unsigned int sFunnyShapePcsTablePad0[3] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E660)), 0, 0};
unsigned int sFunnyShapePcsTablePad1[5] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E660)),
    0,
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CProcess_8032E668)),
    0,
    0,
};

inline CUSBStreamDataStorage::CUSBStreamDataStorage()
{
    new (reinterpret_cast<CUSBStreamData*>(this)) CUSBStreamData;
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
CFunnyShapePcs::~CFunnyShapePcs()
{
}

inline CUSBStreamDataStorage::~CUSBStreamDataStorage()
{
    reinterpret_cast<CUSBStreamData*>(this)->~CUSBStreamData();
}

CUSBStreamDataStorage::CUSBStreamDataStorage()
{
    new (this) CUSBStreamData;
}

template <>
CPtrArray<_GXTexObj*>::~CPtrArray()
{
    RemoveAll();
}

template <>
CPtrArray<OSFS_TEXTURE_ST*>::~CPtrArray()
{
    RemoveAll();
}
