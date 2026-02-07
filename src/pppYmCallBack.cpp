#include "ffcc/pppYmCallBack.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>

extern CPartMng PartMng;

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
    _pppMngSt* pppMngSt;
    _pppMngSt* mngStBase;
    YmCallBackObj* ymCallBack;
    YmCallBackParam* frameParam;
    Vec position;
    s32 mngStIndex;
    u32 graphId;

    ymCallBack = (YmCallBackObj*)pppYmCallBack;
    frameParam = (YmCallBackParam*)param_2;
    graphId = ymCallBack->m_graphId;
    pppMngSt = pppMngStPtr;

    if ((((s32)graphId >> 0xC) + (((s32)graphId < 0) && ((graphId & 0xFFF) != 0))) ==
        (s32)frameParam->m_graphId) {
        position.x = pppMngSt->m_matrix.value[0][3];
        position.y = pppMngSt->m_matrix.value[1][3];
        position.z = pppMngSt->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &position, &position);

        mngStBase = (_pppMngSt*)((u8*)&PartMng + 0x2A18);
        mngStIndex = ((s32)((u8*)pppMngSt - (u8*)mngStBase)) / 0x158;
        Game.game.ParticleFrameCallback(mngStIndex, (s32)pppMngSt->m_kind,
                                        (s32)pppMngSt->m_nodeIndex,
                                        (s32)frameParam->m_initWOrk, (s32)frameParam->m_graphId,
                                        &position);
    }
}
