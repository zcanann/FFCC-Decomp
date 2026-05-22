#include "ffcc/pppCharaZEnvCtrl.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
#include "dolphin/gx/GXPixel.h"

/*
 * --INFO--
 * PAL Address: 0x8013e584
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl* pppCharaZEnvCtrl, pppCharaZEnvCtrlUnkB* param_2, _pppCtrlTable* param_3)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	int dataOffset = *param_3->m_serializedDataOffsets;
	void* work = (void*)((char*)pppCharaZEnvCtrl + dataOffset + 0x80);
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(pppMngStPtr->m_owner), 0);
	int model = reinterpret_cast<int>(GetCharaModelPtr(handle));
	*(void**)(model + 0xe4) = work;
	*(pppCharaZEnvCtrlUnkB**)(model + 0xe8) = param_2;
	*(void (**)(CChara::CModel*, void*, void*, int))(model + 0xf4) = CharaZEnvCtrl_BeforeMeshLockEnvCallback;
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
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(pppMngStPtr->m_owner), 0);
	int model = reinterpret_cast<int>(GetCharaModelPtr(handle));
	*(void**)(model + 0xe4) = 0;
	*(void**)(model + 0xe8) = 0;
	*(void**)(model + 0xf4) = 0;
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
	CCharaPcs::CHandle* handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(pppMngStPtr->m_owner), 0);
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
    unsigned char* zModeState = (unsigned char*)data;
    GXSetZMode((GXBool)zModeState[4], GX_LEQUAL, (GXBool)zModeState[5]);
}
