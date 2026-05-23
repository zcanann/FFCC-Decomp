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

extern "C" const char s_texanim_cpp_801d7adc[];
extern const float FLOAT_8032fb38 = 0.0f;
extern const float FLOAT_8032fb3c = 1.0f;
extern const double DOUBLE_8032fb40 = 4503599627370496.0;
extern const char DAT_8032fb48[] = "e1";
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
    m_refData = 0;
    m_seqIndex = 0;
    m_frame = FLOAT_8032fb38;
    m_mode = -2;
    m_chin = FLOAT_8032fb38;
    m_texGenT = FLOAT_8032fb38;
    m_texGenS = FLOAT_8032fb38;
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
    CTexAnimSeqStorage* self = reinterpret_cast<CTexAnimSeqStorage*>(this);

    if (self->keys != 0) {
        delete[] self->keys;
        self->keys = 0;
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
    CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(this);

    CRef* material = reinterpret_cast<CRef*>(refData->material);
    if (material != 0) {
        int* materialWords = reinterpret_cast<int*>(material);
        int refCount = materialWords[1];
        int nextRefCount = refCount - 1;

        materialWords[1] = nextRefCount;
        if (nextRefCount == 0) {
            delete material;
        }
        refData->material = 0;
    }
    refData->texAnimSeqs.ReleaseAndRemoveAll();
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
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    unsigned int i = 0;

    while (i < static_cast<unsigned int>(self->texAnims.GetSize())) {
        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[texAnim->unk0C]);
        float frameStep;

        if (IsTexAnimChinFlag(seq->flags)) {
            frameStep = FLOAT_8032fb4c;
        } else {
            frameStep = FLOAT_8032fb3c;
        }

        texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[texAnim->unk0C]);

        if (!IsTexAnimE1Flag(seq->flags) || !IsTexAnimE1Flag(seq->flags) ||
            (FLOAT_8032fb3c != texAnim->unk10) || (static_cast<unsigned int>(Math.Rand(0x1E)) == 0)) {
            float currentFrame = (float)fmod((double)texAnim->unk10, (double)(float)seq->totalFrames);
            unsigned int keyCount = seq->keyCount;
            unsigned int* keys = seq->keys;
            unsigned int keyIndex = 0;
            unsigned int lastKeyIndex = keyCount - 1;

            while (keyIndex < keyCount) {
                unsigned int* keyData = keys + keyIndex * 0xC;
                float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[0xC] : seq->totalFrames);
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
                    PSVECAdd(&v0, &v1, reinterpret_cast<Vec*>(&texAnim->unk18));

                    if (!IsTexAnimInterpFlag(seq->flags)) {
                        texAnim->unk18 = reinterpret_cast<float*>(keyData)[9];
                        texAnim->unk1C = reinterpret_cast<float*>(keyData)[10];
                    }
                    break;
                }

                keyIndex = keyIndex + 1;
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

        texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        refData = reinterpret_cast<CTexAnimRefDataStorage*>(texAnim->refData);
        seq = reinterpret_cast<CTexAnimSeqStorage*>(refData->texAnimSeqs[texAnim->unk0C]);
        if (IsTexAnimChinFlag(seq->flags)) {
            texAnim = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
            self->unk24 = texAnim->unk20;
        } else {
            self->unk24 = FLOAT_8032fb38;
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
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    CTexAnimSetStorage* dup = reinterpret_cast<CTexAnimSetStorage*>(
        new (stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0x54) CTexAnimSet);

    dup->texAnims.SetStage(stage);
    for (unsigned int i = 0; i < static_cast<unsigned int>(self->texAnims.GetSize()); i++) {
        CTexAnimStorage* src = reinterpret_cast<CTexAnimStorage*>(self->texAnims[i]);
        CTexAnimStorage* copy = reinterpret_cast<CTexAnimStorage*>(
            new (stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0xF4) CTexAnim);

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
    CTexAnimSetStorage* self = reinterpret_cast<CTexAnimSetStorage*>(this);
    int tanmTag = 0x54414E4D;
    int seqTag = 0x53455120;
    int nameTag = 0x4E414D45;
    int infoTag = 0x494E464F;
    int keyTag = 0x4B455920;

    self->texAnims.SetStage(stage);
    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(outerChunk) != 0) {
        if ((int)outerChunk.m_id != tanmTag) {
            continue;
        }

        CTexAnimStorage* texAnim = reinterpret_cast<CTexAnimStorage*>(
            new (stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0x3F) CTexAnim);
        int* ref = reinterpret_cast<int*>(texAnim->refData);
        if (ref != 0) {
            int nextRefCount = ref[1] - 1;
            ref[1] = nextRefCount;
            if ((nextRefCount == 0) && (ref != 0)) {
                reinterpret_cast<void (**)(int*, int)>(*ref)[2](ref, 1);
            }
            texAnim->refData = 0;
        }
        CTexAnimRefDataStorage* refData = reinterpret_cast<CTexAnimRefDataStorage*>(
            new (stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0xD3) CTexAnim::CRefData);
        texAnim->refData = refData;
        refData->texAnimSeqs.SetStage(stage);

        chunkFile.PushChunk();
        while ((int)chunkFile.GetNextChunk(middleChunk) != 0) {
            if ((int)middleChunk.m_id != seqTag) {
                if (((int)middleChunk.m_id < seqTag) && ((int)middleChunk.m_id == nameTag)) {
                    refData->texSrtIndex = middleChunk.m_arg0;
                    strcpy(refData->name, chunkFile.GetString());
                }
                continue;
            }

            CTexAnimSeqStorage* seq = reinterpret_cast<CTexAnimSeqStorage*>(
                new (stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0xE2) CTexAnimSeq);
            chunkFile.PushChunk();
            char* seqName = seq->name;
            while ((int)chunkFile.GetNextChunk(innerChunk) != 0) {
                if ((int)innerChunk.m_id != keyTag) {
                    if ((int)innerChunk.m_id == infoTag) {
                        seq->totalFrames = chunkFile.Get4();
                        chunkFile.Get4();
                        char b7 = (char)chunkFile.Get4();
                        seq->flags = (unsigned char)(((int)b7 << 7) | (seq->flags & 0x7F));
                        char b6 = (char)chunkFile.Get4();
                        seq->flags = (unsigned char)((((int)b6 << 6) & 0x40) | (seq->flags & 0xBF));
                        unsigned int eq = (unsigned int)__cntlzw((unsigned int)strcmp(seqName, DAT_8032fb48));
                        seq->flags = (unsigned char)(((unsigned char)((int)(char)(eq >> 5) << 5) & 0x20) | (seq->flags & 0xDF));
                    } else if (((int)innerChunk.m_id >= keyTag) && ((int)innerChunk.m_id == nameTag)) {
                        strcpy(seqName, chunkFile.GetString());
                    }
                } else {
                    seq->keyCount = innerChunk.m_size / 0x30;
                    seq->keys = reinterpret_cast<unsigned int*>(
                        Memory._Alloc(innerChunk.m_size, stage, const_cast<char*>(s_texanim_cpp_801d7adc), 0x1D4, 0));
                    memcpy(seq->keys, chunkFile.GetAddress(), innerChunk.m_size);
                }
            }
            chunkFile.PopChunk();
            refData->texAnimSeqs.Add(reinterpret_cast<CTexAnimSeq*>(seq));
        }
        chunkFile.PopChunk();
        self->texAnims.Add(reinterpret_cast<CTexAnim*>(texAnim));
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
    reinterpret_cast<CTexAnimSetStorage*>(this)->texAnims.ReleaseAndRemoveAll();
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
    const float& zero = FLOAT_8032fb38;
    m_chin = zero;
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
