#include "ffcc/wm_menu.h"

#include "ffcc/goout.h"
#include "ffcc/menu.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>
#include <string.h>

extern "C" void* __vt__Q212CFlatRuntime7CObject[];
extern "C" void* __vt__8CGBaseObj[];
extern "C" void* __vt__8CGObject[];
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" void DrawOptionMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawSingCMake__8CMenuPcsFv(CMenuPcs*);
extern "C" void PlaySe__6CSoundFiiii(void*, int, int, int, int);
extern "C" void SetAnim__Q29CCharaPcs7CHandleFiiiii(void*, int, int, int, int, int);
extern "C" void LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(void*, int, unsigned long, unsigned long);
extern "C" void SetFrame__Q26CChara6CModelFf(float, void*);
extern "C" void AddFrame__Q26CChara6CModelFf(float, void*);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(void*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(void*);
extern "C" void CalcSkin__Q26CChara6CModelFv(void*);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, void*, int, int, int, void*, void*);

extern float FLOAT_8032ee18;
extern float FLOAT_803313dc;
extern float FLOAT_803313e8;
extern float FLOAT_803314bc;
extern float FLOAT_80331598;
extern float FLOAT_803315d4;
extern float FLOAT_80331698;
extern float FLOAT_803317e0;
extern float FLOAT_803317e4;
extern float FLOAT_803317e8;
extern unsigned char DAT_8032ee20;
extern unsigned char uRam8032ee21;
extern unsigned char DAT_8032ee24;
extern unsigned char uRam8032ee25;
extern int DAT_8032ee28;
extern int DAT_8032ee2c;
extern unsigned char DAT_8032ee30;
extern unsigned char CFlat[];
extern char s_wm_menu_cpp_801dc418[];
extern char s__s__d___Error_WM_menu_no_error___801dc424[];

/*
 * --INFO--
 * PAL Address: 0x80102e9c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMenuPcs::EffectInfo::EffectInfo()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	void*** const vtable = reinterpret_cast<void***>(bytes + 0x54);

	*vtable = __vt__Q212CFlatRuntime7CObject;
	bytes[0x44] &= 0xEF;
	*vtable = __vt__8CGBaseObj;
	*vtable = __vt__8CGObject;
}

/*
 * --INFO--
 * PAL Address: 0x80102ed8
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WmInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	FLOAT_8032ee18 = FLOAT_803313dc;
	reinterpret_cast<unsigned int*>(bytes + 0x814)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x818)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x81C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x820)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x824)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x828)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x838)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x83C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x840)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x854)[0] = 0;
	bytes[0x858] = 0;
	bytes[0x86E] = 0;
	memset(bytes + 4, 0, 0x1C);
	bytes[0xD] = 0;
	bytes[0x10] = 0;
	bytes[0x12] = 0;
	bytes[0x13] = 0;
	bytes[0xD] = 1;
	bytes[0x16] = 0;
	DAT_8032ee20 = 0xFF;
	uRam8032ee21 = 0xFF;
	DAT_8032ee24 = 0xFF;
	uRam8032ee25 = 0xFF;
	DAT_8032ee2c = -1;
	DAT_8032ee28 = -1;
	DAT_8032ee30 = Game.game.m_gameWork.m_scriptSysVal0;
	if (Game.game.m_gameWork.m_scriptSysVal0 > 99) {
		DAT_8032ee30 = 100;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80102ed4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createWorld()
{
	// Ghidra body is a no-op.
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkNumItemAll()
{
	DAT_8032ee28 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8010172c
 * PAL Size: 6000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadData()
{
	InitFrameInfo();
	InitCharaInfo();
	InitCharaSelectInfo();
	InitCSelCurPos();
	WMSubMenuInit();
	SetParty();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitFrameInfo()
{
	InitFrame0Info();
}

/*
 * --INFO--
 * PAL Address: 0x80101658
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitFrame0Info()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const frame = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);

	reinterpret_cast<unsigned short*>(frame + 4)[0] = 0x10;
	reinterpret_cast<unsigned short*>(frame + 6)[0] = 0x10;
	reinterpret_cast<unsigned short*>(frame + 8)[0] = 0xE8;
	reinterpret_cast<unsigned short*>(frame + 0xA)[0] = 0x168;
	reinterpret_cast<float*>(frame + 0xC)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(frame + 0x10)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(frame + 0x14)[0] = FLOAT_803313e8;
	reinterpret_cast<float*>(frame + 0x18)[0] = FLOAT_803313e8;
	reinterpret_cast<unsigned int*>(frame + 0x1C)[0] = 0;

	reinterpret_cast<unsigned short*>(frame + 0x20)[0] = reinterpret_cast<unsigned short*>(frame + 4)[0];
	reinterpret_cast<unsigned short*>(frame + 0x22)[0] = reinterpret_cast<unsigned short*>(frame + 6)[0];
	reinterpret_cast<unsigned short*>(frame + 0x24)[0] = reinterpret_cast<unsigned short*>(frame + 8)[0];
	reinterpret_cast<unsigned short*>(frame + 0x26)[0] = reinterpret_cast<unsigned short*>(frame + 0xA)[0];
	reinterpret_cast<unsigned int*>(frame + 0x28)[0] = reinterpret_cast<unsigned int*>(frame + 0xC)[0];
	reinterpret_cast<unsigned int*>(frame + 0x2C)[0] = reinterpret_cast<unsigned int*>(frame + 0x10)[0];
	reinterpret_cast<unsigned int*>(frame + 0x30)[0] = reinterpret_cast<unsigned int*>(frame + 0x14)[0];
	reinterpret_cast<unsigned int*>(frame + 0x34)[0] = reinterpret_cast<unsigned int*>(frame + 0x18)[0];
	reinterpret_cast<unsigned int*>(frame + 0x38)[0] = reinterpret_cast<unsigned int*>(frame + 0x1C)[0];

	reinterpret_cast<short*>(frame + 0x20)[0] = 0x280 - (reinterpret_cast<short*>(frame + 8)[0] + reinterpret_cast<short*>(frame + 4)[0]);
	reinterpret_cast<unsigned int*>(frame + 0x38)[0] = 8;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Sprt::operator= (const CMenuPcs::Sprt& src)
{
	memcpy(this, &src, sizeof(CMenuPcs::Sprt));
}

/*
 * --INFO--
 * PAL Address: 0x80101444
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCharaInfo()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	for (int i = 0; i < 4; i++) {
		reinterpret_cast<unsigned int*>(bytes + 0x7F4)[i] = 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitCharaSelectInfo()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	if (selectData != 0) {
		memset(selectData, 0, 0x40);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitCSelCurPos()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80101150
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroyWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	reinterpret_cast<unsigned int*>(bytes + 0x814)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x818)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x81C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x820)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x824)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x828)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x83C)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x840)[0] = 0;
	reinterpret_cast<unsigned int*>(bytes + 0x854)[0] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801005d8
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const worldParams = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x83C)[0]);

	reinterpret_cast<unsigned int*>(worldParams + 4)[0] = reinterpret_cast<unsigned int*>(worldParams + 8)[0];

	if (worldState[8] == 0) {
		PlaySe__6CSoundFiiii(&Sound, 0x138B, 0x40, 0x7F, 0);
		SetAnim__Q29CCharaPcs7CHandleFiiiii(reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(bytes + 0x778)[0]), 0, -1, -1, -1, 0);
		reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
		worldState[8] = 1;
		reinterpret_cast<short*>(worldState + 0x10)[0] = 1;
	}

	void* const handle = reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(bytes + 0x778)[0]);
	void* const model = reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(handle) + 0x168)[0]);
	const float animEnd = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0x10)[0];
	const float animTime = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 8)[0];
	const short animState = reinterpret_cast<short*>(worldState + 0x10)[0];

	if (animState == 1) {
		if (animEnd <= animTime) {
			if (reinterpret_cast<short*>(worldState + 0x22)[0] > 9) {
				int stackData[3];
				stackData[0] = 2;
				stackData[1] = 0;
				stackData[2] = 0;

				SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, 1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
				SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				    CFlat, 0, 1, 4, 3, stackData, 0);
				reinterpret_cast<short*>(worldState + 0x10)[0] = 2;
				reinterpret_cast<short*>(worldState + 0x22)[0] = 0;
			}
		} else {
			AddFrame__Q26CChara6CModelFf(FLOAT_80331698, model);
			reinterpret_cast<short*>(worldState + 0x22)[0] = 0;
		}
	} else if (animState == 2) {
		int nextAnim = static_cast<signed char>(bytes[0xE]);

		if (nextAnim == 0) {
			if (animEnd <= animTime) {
				SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, 1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
			} else {
				AddFrame__Q26CChara6CModelFf(FLOAT_80331698, model);
			}
		} else {
			if (nextAnim >= 1 && nextAnim <= 4) {
				PlaySe__6CSoundFiiii(&Sound, 0x138C, 0x40, 0x7F, 0);
				nextAnim++;
			} else if (nextAnim == 5) {
				PlaySe__6CSoundFiiii(&Sound, 0x138D, 0x40, 0x7F, 0);
				nextAnim = 6;
				reinterpret_cast<short*>(worldState + 0x10)[0] = 3;
				reinterpret_cast<short*>(worldState + 0x22)[0] = 0;
			}

			if (nextAnim != reinterpret_cast<int*>(worldParams + 8)[0]) {
				SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, nextAnim, -1, -1, -1, 0);
				reinterpret_cast<int*>(worldParams + 8)[0] = nextAnim;

				if (nextAnim == 0) {
					SetFrame__Q26CChara6CModelFf(animEnd, model);
				}
			}
			bytes[0xE] = 0;
		}
	} else if (animState == 3 && reinterpret_cast<short*>(worldState + 0x22)[0] > 9) {
		if (animEnd <= animTime) {
			SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, 0, -1, -1, -1, 0);
			reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
			reinterpret_cast<short*>(worldState + 0x18)[0] = 10;
			reinterpret_cast<short*>(worldState + 0x1E)[0] = -1;
			reinterpret_cast<short*>(worldState + 0x10)[0] = 4;
			PlaySe__6CSoundFiiii(&Sound, 0x32, 0x40, 0x7F, 0);
		} else {
			AddFrame__Q26CChara6CModelFf(FLOAT_80331698, model);
		}
	} else if (animState == 4) {
		if (reinterpret_cast<short*>(worldState + 0x18)[0] == 0) {
			reinterpret_cast<short*>(worldState + 0x20)[0] = reinterpret_cast<short*>(worldState + 0x1E)[0];
			reinterpret_cast<short*>(worldState + 0x1E)[0] = 0;
		} else {
			reinterpret_cast<short*>(worldState + 0x18)[0]--;
		}
	}

	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);
	worldObj[0x50] = 1;
	reinterpret_cast<short*>(worldObj + 0x58)[0] = 0;
	reinterpret_cast<short*>(worldObj + 0x5A)[0] = 0;
	reinterpret_cast<short*>(worldObj + 0x5C)[0] = 0x280;
	reinterpret_cast<short*>(worldObj + 0x5E)[0] = 0x1C0;
	reinterpret_cast<float*>(worldObj + 0x60)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x64)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x68)[0] = FLOAT_80331598;
	reinterpret_cast<float*>(worldObj + 0x6C)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x70)[0] = FLOAT_803317e0;
	reinterpret_cast<float*>(worldObj + 0x74)[0] = FLOAT_803317e4;
	reinterpret_cast<float*>(worldObj + 0x78)[0] = FLOAT_803317e8;
	reinterpret_cast<float*>(worldObj + 0x7C)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x80)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x84)[0] = FLOAT_803315d4;
	reinterpret_cast<float*>(worldObj + 0x88)[0] = FLOAT_803315d4;
	reinterpret_cast<float*>(worldObj + 0x8C)[0] = FLOAT_803315d4;

	Mtx matrix;
	PSMTXRotRad(matrix, 'x', FLOAT_803314bc * reinterpret_cast<float*>(worldObj + 0x78)[0]);
	matrix[0][3] = reinterpret_cast<float*>(worldObj + 0x6C)[0];
	matrix[1][3] = reinterpret_cast<float*>(worldObj + 0x70)[0];
	matrix[2][3] = reinterpret_cast<float*>(worldObj + 0x74)[0];
	PSMTXScaleApply(matrix, matrix, reinterpret_cast<float*>(worldObj + 0x84)[0], reinterpret_cast<float*>(worldObj + 0x88)[0],
	                reinterpret_cast<float*>(worldObj + 0x8C)[0]);

	SetMatrix__Q26CChara6CModelFPA4_f(model, matrix);
	CalcMatrix__Q26CChara6CModelFv(model);
	CalcSkin__Q26CChara6CModelFv(model);

	const short updatedAnimState = reinterpret_cast<short*>(worldState + 0x10)[0];

	if (updatedAnimState == 1 && animTime >= animEnd) {
		if (reinterpret_cast<short*>(worldState + 0x22)[0] < 10) {
			reinterpret_cast<short*>(worldState + 0x22)[0]++;
		}
	} else if (updatedAnimState == 3 && reinterpret_cast<short*>(worldState + 0x22)[0] < 10) {
		reinterpret_cast<short*>(worldState + 0x22)[0]++;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcMainMenu()
{
	CalcMainMenuSub();
	CalcWMFrame();
	CalcChara();
	CalcPitcher();
	CalcFukidashi();
}

/*
 * --INFO--
 * PAL Address: 0x80100b00
 * PAL Size: 1616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcDiaryMenu()
{
	CalcMainMenuSub();
	CalcWMFrame();
	CalcFukidashi();
}

/*
 * --INFO--
 * PAL Address: 0x800fec40
 * PAL Size: 6552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMCardMenu()
{
	CalcMainMenuSub();
	CalcMcObj();
	CalcWMFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcCMakeMenu()
{
	CalcCharaSelect();
	CalcWMFrame();
	CalcFukidashi();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcMoveMenu()
{
	CalcMainMenuSub();
	CalcWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800feba0
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitSaveLoadMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x17] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fcfb4
 * PAL Size: 7148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcLoadMenu()
{
	CalcMainMenuSub();
	CalcMcObj();
	CalcWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800fca2c
 * PAL Size: 1416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcTitleMenu()
{
	CalcWMFrame();
	CalcChara();
}

/*
 * --INFO--
 * PAL Address: 0x800fc4bc
 * PAL Size: 1392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutCharaSelect(unsigned char state)
{
	CalcGoOutSelChar(state, 0);
	CalcWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800fc234
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutSelChar(unsigned char state, unsigned char slot)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = slot;
	bytes[0x17] = state;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcGoOutSelCharInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
	bytes[0x17] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc20c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMenuCharaAnim(int charaIndex, int animIndex)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const menuCharaAnims = *reinterpret_cast<unsigned char**>(bytes + 0x844);

	reinterpret_cast<int*>(menuCharaAnims + charaIndex * 0x14 + 4)[0] = animIndex;
}

/*
 * --INFO--
 * PAL Address: 0x800fc220
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetMenuCharaAnim__8CMenuPcsFii2(CMenuPcs* menuPcs)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(menuPcs);
	unsigned char* const data = *reinterpret_cast<unsigned char**>(bytes + 0x828);

	data[0xA] = 0;
	data[0xE] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc1f4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::IsMenuCharaAnimIdle(int charaIndex)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const menuCharaAnims = *reinterpret_cast<unsigned char**>(bytes + 0x844);

	return static_cast<unsigned int>(__cntlzw(reinterpret_cast<unsigned int*>(menuCharaAnims + charaIndex * 0x14)[0])) >> 5 & 0xff;
}

/*
 * --INFO--
 * PAL Address: 0x800fc0b0
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (bytes[0xD] == 0) {
		for (int i = 4; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(bytes + 0x10 + (i - 4) * 4 + 0x10C);
			menu->Draw();
		}
	} else {
		const short menuMode = *reinterpret_cast<short*>(*reinterpret_cast<unsigned int*>(bytes + 0x82C) + 0x1C);

		switch (menuMode) {
		case 0:
			DrawMainMenu();
			break;
		case 1:
			DrawDiaryMenu();
			break;
		case 2:
			DrawMCardMenu();
			break;
		case 3:
			if (*reinterpret_cast<short*>(bytes + 0x868) == 0) {
				DrawCMakeMenu();
			} else {
				DrawSingCMake__8CMenuPcsFv(this);
			}
			break;
		case 4:
			DrawMoveMenu();
			break;
		case 5:
			DrawLoadMenu();
			break;
		case 6:
			DrawTitleMenu();
			break;
		case 7:
			DrawOptionMenu__8CMenuPcsFv(this);
			break;
		case 8:
			DrawGoOutMenu();
			break;
		default:
			if (System.m_execParam != 0) {
				Printf__7CSystemFPce(&System, s__s__d___Error_WM_menu_no_error___801dc424, s_wm_menu_cpp_801dc418, 0xC59);
			}
			break;
		}

		for (int i = 4; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(bytes + 0x10 + (i - 4) * 4 + 0x10C);
			menu->Draw();
		}
		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fb910
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenu()
{
	DrawMainMenuSub();
	DrawMainMenuBase(1.0f);
	DrawWMFrame();
	DrawChara();
	DrawFukidashi();
}

/*
 * --INFO--
 * PAL Address: 0x800fb440
 * PAL Size: 1232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawDiaryMenu()
{
	DrawMainMenuSub();
	DrawWMFrame();
	DrawFukidashi();
}

/*
 * --INFO--
 * PAL Address: 0x800fa1cc
 * PAL Size: 4724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMCardMenu()
{
	DrawMainMenuSub();
	DrawMCList();
	DrawMcWin(0, 0);
	DrawWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800f98bc
 * PAL Size: 2320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCMakeMenu()
{
	DrawCharaName();
	DrawCMLife();
	DrawWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800f9248
 * PAL Size: 1652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMoveMenu()
{
	DrawMainMenuSub();
	DrawWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800f7efc
 * PAL Size: 4940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawLoadMenu()
{
	DrawMCList();
	DrawMcWin(0, 0);
	DrawWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800f7044
 * PAL Size: 3768b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawTitleMenu()
{
	DrawWMFrame();
	DrawChara();
}

/*
 * --INFO--
 * PAL Address: 0x800f6d70
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetWorldParam(int code, int value)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);

	switch (code) {
	case 0:
		bytes[5] = bytes[4];
		bytes[4] = static_cast<unsigned char>(value);
		break;
	case 1:
		bytes[6] = static_cast<unsigned char>(value);
		break;
	case 2:
		*reinterpret_cast<unsigned short*>(bytes + 0x1A) = static_cast<unsigned short>(value) & 0x3FF;
		break;
	case 3:
		bytes[7] = static_cast<unsigned char>(value);
		break;
	case 4:
		bytes[8] = static_cast<unsigned char>(value);
		break;
	case 5:
		*reinterpret_cast<unsigned short*>(bytes + 0x1C) = static_cast<unsigned short>(value);
		break;
	case 6:
		*reinterpret_cast<unsigned short*>(bytes + 0x1E) = static_cast<unsigned short>(value);
		break;
	case 7:
		bytes[9] = static_cast<unsigned char>(value);
		break;
	case 8:
		bytes[0xB] = bytes[0xC];
		bytes[0xC] = static_cast<unsigned char>(value);
		break;
	case 9:
		if (static_cast<signed char>(bytes[0xD]) != value) {
			bytes[0xD] = static_cast<unsigned char>(value);
		}
		*reinterpret_cast<unsigned short*>(worldState + 0x20) = 2;
		break;
	case 10:
		bytes[0x10] = static_cast<unsigned char>(value != 0);
		break;
	case 11:
		bytes[0x11] = static_cast<unsigned char>(value != 0);
		break;
	case 12:
		bytes[0xE] = static_cast<unsigned char>(value);
		break;
	case 13:
		bytes[0xF] = static_cast<unsigned char>(value & 3);
		break;
	case 14:
		bytes[0x12] = static_cast<unsigned char>(value != 0);
		break;
	case 15:
		bytes[0x13] = static_cast<unsigned char>(value != 0);
		break;
	case 16:
		bytes[0x17] = static_cast<unsigned char>(value);
		break;
	default:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f6afc
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetWorldParam(int code)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned int result = 0;

	switch (code) {
	case 0:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[4]));
		break;
	case 1:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[6]));
		break;
	case 2:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1A));
		break;
	case 3:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[7]));
		break;
	case 4:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[8]));
		break;
	case 5:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1C));
		break;
	case 6:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1E));
		break;
	case 7:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[9]));
		break;
	case 8:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0xC]));
		break;
	case 9:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0xD]));
		break;
	case 10:
		result = bytes[0x10] ? 1u : 0u;
		break;
	case 11:
		result = bytes[0x11] ? 1u : 0u;
		break;
	case 12:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0xE]));
		break;
	case 13:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0xF]));
		break;
	case 14:
		result = bytes[0x12] ? 1u : 0u;
		break;
	case 15:
		result = bytes[0x13] ? 1u : 0u;
		break;
	case 16:
		result = static_cast<unsigned int>(static_cast<signed char>(bytes[0x17]));
		break;
	default:
		break;
	}

	DAT_8032ee28 = static_cast<int>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800f6ab0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CallWorldParam(int p0, int p1, int p2)
{
	int stackData[3];
	stackData[0] = p0;
	stackData[1] = p1;
	stackData[2] = p2;

	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    CFlat, 0, 1, 4, 3, stackData, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSpl(CMenuPcs::SPL* out, CMenuPcs::SPL* in, float t)
{
	if (out == 0 || in == 0) {
		return;
	}
	if (t < 0.0f) {
		t = 0.0f;
	}
	if (t > 1.0f) {
		t = 1.0f;
	}
	memcpy(out, in, sizeof(CMenuPcs::SPL));
}

/*
 * --INFO--
 * PAL Address: 0x800f69a8
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetFcvValue(CMenuPcs::FCV, float value)
{
	FLOAT_8032ee18 = value;
}

/*
 * --INFO--
 * PAL Address: 0x800f67e0
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetProjection(int mode)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x11] = static_cast<unsigned char>(mode != 0);
}

/*
 * --INFO--
 * PAL Address: 0x800f673c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::RestoreProjection()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x11] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawObj(int kind)
{
	if (kind == 0) {
		DrawChara();
	} else {
		DrawMcObj();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f653c
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcPitcher()
{
	CalcCharaBase();
}

/*
 * --INFO--
 * PAL Address: 0x800f554c
 * PAL Size: 4080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcFukidashi()
{
	CalcWMFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800f4b24
 * PAL Size: 2600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFukidashi()
{
	DrawWMFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkPlaceLength(char* text)
{
	if (text == 0) {
		DAT_8032ee28 = 0;
		return;
	}
	DAT_8032ee28 = static_cast<int>(strlen(text));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SplitPlace(const char* text, char* left, char* right)
{
	if (left != 0) {
		left[0] = '\0';
	}
	if (right != 0) {
		right[0] = '\0';
	}
	if (text == 0 || left == 0 || right == 0) {
		return;
	}
	const char* const sep = strchr(text, ',');
	if (sep == 0) {
		strcpy(left, text);
		return;
	}
	const int len = static_cast<int>(sep - text);
	strncpy(left, text, len);
	left[len] = '\0';
	strcpy(right, sep + 1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SplitPlace2(const char* text, char* left, char* right, CFont*, int)
{
	SplitPlace(text, left, right);
}

/*
 * --INFO--
 * PAL Address: 0x800f3f60
 * PAL Size: 3012b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame()
{
	CalcWMFrame0(0);
}

/*
 * --INFO--
 * PAL Address: 0x800f36ac
 * PAL Size: 2228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawWMFrame()
{
	DrawWMFrame0(0, 1.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800f3500
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame0(int)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x820)[0] != 0) {
		InitFrame0Info();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f3384
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawWMFrame0(int, float)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawMainMenuBase(float)
{
	DrawWMFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcCharaBase()
{
	PCAnimCtrl();
}

/*
 * --INFO--
 * PAL Address: 0x800f31b8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCharaBase()
{
	DrawChara();
}

/*
 * --INFO--
 * PAL Address: 0x800f2b00
 * PAL Size: 1720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcChara()
{
	CalcCharaSelect();
	PCAnimCtrl();
}

/*
 * --INFO--
 * PAL Address: 0x800f26f4
 * PAL Size: 1036b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::PCAnimCtrl()
{
	GetMaxAnimWait();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetAnimNo(int animNo, int)
{
	DAT_8032ee28 = animNo;
}

/*
 * --INFO--
 * PAL Address: 0x800f2034
 * PAL Size: 1728b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawChara()
{
	DrawCharaName();
	DrawCMLife();
}

/*
 * --INFO--
 * PAL Address: 0x800f2018
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetModelNo(int modelNo, int, int)
{
	DAT_8032ee28 = modelNo;
}

/*
 * --INFO--
 * PAL Address: 0x800f0a70
 * PAL Size: 5544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCharaSelect()
{
	CalcMainMenuSub();
}

/*
 * --INFO--
 * PAL Address: 0x800f0274
 * PAL Size: 2044b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCharaName()
{
	DrawCursor(0, 0, 1.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800efc38
 * PAL Size: 1596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCMLife()
{
	DrawCursor(0, 0, 1.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::WMSubMenuInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x14] = 0;
	bytes[0x15] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800eeea0
 * PAL Size: 3480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WMChgMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[4] = bytes[5];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetParty()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x10] = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800eee34
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCMakeEnd(int channel)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	selectData[channel * 0x10 + 0xC] = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800eed84
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrCMakeFlg(int channel)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	unsigned char* const modelData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]);

	selectData[channel * 0x10 + 0xB] = 0;
	const int current = *reinterpret_cast<short*>(selectData + channel * 0x10 + 4);
	modelData[current * 0x34 + 0xC] = 0;
	LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(bytes + 0x7F4)[current]), 3, 0x43, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eec84
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel()
{
	for (int i = 0; i < 4; i++) {
		ChgModel(i, -1, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eeb9c
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel2()
{
	for (int i = 0; i < 4; i++) {
		ClrCMakeFlg(i);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetMakeChara(int slot)
{
	SetMenuCharaAnim(slot, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eeb1c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgModel(int slot, int tribe, int job, int isFemale)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const modelData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]) + slot * 0x34;
	int modelNo;
	int charaKind;

	if (tribe < 0) {
		charaKind = 3;
		modelData[0xC] = 0;
		modelNo = 0x43;
	} else {
		charaKind = 0;
		modelNo = tribe * 200 + 100;
		if (isFemale != 0) {
			modelNo = tribe * 200 + 200;
		}
		modelNo += job;
		modelData[0xC] = 1;
	}

	LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(bytes + 0x7F4)[slot]), charaKind,
	                                            static_cast<unsigned long>(modelNo), 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ee928
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetAnim(int anim)
{
	SetMenuCharaAnim(0, anim);
}

/*
 * --INFO--
 * PAL Address: 0x800ee828
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCursor(int, int, float)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800ed94c
 * PAL Size: 3804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenuSub()
{
	WMChgMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkSelectParty()
{
	DAT_8032ee28 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800ecff0
 * PAL Size: 2396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenuSub()
{
	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800ecfd0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcAccessPos(int* x, int* y)
{
	*x = DAT_8032ee20;
	*y = uRam8032ee21;
}

/*
 * --INFO--
 * PAL Address: 0x800ecfb0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcOdekakePos(int* x, int* y)
{
	*x = DAT_8032ee24;
	*y = uRam8032ee25;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkMcDataCnt()
{
	DAT_8032ee28 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800eb6f8
 * PAL Size: 6328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMCList()
{
	DrawPageMark();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpBase(int, float)
{
	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800eb1d8
 * PAL Size: 1312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMcObj()
{
	BindMcObj();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawMcObj()
{
	DrawPageMark();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetMcList(int index, McListInfo* info)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	if (list == 0 || info == 0 || index < 0) {
		return;
	}
	memcpy(list + index * sizeof(McListInfo), info, sizeof(McListInfo));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McListInfo::operator= (const McListInfo& src)
{
	memcpy(this, &src, sizeof(McListInfo));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ClrMcList()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	if (list != 0) {
		memset(list, 0, sizeof(McListInfo) * 4);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eb088
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindEffect(int, int, int)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800eafa0
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetLight(int mode)
{
	DAT_8032ee28 = mode;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawPageMark()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800ead94
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect2(unsigned long, float, float, float, float, float, float, float, float, float (*) [4])
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800eab98
 * PAL Size: 508b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect3d(unsigned long, float, float, float, float, float, float, float, float, float)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800eaaec
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMcWinInfo(int x, int y)
{
	DAT_8032ee20 = static_cast<unsigned char>(x);
	uRam8032ee21 = static_cast<unsigned char>(y);
}

/*
 * --INFO--
 * PAL Address: 0x800ea4f4
 * PAL Size: 1528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWin(short, short)
{
	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800ea150
 * PAL Size: 932b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWinMess(int, int)
{
	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800ea014
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetWinSize(int, short* w, short* h, int)
{
	if (w != 0) {
		*w = 0x100;
	}
	if (h != 0) {
		*h = 0x40;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetTextureLoc(int index)
{
	DAT_8032ee28 = index;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800ea00c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMaxAnimWait()
{
	DAT_8032ee28 = static_cast<int>(FLOAT_8032ee18);
}

/*
 * --INFO--
 * PAL Address: 0x800e9c8c
 * PAL Size: 896b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindMcObj()
{
	CalcMcObj();
}

/*
 * --INFO--
 * PAL Address: 0x800e9ba0
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char)
{
	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800e9b2c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CopyNowCaravanDat(Mc::SaveDat* outSave)
{
	MemoryCardMan.CreateMcBuff();
	MemoryCardMan.MakeSaveData();
	MemoryCardMan.DecodeData();
	memcpy(outSave, MemoryCardMan.m_saveBuffer, 0x8BD0);
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9aac
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCaravanWork(Mc::SaveDat* saveDat)
{
	MemoryCardMan.CreateMcBuff();
	memcpy(MemoryCardMan.m_saveBuffer, saveDat, 0x8BD0);
	Game.game.LoadInit();
	MemoryCardMan.SetLoadData();
	Game.game.LoadFinished();
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9904
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetSameCharaData(Mc::SaveDat* source, Mc::SaveDat* target, int memberIndex, int strictMode)
{
	unsigned char* const src = reinterpret_cast<unsigned char*>(source);
	unsigned char* const dst = reinterpret_cast<unsigned char*>(target);
	unsigned int result = 0xFFFFFFFF;

	if (strictMode == 0) {
		const unsigned char* const targetHeader = dst + memberIndex * 0x9C0;
		if (*reinterpret_cast<unsigned int*>(src + 0x13D4) != *reinterpret_cast<const unsigned int*>(targetHeader + 0x13D4) ||
		    *reinterpret_cast<unsigned int*>(src + 0x13D0) != *reinterpret_cast<const unsigned int*>(targetHeader + 0x13D0) ||
		    *reinterpret_cast<unsigned int*>(src + 0x13D8) != *reinterpret_cast<const unsigned int*>(targetHeader + 0x13D8)) {
			DAT_8032ee2c = -2;
			return;
		}
	}

	for (unsigned int i = 0; i < 8; i++) {
		const unsigned char* const cmpBase = dst + (memberIndex * 0x9C0 + 0x1D94) + ((i / 2) * 0x1380);
		const unsigned char* const srcBase = src + ((i % 2) ? 0x2750 : 0x1D90);

		if (srcBase[-0xC] != 0) {
			const unsigned int srcId = *reinterpret_cast<const unsigned int*>(srcBase + 4);
			const unsigned int dstId = *reinterpret_cast<const unsigned int*>(cmpBase);
			if (srcId == dstId) {
				if (strictMode == 0) {
					if (srcBase[0] != 0) {
						result = i;
						break;
					}
				} else if (srcBase[1] != 0 &&
				           *reinterpret_cast<const unsigned int*>(srcBase + 0xC) == *reinterpret_cast<const unsigned int*>(dst + 0x13D4) &&
				           *reinterpret_cast<const unsigned int*>(srcBase + 8) == *reinterpret_cast<const unsigned int*>(dst + 0x13D0) &&
				           *reinterpret_cast<const unsigned int*>(srcBase + 0x10) == *reinterpret_cast<const unsigned int*>(dst + 0x13D8)) {
					result = i;
					break;
				}
			}
		}
	}

	DAT_8032ee2c = static_cast<int>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800e98c4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CheckSameMcFormatID(Mc::SaveDat* lhs, Mc::SaveDat* rhs)
{
	unsigned char* const a = reinterpret_cast<unsigned char*>(lhs);
	unsigned char* const b = reinterpret_cast<unsigned char*>(rhs);
	const int same = (*reinterpret_cast<unsigned int*>(a + 0x13D4) == *reinterpret_cast<unsigned int*>(b + 0x13D4) &&
	                  *reinterpret_cast<unsigned int*>(a + 0x13D0) == *reinterpret_cast<unsigned int*>(b + 0x13D0) &&
	                  *reinterpret_cast<unsigned int*>(a + 0x13D8) == *reinterpret_cast<unsigned int*>(b + 0x13D8))
	                     ? 1
	                     : 0;
	DAT_8032ee28 = same;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::IsAsyncCharaLoadFinish()
{
	DAT_8032ee28 = 1;
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
McCtrl::McCtrl()
{
	Init();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
McCtrl::~McCtrl()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::Init()
{
	m_previousState = 0;
	m_state = 0;
	m_cardChannel = 0;
	m_lastResult = 0;
	m_saveIndex = 0;
	m_iteration = 0;
	m_createFlag = 0;
	m_userBuffer = 0;
	m_serialLo = 0;
	m_serialHi = 0;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::LoadMcList()
{
	m_lastResult = ChkNowData();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetListDat(int slot, int)
{
	if (slot < 0) {
		return;
	}
	m_saveIndex = slot;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetBrokenFile(int isBroken)
{
	m_createFlag = isBroken;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SaveDat()
{
	if (m_userBuffer != 0) {
		SaveDataBuffer(reinterpret_cast<char*>(m_userBuffer));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::LoadDat()
{
	m_lastResult = ChkNowData();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::Format(int unmountAfter)
{
	if (m_state < 0) {
		return;
	}
	m_previousState = m_state;
	if (m_state == 0) {
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		return;
	}
	if (m_state == 1) {
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult == -6 || m_lastResult == -0xD || m_lastResult == 0) {
				m_state = 2;
			} else {
				m_state = -1;
			}
		}
		return;
	}
	if (m_state == 2) {
		MemoryCardMan.McFormat(m_cardChannel);
		m_state = 3;
		return;
	}
	if (m_state == 3 && MemoryCardMan.AsyncFinished() == 1) {
		m_lastResult = MemoryCardMan.GetResult();
		if (m_lastResult < 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
		} else {
			if (unmountAfter != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
			}
			m_state = 4;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int McCtrl::ChkEmpty(int param_2)
{
	int filesFree;
	int bytesFree[3];

	if (m_state < 0)
	{
		return -1;
	}

	m_previousState = m_state;

	int state = m_state;

	if (state == 2)
	{
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			if (m_lastResult == -4)
			{
				if (param_2 != 0)
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -6;
				}

				m_state = 3;
			}
			else
			{
				if (m_lastResult == -5)
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -5;
				}

				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
			}
		}
		else
		{
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = 4;
		}
	}
	else if (state < 2)
	{
		if (state == 0)
		{
			MemoryCardMan.McMount(m_cardChannel);
			m_lastResult = MemoryCardMan.GetResult();
			m_state = 1;
			m_iteration = 0;
		}
		else if (state > -1 && MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult == 0)
			{
				m_state = 2;
			}
			else
			{
				if (m_lastResult == -0x0D)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -3;
				}

				if (m_lastResult == -6)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -4;
				}

				if (m_lastResult == -5)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -5;
				}

				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
				m_state = -1;
			}
		}
	}
	else if (state != 4 && state < 4)
	{
		m_lastResult = MemoryCardMan.McFreeBlocks(m_cardChannel, bytesFree, &filesFree);
		MemoryCardMan.McUnmount(m_cardChannel);

		if (m_lastResult < 0)
		{
			if (m_lastResult == -5)
			{
				m_state = -1;
				return -5;
			}

			m_state = -1;
		}
		else
		{
			if (filesFree == 0)
			{
				m_state = -1;
				return -2;
			}

			if (bytesFree[0] < 0x2C000)
			{
				m_state = -1;
				return -2;
			}

			m_state = 4;
		}
	}

	if (m_state == -1)
	{
		return -1;
	}
	else if (m_state == 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int McCtrl::ChkConnect(int chan)
{
	int result = MemoryCardMan.McChkConnect(chan);

	if (result == 0)
	{
		result = 1;
	}
	else if (result == -1)
	{
		result = -3;
	}
	else if (result == -2)
	{
		result = -6;
	}
	else if (result == -3)
	{
		result = -2;
	}
	else if (result == -4)
	{
		result = -5;
	}
	else
	{
		result = -1;
	}

	return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int McCtrl::ChkNowData()
{
	unsigned int serialLo = 0;
	unsigned int serialHi = 0;

	if (m_state < 0)
	{
		return -999;
	}

	m_previousState = m_state;

	switch (m_state)
	{
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult < 0)
			{
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;

				if (m_lastResult == -6)
				{
					m_state = 2;
				}
				else
				{
					if (m_lastResult == -0x0D)
					{
						m_state = -1;
						return -0x0D;
					}

					if (m_lastResult == -5)
					{
						m_state = -1;
						return -5;
					}

					m_state = -1;
				}
			}
			else
			{
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult != 0)
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;

				if (m_lastResult == -5)
				{
					return -5;
				}
				return -6;
			}

			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();

			if (m_lastResult == -4)
			{
				m_state = -1;
				return -4;
			}

			if (m_lastResult == -5)
			{
				m_state = -1;
				return -5;
			}

			m_state = -1;
		}
		else
		{
			m_state = 5;
		}
		break;

	case 5:
		if (CARDGetSerialNo(m_cardChannel, (unsigned long long*)&serialLo) != 0)
		{
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -999;
		}

		m_serialHi = serialHi;
		m_serialLo = serialLo;

		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult < 0)
			{
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;

				if (m_lastResult == -5)
				{
					return -5;
				}
			}
			else
			{
				MemoryCardMan.DecodeData();

				int r = MemoryCardMan.McClose();
				if (r == 0)
				{
					MemoryCardMan.McUnmount(m_cardChannel);

					if ((*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D4) == Game.game.m_gameWork.m_mcSerial1 &&
						 *(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D0) == Game.game.m_gameWork.m_mcSerial0) &&
						(*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D8) == Game.game.m_gameWork.m_mcRandom))
					{
						r = 1;
					}
					else
					{
						r = -1000;
					}

					MemoryCardMan.DestroyMcBuff();
					m_state = 7;
					return r;
				}

				m_lastResult = r;
				m_state = -1;
			}
		}
		break;
	}

	if (m_state == -1)
	{
		return -999;
	}
	if (m_state == 7)
	{
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SaveDataBuffer(char* buffer)
{
	m_userBuffer = buffer;
	m_state = 0;
	m_lastResult = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::ChkParty(char*)
{
	m_lastResult = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::EraseDat()
{
	m_state = 0;
	Format(1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetDno()
{
	DAT_8032ee28 = m_cardChannel;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetSerial()
{
	DAT_8032ee28 = static_cast<int>(m_serialLo);
	DAT_8032ee2c = static_cast<int>(m_serialHi);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetDataBuff(char* buffer)
{
	m_userBuffer = buffer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetSlot()
{
	DAT_8032ee28 = m_saveIndex;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetDno(int channel)
{
	m_cardChannel = channel;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetSlot(int slot)
{
	m_saveIndex = slot;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::AlphaNormal()
{
	FLOAT_8032ee18 = FLOAT_803313dc;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::AlphaAdd()
{
	FLOAT_8032ee18 = FLOAT_803315d4;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontWorld()
{
	DAT_8032ee28 = 0;
}

