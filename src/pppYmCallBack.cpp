#include "ffcc/pppYmCallBack.h"
#include "ffcc/game.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>

extern "C" {
void ParticleFrameCallback__5CGameFiiiiiP3Vec(CGame*, int, int, int, int, int, Vec*);
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
    _pppMngSt* mngSt;
    Vec position;
    s32 mngStIndex;

    if (((s32)callbackObj->m_graphId / 0x1000) == (s32)param_2->m_graphId) {
        mngSt = pppMngStPtr;
        position.x = mngSt->m_matrix.value[0][3];
        position.y = mngSt->m_matrix.value[1][3];
        position.z = mngSt->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &position, &position);

        mngStIndex = ((s32)((u8*)mngSt - (reinterpret_cast<u8*>(&PartMng) + 0x2A18))) / 0x158;
        ParticleFrameCallback__5CGameFiiiiiP3Vec(
            &Game, mngStIndex, (s32)mngSt->m_kind, (s32)mngSt->m_nodeIndex, (s32)param_2->m_initWOrk,
            (s32)param_2->m_graphId, &position);
    }
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
 * PAL Address: 0x800a6090
 * PAL Size: 4b
 */
void pppConstructYmCallBack(pppYmCallBack*, void*)
{
	return;
}
