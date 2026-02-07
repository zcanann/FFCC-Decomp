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

static f32 GetMngStPosX(const _pppMngSt* mngSt)
{
    return *(const f32*)((const u8*)mngSt + 0x84);
}

static f32 GetMngStPosY(const _pppMngSt* mngSt)
{
    return *(const f32*)((const u8*)mngSt + 0x94);
}

static f32 GetMngStPosZ(const _pppMngSt* mngSt)
{
    return *(const f32*)((const u8*)mngSt + 0xA4);
}

static s16 GetMngStKind(const _pppMngSt* mngSt)
{
    return *(const s16*)((const u8*)mngSt + 0x74);
}

static s16 GetMngStNodeIndex(const _pppMngSt* mngSt)
{
    return *(const s16*)((const u8*)mngSt + 0x76);
}

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
    YmCallBackObj* ymCallBack;
    YmCallBackParam* frameParam;
    Vec position;
    s32 mngStIndex;

    pppMngSt = pppMngStPtr;
    ymCallBack = (YmCallBackObj*)pppYmCallBack;
    frameParam = (YmCallBackParam*)param_2;

    if (((s32)ymCallBack->m_graphId / 0x1000) == (s32)frameParam->m_graphId) {
        _pppMngSt* mngStBase;

        position.x = GetMngStPosX(pppMngSt);
        position.y = GetMngStPosY(pppMngSt);
        position.z = GetMngStPosZ(pppMngSt);
        PSMTXMultVec(ppvWorldMatrix, &position, &position);

        mngStBase = (_pppMngSt*)((u8*)&PartMng + 0x2A18);
        mngStIndex = pppMngSt - mngStBase;
        Game.game.ParticleFrameCallback(mngStIndex, (s32)GetMngStKind(pppMngSt),
                                        (s32)GetMngStNodeIndex(pppMngSt),
                                        (s32)frameParam->m_initWOrk, (s32)frameParam->m_graphId,
                                        &position);
    }
}
