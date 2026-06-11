#include "ffcc/texanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/materialman.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"
#include "ffcc/math.h"

#include <string.h>
#include <math.h>
#include "dolphin/mtx.h"

extern const float kTexAnimZero = 0.0f;
extern const float kTexAnimOne = 1.0f;
extern const double kTexAnimIntToDoubleBias = 4503599627370496.0;
static const char s_texAnimSeqE1[] = "e1";
extern const float kTexAnimChinFrameStep = 1.25f;

static const char sTexAnimPtrArrayGrowError[] = {
    0x83, 0x6f, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x90, 0xac, 0x92, 0xb7, 0x82, 0xaa,
    0x95, 0x73, 0x8b, 0x96, 0x89, 0xc2, 0x82, 0xc5, 0x82, 0xb7, 0x81, 0x42, 0x0a, 0x00,
};
static const char sTexAnimCollectionPtrArrayHeader[] = "collection_ptrarray.h";

namespace {
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
    const float& zero = kTexAnimZero;
    m_refData = 0;
    m_seqIndex = 0;
    m_frame = zero;
    m_mode = -2;
    m_texGen.z = zero;
    m_texGen.y = zero;
    m_texGen.x = zero;
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
    const float& zero = kTexAnimZero;
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
CTexAnim::CRefData::~CRefData()
{
    CRef* material = reinterpret_cast<CRef*>(m_material);
    if (material != 0) {
        if (--material->refCount == 0) {
            delete material;
        }
        m_material = 0;
    }
    m_texAnimSeqs.ReleaseAndRemoveAll();
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
    CRef* refData = reinterpret_cast<CRef*>(m_refData);
    if (refData != 0) {
        if (refData->DecRef() == 0) {
            delete refData;
        }
        m_refData = 0;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnim::SetTexGen()
{
    const float zero = kTexAnimZero;
    CMaterial* material = m_refData->m_material;

    if (material != 0) {
        CTexScroll* texScroll = material->GetTexScroll(m_refData->m_texSrtIndex);
        texScroll->m_u0 = m_texGen.x;
        texScroll->m_v0 = m_texGen.y;
        texScroll->m_u1 = zero;
        texScroll->m_v1 = zero;
        if (zero == texScroll->m_u1) {
            texScroll->m_type0 = 0;
        } else {
            texScroll->m_type0 = 1;
        }
        if (zero == texScroll->m_v1) {
            texScroll->m_type1 = 0;
        } else {
            texScroll->m_type1 = 1;
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
    const float zero = kTexAnimZero;

    for (unsigned int i = 0; i < static_cast<unsigned int>(m_texAnims.GetSize()); i++) {
        CTexAnim* texAnim = m_texAnims[i];
        CMaterial* material = texAnim->m_refData->m_material;

        if (material != 0) {
            float y = texAnim->m_texGen.y;
            int index = texAnim->m_refData->m_texSrtIndex;
            float x = texAnim->m_texGen.x;
            material->m_textureData.m_texScroll[index].m_u0 = x;
            material->m_textureData.m_texScroll[index].m_v0 = y;
            material->m_textureData.m_texScroll[index].m_u1 = zero;
            material->m_textureData.m_texScroll[index].m_v1 = zero;
            if (zero == material->m_textureData.m_texScroll[index].m_u1) {
                material->m_textureData.m_texScroll[index].m_type0 = 0;
            } else {
                material->m_textureData.m_texScroll[index].m_type0 = 1;
            }
            if (zero == material->m_textureData.m_texScroll[index].m_v1) {
                material->m_textureData.m_texScroll[index].m_type1 = 0;
            } else {
                material->m_textureData.m_texScroll[index].m_type1 = 1;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline int CTexAnim::Find(char* name)
{
    unsigned long idx;
    for (unsigned int i = 0; (idx = i) < static_cast<unsigned int>(m_refData->m_texAnimSeqs.GetSize()); i++) {
        CTexAnimSeq* seq = m_refData->m_texAnimSeqs[idx];
        if (strcmp(name, seq->m_name) == 0) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnim::Change(int seqIndex, float frame, CTexAnimSet::ANIM_TYPE mode)
{
    m_seqIndex = seqIndex;
    m_frame = frame;
    m_mode = static_cast<int>(mode);
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
    unsigned int texAnimIndex;

    for (texAnimIndex = 0; texAnimIndex < static_cast<unsigned int>(m_texAnims.GetSize());
         texAnimIndex = texAnimIndex + 1) {
        CTexAnim* texAnim = m_texAnims[texAnimIndex];
        int seqIndex = texAnim->Find(name);
        if (seqIndex >= 0) {
            texAnim->Change(seqIndex, frame, mode);
            return;
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnimSeq::Interp(float frame, Vec& texGen)
{
    float currentFrame = (float)fmod((double)frame, (double)(float)m_totalFrames);
    unsigned int keyCount = m_keyCount;
    CTexAnimKey* keys = m_keys;
    unsigned int keyIndex = 0;
    unsigned int lastKeyIndex = keyCount - 1;

    while (keyIndex < keyCount) {
        CTexAnimKey* keyData = &keys[keyIndex];
        float nextFrame = (float)((keyIndex < lastKeyIndex) ? keyData[1].m_frame : m_totalFrames);
        CTexAnimKey* nextKeyData;

        if (keyIndex < lastKeyIndex) {
            nextKeyData = &keys[keyIndex + 1];
        } else {
            nextKeyData = keys;
        }

        if (((float)keyData->m_frame <= currentFrame) && (currentFrame < nextFrame)) {
            float t;
            float frameSpan = nextFrame - (float)keyData->m_frame;
            if (frameSpan == kTexAnimZero) {
                t = kTexAnimZero;
            } else {
                t = (currentFrame - (float)keyData->m_frame) / frameSpan;
            }

            Vec v0;
            Vec v1;
            PSVECScale(&keyData->m_texGen, &v0, kTexAnimOne - t);
            PSVECScale(&nextKeyData->m_texGen, &v1, t);
            PSVECAdd(&v0, &v1, &texGen);

            if (!IsTexAnimInterpFlag(m_flags)) {
                texGen.x = keyData->m_texGen.x;
                texGen.y = keyData->m_texGen.y;
            }
            break;
        }

        keyIndex = keyIndex + 1;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline int CTexAnimSeq::IsChin()
{
    return IsTexAnimChinFlag(m_flags);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline int CTexAnim::IsChin()
{
    CTexAnimSeq* seq = m_refData->m_texAnimSeqs[m_seqIndex];
    return seq->IsChin();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline float CTexAnim::GetChin()
{
    return m_texGen.z;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline unsigned int CTexAnimSeq::GetTotalFrame()
{
    return m_totalFrames;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline char* CTexAnimSeq::GetName()
{
    return m_name;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnim::AddFrame(float frameStep)
{
    CTexAnimSeq* seq = m_refData->m_texAnimSeqs[m_seqIndex];

    if (!IsTexAnimE1Flag(seq->m_flags) || !IsTexAnimE1Flag(seq->m_flags) ||
        (kTexAnimOne != m_frame) || (static_cast<unsigned int>(Math.Rand(0x1E)) == 0)) {
        seq->Interp(m_frame, m_texGen);

        if (m_mode != -3) {
            m_frame = m_frame + frameStep;
            if ((float)seq->m_totalFrames <= m_frame) {
                if (m_mode == -1) {
                    m_frame = (float)seq->m_totalFrames;
                } else if (m_mode >= 0) {
                    m_seqIndex = m_mode;
                    m_mode = -2;
                }
                m_frame = m_frame - (float)seq->m_totalFrames;
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
    unsigned int i = 0;

    while (i < static_cast<unsigned int>(m_texAnims.GetSize())) {
        float frameStep;

        if (m_texAnims[i]->IsChin()) {
            frameStep = kTexAnimChinFrameStep;
        } else {
            frameStep = kTexAnimOne;
        }

        m_texAnims[i]->AddFrame(frameStep);

        if (m_texAnims[i]->IsChin()) {
            m_chin = m_texAnims[i]->GetChin();
        } else {
            m_chin = kTexAnimZero;
        }

        i = i + 1;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnim::AttachMaterialSet(CMaterialSet* materialSet)
{
    int materialIndex;
    CMaterial* material = m_refData->m_material;

    if (material != 0) {
        if (material->DecRef() == 0) {
            delete material;
        }
        m_refData->m_material = 0;
    }

    if ((materialSet != 0) && ((materialIndex = materialSet->Find(m_refData->m_name)), materialIndex >= 0)) {
        material = materialSet->GetMaterial(materialIndex);
        m_refData->m_material = material;
        m_refData->m_material->AddRef();
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
    unsigned int texAnimIndex;
    unsigned int texAnimCount;

    for (texAnimIndex = 0;
         ((texAnimCount = static_cast<unsigned int>(m_texAnims.GetSize())), texAnimIndex < texAnimCount);
         texAnimIndex = texAnimIndex + 1) {
        CTexAnim* texAnim = m_texAnims[texAnimIndex];
        texAnim->AttachMaterialSet(materialSet);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline CTexAnim* CTexAnim::Duplicate(CMemory::CStage* stage)
{
    CTexAnim* copy = new (stage, const_cast<char*>("texanim.cpp"), 0xF4) CTexAnim;

    copy->m_refData = m_refData;
    copy->m_refData->AddRef();
    copy->m_seqIndex = m_seqIndex;
    copy->m_frame = m_frame;
    copy->m_mode = m_mode;
    copy->m_texGen.x = m_texGen.x;
    copy->m_texGen.y = m_texGen.y;
    copy->m_texGen.z = m_texGen.z;

    return copy;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnimSeq::Create(CChunkFile& chunkFile, CMemory::CStage* stage)
{
    CChunkFile::CChunk chunk;

    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case 'NAME':
            strcpy(m_name, chunkFile.GetString());
            continue;
        case 'INFO': {
            m_totalFrames = chunkFile.Get4();
            chunkFile.Get4();
            m_flagBits.m_interp = (char)chunkFile.Get4();
            m_flagBits.m_chin = (char)chunkFile.Get4();
            unsigned int eq = (unsigned int)__cntlzw((unsigned int)strcmp(m_name, s_texAnimSeqE1));
            m_flagBits.m_e1 = (char)(eq >> 5);
            continue;
        }
        case 'KEY ':
            m_keyCount = chunk.m_size / 0x30;
            m_keys = static_cast<CTexAnimKey*>(
                Memory._Alloc(chunk.m_size, stage, const_cast<char*>("texanim.cpp"), 0x1D4, 0));
            memcpy(m_keys, chunkFile.GetAddress(), chunk.m_size);
            continue;
        default:
            break;
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 */
inline void CTexAnim::Create(CChunkFile& chunkFile, CMemory::CStage* stage)
{
    CChunkFile::CChunk chunk;
    CRef* ref = m_refData;

    if (ref != 0) {
        if (ref->DecRef() == 0) {
            delete ref;
        }
        m_refData = 0;
    }
    CTexAnim::CRefData* refData = new (stage, const_cast<char*>("texanim.cpp"), 0xD3) CTexAnim::CRefData;
    m_refData = refData;
    m_refData->m_texAnimSeqs.SetStage(stage);

    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case 'NAME':
            m_refData->m_texSrtIndex = chunk.m_arg0;
            strcpy(m_refData->m_name, chunkFile.GetString());
            break;
        case 'SEQ ': {
            CTexAnimSeq* seq = new (stage, const_cast<char*>("texanim.cpp"), 0xE2) CTexAnimSeq;
            seq->Create(chunkFile, stage);
            m_refData->m_texAnimSeqs.Add(seq);
            break;
        }
        default:
            break;
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
    CTexAnimSet* dup = new (stage, const_cast<char*>("texanim.cpp"), 0x54) CTexAnimSet;

    dup->m_texAnims.SetStage(stage);
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_texAnims.GetSize()); i++) {
        CTexAnim* src = m_texAnims[i];
        CTexAnim* copy = src->Duplicate(stage);
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
    m_texAnims.SetStage(stage);
    chunkFile.PushChunk();
    while ((int)chunkFile.GetNextChunk(outerChunk) != 0) {
        switch (outerChunk.m_id) {
        case 'TANM':
            break;
        default:
            continue;
        }

        CTexAnim* texAnim = new (stage, const_cast<char*>("texanim.cpp"), 0x3F) CTexAnim;
        texAnim->Create(chunkFile, stage);
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
#pragma dont_inline reset
template <>
void CPtrArray<CTexAnimSeq*>::ReleaseAndRemoveAll()
{
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CRef* item = reinterpret_cast<CRef*>(m_items[i]);
        if (item != 0) {
            if (--item->refCount == 0) {
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
#pragma dont_inline on

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
                System.Printf(const_cast<char*>(sTexAnimPtrArrayGrowError));
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnimSeq**)Memory._Alloc(
            (unsigned long)(m_size << 2), m_stage, const_cast<char*>(sTexAnimCollectionPtrArrayHeader), 0xFA, 0);
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
#pragma dont_inline reset
template <>
void CPtrArray<CTexAnim*>::ReleaseAndRemoveAll()
{
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CRef* item = reinterpret_cast<CRef*>(m_items[i]);
        if (item != 0) {
            if (--item->refCount == 0) {
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
#pragma dont_inline on

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
                System.Printf(const_cast<char*>(sTexAnimPtrArrayGrowError));
            }
            m_size = m_size << 1;
        }

        newItems = (CTexAnim**)Memory._Alloc(
            (unsigned long)(m_size << 2), m_stage, const_cast<char*>(sTexAnimCollectionPtrArrayHeader), 0xFA, 0);
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
