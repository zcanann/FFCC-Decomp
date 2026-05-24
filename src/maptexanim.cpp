#include "ffcc/maptexanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#define FFCC_PTRARRAY_NO_INLINE_ACCESSORS
#include "ffcc/ptrarray.h"

#include <PowerPC_EABI_Support/Runtime/New.h>

class CMaterial;

class CMaterialSet : public CRef
{
public:
    CPtrArray<CMaterial*> m_materials;
};

class CTextureSet : public CRef
{
public:
    CPtrArray<CTexture*> m_textures;
};

extern "C" {
extern "C" const char s_maptexanim_cpp[] = "maptexanim.cpp";
const char s_CMapTexAnim[] = "CMapTexAnim";
char s_SetMapTexAnim_MaterialIdNotFound[];
}
extern "C" float FLOAT_8032fd38;
extern "C" float FLOAT_8032fd48;
extern "C" float FLOAT_8032fd4c;
extern "C" const double DOUBLE_8032FCD0 = 4503601774854144.0;
extern "C" const float FLOAT_8032FCD8 = 0.0f;

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline short& S16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<short*>(Ptr(p, offset));
}

static inline unsigned short& U16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(p, offset));
}

static inline int& S32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(p, offset));
}

static inline float& F32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(p, offset));
}

static inline unsigned char& U8At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(p, offset));
}

static inline void* MaterialAt(CMaterialSet* materialSet, unsigned long index)
{
    return materialSet->m_materials[index];
}

static inline void* TextureAt(CTextureSet* textureSet, unsigned long index)
{
    return textureSet->m_textures[index];
}

static inline void ReplaceRef(void** slot, void* ref)
{
    CRef* current = reinterpret_cast<CRef*>(*slot);
    if (current != 0) {
        int* refCountPtr = reinterpret_cast<int*>(Ptr(current, 4));
        int refCount = *refCountPtr - 1;
        *refCountPtr = refCount;
        if (refCount == 0) {
            delete current;
        }
        *slot = 0;
    }

    *slot = ref;
    reinterpret_cast<CRef*>(ref)->AddRef();
}

static inline void SetMaterialTextureSlot(void* material, unsigned long slotIndex, void* texture)
{
    ReplaceRef(reinterpret_cast<void**>(Ptr(material, 0x3C) + (slotIndex * 4)), texture);

    unsigned short& numTexture = *reinterpret_cast<unsigned short*>(Ptr(material, 0x18));
    if (slotIndex >= numTexture) {
        numTexture = static_cast<unsigned short>(slotIndex + 1);
    }
}
}

/*
 * --INFO--
 * PAL Address: 0x8004f910
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnimSet::SetMapTexAnim(int materialId, int frameStart, int frameEnd, int wrapMode)
{
    int found = 0;

    for (int i = 0; i < m_count; i++) {
        if (m_anims[i]->m_materialId == static_cast<short>(materialId)) {
            m_anims[i]->SetMapTexAnim(frameStart, frameEnd, wrapMode);
            found = 1;
        }
    }

    if ((found == 0) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
        System.Printf(s_SetMapTexAnim_MaterialIdNotFound, materialId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004fa24
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnimSet::Calc()
{
    for (int i = 0; i < m_count; i++) {
        m_anims[i]->Calc(m_materialSet, m_textureSet);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004fa8c
 * PAL Size: 1496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnim::Calc(CMaterialSet* materialSet, CTextureSet* textureSet)
{
    float frame;

    if (m_usesKeyFrame != 0) {
        if (m_keyFrame.IsRun() != 0) {
            int keyFrameIndex;
            int keyFrameIndexNext;
            int reachedFrame = m_keyFrame.Get(keyFrameIndex, keyFrameIndexNext, frame);

            if (reachedFrame != 0) {
                const unsigned short textureIndex = m_frameTable[keyFrameIndex];
                void* texture = TextureAt(textureSet, textureIndex);
                SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                    static_cast<unsigned long>(m_textureSlot), texture);

                if (m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = m_frameTable[keyFrameIndexNext];
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                        static_cast<unsigned long>(m_textureSlot + 1), nextTexture);
                    char blendValue = static_cast<char>(FLOAT_8032fd38 * frame);
                    void* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = blendValue;
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            } else {
                const unsigned short textureIndex = m_frameTable[keyFrameIndex];
                void* texture = TextureAt(textureSet, textureIndex);
                SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                    static_cast<unsigned long>(m_textureSlot), texture);

                if (m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = m_frameTable[keyFrameIndexNext];
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                        static_cast<unsigned long>(m_textureSlot + 1), nextTexture);
                    void* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = 0;
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            }

            m_keyFrame.Calc();
        }
        return;
    }

    frame = m_currentFrame;
    const int frameIndex = static_cast<int>(frame);
    const unsigned short textureIndex = m_frameTable[frameIndex & 0xFFFF];
    SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
        static_cast<unsigned long>(m_textureSlot), TextureAt(textureSet, textureIndex));

    m_currentFrame = m_currentFrame + m_frameStep;
    if (m_currentFrame >= static_cast<float>(m_endFrame)) {
        if (m_wrapMode != 0) {
            m_currentFrame = m_currentFrame - static_cast<float>(m_endFrame - m_startFrame);
        } else {
            m_currentFrame = static_cast<float>(m_endFrame);
        }
    }

    if (m_usesBlendTexture != 0) {
        int nextFrame = (frameIndex + 1) & 0xFFFF;
        if (static_cast<float>(static_cast<unsigned short>(nextFrame)) >= static_cast<float>(m_frameCount)) {
            nextFrame = 0;
        }

        const unsigned short nextTextureIndex = m_frameTable[static_cast<unsigned short>(nextFrame)];
        SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
            static_cast<unsigned long>(m_textureSlot + 1), TextureAt(textureSet, nextTextureIndex));
        void* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
        *reinterpret_cast<char*>(Ptr(material, 0xA4)) =
            static_cast<char>(FLOAT_8032fd38 * (frame - static_cast<float>(static_cast<unsigned short>(frameIndex))));
        *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80050064
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnimSet::Create(CChunkFile& chunkFile, CMaterialSet* materialSet, CTextureSet* textureSet)
{
    CMapTexAnim* ref = 0;
    CChunkFile::CChunk chunk;
    m_materialSet = materialSet;
    m_textureSet = textureSet;

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case 0x54414E4D:
            ref = new (MapMng.m_stage, const_cast<char*>(s_maptexanim_cpp),
                0x24) CMapTexAnim;

            ref->m_materialIndex = chunkFile.Get2();
            ref->m_textureSlot = chunkFile.Get2();
            ref->m_frameCount = chunkFile.Get2();
            ref->m_endFrame = ref->m_frameCount;
            ref->m_currentFrame = static_cast<float>(static_cast<short>(chunkFile.Get2()));
            ref->m_startFrame = 0;
            ref->m_frameStep = chunkFile.GetF4();
            ref->m_usesBlendTexture = chunkFile.Get1();
            chunkFile.Get1();
            chunkFile.Get1();
            chunkFile.Get1();

            if (chunk.m_version == 0) {
                chunkFile.Get4();
                ref->m_materialId = -1;
            } else {
                ref->m_materialId = chunkFile.Get2();
                chunkFile.Get2();
            }

            chunkFile.Get4();
            chunkFile.Get4();
            unsigned short* frameTable =
                new (MapMng.m_stage, const_cast<char*>(s_maptexanim_cpp), 0x3B)
                    unsigned short[ref->m_frameCount];
            ref->m_frameTable = frameTable;

            for (int i = 0; i < ref->m_frameCount; i++) {
                ref->m_frameTable[i] = chunkFile.Get2();
            }

            short count = m_count;
            m_count = count + 1;
            m_anims[count] = ref;
            break;
        case 0x4A554E20:
            ref->m_keyFrame.ReadJun(chunkFile, chunk.m_arg0);
            break;
        case 0x4652414D:
            ref->m_keyFrame.ReadFrame(chunkFile, chunk.m_arg0);
            break;
        case 0x4B455920:
            ref->m_keyFrame.ReadKey(chunkFile, chunk.m_arg0);
            ref->m_usesKeyFrame = 1;
            break;
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x80050320
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnim::~CMapTexAnim()
{
    delete m_frameTable;
    m_frameTable = 0;
    if (static_cast<void*>(&m_keyFrame) != 0) {
        m_keyFrame.Destroy();
    }
}
