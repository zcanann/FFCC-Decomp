#include "ffcc/texanim.h"
#include "ffcc/system.h"
#include "ffcc/math.h"

#include <string.h>
#include <math.h>
#include "dolphin/mtx.h"

template <class T>
class CPtrArray
{
public:
    int m_size;
    int m_numItems;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    virtual ~CPtrArray();

    bool Add(T item);
    int GetSize();
    void RemoveAll();
    void ReleaseAndRemoveAll();
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    int setSize(unsigned long newSize);
    T GetAt(unsigned long index);
};

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* PTR_PTR_s_CTexAnimSet_801e9c6c;
extern "C" float FLOAT_8032fb38;
extern "C" int Rand__5CMathFUl(CMath*, unsigned long);

extern CMemory Memory;
extern CSystem System;
extern CMath Math;
extern float FLOAT_8032fb3c;
extern float FLOAT_8032fb4c;
extern double DOUBLE_8032fb40;

static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline float& F32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(p, offset));
}

static inline int& S32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(p, offset));
}

static inline unsigned int& U32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned int*>(Ptr(p, offset));
}

static inline unsigned char& U8At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(p, offset));
}
}

/*
 * --INFO--
 * PAL Address: 0x80044ae8
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexAnimSeq*>::CPtrArray()
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
 * PAL Address: 0x80044b1c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexAnimSeq*>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x80044b78
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CTexAnimSeq*>::Add(CTexAnimSeq* item)
{
    if (setSize(m_numItems + 1) != 0) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
        return true;
    }
    return false;
}

/*
 * --INFO--
 * PAL Address: 0x80044be8
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexAnimSeq*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80044bf0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnimSeq*>::RemoveAll()
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
 * PAL Address: 0x80044c3c
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnimSeq*>::ReleaseAndRemoveAll()
{
    int offset = 0;

    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if ((refCount - 1 == 0) && (item != 0)) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }

    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80044d08
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexAnimSeq* CPtrArray<CTexAnimSeq*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80044d28
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnimSeq*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80044d30
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexAnimSeq*>::setSize(unsigned long newSize)
{
    CTexAnimSeq** newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnimSeq**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h, 0xFA, 0);
        if (newItems == 0) {
            return 0;
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

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80045158
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexAnimSeq* CPtrArray<CTexAnimSeq*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80044e20
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexAnim*>::CPtrArray()
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
 * PAL Address: 0x80044e54
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexAnim*>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x80044eb0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CTexAnim*>::Add(CTexAnim* item)
{
    if (setSize(m_numItems + 1) != 0) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
        return true;
    }
    return false;
}

/*
 * --INFO--
 * PAL Address: 0x80044f20
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexAnim*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80044f28
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnim*>::RemoveAll()
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
 * PAL Address: 0x80044f74
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnim*>::ReleaseAndRemoveAll()
{
    int offset = 0;

    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if ((refCount - 1 == 0) && (item != 0)) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }

    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80045040
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexAnim* CPtrArray<CTexAnim*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80045060
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexAnim*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x80045068
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexAnim*>::setSize(unsigned long newSize)
{
    CTexAnim** newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnim**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h, 0xFA, 0);
        if (newItems == 0) {
            return 0;
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

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80045168
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexAnim* CPtrArray<CTexAnim*>::GetAt(unsigned long index)
{
    return m_items[index];
}
/*
 * --INFO--
 * PAL Address: 0x80044a9c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnimSet::CTexAnimSet()
{
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = &PTR_PTR_s_CTexAnimSet_801e9c6c;
    CPtrArray<CTexAnim*>* const arr = reinterpret_cast<CPtrArray<CTexAnim*>*>(Ptr(this, 8));
    arr->m_size = 0;
    arr->m_numItems = 0;
    arr->m_defaultSize = 0x10;
    arr->m_items = 0;
    arr->m_stage = 0;
    arr->m_growCapacity = 1;
    F32At(this, 0x24) = FLOAT_8032fb38;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnimSet::~CTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSet::Create(CChunkFile&, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSet::Duplicate(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSet::AttachMaterialSet(CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800440ec
 * PAL Size: 852b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSet::AddFrame()
{
    unsigned int i = 0;
    CPtrArray<CTexAnim*>* texAnims = reinterpret_cast<CPtrArray<CTexAnim*>*>(Ptr(this, 8));

    while (i < (unsigned int)texAnims->GetSize()) {
        CTexAnim* texAnim = (*texAnims)[i];
        CPtrArray<CTexAnimSeq*>* seqArray = reinterpret_cast<CPtrArray<CTexAnimSeq*>*>(Ptr(texAnim, 0x110));
        CTexAnimSeq* seq = (*seqArray)[S32At(texAnim, 0x0C)];
        unsigned char flags = U8At(seq, 0x110);
        float frameStep = FLOAT_8032fb3c;

        if ((flags & 0x80) != 0) {
            frameStep = FLOAT_8032fb4c;
        }

        if (((flags & 0x40) == 0) || (FLOAT_8032fb3c != F32At(texAnim, 0x10)) || (Rand__5CMathFUl(&Math, 0x1E) == 0)) {
            float currentFrame = (float)fmod((double)F32At(texAnim, 0x10), (double)(float)U32At(seq, 0x108));
            int keyCount = S32At(seq, 0x10C);
            unsigned int* keyData = reinterpret_cast<unsigned int*>(Ptr(seq, 0x114));
            unsigned int keyIndex = 0;
            unsigned int lastKeyIndex = keyCount - 1;

            while (keyCount != 0) {
                float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[0xC] : U32At(seq, 0x108));
                unsigned int* nextKeyData = keyData;

                if (keyIndex < lastKeyIndex) {
                    nextKeyData = keyData + 0xC;
                }

                if (((float)keyData[0] <= currentFrame) && (currentFrame < nextFrame)) {
                    float t = FLOAT_8032fb38;
                    float frameSpan = nextFrame - (float)keyData[0];
                    if (frameSpan != FLOAT_8032fb38) {
                        t = (currentFrame - (float)keyData[0]) / frameSpan;
                    }

                    Vec v0;
                    Vec v1;
                    PSVECScale(reinterpret_cast<Vec*>(keyData + 9), &v0, FLOAT_8032fb3c - t);
                    PSVECScale(reinterpret_cast<Vec*>(nextKeyData + 9), &v1, t);
                    PSVECAdd(&v0, &v1, reinterpret_cast<Vec*>(Ptr(texAnim, 0x18)));

                    if ((flags & 0x80) == 0) {
                        U32At(texAnim, 0x18) = keyData[9];
                        U32At(texAnim, 0x1C) = keyData[10];
                    }
                    break;
                }

                keyData += 0xC;
                keyIndex = keyIndex + 1;
                keyCount = keyCount - 1;
            }

            if (S32At(texAnim, 0x14) != -3) {
                F32At(texAnim, 0x10) = F32At(texAnim, 0x10) + frameStep;
                if ((float)U32At(seq, 0x108) <= F32At(texAnim, 0x10)) {
                    int mode = S32At(texAnim, 0x14);
                    if (mode == -1) {
                        F32At(texAnim, 0x10) = (float)U32At(seq, 0x108);
                    } else if (mode >= 0) {
                        S32At(texAnim, 0x0C) = mode;
                        S32At(texAnim, 0x14) = -2;
                    }
                    F32At(texAnim, 0x10) = F32At(texAnim, 0x10) - (float)U32At(seq, 0x108);
                }
            }
        }

        seq = (*seqArray)[S32At(texAnim, 0x0C)];
        if ((U8At(seq, 0x110) & 0x40) != 0) {
            F32At(this, 0x24) = F32At(texAnim, 0x20);
        } else {
            F32At(this, 0x24) = FLOAT_8032fb38;
        }

        i = i + 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSet::Change(char*, float, CTexAnimSet::ANIM_TYPE)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSet::SetTexGen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnim::CTexAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnim::~CTexAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::Create(CChunkFile&, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::Duplicate(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::AttachMaterialSet(CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::AddFrame(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::Find(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::Change(int, float, CTexAnimSet::ANIM_TYPE)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::SetTexGen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::IsChin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnim::GetChin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnim::CRefData::CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnim::CRefData::~CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnimSeq::CTexAnimSeq()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexAnimSeq::~CTexAnimSeq()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSeq::Create(CChunkFile&, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSeq::Interp(float, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSeq::GetTotalFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSeq::GetName()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexAnimSeq::IsChin()
{
	// TODO
}
