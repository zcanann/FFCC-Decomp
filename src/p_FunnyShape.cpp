#include "ffcc/p_FunnyShape.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_usb.h"
#include "ffcc/symbols_shared.h"
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
extern "C" int __cntlzw(unsigned int);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" CUSBStreamData* __ct__14CUSBStreamDataFv(CUSBStreamData*);
extern "C" CFunnyShape* __ct__11CFunnyShapeFv(CFunnyShape*);
extern "C" void* gVtable_CPtrArray_OSFSTexture[];
extern "C" void* gVtable_CPtrArray_GXTexObj[];

inline void* operator new(unsigned long, void* p)
{
    return p;
}

extern void* __vt__8CManager;
extern "C" char __vt__14CFunnyShapePcs[];
extern u32 m_table_desc0__14CFunnyShapePcs[];
extern u32 m_table_desc1__14CFunnyShapePcs[];
extern u32 m_table_desc2__14CFunnyShapePcs[];
extern u32 m_table_desc3__14CFunnyShapePcs[];
unsigned char ARRAY_8026D728[0xC];
CFunnyShapePcs FunnyShapePcs;
extern "C" CFunnyShapePcs* __dt__14CFunnyShapePcsFv(CFunnyShapePcs* self, short shouldDelete);
extern "C" CPtrArray<OSFS_TEXTURE_ST*>* dtor_8004EAD0(CPtrArray<OSFS_TEXTURE_ST*>* ptrArray, short shouldDelete);
extern "C" CFunnyShape* dtor_80051D80(CFunnyShape* funnyShape, short shouldDelete);
extern "C" CUSBStreamData* __dt__14CUSBStreamDataFv(CUSBStreamData* self, short shouldDelete);

extern unsigned char m_table__14CFunnyShapePcs[];

namespace {
static char s_CFunnyShapePcs[] = "CFunnyShapePcs";

static inline u8* Ptr(CFunnyShapePcs* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline CUSBStreamData* UsbStream(CFunnyShapePcs* self)
{
    return reinterpret_cast<CUSBStreamData*>(Ptr(self, 0x8));
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self)
{
    return reinterpret_cast<CFunnyShape*>(Ptr(self, 0x1C));
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
    u32* dst = reinterpret_cast<u32*>(m_table__14CFunnyShapePcs);

    *reinterpret_cast<void**>(self) = __vt__14CFunnyShapePcs;

    __ct__14CUSBStreamDataFv(reinterpret_cast<CUSBStreamData*>(self + 0x3C));
    __ct__11CFunnyShapeFv(reinterpret_cast<CFunnyShape*>(self + 0x50));
    new (self + 0x61BC) CPtrArray<OSFS_TEXTURE_ST*>();
    new (self + 0x61D8) CPtrArray<_GXTexObj*>();

    __register_global_object(self, reinterpret_cast<void*>(__dt__14CFunnyShapePcsFv), ARRAY_8026D728);

    dst[0x004 / 4] = m_table_desc0__14CFunnyShapePcs[0];
    dst[0x008 / 4] = m_table_desc0__14CFunnyShapePcs[1];
    dst[0x00C / 4] = m_table_desc0__14CFunnyShapePcs[2];
    dst[0x010 / 4] = m_table_desc1__14CFunnyShapePcs[0];
    dst[0x014 / 4] = m_table_desc1__14CFunnyShapePcs[1];
    dst[0x018 / 4] = m_table_desc1__14CFunnyShapePcs[2];
    dst[0x01C / 4] = m_table_desc2__14CFunnyShapePcs[0];
    dst[0x020 / 4] = m_table_desc2__14CFunnyShapePcs[1];
    dst[0x024 / 4] = m_table_desc2__14CFunnyShapePcs[2];
    dst[0x030 / 4] = m_table_desc3__14CFunnyShapePcs[0];
    dst[0x034 / 4] = m_table_desc3__14CFunnyShapePcs[1];
    dst[0x038 / 4] = m_table_desc3__14CFunnyShapePcs[2];
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
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
CFunnyShapePcs::~CFunnyShapePcs()
{
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(reinterpret_cast<u8*>(this) + 0x61D8)->~CPtrArray<_GXTexObj*>();
    dtor_8004EAD0(reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(reinterpret_cast<u8*>(this) + 0x61BC), -1);
    dtor_80051D80(reinterpret_cast<CFunnyShape*>(reinterpret_cast<u8*>(this) + 0x50), -1);
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
    u8* self = Ptr(this, 0);
    u32 clz;
    u32 bit;
    u32 negBit;
    const u32 mask = 0x3F;
    f32 origin;
    f32 ndcMin;

    self[0x8] = 0x7F;
    clz = __cntlzw(0);
    bit = (clz >> 5) & 1;

    self[0x9] = 0x7F;
    clz = __cntlzw(1);
    negBit = -bit;

    self[0xA] = 0x7F;
    bit = (clz >> 5) & 1;
    self[0xB] = 0xFF;

    origin = kFunnyShapeViewportOrigin;
    self[0xC] = mask & negBit;

    clz = __cntlzw(2);
    ndcMin = kFunnyShapeNdcMin;

    self[0xD] = mask & negBit;
    self[0xE] = mask & negBit;

    negBit = -((clz >> 5) & 1);
    self[0xF] = 0xFF;

    *reinterpret_cast<f32*>(self + 0x18) = origin;
    *reinterpret_cast<f32*>(self + 0x1C) = origin;
    *reinterpret_cast<f32*>(self + 0x20) = ndcMin;

    self[0x10] = mask & -bit;
    self[0x11] = mask & -bit;
    self[0x12] = mask & -bit;
    self[0x13] = 0xFF;

    *reinterpret_cast<f32*>(self + 0x24) = origin;
    *reinterpret_cast<f32*>(self + 0x28) = origin;
    *reinterpret_cast<f32*>(self + 0x2C) = ndcMin;

    self[0x14] = mask & negBit;
    self[0x15] = mask & negBit;
    self[0x16] = mask & negBit;
    self[0x17] = 0xFF;

    *reinterpret_cast<f32*>(self + 0x30) = origin;
    *reinterpret_cast<f32*>(self + 0x34) = origin;
    *reinterpret_cast<f32*>(self + 0x38) = ndcMin;
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
    *reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x4)) = Memory.CreateStage(0x200000, s_CFunnyShapePcs, 0);
    USBPcs.IsBigAlloc(1);

    GXColor clearColor = {0x40, 0x40, 0x40, 0xFF};
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

    GXColor clearColor = {0, 0, 0, 0};
    GXSetCopyClear(clearColor, 0xFFFFFF);

    reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(Ptr(this, 0x61BC))->DeleteAndRemoveAll();
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(Ptr(this, 0x61D8))->DeleteAndRemoveAll();

    UsbStream(this)->DeleteBuffer();
    FunnyShape(this)->~CFunnyShape();
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x4)));
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::calcViewer()
{
    if (reinterpret_cast<CUSBStreamData*>(reinterpret_cast<u8*>(this) + 0x3C)->IsUSBStreamDataDone() != 0) {
        SetUSBData();
        reinterpret_cast<CUSBStreamData*>(reinterpret_cast<u8*>(this) + 0x3C)->SetUSBStreamDataDone();
    }

    if (static_cast<s8>(reinterpret_cast<u8*>(this)[0x6124]) == 0) {
        return;
    }

    if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x6134) == 0) {
        return;
    }

    reinterpret_cast<CFunnyShape*>(reinterpret_cast<u8*>(this) + 0x50)->Update();
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
    static char s_funnyShapeFmt[] = "FunnyShape %c";
    static char s_spinner[] = "|/-\\";
    static int frameCount;

    C_MTXOrtho(ortho, kFunnyShapeNdcMax, kFunnyShapeNdcMin, kFunnyShapeNdcMin, kFunnyShapeNdcMax, kFunnyShapeNdcMax, kFunnyShapeOrthoFarZ);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    C_MTXLookAt(view, reinterpret_cast<Point3d*>(&eye), &up, reinterpret_cast<Point3d*>(&at));
    GXLoadPosMtxImm(view, GX_PNMTX0);

    GXClearVtxDesc();
    GXSetNumChans(1);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    if ((Ptr(this, 0x6178)[0] & 1) != 0) {
        FunnyShape(this)->RenderTexture();
    }
    if ((Ptr(this, 0x6178)[0] & 4) != 0) {
        FunnyShape(this)->RenderShape();
    }
    if ((Ptr(this, 0x6178)[0] & 8) != 0) {
        FunnyShape(this)->Render();
    }

    frameCount++;
    if (frameCount > 100000) {
        frameCount = 0;
    }

    GXSetViewport(kFunnyShapeViewportOrigin, kFunnyShapeViewportOrigin, kFunnyShapeViewportWidth, kFunnyShapeViewportHeight, kFunnyShapeViewportOrigin, kFunnyShapeNdcMax);
    Graphic.Printf(s_funnyShapeFmt, s_spinner[(frameCount >> 4) & 3]);
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
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); i++) {
        void* item = items[i];
        if (item != 0) {
            __dl__FPv(item);
            items[i] = 0;
        }
    }
    if (items != 0) {
        __dla__FPv(items);
        items = 0;
    }
    size = 0;
    numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e724
 * PAL Size: 136b
 */
template <>
void CPtrArray<OSFS_TEXTURE_ST*>::DeleteAndRemoveAll()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); i++) {
        void* item = items[i];
        if (item != 0) {
            __dl__FPv(item);
            items[i] = 0;
        }
    }
    if (items != 0) {
        __dla__FPv(items);
        items = 0;
    }
    size = 0;
    numItems = 0;
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
