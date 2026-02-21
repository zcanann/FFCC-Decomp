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
    float positions[6];
};

struct VtMimeEnv
{
    void* stage;
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
void pppVtMime(void* param1, void* param2, void* param3)
{
    VtMimeState* state = (VtMimeState*)((char*)param1 + **(int**)((char*)param3 + 0xC) + 0x80);
    VtMimeData* data = (VtMimeData*)param2;

    if (lbl_8032ED70 != 0) {
        return;
    }

    state->velocity += state->accel;
    state->value += state->velocity;
    if (data->id == *(int*)((char*)param1 + 0xC)) {
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
void pppDrawVtMime(void* param1, void* param2, void* param3)
{
    *(void**)((char*)param1 + 0x70) = 0;

    int vertIdx1 = *(int*)((char*)param2 + 0x4);
    int vertIdx2 = *(int*)((char*)param2 + 0x8);
    if (vertIdx1 == 0xFFFF && vertIdx2 == 0xFFFF) {
        return;
    }

    void* dataBase = *(void**)*(void**)((char*)param3 + 0xC);
    char* target = (char*)param1 + (int)dataBase + 0x80;
    void* globalData = *(void**)((char*)lbl_8032ED54 + 0x8);
    VtMimeSource* vert1Data = *(VtMimeSource**)((char*)globalData + (vertIdx1 * 4));
    VtMimeSource* vert2Data = *(VtMimeSource**)((char*)globalData + (vertIdx2 * 4));
    float* vert1Pos = vert1Data->positions;
    float* vert2Pos = vert2Data->positions;
    unsigned short vertCount = (unsigned short)vert1Data->vertexCount;
    void** memPtr = (void**)(target + 0xC);

    if (*memPtr == 0) {
        *memPtr = pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(vertCount * 0xC), *(void**)lbl_8032ED54, lbl_801D8520, 0x2B);
    }

    float* outputVerts = (float*)*memPtr;
    int remaining = (int)vertCount;
    int pairCount = remaining >> 1;
    while (pairCount != 0) {
        outputVerts[0] = vert1Pos[0] + *(float*)target * (vert2Pos[0] - vert1Pos[0]);
        outputVerts[1] = vert1Pos[1] + *(float*)target * (vert2Pos[1] - vert1Pos[1]);
        outputVerts[2] = vert1Pos[2] + *(float*)target * (vert2Pos[2] - vert1Pos[2]);
        outputVerts[3] = vert1Pos[3] + *(float*)target * (vert2Pos[3] - vert1Pos[3]);
        outputVerts[4] = vert1Pos[4] + *(float*)target * (vert2Pos[4] - vert1Pos[4]);
        outputVerts[5] = vert1Pos[5] + *(float*)target * (vert2Pos[5] - vert1Pos[5]);
        vert1Pos += 6;
        vert2Pos += 6;
        outputVerts += 6;
        pairCount--;
    }
    if ((remaining & 1) != 0) {
        outputVerts[0] = vert1Pos[0] + *(float*)target * (vert2Pos[0] - vert1Pos[0]);
        outputVerts[1] = vert1Pos[1] + *(float*)target * (vert2Pos[1] - vert1Pos[1]);
        outputVerts[2] = vert1Pos[2] + *(float*)target * (vert2Pos[2] - vert1Pos[2]);
    }

    DCFlushRange(*memPtr, (unsigned long)(vertCount * 0xC));

    *(void**)((char*)param1 + 0x70) = *memPtr;
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
void pppVtMimeCon(void* param1, void* param2, void* param3)
{
    VtMimeState* state = (VtMimeState*)((char*)param1 + **(int**)((char*)param2 + 0xC) + 0x80);
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
void pppVtMimeCon2(void* param1, void* param2, void* param3)
{
    VtMimeState* state = (VtMimeState*)((char*)param1 + **(int**)((char*)param2 + 0xC) + 0x80);
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
void pppVtMimeDes(void* param1, void* param2)
{
    VtMimeState* state = (VtMimeState*)((char*)param1 + **(int**)((char*)param2 + 0xC) + 0x80);

    if (state->vertexBuffer != 0) {
        void* graphic = &Graphic;
        char* file = lbl_801D8520;
        _WaitDrawDone__8CGraphicFPci(graphic, file, 0x50);
        pppHeapUseRate__FPQ27CMemory6CStage(state->vertexBuffer);
        state->vertexBuffer = 0;
    }
}
