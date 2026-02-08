#include "ffcc/pppLerpPos.h"
#include "ffcc/memory.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

struct pppLerpPos {
    u8 m_pad[0x80];
};

struct UnkB {
    u8 m_pad[4];
    u8 m_dataValIndex;
};

struct UnkC {
    u8 m_pad[0x0C];
    s32* m_serializedDataOffsets;
};

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);
void pppCopyVector__FR3Vec3Vec(void* dst, void* src);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt* pppMngSt);
}
extern _pppEnvSt* pppEnvStPtr;
extern _pppMngSt* pppMngStPtr;
extern float FLOAT_80331bf8;
extern float FLOAT_80331bfc;
extern char s_pppLerpPos_cpp_801dd418[];
extern s32 DAT_8032ed70;

/*
 * --INFO--
 * PAL Address: 0x8012b490
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLerpPos(struct pppLerpPos* pppLerpPos, struct UnkC* param_2)
{
    s32 dataOffset = *param_2->m_serializedDataOffsets;
    Vec** work = (Vec**)((u8*)pppLerpPos + 0x80 + dataOffset);
    *work = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8012b43c
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructLerpPos(struct pppLerpPos* pppLerpPos, struct UnkC* param_2)
{
    s32 dataOffset = *param_2->m_serializedDataOffsets;
    void** work = (void**)((u8*)pppLerpPos + 0x80 + dataOffset);

    if (*work != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)*work);
        *work = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012b24c
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLerpPos(struct pppLerpPos* pppLerpPos, struct UnkB* param_2, struct UnkC* param_3)
{
    _pppMngSt* pppMngSt;
    s32 i;
    s32 dataOffset;
    s32 countMinusOne;
    s32 step;
    Vec* history;
    float* prevFloat;
    Vec sum;
    Vec prev;
    u32 count;

    if (DAT_8032ed70 != 0) {
        return;
    }

    pppMngSt = pppMngStPtr;
    dataOffset = *param_3->m_serializedDataOffsets;
    history = *(Vec**)((u8*)pppLerpPos + 0x80 + dataOffset);

    if (history == 0) {
        count = (u32)param_2->m_dataValIndex;
        history = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            count * (u32)sizeof(Vec), pppEnvStPtr->m_stagePtr, s_pppLerpPos_cpp_801dd418, 0x37);
        *(Vec**)((u8*)pppLerpPos + 0x80 + dataOffset) = history;
        step = 0;
        for (i = 0; i < (s32)count; i++) {
            *(f32*)((u8*)history + step) = pppMngStPtr->m_matrix.value[0][3];
            *(f32*)((u8*)history + step + 4) = pppMngStPtr->m_matrix.value[1][3];
            *(f32*)((u8*)history + step + 8) = pppMngStPtr->m_matrix.value[2][3];
            step += sizeof(Vec);
        }
    } else {
        sum.x = FLOAT_80331bf8;
        sum.y = FLOAT_80331bf8;
        sum.z = FLOAT_80331bf8;

        countMinusOne = (s32)param_2->m_dataValIndex - 1;
        step = countMinusOne * (s32)sizeof(Vec);
        while (0 < countMinusOne) {
            prevFloat = (float*)((u8*)history + step - (s32)sizeof(Vec));
            prev.x = prevFloat[0];
            prev.y = prevFloat[1];
            prev.z = prevFloat[2];
            pppCopyVector__FR3Vec3Vec((void*)((u8*)history + step), &prev);
            step -= sizeof(Vec);
            countMinusOne--;
        }

        history[0].x = pppMngStPtr->m_matrix.value[0][3];
        history[0].y = pppMngStPtr->m_matrix.value[1][3];
        history[0].z = pppMngStPtr->m_matrix.value[2][3];

        count = (u32)param_2->m_dataValIndex;
        step = 0;
        for (i = 0; i < (s32)count; i++) {
            PSVECAdd((Vec*)((u8*)history + step), &sum, &sum);
            step += sizeof(Vec);
        }

        PSVECScale(&sum, &sum, FLOAT_80331bfc / (f32)count);
        pppMngStPtr->m_matrix.value[0][3] = sum.x;
        pppMngStPtr->m_matrix.value[1][3] = sum.y;
        pppMngStPtr->m_matrix.value[2][3] = sum.z;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
}
