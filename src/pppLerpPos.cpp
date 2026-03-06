#include "ffcc/pppLerpPos.h"
#include "ffcc/memory.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

struct pppLerpPos {
    u8 m_pad[0x80];
};

struct pppLerpPosUnkB {
    u8 m_pad[4];
    u8 m_dataValIndex;
};

struct pppLerpPosUnkC {
    u8 m_pad[0x0C];
    s32* m_serializedDataOffsets;
};

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);
void pppCopyVector__FR3Vec3Vec(void* dst, void* src);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt* pppMngSt);
}
extern _pppEnvSt* lbl_8032ED54;
extern _pppMngSt* lbl_8032ED50;
extern float FLOAT_80331bf8;
extern float FLOAT_80331bfc;
extern char s_pppLerpPos_cpp_801dd418[];
extern int gPppCalcDisabled;

/*
 * --INFO--
 * PAL Address: 0x8012b24c
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkB* param_2, struct pppLerpPosUnkC* param_3)
{
    _pppMngSt* pppMngSt = lbl_8032ED50;
    s32 iVar1;
    s32 iVar2;
    s32 iVar4;
    s32 iVar5;
    f32* pfVar6;
    s32 iVar7;
    Vec local_2c;
    Vec local_38;
    u32 count;
    Vec** historyPtr;

    if (gPppCalcDisabled == 0) {
        iVar2 = *param_3->m_serializedDataOffsets;
        historyPtr = (Vec**)((u8*)pppLerpPos + 0x80 + iVar2);
        if (*historyPtr == 0) {
            *historyPtr = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (u32)(u8)param_2->m_dataValIndex * 0xc, lbl_8032ED54->m_stagePtr, s_pppLerpPos_cpp_801dd418,
                0x37);
            iVar5 = 0;
            for (iVar7 = 0; iVar7 < (s32)(u8)param_2->m_dataValIndex; iVar7 = iVar7 + 1) {
                iVar4 = iVar5 + 4;
                iVar1 = iVar5 + 8;
                *(f32*)((u8*)*historyPtr + iVar5) = lbl_8032ED50->m_matrix.value[0][3];
                iVar5 = iVar5 + 0xc;
                *(f32*)((u8*)*historyPtr + iVar4) = lbl_8032ED50->m_matrix.value[1][3];
                *(f32*)((u8*)*historyPtr + iVar1) = lbl_8032ED50->m_matrix.value[2][3];
            }
        } else {
            local_2c.z = FLOAT_80331bf8;
            local_2c.y = FLOAT_80331bf8;
            local_2c.x = FLOAT_80331bf8;

            iVar5 = (u8)param_2->m_dataValIndex - 1;
            iVar7 = iVar5 * 0xc;
            for (; 0 < iVar5; iVar5 = iVar5 - 1) {
                pfVar6 = (f32*)((u8*)*historyPtr + iVar7 - 0xc);
                local_38.x = pfVar6[0];
                local_38.y = pfVar6[1];
                local_38.z = pfVar6[2];
                pppCopyVector__FR3Vec3Vec((void*)((u8*)*historyPtr + iVar7), &local_38);
                iVar7 = iVar7 - 0xc;
            }

            (*historyPtr)->x = lbl_8032ED50->m_matrix.value[0][3];
            *(f32*)((u8*)*historyPtr + 4) = lbl_8032ED50->m_matrix.value[1][3];
            *(f32*)((u8*)*historyPtr + 8) = lbl_8032ED50->m_matrix.value[2][3];

            iVar7 = 0;
            for (iVar5 = 0; count = (u32)(u8)param_2->m_dataValIndex, iVar5 < (s32)count; iVar5 = iVar5 + 1) {
                PSVECAdd((Vec*)((u8*)*historyPtr + iVar7), &local_2c, &local_2c);
                iVar7 = iVar7 + 0xc;
            }

            PSVECScale(&local_2c, &local_2c, FLOAT_80331bfc / (f32)count);
            lbl_8032ED50->m_matrix.value[0][3] = local_2c.x;
            lbl_8032ED50->m_matrix.value[1][3] = local_2c.y;
            lbl_8032ED50->m_matrix.value[2][3] = local_2c.z;
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
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
void pppDestructLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkC* param_2)
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
 * PAL Address: 0x8012b490
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkC* param_2)
{
    s32 dataOffset = *param_2->m_serializedDataOffsets;
    Vec** work = (Vec**)((u8*)pppLerpPos + 0x80 + dataOffset);
    *work = 0;
}
