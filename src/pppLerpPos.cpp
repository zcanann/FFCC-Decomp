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
    _pppMngSt* mng;
    s32 i;
    Vec avgPos;
    u32 count;

    if (ppvUserStopPartF == 0) {
        mng = ppvMng;
        historyPtr = GetLerpPosHistory(object, ctrl);
        if (*historyPtr == 0) {
            *historyPtr = (Vec*)pppMemAlloc(
                (u32)(u8)step->m_dataValIndex * sizeof(Vec), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppLerpPos_cpp),
                0x37);

            for (i = 0; i < (s32)(u8)step->m_dataValIndex; i++) {
                (*historyPtr)[i].x = ppvMng->m_matrix.value[0][3];
                (*historyPtr)[i].y = ppvMng->m_matrix.value[1][3];
                (*historyPtr)[i].z = ppvMng->m_matrix.value[2][3];
            }
        } else {
            avgPos.z = 0.0f;
            avgPos.y = 0.0f;
            avgPos.x = 0.0f;

            for (i = (u8)step->m_dataValIndex - 1; 0 < i; i--) {
                pppCopyVector((*historyPtr)[i], (*historyPtr)[i - 1]);
            }

            i = 0;
            (*historyPtr)[0].x = ppvMng->m_matrix.value[0][3];
            (*historyPtr)[0].y = ppvMng->m_matrix.value[1][3];
            (*historyPtr)[0].z = ppvMng->m_matrix.value[2][3];

            for (; count = (u32)(u8)step->m_dataValIndex, i < (s32)count; i++) {
                PSVECAdd(&(*historyPtr)[i], &avgPos, &avgPos);
            }

            PSVECScale(&avgPos, &avgPos, 1.0f / (f32)count);
            ppvMng->m_matrix.value[0][3] = avgPos.x;
            ppvMng->m_matrix.value[1][3] = avgPos.y;
            ppvMng->m_matrix.value[2][3] = avgPos.z;
            pppSetFpMatrix(mng);
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
    Vec** historyPtr = GetLerpPosHistory(object, ctrl);

    if (*historyPtr != 0) {
        pppMemFree(*historyPtr);
        *historyPtr = 0;
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
    Vec** historyPtr = GetLerpPosHistory(object, ctrl);
    *historyPtr = 0;
}
