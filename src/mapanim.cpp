#include "ffcc/mapanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "dolphin/mtx.h"

#include <string.h>

// TODO: This should be using CPtrArray.h surely?
template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_numItems;
    int m_size;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    ~CPtrArray();

    int Add(T item);
    T GetAt(unsigned long index);
    T operator[](unsigned long index);
    int GetSize();
    void RemoveAll();
    void SetStage(CMemory::CStage* stage);
    int setSize(unsigned long newSize);
};

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* lbl_801EA488[];
extern "C" CPtrArray<CMapAnimNode*>* __ct__26CPtrArray_P12CMapAnimNode_Fv(CPtrArray<CMapAnimNode*>*);
extern "C" CMapAnim* __vc__21CPtrArray_P8CMapAnim_FUl(void*, unsigned long);
extern "C" CMapAnimNode* __vc__26CPtrArray_P12CMapAnimNode_FUl(void*, unsigned long);
extern "C" int Add__26CPtrArray_P12CMapAnimNode_FP12CMapAnimNode(CPtrArray<CMapAnimNode*>*, CMapAnimNode*);
extern "C" int Add__27CPtrArray_P13CMapAnimKeyDt_FP13CMapAnimKeyDt(CPtrArray<CMapAnimKeyDt*>*, CMapAnimKeyDt*);
extern unsigned char MapMng[];

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
    m_vtable = lbl_801EA488;
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
extern "C" CPtrArray<CMapAnimNode*>* dtor_8004AE60(CPtrArray<CMapAnimNode*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        ptrArray->m_vtable = lbl_801EA488;
        ptrArray->RemoveAll();
        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

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
 * PAL Address: 0x80034130
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimNode*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80034270
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80034138
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::operator[](unsigned long index)
{
    return GetAt(index);
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

static void interpTrack(Vec* out, CMapAnimNodeTrack* track, unsigned int frame, unsigned int loopFrameCount)
{
    if (track->count == 1) {
        *out = track->keys[0].value;
        return;
    }

    CMapAnimNodeTrackKey* current = track->keys;
    for (unsigned int i = 0; i < track->count; i++, current++) {
        unsigned int nextIndex = i + 1;
        if (nextIndex >= track->count) {
            nextIndex = 0;
        }

        CMapAnimNodeTrackKey* next = track->keys + nextIndex;
        unsigned int endFrame = next->frame;
        if (nextIndex == 0) {
            endFrame += loopFrameCount;
        }

        if ((current->frame <= frame) && (frame < endFrame)) {
            int frameRange = static_cast<int>(endFrame - current->frame);
            float t = 0.0f;
            if (frameRange != 0) {
                t = static_cast<float>(frame - current->frame) / static_cast<float>(frameRange);
            }

            Vec currentScaled;
            Vec nextScaled;
            PSVECScale(&current->value, &currentScaled, t);
            PSVECScale(&next->value, &nextScaled, 1.0f - t);
            PSVECAdd(&currentScaled, &nextScaled, out);
            break;
        }
    }
}


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
    unsigned char* node = reinterpret_cast<unsigned char*>(this);
    unsigned char* target = *reinterpret_cast<unsigned char**>(node + 0x00);
    unsigned char* run = *reinterpret_cast<unsigned char**>(node + 0x04);
    CMapAnimNodeTracks* tracks = *reinterpret_cast<CMapAnimNodeTracks**>(node + 0x08);

    int startFrame = *reinterpret_cast<int*>(run + 0x1C);
    unsigned int loopFrameCount = static_cast<unsigned int>((*(reinterpret_cast<int*>(run + 0x20)) - startFrame) + 1);
    unsigned int frameInLoop =
        static_cast<unsigned int>(startFrame) +
        (static_cast<unsigned int>(frame) - ((static_cast<unsigned int>(frame) / loopFrameCount) * loopFrameCount));

    interpTrack(reinterpret_cast<Vec*>(target + 0x64), &tracks->position, frameInLoop, loopFrameCount);
    interpTrack(reinterpret_cast<Vec*>(target + 0x70), &tracks->rotation, frameInLoop, loopFrameCount);
    interpTrack(reinterpret_cast<Vec*>(target + 0x7C), &tracks->scale, frameInLoop, loopFrameCount);
    target[0x1B] = 1;
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
    __ct__26CPtrArray_P12CMapAnimNode_Fv(reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this));
    reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this)->SetStage(*reinterpret_cast<CMemory::CStage**>(MapMng));
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
    CPtrArray<CMapAnimNode*>* nodeArray = reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this);
    unsigned int i = 0;

    while (i < static_cast<unsigned int>(nodeArray->m_numItems)) {
        CMapAnimNode* node = __vc__26CPtrArray_P12CMapAnimNode_FUl(this, i);
        if (node != 0 && (node = __vc__26CPtrArray_P12CMapAnimNode_FUl(this, i), node != 0)) {
            reinterpret_cast<int*>(node)[1] = 0;
            __dl__FPv(node);
        }
        i++;
    }

    nodeArray->RemoveAll();
    nodeArray->m_vtable = lbl_801EA488;
    nodeArray->RemoveAll();
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
    CChunkFile::CChunk chunk;
    int* item;
    int keyData;
    int nodeIdx;

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == 0x4652414D) {
            reinterpret_cast<int*>(this)[7] = static_cast<int>(chunkFile.Get4());
            reinterpret_cast<int*>(this)[8] = static_cast<int>(chunkFile.Get4());
        } else if (chunk.m_id == 0x4E4F4445) {
            item = static_cast<int*>(
                __nw__FUlPQ27CMemory6CStagePci(0xC, *reinterpret_cast<CMemory::CStage**>(MapMng), s_mapanim_cpp, 0xC2));
            if (item != 0) {
                item[2] = 0;
            }
            item[1] = reinterpret_cast<int>(this);

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk) != 0) {
                if (chunk.m_id == 0x4E494458) {
                    nodeIdx = static_cast<int>(chunkFile.Get4());
                    item[0] = reinterpret_cast<int>(MapMng + (nodeIdx * 0xF0));
                } else if (chunk.m_id == 0x5452414E) {
                    keyData = reinterpret_cast<int>(
                        __nw__FUlPQ27CMemory6CStagePci(0x18, *reinterpret_cast<CMemory::CStage**>(MapMng), s_mapanim_cpp, 0x4C));
                    if (keyData != 0) {
                        *reinterpret_cast<int*>(keyData + 0x4) = 0;
                        *reinterpret_cast<int*>(keyData + 0xC) = 0;
                        *reinterpret_cast<int*>(keyData + 0x14) = 0;
                    }

                    item[2] = keyData;
                    Add__27CPtrArray_P13CMapAnimKeyDt_FP13CMapAnimKeyDt(
                        reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(MapMng + 0x21418),
                        reinterpret_cast<CMapAnimKeyDt*>(item[2]));
                    *reinterpret_cast<unsigned int*>(item[2]) = chunk.m_size >> 4;
                    *reinterpret_cast<int*>(item[2] + 0x4) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2]) << 4, *reinterpret_cast<CMemory::CStage**>(MapMng), s_mapanim_cpp, 0x4F));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0x4)), chunkFile.GetAddress(), chunk.m_size);
                } else if (chunk.m_id == 0x524F5420) {
                    *reinterpret_cast<unsigned int*>(item[2] + 0x8) = chunk.m_size >> 4;
                    *reinterpret_cast<int*>(item[2] + 0xC) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2] + 0x8) << 4, *reinterpret_cast<CMemory::CStage**>(MapMng), s_mapanim_cpp, 0x55));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0xC)), chunkFile.GetAddress(), chunk.m_size);
                } else if (chunk.m_id == 0x5343414C) {
                    *reinterpret_cast<unsigned int*>(item[2] + 0x10) = chunk.m_size >> 4;
                    *reinterpret_cast<int*>(item[2] + 0x14) = reinterpret_cast<int>(
                        __nwa__FUlPQ27CMemory6CStagePci(
                            *reinterpret_cast<int*>(item[2] + 0x10) << 4, *reinterpret_cast<CMemory::CStage**>(MapMng), s_mapanim_cpp, 0x5B));
                    memcpy(reinterpret_cast<void*>(*reinterpret_cast<int*>(item[2] + 0x14)), chunkFile.GetAddress(), chunk.m_size);
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
    CPtrArray<CMapAnimNode*>* nodeArray = reinterpret_cast<CPtrArray<CMapAnimNode*>*>(this);
    int nodeCount = nodeArray->GetSize();

    for (int i = 0; i < nodeCount; i++) {
        CMapAnimNode* node = __vc__26CPtrArray_P12CMapAnimNode_FUl(this, static_cast<unsigned long>(i));
        node->Interp(static_cast<int>(frame));
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
    int* run = reinterpret_cast<int*>(this);
    CMapAnim* mapAnim;

    if (run[0] < 0 && run[3] != frame) {
        return;
    }

    if (run[0] < 0) {
        run[0] = run[1];
    }

    mapAnim = __vc__21CPtrArray_P8CMapAnim_FUl(MapMng + 0x2140C, reinterpret_cast<unsigned short*>(this)[9]);
    mapAnim->Calc(run[0]);
    int nextFrame = run[0] + 1;
    run[0] = nextFrame;

    if (nextFrame > run[2]) {
        if (reinterpret_cast<unsigned char*>(this)[0x10] != 0) {
            run[0] = 0;
        } else {
            run[0] = -1;
        }
    }
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
