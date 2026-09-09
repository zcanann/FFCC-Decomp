#include "ffcc/pppLerpPos.h"
#include "ffcc/memory.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/linkage.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include <stddef.h>

STATIC_ASSERT(offsetof(pppLerpPosStep, m_dataValIndex) == 0x4);

STATIC_ASSERT(sizeof(LerpPosDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(LerpPosDataOffsets, m_historyOffset) == 0x0);

static inline LerpPosDataOffsets* GetLerpPosDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<LerpPosDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline Vec** GetLerpPosHistory(_pppPObject* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<Vec**>(object->m_workArea + GetLerpPosDataOffsets(ctrl)->m_historyOffset);
}

static const char s_pppLerpPos_cpp[] = "pppLerpPos.cpp";

/*
 * --INFO--
 * PAL Address: 0x8012b24c
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLerpPos(_pppPObject* object, pppLerpPosStep* step, _pppCtrlTable* ctrl)
{
    Vec** historyPtr;
    _pppMngSt* pppMngSt;
    s32 iVar5;
    s32 iVar7;
    Vec local_2c;
    u32 count;

    if (ppvUserStopPartF == 0) {
        pppMngSt = ppvMng;
        historyPtr = GetLerpPosHistory(object, ctrl);
        if (*historyPtr == 0) {
            *historyPtr = (Vec*)pppMemAlloc(
                (u32)(u8)step->m_dataValIndex * 0xc, ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppLerpPos_cpp),
                0x37);

            for (iVar7 = 0; iVar7 < (s32)(u8)step->m_dataValIndex; iVar7 = iVar7 + 1) {
                (*historyPtr)[iVar7].x = ppvMng->m_matrix.value[0][3];
                (*historyPtr)[iVar7].y = ppvMng->m_matrix.value[1][3];
                (*historyPtr)[iVar7].z = ppvMng->m_matrix.value[2][3];
            }
        } else {
            local_2c.z = 0.0f;
            local_2c.y = 0.0f;
            local_2c.x = 0.0f;

            iVar5 = (u8)step->m_dataValIndex - 1;
            iVar7 = iVar5 * 0xc;
            while (0 < iVar5) {
                pppCopyVector(*(Vec*)((u8*)*historyPtr + iVar7), *(Vec*)((u8*)*historyPtr + iVar7 - 0xc));
                iVar7 = iVar7 - 0xc;
                iVar5 = iVar5 - 1;
            }

            iVar5 = 0;
            iVar7 = iVar5;
            (*historyPtr)->x = ppvMng->m_matrix.value[0][3];
            *(f32*)((u8*)*historyPtr + 4) = ppvMng->m_matrix.value[1][3];
            *(f32*)((u8*)*historyPtr + 8) = ppvMng->m_matrix.value[2][3];

            for (; count = (u32)(u8)step->m_dataValIndex, iVar5 < (s32)count; iVar5 = iVar5 + 1) {
                PSVECAdd((Vec*)((u8*)*historyPtr + iVar7), &local_2c, &local_2c);
                iVar7 = iVar7 + 0xc;
            }

            PSVECScale(&local_2c, &local_2c, 1.0f / (f32)count);
            ppvMng->m_matrix.value[0][3] = local_2c.x;
            ppvMng->m_matrix.value[1][3] = local_2c.y;
            ppvMng->m_matrix.value[2][3] = local_2c.z;
            pppSetFpMatrix(pppMngSt);
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
void pppDestructLerpPos(_pppPObject* object, _pppCtrlTable* ctrl)
{
    void** work = (void**)GetLerpPosHistory(object, ctrl);

    if (*work != 0) {
        pppMemFree(*work);
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
void pppConstructLerpPos(_pppPObject* object, _pppCtrlTable* ctrl)
{
    Vec** work = GetLerpPosHistory(object, ctrl);
    *work = 0;
}
