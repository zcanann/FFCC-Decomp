#define FFCC_PTRARRAY_NO_INLINE_ACCESSORS
#include "ffcc/texanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/materialman.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"
#include "ffcc/math.h"

#include <string.h>
#include <math.h>
#include "dolphin/mtx.h"

extern "C" const char s_texanim_cpp[];
extern const float FLOAT_8032fb38 = 0.0f;
extern const float FLOAT_8032fb3c = 1.0f;
extern const double DOUBLE_8032fb40 = 4503599627370496.0;
extern const char s_texAnimSeqE1[] = "e1";
extern const float FLOAT_8032fb4c = 1.25f;
extern "C" const char s_scenegraph_step_none[4] = "";
extern "C" const char s_scenegraph_step_x8[] = "x8";
extern "C" const char s_scenegraph_step_x0[] = "x0";
extern "C" const char s_scenegraph_step_x1_8[] = "x1/8";

extern const char s_collection_ptrarray_h_801D7B30[];
extern const char s_ptrarray_grow_error_801D7B14[];

namespace {
struct RefObject
{
    void* vtable;
    int refCount;
};

struct CMaterialSetStorage
{
    void* vtable;
    int refCount;
    CPtrArray<CMaterial*> materials;
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

static inline int IsTexAnimChinFlag(unsigned char flags)
{
    unsigned int bits = (static_cast<unsigned int>(flags) << 25) & 0xC0000000;
    return static_cast<int>(bits) >> 31;
}

static inline char IsTexAnimE1Flag(unsigned char flags)
{
    unsigned int bits = (static_cast<unsigned int>(flags) << 26) & 0xC0000000;
    return static_cast<char>(static_cast<int>(bits) >> 31);
}

static inline char IsTexAnimInterpFlag(unsigned char flags)
{
    unsigned int bits = (static_cast<unsigned int>(flags) << 24) & 0xC0000000;
    return static_cast<char>(static_cast<int>(bits) >> 31);
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
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline CTexAnimSeq::CTexAnimSeq()
{
    m_keyCount = 0;
    m_keys = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline CTexAnim::CRefData::CRefData()
{
    m_material = 0;
    m_texSrtIndex = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline CTexAnim::CTexAnim()
{
    const float& zero = FLOAT_8032fb38;
    m_refData = 0;
    m_seqIndex = 0;
    m_frame = zero;
    m_mode = -2;
    m_chin = zero;
    m_texGenT = zero;
    m_texGenS = zero;
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
    const float& zero = FLOAT_8032fb38;
    m_chin = zero;
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
    if (m_keys != 0) {
        delete[] m_keys;
        m_keys = 0;
    }
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
    CRef* material = reinterpret_cast<CRef*>(m_material);
    if (material != 0) {
        int* materialWords = reinterpret_cast<int*>(material);
        int refCount = materialWords[1];
        int nextRefCount = refCount - 1;

        materialWords[1] = nextRefCount;
        if (nextRefCount == 0) {
            delete material;
        }
        m_material = 0;
    }
    m_texAnimSeqs.ReleaseAndRemoveAll();
}
#pragma dont_inline reset

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
    CRef* refData = reinterpret_cast<CRef*>(m_refData);
    if (refData != 0) {
        int* refDataWords = reinterpret_cast<int*>(refData);
        int refCount = refDataWords[1];
        int nextRefCount = refCount - 1;

        refDataWords[1] = nextRefCount;
        if (nextRefCount == 0) {
            delete refData;
        }
        m_refData = 0;
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
    const float zero = FLOAT_8032fb38;

    for (unsigned int i = 0; i < static_cast<unsigned int>(m_texAnims.GetSize()); i++) {
        CTexAnim* texAnim = m_texAnims[i];
        CTexAnim::CRefData* refData = texAnim->m_refData;
        CMaterial* material = refData->m_material;
        if (material != 0) {
            const float texGenS = texAnim->m_texGenS;
            const float texGenT = texAnim->m_texGenT;
            int texSrtIndex = refData->m_texSrtIndex;
            material->m_texScroll[texSrtIndex].m_u0 = texGenS;
            material->m_texScroll[texSrtIndex].m_v0 = texGenT;
            material->m_texScroll[texSrtIndex].m_u1 = zero;
            material->m_texScroll[texSrtIndex].m_v1 = zero;
            if (zero == material->m_texScroll[texSrtIndex].m_u1) {
                material->m_texScroll[texSrtIndex].m_type0 = 0;
            } else {
                material->m_texScroll[texSrtIndex].m_type0 = 1;
            }
            if (zero == material->m_texScroll[texSrtIndex].m_v1) {
                material->m_texScroll[texSrtIndex].m_type1 = 0;
            } else {
                material->m_texScroll[texSrtIndex].m_type1 = 1;
            }
        }
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
    unsigned int seqIndex;
    unsigned int texAnimIndex;

    for (texAnimIndex = 0; texAnimIndex < static_cast<unsigned int>(m_texAnims.GetSize());
         texAnimIndex = texAnimIndex + 1) {
        CTexAnim* texAnim = m_texAnims[texAnimIndex];
        for (seqIndex = 0;
             seqIndex < static_cast<unsigned int>(texAnim->m_refData->m_texAnimSeqs.GetSize());
             seqIndex = seqIndex + 1) {
            CTexAnimSeq* seq = texAnim->m_refData->m_texAnimSeqs[seqIndex];
            if (strcmp(name, seq->m_name) == 0) {
                goto found;
            }
        }
        seqIndex = 0xFFFFFFFF;
found:
        if (static_cast<int>(seqIndex) >= 0) {
            texAnim->m_seqIndex = static_cast<int>(seqIndex);
            texAnim->m_frame = frame;
            texAnim->m_mode = static_cast<int>(mode);
            return;
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
    unsigned int i = 0;

    while (i < static_cast<unsigned int>(m_texAnims.GetSize())) {
        CTexAnim* texAnim = m_texAnims[i];
        CTexAnim::CRefData* refData = texAnim->m_refData;
        CTexAnimSeq* seq = refData->m_texAnimSeqs[texAnim->m_seqIndex];
        float frameStep;

        if (IsTexAnimChinFlag(seq->m_flags)) {
            frameStep = FLOAT_8032fb4c;
        } else {
            frameStep = FLOAT_8032fb3c;
        }

        texAnim = m_texAnims[i];
        refData = texAnim->m_refData;
        seq = refData->m_texAnimSeqs[texAnim->m_seqIndex];

        if (!IsTexAnimE1Flag(seq->m_flags) || !IsTexAnimE1Flag(seq->m_flags) ||
            (FLOAT_8032fb3c != texAnim->m_frame) || (static_cast<unsigned int>(Math.Rand(0x1E)) == 0)) {
            float currentFrame = (float)fmod((double)texAnim->m_frame, (double)(float)seq->m_totalFrames);
            unsigned int keyCount = seq->m_keyCount;
            unsigned int* keys = seq->m_keys;
            unsigned int keyIndex = 0;
            unsigned int lastKeyIndex = keyCount - 1;

            while (keyIndex < keyCount) {
                unsigned int* keyData = keys + keyIndex * 0xC;
                float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[0xC] : seq->m_totalFrames);
                unsigned int* nextKeyData;

                if (keyIndex < lastKeyIndex) {
                    nextKeyData = keys + (keyIndex + 1) * 0xC;
                } else {
                    nextKeyData = keys;
                }

                if (((float)keyData[0] <= currentFrame) && (currentFrame < nextFrame)) {
                    float t = FLOAT_8032fb38;
                    float frameSpan = nextFrame - (float)keyData[0];
                    if (frameSpan != FLOAT_8032fb38) {
                        t = (currentFrame - (float)keyData[0]) / frameSpan;
                    }

                    Vec v1;
                    Vec v0;
                    PSVECScale(reinterpret_cast<Vec*>(keyData + 9), &v0, FLOAT_8032fb3c - t);
                    PSVECScale(reinterpret_cast<Vec*>(nextKeyData + 9), &v1, t);
                    PSVECAdd(&v0, &v1, reinterpret_cast<Vec*>(&texAnim->m_texGenS));

                    if (!IsTexAnimInterpFlag(seq->m_flags)) {
                        texAnim->m_texGenS = reinterpret_cast<float*>(keyData)[9];
                        texAnim->m_texGenT = reinterpret_cast<float*>(keyData)[10];
                    }
                    break;
                }

                keyIndex = keyIndex + 1;
            }

            if (texAnim->m_mode != -3) {
                texAnim->m_frame = texAnim->m_frame + frameStep;
                if ((float)seq->m_totalFrames <= texAnim->m_frame) {
                    int mode = texAnim->m_mode;
                    if (mode == -1) {
                        texAnim->m_frame = (float)seq->m_totalFrames;
                    } else if (mode >= 0) {
                        texAnim->m_seqIndex = mode;
                        texAnim->m_mode = -2;
                    }
                    texAnim->m_frame = texAnim->m_frame - (float)seq->m_totalFrames;
                }
            }
        }

        texAnim = m_texAnims[i];
        refData = texAnim->m_refData;
        seq = refData->m_texAnimSeqs[texAnim->m_seqIndex];
        if (IsTexAnimChinFlag(seq->m_flags)) {
            texAnim = m_texAnims[i];
            m_chin = texAnim->m_chin;
        } else {
            m_chin = FLOAT_8032fb38;
        }

        i = i + 1;
    }
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
    CMaterialSetStorage* materialSetStorage = reinterpret_cast<CMaterialSetStorage*>(materialSet);
    unsigned int texAnimIndex;
    unsigned int texAnimCount;
    int materialIndex;

    for (texAnimIndex = 0;
         ((texAnimCount = static_cast<unsigned int>(m_texAnims.GetSize())), texAnimIndex < texAnimCount);
         texAnimIndex = texAnimIndex + 1) {
        CTexAnim* texAnim = m_texAnims[texAnimIndex];
        int* material = reinterpret_cast<int*>(texAnim->m_refData->m_material);

        if (material != 0) {
            int refCount = material[1] - 1;
            material[1] = refCount;
            if (refCount == 0) {
                delete reinterpret_cast<CMaterial*>(material);
            }
            texAnim->m_refData->m_material = 0;
        }

        if ((materialSet != 0) &&
            ((materialIndex = materialSet->Find(texAnim->m_refData->m_name)), materialIndex >= 0)) {
            CMaterial* foundMaterial = materialSetStorage->materials[materialIndex];
            texAnim->m_refData->m_material = foundMaterial;
            material = reinterpret_cast<int*>(texAnim->m_refData->m_material);
            material[1] = material[1] + 1;
        }
    }
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
    CTexAnimSet* dup = new (stage, const_cast<char*>(s_texanim_cpp), 0x54) CTexAnimSet;

    dup->m_texAnims.SetStage(stage);
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_texAnims.GetSize()); i++) {
        CTexAnim* src = m_texAnims[i];
        CTexAnim* copy = new (stage, const_cast<char*>(s_texanim_cpp), 0xF4) CTexAnim;

        copy->m_refData = src->m_refData;
        reinterpret_cast<RefObject*>(copy->m_refData)->refCount =
            reinterpret_cast<RefObject*>(copy->m_refData)->refCount + 1;
        copy->m_seqIndex = src->m_seqIndex;
        copy->m_frame = src->m_frame;
        copy->m_mode = src->m_mode;
        copy->m_texGenS = src->m_texGenS;
        copy->m_texGenT = src->m_texGenT;
        copy->m_chin = src->m_chin;
        dup->m_texAnims.Add(copy);
    }

    dup->m_chin = m_chin;
    return dup;
}

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
    CChunkFile::CChunk outerChunk;
    CChunkFile::CChunk middleChunk;
    CChunkFile::CChunk innerChunk;
    m_texAnims.SetStage(stage);
    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(outerChunk) != 0) {
        switch (outerChunk.m_id) {
        case 'TANM':
            break;
        default:
            continue;
        }

        CTexAnim* texAnim = new (stage, const_cast<char*>(s_texanim_cpp), 0x3F) CTexAnim;
        int* ref = reinterpret_cast<int*>(texAnim->m_refData);
        if (ref != 0) {
            int nextRefCount = ref[1] - 1;
            ref[1] = nextRefCount;
            if ((nextRefCount == 0) && (ref != 0)) {
                reinterpret_cast<void (**)(int*, int)>(*ref)[2](ref, 1);
            }
            texAnim->m_refData = 0;
        }
        CTexAnim::CRefData* refData = new (stage, const_cast<char*>(s_texanim_cpp), 0xD3) CTexAnim::CRefData;
        texAnim->m_refData = refData;
        texAnim->m_refData->m_texAnimSeqs.SetStage(stage);

        chunkFile.PushChunk();
        while ((int)chunkFile.GetNextChunk(middleChunk) != 0) {
            switch (middleChunk.m_id) {
            case 'SEQ ':
                break;
            case 'NAME':
                texAnim->m_refData->m_texSrtIndex = middleChunk.m_arg0;
                strcpy(texAnim->m_refData->m_name, chunkFile.GetString());
                continue;
            default:
                continue;
            }

            CTexAnimSeq* seq = new (stage, const_cast<char*>(s_texanim_cpp), 0xE2) CTexAnimSeq;
            chunkFile.PushChunk();
            char* seqName = seq->m_name;
            while ((int)chunkFile.GetNextChunk(innerChunk) != 0) {
                if (innerChunk.m_id != 'KEY ') {
                    if (innerChunk.m_id != 'INFO') {
                        if (innerChunk.m_id == 'NAME') {
                            strcpy(seqName, chunkFile.GetString());
                            continue;
                        }
                    } else {
                        seq->m_totalFrames = chunkFile.Get4();
                        chunkFile.Get4();
                        char b7 = (char)chunkFile.Get4();
                        seq->m_flags = (unsigned char)(((int)b7 << 7) | (seq->m_flags & 0x7F));
                        char b6 = (char)chunkFile.Get4();
                        seq->m_flags = (unsigned char)((((int)b6 << 6) & 0x40) | (seq->m_flags & 0xBF));
                        unsigned int eq = (unsigned int)__cntlzw((unsigned int)strcmp(seqName, s_texAnimSeqE1));
                        seq->m_flags = (unsigned char)(((unsigned char)((int)(char)(eq >> 5) << 5) & 0x20) | (seq->m_flags & 0xDF));
                        continue;
                    }
                } else {
                    seq->m_keyCount = innerChunk.m_size / 0x30;
                    seq->m_keys = reinterpret_cast<unsigned int*>(
                        Memory._Alloc(innerChunk.m_size, stage, const_cast<char*>(s_texanim_cpp), 0x1D4, 0));
                    memcpy(seq->m_keys, chunkFile.GetAddress(), innerChunk.m_size);
                    continue;
                }
            }
            chunkFile.PopChunk();
            texAnim->m_refData->m_texAnimSeqs.Add(seq);
        }
        chunkFile.PopChunk();
        m_texAnims.Add(texAnim);
    }
    chunkFile.PopChunk();
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
    m_texAnims.ReleaseAndRemoveAll();
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80044ae8
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
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
int CPtrArray<CTexAnimSeq*>::Add(CTexAnimSeq* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
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
        delete[] m_items;
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
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CRef* item = reinterpret_cast<CRef*>(m_items[i]);
        if (item != 0) {
            int* itemWords = reinterpret_cast<int*>(item);
            int refCount = itemWords[1];
            int nextRefCount = refCount - 1;

            itemWords[1] = nextRefCount;
            if (nextRefCount == 0) {
                delete item;
            }
            m_items[i] = 0;
        }
    }

    if (m_items != 0) {
        delete[] m_items;
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
                System.Printf(const_cast<char*>(s_ptrarray_grow_error_801D7B14));
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnimSeq**)Memory._Alloc(
            (unsigned long)(m_size << 2), m_stage, const_cast<char*>(s_collection_ptrarray_h_801D7B30), 0xFA, 0);
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            delete[] m_items;
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
#pragma dont_inline reset

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
int CPtrArray<CTexAnim*>::Add(CTexAnim* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
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
        delete[] m_items;
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
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CRef* item = reinterpret_cast<CRef*>(m_items[i]);
        if (item != 0) {
            int* itemWords = reinterpret_cast<int*>(item);
            int refCount = itemWords[1];
            int nextRefCount = refCount - 1;

            itemWords[1] = nextRefCount;
            if (nextRefCount == 0) {
                delete item;
            }
            m_items[i] = 0;
        }
    }

    if (m_items != 0) {
        delete[] m_items;
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
                System.Printf(const_cast<char*>(s_ptrarray_grow_error_801D7B14));
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnim**)Memory._Alloc(
            (unsigned long)(m_size << 2), m_stage, const_cast<char*>(s_collection_ptrarray_h_801D7B30), 0xFA, 0);
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            delete[] m_items;
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
