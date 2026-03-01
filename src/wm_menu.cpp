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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitFrameInfo()
{
	return;
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
void CMenuPcs::Sprt::operator= (const CMenuPcs::Sprt&)
{
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitCharaSelectInfo()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitCSelCurPos()
{
	return;
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
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcCMakeMenu()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcMoveMenu()
{
	return;
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
	return;
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
	return;
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
	return;
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
void CMenuPcs::CalcGoOutCharaSelect(unsigned char)
{
	return;
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
void CMenuPcs::CalcGoOutSelChar(unsigned char, unsigned char)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcGoOutSelCharInit()
{
	return;
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
	return;
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
	return;
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
	return;
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
	return;
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
	return;
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
	return;
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
	return;
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
void CMenuPcs::SetWorldParam(int, int)
{
	return;
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
void CMenuPcs::GetWorldParam(int)
{
	return;
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
void CMenuPcs::CallWorldParam(int, int, int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSpl(CMenuPcs::SPL*, CMenuPcs::SPL*, float)
{
	return;
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
void CMenuPcs::GetFcvValue(CMenuPcs::FCV, float)
{
	return;
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
void CMenuPcs::SetProjection(int)
{
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawObj(int)
{
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkPlaceLength(char*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SplitPlace(const char*, char*, char*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SplitPlace2(const char*, char*, char*, CFont*, int)
{
	return;
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
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcCharaBase()
{
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetAnimNo(int, int)
{
	return;
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
	return;
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
void CMenuPcs::GetModelNo(int, int, int)
{
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::WMSubMenuInit()
{
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetParty()
{
	return;
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
void CMenuPcs::SetCMakeEnd(int)
{
	return;
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
void CMenuPcs::ClrCMakeFlg(int)
{
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetMakeChara(int)
{
	return;
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
void CMenuPcs::ChgModel(int, int, int, int)
{
	return;
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
void CMenuPcs::SetAnim(int)
{
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkSelectParty()
{
	return;
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
	return;
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
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpBase(int, float)
{
	return;
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
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawMcObj()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetMcList(int, McListInfo*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McListInfo::operator= (const McListInfo&)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ClrMcList()
{
	return;
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
void CMenuPcs::SetLight(int)
{
	return;
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
void CMenuPcs::SetMcWinInfo(int, int)
{
	return;
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
	return;
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
	return;
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
void CMenuPcs::GetWinSize(int, short*, short*, int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetTextureLoc(int)
{
	return;
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
	return;
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
	return;
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
	return;
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
void CMenuPcs::CopyNowCaravanDat(Mc::SaveDat*)
{
	return;
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
void CMenuPcs::SetCaravanWork(Mc::SaveDat*)
{
	return;
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
void CMenuPcs::GetSameCharaData(Mc::SaveDat*, Mc::SaveDat*, int, int)
{
	return;
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
void CMenuPcs::CheckSameMcFormatID(Mc::SaveDat*, Mc::SaveDat*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::IsAsyncCharaLoadFinish()
{
	return;
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
McCtrl::McCtrl()
{
	return;
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
	return;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::LoadMcList()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetListDat(int, int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetBrokenFile(int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SaveDat()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::LoadDat()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::Format(int)
{
	return;
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
	unsigned int serialLo;
	unsigned int serialHi;

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
void McCtrl::SaveDataBuffer(char*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::ChkParty(char*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::EraseDat()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetDno()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetSerial()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetDataBuff(char*)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::GetSlot()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetDno(int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void McCtrl::SetSlot(int)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::AlphaNormal()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::AlphaAdd()
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontWorld()
{
	return;
}

