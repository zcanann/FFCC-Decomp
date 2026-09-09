#include "ffcc/pppScreenQuake.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppYmEnv.h"

STATIC_ASSERT(sizeof(ScreenQuakeDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(ScreenQuakeDataOffsets, m_workOffset) == 0x0);

static inline ScreenQuakeDataOffsets* GetScreenQuakeDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<ScreenQuakeDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float* GetScreenQuakeWork(pppScreenQuake* quake, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<float*>(quake->m_workArea + GetScreenQuakeDataOffsets(ctrl)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x8013e3bc
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenQuake(pppScreenQuake*, pppScreenQuakeStep*, _pppCtrlTable*)
{
}

/*
 * --INFO--
 * PAL Address: 0x8013e3c0
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameScreenQuake(pppScreenQuake *quake, pppScreenQuakeStep *param2, _pppCtrlTable *param3)
{
    if (ppvUserStopPartF == 0) {
        float *value = GetScreenQuakeWork(quake, param3);

        CalcGraphValue(quake, param2->m_graphId, value[0], value[1], value[2], param2->m_dataValIndex, param2->m_initWOrk, param2->m_stepValue);
        CalcGraphValue(quake, param2->m_graphId, value[3], value[4], value[5], param2->m_arg3, param2->m_initWOrk2, param2->m_stepValue2);
        CalcGraphValue(quake, param2->m_graphId, value[6], value[7], value[8], param2->m_arg4, param2->m_initWOrk3, param2->m_stepValue3);

        CameraPcs.SetQuakeParameter(
            1,
            0,
            0,
            0,
            value[0],
            value[3],
            value[6],
            param2->m_quakeParam0,
            param2->m_quakeParam1,
            param2->m_quakeParam2,
            1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013e4b8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenQuake(pppScreenQuake*, _pppCtrlTable*)
{
    float val = 0.0f;

    CameraPcs.SetQuakeParameter(
        0,
        0,
        0,
        0,
        val,
        val,
        val,
        val,
        val,
        val,
        1);
}

/*
 * --INFO--
 * PAL Address: 0x8013e50c
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2)
{
    float val = 0.0f;
    float *data = GetScreenQuakeWork(quake, param2);

    data[2] = val;
    data[1] = val;
    data[0] = val;
    data[5] = val;
    data[4] = val;
    data[3] = val;
    data[8] = val;
    data[7] = val;
    data[6] = val;
}

/*
 * --INFO--
 * PAL Address: 0x8013e548
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenQuake(pppScreenQuake *quake, _pppCtrlTable *param2)
{
    float val = 0.0f;
    float *data = GetScreenQuakeWork(quake, param2);

    data[2] = val;
    data[1] = val;
    data[0] = val;
    data[5] = val;
    data[4] = val;
    data[3] = val;
    data[8] = val;
    data[7] = val;
    data[6] = val;
}
