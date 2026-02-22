#include "ffcc/p_FunnyShape.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_usb.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/mtx.h"

#include <string.h>

struct _GXTexObj;
struct OSFS_TEXTURE_ST;

template <class T>
class CPtrArray
{
public:
    unsigned long size;
    unsigned long numItems;
    unsigned long defaultSize;
    T** items;
    CMemory::CStage* stage;
    int growCapacity;

    CPtrArray();
    virtual ~CPtrArray();

    void RemoveAll();
    void DeleteAndRemoveAll();
};

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern "C" int __cntlzw(unsigned int);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" CUSBStreamData* __ct__14CUSBStreamDataFv(CUSBStreamData*);
extern "C" CFunnyShape* __ct__11CFunnyShapeFv(CFunnyShape*);

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801EA924;
extern u32 DAT_801EA778;
extern u32 DAT_801EA77C;
extern u32 PTR_createViewer__14CFunnyShapePcsFv_801EA780;
extern u32 DAT_801EA784;
extern u32 DAT_801EA788;
extern u32 PTR_destroyViewer__14CFunnyShapePcsFv_801EA78C;
extern u32 DAT_801EA790;
extern u32 DAT_801EA794;
extern u32 PTR_calcViewer__14CFunnyShapePcsFv_801EA798;
extern u32 DAT_801EA79C;
extern u32 DAT_801EA7A0;
extern u32 PTR_drawViewer__14CFunnyShapePcsFv_801EA7A4;
extern u32 DAT_801EA7AC;
extern u32 DAT_801EA7B0;
extern u32 DAT_801EA7B4;
extern u32 DAT_801EA7B8;
extern u32 DAT_801EA7BC;
extern u32 DAT_801EA7C0;
extern u32 DAT_801EA7C4;
extern u32 DAT_801EA7C8;
extern u32 DAT_801EA7CC;
extern u32 DAT_801EA7D8;
extern u32 DAT_801EA7DC;
extern u32 DAT_801EA7E0;
extern unsigned char ARRAY_8026D728[];
extern unsigned char FunnyShapePcs[];
extern "C" CFunnyShapePcs* __dt__14CFunnyShapePcsFv(CFunnyShapePcs* self, short shouldDelete);
extern "C" CPtrArray<OSFS_TEXTURE_ST*>* dtor_8004EAD0(CPtrArray<OSFS_TEXTURE_ST*>* ptrArray, short shouldDelete);

extern f32 lbl_8032FD14;
extern f32 lbl_8032FD10;
extern f32 lbl_8032FD18;
extern f32 lbl_8032FD24;
extern f32 lbl_8032FD28;
extern f32 lbl_8032FD2C;
extern CMemory Memory;
extern CUSBPcs USBPcs;
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
    *reinterpret_cast<void**>(FunnyShapePcs) = &__vt__8CManager;
    *reinterpret_cast<void**>(FunnyShapePcs) = &lbl_801E8668;
    *reinterpret_cast<void**>(FunnyShapePcs) = &lbl_801EA924;

    __ct__14CUSBStreamDataFv(reinterpret_cast<CUSBStreamData*>(FunnyShapePcs + 0x3C));
    __ct__11CFunnyShapeFv(reinterpret_cast<CFunnyShape*>(FunnyShapePcs + 0x50));
    reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(FunnyShapePcs + 0x61BC)->CPtrArray<OSFS_TEXTURE_ST*>::CPtrArray();
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(FunnyShapePcs + 0x61D8)->CPtrArray<_GXTexObj*>::CPtrArray();

    __register_global_object(FunnyShapePcs, reinterpret_cast<void*>(__dt__14CFunnyShapePcsFv), ARRAY_8026D728);

    DAT_801EA7AC = DAT_801EA778;
    DAT_801EA7B0 = DAT_801EA77C;
    DAT_801EA7B4 = PTR_createViewer__14CFunnyShapePcsFv_801EA780;
    DAT_801EA7B8 = DAT_801EA784;
    DAT_801EA7BC = DAT_801EA788;
    DAT_801EA7C0 = PTR_destroyViewer__14CFunnyShapePcsFv_801EA78C;
    DAT_801EA7C4 = DAT_801EA790;
    DAT_801EA7C8 = DAT_801EA794;
    DAT_801EA7CC = PTR_calcViewer__14CFunnyShapePcsFv_801EA798;
    DAT_801EA7D8 = DAT_801EA79C;
    DAT_801EA7DC = DAT_801EA7A0;
    DAT_801EA7E0 = PTR_drawViewer__14CFunnyShapePcsFv_801EA7A4;
}

template <class T>
CPtrArray<T>::CPtrArray()
{
    size = 0;
    numItems = 0;
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
    reinterpret_cast<CPtrArray<_GXTexObj*>*>(Ptr(this, 0x61D8))->~CPtrArray<_GXTexObj*>();
    dtor_8004EAD0(reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(Ptr(this, 0x61BC)), -1);
    FunnyShape(this)->~CFunnyShape();
    UsbStream(this)->~CUSBStreamData();
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
    unsigned char* self = Ptr(this, 0);
    const unsigned int clz0 = static_cast<unsigned int>(__cntlzw(0));
    const unsigned int clz1 = static_cast<unsigned int>(__cntlzw(1));
    unsigned char level;
    const f32 value24 = lbl_8032FD24;
    const f32 value14 = lbl_8032FD14;

    self[0x8] = 0x7F;
    self[0x9] = 0x7F;
    self[0xA] = 0x7F;
    level = static_cast<unsigned char>(-static_cast<int>((clz0 >> 5) & 1)) & 0x3F;
    self[0xB] = 0xFF;
    self[0xC] = level;
    const unsigned int clz2 = static_cast<unsigned int>(__cntlzw(2));
    self[0xD] = level;
    self[0xE] = level;
    self[0xF] = 0xFF;
    *reinterpret_cast<f32*>(self + 0x18) = value24;
    *reinterpret_cast<f32*>(self + 0x1C) = value24;
    *reinterpret_cast<f32*>(self + 0x20) = value14;

    level = static_cast<unsigned char>(-static_cast<int>((clz1 >> 5) & 1)) & 0x3F;
    self[0x10] = level;
    self[0x11] = level;
    self[0x12] = level;
    self[0x13] = 0xFF;
    *reinterpret_cast<f32*>(self + 0x24) = value24;
    *reinterpret_cast<f32*>(self + 0x28) = value24;
    *reinterpret_cast<f32*>(self + 0x2C) = value14;

    level = static_cast<unsigned char>(-static_cast<int>((clz2 >> 5) & 1)) & 0x3F;
    self[0x14] = level;
    self[0x15] = level;
    self[0x16] = level;
    self[0x17] = 0xFF;
    *reinterpret_cast<f32*>(self + 0x30) = value24;
    *reinterpret_cast<f32*>(self + 0x34) = value24;
    *reinterpret_cast<f32*>(self + 0x38) = value14;
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

    C_MTXOrtho(ortho, lbl_8032FD10, lbl_8032FD14, lbl_8032FD14, lbl_8032FD10, lbl_8032FD10, lbl_8032FD18);
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

    GXSetViewport(lbl_8032FD24, lbl_8032FD24, lbl_8032FD28, lbl_8032FD2C, lbl_8032FD24, lbl_8032FD10);
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
    size = 0;
    numItems = 0;
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
    size = 0;
    numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004e69c
 * PAL Size: 136b
 */
template <>
void CPtrArray<_GXTexObj*>::DeleteAndRemoveAll()
{
    int offset = 0;
    for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); i++) {
        if (*(int*)((int)items + offset) != 0) {
            __dl__FPv(*(void**)((int)items + offset));
            *(int*)((int)items + offset) = 0;
        }
        offset += 4;
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
    int offset = 0;
    for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); i++) {
        if (*(int*)((int)items + offset) != 0) {
            __dl__FPv(*(void**)((int)items + offset));
            *(int*)((int)items + offset) = 0;
        }
        offset += 4;
    }
    RemoveAll();
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
        if (ptrArray->items != 0) {
            __dla__FPv(ptrArray->items);
            ptrArray->items = 0;
        }
        ptrArray->size = 0;
        ptrArray->numItems = 0;
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

template class CPtrArray<_GXTexObj*>;
template class CPtrArray<OSFS_TEXTURE_ST*>;
