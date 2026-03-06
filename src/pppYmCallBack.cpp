#include "ffcc/pppYmCallBack.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"

#include <dolphin/mtx.h>

extern CGame Game;

/*
 * --INFO--
 * PAL Address: 0x800a6090
 * PAL Size: 4b
 */
void pppConstructYmCallBack(pppYmCallBack*, void*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 4b
 */
void pppDestructYmCallBack(pppYmCallBack*, void*)
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
void pppFrameYmCallBack(pppYmCallBack* callbackObj, pppYmCallBackUnkB* param_2, void*)
{
    pppYmCallBackUnkB* frameParam = param_2;
    pppYmCallBack* ymCallBack = callbackObj;
    unsigned char* mngSt;
    Vec position;
    s32 mngStIndex;

    if (((s32)ymCallBack->m_graphId / 0x1000) == (s32)frameParam->m_graphId) {
        mngSt = (unsigned char*)pppMngStPtr;
        position.x = *(f32*)(mngSt + 0x84);
        position.y = *(f32*)(mngSt + 0x94);
        position.z = *(f32*)(mngSt + 0xA4);
        PSMTXMultVec(ppvWorldMatrix, &position, &position);

        mngStIndex = ((s32)(mngSt - (reinterpret_cast<u8*>(&PartMng) + 0x2A18))) / 0x158;
        Game.ParticleFrameCallback(mngStIndex, (s32)*(s16*)(mngSt + 0x74),
                                   (s32)*(s16*)(mngSt + 0x76), (s32)frameParam->m_initWOrk,
                                   (s32)frameParam->m_graphId, &position);
    }
}


