#include "ffcc/texanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/materialman.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"
#include "ffcc/math.h"

#include <string.h>
#include <math.h>
#include "dolphin/mtx.h"

template <class T>
class CPtrArray
{
public:
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

    int m_numItems;
    int m_size;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* __vt__11CTexAnimSet[];
extern "C" void* __vt__8CTexAnim[];
extern "C" void* __vt__11CTexAnimSeq[];
extern "C" void* __vt__Q28CTexAnim8CRefData[];
extern "C" void __ct__21CPtrArray_P8CTexAnim_Fv(void*);
extern "C" void __ct__25CPtrArray_P11CTexAnimSeq_Fv(void*);
extern "C" void __dt__21CPtrArray_P8CTexAnim_Fv(void*, int);
extern "C" void __dt__25CPtrArray_P11CTexAnimSeq_Fv(void*, int);
extern "C" int GetSize__21CPtrArray_P8CTexAnim_Fv(void*);
extern "C" int GetSize__25CPtrArray_P11CTexAnimSeq_Fv(void*);
extern "C" void* __vc__21CPtrArray_P8CTexAnim_FUl(void*, unsigned long);
extern "C" void* __vc__25CPtrArray_P11CTexAnimSeq_FUl(void*, unsigned long);
extern "C" {
char s_texanim_cpp_801d7adc[] = "texanim.cpp";
}
static const char DAT_8032fb48[] = "e1";
const float FLOAT_8032fb38 = 0.0f;
const float FLOAT_8032fb3c = 1.0f;
const float FLOAT_8032fb4c = 1.25f;
const double DOUBLE_8032fb40 = 4503599627370496.0;

static char s_collection_ptrarray_h_801D7B30[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error_801D7B14[] = "CPtrArray grow error";

inline void* operator new(unsigned long, void* p)
{
    return p;
}

namespace {
struct RefObject
{
    void* vtable;
    int refCount;
};

struct CTexAnimStorage
{
    void* vtable;
    int refCount;
    void* refData;
    int unk0C;
    float unk10;
    int unk14;
    float unk18;
    float unk1C;
    float unk20;
};

struct CTexAnimSetStorage
{
    void* vtable;
    int refCount;
    CPtrArray<CTexAnim*> texAnims;
    float unk24;
};

struct CTexAnimRefDataStorage
{
    void* vtable;
    int refCount;
    char name[0x100];
    void* material;
    int texSrtIndex;
    CPtrArray<CTexAnimSeq*> texAnimSeqs;
};

struct CTexAnimSeqStorage
{
    void* vtable;
    int refCount;
    char name[0x100];
    unsigned int totalFrames;
    int keyCount;
    unsigned char flags;
    unsigned char pad111[3];
    unsigned int* keys;
};

struct CTexScrollStorage
{
    unsigned char type0;
    unsigned char type1;
    unsigned char pad[2];
    float u0;
    float v0;
    float u1;
    float v1;
};

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

static inline void ReleaseRef(void** slot)
{
    int* ref = reinterpret_cast<int*>(*slot);
    if (ref != 0) {
        const int nextRefCount = ref[1] - 1;
        ref[1] = nextRefCount;
        if (nextRefCount == 0) {
            reinterpret_cast<void (**)(int*, int)>(*ref)[2](ref, 1);
        }
        *slot = 0;
    }
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
    if (setSize(m_numItems + 1) == 0) {
        return false;
    }
    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return true;
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
        if ((unsigned long)m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error_801D7B14);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnimSeq**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h_801D7B30, 0xFA, 0);
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
#pragma dont_inline on
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
    if (setSize(m_numItems + 1) == 0) {
        return false;
    }
    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return true;
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
        if ((unsigned long)m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error_801D7B14);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnim**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h_801D7B30, 0xFA, 0);
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
#pragma dont_inline reset
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
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);

    __ct__4CRefFv(this);
    self->vtable = __vt__11CTexAnimSet;
    __ct__21CPtrArray_P8CTexAnim_Fv(&self->texAnims);
    self->unk24 = FLOAT_8032fb38;
}

/*
 * --INFO--
 * PAL Address: 0x80044a24
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
CTexAnimSet::~CTexAnimSet()
{
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);

    self->vtable = __vt__11CTexAnimSet;
    self->texAnims.ReleaseAndRemoveAll();
    __dt__21CPtrArray_P8CTexAnim_Fv(&self->texAnims, -1);
    __dt__4CRefFv(this, 0);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800446a0
 * PAL Size: 900b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSet::Create(CChunkFile& chunkFile, CMemory::CStage* stage)
{
    unsigned int outerChunkData[4];
    unsigned int& outerChunkId = outerChunkData[0];
    unsigned int middleChunkData[4];
    unsigned int& middleChunkId = middleChunkData[0];
    unsigned int middleChunkArg0 = 0;
    unsigned int innerChunkData[4];
    unsigned int& innerChunkId = innerChunkData[0];
    unsigned int& innerChunkSize = innerChunkData[3];
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);

    self->texAnims.SetStage(stage);
    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(outerChunkData)) != 0) {
        if (outerChunkId == 0x54414E4D) {
            CTexAnim* texAnim =
                static_cast<CTexAnim*>(__nw__FUlPQ27CMemory6CStagePci(0x24, stage, s_texanim_cpp_801d7adc, 0x3F));
            if (texAnim != 0) {
                __ct__4CRefFv(texAnim);
                *reinterpret_cast<void**>(texAnim) = __vt__8CTexAnim;
                *reinterpret_cast<void**>((int)texAnim + 8) = 0;
                *reinterpret_cast<int*>((int)texAnim + 0xC) = 0;
                *reinterpret_cast<float*>((int)texAnim + 0x10) = FLOAT_8032fb38;
                *reinterpret_cast<int*>((int)texAnim + 0x14) = -2;
                *reinterpret_cast<float*>((int)texAnim + 0x18) = FLOAT_8032fb38;
                *reinterpret_cast<float*>((int)texAnim + 0x1C) = FLOAT_8032fb38;
                *reinterpret_cast<float*>((int)texAnim + 0x20) = FLOAT_8032fb38;
            }
            int* ref = *reinterpret_cast<int**>((int)texAnim + 8);
            if (ref != 0) {
                int refCount = ref[1];
                ref[1] = refCount - 1;
                if ((refCount - 1 == 0) && (ref != 0)) {
                    (*reinterpret_cast<void (**)(int*, int)>(*ref + 8))(ref, 1);
                }
                *reinterpret_cast<void**>((int)texAnim + 8) = 0;
            }
            CTexAnimRefDataStorage* refData = static_cast<CTexAnimRefDataStorage*>(
                __nw__FUlPQ27CMemory6CStagePci(300, stage, s_texanim_cpp_801d7adc, 0xD3));
            if (refData != 0) {
                __ct__4CRefFv(refData);
                *reinterpret_cast<void**>(refData) = __vt__Q28CTexAnim8CRefData;
                __ct__25CPtrArray_P11CTexAnimSeq_Fv(&refData->texAnimSeqs);
                refData->material = 0;
                refData->texSrtIndex = 0;
            }
            *reinterpret_cast<void**>((int)texAnim + 8) = refData;
            refData->texAnimSeqs.SetStage(stage);

            chunkFile.PushChunk();
            while ((int)chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(middleChunkData)) != 0) {
                if (middleChunkId == 0x53455120) {
                    CTexAnimSeq* seq = static_cast<CTexAnimSeq*>(
                        __nw__FUlPQ27CMemory6CStagePci(0x118, stage, s_texanim_cpp_801d7adc, 0xE2));
                    if (seq != 0) {
                        __ct__4CRefFv(seq);
                        *reinterpret_cast<void**>(seq) = __vt__11CTexAnimSeq;
                        *reinterpret_cast<int*>((int)seq + 0x10C) = 0;
                        *reinterpret_cast<int*>((int)seq + 0x114) = 0;
                    }
                    chunkFile.PushChunk();
                    while ((int)chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(innerChunkData)) != 0) {
                        if (innerChunkId == 0x4B455920) {
                            *reinterpret_cast<unsigned int*>((int)seq + 0x10C) = innerChunkSize / 0x30;
                            int keys = (int)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                                &Memory, innerChunkSize, stage, s_texanim_cpp_801d7adc, 0x1D4, 0);
                            *reinterpret_cast<int*>((int)seq + 0x114) = keys;
                            memcpy((void*)*reinterpret_cast<int*>((int)seq + 0x114), chunkFile.GetAddress(), innerChunkSize);
                        } else if ((int)innerChunkId < 0x4B455920) {
                            if (innerChunkId == 0x494E464F) {
                                *reinterpret_cast<void**>((int)seq + 0x108) = (void*)chunkFile.Get4();
                                chunkFile.Get4();
                                char b7 = (char)chunkFile.Get4();
                                *reinterpret_cast<unsigned char*>((int)seq + 0x110) =
                                    (unsigned char)(((int)b7 << 7) | (*reinterpret_cast<unsigned char*>((int)seq + 0x110) & 0x7F));
                                char b6 = (char)chunkFile.Get4();
                                *reinterpret_cast<unsigned char*>((int)seq + 0x110) =
                                    (unsigned char)((((int)b6 << 6) & 0x40) | (*reinterpret_cast<unsigned char*>((int)seq + 0x110) & 0xBF));
                                unsigned int eq = (unsigned int)__cntlzw((unsigned int)strcmp((char*)((int)seq + 8), DAT_8032fb48));
                                *reinterpret_cast<unsigned char*>((int)seq + 0x110) =
                                    (unsigned char)(((unsigned char)((int)(char)(eq >> 5) << 5) & 0x20) |
                                                    (*reinterpret_cast<unsigned char*>((int)seq + 0x110) & 0xDF));
                            }
                        } else if (innerChunkId == 0x4E414D45) {
                            strcpy((char*)((int)seq + 8), chunkFile.GetString());
                        }
                    }
                    chunkFile.PopChunk();
                    refData->texAnimSeqs.Add(seq);
                } else if (((int)middleChunkId < 0x53455120) && (middleChunkId == 0x4E414D45)) {
                    middleChunkArg0 = middleChunkData[1];
                    refData->texSrtIndex = middleChunkArg0;
                    strcpy(refData->name, chunkFile.GetString());
                }
            }
            chunkFile.PopChunk();
            self->texAnims.Add(texAnim);
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x80044540
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnimSet* CTexAnimSet::Duplicate(CMemory::CStage* stage)
{
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    CTexAnimSetStorage* dup = reinterpret_cast<CTexAnimSetStorage*>(
        __nw__FUlPQ27CMemory6CStagePci(0x28, stage, s_texanim_cpp_801d7adc, 0x54));
    if (dup != 0) {
        __ct__4CRefFv(dup);
        dup->vtable = __vt__11CTexAnimSet;
        __ct__21CPtrArray_P8CTexAnim_Fv(&dup->texAnims);
        dup->unk24 = FLOAT_8032fb38;
    }

    dup->texAnims.SetStage(stage);
    for (unsigned int i = 0; i < static_cast<unsigned int>(self->texAnims.GetSize()); i++) {
        CTexAnimStorage* src = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimStorage* copy = reinterpret_cast<CTexAnimStorage*>(
            __nw__FUlPQ27CMemory6CStagePci(0x24, stage, s_texanim_cpp_801d7adc, 0xF4));
        if (copy != 0) {
            __ct__4CRefFv(copy);
            copy->vtable = __vt__8CTexAnim;
            copy->refData = 0;
            copy->unk0C = 0;
            copy->unk10 = FLOAT_8032fb38;
            copy->unk14 = -2;
            copy->unk20 = FLOAT_8032fb38;
            copy->unk1C = FLOAT_8032fb38;
            copy->unk18 = FLOAT_8032fb38;
        }

        copy->refData = src->refData;
        reinterpret_cast<RefObject*>(copy->refData)->refCount = reinterpret_cast<RefObject*>(copy->refData)->refCount + 1;
        copy->unk0C = src->unk0C;
        copy->unk10 = src->unk10;
        copy->unk14 = src->unk14;
        copy->unk18 = src->unk18;
        copy->unk1C = src->unk1C;
        copy->unk20 = src->unk20;
        dup->texAnims.Add(reinterpret_cast<CTexAnim*>(copy));
    }

    dup->unk24 = self->unk24;
    return reinterpret_cast<CTexAnimSet*>(dup);
}

/*
 * --INFO--
 * PAL Address: 0x80044440
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSet::AttachMaterialSet(CMaterialSet* materialSet)
{
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    unsigned int texAnimIndex;
    unsigned int texAnimCount;

    for (texAnimIndex = 0;
         ((texAnimCount = static_cast<unsigned int>(GetSize__21CPtrArray_P8CTexAnim_Fv(&self->texAnims))), texAnimIndex < texAnimCount);
         texAnimIndex = texAnimIndex + 1) {
        CTexAnimStorage* texAnim =
            reinterpret_cast<CTexAnimStorage*>(__vc__21CPtrArray_P8CTexAnim_FUl(&self->texAnims, texAnimIndex));
        int* material = reinterpret_cast<int*>(*reinterpret_cast<void**>((int)texAnim->refData + 0x108));
        int materialIndex;

        if (material != 0) {
            materialIndex = material[1];
            material[1] = materialIndex - 1;
            if (((materialIndex - 1) == 0) && (material != 0)) {
                (*(void (**)(int*, int))(*material + 8))(material, 1);
            }
            *reinterpret_cast<int*>((int)texAnim->refData + 0x108) = 0;
        }

        if ((materialSet != 0) &&
            ((materialIndex = static_cast<int>(materialSet->Find(reinterpret_cast<char*>((int)texAnim->refData + 8)))) >= 0)) {
            void* foundMaterial =
                (*reinterpret_cast<CPtrArray<CMaterial*>*>((int)materialSet + 8))[static_cast<unsigned long>(materialIndex)];
            *reinterpret_cast<void**>((int)texAnim->refData + 0x108) = foundMaterial;
            material = reinterpret_cast<int*>(*reinterpret_cast<void**>((int)texAnim->refData + 0x108));
            material[1] = material[1] + 1;
        }
    }
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
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    unsigned int i = 0;

    while (i < static_cast<unsigned int>(GetSize__21CPtrArray_P8CTexAnim_Fv(&self->texAnims))) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(__vc__21CPtrArray_P8CTexAnim_FUl(&self->texAnims, i));
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        CTexAnimSeqStorage* seq =
            reinterpret_cast<CTexAnimSeqStorage*>(__vc__25CPtrArray_P11CTexAnimSeq_FUl(&refData->texAnimSeqs, texAnim->unk0C));
        unsigned char flags = seq->flags;
        float frameStep = FLOAT_8032fb3c;

        if ((flags & 0x80) != 0) {
            frameStep = FLOAT_8032fb4c;
        }

        if (((flags & 0x40) == 0) || (FLOAT_8032fb3c != texAnim->unk10) || (Math.Rand(0x1E) == 0)) {
            float currentFrame = (float)fmod((double)texAnim->unk10, (double)(float)seq->totalFrames);
            int keyCount = seq->keyCount;
            unsigned int* keyData = seq->keys;
            unsigned int keyIndex = 0;
            unsigned int lastKeyIndex = keyCount - 1;

            while (keyCount != 0) {
                float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[0xC] : seq->totalFrames);
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
                    PSVECAdd(&v0, &v1, reinterpret_cast<Vec*>(&texAnim->unk18));

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

            if (texAnim->unk14 != -3) {
                texAnim->unk10 = texAnim->unk10 + frameStep;
                if ((float)seq->totalFrames <= texAnim->unk10) {
                    int mode = texAnim->unk14;
                    if (mode == -1) {
                        texAnim->unk10 = (float)seq->totalFrames;
                    } else if (mode >= 0) {
                        texAnim->unk0C = mode;
                        texAnim->unk14 = -2;
                    }
                    texAnim->unk10 = texAnim->unk10 - (float)seq->totalFrames;
                }
            }
        }

        seq = reinterpret_cast<CTexAnimSeqStorage*>(__vc__25CPtrArray_P11CTexAnimSeq_FUl(&refData->texAnimSeqs, texAnim->unk0C));
        if ((seq->flags & 0x40) != 0) {
            self->unk24 = texAnim->unk20;
        } else {
            self->unk24 = FLOAT_8032fb38;
        }

        i = i + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004401c
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSet::Change(char* name, float frame, CTexAnimSet::ANIM_TYPE mode)
{
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    unsigned int texAnimIndex = 0;

    do {
        unsigned int texAnimCount = static_cast<unsigned int>(GetSize__21CPtrArray_P8CTexAnim_Fv(&self->texAnims));
        if (texAnimCount <= texAnimIndex) {
            return;
        }

        CTexAnimStorage* texAnim =
            reinterpret_cast<CTexAnimStorage*>(__vc__21CPtrArray_P8CTexAnim_FUl(&self->texAnims, texAnimIndex));
        unsigned int seqIndex;
        unsigned int seqCount;

        for (seqIndex = 0;
             ((seqCount = static_cast<unsigned int>(GetSize__25CPtrArray_P11CTexAnimSeq_Fv(Ptr(texAnim->refData, 0x110)))),
              seqIndex < seqCount);
             seqIndex = seqIndex + 1) {
            CTexAnimSeqStorage* seq =
                reinterpret_cast<CTexAnimSeqStorage*>(__vc__25CPtrArray_P11CTexAnimSeq_FUl(Ptr(texAnim->refData, 0x110), seqIndex));
            if (strcmp(name, seq->name) == 0) {
                goto found;
            }
        }
        seqIndex = 0xFFFFFFFF;
found:
        if (-1 < static_cast<int>(seqIndex)) {
            texAnim->unk0C = static_cast<int>(seqIndex);
            texAnim->unk10 = frame;
            texAnim->unk14 = static_cast<int>(mode);
            return;
        }
        texAnimIndex = texAnimIndex + 1;
    } while (true);
}

/*
 * --INFO--
 * PAL Address: 0x80043f48
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSet::SetTexGen()
{
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    const float zero = FLOAT_8032fb38;

    for (unsigned int i = 0; i < static_cast<unsigned int>(self->texAnims.GetSize()); i++) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        int* material = reinterpret_cast<int*>(refData->material);
        if (material != 0) {
            CTexScrollStorage* texScroll = reinterpret_cast<CTexScrollStorage*>(Ptr(material, 0x4C)) + refData->texSrtIndex;
            const float texGenS = F32At(texAnim, 0x18);
            const float texGenT = F32At(texAnim, 0x1C);
            texScroll->u0 = texGenS;
            texScroll->v0 = texGenT;
            texScroll->u1 = zero;
            texScroll->v1 = zero;
            if (zero == texScroll->u1) {
                texScroll->type0 = 0;
            } else {
                texScroll->type0 = 1;
            }
            if (zero == texScroll->v1) {
                texScroll->type1 = 0;
            } else {
                texScroll->type1 = 1;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80043e40
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnim::CTexAnim()
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);

    __ct__4CRefFv(this);
    self->vtable = __vt__8CTexAnim;
    self->refData = 0;
    self->unk0C = 0;
    self->unk10 = FLOAT_8032fb38;
    self->unk14 = -2;
    self->unk18 = FLOAT_8032fb38;
    self->unk1C = FLOAT_8032fb38;
    self->unk20 = FLOAT_8032fb38;
}

/*
 * --INFO--
 * PAL Address: 0x80043ea4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnim::~CTexAnim()
{
    *reinterpret_cast<void**>(this) = __vt__8CTexAnim;
    CRef* refData = reinterpret_cast<CRef*>(*reinterpret_cast<void**>(Ptr(this, 8)));
    if (refData != 0) {
        int* refDataWords = reinterpret_cast<int*>(refData);
        int refCount = refDataWords[1];
        int nextRefCount = refCount - 1;

        refDataWords[1] = nextRefCount;
        if (nextRefCount == 0) {
            delete refData;
        }
        *reinterpret_cast<void**>(Ptr(this, 8)) = 0;
    }
    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80043bcc
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnim::Create(CChunkFile& chunkFile, CMemory::CStage* stage)
{
    CChunkFile::CChunk chunk;
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);

    ReleaseRef(&self->refData);

    CTexAnimRefDataStorage* refData = static_cast<CTexAnimRefDataStorage*>(
        __nw__FUlPQ27CMemory6CStagePci(0x12C, stage, s_texanim_cpp_801d7adc, 0xD3));
    if (refData != 0) {
        __ct__4CRefFv(refData);
        refData->vtable = __vt__Q28CTexAnim8CRefData;
        __ct__25CPtrArray_P11CTexAnimSeq_Fv(&refData->texAnimSeqs);
        refData->material = 0;
        refData->texSrtIndex = 0;
    }
    self->refData = refData;
    refData->texAnimSeqs.SetStage(stage);

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == 0x53455120) {
            CTexAnimSeq* seq = static_cast<CTexAnimSeq*>(
                __nw__FUlPQ27CMemory6CStagePci(0x118, stage, s_texanim_cpp_801d7adc, 0xE2));
            if (seq != 0) {
                __ct__4CRefFv(seq);
                *reinterpret_cast<void**>(seq) = __vt__11CTexAnimSeq;
                *reinterpret_cast<int*>(Ptr(seq, 0x10C)) = 0;
                *reinterpret_cast<int*>(Ptr(seq, 0x114)) = 0;
            }

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk) != 0) {
                if (chunk.m_id == 0x4B455920) {
                    *reinterpret_cast<unsigned int*>(Ptr(seq, 0x10C)) = chunk.m_size / 0x30;
                    int keys = (int)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                        &Memory, chunk.m_size, stage, s_texanim_cpp_801d7adc, 0x1D4, 0);
                    *reinterpret_cast<int*>(Ptr(seq, 0x114)) = keys;
                    memcpy((void*)*reinterpret_cast<int*>(Ptr(seq, 0x114)), chunkFile.GetAddress(), chunk.m_size);
                } else if ((int)chunk.m_id < 0x4B455920) {
                    if (chunk.m_id == 0x494E464F) {
                        *reinterpret_cast<void**>(Ptr(seq, 0x108)) = (void*)chunkFile.Get4();
                        chunkFile.Get4();

                        const char bit7 = (char)chunkFile.Get4();
                        *reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) = (unsigned char)(
                            (((int)bit7 << 7) & 0x80) | (*reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) & 0x7F));

                        const char bit6 = (char)chunkFile.Get4();
                        *reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) = (unsigned char)(
                            (((int)bit6 << 6) & 0x40) | (*reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) & 0xBF));

                        const unsigned int emptyName =
                            (unsigned int)__cntlzw((unsigned int)strcmp((char*)Ptr(seq, 8), DAT_8032fb48));
                        *reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) = (unsigned char)(
                            ((((unsigned char)((int)(char)(emptyName >> 5) << 5)) & 0x20) |
                             (*reinterpret_cast<unsigned char*>(Ptr(seq, 0x110)) & 0xDF)));
                    }
                } else if (chunk.m_id == 0x4E414D45) {
                    strcpy((char*)Ptr(seq, 8), chunkFile.GetString());
                }
            }
            chunkFile.PopChunk();
            refData->texAnimSeqs.Add(seq);
        } else if (((int)chunk.m_id < 0x53455120) && (chunk.m_id == 0x4E414D45)) {
            refData->texSrtIndex = chunk.m_arg0;
            strcpy(refData->name, chunkFile.GetString());
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x80043afc
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnim* CTexAnim::Duplicate(CMemory::CStage* stage)
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimStorage* dup = reinterpret_cast<CTexAnimStorage*>(
        __nw__FUlPQ27CMemory6CStagePci(0x24, stage, s_texanim_cpp_801d7adc, 0xF4));

    if (dup != 0) {
        __ct__4CRefFv(dup);
        dup->vtable = __vt__8CTexAnim;
        dup->refData = 0;
        dup->unk0C = 0;
        dup->unk10 = FLOAT_8032fb38;
        dup->unk14 = -2;
        dup->unk20 = FLOAT_8032fb38;
        dup->unk1C = FLOAT_8032fb38;
        dup->unk18 = FLOAT_8032fb38;
    }

    dup->refData = self->refData;
    reinterpret_cast<RefObject*>(dup->refData)->refCount = reinterpret_cast<RefObject*>(dup->refData)->refCount + 1;
    dup->unk0C = self->unk0C;
    dup->unk10 = self->unk10;
    dup->unk14 = self->unk14;
    dup->unk18 = self->unk18;
    dup->unk1C = self->unk1C;
    dup->unk20 = self->unk20;
    return reinterpret_cast<CTexAnim*>(dup);
}

/*
 * --INFO--
 * PAL Address: 0x800439e4
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnim::AttachMaterialSet(CMaterialSet* materialSet)
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(self->refData);
    int* material = reinterpret_cast<int*>(refData->material);
    int materialIndex;

    if (material != 0) {
        materialIndex = material[1];
        material[1] = materialIndex - 1;
        if (((materialIndex - 1) == 0) && (material != 0)) {
            (*(void (**)(int*, int))(*material + 8))(material, 1);
        }
        refData->material = 0;
    }

    if ((materialSet != 0) && ((materialIndex = static_cast<int>(materialSet->Find(refData->name))) >= 0)) {
        refData->material =
            (*reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(materialSet, 8)))[static_cast<unsigned long>(materialIndex)];
        material = reinterpret_cast<int*>(refData->material);
        material[1] = material[1] + 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80043708
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnim::AddFrame(float frameStep)
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(self->refData);
    CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[self->unk0C]);
    const unsigned char flags = seq->flags;

    if ((flags & 0x80) != 0) {
        frameStep = FLOAT_8032fb4c;
    }

    if (((flags & 0x40) == 0) || (FLOAT_8032fb3c != self->unk10) || (Math.Rand(0x1E) == 0)) {
        const float currentFrame = (float)fmod((double)self->unk10, (double)(float)seq->totalFrames);
        int keyCount = seq->keyCount;
        unsigned int* keyData = seq->keys;
        unsigned int keyIndex = 0;
        const unsigned int lastKeyIndex = keyCount - 1;

        while (keyCount != 0) {
            const float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[0xC] : seq->totalFrames);
            unsigned int* nextKeyData = keyData;

            if (keyIndex < lastKeyIndex) {
                nextKeyData = keyData + 0xC;
            }

            if (((float)keyData[0] <= currentFrame) && (currentFrame < nextFrame)) {
                float t = FLOAT_8032fb38;
                const float frameSpan = nextFrame - (float)keyData[0];
                if (frameSpan != FLOAT_8032fb38) {
                    t = (currentFrame - (float)keyData[0]) / frameSpan;
                }

                Vec v0;
                Vec v1;
                PSVECScale(reinterpret_cast<Vec*>(keyData + 9), &v0, FLOAT_8032fb3c - t);
                PSVECScale(reinterpret_cast<Vec*>(nextKeyData + 9), &v1, t);
                PSVECAdd(&v0, &v1, reinterpret_cast<Vec*>(&self->unk18));

                if ((flags & 0x80) == 0) {
                    U32At(self, 0x18) = keyData[9];
                    U32At(self, 0x1C) = keyData[10];
                }
                break;
            }

            keyData += 0xC;
            keyIndex = keyIndex + 1;
            keyCount = keyCount - 1;
        }

        if (self->unk14 != -3) {
            self->unk10 = self->unk10 + frameStep;
            if ((float)seq->totalFrames <= self->unk10) {
                const int mode = self->unk14;
                if (mode == -1) {
                    self->unk10 = (float)seq->totalFrames;
                } else if (mode >= 0) {
                    self->unk0C = mode;
                    self->unk14 = -2;
                }
                self->unk10 = self->unk10 - (float)seq->totalFrames;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80043678
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTexAnim::Find(char* name)
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(self->refData);

    for (unsigned int i = 0; i < static_cast<unsigned int>(refData->texAnimSeqs.GetSize()); i++) {
        CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[i]);
        if (strcmp(name, seq->name) == 0) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800435d4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnim::Change(int seqIndex, float frame, CTexAnimSet::ANIM_TYPE mode)
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);

    self->unk0C = seqIndex;
    self->unk10 = frame;
    self->unk14 = static_cast<int>(mode);
}

/*
 * --INFO--
 * PAL Address: 0x8004354c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnim::SetTexGen()
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(self->refData);
    int* material = reinterpret_cast<int*>(refData->material);

    if (material != 0) {
        CTexScrollStorage* texScroll = reinterpret_cast<CTexScrollStorage*>(Ptr(material, 0x4C)) + refData->texSrtIndex;
        texScroll->u0 = self->unk18;
        texScroll->v0 = self->unk1C;
        texScroll->u1 = FLOAT_8032fb38;
        texScroll->v1 = FLOAT_8032fb38;
        texScroll->type0 = (texScroll->u1 == FLOAT_8032fb38) ? 0 : 1;
        texScroll->type1 = (texScroll->v1 == FLOAT_8032fb38) ? 0 : 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80043514
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTexAnim::IsChin()
{
    CTexAnimStorage* self = reinterpret_cast<CTexAnimStorage*>(this);
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(self->refData);
    CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[self->unk0C]);

    return (seq->flags & 0x40) != 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004350c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CTexAnim::GetChin()
{
    return reinterpret_cast<CTexAnimStorage*>(this)->unk20;
}

/*
 * --INFO--
 * PAL Address: 0x80043d1c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnim::CRefData::CRefData()
{
    CTexAnimRefDataStorage* self = reinterpret_cast<CTexAnimRefDataStorage*>(this);

    __ct__4CRefFv(this);
    self->vtable = __vt__Q28CTexAnim8CRefData;
    __ct__25CPtrArray_P11CTexAnimSeq_Fv(&self->texAnimSeqs);
    self->material = 0;
    self->texSrtIndex = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80043dec
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
CTexAnim::CRefData::~CRefData()
{
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(this);

    refData->vtable = __vt__Q28CTexAnim8CRefData;
    int* material = reinterpret_cast<int*>(refData->material);
    if (material != 0) {
        int refCount = material[1];
        int nextRefCount = refCount - 1;

        material[1] = nextRefCount;
        if ((nextRefCount == 0) && (material != 0)) {
            (*(void (**)(int*, int))(*material + 8))(material, 1);
        }
        refData->material = 0;
    }
    refData->texAnimSeqs.ReleaseAndRemoveAll();
    __dt__25CPtrArray_P11CTexAnimSeq_Fv(&refData->texAnimSeqs, -1);

    __dt__4CRefFv(this, 0);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80043d20
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnimSeq::CTexAnimSeq()
{
    CTexAnimSeqStorage* self = reinterpret_cast<CTexAnimSeqStorage*>(this);

    __ct__4CRefFv(this);
    self->vtable = __vt__11CTexAnimSeq;
    self->name[0] = '\0';
    self->totalFrames = 0;
    self->keyCount = 0;
    self->flags = 0;
    self->keys = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80043d70
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexAnimSeq::~CTexAnimSeq()
{
    *reinterpret_cast<void**>(this) = __vt__11CTexAnimSeq;
    void** keys = reinterpret_cast<void**>(Ptr(this, 0x114));
    if (*keys != 0) {
        __dla__FPv(*keys);
        *keys = 0;
    }
    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80043a48
 * PAL Size: 652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexAnimSeq::Create(CChunkFile& chunkFile, CMemory::CStage* stage)
{
    CChunkFile::CChunk chunk;
    CTexAnimSeqStorage* self = reinterpret_cast<CTexAnimSeqStorage*>(this);

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == 0x4B455920) {
            self->keyCount = chunk.m_size / 0x30;
            self->keys = static_cast<unsigned int*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory, chunk.m_size, stage, s_texanim_cpp_801d7adc, 0x1D4, 0));
            memcpy(self->keys, chunkFile.GetAddress(), chunk.m_size);
        } else if ((int)chunk.m_id < 0x4B455920) {
            if (chunk.m_id == 0x494E464F) {
                self->totalFrames = chunkFile.Get4();
                chunkFile.Get4();

                const char bit7 = (char)chunkFile.Get4();
                self->flags = (unsigned char)((((int)bit7 << 7) & 0x80) | (self->flags & 0x7F));

                const char bit6 = (char)chunkFile.Get4();
                self->flags = (unsigned char)((((int)bit6 << 6) & 0x40) | (self->flags & 0xBF));

                const unsigned int emptyName = (unsigned int)__cntlzw((unsigned int)strcmp(self->name, DAT_8032fb48));
                self->flags =
                    (unsigned char)((((unsigned char)((int)(char)(emptyName >> 5) << 5)) & 0x20) | (self->flags & 0xDF));
            }
        } else if (chunk.m_id == 0x4E414D45) {
            strcpy(self->name, chunkFile.GetString());
        }
    }
    chunkFile.PopChunk();
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
 * PAL Address: 0x80043a40
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CTexAnimSeq::GetTotalFrame()
{
    return reinterpret_cast<CTexAnimSeqStorage*>(this)->totalFrames;
}

/*
 * --INFO--
 * PAL Address: 0x80043a38
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CTexAnimSeq::GetName()
{
    return reinterpret_cast<CTexAnimSeqStorage*>(this)->name;
}

/*
 * --INFO--
 * PAL Address: 0x80043a00
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTexAnimSeq::IsChin()
{
    return (reinterpret_cast<CTexAnimSeqStorage*>(this)->flags & 0x40) != 0;
}
