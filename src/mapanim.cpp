#define FFCC_PTRARRAY_NO_INLINE_ACCESSORS
#include "ffcc/mapanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "dolphin/mtx.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <PowerPC_EABI_Support/Runtime/New.h>

static const char s_mapanim_cpp[] = "mapanim.cpp";
static const char s_ptrarray_grow_error[] =
    "\x83\x6F\x83\x62\x83\x74\x83\x40\x90\xAC\x92\xB7\x82\xAA\x95\x73\x8B\x96\x89\xC2\x82\xC5\x82\xB7\x81\x42\x0A";
static const char s_collection_ptrarray_h[] = "collection_ptrarray.h";

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
    m_startFrame = startFrame;
    m_endFrame = endFrame;
    m_loop = static_cast<unsigned char>(loop);
    m_currentFrame = m_startFrame;
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
    if (m_currentFrame < 0) {
        goto checkStart;
    }

runFrame:
    CPtrArray<CMapAnim*>* mapAnimArray = &MapMng.GetMapAnimArray();
    CMapAnim* mapAnim = (*mapAnimArray)[m_mapAnimIndex];
    mapAnim->Calc(m_currentFrame);
    if (++m_currentFrame > m_endFrame) {
        if (m_loop != 0) {
            m_currentFrame = 0;
        } else {
            m_currentFrame = -1;
        }
    }
    return;

checkStart:
    if (m_triggerFrame != frame) {
        return;
    }
    m_currentFrame = m_startFrame;
    goto runFrame;
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

    CPtrArray<CMapAnimNode*>* nodeArray = &mapAnimNodes;
    nodeCount = mapAnimNodes.GetSize();
    for (i = 0; i < nodeCount; i = i + 1) {
        CMapAnimNode* node = (*nodeArray)[i];
        node->Interp(frame);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapAnimNode::~CMapAnimNode()
{
    m_mapAnim = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapAnimNode::CMapAnimNode()
{
    m_tracks = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMapAnimKeyDt::CMapAnimKeyDt()
{
    position.keys = 0;
    rotation.keys = 0;
    scale.keys = 0;
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
    CMapAnimNode* item;
    CPtrArray<CMapAnimKeyDt*>* mapAnimKeyDtArray;
    int nodeIdx;

    chunkFile.PushChunk();
    mapAnimKeyDtArray = &MapMng.GetMapAnimKeyDtArray();
    while ((hasChunk = static_cast<int>(chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(outerChunkData)))) != 0) {
        if (chunkId == 0x4652414D) {
            m_startFrame = static_cast<int>(chunkFile.Get4());
            m_endFrame = static_cast<int>(chunkFile.Get4());
        } else if (chunkId == 0x4E4F4445) {
            item = new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0xC2) CMapAnimNode;
            item->m_mapAnim = this;

            chunkFile.PushChunk();
            while ((hasChunk = static_cast<int>(chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(innerChunkData)))) != 0) {
                if (innerChunkId == 0x4E494458) {
                    nodeIdx = static_cast<int>(chunkFile.Get4());
                    item->m_node = reinterpret_cast<CMapAnimTargetNode*>(MapMng.GetMapObj(nodeIdx));
                } else if (innerChunkId == 0x5452414E) {
                    CMapAnimKeyDt* tracks = new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x4C) CMapAnimKeyDt;

                    item->m_tracks = tracks;
                    mapAnimKeyDtArray->Add(item->m_tracks);
                    item->m_tracks->position.count = innerChunkSize >> 4;
                    item->m_tracks->position.keys =
                        new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x4F)
                            CMapAnimKey[item->m_tracks->position.count];
                    memcpy(item->m_tracks->position.keys, chunkFile.GetAddress(), innerChunkSize);
                } else if (innerChunkId == 0x524F5420) {
                    item->m_tracks->rotation.count = innerChunkSize >> 4;
                    item->m_tracks->rotation.keys =
                        new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x55)
                            CMapAnimKey[item->m_tracks->rotation.count];
                    memcpy(item->m_tracks->rotation.keys, chunkFile.GetAddress(), innerChunkSize);
                } else if (innerChunkId == 0x5343414C) {
                    item->m_tracks->scale.count = innerChunkSize >> 4;
                    item->m_tracks->scale.keys =
                        new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x5B)
                            CMapAnimKey[item->m_tracks->scale.count];
                    memcpy(item->m_tracks->scale.keys, chunkFile.GetAddress(), innerChunkSize);
                }
            }
            chunkFile.PopChunk();
            mapAnimNodes.Add(item);
        }
    }
    chunkFile.PopChunk();
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

    while (static_cast<unsigned int>(mapAnimNodes.GetSize()) > i) {
        CMapAnimNode* node = mapAnimNodes[i];
        if (node != 0 && (node = mapAnimNodes[i], node != 0)) {
            node->m_mapAnim = 0;
            operator delete(node);
        }
        i++;
    }

    mapAnimNodes.RemoveAll();
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
    mapAnimNodes.SetStage(MapMng.m_stage);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMapAnimNode::interp(Vec* out, CMapAnimKey* keys, int trackCount, int frameInLoop)
{
    if (trackCount == 1) {
        *out = keys[0].value;
    } else {
        CMapAnimKey* current = keys;
        unsigned int i = 0;

        for (; i < trackCount; i++) {
            unsigned int nextIndex = (trackCount <= (i + 1)) ? 0 : (i + 1);
            CMapAnimKey* next = keys + nextIndex;
            unsigned int endFrame;

            if (nextIndex != 0) {
                endFrame = next->frame;
            } else {
                endFrame = next->frame +
                    static_cast<unsigned int>((m_mapAnim->m_endFrame - m_mapAnim->m_startFrame) + 1);
            }

            unsigned int currentFrame = current->frame;
            if ((currentFrame <= static_cast<unsigned int>(frameInLoop)) &&
                (frameInLoop < static_cast<int>(endFrame))) {
                unsigned int frameRange = endFrame - currentFrame;
                float t;
                Vec currentScaled;
                Vec nextScaled;

                if (frameRange == 0) {
                    t = 0.0f;
                } else {
                    t = static_cast<float>(static_cast<unsigned int>(frameInLoop) - currentFrame) /
                        static_cast<float>(frameRange);
                }

                PSVECScale(&current->value, &currentScaled, t);
                PSVECScale(&next->value, &nextScaled, 1.0f - t);
                PSVECAdd(&currentScaled, &nextScaled, out);
                break;
            }

            current++;
        }
    }
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
    int frameInLoop = m_mapAnim->m_startFrame +
        (frame % static_cast<unsigned int>(m_mapAnim->m_endFrame - m_mapAnim->m_startFrame + 1));

    interp(&m_node->position, m_tracks->position.keys, m_tracks->position.count, frameInLoop);
    interp(&m_node->rotation, m_tracks->rotation.keys, m_tracks->rotation.count, frameInLoop);
    interp(&m_node->scale, m_tracks->scale.keys, m_tracks->scale.count, frameInLoop);
    m_node->dirty = 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 564b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMapAnimNode::ReadOtmAnimNode(CChunkFile& chunkFile, CMapAnim* mapAnim)
{
    unsigned int chunkData[4];
    unsigned int& chunkId = chunkData[0];
    unsigned int& chunkSize = chunkData[3];
    CPtrArray<CMapAnimKeyDt*>* mapAnimKeyDtArray = &MapMng.GetMapAnimKeyDtArray();
    int hasChunk;

    m_mapAnim = mapAnim;
    chunkFile.PushChunk();
    while ((hasChunk = static_cast<int>(chunkFile.GetNextChunk(*reinterpret_cast<CChunkFile::CChunk*>(chunkData)))) != 0) {
        if (chunkId == 0x4E494458) {
            int nodeIdx = static_cast<int>(chunkFile.Get4());
            m_node = reinterpret_cast<CMapAnimTargetNode*>(MapMng.GetMapObj(nodeIdx));
        } else if (chunkId == 0x5452414E) {
            CMapAnimKeyDt* keyData =
                new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x4C) CMapAnimKeyDt;
            m_tracks = keyData;
            mapAnimKeyDtArray->Add(keyData);
            m_tracks->position.count = chunkSize >> 4;
            m_tracks->position.keys =
                new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x4F)
                    CMapAnimKey[m_tracks->position.count];
            memcpy(m_tracks->position.keys, chunkFile.GetAddress(), chunkSize);
        } else if (chunkId == 0x524F5420) {
            m_tracks->rotation.count = chunkSize >> 4;
            m_tracks->rotation.keys =
                new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x55)
                    CMapAnimKey[m_tracks->rotation.count];
            memcpy(m_tracks->rotation.keys, chunkFile.GetAddress(), chunkSize);
        } else if (chunkId == 0x5343414C) {
            m_tracks->scale.count = chunkSize >> 4;
            m_tracks->scale.keys =
                new (MapMng.m_stage, const_cast<char*>(s_mapanim_cpp), 0x5B)
                    CMapAnimKey[m_tracks->scale.count];
            memcpy(m_tracks->scale.keys, chunkFile.GetAddress(), chunkSize);
        }
    }
    chunkFile.PopChunk();
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
    if (position.keys != 0) {
        delete[] position.keys;
        position.keys = 0;
    }
    if (rotation.keys != 0) {
        delete[] rotation.keys;
        rotation.keys = 0;
    }
    if (scale.keys != 0) {
        delete[] scale.keys;
        scale.keys = 0;
    }
}

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
        delete[] m_items;
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
                System.Printf(const_cast<char*>(s_ptrarray_grow_error));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapAnimNode**>(
            Memory._Alloc(static_cast<unsigned long>(m_size << 2), m_stage, const_cast<char*>(s_collection_ptrarray_h), 0xFA, 0));
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
                System.Printf(const_cast<char*>(s_ptrarray_grow_error));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapAnimKeyDt**>(
            Memory._Alloc(static_cast<unsigned long>(m_size << 2), m_stage, const_cast<char*>(s_collection_ptrarray_h), 0xFA, 0));
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
