#define FFCC_MAPKEYFRAME_NO_DESTRUCTOR
#include "ffcc/maptexanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"
#include "ffcc/ptrarray.h"

#include <dolphin/gx.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

extern "C" {
extern const char s_SetMapTexAnim_MaterialIdNotFound[] = {
    0x6D, 0x61, 0x70, 0x83, 0x65, 0x83, 0x4E, 0x83, 0x58, 0x83, 0x60, 0x83, 0x83, 0x83, 0x41, 0x83,
    0x6A, 0x83, 0x81, 0x20, 0x69, 0x64, 0x3D, 0x25, 0x64, 0x20, 0x82, 0xAA, 0x82, 0xA0, 0x82, 0xE8,
    0x82, 0xDC, 0x82, 0xB9, 0x82, 0xF1, 0x81, 0x42, 0x0A, 0x00, 0x00, 0x00
};
static const char s_maptexanim_cpp[] = "maptexanim.cpp";
}

namespace {
static inline CMaterial* MaterialAt(CMaterialSet* materialSet, unsigned long index)
{
    return materialSet->m_materials[index];
}

static inline CTexture* TextureAt(CTextureSet* textureSet, unsigned long index)
{
    return textureSet->m_textureArray[index];
}

static inline void ReplaceRef(CTexture*& slot, CTexture* texture)
{
    CTexture* current = slot;
    if (current != 0) {
        current->Release();
        slot = 0;
    }

    slot = texture;
    texture->AddRef();
}

}

inline void CMapTexAnim::SetMaterialTextureSlot(CMaterial* material, unsigned long slotIndex, CTexture* texture)
{
    ReplaceRef(material->m_textureData.m_textures[slotIndex], texture);

    if (slotIndex >= material->m_textureCount) {
        material->m_textureCount = static_cast<unsigned short>(slotIndex + 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004f910
 * PAL Size: 276b
 * EN Address: 0x8004F704
 * EN Size: 276b
 * JP Address: 0x8004F18C
 * JP Size: 276b
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
        System.Printf(const_cast<char*>(s_SetMapTexAnim_MaterialIdNotFound), materialId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004fa24
 * PAL Size: 104b
 * EN Address: 0x8004F818
 * EN Size: 104b
 * JP Address: 0x8004F2A0
 * JP Size: 104b
 */
void CMapTexAnimSet::Calc()
{
    for (int i = 0; i < m_count; i++) {
        m_anims[i]->Calc(m_materialSet, m_textureSet);
    }
}

static const float kMapTexAnimBlendScale = 256.0f;

/*
 * --INFO--
 * PAL Address: 0x8004fa8c
 * PAL Size: 1496b
 * EN Address: 0x8004F880
 * EN Size: 1496b
 * JP Address: 0x8004F308
 * JP Size: 1496b
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
                CTexture* texture = TextureAt(textureSet, textureIndex);
                SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                    static_cast<unsigned long>(m_textureSlot), texture);

                if (m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = m_frameTable[keyFrameIndexNext];
                    CTexture* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                        static_cast<unsigned long>(m_textureSlot + 1), nextTexture);
                    char blendValue = static_cast<char>(kMapTexAnimBlendScale * frame);
                    CMaterial* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
                    material->m_shadowKColorId = blendValue;
                    material->m_tevBit |= 0x8000;
                }
            } else {
                const unsigned short textureIndex = m_frameTable[keyFrameIndex];
                CTexture* texture = TextureAt(textureSet, textureIndex);
                SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                    static_cast<unsigned long>(m_textureSlot), texture);

                if (m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = m_frameTable[keyFrameIndexNext];
                    CTexture* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex)),
                        static_cast<unsigned long>(m_textureSlot + 1), nextTexture);
                    CMaterial* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
                    material->m_shadowKColorId = 0;
                    material->m_tevBit |= 0x8000;
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
        CMaterial* material = MaterialAt(materialSet, static_cast<unsigned long>(m_materialIndex));
        material->m_shadowKColorId =
            static_cast<char>(kMapTexAnimBlendScale * (frame - static_cast<float>(static_cast<unsigned short>(frameIndex))));
        material->m_tevBit |= 0x8000;
    }
}


/*
 * --INFO--
 * PAL Address: 0x80050064
 * PAL Size: 700b
 * EN Address: 0x8004FE58
 * EN Size: 700b
 * JP Address: 0x8004F8E0
 * JP Size: 700b
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
            ref = new (g_MapMng.m_stage, const_cast<char*>(s_maptexanim_cpp),
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
                new (g_MapMng.m_stage, const_cast<char*>(s_maptexanim_cpp), 0x3B)
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
 * EN Address: 0x80050114
 * EN Size: 220b
 * JP Address: 0x8004FB9C
 * JP Size: 220b
 */
CMapTexAnim::~CMapTexAnim()
{
    delete m_frameTable;
    m_frameTable = 0;
    if (&m_keyFrame != 0) {
        m_keyFrame.Destroy();
    }
}
