#define FFCC_DEFINE_FUNNYSHAPEPCS_STORAGE
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
extern "C" void createViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void destroyViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void calcViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" void drawViewer__14CFunnyShapePcsFv(CFunnyShapePcs*);
extern "C" CFunnyShape* __dt__11CFunnyShapeFv(CFunnyShape*, short);
extern "C" void __dt__14CFunnyShapePcsFv(void*);
extern "C" void* __vt__8CManager[];
extern "C" void* __vt__8CProcess[];
extern "C" void* gVtable_CPtrArray_OSFSTexture[];
extern "C" void* gVtable_CPtrArray_GXTexObj[];
extern "C" void* __vt__14CFunnyShapePcs[];
static const char lbl_801D7DD0[] = "CFunnyShapePcs(VIEWER)";
static const Vec s_funnyEye = {0.0f, 0.0f, 4.0f};
static const Vec s_funnyAt = {0.0f, 0.0f, 0.0f};
static const Vec s_funnyUp = {0.0f, 1.0f, 0.0f};
const char s_CFunnyShapePcs[] = "CFunnyShapePcs";
static const char s_CManager_801D7E1C[] = "CManager";
static const char s_CProcess_801D7E28[] = "CProcess";
static const char s_funnyShapeFmt[] = "FunnyShape [%c]";
static const char s_CPtrArray_OSFS_TEXTURE_ST_801D7E44[] = "CPtrArray<OSFS_TEXTURE_ST *>";
static const char s_CPtrArray_GXTexObj[] = "CPtrArray<_GXTexObj *>";
extern char lbl_8032E660[];
extern u8 ARRAY_8026D728[];

extern "C" CUSBStreamData* __dt__14CUSBStreamDataFv(CUSBStreamData* self, short shouldDelete);
extern "C" const char lbl_8032FD1C[5];

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
    Mtx44 view;
    Vec eye = {0.0f, 0.0f, 4.0f};
    Vec at = {0.0f, 0.0f, 0.0f};
    Vec up = {0.0f, 1.0f, 0.0f};
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

    static char* pFan = const_cast<char*>(lbl_8032FD1C);
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
 * PAL Address: 0x8004e5cc
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFunnyShapePcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table__14CFunnyShapePcs) + index * 0x15C);
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
 * PAL Address: 0x8004e844
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_FunnyShape_cpp(void)
{
    CFunnyShapePcs* pcs = reinterpret_cast<CFunnyShapePcs*>(&FunnyShapePcs);
    u8* self = reinterpret_cast<u8*>(pcs);
    unsigned int* dst = m_table__14CFunnyShapePcs;
    unsigned int* desc0 = m_table_desc0__14CFunnyShapePcs;
    unsigned int* desc1 = m_table_desc1__14CFunnyShapePcs;
    unsigned int* desc2 = m_table_desc2__14CFunnyShapePcs;
    unsigned int* desc3 = m_table_desc3__14CFunnyShapePcs;

    *reinterpret_cast<void**>(self) = __vt__8CManager;
    *reinterpret_cast<void**>(self) = __vt__8CProcess;
    *reinterpret_cast<void**>(self) = __vt__14CFunnyShapePcs;

    __ct__14CUSBStreamDataFv(self + 0x3C);
    __ct__11CFunnyShapeFv(self + 0x50);
    __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(self + 0x61BC);
    __ct__22CPtrArray_P9_GXTexObj_Fv(self + 0x61D8);
    __register_global_object(self, __dt__14CFunnyShapePcsFv, ARRAY_8026D728);
    unsigned int* table = dst + 1;
    table[0] = desc0[0];
    table[1] = desc0[1];
    table[2] = desc0[2];
    table[3] = desc1[0];
    table[4] = desc1[1];
    table[5] = desc1[2];
    table[6] = desc2[0];
    table[7] = desc2[1];
    table[8] = desc2[2];
    table[11] = desc3[0];
    table[12] = desc3[1];
    table[13] = desc3[2];
}

unsigned int m_table_desc0__14CFunnyShapePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__14CFunnyShapePcsFv)};
unsigned int m_table_desc1__14CFunnyShapePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__14CFunnyShapePcsFv)};
unsigned int m_table_desc2__14CFunnyShapePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__14CFunnyShapePcsFv)};
unsigned int m_table_desc3__14CFunnyShapePcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__14CFunnyShapePcsFv)};
unsigned int m_table__14CFunnyShapePcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(lbl_801D7DD0)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x21, 0, 0, 0, 0,
    0x42, 1
};
unsigned int lbl_801EA904[4] = {
    reinterpret_cast<unsigned int>(lbl_8032E660), 0, 0, reinterpret_cast<unsigned int>(lbl_8032E660)
};
unsigned int lbl_801EA914[4] = {
    0, 0, 0, 0
};
u8 ARRAY_8026D728[0xC];
u8 FunnyShapePcs[sizeof(CFunnyShapePcs)];

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

extern "C" void __ct__22CPtrArray_P9_GXTexObj_Fv(void* ptrArray_)
{
    CPtrArray<_GXTexObj*>* ptrArray = reinterpret_cast<CPtrArray<_GXTexObj*>*>(ptrArray_);

    ptrArray->vtable = gVtable_CPtrArray_GXTexObj;
    ptrArray->numItems = 0;
    ptrArray->size = 0;
    ptrArray->defaultSize = 0x10;
    ptrArray->items = 0;
    ptrArray->stage = 0;
    ptrArray->growCapacity = 1;
}

extern "C" void __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(void* ptrArray_)
{
    CPtrArray<OSFS_TEXTURE_ST*>* ptrArray = reinterpret_cast<CPtrArray<OSFS_TEXTURE_ST*>*>(ptrArray_);

    ptrArray->vtable = gVtable_CPtrArray_OSFSTexture;
    ptrArray->numItems = 0;
    ptrArray->size = 0;
    ptrArray->defaultSize = 0x10;
    ptrArray->items = 0;
    ptrArray->stage = 0;
    ptrArray->growCapacity = 1;
}

template <>
CPtrArray<OSFS_TEXTURE_ST*>::~CPtrArray()
{
    SetPtrArrayDtorVtable(this);
    RemoveAll();
}

template <>
CPtrArray<_GXTexObj*>::~CPtrArray()
{
    SetPtrArrayDtorVtable(this);
    RemoveAll();
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
inline CFunnyShapePcs::CFunnyShapePcs()
{
    u8* self = reinterpret_cast<u8*>(this);

    __ct__14CUSBStreamDataFv(self + 0x3C);
    __ct__11CFunnyShapeFv(self + 0x50);
    __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(self + 0x61BC);
    __ct__22CPtrArray_P9_GXTexObj_Fv(self + 0x61D8);
}
