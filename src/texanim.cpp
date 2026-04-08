#include "ffcc/texanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/materialman.h"
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
extern "C" {
char s_texanim_cpp_801d7adc[] = "texanim.cpp";
}
static const char DAT_8032fb48[] = "";
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

static inline void AddRef(void* ref)
{
    if (ref != 0) {
        reinterpret_cast<RefObject*>(ref)->refCount = reinterpret_cast<RefObject*>(ref)->refCount + 1;
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
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = __vt__11CTexAnimSet;
    __ct__21CPtrArray_P8CTexAnim_Fv(Ptr(this, 8));
    F32At(this, 0x24) = 0.0f;
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
    self->texAnims.~CPtrArray<CTexAnim*>();
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
    CChunkFile::CChunk chunk;
    CPtrArray<CTexAnim*>* texAnims = reinterpret_cast<CPtrArray<CTexAnim*>*>((int)this + 8);

    texAnims->SetStage(stage);
    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == 0x54414E4D) {
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
            void* refData = __nw__FUlPQ27CMemory6CStagePci(300, stage, s_texanim_cpp_801d7adc, 0xD3);
            if (refData != 0) {
                __ct__4CRefFv(refData);
                *reinterpret_cast<void**>(refData) = __vt__Q28CTexAnim8CRefData;
                __ct__25CPtrArray_P11CTexAnimSeq_Fv((void*)((int)refData + 0x110));
                *reinterpret_cast<void**>((int)refData + 0x108) = 0;
                *reinterpret_cast<int*>((int)refData + 0x10C) = 0;
            }
            *reinterpret_cast<void**>((int)texAnim + 8) = refData;
            reinterpret_cast<CPtrArray<CTexAnimSeq*>*>((int)(*reinterpret_cast<void**>((int)texAnim + 8)) + 0x110)
                ->SetStage(stage);

            chunkFile.PushChunk();
            while ((int)chunkFile.GetNextChunk(chunk) != 0) {
                if (chunk.m_id == 0x53455120) {
                    CTexAnimSeq* seq = static_cast<CTexAnimSeq*>(
                        __nw__FUlPQ27CMemory6CStagePci(0x118, stage, s_texanim_cpp_801d7adc, 0xE2));
                    if (seq != 0) {
                        __ct__4CRefFv(seq);
                        *reinterpret_cast<void**>(seq) = __vt__11CTexAnimSeq;
                        *reinterpret_cast<int*>((int)seq + 0x10C) = 0;
                        *reinterpret_cast<int*>((int)seq + 0x114) = 0;
                    }
                    chunkFile.PushChunk();
                    while ((int)chunkFile.GetNextChunk(chunk) != 0) {
                        if (chunk.m_id == 0x4B455920) {
                            *reinterpret_cast<unsigned int*>((int)seq + 0x10C) = chunk.m_size / 0x30;
                            int keys = (int)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                                &Memory, chunk.m_size, stage, s_texanim_cpp_801d7adc, 0x1D4, 0);
                            *reinterpret_cast<int*>((int)seq + 0x114) = keys;
                            memcpy((void*)*reinterpret_cast<int*>((int)seq + 0x114), chunkFile.GetAddress(), chunk.m_size);
                        } else if ((int)chunk.m_id < 0x4B455920) {
                            if (chunk.m_id == 0x494E464F) {
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
                        } else if (chunk.m_id == 0x4E414D45) {
                            strcpy((char*)((int)seq + 8), chunkFile.GetString());
                        }
                    }
                    chunkFile.PopChunk();
                    reinterpret_cast<CPtrArray<CTexAnimSeq*>*>((int)*reinterpret_cast<void**>((int)texAnim + 8) + 0x110)
                        ->Add(seq);
                } else if (((int)chunk.m_id < 0x53455120) && (chunk.m_id == 0x4E414D45)) {
                    *reinterpret_cast<unsigned char**>((int)*reinterpret_cast<void**>((int)texAnim + 8) + 0x10C) =
                        (unsigned char*)chunk.m_arg0;
                    strcpy((char*)((int)*reinterpret_cast<void**>((int)texAnim + 8) + 8), chunkFile.GetString());
                }
            }
            chunkFile.PopChunk();
            texAnims->Add(texAnim);
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
        new (&dup->texAnims) CPtrArray<CTexAnim*>();
        dup->unk24 = FLOAT_8032fb38;
    }

    dup->texAnims.SetStage(stage);
    for (unsigned long i = 0; i < static_cast<unsigned long>(self->texAnims.GetSize()); i++) {
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
        AddRef(copy->refData);
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
    CPtrArray<CMaterial*>* materials = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(materialSet, 8));

    for (unsigned int i = 0; i < static_cast<unsigned int>(self->texAnims.GetSize()); i++) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        int* current = reinterpret_cast<int*>(refData->material);

        if (current != 0) {
            int refCount = current[1];
            int nextRefCount = refCount - 1;

            current[1] = nextRefCount;
            if ((nextRefCount == 0) && (current != 0)) {
                (*(void (**)(int*, int))(*current + 8))(current, 1);
            }
            refData->material = 0;
        }

        if (materialSet != 0) {
            int materialIndex = static_cast<int>(materialSet->Find(refData->name));
            if (materialIndex >= 0) {
                refData->material = (*materials)[static_cast<unsigned long>(materialIndex)];
                current = reinterpret_cast<int*>(refData->material);
                current[1] = current[1] + 1;
            }
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

    while (i < static_cast<unsigned int>(self->texAnims.GetSize())) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[texAnim->unk0C]);
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

        seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[texAnim->unk0C]);
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

    for (unsigned int texAnimIndex = 0; texAnimIndex < static_cast<unsigned int>(self->texAnims.GetSize());
         texAnimIndex++) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[texAnimIndex]);
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        int seqIndex = -1;

        for (unsigned int i = 0; i < static_cast<unsigned int>(refData->texAnimSeqs.GetSize()); i++) {
            CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[i]);

            if (strcmp(name, seq->name) == 0) {
                seqIndex = static_cast<int>(i);
                break;
            }
        }

        if (seqIndex >= 0) {
            texAnim->unk0C = seqIndex;
            texAnim->unk10 = frame;
            texAnim->unk14 = static_cast<int>(mode);
            return;
        }
    }
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
    CPtrArray<CTexAnim*>* texAnims = reinterpret_cast<CPtrArray<CTexAnim*>*>(Ptr(this, 8));

    for (unsigned int i = 0; i < static_cast<unsigned int>(texAnims->GetSize()); i++) {
        CTexAnim* texAnim = (*texAnims)[i];
        const float fVar2 = FLOAT_8032fb38;
        void* refData = *reinterpret_cast<void**>(Ptr(texAnim, 8));
        int* material = reinterpret_cast<int*>(*reinterpret_cast<void**>(Ptr(refData, 0x108)));
        if (material != 0) {
            const unsigned int uVar1 = U32At(texAnim, 0x1C);
            int* texSrt = material + (S32At(refData, 0x10C) * 5);
            U32At(texSrt, 0x50) = U32At(texAnim, 0x18);
            U32At(texSrt, 0x54) = uVar1;
            F32At(texSrt, 0x58) = fVar2;
            F32At(texSrt, 0x5C) = fVar2;
            if (fVar2 == F32At(texSrt, 0x58)) {
                U8At(texSrt, 0x4C) = 0;
            } else {
                U8At(texSrt, 0x4C) = 1;
            }
            if (FLOAT_8032fb38 == F32At(texSrt, 0x5C)) {
                U8At(texSrt, 0x4D) = 0;
            } else {
                U8At(texSrt, 0x4D) = 1;
            }
        }
    }
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
    int* refData = reinterpret_cast<int*>(*reinterpret_cast<void**>(Ptr(this, 8)));
    if (refData != 0) {
        int refCount = refData[1];
        int nextRefCount = refCount - 1;

        refData[1] = nextRefCount;
        if ((nextRefCount == 0) && (refData != 0)) {
            (*(void (**)(int*, int))(*refData + 8))(refData, 1);
        }
        *reinterpret_cast<void**>(Ptr(this, 8)) = 0;
    }
    __dt__4CRefFv(this, 0);
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
    refData->texAnimSeqs.~CPtrArray<CTexAnimSeq*>();

    __dt__4CRefFv(this, 0);
}
#pragma dont_inline reset

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
