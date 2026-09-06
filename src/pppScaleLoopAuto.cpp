#include "global.h"
#include "ffcc/pppScaleLoopAuto.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppsintbl.h"
#include <dolphin/types.h>
#include "ffcc/ppp_linkage.h"

struct pppScaleLoopAutoWork {
    float m_scale[3];
    u8 _pad0x0c[4];
    float m_baseScale[3];
    u8 m_initialized;
    u8 m_step;
    s16 m_angle;
    s8 m_countA;
    s8 m_countB;
    u8 _pad0x22[2];
    float m_delta;
};

STATIC_ASSERT(sizeof(pppScaleLoopAutoDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(pppScaleLoopAutoDataOffsets, m_workOffset) == 0x0);

static inline pppScaleLoopAutoDataOffsets* GetScaleLoopAutoDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppScaleLoopAutoDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline pppScaleLoopAutoWork* GetScaleLoopAutoWork(_pppPObject* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppScaleLoopAutoWork*>(object->m_workArea + GetScaleLoopAutoDataOffsets(ctrl)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x8012b4a8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAutoCon(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	float zero = 0.0f;

	pppScaleLoopAutoWork* work = GetScaleLoopAutoWork(object, ctrlTable);

	work->m_scale[2] = zero;
	work->m_scale[1] = zero;
	work->m_scale[0] = zero;
	work->m_baseScale[2] = zero;
	work->m_baseScale[1] = zero;
	work->m_baseScale[0] = zero;
	work->m_initialized = 0;
	work->m_step = 0;
	work->m_angle = 0;
	work->m_countB = 0;
	work->m_countA = 0;
	work->m_delta = zero;
}

/*
 * --INFO--
 * PAL Address: 0x8012b4f4
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAuto(_pppPObject* arg1, pppScaleLoopAutoStep* arg2, _pppCtrlTable* arg3){
    if (ppvUserStopPartF != 0) {
        return;
    }

    pppScaleLoopAutoWork* work = GetScaleLoopAutoWork(arg1, arg3);

    if (arg2->m_index == arg1->m_graphId) {
        work->m_scale[0] += arg2->m_addScale[0];
        work->m_scale[1] += arg2->m_addScale[1];
        work->m_scale[2] += arg2->m_addScale[2];
    }

    if (work->m_initialized == 0) {
        work->m_initialized = 1;
        work->m_baseScale[0] = work->m_scale[0];
        work->m_baseScale[1] = work->m_scale[1];
        work->m_baseScale[2] = work->m_scale[2];
        work->m_countA = arg2->m_countA;
        work->m_countB = arg2->m_countB;
        return;
    }

    if (work->m_angle >= 90) {
        if (work->m_countA > 0) {
            work->m_countA--;
            work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
            work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
            work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
            return;
        }
    }

    if (work->m_angle >= 270) {
        if (work->m_countB > 0) {
            work->m_countB--;
            work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
            work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
            work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
            return;
        }
    }

    work->m_step++;
    if (work->m_step > arg2->m_stepCount) {
        work->m_step = 0;
        work->m_angle = 0;
        work->m_countA = arg2->m_countA;
        work->m_countB = arg2->m_countB;
        return;
    }

    work->m_angle += 360 / (s32)arg2->m_stepCount;

    {
        s32 tableAngle = (s32)(((f32)((s32)work->m_angle << 15)) / 180.0f);
        f32 sinVal = pppSinFromTable(tableAngle);
        f32 delta = (arg2->m_amplitude * sinVal) * arg2->m_scale;

        work->m_delta = delta;
        work->m_scale[0] = work->m_baseScale[0] + delta;
        work->m_scale[1] = work->m_baseScale[1] + delta;
        work->m_scale[2] = work->m_baseScale[2] + delta;
    }
}
