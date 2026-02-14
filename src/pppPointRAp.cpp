#include "ffcc/pppPointRAp.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include <dolphin/types.h>

extern CMath math[];
extern int lbl_8032ED70;
extern unsigned char* lbl_8032ED50;
extern float lbl_801EC9F0[];
extern float lbl_8032FEE8;
extern float lbl_8032FEEC;
extern float lbl_8032FEF0;
extern "C" float RandF__5CMathFv(CMath* instance);

extern _pppPObject* pppCreatePObject(_pppMngSt*, _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x80060ee4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointRApCon(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    u32* ctrlData = *(u32**)((u8*)dataVal + 0xC);
    u32 offset = ctrlData[1];
    u8* state = (u8*)mngSt + offset;
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
void pppPointRAp(void* mngSt, void* dataVal, void* ctrlTable)
{
    u32* ctrlData = *(u32**)((u8*)ctrlTable + 0xC);
    u8* state = (u8*)mngSt + ctrlData[1] + 0x80;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (state[1] == 0) {
        u32 createId = *(u32*)((u8*)dataVal + 0xC);
        Vec* srcPos = (Vec*)((u8*)mngSt + ctrlData[0] + 0x80);

        if ((createId + 0x10000) == 0xFFFF) {
            return;
        }

        _pppPObject* obj;
        _pppPDataVal* objData = (_pppPDataVal*)((u8*)(*(u32*)(lbl_8032ED50 + 0xD4)) + (createId << 4));

        if (objData == 0) {
            obj = 0;
        } else {
            obj = (_pppPObject*)pppCreatePObject((_pppMngSt*)lbl_8032ED50, objData);
            *(void**)((u8*)obj + 0x4) = mngSt;
        }

        float* trig = lbl_801EC9F0;
        s32 angleA = (s32)(lbl_8032FEE8 * RandF__5CMathFv(math) - lbl_8032FEEC);
        float scaleA = *(float*)((u8*)dataVal + 0x4);
        float yOff = scaleA * *(float*)((u8*)trig + (angleA & 0xFFFC));
        float zOff = scaleA * *(float*)((u8*)trig + ((angleA + 0x4000) & 0xFFFC));
        s32 angleB = (s32)(lbl_8032FEF0 * (lbl_8032FEE8 * RandF__5CMathFv(math)));
        Vec* dstPos = (Vec*)((u8*)obj + *(u32*)((u8*)dataVal + 0x10) + 0x80);
        Vec* dstVel = (Vec*)((u8*)obj + *(u32*)((u8*)dataVal + 0x18) + 0x80);
        float xOff = zOff * *(float*)((u8*)trig + (angleB & 0xFFFC));
        zOff *= *(float*)((u8*)trig + ((angleB + 0x4000) & 0xFFFC));

        dstPos->x = srcPos->x + xOff;
        dstPos->y = srcPos->y + yOff;
        dstPos->z = srcPos->z + zOff;

        {
            float velocityScale = *(float*)((u8*)dataVal + 0x8);
            dstVel->x = xOff * velocityScale;
            dstVel->y = yOff * velocityScale;
            dstVel->z = zOff * velocityScale;
        }

        state[1] = *(u8*)((u8*)dataVal + 0x1C);
    }

    state[1]--;
}
