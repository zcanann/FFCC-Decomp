#include "ffcc/pppYmCallBack.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>

extern CPartMng PartMng;
extern unsigned char* lbl_8032ED50;

struct YmCallBackObj {
    u8 m_pad0[0xc];
    u32 m_graphId;
};

struct YmCallBackParam {
    u32 m_unk0;
    s16 m_graphId;
    s16 m_initWOrk;
};

/*
 * --INFO--
 * PAL Address: 0x800a6090
 * PAL Size: 4b
 */
void pppConstructYmCallBack(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 4b
 */
void pppDestructYmCallBack(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800A5FCC
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmCallBack(void* pppYmCallBack, void* param_2)
{
    YmCallBackObj* ymCallBack;
    YmCallBackParam* frameParam;
    unsigned char* mngSt;
    Vec position;
    s32 mngStIndex;
    u32 graphId;

    ymCallBack = (YmCallBackObj*)pppYmCallBack;
    frameParam = (YmCallBackParam*)param_2;
    graphId = ymCallBack->m_graphId;
    mngSt = lbl_8032ED50;

    if (((s32)graphId / 0x1000) == (s32)frameParam->m_graphId) {
        position.x = *(f32*)(mngSt + 0x84);
        position.y = *(f32*)(mngSt + 0x94);
        position.z = *(f32*)(mngSt + 0xA4);
        PSMTXMultVec(ppvWorldMatrix, &position, &position);

        mngStIndex = ((s32)(mngSt - ((u8*)&PartMng + 0x2A18))) / 0x158;
        Game.game.ParticleFrameCallback(mngStIndex, (s32)*(s16*)(mngSt + 0x74),
                                        (s32)*(s16*)(mngSt + 0x76),
                                        (s32)frameParam->m_initWOrk, (s32)frameParam->m_graphId,
                                        &position);
    }
}
