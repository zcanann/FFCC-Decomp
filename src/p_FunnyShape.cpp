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

struct _GXTexObj;
struct OSFS_TEXTURE_ST;

template <class T>
class CPtrArray
{
public:
    void** vtable;
    unsigned long size;
    unsigned long numItems;
    unsigned long defaultSize;
    T* items;
    CMemory::CStage* stage;
    int growCapacity;

    CPtrArray();
    ~CPtrArray();

    void RemoveAll();
    void DeleteAndRemoveAll();
};

template <class T>
inline void SetPtrArrayDtorVtable(CPtrArray<T>*)
{
}

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void CreateBuffer__14CUSBStreamDataFv(CUSBStreamData*);
extern "C" void DeleteBuffer__14CUSBStreamDataFv(CUSBStreamData*);
extern "C" CFunnyShape* __dt__11CFunnyShapeFv(CFunnyShape*, short);
extern "C" void __dt__14CFunnyShapePcsFv(void*);
extern "C" void* __vt__8CManager[];
extern "C" void* gVtable_CPtrArray_OSFSTexture[];
extern "C" void* gVtable_CPtrArray_GXTexObj[];
extern "C" void* __vt__14CFunnyShapePcs[];

CFunnyShapePcs FunnyShapePcs;
u8 ARRAY_8026D728[0xC];

namespace {
void CopyFunnyShapePcsTable()
{
    unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__14CFunnyShapePcs);

    dst[1] = m_table_desc0__14CFunnyShapePcs[0];
    dst[2] = m_table_desc0__14CFunnyShapePcs[1];
    dst[3] = m_table_desc0__14CFunnyShapePcs[2];
    dst[4] = m_table_desc1__14CFunnyShapePcs[0];
    dst[5] = m_table_desc1__14CFunnyShapePcs[1];
    dst[6] = m_table_desc1__14CFunnyShapePcs[2];
    dst[7] = m_table_desc2__14CFunnyShapePcs[0];
    dst[8] = m_table_desc2__14CFunnyShapePcs[1];
    dst[9] = m_table_desc2__14CFunnyShapePcs[2];
    dst[12] = m_table_desc3__14CFunnyShapePcs[0];
    dst[13] = m_table_desc3__14CFunnyShapePcs[1];
    dst[14] = m_table_desc3__14CFunnyShapePcs[2];
}

} // namespace

extern "C" CPtrArray<OSFS_TEXTURE_ST*>* dtor_8004EAD0(CPtrArray<OSFS_TEXTURE_ST*>* ptrArray, short shouldDelete);
extern "C" CUSBStreamData* __dt__14CUSBStreamDataFv(CUSBStreamData* self, short shouldDelete);
static const char s_CFunnyShapePcs[] = "CFunnyShapePcs";
static const char s_funnyShapeSpinnerText[] = "|/-\\";
char* gFunnyShapeSpinnerText = 0;
s8 gFunnyShapeSpinnerTextInitialized = 0;
int gFunnyShapeSpinnerFrame = 0;
s8 gFunnyShapeSpinnerFrameInitialized = 0;

namespace {
static inline u8* Ptr(CFunnyShapePcs* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline CUSBStreamData* UsbStream(CFunnyShapePcs* self)
{
    return reinterpret_cast<CUSBStreamData*>(Ptr(self, 0x3C));
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self)
{
    return reinterpret_cast<CFunnyShape*>(Ptr(self, 0x50));
}
} // namespace

/*
 * --INFO--
 * PAL Address: 0x8004e844
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_FunnyShape_cpp(void)
{
    u8* self = reinterpret_cast<u8*>(&FunnyShapePcs);

    *reinterpret_cast<void**>(self) = __vt__8CManager;
    *reinterpret_cast<void**>(self) = __vt__8CProcess;
    *reinterpret_cast<void**>(self) = __vt__14CFunnyShapePcs;

    __ct__14CUSBStreamDataFv(self + 0x3C);
    __ct__11CFunnyShapeFv(self + 0x50);
    __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(self + 0x61BC);
    __ct__22CPtrArray_P9_GXTexObj_Fv(self + 0x61D8);
    __register_global_object(self, __dt__14CFunnyShapePcsFv, ARRAY_8026D728);

    CopyFunnyShapePcsTable();
}

template <class T>
CPtrArray<T>::CPtrArray()
{
    vtable = 0;
    numItems = 0;
    size = 0;
    defaultSize = 0x10;
    items = 0;
    stage = 0;
    growCapacity = 1;
}

template <>
CPtrArray<_GXTexObj*>::CPtrArray()
{
    vtable = gVtable_CPtrArray_GXTexObj;
    numItems = 0;
    size = 0;
    defaultSize = 0x10;
    items = 0;
    stage = 0;
    growCapacity = 1;
}

template <>
CPtrArray<OSFS_TEXTURE_ST*>::CPtrArray()
{
    vtable = gVtable_CPtrArray_OSFSTexture;
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
    SetPtrArrayDtorVtable(this);
    RemoveAll();
}

template <>
inline void SetPtrArrayDtorVtable(CPtrArray<_GXTexObj*>* ptrArray)
{
    ptrArray->vtable = gVtable_CPtrArray_GXTexObj;
}

template <>
inline void SetPtrArrayDtorVtable(CPtrArray<OSFS_TEXTURE_ST*>* ptrArray)
{
    ptrArray->vtable = gVtable_CPtrArray_OSFSTexture;
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
 * Address: TODO
 * Size: TODO
 */
CFunnyShapePcs::CFunnyShapePcs()
{
    __ct__14CUSBStreamDataFv(reinterpret_cast<unsigned char*>(this) + 0x3C);
    __ct__11CFunnyShapeFv(reinterpret_cast<unsigned char*>(this) + 0x50);
    __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(reinterpret_cast<unsigned char*>(this) + 0x61BC);
    __ct__22CPtrArray_P9_GXTexObj_Fv(reinterpret_cast<unsigned char*>(this) + 0x61D8);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
CFunnyShapePcs::~CFunnyShapePcs()
{
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(reinterpret_cast<u8*>(this) + 0x61D8)->~CPtrArray<_GXTexObj*>();
    reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(reinterpret_cast<u8*>(this) + 0x61BC)->~CPtrArray<OSFS_TEXTURE_ST*>();
    __dt__11CFunnyShapeFv(reinterpret_cast<CFunnyShape*>(reinterpret_cast<u8*>(this) + 0x50), -1);
    __dt__14CUSBStreamDataFv(reinterpret_cast<CUSBStreamData*>(reinterpret_cast<u8*>(this) + 0x3C), -1);
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
    GXColor* colors = reinterpret_cast<GXColor*>(m_viewerState);
    Vec* positions = reinterpret_cast<Vec*>(&m_viewerState[0x10]);

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
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::Quit()
{
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
    return reinterpret_cast<int>(m_table__14CFunnyShapePcs + index * 0x15C);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::createViewer()
{
    *reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x4)) =
        Memory.CreateStage(0x200000, const_cast<char*>(s_CFunnyShapePcs), 0);
    USBPcs.IsBigAlloc(1);

    GXColor clearColor;
    clearColor.r = 0x40;
    clearColor.g = 0x40;
    clearColor.b = 0x40;
    clearColor.a = 0xFF;
    GXSetCopyClear(clearColor, 0xFFFFFF);

    memset(Ptr(this, 0x6178), 0, 0x40);
    UsbStream(this)->CreateBuffer();
    *reinterpret_cast<u32*>(Ptr(this, 0x61B8)) = 0;
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

    reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(Ptr(this, 0x61BC))->DeleteAndRemoveAll();
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(Ptr(this, 0x61D8))->DeleteAndRemoveAll();

    DeleteBuffer__14CUSBStreamDataFv(UsbStream(this));
    __dt__11CFunnyShapeFv(FunnyShape(this), -1);
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x4)));
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::calcViewer()
{
    u8* self = reinterpret_cast<u8*>(this);

    if (reinterpret_cast<CUSBStreamData*>(self + 0x3C)->IsUSBStreamDataDone()) {
        SetUSBData();
        reinterpret_cast<CUSBStreamData*>(self + 0x3C)->SetUSBStreamDataDone();
    }

    if ((static_cast<s8>(self[0x6124]) == 0) || (*reinterpret_cast<u32*>(self + 0x6134) == 0)) {
        return;
    }

    reinterpret_cast<CFunnyShape*>(self + 0x50)->Update();
}

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
    Mtx44 ortho;
    Mtx view;
    Vec eye = {0.0f, 0.0f, 0.0f};
    Vec at = {0.0f, 0.0f, 0.0f};
    Vec up = {0.0f, 1.0f, 0.0f};
    static const char s_funnyShapeFmt[] = "FunnyShape %c";

    C_MTXOrtho(ortho, kFunnyShapeNdcMax, kFunnyShapeNdcMin, kFunnyShapeNdcMin, kFunnyShapeNdcMax, kFunnyShapeNdcMax, kFunnyShapeOrthoFarZ);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    C_MTXLookAt(view, reinterpret_cast<Point3d*>(&eye), &up, reinterpret_cast<Point3d*>(&at));
    GXLoadPosMtxImm(view, GX_PNMTX0);

    GXClearVtxDesc();
    GXSetNumChans(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    if ((*reinterpret_cast<u32*>(Ptr(this, 0x6178)) & 1) != 0) {
        FunnyShape(this)->RenderTexture();
    }
    if ((*reinterpret_cast<u32*>(Ptr(this, 0x6178)) & 4) != 0) {
        FunnyShape(this)->RenderShape();
    }
    if ((*reinterpret_cast<u32*>(Ptr(this, 0x6178)) & 8) != 0) {
        FunnyShape(this)->Render();
    }

    if (!gFunnyShapeSpinnerTextInitialized) {
        gFunnyShapeSpinnerText = const_cast<char*>(s_funnyShapeSpinnerText);
        gFunnyShapeSpinnerTextInitialized = true;
    }
    if (!gFunnyShapeSpinnerFrameInitialized) {
        gFunnyShapeSpinnerFrame = 0;
        gFunnyShapeSpinnerFrameInitialized = true;
    }

    gFunnyShapeSpinnerFrame++;
    if (gFunnyShapeSpinnerFrame > 100000) {
        gFunnyShapeSpinnerFrame = 0;
    }

    GXSetViewport(kFunnyShapeViewportOrigin, kFunnyShapeViewportOrigin, kFunnyShapeViewportWidth, kFunnyShapeViewportHeight, kFunnyShapeViewportOrigin, kFunnyShapeNdcMax);
    {
        int frame = gFunnyShapeSpinnerFrame >> 4;
        Graphic.Printf(const_cast<char*>(s_funnyShapeFmt), gFunnyShapeSpinnerText[frame % 4]);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(size); i++) {
        void* item = items[i];
        if (item != 0) {
            __dl__FPv(item);
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
        void* item = items[i];
        if (item != 0) {
            __dl__FPv(item);
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
        __dla__FPv(items);
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
        __dla__FPv(items);
        items = 0;
    }
    numItems = 0;
    size = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004ead0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<OSFS_TEXTURE_ST*>* dtor_8004EAD0(CPtrArray<OSFS_TEXTURE_ST*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        SetPtrArrayDtorVtable(ptrArray);
        if (ptrArray->items != 0) {
            __dla__FPv(ptrArray->items);
            ptrArray->items = 0;
        }
        ptrArray->numItems = 0;
        ptrArray->size = 0;
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

template class CPtrArray<_GXTexObj*>;
template class CPtrArray<OSFS_TEXTURE_ST*>;
