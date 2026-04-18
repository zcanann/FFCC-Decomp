#include "ffcc/maptexanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

class CMaterial;

extern "C" void Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(CMapTexAnim*, CMaterialSet*, CTextureSet*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dl__FPv(void*);
extern "C" void* PTR_PTR_s_CMapTexAnim[];
extern "C" {
static const char s_maptexanim_cpp_801d7ec4[] = "maptexanim.cpp";
char s_SetMapTexAnim_MaterialIdNotFound[];
}
extern "C" float FLOAT_8032fd38;
extern "C" float FLOAT_8032fd48;
extern "C" float FLOAT_8032fd4c;

namespace {
struct CMapKeyFrameFields
{
    unsigned char m_mode;
    unsigned char m_junCount;
    unsigned char m_keyCount;
    unsigned char m_loop;
    unsigned char m_isRun;
    unsigned char m_pad05[3];
    int m_currentFrame;
    int m_startFrame;
    int m_endFrame;
    int m_frameCount;
    unsigned char* m_junTable;
    float* m_keyFrame;
    float* m_keyValue;
    float* m_splineTable;
};

struct CMapTexAnimFields
{
    void* m_vtable;
    int m_refCount;
    short m_materialIndex;
    short m_textureSlot;
    short m_frameCount;
    short m_startFrame;
    short m_endFrame;
    short m_materialId;
    unsigned char m_usesBlendTexture;
    unsigned char m_usesKeyFrame;
    unsigned char m_wrapMode;
    unsigned char m_pad17;
    float m_frameStep;
    float m_currentFrame;
    unsigned short* m_frameTable;
    CMapKeyFrameFields m_keyFrame;
};

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
    return (*reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(materialSet, 8)))[static_cast<int>(index)];
}

static inline void* TextureAt(CTextureSet* textureSet, unsigned long index)
{
    return (*reinterpret_cast<CPtrArray<CTexture*>*>(Ptr(textureSet, 8)))[static_cast<int>(index)];
}

static inline void ReplaceRef(void** slot, void* ref)
{
    int* current = reinterpret_cast<int*>(*slot);
    if (current != 0) {
        const int refCount = current[1];
        current[1] = refCount - 1;
        if ((refCount - 1) == 0) {
            reinterpret_cast<void (**)(void*, int)>(*reinterpret_cast<void**>(current))[2](current, 1);
        }
        *slot = 0;
    }

    *slot = ref;
    *reinterpret_cast<int*>(Ptr(ref, 4)) = *reinterpret_cast<int*>(Ptr(ref, 4)) + 1;
}

static inline void SetMaterialTextureSlot(void* material, unsigned long slotIndex, void* texture)
{
    void** slot = reinterpret_cast<void**>(Ptr(material, 0x3C + (slotIndex * 4)));
    ReplaceRef(slot, texture);

    unsigned short& numTexture = *reinterpret_cast<unsigned short*>(Ptr(material, 0x18));
    if (numTexture <= slotIndex) {
        numTexture = static_cast<unsigned short>(slotIndex + 1);
    }
}

static inline CMapTexAnimFields* Fields(CMapTexAnim* anim)
{
    return reinterpret_cast<CMapTexAnimFields*>(anim);
}

static inline CMapKeyFrame* KeyFrame(CMapTexAnimFields* anim)
{
    return reinterpret_cast<CMapKeyFrame*>(&anim->m_keyFrame);
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
            ref = static_cast<CMapTexAnim*>(__nw__FUlPQ27CMemory6CStagePci(
                0x4C, *reinterpret_cast<CMemory::CStage**>(&MapMng), const_cast<char*>(s_maptexanim_cpp_801d7ec4),
                0x24));
            if (ref != 0) {
                CMapTexAnimFields* anim = Fields(ref);
                __ct__4CRefFv(ref);
                *reinterpret_cast<void**>(ref) = PTR_PTR_s_CMapTexAnim;
                anim->m_keyFrame.m_junTable = 0;
                anim->m_keyFrame.m_keyFrame = 0;
                anim->m_keyFrame.m_keyValue = 0;
                anim->m_keyFrame.m_splineTable = 0;
                anim->m_keyFrame.m_loop = 1;
                anim->m_keyFrame.m_isRun = 0;
                anim->m_frameTable = 0;
                anim->m_frameStep = FLOAT_8032fd48;
                anim->m_currentFrame = FLOAT_8032fd4c;
                anim->m_usesBlendTexture = 0;
                anim->m_usesKeyFrame = 0;
                anim->m_materialId = -1;
                anim->m_wrapMode = 1;
            }

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
            unsigned short* frameTable = reinterpret_cast<unsigned short*>(__nwa__FUlPQ27CMemory6CStagePci(
                static_cast<unsigned long>(ref->m_frameCount << 1),
                *reinterpret_cast<CMemory::CStage**>(&MapMng),
                const_cast<char*>(s_maptexanim_cpp_801d7ec4), 0x3B));
            ref->m_frameTable = frameTable;

            unsigned short* frame = frameTable;
            for (int i = 0; i < ref->m_frameCount; i++, frame++) {
                *frame = chunkFile.Get2();
            }

            short count = m_count;
            m_count = count + 1;
            m_anims[count] = ref;
            break;
        case 0x4A554E20:
            KeyFrame(Fields(ref))->ReadJun(chunkFile, chunk.m_arg0);
            break;
        case 0x4652414D:
            KeyFrame(Fields(ref))->ReadFrame(chunkFile, chunk.m_arg0);
            break;
        case 0x4B455920:
            KeyFrame(Fields(ref))->ReadKey(chunkFile, chunk.m_arg0);
            ref->m_usesKeyFrame = 1;
            break;
        }
    }
    chunkFile.PopChunk();
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
    CMapTexAnimFields* anim = Fields(this);

    if (anim->m_usesKeyFrame != 0) {
        CMapKeyFrame* keyFrame = KeyFrame(anim);
        if (keyFrame->IsRun() != 0) {
            int keyFrameIndex = 0;
            int keyFrameIndexNext = 0;
            float blend = 0.0f;
            int reachedFrame = keyFrame->Get(keyFrameIndex, keyFrameIndexNext, blend);

            if (reachedFrame == 0) {
                const unsigned short textureIndex = anim->m_frameTable[keyFrameIndex];
                void* texture = TextureAt(textureSet, textureIndex);
                void* material = MaterialAt(materialSet, static_cast<unsigned long>(anim->m_materialIndex));
                SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot), texture);

                if (anim->m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = anim->m_frameTable[keyFrameIndexNext];
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot + 1), nextTexture);
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = 0;
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            } else {
                const unsigned short textureIndex = anim->m_frameTable[keyFrameIndex];
                void* texture = TextureAt(textureSet, textureIndex);
                void* material = MaterialAt(materialSet, static_cast<unsigned long>(anim->m_materialIndex));
                SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot), texture);

                if (anim->m_usesBlendTexture != 0) {
                    const unsigned short nextTextureIndex = anim->m_frameTable[keyFrameIndexNext];
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot + 1), nextTexture);
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = static_cast<char>(FLOAT_8032fd38 * blend);
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            }

            keyFrame->Calc();
        }
        return;
    }

    const float frameFloat = anim->m_currentFrame;
    const int frameIndex = static_cast<int>(frameFloat);
    const unsigned short textureIndex = anim->m_frameTable[frameIndex & 0xFFFF];
    void* material = MaterialAt(materialSet, static_cast<unsigned long>(anim->m_materialIndex));
    SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot), TextureAt(textureSet, textureIndex));

    anim->m_currentFrame = anim->m_currentFrame + anim->m_frameStep;
    const float endFrame = static_cast<float>(anim->m_endFrame);
    if (endFrame <= anim->m_currentFrame) {
        if (anim->m_wrapMode == 0) {
            anim->m_currentFrame = endFrame;
        } else {
            anim->m_currentFrame =
                anim->m_currentFrame - static_cast<float>(anim->m_endFrame - anim->m_startFrame);
        }
    }

    if (anim->m_usesBlendTexture != 0) {
        int nextFrame = (frameIndex + 1) & 0xFFFF;
        if (static_cast<float>(anim->m_frameCount) <= static_cast<float>(frameIndex + 1)) {
            nextFrame = 0;
        }

        const unsigned short nextTextureIndex = anim->m_frameTable[nextFrame];
        SetMaterialTextureSlot(material, static_cast<unsigned long>(anim->m_textureSlot + 1), TextureAt(textureSet, nextTextureIndex));
        *reinterpret_cast<char*>(Ptr(material, 0xA4)) =
            static_cast<char>(FLOAT_8032fd38 * (frameFloat - static_cast<float>(frameIndex & 0xFFFF)));
        *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapTexAnim::SetMapTexAnim(int frameStart, int frameEnd, int wrapMode)
{
    CMapTexAnimFields* anim = Fields(this);
    int end = frameEnd;

    if (anim->m_usesKeyFrame != 0) {
        anim->m_keyFrame.m_startFrame = frameStart;
        anim->m_keyFrame.m_currentFrame = frameStart;
        if (frameEnd > anim->m_keyFrame.m_frameCount) {
            end = anim->m_keyFrame.m_frameCount;
        }
        anim->m_keyFrame.m_endFrame = end;
        anim->m_keyFrame.m_loop = static_cast<unsigned char>(wrapMode);
        anim->m_keyFrame.m_isRun = 1;
    } else {
        anim->m_startFrame = static_cast<short>(frameStart);
        anim->m_currentFrame = static_cast<float>(static_cast<short>(frameStart));
        if (frameEnd > anim->m_frameCount) {
            end = anim->m_frameCount;
        }
        anim->m_endFrame = static_cast<short>(end);
        anim->m_wrapMode = static_cast<unsigned char>(wrapMode);
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
    int setPtr = reinterpret_cast<int>(this);
    for (int i = 0; i < S16At(this, 8); i++) {
        Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(
            *reinterpret_cast<CMapTexAnim**>(setPtr + 0xC),
            *reinterpret_cast<CMaterialSet**>(Ptr(this, 0x10C)),
            *reinterpret_cast<CTextureSet**>(Ptr(this, 0x110)));
        setPtr += 4;
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
    int i = 0;
    int setPtr = reinterpret_cast<int>(this);

    while (i < S16At(this, 8)) {
        void* animPtr = reinterpret_cast<void*>(*reinterpret_cast<int*>(setPtr + 0xC));
        if (static_cast<short>(materialId) == S16At(animPtr, 0x12)) {
            int end = frameEnd;
            if (U8At(animPtr, 0x15) != 0) {
                S32At(animPtr, 0x30) = frameStart;
                S32At(animPtr, 0x2C) = frameStart;
                if (frameEnd > S32At(animPtr, 0x38)) {
                    end = S32At(animPtr, 0x38);
                }
                S32At(animPtr, 0x34) = end;
                U8At(animPtr, 0x27) = static_cast<unsigned char>(wrapMode);
                U8At(animPtr, 0x28) = 1;
            } else {
                S16At(animPtr, 0xE) = static_cast<short>(frameStart);
                F32At(animPtr, 0x1C) = static_cast<float>(static_cast<short>(frameStart));
                if (frameEnd > S16At(animPtr, 0xC)) {
                    end = S16At(animPtr, 0xC);
                }
                S16At(animPtr, 0x10) = static_cast<short>(end);
                U8At(animPtr, 0x16) = static_cast<unsigned char>(wrapMode);
            }
            found = 1;
        }
        setPtr += 4;
        i += 1;
    }

    if ((found == 0) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
        System.Printf(s_SetMapTexAnim_MaterialIdNotFound, materialId);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnim::CMapTexAnim()
{
	// TODO
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
extern "C" CMapTexAnim* __dt__11CMapTexAnimFv(CMapTexAnim* anim, short shouldDelete)
{
    if (anim != 0) {
        unsigned char* const p = reinterpret_cast<unsigned char*>(anim);

        *reinterpret_cast<void**>(p) = PTR_PTR_s_CMapTexAnim;

        __dl__FPv(*reinterpret_cast<void**>(p + 0x20));
        *reinterpret_cast<void**>(p + 0x20) = 0;

        if ((reinterpret_cast<int>(anim) + 0x24) != 0) {
            if (*reinterpret_cast<void**>(p + 0x3C) != 0) {
                __dl__FPv(*reinterpret_cast<void**>(p + 0x3C));
                *reinterpret_cast<void**>(p + 0x3C) = 0;
            }
            if (*reinterpret_cast<void**>(p + 0x40) != 0) {
                __dl__FPv(*reinterpret_cast<void**>(p + 0x40));
                *reinterpret_cast<void**>(p + 0x40) = 0;
            }
            if (*reinterpret_cast<void**>(p + 0x44) != 0) {
                __dl__FPv(*reinterpret_cast<void**>(p + 0x44));
                *reinterpret_cast<void**>(p + 0x44) = 0;
            }
            if (*reinterpret_cast<void**>(p + 0x48) != 0) {
                __dl__FPv(*reinterpret_cast<void**>(p + 0x48));
                *reinterpret_cast<void**>(p + 0x48) = 0;
            }
        }

        __dt__4CRefFv(anim, 0);
        if (shouldDelete > 0) {
            __dl__FPv(anim);
        }
    }

    return anim;
}
