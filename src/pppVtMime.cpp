#include "ffcc/pppVtMime.h"

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
    short vertexCount;
    unsigned char pad2[0x2A];
    float* positions;
};

struct VtMimeEnv
{
    void* stage;
    void* unk4;
    void** sourceTable;
};

extern int lbl_8032ED70;
extern VtMimeEnv* lbl_8032ED54;
extern const float lbl_803300F0;
extern char Graphic[];
static char lbl_801D8520[] = "pppVtMime.cpp";

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long size, void* stage, char* file, int line);
void _WaitDrawDone__8CGraphicFPci(void* graphic, const char* file, int line);
void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
void DCFlushRange(void* addr, unsigned long nBytes);
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
    VtMimeState* state = (VtMimeState*)((char*)object + *ctrl->m_serializedDataOffsets + 0x80);
    VtMimeData* data = (VtMimeData*)step;

    if (lbl_8032ED70 != 0) {
        return;
    }

    state->velocity += state->accel;
    state->value += state->velocity;
    if (data->id == *(int*)((char*)object + 0xC)) {
        state->value += data->addX;
        state->velocity += data->addY;
        state->accel += data->addZ;
    }
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
    *(void**)((char*)object + 0x70) = 0;

    int vertIdx1 = *(int*)((char*)step + 0x4);
    if (vertIdx1 == 0xFFFF && *(int*)((char*)step + 0x8) == 0xFFFF) {
        return;
    }

    VtMimeState* state = (VtMimeState*)((char*)object + *ctrl->m_serializedDataOffsets + 0x80);
    void** sourceTable = lbl_8032ED54->sourceTable;
    int vertIdx2 = *(int*)((char*)step + 0x8);
    VtMimeSource* vert1Data = (VtMimeSource*)sourceTable[vertIdx1];
    VtMimeSource* vert2Data = (VtMimeSource*)sourceTable[vertIdx2];
    float* vert1Pos = vert1Data->positions;
    float* vert2Pos = vert2Data->positions;
    unsigned short vertCount = (unsigned short)vert1Data->vertexCount;
    void** memPtr = &state->vertexBuffer;

    if (*memPtr == 0) {
        *memPtr = pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(vertCount * 0xC), lbl_8032ED54->stage, lbl_801D8520, 0x2B);
    }

    float* outputVerts = (float*)*memPtr;
    int remaining = (int)vertCount;
    int pairCount = remaining >> 1;
    while (pairCount != 0) {
        outputVerts[0] = vert1Pos[0] + state->value * (vert2Pos[0] - vert1Pos[0]);
        outputVerts[1] = vert1Pos[1] + state->value * (vert2Pos[1] - vert1Pos[1]);
        outputVerts[2] = vert1Pos[2] + state->value * (vert2Pos[2] - vert1Pos[2]);
        outputVerts[3] = vert1Pos[3] + state->value * (vert2Pos[3] - vert1Pos[3]);
        outputVerts[4] = vert1Pos[4] + state->value * (vert2Pos[4] - vert1Pos[4]);
        outputVerts[5] = vert1Pos[5] + state->value * (vert2Pos[5] - vert1Pos[5]);
        vert1Pos += 6;
        vert2Pos += 6;
        outputVerts += 6;
        pairCount--;
    }
    if ((remaining & 1) != 0) {
        outputVerts[0] = vert1Pos[0] + state->value * (vert2Pos[0] - vert1Pos[0]);
        outputVerts[1] = vert1Pos[1] + state->value * (vert2Pos[1] - vert1Pos[1]);
        outputVerts[2] = vert1Pos[2] + state->value * (vert2Pos[2] - vert1Pos[2]);
    }

    DCFlushRange(*memPtr, (unsigned long)(vertCount * 0xC));

    *(void**)((char*)object + 0x70) = *memPtr;
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
    VtMimeState* state = (VtMimeState*)((char*)object + *ctrl->m_serializedDataOffsets + 0x80);
    float zero = lbl_803300F0;

    state->accel = zero;
    state->velocity = zero;
    state->value = zero;
    state->vertexBuffer = 0;
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
    VtMimeState* state = (VtMimeState*)((char*)object + *ctrl->m_serializedDataOffsets + 0x80);
    float zero = lbl_803300F0;

    state->accel = zero;
    state->velocity = zero;
    state->value = zero;
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
    VtMimeState* state = (VtMimeState*)((char*)object + *ctrl->m_serializedDataOffsets + 0x80);

    if (state->vertexBuffer != 0) {
        void* graphic = &Graphic;
        char* file = lbl_801D8520;
        _WaitDrawDone__8CGraphicFPci(graphic, file, 0x50);
        pppHeapUseRate__FPQ27CMemory6CStage(state->vertexBuffer);
        state->vertexBuffer = 0;
    }
}
