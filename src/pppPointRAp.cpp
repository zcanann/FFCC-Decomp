#include "ffcc/pppPointRAp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppsintbl.h"
#include "ffcc/math.h"
#include <dolphin/types.h>

extern "C" const float gPppPointRApRandomAngleRange = 32768.0f;
extern "C" const float gPppPointRApRandomAngleBias = 16384.0f;
extern "C" const float gPppPointRApSpinScale = 2.0f;

struct pppPointRApOffsets {
    u32 m_srcOffset;
    u32 m_stateOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80060d20
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointRAp(_pppPObject* pObject, pppPointRApStep* step, _pppCtrlTable* ctrlTable)
{
    pppPointRApOffsets* ctrlData = (pppPointRApOffsets*)ctrlTable->m_serializedDataOffsets;
    u8* state = pObject->m_workArea + ctrlData->m_stateOffset;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (state[1] == 0) {
        u32 createId = step->m_createProgramIndex;
        Vec* srcPos = (Vec*)(pObject->m_workArea + ctrlData->m_srcOffset);

        if ((createId + 0x10000) == 0xFFFF) {
            return;
        }

        _pppPObject* obj;
        _pppPDataVal* objData = ppvMng->m_pppPDataVals + createId;

        if (objData == 0) {
            obj = 0;
        } else {
            obj = (_pppPObject*)pppCreatePObject(ppvMng, objData);
            obj->m_link.m_previous = &pObject->m_link;
        }

        s32 angleA = (s32)(gPppPointRApRandomAngleRange * Math.RandF() - gPppPointRApRandomAngleBias);
        float scaleA = step->m_radius;
        float yOff;
        float planarOff = scaleA * pppCosFromTable(angleA);
        yOff = scaleA * pppSinFromTable(angleA);
        float spinRand = Math.RandF();
        float spinAngle = gPppPointRApRandomAngleRange * spinRand;
        s32 angleB = (s32)(gPppPointRApSpinScale * spinAngle);
        u32 childPosOffset = step->m_childPosOffset;
        u32 childVelocityOffset = step->m_childVelocityOffset;
        float xOff = planarOff * pppSinFromTable(angleB);
        planarOff *= pppCosFromTable(angleB);
        Vec* dstPos = (Vec*)(obj->m_workArea + childPosOffset);
        Vec* dstVel = (Vec*)(obj->m_workArea + childVelocityOffset);

        dstPos->x = srcPos->x + xOff;
        dstPos->y = srcPos->y + yOff;
        dstPos->z = srcPos->z + planarOff;

        dstVel->x = xOff * step->m_speedScale;
        dstVel->y = yOff * step->m_speedScale;
        dstVel->z = planarOff * step->m_speedScale;

        state[1] = step->m_cooldown;
    }

    state[1]--;
}

/*
 * --INFO--
 * PAL Address: 0x80060ee4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointRApCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
    pppPointRApOffsets* ctrlData = (pppPointRApOffsets*)ctrlTable->m_serializedDataOffsets;
    u8* state = pObject->m_workArea + ctrlData->m_stateOffset;
    state[1] = 0;
}
