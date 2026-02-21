#include "ffcc/maptexanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

class CMaterial;

extern "C" void Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(CMapTexAnim*, CMaterialSet*, CTextureSet*);
extern "C" void ReadJun__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*, int);
extern "C" void ReadFrame__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*);
extern "C" void ReadKey__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*, int);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dl__FPv(void*);
extern "C" void* PTR_PTR_s_CMapTexAnimSet_801e896c;
extern "C" void* PTR_PTR_s_CMapTexAnim_801ea9a4;
extern "C" char s_maptexanim_cpp_801d7ec4[];
extern "C" int IsRun__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" int Get__12CMapKeyFrameFRiRiRf(CMapKeyFrame*, int*, int*, float*);
extern "C" void Calc__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" float FLOAT_8032fd38;
extern "C" float FLOAT_8032fd48;
extern "C" float FLOAT_8032fd4c;

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

static inline CMapTexAnim*& AnimAt(CMapTexAnimSet* self, int index)
{
    return *reinterpret_cast<CMapTexAnim**>(reinterpret_cast<unsigned char*>(self) + 0xC + (index * 4));
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::CMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800335d0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnimSet::~CMapTexAnimSet()
{
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);
    const short count = *reinterpret_cast<short*>(p + 8);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnimSet_801e896c;

    for (int i = 0; i < count; i++) {
        int* entry = *reinterpret_cast<int**>(p + 0xC + (i * 4));
        if (entry != 0) {
            const int refCount = entry[1];
            entry[1] = refCount - 1;
            if ((refCount - 1) == 0 && entry != 0) {
                (*reinterpret_cast<void (**)(int*, int)>(*entry + 8))(entry, 1);
            }
            *reinterpret_cast<int**>(p + 0xC + (i * 4)) = 0;
        }
    }

    __dt__4CRefFv(this, 0);
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
    CMapTexAnim* anim;
    CChunkFile::CChunk chunk;
    int i;
    int index;

    anim = 0;
    *reinterpret_cast<CMaterialSet**>(Ptr(this, 0x10C)) = materialSet;
    *reinterpret_cast<CTextureSet**>(Ptr(this, 0x110)) = textureSet;

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == 0x4B455920) {
            ReadKey__12CMapKeyFrameFR10CChunkFilei(
                reinterpret_cast<CMapKeyFrame*>(Ptr(anim, 0x24)), &chunkFile, static_cast<char>(chunk.m_arg0));
            U8At(anim, 0x15) = 1;
        } else if ((int)chunk.m_id < 0x4B455920) {
            if (chunk.m_id == 0x4A554E20) {
                ReadJun__12CMapKeyFrameFR10CChunkFilei(
                    reinterpret_cast<CMapKeyFrame*>(Ptr(anim, 0x24)), &chunkFile, static_cast<char>(chunk.m_arg0));
            } else if (((int)chunk.m_id < 0x4A554E20) && (chunk.m_id == 0x4652414D)) {
                ReadFrame__12CMapKeyFrameFR10CChunkFilei(reinterpret_cast<CMapKeyFrame*>(Ptr(anim, 0x24)), &chunkFile);
            }
        } else if (chunk.m_id == 0x54414E4D) {
            anim = static_cast<CMapTexAnim*>(__nw__FUlPQ27CMemory6CStagePci(
                0x4C, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_maptexanim_cpp_801d7ec4, 0x24));
            if (anim != 0) {
                __ct__4CRefFv(anim);
                *reinterpret_cast<void**>(anim) = &PTR_PTR_s_CMapTexAnim_801ea9a4;
                F32At(anim, 0x18) = FLOAT_8032fd48;
                F32At(anim, 0x1C) = FLOAT_8032fd4c;
                *reinterpret_cast<void**>(Ptr(anim, 0x3C)) = 0;
                *reinterpret_cast<void**>(Ptr(anim, 0x40)) = 0;
                *reinterpret_cast<void**>(Ptr(anim, 0x44)) = 0;
                *reinterpret_cast<void**>(Ptr(anim, 0x48)) = 0;
                U8At(anim, 0x14) = 0;
                U8At(anim, 0x15) = 0;
                U16At(anim, 0x12) = 0xFFFF;
                U8At(anim, 0x16) = 1;
                S32At(anim, 0x2C) = 0;
                S32At(anim, 0x30) = 0;
                *reinterpret_cast<void**>(Ptr(anim, 0x20)) = 0;
            }

            U16At(anim, 0x8) = chunkFile.Get2();
            U16At(anim, 0xA) = chunkFile.Get2();
            U16At(anim, 0xC) = chunkFile.Get2();
            U16At(anim, 0x10) = U16At(anim, 0xC);
            F32At(anim, 0x1C) = static_cast<float>(static_cast<short>(chunkFile.Get2()));
            U16At(anim, 0xE) = 0;
            F32At(anim, 0x18) = chunkFile.GetF4();
            U8At(anim, 0x14) = chunkFile.Get1();
            chunkFile.Get1();
            chunkFile.Get1();
            chunkFile.Get1();

            if (chunk.m_version == 0) {
                chunkFile.Get4();
                U16At(anim, 0x12) = 0xFFFF;
            } else {
                U16At(anim, 0x12) = chunkFile.Get2();
                chunkFile.Get2();
            }

            chunkFile.Get4();
            chunkFile.Get4();
            *reinterpret_cast<void**>(Ptr(anim, 0x20)) = __nwa__FUlPQ27CMemory6CStagePci(
                static_cast<unsigned long>(S16At(anim, 0xC) << 1), *reinterpret_cast<CMemory::CStage**>(&MapMng),
                s_maptexanim_cpp_801d7ec4, 0x3B);

            index = 0;
            for (i = 0; i < S16At(anim, 0xC); i++) {
                U16At(*reinterpret_cast<void**>(Ptr(anim, 0x20)), static_cast<unsigned int>(index)) = chunkFile.Get2();
                index += 2;
            }

            const short count = S16At(this, 8);
            S16At(this, 8) = count + 1;
            AnimAt(this, count) = anim;
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
    if (U8At(this, 0x15) != 0) {
        CMapKeyFrame* keyFrame = reinterpret_cast<CMapKeyFrame*>(Ptr(this, 0x24));
        if (IsRun__12CMapKeyFrameFv(keyFrame) != 0) {
            int keyFrameIndex = 0;
            int keyFrameIndexNext = 0;
            float blend = 0.0f;
            int reachedFrame = Get__12CMapKeyFrameFRiRiRf(keyFrame, &keyFrameIndex, &keyFrameIndexNext, &blend);

            if (reachedFrame == 0) {
                const unsigned short textureIndex = U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), keyFrameIndex * 2);
                void* texture = TextureAt(textureSet, textureIndex);
                void* material = MaterialAt(materialSet, static_cast<unsigned long>(U16At(this, 8)));
                SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA)), texture);

                if (U8At(this, 0x14) != 0) {
                    const unsigned short nextTextureIndex =
                        U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), keyFrameIndexNext * 2);
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA) + 1), nextTexture);
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = 0;
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            } else {
                const unsigned short textureIndex = U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), keyFrameIndex * 2);
                void* texture = TextureAt(textureSet, textureIndex);
                void* material = MaterialAt(materialSet, static_cast<unsigned long>(U16At(this, 8)));
                SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA)), texture);

                if (U8At(this, 0x14) != 0) {
                    const unsigned short nextTextureIndex =
                        U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), keyFrameIndexNext * 2);
                    void* nextTexture = TextureAt(textureSet, nextTextureIndex);
                    SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA) + 1), nextTexture);
                    *reinterpret_cast<char*>(Ptr(material, 0xA4)) = static_cast<char>(FLOAT_8032fd38 * blend);
                    *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
                }
            }

            Calc__12CMapKeyFrameFv(keyFrame);
        }
        return;
    }

    const float frameFloat = F32At(this, 0x1C);
    const unsigned short frameIndex = static_cast<unsigned short>(frameFloat);
    const unsigned short textureIndex = U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), frameIndex * 2);
    void* material = MaterialAt(materialSet, static_cast<unsigned long>(U16At(this, 8)));
    SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA)), TextureAt(textureSet, textureIndex));

    F32At(this, 0x1C) = F32At(this, 0x1C) + F32At(this, 0x18);
    const float endFrame = static_cast<float>(U16At(this, 0x10));
    if (endFrame <= F32At(this, 0x1C)) {
        if (U8At(this, 0x16) == 0) {
            F32At(this, 0x1C) = endFrame;
        } else {
            F32At(this, 0x1C) = F32At(this, 0x1C) - static_cast<float>(U16At(this, 0x10) - U16At(this, 0xE));
        }
    }

    if (U8At(this, 0x14) != 0) {
        int nextFrame = static_cast<int>(frameIndex) + 1;
        if (nextFrame >= static_cast<int>(U16At(this, 0xC))) {
            nextFrame = 0;
        }

        const unsigned short nextTextureIndex =
            U16At(*reinterpret_cast<void**>(Ptr(this, 0x20)), static_cast<unsigned int>(nextFrame) * 2);
        SetMaterialTextureSlot(material, static_cast<unsigned long>(U16At(this, 0xA) + 1), TextureAt(textureSet, nextTextureIndex));
        *reinterpret_cast<char*>(Ptr(material, 0xA4)) =
            static_cast<char>(FLOAT_8032fd38 * (frameFloat - static_cast<float>(frameIndex)));
        *reinterpret_cast<unsigned int*>(Ptr(material, 0x24)) |= 0x8000;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapTexAnim::SetMapTexAnim(int, int, int)
{
	// TODO
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
    int iVar1;
    int iVar2;

    iVar2 = (int)this;
    for (iVar1 = 0; iVar1 < *(short*)((int)this + 8); iVar1 = iVar1 + 1) {
        Calc__11CMapTexAnimFP12CMaterialSetP11CTextureSet(
            *(CMapTexAnim**)(iVar2 + 0xC), *(CMaterialSet**)((int)this + 0x10C),
            *(CTextureSet**)((int)this + 0x110));
        iVar2 = iVar2 + 4;
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
    int setPtr = reinterpret_cast<int>(this);

    for (int i = 0; i < S16At(this, 8); i++) {
        int anim = *reinterpret_cast<int*>(setPtr + 0xC);
        void* animPtr = reinterpret_cast<void*>(anim);
        if (S16At(animPtr, 0x12) == static_cast<short>(materialId)) {
            if (U8At(animPtr, 0x15) != 0) {
                int end = frameEnd;
                S32At(animPtr, 0x30) = frameStart;
                S32At(animPtr, 0x2C) = frameStart;
                if (S32At(animPtr, 0x38) < frameEnd) {
                    end = S32At(animPtr, 0x38);
                }
                S32At(animPtr, 0x34) = end;
                U8At(animPtr, 0x27) = static_cast<unsigned char>(wrapMode);
                U8At(animPtr, 0x28) = 1;
            } else {
                int end = frameEnd;
                S16At(animPtr, 0xE) = static_cast<short>(frameStart);
                F32At(animPtr, 0x1C) = static_cast<float>(static_cast<short>(frameStart));
                if (S16At(animPtr, 0xC) < frameEnd) {
                    end = S16At(animPtr, 0xC);
                }
                S16At(animPtr, 0x10) = static_cast<short>(end);
                U8At(animPtr, 0x16) = static_cast<unsigned char>(wrapMode);
            }
            found = 1;
        }
        setPtr += 4;
    }

    if ((found == 0) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
        System.Printf("SetMapTexAnim: material id (%d) not found\n", materialId);
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
CMapTexAnim::~CMapTexAnim()
{
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnim_801ea9a4;

    __dl__FPv(*reinterpret_cast<void**>(p + 0x20));
    *reinterpret_cast<void**>(p + 0x20) = 0;

    if (this != reinterpret_cast<CMapTexAnim*>(-0x24)) {
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

    __dt__4CRefFv(this, 0);
}
