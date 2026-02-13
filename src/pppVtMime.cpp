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
    void** sourceTable;
};

extern int lbl_8032ED70;
extern VtMimeEnv* lbl_8032ED54;
extern void* Graphic;
static char s_pppVtMime_cpp[] = "pppVtMime.cpp";

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

    if ((vertIdx1 & 0xFFFF0000) == 0xFFFF0000) {
        return;
    }
    if ((vertIdx2 & 0xFFFF0000) == 0xFFFF0000) {
        return;
    }

    void* dataBase = *(void**)*(void**)((char*)param3 + 0xC);
    char* target = (char*)param1 + (int)dataBase + 0x80;
    void* globalData = *(void**)((char*)lbl_8032ED54 + 0x8);
    void* vert1Data = *(void**)((char*)globalData + (vertIdx1 * 4));
    void* vert2Data = *(void**)((char*)globalData + (vertIdx2 * 4));
    float* vert1Pos = (float*)((char*)vert1Data + 0x2C);
    float* vert2Pos = (float*)((char*)vert2Data + 0x2C);
    short vertCount = *(short*)vert1Data;
    void** memPtr = (void**)(target + 0xC);

    if (*memPtr == 0) {
        *memPtr = pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(vertCount * 0xC), *(void**)lbl_8032ED54, s_pppVtMime_cpp, 0x2B);
    }

    if (vertCount > 0) {
        float* outputVerts = (float*)*memPtr;
        float interpFactor = *(float*)target;
        int i;

        for (i = 0; i < vertCount; i++) {
            float v1X = vert1Pos[i * 6 + 0];
            float v2X = vert2Pos[i * 6 + 0];
            outputVerts[i * 3 + 0] = v1X + interpFactor * (v2X - v1X);

            float v1Y = vert1Pos[i * 6 + 1];
            float v2Y = vert2Pos[i * 6 + 1];
            outputVerts[i * 3 + 1] = v1Y + interpFactor * (v2Y - v1Y);

            float v1Z = vert1Pos[i * 6 + 2];
            float v2Z = vert2Pos[i * 6 + 2];
            outputVerts[i * 3 + 2] = v1Z + interpFactor * (v2Z - v1Z);
        }

        DCFlushRange(*memPtr, (unsigned long)(vertCount * 0xC));
    }

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

    state->value = 0.0f;
    state->velocity = 0.0f;
    state->accel = 0.0f;
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

    state->value = 0.0f;
    state->velocity = 0.0f;
    state->accel = 0.0f;
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
        _WaitDrawDone__8CGraphicFPci(Graphic, s_pppVtMime_cpp, 0x50);
        pppHeapUseRate__FPQ27CMemory6CStage(state->vertexBuffer);
        state->vertexBuffer = 0;
    }
}
