#include "ffcc/bonus_menu.h"
#include "ffcc/fontman.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include "ffcc/wind.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

extern char* PTR_s_bonus[];
extern CMenuPcs::CTmp s_bonusTextureTable[];
extern char s_menuSubfontPathFmt[];
extern const double kPppCrystal2RefractionScale;
extern const float s_BonusModelYPos[];
extern const float s_BonusModelScale[];

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

#pragma force_active on
extern "C" {
BonusSummaryData* s_Rinfo = 0;
unsigned char s_CntTop = 0;
unsigned char s_ArtiTop = 0;
unsigned char s_PlayerTop = 0;
float* s_Base[1];
}
#pragma force_active reset
extern "C" const char sDrawBonusFmt[16] = {
    'd', 'r', 'a', 'w', ' ', 'B', 'o', 'n', 'u', 's', ' ', '(', '%', 'd', ')', '\n',
};
extern "C" const char s_bonus_menu_cpp[] = "bonus_menu.cpp";

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

struct BonusFlatTableRaw {
	int m_numEntries;
	char** m_strings;
	char* m_stringBuf;
};

struct BonusFlatDataRaw {
	unsigned char pad_0000[0x6C];
	BonusFlatTableRaw m_table[8];
};

struct BonusMenuStateRaw {
	unsigned char bytes[0x48];
};

struct BonusMenuAuxRaw {
	unsigned char bytes[0xC];
};

struct BonusBaseRaw {
	float values[18];
};

struct BonusMenuMembers {
	unsigned char pad_0000[0x8C];
	unsigned char m_bonusAlpha;
	unsigned char m_bonusCursorFlag;
	unsigned char pad_008E[0x6A];
	CFont* m_font;
	CFont* m_fontWide;
	unsigned char pad_0100[0x714];
	int m_bonusBoardPtr;
	unsigned char pad_0818[0x14];
	int m_bonusStatePtr;
	unsigned char pad_0830[0x10];
	int m_bonusListPtr;
	unsigned char pad_0844[4];
	int m_bonusAuxPtr;
	int m_bonusAnimPtr;
};

STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusAlpha) == 0x8C);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusCursorFlag) == 0x8D);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_font) == 0xF8);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_fontWide) == 0xFC);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusBoardPtr) == 0x814);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusStatePtr) == 0x82C);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusListPtr) == 0x840);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusAuxPtr) == 0x848);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusAnimPtr) == 0x84C);

struct BonusBoardEntryRaw {
	int m_modelHandle;
	int m_effectHandle;
	short m_kind;
	short m_state;
	short m_width;
	short m_height;
	float m_posX;
	float m_posY;
	float m_depth;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;
	int m_drawFlags;
	int m_drawState;
	int m_screenWidth;
	int m_screenHeight;
};

struct BonusBoardEntryList {
	BonusBoardEntryRaw entries[0x18];
	unsigned char pad_0660[0x120];
};

struct BonusEffectSlotBlock {
	unsigned char bytes[0x2920];
};

struct BonusEffectSlotList {
	BonusEffectSlotBlock slots[5];
	unsigned char pad_CDA0[0x10];
};

STATIC_ASSERT(sizeof(BonusMenuStateRaw) == 0x48);
STATIC_ASSERT(sizeof(BonusMenuAuxRaw) == 0xC);
STATIC_ASSERT(sizeof(BonusBaseRaw) == 0x48);
STATIC_ASSERT(sizeof(BonusBoardEntryRaw) == 0x44);
STATIC_ASSERT(sizeof(BonusBoardEntryList) == 0x780);
STATIC_ASSERT(sizeof(BonusEffectSlotBlock) == 0x2920);
STATIC_ASSERT(sizeof(BonusEffectSlotList) == 0xCDB0);

static inline void InitBonusEffectSlotBlock(BonusEffectSlotBlock* slot)
{
	unsigned char* slotBase = slot->bytes;
	static const int s_sentinelOffsets[] = {
	    0x000, 0x004, 0x008,
	    0x524, 0x528, 0x52C,
	    0xA48, 0xA4C, 0xA50,
	    0xF6C, 0xF70, 0xF74,
	    0x1490, 0x1494, 0x1498,
	    0x19B4, 0x19B8, 0x19BC,
	    0x1ED8, 0x1EDC, 0x1EE0,
	    0x23FC, 0x2400, 0x2404,
	};

	for (int i = 0; i < static_cast<int>(sizeof(s_sentinelOffsets) / sizeof(s_sentinelOffsets[0])); i++) {
		*reinterpret_cast<int*>(slotBase + s_sentinelOffsets[i]) = -1;
	}
}

static inline void InitBonusBoardEntry(unsigned char* entry)
{
	*reinterpret_cast<int*>(entry) = 0;
	*reinterpret_cast<int*>(entry + 4) = 0;
	*reinterpret_cast<short*>(entry + 8) = 0;
	*reinterpret_cast<short*>(entry + 10) = 0;
	*reinterpret_cast<short*>(entry + 12) = 0x280;
	*reinterpret_cast<short*>(entry + 14) = 0x1C0;
	*reinterpret_cast<float*>(entry + 0x10) = 0.0f;
	*reinterpret_cast<float*>(entry + 0x14) = 0.0f;
	*reinterpret_cast<float*>(entry + 0x18) = 1000.0f;
	*reinterpret_cast<float*>(entry + 0x1C) = 0.0f;
	*reinterpret_cast<float*>(entry + 0x20) = 0.0f;
	*reinterpret_cast<float*>(entry + 0x24) = 0.0f;
	*reinterpret_cast<float*>(entry + 0x28) = 1.0f;
	*reinterpret_cast<float*>(entry + 0x2C) = 1.0f;
	*reinterpret_cast<float*>(entry + 0x30) = 1.0f;
	*reinterpret_cast<int*>(entry + 0x40) = 0;
	*reinterpret_cast<int*>(entry + 0x44) = 0;
	*reinterpret_cast<int*>(entry + 0x48) = 0x280;
	*reinterpret_cast<int*>(entry + 0x4C) = 0x1C0;
}

static inline BonusMenuMembers& GetBonusMenuMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<BonusMenuMembers*>(menu);
}

static inline void ReleaseBonusRefObject(void* object)
{
	int* raw = reinterpret_cast<int*>(object);
	int refCount = raw[1] - 1;
	raw[1] = refCount;
	if (refCount == 0 && object != 0) {
		reinterpret_cast<void (**)(void*, int)>(*raw)[2](object, 1);
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
	return reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(menu) + 0x774);
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
	short x = ((0 < slotIndex) && (slotIndex < 3)) ? 0x30 : 0x48;

	InitAnimSprite(sprite, 0, x, y, 0x60, 0x58, 0, 8);
	ResetAnimSpriteMotion(sprite);
	sprite->mulX = (float)sprite->w;
	sprite->mulY = (float)sprite->h;
	sprite->depth = 1.0f;
	sprite->motionX = 100.0f;
	sprite->motionY = 0.0f;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
	BonusSpriteFlags(sprite) = 0x10000;
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
	BonusSpriteFlags(sprite) = 0x10000;
}

static inline void SetupSelectCloseSpriteMotion(BonusAnimSprite* sprite)
{
	sprite->timer = 0;
	sprite->startFrame = 0;
	sprite->duration = 8;
	sprite->depth = 1.0f;
	sprite->x = (short)(int)sprite->targetX;
	sprite->y = (short)(int)sprite->targetY;
	sprite->motionX = 100.0f;
	sprite->motionY = 0.0f;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
}

static inline void DrawBonusActiveMarks(CMenuPcs* menu, int statePtr, float alpha)
{
	if (statePtr == 0 || alpha <= 0.0f) {
		return;
	}

	unsigned char activeMask = *(unsigned char*)(statePtr + 9);
	if (activeMask == 0) {
		return;
	}

	menu->SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	menu->SetTexture(static_cast<CMenuPcs::TEX>(0x23));
	GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);

	float* markPos = s_Base[0];
	if (markPos == 0) {
		return;
	}

	for (int i = 0; i < 8; i++) {
		if ((activeMask & (1 << i)) == 0) {
			continue;
		}
		float x = markPos[i * 2 + 2] + 4.0f;
		float y = markPos[i * 2 + 3] + 4.0f;
		menu->DrawRect(0, x, y, 24.0f, 24.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

static inline unsigned char GetBonusUnavailableMask(int statePtr, BonusPartySummary* summary)
{
	unsigned char mask = 0;
	if (statePtr != 0) {
		mask = *(unsigned char*)(statePtr + 9);
	}
	if (summary != 0) {
		mask = (unsigned char)(mask | (unsigned char)summary->m_ownedArtifactMask);
	}
	return mask;
}

static inline void DrawBonusPartyNames(CMenuPcs* menu, BonusAnimHeader* header, BonusAnimSprite* sprites)
{
	CFont* font = GetBonusMenuMembers(menu).m_font;
	int activePartyCount = s_Rinfo->m_partyCount;

	if (font == 0 || activePartyCount <= 0) {
		return;
	}

	menu->DrawInit();
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.9f);
	font->SetTlut(7);
	font->DrawInit();

	int nameIndex = 0;
	for (int i = 0; i < (int)header->count && nameIndex < activePartyCount; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->kind != -1) {
			continue;
		}

		const char* name = GetBonusPartyNameByActiveIndex(nameIndex);
		GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
		font->SetColor(color);
		font->SetPosX((float)sprite->x + sprite->mulX);
		font->SetPosY((float)sprite->y + sprite->mulY - 12.0f);
		font->Draw(const_cast<char*>(name));
		nameIndex++;
	}
}

static inline void DrawBonusMcWinOverlay(CMenuPcs* menu, int statePtr)
{
	int auxPtr = GetBonusMenuMembers(menu).m_bonusAuxPtr;

	if (statePtr == 0 || auxPtr == 0 || *(short*)(auxPtr + 10) == 3) {
		return;
	}

	menu->DrawInit();
	menu->DrawMcWin(-1, 1);
	if (*(short*)(auxPtr + 10) == 1) {
		menu->DrawMcWinMess(0x18, 1);
		menu->DrawInit();
		int cursorX = menu->GetYesNoXPos((int)*(short*)(statePtr + 0x28));
		float cursorY = (float)(*(short*)(auxPtr + 2) + *(short*)(auxPtr + 6) - 0x3e);
		menu->DrawCursor(cursorX, (int)cursorY, 1.0f);
	}
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

	return reinterpret_cast<const char*>(caravanWork->unk_0x3ca_0x3dd);
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

	BonusFlatDataRaw* flat = reinterpret_cast<BonusFlatDataRaw*>(&Game.m_cFlatDataArr[1]);
	if (flat->m_table[7].m_strings == 0 || labelIndex >= flat->m_table[7].m_numEntries) {
		return 0;
	}

	return flat->m_table[7].m_strings[labelIndex];
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
	float* base = s_Base[0];

	base[0] = (float)(board[0] + board[2] * 0.5);
	base[1] = (float)(board[1] + board[3] * 0.5);

	float iconW = (float)icon[2];
	float iconH = (float)icon[3];
	double iconHalfW = (double)iconW * 0.5;
	double iconHalfH = (double)iconH * 0.5;

	base[14] = (float)((double)base[0] - iconHalfW);
	base[15] = (float)board[1];
	base[6] = base[14];
	base[7] = (float)((double)(float)(board[1] + board[3]) - (double)iconH);
	base[10] = (float)board[0];
	base[11] = (float)((double)base[1] - iconHalfH);
	base[2] = (float)((double)(float)(board[0] + board[2]) - (double)iconW);
	base[3] = base[11];

	for (int row = 0; row < 2; row++) {
		float slotX = (float)((double)(float)(board[0] + board[2] * 0.25) - iconHalfW);
		float slotY = (float)((double)(float)(board[1] + board[3] * 0.25) - iconHalfH);
		if (row == 0) {
			base[12] = slotX;
			base[13] = slotY;
		} else {
			slotY = (float)(board[3] * 0.5 + slotY);
			base[8] = slotX;
			base[9] = slotY;
		}
		float nextX = (float)(board[2] * 0.5 + slotX);
		if (row == 0) {
			base[16] = nextX;
			base[17] = slotY;
		} else {
			base[4] = nextX;
			base[5] = slotY;
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
	if (alpha <= 0.0f) {
		return;
	}

	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;

	if (*(short*)(statePtr + 0x1c) != 4) {
		_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
		GXSetChanMatColor(GX_COLOR0A0, color);
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1A));

	BonusAnimSprite* sprite = reinterpret_cast<BonusAnimSprite*>(sprt);
	float width = (float)sprite->w;
	float height = (float)sprite->h;

	int partyIndex = 0;
	for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
		if ((int)*(short*)(statePtr + 0xe) == s_Rinfo->m_party[i].m_rank) {
			partyIndex = i;
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (*(short*)(statePtr + 0x1c) == 4) {
			float rgb = 1.0f;
			unsigned int mask = s_Rinfo->pad_0008 | s_Rinfo->m_party[partyIndex].m_ownedArtifactMask | s_Rinfo->m_missingArtifactMask;
			if ((mask & (1 << i)) != 0) {
				rgb = 0.5f;
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
	if (alpha <= 0.0f) {
		return;
	}

	_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(255.0 * alpha)};
	const float corner = 8.0f;
	const float texScale = 1.0f;
	const float right = (x + w) - corner;
	const float bottom = (y + h) - corner;

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXSetChanMatColor(GX_COLOR0A0, color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1B));
	for (int i = 0; i < 4; i++) {
		float drawX = x;
		float drawY = y;
		float texU = 0.0f;
		float texV = 0.0f;
		if (i == 1) {
			drawX = right;
			texU = corner;
		} else if (i == 2) {
			drawY = bottom;
			texV = corner;
		} else if (i == 3) {
			drawX = right;
			drawY = bottom;
			texU = corner;
			texV = corner;
		}
		MenuPcs.DrawRect(0, drawX, drawY, corner, corner, texU, texV, texScale, texScale, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1C));
	w -= 16.0f;
	MenuPcs.DrawRect(0, x + corner, y, w, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x22));
	MenuPcs.DrawRect(0, x + corner, bottom, w, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
	h -= 16.0f;
	MenuPcs.DrawRect(0, x, y + corner, corner, h, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
	MenuPcs.DrawRect(0, right, y + corner, corner, h, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	MenuPcs.DrawRect(0, x + corner, y + corner, w, h, 0.0f, 0.0f, texScale, texScale, 0.0f);
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
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
		sprites[2].kind = 0x1f;
		sprites[2].mulX = 0.0f;
		sprites[2].mulY = 0.0f;
		sprites[2].startFrame = 0;
		sprites[2].duration = 0;
		BonusSpriteFlags(&sprites[2]) = 2;
		sprites[3].kind = -4;
		sprites[3].startFrame = 0;
		sprites[3].duration = 8;

		for (int i = 0; i < activePartyCount; i++) {
			SetupSelectCloseSpriteMotion(&sprites[iconBase + i]);
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
			nameSprite->depth = 1.0f;
			nameSprite->motionX = 100.0f;
			nameSprite->motionY = 0.0f;
			nameSprite->targetX = (float)nameSprite->x + nameSprite->motionX;
			nameSprite->targetY = (float)nameSprite->y + nameSprite->motionY;
		}

		*(short*)(animPtr + 6) = 0;
		*(unsigned char*)(statePtr + 0xb) = 1;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		int flags = BonusSpriteFlags(sprite);

		if ((flags & 1) == 0) {
			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			}
			if (frame < sprite->startFrame + sprite->duration) {
				sprite->alpha = 1.0f - ((float)sprite->timer / (float)sprite->duration);
			} else {
				sprite->alpha = 0.0f;
			}
		} else {
			sprite->alpha = 0.0f;
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame > 9998) {
			doneCount++;
		}

		if ((flags & 2) == 0 && (sprite->motionX != 0.0f || sprite->motionY != 0.0f)) {
			float progress = 1.0f - ((float)sprite->timer / (float)sprite->duration);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (sprite->targetY - (float)sprite->y) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	int boardPtr = GetBonusMenuMembers(this).m_bonusBoardPtr;
	int entryOffset = 0;
	for (int i = 0; i < activePartyCount; i++) {
		BonusAnimSprite* sprite = &sprites[4 + i];
		int centerX = (int)((double)(float)((double)sprite->w * 0.5 + (double)((float)sprite->x + sprite->motionX)) - 320.0);
		int centerY = (int)((double)(float)((double)sprite->h * 0.5 + (double)((float)sprite->y + sprite->motionY)) - 240.0);
		*reinterpret_cast<short*>(boardPtr + entryOffset + 8) = (short)centerX;
		*reinterpret_cast<short*>(boardPtr + entryOffset + 10) = (short)centerY;

		int screenX = (int)(24.0f + (float)sprite->x + sprite->motionX);
		int screenY = (int)(((float)sprite->y + sprite->motionY) - 28.0f);
		if ((double)screenX < 0.0) {
			screenX = 0;
		}
		if ((double)screenY < 0.0) {
			screenY = 0;
		}
		*reinterpret_cast<int*>(boardPtr + entryOffset + 0x40) = screenX;
		*reinterpret_cast<int*>(boardPtr + entryOffset + 0x44) = screenY;
		*reinterpret_cast<int*>(boardPtr + entryOffset + 0x48) = 0x48;
		*reinterpret_cast<int*>(boardPtr + entryOffset + 0x4C) = 0x58;
		entryOffset += 0x50;
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

		CChara::CModel* model = handle->m_model;
		model->m_flags10C = (model->m_flags10C & 0x7F) | 0x80;
		model->SetMatrix(scaleMtx);
		model->CalcMatrix();
		model->CalcSkin();
		model->m_lightAlpha = sprites[(int)(signed char)s_PlayerTop + i].alpha;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int auxPtr = GetBonusMenuMembers(this).m_bonusAuxPtr;
	BonusAnimHeader* header;
	BonusAnimSprite* sprites;

	header = (BonusAnimHeader*)animPtr;
	sprites = (BonusAnimSprite*)(animPtr + 8);
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(auxPtr + 10) = 3;
		*(short*)(statePtr + 0xe) = 0;
		*(short*)(statePtr + 0x18) = 0;
		*(short*)(statePtr + 0x1a) = 0;
		*(short*)(statePtr + 0x26) = 4;
		*(unsigned char*)(statePtr + 8) = 0;
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].alpha = 1.0f;
			sprites[i].depth = 3.0f;
		}
		BonusAnimSprite* cursor = &sprites[header->count];
		BonusAnimSprite* partySprite = cursor - activePartyCount * 2;
		InitAnimSprite(cursor, 0x20, (short)(partySprite->x - 3), (short)(partySprite->y - 8), 0x40, 0x30, 0, 8);
		ResetAnimSpriteMotion(cursor);
		cursor->alpha = 1.0f;
		cursor->depth = 1.0f;
		header->count = (short)(header->count + 1);
		header->finished = 0;
		*(unsigned char*)(statePtr + 0xb) = 1;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	short& promptMode = *(short*)(auxPtr + 10);
	short& currentPartyIndex = *(short*)(statePtr + 0xe);
	short& selection = *(short*)(statePtr + 0x26);
	short& confirmSel = *(short*)(statePtr + 0x28);
	short& delay = *(short*)(statePtr + 0x1a);
	BonusPartySummary* currentParty = GetBonusPartySummary(currentPartyIndex);
	int padSlot = (currentParty != 0) ? currentParty->m_partySlot : 0;
	unsigned short repeat = GetButtonRepeat(padSlot);
	unsigned short down = GetButtonDown(padSlot);
	unsigned char unavailableMask = GetBonusUnavailableMask(statePtr, currentParty);

	switch (promptMode) {
	case 3:
		if (delay == 0 && currentPartyIndex < activePartyCount && currentParty != 0) {
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
					unsigned char bit = (unsigned char)(1 << (selection & 7));
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
			if (delay == 0 && *(unsigned char*)(statePtr + 8) != 0) {
				unsigned char bit = (unsigned char)(1 << (selection & 7));
				int itemId = (&s_Rinfo->m_tempArtifacts[0])[selection & 7];
				*(unsigned char*)(statePtr + 9) = (unsigned char)(*(unsigned char*)(statePtr + 9) | bit);
				*(unsigned char*)(statePtr + 8) = 0;
				if (currentParty != 0) {
					currentParty->m_selectedItemId = itemId;
					currentParty->m_selectedSlot = selection & 7;
				}
				currentPartyIndex = (short)(currentPartyIndex + 1);
			}
		} else {
			delay = 0;
		}
		break;
	case 1:
		if ((repeat & 3) != 0) {
			confirmSel = (short)(confirmSel ^ 1);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((down & 0x100) != 0) {
			promptMode = 2;
			Sound.PlaySe(2, 0x40, 0x7f, 0);
		} else if ((down & 0x200) != 0) {
			promptMode = 2;
			confirmSel = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
		}
		break;
	case 2:
		if (*(short*)(auxPtr + 8) == 1 && confirmSel == 0) {
			delay = 10;
			*(unsigned char*)(statePtr + 8) = 0xff;
		}
		break;
	default:
		promptMode = 3;
		break;
	}

	float* base = s_Base[0];
	if (base != 0) {
		sprites[2].x = (short)(int)base[selection * 2 + 2];
		sprites[2].y = (short)(int)base[selection * 2 + 3];
	}
	if (sprites[2].timer < sprites[2].duration) {
		sprites[2].alpha = (float)sprites[2].timer / (float)sprites[2].duration;
		sprites[2].timer++;
	} else {
		sprites[2].alpha = 1.0f;
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
			cursor->alpha = 0.0f;
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
			scaleMtx[0][3] = 0.0f;
		} else {
			int artifactIndex = i - activePartyCount;
			handle = GetBonusDisplayHandleSlots(this)[activePartyCount * 2 + artifactIndex];
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

		CChara::CModel* model = handle->m_model;
		model->m_flags10C = (model->m_flags10C & 0x7F) | 0x80;
		model->SetMatrix(scaleMtx);
		model->CalcMatrix();
		model->CalcSkin();
		model->m_lightAlpha = sprites[(int)(signed char)s_PlayerTop + i].alpha;
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
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float artiAlpha = 0.0f;
	int modelIndex = 0;
	int lastKind = 0;
	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = sprite->alpha;
		int kind = sprite->kind;
		switch (kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			artiAlpha = alpha;
			lastKind = kind;
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			lastKind = kind;
			break;
		case -2:
			{
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
						lastKind = kind;
						break;
					}
				}

				SetProjection(projectionIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				if (modelIndex >= activePartyCount) {
					int listPtr = GetBonusMenuMembers(this).m_bonusListPtr;
					PartPcs.DrawMenuIdx(*reinterpret_cast<int*>(listPtr + projectionIndex * 0x524 + 4));
				}
				RestoreProjection();
			}
			modelIndex++;
			lastKind = kind;
			break;
		case -1:
			break;
		default:
			{
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->tex));
				if (sprite->tex == 0x20) {
					GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
				}
				MenuPcs.DrawRect(0,
				    (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
				    (float)sprite->w, (float)sprite->h,
				    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
				if (sprite->tex == 0x20) {
					GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
				}
				lastKind = kind;
			}
			break;
		}

	}

	DrawBonusActiveMarks(this, statePtr, artiAlpha);
	DrawBonusPartyNames(this, header, sprites);
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	int activePartyCount = s_Rinfo->m_partyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int idx;
		int iconBase;
		int detailBase;

		GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, sizeof(BonusAnimList));
		*(short*)(statePtr + 0x22) = 0;

		idx = 0;
		InitAnimSprite(&sprites[idx++], 0x16, 0, 0, 0x280, 0x1c0, 0, 0);
		BonusSpriteFlags(&sprites[0]) = 3;
		sprites[0].alpha = 0.0f;

		InitAnimSprite(&sprites[idx++], -3, 0xf0, 0x38, 0x168, 0x148, 0, 8);
		ResetAnimSpriteMotion(&sprites[1]);
		InitAnimSprite(&sprites[idx++], 0x1f, 0, 0, 0x80, 0x78, 9999, 8);
		sprites[2].mulX = -150.0f;
		sprites[2].mulY = -150.0f;
		sprites[2].scale = 2.0f;
		sprites[2].alpha = 0.0f;
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
			int start = (int)((float)(10 + i * 5) * 0.6f);
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
			sprites[idx].scale = 1.0f;
			sprites[idx].depth = 1.0f;
			sprites[idx].motionX = 100.0f;
			sprites[idx].motionY = 0.0f;
			sprites[idx].targetX = (float)sprites[idx].x + sprites[idx].motionX;
			sprites[idx].targetY = (float)sprites[idx].y + sprites[idx].motionY;
			idx++;
		}

		y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			short x = ((0 < i) && (i < 3)) ? 8 : 0x20;
			InitAnimSprite(&sprites[idx], 0x19, x, y, 0x38, 0x28, i * 2, 8);
			ResetAnimSpriteMotion(&sprites[idx]);
			sprites[idx].mulX = (float)(i * sprites[idx].w);
			idx++;
			y += 0x60;
		}

		for (int i = 0; i < activePartyCount; i++) {
			InitSelectOpenPartyName(&sprites[idx], &sprites[iconBase + i], 0x50, 0x48, sprites[detailBase + i].startFrame + 2);
			idx++;
		}

		ArtiBaseInfoInit(reinterpret_cast<CMenuPcs::Sprt2*>(&sprites[1]), reinterpret_cast<CMenuPcs::Sprt2*>(&sprites[3]));
		int boardPtr = GetBonusMenuMembers(this).m_bonusBoardPtr;
		int entryOffset = activePartyCount * 0xA0;
		for (int i = 0; i < 8; i++) {
			BonusAnimSprite* boardSprite = &sprites[1];
			*reinterpret_cast<int*>(boardPtr + entryOffset) = 0;
			*reinterpret_cast<int*>(boardPtr + entryOffset + 4) = 0;
			int centerX = (int)((double)(float)((double)boardSprite->w * 0.5 + (double)boardSprite->x) - 320.0);
			int centerY = (int)((double)(float)((double)boardSprite->h * 0.5 + (double)boardSprite->y) - 240.0);
			*reinterpret_cast<short*>(boardPtr + entryOffset + 8) = (short)centerX;
			*reinterpret_cast<short*>(boardPtr + entryOffset + 10) = (short)centerY;
			*reinterpret_cast<short*>(boardPtr + entryOffset + 12) = 0x280;
			*reinterpret_cast<short*>(boardPtr + entryOffset + 14) = 0x1C0;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x10) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x14) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x18) = 1000.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x1C) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x20) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x24) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x28) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x2C) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x30) = 0.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x34) = 1.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x38) = 1.0f;
			*reinterpret_cast<float*>(boardPtr + entryOffset + 0x3C) = 1.0f;
			*reinterpret_cast<int*>(boardPtr + entryOffset + 0x40) = 0;
			*reinterpret_cast<int*>(boardPtr + entryOffset + 0x44) = 0;
			*reinterpret_cast<int*>(boardPtr + entryOffset + 0x48) = 0x280;
			*reinterpret_cast<int*>(boardPtr + entryOffset + 0x4C) = 0x1C0;
			entryOffset += 0x50;
		}

		header->count = (short)idx;
		header->finished = 0;
		*(unsigned char*)(statePtr + 0xb) = 1;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame > 9998) {
			doneCount++;
		}

		if (frame < sprite->startFrame) {
			continue;
		}

		if (frame < sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}

		float progress = CalcBonusSpriteProgress(sprite, frame);

		if (progress < 0.0f) {
			sprite->alpha = 0.0f;
			continue;
		}

		sprite->alpha = progress;
		switch (sprite->kind) {
		case 0x16:
			sprite->scale = 3.0f;
			break;
		case -3:
			sprite->mulY = (1.0f - progress) * 24.0f;
			break;
		case 0x1f:
			sprite->mulX = -150.0f * (1.0f - progress);
			sprite->mulY = -150.0f * (1.0f - progress);
			sprite->scale = 1.0f + (1.0f - progress);
			break;
		case -4:
			sprite->mulY = (1.0f - progress) * 20.0f;
			break;
		case 0:
			sprite->mulX = (1.0f - progress) * sprite->w;
			sprite->mulY = (1.0f - progress) * sprite->h;
			break;
		case 0x19:
			sprite->mulX = (1.0f - progress) * 20.0f;
			sprite->scale = 0.85f + progress * 0.15f;
			break;
		case -1:
			sprite->mulX = (1.0f - progress) * 24.0f;
			sprite->mulY = (1.0f - progress) * 6.0f;
			break;
		case -2:
			sprite->scale = 0.75f + progress * 0.25f;
			break;
		default:
			break;
		}
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
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int modelIndex = 0;
	int lastKind = 0;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
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

				if (0.0f < *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C)) {
					SetProjection(modelIndex);
					SetLight(1);
					unsigned int oldFlags = handle->m_flags;
					handle->m_flags = 0x300543;
					handle->Draw(5);
					handle->m_flags = oldFlags;
					RestoreProjection();
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
					_GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
					colors[0] = white;
					colors[1] = white;
					colors[2] = white;
					colors[3] = white;
					_GXColor color = white;
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
					if (i < s_CntTop || i >= s_CntTop + activePartyCount) {
						MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
						    (float)sprite->w, (float)sprite->h,
						    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
					} else {
						int value = s_Rinfo->m_party[i - s_CntTop].m_totalValue;
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
						float digitX = ((3.0f * digitW) - ((float)digitCount * digitW)) * 0.5f + (float)sprite->x;
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
	CFont* font = GetBonusMenuMembers(this).m_font;
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.9f);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[128];
	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->kind == -1) {
			_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
			font->SetColor(color);

			int partyIndex = textIndex % activePartyCount;
			CCaravanWork* caravanWork =
			    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
			if (textIndex < activePartyCount) {
				strcpy(text, reinterpret_cast<char*>(caravanWork->unk_0x3ca_0x3dd));
			} else {
				BonusFlatDataRaw* flat = reinterpret_cast<BonusFlatDataRaw*>(&Game.m_cFlatDataArr[1]);
				strcpy(text, flat->m_table[7].m_strings[(int)caravanWork->m_bonusCondition * 2 + 1]);
			}

			float y = (float)sprite->y + sprite->motionY - 6.0f;
			if (textIndex < activePartyCount) {
				y -= 6.0f;
			}
			font->SetPosX((float)sprite->x + sprite->motionX);
			font->SetPosY(y);
			font->Draw(text);

			textIndex++;
			if (textIndex == activePartyCount) {
				font = GetBonusMenuMembers(this).m_fontWide;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	const int activePartyCount = s_Rinfo->m_partyCount;
	const int baseCount = 1 + activePartyCount * 3;
	const int frameBase = 1;
	const int iconBase = frameBase + activePartyCount;
	const int digitBase = iconBase + activePartyCount;
	const int frameEchoBase = digitBase + activePartyCount;
	const int iconEchoBase = frameEchoBase + activePartyCount;
	const int digitEchoBase = iconEchoBase + activePartyCount;
	const int nameBase = digitEchoBase + activePartyCount;
	const int closeCount = nameBase + activePartyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;

		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].timer = 0;
			sprites[i].motionX = 0.0f;
			sprites[i].motionY = 0.0f;
		}

		sprites[0].startFrame = 9999;
		BonusSpriteFlags(&sprites[0]) = 3;

		for (int i = 0; i < activePartyCount; i++) {
			sprites[frameBase + i].startFrame = 0x10;
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[iconBase + i];
			BonusAnimSprite* source = &sprites[frameBase + i];
			sprite->startFrame = source->startFrame + source->duration;
			BonusSpriteFlags(sprite) = 1;
			sprite->targetX = (float)sprite->x;
			sprite->motionX = 100.0f;
			sprite->x = (short)((float)sprite->x - sprite->motionX);
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[digitBase + i];
			BonusAnimSprite* source = &sprites[iconBase + i];
			sprite->startFrame = source->startFrame + source->duration;
			BonusSpriteFlags(sprite) = 1;
		}

		for (int i = 0; i < activePartyCount; i++) {
			sprites[frameEchoBase + i].startFrame = 0;
		}

		for (int i = 0; i < activePartyCount; i++) {
			sprites[iconEchoBase + i].startFrame = 9999;
			BonusSpriteFlags(&sprites[iconEchoBase + i]) = 3;
		}

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[digitEchoBase + i];
			BonusAnimSprite* source = &sprites[digitBase + i];
			sprite->startFrame = source->startFrame;
			BonusSpriteFlags(sprite) = 1;
			sprite->targetX = (float)sprite->x;
			sprite->motionX = 100.0f;
			sprite->x = (short)((float)sprite->x - sprite->motionX);
		}

		int countTop = digitEchoBase + activePartyCount + 1;
		if (digitEchoBase + activePartyCount < (int)header->count) {
			sprites[digitEchoBase + activePartyCount].startFrame = sprites[1].startFrame;
		}
		if (countTop + activePartyCount > (int)header->count) {
			countTop = (int)header->count - activePartyCount;
		}
		s_CntTop = (unsigned char)countTop;

		for (int i = 0; i < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[(int)s_CntTop + i];
			sprite->startFrame = 8;
			sprite->duration = 8;
		}

		for (int i = 0; i < (int)header->count; i++) {
			BonusAnimSprite* sprite = &sprites[i];
			if (sprite->motionX == 0.0f) {
				sprite->targetX = (float)sprite->x;
			}
			if (sprite->motionY == 0.0f) {
				sprite->targetY = (float)sprite->y;
			}
		}

		*(short*)(animPtr + 6) = 0;
		*(unsigned char*)(statePtr + 0xb) = 1;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		int flags = BonusSpriteFlags(sprite);

		if ((flags & 1) == 0) {
			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			}
			if (frame < sprite->startFrame + sprite->duration) {
				sprite->alpha = 1.0f - ((float)sprite->timer / (float)sprite->duration);
			} else {
				sprite->alpha = 0.0f;
			}
		} else {
			sprite->alpha = 0.0f;
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame > 9998) {
			doneCount++;
		}

		if ((flags & 2) == 0 && (sprite->motionX != 0.0f || sprite->motionY != 0.0f)) {
			float progress = 1.0f - ((float)sprite->timer / (float)sprite->duration);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (sprite->targetY - (float)sprite->y) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
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
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * *reinterpret_cast<float*>(statePtr));
			PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
		}

		if (i < activePartyCount) {
			scaleMtx[1][3] = s_BonusModelYPos[tribeId];
		} else {
			scaleMtx[1][3] = 0.0f;
		}
		scaleMtx[0][3] = 0.0f;
		scaleMtx[2][3] = scaleMtx[0][3];

		CChara::CModel* model = handle->m_model;
		model->m_flags10C = (model->m_flags10C & 0x7F) | 0x80;
		model->SetMatrix(scaleMtx);
		model->CalcMatrix();
		model->CalcSkin();
		if (i < activePartyCount) {
			model->m_lightAlpha = 1.0f;
		} else {
			model->m_lightAlpha = sprites[frameEchoBase + i - activePartyCount].alpha;
		}
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
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
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int modelIndex = 0;
	int lastKind = 0;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	DrawInit();
	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		int kind = sprite->kind;

		if (kind >= 0 || kind == -2) {
			if (kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex < activePartyCount * 2) {
					handle = GetBonusDisplayHandleSlots(this)[modelIndex - activePartyCount];
				} else {
					lastKind = kind;
					continue;
				}

				SetProjection(modelIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				RestoreProjection();
				modelIndex++;
				lastKind = kind;
			} else {
				if (lastKind < 0) {
					DrawInit();
					SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				SetTexture(static_cast<CMenuPcs::TEX>(kind));

				if (i < s_CntTop || i >= s_CntTop + activePartyCount) {
					DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
					    (float)sprite->w, (float)sprite->h,
					    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
				} else {
					int value = s_Rinfo->m_party[i - s_CntTop].m_totalValue;
					if (*(short*)(statePtr + 0x10) == 0) {
						int frame = (int)*(short*)(statePtr + 0x22) - 8;
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
					float digitX = ((3.0f * digitW) - ((float)digitCount * digitW)) * 0.5f + (float)sprite->x;
					for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
						DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
						    digitW * (float)digits[digitIndex], sprite->mulY,
						    sprite->depth, sprite->depth, 0.0f);
						digitX += digitW;
					}
				}
				lastKind = kind;
			}
		}
	}

	DrawInit();
	CFont* font = GetBonusMenuMembers(this).m_font;
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.9f);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[128];
	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->kind == -1) {
			_GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
			font->SetColor(color);

			int partyIndex = textIndex % activePartyCount;
			CCaravanWork* caravanWork =
			    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
			if (textIndex < activePartyCount) {
				strcpy(text, reinterpret_cast<char*>(caravanWork->unk_0x3ca_0x3dd));
			} else {
				BonusFlatDataRaw* flat = reinterpret_cast<BonusFlatDataRaw*>(&Game.m_cFlatDataArr[1]);
				strcpy(text, flat->m_table[7].m_strings[(int)caravanWork->m_bonusCondition * 2 + 1]);
			}

			float y = (float)sprite->y + sprite->motionY - 6.0f;
			if (textIndex < activePartyCount) {
				y -= 6.0f;
			}
			font->SetPosX((float)sprite->x + sprite->motionX);
			font->SetPosY(y);
			font->Draw(text);

			textIndex++;
			if (textIndex == activePartyCount) {
				font = GetBonusMenuMembers(this).m_fontWide;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int countTop = header->count;
		s_CntTop = (unsigned char)countTop;
		for (int i = 0; i < activePartyCount; i++) {
			short stripX = ((0 < i) && (i < 3)) ? 8 : 0x20;
			short y = (short)(0x28 + i * 0x60);
			BonusAnimSprite* sprite = &sprites[countTop + i];
			sprite->x = stripX;
			sprite->y = y;
			sprite->w = 0x38;
			sprite->h = 0x28;
			sprite->mulX = (float)(s_Rinfo->m_party[i].m_rank * sprite->w);
			sprite->alpha = 0.0f;
			sprite->depth = 1.0f;
			sprite->kind = 0x19;
			sprite->timer = 0;
			sprite->startFrame = 9999;
			sprite->duration = 4;
			sprite->scale = 1.0f;
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->targetX = (float)(sprite->x - 0x60);
			sprite->targetY = (float)(sprite->y - 0x40);
		}

		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = GetBonusDisplayHandleSlots(this)[i];
			if (handle != 0) {
				*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C) = 0.0f;
			}
		}

		header->count = (short)(countTop + activePartyCount);
		*(unsigned char*)(statePtr + 0xb) = 1;
	}

	if (*(short*)(statePtr + 0x10) == 0) {
		*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	}

	int frame = (int)*(short*)(statePtr + 0x22) - 8;
	int countTop = (int)header->count - activePartyCount;

	for (int i = 0; i < activePartyCount; i++) {
		BonusAnimSprite* sprite = &sprites[countTop + i];
		if (*(short*)(statePtr + 0x10) == 0) {
			int value = s_Rinfo->m_party[i].m_totalValue;
			if (frame == value) {
				Sound.PlaySe(0x4b, 0x40, 0x7f, 0);
				sprite->timer = frame;
			}

			if (frame < sprite->timer) {
				sprite->alpha = 0.0f;
			} else {
				int elapsed = frame - sprite->timer;
				sprite->alpha = 1.0f;
				if (elapsed < sprite->duration) {
					float progress = 1.0f - ((float)elapsed / (float)sprite->duration);
					sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
					sprite->motionY = (sprite->targetY - (float)sprite->y) * progress;
				} else {
					sprite->motionX = 0.0f;
					sprite->motionY = 0.0f;
				}
			}
		} else {
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->alpha = 1.0f;
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
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * *reinterpret_cast<float*>(statePtr));
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

	if (*(short*)(statePtr + 0x10) == 0 && frame >= 0 && frame <= s_Rinfo->m_winnerTotalValue) {
		Sound.PlaySe(0x4a, 0x40, 0x7f, 0);
	}

	if (*(short*)(statePtr + 0x10) == 0 && frame >= 0 &&
	    (double)s_Rinfo->m_winnerTotalValue + 8.333333134651184 <= (double)frame) {
		*(short*)(statePtr + 0x10) = 1;
		return;
	}

	if (*(short*)(statePtr + 0x10) != 0) {
		unsigned short buttons = 0;
		int padRemap = Pad._448_4_;
		int padLock = Pad._452_4_;
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
			*(short*)(animPtr + 6) = 1;
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
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int modelIndex = 0;

	if (*(unsigned char*)(statePtr + 0xb) != 0) {
		int activePartyCount = s_Rinfo->m_partyCount;
		BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
		BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
		CCharaPcs::CHandle** displaySlots = GetBonusDisplayHandleSlots(this);
		int lastKind = 0;

		DrawInit();
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		for (int i = 0; i < (int)header->count; i++) {
			BonusAnimSprite* sprite = &sprites[i];
			int kind = sprite->kind;

			if (kind >= 0 || kind == -2) {
				if (kind == -2) {
					CCharaPcs::CHandle* handle;
					if (modelIndex < activePartyCount) {
						handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
					} else {
						handle = displaySlots[modelIndex - activePartyCount];
					}

					if (0.0f < *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C)) {
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
						_GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
						colors[0] = white;
						colors[1] = white;
						colors[2] = white;
						colors[3] = white;
						_GXColor color = white;
						GXSetChanMatColor(GX_COLOR0A0, color);
					} else {
						_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
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
							    (float)sprite->x + ((3.0f * (float)sprite->w - (float)sprite->w) * 0.5f),
							    (float)sprite->y, (float)sprite->w, (float)sprite->h,
							    0.0f, sprite->mulY, sprite->depth, sprite->depth, 0.0f);
						}
					}
					lastKind = kind;
				}
			}
		}

		DrawInit();
		CFont* font = GetBonusMenuMembers(this).m_font;
		font->SetMargin(1.0f);
		font->SetShadow(1);
		font->SetScale(0.9f);
		font->SetTlut(7);
		font->DrawInit();

		int textIndex = 0;
		char text[128];
		for (int i = 0; i < (int)header->count; i++) {
			BonusAnimSprite* sprite = &sprites[i];
			if (sprite->kind == -1) {
				_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
				font->SetColor(color);

				int partyIndex = textIndex % activePartyCount;
				CCaravanWork* caravanWork =
				    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[s_Rinfo->m_party[partyIndex].m_partySlot]);
				if (textIndex < activePartyCount) {
					strcpy(text, reinterpret_cast<char*>(caravanWork->unk_0x3ca_0x3dd));
				} else {
					BonusFlatDataRaw* flat = reinterpret_cast<BonusFlatDataRaw*>(&Game.m_cFlatDataArr[1]);
					strcpy(text, flat->m_table[7].m_strings[(int)caravanWork->m_bonusCondition * 2 + 1]);
				}

				float y = (float)sprite->y + sprite->motionY - 6.0f;
				if (textIndex < activePartyCount) {
					y -= 6.0f;
				}
				font->SetPosX((float)sprite->x + sprite->motionX);
				font->SetPosY(y);
				font->Draw(text);

				textIndex++;
				if (textIndex == activePartyCount) {
					font = GetBonusMenuMembers(this).m_fontWide;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	const int activePartyCount = s_Rinfo->m_partyCount;
	const int frameBase = 1;
	const int iconBase = frameBase + activePartyCount;
	const int modelBase = iconBase + activePartyCount;
	const int itemModelBase = modelBase + activePartyCount;
	const int nameBase = itemModelBase + activePartyCount;
	const int labelBase = nameBase + activePartyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		GetBonusMenuMembers(this).m_bonusAlpha = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, sizeof(BonusAnimList));

		header->count = (short)(1 + activePartyCount * 6);

		InitAnimSprite(&sprites[0], 0x16, 0, 0, 0x280, 0x1c0, 0, 8);
		sprites[0].depth = 0.0f;
		sprites[0].scale = 0.0f;
		sprites[0].alpha = 0.0f;

		for (int i = 0; i < activePartyCount; i++) {
			int idx = frameBase + i;
			InitAnimSprite(&sprites[idx], 0x17, 0x80, (short)(0x38 + i * 0x60), 0x1a0, 0x40, 0, 8);
			sprites[idx].depth = 1.0f;
			sprites[idx].alpha = 0.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = iconBase + i;
			InitAnimSprite(&sprites[idx], 0x18, 0x48, (short)(0x28 + i * 0x60), 0x60, 0x58, 0x20 + i * 3, 8);
			sprites[idx].depth = 1.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = -48.0f;
			sprites[idx].mulY = 12.0f;
			sprites[idx].scale = 0.8f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = modelBase + i;
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, 0x28 + i * 4, 0x18);
			sprites[idx].depth = 0.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].scale = 1.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = itemModelBase + i;
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, 0x34 + i * 4, 0x18);
			sprites[idx].depth = 0.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].scale = 0.95f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = nameBase + i;
			InitAnimSprite(&sprites[idx], -1, 0x108, (short)(0x6C + i * 0x60), 0, 0, 0x2E + i * 4, 0x18);
			sprites[idx].depth = 1.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = 18.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = labelBase + i;
			InitAnimSprite(&sprites[idx], -1, 0x108, (short)(0x90 + i * 0x60), 0, 0, 0x3A + i * 4, 0x18);
			sprites[idx].depth = 1.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = 24.0f;
		}

		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = GetBonusDisplayHandleSlots(this)[i];
			if (handle != 0) {
				handle->m_model->m_lightAlpha = 0.0f;
			}
		}

		*(unsigned char*)(statePtr + 0xb) = 1;
		header->finished = 0;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (frame < sprite->startFrame) {
			continue;
		}

		if (frame < sprite->startFrame + sprite->duration) {
			sprite->timer++;
			sprite->alpha = (float)sprite->timer / (float)sprite->duration;
		} else {
			sprite->alpha = 1.0f;
			doneCount++;
		}

		if (i == 0) {
			sprite->scale = sprite->alpha * 3.0f;
		} else if (i >= frameBase && i < iconBase) {
			sprite->mulX = (1.0f - sprite->alpha) * -24.0f;
		} else if (i >= iconBase && i < modelBase) {
			sprite->mulX = (1.0f - sprite->alpha) * -48.0f;
			sprite->mulY = (1.0f - sprite->alpha) * 12.0f;
			sprite->scale = 0.8f + sprite->alpha * 0.2f;
		} else if (i >= modelBase && i < itemModelBase) {
			sprite->scale = 0.85f + sprite->alpha * 0.15f;
		} else if (i >= itemModelBase && i < nameBase) {
			sprite->mulY = (1.0f - sprite->alpha) * 10.0f;
			sprite->scale = 0.8f + sprite->alpha * 0.15f;
		} else if (i >= nameBase && i < labelBase) {
			sprite->mulX = (1.0f - sprite->alpha) * 18.0f;
		} else if (i >= labelBase) {
			sprite->mulX = (1.0f - sprite->alpha) * 24.0f;
			sprite->mulY = (1.0f - sprite->alpha) * 4.0f;
		}

		if (sprite->kind == 0x17 && sprite->timer == 1) {
			Sound.PlaySe(0x49, 0x40, 0x7f, 0);
		}
		if (sprite->kind == -2 && sprite->timer == 1) {
			Sound.PlaySe(0x47, 0x40, 0x7f, 0);
		}
		if (sprite->kind == -1 && sprite->timer == 1 && GetBonusMenuMembers(this).m_bonusAlpha == 0) {
			Sound.PlaySe(0x48, 0x40, 0x7f, 0);
			GetBonusMenuMembers(this).m_bonusAlpha = 1;
		}
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
	gUtil.ClearZBufferRect(0.0f, 0.0f, 640.0f, 480.0f);

	if ((unsigned int)System.m_execParam >= 1) {
		System.Printf(const_cast<char*>(sDrawBonusFmt), (int)*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c));
	}

	switch (*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c)) {
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
	*reinterpret_cast<float*>(GetBonusMenuMembers(this).m_bonusStatePtr) =
	    static_cast<float>((double)*reinterpret_cast<float*>(GetBonusMenuMembers(this).m_bonusStatePtr) - kPppCrystal2RefractionScale);

	if (*(short*)(GetBonusMenuMembers(this).m_bonusAnimPtr + 6) != 0) {
		*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c) =
		    *(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c) + 1;
		*(short*)(GetBonusMenuMembers(this).m_bonusAnimPtr + 6) = 0;
		*(unsigned char*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0xb) = 0;
		*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x10) = 0;
		*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x22) = 0;
	}

	switch (*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c)) {
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
		if (*(short*)(GetBonusMenuMembers(this).m_bonusAnimPtr + 6) != 0) {
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
	Pad._456_4_ = 1;

	if (GetBonusMenuMembers(this).m_fontWide != 0) {
		ReleaseBonusRefObject(GetBonusMenuMembers(this).m_fontWide);
		GetBonusMenuMembers(this).m_fontWide = 0;
	}

	for (int i = 0; i < 0x18; i++) {
		CCharaPcs::CHandle** handleSlot = &GetBonusDisplayHandleSlots(this)[i];
		if (*handleSlot != 0) {
			delete *handleSlot;
			*handleSlot = 0;
		}
	}

	int ptr = GetBonusMenuMembers(this).m_bonusListPtr;
	if (ptr != 0) {
		delete[] (CMenuPcs::EffectInfo*)ptr;
		GetBonusMenuMembers(this).m_bonusListPtr = 0;
	}

	if (s_Rinfo != 0) {
		delete s_Rinfo;
		s_Rinfo = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusStatePtr;
	if (ptr != 0) {
		delete (BonusMenuStateRaw*)ptr;
		GetBonusMenuMembers(this).m_bonusStatePtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	if (ptr != 0) {
		delete (BonusAnimList*)ptr;
		GetBonusMenuMembers(this).m_bonusAnimPtr = 0;
	}

	if (s_Base[0] != 0) {
		delete reinterpret_cast<BonusBaseRaw*>(s_Base[0]);
		s_Base[0] = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusBoardPtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusBoardPtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusAuxPtr;
	if (ptr != 0) {
		delete (BonusMenuAuxRaw*)ptr;
		GetBonusMenuMembers(this).m_bonusAuxPtr = 0;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int listPtr = GetBonusMenuMembers(this).m_bonusListPtr;
	int auxPtr = GetBonusMenuMembers(this).m_bonusAuxPtr;
	int boardPtr = GetBonusMenuMembers(this).m_bonusBoardPtr;

	Pad._456_4_ = 0x28;
	for (int i = 0; i < 4; i++) {
		GbaQue.OpenMenu(i, 0, 0);
		GbaQue.SetRadarMode(i, 0);
	}

	loadTexture(PTR_s_bonus, 2, 1, s_bonusTextureTable, 0x16, 0x12, 0);
	sprintf(fontPath, s_menuSubfontPathFmt, Game.GetLangString());
	loadFont(0, fontPath, 1, -1);

	s_Rinfo = new BonusSummaryData;
	memset(s_Rinfo, 0, sizeof(*s_Rinfo));
	for (int i = 0; i < 4; i++) {
		s_Rinfo->m_tempArtifacts[i] = -1;
	}
	for (int i = 0; i < 4; i++) {
		s_Rinfo->m_bossArtifacts[i] = -1;
	}

	statePtr = reinterpret_cast<int>(new BonusMenuStateRaw);
	GetBonusMenuMembers(this).m_bonusStatePtr = statePtr;
	listPtr = reinterpret_cast<int>(new CMenuPcs::EffectInfo[0x28]);
	GetBonusMenuMembers(this).m_bonusListPtr = listPtr;

	BonusEffectSlotList* effectSlots = reinterpret_cast<BonusEffectSlotList*>(listPtr);
	for (int i = 0; i < 5; i++) {
		InitBonusEffectSlotBlock(&effectSlots->slots[i]);
	}
	memset((void*)statePtr, 0, sizeof(BonusMenuStateRaw));
	s_Base[0] = reinterpret_cast<float*>(new BonusBaseRaw);
	memset(s_Base[0], 0, sizeof(float) * 18);
	animPtr = reinterpret_cast<int>(new BonusAnimList);
	GetBonusMenuMembers(this).m_bonusAnimPtr = animPtr;
	memset((void*)animPtr, 0, sizeof(BonusAnimList));
	boardPtr = reinterpret_cast<int>(new unsigned char[sizeof(BonusBoardEntryList)]);
	GetBonusMenuMembers(this).m_bonusBoardPtr = boardPtr;
	auxPtr = reinterpret_cast<int>(new BonusMenuAuxRaw);
	GetBonusMenuMembers(this).m_bonusAuxPtr = auxPtr;
	memset((void*)auxPtr, 0, sizeof(BonusMenuAuxRaw));
	unsigned char* boardEntries = reinterpret_cast<unsigned char*>(boardPtr);
	for (int i = 0; i < 0x18; i++) {
		InitBonusBoardEntry(boardEntries + i * 0x50);
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

			BonusPartySummary& entry = s_Rinfo->m_party[activeCount];
			entry.m_partySlot = i;
			entry.m_partyHandle =
			    (Game.m_partyObjArr[i] != 0) ? *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(Game.m_partyObjArr[i]) + 0xF8) : 0;
			entry.m_bonusCondition = (int)caravanWork->m_bonusCondition;
			entry.m_foodValue = (int)caravanWork->m_artifactRelated[2] + (int)caravanWork->m_artifactRelated[3];
			if (entry.m_foodValue > 100) {
				entry.m_foodValue = 100;
			}
			entry.m_artifactValue =
			    (int)caravanWork->m_artifactRelated[0] + (int)caravanWork->m_artifactRelated[1] - (int)caravanWork->m_artifactRelated[4];
			entry.m_totalValue = entry.m_foodValue + entry.m_artifactValue;
			entry.m_selectedItemId = -1;
			entry.m_selectedSlot = -1;
			int totalValueClamped;
			if (entry.m_totalValue < 0) {
				totalValueClamped = 0;
			} else {
				totalValueClamped = 999;
				if (entry.m_totalValue < 1000) {
					totalValueClamped = entry.m_totalValue;
				}
			}
			entry.m_totalValue = totalValueClamped;
			entry.m_tribeId = (unsigned int)caravanWork->m_tribeId;
			*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(entry.m_partyHandle->m_model) + 0x9C) = 0.0f;

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

			totalValue += entry.m_totalValue;
			activeCount++;
		}

		s_Rinfo->m_partyCount = activeCount;

		short* bossArtifact = reinterpret_cast<short*>(Game.GetBossArtifact(activeCount, totalValue));
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

		for (int i = 0; i < activeCount; i++) {
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

		int order[4] = {0, 1, 2, 3};
		for (int i = 0; i < activeCount; i++) {
			for (int j = i + 1; j < activeCount; j++) {
				BonusPartySummary& a = s_Rinfo->m_party[order[i]];
				BonusPartySummary& b = s_Rinfo->m_party[order[j]];
				unsigned int coin = rand();

				if (a.m_totalValue < b.m_totalValue ||
				    (a.m_totalValue == b.m_totalValue && a.m_artifactValue < b.m_artifactValue) ||
				    (a.m_totalValue == b.m_totalValue && a.m_artifactValue == b.m_artifactValue &&
				        a.m_foodValue < b.m_foodValue) ||
				    (a.m_totalValue == b.m_totalValue && a.m_artifactValue == b.m_artifactValue &&
				        a.m_foodValue == b.m_foodValue && (coin & 1) != 0)) {
					int temp = order[i];
					order[i] = order[j];
					order[j] = temp;
				}
			}
		}

		s_Rinfo->m_winnerTotalValue = 0;
		for (int i = 0; i < activeCount; i++) {
			BonusPartySummary& ranked = s_Rinfo->m_party[order[i]];
			ranked.m_rank = i;
			if (i == 0) {
				s_Rinfo->m_winnerTotalValue = ranked.m_totalValue;
			}
		}

		CMemory::CStage* stage = GetBonusAllocStage(this);
		CCharaPcs::CHandle** displaySlots = GetBonusDisplayHandleSlots(this);
		for (int i = 0; i < 0x18; i++) {
			displaySlots[i] = 0;
		}

		for (int i = 0; i < activeCount * 2; i++) {
			BonusPartySummary& entry = s_Rinfo->m_party[i % activeCount];
			unsigned long modelCode = entry.m_tribeId + ((i < activeCount) ? 0x87 : 0x83);
			CCharaPcs::CHandle* handle =
			    new (stage, const_cast<char*>(s_bonus_menu_cpp), 0x183) CCharaPcs::CHandle;
			displaySlots[i] = handle;
			handle->Add();
			handle->LoadModel(3, modelCode & 0xFFF, (modelCode >> 12) & 0xF, 0, -1, 0, 0);
			handle->m_flags = 0x300543;
		}

		int handleIndex = activeCount * 2;
		short* rewardItems = &s_Rinfo->m_tempArtifacts[0];
		for (int artifactIndex = 0; artifactIndex < 8; artifactIndex++) {
			short itemId = rewardItems[artifactIndex];
			if (itemId <= 0) {
				displaySlots[handleIndex] = 0;
				handleIndex++;
				continue;
			}

			unsigned short itemModelCode =
			    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2);
			unsigned short modelNo = itemModelCode & 0x0FFF;
			CCharaPcs::CHandle* itemHandle =
			    new (stage, const_cast<char*>(s_bonus_menu_cpp), 0x19C) CCharaPcs::CHandle;
			displaySlots[handleIndex] = itemHandle;
			itemHandle->Add();
			itemHandle->LoadModel(3, modelNo, itemModelCode >> 12, 0, -1, 0, 0);
			itemHandle->m_flags = 0x300543;

			if (modelNo == 0x79) {
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
	*(short*)(GetBonusMenuMembers(this).m_bonusAuxPtr + 10) = 3;
	s_CntTop = 0;
	s_ArtiTop = 0;
	s_PlayerTop = 0;
	*(short*)(GetBonusMenuMembers(this).m_bonusStatePtr + 0x1c) = 0;
	Wind.ClearAll();
	GetBonusMenuMembers(this).m_bonusAlpha = 0;
	GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
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
	GetBonusMenuMembers(this).m_bonusAnimPtr = 0;
	s_Base[0] = 0;
}
