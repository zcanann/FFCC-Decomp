#include "ffcc/map.h"
#include "ffcc/chunkfile.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/mapshadow.h"
#include "ffcc/mapanim.h"
#include "ffcc/maptexanim.h"
#include "ffcc/materialman.h"
#include "ffcc/p_game.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/file.h"
#include "ffcc/system.h"

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void __destroy_arr(void*, void*, unsigned long, unsigned long);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dt__8COctTreeFv(void*, int);
extern "C" void __dt__7CMapHitFv(void*, int);
extern "C" void __dt__7CMapObjFv(void*, int);
extern "C" void __dt__8CMapMeshFv(void*, int);
extern "C" void __dt__7CMapMngFv(void*, int);
extern "C" void __dt__8CMapAnimFv(void*, int);
extern "C" void __dt__13CMapAnimKeyDtFv(void*, int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void* __register_global_object(void*, void*, void*);
extern "C" void __ct__8COctTreeFv(void*);
extern "C" void __ct__7CMapHitFv(void*);
extern "C" void __ct__7CMapObjFv(void*);
extern "C" void __ct__8CMapMeshFv(void*);
extern "C" void __ct__9CMapIdGrpFv(void*);
extern "C" void* __nw__11CTextureSetFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CTextureSet* __ct__11CTextureSetFv(CTextureSet*);
extern "C" void Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(CTextureSet*, void*, CMemory::CStage*, int, void*, int, int);
extern "C" void* PTR_PTR_s_CMapTexAnimSet_801e896c;
extern "C" float Spline1D__5CMathFifPfPfPf(CMath*, int, float, float*, float*, float*);
extern "C" float Line1D__5CMathFifPfPf(CMath*, int, float, float*, float*);
extern "C" void MakeSpline1Dtable__5CMathFiPfPfPf(CMath*, int, float*, float*, float*);
extern "C" float lbl_8032F990;
extern "C" float lbl_8032F994;
extern "C" float lbl_8032F998;
extern "C" float lbl_8032F99C;
extern "C" int CheckHitCylinder__8COctTreeFP12CMapCylinderP3VecUl(void*, CMapCylinder*, Vec*, unsigned long);
extern "C" int CheckHitCylinderNear__8COctTreeFP12CMapCylinderP3VecUl(void*, CMapCylinder*, Vec*, unsigned long);
extern "C" void SetDrawFlag__8COctTreeFv(void*);
extern "C" void Draw__8COctTreeFUc(void*, unsigned char);
extern "C" void Draw__7CMapObjFUc(void*, unsigned char);
extern "C" void Calc__11CMapAnimRunFl(CMapAnimRun*, long);
extern "C" unsigned int CheckSum__FPvi(void*, int);
extern "C" void* lbl_801E89A8[];
extern "C" void* lbl_801E899C[];
extern "C" void* lbl_801E8990[];
extern "C" void* lbl_801E8984[];
extern "C" void* lbl_801E8978[];
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void SetOffsetZBuff__10CCameraPcsFf(double, void*);
extern unsigned char CameraPcs[];
extern int DAT_8032ec78;
extern float FLOAT_8032ec80;
extern unsigned char DAT_8032ec88;
extern unsigned char DAT_8032ecb8;
extern float FLOAT_8032f9a0;
extern float FLOAT_8032f9a4;
extern float FLOAT_8032f9a8;
extern float FLOAT_8032f9ac;
extern float FLOAT_8032f988;
extern float FLOAT_8032f98c;
extern float FLOAT_8032f9bc;
extern char DAT_801ead4c[];
extern char DAT_801d7318[];
extern char DAT_801d7350[];
extern char DAT_801d7384[];
extern char DAT_801d73c4[];
extern char DAT_8032f984[];
extern CLightPcs LightPcs;
extern CMath Math;
extern unsigned char DAT_8032ecb9;
extern CPartPcs PartPcs;
extern "C" unsigned char Vec_80245758[];
extern "C" void __ct__Q29CLightPcs6CLightFv(void*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void SetLink__7CMapObjFv();
extern "C" void ReadOtmOctTree__8COctTreeFR10CChunkFile(void*, CChunkFile&);
extern "C" int sprintf(char*, const char*, ...);

static char s_map_cpp[] = "map.cpp";
static char s_CMapMng_mapmng[] = "CMapMng.mapmng";
static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static void InitPtrArrayRaw(void* ptrArray)
{
    unsigned char* raw = reinterpret_cast<unsigned char*>(ptrArray);
    *reinterpret_cast<unsigned int*>(raw + 0x0) = 0;
    *reinterpret_cast<unsigned int*>(raw + 0x4) = 0;
    *reinterpret_cast<unsigned int*>(raw + 0x8) = 0x10;
    *reinterpret_cast<void**>(raw + 0xC) = 0;
    *reinterpret_cast<void**>(raw + 0x10) = 0;
    *reinterpret_cast<int*>(raw + 0x14) = 1;
}

}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::CMapKeyFrame()
{
    *reinterpret_cast<int*>(Ptr(this, 0)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 4)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 8)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0xC)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x10)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x14)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x18)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x1C)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x20)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x24)) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::CMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800335d0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnimSet::~CMapTexAnimSet()
{
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);
    const short count = *reinterpret_cast<short*>(p + 8);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnimSet_801e896c;

    for (int i = 0; i < count; i++) {
        int* entry = *reinterpret_cast<int**>(p + 0xC + (i * 4));
        if (entry != 0) {
            const int refCount = entry[1];
            entry[1] = refCount - 1;
            if ((refCount - 1) == 0 && entry != 0) {
                (*reinterpret_cast<void (**)(int*, int)>(*entry + 8))(entry, 1);
            }
            *reinterpret_cast<int**>(p + 0xC + (i * 4)) = 0;
        }
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003492c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapIdGrp::CMapIdGrp()
{
    *reinterpret_cast<int*>(Ptr(this, 0)) = -1;
    *reinterpret_cast<unsigned char*>(Ptr(this, 4)) = 0x80;
    *reinterpret_cast<unsigned char*>(Ptr(this, 6)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 5)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 7)) = 0x80;
    *reinterpret_cast<unsigned char*>(Ptr(this, 8)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 9)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 10)) = 0x80;
    *reinterpret_cast<unsigned char*>(Ptr(this, 11)) = 0x80;
    *reinterpret_cast<unsigned char*>(Ptr(this, 12)) = 0xff;
    *reinterpret_cast<unsigned char*>(Ptr(this, 13)) = 0x40;
    *reinterpret_cast<unsigned char*>(Ptr(this, 14)) = 0x40;
    *reinterpret_cast<unsigned char*>(Ptr(this, 15)) = 0x80;
    *reinterpret_cast<unsigned char*>(Ptr(this, 16)) = 0x40;
    *reinterpret_cast<unsigned char*>(Ptr(this, 17)) = 0x40;
    *reinterpret_cast<unsigned char*>(Ptr(this, 18)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 19)) = 0x80;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapKeyFrame::~CMapKeyFrame()
{
    void*& junTable = *reinterpret_cast<void**>(Ptr(this, 0x18));
    void*& keyFrame = *reinterpret_cast<void**>(Ptr(this, 0x1C));
    void*& keyValue = *reinterpret_cast<void**>(Ptr(this, 0x20));
    void*& splineTable = *reinterpret_cast<void**>(Ptr(this, 0x24));

    if (junTable != 0) {
        __dla__FPv(junTable);
        junTable = 0;
    }
    if (keyFrame != 0) {
        __dla__FPv(keyFrame);
        keyFrame = 0;
    }
    if (keyValue != 0) {
        __dla__FPv(keyValue);
        keyValue = 0;
    }
    if (splineTable != 0) {
        __dla__FPv(splineTable);
        splineTable = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMapKeyFrame::Get()
{
    const int keyCount = static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2)));
    const int currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    float* keyValue = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)));
    float* keyFrame = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)));
    float* splineTable = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24)));

    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 1) {
        return Spline1D__5CMathFifPfPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame, splineTable);
    }
    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 0) {
        return Line1D__5CMathFifPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame);
    }
    return 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80033d0c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" unsigned long UnkMaterialSetGetter(void* ptrArray)
{
    return *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(ptrArray) + 4);
}

/*
 * --INFO--
 * PAL Address: 0x80033d14
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMaterial*>::SetDefaultSize(unsigned long defaultSize)
{
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + 8) = defaultSize;
}

/*
 * --INFO--
 * PAL Address: 0x80033d1c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMaterial*>::SetGrow(int growCapacity)
{
    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x14) = growCapacity;
}

/*
 * --INFO--
 * PAL Address: 0x800343e0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapLightHolder*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80034414
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapLightHolder*>::~CPtrArray()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    void*& items = *reinterpret_cast<void**>(self + 0x10);

    if (items != 0) {
        __dla__FPv(items);
        items = 0;
    }

    *reinterpret_cast<int*>(self + 8) = 0;
    *reinterpret_cast<int*>(self + 4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034414
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapLightHolder*>* dtor_80034414(CPtrArray<CMapLightHolder*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = lbl_801E89A8;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            __dla__FPv(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }

    return ptrArray;
}

template <>
bool CPtrArray<CMapLightHolder*>::setSize(unsigned long newSize);

/*
 * --INFO--
 * PAL Address: 0x80033d24
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapLightHolder*>::Add(CMapLightHolder* item)
{
    bool success = setSize(m_numItems + 1);
    if (success) {
        m_items[m_numItems] = item;
        m_numItems++;
    }
    return success;
}

/*
 * --INFO--
 * PAL Address: 0x80033d94
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapLightHolder*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
template <>
void CPtrArray<CMapLightHolder*>::SetStage(CMemory::CStage* stage)
{
    *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(this) + 0x14) = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80033de8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapLightHolder*>::setSize(unsigned long newSize)
{
    CMapLightHolder** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CMapLightHolder**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, m_size << 2, m_stage, s_collection_ptrarray_h, 0xFA, 0);
        if (newItems == 0) {
            return false;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            __dla__FPv(m_items);
            m_items = 0;
        }

        m_items = newItems;
    }

    return true;
}

template <>
bool CPtrArray<CMapAnim*>::setSize(unsigned long newSize);

/*
 * --INFO--
 * PAL Address: 0x80033f54
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapAnim*>::Add(CMapAnim* item)
{
    bool success = setSize(m_numItems + 1);
    if (success) {
        m_items[m_numItems] = item;
        m_numItems++;
    }
    return success;
}

/*
 * --INFO--
 * PAL Address: 0x80033fc4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnim*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80033fcc
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnim*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034018
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034130
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimNode*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80034138
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034270
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80034158
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimKeyDt*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x800341ac
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimKeyDt* CPtrArray<CMapAnimKeyDt*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x800341cc
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimKeyDt*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034160
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimKeyDt*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034038
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnim*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034040
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CMapAnim*>::setSize(unsigned long newSize)
{
    CMapAnim** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CMapAnim**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, m_size << 2, m_stage, s_collection_ptrarray_h, 0xFA, 0);
        if (newItems == 0) {
            return false;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            __dla__FPv(m_items);
            m_items = 0;
        }

        m_items = newItems;
    }

    return true;
}

/*
 * --INFO--
 * PAL Address: 0x80034490
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimRun*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800344c4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimRun*>::~CPtrArray()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800344c4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnimRun*>* dtor_800344C4(CPtrArray<CMapAnimRun*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = lbl_801E899C;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            __dla__FPv(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }

    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 0x80034540
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnim*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80034574
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnim*>::~CPtrArray()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }

    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034574
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnim*>* dtor_80034574(CPtrArray<CMapAnim*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = lbl_801E8990;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            __dla__FPv(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }

    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 0x800345f0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimKeyDt*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80034624
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimKeyDt*>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x80034624
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnimKeyDt*>* dtor_80034624(CPtrArray<CMapAnimKeyDt*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = lbl_801E8984;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            __dla__FPv(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }

    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 0x800346a0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapShadow*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800346d4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapShadow*>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x800346d4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapShadow*>* dtor_800346D4(CPtrArray<CMapShadow*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = lbl_801E8978;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            __dla__FPv(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }

    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 0x80034260
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
template <>
int CPtrArray<CMapAnimRun*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x800340f0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimRun*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003413c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034170
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimRun*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034a44
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x800341d4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapShadow*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x800341dc
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapShadow*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034228
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapShadow* CPtrArray<CMapShadow*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034248
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapShadow*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80034290
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapShadow* CPtrArray<CMapShadow*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::Get(int& key0, int& key1, float& blend)
{
    const unsigned char mode = *reinterpret_cast<unsigned char*>(Ptr(this, 0));
    const int keyCount = static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2)));
    const int currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    unsigned char* junTable = *reinterpret_cast<unsigned char**>(Ptr(this, 0x18));
    float* keyFrame = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)));
    float* keyValue = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)));
    float* splineTable = reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24)));

    if (mode == 1) {
        blend = Spline1D__5CMathFifPfPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame, splineTable);
    } else if (mode == 0) {
        blend = Line1D__5CMathFifPfPf(&Math, keyCount - 1, static_cast<float>(currentFrame), keyValue, keyFrame);
    } else {
        blend = 0.0f;
        key0 = junTable[0];
        key1 = key0;
        return 0;
    }

    if (blend > 0.0f) {
        const float junMax = static_cast<float>(*reinterpret_cast<unsigned char*>(Ptr(this, 1)) - 1);
        if (blend < junMax) {
            key0 = static_cast<int>(blend);
            key1 = static_cast<int>(1.0f + blend);
            blend = blend - static_cast<float>(key0);
            key0 = junTable[key0];
            if (blend == 0.0f) {
                key1 = key0;
                return 0;
            }
            key1 = junTable[key1];
            return 1;
        }

        key0 = junTable[*reinterpret_cast<unsigned char*>(Ptr(this, 1)) - 1];
        key1 = key0;
        blend = 1.0f;
        return 0;
    }

    key0 = junTable[0];
    key1 = key0;
    blend = 0.0f;
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Calc()
{
    int& currentFrame = *reinterpret_cast<int*>(Ptr(this, 8));
    const int startFrame = *reinterpret_cast<int*>(Ptr(this, 0xC));
    const int endFrame = *reinterpret_cast<int*>(Ptr(this, 0x10));
    unsigned char& loop = *reinterpret_cast<unsigned char*>(Ptr(this, 3));
    unsigned char& isRun = *reinterpret_cast<unsigned char*>(Ptr(this, 4));

    currentFrame++;
    if (currentFrame <= endFrame) {
        return;
    }
    if (startFrame == endFrame) {
        isRun = 0;
        return;
    }
    if (loop != 0) {
        currentFrame = startFrame;
        return;
    }

    currentFrame = endFrame;
    isRun = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::IsRun()
{
    return *reinterpret_cast<unsigned char*>(Ptr(this, 4));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadJun(CChunkFile& chunkFile, int count)
{
    *reinterpret_cast<unsigned char*>(Ptr(this, 1)) = static_cast<unsigned char>(count);
    *reinterpret_cast<void**>(Ptr(this, 0x18)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(*reinterpret_cast<unsigned char*>(Ptr(this, 1))),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xC1);

    for (int i = 0; i < static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 1))); i++) {
        (*reinterpret_cast<unsigned char**>(Ptr(this, 0x18)))[i] = chunkFile.Get1();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadFrame(CChunkFile& chunkFile, int)
{
    const int startFrame = static_cast<int>(chunkFile.Get4());
    const int endFrame = static_cast<int>(chunkFile.Get4());

    *reinterpret_cast<int*>(Ptr(this, 0xC)) = startFrame;
    *reinterpret_cast<int*>(Ptr(this, 8)) = startFrame;
    *reinterpret_cast<int*>(Ptr(this, 0x10)) = endFrame;
    *reinterpret_cast<int*>(Ptr(this, 0x14)) = endFrame;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0)) = static_cast<unsigned char>(chunkFile.Get4());
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadKey(CChunkFile& chunkFile, int count)
{
    *reinterpret_cast<unsigned char*>(Ptr(this, 4)) = 1;
    *reinterpret_cast<unsigned char*>(Ptr(this, 2)) = static_cast<unsigned char>(count);
    *reinterpret_cast<void**>(Ptr(this, 0x1C)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xD5);
    *reinterpret_cast<void**>(Ptr(this, 0x20)) = __nwa__FUlPQ27CMemory6CStagePci(
        static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
        *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xD6);

    for (int i = 0; i < static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))); i++) {
        reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C)))[i] = chunkFile.GetF4();
        reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20)))[i] = chunkFile.GetF4();
    }

    if (*reinterpret_cast<unsigned char*>(Ptr(this, 0)) == 1) {
        *reinterpret_cast<void**>(Ptr(this, 0x24)) = __nwa__FUlPQ27CMemory6CStagePci(
            static_cast<unsigned long>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) << 2),
            *reinterpret_cast<CMemory::CStage**>(&MapMng), s_map_cpp, 0xDE);
        MakeSpline1Dtable__5CMathFiPfPfPf(&Math, static_cast<int>(*reinterpret_cast<unsigned char*>(Ptr(this, 2))) - 1,
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x20))),
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x1C))),
            reinterpret_cast<float*>(*reinterpret_cast<void**>(Ptr(this, 0x24))));
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003368c
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Create()
{
    *reinterpret_cast<unsigned int*>(Ptr(this, 4)) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 0x10)) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 0xE)) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 0xC)) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 8)) = 0;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0x2298C)) = 0xFF;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0x2298D)) = 0xFF;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0x2298E)) = 0xFF;
    *reinterpret_cast<unsigned char*>(Ptr(this, 0x2298F)) = 0xFF;

    if (Game.game.m_currentSceneId == 3) {
        *reinterpret_cast<unsigned char*>(Ptr(this, 0x22988)) = 0;
    } else {
        *reinterpret_cast<unsigned char*>(Ptr(this, 0x22988)) = 1;
    }

    *reinterpret_cast<unsigned int*>(Ptr(this, 0x22A6C)) = 0;
    *reinterpret_cast<unsigned int*>(Ptr(this, 0x228E8)) = 0;

    CMemory::CStage* stage = Memory.CreateStage(0x540000, s_CMapMng_mapmng, 0);
    *reinterpret_cast<CMemory::CStage**>(this) = stage;

    reinterpret_cast<CPtrArray<CMapAnimRun*>*>(Ptr(this, 0x213E0))->SetStage(stage);
    reinterpret_cast<CPtrArray<CMapAnim*>*>(Ptr(this, 0x213FC))->SetStage(stage);
    reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(Ptr(this, 0x21418))->SetStage(stage);
    reinterpret_cast<CPtrArray<CMapShadow*>*>(Ptr(this, 0x21434))->SetStage(stage);

    for (int i = 0; i < 2; i++) {
        reinterpret_cast<CPtrArray<CMapLightHolder*>*>(Ptr(this, 0x21450 + (i * 0x1C)))->SetStage(stage);
    }

    DAT_8032ecb9 = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyOctTree()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapMesh()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMaterialSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyAnimation()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapLightHolder()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80033254
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DestroyMap()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    short octTreeCount = *reinterpret_cast<short*>(self + 8);
    for (int i = 0; i < octTreeCount; i++) {
        __dt__8COctTreeFv(self + 0x14 + (i * 0x4C), 0xFFFF);
    }
    *reinterpret_cast<short*>(self + 8) = 0;

    short mapHitCount = *reinterpret_cast<short*>(self + 0xA);
    for (int i = 0; i < mapHitCount; i++) {
        __dt__7CMapHitFv(self + 0x4D4 + (i * 0x24), 0xFFFF);
    }
    *reinterpret_cast<short*>(self + 0xA) = 0;

    short mapObjCount = *reinterpret_cast<short*>(self + 0xC);
    for (int i = 0; i < mapObjCount; i++) {
        __dt__7CMapObjFv(self + 0x954 + (i * 0xF0), -1);
    }
    *reinterpret_cast<short*>(self + 0xC) = 0;

    short mapMeshCount = *reinterpret_cast<short*>(self + 0xE);
    for (int i = 0; i < mapMeshCount; i++) {
        __dt__8CMapMeshFv(self + 0x1E954 + (i * 0x44), 0xFFFF);
    }
    *reinterpret_cast<short*>(self + 0xE) = 0;

    int* materialSet = *reinterpret_cast<int**>(self + 0x213D4);
    if (materialSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*materialSet + 8))(materialSet, 1);
        *reinterpret_cast<int**>(self + 0x213D4) = 0;
    }

    int* textureSet = *reinterpret_cast<int**>(self + 0x213D8);
    if (textureSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*textureSet + 8))(textureSet, 1);
        *reinterpret_cast<int**>(self + 0x213D8) = 0;
    }

    int* mapTexAnimSet = *reinterpret_cast<int**>(self + 0x213DC);
    if (mapTexAnimSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*mapTexAnimSet + 8))(mapTexAnimSet, 1);
        *reinterpret_cast<int**>(self + 0x213DC) = 0;
    }

    CPtrArray<CMapAnim*>* mapAnimArray = reinterpret_cast<CPtrArray<CMapAnim*>*>(self + 0x213FC);
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimArray->GetSize()); i++) {
        CMapAnim* mapAnim = (*mapAnimArray)[i];
        if (mapAnim != 0) {
            __dt__8CMapAnimFv(mapAnim, 1);
        }
    }
    mapAnimArray->RemoveAll();

    CPtrArray<CMapAnimKeyDt*>* mapAnimKeyDtArray = reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(self + 0x21418);
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimKeyDtArray->GetSize()); i++) {
        CMapAnimKeyDt* mapAnimKeyDt = (*mapAnimKeyDtArray)[i];
        if (mapAnimKeyDt != 0) {
            __dt__13CMapAnimKeyDtFv(mapAnimKeyDt, 1);
        }
    }
    mapAnimKeyDtArray->RemoveAll();

    CPtrArray<CMapAnimRun*>* mapAnimRunArray = reinterpret_cast<CPtrArray<CMapAnimRun*>*>(self + 0x213E0);
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimRunArray->GetSize()); i++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[i];
        if (mapAnimRun != 0) {
            __dl__FPv(mapAnimRun);
        }
    }
    mapAnimRunArray->RemoveAll();

    CPtrArray<CMapShadow*>* mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>(self + 0x21434);
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        if (mapShadow != 0) {
            __dl__FPv(mapShadow);
        }
    }
    mapShadowArray->RemoveAll();

    for (int i = 0; i < 2; i++) {
        CPtrArray<CMapLightHolder*>* mapLightHolderArray =
            reinterpret_cast<CPtrArray<CMapLightHolder*>*>(self + 0x21450 + (i * 0x1C));

        for (unsigned int j = 0; j < static_cast<unsigned int>(mapLightHolderArray->GetSize()); j++) {
            CMapLightHolder* holder = (*mapLightHolderArray)[j];
            if (holder != 0) {
                __dl__FPv(holder);
            }
        }
        mapLightHolderArray->RemoveAll();
    }

    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs, 1);
    *reinterpret_cast<void**>(self + 0x228E8) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80033218
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Destroy()
{
    DestroyMap();
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(this));
}

/*
 * --INFO--
 * PAL Address: 0x8003311c
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::MapFileRead(char*, unsigned long&)
{
    for (int i = 0; i < 0x10; i++) {
        CFile::CHandle** handleSlot = reinterpret_cast<CFile::CHandle**>(Ptr(this, 0x22A2C + (i * 4)));
        CFile::CHandle* handle = *handleSlot;
        if (handle != 0 && File.IsCompleted(handle)) {
            int len = File.GetLength(handle);
            void* readBuffer = File.m_readBuffer;
            void* amemCursor = *reinterpret_cast<void**>(Ptr(this, 0x22998));

            Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1F) & ~0x1F);
            *reinterpret_cast<int*>(Ptr(this, 0x229AC + (i * 4))) = len;
            *reinterpret_cast<unsigned int*>(Ptr(this, 0x229EC + (i * 4))) = CheckSum__FPvi(readBuffer, len);
            (*reinterpret_cast<int*>(Ptr(this, 0x229A0)))++;
            *reinterpret_cast<unsigned char**>(Ptr(this, 0x22998)) += len;

            File.Close(handle);
            *handleSlot = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::MapCheckFileRead(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::LoadMapNoSyncCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800330CC
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj* CMapMng::SearchChildMapObj(CMapObj* searchStart, CMapObj* parentObj)
{
    const int objCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    CMapObj* mapObjEnd = reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (objCount * 0xF0)));

    for (CMapObj* obj = searchStart; obj < mapObjEnd; obj = reinterpret_cast<CMapObj*>(Ptr(obj, 0xF0))) {
        if (*reinterpret_cast<CMapObj**>(Ptr(obj, 0x0)) == parentObj) {
            return obj;
        }
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SearchAtribMapObj(CMapObj*, CMapObjAtr::TYPE)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80032fd0
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::AttachMapHit(CMapHit* mapHit, char* mapHitName)
{
    int mapObjCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    unsigned char* mapObj = Ptr(this, 0x954);
    unsigned char* mapObjEnd = mapObj + (mapObjCount * 0xF0);

    while (true) {
        while (mapObj < mapObjEnd) {
            unsigned char* mapObjAtr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
            if (mapObjAtr != 0 && *reinterpret_cast<int*>(mapObjAtr + 4) == 3) {
                break;
            }
            mapObj += 0xF0;
        }

        if (mapObj >= mapObjEnd) {
            return;
        }

        unsigned char* mapObjAtr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
        if (strcmp(mapHitName, reinterpret_cast<char*>(mapObjAtr + 8)) == 0) {
            *reinterpret_cast<CMapHit**>(mapObj + 0xC) = mapHit;

            if (mapObjAtr != 0) {
                void (**vtable)(void*, int) = reinterpret_cast<void (**)(void*, int)>(*reinterpret_cast<void**>(mapObjAtr));
                vtable[2](mapObjAtr, 1);
                *reinterpret_cast<unsigned char**>(mapObj + 0xEC) = 0;
            }
        }

        mapObj += 0xF0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80032f1c
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::GetDebugPlaySta(int playStaNo, Vec* vec)
{
    unsigned char* mapObj = Ptr(this, 0x954);
    unsigned char* mapObjEnd = mapObj + (*reinterpret_cast<short*>(Ptr(this, 0xC)) * 0xF0);

    while (mapObj < mapObjEnd) {
        unsigned char* mapObjAtr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
        if (mapObjAtr != 0 && *reinterpret_cast<int*>(mapObjAtr + 4) == 4 &&
            *(mapObjAtr + 8) == static_cast<unsigned char>(playStaNo)) {
            vec->x = *reinterpret_cast<float*>(mapObj + 0xC4);
            vec->y = *reinterpret_cast<float*>(mapObj + 0xD4);
            vec->z = *reinterpret_cast<float*>(mapObj + 0xE4);
            return 1;
        }
        mapObj += 0xF0;
    }

    vec->x = FLOAT_8032f9a0;
    vec->y = FLOAT_8032f9a0;
    vec->z = FLOAT_8032f9a0;
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetLightSource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetBumpLightSource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::InitMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80032784
 * PAL Size: 1132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ReadMtx(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    char path[256];
    int loadIndex = 0;
    int append = 0;

    *reinterpret_cast<unsigned char*>(self + 0x2298B) = 1;

    if (*reinterpret_cast<int*>(self + 0x229A8) != 2 && *reinterpret_cast<int*>(self + 0x229A8) != 3) {
        CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(self + 0x0);
        CTextureSet* textureSet =
            static_cast<CTextureSet*>(__nw__11CTextureSetFUlPQ27CMemory6CStagePci(0x24, stage, s_map_cpp, 0x3A9));
        if (textureSet != 0) {
            textureSet = __ct__11CTextureSetFv(textureSet);
        }
        *reinterpret_cast<CTextureSet**>(self + 0x213D8) = textureSet;
    }

    while (true) {
        sprintf(path, "%s_%d.mtx", mapName, loadIndex);

        bool exists = false;
        if (*reinterpret_cast<int*>(self + 0x229A8) == 1) {
            exists = true;
        } else {
            CFile::CHandle* openProbe = File.Open(path, 0, CFile::PRI_LOW);
            if (openProbe != 0) {
                File.Close(openProbe);
                exists = true;
            }
        }
        if (!exists) {
            break;
        }

        void* filePtr = File.m_readBuffer;
        if (*reinterpret_cast<int*>(self + 0x229A8) == 1) {
            int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
            int size = *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4));
            void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);
            Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, static_cast<unsigned long>((size + 0x1F) & ~0x1F));
            *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
            CheckSum__FPvi(filePtr, size);
            readIndex += 1;
        } else {
            CFile::CHandle* handle = File.Open(path, 0, CFile::PRI_LOW);
            if (handle == 0) {
                filePtr = 0;
            } else {
                int size = File.GetLength(handle);
                if (*reinterpret_cast<int*>(self + 0x229A8) == 3) {
                    File.ReadASync(handle);
                    filePtr = reinterpret_cast<void*>(1);
                    int& openIndex = *reinterpret_cast<int*>(self + 0x229A4);
                    *reinterpret_cast<CFile::CHandle**>(self + 0x22A2C + (openIndex * 4)) = handle;
                    openIndex += 1;
                } else {
                    File.Read(handle);
                    File.SyncCompleted(handle);
                    filePtr = File.m_readBuffer;
                    File.Close(handle);
                    if (*reinterpret_cast<int*>(self + 0x229A8) == 2) {
                        int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
                        void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);
                        Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                        *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4)) = size;
                        *reinterpret_cast<unsigned int*>(self + 0x229EC + (readIndex * 4)) = CheckSum__FPvi(filePtr, size);
                        readIndex += 1;
                        *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
                    }
                }
            }
        }

        if (filePtr == 0) {
            return;
        }

        if (*reinterpret_cast<int*>(self + 0x229A8) != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (*reinterpret_cast<int*>(self + 0x229A8) == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x54534554 && chunk.m_arg0 == 1) {
                        return;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x54534554) {
                        Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(
                            *reinterpret_cast<CTextureSet**>(self + 0x213D8),
                            &chunkFile,
                            *reinterpret_cast<CMemory::CStage**>(self + 0x0),
                            append,
                            0,
                            0,
                            0);
                        append = 1;
                        if (chunk.m_arg0 == 1) {
                            return;
                        }
                    }
                }
            }
        }

        loadIndex += 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800322c4
 * PAL Size: 1216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ReadMpl(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int loadIndex = 0;

    *reinterpret_cast<unsigned char*>(self + 0x2298B) = 1;

    while (true) {
        char path[256];
        sprintf(path, "%s_%d.mpl", mapName, loadIndex);

        bool canRead = false;
        const int readMode = *reinterpret_cast<int*>(self + 0x229A8);
        if (readMode == 1) {
            canRead = true;
        } else {
            CFile::CHandle* existsHandle = File.Open(path, 0, CFile::PRI_LOW);
            if (existsHandle != 0) {
                File.Close(existsHandle);
                canRead = true;
            }
        }

        if (!canRead) {
            if (readMode == 3) {
                return;
            }
            if (loadIndex == 0) {
                if (System.m_execParam != 0) {
                    System.Printf("CAN NOT READ OPEN %s", path);
                }
                return;
            }
            return;
        }

        if (static_cast<unsigned int>(System.m_execParam) > 2) {
            System.Printf("ReadMpl fn %s", path);
        }

        void* filePtr = File.m_readBuffer;
        if (readMode == 1) {
            int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
            const int size = *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4));
            void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);

            Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, (size + 0x1F) & ~0x1F);
            *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
            CheckSum__FPvi(filePtr, size);
            readIndex += 1;
        } else {
            CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
            if (fileHandle == 0) {
                filePtr = 0;
            } else {
                const int size = File.GetLength(fileHandle);
                if (readMode == 3) {
                    File.ReadASync(fileHandle);
                    filePtr = reinterpret_cast<void*>(1);
                    int& openIndex = *reinterpret_cast<int*>(self + 0x229A4);
                    *reinterpret_cast<CFile::CHandle**>(self + 0x22A2C + (openIndex * 4)) = fileHandle;
                    openIndex += 1;
                } else {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    filePtr = File.m_readBuffer;
                    File.Close(fileHandle);
                    if (readMode == 2) {
                        int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
                        void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);
                        Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                        *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4)) = size;
                        *reinterpret_cast<unsigned int*>(self + 0x229EC + (readIndex * 4)) = CheckSum__FPvi(filePtr, size);
                        readIndex += 1;
                        *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
                    }
                }
            }
        }

        if (filePtr == 0) {
            if (System.m_execParam != 0) {
                System.Printf("CAN NOT READ %s", path);
            }
            return;
        }

        if (readMode != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (readMode == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x4D455348 && chunk.m_arg0 == 1) {
                        return;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id != 0x4D455348) {
                        continue;
                    }

                    chunkFile.PushChunk();
                    CChunkFile::CChunk meshChunk;
                    while (chunkFile.GetNextChunk(meshChunk)) {
                        if (meshChunk.m_id == 0x56534554) {
                            short& meshCount = *reinterpret_cast<short*>(self + 0xE);
                            if (meshCount > 0x9F) {
                                return;
                            }
                            CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                            mesh->ReadOtmMesh(chunkFile, *reinterpret_cast<CMemory::CStage**>(self), 1, 1);
                        } else if (meshChunk.m_id == 0x44534554) {
                            short& meshCount = *reinterpret_cast<short*>(self + 0xE);
                            CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                            mesh->ReadOtmMesh(chunkFile, *reinterpret_cast<CMemory::CStage**>(self), 1, 1);
                            meshCount += 1;
                        }
                    }
                    chunkFile.PopChunk();

                    if (chunk.m_arg0 == 1) {
                        return;
                    }
                }
            }
        }

        loadIndex += 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800319ec
 * PAL Size: 2264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ReadOtm(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    char path[64];
    CFile::CHandle* fileHandle = 0;
    void* filePtr = File.m_readBuffer;

    *reinterpret_cast<unsigned char*>(self + 0x2298B) = 1;
    sprintf(path, "%s", mapName);
    *reinterpret_cast<int*>(self + 0x22A6C) = 0;

    const int readMode = *reinterpret_cast<int*>(self + 0x229A8);
    if (readMode == 1) {
        int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
        const int size = *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4));
        void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);

        Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, (size + 0x1F) & ~0x1F);
        *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
        CheckSum__FPvi(File.m_readBuffer, size);
        readIndex += 1;
    } else {
        fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            const int size = File.GetLength(fileHandle);
            if (readMode == 3) {
                File.ReadASync(fileHandle);
                filePtr = reinterpret_cast<void*>(1);
                int& openIndex = *reinterpret_cast<int*>(self + 0x229A4);
                *reinterpret_cast<CFile::CHandle**>(self + 0x22A2C + (openIndex * 4)) = fileHandle;
                openIndex += 1;
            } else {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                filePtr = File.m_readBuffer;
                File.Close(fileHandle);

                if (readMode == 2) {
                    int& readIndex = *reinterpret_cast<int*>(self + 0x229A0);
                    void* amemCursor = *reinterpret_cast<void**>(self + 0x22998);
                    Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                    *reinterpret_cast<int*>(self + 0x229AC + (readIndex * 4)) = size;
                    *reinterpret_cast<unsigned int*>(self + 0x229EC + (readIndex * 4)) = CheckSum__FPvi(filePtr, size);
                    readIndex += 1;
                    *reinterpret_cast<unsigned char**>(self + 0x22998) += size;
                }
            }
        } else {
            filePtr = 0;
        }
    }

    if (filePtr == 0) {
        return;
    }

    if (readMode == 2 || readMode == 3) {
        return;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(filePtr);

    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 0x4F544D20) {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id == 0x4F43544D) {
                short& octTreeCount = *reinterpret_cast<short*>(self + 0x8);
                if (octTreeCount > 0xF) {
                    return;
                }

                void* octTree = self + 0x14 + (octTreeCount * 0x4C);
                ReadOtmOctTree__8COctTreeFR10CChunkFile(octTree, chunkFile);
                octTreeCount += 1;
                continue;
            }

            if (chunk.m_id == 0x4C495448) {
                CMapLightHolder* light = reinterpret_cast<CMapLightHolder*>(
                    _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                        &Memory, 0x10, *reinterpret_cast<CMemory::CStage**>(self), s_map_cpp, 0x4D3, 0));
                if (light != 0) {
                    unsigned char* lightRaw = reinterpret_cast<unsigned char*>(light);
                    lightRaw[0] = chunkFile.Get1();
                    lightRaw[1] = chunkFile.Get1();
                    lightRaw[2] = chunkFile.Get1();
                    lightRaw[3] = chunkFile.Get1();
                    *reinterpret_cast<float*>(lightRaw + 4) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(lightRaw + 8) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(lightRaw + 0xC) = chunkFile.GetF4();

                    CPtrArray<CMapLightHolder*>* holderArray =
                        reinterpret_cast<CPtrArray<CMapLightHolder*>*>(self + 0x21450 + (chunk.m_arg0 * 0x1C));
                    holderArray->Add(light);
                }
                continue;
            }

            if (chunk.m_id != 0x5343454E) {
                continue;
            }

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 0x4D455348) {
                    short& meshCount = *reinterpret_cast<short*>(self + 0xE);
                    if (meshCount > 0x9F) {
                        return;
                    }
                    CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                    mesh->ReadOtmMesh(chunkFile, *reinterpret_cast<CMemory::CStage**>(self), 0, 1);
                    meshCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x41534554) {
                    CMapTexAnimSet* texAnimSet =
                        new (*reinterpret_cast<CMemory::CStage**>(self), s_map_cpp, 0x49A) CMapTexAnimSet();
                    *reinterpret_cast<CMapTexAnimSet**>(self + 0x213DC) = texAnimSet;
                    if (texAnimSet != 0) {
                        texAnimSet->Create(
                            chunkFile,
                            *reinterpret_cast<CMaterialSet**>(self + 0x213D4),
                            *reinterpret_cast<CTextureSet**>(self + 0x213D8));
                    }
                    continue;
                }

                if (chunk.m_id == 0x414E494D) {
                    CMapAnim* mapAnim = new (*reinterpret_cast<CMemory::CStage**>(self), s_map_cpp, 0x4BF) CMapAnim();
                    if (mapAnim != 0) {
                        mapAnim->ReadOtmAnim(chunkFile);
                        reinterpret_cast<CPtrArray<CMapAnim*>*>(self + 0x213FC)->Add(mapAnim);
                    }
                    continue;
                }

                if (chunk.m_id == 0x48495420) {
                    short& hitCount = *reinterpret_cast<short*>(self + 0xA);
                    if (hitCount > 0x1F) {
                        return;
                    }
                    CMapHit* hit = reinterpret_cast<CMapHit*>(self + 0x4D4 + (hitCount * 0x24));
                    hit->ReadOtmHit(chunkFile);
                    hitCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x4E4F4445) {
                    short& mapObjCount = *reinterpret_cast<short*>(self + 0xC);
                    if (mapObjCount > 0x1FF) {
                        return;
                    }
                    CMapObj* mapObj = reinterpret_cast<CMapObj*>(self + 0x954 + (mapObjCount * 0xF0));
                    mapObj->ReadOtmObj(chunkFile);
                    mapObjCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x4D534554) {
                    CMaterialSet* materialSet =
                        new (*reinterpret_cast<CMemory::CStage**>(self), s_map_cpp, 0x482) CMaterialSet();
                    *reinterpret_cast<CMaterialSet**>(self + 0x213D4) = materialSet;
                    if (materialSet != 0) {
                        reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(materialSet) + 8)
                            ->SetDefaultSize(0x180);
                        reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(materialSet) + 8)
                            ->SetGrow(0);
                        materialSet->Create(
                            chunkFile,
                            *reinterpret_cast<CTextureSet**>(self + 0x213D8),
                            static_cast<CMaterialMan::TEV_BIT>(0xFFF53060),
                            0);
                    }
                }
            }
            chunkFile.PopChunk();
        }
        chunkFile.PopChunk();
    }

    const short octTreeCount = *reinterpret_cast<short*>(self + 8);
    for (int i = 0; i < octTreeCount; i++) {
        unsigned char* octTreeRaw = self + 0x14 + (i * 0x4C);
        if (*reinterpret_cast<void**>(octTreeRaw + 8) != 0) {
            *reinterpret_cast<char*>(octTreeRaw + 0x1F) = static_cast<char>(i);
        }
    }

    CPtrArray<CMapShadow*>* mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>(self + 0x21434);
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        mapShadow->Init();
    }

    CMapObj* mapObj = reinterpret_cast<CMapObj*>(self + 0x954);
    CMapObj* mapObjEnd = reinterpret_cast<CMapObj*>(self + 0x954 + (*reinterpret_cast<short*>(self + 0xC) * 0xF0));
    CMapObj* root = 0;
    while (mapObj < mapObjEnd) {
        if (*reinterpret_cast<CMapObj**>(mapObj) != 0) {
            root = mapObj;
            break;
        }
        mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(mapObj) + 0xF0);
    }

    *reinterpret_cast<CMapObj**>(self + 0x228E8) = root;
    if (root == 0) {
        return;
    }

    SetLink__7CMapObjFv();

    Mtx identity;
    PSMTXIdentity(identity);
    root->CalcMtx(identity, 1);

    const int mapObjCount = *reinterpret_cast<short*>(self + 0xC);
    for (int i = 0; i < mapObjCount; i++) {
        unsigned char* obj = self + 0x954 + (i * 0xF0);
        unsigned char* atr = *reinterpret_cast<unsigned char**>(obj + 0xEC);
        if (atr == 0) {
            continue;
        }
        if (*reinterpret_cast<int*>(atr + 4) != 1 || *reinterpret_cast<int*>(atr + 0x34) == 0) {
            continue;
        }

        unsigned char lightRaw[0xB0];
        __ct__Q29CLightPcs6CLightFv(lightRaw);
        *reinterpret_cast<int*>(lightRaw + 0x8) = 1;
        *reinterpret_cast<float*>(lightRaw + 0xC) = *reinterpret_cast<float*>(obj + 0xC4);
        *reinterpret_cast<float*>(lightRaw + 0x10) = *reinterpret_cast<float*>(obj + 0xD4);
        *reinterpret_cast<float*>(lightRaw + 0x14) = *reinterpret_cast<float*>(obj + 0xE4);

        unsigned char* targetObj = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(atr + 0x10));
        Vec source;
        source.x = *reinterpret_cast<float*>(targetObj + 0xC4);
        source.y = *reinterpret_cast<float*>(targetObj + 0xD4);
        source.z = *reinterpret_cast<float*>(targetObj + 0xE4);
        Vec target;
        target.x = *reinterpret_cast<float*>(obj + 0xC4);
        target.y = *reinterpret_cast<float*>(obj + 0xD4);
        target.z = *reinterpret_cast<float*>(obj + 0xE4);
        Vec dir;
        PSVECSubtract(&source, &target, &dir);
        PSVECNormalize(&dir, &dir);

        *reinterpret_cast<float*>(lightRaw + 0x40) = dir.x;
        *reinterpret_cast<float*>(lightRaw + 0x44) = dir.y;
        *reinterpret_cast<float*>(lightRaw + 0x48) = dir.z;
        *reinterpret_cast<unsigned int*>(lightRaw + 0x4C) = *reinterpret_cast<unsigned int*>(atr + 0x34);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x20) = *reinterpret_cast<unsigned int*>(atr + 0x20);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x24) = *reinterpret_cast<unsigned int*>(atr + 0x24);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x28) = *reinterpret_cast<unsigned int*>(atr + 0x28);
        lightRaw[0x58] = atr[8];
        lightRaw[0x59] = atr[9];
        lightRaw[0x5A] = atr[10];
        lightRaw[0x5B] = atr[11];

        CLightPcs::CBumpLight* bump = LightPcs.AddBump(
            reinterpret_cast<CLightPcs::CLight*>(lightRaw),
            static_cast<CLightPcs::TARGET>(1),
            *reinterpret_cast<CMemory::CStage**>(self),
            1);
        *reinterpret_cast<CLightPcs::CBumpLight**>(atr + 0x38) = bump;

        for (int j = 0; j < mapObjCount; j++) {
            unsigned char* scan = self + 0x954 + (j * 0xF0);
            if (*reinterpret_cast<short*>(scan + 0x16) == i) {
                *reinterpret_cast<CLightPcs::CBumpLight**>(scan + 0x10) = bump;
            }
        }

    }
}

/*
 * --INFO--
 * PAL Address: 0x80031410
 * PAL Size: 1500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ReadMid(char* mapName)
{
    (void)mapName;
    // TODO
}

/*
 * --INFO--
 * PAL Address: 0x800311e8
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Calc()
{
    *reinterpret_cast<int*>(Ptr(this, 4)) += 1;

    const int mapObjCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    if (mapObjCount == 0) {
        return;
    }

    CPtrArray<CMapAnimRun*>* mapAnimRunArray = reinterpret_cast<CPtrArray<CMapAnimRun*>*>(Ptr(this, 0x213E0));
    const int mapAnimRunCount = mapAnimRunArray->GetSize();
    for (int i = 0; i < mapAnimRunCount; i++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[i];
        Calc__11CMapAnimRunFl(mapAnimRun, *reinterpret_cast<int*>(Ptr(this, 0x22A6C)));
    }

    Mtx identity;
    PSMTXIdentity(identity);

    CMapObj* mapObj = *reinterpret_cast<CMapObj**>(Ptr(this, 0x228E8));
    if (mapObj != 0) {
        mapObj->CalcMtx(identity, 0);
    }

    int& mapLightId = *reinterpret_cast<int*>(Ptr(this, 0x22A6C));
    mapLightId += 1;
    mapLightId += 1;
    if (mapLightId != 0x1E) {
        mapLightId = 0x1C;
    }

    SetLightSource();

    CPtrArray<CMapShadow*>* mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>(Ptr(this, 0x21434));
    const int mapShadowCount = mapShadowArray->GetSize();
    for (int i = 0; i < mapShadowCount; i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        mapShadow->Calc();
    }

    for (int i = 0; i < mapObjCount; i++) {
        reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)))->Calc();
    }

    CMapTexAnimSet* mapTexAnimSet = *reinterpret_cast<CMapTexAnimSet**>(Ptr(this, 0x213DC));
    if (mapTexAnimSet != 0) {
        mapTexAnimSet->Calc();
    }

    CMaterialSet* materialSet = *reinterpret_cast<CMaterialSet**>(Ptr(this, 0x213D4));
    materialSet->Calc();

    const int octTreeCount = *reinterpret_cast<short*>(Ptr(this, 8));
    for (int i = 0; i < octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x38)));
        LightPcs.InsertOctTree(static_cast<CLightPcs::TARGET>(1), *octTree);
    }

    for (int i = 0; i < octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x38)));
        CMapShadowInsertOctTree(static_cast<CMapShadow::TARGET>(1), *octTree);
    }

    for (int i = 0; i < octTreeCount; i++) {
        SetDrawFlag__8COctTreeFv(Ptr(this, 0x14 + (i * 0x38)));
    }

    for (int i = 0; i < mapObjCount; i++) {
        reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)))->SetDrawFlag();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawMapShadow()
{
    if (*reinterpret_cast<short*>(Ptr(this, 0xC)) != 0) {
        CPtrArray<CMapShadow*>* mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>(Ptr(this, 0x21434));
        for (unsigned int i = 0; i < mapShadowArray->GetSize(); i++) {
            CMapShadow* mapShadow = (*mapShadowArray)[i];
            mapShadow->Draw();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setDbgLight(int, Vec&, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80031084
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DrawBefore()
{
    const short mapObjCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    if ((mapObjCount == 0) || (*reinterpret_cast<unsigned char*>(Ptr(this, 0x2298B)) == 0)) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    if ((DAT_8032ecb8 & 8) == 0) {
        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            Draw__7CMapObjFUc(mapObj, 0xFE);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        const short octTreeCount = *reinterpret_cast<short*>(Ptr(this, 8));
        void* octTree = Ptr(this, 0x14);
        for (int i = 0; i < octTreeCount; i++) {
            Draw__8COctTreeFUc(octTree, 0xFF);
            octTree = Ptr(octTree, 0x38);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80030394
 * PAL Size: 3312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Draw()
{
    const short mapObjCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    if ((mapObjCount == 0) || (*reinterpret_cast<unsigned char*>(Ptr(this, 0x2298B)) == 0)) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    Mtx44 projection;
    PSMTX44Copy(reinterpret_cast<float(*)[4]>(Ptr(CameraPcs, 0x94)), projection);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    *reinterpret_cast<unsigned char*>(Ptr(this, 0x2298A)) = 1;

    if ((DAT_8032ecb8 & 8) == 0) {
        const short octTreeCount = *reinterpret_cast<short*>(Ptr(this, 8));

        void* octTree = Ptr(this, 0x14);
        for (int i = 0; i < octTreeCount; i++) {
            Draw__8COctTreeFUc(octTree, 0);
            octTree = Ptr(octTree, 0x38);
        }

        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            Draw__7CMapObjFUc(mapObj, 0x40);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        PartPcs.DrawShoki();

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(1, GX_LEQUAL, 1);
        LightPcs.SetNumDiffuse(0);

        mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            Draw__7CMapObjFUc(mapObj, 0);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        octTree = Ptr(this, 0x14);
        for (int i = 0; i < octTreeCount; i++) {
            Draw__8COctTreeFUc(octTree, 1);
            octTree = Ptr(octTree, 0x38);
        }
    }

    if ((DAT_8032ecb8 & 8) != 0) {
        _GXColor clearColor;
        clearColor.r = 0xFF;
        clearColor.g = 0xFF;
        clearColor.b = 0xFF;
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);
    }

    if ((DAT_8032ecb8 & 4) != 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
        GXSetZCompLoc(0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        _GXColor wireColor;
        wireColor.r = 0x80;
        wireColor.g = 0x80;
        wireColor.b = 0x80;
        wireColor.a = 0x80;
        GXSetChanMatColor(GX_COLOR0A0, wireColor);

        SetOffsetZBuff__10CCameraPcsFf(static_cast<double>(FLOAT_8032f9bc), &CameraPcs);

        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->DrawHitWire();
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->DrawHitNormal();
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        SetOffsetZBuff__10CCameraPcsFf(static_cast<double>(FLOAT_8032f9a0), &CameraPcs);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80030280
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DrawAfter()
{
    const short mapObjCount = *reinterpret_cast<short*>(Ptr(this, 0xC));
    if ((mapObjCount == 0) || (*reinterpret_cast<unsigned char*>(Ptr(this, 0x2298B)) == 0)) {
        return;
    }

    Mtx44 projection;
    PSMTX44Copy(reinterpret_cast<float(*)[4]>(Ptr(CameraPcs, 0x94)), projection);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    if (DAT_8032ecb8 == 0) {
        void* octTree = Ptr(this, 0x14);
        const short octTreeCount = *reinterpret_cast<short*>(Ptr(this, 8));
        for (int i = 0; i < octTreeCount; i++) {
            Draw__8COctTreeFUc(octTree, 2);
            octTree = Ptr(octTree, 0x4C);
        }

        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(&MapMng, 0x954));
        for (int i = 0; i < mapObjCount; i++) {
            Draw__7CMapObjFUc(mapObj, 2);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003007c
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::CheckHitCylinder(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((FLOAT_8032f9a0 == move->x) && (FLOAT_8032f9a0 == move->y) && (FLOAT_8032f9a0 == move->z)) {
        return 0;
    }

    if ((move->x <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->x) && (move->y <= FLOAT_8032f9a4) &&
        (FLOAT_8032f9a8 <= move->y) && (move->z <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->z)) {
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801ead4c);
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801d73c4, static_cast<double>(move->x), static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801ead4c);
        }
    }

    DAT_8032ec78 = -2;
    FLOAT_8032ec80 = FLOAT_8032f9ac;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 8)); i++) {
        unsigned char* octTree = Ptr(this, 0x14 + (i * 0x38));
        if (CheckHitCylinder__8COctTreeFP12CMapCylinderP3VecUl(octTree, cylinder, move, mask) != 0) {
            *reinterpret_cast<void**>(Ptr(this, 0x22A78)) = *reinterpret_cast<void**>(octTree + 8);
            return 1;
        }
    }

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 0xC)); i++) {
        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)));
        *reinterpret_cast<CMapObj**>(Ptr(this, 0x22A78)) = mapObj;
        if (mapObj->CheckHitCylinder(cylinder, move, mask) != 0) {
            return 1;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002fe6c
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    int hit = 0;

    if ((FLOAT_8032f9a0 == move->x) && (FLOAT_8032f9a0 == move->y) && (FLOAT_8032f9a0 == move->z)) {
        return 0;
    }

    if ((move->x <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->x) && (move->y <= FLOAT_8032f9a4) &&
        (FLOAT_8032f9a8 <= move->y) && (move->z <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->z)) {
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801ead4c);
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801d7384, static_cast<double>(move->x), static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(DAT_801ead4c);
        }
    }

    DAT_8032ec78 = -2;
    FLOAT_8032ec80 = FLOAT_8032f9ac;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 8)); i++) {
        unsigned char* octTree = Ptr(this, 0x14 + (i * 0x38));
        DAT_8032ec88 = 0;
        CheckHitCylinderNear__8COctTreeFP12CMapCylinderP3VecUl(octTree, cylinder, move, mask);
        if (DAT_8032ec88 != 0) {
            hit = 1;
            *reinterpret_cast<void**>(Ptr(this, 0x22A78)) = *reinterpret_cast<void**>(octTree + 8);
        }
    }

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 0xC)); i++) {
        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)));
        DAT_8032ec88 = 0;
        mapObj->CheckHitCylinderNear(cylinder, move, mask);
        if (DAT_8032ec88 != 0) {
            hit = 1;
            *reinterpret_cast<CMapObj**>(Ptr(this, 0x22A78)) = mapObj;
        }
    }

    return hit;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunMapObj(CMapObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunID(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002fdb0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetViewMtx(float (*viewMtx)[4], float (*projMtx)[4])
{
    float* proj = reinterpret_cast<float*>(projMtx);
    float scaleY = lbl_8032F994 * proj[5];
    float scaleX = proj[0];
    Mtx* viewCopy = reinterpret_cast<Mtx*>(Ptr(this, 0x228F8));

    PSMTXCopy(viewMtx, *viewCopy);
    PSMTXScaleApply(
        *viewCopy, *reinterpret_cast<Mtx*>(Ptr(this, 0x22928)), lbl_8032F990 * scaleX, scaleY, lbl_8032F998);
    PSMTXScaleApply(
        *viewCopy, *reinterpret_cast<Mtx*>(Ptr(this, 0x22958)), lbl_8032F99C * scaleX, scaleY, lbl_8032F998);
}

/*
 * --INFO--
 * PAL Address: 0x8002fd9c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetIdGrpMask(int mapIdGrpIndex, unsigned long mask)
{
    int offset = mapIdGrpIndex * 0x14;
    offset += 0x214E8;
    *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(this) + offset) = mask;
}

/*
 * --INFO--
 * PAL Address: 0x8002fcb4
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetIdGrpColor(int mapIdGrpIndex, int channelIndex, _GXColor color)
{
    unsigned char* mapIdGrp = Ptr(this, 0x214E8 + (mapIdGrpIndex * 0x14));
    unsigned char* colorBytes = reinterpret_cast<unsigned char*>(&color);

    if (channelIndex == 2) {
        mapIdGrp[0xC] = colorBytes[0];
        mapIdGrp[0xD] = colorBytes[1];
        mapIdGrp[0xE] = colorBytes[2];
        mapIdGrp[0xF] = colorBytes[3];
        return;
    }

    if (channelIndex > 1) {
        if (channelIndex > 3) {
            return;
        }
        mapIdGrp[0x10] = colorBytes[0];
        mapIdGrp[0x11] = colorBytes[1];
        mapIdGrp[0x12] = colorBytes[2];
        mapIdGrp[0x13] = colorBytes[3];
        return;
    }

    if (channelIndex == 0) {
        mapIdGrp[4] = colorBytes[0];
        mapIdGrp[5] = colorBytes[1];
        mapIdGrp[6] = colorBytes[2];
        mapIdGrp[7] = colorBytes[3];
        return;
    }

    if (channelIndex < 0) {
        return;
    }

    mapIdGrp[8] = colorBytes[0];
    mapIdGrp[9] = colorBytes[1];
    mapIdGrp[10] = colorBytes[2];
    mapIdGrp[11] = colorBytes[3];
}

/*
 * --INFO--
 * PAL Address: 0x8002fb4c
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMeshCameraSemiTransRange(unsigned short id, float nearRange, float farRange, float minAlpha,
                                          float maxAlpha, float fadeRange)
{
    bool found = false;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 0xC)); i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == id) {
            *reinterpret_cast<float*>(mapObj + 0x998) = nearRange;
            *reinterpret_cast<float*>(mapObj + 0x99C) = farRange;
            *reinterpret_cast<float*>(mapObj + 0x9A8) = fadeRange;
            *reinterpret_cast<float*>(mapObj + 0x9A0) = minAlpha;
            *reinterpret_cast<float*>(mapObj + 0x9A4) = maxAlpha;
            if (*reinterpret_cast<void**>(mapObj + 0x960) != 0 && *reinterpret_cast<signed char*>(mapObj + 0x973) != -1) {
                *reinterpret_cast<float*>(mapObj + 0x9A0) = FLOAT_8032f988;
                *reinterpret_cast<float*>(mapObj + 0x9A4) = FLOAT_8032f98c;
                *reinterpret_cast<unsigned char*>(mapObj + 0x969) = 2;
                *reinterpret_cast<unsigned char*>(mapObj + 0x97A) = 1;
            }
            *reinterpret_cast<short*>(mapObj + 0x97E) = 0x4000;
            found = true;
            *reinterpret_cast<short*>(mapObj + 0x97C) = 0x4000;
            *reinterpret_cast<short*>(mapObj + 0x980) = 0;
        }
        mapObj += 0xF0;
    }

    if (!found) {
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801ead4c);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801d7350, id);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801ead4c);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_8032f984);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002fa2c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMeshCameraSemiTransAlpha(unsigned short id, int alpha, int frameCount)
{
    bool found = false;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < *reinterpret_cast<short*>(Ptr(this, 0xC)); i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == id) {
            *reinterpret_cast<short*>(mapObj + 0x97E) = static_cast<short>(alpha << 7);
            found = true;
            *reinterpret_cast<short*>(mapObj + 0x980) = static_cast<short>(
                (static_cast<int>(*reinterpret_cast<short*>(mapObj + 0x97E)) -
                 static_cast<int>(*reinterpret_cast<short*>(mapObj + 0x97C))) /
                frameCount);
        }
        mapObj += 0xF0;
    }

    if (!found) {
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801ead4c);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801d7318, id);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_801ead4c);
        }
        if (System.m_execParam >= 1) {
            System.Printf(DAT_8032f984);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjIdx(unsigned short id)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == id) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
    }

    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterial* CMapMng::GetMaterialID(unsigned char materialId)
{
    unsigned long index = 0;
    unsigned char* materialSet = *reinterpret_cast<unsigned char**>(reinterpret_cast<unsigned char*>(this) + 0x213D4);
    CPtrArray<CMaterial*>* materials = reinterpret_cast<CPtrArray<CMaterial*>*>(materialSet + 8);

    while (index < UnkMaterialSetGetter(materials)) {
        CMaterial* material = (*materials)[index];
        if (material != 0 && reinterpret_cast<unsigned char*>(material)[0xA6] == materialId) {
            return (*materials)[index];
        }
        index++;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjEffectIdx(unsigned short effectId)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x984) == effectId) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8002f8b4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjLMtx(int mapObjIndex, float (*source)[4])
{
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
    PSMTXCopy(source, *reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(mapObj) + 0x88));
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(mapObj) + 0x1C) = 1;
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(mapObj) + 0x1B) = 1;
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(mapObj) + 0x1C) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002f880
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::GetMapObjWMtx(int mapObjIndex, float (*destination)[4])
{
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
    PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(mapObj) + 0xB8), destination);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjAnim(int mapObjIndex, int startFrame, int endFrame, int loop)
{
    CPtrArray<CMapAnimRun*>* mapAnimRunArray = reinterpret_cast<CPtrArray<CMapAnimRun*>*>(Ptr(this, 0x213E0));
    CPtrArray<CMapAnim*>* mapAnimArray = reinterpret_cast<CPtrArray<CMapAnim*>*>(Ptr(this, 0x213FC));
    CMapAnimRun* foundMapAnimRun = 0;
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
    int mapAnimRunCount = mapAnimRunArray->GetSize();

    for (unsigned int mapAnimRunIndex = 0; mapAnimRunIndex < static_cast<unsigned int>(mapAnimRunCount); mapAnimRunIndex++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[mapAnimRunIndex];
        unsigned short mapAnimIndex = *reinterpret_cast<unsigned short*>(Ptr(mapAnimRun, 0x12));
        CPtrArray<CMapAnimNode*>* mapAnimNodeArray = reinterpret_cast<CPtrArray<CMapAnimNode*>*>((*mapAnimArray)[mapAnimIndex]);
        int mapAnimNodeCount = mapAnimNodeArray->GetSize();

        for (int mapAnimNodeIndex = 0; mapAnimNodeIndex < mapAnimNodeCount; mapAnimNodeIndex++) {
            CMapAnimNode* mapAnimNode = (*mapAnimNodeArray)[mapAnimNodeIndex];
            if (reinterpret_cast<CMapObj*>(*reinterpret_cast<int*>(mapAnimNode)) == mapObj) {
                foundMapAnimRun = mapAnimRun;
                goto startMapObjAnim;
            }
        }
    }

startMapObjAnim:
    foundMapAnimRun->Start(startFrame, endFrame, loop);
}

/*
 * --INFO--
 * PAL Address: 0x8002f710
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapAnimID(int animId, int startFrame, int endFrame, int loop)
{
    CPtrArray<CMapAnimRun*>* mapAnimRunArray = reinterpret_cast<CPtrArray<CMapAnimRun*>*>(Ptr(this, 0x213E0));
    CMapAnimRun* mapAnimRun = 0;
    int mapAnimRunCount = mapAnimRunArray->GetSize();

    for (unsigned long i = 0; i < static_cast<unsigned long>(mapAnimRunCount); i++) {
        CMapAnimRun* current = (*mapAnimRunArray)[i];
        if (*reinterpret_cast<unsigned char*>(Ptr(current, 1)) == static_cast<unsigned char>(animId)) {
            mapAnimRun = current;
            break;
        }
    }

    mapAnimRun->Start(startFrame, endFrame, loop);
}

/*
 * --INFO--
 * PAL Address: 0x8002f6d4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjMime(int mapObjIndex, int mode, int target, int type)
{
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
    mapObj->SetMime(mode, target, type);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapTexAnim(int materialId, int frameStart, int frameEnd, int wrapMode)
{
    CMapTexAnimSet* mapTexAnimSet = *reinterpret_cast<CMapTexAnimSet**>(reinterpret_cast<unsigned char*>(this) + 0x213DC);
    mapTexAnimSet->SetMapTexAnim(materialId, frameStart, frameEnd, wrapMode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObj(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjID(int id, int show)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < objCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == static_cast<unsigned int>(id)) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapObj += 0xF0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjChild(int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002f5f0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ShowMapObjChildID(int id, int show)
{
    CMapMng* mapMng = this;
    int mapObjCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);

    for (int i = 0; i < mapObjCount; i++) {
        if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(mapMng) + 0x982) ==
            static_cast<unsigned int>(id)) {
            reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(mapMng) + 0x954)->SetShow(show);
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(mapMng) + 0xF0);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapMeshID(int id, int show)
{
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < objCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == static_cast<unsigned int>(id)) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapObj += 0xF0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjPrioID(int id, unsigned char prio)
{
    int i = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC)) {
        if (static_cast<int>(*reinterpret_cast<unsigned short*>(mapObj + 0x982)) == id) {
            *reinterpret_cast<unsigned char*>(mapObj + 0x969) = prio;
            *reinterpret_cast<unsigned char*>(mapObj + 0x968) = prio;
        }
        mapObj += 0xF0;
        i++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjTransRate(int mapObjIndex, float x, float y, float z)
{
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954;
    *reinterpret_cast<float*>(mapObj + 0x58) = x;
    *reinterpret_cast<float*>(mapObj + 0x5C) = y;
    *reinterpret_cast<float*>(mapObj + 0x60) = z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjWorldMapLightIdx(int, _GXColor, Vec)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002f47c
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjWorldMapLightID(int id, _GXColor color, Vec position)
{
    int objIndex = 0;
    int numMapObj = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* scan = reinterpret_cast<unsigned char*>(this);

    while (0 < numMapObj) {
        if (*reinterpret_cast<unsigned short*>(scan + 0x982) == static_cast<unsigned short>(id)) {
            goto found;
        }
        scan += 0xF0;
        objIndex++;
        numMapObj--;
    }
    objIndex = -1;

found:
    const unsigned int packedColor = *reinterpret_cast<unsigned int*>(&color);
    const float posX = position.x;
    const float posY = position.y;
    const float posZ = position.z;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (objIndex * 0xF0) + 0x954;
    unsigned char* mapObjLight = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);

    if (*reinterpret_cast<int*>(mapObjLight + 4) == 1) {
        const unsigned char* colorBytes = reinterpret_cast<const unsigned char*>(&packedColor);
        *reinterpret_cast<unsigned char*>(mapObjLight + 8) = colorBytes[0];
        *reinterpret_cast<unsigned char*>(mapObjLight + 9) = colorBytes[1];
        *reinterpret_cast<unsigned char*>(mapObjLight + 10) = colorBytes[2];
        *reinterpret_cast<unsigned char*>(mapObjLight + 11) = colorBytes[3];
        *reinterpret_cast<float*>(mapObj + 0x70) = posX;
        *reinterpret_cast<float*>(mapObj + 0x74) = posY;
        *reinterpret_cast<float*>(mapObj + 0x78) = posZ;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1C) = 1;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1B) = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002f46c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeOctTree(float drawRange)
{
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x22A70) = -drawRange;
}

/*
 * --INFO--
 * PAL Address: 0x8002f45c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeMapObj(float drawRange)
{
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x22A74) = -drawRange;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetDraw(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetFogEnable()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800342a0
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_map_cpp(void)
{
    __construct_array(Ptr(&MapMng, 0x14), __ct__8COctTreeFv, __dt__8COctTreeFv, 0x4C, 0x10);
    __construct_array(Ptr(&MapMng, 0x4D4), __ct__7CMapHitFv, __dt__7CMapHitFv, 0x24, 0x20);
    __construct_array(Ptr(&MapMng, 0x954), __ct__7CMapObjFv, __dt__7CMapObjFv, 0xF0, 0x200);
    __construct_array(Ptr(&MapMng, 0x1E954), __ct__8CMapMeshFv, __dt__8CMapMeshFv, 0x44, 0xA0);

    InitPtrArrayRaw(Ptr(&MapMng, 0x213E0));
    InitPtrArrayRaw(Ptr(&MapMng, 0x213FC));
    InitPtrArrayRaw(Ptr(&MapMng, 0x21418));
    InitPtrArrayRaw(Ptr(&MapMng, 0x21434));

    InitPtrArrayRaw(Ptr(&MapMng, 0x21450));
    InitPtrArrayRaw(Ptr(&MapMng, 0x2146C));

    __construct_array(Ptr(&MapMng, 0x214E4), __ct__9CMapIdGrpFv, 0, 0x14, 0x100);
    __register_global_object(&MapMng, reinterpret_cast<void*>(__dt__7CMapMngFv), &Vec_80245758);
}

/*
 * --INFO--
 * PAL Address: 0x80034750
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapMng::~CMapMng()
{
    if (this != 0) {
        CPtrArray<CMapLightHolder*>* mapLightHolderArr = reinterpret_cast<CPtrArray<CMapLightHolder*>*>(Ptr(this, 0x21450));
        mapLightHolderArr[0].~CPtrArray();
        mapLightHolderArr[1].~CPtrArray();
        if (this != reinterpret_cast<CMapMng*>(0xFFFDEBCC)) {
            reinterpret_cast<CPtrArray<CMapShadow*>*>(Ptr(this, 0x21434))->~CPtrArray();
        }
        if (this != reinterpret_cast<CMapMng*>(0xFFFDEBE8)) {
            reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(Ptr(this, 0x21418))->~CPtrArray();
        }
        if (this != reinterpret_cast<CMapMng*>(0xFFFDEC04)) {
            reinterpret_cast<CPtrArray<CMapAnim*>*>(Ptr(this, 0x213FC))->~CPtrArray();
        }
        if (this != reinterpret_cast<CMapMng*>(0xFFFDEC20)) {
            reinterpret_cast<CPtrArray<CMapAnimRun*>*>(Ptr(this, 0x213E0))->~CPtrArray();
        }
        __destroy_arr(Ptr(this, 0x1E954), (void*)__dt__8CMapMeshFv, 0x44, 0xA0);
        __destroy_arr(Ptr(this, 0x954), (void*)__dt__7CMapObjFv, 0xF0, 0x200);
        __destroy_arr(Ptr(this, 0x4D4), (void*)__dt__7CMapHitFv, 0x24, 0x20);
        __destroy_arr(Ptr(this, 0x14), (void*)__dt__8COctTreeFv, 0x4C, 0x10);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMng::CMapMng()
{
	// TODO
}
