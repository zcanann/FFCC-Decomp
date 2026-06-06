#include "ffcc/pppCharaZEnvCtrl.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
#include "dolphin/gx/GXPixel.h"

void CharaZEnvCtrl_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

STATIC_ASSERT(sizeof(CharaZEnvCtrlDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(CharaZEnvCtrlDataOffsets, m_workOffset) == 0x0);

static inline CharaZEnvCtrlDataOffsets* GetCharaZEnvCtrlDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<CharaZEnvCtrlDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x8013e584
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl* pppCharaZEnvCtrl, pppCharaZEnvCtrlStep* step, _pppCtrlTable* param_3)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	int dataOffset = GetCharaZEnvCtrlDataOffsets(param_3)->m_workOffset;
	void* work = pppCharaZEnvCtrl->m_workArea + dataOffset;
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
	CChara::CModel* model = GetCharaModelPtr(handle);
	model->SetCallbackContext(work, step);
	model->SetBeforeMeshLockEnvCallback(CharaZEnvCtrl_BeforeMeshLockEnvCallback);
}

/*
 * --INFO--
 * PAL Address: 0x8013e5f8
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*)
{
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
	CChara::CModel* model = GetCharaModelPtr(handle);
	model->SetCallbackContext(0, 0);
	model->SetBeforeMeshLockEnvCallback(0);
}

/*
 * --INFO--
 * PAL Address: 0x8013e638
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConCharaZEnvCtrl(_pppPObjLink*, _pppCtrlTable*)
{
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
	GetCharaModelPtr(handle);
}

/*
 * --INFO--
 * PAL Address: 0x8013e668
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CharaZEnvCtrl_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void* data, int)
{
    pppCharaZEnvCtrlStep* step = (pppCharaZEnvCtrlStep*)data;
    GXSetZMode((GXBool)step->m_zEnable, GX_LEQUAL, (GXBool)step->m_zWriteEnable);
}
