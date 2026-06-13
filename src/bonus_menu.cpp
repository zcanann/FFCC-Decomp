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
extern const float kBonusZClearOrigin;
extern const float FLOAT_80331EB0;
extern const float FLOAT_80331ED0;
extern const float FLOAT_80331F6C;
extern const float FLOAT_80331F5C;
extern const float FLOAT_80331F60;
extern const float FLOAT_80331F64;
extern const float FLOAT_80331F68;
extern const double DOUBLE_80331E78;
extern const double DOUBLE_80331EE8;
extern const double DOUBLE_80331EF0;
extern const float FLOAT_80331EF8;
extern const float FLOAT_80331EFC;
extern const float FLOAT_80331E98;
extern const double DOUBLE_80331EC8;
extern const float FLOAT_80331F38;
extern const float FLOAT_80331F3C;
extern const float FLOAT_80331F90;
extern const float FLOAT_80331F00;
extern const float FLOAT_80331F04;
extern const double DOUBLE_80331F08;
extern const float FLOAT_80331F10;
extern const float FLOAT_80331F14;
extern const float FLOAT_80331F18;
extern const double DOUBLE_80331F20;
extern const float FLOAT_80331F28;
extern const float FLOAT_80331F2C;
extern const float FLOAT_80331F94;
extern const float FLOAT_80331FA0;
extern const float FLOAT_80331FA4;
extern const float FLOAT_80331FA8;
extern const double DOUBLE_80331E90;
extern const double DOUBLE_80331F98;
extern const double DOUBLE_80331ED8;
extern const double DOUBLE_80331EE0;
extern const double DOUBLE_80331FB0;
extern const float kBonusZClearWidth;
extern const float kBonusZClearHeight;
extern char lbl_801DD510[];
extern const float s_BonusModelYPos[];
extern const float s_BonusModelScale[];
extern const float FLOAT_80331E9C;
extern const float FLOAT_80331EA0;
extern const float FLOAT_80331EA4;
extern const float FLOAT_80331EA8;
extern const float FLOAT_80331F40;
extern const float FLOAT_80331F44;
extern const float FLOAT_80331F48;
extern const float FLOAT_80331F4C;
extern const float FLOAT_80331F50;
extern const float FLOAT_80331F58;
extern const char lbl_80331F54[2];
extern "C" const char s_pcts_pctd_Error_memory_allocation_error_801DD598[];
extern const double DOUBLE_80331F30;
extern const double DOUBLE_80331F70;
extern const float FLOAT_80331F78;
extern const double DOUBLE_80331F80;
extern const double DOUBLE_80331F88;

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

extern const char sBonusTextureSetName[] = "bonus";
extern const char sBonusTextureName1[] = "bonus1";
extern const char sBonusTextureName2[] = "bonus2";
extern const char sBonusTextureName3[] = "bonus3";
extern const char sBonusTextureName4[] = "bonus4";
extern const char sBonusTextureName5[] = "bonus5";
extern const char sBonusTextureName6[] = "bonus6";
extern const char sBonusTextureName7[] = "bonus7";
extern const char sBonusTextureName8[] = "bonus8";
extern const char sBonusTextureName9[] = "bonus9";
extern const char sBonusTextureName10[] = "bonus10";
extern const char sBonusTextureName11[] = "bonus11";
extern const char sBonusTextureName12[] = "bonus12";
extern const char sBonusTextureName13[] = "bonus13";
extern const char sBonusTextureName14[] = "bonus14";
extern const char sBonusTextureName15[] = "bonus15";
extern const char sBonusTextureName16[] = "bonus16";
extern const char sBonusTextureName17[] = "bonus17";
extern const char sBonusTextureName18[] = "bonus18";

extern const double DOUBLE_80331E78 = 0.5;
extern const double DOUBLE_80331E80 = 0.25;
extern const double DOUBLE_80331E88 = 4503601774854144.0;
extern const double DOUBLE_80331E90 = 0.0;
extern const float FLOAT_80331E98 = 255.0f;
extern const float FLOAT_80331E9C = 28.0f;
extern const float FLOAT_80331EA0 = 20.0f;
extern const float FLOAT_80331EA4 = 56.0f;
extern const float FLOAT_80331EA8 = 64.0f;
extern const float kBonusZClearOrigin = 0.0f;
extern const float FLOAT_80331EB0 = 1.0f;
extern const float FLOAT_80331EB4 = 0.699999988079071f;
extern const float FLOAT_80331EB8 = 32.0f;
extern const double DOUBLE_80331EC0 = 64.0;
extern const double DOUBLE_80331EC8 = 3.0;
extern const float FLOAT_80331ED0 = 240.0f;
extern const double DOUBLE_80331ED8 = 1.0;
extern const double DOUBLE_80331EE0 = 4.0;
extern const double DOUBLE_80331EE8 = 320.0;
extern const double DOUBLE_80331EF0 = 224.0;
extern const float FLOAT_80331EF8 = 12.0f;
extern const float FLOAT_80331EFC = 8.0f;
extern const float FLOAT_80331F00 = 0.5799999833106995f;
extern const float FLOAT_80331F04 = 0.01745329238474369f;
extern const double DOUBLE_80331F08 = -45.0;
extern const float FLOAT_80331F10 = 3.1415927410125732f;
extern const float FLOAT_80331F14 = -1.1693705320358276f;
extern const float FLOAT_80331F18 = 0.9670329689979553f;
extern const double DOUBLE_80331F20 = 5.0;
extern const float FLOAT_80331F28 = 3.4000000953674316f;
extern const float FLOAT_80331F2C = 5.0f;
extern const double DOUBLE_80331F30 = 10.0;
extern const float FLOAT_80331F38 = 0.7300000190734863f;
extern const float FLOAT_80331F3C = 4.0f;
extern const float FLOAT_80331F40 = 0.7200000286102295f;
extern const float FLOAT_80331F44 = 0.8999999761581421f;
extern const float FLOAT_80331F48 = 44.0f;
extern const float FLOAT_80331F4C = 11.0f;
extern const float FLOAT_80331F50 = 7.0f;
extern const char lbl_80331F54[2] = "\n";
extern const float FLOAT_80331F58 = 22.0f;
extern const float FLOAT_80331F5C = -8.0f;
extern const float FLOAT_80331F60 = -240.0f;
extern const float FLOAT_80331F64 = 0.8333333134651184f;
extern const float FLOAT_80331F68 = 176.0f;
extern const float FLOAT_80331F6C = 100.0f;
extern const double DOUBLE_80331F70 = 450.0;
extern const float FLOAT_80331F78 = -90.0f;
extern const double DOUBLE_80331F80 = 45.0;
extern const double DOUBLE_80331F88 = -90.0;
extern const float FLOAT_80331F90 = 0.800000011920929f;
extern const float FLOAT_80331F94 = 0.2617993950843811f;
extern const double DOUBLE_80331F98 = 8.333333134651184;
extern const float FLOAT_80331FA0 = 80.0f;
extern const float FLOAT_80331FA4 = 40.0f;
extern const float FLOAT_80331FA8 = 0.5f;
extern const double DOUBLE_80331FB0 = 1.8;
extern const float kBonusZClearWidth = 640.0f;
extern const float kBonusZClearHeight = 448.0f;

char* sBonusTextureSetNames[] = {
    const_cast<char*>(sBonusTextureSetName),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

CMenuPcs::CTmp sBonusTextureTable[] = {
    {2, const_cast<char*>(sBonusTextureName1)},
    {2, const_cast<char*>(sBonusTextureName2)},
    {2, const_cast<char*>(sBonusTextureName3)},
    {2, const_cast<char*>(sBonusTextureName4)},
    {2, const_cast<char*>(sBonusTextureName5)},
    {2, const_cast<char*>(sBonusTextureName6)},
    {2, const_cast<char*>(sBonusTextureName7)},
    {2, const_cast<char*>(sBonusTextureName8)},
    {2, const_cast<char*>(sBonusTextureName9)},
    {2, const_cast<char*>(sBonusTextureName10)},
    {2, const_cast<char*>(sBonusTextureName11)},
    {2, const_cast<char*>(sBonusTextureName12)},
    {2, const_cast<char*>(sBonusTextureName13)},
    {2, const_cast<char*>(sBonusTextureName14)},
    {2, const_cast<char*>(sBonusTextureName15)},
    {2, const_cast<char*>(sBonusTextureName16)},
    {2, const_cast<char*>(sBonusTextureName17)},
    {2, const_cast<char*>(sBonusTextureName18)},
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
	int flags;
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
	*reinterpret_cast<float*>(&sprite->flags) = 1.0f;
}

static inline void ResetAnimSpriteMotion(BonusAnimSprite* sprite)
{
	sprite->mulX = 0.0f;
	sprite->mulY = 0.0f;
	sprite->alpha = 0.0f;
	sprite->depth = 0.0f;
	*reinterpret_cast<float*>(&sprite->flags) = 1.0f;
}

static inline int& BonusSpriteFlags(BonusAnimSprite* sprite)
{
	return sprite->flags;
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
	sprite->startFrame = 0;
	sprite->duration = 8;
	sprite->x = (short)(int)sprite->targetX;
	sprite->y = (short)(int)sprite->targetY;
	sprite->motionX = FLOAT_80331ED0;
	sprite->motionY = kBonusZClearOrigin;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
}

static inline void DrawBonusActiveMarks(CMenuPcs* menu, int statePtr, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = (unsigned char)(alpha * 255.0f);
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
		float ny = (float)sprite->y + sprite->motionY - 12.0f;
		font->SetPosX((float)sprite->x + sprite->motionX);
		font->SetPosY(ny);
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
	int frameIndex = 0;
	for (int i = 0; i < (int)header->count; i++) {
		if (sprites[i].kind == -3) {
			frameIndex = i;
			break;
		}
	}
	frame = &sprites[frameIndex];

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

	float v14 = (float)((double)s_Base[0][0] - (double)iconW * 0.5);
	float v15 = (float)board[1];
	for (int r0 = 0; r0 < 2; r0++) {
		if (r0 != 0) {
			v15 = v15 + ((float)board[3] - iconH);
		}
		if (r0 == 0) {
			s_Base[0][14] = v14;
			s_Base[0][15] = v15;
		} else {
			s_Base[0][6] = v14;
			s_Base[0][7] = v15;
		}
	}

	float v10 = (float)board[0];
	float v11 = (float)((double)s_Base[0][1] - (double)iconH * 0.5);
	for (int r1 = 0; r1 < 2; r1++) {
		if (r1 != 0) {
			v10 = v10 + ((float)board[2] - iconW);
		}
		if (r1 == 0) {
			s_Base[0][10] = v10;
			s_Base[0][11] = v11;
		} else {
			s_Base[0][2] = v10;
			s_Base[0][3] = v11;
		}
	}

	for (int row = 0; row < 2; row++) {
		float slotX = (float)((double)(float)(board[0] + board[2] * 0.25) - (double)iconW * 0.5);
		float slotY = (float)((double)(float)(board[1] + board[3] * 0.25) - (double)iconH * 0.5);
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

	_GXColor color;
	if (*(short*)(this->m_bonusStatePtr + 0x1c) != 4) {
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
			float gray;
			unsigned int mask = ((int)(signed char)s_Rinfo->pad_0008 | (int)(signed char)s_Rinfo->m_missingArtifactMask) |
			    s_Rinfo->m_party[partyIndex].m_ownedArtifactMask;
			if ((mask & (1 << i)) != 0) {
				gray = 0.7f * 255.0f;
			} else {
				gray = 1.0f * 255.0f;
			}
			color.r = (unsigned char)gray;
			color.g = (unsigned char)gray;
			color.b = (unsigned char)gray;
			color.a = (unsigned char)(alpha * 255.0f);
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
	MenuPcs.DrawRect(0, xCorner, yCorner, (float)((double)w - 16.0), innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
}

#pragma push
#pragma opt_propagation off
void CMenuPcs::CalcSelectCloseAnim()
{
	int activePartyCount = s_Rinfo->m_partyCount;
	char* anchor = lbl_801DD510;
	int partyByteOff;
	int twice;
	int i;
	BonusAnimSprite* alphaSprite;
	int doneCount;
	CCharaPcs::CHandle* handle;
	int total;
	int tribeId;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int idx;

		((BonusAnimHeader*)this->m_bonusAnimPtr)->count =
		    (short)(((BonusAnimHeader*)this->m_bonusAnimPtr)->count - 1);

		{
			int off = 0;
			int i = 0;
			int __p3 = i;
			for (; __p3 < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
				int sprOff = off + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(sprOff + this->m_bonusAnimPtr);
				spr->alpha = FLOAT_80331EB0;
				spr->timer = 0;
				BonusSpriteFlags(spr) = 0;
			}
		}

		idx = 0;
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->kind = 0x16;
			spr->startFrame = 8;
			spr->duration = 8;
			idx++;
		}
		int i1 = 0;
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->startFrame = i1;
			spr->duration = 8;
			BonusSpriteFlags(spr) = 2;
			idx++;
		}
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->kind = 0x1f;
			spr->startFrame = i1;
			spr->duration = i1;
			BonusSpriteFlags(spr) = 2;
			idx++;
		}
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->kind = -4;
			spr->startFrame = i1;
			spr->duration = 8;
		}

		for (; i1 < activePartyCount; i1++) {
			int off = ((i1 + 4) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->x = (short)(int)spr->targetX;
			spr->y = (short)(int)spr->targetY;
			spr->motionX = FLOAT_80331ED0;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
		}

		int base;
		base = activePartyCount + 4;
		s_PlayerTop = (unsigned char)base;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((base + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		s_ArtiTop = (unsigned char)base;
		for (int i = 0; i < 8; i++) {
			int off = ((base + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			spr->startFrame = 0;
			spr->duration = 8;
			BonusSpriteFlags(spr) = 0;
		}

		base += 8;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((base + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((base + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		{
			int delta = (base - 4) << 6;
			for (int i = 0; i < activePartyCount; i++) {
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(off + this->m_bonusAnimPtr);
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->kind = -1;
				spr->x = (short)(src->x + 0x50);
				spr->y = (short)(src->y + 0x48);
				spr->startFrame = src->startFrame;
				spr->duration = 8;
				spr->motionX = FLOAT_80331ED0;
				spr->motionY = kBonusZClearOrigin;
				spr->targetX = (float)spr->x + spr->motionX;
				spr->targetY = (float)spr->y + spr->motionY;
			}
		}

		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	int i0 = 0;
	int off = i0;
	doneCount = 0;
	*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22);

	for (; i0 < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i0++, off += 0x40) {
		int sprOff = off + 8;
		BonusAnimSprite* sprite = (BonusAnimSprite*)(sprOff + this->m_bonusAnimPtr);

		if ((BonusSpriteFlags(sprite) & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = FLOAT_80331EB0;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = kBonusZClearOrigin;
			} else {
				sprite->alpha = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((BonusSpriteFlags(sprite) & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float progress = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	{
		int i = 0;
		int boardOff = i;
		for (; i < activePartyCount; i++) {
			int sprOff = ((4 + i) << 6) + 8;
			BonusAnimSprite* sprite = (BonusAnimSprite*)(sprOff + this->m_bonusAnimPtr);
			int o08 = boardOff + 0x8;
			int o0a = boardOff + 0xa;
			int o40 = boardOff + 0x40;
			int o44 = boardOff + 0x44;
			int centerX = (int)(float)((double)(float)(DOUBLE_80331EE0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			*(short*)(this->m_bonus.m_bonusBoardPtr + o08) = (short)centerX;
			*(short*)(this->m_bonus.m_bonusBoardPtr + o0a) = (short)centerY;
			*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			*(int*)(this->m_bonus.m_bonusBoardPtr + o44) = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)*(int*)(this->m_bonus.m_bonusBoardPtr + o40) < DOUBLE_80331E90) {
				*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = 0;
			}
			{
				int o44b = boardOff + 0x44;
				if ((double)*(int*)(this->m_bonus.m_bonusBoardPtr + o44b) < DOUBLE_80331E90) {
					*(int*)(this->m_bonus.m_bonusBoardPtr + o44b) = 0;
				}
			}
			{
				int o48 = boardOff + 0x48;
				int o4c = boardOff + 0x4c;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o48) = 0x48;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o4c) = 0x58;
			}
			boardOff += 0x50;
		}
	}

	Mtx scaleMtx;
	Mtx rotZMtx;
	Mtx rotYMtx;
	Mtx rotXMtx;
	Vec srcVec;
	Vec dstVec;
	{
		i = 0;
		twice = activePartyCount * 2;
		partyByteOff = i;
		total = activePartyCount + 8;
		for (; i < total; i++, partyByteOff += sizeof(BonusPartySummary)) {
			int sprOff2 = (((int)(signed char)s_PlayerTop + i) << 6) + 8;
			alphaSprite = (BonusAnimSprite*)(sprOff2 + this->m_bonusAnimPtr);
			if (i < activePartyCount) {
				int p = (int)s_Rinfo + partyByteOff;
				tribeId = *(int*)(p + 0x44);
				handle = *(CCharaPcs::CHandle**)(p + 0x20);
				const float* scaleTbl = (const float*)(anchor + 0x5c);
				float modelScale = scaleTbl[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeId = twice + (i - activePartyCount);
				int slotOff = tribeId * 4 + 0x774;
				handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
				if (handle == 0) {
					continue;
				}
				float modelScale = FLOAT_80331F00;
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			}
			if (i < activePartyCount) {
				const float* yposTbl = (const float*)(anchor + 0x4c);
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = yposTbl[tribeId];
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int rotIndex = i - activePartyCount;
				srcVec.x = *(const float*)(anchor + 0x6c);
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotZMtx, 'z', FLOAT_80331F04 * (float)(DOUBLE_80331F08 * (double)rotIndex));
				PSMTXMultVecSR(rotZMtx, &srcVec, &dstVec);
				if ((unsigned int)handle->m_charaNo == 0x44) {
					PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
					PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				}
				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if ((unsigned int)handle->m_charaNo == 0x41 || (unsigned int)handle->m_charaNo == 0x37) {
					modelY += FLOAT_80331F28;
				} else if ((unsigned int)handle->m_charaNo == 0x44) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = alphaSprite->alpha;
		}
	}

	if ((int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count == doneCount) {
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
	}
}
#pragma pop

#pragma push
#pragma optimization_level 3
/*
 * --INFO--
 * PAL Address: 0x8013473c
 * PAL Size: 2844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
namespace {
struct BonusModelFlags {
	unsigned char m_visible : 1;
	unsigned char m_rest : 7;
};
} // namespace

// CalcSelectWait / CalcSelectOpenAnim anchor on &lbl_801DD510 and reach the
// bonus model arrays via fixed offsets (matching the target's pooled-base
// addressing).
#define s_BonusModelYPos ((const float*)(lbl_801DD510 + 0x4C))
#define s_BonusModelScale ((const float*)(lbl_801DD510 + 0x5C))
void CMenuPcs::CalcSelectWait()
{
	int frame;
	int i;
	char* anchor = lbl_801DD510;
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		this->m_menuWindowInfo->state = 3;
		{
			int walkOff;
			i = 0;
			walkOff = 0;
			while (i < (int)*(short*)this->m_bonusAnimPtr) {
				int animBase = this->m_bonusAnimPtr + walkOff + 8;
				*(float*)(animBase + 0x10) = FLOAT_80331EB0;
				*(int*)(animBase + 0x2c) = 3;
				walkOff += 0x40;
				i++;
			}
		}
		{
			int animBase = this->m_bonusAnimPtr;
			short count = *(short*)animBase;
			BonusAnimSprite* cursor = (BonusAnimSprite*)(animBase + count * 0x40 + 8);
			BonusAnimSprite* partySprite = cursor - activePartyCount * 2;
			cursor->kind = 0x20;
			cursor->x = (short)(partySprite->x - 3);
			cursor->y = (short)(partySprite->y - 8);
			cursor->w = 0x40;
			cursor->h = 0x30;
			cursor->mulX = kBonusZClearOrigin;
			cursor->mulY = kBonusZClearOrigin;
			cursor->startFrame = 0;
			cursor->duration = 8;
			cursor->depth = FLOAT_80331EB0;
			cursor->flags = 0;
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
	}

#define statePtr (this->m_bonusStatePtr)
#define currentPartyIndex (*(short*)(this->m_bonusStatePtr + 0xe))
#define selection (*(short*)(this->m_bonusStatePtr + 0x26))
#define confirmSel (*(short*)(this->m_bonusStatePtr + 0x28))
#define delay (*(short*)(this->m_bonusStatePtr + 0x1a))
	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	frame = (int)*(short*)(statePtr + 0x22);

	for (i = 0; i < activePartyCount; i++) {
		if (s_Rinfo->m_party[i].m_rank == currentPartyIndex) {
			break;
		}
	}

	if (this->m_menuWindowInfo->state != 3) {
		if (this->m_menuWindowInfo->state == 1) {
			int padSlot = s_Rinfo->m_party[i].m_partySlot;
			unsigned short repeat = (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1))
			    ? 0
			    : Pad.m_padInputs[(Pad.m_debugPadPort == padSlot) ? 0 : padSlot].repeatButton;
			unsigned short down = (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1))
			    ? 0
			    : Pad.m_padInputs[(Pad.m_debugPadPort == padSlot) ? 0 : padSlot].buttonDown[0];
			if ((repeat & 3) != 0) {
				confirmSel = (short)(confirmSel ^ 1);
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
			if ((repeat & 3) == 0) {
				if ((down & 0x100) != 0) {
					this->m_menuWindowInfo->state = 2;
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				} else if ((down & 0x200) != 0) {
					this->m_menuWindowInfo->state = 2;
					confirmSel = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			}
		} else if (this->m_menuWindowInfo->state == 2) {
			if (this->m_menuWindowInfo->frame - 1 <= 0 && confirmSel == 0) {
				delay = 10;
				*(signed char*)(statePtr + 8) = -1;
			}
		}
	} else {
		if (delay == 0 && currentPartyIndex < activePartyCount) {
			int padSlot = s_Rinfo->m_party[i].m_partySlot;
			unsigned short repeat = (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1))
			    ? 0
			    : Pad.m_padInputs[(Pad.m_debugPadPort == padSlot) ? 0 : padSlot].repeatButton;
			unsigned short down = (Pad.m_debugPadLock != 0 || (padSlot == 0 && Pad.m_debugPadPort != -1))
			    ? 0
			    : Pad.m_padInputs[(Pad.m_debugPadPort == padSlot) ? 0 : padSlot].buttonDown[0];
			if ((repeat & 9) != 0) {
				selection = (short)(selection + 1);
				if (*(short*)(this->m_bonusStatePtr + 0x26) > 7) {
					selection = 0;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			} else if ((repeat & 6) != 0) {
				selection = (short)(selection - 1);
				if (*(short*)(this->m_bonusStatePtr + 0x26) < 0) {
					selection = 7;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			}

			if ((repeat & 0xf) == 0) {
				int unavailableMask = ((int)(signed char)s_Rinfo->pad_0008 | (int)(signed char)s_Rinfo->m_missingArtifactMask)
				    | s_Rinfo->m_party[i].m_ownedArtifactMask;
				if ((down & 0x100) != 0) {
					if (!((unavailableMask & (1 << selection)) == 0)) {
						Sound.PlaySe(4, 0x40, 0x7f, 0);
					} else {
						delay = 10;
						*(unsigned char*)(statePtr + 8) = 1;
						Sound.PlaySe(0x4f, 0x40, 0x7f, 0);
					}
				} else if ((down & 0x200) != 0) {
					short winW;
					short winH;
					GetWinSize(0x18, &winW, &winH, 1);
					SetMcWinInfo((int)winW, (int)winH);
					this->m_menuWindowInfo->state = 0;
					confirmSel = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			}
		} else if (currentPartyIndex < activePartyCount) {
			delay = (short)(delay - 1);
			if (delay == 0) {
				if (*(signed char*)(statePtr + 8) > 0) {
					int bit = 1 << selection;
					s_Rinfo->pad_0008 = (unsigned char)(s_Rinfo->pad_0008 | bit);
					s_Rinfo->m_party[i].m_selectedSlot = selection;
					s_Rinfo->m_party[i].m_selectedItemId = s_Rinfo->m_tempArtifacts[selection];
				}
				if (currentPartyIndex < activePartyCount) {
					currentPartyIndex = (short)(currentPartyIndex + 1);
				}
				*(unsigned char*)(statePtr + 8) = 0;
			}
		} else {
			delay = 0;
		}
	}

	short count2;
	{
		BonusAnimSprite* spr2 = (BonusAnimSprite*)(this->m_bonusAnimPtr + 0x88);
		count2 = *(short*)this->m_bonusAnimPtr;
		spr2->x = (short)(int)s_Base[0][selection * 2 + 2];
		spr2 = (BonusAnimSprite*)(this->m_bonusAnimPtr + 0x88);
		spr2->y = (short)(int)s_Base[0][selection * 2 + 3];
		if (spr2->timer < spr2->duration) {
			spr2->alpha = (float)spr2->timer / (float)spr2->duration;
			spr2->timer++;
		} else {
			spr2->alpha = FLOAT_80331EB0;
		}
	}
	{
		BonusAnimSprite* cursor = (BonusAnimSprite*)(this->m_bonusAnimPtr + (count2 - 1) * 0x40 + 8);
		if (currentPartyIndex < activePartyCount) {
			BonusAnimSprite* partySprite = cursor - (activePartyCount * 2 - currentPartyIndex);
			int pulseFrame = frame % 20 - 10;
			if (pulseFrame < 0) {
				pulseFrame = -pulseFrame;
			}
			cursor->x = (short)(partySprite->x - 3);
			cursor->y = (short)(partySprite->y - 8);
			cursor->alpha = (float)((double)pulseFrame / DOUBLE_80331F30);
		} else {
			cursor->alpha = kBonusZClearOrigin;
		}
	}

	Mtx scaleMtx;
	Mtx rotMtx;
	Mtx tempMtx;
	Mtx tempMtx2;
	Vec srcVec;
	Vec dstVec;
	{
		int doubleCount = activePartyCount * 2;
		for (i = 0; i < activePartyCount + 8; i++) {
			BonusAnimSprite* alphaSprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (((int)(signed char)s_PlayerTop + i) << 6) + 8);
			CCharaPcs::CHandle* handle;
			int tribeOrSlot;
			if (i < activePartyCount) {
				tribeOrSlot = s_Rinfo->m_party[i].m_tribeId;
				handle = s_Rinfo->m_party[i].m_partyHandle;
				float modelScale = *(const float*)((anchor + 0x5C) + (tribeOrSlot << 2));
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeOrSlot = doubleCount + (i - activePartyCount);
				handle = GetBonusDisplayHandleSlots(this)[tribeOrSlot];
				if (handle == 0) {
					continue;
				}
				PSMTXScale(scaleMtx, FLOAT_80331F00, FLOAT_80331F00, FLOAT_80331F00);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = *(const float*)((anchor + 0x4C) + (tribeOrSlot << 2));
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int artifactIndex = i - activePartyCount;
				srcVec.x = *(const float*)(anchor + 0x6C);
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotMtx, 'z', FLOAT_80331F04 * (float)(DOUBLE_80331F08 * (double)artifactIndex));
				PSMTXMultVecSR(rotMtx, &srcVec, &dstVec);

				if (handle->m_charaNo == 0x44u) {
					PSMTXRotRad(tempMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
					PSMTXRotRad(tempMtx2, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, tempMtx2, scaleMtx);
				}

				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if (handle->m_charaNo == 0x41u || handle->m_charaNo == 0x37u) {
					modelY += FLOAT_80331F28;
				} else if (handle->m_charaNo == 0x44u) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			((BonusModelFlags*)&handle->m_model->m_flags10C)->m_visible = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = alphaSprite->alpha;
		}
	}

	if (currentPartyIndex >= activePartyCount && delay == 0) {
		if (*(short*)(statePtr + 0x18) >= 10) {
			*(short*)(statePtr + 0x18) = 0;
			i = 0;
			((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
			for (; i < activePartyCount; i++) {
				int itemId = s_Rinfo->m_party[i].m_selectedItemId;
				int partySlot = s_Rinfo->m_party[i].m_partySlot;
				if (itemId > 0) {
					if (itemId < 0xff) {
						int artIdx = itemId - 0x9f;
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						caravanWork->m_artifacts[artIdx] = static_cast<unsigned short>(itemId);
					} else {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						caravanWork->AddItem(itemId, 0);
					}
				}
			}
		} else {
			*(short*)(statePtr + 0x18) = (short)(*(short*)(statePtr + 0x18) + 1);
		}
	}
}
#undef statePtr
#undef currentPartyIndex
#undef selection
#undef confirmSel
#undef delay
#pragma pop

#pragma push
#pragma optimization_level 3
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
	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		return;
	}

	int idx;
	int activePartyCount = s_Rinfo->m_partyCount;
	BonusAnimSprite* sprite;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int off;
	int doubleCount;
	int modelIndex = 0;
	int i;
	int kind;
	doubleCount = activePartyCount * 2;
	off = modelIndex << 6;
	int lastKind =  (int)(unsigned int)(0);
	BonusAnimSprite* artiSprite = 0;
	for (i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; off += 0x40, i++) {
		sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);
		kind = sprite->kind;
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
				CCharaPcs::CHandle* handle;
				if (modelIndex < activePartyCount) {
					for (int j = 0; j < activePartyCount; j++) {
						if (modelIndex == s_Rinfo->m_party[j].m_rank) {
							idx = j;
							break;
						}
					}
					handle = s_Rinfo->m_party[idx].m_partyHandle;
					SetProjection(modelIndex);
				} else {
					idx = doubleCount + (modelIndex - activePartyCount);
					handle = GetBonusDisplayHandleSlots(this)[idx];
					if (handle == 0) {
						lastKind = kind;
						modelIndex++;
						continue;
					}
					SetProjection(idx);
				}
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				if (modelIndex >= activePartyCount) {
					PartPcs.DrawMenuIdx(*reinterpret_cast<int*>(this->m_bonusListPtr + idx * 0x524 + 4));
				}
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));
				if (sprite->kind == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
				}
				MenuPcs.DrawRect(0,
				    (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
				    (float)sprite->w, (float)sprite->h,
				    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
				if (sprite->kind == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
				}
				lastKind = sprite->kind;
			}
		}
	}

	float artiAlpha = artiSprite->alpha;
	if (!((double)artiAlpha <= DOUBLE_80331E90)) {
		_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
		GXColor markColor;
		markColor.r = 0xFF;
		markColor.g = 0xFF;
		markColor.b = 0xFF;
		markColor.a = (unsigned char)(FLOAT_80331E98 * artiAlpha);
		GXSetChanMatColor(GX_COLOR0A0, markColor);
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));

		unsigned int activeMask = 0;
		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			int selection = s_Rinfo->m_party[i].m_selectedSlot;
			if (selection >= 0) {
				activeMask |= 1 << selection;
			}
		}

		{
			int i = 0;
			int markOff = i;
			int __p3 = i;
			for (; __p3 < 8; i++, markOff += 8) {
				if ((activeMask & (1 << i)) == 0) {
					continue;
				}
				float x = s_Base[0][i * 2 + 2] + FLOAT_80331E9C;
				float y = s_Base[0][i * 2 + 3] + FLOAT_80331EA0;
				MenuPcs.DrawRect(0, x, y, FLOAT_80331EA4, FLOAT_80331EA8, kBonusZClearOrigin, kBonusZClearOrigin, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
			}
		}
	}

	DrawInit();
	CFont* font = this->m_fonts[0];
	font->SetMargin(FLOAT_80331EB0);
	font->SetShadow(1);
	font->SetScale(FLOAT_80331F38);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[268];
	{
		int i = 0;
		int off2 = textIndex << 6;
		int __p21 = textIndex;
		for (; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count && __p21 < activePartyCount; off2 += 0x40, i++) {
			sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off2 + 8);
			if (sprite->kind != -1) {
				continue;
			}
			CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha));
			font->SetColor(color.color);

			for (int j = 0; j < activePartyCount; j++) {
				if (textIndex == s_Rinfo->m_party[j].m_rank) {
					idx = j;
					break;
				}
			}
			int partySlot = s_Rinfo->m_party[idx].m_partySlot;
			if (textIndex < activePartyCount) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			}

			float x = (float)sprite->x + sprite->motionX;
			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= FLOAT_80331F3C;
			}
			font->SetPosX(x);
			font->SetPosY(y - FLOAT_80331F3C);
			font->Draw(text);
			textIndex++;
		}
	}

	if (*(short*)(this->m_bonusStatePtr + 0x1c) == 4
	    && s_Rinfo->m_tempArtifacts[*(short*)(this->m_bonusStatePtr + 0x26)] > 0) {
		{
			int off3 = 0;
			for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; off3 += 0x40, i++) {
				int __p2 = off3;
				sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + __p2 + 8);
				if (sprite->kind == -3) {
					break;
				}
			}
		}

		font = this->m_fonts[1];
		font->SetMargin(FLOAT_80331EB0);
		font->SetShadow(0);
		font->SetScaleX(FLOAT_80331F40);
		font->SetScaleY(FLOAT_80331F44);
		font->DrawInit();
		CColor color(0xFF, 0xFF, 0xFF, 0xFF);
		font->SetColor(color.color);

		idx = (int)s_Rinfo->m_tempArtifacts[*(short*)(this->m_bonusStatePtr + 0x26)];
		char* title = Game.m_cFlatDataArr[1].TableStrings(0)[idx * 5 + 4];
		float centerX = (float)((double)sprite->x + (double)(float)sprite->w * DOUBLE_80331E78);
		float centerY = (float)((double)sprite->y + (double)(float)sprite->h * DOUBLE_80331E78);
		font->SetPosX((float)-(DOUBLE_80331E78 * (double)font->GetWidth(title) - (double)centerX));
		font->SetPosY(centerY - FLOAT_80331F48 - FLOAT_80331F3C);
		font->Draw(title);

		char* source = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xA9C) char[0x200];
		if ((source == 0) && ((unsigned int)System.m_execParam >= 1)) {
			System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DD598), const_cast<char*>(s_bonus_menu_cpp), 0xA9F);
		}
		memset(source, 0, 0x200);
		char* converted = new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0xAA5) char[0x200];
		if ((converted == 0) && ((unsigned int)System.m_execParam >= 1)) {
			System.Printf(const_cast<char*>(s_pcts_pctd_Error_memory_allocation_error_801DD598), const_cast<char*>(s_bonus_menu_cpp), 0xAA8);
		}
		memset(converted, 0, 0x200);
		strcpy(source, Game.m_cFlatDataArr[1].TableStrings(6)[idx]);
		CMes::MakeAgbString(converted, source, 0, 0);
		strlen(converted);

		float lineY = centerY - FLOAT_80331F4C - FLOAT_80331F50;
		for (int line = 0;; line++) {
			char* lineText = (line != 0) ? strtok(0, const_cast<char*>(lbl_80331F54)) : strtok(converted, const_cast<char*>(lbl_80331F54));
			if (lineText == 0) {
				break;
			}
			font->SetPosX((float)-(DOUBLE_80331E78 * (double)font->GetWidth(lineText) - (double)centerX));
			font->SetPosY(lineY - FLOAT_80331F3C);
			font->Draw(lineText);
			lineY += FLOAT_80331F58;
		}

		delete[] source;
		delete[] converted;
	}

	DrawInit();
	if (this->m_menuWindowInfo->state == 3) {
		return;
	}

	DrawMcWin(-1, 1);
	if (this->m_menuWindowInfo->state == 1) {
		DrawMcWinMess(0x18, 1);
		DrawInit();
		float cursorY = (float)(this->m_menuWindowInfo->y + this->m_menuWindowInfo->height - 0x3e);
		float cursorX = (float)GetYesNoXPos((int)*(short*)(this->m_bonusStatePtr + 0x28));
		DrawCursor((int)cursorX, (int)cursorY, FLOAT_80331EB0);
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x80135d60
 * PAL Size: 4668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_strength_reduction off
#pragma opt_propagation off
#pragma push
#pragma opt_lifetimes off
void CMenuPcs::CalcSelectOpenAnim()
{
	int activePartyCount = s_Rinfo->m_partyCount;
	int frame;
	int doneCount;
	char* anchor = lbl_801DD510;
	int partyByteOff;
	int twice;
	float* scale4;
	BonusAnimSprite* iconSprite;
	int i;
	int tribeId;
	CCharaPcs::CHandle* handle;
	int total;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int idx;

		this->m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset((void*)this->m_bonusAnimPtr, 0, sizeof(BonusAnimList));

		idx = 0;
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = 0x16;
			spr->y = 0;
			spr->x = 0;
			spr->w = 0x280;
			spr->h = 0x1c0;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 0;
			spr->depth = FLOAT_80331EB0;
			BonusSpriteFlags(spr) = 3;
			idx = 1;
		}
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = -3;
			spr->x = 0xf0;
			spr->y = 0x38;
			spr->w = 0x168;
			spr->h = 0x148;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			idx = 2;
		}
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = 0x1f;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0x80;
			spr->h = 0x78;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 9999;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F5C;
			spr->motionY = FLOAT_80331F5C;
			BonusSpriteFlags(spr) = 2;
			idx = 3;
		}
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = -4;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0x70;
			spr->h = 0x68;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			idx = 4;
		}

		int top;
		int y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			int partySlot;
			BonusSummaryData* p = s_Rinfo;
			for (int j = 0; activePartyCount > j; j++) {
				if (i == p->m_party[0].m_rank) {
					partySlot = s_Rinfo->m_party[j].m_partySlot;
					break;
				}
				p = (BonusSummaryData*)((int)p + 0x2c);
			}
			int off = ((4 + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = 0x18;
			spr->x = ((1 <= i) && (i <= 2)) ? 0x30 : 0x48;
			spr->y = y;
			spr->w = 0x60;
			spr->h = 0x58;
			spr->mulX = (float)((partySlot & 1) ? spr->w : 0);
			spr->mulY = (float)((partySlot >> 1) ? spr->h : 0);
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			BonusSpriteFlags(spr) = 1;
			y += 0x60;
		}

		top = activePartyCount + 4;
		s_PlayerTop = (unsigned char)top;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((top + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = -2;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0;
			spr->h = 0;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = (spr - activePartyCount)->startFrame;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			BonusSpriteFlags(spr) = 1;
		}

		top += activePartyCount;
		s_ArtiTop = (unsigned char)top;
		{
			int start = 10;
			for (int i = 0; i < 8; i++) {
				int off = ((top + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -2;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = start;
				spr->startFrame = (int)(FLOAT_80331F64 * (float)spr->startFrame);
				spr->duration = 0x21;
				spr->depth = FLOAT_80331EB0;
				BonusSpriteFlags(spr) = 1;
				start += 5;
			}
		}

		int copyDelta = top + 4;
		top += 8;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((top + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			int __p21 = copyDelta;
			*spr = *(spr - __p21);
			spr->y = (short)(spr->y + 0x20);
			spr->w = 0xA8;
			spr->h = 0x38;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = FLOAT_80331F68;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			BonusSpriteFlags(spr) = 1;
		}

		top += activePartyCount;
		y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((top + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = 0x19;
			spr->x = ((1 <= i) && (i <= 2)) ? 8 : 0x20;
			spr->y = y;
			spr->w = 0x38;
			spr->h = 0x28;
			spr->mulX = (float)(i * spr->w);
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			BonusSpriteFlags(spr) = 1;
			y += 0x60;
		}

		top += activePartyCount;
		int nameDelta = top - 4;
		for (int i = 0; i < activePartyCount; i++) {
			int off = ((top + i) << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			BonusAnimSprite* prev = spr - nameDelta;
			spr->kind = -1;
			spr->x = (short)(prev->x + 0x50);
			spr->y = (short)(prev->y + 0x48);
			spr->w = 0;
			spr->h = 0;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = prev->startFrame;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			BonusSpriteFlags(spr) = 1;
		}

		top += activePartyCount;
		{
			CMenuPcs::Sprt2* p3 = reinterpret_cast<CMenuPcs::Sprt2*>(this->m_bonusAnimPtr + 0xc8);
			ArtiBaseInfoInit(reinterpret_cast<CMenuPcs::Sprt2*>((int)p3 - 0x80), p3);
		}
		{
			int anim = this->m_bonusAnimPtr;
			int boardOff = activePartyCount * 2;
			boardOff = boardOff * 0x50;
			for (int i = 0; i < 8; i++) {
				int o04 = boardOff + 0x4;
				int o08 = boardOff + 0x8;
				int o0a = boardOff + 0xa;
				int o0c = boardOff + 0xc;
				int o0e = boardOff + 0xe;
				int o10 = boardOff + 0x10;
				int o14 = boardOff + 0x14;
				int o18 = boardOff + 0x18;
				int o40 = boardOff + 0x40;
				int o44 = boardOff + 0x44;
				int o48 = boardOff + 0x48;
				int o4c = boardOff + 0x4c;
				float* fl = (float*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x1c);
				fl[2] = kBonusZClearOrigin;
				fl[1] = kBonusZClearOrigin;
				fl[0] = kBonusZClearOrigin;
				fl[5] = kBonusZClearOrigin;
				fl[4] = kBonusZClearOrigin;
				fl[3] = kBonusZClearOrigin;
				fl[8] = FLOAT_80331EB0;
				fl[7] = FLOAT_80331EB0;
				fl[6] = FLOAT_80331EB0;
				*(int*)(this->m_bonus.m_bonusBoardPtr + boardOff) = 0;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o04) = 0;
				int centerX = (int)((double)(float)((double)*(short*)(anim + 0x4c) * DOUBLE_80331E78 + (double)*(short*)(anim + 0x48)) - DOUBLE_80331EE8);
				*(short*)(this->m_bonus.m_bonusBoardPtr + o08) = (short)centerX;
				int centerY = (int)((double)(float)((double)*(short*)(anim + 0x4e) * DOUBLE_80331E78 + (double)*(short*)(anim + 0x4a)) - DOUBLE_80331EF0);
				*(short*)(this->m_bonus.m_bonusBoardPtr + o0a) = (short)centerY;
				*(short*)(this->m_bonus.m_bonusBoardPtr + o0c) = 0x280;
				*(short*)(this->m_bonus.m_bonusBoardPtr + o0e) = 0x1C0;
				*(float*)(this->m_bonus.m_bonusBoardPtr + o10) = kBonusZClearOrigin;
				*(float*)(this->m_bonus.m_bonusBoardPtr + o14) = kBonusZClearOrigin;
				*(float*)(this->m_bonus.m_bonusBoardPtr + o18) = FLOAT_80331F6C;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = 0;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o44) = 0;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o48) = 0x280;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o4c) = 0x1C0;
				boardOff += 0x50;
			}
		}

		((BonusAnimHeader*)this->m_bonusAnimPtr)->count = (short)top;
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	frame = (int)*(short*)(this->m_bonusStatePtr + 0x22);
	int i0 = 0;
	int off = i0;
	doneCount = 0;

	for (; i0 < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i0++, off += 0x40) {
		int sprOff = off + 8;
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);

		if ((BonusSpriteFlags(sprite) & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = kBonusZClearOrigin;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = FLOAT_80331EB0;
			} else {
				sprite->alpha = (float)((1.0 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((BonusSpriteFlags(sprite) & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float progress = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	{
		int i = 0;
		int boardOff = i;
		for (; i < activePartyCount; i++) {
			int sprOff = ((4 + i) << 6) + 8;
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);
			int o08 = boardOff + 0x8;
			int o0a = boardOff + 0xa;
			int o40 = boardOff + 0x40;
			int o44 = boardOff + 0x44;
			int centerX = (int)(float)((double)(float)(4.0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			*(short*)(this->m_bonus.m_bonusBoardPtr + o08) = (short)centerX;
			*(short*)(this->m_bonus.m_bonusBoardPtr + o0a) = (short)centerY;
			*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			*(int*)(this->m_bonus.m_bonusBoardPtr + o44) = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)*(int*)(this->m_bonus.m_bonusBoardPtr + o40) < 0.0) {
				*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = 0;
			}
			{
				int o44b = boardOff + 0x44;
				if ((double)*(int*)(this->m_bonus.m_bonusBoardPtr + o44b) < 0.0) {
					*(int*)(this->m_bonus.m_bonusBoardPtr + o44b) = 0;
				}
			}
			{
				int o48 = boardOff + 0x48;
				int o4c = boardOff + 0x4c;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o48) = 0x48;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o4c) = 0x58;
			}
			boardOff += 0x50;
		}
	}

	Mtx scaleMtx;
	Mtx rotZMtx;
	Mtx rotYMtx;
	Mtx rotXMtx;
	Vec srcVec;
	Vec dstVec;
	{
		i = 0;
		twice = activePartyCount * 2;
		partyByteOff = i;
		scale4 = (float*)(anchor + 0x6c);
		total = activePartyCount + 8;
		for (; i < total; i++, partyByteOff += sizeof(BonusPartySummary)) {
			int sprOff2 = (((int)(signed char)s_PlayerTop + i) << 6) + 8;
			iconSprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff2);
			if (i < activePartyCount) {
				int p = (int)s_Rinfo + partyByteOff;
				tribeId = *(int*)(p + 0x44);
				handle = *(CCharaPcs::CHandle**)(p + 0x20);
				const float* scaleTbl = (const float*)(anchor + 0x5c);
				float modelScale = scaleTbl[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeId = twice + (i - activePartyCount);
				int slotOff = tribeId * 4 + 0x774;
				handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
				if (handle == 0) {
					continue;
				}
				PSMTXScale(scaleMtx, FLOAT_80331F00, FLOAT_80331F00, FLOAT_80331F00);
			}
			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				const float* yposTbl = (const float*)(anchor + 0x4c);
				scaleMtx[1][3] = yposTbl[tribeId];
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int duration = iconSprite->duration;
				int artifactIndex = i - activePartyCount;
				int fcvIndex = duration / 5;
				int rem = 8 - artifactIndex;
				int phase = (int)(((double)duration / 10.0) * (double)(rem + 2));
				float rate = (float)(450.0 / (double)(float)duration);

				if (frame == iconSprite->startFrame && *(signed char*)&this->m_bonusCursorFlag == 0) {
					this->m_bonusCursorFlag = 1;
					Sound.PlaySe(0x4d, 0x40, 0x7f, 0);
				}

				float angle;
				if (frame < iconSprite->startFrame) {
					srcVec.x = scale4[2];
					angle = FLOAT_80331F78;
				} else if (iconSprite->timer >= phase) {
					srcVec.x = ((const float*)(anchor + 0x5c))[4];
					angle = (float)(DOUBLE_80331F80 * (double)rem);
				} else {
					int last = iconSprite->timer - 1;
					if (last <= fcvIndex) {
						srcVec.x = scale4[2] -
						    (float)last * ((scale4[2] - scale4[1]) / (float)fcvIndex);
					} else {
						srcVec.x = scale4[1] -
						    ((scale4[1] - ((const float*)(anchor + 0x5c))[4]) /
						    ((float)phase - (float)fcvIndex)) *
						    (float)(last - fcvIndex);
					}
					angle = (float)(DOUBLE_80331F88 + (double)(rate * (float)last));
				}
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotZMtx, 'z', FLOAT_80331F04 * angle);
				PSMTXMultVecSR(rotZMtx, &srcVec, &dstVec);

				if ((unsigned int)handle->m_charaNo == 0x44) {
					PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
					PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				}

				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if ((unsigned int)handle->m_charaNo == 0x41 || (unsigned int)handle->m_charaNo == 0x37) {
					modelY += FLOAT_80331F28;
				} else if ((unsigned int)handle->m_charaNo == 0x44) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = iconSprite->alpha;
		}
	}

	if ((int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count == doneCount) {
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x80136f9c
 * PAL Size: 2452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
void CMenuPcs::DrawResultCloseAnim()
{
	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;
	int off = modelIndex << 6;
	int partyOff = 0;
	for (int i = 0; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		int sprOff = off + 8;
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);

		if (sprite->kind >= 0 || sprite->kind == -2) {
			if (sprite->kind == -2) {
				CCharaPcs::CHandle* handle;
				if (modelIndex < activePartyCount) {
					int pOff = partyOff + 0x20;
					handle = *(CCharaPcs::CHandle**)((int)s_Rinfo + pOff);
				} else if (modelIndex / activePartyCount > 1) {
					modelIndex++;
					partyOff += 0x2c;
					continue;
				} else {
					int slotOff = (modelIndex - activePartyCount) * 4 + 0x774;
					handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
				}

				if ((double)handle->m_model->m_lightAlpha <= DOUBLE_80331E90) {
					modelIndex++;
					partyOff += 0x2c;
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
				partyOff += 0x2c;
				continue;
			} else {
				if (lastKind < 0) {
					DrawInit();
				}
				if (lastKind != 0x17 && sprite->kind == 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				} else if (lastKind == 0x17 && sprite->kind != 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}

				_GXColor colors[4];
				if (sprite->kind == 0x17) {
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
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				}
				if (sprite->kind != 0x17) {
					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				}
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

				if (sprite->kind == 0x17) {
					if (sprite->duration <= sprite->timer) {
						lastKind = sprite->kind;
						continue;
					}
					{
						float x = (float)sprite->x;
						float y = (float)sprite->y;
						float fillWidth;
						if (sprite->duration > sprite->timer) {
							fillWidth = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)(sprite->timer - 1));
							if (fillWidth < kBonusZClearOrigin) {
								fillWidth = kBonusZClearOrigin;
							}
						} else {
							fillWidth = kBonusZClearOrigin;
						}
						float mulX = sprite->mulX;
						fillWidth *= (float)sprite->w;
						if (fillWidth > kBonusZClearOrigin) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    mulX, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
							x += fillWidth;
						}
						if (fillWidth < (float)sprite->w) {
							colors[1].r = 0xFF;
							colors[1].g = 0xFF;
							colors[1].b = 0xFF;
							colors[1].a = 0;
							colors[3].r = 0xFF;
							colors[3].g = 0xFF;
							colors[3].b = 0xFF;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)(DOUBLE_80331ED8 / (double)sprite->duration) * (float)sprite->w, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
						}
					}
				} else {
					if ((signed char)s_CntTop <= i && i < (signed char)s_CntTop + activePartyCount) {
						int value = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
						int digits[3];
						int digitCount;

						if (value >= 100) {
							digitCount = 3;
							digits[0] = value / 100;
							value %= 100;
							digits[1] = value / 10;
							digits[2] = value % 10;
						} else if (value >= 10) {
							digitCount = 2;
							digits[0] = value / 10;
							digits[1] = value % 10;
						} else {
							digitCount = 1;
							digits[0] = value;
						}

						float digitX = (float)((DOUBLE_80331EC8 * (double)sprite->w - (float)(digitCount * sprite->w)) * DOUBLE_80331E78 + (double)sprite->x);
						float digitW = (float)sprite->w;
						int* dp = digits;
						for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
							MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
							    (float)(sprite->w * *dp), sprite->mulY,
							    sprite->depth, sprite->depth, kBonusZClearOrigin);
							digitX += digitW;
							dp++;
						}
					} else {
						MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
						    (float)sprite->w, (float)sprite->h,
						    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
					}
				}
				lastKind = sprite->kind;
			}
		}
	}

	DrawInit();
	CFont* font0 = this->m_fonts[0];
	CFont* font = font0;
	font0->SetMargin(FLOAT_80331EB0);
	font0->SetShadow(1);
	font0->SetScale(FLOAT_80331F38);
	font0->SetTlut(7);
	font0->DrawInit();

	int textIndex = 0;
	char text[128];
	{
		int i = 0;
		int off2 = textIndex << 6;
		for (; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off2 += 0x40) {
			int sprOff = off2 + 8;
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);
			if (sprite->kind == -1) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha)).color);

				int partyIndex = textIndex % activePartyCount;
				int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
				if (textIndex < activePartyCount) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
					strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
				} else {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
					strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[(int)caravanWork->m_bonusCondition * 2 + 1]);
				}

				float x = (float)sprite->x + sprite->motionX;
				float y = (float)sprite->y + sprite->motionY;
				if (textIndex < activePartyCount) {
					y -= FLOAT_80331F3C;
				}
				font->SetPosX(x);
				font->SetPosY(y - FLOAT_80331F3C);
				font->Draw(text);

				textIndex++;
				if (textIndex == activePartyCount) {
					CFont* font1 = this->m_fonts[1];
					font = font1;
					font1->SetMargin(FLOAT_80331EB0);
					font1->SetShadow(0);
					font1->SetScaleX(FLOAT_80331F90);
					font1->SetScaleY(FLOAT_80331EB0);
					font1->DrawInit();
				}
			}
		}
	}
	DrawInit();
}
#pragma pop
#undef s_BonusModelYPos
#undef s_BonusModelScale
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x80137930
 * PAL Size: 8676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_loop_invariants off
#pragma opt_strength_reduction off
#pragma opt_dead_assignments off
#pragma opt_propagation off
void CMenuPcs::CalcResultCloseAnim()
{
	int doneCount;
	int delta;
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		for (int i = 0; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
			((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i].timer = 0;
			((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i].motionX = kBonusZClearOrigin;
			((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i].motionY = kBonusZClearOrigin;
		}

		{
			int idx = 0;
			BonusAnimSprite* spr = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[idx];
			spr->startFrame = 9999;
			spr->flags = 3;
		}

		for (int i = 0; activePartyCount > i; i++) {
			int sprite = this->m_bonusAnimPtr + (i + 1) * 0x40 + 8;
			*(int*)(sprite + 0x24) = 0x10;
		}

		// iconBase block: src = frameBase (back = activePartyCount sprites); dance
		int base = activePartyCount + 1;
		delta = base - 1;
		int __p13 = activePartyCount;
		int byteDelta = delta * 0x40;
		for (int i = 0; i < __p13; i++) {
			int spr = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
			int src = spr - byteDelta;
			*(int*)(spr + 0x24) = *(int*)(src + 0x24) + *(int*)(src + 0x28);
			*(int*)(spr + 0x2c) = 1;
			*(float*)(spr + 0x38) = (float)*(short*)spr;
			*(float*)(spr + 0x30) = FLOAT_80331ED0;
			*(short*)spr = (short)(int)((float)*(short*)spr - *(float*)(spr + 0x30));
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
			int sprite =  (int)(long)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x24) = 0;
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
		{
			int back = base - (activePartyCount + 1);
			int byteDelta = back * 0x40;
			for (int i = 0; activePartyCount > i; i++) {
				int spr = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
				int src = spr - byteDelta;
				*(int*)(spr + 0x24) = *(int*)(src + 0x24);
				*(int*)(spr + 0x2c) = 1;
				*(float*)(spr + 0x38) = (float)*(short*)spr;
				*(float*)(spr + 0x30) = FLOAT_80331ED0;
				*(short*)spr = (unsigned short)(int)((float)*(short*)spr - *(float*)(spr + 0x30));
			}
		}

		// sprites[digitEchoBase + pc].startFrame = sprites[1].startFrame
		base += activePartyCount;
		{
			int sprite = this->m_bonusAnimPtr + base * 0x40 + 8;
			int __p9 = sprite;
			*(int*)(__p9 + 0x24) = *(int*)(this->m_bonusAnimPtr + 0x6c);
		}
		base += 1;
		s_CntTop = (signed char)base;

		// countTop block: startFrame = 8, duration = 8
		for (int i = 0; i < activePartyCount; i++) {
			int sprite = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
			*(int*)(sprite + 0x24) = 8;
			*(int*)(sprite + 0x28) = 8;
		}

		// extraBase block: src = iconBase (back = base - (pc+1)); dance
		base += activePartyCount;
		{
			int back = base - (activePartyCount + 1);
			int byteDelta = back * 0x40;
			for (int i = 0; i < activePartyCount; i++) {
				int spr = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
				int src = spr - byteDelta;
				*(int*)(spr + 0x24) = *(int*)(src + 0x24);
				*(int*)(spr + 0x2c) = 1;
				*(float*)(spr + 0x38) = (float)*(short*)spr;
				*(float*)(spr + 0x30) = FLOAT_80331ED0;
				*(short*)spr = (unsigned short)(int)((float)*(short*)spr - *(float*)(spr + 0x30));
			}
		}

		// extraBase + pc block: flags = 0
		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			int sprite =  (s32)(this->m_bonusAnimPtr + (base + i) * 0x40 + 8);
			*(int*)(sprite + 0x24) = 0;
		}

		// extraBase + 2*pc block: src = extraBase + pc (back = activePartyCount sprites); dance
		base += activePartyCount;
		{
			int back = activePartyCount;
			int byteDelta = back * 0x40;
			for (int i = 0; i < activePartyCount; i++) {
				int spr = this->m_bonusAnimPtr + (base + i) * 0x40 + 8;
				int src = spr - byteDelta;
				*(int*)(spr + 0x24) = *(int*)(src + 0x24);
				*(int*)(spr + 0x2c) = 1;
				*(float*)(spr + 0x38) = (float)*(short*)spr;
				*(float*)(spr + 0x30) = FLOAT_80331ED0;
				*(short*)spr = (short)(int)((float)*(short*)spr - *(float*)(spr + 0x30));
			}
		}

		{
			int i = 0;
			int off = i;
			for (; i < *(short*)this->m_bonusAnimPtr; i++) {
				if (kBonusZClearOrigin == *(float*)(this->m_bonusAnimPtr + off + 0x38)) {
					*(float*)(this->m_bonusAnimPtr + off + 0x40) = (float)(int)*(short*)(this->m_bonusAnimPtr + off + 8);
				}
				int s = this->m_bonusAnimPtr + off;
				if (kBonusZClearOrigin == *(float*)(s + 0x3c)) {
					*(float*)(s + 0x44) = (float)(int)*(short*)(s + 10);
				}
				off += 0x40;
			}
		}

		((short*)this->m_bonusAnimPtr)[3] = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	doneCount = 0;
	*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22);

	int off = 0;
	for (int i = 0; i < *(short*)this->m_bonusAnimPtr; i++) {
		int sprOff = off + 8;
		int __p10 = sprOff;
		int __p4 = __p10;
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + __p4);

		if ((BonusSpriteFlags(sprite) & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (sprite->startFrame > frame) {
				sprite->alpha = FLOAT_80331EB0;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = kBonusZClearOrigin;
			} else {
				sprite->alpha = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((BonusSpriteFlags(sprite) & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			float progress = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)sprite->timer);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}

		off += 0x40;
	}

	{
		int i = 0;
		int base2 = activePartyCount + 1;
		for (; i < activePartyCount; i++) {
			int sprOff2 = ((base2 + i) << 6) + 8;
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff2);
			int centerX = (int)(float)((double)(float)(DOUBLE_80331EE0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_centerX = (short)centerX;
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_centerY = (short)centerY;
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenX = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenY = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenX < DOUBLE_80331E90) {
				((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenX = 0;
			}
			if ((double)((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenY < DOUBLE_80331E90) {
				((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenY = 0;
			}
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenWidth = 0x48;
			((MenuBoardEntry*)this->m_bonus.m_bonusBoardPtr)[i].m_screenHeight = 0x58;
		}
	}
	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	{
		int total2 = activePartyCount * 2;
		int i = 0;
		int alphaOff = (total2 + 1) * 0x40;
		int partyOff = i;
		for (; i < total2; i++) {
			int __p2 =   (int)(unsigned int)((alphaOff - 0));
			int aOff = __p2 + 0x8;
			BonusAnimSprite* alphaSprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + aOff);
			CCharaPcs::CHandle* handle;
			if (!(!(i < activePartyCount))) {
				int p = (int)s_Rinfo + partyOff;
				handle = *(CCharaPcs::CHandle**)(p + 0x20);
				delta = *(int*)(p + 0x44);
			} else {
				int slotOff = (i - activePartyCount) * 4 + 0x774;
				handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
			}
			if (i < activePartyCount) {
				float modelScale = s_BonusModelScale[delta];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				PSMTXScale(scaleMtx, FLOAT_80331EB0, FLOAT_80331EB0, FLOAT_80331EB0);
			}

			if (i / activePartyCount == 1) {
				PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F94);
				PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F04 * *reinterpret_cast<float*>(this->m_bonusStatePtr));
				PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_BonusModelYPos[delta];
			} else {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			if (i < activePartyCount) {
				handle->m_model->m_lightAlpha = FLOAT_80331EB0;
			} else {
				handle->m_model->m_lightAlpha = alphaSprite->alpha;
			}
			alphaOff += 0x40;
			partyOff += 0x2c;
		}
	}

	if (*(short*)this->m_bonusAnimPtr == doneCount) {
		((short*)this->m_bonusAnimPtr)[3] = 1;
	}
}
#pragma pop

#pragma push
#pragma opt_dead_assignments off
#pragma optimization_level 3
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
	int i = 0;
	int off;
	off = i << 6;
	for (; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++, off += 0x40) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off + 8);

		if (sprite->kind >= 0 || sprite->kind == -2) {
			if (sprite->kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex < activePartyCount * 2) {
					int __p11 = modelIndex;
					handle = GetBonusDisplayHandleSlots(this)[__p11 - activePartyCount];
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
				_GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (unsigned char)(sprite->alpha * 255.0f);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

				if ((signed char)s_CntTop <= i && i < (signed char)s_CntTop + activePartyCount) {
					int total = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
					int value;
					if (*(short*)(this->m_bonusStatePtr + 0x10) == 0) {
						double frame = (double)*(short*)(this->m_bonusStatePtr + 0x22) - DOUBLE_80331F98;
						if (frame <= DOUBLE_80331E90) {
							value = 0;
						} else if (frame < (double)total) {
							value = (int)frame;
						} else {
							value = total;
						}
					} else {
						value = total;
					}
					int digits[3];
					int digitCount;

					if (value >= 100) {
						digitCount = 3;
						digits[0] = value / 100;
						value %= 100;
						digits[1] = value / 10;
						digits[2] = value % 10;
					} else if (value >= 10) {
						digitCount = 2;
						digits[0] = value / 10;
						digits[1] = value % 10;
					} else {
						digitCount = 1;
						digits[0] = value;
					}

					float digitW = (float)sprite->w;
					float digitX = (float)((DOUBLE_80331EC8 * (double)sprite->w - (float)(digitCount * sprite->w)) * DOUBLE_80331E78 + (double)sprite->x);
					for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
						MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
						    (float)(sprite->w * digits[digitIndex]), sprite->mulY,
						    sprite->depth, sprite->depth, kBonusZClearOrigin);
						digitX += digitW;
					}
				} else {
					MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
					    (float)sprite->w, (float)sprite->h,
					    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
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
	int __p13 = i;
	for (int i = 0; __p13 < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i++) {
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + (i << 6) + 8);
		if (sprite->kind == -1) {
			CColor color(0xFF, 0xFF, 0xFF, 0xFF);
			font->SetColor(color.color);

			int partyIndex = textIndex % activePartyCount;
			int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
			if (textIndex < activePartyCount) {
				int __p12 = partySlot;
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[__p12]);
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			} else {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
				int strIdx = (int)caravanWork->m_bonusCondition * 2 + 1;
				int __p2 = strIdx;
				strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[__p2]);
			}

			float x = (float)sprite->x + sprite->motionX;
			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= FLOAT_80331F3C;
			}
			font->SetPosX(x);
			font->SetPosY(y - FLOAT_80331F3C);
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
#pragma pop

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
	const int activePartyCount =  (int)(unsigned int)(s_Rinfo->m_partyCount);

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int countTop = ((BonusAnimHeader*)this->m_bonusAnimPtr)->count;
		int partyByteOff = 0;
		short y = 0x28;
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

		int newCount = countTop + activePartyCount;
		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = GetBonusDisplayHandleSlots(this)[i];
			if (handle != 0) {
				handle->m_model->m_lightAlpha = 0.0f;
			}
		}

		((BonusAnimHeader*)this->m_bonusAnimPtr)->count = (short)newCount;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) == 0) {
		*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	}

	int countTop = (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count - activePartyCount;
	int frame;
	frame = (int)*(short*)(this->m_bonusStatePtr + 0x22) - 8;

	for (int i = 0; i < activePartyCount; i++) {
		BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[countTop + i];
		if (*(short*)(this->m_bonusStatePtr + 0x10) != 0) {
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->alpha = 1.0f;
		} else {
			int value = s_Rinfo->m_party[i].m_totalValue;
			int __p27 = value;
			if (frame == __p27) {
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
	int tribeId;
	for (int i = 0; activePartyCount > i * 2; i++) {
		CCharaPcs::CHandle* handle;
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

		handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		handle->m_model->m_lightAlpha = 1.0f;
	}

	if (*(short*)(this->m_bonusStatePtr + 0x10) == 0 && frame >= 0 && !(s_Rinfo->m_winnerTotalValue < frame)) {
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
			int padIndex = s_Rinfo->m_party[i].m_partySlot;
			unsigned short down;
			unsigned char padLocked = (padLock != 0 || (padIndex == 0 && padRemap != -1));
			if (padLocked) {
				down = 0;
			} else {
				unsigned int resolvedIndex = (padRemap == (int)padIndex) ? 0 : padIndex;
				down = Pad.m_padInputs[resolvedIndex].buttonDown[0];
			}
			unsigned int __p28 = buttons;
			buttons = (unsigned short)(__p28 | down);
		}
		if ((buttons & 0x300) != 0) {
			Sound.PlaySe(2, 0x40, 0x7f, 0);
			((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
		}
	}
}

#pragma push
#pragma opt_propagation off
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
	int activePartyCount;
	BonusAnimSprite* sprite;
	int modelIndex;
	int lastKind;
	int i;
	int partyOff;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) != 0) {
		activePartyCount = s_Rinfo->m_partyCount;

		DrawInit();
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		modelIndex = 0;
		lastKind = 0;
		partyOff = 0;
		i = 0;
		for (; i < (int)((BonusAnimList*)this->m_bonusAnimPtr)->header.count; i++) {
			sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i];

			if (sprite->kind >= 0 || sprite->kind == -2) {
				if (sprite->kind == -2) {
					CCharaPcs::CHandle* handle;
					if (modelIndex < activePartyCount) {
						int pOff = partyOff + 0x20;
						handle = *(CCharaPcs::CHandle**)((int)s_Rinfo + pOff);
					} else {
						int slotOff = (modelIndex - activePartyCount) * 4 + 0x774;
						handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
					}

					if ((double)handle->m_model->m_lightAlpha <= DOUBLE_80331E90) {
						modelIndex++;
						partyOff += 0x2c;
						continue;
					}
					int __p15 = modelIndex;
					SetProjection(__p15);
					SetLight(1);
					handle->m_flags = 0x300543;
					handle->Draw(5);
					RestoreProjection();
					lastKind = sprite->kind;
					modelIndex++;
					partyOff += 0x2c;
				} else {
					if (lastKind < 0) {
						DrawInit();
					}
					if (lastKind != 0x17 && sprite->kind == 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					} else if (lastKind == 0x17 && sprite->kind != 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
					}

					_GXColor colors[4];
					if (sprite->kind == 0x17) {
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
						GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					}
					if (sprite->kind != 0x17) {
						colors[0].r = 0xFF;
						colors[0].g = 0xFF;
						colors[0].b = 0xFF;
						colors[0].a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
						GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					}
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

					if (sprite->kind == 0x17) {
						float x = (float)sprite->x;
						float y = (float)sprite->y;
						float fillWidth;
						if (sprite->duration > sprite->timer) {
							fillWidth = (float)((DOUBLE_80331ED8 / (double)sprite->duration) * (double)(sprite->timer - 1));
							if (fillWidth < kBonusZClearOrigin) {
								fillWidth = kBonusZClearOrigin;
							}
						} else {
							fillWidth = FLOAT_80331EB0;
						}
						float mulX = sprite->mulX;
						fillWidth *= (float)sprite->w;
						if (fillWidth > kBonusZClearOrigin) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    mulX, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
							x += fillWidth;
						}
						if (fillWidth > kBonusZClearOrigin && fillWidth < (float)sprite->w) {
							colors[1].r = 0xFF;
							colors[1].g = 0xFF;
							colors[1].b = 0xFF;
							colors[1].a = 0;
							colors[3].r = 0xFF;
							colors[3].g = 0xFF;
							colors[3].b = 0xFF;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)(DOUBLE_80331ED8 / (double)sprite->duration) * (float)sprite->w, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
						}
					} else {
						if ((signed char)i >= s_CntTop && i < (signed char)s_CntTop + activePartyCount) {
							float digitX;
							float digitW;
							int value = 0;
							digitX = (float)((DOUBLE_80331EC8 * (double)sprite->w - (float)sprite->w) * DOUBLE_80331E78 + (double)sprite->x);
							digitW = (float)sprite->w;
							MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
							    (float)(sprite->w * value), sprite->mulY,
							    sprite->depth, sprite->depth, kBonusZClearOrigin);
						} else {
							MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
							    (float)sprite->w, (float)sprite->h,
							    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
						}
					}
					lastKind = sprite->kind;
				}
			}
		}

		DrawInit();
		CFont* font = this->m_fonts[0];
		font->SetMargin(FLOAT_80331EB0);
		font->SetShadow(1);
		font->SetScale(FLOAT_80331F38);
		font->SetTlut(7);
		font->DrawInit();

		int off2;
		int textIndex = 0;
		char text[128];
		{
			int i = 0;
			off2 = textIndex << 6;
			for (; i < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; off2 += 0x40, i++) {
				BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + off2 + 8);
				if (sprite->kind == -1) {
					font->SetColor(CColor(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha)).color);

					int partyIndex = textIndex % activePartyCount;
					int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
					if (textIndex < activePartyCount) {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
					} else {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						int strIdx = (int)caravanWork->m_bonusCondition * 2 + 1;
						strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[strIdx]);
					}

					float x = (float)sprite->x + sprite->motionX;
					float y = (float)sprite->y + sprite->motionY;
					if (textIndex < activePartyCount) {
						y -= FLOAT_80331F3C;
					}
					font->SetPosX(x);
					font->SetPosY(y - FLOAT_80331F3C);
					font->Draw(text);

					textIndex++;
					if (textIndex == activePartyCount) {
						font = this->m_fonts[1];
						font->SetMargin(FLOAT_80331EB0);
						font->SetShadow(0);
						font->SetScaleX(FLOAT_80331F90);
						font->SetScaleY(FLOAT_80331EB0);
						font->DrawInit();
					}
				}
			}
		}
		DrawInit();
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8013b14c
 * PAL Size: 8316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
void CMenuPcs::CalcResultOpenAnim()
{
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (*(signed char*)(this->m_bonusStatePtr + 0xb) == 0) {
		int idx;

		this->m_bonusAlpha = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		memset((void*)this->m_bonusAnimPtr, 0, sizeof(BonusAnimList));

		idx = 0;
		{
			int off = (idx << 6) + 8;
			BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			spr->kind = 0x16;
			spr->y = 0;
			spr->x = 0;
			spr->w = 0x280;
			spr->h = 0x1c0;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->alpha = kBonusZClearOrigin;
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* spr = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i + 1];
			spr->kind = 0x17;
			spr->x = 0x80;
			spr->y = (short)(i * 0x60 + 0x38);
			spr->w = 0x1a0;
			spr->h = 0x40;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = kBonusZClearOrigin;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
		}
		int base = activePartyCount + 1;
		{
			int i = 0;
			int partyOff = i;
			int backOff = base << 6;
			int y = 0x28;
			for (; i < activePartyCount; i++) {
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				int pOff = partyOff + 0x1c;
				int partySlot = *(int*)((int)s_Rinfo + pOff);
				spr->kind = 0x18;
				spr->x = ((1 <= i) && (i <= 2)) ? 0x30 : 0x48;
				spr->y = (short)y;
				spr->w = 0x60;
				spr->h = 0x58;
				spr->mulX = (float)((partySlot & 1) ? spr->w : 0);
				spr->mulY = (float)((partySlot >> 1) ? spr->h : 0);
				if (i == 0) {
					BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - backOff);
					spr->startFrame = src->startFrame + src->duration;
					spr->startFrame += 0x18;
				} else {
					spr->startFrame = ((BonusAnimSprite*)((int)spr - 0x40))->startFrame + 3;
				}
				spr->duration = 8;
				partyOff += 0x2c;
				y += 0x60;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// model sprites: startFrame chained from icons
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = (base - (activePartyCount + 1)) << 6;
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -2;
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// zeroed model sprites; startFrame fixed up later
		base += activePartyCount;
		int zeroBase = base;
		if (0 < activePartyCount) {
			for (int i = 0; i < activePartyCount; i++) {
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -2;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->duration = 8;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// staggered model sprites
		base += activePartyCount;
		{
			int i = 0;
			int bump = i;
			for (; i < activePartyCount; i++) {
				int delta = base << 6;
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -2;
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = src->startFrame + src->duration;
				if (i != 0) {
					spr->startFrame += bump;
				}
				spr->duration = 0x20;
				bump += 3;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// icon echo sprites (copies shifted down)
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = (base - (activePartyCount + 1)) << 6;
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				*spr = *src;
				spr->y = (short)(spr->y + 0x20);
				spr->w = 0xA8;
				spr->h = 0x38;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = FLOAT_80331F68;
			}
		}

		base += activePartyCount;

		// frame rows start after their icons
		if (0 < activePartyCount) {
			for (int i = 0; i < activePartyCount; i++) {
				int fwd = activePartyCount << 6;
				int off = ((i + 1) << 6) + 8;
				int spr = this->m_bonusAnimPtr + off;
				int src = spr + fwd;
				*(int*)(spr + 0x24) = *(int*)(src + 0x24) + *(int*)(src + 0x28);
			}
		}

		// zeroed model sprites follow the frame rows
		for (int i = 0; i < activePartyCount; i++) {
			int delta = (zeroBase - 1) << 6;
			int off = ((zeroBase + i) << 6) + 8;
			int spr = this->m_bonusAnimPtr + off;
			int src = spr - delta;
			*(int*)(spr + 0x24) = *(int*)(src + 0x24) + *(int*)(src + 0x28);
		}

		{
			int off = (base << 6) + 8;
			BonusAnimSprite* count = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
			count->kind = 0x19;
			count->y = 0x10;
			count->w = 0x140;
			count->x = (short)((0x280 - count->w) >> 1);
			count->h = 0x28;
			count->mulX = kBonusZClearOrigin;
			count->mulY = FLOAT_80331FA0;
			count->startFrame = *(int*)(this->m_bonusAnimPtr + 0x6c);
			count->duration = 8;
			count->duration = 10;
			count->depth = FLOAT_80331EB0;
		}
		int countTop = base + 1;
		s_CntTop = (signed char)countTop;

		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = (base + 0) << 6;
				int off = ((countTop + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = 0x19;
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->x = 0x200;
				spr->y = (short)(src->y + 0xC);
				spr->w = 0x20;
				spr->h = 0x28;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = FLOAT_80331FA4;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// name sprites
		base = countTop + activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = (base - (activePartyCount + 1)) << 6;
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -1;
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->x = (short)(src->x + 0x50);
				spr->y = (short)(src->y + 0x48);
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = src->startFrame;
				spr->duration = 8;
				spr->depth = FLOAT_80331EB0;
			}
		}

		// value text sprites
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = (base - 1) << 6;
				int off = ((base + i) << 6) + 8;
				BonusAnimSprite* spr = (BonusAnimSprite*)(this->m_bonusAnimPtr + off);
				spr->kind = -1;
				spr->x = 0xb8;
				BonusAnimSprite* src = (BonusAnimSprite*)((int)spr - delta);
				spr->y = (short)(src->y + 0x15);
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = FLOAT_80331EB0;
			}
		}

		base += activePartyCount;

		{
			int i = 0;
			int boardOff = i;
			for (; i < activePartyCount; i++) {
				int sprOff = ((activePartyCount + i + 1) << 6) + 8;
				BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);
				int o08 = boardOff + 0x8;
				int o0a = boardOff + 0xa;
				int o40 = boardOff + 0x40;
				int o44 = boardOff + 0x44;
				int o48 = boardOff + 0x48;
				int o4c = boardOff + 0x4c;
				int centerX = (int)(float)((double)(float)(DOUBLE_80331EE0 + ((double)sprite->w * DOUBLE_80331E78 + (double)sprite->x)) - DOUBLE_80331EE8);
				int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)sprite->y) - DOUBLE_80331EF0);
				*(short*)(this->m_bonus.m_bonusBoardPtr + o08) = (short)centerX;
				*(short*)(this->m_bonus.m_bonusBoardPtr + o0a) = (short)centerY;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o40) = sprite->x + 0xC;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o44) = sprite->y - 8;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o48) = 0x48;
				*(int*)(this->m_bonus.m_bonusBoardPtr + o4c) = 0x58;
				boardOff += 0x50;
			}
		}

		{
			unsigned int i = 0;
			int boardOff = i;
			int half = activePartyCount * 0x50;
			for (; i < activePartyCount; i++) {
				int sprOff = (((unsigned char)s_CntTop + i) << 6) + 8;
				BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);
				int w3 = sprite->w * 3;
				int extent = w3 + 0x20;
				int centerX = (int)(float)((double)(float)((double)w3 * DOUBLE_80331E78 + (double)sprite->x) - DOUBLE_80331EE8);
				int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)sprite->y) - DOUBLE_80331EF0);
				*(short*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x8 + half) = (short)centerX;
				*(short*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0xa + half) = (short)centerY;
				*(int*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x40 + half) = sprite->x - 0x10;
				*(int*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x44 + half) = sprite->y - 0x10;
				*(int*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x48 + half) = extent;
				*(int*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x4c + half) = extent;
				boardOff += 0x50;
			}
		}

		{
			int i = 0;
			int total2 = activePartyCount * 2;
			int boardBase = total2 * 0x50;
			for (; i < activePartyCount; i++) {
				BonusAnimSprite* sprite = &((BonusAnimList*)this->m_bonusAnimPtr)->sprites[i + 1];
				int boardOff = boardBase + i * 0x50;
				*(short*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0x8) = (short)(int)kBonusZClearOrigin;
				int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)sprite->y) - DOUBLE_80331EF0);
				*(unsigned short*)(this->m_bonus.m_bonusBoardPtr + boardOff + 0xa) = (short)centerY;
			}
		}

		{
			int p = (int)this;
			for (int i = 0; i < 0x18; i++, p += 4) {
				CCharaPcs::CHandle* handle = *(CCharaPcs::CHandle**)(p + 0x774);
				if (handle != 0) {
					handle->m_model->m_lightAlpha = kBonusZClearOrigin;
				}
			}
		}

		((BonusAnimHeader*)this->m_bonusAnimPtr)->count = (short)base;
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 0;
		*(unsigned char*)(this->m_bonusStatePtr + 0xb) = 1;
		return;
	}

	*(short*)(this->m_bonusStatePtr + 0x22) = *(short*)(this->m_bonusStatePtr + 0x22) + 1;
	int frame = (int)*(short*)(this->m_bonusStatePtr + 0x22);
	int i0 = 0;
	int off = i0;
	int doneCount = 0;

	for (; i0 < (int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count; i0++, off += 0x40) {
		int sprOff = off + 8;
		BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + sprOff);

		if (sprite->startFrame <= frame) {
			if (sprite->startFrame + sprite->duration <= frame) {
				doneCount++;
				sprite->alpha = FLOAT_80331EB0;
			} else {
				sprite->timer++;
				sprite->alpha = (float)((1.0 / (double)sprite->duration) * (double)sprite->timer);
			}

			if (sprite->kind == 0x17) {
				for (int j = 0; j < s_Rinfo->m_partyCount; j++) {
					if (sprite->timer - 1 == 0) {
						Sound.PlaySe(0x49, 0x40, 0x7f, 0);
					}
					sprite++;
				}
			}
		}
	}

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	{
		int i = 0;
		int total2 = activePartyCount * 2;
		int total3 = activePartyCount * 3;
		int sprOff2 = (total2 + 1) << 6;
		int partyOff = i;
		for (; i < total3; i++) {
			int aOff = sprOff2 + 0x8;
			BonusAnimSprite* sprite = (BonusAnimSprite*)(this->m_bonusAnimPtr + aOff);
			CCharaPcs::CHandle* handle;
			int tribeId;
			if (i < activePartyCount) {
				int p = (int)s_Rinfo + partyOff;
				handle = *(CCharaPcs::CHandle**)(p + 0x20);
				tribeId = *(int*)(p + 0x44);
			} else {
				int slotOff = (i - activePartyCount) * 4 + 0x774;
				handle = *(CCharaPcs::CHandle**)((int)this + slotOff);
			}
			if (i < activePartyCount) {
				float modelScale = s_BonusModelScale[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else if (i >= total2) {
				float modelScale = FLOAT_80331FA8;
				if (sprite->timer == 0x18 && *(signed char*)&this->m_bonusAlpha == 0) {
					Sound.PlaySe(0x48, 0x40, 0x7f, 0);
					this->m_bonusAlpha = 1;
				}
				if (sprite->timer >= 0x18) {
					modelScale = (float)(DOUBLE_80331E78 * (double)((float)(sprite->timer - 0x18) /
					                 (float)(sprite->duration - 0x18)) + (double)modelScale);
				}
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				float modelScale = FLOAT_80331EB0;
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			}

			if (i / activePartyCount == 1) {
				PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F94);
				PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F04 * *reinterpret_cast<float*>(this->m_bonusStatePtr));
				PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_BonusModelYPos[tribeId];
			} else if (i >= total2) {
				double tx = GetFcvValue(s_BallTrnsX, (float)(sprite->timer - 1));
				scaleMtx[0][3] = tx;
				if (sprite->timer - 1 == 7) {
					Sound.PlaySe(0x47, 0x40, 0x7f, 0);
				}
				double ty = GetFcvValue(s_BallTrnsY, (float)(sprite->timer - 1));
				int itemIndex = i - total2;
				scaleMtx[1][3] = ty;
				scaleMtx[2][3] = kBonusZClearOrigin;
				if (1 <= itemIndex && itemIndex <= 2) {
					scaleMtx[1][3] = (float)((double)(float)ty - DOUBLE_80331FB0);
				}
			} else {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			if (i >= total2) {
				if (sprite->timer >= 0x18) {
					sprite->alpha = (float)(DOUBLE_80331ED8 - (double)((float)(sprite->timer - 0x18) /
					                 (float)(sprite->duration - 0x18)));
					if (sprite->alpha < DOUBLE_80331E90) {
						sprite->alpha = kBonusZClearOrigin;
					}
				} else {
					sprite->alpha = FLOAT_80331EB0;
				}
			}
			handle->m_model->m_lightAlpha = sprite->alpha;
			sprOff2 += 0x40;
			partyOff += 0x2c;
		}
	}

	if ((int)((BonusAnimHeader*)this->m_bonusAnimPtr)->count == doneCount) {
		((BonusAnimHeader*)this->m_bonusAnimPtr)->finished = 1;
	}
}
#pragma pop

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
	gUtil.ClearZBufferRect(kBonusZClearOrigin, kBonusZClearOrigin, kBonusZClearWidth, kBonusZClearHeight);

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

#pragma push
#pragma optimization_level 3
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

	loadTexture(sBonusTextureSetNames, 2, 1, sBonusTextureTable, 0x16, 0x12, 0);
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
	const float zero = kBonusZClearOrigin;
	int off;
	off = 0;
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
			s_Rinfo->m_party[activeCount].m_partyHandle->m_model->m_lightAlpha = kBonusZClearOrigin;
			s_Rinfo->m_party[activeCount].m_bonusCondition = (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_bonusCondition;
			int foodValue =  (int)(unsigned int)((int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[3] + (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[4]);
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
			    (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[0] + (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[1] - (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[2];
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
			s_Rinfo->m_party[activeCount].m_tribeId = (unsigned int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_tribeId;
			activeCount++;

			unsigned int* slot = &Game.m_scriptFoodBase[i];
			int treasure0 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_treasures[0];
			if (treasure0 > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = (short)treasure0;
			}
			int treasure1 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_treasures[1];
			if (treasure1 > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = (short)treasure1;
			}
			int treasure2 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_treasures[2];
			if (treasure2 > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = (short)treasure2;
			}
			int treasure3 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_treasures[3];
			if (treasure3 > 0) {
				s_Rinfo->m_tempArtifacts[tempArtifactCount++] = (short)treasure3;
			}
		}

		s_Rinfo->m_partyCount = activeCount;

		unsigned short* bossArtifact = reinterpret_cast<unsigned short*>(Game.GetBossArtifact(s_Rinfo->m_partyCount, totalValue));
		for (int i = 0; i < 4; i++) {
			s_Rinfo->m_bossArtifacts[i] = bossArtifact[i];
		}

		s_Rinfo->m_missingArtifactMask = 0;
		for (int i = 0; i < 8; i++) {
			if (s_Rinfo->m_tempArtifacts[i] < 0) {
				s_Rinfo->m_missingArtifactMask =
				    (unsigned char)(s_Rinfo->m_missingArtifactMask | (1 << i));
			}
		}

		{
			int i = 0;
			int partyOff = i;
			for (; i < s_Rinfo->m_partyCount; i++) {
				unsigned int* slot = &Game.m_scriptFoodBase[s_Rinfo->m_party[i].m_partySlot];

				for (int artifactIndex = 0; artifactIndex < 8; artifactIndex++) {
					short itemId = s_Rinfo->m_tempArtifacts[artifactIndex];
					if (itemId <= 0) {
						continue;
					}

					if (GetItemType(itemId, 1) == 2) {
						int artifactSlot = s_Rinfo->m_tempArtifacts[artifactIndex] - 0x9F;
						if (reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[artifactSlot] == s_Rinfo->m_tempArtifacts[artifactIndex]) {
							s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
						}
					} else if (reinterpret_cast<CCaravanWork*>(*slot)->m_inventoryItemCount + 1 > 0x40) {
						s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
					}
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
				int aTotal = s_Rinfo->m_party[leftIndex].m_totalValue;
				int aFood = s_Rinfo->m_party[leftIndex].m_foodValue;
				int bTotal = s_Rinfo->m_party[order[j]].m_totalValue;
				int bFood = s_Rinfo->m_party[order[j]].m_foodValue;
				int aArtifact = s_Rinfo->m_party[leftIndex].m_artifactValue;
				int bArtifact = s_Rinfo->m_party[order[j]].m_artifactValue;
				int coin = rand() & 1;

				if (aTotal < bTotal ||
				    (aTotal == bTotal && aArtifact < bArtifact) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood < bFood) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood == bFood && coin != 0)) {
					int temp = order[i];
					order[i] = order[j];
					order[j] = temp;
					leftIndex = order[i];
				}
			}
		}

		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			s_Rinfo->m_party[order[i]].m_rank = i;
			if (i == 0) {
				s_Rinfo->m_winnerTotalValue = s_Rinfo->m_party[order[i]].m_totalValue;
			}
		}

		for (int i = 0; i < 0x18; i++) {
			this->m_wm.m_handles[i] = 0;
		}

		int slotIdx = 0;
		int i;
		for (i = 0; i < 0x18; i++) {
			int pc = s_Rinfo->m_partyCount;
			if (pc * 2 <= i) {
				break;
			}
			CCharaPcs::CHandle* handle =
			    new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0x183) CCharaPcs::CHandle;
			this->m_wm.m_handles[slotIdx] = handle;
			this->m_wm.m_handles[slotIdx]->Add();
			unsigned long modelCode = s_Rinfo->m_party[i % pc].m_partySlot + 0x83;
			if (i < pc) {
				modelCode = s_Rinfo->m_party[i % pc].m_partySlot + 0x87;
			}
			this->m_wm.m_handles[slotIdx]->LoadModel(3, modelCode & 0xFFF, (modelCode >> 12) & 0xF, 0, -1, 0, 0);
			this->m_wm.m_handles[slotIdx]->m_flags = 0x300543;
			slotIdx++;
		}

		int handleIndex = i;
		for (int artifactIndex = 0; artifactIndex < 8; artifactIndex++, handleIndex++) {
			int itemId = s_Rinfo->m_tempArtifacts[artifactIndex];
			if (itemId <= 0) {
				GetBonusDisplayHandleSlots(this)[handleIndex] = 0;
			} else {
				CCharaPcs::CHandle* itemHandle =
				    new (MenuPcs.m_menuStage, const_cast<char*>(s_bonus_menu_cpp), 0x19C) CCharaPcs::CHandle;
				GetBonusDisplayHandleSlots(this)[handleIndex] = itemHandle;
				GetBonusDisplayHandleSlots(this)[handleIndex]->Add();
				unsigned short itemModelCode =
				    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2);
				int modelNo = itemModelCode & 0x0FFF;
				GetBonusDisplayHandleSlots(this)[handleIndex]->LoadModel(3, modelNo, (itemModelCode >> 12) & 0xF, 0, -1, 0, 0);
				GetBonusDisplayHandleSlots(this)[handleIndex]->m_flags = 0x300543;

				if (modelNo == 0x79) {
					short itemId2 = s_Rinfo->m_tempArtifacts[artifactIndex];
					int effectNo;
					if (itemId2 == 0xDF) {
						effectNo = 0x75;
					} else if (itemId2 == 0xE0) {
						effectNo = 0x76;
					} else if (itemId2 == 0xE1) {
						effectNo = 0x77;
					} else if (itemId2 == 0xE2) {
						effectNo = 0x78;
					} else if (itemId2 == 0xE3) {
						effectNo = 0x79;
					} else {
						continue;
					}
					BindEffect(handleIndex, effectNo, -1);
				}
			}
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
#pragma pop

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
