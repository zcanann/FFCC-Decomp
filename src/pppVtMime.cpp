#include "ffcc/pppVtMime.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"

#include <dolphin/os/OSCache.h>

struct VtMimeCtrl
{
    unsigned char pad0[0xC];
    int* stateOffset;
};

struct VtMimeState
{
    float value;
    float velocity;
    float accel;
    void* vertexBuffer;
};

struct VtMimeData
{
    int id;
    int sourceA;
    int sourceB;
    float addX;
    float addY;
    float addZ;
};

struct VtMimeSource
{
    unsigned short vertexCount;
    unsigned char pad2[0x2A];
    float* positions;
};

struct VtMimeEnv
{
    void* stage;
    void* unk4;
    void** sourceTable;
};

extern "C" const char s_pppVtMime_cpp[] = "pppVtMime.cpp";

static inline VtMimeState* GetVtMimeState(_pppPObject* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VtMimeState*>(object->m_workArea + *ctrl->m_serializedDataOffsets);
}

static inline VtMimeState* GetVtMimeState(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    return GetVtMimeState(reinterpret_cast<_pppPObject*>(object), ctrl);
}

/*
 * --INFO--
 * PAL Address: 80065034
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeDes(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    VtMimeState* state = GetVtMimeState(object, ctrl);

    if (state->vertexBuffer != 0) {
        Graphic._WaitDrawDone(const_cast<char*>(s_pppVtMime_cpp), 0x50);
        pppHeapUseRate(static_cast<CMemory::CStage*>(state->vertexBuffer));
        state->vertexBuffer = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8006509c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeCon2(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    VtMimeState* state = GetVtMimeState(object, ctrl);
    float zero = kPppVtMimeZero;

    state->accel = zero;
    state->velocity = zero;
    state->value = zero;
}

/*
 * --INFO--
 * PAL Address: 800650c0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeCon(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    VtMimeState* state = GetVtMimeState(object, ctrl);
    float zero = kPppVtMimeZero;

    state->accel = zero;
    state->velocity = zero;
    state->value = zero;
    state->vertexBuffer = 0;
}

/*
 * --INFO--
 * PAL Address: 800650ec
 * PAL Size: 484b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawVtMime(_pppPObject* object, void* step, _pppCtrlTable* ctrl)
{
    VtMimeData* data = (VtMimeData*)step;

    object->m_drawMatrixPtr = 0;

    int vertIdx1 = data->sourceA;
    if (vertIdx1 == 0xFFFF && data->sourceB == 0xFFFF) {
        return;
    }

    VtMimeState* state = GetVtMimeState(object, ctrl);
    VtMimeEnv* env = (VtMimeEnv*)ppvEnv;
    void** sourceTable = env->sourceTable;
    int vertIdx2 = data->sourceB;
    VtMimeSource* vert1Data = (VtMimeSource*)sourceTable[vertIdx1];
    VtMimeSource* vert2Data = (VtMimeSource*)sourceTable[vertIdx2];
    float* vert1Pos = vert1Data->positions;
    float* vert2Pos = vert2Data->positions;
    int vertCount = vert1Data->vertexCount;
    void** memPtr = &state->vertexBuffer;

    if (*memPtr == 0) {
        *memPtr = pppMemAlloc((unsigned long)(vertCount * 0xC), reinterpret_cast<CMemory::CStage*>(env->stage),
                              const_cast<char*>(s_pppVtMime_cpp), 0x2B);
    }

    float* outputVerts = (float*)*memPtr;
    int pairCount = vertCount;
    for (; pairCount != 0; pairCount--) {
        outputVerts[0] = vert1Pos[0] + state->value * (vert2Pos[0] - vert1Pos[0]);
        outputVerts[1] = vert1Pos[1] + state->value * (vert2Pos[1] - vert1Pos[1]);
        outputVerts[2] = vert1Pos[2] + state->value * (vert2Pos[2] - vert1Pos[2]);
        vert1Pos += 3;
        vert2Pos += 3;
        outputVerts += 3;
    }

    DCFlushRange(*memPtr, (unsigned long)(vertCount * 0xC));

    object->m_drawMatrixPtr = reinterpret_cast<Vec*>(*memPtr);
}

/*
 * --INFO--
 * PAL Address: 800652d0
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMime(_pppPObject* object, void* step, _pppCtrlTable* ctrl)
{
    VtMimeState* state = GetVtMimeState(object, ctrl);
    VtMimeData* data = (VtMimeData*)step;

    if (gPppCalcDisabled != 0) {
        return;
    }

    state->velocity += state->accel;
    state->value += state->velocity;
    if (data->id == object->m_graphId) {
        state->value += data->addX;
        state->velocity += data->addY;
        state->accel += data->addZ;
    }
}
