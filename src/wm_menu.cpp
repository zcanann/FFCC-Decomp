#include "ffcc/wm_menu.h"

#include "ffcc/goout.h"
#include "ffcc/gbaque.h"
#include "ffcc/graphic.h"
#include "ffcc/menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_game.h"
#include "ffcc/linkage.h"
#include "ffcc/sound.h"
#include "ffcc/p_light.h"
#include "ffcc/partMng.h"
#include "ffcc/THPSimple.h"

#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include "ffcc/fontman.h"

extern "C" void* __vt__Q212CFlatRuntime7CObject[];
extern "C" void* __vt__8CGBaseObj[];
extern "C" void* __vt__8CGObject[];
extern "C" int rand(void);
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" void DrawOptionMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawSingCMake__8CMenuPcsFv(CMenuPcs*);

extern "C" void SetAnim__Q29CCharaPcs7CHandleFiiiii(void*, int, int, int, int, int);
extern "C" void LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(void*, char*, int, int, int, int, int, int);
extern "C" void LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(void*, int, unsigned long, unsigned long);
extern "C" void SetFrame__Q26CChara6CModelFf(float, void*);
extern "C" void AddFrame__Q26CChara6CModelFf(float, void*);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(void*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(void*);
extern "C" void CalcSkin__Q26CChara6CModelFv(void*);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, void*, int, int, int, void*, void*);
extern "C" int GetWinMess__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int GetMcWinMessBuff__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetFog__8CGraphicFii(void*, int, int);
extern "C" void SetAmbient__9CLightPcsF8_GXColor(void*, void*);
extern "C" void SetNumDiffuse__9CLightPcsFUl(void*, unsigned long);
extern "C" void SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(void*, unsigned long, void*, void*, int);
extern "C" void SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(void*, int, Vec*, unsigned long);
extern "C" void Create__9CGBaseObjFv(void*);
extern "C" void SetViewport__8CGraphicFv(void*);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void InitEnv__9CCharaPcsFi(void*, int);
extern "C" unsigned int pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(void*, int, int, void*, int);
extern "C" void pppDeletePart__8CPartMngFi(void*, int);
extern "C" void pppDestroyAll__8CPartMngFv(void*);
extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* Free__7CMemoryFPv(CMemory*, void*);
extern "C" int DAT_8021082c[];
extern "C" int DAT_80210830[];

float FLOAT_8032ee18;
extern float FLOAT_803313dc;
extern float FLOAT_803313e0;
extern float FLOAT_803313e4;
extern float FLOAT_803313e8;
extern float FLOAT_80331470;
extern float FLOAT_80331474;
extern float FLOAT_80331478;
extern float FLOAT_8033147c;
extern float FLOAT_803314bc;
extern float FLOAT_803314c0;
extern float FLOAT_803314c4;
extern float FLOAT_803314c8;
extern float FLOAT_803314cc;
extern float FLOAT_80331430;
extern float FLOAT_8033151c;
extern float FLOAT_80331528;
extern float FLOAT_803315cc;
extern float FLOAT_803315d0;
extern float FLOAT_80331598;
extern float FLOAT_803315d4;
extern float FLOAT_80331698;
extern float FLOAT_80331748;
extern float FLOAT_8033174c;
extern float FLOAT_80331750;
extern float FLOAT_80331754;
extern float FLOAT_803317e0;
extern float FLOAT_803317e4;
extern float FLOAT_803317e8;
extern char s_stand_80331638[];
extern char DAT_80331640[];
extern char DAT_80331648[];
extern char DAT_8033164c[];
extern char DAT_80331654[];
extern char DAT_8033165c[];
unsigned char gWmMenuCursorX;
unsigned char uRam8032ee21;
unsigned char gWmMenuCursorY;
unsigned char uRam8032ee25;
int gWmMenuWorkA;
int gWmMenuWorkB;
unsigned char gWmMenuScriptValueCache;
char s_wm_menu_cpp_801dc418[] = "wm_menu.cpp";
extern char s__s__d___Error_WM_menu_no_error___801dc424[];
extern char s_SetCMakeEnd___chan____d_cur____d_801dc3b4[];

static const int kMcListEntrySize = 0x48;
static const int kMcListCount = 4;

static void releaseRefCounted(void** refObj)
{
	if (refObj == 0 || *refObj == 0) {
		return;
	}
	int* const obj = reinterpret_cast<int*>(*refObj);
	const int refCount = obj[1] - 1;
	obj[1] = refCount;
	if (refCount == 0) {
		typedef void (*DestroyFn)(void*, int);
		DestroyFn destroyFn = *reinterpret_cast<DestroyFn*>(reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(obj)) + 8);
		destroyFn(obj, 1);
	}
	*refObj = 0;
}

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
	gWmMenuCursorX = 0xFF;
	uRam8032ee21 = 0xFF;
	gWmMenuCursorY = 0xFF;
	uRam8032ee25 = 0xFF;
	gWmMenuWorkB = -1;
	gWmMenuWorkA = -1;
	gWmMenuScriptValueCache = Game.m_gameWork.m_scriptSysVal0;
	if (Game.m_gameWork.m_scriptSysVal0 > 99) {
		gWmMenuScriptValueCache = 100;
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
	return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkNumItemAll()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int total = 0;

	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	if (list != 0) {
		for (int i = 0; i < kMcListCount; i++) {
			unsigned char* const entry = list + i * kMcListEntrySize;
			if (entry[0x43] == 0 && entry[0x41] != 0 && entry[0x42] == 0) {
				total++;
			}
		}
	}

	int selected = 0;
	unsigned char* const modelData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]);
	if (modelData != 0) {
		for (int i = 0; i < 8; i++) {
			if (modelData[i * 0x34 + 0xC] != 0) {
				selected++;
			}
		}
	}

	bytes[0x10] = static_cast<unsigned char>(selected != 0);
	gWmMenuWorkA = total + selected;
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<unsigned short*>(bytes + 0x86C) = 0;

	reinterpret_cast<void**>(bytes + 0x774)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x778)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x77C)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x780)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x784)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x788)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x78C)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x790)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x794)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x798)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x79C)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7A0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7A4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7A8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7AC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7B0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7B4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7B8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7BC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7C0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7C4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7C8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7CC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7D0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7D4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7D8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7DC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7E0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7E4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7E8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7EC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7F0)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7F4)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7F8)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x7FC)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x800)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x804)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x808)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x80C)[0] = 0;
	reinterpret_cast<void**>(bytes + 0x810)[0] = 0;

	reinterpret_cast<void**>(bytes + 0x814)[0] = new unsigned char[0xC80];
	memset(reinterpret_cast<void**>(bytes + 0x814)[0], 0, 0xC80);
	for (int i = 0; i < 0x28; i++) {
		unsigned char* const entry = reinterpret_cast<unsigned char*>(reinterpret_cast<void**>(bytes + 0x814)[0]) + i * 0x50;
		*reinterpret_cast<short*>(entry + 0x0C) = 0;
		*reinterpret_cast<short*>(entry + 0x0E) = 0;
		*reinterpret_cast<short*>(entry + 0x10) = 0x280;
		*reinterpret_cast<short*>(entry + 0x12) = 0x1C0;
		*reinterpret_cast<float*>(entry + 0x14) = FLOAT_803313dc;
		*reinterpret_cast<float*>(entry + 0x18) = FLOAT_803313dc;
		*reinterpret_cast<float*>(entry + 0x1C) = FLOAT_80331598;
		*reinterpret_cast<unsigned int*>(entry + 0x40) = 0;
		*reinterpret_cast<unsigned int*>(entry + 0x44) = 0;
		*reinterpret_cast<unsigned int*>(entry + 0x48) = 0x280;
		*reinterpret_cast<unsigned int*>(entry + 0x4C) = 0x1C0;
	}

	reinterpret_cast<void**>(bytes + 0x818)[0] = new unsigned char[0x8C];
	memset(reinterpret_cast<void**>(bytes + 0x818)[0], 0, 0x8C);

	reinterpret_cast<void**>(bytes + 0x81C)[0] = new unsigned char[0xEC];
	memset(reinterpret_cast<void**>(bytes + 0x81C)[0], 0, 0xEC);

	reinterpret_cast<void**>(bytes + 0x820)[0] = new unsigned char[0x3C];
	memset(reinterpret_cast<void**>(bytes + 0x820)[0], 0, 0x3C);

	reinterpret_cast<void**>(bytes + 0x824)[0] = new unsigned char[0x1A0];
	memset(reinterpret_cast<void**>(bytes + 0x824)[0], 0, 0x1A0);

	reinterpret_cast<void**>(bytes + 0x828)[0] = new unsigned char[0x80];
	memset(reinterpret_cast<void**>(bytes + 0x828)[0], 0, 0x80);

	reinterpret_cast<void**>(bytes + 0x82C)[0] = new unsigned char[0x48];
	memset(reinterpret_cast<void**>(bytes + 0x82C)[0], 0, 0x48);

	reinterpret_cast<void**>(bytes + 0x838)[0] = new unsigned char[0x120];
	memset(reinterpret_cast<void**>(bytes + 0x838)[0], 0, 0x120);

	reinterpret_cast<void**>(bytes + 0x83C)[0] = new unsigned char[0x10];
	memset(reinterpret_cast<void**>(bytes + 0x83C)[0], 0, 0x10);

	unsigned char* const effectRaw = new unsigned char[0xCDB0 + 0x10];
	memset(effectRaw, 0, 0xCDB0 + 0x10);
	reinterpret_cast<void**>(bytes + 0x840)[0] = effectRaw + 0x10;
	for (int i = 0; i < 0x28; i++) {
		unsigned char* const effect = reinterpret_cast<unsigned char*>(reinterpret_cast<void**>(bytes + 0x840)[0]) + i * 0x524;
		*reinterpret_cast<int*>(effect + 0x0) = -1;
		*reinterpret_cast<int*>(effect + 0x4) = -1;
		*reinterpret_cast<int*>(effect + 0x8) = -1;
	}

	reinterpret_cast<void**>(bytes + 0x844)[0] = new unsigned char[0xA0];
	memset(reinterpret_cast<void**>(bytes + 0x844)[0], 0, 0xA0);

	reinterpret_cast<void**>(bytes + 0x848)[0] = new unsigned char[0x0C];
	memset(reinterpret_cast<void**>(bytes + 0x848)[0], 0, 0x0C);

	InitFrameInfo();
	InitCharaInfo();
	InitCharaSelectInfo();
	InitCSelCurPos();
	WMSubMenuInit();
	SetParty();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitFrameInfo()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const frame = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);
	if (frame != 0) {
		memset(frame, 0, 0x3C);
	}
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
 * PAL Address: 0x80101444
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);

	int row = 0;
	int baseSlot = 0x20;
	short baseY = 0x66;
	while (row < 2) {
		int slotOffset = baseSlot * 0x50;
		short baseX = 0x68;
		for (int col = 0; col < 2; col++) {
			short y = baseY;
			if (row != 0) {
				y = static_cast<short>(baseY + 8);
			}

			*reinterpret_cast<short*>(worldObj + slotOffset + 8) = static_cast<short>(baseX - 0xA0);
			*reinterpret_cast<short*>(worldObj + slotOffset + 0xA) = static_cast<short>(y - 0x70);
			*reinterpret_cast<unsigned short*>(worldObj + slotOffset + 0xC) = 0x140;
			*reinterpret_cast<unsigned short*>(worldObj + slotOffset + 0xE) = 0xE0;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x10) = FLOAT_803313dc;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x14) = FLOAT_803313dc;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x18) = FLOAT_803313e8;

			short y2 = baseY;
			if (row != 0) {
				y2 = static_cast<short>(baseY + 8);
			}

			*reinterpret_cast<short*>(worldObj + slotOffset + 0x58) = static_cast<short>(baseX - 0x10);
			*reinterpret_cast<short*>(worldObj + slotOffset + 0x5A) = static_cast<short>(y2 - 0x70);
			*reinterpret_cast<unsigned short*>(worldObj + slotOffset + 0x5C) = 0x140;
			*reinterpret_cast<unsigned short*>(worldObj + slotOffset + 0x5E) = 0xE0;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x60) = FLOAT_803313dc;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x64) = FLOAT_803313dc;
			*reinterpret_cast<float*>(worldObj + slotOffset + 0x68) = FLOAT_803313e8;

			slotOffset += 0xA0;
			baseX = static_cast<short>(baseX + 0x120);
		}
		row++;
		baseY = static_cast<short>(baseY + 0xB8);
		baseSlot += 4;
	}

	for (int i = 0; i < 4; i++) {
		reinterpret_cast<unsigned int*>(bytes + 0x7F4)[i] = 0;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCharaSelectInfo()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	if (selectData != 0) {
		memset(selectData, 0, 0x80);
		for (int i = 0; i < 4; i++) {
			unsigned char* const entry = selectData + i * 0x10;
			*reinterpret_cast<short*>(entry + 4) = static_cast<short>(i);
			entry[0xA] = 0;
			entry[0xB] = 0;
			entry[0xC] = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCSelCurPos()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
	bytes[0x17] = 0;
	*reinterpret_cast<short*>(bytes + 0x1A) = 0;
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

	releaseRefCounted(reinterpret_cast<void**>(bytes + 0x11C));
	releaseRefCounted(reinterpret_cast<void**>(bytes + 0x120));
	releaseRefCounted(reinterpret_cast<void**>(bytes + 0xFC));

	if (reinterpret_cast<void**>(bytes + 0x81C)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x81C)[0]);
		reinterpret_cast<void**>(bytes + 0x81C)[0] = 0;
	}

	freeTexture(2, 3, 0x16, 0x2F);

	if (reinterpret_cast<void**>(bytes + 0xBC)[0] != 0) {
		releaseRefCounted(reinterpret_cast<void**>(bytes + 0xBC));
	}

	if (reinterpret_cast<void**>(bytes + 0x814)[0] != 0) {
		__dla__FPv(reinterpret_cast<void**>(bytes + 0x814)[0]);
		reinterpret_cast<void**>(bytes + 0x814)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x818)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x818)[0]);
		reinterpret_cast<void**>(bytes + 0x818)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x81C)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x81C)[0]);
		reinterpret_cast<void**>(bytes + 0x81C)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x820)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x820)[0]);
		reinterpret_cast<void**>(bytes + 0x820)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x824)[0] != 0) {
		__dla__FPv(reinterpret_cast<void**>(bytes + 0x824)[0]);
		reinterpret_cast<void**>(bytes + 0x824)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x828)[0] != 0) {
		__dla__FPv(reinterpret_cast<void**>(bytes + 0x828)[0]);
		reinterpret_cast<void**>(bytes + 0x828)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x844)[0] != 0) {
		__dla__FPv(reinterpret_cast<void**>(bytes + 0x844)[0]);
		reinterpret_cast<void**>(bytes + 0x844)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x82C)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x82C)[0]);
		reinterpret_cast<void**>(bytes + 0x82C)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x838)[0] != 0) {
		__dla__FPv(reinterpret_cast<void**>(bytes + 0x838)[0]);
		reinterpret_cast<void**>(bytes + 0x838)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x83C)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x83C)[0]);
		reinterpret_cast<void**>(bytes + 0x83C)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x840)[0] != 0) {
		unsigned char* const slotAlloc = reinterpret_cast<unsigned char*>(reinterpret_cast<void**>(bytes + 0x840)[0]);
		__dla__FPv(slotAlloc - 0x10);
		reinterpret_cast<void**>(bytes + 0x840)[0] = 0;
	}
	if (reinterpret_cast<void**>(bytes + 0x848)[0] != 0) {
		__dl__FPv(reinterpret_cast<void**>(bytes + 0x848)[0]);
		reinterpret_cast<void**>(bytes + 0x848)[0] = 0;
	}

	if (bytes[0x858] != 0) {
		THPSimpleAudioStop();
		THPSimpleLoadStop();
		THPSimpleClose();
		THPSimpleQuit();
		if (reinterpret_cast<void**>(bytes + 0x854)[0] != 0) {
			Free__7CMemoryFPv(&Memory, reinterpret_cast<void**>(bytes + 0x854)[0]);
			reinterpret_cast<void**>(bytes + 0x854)[0] = 0;
		}
		bytes[0x858] = 0;
	}

	pppDestroyAll__8CPartMngFv(&PartMng);
	MemoryCardMan.McEnd();

	GXColor clearColor;
	clearColor.r = 0;
	clearColor.g = 0;
	clearColor.b = 0;
	clearColor.a = 0;
	GXSetCopyClear(clearColor, 0x00FFFFFF);
	GbaQue.SetControllerMode(0);
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
		Sound.PlaySe(0x138B, 0x40, 0x7F, 0);
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
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim++;
			} else if (nextAnim == 5) {
				Sound.PlaySe(0x138D, 0x40, 0x7F, 0);
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
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
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
 * PAL Address: UNUSED
 * PAL Size: 504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	if (worldState == 0) {
		return;
	}

	switch (*reinterpret_cast<short*>(worldState + 0x1C)) {
	case 0:
		CalcMainMenuSub();
		break;
	case 1:
		calcWorld();
		break;
	case 2:
		CalcMCardMenu();
		break;
	case 3:
		if (*reinterpret_cast<short*>(bytes + 0x868) == 0) {
			if (worldState[0x0C] == 0) {
				unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]);
				if (selectData != 0) {
					for (int i = 0; i < 8; i++) {
						selectData[i * 0x34 + 0x0C] = 1;
					}
				}
				worldState[0x0C] = 1;
			}
			if (*reinterpret_cast<short*>(worldState + 0x10) < 5) {
				CalcCharaSelect();
				const short animState = *reinterpret_cast<short*>(worldState + 0x10);
				if (animState > 0 && animState < 4) {
					CalcChara();
				}
			}
		}
		break;
	case 4:
		CalcFukidashi();
		CalcPitcher();
		CalcWMFrame();
		break;
	case 5:
		CalcLoadMenu();
		break;
	case 6:
		CalcTitleMenu();
		break;
	case 7:
		CalcMoveMenu();
		break;
	case 8:
		CalcGoOutMenu();
		break;
	default:
		if (System.m_execParam != 0) {
			Printf__7CSystemFPce(&System, s__s__d___Error_WM_menu_no_error___801dc424, s_wm_menu_cpp_801dc418, 0x4c0);
		}
		break;
	}
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const frameState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);

	if (worldState != 0 && frameState != 0) {
		if (worldState[8] == 0) {
			memset(bytes + 0x838, 0, 0x120);
			worldState[0x0A] = 0;
			worldState[8] = 1;
		}

		const short menuAnim = *reinterpret_cast<short*>(worldState + 0x10);
		int offset = 0;
		if (menuAnim == 0) {
			offset = static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22)) - 10;
		} else if (menuAnim < 1 || menuAnim > 3) {
			offset = -static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22));
		}

		*reinterpret_cast<short*>(frameState + 4) = 0x10;
		*reinterpret_cast<short*>(frameState + 0x20) =
		    static_cast<short>(0x280 - (*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4)));

		if (offset < 0) {
			float shift = 0.0f;
			if (offset > -11) {
				int absOffset = offset < 0 ? -offset : offset;
				if (absOffset > 10) {
					absOffset = 10;
				}
				const float t = static_cast<float>(absOffset);
				const float baseWidth =
				    static_cast<float>(*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4));
				shift = baseWidth * FLOAT_8033151c * t;
				shift *= static_cast<float>(sin(FLOAT_803314bc * t * FLOAT_80331698));
			}

			*reinterpret_cast<short*>(frameState + 4) =
			    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 4)) - shift);
			*reinterpret_cast<short*>(frameState + 0x20) =
			    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 0x20)) + shift);
		}
	}

	CalcMainMenuSub();
	CalcMcObj();
	CalcWMFrame();
	CalcFukidashi();
	CalcCharaBase();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCMakeMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

	CalcCharaBase();
	CalcCharaSelect();
	CalcWMFrame();
	CalcFukidashi();
	if (static_cast<signed char>(bytes[0x17]) != 0) {
		CalcMainMenuSub();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMoveMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

	CalcMainMenuSub();
	CalcWMFrame();
	CalcFukidashi();
	CalcCharaBase();
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
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);

	if (worldState != 0) {
		*reinterpret_cast<float*>(worldState + 0x00) = FLOAT_803313dc;
		*reinterpret_cast<float*>(worldState + 0x04) = FLOAT_803313e8;
		worldState[0x08] = 0;
		worldState[0x09] = 0;
		worldState[0x0A] = 0;
		*reinterpret_cast<short*>(worldState + 0x0E) = 0;
		*reinterpret_cast<short*>(worldState + 0x10) = 0;
		*reinterpret_cast<short*>(worldState + 0x12) = 0;
		*reinterpret_cast<short*>(worldState + 0x16) = 0;
		*reinterpret_cast<short*>(worldState + 0x18) = 0;
		*reinterpret_cast<short*>(worldState + 0x1A) = 0;
		*reinterpret_cast<short*>(worldState + 0x22) = 0;
		*reinterpret_cast<short*>(worldState + 0x24) = 0;
		worldState[0x0B] = 0;
		*reinterpret_cast<short*>(worldState + 0x26) = 0;
		*reinterpret_cast<short*>(worldState + 0x2E) = 0;
	}

	*reinterpret_cast<short*>(bytes + 0x870) = 0;
	bytes[0x86E] = 0;
	bytes[0x858] = 0;
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const frameState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);
	bytes[0x86E] = 0;

	if (worldState != 0 && frameState != 0) {
		if (worldState[8] == 0) {
			*reinterpret_cast<short*>(frameState + 4) = 0x10;
			*reinterpret_cast<short*>(frameState + 6) = 0x10;
			*reinterpret_cast<short*>(frameState + 8) = 0xE8;
			*reinterpret_cast<short*>(frameState + 0x0A) = 0x168;
			*reinterpret_cast<float*>(frameState + 0x0C) = FLOAT_803313dc;
			*reinterpret_cast<float*>(frameState + 0x10) = FLOAT_803313dc;
			*reinterpret_cast<float*>(frameState + 0x14) = FLOAT_803313e8;
			*reinterpret_cast<float*>(frameState + 0x18) = FLOAT_803313e8;
			*reinterpret_cast<unsigned int*>(frameState + 0x1C) = 0;

			*reinterpret_cast<unsigned short*>(frameState + 0x20) = *reinterpret_cast<unsigned short*>(frameState + 4);
			*reinterpret_cast<unsigned short*>(frameState + 0x22) = *reinterpret_cast<unsigned short*>(frameState + 6);
			*reinterpret_cast<unsigned short*>(frameState + 0x24) = *reinterpret_cast<unsigned short*>(frameState + 8);
			*reinterpret_cast<unsigned short*>(frameState + 0x26) = *reinterpret_cast<unsigned short*>(frameState + 0x0A);
			*reinterpret_cast<unsigned int*>(frameState + 0x28) = *reinterpret_cast<unsigned int*>(frameState + 0x0C);
			*reinterpret_cast<unsigned int*>(frameState + 0x2C) = *reinterpret_cast<unsigned int*>(frameState + 0x10);
			*reinterpret_cast<unsigned int*>(frameState + 0x30) = *reinterpret_cast<unsigned int*>(frameState + 0x14);
			*reinterpret_cast<unsigned int*>(frameState + 0x34) = *reinterpret_cast<unsigned int*>(frameState + 0x18);
			*reinterpret_cast<unsigned int*>(frameState + 0x38) = *reinterpret_cast<unsigned int*>(frameState + 0x1C);
			*reinterpret_cast<short*>(frameState + 0x20) =
			    static_cast<short>(0x280 - (*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4)));
			*reinterpret_cast<unsigned int*>(frameState + 0x38) = 8;

			memset(bytes + 0x838, 0, 0x120);
			worldState[0x0A] = 0;
			worldState[8] = 1;
		}

		const short menuAnim = *reinterpret_cast<short*>(worldState + 0x10);
		int offset = 0;
		if (menuAnim == 0) {
			offset = static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22)) - 10;
		} else if (menuAnim < 1 || menuAnim > 3) {
			offset = -static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22));
		}

		*reinterpret_cast<short*>(frameState + 4) = 0x10;
		*reinterpret_cast<short*>(frameState + 0x20) =
		    static_cast<short>(0x280 - (*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4)));

		if (offset < 0) {
			float shift = 0.0f;
			if (offset > -11) {
				int absOffset = offset < 0 ? -offset : offset;
				if (absOffset > 10) {
					absOffset = 10;
				}
				const float t = static_cast<float>(absOffset);
				const float baseWidth =
				    static_cast<float>(*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4));
				shift = baseWidth * FLOAT_8033151c * t;
				shift *= static_cast<float>(sin(FLOAT_803314bc * t * FLOAT_80331698));
			}

			*reinterpret_cast<short*>(frameState + 4) =
			    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 4)) - shift);
			*reinterpret_cast<short*>(frameState + 0x20) =
			    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 0x20)) + shift);
		}
	}

	CalcMainMenuSub();
	CalcMcObj();
	CalcWMFrame();
	CalcFukidashi();
	CalcCharaBase();
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);

	if (worldState != 0) {
		if (worldState[8] == 0) {
			*reinterpret_cast<short*>(worldState + 0x18) = 0;
			*reinterpret_cast<short*>(worldState + 0x24) = 0;
			*reinterpret_cast<short*>(worldState + 0x0E) = -1;
			*reinterpret_cast<short*>(worldState + 0x12) = 0;
			*reinterpret_cast<short*>(worldState + 0x26) = 0;
			worldState[8] = 1;
			worldState[9] = 1;
			bytes[0x858] = 0;
		}

		if (*reinterpret_cast<short*>(worldState + 0x10) == 2 && *reinterpret_cast<short*>(worldState + 0x18) == 0) {
			const unsigned short repeat = GetButtonRepeat(0);
			if ((repeat & 0xC) != 0) {
				*reinterpret_cast<unsigned short*>(worldState + 0x26) ^= 1;
				*reinterpret_cast<short*>(worldState + 0x24) = 0;
				*reinterpret_cast<short*>(worldState + 0x12) = 0;
				worldState[9] = 0;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if ((repeat & 0x100) != 0) {
				*reinterpret_cast<short*>(worldState + 0x18) = 0x14;
				*reinterpret_cast<short*>(worldState + 0x0E) = 1;
				Sound.PlaySe(0x0B, 0x40, 0x7F, 0);
			}

			if (repeat == 0) {
				*reinterpret_cast<short*>(worldState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(worldState + 0x22) + 1);
			} else {
				*reinterpret_cast<short*>(worldState + 0x22) = 0;
			}
		}
	}

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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const selectState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	unsigned char* const animState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x844)[0]);

	if (worldState != 0 && selectState != 0 && *reinterpret_cast<short*>(worldState + 0x10) == 2) {
		short& cursor = *reinterpret_cast<short*>(selectState + 4);
		if (cursor < 0) {
			cursor = 0;
		}
		if (cursor > 7) {
			cursor = 7;
		}
		if (state != 0 && animState != 0) {
			*reinterpret_cast<int*>(animState + cursor * 0x14 + 4) = 3;
			selectState[0x0A] = 1;
		}
	}

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
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const frameState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);
	bytes[0x16] = slot;
	bytes[0x17] = state;

	if (worldState == 0 || frameState == 0 || *reinterpret_cast<short*>(worldState + 0x10) >= 5) {
		return;
	}

	if (state != 0) {
		CalcGoOutCharaSelect(slot);
	}

	const short menuAnim = *reinterpret_cast<short*>(worldState + 0x10);
	int offset = 0;
	if (menuAnim == 0) {
		offset = static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22)) - 10;
	} else if (menuAnim < 1 || menuAnim > 3) {
		offset = -static_cast<int>(*reinterpret_cast<short*>(worldState + 0x22));
	}

	*reinterpret_cast<short*>(frameState + 4) = 0x10;
	*reinterpret_cast<short*>(frameState + 0x20) =
	    static_cast<short>(0x280 - (*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4)));

	if (offset < 0) {
		float shift = 0.0f;
		if (offset > -11) {
			int absOffset = offset < 0 ? -offset : offset;
			if (absOffset > 10) {
				absOffset = 10;
			}
			const float t = static_cast<float>(absOffset);
			const float baseWidth =
			    static_cast<float>(*reinterpret_cast<short*>(frameState + 8) + *reinterpret_cast<short*>(frameState + 4));
			shift = baseWidth * FLOAT_8033151c * t;
			shift *= static_cast<float>(sin(FLOAT_803314bc * t * FLOAT_80331698));
		}

		*reinterpret_cast<short*>(frameState + 4) =
		    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 4)) - shift);
		*reinterpret_cast<short*>(frameState + 0x20) =
		    static_cast<short>(static_cast<float>(*reinterpret_cast<short*>(frameState + 0x20)) + shift);
	}

	if (menuAnim > 0 && menuAnim < 4) {
		CalcChara();
	}
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
void CMenuPcs::CalcGoOutSelCharInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x16] = 0;
	bytes[0x17] = 0;
	bytes[0xE] = 0;
	bytes[0xF] = 0;
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

	DrawMainMenuSub();
	DrawWMFrame();
	DrawFukidashi();
	DrawCharaBase();
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
	DrawPageMark();
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (reinterpret_cast<unsigned int*>(bytes + 0x82C)[0] == 0) {
		return;
	}

	DrawMainMenuSub();
	DrawWMFrame();
	DrawFukidashi();
	DrawCharaBase();
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
	DrawMainMenuSub();
	DrawMCList();
	DrawMcWin(-1, 0);
	DrawWMFrame();
	DrawPageMark();
	DrawCharaBase();
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
	DrawFukidashi();
	DrawPageMark();
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

	gWmMenuWorkA = static_cast<int>(result);
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
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);
	if (worldObj == 0) {
		return;
	}

	unsigned char* const slot = worldObj + mode * 0x50;
	Mtx44 projectionMtx;
	C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	PSMTX44Copy(projectionMtx, *reinterpret_cast<Mtx44*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x48));

	Vec target;
	target.x = FLOAT_803313dc;
	target.y = FLOAT_803313dc;
	target.z = FLOAT_803313dc;
	Vec up;
	up.x = FLOAT_803313dc;
	up.y = FLOAT_803313e8;
	up.z = FLOAT_803313dc;

	Mtx lookAtMtx;
	C_MTXLookAt(lookAtMtx, reinterpret_cast<Point3d*>(slot + 0x10), &up, reinterpret_cast<Point3d*>(&target));
	PSMTXCopy(lookAtMtx, *reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4));

	InitEnv__9CCharaPcsFi(&CharaPcs, 5);
	GXSetColorUpdate(0);
	GXSetAlphaUpdate(0);
	_GXColor clearColor = {0, 0, 0, 0};
	GXSetCopyClear(clearColor, 0x00FFFFFF);
	GXSetColorUpdate(1);
	GXSetAlphaUpdate(1);

	GXSetViewport(
	    static_cast<float>(*reinterpret_cast<short*>(slot + 8)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xA)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xC)),
	    static_cast<float>(*reinterpret_cast<short*>(slot + 0xE)),
	    FLOAT_803313dc,
	    FLOAT_803313e8);
	GXSetScissor(
	    *reinterpret_cast<unsigned int*>(slot + 0x40),
	    *reinterpret_cast<unsigned int*>(slot + 0x44),
	    *reinterpret_cast<unsigned int*>(slot + 0x48),
	    *reinterpret_cast<unsigned int*>(slot + 0x4C));
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
	Mtx44 projectionMtx;
	_GXColor clearColor = {0, 0, 0, 0};
	GXSetCopyClear(clearColor, 0x00FFFFFF);
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x48), projectionMtx);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	SetViewport__8CGraphicFv(&Graphic);
	GXSetScissor(0, 0, 0x280, 0x1C0);
	DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawObj(int kind)
{
	if (kind == 0) {
		DrawChara();
	} else if (kind == 1) {
		DrawMcObj();
	} else {
		DrawWMFrame();
		DrawFukidashi();
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);
	unsigned char* const handle = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x788)[0]);
	if (worldState == 0 || worldObj == 0 || handle == 0) {
		return;
	}

	const short state = reinterpret_cast<short*>(worldState + 0x10)[0];
	if (state <= 0 || state >= 3) {
		return;
	}

	reinterpret_cast<unsigned int*>(worldObj + 0x190)[0] = 1;
	reinterpret_cast<short*>(worldObj + 0x198)[0] = 0x140;
	reinterpret_cast<short*>(worldObj + 0x19A)[0] = 0xE0;
	reinterpret_cast<short*>(worldObj + 0x19C)[0] = 0x140;
	reinterpret_cast<short*>(worldObj + 0x19E)[0] = 0xE0;
	reinterpret_cast<float*>(worldObj + 0x1A0)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x1A4)[0] = FLOAT_803313dc;
	reinterpret_cast<float*>(worldObj + 0x1A8)[0] = FLOAT_803314bc;
	reinterpret_cast<float*>(worldObj + 0x1AC)[0] = FLOAT_80331748;
	reinterpret_cast<float*>(worldObj + 0x1B0)[0] = FLOAT_8033174c;
	reinterpret_cast<float*>(worldObj + 0x1B4)[0] = FLOAT_80331750;
	reinterpret_cast<float*>(worldObj + 0x1B8)[0] = FLOAT_803315d0;
	reinterpret_cast<float*>(worldObj + 0x1BC)[0] += FLOAT_80331754;

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	PSMTXScale(scaleMtx, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313e8);
	PSMTXRotRad(rotXMtx, 'x', reinterpret_cast<float*>(worldObj + 0x1B8)[0]);
	PSMTXRotRad(rotYMtx, 'y', reinterpret_cast<float*>(worldObj + 0x1BC)[0]);
	PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
	rotXMtx[0][3] = reinterpret_cast<float*>(worldObj + 0x1AC)[0];
	rotXMtx[1][3] = reinterpret_cast<float*>(worldObj + 0x1B0)[0];
	rotXMtx[2][3] = reinterpret_cast<float*>(worldObj + 0x1B4)[0];
	PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

	void* const model = reinterpret_cast<void*>(reinterpret_cast<unsigned int*>(handle + 0x168)[0]);
	if (model == 0) {
		return;
	}

	const unsigned int step = static_cast<unsigned int>(reinterpret_cast<short*>(worldState + 0x22)[0]);
	float blend = FLOAT_803313e8;
	if (state == 1 && step < 10) {
		blend = static_cast<float>(step) * 0.1f;
	} else if (state == 2 && bytes[0x13] != 0) {
		blend = 1.0f - static_cast<float>(step) * 0.1f;
	}
	reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0x9C)[0] = blend;

	SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
	CalcMatrix__Q26CChara6CModelFv(model);
	CalcSkin__Q26CChara6CModelFv(model);
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
	CalcPitcher();
	CalcMainMenuSub();
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
	DrawWMFrame0(3, 1.0f);
	DrawMainMenuSub();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkPlaceLength(char* text)
{
	if (text == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	int len = static_cast<int>(strlen(text));
	while (len > 0) {
		const char c = text[len - 1];
		if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
			break;
		}
		len--;
	}
	gWmMenuWorkA = len;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	const char* rhs = sep + 1;
	while (*rhs == ' ' || *rhs == '\t') {
		rhs++;
	}
	strcpy(right, rhs);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SplitPlace2(const char* text, char* left, char* right, CFont*, int)
{
	SplitPlace(text, left, right);
	if (left != 0) {
		for (char* p = left; *p != '\0'; p++) {
			if (*p == '\t') {
				*p = ' ';
			}
		}
	}
	if (right != 0) {
		for (char* p = right; *p != '\0'; p++) {
			if (*p == '\t') {
				*p = ' ';
			}
		}
	}
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
	DrawWMFrame0(3, 1.0f);
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
void CMenuPcs::CalcWMFrame0(int param)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const frame = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);

	if (frame == 0) {
		return;
	}

	reinterpret_cast<short*>(frame + 4)[0] = 0x10;
	reinterpret_cast<short*>(frame + 0x20)[0] = static_cast<short>(640 - (reinterpret_cast<short*>(frame + 8)[0] + reinterpret_cast<short*>(frame + 4)[0]));

	if (param < 0) {
		float offset = static_cast<float>(reinterpret_cast<short*>(frame + 8)[0] + reinterpret_cast<short*>(frame + 4)[0]);
		if (param > -11) {
			int absParam = -param;
			if (absParam > 10) {
				absParam = 10;
			}
			float t = static_cast<float>(absParam);
			offset = offset * 0.1f * t;
			offset = offset * static_cast<float>(sin(FLOAT_803314bc * t * FLOAT_80331698));
		}
		reinterpret_cast<short*>(frame + 4)[0] = static_cast<short>(static_cast<float>(reinterpret_cast<short*>(frame + 4)[0]) - offset);
		reinterpret_cast<short*>(frame + 0x20)[0] = static_cast<short>(static_cast<float>(reinterpret_cast<short*>(frame + 0x20)[0]) + offset);
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
void CMenuPcs::DrawWMFrame0(int mask, float alpha)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const frame = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);
	if (frame == 0) {
		return;
	}

	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(255.0f * alpha);
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	if (mask == 0) {
		mask = 3;
	}

	for (int i = 0; i < 2; i++) {
		if ((mask & (1 << i)) == 0) {
			continue;
		}

		unsigned char* const entry = frame + 4 + i * 0x1C;
		const short x = reinterpret_cast<short*>(entry + 0)[0];
		const short y = reinterpret_cast<short*>(entry + 2)[0];
		const short w = reinterpret_cast<short*>(entry + 4)[0];
		const short h = reinterpret_cast<short*>(entry + 6)[0];
		const float u = reinterpret_cast<float*>(entry + 8)[0];
		const float v = reinterpret_cast<float*>(entry + 0xC)[0];
		const unsigned int flags = reinterpret_cast<unsigned int*>(entry + 0x18)[0];

		DrawRect(0xFFFFFFFF, static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), u, v, 1.0f, 1.0f,
		         static_cast<float>(flags));
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 388b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenuBase(float)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const frame = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x820)[0]);
	float alpha = 1.0f;

	if (worldState != 0) {
		const short state = *reinterpret_cast<short*>(worldState + 0x10);
		const short step = *reinterpret_cast<short*>(worldState + 0x22);
		if (state == 0) {
			alpha = static_cast<float>(step) * 0.1f;
		} else if (state >= 3) {
			alpha = 1.0f - static_cast<float>(step) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	if (frame != 0) {
		for (int i = 0; i < 2; i++) {
			unsigned char* const entry = frame + 4 + i * 0x1C;
			DrawRect(0xFFFFFFFF, static_cast<float>(*reinterpret_cast<short*>(entry + 0)),
			         static_cast<float>(*reinterpret_cast<short*>(entry + 2)), static_cast<float>(*reinterpret_cast<short*>(entry + 4)),
			         static_cast<float>(*reinterpret_cast<short*>(entry + 6)), *reinterpret_cast<float*>(entry + 8),
			         *reinterpret_cast<float*>(entry + 0x0C), 1.0f, 1.0f, static_cast<float>(*reinterpret_cast<unsigned int*>(entry + 0x18)));
		}
	}

	DrawMainMenuSub();
	DrawPageMark();
	DrawHelpBase(0, alpha);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCharaBase()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);
	if (worldState == 0 || worldObj == 0) {
		return;
	}

	const short state = *reinterpret_cast<short*>(worldState + 0x10);
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			unsigned char* const slot = worldObj + 0x1E0 + (row * 4 + col) * 0x50;
			*reinterpret_cast<unsigned int*>(slot + 0x00) = (state > 0 && state < 4) ? 1u : 0u;
			*reinterpret_cast<short*>(slot + 0x08) = static_cast<short>(0x1C + col * 0x90);
			*reinterpret_cast<short*>(slot + 0x0A) = static_cast<short>((row == 0 ? 0x22 : 0xCA) + (row != 0 ? 8 : 0));
			*reinterpret_cast<unsigned short*>(slot + 0x0C) = 0x140;
			*reinterpret_cast<unsigned short*>(slot + 0x0E) = 0xE0;
			*reinterpret_cast<float*>(slot + 0x10) = FLOAT_803313dc;
			*reinterpret_cast<float*>(slot + 0x14) = FLOAT_803313dc;
			*reinterpret_cast<float*>(slot + 0x18) = FLOAT_80331598;
		}
	}
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	if (worldState == 0) {
		return;
	}

	const short state = *reinterpret_cast<short*>(worldState + 0x10);
	if (state <= 0) {
		return;
	}

	float alpha = 1.0f;
	if (state == 1) {
		alpha = static_cast<float>(*reinterpret_cast<short*>(worldState + 0x22)) * 0.1f;
	} else if (state >= 3) {
		alpha = 1.0f - static_cast<float>(*reinterpret_cast<short*>(worldState + 0x22)) * 0.1f;
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	SetTexture(static_cast<CMenuPcs::TEX>(0x29));

	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			const float x = static_cast<float>(0x1C + col * 0x90);
			const float y = static_cast<float>((row == 0 ? 0x22 : 0xCA) + (row != 0 ? 8 : 0));
			DrawRect(0xFFFFFFFF, x, y, 0x140, 0xE0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		}
	}
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const charaSelect = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	unsigned int selectedMask = 0;

	if (charaSelect[0x0D] != 0 && charaSelect[0x0A] != 0) {
		selectedMask |= 1u << static_cast<unsigned int>(reinterpret_cast<unsigned short*>(charaSelect + 4)[0]);
	}
	if (charaSelect[0x1D] != 0 && charaSelect[0x1A] != 0) {
		selectedMask |= 1u << static_cast<unsigned int>(reinterpret_cast<unsigned short*>(charaSelect + 0x14)[0]);
	}
	if (charaSelect[0x2D] != 0 && charaSelect[0x2A] != 0) {
		selectedMask |= 1u << static_cast<unsigned int>(reinterpret_cast<unsigned short*>(charaSelect + 0x24)[0]);
	}
	if (charaSelect[0x3D] != 0 && charaSelect[0x3A] != 0) {
		selectedMask |= 1u << static_cast<unsigned int>(reinterpret_cast<unsigned short*>(charaSelect + 0x34)[0]);
	}

	int* animState = reinterpret_cast<int*>(reinterpret_cast<unsigned int*>(bytes + 0x844)[0]);
	for (int i = 0; i < 8; i++, animState += 5) {
		unsigned char* const handle = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x7F4)[i]);
		if (handle == 0) {
			continue;
		}

		unsigned char* const model = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(handle + 0x168)[0]);
		if (model == 0 || reinterpret_cast<unsigned int*>(model + 0x18)[0] == 0 || reinterpret_cast<int*>(handle)[0] == 3) {
			continue;
		}

		const unsigned int isSelected = selectedMask & (1u << static_cast<unsigned int>(i));
		animState[3] = reinterpret_cast<int*>(model + 8)[0];
		const int baseAnim = (static_cast<int>(reinterpret_cast<unsigned int*>(handle + 4)[0] / 100) - 1) * 6;
		const int currentAnimIndex = reinterpret_cast<int*>(handle + 0x16C)[0];
		const int blendMode = -1 - (currentAnimIndex >> 31);

		if (animState[1] >= 0) {
			animState[0] = animState[1];
			animState[1] = -1;
			SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, baseAnim + animState[0], -1, -1, blendMode, 0);
			animState[3] = reinterpret_cast<int*>(model + 8)[0];
			animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
			animState[2] = 0;
			continue;
		}

		const float frame = reinterpret_cast<float*>(model + 8)[0];
		const float frameEnd = reinterpret_cast<float*>(model + 0x10)[0];
		if (isSelected == 0 && reinterpret_cast<short*>(worldState + 0x1C)[0] != 8 && animState[0] == 0 && animState[2] > 2999) {
			animState[0] = 4;
			SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, baseAnim + animState[0], -1, -1, blendMode, 0);
			animState[3] = reinterpret_cast<int*>(model + 8)[0];
			animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
			animState[2] = 0;
		} else if (isSelected != 0 && reinterpret_cast<short*>(worldState + 0x1C)[0] != 8) {
			if (animState[0] == 1 && animState[2] > 11999) {
				animState[0] = 0;
				animState[2] = 0;
			} else if (animState[0] == 2 && animState[2] > 8999) {
				animState[0] = 1;
			} else if (animState[0] == 1 && animState[2] > 5999 && animState[2] < 9000) {
				animState[0] = 2;
			} else if (animState[0] == 0 && animState[2] >= 3000) {
				animState[0] = 1;
			} else {
				if (frameEnd <= frame) {
					if (animState[0] == 3 || animState[0] == 4 || animState[0] == 5) {
						animState[0] = 0;
						SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, baseAnim + animState[0], -1, -1, blendMode, 0);
						animState[3] = reinterpret_cast<int*>(model + 8)[0];
						animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
						animState[2] = isSelected == 0 ? 0 : 0x834;
					}
					SetFrame__Q26CChara6CModelFf(FLOAT_803313dc, model);
				} else {
					AddFrame__Q26CChara6CModelFf(FLOAT_80331698, model);
				}
				animState[2]++;
				continue;
			}

			SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, baseAnim + animState[0], -1, -1, blendMode, 0);
			animState[3] = reinterpret_cast<int*>(model + 8)[0];
			animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
		} else {
			if (frameEnd <= frame) {
				if (animState[0] == 3 || animState[0] == 4 || animState[0] == 5) {
					animState[0] = 0;
					SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, baseAnim + animState[0], -1, -1, blendMode, 0);
					animState[3] = reinterpret_cast<int*>(model + 8)[0];
					animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
					animState[2] = isSelected == 0 ? 0 : 0x834;
				}
				SetFrame__Q26CChara6CModelFf(FLOAT_803313dc, model);
			} else {
				AddFrame__Q26CChara6CModelFf(FLOAT_80331698, model);
			}
			animState[2]++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetAnimNo(int animNo, int)
{
	if (animNo < 0) {
		animNo = 0;
	}
	gWmMenuWorkA = animNo;
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
int CMenuPcs::GetModelNo(int modelNo, int offset, int baseType)
{
	int result = modelNo * 200 + 100;
	if (baseType != 0) {
		result += 100;
	}
	return result + offset;
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
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WMSubMenuInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	bytes[0x14] = 0;
	bytes[0x15] = 0;
	bytes[0x16] = 0;
	bytes[0x17] = 0;
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
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetParty()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const modelData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]);
	unsigned char* const mcList = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	int partyCount = 0;

	if (modelData != 0) {
		for (int i = 0; i < 8; i++) {
			if (modelData[i * 0x34 + 0x0C] != 0) {
				partyCount++;
			}
		}
	}
	if (partyCount == 0 && mcList != 0) {
		for (int i = 0; i < kMcListCount; i++) {
			unsigned char* const entry = mcList + i * kMcListEntrySize;
			if (entry[0x41] != 0 && entry[0x42] == 0 && entry[0x43] == 0) {
				partyCount++;
			}
		}
	}
	gWmMenuWorkA = partyCount;
	bytes[0x10] = static_cast<unsigned char>(partyCount > 0);
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
	if ((unsigned int)System.m_execParam > 2) {
		Printf__7CSystemFPce(&System, s_SetCMakeEnd___chan____d_cur____d_801dc3b4, channel,
		                     (int)*reinterpret_cast<short*>(selectData + channel * 0x10 + 4));
	}
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
 * PAL Address: UNUSED
 * PAL Size: 660b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMakeChara(int slot)
{
	if (slot < 0) {
		slot = 0;
	}
	if (slot > 3) {
		slot = 3;
	}
	SetMenuCharaAnim(slot, 0);
	reinterpret_cast<unsigned char*>(this)[0x16] = static_cast<unsigned char>(slot);
	ChkSelectParty();
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const handle = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x7F4)[anim]);
	if (handle == 0 || reinterpret_cast<int*>(handle)[0] == 3) {
		return;
	}

	const unsigned int charaNo = reinterpret_cast<unsigned int*>(handle + 4)[0];
	const int modelBase = static_cast<int>(charaNo / 100) * 100;
	const int animBase = (static_cast<int>(charaNo / 100) - 1) * 6;

	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, s_stand_80331638, animBase + 0, 1, 0, modelBase, -1, 0);
	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, DAT_80331640, animBase + 1, 1, 0, modelBase, -1, 0);
	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, DAT_80331648, animBase + 2, 1, 0, modelBase, -1, 0);
	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, DAT_8033164c, animBase + 3, 3, 0, modelBase, -1, 0);
	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, DAT_80331654, animBase + 4, 1, 0, modelBase, -1, 0);
	LoadAnim__Q29CCharaPcs7CHandleFPciiiiii(handle, DAT_8033165c, animBase + 5, 1, 0, modelBase, -1, 0);

	int* const animState = reinterpret_cast<int*>(reinterpret_cast<unsigned int*>(bytes + 0x844)[0]) + anim * 5;
	animState[0] = 0;
	animState[1] = -1;
	animState[2] = rand() % 250;

	const int currentAnimIndex = reinterpret_cast<int*>(handle + 0x16C)[0];
	const int blendMode = -1 - (currentAnimIndex >> 31);
	SetAnim__Q29CCharaPcs7CHandleFiiiii(handle, animBase + animState[0], -1, -1, blendMode, 1);

	unsigned char* const model = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(handle + 0x168)[0]);
	if (model != 0) {
		animState[3] = reinterpret_cast<int*>(model + 8)[0];
		animState[4] = reinterpret_cast<int*>(model + 0x10)[0];
	}
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
void CMenuPcs::DrawCursor(int x, int y, float scale)
{
	float size = 20.0f * scale;
	if (size < 1.0f) {
		size = 1.0f;
	}
	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	SetTexture(static_cast<CMenuPcs::TEX>(0));
	DrawRect(0xFFFFFFFF, static_cast<float>(x), static_cast<float>(y), size, size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const world = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	const unsigned short btn = static_cast<unsigned short>(GetButtonDown(0));
	const short state = reinterpret_cast<short*>(world + 0x10)[0];

	if (((state > 0) && (state < 4)) || reinterpret_cast<short*>(world + 0x26)[0] == 1) {
		if (state == 2 && reinterpret_cast<short*>(world + 0x18)[0] == 0) {
			if ((btn & 1) != 0) {
				*reinterpret_cast<float*>(bytes + 0x78) -= FLOAT_8033151c;
				if (*reinterpret_cast<float*>(bytes + 0x78) < FLOAT_803313dc) {
					*reinterpret_cast<float*>(bytes + 0x78) += FLOAT_80331528;
					*reinterpret_cast<float*>(bytes + 0x7C) += FLOAT_80331528;
				}
				*reinterpret_cast<short*>(world + 0x22) = 0xE;
				if (*reinterpret_cast<short*>(world + 0x26) < 4) {
					(*reinterpret_cast<short*>(world + 0x26))++;
				} else {
					*reinterpret_cast<short*>(world + 0x26) = 0;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			} else if ((btn & 2) != 0) {
				*reinterpret_cast<float*>(bytes + 0x78) += FLOAT_8033151c;
				if (*reinterpret_cast<float*>(bytes + 0x78) > FLOAT_80331528) {
					*reinterpret_cast<float*>(bytes + 0x78) -= FLOAT_80331528;
					*reinterpret_cast<float*>(bytes + 0x7C) -= FLOAT_80331528;
				}
				*reinterpret_cast<short*>(world + 0x22) = 0xE;
				if (*reinterpret_cast<short*>(world + 0x26) < 1) {
					*reinterpret_cast<short*>(world + 0x26) = 4;
				} else {
					(*reinterpret_cast<short*>(world + 0x26))--;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			}

			const float selA = *reinterpret_cast<float*>(bytes + 0x78);
			const float selB = *reinterpret_cast<float*>(bytes + 0x7C);
			const float lo = (selA < selB) ? selA : selB;
			const float hi = (selA < selB) ? selB : selA;
			const float delta = FLOAT_803315cc * (hi - lo);
			if (selA < selB) {
				*reinterpret_cast<float*>(bytes + 0x7C) -= delta;
			} else {
				*reinterpret_cast<float*>(bytes + 0x7C) += delta;
			}

			if (*reinterpret_cast<short*>(world + 0x22) > 0) {
				(*reinterpret_cast<short*>(world + 0x22))--;
			}

			if (*reinterpret_cast<short*>(world + 0x22) == 0 && (btn & 3) == 0) {
				if ((btn & 0x100) != 0) {
					*reinterpret_cast<float*>(bytes + 0x7C) = *reinterpret_cast<float*>(bytes + 0x78);
					*reinterpret_cast<short*>(world + 0x18) = 0x14;
					*reinterpret_cast<short*>(world + 0x1E) = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else if ((btn & 0x200) != 0) {
					int valid = 0;
					*reinterpret_cast<float*>(bytes + 0x7C) = *reinterpret_cast<float*>(bytes + 0x78);
					for (int i = 0; i < 4; i++) {
						if (Game.m_gameWork.m_menuStageMode != 0 && i != 0) {
							break;
						}
						if (*reinterpret_cast<short*>(world + 0x3E + i * 2) >= 0) {
							valid++;
						}
					}
					if (valid == 0) {
						Sound.PlaySe(4, 0x40, 0x7F, 0);
					} else {
						*reinterpret_cast<short*>(world + 0x18) = 1;
						*reinterpret_cast<short*>(world + 0x1E) = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}
	}

	WMChgMenu();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkSelectParty()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const modelData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x824)[0]);
	int selected = 0;

	if (modelData == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	for (int i = 0; i < 8; i++) {
		if (modelData[i * 0x34 + 0xC] != 0) {
			selected++;
		}
	}

	gWmMenuWorkA = selected;
	reinterpret_cast<unsigned char*>(this)[0x10] = static_cast<unsigned char>(selected != 0);
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
	DrawWMFrame0(3, 1.0f);
	if (gWmMenuWorkA > 0) {
		DrawCursor(gWmMenuCursorX, uRam8032ee21, 1.0f);
	}
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
	*x = gWmMenuCursorX;
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
	*x = gWmMenuCursorY;
	*y = uRam8032ee25;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChkMcDataCnt()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	int count = 0;

	if (list == 0) {
		gWmMenuWorkA = 0;
		return;
	}

	for (int i = 0; i < kMcListCount; i++) {
		unsigned char* const entry = list + i * kMcListEntrySize;
		if (entry[0x43] == 0 && entry[0x41] != 0 && entry[0x42] == 0) {
			count++;
		}
	}

	gWmMenuWorkA = count;
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
	ChkMcDataCnt();
	DrawPageMark();
	if (gWmMenuWorkA > 0) {
		DrawMcWin(0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawHelpBase(int, float)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldState = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x82C)[0]);
	float alpha = 1.0f;

	if (worldState != 0) {
		const short state = *reinterpret_cast<short*>(worldState + 0x10);
		if (state == 0) {
			alpha = static_cast<float>(*reinterpret_cast<short*>(worldState + 0x22)) * 0.1f;
		} else if (state >= 3) {
			alpha = 1.0f - static_cast<float>(*reinterpret_cast<short*>(worldState + 0x22)) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
	DrawRect(0xFFFFFFFF, 0.0f, 0x1A8, 0x280, 0x18, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const worldObj = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x814)[0]);
	unsigned int* charaState = reinterpret_cast<unsigned int*>(bytes + 0x838);
	unsigned int animCounter = 0;

	for (int i = 0; i < 4; i++) {
		unsigned char* const panel = worldObj + 0x550 + i * 0x50;
		*reinterpret_cast<unsigned short*>(panel + 8) = static_cast<unsigned short>(FLOAT_80331470);

		const int y = static_cast<int>(FLOAT_80331478 + FLOAT_8033147c * static_cast<float>(animCounter) + FLOAT_80331474 - FLOAT_803314bc);
		*reinterpret_cast<unsigned short*>(panel + 0xA) = static_cast<unsigned short>(y);
		*reinterpret_cast<unsigned short*>(panel + 0xC) = 0x140;
		*reinterpret_cast<unsigned short*>(panel + 0xE) = 0xE0;
		*reinterpret_cast<float*>(panel + 0x10) = FLOAT_803313dc;
		*reinterpret_cast<float*>(panel + 0x14) = FLOAT_803313dc;
		*reinterpret_cast<float*>(panel + 0x18) = FLOAT_803313e8;

		unsigned int* const panelState = reinterpret_cast<unsigned int*>(panel);
		panelState[1]++;
		if (panelState[1] >= 30U) {
			panelState[1] = 0;
		}

		if (static_cast<int>(charaState[i * 0x12 + 2]) > 0) {
			panelState[0] = 1;
			panelState[7] = FLOAT_80331598;
			panelState[8] = FLOAT_803315cc;
			panelState[9] = FLOAT_803313dc;
			panelState[10] = FLOAT_8033174c;
			panelState[0xB] = panelState[0xB] + FLOAT_803314bc;
			panelState[0xD] = FLOAT_803315d0;
			panelState[0xE] = FLOAT_803315d0;
			panelState[0xF] = FLOAT_803315d0;
		} else {
			panelState[0] = 0;
		}

		animCounter++;
	}

	BindMcObj();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcObj()
{
	CalcMcObj();
	DrawMCList();
	DrawMcWin(-1, 0);
	DrawPageMark();
	DrawHelpBase(0, 1.0f);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMcList(int index, McListInfo* info)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	if (list == 0 || info == 0 || index < 0 || index >= kMcListCount) {
		return;
	}
	unsigned char* const dst = list + index * kMcListEntrySize;
	memcpy(dst, info, kMcListEntrySize);
	dst[0x43] = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McListInfo::operator= (const McListInfo& src)
{
	memcpy(this, &src, kMcListEntrySize);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrMcList()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const list = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x854)[0]);
	if (list != 0) {
		memset(list, 0, kMcListEntrySize * kMcListCount);
	}
	gWmMenuCursorX = 0xFF;
	uRam8032ee21 = 0xFF;
	gWmMenuCursorY = 0xFF;
	uRam8032ee25 = 0xFF;
	gWmMenuWorkA = 0;
	gWmMenuWorkB = 0;
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
unsigned int CMenuPcs::BindEffect(int slot, int effectNo, int cameraSlot)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (cameraSlot < 0) {
		cameraSlot = slot;
	}

	unsigned char* effect = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x840)[0] + slot * 0x524);
	if (slot == 5 && effectNo < 0x13) {
		effect += 0x524;
	} else if (slot > 0x10 && slot < 0x15 && effectNo > 0x19) {
		effect += 0x524;
	}

	*reinterpret_cast<unsigned int*>(effect + 0x0) = static_cast<unsigned int>(effectNo);
	*reinterpret_cast<unsigned int*>(effect + 0x8) = static_cast<unsigned int>(slot);
	Create__9CGBaseObjFv(effect + 0xC);
	*reinterpret_cast<unsigned int*>(effect + 0x104) = *reinterpret_cast<unsigned int*>(bytes + 0x4A8 + cameraSlot * 4);

	unsigned char createParam[0x88];
	*reinterpret_cast<unsigned int*>(createParam + 0x48) = 0xFFFFFFFF;
	*reinterpret_cast<unsigned int*>(createParam + 0x58) = 0xFFFFFFFF;
	createParam[0x54] = 0;
	createParam[0x53] = 1;
	*reinterpret_cast<unsigned int*>(createParam + 0x50) = 0;
	createParam[0x52] = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x4C) = 0x1E;
	*reinterpret_cast<unsigned int*>(createParam + 0x44) = 0;
	*reinterpret_cast<unsigned short*>(createParam + 0x40) = 0;
	createParam[0x3E] = 0;
	createParam[0x3D] = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x0) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x4) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x8) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0xC) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x10) = 0;
	*reinterpret_cast<void**>(createParam + 0x14) = 0;
	*reinterpret_cast<void**>(createParam + 0x18) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x1C) = 0;
	*reinterpret_cast<unsigned int*>(createParam + 0x20) = 0;
	*reinterpret_cast<float*>(createParam + 0x24) = FLOAT_803313e8;
	*reinterpret_cast<float*>(createParam + 0x28) = FLOAT_803313e8;
	createParam[0x2C] = 0;
	*reinterpret_cast<void**>(createParam + 0x74) = effect + 0xC;
	*reinterpret_cast<void**>(createParam + 0x70) = effect + 0xC;
	*reinterpret_cast<float*>(createParam + 0x64) = FLOAT_803313e8;
	*reinterpret_cast<float*>(createParam + 0x60) = FLOAT_803313e8;
	createParam[0x5C] = 0;

	const int group = ((effectNo ^ 100) >> 1) - ((((effectNo ^ 100) & effectNo)) >> 31);
	const unsigned int partId = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng, group, effectNo, createParam, 1);
	*reinterpret_cast<unsigned int*>(effect + 0x4) = partId;
	return partId;
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
	int localColor;
	int* const lightTable = DAT_8021082c + mode * 0xE;

	SetFog__8CGraphicFii(&Graphic, 1, 0);
	SetAmbient__9CLightPcsF8_GXColor(&LightPcs, &DAT_80210830[mode * 0xE]);
	SetNumDiffuse__9CLightPcsFUl(&LightPcs, static_cast<unsigned long>(lightTable[0]));

	for (int i = 0; i < lightTable[0]; i++) {
		localColor = lightTable[2 + i];
		SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs, static_cast<unsigned long>(i), &localColor, lightTable + 5 + i * 3, 0);
	}

	SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs, 0, 0, 0xFFFFFFFF);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawPageMark()
{
	int x;
	int y;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	SetTexture(static_cast<CMenuPcs::TEX>(0x2B));

	const unsigned char cur = bytes[0x14];
	const unsigned char max = bytes[0x15];
	for (unsigned int i = 0; i < max; i++) {
		const float px = 0x20 + static_cast<float>(i * 0x14);
		const float py = 0x1A0;
		const float tx = (i == cur) ? 0.0f : 16.0f;
		DrawRect(0xFFFFFFFF, px, py, 16.0f, 16.0f, tx, 0.0f, 1.0f, 1.0f, 0.0f);
	}

	GetMcAccessPos(&x, &y);
	if (x >= 0 && x < 0x280 && y >= 0 && y < 0x1C0) {
		DrawCursor(x, y, 1.0f);
	}
	GetMcOdekakePos(&x, &y);
	if (x >= 0 && x < 0x280 && y >= 0 && y < 0x1C0) {
		DrawCursor(x, y, 1.0f);
	}
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
void CMenuPcs::DrawRect2(unsigned long, float x, float y, float w, float h, float tx, float ty, float scale, float flags, float (*mtx)[4])
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

	const unsigned int drawFlags = static_cast<unsigned int>(flags);
	const float halfTexel = FLOAT_803314bc;
	float u0;
	float u1;
	float v0;
	float v1;

	if ((drawFlags & 8) == 0) {
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	} else {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	}

	if ((drawFlags & 4) == 0) {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
	} else {
		v1 = ty + halfTexel;
		v0 = (ty + h) - halfTexel;
	}

	if ((drawFlags & 1) != 0) {
		x = x - halfTexel * (w * scale);
	}
	if ((drawFlags & 2) != 0) {
		y = y - halfTexel * (h * scale);
	}

	Vec in[4];
	Vec out[4];

	in[0].x = x;
	in[0].y = y;
	in[0].z = 0.0f;

	in[1].x = x + (w * scale);
	in[1].y = y;
	in[1].z = 0.0f;

	in[2].x = x;
	in[2].y = y + (h * scale);
	in[2].z = 0.0f;

	in[3].x = x + (w * scale);
	in[3].y = y + (h * scale);
	in[3].z = 0.0f;

	if (mtx != 0) {
		PSMTXMultVecArray(reinterpret_cast<MtxPtr>(mtx), in, out, 4);
	} else {
		for (int i = 0; i < 4; i++) {
			out[i] = in[i];
		}
	}

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	GXPosition3f32(out[0].x, out[0].y, out[0].z);
	GXTexCoord2f32(u0, v0);

	GXPosition3f32(out[1].x, out[1].y, out[1].z);
	GXTexCoord2f32(u1, v0);

	GXPosition3f32(out[2].x, out[2].y, out[2].z);
	GXTexCoord2f32(u0, v1);

	GXPosition3f32(out[3].x, out[3].y, out[3].z);
	GXTexCoord2f32(u1, v1);
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
void CMenuPcs::DrawRect3d(unsigned long, float x, float y, float z, float w, float h, float tx, float ty, float scale, float flags)
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

	const unsigned int drawFlags = static_cast<unsigned int>(flags);
	const float halfTexel = FLOAT_803314bc;
	float u0;
	float u1;
	float v0;
	float v1;

	if ((drawFlags & 8) == 0) {
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	} else {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	}

	if ((drawFlags & 4) == 0) {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
	} else {
		v1 = ty + halfTexel;
		v0 = (ty + h) - halfTexel;
	}

	if ((drawFlags & 1) != 0) {
		x = x - halfTexel * (w * scale);
	}
	if ((drawFlags & 2) != 0) {
		y = y - halfTexel * (h * scale);
	}

	const float x1 = x + (w * scale);
	const float y1 = y + (h * scale);

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	GXPosition3f32(x, y, z);
	GXTexCoord2f32(u0, v0);

	GXPosition3f32(x1, y, z);
	GXTexCoord2f32(u1, v0);

	GXPosition3f32(x, y1, z);
	GXTexCoord2f32(u0, v1);

	GXPosition3f32(x1, y1, z);
	GXTexCoord2f32(u1, v1);
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
    short* const win = *reinterpret_cast<short**>(reinterpret_cast<unsigned char*>(this) + 0x848);

    win[0] = static_cast<short>(static_cast<int>(static_cast<float>(0x280 - x) * 0.5f));
    win[1] = static_cast<short>(static_cast<int>((FLOAT_80331430 - static_cast<float>(y)) * 0.5f));
    win[2] = static_cast<short>(x);
    win[3] = static_cast<short>(y);
    win[4] = 0;
    win[5] = 3;
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
void CMenuPcs::DrawMcWin(short state, short kind)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	short* const win = reinterpret_cast<short*>(reinterpret_cast<unsigned int*>(bytes + 0x848)[0]);
	if (win == 0) {
		return;
	}

	if (state >= 0 && win[5] != 3) {
		win[5] = state;
	}

	if (win[5] == 3) {
		return;
	}

	const float x = static_cast<float>(win[0]);
	const float y = static_cast<float>(win[1]);
	const float w = static_cast<float>(win[2]);
	const float h = static_cast<float>(win[3]);
	const float step = static_cast<float>(win[4]) / 6.0f;

	float sx = x;
	float sy = y;
	float sw = w;
	float sh = h;

	if (win[5] == 0) {
		sx += (w * 0.5f) * (1.0f - step);
		sy += (h * 0.5f) * (1.0f - step);
		sw *= step;
		sh *= step;
	} else if (win[5] == 2) {
		sx += (w * 0.5f) * step;
		sy += (h * 0.5f) * step;
		sw *= (1.0f - step);
		sh *= (1.0f - step);
	}

	if (sw <= 1.0f || sh <= 1.0f) {
		return;
	}

	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	const int cornerTex = (kind == 0) ? 0x2C : 0x24;
	const int edgeHTex = (kind == 0) ? 0x2D : 0x26;
	const int edgeVTex = (kind == 0) ? 0x2E : 0x25;
	const int fillTex = (kind == 0) ? 0x2F : 0x27;
	const float border = 16.0f;

	SetTexture(static_cast<CMenuPcs::TEX>(cornerTex));
	DrawRect(0xFFFFFFFF, sx, sy, border, border, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	DrawRect(0xFFFFFFFF, (sx + sw) - border, sy, border, border, 0.0f, 0.0f, 1.0f, 1.0f, 8.0f);
	DrawRect(0xFFFFFFFF, sx, (sy + sh) - border, border, border, 0.0f, 0.0f, 1.0f, 1.0f, 4.0f);
	DrawRect(0xFFFFFFFF, (sx + sw) - border, (sy + sh) - border, border, border, 0.0f, 0.0f, 1.0f, 1.0f, 12.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(edgeHTex));
	DrawRect(0xFFFFFFFF, sx + border, sy, sw - border * 2.0f, border, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	DrawRect(0xFFFFFFFF, sx + border, (sy + sh) - border, sw - border * 2.0f, border, 0.0f, 0.0f, 1.0f, 1.0f, 4.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(edgeVTex));
	DrawRect(0xFFFFFFFF, sx, sy + border, border, sh - border * 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	DrawRect(0xFFFFFFFF, (sx + sw) - border, sy + border, border, sh - border * 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 8.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(fillTex));
	DrawRect(0xFFFFFFFF, sx + border, sy + border, sw - border * 2.0f, sh - border * 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	DrawMcWinMess(win[5], kind);

	if (win[5] == 0) {
		win[4]++;
		if (win[4] >= 6) {
			win[4] = 6;
			win[5] = 1;
		}
	} else if (win[5] == 1) {
		win[4] = 6;
	} else if (win[5] == 2) {
		win[4]--;
		if (win[4] <= 0) {
			win[4] = 0;
			win[5] = 3;
		}
	}
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
void CMenuPcs::DrawMcWinMess(int winType, int messType)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	CFont* const font = reinterpret_cast<CFont**>(bytes + 0xF8)[0];
	short* const win = reinterpret_cast<short*>(reinterpret_cast<unsigned int*>(bytes + 0x848)[0]);
	if (font == 0 || win == 0) {
		return;
	}

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);
	font->DrawInit();

	GXColor textColor = {0xFF, 0xFF, 0xFF, 0xFF};
	font->SetColor(textColor);
	font->SetTlut(0x23);

	const int msgTable = GetMcWinMessBuff__8CMenuPcsFi(this, messType);
	const unsigned char* const winMess = reinterpret_cast<unsigned char*>(GetWinMess__8CMenuPcsFi(this, winType));
	if (msgTable == 0 || winMess == 0) {
		DrawInit__8CMenuPcsFv(this);
		return;
	}

	const int count = *reinterpret_cast<const int*>(winMess);
	float centerX = static_cast<float>(win[0] + win[2] / 2);
	float y = static_cast<float>(win[1] + 0x20);

	char textBuf[128];
	const unsigned char* entry = winMess + 4;
	for (int i = 0; i < count; i++) {
		const short msgId = *reinterpret_cast<const short*>(entry + 4);
		const char* text = *reinterpret_cast<const char**>(msgTable + msgId * 4);
		if (text != 0 && text[0] != '\0') {
			if (text[0] == '$') {
				text++;
			}

			strncpy(textBuf, text, sizeof(textBuf) - 1);
			textBuf[sizeof(textBuf) - 1] = '\0';

			const int textWidth = font->GetWidth(textBuf);
			float posX = static_cast<float>(win[0] + 0x20);
			if (winType != 0) {
				posX = centerX - static_cast<float>(textWidth) * 0.5f;
			}
			font->SetPosX(posX);
			font->SetPosY(y);
			font->Draw(textBuf);
		}
		y += 30.0f;
		entry += 8;
	}

	DrawInit__8CMenuPcsFv(this);
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
void CMenuPcs::GetWinSize(int winType, short* w, short* h, int messType)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	CFont* const font = *reinterpret_cast<CFont**>(bytes + 0xF8);

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);

	const int msgTable = GetMcWinMessBuff__8CMenuPcsFi(this, messType);
	const unsigned char* const winMess = reinterpret_cast<unsigned char*>(GetWinMess__8CMenuPcsFi(this, winType));
	const int count = *reinterpret_cast<const int*>(winMess);
	int maxWidth = 0;

	const unsigned char* entry = winMess + 4;
	for (int i = 0; i < count; i++) {
		const short msgId = *reinterpret_cast<const short*>(entry + 4);
		const char* text = *reinterpret_cast<const char**>(msgTable + msgId * 4);
		if (text != 0) {
			if (text[0] == '$') {
				text++;
			}
			const int textWidth = font->GetWidth(text);
			if (maxWidth < textWidth) {
				maxWidth = textWidth;
			}
		}
		entry += 8;
	}

	int cols = maxWidth / 0x16;
	if ((maxWidth % 0x16) != 0) {
		cols++;
	}

	if (w != 0) {
		*w = static_cast<short>((cols + 2) * 0x16 + 0x40);
	}
	if (h != 0) {
		*h = static_cast<short>(count * 0x1E + 0x40);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetTextureLoc(int index)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (index < 0) {
		index = 0;
	}
	if (index > 0xFF) {
		index = 0xFF;
	}
	bytes[0x86E] = static_cast<unsigned char>(index);
	SetTexture(static_cast<CMenuPcs::TEX>(index));
	gWmMenuWorkA = index;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
float CMenuPcs::GetMaxAnimWait()
{
	return FLOAT_8032ee18;
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* const effectBase = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x840)[0]);
	unsigned int* charaState = reinterpret_cast<unsigned int*>(bytes + 0x838);

	for (int i = 0; i < 4; i++) {
		unsigned int* const effectA = reinterpret_cast<unsigned int*>(effectBase + (i + 0x11) * 0x524);
		if (static_cast<int>(effectA[1]) >= 0) {
			pppDeletePart__8CPartMngFi(&PartMng, static_cast<int>(effectA[1]));
			effectA[1] = 0xFFFFFFFF;
			effectA[2] = 0xFFFFFFFF;
			effectA[0] = 0xFFFFFFFF;
		}

		unsigned int* const effectB = reinterpret_cast<unsigned int*>(effectBase + (i + 0x12) * 0x524);
		if (static_cast<int>(effectB[1]) >= 0) {
			pppDeletePart__8CPartMngFi(&PartMng, static_cast<int>(effectB[1]));
			effectB[1] = 0xFFFFFFFF;
			effectB[2] = 0xFFFFFFFF;
			effectB[0] = 0xFFFFFFFF;
		}
	}

	for (int i = 0; i < 4; i++) {
		const int modelNo = static_cast<int>(charaState[i * 0x12 + 3]);
		const int slot = i + 0x11;

		if (modelNo != 0) {
			BindEffect(slot, modelNo + 0x16, i);
		}

		const unsigned int flags = charaState[i * 0x12 + 0xA];
		int weaponModel = 0;
		if ((flags & 1) != 0) {
			weaponModel = 0;
		} else if ((flags & 2) != 0) {
			weaponModel = 1;
		} else if ((flags & 4) != 0) {
			weaponModel = 2;
		} else if ((flags & 8) != 0) {
			weaponModel = 3;
		} else if ((flags & 0x10) != 0) {
			weaponModel = 4;
		}

		BindEffect(slot, weaponModel + 0x1A, i);
	}
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
void CMenuPcs::DrawFilter(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SetAttrFmt(static_cast<CMenuPcs::FMT>(2));

	GXColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	SetTexture(static_cast<CMenuPcs::TEX>(-1));
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
	GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
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
	Game.LoadInit();
	MemoryCardMan.SetLoadData();
	Game.LoadFinished();
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
			gWmMenuWorkB = -2;
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

	gWmMenuWorkB = static_cast<int>(result);
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
int CMenuPcs::CheckSameMcFormatID(Mc::SaveDat* lhs, Mc::SaveDat* rhs)
{
	unsigned char* const a = reinterpret_cast<unsigned char*>(lhs);
	unsigned char* const b = reinterpret_cast<unsigned char*>(rhs);
	if (*reinterpret_cast<unsigned int*>(a + 0x13D4) != *reinterpret_cast<unsigned int*>(b + 0x13D4) ||
	    *reinterpret_cast<unsigned int*>(a + 0x13D0) != *reinterpret_cast<unsigned int*>(b + 0x13D0) ||
	    *reinterpret_cast<unsigned int*>(a + 0x13D8) != *reinterpret_cast<unsigned int*>(b + 0x13D8)) {
		return 0;
	}
	return 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::IsAsyncCharaLoadFinish()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int ready = 1;
	for (int i = 0; i < 4; i++) {
		if (reinterpret_cast<unsigned int*>(bytes + 0x7F4)[i] == 0) {
			ready = 0;
			break;
		}
	}
	if (ready != 0) {
		const unsigned char* const selectData = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int*>(bytes + 0x828)[0]);
		if (selectData != 0) {
			for (int i = 0; i < 4; i++) {
				if (selectData[i * 0x10 + 0xB] != 0 && selectData[i * 0x10 + 0xC] == 0) {
					ready = 0;
					break;
				}
			}
		}
	}
	gWmMenuWorkA = ready;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
McCtrl::McCtrl()
{
	Init();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
McCtrl::~McCtrl()
{
	return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800e9348
 * PAL Size: 1404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::LoadMcList()
{
	if (m_state < 0) {
		m_lastResult = -1;
		return;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MenuPcs.ClrMcList();
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
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
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
				m_lastResult = -3;
				return;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			if (m_lastResult == -4) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
				break;
			}
			if (m_lastResult == -5) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				m_lastResult = -4;
				return;
			}
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
		} else if (!MemoryCardMan.IsBrokenFile()) {
			m_state = 5;
		} else {
			const int closeResult = MemoryCardMan.McClose();
			if (closeResult == 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				for (int i = 0; i < kMcListCount; i++) {
					unsigned char entry[kMcListEntrySize];
					memset(entry, 0, sizeof(entry));
					entry[0x42] = 1;
					MenuPcs.SetMcList(i, reinterpret_cast<McListInfo*>(entry));
				}
				m_state = 7;
			} else {
				m_lastResult = closeResult;
				m_state = -1;
			}
		}
		break;

	case 5: {
		unsigned int serialLo = 0;
		unsigned int serialHi = 0;
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&serialLo)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			m_lastResult = -1;
			return;
		}
		m_serialHi = serialHi;
		m_serialLo = serialLo;
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				MemoryCardMan.DecodeData();
				const int iteration = m_iteration;
				m_iteration = iteration + 1;
				SetListDat(iteration, 0);
				if (m_iteration < 4) {
					m_state = 5;
				} else {
					const int closeResult = MemoryCardMan.McClose();
					if (closeResult == 0) {
						MemoryCardMan.McUnmount(m_cardChannel);
						MemoryCardMan.DestroyMcBuff();
						m_state = 7;
					} else {
						m_lastResult = closeResult;
						m_state = -1;
					}
				}
			}
		}
		break;
	}

	if (m_state == -1) {
		m_lastResult = -1;
	} else if (m_state == 7) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e902c
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetListDat(int slot, int)
{
	if (slot < 0 || slot >= kMcListCount) {
		return;
	}
	m_saveIndex = slot;

	unsigned char entry[kMcListEntrySize];
	memset(entry, 0, sizeof(entry));

	unsigned char* const save = reinterpret_cast<unsigned char*>(MemoryCardMan.m_saveBuffer);
	unsigned char hasData = 0;
	unsigned char hasError = 0;

	if (save == 0 || save[0x10C0] == 0) {
		hasData = 0;
		hasError = 0;
	} else {
		if (MemoryCardMan.ChkCrc(reinterpret_cast<Mc::SaveDat*>(save)) != 0) {
			unsigned int playTime = *reinterpret_cast<unsigned int*>(save + 0x20);
			memcpy(entry + 0x00, save + 0x8AD0, 8);
			memcpy(entry + 0x0C, save + 0x24, 0x0C);

			int party0 = *reinterpret_cast<int*>(save + 0x30);
			int party1 = *reinterpret_cast<int*>(save + 0x34);
			int party2 = *reinterpret_cast<int*>(save + 0x38);
			int party3 = *reinterpret_cast<int*>(save + 0x3C);

			if (party0 < 0 || party0 >= 8 || *reinterpret_cast<int*>(save + party0 * 0x9C0 + 0x1A84) == 0 || save[party0 * 0x9C0 + 0x1D90] != 0) {
				*reinterpret_cast<int*>(save + 0x30) = -1;
				party0 = -1;
			}
			if (party1 < 0 || party1 >= 8 || *reinterpret_cast<int*>(save + party1 * 0x9C0 + 0x1A84) == 0 || save[party1 * 0x9C0 + 0x1D90] != 0) {
				*reinterpret_cast<int*>(save + 0x34) = -1;
				party1 = -1;
			}
			if (party2 < 0 || party2 >= 8 || *reinterpret_cast<int*>(save + party2 * 0x9C0 + 0x1A84) == 0 || save[party2 * 0x9C0 + 0x1D90] != 0) {
				*reinterpret_cast<int*>(save + 0x38) = -1;
				party2 = -1;
			}
			if (party3 < 0 || party3 >= 8 || *reinterpret_cast<int*>(save + party3 * 0x9C0 + 0x1A84) == 0 || save[party3 * 0x9C0 + 0x1D90] != 0) {
				*reinterpret_cast<int*>(save + 0x3C) = -1;
				party3 = -1;
			}

			*reinterpret_cast<unsigned int*>(save + 0x1C) = MemoryCardMan.CalcCrc(reinterpret_cast<Mc::SaveDat*>(save));

			*reinterpret_cast<unsigned int*>(entry + 0x08) = playTime;
			*reinterpret_cast<unsigned int*>(entry + 0x18) = (party0 < 0) ? 0xFFFFFFFFu : *reinterpret_cast<unsigned short*>(save + party0 * 0x9C0 + 0x14D0);
			*reinterpret_cast<unsigned int*>(entry + 0x1C) = (party1 < 0) ? 0xFFFFFFFFu : *reinterpret_cast<unsigned short*>(save + party1 * 0x9C0 + 0x14D0);
			*reinterpret_cast<unsigned int*>(entry + 0x20) = (party2 < 0) ? 0xFFFFFFFFu : *reinterpret_cast<unsigned short*>(save + party2 * 0x9C0 + 0x14D0);
			*reinterpret_cast<unsigned int*>(entry + 0x24) = (party3 < 0) ? 0xFFFFFFFFu : *reinterpret_cast<unsigned short*>(save + party3 * 0x9C0 + 0x14D0);
			*reinterpret_cast<unsigned int*>(entry + 0x28) = *reinterpret_cast<unsigned int*>(save + 0xB8);
			memcpy(entry + 0x2C, save + 0x10C0, 0x15);
			hasData = 1;
		} else {
			hasError = 1;
		}
	}

	entry[0x41] = hasData;
	entry[0x42] = hasError;
	entry[0x43] = 0;
	MenuPcs.SetMcList(slot, reinterpret_cast<McListInfo*>(entry));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetBrokenFile(int isBroken)
{
	m_createFlag = isBroken;
	if (isBroken != 0) {
		m_lastResult = -1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e8738
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SaveDat()
{
	if (m_state < 0) {
		m_lastResult = -1;
		return;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
				m_lastResult = -3;
				return;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			m_lastResult = -4;
			return;
		} else if (!MemoryCardMan.IsBrokenFile()) {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		} else {
			m_state = 8;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
				for (int i = 0; i < kMcListCount; i++) {
					unsigned char entry[kMcListEntrySize];
					memset(entry, 0, sizeof(entry));
					MenuPcs.SetMcList(i, reinterpret_cast<McListInfo*>(entry));
				}
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult == 0) {
			m_state = 0x0D;
		} else {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				m_lastResult = -4;
				return;
			}
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult == 0) {
			m_state = 0x12;
		} else {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				m_lastResult = -4;
				return;
			}
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else if (m_iteration < 4) {
				m_state = 0x10;
			} else {
				m_state = 0x0C;
			}
		}
		break;

	case 0x12: {
		unsigned int serialLo = 0;
		unsigned int serialHi = 0;
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&serialLo)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			m_lastResult = -1;
			return;
		}
		m_serialHi = serialHi;
		m_serialLo = serialLo;
		MemoryCardMan.CreateMcBuff();
		if (m_userBuffer == 0) {
			MemoryCardMan.MakeSaveData();
		} else {
			memcpy(MemoryCardMan.m_saveBuffer, m_userBuffer, 0x8BD0);
		}
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x13;
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					m_lastResult = -4;
					return;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj();
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (closeResult == 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			} else {
				m_lastResult = closeResult;
				m_state = -1;
			}
		}
		break;
	}

	if (m_state == -1) {
		m_lastResult = -1;
	} else if (m_state == 0x14) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e8300
 * PAL Size: 1080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::LoadDat()
{
	if (m_state < 0) {
		m_lastResult = -1;
		return;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
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
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
				m_lastResult = -3;
				return;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			if (m_lastResult == -4) {
				m_state = 7;
			} else if (m_lastResult == -5) {
				m_state = -1;
				m_lastResult = -4;
				return;
			} else {
				m_state = -1;
			}
		} else {
			m_state = 5;
		}
		break;

	case 5: {
		unsigned int serialLo = 0;
		unsigned int serialHi = 0;
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&serialLo)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			m_lastResult = -1;
			return;
		}
		m_serialHi = serialHi;
		m_serialLo = serialLo;
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				MemoryCardMan.DecodeData();
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				if (m_userBuffer == 0) {
					Game.LoadInit();
					MemoryCardMan.SetLoadData();
					Game.LoadFinished();
				} else {
					memcpy(m_userBuffer, MemoryCardMan.m_saveBuffer, 0x8BD0);
					MemoryCardMan.CalcSaveDatHpMax(reinterpret_cast<Mc::SaveDat*>(m_userBuffer));
				}
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
			}
		}
		break;
	}

	if (m_state == -1) {
		m_lastResult = -1;
	} else if (m_state == 7) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e80f0
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::Format(int unmountAfter)
{
	if (m_state < 0) {
		m_lastResult = -1;
		return;
	}

	m_previousState = m_state;

	if (m_state == 2) {
		MemoryCardMan.McFormat(m_cardChannel);
		m_state = 3;
	} else if (m_state < 2) {
		if (m_state == 0) {
			MemoryCardMan.McMount(m_cardChannel);
			m_lastResult = MemoryCardMan.GetResult();
			m_state = 1;
			m_iteration = 0;
		} else if (m_state > -1 && MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult == -6 || m_lastResult == -0xD || m_lastResult == 0) {
				m_state = 2;
			} else {
				if (m_lastResult == -5) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
					m_state = -1;
					m_lastResult = -2;
					return;
				}
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				m_state = -1;
			}
		}
	} else if (m_state != 4 && m_state < 4 && MemoryCardMan.AsyncFinished() == 1) {
		m_lastResult = MemoryCardMan.GetResult();
		if (m_lastResult < 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				m_lastResult = -2;
				return;
			}
		} else {
			if (unmountAfter != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
			}
			m_state = 4;
		}
	}

	if (m_state == -1) {
		m_lastResult = -1;
	} else if (m_state == 4) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e7dc8
 * PAL Size: 808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800e7d4c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x800e78f8
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

					if ((*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D4) == Game.m_gameWork.m_mcSerial1 &&
						 *(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D0) == Game.m_gameWork.m_mcSerial0) &&
						(*(unsigned int*)(MemoryCardMan.m_saveBuffer + 0x13D8) == Game.m_gameWork.m_mcRandom))
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
 * PAL Address: 0x800e7430
 * PAL Size: 1224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SaveDataBuffer(char* buffer)
{
	unsigned int serialLo = 0;
	unsigned int serialHi = 0;

	m_userBuffer = buffer;

	if (m_state < 0) {
		m_lastResult = -1000;
		return;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0xD) {
					m_state = -1;
					m_lastResult = -13;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -5;
					return;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
			} else {
				m_state = 7;
			}
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			m_lastResult = -4;
			return;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			m_lastResult = -5;
			return;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x10;
		}
		break;

	case 0x10: {
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&serialLo)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			m_lastResult = -999;
			break;
		}

		m_serialLo = serialLo;
		m_serialHi = serialHi;

		unsigned char* const save = reinterpret_cast<unsigned char*>(MemoryCardMan.m_saveBuffer);
		if (save == 0 || m_userBuffer == 0) {
			m_state = -1;
			m_lastResult = -999;
			break;
		}

		memcpy(save, m_userBuffer, 0x8BD0);

		int member = *reinterpret_cast<int*>(save + 0x30);
		if (member < 0 || member >= 8 || *reinterpret_cast<int*>(save + member * 0x9C0 + 0x1A84) == 0 || save[member * 0x9C0 + 0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x30) = -1;
		}
		member = *reinterpret_cast<int*>(save + 0x34);
		if (member < 0 || member >= 8 || *reinterpret_cast<int*>(save + member * 0x9C0 + 0x1A84) == 0 || save[member * 0x9C0 + 0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x34) = -1;
		}
		member = *reinterpret_cast<int*>(save + 0x38);
		if (member < 0 || member >= 8 || *reinterpret_cast<int*>(save + member * 0x9C0 + 0x1A84) == 0 || save[member * 0x9C0 + 0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x38) = -1;
		}
		member = *reinterpret_cast<int*>(save + 0x3C);
		if (member < 0 || member >= 8 || *reinterpret_cast<int*>(save + member * 0x9C0 + 0x1A84) == 0 || save[member * 0x9C0 + 0x1D90] != 0) {
			*reinterpret_cast<int*>(save + 0x3C) = -1;
		}

		*reinterpret_cast<unsigned int*>(save + 0x1C) = MemoryCardMan.CalcCrc(reinterpret_cast<Mc::SaveDat*>(save));
		MemoryCardMan.EncodeData();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x11;
		break;
	}

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					m_lastResult = -5;
					return;
				}
			} else {
				m_state = 0x12;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (closeResult == 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			} else {
				m_lastResult = closeResult;
				m_state = -1;
			}
		}
		break;
	}

	if (m_state == -1) {
		m_lastResult = -999;
	} else if (m_state == 0x12) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::ChkParty(char*)
{
	m_lastResult = 0;
	if (m_userBuffer == 0) {
		return;
	}

	unsigned char* const save = reinterpret_cast<unsigned char*>(m_userBuffer);
	for (int i = 0; i < 4; i++) {
		const int party = *reinterpret_cast<int*>(save + 0x30 + i * 4);
		if (party >= 0 && party < 8 && *reinterpret_cast<int*>(save + party * 0x9C0 + 0x1A84) != 0 && save[party * 0x9C0 + 0x1D90] == 0) {
			m_lastResult++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e6b98
 * PAL Size: 2200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::EraseDat()
{
	if (m_state < 0) {
		m_lastResult = -1;
		return;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
				m_lastResult = -3;
				return;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			m_lastResult = -4;
			return;
		} else if (!MemoryCardMan.IsBrokenFile()) {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		} else {
			m_state = 8;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					m_lastResult = -2;
					return;
				} else if (m_lastResult == -5) {
					m_state = -1;
					m_lastResult = -4;
					return;
				} else {
					m_state = -1;
				}
			} else {
				for (int i = 0; i < kMcListCount; i++) {
					unsigned char entry[kMcListEntrySize];
					memset(entry, 0, sizeof(entry));
					MenuPcs.SetMcList(i, reinterpret_cast<McListInfo*>(entry));
				}
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult == 0) {
			m_state = 0x0D;
		} else {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				m_lastResult = -4;
				return;
			}
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult == 0) {
			m_state = 0x12;
		} else {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				m_lastResult = -4;
				return;
			}
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					m_lastResult = -4;
					return;
				}
			} else {
				const int finishedSlot = m_iteration - 1;
				SetListDat(finishedSlot, 1);
				MenuPcs.BindMcObj();
				if (m_iteration < 4) {
					m_state = 0x10;
				} else {
					m_state = 0x0C;
				}
			}
		}
		break;

	case 0x12: {
		unsigned int serialLo = 0;
		unsigned int serialHi = 0;
		if (CARDGetSerialNo(m_cardChannel, reinterpret_cast<unsigned long long*>(&serialLo)) != 0) {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			m_lastResult = -1;
			return;
		}
		m_serialHi = serialHi;
		m_serialLo = serialLo;
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x13;
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					m_lastResult = -4;
					return;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj();
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
			if (closeResult == 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			} else {
				m_lastResult = closeResult;
				m_state = -1;
			}
		}
		break;
	}

	if (m_state == -1) {
		m_lastResult = -1;
	} else if (m_state == 0x14) {
		m_lastResult = 1;
	} else {
		m_lastResult = 0;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetDno()
{
	gWmMenuWorkA = m_cardChannel;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetSerial()
{
	gWmMenuWorkA = static_cast<int>(m_serialLo);
	gWmMenuWorkB = static_cast<int>(m_serialHi);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDataBuff(char* buffer)
{
	m_userBuffer = buffer;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::GetSlot()
{
	gWmMenuWorkA = m_saveIndex;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDno(int channel)
{
	m_cardChannel = channel;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetSlot(int slot)
{
	m_saveIndex = slot;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaNormal()
{
	FLOAT_8032ee18 = FLOAT_803313dc;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaAdd()
{
	FLOAT_8032ee18 = FLOAT_803315d4;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetFontWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	gWmMenuWorkA = static_cast<int>(reinterpret_cast<unsigned int*>(bytes + 0xFC)[0]);
}
