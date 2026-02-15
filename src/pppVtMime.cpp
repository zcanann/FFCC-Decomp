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
    unsigned int maskedIdx;

    maskedIdx = (unsigned int)vertIdx1;
    maskedIdx &= 0xFFFF0000;
    if (maskedIdx + 0x00010000 == 0) {
        return;
    }
    maskedIdx = (unsigned int)vertIdx2;
    maskedIdx &= 0xFFFF0000;
    if (maskedIdx + 0x00010000 == 0) {
        return;
    }

    void* dataBase = *(void**)*(void**)((char*)param3 + 0xC);
    char* target = (char*)param1 + (int)dataBase + 0x80;
    void* globalData = *(void**)((char*)lbl_8032ED54 + 0x8);
    VtMimeSource* vert1Data = *(VtMimeSource**)((char*)globalData + (vertIdx1 * 4));
    VtMimeSource* vert2Data = *(VtMimeSource**)((char*)globalData + (vertIdx2 * 4));
    float* vert1Pos = vert1Data->positions;
    float* vert2Pos = vert2Data->positions;
    short vertCount = vert1Data->vertexCount;
    void** memPtr = (void**)(target + 0xC);

    if (*memPtr == 0) {
        *memPtr = pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(vertCount * 0xC), *(void**)lbl_8032ED54, lbl_801D8520, 0x2B);
    }

    if (vertCount > 0) {
        float* outputVerts = (float*)*memPtr;
        float interpFactor = *(float*)target;
        float* src1 = vert1Pos;
        float* src2 = vert2Pos;
        int i;

        for (i = 0; i < vertCount; i++) {
            float v1X = src1[0];
            float v2X = src2[0];
            outputVerts[i * 3 + 0] = v1X + interpFactor * (v2X - v1X);

            float v1Y = src1[1];
            float v2Y = src2[1];
            outputVerts[i * 3 + 1] = v1Y + interpFactor * (v2Y - v1Y);

            float v1Z = src1[2];
            float v2Z = src2[2];
            outputVerts[i * 3 + 2] = v1Z + interpFactor * (v2Z - v1Z);

            src1 += 6;
            src2 += 6;
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

    state->accel = 0.0f;
    state->velocity = 0.0f;
    state->value = 0.0f;
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

    state->accel = 0.0f;
    state->velocity = 0.0f;
    state->value = 0.0f;
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
