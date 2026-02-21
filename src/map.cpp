#include "ffcc/map.h"
#include "ffcc/chunkfile.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/maphit.h"
#include "ffcc/mapshadow.h"
#include "ffcc/maptexanim.h"
#include "ffcc/materialman.h"
#include "ffcc/p_light.h"
#include "ffcc/system.h"

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void __destroy_arr(void*, void*, unsigned long, unsigned long);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dt__8COctTreeFv(void*, int);
extern "C" void __dt__7CMapHitFv(void*, int);
extern "C" void __dt__7CMapObjFv(void*, int);
extern "C" void __dt__8CMapMeshFv(void*, int);
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
extern "C" void Calc__11CMapAnimRunFl(CMapAnimRun*, long);
extern "C" void* lbl_801E89A8[];
extern "C" void* lbl_801E899C[];
extern "C" void* lbl_801E8990[];
extern "C" void* lbl_801E8984[];
extern "C" void* lbl_801E8978[];
extern int DAT_8032ec78;
extern float FLOAT_8032ec80;
extern unsigned char DAT_8032ec88;
extern float FLOAT_8032f9a0;
extern float FLOAT_8032f9a4;
extern float FLOAT_8032f9a8;
extern float FLOAT_8032f9ac;
extern char DAT_801ead4c[];
extern char DAT_801d7384[];
extern char DAT_801d73c4[];
extern CLightPcs LightPcs;
extern CMath Math;

static char s_map_cpp[] = "map.cpp";
static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Create()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMap()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::MapFileRead(char*, unsigned long&)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::AttachMapHit(CMapHit*, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetDebugPlaySta(int, Vec*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMtx(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMpl(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadOtm(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ReadMid(char*)
{
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
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawBefore()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::Draw()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DrawAfter()
{
	// TODO
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
    unsigned char* mapIdGrp = reinterpret_cast<unsigned char*>(this) + offset;
    *reinterpret_cast<unsigned long*>(mapIdGrp + 0x214E8) = mask;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetIdGrpColor(int, int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMeshCameraSemiTransRange(unsigned short, float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMeshCameraSemiTransAlpha(unsigned short, int, int)
{
	// TODO
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
void CMapMng::SetMapObjAnim(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapAnimID(int, int, int, int)
{
	// TODO
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
