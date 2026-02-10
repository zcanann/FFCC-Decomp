#include "ffcc/pppYmTracer2.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"

#include <dolphin/mtx.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(float, _pppMngSt*, Mtx);

extern int DAT_8032ed70;
extern int DAT_801eadc8;
extern float FLOAT_80331840;
extern float FLOAT_80331860;
extern double DOUBLE_80331858;

static char s_pppYmTracer2_cpp_801dc4b8[] = "pppYmTracer2.cpp";

struct YmTracer2Step {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

struct TraceEntry {
    Vec pos;
    float pad0;
    Vec targetPos;
    float pad1;
    u8 flags[8];
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void initTracePolygon(PYmTracer2*, TRACE_POLYGON&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80103e68
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	float fVar1 = 1.0f; // FLOAT_80331840 placeholder
	unsigned char* puVar2 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(u32*)(puVar2 + 0x28) = 0;
	*(u32*)(puVar2 + 0x24) = 0;
	*(u32*)(puVar2 + 0x20) = 0;
	*(u16*)(puVar2 + 0x2c) = 0;
	
	*(float*)(puVar2 + 0xc) = fVar1;
	*(float*)(puVar2 + 8) = fVar1;
	*(float*)(puVar2 + 4) = fVar1;
	*(float*)puVar2 = fVar1;
	*(float*)(puVar2 + 0x1c) = fVar1;
	*(float*)(puVar2 + 0x18) = fVar1;
	*(float*)(puVar2 + 0x14) = fVar1;
	*(float*)(puVar2 + 0x10) = fVar1;
	
	*(u16*)(puVar2 + 0x2e) = 0;
	*(u16*)(puVar2 + 0x30) = 0;
	*(u16*)(puVar2 + 0x32) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103e44
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	unsigned char* iVar1 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(short*)(iVar1 + 0x2c) = 0;
	*(short*)(iVar1 + 0x2e) = 0;
	*(short*)(iVar1 + 0x32) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103e0c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	void** memPtr = (void**)((unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets + 0x28);
	if (*memPtr != 0) {
		pppHeapUseRate((CMemory::CStage*)*memPtr);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801039b4
 * PAL Size: 1112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTracer2(pppYmTracer2* pppYmTracer2, UnkB* param_2, UnkC* param_3)
{
    YmTracer2Step* step = (YmTracer2Step*)param_2;
    u8* work;
    s32 colorOffset;
    bool useFallback;
    TraceEntry* entries;

    if (DAT_8032ed70 != 0) {
        return;
    }

    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (u8*)pppYmTracer2 + 0x80 + *param_3->m_serializedDataOffsets;

    if (step->m_initWOrk == -1) {
        *(void**)(work + 0x20) = &DAT_801eadc8;
    } else {
        *(void**)(work + 0x20) = (void*)((u8*)pppMngStPtr + step->m_stepValue);
    }

    if (step->m_arg3 == -1) {
        *(void**)(work + 0x24) = &DAT_801eadc8;
    } else {
        *(void**)(work + 0x24) = (void*)((u8*)pppMngStPtr + *(s32*)step->m_payload);
    }

    useFallback = false;
    if (*(void**)(work + 0x28) == NULL) {
        u16 maxCount = *(u16*)(step->m_payload + 4);
        TraceEntry* it;

        useFallback = true;
        *(u16*)(work + 0x30) = (u16)((u32)step->m_payload[8] / *(u16*)(step->m_payload + 6));
        *(void**)(work + 0x28) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((u32)maxCount * sizeof(TraceEntry), pppEnvStPtr->m_stagePtr,
                                                  s_pppYmTracer2_cpp_801dc4b8, 0xAD);

        it = (TraceEntry*)(*(void**)(work + 0x28));
        for (s32 i = 0; i < (s32)maxCount; i++) {
            it->flags[0] = 0;
            it->flags[7] = 0;
            it->pos.x = FLOAT_80331840;
            it->pos.y = FLOAT_80331840;
            it->pos.z = FLOAT_80331840;
            it->targetPos.x = FLOAT_80331840;
            it->targetPos.y = FLOAT_80331840;
            it->targetPos.z = FLOAT_80331840;
            it++;
        }
    }

    entries = (TraceEntry*)(*(void**)(work + 0x28));
    entries[0].flags[0] = 1;

    for (u32 i = 0; i < (u32)(step->m_payload[9] + 1); i++) {
        s32 last = *(u16*)(step->m_payload + 4) - 2;

        while ((s32)i <= last) {
            entries[last + 1].flags[0] = entries[last].flags[0];
            pppCopyVector(entries[last + 1].pos, entries[last].pos);
            pppCopyVector(entries[last + 1].targetPos, entries[last].targetPos);
            entries[last + 1].flags[1] = entries[last].flags[1];
            entries[last + 1].flags[5] = entries[last].flags[5];
            entries[last + 1].flags[6] = entries[last].flags[6];
            entries[last + 1].flags[7] = entries[last].flags[7];
            last--;
        }

        {
            float* srcA = *(float**)(work + 0x20);
            float* srcB = *(float**)(work + 0x24);
            TraceEntry* entry = &entries[i];

            *(float*)(work + 0x0) = srcA[0];
            *(float*)(work + 0x4) = srcA[1];
            *(float*)(work + 0x8) = srcA[2];
            entry->pos.x = srcA[0];
            entry->pos.y = srcA[1];
            entry->pos.z = srcA[2];

            *(float*)(work + 0x10) = srcB[0];
            *(float*)(work + 0x14) = srcB[1];
            *(float*)(work + 0x18) = srcB[2];
            entry->targetPos.x = srcB[0];
            entry->targetPos.y = srcB[1];
            entry->targetPos.z = srcB[2];

            entry->flags[1] = ((u8*)pppYmTracer2)[colorOffset + 0x88];
            entry->flags[2] = ((u8*)pppYmTracer2)[colorOffset + 0x89];
            entry->flags[3] = ((u8*)pppYmTracer2)[colorOffset + 0x8A];
        }

        if (i == 0) {
            Mtx tmpMtx;
            PSMTXConcat(pppMngStPtr->m_matrix.value, *(Mtx*)((u8*)pppYmTracer2 + 4), tmpMtx);
            PSMTXMultVec(tmpMtx, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(tmpMtx, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            Mtx tmpMtx;
            u32 numer = i ^ 0x80000000;
            u32 denom = (u32)(step->m_payload[9] + 1) ^ 0x80000000;
            float t = (FLOAT_80331860 / (float)((double)((u64)0x4330000000000000ULL | denom) - DOUBLE_80331858)) *
                      (float)((double)((u64)0x4330000000000000ULL | numer) - DOUBLE_80331858);

            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(t, pppMngStPtr, tmpMtx) == 0) {
                useFallback = true;
            } else {
                PSMTXConcat(tmpMtx, *(Mtx*)((u8*)pppYmTracer2 + 4), tmpMtx);
                PSMTXMultVec(tmpMtx, &entries[i].pos, &entries[i].pos);
                PSMTXMultVec(tmpMtx, &entries[i].targetPos, &entries[i].targetPos);
            }
        }
    }

    if (useFallback) {
        for (s32 i = 0; i < (s32)*(u16*)(step->m_payload + 4); i++) {
            pppCopyVector(entries[i].pos, entries[0].pos);
            pppCopyVector(entries[i].targetPos, entries[0].targetPos);
        }
    }

    {
        s16 visibleCount = 0;
        u16 maxCount = *(u16*)(step->m_payload + 4);
        s16 stepAlpha = *(u16*)(work + 0x30);

        for (s32 i = 0; i < (s32)maxCount; i++) {
            s16 alpha = (s16)step->m_payload[8] - (s16)i * stepAlpha;
            if (alpha < 0 || entries[i].flags[0] == 0) {
                entries[i].flags[7] = 0;
            } else {
                entries[i].flags[7] = (u8)alpha;
                visibleCount++;
            }
        }

        *(s16*)(work + 0x2C) = visibleCount;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmTracer2(pppYmTracer2*, UnkB*, UnkC*)
{
	// TODO
}
