#include "ffcc/pppCharaZEnvCtrl.h"
#include "ffcc/partMng.h"
#include "dolphin/gx/GXPixel.h"

extern int DAT_8032ed70;

struct UnkC {
    unsigned char pad0[0xC];
    int* m_serializedDataOffsets;
};

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
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
void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl* pppCharaZEnvCtrl, UnkB* param_2, UnkC* param_3)
{
	if (DAT_8032ed70 != 0) {
		return;
	}

	int dataOffset = *param_3->m_serializedDataOffsets;
	void* work = (void*)((char*)pppCharaZEnvCtrl + dataOffset + 0x80);
	void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0xd8), 0);
	int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
	*(void**)(model + 0xe4) = work;
	*(UnkB**)(model + 0xe8) = param_2;
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
void pppDesCharaZEnvCtrl(void)
{
	void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0xd8), 0);
	int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
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
void pppConCharaZEnvCtrl(void)
{
	void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0xd8), 0);
	GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
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
