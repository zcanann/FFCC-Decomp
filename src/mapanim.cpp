#include "ffcc/mapanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "dolphin/mtx.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"

// TODO: This should be using CPtrArray.h surely?
template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    ~CPtrArray();

    int Add(T item);
    int GetSize();
    T GetAt(unsigned long index);
    void RemoveAll();
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    int setSize(unsigned long newSize);
};

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* __vt__8CPtrArrayIP12CMapAnimNode[];
extern "C" CPtrArray<CMapAnimNode*>* __ct__26CPtrArray_P12CMapAnimNode_Fv(CPtrArray<CMapAnimNode*>*);
extern "C" void SetStage__26CPtrArray_P12CMapAnimNode_FPQ27CMemory6CStage(
    CPtrArray<CMapAnimNode*>*, CMemory::CStage*);
extern "C" CMapAnimNode* __vc__26CPtrArray_P12CMapAnimNode_FUl(void*, unsigned long);
extern "C" void Calc__8CMapAnimFl(CMapAnim*, long);
extern "C" int GetSize__26CPtrArray_P12CMapAnimNode_Fv(void*);
extern "C" int Add__26CPtrArray_P12CMapAnimNode_FP12CMapAnimNode(CPtrArray<CMapAnimNode*>*, CMapAnimNode*);
extern "C" int Add__27CPtrArray_P13CMapAnimKeyDt_FP13CMapAnimKeyDt(CPtrArray<CMapAnimKeyDt*>*, CMapAnimKeyDt*);

static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";
static char s_mapanim_cpp[] = "mapanim.cpp";

/*
 * --INFO--
 * PAL Address: 0x8004ae2c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimNode*>::CPtrArray()
{
    m_vtable = __vt__8CPtrArrayIP12CMapAnimNode;
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004ae60
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimNode*>::~CPtrArray()
{
    m_vtable = __vt__8CPtrArrayIP12CMapAnimNode;
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8004ae60
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
extern "C" CPtrArray<CMapAnimNode*>* dtor_8004AE60(CPtrArray<CMapAnimNode*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        ptrArray->m_vtable = __vt__8CPtrArrayIP12CMapAnimNode;
        ptrArray->RemoveAll();
        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x8004aebc
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimNode*>::Add(CMapAnimNode* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004af78
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimNode*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x8004af80
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimNode*>::setSize(unsigned long newSize)
{
    CMapAnimNode** newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CMapAnimNode**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
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
 * PAL Address: 0x8004b070
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimKeyDt*>::Add(CMapAnimKeyDt* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004b0e0
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimKeyDt*>::setSize(unsigned long newSize)
{
    CMapAnimKeyDt** newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CMapAnimKeyDt**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
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

struct CMapAnimNodeTrackKey
{
    unsigned int frame;
    Vec value;
};

struct CMapAnimNodeTrack
{
    unsigned int count;
    CMapAnimNodeTrackKey* keys;
};

struct CMapAnimNodeTracks
{
    CMapAnimNodeTrack position;
    CMapAnimNodeTrack rotation;
    CMapAnimNodeTrack scale;
};

struct CMapAnimData
{
    unsigned char _00[0x1C];
    int startFrame;
    int endFrame;
};

struct CMapAnimTargetNode
{
    unsigned char _00[0x1B];
    unsigned char dirty;
    unsigned char _1C[0x48];
    Vec position;
    Vec rotation;
    Vec scale;
};

struct CMapAnimNodeData
{
    CMapAnimTargetNode* node;
    CMapAnimData* mapAnim;
    CMapAnimNodeTracks* tracks;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapAnimKeyDt::CMapAnimKeyDt()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004ad98
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapAnimKeyDt::~CMapAnimKeyDt()
{
    struct CMapAnimKeyDtData
    {
        unsigned int positionCount;
        CMapAnimNodeTrackKey* position;
        unsigned int rotationCount;
        CMapAnimNodeTrackKey* rotation;
        unsigned int scaleCount;
        CMapAnimNodeTrackKey* scale;
    };

    CMapAnimKeyDtData* keyData = reinterpret_cast<CMapAnimKeyDtData*>(this);

    if (keyData->position != 0) {
        __dla__FPv(keyData->position);
        keyData->position = 0;
    }
    if (keyData->rotation != 0) {
        __dla__FPv(keyData->rotation);
        keyData->rotation = 0;
    }
    if (keyData->scale != 0) {
        __dla__FPv(keyData->scale);
        keyData->scale = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapAnimNode::CMapAnimNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapAnimNode::~CMapAnimNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapAnimNode::ReadOtmAnimNode(CChunkFile&, CMapAnim*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004a9b4
 * PAL Size: 996b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapAnimNode::Interp(int frame)
{
    CMapAnimNodeData* nodeData = reinterpret_cast<CMapAnimNodeData*>(this);
    int startFrame = nodeData->mapAnim->startFrame;
    unsigned int loopFrameCount = static_cast<unsigned int>((nodeData->mapAnim->endFrame - startFrame) + 1);
    unsigned int frameInLoop = startFrame + (frame - (frame / loopFrameCount) * loopFrameCount);

    {
        int trackCount = nodeData->tracks->position.count;
        CMapAnimNodeTrackKey* keys = nodeData->tracks->position.keys;
        Vec* out = &nodeData->node->position;

        if (trackCount == 1) {
            *out = keys[0].value;
        } else {
            unsigned int i = 0;
            CMapAnimNodeTrackKey* current = keys;
            unsigned int keyCount = static_cast<unsigned int>(trackCount);

            for (unsigned int remaining = keyCount; remaining != 0; remaining--) {
                unsigned int nextIndex = (keyCount <= (i + 1)) ? 0 : (i + 1);
                CMapAnimNodeTrackKey* next = keys + nextIndex;
                unsigned int endFrame;

                if (nextIndex != 0) {
                    endFrame = next->frame;
                } else {
                    endFrame = next->frame + loopFrameCount;
                }

                unsigned int currentFrame = current->frame;
                if ((currentFrame <= frameInLoop) && ((int)frameInLoop < (int)endFrame)) {
                    unsigned int frameRange = endFrame - currentFrame;
                    float t;
                    Vec nextScaled;
                    Vec currentScaled;

                    if (frameRange == 0) {
                        t = 0.0f;
                    } else {
                        t = static_cast<float>(frameInLoop - currentFrame) / static_cast<float>(frameRange);
                    }

                    PSVECScale(&current->value, &currentScaled, 1.0f - t);
                    PSVECScale(&next->value, &nextScaled, t);
                    PSVECAdd(&currentScaled, &nextScaled, out);
                    break;
                }

                current++;
                i++;
            }
        }
    }

    {
        int trackCount = nodeData->tracks->rotation.count;
        CMapAnimNodeTrackKey* keys = nodeData->tracks->rotation.keys;
        Vec* out = &nodeData->node->rotation;

        if (trackCount == 1) {
            *out = keys[0].value;
        } else {
            unsigned int i = 0;
            CMapAnimNodeTrackKey* current = keys;
            unsigned int keyCount = static_cast<unsigned int>(trackCount);

            for (unsigned int remaining = keyCount; remaining != 0; remaining--) {
                unsigned int nextIndex = (keyCount <= (i + 1)) ? 0 : (i + 1);
                CMapAnimNodeTrackKey* next = keys + nextIndex;
                unsigned int endFrame;

                if (nextIndex != 0) {
                    endFrame = next->frame;
                } else {
                    endFrame =
                        next->frame +
                        static_cast<unsigned int>((nodeData->mapAnim->endFrame - nodeData->mapAnim->startFrame) + 1);
                }

                unsigned int currentFrame = current->frame;
                if ((currentFrame <= frameInLoop) && ((int)frameInLoop < (int)endFrame)) {
                    unsigned int frameRange = endFrame - currentFrame;
                    float t;
                    Vec nextScaled;
                    Vec currentScaled;

                    if (frameRange == 0) {
                        t = 0.0f;
                    } else {
                        t = static_cast<float>(frameInLoop - currentFrame) / static_cast<float>(frameRange);
                    }

                    PSVECScale(&current->value, &currentScaled, 1.0f - t);
                    PSVECScale(&next->value, &nextScaled, t);
                    PSVECAdd(&currentScaled, &nextScaled, out);
                    break;
                }

                current++;
                i++;
            }
        }
    }

    {
        int trackCount = nodeData->tracks->scale.count;
        CMapAnimNodeTrackKey* keys = nodeData->tracks->scale.keys;
        Vec* out = &nodeData->node->scale;

        if (trackCount == 1) {
            *out = keys[0].value;
        } else {
            unsigned int i = 0;
            CMapAnimNodeTrackKey* current = keys;
            unsigned int keyCount = static_cast<unsigned int>(trackCount);

            for (unsigned int remaining = keyCount; remaining != 0; remaining--) {
                unsigned int nextIndex = (keyCount <= (i + 1)) ? 0 : (i + 1);
                CMapAnimNodeTrackKey* next = keys + nextIndex;
                unsigned int endFrame;

                if (nextIndex != 0) {
                    endFrame = next->frame;
                } else {
                    endFrame =
                        next->frame +
                        static_cast<unsigned int>((nodeData->mapAnim->endFrame - nodeData->mapAnim->startFrame) + 1);
                }

                unsigned int currentFrame = current->frame;
                if ((currentFrame <= frameInLoop) && ((int)frameInLoop < (int)endFrame)) {
                    unsigned int frameRange = endFrame - currentFrame;
                    float t;
                    Vec nextScaled;
                    Vec currentScaled;

                    if (frameRange == 0) {
                        t = 0.0f;
                    } else {
                        t = static_cast<float>(frameInLoop - currentFrame) / static_cast<float>(frameRange);
                    }

                    PSVECScale(&current->value, &currentScaled, 1.0f - t);
                    PSVECScale(&next->value, &nextScaled, t);
                    PSVECAdd(&currentScaled, &nextScaled, out);
                    break;
                }

                current++;
                i++;
            }
        }
    }

    nodeData->node->dirty = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapAnimNode::interp(Vec*, CMapAnimKey*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004a970
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapAnim::CMapAnim()
{
    CPtrArray<CMapAnimNode*>* nodeArray = reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this);

    __ct__26CPtrArray_P12CMapAnimNode_Fv(nodeArray);
    SetStage__26CPtrArray_P12CMapAnimNode_FPQ27CMemory6CStage(nodeArray, *reinterpret_cast<CMemory::CStage**>(&MapMng));
}

/*
 * --INFO--
 * PAL Address: 0x8004a8b0
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapAnim::~CMapAnim()
{
    unsigned int i = 0;

    while (static_cast<unsigned int>(GetSize__26CPtrArray_P12CMapAnimNode_Fv(this)) > i) {
        CMapAnimNode* node = __vc__26CPtrArray_P12CMapAnimNode_FUl(this, i);
        if (node != 0 && (node = __vc__26CPtrArray_P12CMapAnimNode_FUl(this, i), node != 0)) {
            reinterpret_cast<int*>(node)[1] = 0;
            __dl__FPv(node);
        }
        i++;
    }

    reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this)->RemoveAll();
    dtor_8004AE60(reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this), -1);
}

/*
 * --INFO--
 * PAL Address: 0x8004af2c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimNode*>::RemoveAll()
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
 * PAL Address: 0x8004a5d8
 * PAL Size: 728b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapAnim::ReadOtmAnim(CChunkFile& chunkFile)
{
    unsigned int outerChunkData[4];
    unsigned int& chunkId = outerChunkData[0];
    unsigned int innerChunkData[4];
    unsigned int& innerChunkId = innerChunkData[0];
    unsigned int& innerChunkSize = innerChunkData[3];
    int hasChunk;
    int* item;
    unsigned int keyData;
    int nodeIdx;

    chunkFile.PushChunk();
    while ((hasChunk = static_cast<int>(chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(outerChunkData)))) != 0) {
        if (chunkId == 0x4652414D) {
            reinterpret_cast<int*>(this)[7] = static_cast<int>(chunkFile.Get4());
            reinterpret_cast<int*>(this)[8] = static_cast<int>(chunkFile.Get4());
        } else if (chunkId == 0x4E4F4445) {
            item = static_cast<int*>(
                __nw__FUlPQ27CMemory6CStagePci(0xC, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapanim_cpp, 0xC2));
            if (item != 0) {
                item[2] = 0;
            }
            item[1] = reinterpret_cast<int>(this);

            chunkFile.PushChunk();
            while ((hasChunk = static_cast<int>(chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(innerChunkData)))) != 0) {
                if (innerChunkId == 0x4E494458) {
                    nodeIdx = static_cast<int>(chunkFile.Get4());
                    item[0] = reinterpret_cast<int>(reinterpret_cast<unsigned char*>(&MapMng) + (nodeIdx * 0xF0) + 0x954);
                } else if (innerChunkId == 0x5452414E) {
                    keyData = reinterpret_cast<int>(
                        __nw__FUlPQ27CMemory6CStagePci(0x18, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapanim_cpp, 0x4C));
                    if (keyData != 0) {
                        *reinterpret_cast<int*>(keyData + 0x4) = 0;
                        *reinterpret_cast<int*>(keyData + 0xC) = 0;
                        *reinterpret_cast<int*>(keyData + 0x14) = 0;
                    }

                    item[2] = keyData;
                    Add__27CPtrArray_P13CMapAnimKeyDt_FP13CMapAnimKeyDt(
                        reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x21418),
                        reinterpret_cast<CMapAnimKeyDt*>(item[2]));
                    *reinterpret_cast<unsigned int*>(item[2]) = innerChunkSize >> 4;
                    *reinterpret_cast<int*>(item[2] + 0x4) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2]) << 4, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapanim_cpp, 0x4F));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0x4)), chunkFile.GetAddress(), innerChunkSize);
                } else if (innerChunkId == 0x524F5420) {
                    *reinterpret_cast<unsigned int*>(item[2] + 0x8) = innerChunkSize >> 4;
                    *reinterpret_cast<int*>(item[2] + 0xC) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2] + 0x8) << 4, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapanim_cpp, 0x55));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0xC)), chunkFile.GetAddress(), innerChunkSize);
                } else if (innerChunkId == 0x5343414C) {
                    *reinterpret_cast<unsigned int*>(item[2] + 0x10) = innerChunkSize >> 4;
                    *reinterpret_cast<int*>(item[2] + 0x14) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2] + 0x10) << 4, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapanim_cpp, 0x5B));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0x14)), chunkFile.GetAddress(), innerChunkSize);
                }
            }
            chunkFile.PopChunk();
            Add__26CPtrArray_P12CMapAnimNode_FP12CMapAnimNode(
                reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this), reinterpret_cast<CMapAnimNode*>(item));
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x8004a560
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapAnim::Calc(long frame)
{
    int nodeCount;
    int i;

    nodeCount = reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this)->GetSize();
    for (i = 0; i < nodeCount; i = i + 1) {
        CMapAnimNode* node = (*reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this))[i];
        node->Interp(frame);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004a4b8
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapAnimRun::Calc(long frame)
{
    struct CMapAnimRunData
    {
        int currentFrame;
        int startFrame;
        int endFrame;
        int triggerFrame;
        unsigned char loop;
        unsigned char _pad11;
        unsigned short mapAnimIndex;
    };

    CMapAnimRunData* run = reinterpret_cast<CMapAnimRunData*>(this);

    if (run->currentFrame < 0) {
        goto checkStart;
    }

runFrame:
    CPtrArray<CMapAnim*>* mapAnimArray =
        reinterpret_cast<CPtrArray<CMapAnim*>*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x213FC);
    CMapAnim* mapAnim = (*mapAnimArray)[run->mapAnimIndex];
    Calc__8CMapAnimFl(mapAnim, run->currentFrame);
    if (++run->currentFrame > run->endFrame) {
        if (run->loop != 0) {
            run->currentFrame = 0;
        } else {
            run->currentFrame = -1;
        }
    }
    return;

checkStart:
    if (run->triggerFrame != frame) {
        return;
    }
    run->currentFrame = run->startFrame;
    goto runFrame;
}

/*
 * --INFO--
 * PAL Address: 0x8004b978
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::operator[](unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x8004a4a0
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapAnimRun::Start(int startFrame, int endFrame, int loop)
{
    int* data = reinterpret_cast<int*>(this);

    data[1] = startFrame;
    data[2] = endFrame;
    reinterpret_cast<unsigned char*>(this)[0x10] = static_cast<unsigned char>(loop);
    data[0] = data[1];
}
