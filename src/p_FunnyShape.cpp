#include "ffcc/p_FunnyShape.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/p_usb.h"
#include "dolphin/gx/GXFrameBuffer.h"

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
    ~CPtrArray();

    void RemoveAll();
    void DeleteAndRemoveAll();
};

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);

extern f32 lbl_8032FD14;
extern f32 lbl_8032FD24;
extern CMemory Memory;
extern CUSBPcs USBPcs;

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

template class CPtrArray<_GXTexObj*>;
template class CPtrArray<OSFS_TEXTURE_ST*>;

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
    reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(Ptr(this, 0x61BC))->~CPtrArray<OSFS_TEXTURE_ST*>();
    FunnyShape(this)->~CFunnyShape();
    UsbStream(this)->~CUSBStreamData();
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::Init()
{
    Ptr(this, 0x8)[0] = 0x7F;
    Ptr(this, 0x8)[1] = 0x7F;
    Ptr(this, 0x8)[2] = 0x7F;
    Ptr(this, 0x8)[3] = 0xFF;
    Ptr(this, 0x8)[4] = 0x3F;
    Ptr(this, 0x8)[5] = 0x3F;
    Ptr(this, 0x8)[6] = 0x3F;
    Ptr(this, 0x8)[7] = 0xFF;
    *reinterpret_cast<f32*>(Ptr(this, 0x18)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x1C)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x20)) = lbl_8032FD14;

    Ptr(this, 0x10)[0] = 0x3F;
    Ptr(this, 0x10)[1] = 0x3F;
    Ptr(this, 0x10)[2] = 0x3F;
    Ptr(this, 0x10)[3] = 0xFF;
    *reinterpret_cast<f32*>(Ptr(this, 0x24)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x28)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x2C)) = lbl_8032FD14;

    Ptr(this, 0x14)[0] = 0x3F;
    Ptr(this, 0x14)[1] = 0x3F;
    Ptr(this, 0x14)[2] = 0x3F;
    Ptr(this, 0x14)[3] = 0xFF;
    *reinterpret_cast<f32*>(Ptr(this, 0x30)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x34)) = lbl_8032FD24;
    *reinterpret_cast<f32*>(Ptr(this, 0x38)) = lbl_8032FD14;
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
    return static_cast<int>(index) * 0x15c + -0x7fe15858;
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
 * Address: TODO
 * Size: TODO
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
    if (UsbStream(this)->IsUSBStreamDataDone()) {
        SetUSBData();
        UsbStream(this)->SetUSBStreamDataDone();
    }

    if ((Ptr(this, 0x6124)[0] != 0) && (*reinterpret_cast<int*>(Ptr(this, 0x6134)) != 0)) {
        FunnyShape(this)->Update();
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CFunnyShapePcs::drawViewer()
{
    // TODO
}
