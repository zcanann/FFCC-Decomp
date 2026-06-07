#include "ffcc/bonus_menu.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/mes.h"
#include "ffcc/pad.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include "ffcc/wind.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

extern char lbl_801DD5D4[];
extern const double kPppCrystal2RefractionScale;
extern const float FLOAT_80331EAC;
extern const float FLOAT_80331EB0;
extern const float FLOAT_80331ED0;
extern const float FLOAT_80331F00;
extern const float FLOAT_80331F04;
extern const double DOUBLE_80331F08;
extern const float FLOAT_80331F10;
extern const float FLOAT_80331F14;
extern const float FLOAT_80331F18;
extern const double DOUBLE_80331F20;
extern const float FLOAT_80331F28;
extern const float FLOAT_80331F2C;
extern const float FLOAT_80331F6C;
extern const float FLOAT_80331FB8;
extern const float FLOAT_80331FBC;
extern const float s_BonusModelYPos[];
extern const float s_BonusModelScale[];

static float s_BallTrnsXspl[] = {
    0.03333299979567528f, 27.700000762939453f, 0.0f, 0.0f,
    0.23524600267410278f, 12.29898452758789f, -55.570411682128906f, -55.570411682128906f,
    0.3703629970550537f, 6.334517955780029f, -25.889270782470703f, -25.889270782470703f,
    1.0f, -14.300000190734863f, 0.0f, 0.0f,
};

static float s_BallTrnsYspl[] = {
    0.03333299979567528f, 8.5f, 0.0f, 0.0f,
    0.241907000541687f, -1.2000000476837158f, 0.0f, 0.0f,
    0.3153750002384186f, 1.6390860080718994f, 0.0f, 0.0f,
    0.3817799985408783f, -1.2000000476837158f, 0.0f, 0.0f,
    1.0f, -1.2000000476837158f, 0.0f, 0.0f,
    1.3333330154418945f, 0.30000001192092896f, 0.0f, 0.0f,
};

static CMenuPcs::FCV s_BallTrnsX = {4, s_BallTrnsXspl};
static CMenuPcs::FCV s_BallTrnsY = {6, s_BallTrnsYspl};

extern const char s_bonus_80331DE0[] = "bonus";
extern const char s_bonus1_80331DE8[] = "bonus1";
extern const char s_bonus2_80331DF0[] = "bonus2";
extern const char s_bonus3_80331DF8[] = "bonus3";
extern const char s_bonus4_80331E00[] = "bonus4";
extern const char s_bonus5_80331E08[] = "bonus5";
extern const char s_bonus6_80331E10[] = "bonus6";
extern const char s_bonus7_80331E18[] = "bonus7";
extern const char s_bonus8_80331E20[] = "bonus8";
extern const char s_bonus9_80331E28[] = "bonus9";
extern const char s_bonus10_80331E30[] = "bonus10";
extern const char s_bonus11_80331E38[] = "bonus11";
extern const char s_bonus12_80331E40[] = "bonus12";
extern const char s_bonus13_80331E48[] = "bonus13";
extern const char s_bonus14_80331E50[] = "bonus14";
extern const char s_bonus15_80331E58[] = "bonus15";
extern const char s_bonus16_80331E60[] = "bonus16";
extern const char s_bonus17_80331E68[] = "bonus17";
extern const char s_bonus18_80331E70[] = "bonus18";

char* PTR_s_bonus[] = {
    const_cast<char*>(s_bonus_80331DE0),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

CMenuPcs::CTmp s_bonusTextureTable[] = {
    {2, const_cast<char*>(s_bonus1_80331DE8)},
    {2, const_cast<char*>(s_bonus2_80331DF0)},
    {2, const_cast<char*>(s_bonus3_80331DF8)},
    {2, const_cast<char*>(s_bonus4_80331E00)},
    {2, const_cast<char*>(s_bonus5_80331E08)},
    {2, const_cast<char*>(s_bonus6_80331E10)},
    {2, const_cast<char*>(s_bonus7_80331E18)},
    {2, const_cast<char*>(s_bonus8_80331E20)},
    {2, const_cast<char*>(s_bonus9_80331E28)},
    {2, const_cast<char*>(s_bonus10_80331E30)},
    {2, const_cast<char*>(s_bonus11_80331E38)},
    {2, const_cast<char*>(s_bonus12_80331E40)},
    {2, const_cast<char*>(s_bonus13_80331E48)},
    {2, const_cast<char*>(s_bonus14_80331E50)},
    {2, const_cast<char*>(s_bonus15_80331E58)},
    {2, const_cast<char*>(s_bonus16_80331E60)},
    {2, const_cast<char*>(s_bonus17_80331E68)},
    {2, const_cast<char*>(s_bonus18_80331E70)},
};

struct BonusPartySummary {
	int m_partySlot;
	CCharaPcs::CHandle* m_partyHandle;
	int m_bonusCondition;
	int m_totalValue;
	int m_foodValue;
	int m_artifactValue;
	int m_rank;
	unsigned int m_ownedArtifactMask;
	int m_selectedItemId;
	int m_selectedSlot;
	unsigned int m_tribeId;
};

STATIC_ASSERT(sizeof(BonusPartySummary) == 0x2C);

struct BonusSummaryData {
	int m_partyCount;
	int m_winnerTotalValue;
	unsigned char pad_0008;
	unsigned char m_missingArtifactMask;
	short m_tempArtifacts[4];
	short m_bossArtifacts[4];
	short pad_001A;
	BonusPartySummary m_party[4];
};

STATIC_ASSERT(sizeof(BonusSummaryData) == 0xCC);

static BonusSummaryData* s_Rinfo = 0;
static unsigned char s_CntTop = 0;
static unsigned char s_ArtiTop = 0;
static unsigned char s_PlayerTop = 0;
static float* s_Base[1];
extern "C" const char sDrawBonusFmt[16] = {
    'd', 'r', 'a', 'w', ' ', 'B', 'o', 'n', 'u', 's', ' ', '(', '%', 'd', ')', '\n',
};
extern "C" const char s_bonus_menu_cpp[];
extern "C" const char s_bonusAllocErrorFmt[];

namespace {

struct BonusAnimHeader {
	short count;
	short unk02;
	short unk04;
	short finished;
};

struct BonusAnimSprite {
	short x;
	short y;
	short w;
	short h;
	float mulX;
	float mulY;
	float alpha;
	float depth;
	int tex;
	int kind;
	int timer;
	int startFrame;
	int duration;
	float scale;
	float motionX;
	float motionY;
	float targetX;
	float targetY;
};

struct BonusAnimList {
	BonusAnimHeader header;
	BonusAnimSprite sprites[64];
};

STATIC_ASSERT(sizeof(BonusAnimHeader) == 8);
STATIC_ASSERT(sizeof(BonusAnimSprite) == 0x40);
STATIC_ASSERT(sizeof(BonusAnimList) == 0x1008);

struct BonusMenuStateRaw {
	unsigned char bytes[0x48];
};

struct BonusBaseRaw {
	float values[18];
};

struct BonusBoardEntryList {
	MenuBoardEntry entries[0x18];
};

struct BonusEffectSlotBlock {
	unsigned char bytes[0x2920];
};

struct BonusEffectSlotList {
	BonusEffectSlotBlock slots[5];
	unsigned char pad_CDA0[0x10];
};

STATIC_ASSERT(sizeof(BonusMenuStateRaw) == 0x48);
STATIC_ASSERT(sizeof(BonusBaseRaw) == 0x48);
STATIC_ASSERT(sizeof(BonusBoardEntryList) == 0x780);
STATIC_ASSERT(sizeof(BonusEffectSlotBlock) == 0x2920);
STATIC_ASSERT(sizeof(BonusEffectSlotList) == 0xCDB0);

static inline void InitBonusEffectSlots(CMenuPcs* menu)
{
	int base = 0;
	for (int i = 0; i < 5; i++) {
		*(int*)(menu->m_bonusListPtr + base + 0x000) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x004) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x008) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x524) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x528) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x52C) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xA48) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xA4C) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xA50) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xF6C) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xF70) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0xF74) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1490) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1494) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1498) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x19B4) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x19B8) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x19BC) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1ED8) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1EDC) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x1EE0) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x23FC) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x2400) = -1;
		*(int*)(menu->m_bonusListPtr + base + 0x2404) = -1;
		base += 0x2920;
	}
}

static inline void InitBonusBoardEntry(MenuBoardEntry* entry)
{
	entry->m_modelHandle = 0;
	entry->m_effectHandle = 0;
	entry->m_centerX = 0;
	entry->m_centerY = 0;
	entry->m_width = 0x280;
	entry->m_height = 0x1C0;
	entry->m_posX = 0.0f;
	entry->m_posY = 0.0f;
	entry->m_depth = 1000.0f;
	entry->m_rotX = 0.0f;
	entry->m_rotY = 0.0f;
	entry->m_rotZ = 0.0f;
	entry->m_scaleX = 1.0f;
	entry->m_scaleY = 1.0f;
	entry->m_scaleZ = 1.0f;
	entry->m_screenX = 0;
	entry->m_screenY = 0;
	entry->m_screenWidth = 0x280;
	entry->m_screenHeight = 0x1C0;
}

static inline void ReleaseBonusRefObject(void* object)
{
	CRef* ref = reinterpret_cast<CRef*>(object);
	if (ref->DecRef() == 0) {
		delete ref;
	}
}

static inline float CalcBonusSpriteProgress(const BonusAnimSprite* sprite, int frame);
static inline float ClampBonusUnit(float value);
static const char* GetBonusPartyNameByActiveIndex(int activeIndex);
static CCaravanWork* GetBonusActiveCaravanByActiveIndex(int activeIndex);
static int GetBonusResultValueByActiveIndex(int activeIndex);
static const char* GetBonusResultLabelByActiveIndex(int activeIndex);

static inline BonusSummaryData* GetBonusSummaryData()
{
	return s_Rinfo;
}

static inline BonusPartySummary* GetBonusPartySummary(int activeIndex)
{
	if (s_Rinfo == 0 || activeIndex < 0 || activeIndex >= s_Rinfo->m_partyCount) {
		return 0;
	}

	return &s_Rinfo->m_party[activeIndex];
}

static inline CMemory::CStage* GetBonusAllocStage(CMenuPcs* menu)
{
	return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(menu) + 0xEC);
}

static inline CCharaPcs::CHandle** GetBonusDisplayHandleSlots(CMenuPcs* menu)
{
	return menu->m_wm.m_handles;
}

static inline MenuBoardEntry* GetBonusBoardEntries(CMenuPcs* menu)
{
	return reinterpret_cast<MenuBoardEntry*>(menu->m_bonus.m_bonusBoardPtr);
}

static inline void InitAnimSprite(BonusAnimSprite* sprite, int kind, short x, short y, short w, short h, int startFrame, int duration)
{
	sprite->x = x;
	sprite->y = y;
	sprite->w = w;
	sprite->h = h;
	sprite->mulX = 0.0f;
	sprite->mulY = 0.0f;
	sprite->alpha = 1.0f;
	sprite->depth = 0.0f;
	sprite->tex = kind;
	sprite->kind = kind;
	sprite->timer = 0;
	sprite->startFrame = startFrame;
	sprite->duration = duration;
	sprite->scale = 1.0f;
}

static inline void ResetAnimSpriteMotion(BonusAnimSprite* sprite)
{
	sprite->mulX = 0.0f;
	sprite->mulY = 0.0f;
	sprite->alpha = 0.0f;
	sprite->depth = 0.0f;
	sprite->scale = 1.0f;
}

static inline int& BonusSpriteFlags(BonusAnimSprite* sprite)
{
	return *reinterpret_cast<int*>(&sprite->scale);
}

static inline void InitSelectOpenPartyIcon(BonusAnimSprite* sprite, int slotIndex, short y)
{
	short x = ((1 <= slotIndex) && (slotIndex <= 2)) ? 0x30 : 0x48;

	InitAnimSprite(sprite, 0, x, y, 0x60, 0x58, 0, 8);
	ResetAnimSpriteMotion(sprite);
	sprite->mulX = (float)sprite->w;
	sprite->mulY = (float)sprite->h;
	sprite->depth = 1.0f;
	sprite->motionX = 100.0f;
	sprite->motionY = 0.0f;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
	BonusSpriteFlags(sprite) = 1;
}

static inline void InitSelectOpenPartyName(BonusAnimSprite* sprite, const BonusAnimSprite* iconSprite, short xOffset, short yOffset, int startFrame)
{
	InitAnimSprite(sprite, -1, (short)(iconSprite->x + xOffset), (short)(iconSprite->y + yOffset), 0, 0, startFrame, 8);
	ResetAnimSpriteMotion(sprite);
	sprite->mulX = 24.0f;
	sprite->depth = 1.0f;
	sprite->motionX = 100.0f;
	sprite->motionY = 0.0f;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
	BonusSpriteFlags(sprite) = 1;
}

static inline void SetupSelectCloseSpriteMotion(BonusAnimSprite* sprite)
{
	sprite->timer = 0;
	sprite->startFrame = 0;
	sprite->duration = 8;
	sprite->x = (short)(int)sprite->targetX;
	sprite->y = (short)(int)sprite->targetY;
	sprite->motionX = 100.0f;
	sprite->motionY = 0.0f;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
}

static inline void DrawBonusActiveMarks(CMenuPcs* menu, int statePtr, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));

	unsigned int activeMask = 0;
	for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
		int selection = s_Rinfo->m_party[i].m_selectedSlot;
		if (selection >= 0) {
			activeMask |= 1 << selection;
		}
	}

	for (int i = 0; i < 8; i++) {
		if ((activeMask & (1 << i)) == 0) {
			continue;
		}
		float x = s_Base[0][i * 2 + 2] + 28.0f;
		float y = s_Base[0][i * 2 + 3] + 20.0f;
		MenuPcs.DrawRect(0, x, y, 56.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

static inline int GetBonusUnavailableMask(int statePtr, BonusPartySummary* summary)
{
	return (int)(signed char)(*(unsigned char*)(statePtr + 9) | s_Rinfo->m_missingArtifactMask) | summary->m_ownedArtifactMask;
}

static inline void DrawBonusPartyNames(CMenuPcs* menu, BonusAnimHeader* header, BonusAnimSprite* sprites)
{
	CFont* font = menu->m_fonts[0];
	int activePartyCount = s_Rinfo->m_partyCount;

	menu->DrawInit();
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.7300000190734863f);
	font->SetTlut(7);
	font->DrawInit();

	int nameIndex = 0;
	for (int i = 0; i < (int)header->count && nameIndex < activePartyCount; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->kind != -1) {
			continue;
		}

		char name[260];
		for (int j = 0; j < activePartyCount; j++) {
			if (s_Rinfo->m_party[j].m_rank == nameIndex) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[j].m_partySlot]);
				strcpy(name, reinterpret_cast<const char*>(caravanWork->m_name));
				break;
			}
		}
		CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f));
		font->SetColor(color.color);
		font->SetPosX((float)sprite->x + sprite->motionX);
		font->SetPosY((float)sprite->y + sprite->motionY - 12.0f);
		font->Draw(name);
		nameIndex++;
	}
}

static inline void DrawBonusMcWinOverlay(CMenuPcs* menu, int statePtr)
{
	MenuWindowInfo* window = menu->m_menuWindowInfo;

	menu->DrawInit();
	if (window->state == 3) {
		return;
	}

	menu->DrawMcWin(-1, 1);
	if (window->state == 1) {
		menu->DrawMcWinMess(0x18, 1);
		menu->DrawInit();
		int cursorX = menu->GetYesNoXPos((int)*(short*)(statePtr + 0x28));
		float cursorY = (float)(window->y + window->height - 0x3e);
		menu->DrawCursor(cursorX, (int)cursorY, 1.0f);
	}
}

static inline void DrawBonusSelectedArtifactHelp(CMenuPcs* menu, int statePtr, BonusAnimHeader* header, BonusAnimSprite* sprites)
{
	if (*(short*)(statePtr + 0x1c) != 4) {
		return;
	}

	int selection = (int)*(short*)(statePtr + 0x26);
	short* rewardItems = &s_Rinfo->m_tempArtifacts[0];
	if (rewardItems[selection] <= 0) {
		return;
	}

	BonusAnimSprite* frame = 0;
	for (int i = 0; i < (int)header->count; i++) {
		if (sprites[i].kind == -3) {
			frame = &sprites[i];
			break;
		}
	}

	CFont* font = menu->m_fonts[1];
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScaleX(0.7200000286102295f);
	font->SetScaleY(0.8999999761581421f);
	font->DrawInit();
	CColor color(0xFF, 0xFF, 0xFF, 0xFF);
	font->SetColor(color.color);

	int itemId = (int)rewardItems[selection];
	char* title = Game.m_cFlatDataArr[1].TableStrings(0)[itemId * 5 + 4];
	float centerX = (float)((double)frame->x + (double)(float)frame->w * 0.5);
	float centerY = (float)((double)frame->y + (double)(float)frame->h * 0.5);
	font->SetPosX((float)-((double)font->GetWidth(title) * 0.5 - (double)centerX));
	font->SetPosY(centerY - 44.0f - 4.0f);
	font->Draw(title);

	char* source = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xA9C) char[0x200];
	if ((source == 0) && (System.m_execParam != 0)) {
		System.Printf(const_cast<char*>(s_bonusAllocErrorFmt), const_cast<char*>(s_bonus_menu_cpp), 0xA9F);
	}
	memset(source, 0, 0x200);
	char* converted = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xAA5) char[0x200];
	if ((converted == 0) && (System.m_execParam != 0)) {
		System.Printf(const_cast<char*>(s_bonusAllocErrorFmt), const_cast<char*>(s_bonus_menu_cpp), 0xAA8);
	}
	memset(converted, 0, 0x200);
	strcpy(source, Game.m_cFlatDataArr[1].TableStrings(6)[itemId]);
	CMes::MakeAgbString(converted, source, 0, 0);
	strlen(converted);

	float lineY = centerY - 11.0f - 7.0f;
	for (int line = 0;; line++) {
		char* text = (line == 0) ? strtok(converted, "\n") : strtok(0, "\n");
		if (text == 0) {
			break;
		}
		font->SetPosX((float)-((double)font->GetWidth(text) * 0.5 - (double)centerX));
		font->SetPosY(lineY - 4.0f);
		font->Draw(text);
		lineY += 22.0f;
	}

	delete[] source;
	delete[] converted;
}

static inline float ClampBonusUnit(float value)
{
	if (value < 0.0f) {
		return 0.0f;
	}
	if (value > 1.0f) {
		return 1.0f;
	}
	return value;
}

static inline float CalcBonusSpriteProgress(const BonusAnimSprite* sprite, int frame)
{
	if (frame < sprite->startFrame) {
		return -1.0f;
	}
	if (sprite->duration <= 0) {
		return 1.0f;
	}

	return ClampBonusUnit((float)(frame - sprite->startFrame + 1) / (float)sprite->duration);
}

static inline int GetBonusPartySlotByActiveIndex(int activeIndex)
{
	unsigned int* scriptFoodBase = Game.m_scriptFoodBase;
	int activeCount = 0;

	for (int i = 0; i < 4; i++) {
		if (scriptFoodBase[i] == 0) {
			continue;
		}
		if (activeCount == activeIndex) {
			return i;
		}
		activeCount++;
	}

	return -1;
}

static inline CCaravanWork* GetBonusActiveCaravanByActiveIndex(int activeIndex)
{
	BonusPartySummary* summary = GetBonusPartySummary(activeIndex);
	if (summary != 0 && summary->m_partySlot >= 0 && summary->m_partySlot < 4) {
		return reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[summary->m_partySlot]);
	}

	int slot = GetBonusPartySlotByActiveIndex(activeIndex);
	if (slot < 0) {
		return 0;
	}

	return reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[slot]);
}

static inline const char* GetBonusPartyNameByActiveIndex(int activeIndex)
{
	CCaravanWork* caravanWork = GetBonusActiveCaravanByActiveIndex(activeIndex);
	if (caravanWork == 0) {
		return 0;
	}

	return reinterpret_cast<const char*>(caravanWork->m_name);
}

static inline int GetBonusResultValueByActiveIndex(int activeIndex)
{
	BonusPartySummary* summary = GetBonusPartySummary(activeIndex);
	if (summary != 0) {
		if (summary->m_totalValue < 0) {
			return 0;
		}
		if (summary->m_totalValue > 999) {
			return 999;
		}
		return summary->m_totalValue;
	}

	CCaravanWork* caravanWork = GetBonusActiveCaravanByActiveIndex(activeIndex);
	if (caravanWork == 0) {
		return 0;
	}

	int value = (int)caravanWork->m_bonusCondition;
	if (value < 0) {
		return 0;
	}
	if (value > 999) {
		return 999;
	}
	return value;
}

static inline const char* GetBonusResultLabelByActiveIndex(int activeIndex)
{
	int labelIndex = -1;
	BonusPartySummary* summary = GetBonusPartySummary(activeIndex);
	if (summary != 0) {
		labelIndex = summary->m_bonusCondition * 2 + 1;
	} else {
		CCaravanWork* caravanWork = GetBonusActiveCaravanByActiveIndex(activeIndex);
		if (caravanWork == 0) {
			return 0;
		}
		labelIndex = (int)caravanWork->m_bonusCondition * 2 + 1;
	}

	if (labelIndex < 0) {
		return 0;
	}

	if (Game.m_cFlatDataArr[1].TableStrings(7) == 0 || labelIndex >= Game.m_cFlatDataArr[1].Table(7).m_numEntries) {
		return 0;
	}

	return Game.m_cFlatDataArr[1].TableStrings(7)[labelIndex];
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x80133108
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrBattleItem()
{
	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] != 0) {
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80133170
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiBaseInfoInit(CMenuPcs::Sprt2* a, CMenuPcs::Sprt2* b)
{
	short* board = reinterpret_cast<short*>(a);
	short* icon = reinterpret_cast<short*>(b);

	s_Base[0][0] = (float)(board[0] + board[2] * 0.5);
	s_Base[0][1] = (float)(board[1] + board[3] * 0.5);

	float iconW = (float)icon[2];
	float iconH = (float)icon[3];
	double iconHalfW = (double)iconW * 0.5;
	double iconHalfH = (double)iconH * 0.5;

	float v14 = (float)((double)s_Base[0][0] - iconHalfW);
	float v15 = (float)board[1];
	s_Base[0][14] = v14;
	s_Base[0][15] = v15;
	s_Base[0][6] = v14;
	s_Base[0][7] = v15 + (float)((double)(float)board[3] - (double)iconH);
	float v11 = (float)((double)s_Base[0][1] - iconHalfH);
	float v10 = (float)board[0];
	s_Base[0][10] = v10;
	s_Base[0][11] = v11;
	s_Base[0][2] = v10 + (float)((double)(float)board[2] - (double)iconW);
	s_Base[0][3] = v11;

	for (int row = 0; row < 2; row++) {
		float slotX = (float)((double)(float)(board[0] + board[2] * 0.25) - iconHalfW);
		float slotY = (float)((double)(float)(board[1] + board[3] * 0.25) - iconHalfH);
		if (row != 0) {
			slotY = (float)(board[3] * 0.5 + slotY);
			s_Base[0][8] = slotX;
			s_Base[0][9] = slotY;
		} else {
			s_Base[0][12] = slotX;
			s_Base[0][13] = slotY;
		}
		float nextX = (float)(board[2] * 0.5 + slotX);
		if (row == 0) {
			s_Base[0][16] = nextX;
			s_Base[0][17] = slotY;
		} else {
			s_Base[0][4] = nextX;
			s_Base[0][5] = slotY;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013351c
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawArtiBase(CMenuPcs::Sprt2* sprt, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x1c) != 4) {
		_GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = (unsigned char)(alpha * 255.0f);
		GXSetChanMatColor(GX_COLOR0A0, color);
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1A));

	BonusAnimSprite* sprite = reinterpret_cast<BonusAnimSprite*>(sprt);
	float width = (float)sprite->w;
	float height = (float)sprite->h;

	int partyIndex = 0;
	for (; partyIndex < s_Rinfo->m_partyCount; partyIndex++) {
		if ((int)*(short*)(this->m_bonusStatePtr + 0xe) == s_Rinfo->m_party[partyIndex].m_rank) {
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (*(short*)(this->m_bonusStatePtr + 0x1c) == 4) {
			float rgb = 1.0f;
			unsigned int mask = ((int)(signed char)s_Rinfo->pad_0008 | (int)(signed char)s_Rinfo->m_missingArtifactMask) |
			    s_Rinfo->m_party[partyIndex].m_ownedArtifactMask;
			if ((mask & (1 << i)) != 0) {
				rgb = 0.7f;
			}
			_GXColor color = {
			    (unsigned char)(rgb * 255.0f),
			    (unsigned char)(rgb * 255.0f),
			    (unsigned char)(rgb * 255.0f),
			    (unsigned char)(alpha * 255.0f),
			};
			GXSetChanMatColor(GX_COLOR0A0, color);
		}
		MenuPcs.DrawRect(0, s_Base[0][i * 2 + 2], s_Base[0][i * 2 + 3], width, height,
		    0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80133784
 * PAL Size: 852b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawBonusFrame(float x, float y, float w, float h, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	_GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = (unsigned char)(255.0f * alpha);
	const float corner = 8.0f;
	const float texScale = 1.0f;

	GXSetChanMatColor(GX_COLOR0A0, color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1B));
	const float right = (x + w) - corner;
	const float bottom = (y + h) - corner;
	for (int i = 0; i < 4; i++) {
		float drawX = x;
		float drawY = y;
		float texU;
		float texV;
		if (i == 0) {
			texU = 0.0f;
			texV = 0.0f;
		} else if (i == 1) {
			texU = corner;
			drawX = right;
			texV = 0.0f;
		} else {
			drawY = bottom;
			if (i == 2) {
				texU = 0.0f;
				texV = corner;
			} else {
				texU = corner;
				drawX = right;
				texV = corner;
			}
		}
		MenuPcs.DrawRect(0, drawX, drawY, corner, corner, texU, texV, texScale, texScale, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1C));
	float innerW = (float)((double)w - 16.0);
	float xCorner = corner + x;
	MenuPcs.DrawRect(0, xCorner, y, innerW, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x22));
	MenuPcs.DrawRect(0, xCorner, bottom, innerW, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
	float yCorner = corner + y;
	float innerH = (float)((double)h - 16.0);
	MenuPcs.DrawRect(0, x, yCorner, corner, innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
	MenuPcs.DrawRect(0, right, yCorner, corner, innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	MenuPcs.DrawRect(0, xCorner, yCorner, innerW, innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80133ad8
 * PAL Size: 3172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectCloseAnim()
{
	int statePtr = this->m_bonusStatePtr;
	int animPtr = this->m_bonusAnimPtr;

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(statePtr + 0xb) == 0) {
		int iconBase = 4;
		int nameBase = iconBase + activePartyCount;
		int slotBase = nameBase + activePartyCount;
		int detailBase = slotBase + 8;
		int markBase = detailBase + activePartyCount;
		int lowerNameBase = markBase + activePartyCount;

		header->count = (short)(header->count - 1);

		for (int i = 0; i < (int)header->count; i++) {
			BonusAnimSprite* sprite = &sprites[i];
			sprite->alpha = 1.0f;
			sprite->timer = 0;
			BonusSpriteFlags(sprite) = 0;
		}

		sprites[0].kind = 0x16;
		sprites[0].startFrame = 0;
		sprites[0].duration = 8;
		sprites[1].startFrame = 0;
		sprites[1].duration = 8;
		BonusSpriteFlags(&sprites[1]) = 2;
		sprites[2].kind = 0x1f;
		sprites[2].startFrame = 0;
		sprites[2].duration = 0;
		BonusSpriteFlags(&sprites[2]) = 2;
		sprites[3].kind = -4;
		sprites[3].startFrame = 0;
		sprites[3].duration = 8;

		for (int i = 0; i < activePartyCount; i++) {
			SetupSelectCloseSpriteMotion(&sprites[iconBase + i]);
			sprites[iconBase + i].depth = 1.0f;
		}

		s_PlayerTop = (unsigned char)nameBase;
		for (int i = 0; i < activePartyCount; i++) {
			SetupSelectCloseSpriteMotion(&sprites[nameBase + i]);
		}

		s_ArtiTop = (unsigned char)slotBase;
		for (int i = 0; i < 8; i++) {
			sprites[slotBase + i].timer = 0;
			sprites[slotBase + i].startFrame = 0;
			sprites[slotBase + i].duration = 8;
		}

		for (int i = 0; i < activePartyCount; i++) {
			SetupSelectCloseSpriteMotion(&sprites[detailBase + i]);
		}

		for (int i = 0; i < activePartyCount; i++) {
			SetupSelectCloseSpriteMotion(&sprites[markBase + i]);
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* iconSprite = &sprites[iconBase + i];
			BonusAnimSprite* nameSprite = &sprites[lowerNameBase + i];
			nameSprite->tex = -1;
			nameSprite->kind = -1;
			nameSprite->x = (short)(iconSprite->x + 0x50);
			nameSprite->y = (short)(iconSprite->y + 0x48);
			nameSprite->startFrame = iconSprite->startFrame;
			nameSprite->timer = 0;
			nameSprite->duration = 8;
			nameSprite->motionX = 100.0f;
			nameSprite->motionY = 0.0f;
			nameSprite->targetX = (float)nameSprite->x + nameSprite->motionX;
			nameSprite->targetY = (float)nameSprite->y + nameSprite->motionY;
		}

		*(short*)(animPtr + 6) = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		int flags = BonusSpriteFlags(sprite);

		if ((flags & 1) != 0) {
			sprite->alpha = 0.0f;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = 0.0f;
			} else {
				sprite->alpha = 1.0f - ((1.0f / (float)sprite->duration) * (float)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((flags & 2) == 0 && (sprite->motionX != 0.0f || sprite->motionY != 0.0f)) {
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			float progress = 1.0f - ((1.0f / (float)sprite->duration) * (float)sprite->timer);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	MenuBoardEntry* boardEntries = GetBonusBoardEntries(this);
	for (int i = 0; i < activePartyCount; i++) {
		MenuBoardEntry& entry = boardEntries[i];
		BonusAnimSprite* sprite = &sprites[4 + i];
		int centerX = (int)((double)(float)((double)sprite->w * 0.5 + (double)((float)sprite->x + sprite->motionX)) - 320.0);
		int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)((float)sprite->y + sprite->motionY)) - 240.0);
		entry.m_centerX = (short)centerX;
		entry.m_centerY = (short)centerY;

		int screenX = (int)(24.0f + (float)sprite->x + sprite->motionX);
		int screenY = (int)(((float)sprite->y + sprite->motionY) - 28.0f);
		if ((double)screenX < 0.0) {
			screenX = 0;
		}
		if ((double)screenY < 0.0) {
			screenY = 0;
		}
		entry.m_screenX = screenX;
		entry.m_screenY = screenY;
		entry.m_screenWidth = 0x48;
		entry.m_screenHeight = 0x58;
	}

	Mtx scaleMtx;
	Mtx rotMtx;
	Mtx tempMtx;
	Vec srcVec;
	Vec dstVec;
	CCharaPcs::CHandle** displaySlots = GetBonusDisplayHandleSlots(this);
	for (int i = 0; i < activePartyCount + 8; i++) {
		CCharaPcs::CHandle* handle;
		int tribeId;
		if (i < activePartyCount) {
			handle = s_Rinfo->m_party[i].m_partyHandle;
			tribeId = s_Rinfo->m_party[i].m_tribeId;
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);

			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			scaleMtx[0][3] = 0.0f;
		} else {
			int artifactIndex = i - activePartyCount;
			handle = displaySlots[activePartyCount * 2 + artifactIndex];
			if (handle == 0) {
				continue;
			}

			PSMTXScale(scaleMtx, 0.5799999833106995f, 0.5799999833106995f, 0.5799999833106995f);
			srcVec.x = s_BonusModelScale[4];
			srcVec.y = 0.0f;
			srcVec.z = 0.0f;
			PSMTXRotRad(rotMtx, 'z', 0.01745329238474369f * (float)(-45.0 * (double)artifactIndex));
			PSMTXMultVecSR(rotMtx, &srcVec, &dstVec);

			int charaNo = handle->m_charaNo;
			if (charaNo == 0x44) {
				PSMTXRotRad(tempMtx, 'y', 3.1415927410125732f);
				PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
				PSMTXRotRad(tempMtx, 'x', -1.1693705320358276f);
				PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
			}

			scaleMtx[0][3] = dstVec.x;
			float modelY = (float)((double)(0.9670329689979553f * dstVec.y) - 5.0);
			if (charaNo == 0x41 || charaNo == 0x37) {
				modelY += 3.4000000953674316f;
			} else if (charaNo == 0x44) {
				modelY += 5.0f;
			}
			scaleMtx[1][3] = modelY;
		}
		scaleMtx[2][3] = 0.0f;

		handle->m_model->m_flags10C = (handle->m_model->m_flags10C & 0x7F) | 0x80;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		handle->m_model->m_lightAlpha = sprites[(int)(signed char)s_PlayerTop + i].alpha;
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013473c
 * PAL Size: 2844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectWait()
{
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		this->m_menuWindowInfo->state = 3;
		int animBase;
		short count;
		int walkOff = 0;
		for (int i = 0; ; i++) {
			animBase = this->m_bonusAnimPtr;
			count = *(short*)animBase;
			if ((int)count <= i) {
				break;
			}
			*(float*)(animBase + walkOff + 0x18) = FLOAT_80331EB0;
			*(int*)(animBase + walkOff + 0x34) = 3;
			walkOff += 0x40;
		}
		BonusAnimSprite* cursor = (BonusAnimSprite*)(animBase + count * 0x40 + 8);
		BonusAnimSprite* partySprite = cursor - activePartyCount * 2;
		cursor->kind = 0x20;
		cursor->x = (short)(partySprite->x - 3);
		cursor->y = (short)(partySprite->y - 8);
		cursor->w = 0x40;
		cursor->h = 0x30;
		cursor->mulX = FLOAT_80331EAC;
		cursor->mulY = FLOAT_80331EAC;
		cursor->startFrame = 0;
		cursor->duration = 8;
		cursor->depth = FLOAT_80331EB0;
		((BonusAnimHeader*)this->m_bonusAnimPtr)->count = (short)(count + 1);
		BonusSpriteFlags(&((BonusAnimSprite*)(this->m_bonusAnimPtr + 8))[2]) = 0;
		*(short*)(this->m_bonusStatePtr + 0xe) = 0;
		*(short*)(this->m_bonusStatePtr + 0x26) = 4;
		*(short*)(this->m_bonusStatePtr + 0x18) = 0;
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
		*(short*)(this->m_bonusStatePtr + 0x1a) = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 8) = 0;
	}

	int statePtr = this->m_bonusStatePtr;
	int animPtr = this->m_bonusAnimPtr;
	MenuWindowInfo* window = this->m_menuWindowInfo;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	short& promptMode = window->state;
	short& currentPartyIndex = *(short*)(statePtr + 0xe);
	short& selection = *(short*)(statePtr + 0x26);
	short& confirmSel = *(short*)(statePtr + 0x28);
	short& delay = *(short*)(statePtr + 0x1a);
	int currentPartySlot = 0;
	for (; currentPartySlot < activePartyCount; currentPartySlot++) {
		if (s_Rinfo->m_party[currentPartySlot].m_rank == currentPartyIndex) {
			break;
		}
	}
	BonusPartySummary* currentParty = &s_Rinfo->m_party[currentPartySlot];
	int padSlot = currentParty->m_partySlot;
	unsigned short repeat;
	unsigned short down;
	if (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1)) {
		repeat = 0;
	} else {
		int resolvedPadSlot = (Pad.m_debugPadPort == padSlot) ? 0 : padSlot;
		repeat = Pad.m_padInputs[resolvedPadSlot].repeatButton;
	}
	if (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1)) {
		down = 0;
	} else {
		int resolvedPadSlot = (Pad.m_debugPadPort == padSlot) ? 0 : padSlot;
		down = Pad.m_padInputs[resolvedPadSlot].buttonDown[0];
	}
	int unavailableMask = GetBonusUnavailableMask(statePtr, currentParty);

	if (promptMode == 3) {
		if (delay == 0 && currentPartyIndex < activePartyCount) {
			if ((repeat & 9) != 0) {
				selection = (short)(selection + 1);
				if (selection > 7) {
					selection = 0;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			} else if ((repeat & 6) != 0) {
				selection = (short)(selection - 1);
				if (selection < 0) {
					selection = 7;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			}

			if ((repeat & 0xf) == 0) {
				if ((down & 0x100) != 0) {
					int bit = 1 << selection;
					if ((unavailableMask & bit) == 0) {
						*(unsigned char*)(statePtr + 8) = 1;
						delay = 10;
						Sound.PlaySe(0x4f, 0x40, 0x7f, 0);
					} else {
						Sound.PlaySe(4, 0x40, 0x7f, 0);
					}
				} else if ((down & 0x200) != 0) {
					short winW = 0;
					short winH = 0;
					GetWinSize(0x18, &winW, &winH, 1);
					SetMcWinInfo((int)winW, (int)winH);
					promptMode = 0;
					confirmSel = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			}
		} else if (currentPartyIndex < activePartyCount) {
			delay = (short)(delay - 1);
			if (delay == 0 && *(signed char*)(statePtr + 8) > 0) {
				int bit = 1 << selection;
				int itemId = (&s_Rinfo->m_tempArtifacts[0])[selection];
				s_Rinfo->pad_0008 = (unsigned char)(s_Rinfo->pad_0008 | bit);
				*(unsigned char*)(statePtr + 8) = 0;
				currentParty->m_selectedItemId = itemId;
				currentParty->m_selectedSlot = selection;
				currentPartyIndex = (short)(currentPartyIndex + 1);
			}
		} else {
			delay = 0;
		}
	} else if (promptMode == 1) {
		if ((repeat & 3) == 0) {
			if ((down & 0x100) == 0) {
				if ((down & 0x200) != 0) {
					promptMode = 2;
					confirmSel = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			} else {
				promptMode = 2;
				Sound.PlaySe(2, 0x40, 0x7f, 0);
			}
		} else {
			confirmSel = (short)(confirmSel ^ 1);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	} else if (promptMode == 2) {
		if (window->frame == 1 && confirmSel == 0) {
			delay = 10;
			*(unsigned char*)(statePtr + 8) = 0xff;
		}
	} else {
		promptMode = 3;
	}

	float* base = s_Base[0];
	sprites[2].x = (short)(int)base[selection * 2 + 2];
	sprites[2].y = (short)(int)base[selection * 2 + 3];
	if (sprites[2].timer < sprites[2].duration) {
		sprites[2].alpha = (float)sprites[2].timer / (float)sprites[2].duration;
		sprites[2].timer++;
	} else {
		sprites[2].alpha = FLOAT_80331EB0;
	}
	{
		BonusAnimSprite* cursor = &sprites[header->count - 1];
		if (currentPartyIndex < activePartyCount) {
			BonusAnimSprite* partySprite = cursor - (activePartyCount * 2 - currentPartyIndex);
			int pulseFrame = frame % 20 - 10;
			if (pulseFrame < 0) {
				pulseFrame = -pulseFrame;
			}
			cursor->x = (short)(partySprite->x - 3);
			cursor->y = (short)(partySprite->y - 8);
			cursor->alpha = (float)pulseFrame / 10.0f;
		} else {
			cursor->alpha = FLOAT_80331EAC;
		}
	}

	Mtx scaleMtx;
	Mtx rotMtx;
	Mtx tempMtx;
	Vec srcVec;
	Vec dstVec;
	for (int i = 0; i < activePartyCount + 8; i++) {
		CCharaPcs::CHandle* handle;
		int tribeId;
		if (i < activePartyCount) {
			handle = s_Rinfo->m_party[i].m_partyHandle;
			tribeId = s_Rinfo->m_party[i].m_tribeId;
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);

			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			scaleMtx[0][3] = FLOAT_80331EAC;
		} else {
			int artifactIndex = i - activePartyCount;
			handle = GetBonusDisplayHandleSlots(this)[activePartyCount * 2 + artifactIndex];
			if (handle == 0) {
				continue;
			}

			PSMTXScale(scaleMtx, FLOAT_80331F00, FLOAT_80331F00, FLOAT_80331F00);
			srcVec.x = s_BonusModelScale[4];
			srcVec.y = FLOAT_80331EAC;
			srcVec.z = FLOAT_80331EAC;
			PSMTXRotRad(rotMtx, 'z', FLOAT_80331F04 * (float)(DOUBLE_80331F08 * (double)artifactIndex));
			PSMTXMultVecSR(rotMtx, &srcVec, &dstVec);

			int charaNo = handle->m_charaNo;
			if (charaNo == 0x44) {
				PSMTXRotRad(tempMtx, 'y', FLOAT_80331F10);
				PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
				PSMTXRotRad(tempMtx, 'x', FLOAT_80331F14);
				PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
			}

			scaleMtx[0][3] = dstVec.x;
			float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
			if (charaNo == 0x41 || charaNo == 0x37) {
				modelY += FLOAT_80331F28;
			} else if (charaNo == 0x44) {
				modelY += FLOAT_80331F2C;
			}
			scaleMtx[1][3] = modelY;
		}
		scaleMtx[2][3] = FLOAT_80331EAC;

		handle->m_model->m_flags10C = (handle->m_model->m_flags10C & 0x7F) | 0x80;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		handle->m_model->m_lightAlpha = sprites[(int)(signed char)s_PlayerTop + i].alpha;
	}

	if (currentPartyIndex >= activePartyCount && delay == 0) {
		if (*(short*)(statePtr + 0x18) < 10) {
			*(short*)(statePtr + 0x18) = (short)(*(short*)(statePtr + 0x18) + 1);
		} else {
			*(short*)(statePtr + 0x18) = 0;
			for (int i = 0; i < activePartyCount; i++) {
				BonusPartySummary& summary = s_Rinfo->m_party[i];
				int itemId = summary.m_selectedItemId;
				if (itemId > 0) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[summary.m_partySlot]);
					if (itemId < 0xff) {
						caravanWork->m_artifacts[itemId - 0x9f] = static_cast<unsigned short>(itemId);
					} else {
						caravanWork->AddItem(itemId, 0);
					}
				}
			}
			header->finished = 1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80135258
 * PAL Size: 2824b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSelectOpenAnim()
{
	int statePtr = this->m_bonusStatePtr;

	if (*(signed char*)(statePtr + 0xb) == 0) {
		return;
	}

	BonusAnimSprite* artiSprite = 0;
	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;
	int off = 0;
	for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);
		int kind = sprite->kind;
		if (kind >= 0 || kind != -1) {
			if (kind == -3) {
				DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, sprite->alpha);
				lastKind = sprite->kind;
			} else if (kind == -4) {
				if (artiSprite == 0) {
					artiSprite = sprite;
				}
				DrawArtiBase((CMenuPcs::Sprt2*)sprite, sprite->alpha);
				lastKind = sprite->kind;
			} else if (kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				int projectionIndex = modelIndex;
				if (modelIndex < activePartyCount) {
					for (int j = 0; j < activePartyCount; j++) {
						if (s_Rinfo->m_party[j].m_rank == modelIndex) {
							handle = s_Rinfo->m_party[j].m_partyHandle;
							break;
						}
					}
				} else {
					projectionIndex = modelIndex + activePartyCount;
					handle = GetBonusDisplayHandleSlots(this)[projectionIndex];
					if (handle == 0) {
						modelIndex++;
						lastKind = -2;
						continue;
					}
				}

				SetProjection(projectionIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				if (modelIndex >= activePartyCount) {
					int listPtr = this->m_bonusListPtr;
					PartPcs.DrawMenuIdx(*reinterpret_cast<int*>(listPtr + projectionIndex * 0x524 + 4));
				}
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->tex));
				if (sprite->tex == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
				}
				MenuPcs.DrawRect(0,
				    (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
				    (float)sprite->w, (float)sprite->h,
				    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
				if (sprite->tex == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
				}
				lastKind = sprite->kind;
			}
		}
	}

	int animPtr = this->m_bonusAnimPtr;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	DrawBonusActiveMarks(this, statePtr, artiSprite->alpha);
	DrawBonusPartyNames(this, header, sprites);
	DrawBonusSelectedArtifactHelp(this, statePtr, header, sprites);
	DrawBonusMcWinOverlay(this, statePtr);
}

/*
 * --INFO--
 * PAL Address: 0x80135d60
 * PAL Size: 4668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectOpenAnim()
{
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int animPtr = this->m_bonusAnimPtr;
		BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
		BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
		int idx;
		int iconBase;
		int detailBase;

		this->m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, sizeof(BonusAnimList));
		*(short*)(this->m_bonusStatePtr + 0x22) = 0;

		idx = 0;
		sprites[idx].kind = 0x16;
		sprites[idx].x = 0;
		sprites[idx].y = 0;
		sprites[idx].w = 0x280;
		sprites[idx].h = 0x1c0;
		sprites[idx].mulX = 0.0f;
		sprites[idx].mulY = 0.0f;
		sprites[idx].startFrame = 0;
		sprites[idx].duration = 0;
		sprites[idx].depth = 1.0f;
		idx++;
		BonusSpriteFlags(&sprites[0]) = 3;
		sprites[0].alpha = 0.0f;

		sprites[idx].kind = -3;
		sprites[idx].x = 0xf0;
		sprites[idx].y = 0x38;
		sprites[idx].w = 0x168;
		sprites[idx].h = 0x148;
		sprites[idx].mulX = 0.0f;
		sprites[idx].mulY = 0.0f;
		sprites[idx].startFrame = 0;
		sprites[idx].duration = 8;
		sprites[idx].depth = 1.0f;
		idx++;
		sprites[idx].kind = 0x1f;
		sprites[idx].x = 0;
		sprites[idx].y = 0;
		sprites[idx].w = 0x80;
		sprites[idx].h = 0x78;
		sprites[idx].mulX = 0.0f;
		sprites[idx].mulY = 0.0f;
		sprites[idx].startFrame = 9999;
		sprites[idx].duration = 8;
		sprites[idx].depth = 1.0f;
		idx++;
		BonusSpriteFlags(&sprites[2]) = 2;
		sprites[2].motionX = -150.0f;
		sprites[2].motionY = -150.0f;
		InitAnimSprite(&sprites[idx++], -4, 0, 0, 0x70, 0x68, 0, 8);
		ResetAnimSpriteMotion(&sprites[3]);
		sprites[3].depth = 1.0f;

		iconBase = idx;
		short y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			InitSelectOpenPartyIcon(&sprites[idx], i, y);
			idx++;
			y += 0x60;
		}

		s_PlayerTop = (unsigned char)idx;
		for (int i = 0; i < activePartyCount; i++) {
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, sprites[iconBase + i].startFrame, 8);
			sprites[idx].tex = 0;
			sprites[idx].motionX = 100.0f;
			sprites[idx].motionY = 0.0f;
			sprites[idx].targetX = (float)sprites[idx].x + sprites[idx].motionX;
			sprites[idx].targetY = (float)sprites[idx].y + sprites[idx].motionY;
			idx++;
		}

		s_ArtiTop = (unsigned char)idx;
		for (int i = 0; i < 8; i++) {
			int start = 10 + i * 5;
			start = (int)(0.6f * (float)start);
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, start, 0x21);
			sprites[idx].tex = 0;
			BonusSpriteFlags(&sprites[idx]) = 1;
			idx++;
		}

		detailBase = idx;
		for (int i = 0; i < activePartyCount; i++) {
			sprites[idx] = sprites[iconBase + i];
			sprites[idx].y = (short)(sprites[idx].y + 0x20);
			sprites[idx].w = 0xA8;
			sprites[idx].h = 0x38;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = 0.0f;
			sprites[idx].mulY = 56.0f;
			BonusSpriteFlags(&sprites[idx]) = 1;
			sprites[idx].depth = 1.0f;
			sprites[idx].motionX = 100.0f;
			sprites[idx].motionY = 0.0f;
			sprites[idx].targetX = (float)sprites[idx].x + sprites[idx].motionX;
			sprites[idx].targetY = (float)sprites[idx].y + sprites[idx].motionY;
			idx++;
		}

		y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			short x = ((1 <= i) && (i <= 2)) ? 8 : 0x20;
			InitAnimSprite(&sprites[idx], 0x19, x, y, 0x38, 0x28, i * 2, 8);
			ResetAnimSpriteMotion(&sprites[idx]);
			sprites[idx].mulX = (float)(i * sprites[idx].w);
			sprites[idx].depth = 1.0f;
			sprites[idx].motionX = 100.0f;
			sprites[idx].motionY = 0.0f;
			sprites[idx].targetX = (float)sprites[idx].x + sprites[idx].motionX;
			sprites[idx].targetY = (float)sprites[idx].y + sprites[idx].motionY;
			BonusSpriteFlags(&sprites[idx]) = 1;
			idx++;
			y += 0x60;
		}

		for (int i = 0; i < activePartyCount; i++) {
			InitSelectOpenPartyName(&sprites[idx], &sprites[iconBase + i], 0x50, 0x48, sprites[detailBase + i].startFrame + 2);
			idx++;
		}

		ArtiBaseInfoInit(reinterpret_cast<CMenuPcs::Sprt2*>(&sprites[1]), reinterpret_cast<CMenuPcs::Sprt2*>(&sprites[3]));
		MenuBoardEntry* boardEntries = GetBonusBoardEntries(this);
		BonusAnimSprite* boardSprite = &sprites[1];
		for (int i = 0; i < 8; i++) {
			MenuBoardEntry& entry = boardEntries[activePartyCount * 2 + i];
			entry.m_rotZ = 0.0f;
			entry.m_rotY = 0.0f;
			entry.m_rotX = 0.0f;
			entry.m_scaleZ = 0.0f;
			entry.m_scaleY = 0.0f;
			entry.m_scaleX = 0.0f;
			entry.m_unk3c = 1.0f;
			entry.m_unk38 = 1.0f;
			entry.m_unk34 = 1.0f;
			entry.m_modelHandle = 0;
			entry.m_effectHandle = 0;
			int centerX = (int)((double)(float)((double)boardSprite->w * 0.5 + (double)boardSprite->x) - 320.0);
			int centerY = (int)((double)(float)((double)boardSprite->h * 0.5 + (double)boardSprite->y) - 240.0);
			entry.m_centerX = (short)centerX;
			entry.m_centerY = (short)centerY;
			entry.m_width = 0x280;
			entry.m_height = 0x1C0;
			entry.m_posX = 0.0f;
			entry.m_posY = 0.0f;
			entry.m_depth = 1000.0f;
			entry.m_screenX = 0;
			entry.m_screenY = 0;
			entry.m_screenWidth = 0x280;
			entry.m_screenHeight = 0x1C0;
		}

		header->count = (short)idx;
		header->finished = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	int statePtr = this->m_bonusStatePtr;
	int animPtr = this->m_bonusAnimPtr;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	int off = 0;
	for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);
		int flags = BonusSpriteFlags(sprite);

		if ((flags & 1) != 0) {
			sprite->alpha = 1.0f;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = 1.0f;
			} else {
				sprite->alpha = (1.0f / (float)sprite->duration) * (float)sprite->timer;
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((flags & 2) == 0 && (sprite->motionX != 0.0f || sprite->motionY != 0.0f)) {
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			float progress = 1.0f - ((1.0f / (float)sprite->duration) * (float)sprite->timer);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	MenuBoardEntry* boardEntries = GetBonusBoardEntries(this);
	for (int i = 0; i < activePartyCount; i++) {
		MenuBoardEntry& entry = boardEntries[i];
		BonusAnimSprite* sprite = &sprites[4 + i];
		int centerX = (int)((double)(float)((double)sprite->w * 0.5 + (double)((float)sprite->x + sprite->motionX)) - 320.0);
		int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)((float)sprite->y + sprite->motionY)) - 240.0);
		entry.m_centerX = (short)centerX;
		entry.m_centerY = (short)centerY;

		int screenX = (int)(24.0f + (float)sprite->x + sprite->motionX);
		int screenY = (int)(((float)sprite->y + sprite->motionY) - 28.0f);
		if ((double)screenX < 0.0) {
			screenX = 0;
		}
		if ((double)screenY < 0.0) {
			screenY = 0;
		}
		entry.m_screenX = screenX;
		entry.m_screenY = screenY;
		entry.m_screenWidth = 0x48;
		entry.m_screenHeight = 0x58;
	}

	Mtx scaleMtx;
	Mtx rotZMtx;
	Mtx rotYMtx;
	Mtx rotXMtx;
	Vec srcVec;
	Vec dstVec;
	CCharaPcs::CHandle** displaySlots = GetBonusDisplayHandleSlots(this);
	int partyByteOff = 0;
	for (int i = 0; i < activePartyCount + 8; i++, partyByteOff += sizeof(BonusPartySummary)) {
		BonusAnimSprite* iconSprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + ((int)(signed char)s_PlayerTop + i) * 0x40 + 8);
		CCharaPcs::CHandle* handle;
		int tribeId;
		if (i < activePartyCount) {
			tribeId = *(int*)((int)s_Rinfo + partyByteOff + 0x44);
			handle = *(CCharaPcs::CHandle**)((int)s_Rinfo + partyByteOff + 0x20);
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);

			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			scaleMtx[0][3] = 0.0f;
		} else {
			handle = displaySlots[i + activePartyCount];
			if (handle == 0) {
				continue;
			}
			PSMTXScale(scaleMtx, 0.5799999833106995f, 0.5799999833106995f, 0.5799999833106995f);

			int duration = iconSprite->duration;
			int artifactIndex = i - activePartyCount;
			int fcvIndex = duration / 5;
			float rate = (float)(450.0 / (double)(float)duration);
			int phase = (int)(((double)duration / 10.0) * (double)(10 - artifactIndex));

			if (frame == iconSprite->startFrame && this->m_bonusCursorFlag == 0) {
				this->m_bonusCursorFlag = 1;
				Sound.PlaySe(0x4d, 0x40, 0x7f, 0);
			}

			float angle;
			if (frame < iconSprite->startFrame) {
				srcVec.x = s_BonusModelScale[6];
				angle = -90.0f;
			} else if (iconSprite->timer < phase) {
				int last = iconSprite->timer - 1;
				if (fcvIndex < last) {
					srcVec.x = ((s_BonusModelScale[5] - s_BonusModelScale[4]) /
					    ((float)phase - (float)fcvIndex)) *
					    (float)(last - fcvIndex) - s_BonusModelScale[5];
				} else {
					srcVec.x = (float)last *
					    ((s_BonusModelScale[6] - s_BonusModelScale[5]) / (float)fcvIndex) -
					    s_BonusModelScale[6];
				}
				srcVec.x = -srcVec.x;
				angle = (float)(-90.0 + (double)(float)(rate * (double)(float)last));
			} else {
				srcVec.x = s_BonusModelScale[4];
				angle = (float)(45.0 * (double)(8 - artifactIndex));
			}
			srcVec.y = 0.0f;
			srcVec.z = 0.0f;
			PSMTXRotRad(rotZMtx, 'z', 0.01745329238474369f * angle);
			PSMTXMultVecSR(rotZMtx, &srcVec, &dstVec);

			int charaNo = handle->m_charaNo;
			if (charaNo == 0x44) {
				PSMTXRotRad(rotYMtx, 'y', 3.1415927410125732f);
				PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
				PSMTXRotRad(rotXMtx, 'x', -1.1693705320358276f);
				PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
			}

			scaleMtx[0][3] = dstVec.x;
			scaleMtx[1][3] = (float)((double)(0.9670329689979553f * dstVec.y) - 5.0);
			if (charaNo == 0x41 || charaNo == 0x37) {
				scaleMtx[1][3] = scaleMtx[1][3] + 3.4000000953674316f;
			} else if (charaNo == 0x44) {
				scaleMtx[1][3] = scaleMtx[1][3] + 5.0f;
			}
		}
		scaleMtx[2][3] = 0.0f;

		handle->m_model->m_flags10C = (handle->m_model->m_flags10C & 0x7F) | 0x80;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		handle->m_model->m_lightAlpha = iconSprite->alpha;
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80136f9c
 * PAL Size: 2452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultCloseAnim()
{
	int statePtr = this->m_bonusStatePtr;

	if (*(signed char*)(statePtr + 0xb) == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;
	for (int i = 0; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
		BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i];
		int kind = sprite->kind;

		if (kind >= 0 || kind == -2) {
			if (kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex / activePartyCount <= 1) {
					handle = GetBonusDisplayHandleSlots(this)[modelIndex - activePartyCount];
				} else {
					modelIndex++;
					continue;
				}

				if ((double)handle->m_model->m_lightAlpha > 0.0) {
					SetProjection(modelIndex);
					SetLight(1);
					unsigned int oldFlags = handle->m_flags;
					handle->m_flags = 0x300543;
					handle->Draw(5);
					handle->m_flags = oldFlags;
					RestoreProjection();
					lastKind = sprite->kind;
				}
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
				}
				if (lastKind != 0x17 && kind == 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				} else if (lastKind == 0x17 && kind != 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}

				_GXColor colors[4];
				if (kind == 0x17) {
					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = 0xFF;
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0xFF;
					colors[2].r = 0xFF;
					colors[2].g = 0xFF;
					colors[2].b = 0xFF;
					colors[2].a = 0xFF;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0xFF;
					_GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
					GXSetChanMatColor(GX_COLOR0A0, color);
				} else {
					_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
					GXSetChanMatColor(GX_COLOR0A0, color);
				}
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kind));

				if (kind == 0x17) {
					if (sprite->timer < sprite->duration) {
						float progress = 0.0f;
						if (sprite->timer < sprite->duration) {
							progress = 1.0f - ((float)(sprite->timer - 1) / (float)sprite->duration);
							if (progress < 0.0f) {
								progress = 0.0f;
							}
						}
						float fillWidth = progress * (float)sprite->w;
						float x = (float)sprite->x;
						float y = (float)sprite->y;
						if (fillWidth > 0.0f) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    sprite->mulX, sprite->mulY, colors, 1.0f, 1.0f, 0.0f);
							x += fillWidth;
						}
						if (fillWidth < (float)sprite->w) {
							colors[0].a = 0;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)sprite->w / (float)sprite->duration, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, 1.0f, 1.0f, 0.0f);
						}
					}
				} else {
					if ((signed char)s_CntTop > i || i >= (signed char)s_CntTop + activePartyCount) {
						MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
						    (float)sprite->w, (float)sprite->h,
						    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
					} else {
						int value = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
						int digits[3];
						int digitCount;

						if (value >= 100) {
							digitCount = 3;
							digits[0] = value / 100;
							value -= digits[0] * 100;
							digits[1] = value / 10;
							digits[2] = value - digits[1] * 10;
						} else if (value >= 10) {
							digitCount = 2;
							digits[0] = value / 10;
							digits[1] = value - digits[0] * 10;
						} else {
							digitCount = 1;
							digits[0] = value;
						}

						float digitW = (float)sprite->w;
						float digitX = ((3.0f * digitW) - (float)(digitCount * sprite->w)) * 0.5f + (float)sprite->x;
						for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
							MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
							    digitW * (float)digits[digitIndex], sprite->mulY,
							    sprite->depth, sprite->depth, 0.0f);
							digitX += digitW;
						}
					}
				}
				lastKind = kind;
			}
		}
	}

	DrawInit();
	CFont* font = this->m_fonts[0];
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.7300000190734863f);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[128];
	for (int i = 0; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
		BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i];
		if (sprite->kind == -1) {
			CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f));
			font->SetColor(color.color);

			int partyIndex = textIndex % activePartyCount;
			CCaravanWork* caravanWork =
			    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
			if (textIndex < activePartyCount) {
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			} else {
				strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[(int)caravanWork->m_bonusCondition * 2 + 1]);
			}

			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= 6.0f;
			}
			font->SetPosX((float)sprite->x + sprite->motionX);
			font->SetPosY(y - 6.0f);
			font->Draw(text);

			textIndex++;
			if (textIndex == activePartyCount) {
				font = this->m_fonts[1];
				font->SetMargin(1.0f);
				font->SetShadow(0);
				font->SetScaleX(0.7f);
				font->SetScaleY(1.0f);
				font->DrawInit();
			}
		}
	}
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x80137930
 * PAL Size: 8676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultCloseAnim()
{
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int off = 0;
		short* count = (short*)this->m_bonusAnimPtr;
		for (int i = 0; i < *count; i++, count = (short*)this->m_bonusAnimPtr) {
			*(int*)((int)count + off + 0x28) = 0;
			*(float*)(this->m_bonusAnimPtr + off + 0x38) = FLOAT_80331EAC;
			*(float*)(this->m_bonusAnimPtr + off + 0x3c) = FLOAT_80331EAC;
			off += 0x40;
		}

		count[0x16] = 0;
		count[0x17] = 9999;
		count[0x1a] = 0;
		count[0x1b] = 3;

		for (int i = 0; i < activePartyCount; i++) {
			*(int*)(this->m_bonusAnimPtr + (i + 1) * 0x40 + 0x2c) = 0x10;
		}

		// iconBase block: src = frameBase (back = activePartyCount sprites); dance
		int base = activePartyCount + 1;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x12) = *(int*)(sprite - activePartyCount * 0x20 + 0x12) +
			    *(int*)(sprite - activePartyCount * 0x20 + 0x14);
			sprite[0x16] = 0;
			sprite[0x17] = 1;
			*(float*)(sprite + 0x1c) = (float)(int)*sprite;
			*(float*)(sprite + 0x18) = FLOAT_80331ED0;
			*sprite = (short)(int)((float)(int)*sprite - *(float*)(sprite + 0x18));
		}

		// digitBase block: src = iconBase (back = activePartyCount sprites); no dance
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			int sprite = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
			int source = sprite - activePartyCount * 0x40;
			*(int*)(sprite + 0x24) = *(int*)(source + 0x24) + *(int*)(source + 0x28);
			*(int*)(sprite + 0x2c) = 1;
		}

		// frameEchoBase block: startFrame = 0
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			*(int*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 0x2c) = 0;
		}

		// iconEchoBase block: startFrame = 9999, flags = 3
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			int sprite = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
			*(int*)(sprite + 0x24) = 9999;
			*(int*)(sprite + 0x2c) = 3;
		}

		// digitEchoBase block: src = iconBase (back = base - iconBase = base - (pc+1)); dance
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x12) = *(int*)(sprite - (base - activePartyCount - 1) * 0x20 + 0x12);
			sprite[0x16] = 0;
			sprite[0x17] = 1;
			*(float*)(sprite + 0x1c) = (float)(int)*sprite;
			*(float*)(sprite + 0x18) = FLOAT_80331ED0;
			*sprite = (short)(int)((float)(int)*sprite - *(float*)(sprite + 0x18));
		}

		// sprites[digitEchoBase + pc].startFrame = sprites[1].startFrame
		int countTop = base + activePartyCount + 1;
		*(int*)(this->m_bonusAnimPtr + (base + activePartyCount) * 0x40 + 0x2c) =
		    *(int*)(this->m_bonusAnimPtr + 0x6c);
		s_CntTop = (unsigned char)countTop;

		// countTop block: startFrame = 8, duration = 8
		for (int i = 0; i < activePartyCount; i++) {
			int sprite = this->m_bonusAnimPtr + (countTop + i) * 0x40 + 8;
			*(int*)(sprite + 0x24) = 8;
			*(int*)(sprite + 0x28) = 8;
		}

		// extraBase block: src = iconBase (back = base - (pc+1)); dance
		base = countTop + activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x12) = *(int*)(sprite - (base - activePartyCount - 1) * 0x20 + 0x12);
			sprite[0x16] = 0;
			sprite[0x17] = 1;
			*(float*)(sprite + 0x1c) = (float)(int)*sprite;
			*(float*)(sprite + 0x18) = FLOAT_80331ED0;
			*sprite = (short)(int)((float)(int)*sprite - *(float*)(sprite + 0x18));
		}

		// extraBase + pc block: flags = 0
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			*(int*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 0x2c) = 0;
		}

		// extraBase + 2*pc block: src = extraBase + pc (back = activePartyCount sprites); dance
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x12) = *(int*)(sprite - activePartyCount * 0x20 + 0x12);
			sprite[0x16] = 0;
			sprite[0x17] = 1;
			*(float*)(sprite + 0x1c) = (float)(int)*sprite;
			*(float*)(sprite + 0x18) = FLOAT_80331ED0;
			*sprite = (short)(int)((float)(int)*sprite - *(float*)(sprite + 0x18));
		}

		// extraBase + 3*pc block: flags = 0
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			*(int*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 0x2c) = 0;
		}

		// extraBase + 4*pc block: src = iconBase (back = base - (pc+1)); dance
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x12) = *(int*)(sprite - (base - activePartyCount - 1) * 0x20 + 0x12);
			sprite[0x16] = 0;
			sprite[0x17] = 1;
			*(float*)(sprite + 0x1c) = (float)(int)*sprite;
			*(float*)(sprite + 0x18) = FLOAT_80331ED0;
			*sprite = (short)(int)((float)(int)*sprite - *(float*)(sprite + 0x18));
		}

		off = 0;
		short* sp = (short*)this->m_bonusAnimPtr;
		for (int i = 0; i < *sp; i++, sp = (short*)this->m_bonusAnimPtr) {
			if (0.0f == *(float*)((int)sp + off + 0x38)) {
				*(float*)((int)sp + off + 0x40) = (float)(int)*(short*)((int)sp + off + 8);
			}
			int s = this->m_bonusAnimPtr + off;
			if (0.0f == *(float*)(s + 0x3c)) {
				*(float*)(s + 0x44) = (float)(int)*(short*)(s + 10);
			}
			off += 0x40;
		}

		sp[3] = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	int doneCount = 0;
	*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22);

	int off = 0;
	for (int i = 0; i < *(short*)this->m_bonusAnimPtr; i++) {
		short* sprite = (short*)((int)this->m_bonusAnimPtr + off + 8);

		if ((*(unsigned int*)(sprite + 0x16) & 1) == 0) {
			if (frame < *(int*)(sprite + 0x12)) {
				*(float*)(sprite + 8) = 0.0f;
			}
			if (frame < (int)(*(int*)(sprite + 0x12) + *(unsigned int*)(sprite + 0x14))) {
				*(float*)(sprite + 8) =
				    1.0f - ((float)*(int*)(sprite + 0x10) / (float)*(unsigned int*)(sprite + 0x14));
			} else {
				*(float*)(sprite + 8) = 0.0f;
			}
		} else {
			*(float*)(sprite + 8) = 0.0f;
		}

		if ((int)(*(int*)(sprite + 0x12) + *(unsigned int*)(sprite + 0x14)) <= frame ||
		    0x270e < *(int*)(sprite + 0x12)) {
			doneCount++;
		}

		if ((*(unsigned int*)(sprite + 0x16) & 2) == 0 &&
		    (*(float*)(sprite + 0x18) != 0.0f || *(float*)(sprite + 0x1a) != 0.0f)) {
			float fy = (float)(int)sprite[1];
			float ty = *(float*)(sprite + 0x1e);
			float progress =
			    1.0f - ((float)*(int*)(sprite + 0x10) / (float)*(unsigned int*)(sprite + 0x14));
			*(float*)(sprite + 0x18) =
			    (*(float*)(sprite + 0x1c) - (float)(int)*sprite) * progress;
			*(float*)(sprite + 0x1a) = (ty - fy) * progress;
		}

		if (*(int*)(sprite + 0x12) < frame &&
		    frame <= *(int*)(sprite + 0x12) + *(int*)(sprite + 0x14)) {
			*(int*)(sprite + 0x10) = *(int*)(sprite + 0x10) + 1;
		}

		off += 0x40;
	}

	int boardOff = 0;
	off = 0;
	if (0 < activePartyCount) {
		int base = activePartyCount + 1;
		for (int i = 0; i < activePartyCount; i++) {
			short* sprite = (short*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			int boardPtr = this->m_bonus.m_bonusBoardPtr;
			float x = (float)(int)*sprite + *(float*)(sprite + 0x18);
			float y = (float)(int)sprite[1] + *(float*)(sprite + 0x1a);
			*(short*)(boardPtr + boardOff + 8) =
			    (short)(int)((double)(float)(24.0f + (float)(int)sprite[2] * 0.5f + x) - 320.0);
			*(short*)(boardPtr + boardOff + 10) =
			    (short)(int)((double)(float)((float)(int)sprite[3] * 0.5f + y) - 224.0);
			*(int*)(boardPtr + boardOff + 0x40) = (int)(x + 12.0f);
			*(int*)(boardPtr + boardOff + 0x44) = (int)(y - 8.0f);
			if ((double)*(int*)(boardPtr + boardOff + 0x40) < 0.0) {
				*(int*)(boardPtr + boardOff + 0x40) = 0;
			}
			if ((double)*(int*)(boardPtr + boardOff + 0x44) < 0.0) {
				*(int*)(boardPtr + boardOff + 0x44) = 0;
			}
			*(int*)(boardPtr + boardOff + 0x48) = 0x48;
			*(int*)(boardPtr + boardOff + 0x4c) = 0x58;
			boardOff += 0x50;
		}
	}
	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	int partyByteOff = 0;
	int alphaOff = (activePartyCount * 2 + 1) * 0x40;
	for (int i = 0; i < activePartyCount * 2; i++) {
		int animPtr = this->m_bonusAnimPtr;
		CCharaPcs::CHandle* handle;
		unsigned int tribeId = 0;
		if (i < activePartyCount) {
			handle = *(CCharaPcs::CHandle**)((int)s_Rinfo + partyByteOff + 0x20);
			tribeId = *(unsigned int*)((int)s_Rinfo + partyByteOff + 0x44);
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
		} else {
			handle = GetBonusDisplayHandleSlots(this)[i - activePartyCount];
			PSMTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
		}

		if (i / activePartyCount == 1) {
			PSMTXRotRad(rotXMtx, 'x', 0.2617993950843811f);
			PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * *reinterpret_cast<float*>(this->m_bonusStatePtr));
			PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
		}

		if (i < activePartyCount) {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			scaleMtx[2][3] = 0.0f;
		} else {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
		}

		handle->m_model->m_flags10C = (handle->m_model->m_flags10C & 0x7F) | 0x80;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		if (i < activePartyCount) {
			handle->m_model->m_lightAlpha = 1.0f;
		} else {
			handle->m_model->m_lightAlpha = *(float*)(animPtr + alphaOff + 0x18);
		}
		alphaOff += 0x40;
		partyByteOff += 0x2c;
	}

	if (*(short*)this->m_bonusAnimPtr == doneCount) {
		((short*)this->m_bonusAnimPtr)[3] = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80139b14
 * PAL Size: 1816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultCountAnim()
{
	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;
	int off = 0;
	for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);
		int kind = sprite->kind;

		if (kind >= 0 || kind == -2) {
			if (kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex < activePartyCount * 2) {
					handle = GetBonusDisplayHandleSlots(this)[modelIndex - activePartyCount];
				} else {
					continue;
				}

				SetProjection(modelIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kind));

				if ((signed char)s_CntTop > i || i >= (signed char)s_CntTop + activePartyCount) {
					MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
					    (float)sprite->w, (float)sprite->h,
					    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
				} else {
					int value = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
					if (*(short*)(this->m_bonusStatePtr + 0x10) == 0) {
						int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22) - 8;
						if (frame > 0) {
							if (frame < value) {
								value = frame;
							}
						} else {
							value = 0;
						}
					}
					int digits[3];
					int digitCount;

					if (value >= 100) {
						digitCount = 3;
						digits[0] = value / 100;
						value -= digits[0] * 100;
						digits[1] = value / 10;
						digits[2] = value - digits[1] * 10;
					} else if (value >= 10) {
						digitCount = 2;
						digits[0] = value / 10;
						digits[1] = value - digits[0] * 10;
					} else {
						digitCount = 1;
						digits[0] = value;
					}

					float digitW = (float)sprite->w;
					float digitX = ((3.0f * digitW) - (float)(digitCount * sprite->w)) * 0.5f + (float)sprite->x;
					for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
						MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
						    digitW * (float)digits[digitIndex], sprite->mulY,
						    sprite->depth, sprite->depth, 0.0f);
						digitX += digitW;
					}
				}
				lastKind = sprite->kind;
			}
		}
	}

	DrawInit();
	CFont* font = this->m_fonts[0];
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.7300000190734863f);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[128];
	off = 0;
	for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);
		if (sprite->kind == -1) {
			CColor color(0xFF, 0xFF, 0xFF, 0xFF);
			font->SetColor(color.color);

			int partyIndex = textIndex % activePartyCount;
			CCaravanWork* caravanWork =
			    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
			if (textIndex < activePartyCount) {
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			} else {
				strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[(int)caravanWork->m_bonusCondition * 2 + 1]);
			}

			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= 6.0f;
			}
			font->SetPosX((float)sprite->x + sprite->motionX);
			font->SetPosY(y - 6.0f);
			font->Draw(text);

			textIndex++;
			if (textIndex == activePartyCount) {
				font = this->m_fonts[1];
				font->SetMargin(1.0f);
				font->SetScaleX(0.7f);
				font->SetScaleY(1.0f);
				font->SetShadow(0);
				font->DrawInit();
			}
		}
	}
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x8013a22c
 * PAL Size: 1736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultCountAnim()
{
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int countTop = ((BonusAnimHeader*)this->m_bonusAnimPtr)->count;
		short y = 0x28;
		int partyByteOff = 0;
		for (int i = 0; i < activePartyCount; i++, partyByteOff += sizeof(BonusPartySummary)) {
			int rank = *(int*)((int)s_Rinfo + partyByteOff + 0x34);
			BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[countTop + i];
			sprite->kind = 0x19;
			short stripX = ((1 <= i) && (i <= 2)) ? 8 : 0x20;
			sprite->x = stripX;
			sprite->y = y;
			sprite->w = 0x38;
			y += 0x60;
			sprite->h = 0x28;
			sprite->mulX = (float)(rank * sprite->w);
			sprite->mulY = 0.0f;
			sprite->startFrame = 9999;
			sprite->duration = 4;
			sprite->depth = 1.0f;
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->targetX = (float)(sprite->x - 0x60);
			sprite->targetY = (float)(sprite->y - 0x40);
			sprite->timer = 0;
		}

		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = GetBonusDisplayHandleSlots(this)[i];
			if (handle != 0) {
				handle->m_model->m_lightAlpha = 0.0f;
			}
		}

		((BonusAnimHeader*)this->m_bonusAnimPtr)->count = (short)(countTop + activePartyCount);
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) == 0) {
		*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	}

	int countTop = (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count - activePartyCount;
	int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22) - 8;

	for (int i = 0; i < activePartyCount; i++) {
		BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[countTop + i];
		if (*(short*)(this->m_bonusStatePtr + 0x10) != 0) {
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->alpha = 1.0f;
		} else {
			int value = s_Rinfo->m_party[i].m_totalValue;
			if (frame == value) {
				Sound.PlaySe(0x4b, 0x40, 0x7f, 0);
				sprite->startFrame = frame;
			}

			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			} else {
				int elapsed = frame - sprite->startFrame;
				sprite->alpha = 1.0f;
				if (elapsed < sprite->duration) {
					float fy = (float)sprite->y;
					float ty = sprite->targetY;
					double progress = 1.0 - (double)((float)elapsed / (float)sprite->duration);
					sprite->motionX = (float)((double)(sprite->targetX - (float)sprite->x) * progress);
					sprite->motionY = (float)((double)(ty - fy) * progress);
				} else {
					sprite->motionX = 0.0f;
					sprite->motionY = 0.0f;
				}
			}
		}
	}

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	for (int i = 0; i < activePartyCount * 2; i++) {
		CCharaPcs::CHandle* handle;
		int tribeId;
		if (i < activePartyCount) {
			handle = s_Rinfo->m_party[i].m_partyHandle;
			tribeId = s_Rinfo->m_party[i].m_tribeId;
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
		} else {
			handle = GetBonusDisplayHandleSlots(this)[i - activePartyCount];
			PSMTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
		}

		if (i / activePartyCount == 1) {
			PSMTXRotRad(rotXMtx, 'x', 0.2617993950843811f);
			PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * *reinterpret_cast<float*>(this->m_bonusStatePtr));
			PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
		}

		if (i < activePartyCount) {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
		} else {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
		}

		CChara::CModel* model = handle->m_model;
		model->m_flags10C = (model->m_flags10C & 0x7F) | 0x80;
		model->SetMatrix(scaleMtx);
		model->CalcMatrix();
		model->CalcSkin();
		model->m_lightAlpha = 1.0f;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) == 0 && frame >= 0 && frame <= s_Rinfo->m_winnerTotalValue) {
		Sound.PlaySe(0x4a, 0x40, 0x7f, 0);
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) == 0 && frame >= 0 &&
	    (double)s_Rinfo->m_winnerTotalValue + 8.333333134651184 <= (double)frame) {
		*(short*)(this->m_bonusStatePtr + 0x10) = 1;
		return;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) != 0) {
		unsigned short buttons = 0;
		int padRemap = Pad.m_debugPadPort;
		int padLock = Pad.m_debugPadLock;
		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			unsigned int padIndex = s_Rinfo->m_party[i].m_partySlot;
			unsigned short down;
			if (padLock != 0 || (padIndex == 0 && padRemap != -1)) {
				down = 0;
			} else {
				unsigned int resolvedIndex = (padRemap == (int)padIndex) ? 0 : padIndex;
				down = Pad.m_padInputs[resolvedIndex].buttonDown[0];
			}
			buttons = (unsigned short)(buttons | down);
		}
		if ((buttons & 0x300) != 0) {
			Sound.PlaySe(2, 0x40, 0x7f, 0);
			((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013a8f4
 * PAL Size: 2136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultOpenAnim()
{
	int statePtr = this->m_bonusStatePtr;

	if (*(signed char*)(statePtr + 0xb) != 0) {
		int activePartyCount = s_Rinfo->m_partyCount;
		int lastKind = 0;

		DrawInit();
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		int modelIndex = 0;

		for (int i = 0; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
			BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i];
			int kind = sprite->kind;

			if (kind >= 0 || kind == -2) {
				if (kind == -2) {
					CCharaPcs::CHandle* handle;
					if (modelIndex < activePartyCount) {
						handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
					} else {
						handle = GetBonusDisplayHandleSlots(this)[modelIndex - activePartyCount];
					}

					if ((double)handle->m_model->m_lightAlpha > 0.0) {
						SetProjection(modelIndex);
						SetLight(1);
						handle->m_flags = 0x300543;
						handle->Draw(5);
						RestoreProjection();
					}
					lastKind = kind;
					modelIndex++;
				} else {
					if (lastKind < 0) {
						DrawInit();
					}
					if (lastKind != 0x17 && kind == 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					} else if (lastKind == 0x17 && kind != 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
					}

					_GXColor colors[4];
					if (kind == 0x17) {
						colors[0].r = 0xFF;
						colors[0].g = 0xFF;
						colors[0].b = 0xFF;
						colors[0].a = 0xFF;
						colors[1].r = 0xFF;
						colors[1].g = 0xFF;
						colors[1].b = 0xFF;
						colors[1].a = 0xFF;
						colors[2].r = 0xFF;
						colors[2].g = 0xFF;
						colors[2].b = 0xFF;
						colors[2].a = 0xFF;
						colors[3].r = 0xFF;
						colors[3].g = 0xFF;
						colors[3].b = 0xFF;
						colors[3].a = 0xFF;
						_GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
						GXSetChanMatColor(GX_COLOR0A0, color);
					} else {
						_GXColor color;
						color.r = 0xFF;
						color.g = 0xFF;
						color.b = 0xFF;
						color.a = (unsigned char)(sprite->alpha * 255.0f);
						GXSetChanMatColor(GX_COLOR0A0, color);
					}
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kind));

					if (kind == 0x17) {
						float fillWidth = 1.0f;
						if (sprite->timer < sprite->duration) {
							fillWidth = 1.0f - ((float)(sprite->timer - 1) / (float)sprite->duration);
							if (fillWidth < 0.0f) {
								fillWidth = 0.0f;
							}
						}
						fillWidth *= (float)sprite->w;

						float x = (float)sprite->x;
						float y = (float)sprite->y;
						if (fillWidth > 0.0f) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    sprite->mulX, sprite->mulY, colors, 1.0f, 1.0f, 0.0f);
							x += fillWidth;
						}
						if (fillWidth > 0.0f && fillWidth < (float)sprite->w) {
							colors[0].a = 0;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)sprite->w / (float)sprite->duration, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, 1.0f, 1.0f, 0.0f);
						}
					} else {
						if (i < s_CntTop || i >= s_CntTop + activePartyCount) {
							MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
							    (float)sprite->w, (float)sprite->h,
							    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
						} else {
							MenuPcs.DrawRect(0,
							    (float)sprite->x + ((float)(3 * sprite->w - sprite->w) * 0.5f),
							    (float)sprite->y, (float)sprite->w, (float)sprite->h,
							    0.0f, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
						}
					}
					lastKind = kind;
				}
			}
		}

		DrawInit();
		CFont* font = this->m_fonts[0];
		font->SetMargin(1.0f);
		font->SetShadow(1);
		font->SetScale(0.7300000190734863f);
		font->SetTlut(7);
		font->DrawInit();

		int textIndex = 0;
		char text[128];
		for (int i = 0; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
			BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i];
			if (sprite->kind == -1) {
				CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f));
				font->SetColor(color.color);

				int partyIndex = textIndex % activePartyCount;
				CCaravanWork* caravanWork =
				    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
				if (textIndex < activePartyCount) {
					strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
				} else {
					strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[(int)caravanWork->m_bonusCondition * 2 + 1]);
				}

				float y = (float)sprite->y + sprite->motionY;
				if (textIndex < activePartyCount) {
					y -= 6.0f;
				}
				font->SetPosX((float)sprite->x + sprite->motionX);
				font->SetPosY(y - 6.0f);
				font->Draw(text);

				textIndex++;
				if (textIndex == activePartyCount) {
					font = this->m_fonts[1];
					font->SetMargin(1.0f);
					font->SetShadow(0);
					font->SetScaleX(0.7f);
					font->SetScaleY(1.0f);
					font->DrawInit();
				}
			}
		}

		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013b14c
 * PAL Size: 8316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultOpenAnim()
{
	int statePtr = this->m_bonusStatePtr;
	const int activePartyCount = s_Rinfo->m_partyCount;
	const int frameBase = 1;
	const int iconBase = frameBase + activePartyCount;

	if (*(signed char*)(statePtr + 0xb) == 0) {
		int animPtr = this->m_bonusAnimPtr;
		BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
		BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

		this->m_bonusAlpha = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, sizeof(BonusAnimList));

		{
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + 8);
			sprite->kind = 0x16;
			sprite->y = 0;
			sprite->x = 0;
			sprite->w = 0x280;
			sprite->h = 0x1c0;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->startFrame = 0;
			sprite->duration = 8;
			sprite->depth = 1.0f;
			sprite->alpha = 0.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (frameBase + i) * 0x40 + 8);
			sprite->kind = 0x17;
			sprite->x = 0x80;
			sprite->y = (short)(0x38 + i * 0x60);
			sprite->w = 0x1a0;
			sprite->h = 0x40;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		int base = iconBase;
		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[base + i];
			unsigned int partySlot = s_Rinfo->m_party[i].m_partySlot;
			sprite->kind = 0x18;
			sprite->x = ((1 <= i) && (i <= 2)) ? 0x30 : 0x48;
			sprite->y = (short)(0x28 + i * 0x60);
			sprite->w = 0x60;
			sprite->h = 0x58;
			int texX = (partySlot & 1) ? (int)sprite->w : 0;
			sprite->mulX = (float)texX;
			int texY = ((int)partySlot >> 1) ? (int)sprite->h : 0;
			sprite->mulY = (float)texY;
			if (i == 0) {
				sprite->startFrame = sprites[frameBase].startFrame + sprites[frameBase].duration + 0x18;
			} else {
				sprite->startFrame = sprites[base + i - 1].startFrame + 3;
			}
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			BonusAnimSprite* icon = (BonusAnimSprite*)((int)sprite - activePartyCount * 0x40);
			sprite->kind = -2;
			sprite->x = 0;
			sprite->y = 0;
			sprite->w = 0;
			sprite->h = 0;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->startFrame = icon->startFrame + icon->duration;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			sprite->kind = -2;
			sprite->x = 0;
			sprite->y = 0;
			sprite->w = 0;
			sprite->h = 0;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			BonusAnimSprite* icon = (BonusAnimSprite*)((int)sprite - 3 * activePartyCount * 0x40);
			sprite->kind = -1;
			sprite->x = (short)(icon->x + 0x50);
			sprite->y = (short)(icon->y + 0x48);
			sprite->w = 0;
			sprite->h = 0;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->startFrame = icon->startFrame;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			BonusAnimSprite* name = (BonusAnimSprite*)((int)sprite - activePartyCount * 0x40);
			sprite->kind = -1;
			sprite->x = 0xb8;
			sprite->y = (short)(name->y + 0x15);
			sprite->w = 0;
			sprite->h = 0;
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->startFrame = name->startFrame + name->duration;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}
		int countBase = base + activePartyCount;
		{
			BonusAnimSprite* count = (BonusAnimSprite*)(this->m_bonusAnimPtr + countBase * 0x40 + 8);
			count->kind = 0x19;
			count->x = (short)((0x280 - 0x140) >> 1);
			count->y = 0x10;
			count->w = 0x140;
			count->h = 0x28;
			count->mulX = 0.0f;
			count->mulY = 0.0f;
			count->startFrame = ((BonusAnimSprite*)(this->m_bonusAnimPtr + 8))[1].startFrame;
			count->duration = 8;
			count->duration = 10;
			count->depth = 1.0f;
		}
		int countTop = countBase + 1;
		s_CntTop = (unsigned char)countTop;

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (countTop + i) * 0x40 + 8);
			BonusAnimSprite* count = (BonusAnimSprite*)(this->m_bonusAnimPtr + countBase * 0x40 + 8);
			sprite->kind = 0x19;
			sprite->x = 0x200;
			sprite->y = (short)(count->y + 0xC);
			sprite->w = 0x20;
			sprite->h = 0x28;
			sprite->mulX = 0.0f;
			sprite->mulY = 80.0f;
			sprite->startFrame = count->startFrame + count->duration;
			sprite->duration = 8;
			sprite->depth = 1.0f;
		}

		MenuBoardEntry* boardEntries = GetBonusBoardEntries(this);
		for (int i = 0; i < activePartyCount; i++) {
			MenuBoardEntry& entry = boardEntries[i];
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (activePartyCount + i + 1) * 0x40 + 8);
			int centerX = (int)((double)(float)((double)sprite->w * 0.5 + (double)((float)sprite->x + 24.0f)) - 320.0);
			int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 240.0);
			entry.m_centerX = (short)centerX;
			entry.m_centerY = (short)centerY;
			entry.m_screenX = sprite->x + 0xC;
			entry.m_screenY = sprite->y - 8;
			entry.m_screenWidth = 0x48;
			entry.m_screenHeight = 0x58;
		}

		for (int i = 0; i < activePartyCount; i++) {
			MenuBoardEntry& entry = boardEntries[activePartyCount + i];
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + ((signed char)s_CntTop + i) * 0x40 + 8);
			int extent = sprite->w * 3 + 0x20;
			int centerX = (int)((double)(float)((double)(sprite->w * 3) * 0.5 + (double)sprite->x) - 320.0);
			int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 240.0);
			entry.m_centerX = (short)centerX;
			entry.m_centerY = (short)centerY;
			entry.m_screenX = sprite->x - 0x10;
			entry.m_screenY = sprite->y - 0x10;
			entry.m_screenWidth = extent;
			entry.m_screenHeight = extent;
		}

		for (int i = 0; i < activePartyCount; i++) {
			MenuBoardEntry& entry = boardEntries[activePartyCount * 2 + i];
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (frameBase + i) * 0x40 + 8);
			int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 240.0);
			entry.m_centerX = 0;
			entry.m_centerY = (short)centerY;
		}

		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = GetBonusDisplayHandleSlots(this)[i];
			if (handle != 0) {
				handle->m_model->m_lightAlpha = 0.0f;
			}
		}

		header->count = (short)(countTop + activePartyCount);
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
		header->finished = 0;
		return;
	}

	int animPtr = this->m_bonusAnimPtr;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->startFrame <= frame) {
			if (frame < sprite->startFrame + sprite->duration) {
				sprite->timer++;
				sprite->alpha = (float)((1.0 / (double)sprite->duration) * (double)sprite->timer);
			} else {
				doneCount++;
				sprite->alpha = 1.0f;
			}

			if (sprite->kind == 0x17) {
				BonusAnimSprite* sound = sprite;
				for (int j = 0; j < activePartyCount; j++) {
					if (sound->timer == 1) {
						Sound.PlaySe(0x49, 0x40, 0x7f, 0);
					}
					sound++;
				}
			}
		}
	}

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	for (int i = 0; i < activePartyCount * 3; i++) {
		BonusAnimSprite* sprite = &sprites[activePartyCount * 2 + 1 + i];
		CCharaPcs::CHandle* handle;
		int tribeId;
		if (i < activePartyCount) {
			handle = s_Rinfo->m_party[i].m_partyHandle;
			tribeId = s_Rinfo->m_party[i].m_tribeId;
			float modelScale = s_BonusModelScale[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
		} else {
			handle = GetBonusDisplayHandleSlots(this)[i - activePartyCount];
			if (i < activePartyCount * 2) {
				PSMTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
			} else {
				float modelScale = 0.5f;
				if (sprite->timer == 0x18 && this->m_bonusAlpha == 0) {
					Sound.PlaySe(0x48, 0x40, 0x7f, 0);
					this->m_bonusAlpha = 1;
				}
				if (0x17 < sprite->timer) {
					modelScale = (float)(0.5 * (double)((float)(sprite->timer - 0x18) /
					                 (float)(sprite->duration - 0x18)) + (double)modelScale);
				}
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			}
		}

		if (i / activePartyCount == 1) {
			PSMTXRotRad(rotXMtx, 'x', 0.2617993950843811f);
			PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * *reinterpret_cast<float*>(statePtr));
			PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
		}

		if (i < activePartyCount) {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			scaleMtx[2][3] = 0.0f;
		} else if (i < activePartyCount * 2) {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
		} else {
			scaleMtx[0][3] = (float)GetFcvValue(s_BallTrnsX, (float)(sprite->timer - 1));
			if (sprite->timer == 8) {
				Sound.PlaySe(0x47, 0x40, 0x7f, 0);
			}
			float ty = (float)GetFcvValue(s_BallTrnsY, (float)(sprite->timer - 1));
			int itemIndex = i - activePartyCount * 2;
			scaleMtx[1][3] = ty;
			scaleMtx[2][3] = 0.0f;
			if (itemIndex > 0 && itemIndex < 3) {
				scaleMtx[1][3] = (float)((double)ty - 1.8);
			}
		}

		handle->m_model->m_flags10C = (handle->m_model->m_flags10C & 0x7F) | 0x80;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		if (activePartyCount * 2 <= i) {
			if (sprite->timer < 0x18) {
				sprite->alpha = 1.0f;
			} else {
				sprite->alpha = (float)(1.0 - (double)((float)(sprite->timer - 0x18) /
				                 (float)(sprite->duration - 0x18)));
				if ((double)sprite->alpha < 0.0) {
					sprite->alpha = 0.0f;
				}
			}
		}
		handle->m_model->m_lightAlpha = sprite->alpha;
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013d1c8
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawBonus()
{
	gUtil.ClearZBufferRect(FLOAT_80331EAC, FLOAT_80331EAC, FLOAT_80331FB8, FLOAT_80331FBC);

	if ((unsigned int)System.m_execParam >= 1) {
		System.Printf(const_cast<char*>(sDrawBonusFmt), (int)*(short*)(this->m_bonusStatePtr + 0x1c));
	}

	switch (*(short*)(this->m_bonusStatePtr + 0x1c)) {
	case 0:
		DrawResultOpenAnim();
		break;
	case 1:
		DrawResultCountAnim();
		break;
	case 2:
		DrawResultCloseAnim();
		break;
	case 3:
		DrawSelectOpenAnim();
		break;
	case 4:
		DrawSelectOpenAnim();
		break;
	case 5:
		DrawSelectOpenAnim();
		break;
	case 6:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013d2a0
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcBonus()
{
	*reinterpret_cast<float*>(this->m_bonusStatePtr) =
	    static_cast<float>((double)*reinterpret_cast<float*>(this->m_bonusStatePtr) - kPppCrystal2RefractionScale);

	if (*(short*)(this->m_bonusAnimPtr + 6) != 0) {
		*(short*)(this->m_bonusStatePtr + 0x1c) =
		    *(short*)(this->m_bonusStatePtr + 0x1c) + 1;
		*(short*)(this->m_bonusAnimPtr + 6) = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 0;
		*(short*)(this->m_bonusStatePtr + 0x10) = 0;
		*(short*)(this->m_bonusStatePtr + 0x22) = 0;
	}

	switch (*(short*)(this->m_bonusStatePtr + 0x1c)) {
	case 0:
		CalcResultOpenAnim();
		break;
	case 1:
		CalcResultCountAnim();
		break;
	case 2:
		CalcResultCloseAnim();
		break;
	case 3:
		CalcSelectOpenAnim();
		break;
	case 4:
		CalcSelectWait();
		break;
	case 5:
		CalcSelectCloseAnim();
		if (*(short*)(this->m_bonusAnimPtr + 6) != 0) {
			CallWorldParam(8, 0, 0);
		}
		break;
	case 6:
		for (int i = 0; i < 4; i++) {
			if (Game.m_scriptFoodBase[i] != 0) {
				reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
				reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
			}
		}
		changeMode(static_cast<CMenuPcs::MENUMODE>(0));
		break;
	default:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013d410
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroyBonus()
{
	Pad.m_stickDigitalThreshold = 1;

	if (this->m_fonts[1] != 0) {
		ReleaseBonusRefObject(this->m_fonts[1]);
		this->m_fonts[1] = 0;
	}

	for (int i = 0; i < 0x18; i++) {
		if (GetBonusDisplayHandleSlots(this)[i] != 0) {
			delete GetBonusDisplayHandleSlots(this)[i];
			GetBonusDisplayHandleSlots(this)[i] = 0;
		}
	}

	CMenuPcs::EffectInfo* list = (CMenuPcs::EffectInfo*)this->m_bonusListPtr;
	if (list != 0) {
		delete[] list;
		this->m_bonusListPtr = 0;
	}

	if (s_Rinfo != 0) {
		delete s_Rinfo;
		s_Rinfo = 0;
	}

	BonusMenuStateRaw* state = (BonusMenuStateRaw*)this->m_bonusStatePtr;
	if (state != 0) {
		delete state;
		this->m_bonusStatePtr = 0;
	}

	BonusAnimList* anim = (BonusAnimList*)this->m_bonusAnimPtr;
	if (anim != 0) {
		delete anim;
		this->m_bonusAnimPtr = 0;
	}

	if (s_Base[0] != 0) {
		delete reinterpret_cast<BonusBaseRaw*>(s_Base[0]);
		s_Base[0] = 0;
	}

	unsigned char* board = (unsigned char*)this->m_bonus.m_bonusBoardPtr;
	if (board != 0) {
		delete[] board;
		this->m_bonus.m_bonusBoardPtr = 0;
	}

	MenuWindowInfo* window = this->m_menuWindowInfo;
	if (window != 0) {
		delete window;
		this->m_menuWindowInfo = 0;
	}

	freeTexture(2, 1, 0x16, 0x12);
}

/*
 * --INFO--
 * PAL Address: 0x8013d59c
 * PAL Size: 3300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createBonus()
{
	char fontPath[128];

	Pad.m_stickDigitalThreshold = 0x28;
	for (int i = 0; i < 4; i++) {
		GbaQue.OpenMenu(i, 0, 0);
		GbaQue.SetRadarMode(i, 0);
	}

	loadTexture(PTR_s_bonus, 2, 1, s_bonusTextureTable, 0x16, 0x12, 0);
	sprintf(fontPath, lbl_801DD5D4, Game.GetLangString());
	loadFont(0, fontPath, 1, -1);

	s_Rinfo = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xDD) BonusSummaryData;
	memset(s_Rinfo, 0, sizeof(*s_Rinfo));
	for (int i = 0; i < 4; i++) {
		s_Rinfo->m_tempArtifacts[i] = -1;
	}
	for (int i = 0; i < 4; i++) {
		s_Rinfo->m_bossArtifacts[i] = -1;
	}

	this->m_bonusStatePtr = reinterpret_cast<int>(new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xE5) BonusMenuStateRaw);
	this->m_bonusListPtr = reinterpret_cast<int>(new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xE6) CMenuPcs::EffectInfo[0x28]);

	InitBonusEffectSlots(this);
	memset((void*)this->m_bonusStatePtr, 0, sizeof(BonusMenuStateRaw));
	s_Base[0] = reinterpret_cast<float*>(new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xF1) BonusBaseRaw);
	memset(s_Base[0], 0, sizeof(float) * 18);
	this->m_bonusAnimPtr = reinterpret_cast<int>(new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xF5) BonusAnimList);
	memset((void*)this->m_bonusAnimPtr, 0, sizeof(BonusAnimList));
	this->m_bonus.m_bonusBoardPtr = reinterpret_cast<int>(new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xF8) unsigned char[sizeof(BonusBoardEntryList)]);
	this->m_menuWindowInfo = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xFA) MenuWindowInfo;
	memset(this->m_menuWindowInfo, 0, sizeof(MenuWindowInfo));
	const float depth1000 = FLOAT_80331F6C;
	const float scale1 = FLOAT_80331EB0;
	const float zero = FLOAT_80331EAC;
	int off = 0;
	for (int i = 0; i < 0x18; i++) {
		float* pos = (float*)(this->m_bonus.m_bonusBoardPtr + off + 0x1c);
		pos[2] = zero;
		pos[1] = zero;
		pos[0] = zero;
		pos[5] = zero;
		pos[4] = zero;
		pos[3] = zero;
		pos[8] = scale1;
		pos[7] = scale1;
		pos[6] = scale1;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off) = 0;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off + 0x4) = 0;
		*(short*)(this->m_bonus.m_bonusBoardPtr + off + 0x8) = 0;
		*(short*)(this->m_bonus.m_bonusBoardPtr + off + 0xa) = 0;
		*(short*)(this->m_bonus.m_bonusBoardPtr + off + 0xc) = 0x280;
		*(short*)(this->m_bonus.m_bonusBoardPtr + off + 0xe) = 0x1c0;
		*(float*)(this->m_bonus.m_bonusBoardPtr + off + 0x10) = zero;
		*(float*)(this->m_bonus.m_bonusBoardPtr + off + 0x14) = zero;
		*(float*)(this->m_bonus.m_bonusBoardPtr + off + 0x18) = depth1000;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off + 0x40) = 0;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off + 0x44) = 0;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off + 0x48) = 0x280;
		*(int*)(this->m_bonus.m_bonusBoardPtr + off + 0x4c) = 0x1c0;
		off += 0x50;
	}

	if (s_Rinfo != 0) {
		int activeCount = 0;
		int totalValue = 0;
		int tempArtifactCount = 0;

		for (int i = 0; i < 4; i++) {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
			if (caravanWork == 0) {
				continue;
			}
			if (Game.m_gameWork.m_menuStageMode != 0 && activeCount != 0) {
				break;
			}

			s_Rinfo->m_party[activeCount].m_partySlot = i;
			s_Rinfo->m_party[activeCount].m_partyHandle =
			    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(Game.m_partyObjArr[i]) + 0xF8);
			s_Rinfo->m_party[activeCount].m_partyHandle->m_model->m_lightAlpha = 0.0f;
			s_Rinfo->m_party[activeCount].m_bonusCondition = (int)caravanWork->m_bonusCondition;
			int foodValue = (int)caravanWork->m_artifactRelated[3] + (int)caravanWork->m_artifactRelated[4];
			int foodClamped;
			if (foodValue < 0) {
				foodClamped = 0;
			} else {
				foodClamped = 100;
				if (foodValue <= 100) {
					foodClamped = foodValue;
				}
			}
			s_Rinfo->m_party[activeCount].m_foodValue = foodClamped;
			s_Rinfo->m_party[activeCount].m_artifactValue =
			    (int)caravanWork->m_artifactRelated[0] + (int)caravanWork->m_artifactRelated[1] - (int)caravanWork->m_artifactRelated[2];
			s_Rinfo->m_party[activeCount].m_totalValue =
			    s_Rinfo->m_party[activeCount].m_foodValue + s_Rinfo->m_party[activeCount].m_artifactValue;
			s_Rinfo->m_party[activeCount].m_selectedItemId = -1;
			s_Rinfo->m_party[activeCount].m_selectedSlot = -1;
			int rawTotal = s_Rinfo->m_party[activeCount].m_totalValue;
			int totalValueClamped;
			if (rawTotal < 0) {
				totalValueClamped = 0;
			} else {
				totalValueClamped = 999;
				if (rawTotal <= 999) {
					totalValueClamped = rawTotal;
				}
			}
			s_Rinfo->m_party[activeCount].m_totalValue = totalValueClamped;
			totalValue += s_Rinfo->m_party[activeCount].m_totalValue;
			s_Rinfo->m_party[activeCount].m_tribeId = (unsigned int)caravanWork->m_tribeId;
			activeCount++;

			if (caravanWork->m_treasures[0] > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = caravanWork->m_treasures[0];
			}
			if (caravanWork->m_treasures[1] > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = caravanWork->m_treasures[1];
			}
			if (caravanWork->m_treasures[2] > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = caravanWork->m_treasures[2];
			}
			if (caravanWork->m_treasures[3] > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = caravanWork->m_treasures[3];
			}
		}

		s_Rinfo->m_partyCount = activeCount;

		short* bossArtifact = reinterpret_cast<short*>(Game.GetBossArtifact(s_Rinfo->m_partyCount, totalValue));
		for (int i = 0; i < 4; i++) {
			s_Rinfo->m_bossArtifacts[i] = bossArtifact[i];
		}

		s_Rinfo->m_missingArtifactMask = 0;
		for (int i = 0; i < 4; i++) {
			if (s_Rinfo->m_tempArtifacts[i] < 0) {
				s_Rinfo->m_missingArtifactMask =
				    (unsigned char)(s_Rinfo->m_missingArtifactMask | (1 << i));
			}
			if (s_Rinfo->m_bossArtifacts[i] < 0) {
				s_Rinfo->m_missingArtifactMask =
				    (unsigned char)(s_Rinfo->m_missingArtifactMask | (1 << (i + 4)));
			}
		}

		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			CCaravanWork* caravanWork =
			    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[i].m_partySlot]);

			short* rewardItems = &s_Rinfo->m_tempArtifacts[0];
			for (int artifactIndex = 0; artifactIndex < 8; artifactIndex++) {
				short itemId = rewardItems[artifactIndex];
				if (itemId <= 0) {
					continue;
				}

				if (GetItemType(itemId, 1) == 2) {
					int artifactSlot = itemId - 0x9F;
					if (caravanWork->m_artifacts[artifactSlot] == itemId) {
						s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
					}
				} else if (caravanWork->m_inventoryItemCount + 1 > 0x40) {
					s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
				}
			}
		}

		int order[4];
		order[0] = 0;
		order[1] = 1;
		order[2] = 2;
		order[3] = 3;
		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			int leftIndex = order[i];
			for (int j = i + 1; j < s_Rinfo->m_partyCount; j++) {
				BonusPartySummary& a = s_Rinfo->m_party[leftIndex];
				BonusPartySummary& b = s_Rinfo->m_party[order[j]];
				int aTotal = a.m_totalValue;
				int aArtifact = a.m_artifactValue;
				int bTotal = b.m_totalValue;
				int bArtifact = b.m_artifactValue;
				int aFood = a.m_foodValue;
				int bFood = b.m_foodValue;
				unsigned int coin = rand();

				if (aTotal < bTotal ||
				    (aTotal == bTotal && aArtifact < bArtifact) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood < bFood) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood == bFood && (coin & 1) != 0)) {
					int temp = leftIndex;
					order[i] = order[j];
					order[j] = temp;
					leftIndex = order[i];
				}
			}
		}

		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			BonusPartySummary& ranked = s_Rinfo->m_party[order[i]];
			ranked.m_rank = i;
			if (i == 0) {
				s_Rinfo->m_winnerTotalValue = ranked.m_totalValue;
			}
		}

		for (int i = 0; i < 0x18; i++) {
			this->m_wm.m_handles[i] = 0;
		}

		CCharaPcs::CHandle** slot = this->m_wm.m_handles;
		for (int i = 0; i < s_Rinfo->m_partyCount * 2; i++) {
			CCharaPcs::CHandle* handle =
			    new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0x183) CCharaPcs::CHandle;
			slot[0] = handle;
			slot[0]->Add();
			unsigned long modelCode = s_Rinfo->m_party[i % s_Rinfo->m_partyCount].m_partySlot + 0x83;
			if (i < s_Rinfo->m_partyCount) {
				modelCode = s_Rinfo->m_party[i % s_Rinfo->m_partyCount].m_partySlot + 0x87;
			}
			slot[0]->LoadModel(3, modelCode & 0xFFF, (modelCode >> 12) & 0xF, 0, -1, 0, 0);
			slot = (CCharaPcs::CHandle**)((char*)slot + 4);
			slot[-1]->m_flags = 0x300543;
		}

		CCharaPcs::CHandle** displaySlots = GetBonusDisplayHandleSlots(this);
		int handleIndex = s_Rinfo->m_partyCount * 2;
		short* rewardItems = &s_Rinfo->m_tempArtifacts[0];
		for (int artifactIndex = 0; artifactIndex < 8; artifactIndex++) {
			short itemId = rewardItems[artifactIndex];
			if (itemId < 1) {
				displaySlots[handleIndex] = 0;
			} else {
				CCharaPcs::CHandle* itemHandle =
				    new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0x19C) CCharaPcs::CHandle;
				displaySlots[handleIndex] = itemHandle;
				itemHandle->Add();
				unsigned short itemModelCode =
				    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2);
				int modelNo = itemModelCode & 0x0FFF;
				itemHandle->LoadModel(3, modelNo, (itemModelCode >> 12) & 0xF, 0, -1, 0, 0);
				itemHandle->m_flags = 0x300543;

				if (modelNo == 0x79) {
					itemId = rewardItems[artifactIndex];
					int effectNo = -1;
					if (itemId == 0xDF) {
						effectNo = 0x75;
					} else if (itemId == 0xE0) {
						effectNo = 0x76;
					} else if (itemId == 0xE1) {
						effectNo = 0x77;
					} else if (itemId == 0xE2) {
						effectNo = 0x78;
					} else if (itemId == 0xE3) {
						effectNo = 0x79;
					}
					if (effectNo >= 0) {
						BindEffect(handleIndex, effectNo, -1);
					}
				}
			}

			handleIndex++;
		}
	}

	GbaQue.SetStartBonusFlg();
	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] != 0) {
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
		}
	}
	this->m_menuWindowInfo->state = 3;
	s_CntTop = 0;
	s_ArtiTop = 0;
	s_PlayerTop = 0;
	*(short*)(this->m_bonusStatePtr + 0x1c) = 0;
	Wind.ClearAll();
	this->m_bonusAlpha = 0;
	this->m_bonusCursorFlag = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013e280
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BonusInit()
{
	s_Rinfo = 0;
	this->m_bonusAnimPtr = 0;
	s_Base[0] = 0;
}
