#include "ffcc/pppPointRAp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/math.h"
#include <dolphin/types.h>

extern CMath Math;
extern int gPppCalcDisabled;
extern "C" float RandF__5CMathFv(CMath* instance);

struct pppPointRApStep {
    u32 m_unknown0;
    float m_radius;
    float m_speedScale;
    u32 m_createProgramIndex;
    u32 m_childPosOffset;
    u32 m_unused14;
    u32 m_childVelocityOffset;
    u8 m_cooldown;
};

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
    u32* ctrlData = (u32*)ctrlTable->m_serializedDef;
    u32 offset = ctrlData[1];
    u8* state = (u8*)pObject + offset;
    state[0x81] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060d20
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointRAp(_pppPObject* pObject, void* step, _pppCtrlTable* ctrlTable)
{
    pppPointRApStep* payload = (pppPointRApStep*)step;
    u32* ctrlData = (u32*)ctrlTable->m_serializedDef;
    u8* state = (u8*)pObject + ctrlData[1] + 0x80;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (state[1] == 0) {
        u32 createId = payload->m_createProgramIndex;
        Vec* srcPos = (Vec*)((u8*)pObject + ctrlData[0] + 0x80);

        if ((createId + 0x10000) == 0xFFFF) {
            return;
        }

        _pppPObject* obj;
        _pppPDataVal* objData = (_pppPDataVal*)((u8*)(*(u32*)((u8*)pppMngStPtr + 0xD4)) + (createId << 4));

        if (objData == 0) {
            obj = 0;
        } else {
            obj = (_pppPObject*)pppCreatePObject(pppMngStPtr, objData);
            *(_pppPObject**)((u8*)obj + 0x4) = pObject;
        }

        float* trig = gPppTrigTable;
        s32 angleA = (s32)(gPppPointRApRandomAngleRange * RandF__5CMathFv(&Math) - gPppPointRApRandomAngleBias);
        float scaleA = payload->m_radius;
        float yOff = scaleA * *(float*)((u8*)trig + ((angleA + 0x4000) & 0xFFFC));
        float planarOff = scaleA * *(float*)((u8*)trig + (angleA & 0xFFFC));
        float spinAngle = gPppPointRApRandomAngleRange * RandF__5CMathFv(&Math);
        s32 angleB = (s32)(spinAngle * gPppPointRApSpinScale);
        float xOff = planarOff * *(float*)((u8*)trig + (angleB & 0xFFFC));
        float zOff = planarOff * *(float*)((u8*)trig + ((angleB + 0x4000) & 0xFFFC));
        u32 childPosOffset = payload->m_childPosOffset;
        u32 childVelocityOffset = payload->m_childVelocityOffset;
        Vec* dstPos = (Vec*)((u8*)obj + childPosOffset + 0x80);
        Vec* dstVel = (Vec*)((u8*)obj + childVelocityOffset + 0x80);

        dstPos->x = srcPos->x + xOff;
        dstPos->y = srcPos->y + yOff;
        dstPos->z = srcPos->z + zOff;

        dstVel->x = xOff * payload->m_speedScale;
        dstVel->y = yOff * payload->m_speedScale;
        dstVel->z = zOff * payload->m_speedScale;

        state[1] = payload->m_cooldown;
    }

    state[1]--;
}
