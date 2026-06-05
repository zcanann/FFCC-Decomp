#include "ffcc/pppVertexApAt.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

struct VertexApAtEntry
{
    u16 unk0;
    s16 maxValue;
    u32 unk4;
};

struct VertexApAtEnv
{
    u8 unk0[0x10];
    VertexApAtEntry* entries;
};

struct VertexApAtData
{
    u8 unk0[0x4];
    s16 entryIndex;
    u8 spawnCount;
    u8 waitFrames;
    u8 mode;
    u8 unk9[0x2];
    u32 childId;
    u32 childValueOffset;
};

struct VertexApAtState
{
    u16 index;
    u16 countdown;
};

struct _pppPDataVal;

/*
 * --INFO--
 * PAL Address: 0x80064b08
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAt(_pppPObject* parent, PVertexApAt* data, _pppCtrlTable* ctrl)
{
    VertexApAtData* vtxData = (VertexApAtData*)data;
    s32 stateOffset = *ctrl->m_serializedDataOffsets;
    VertexApAtState* state = (VertexApAtState*)(parent->m_workArea + stateOffset);

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (vtxData->entryIndex < 0) {
        return;
    }

    if (state->countdown == 0) {
        int count = vtxData->spawnCount;
        VertexApAtEnv* env = (VertexApAtEnv*)ppvEnv;
        VertexApAtEntry* entry = &env->entries[vtxData->entryIndex];

        switch (vtxData->mode) {
        case 0:
            while (count-- != 0) {
                if (state->index >= entry->maxValue) {
                    state->index = 0;
                }

                u16 outValue = state->index;
                state->index++;

                if ((vtxData->childId + 0x10000) != 0xFFFF) {
                    s32 childId = vtxData->childId;
                    _pppPDataVal* childData = ppvMng->m_pppPDataVals + childId;
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject(ppvMng, childData);
                        child->m_link.m_previous = &parent->m_link;
                    }

                    *(u16*)(child->m_workArea + vtxData->childValueOffset) = outValue;
                }
            }
            break;
        case 1:
            while (count-- != 0) {
                f32 randValue = Math.RandF();
                f32 maxValue = (f32)entry->maxValue;
                int outValue = (int)(randValue * maxValue);
                u16 outValue16 = (u16)outValue;

                if ((vtxData->childId + 0x10000) != 0xFFFF) {
                    s32 childId = vtxData->childId;
                    _pppPDataVal* childData = ppvMng->m_pppPDataVals + childId;
                    _pppPObject* child;

                    if (childData == 0) {
                        child = 0;
                    } else {
                        child = pppCreatePObject(ppvMng, childData);
                        child->m_link.m_previous = &parent->m_link;
                    }

                    *(u16*)(child->m_workArea + vtxData->childValueOffset) = outValue16;
                }
            }
            break;
        }

        state->countdown = vtxData->waitFrames;
    }

    state->countdown--;
}

/*
 * --INFO--
 * PAL Address: 0x80064cc8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAtCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    s32 offset = *ctrl->m_serializedDataOffsets;
    u16* state = (u16*)(obj->m_workArea + offset);
    state[0] = 0;
    state[1] = 0;
}
