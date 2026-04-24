#include "ffcc/bonus_menu.h"
#include "ffcc/fontman.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include <string.h>

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawMcWin__8CMenuPcsFss(CMenuPcs*, short, short);
extern "C" void DrawMcWinMess__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetYesNoXPos__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" unsigned short GetButtonDown__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void GetSingWinSize__8CMenuPcsFiPsPsi(CMenuPcs*, short, short*, short*, int);
extern "C" void SetMcWinInfo__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" void SetProjection__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetLight__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void RestoreProjection__8CMenuPcsFv(CMenuPcs*);
extern "C" void Draw__Q29CCharaPcs7CHandleFi(void*, int);
extern "C" void DrawMenuIdx__8CPartPcsFi(CPartPcs*, int);
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" void OpenMenu__8GbaQueueFiii(void*, int, int, int);
extern "C" void SetRadarMode__8GbaQueueFii(void*, int, int);
extern "C" void loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs*, char**, int, int, void*, int, int, int);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void loadFont__8CMenuPcsFiPcii(CMenuPcs*, int, char*, int, int);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(CMenuPcs*, int);
extern "C" int sprintf(char*, const char*, ...);
extern char* PTR_s_bonus_802128c0[];
extern char DAT_802128e4[];
extern char s_dvd__smenu_subfont_fnt_801e3020[];
#pragma force_active on
extern "C" {
int gBonusMenuWork0 = 0;
unsigned char gBonusMenuFlag0 = 0;
unsigned char gBonusMenuFlag1 = 0;
unsigned char gBonusMenuFlag2 = 0;
unsigned char gBonusMenuFlagPad = 0;
float* gBonusCheckMarkPosBuffer[2];
}
#pragma force_active reset
static const char s_drawBonusFmt[] = "draw Bonus[%d]\n";
static const char s_bonusMenuSourceFile[] = "bonus_menu.cpp";

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
	unsigned char pad[0x10];
};

STATIC_ASSERT(sizeof(BonusAnimHeader) == 8);
STATIC_ASSERT(sizeof(BonusAnimSprite) == 0x40);

struct BonusFlatTableRaw {
	int m_numEntries;
	char** m_strings;
	char* m_stringBuf;
};

struct BonusFlatDataRaw {
	unsigned char pad_0000[0x6C];
	BonusFlatTableRaw m_table[8];
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

static inline BonusMenuMembers& GetBonusMenuMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<BonusMenuMembers*>(menu);
}

static float CalcBonusSpriteProgress(const BonusAnimSprite* sprite, int frame);
static int GetActiveBonusPartyCount();
static float ClampBonusUnit(float value);
static const char* GetBonusPartyNameByActiveIndex(int activeIndex);
static CCaravanWork* GetBonusActiveCaravanByActiveIndex(int activeIndex);
static int GetBonusResultValueByActiveIndex(int activeIndex);
static const char* GetBonusResultLabelByActiveIndex(int activeIndex);
static void SetBonusPartyModelAlpha(CMenuPcs* menu, int modelIndex, float alpha);

static void InitAnimSprite(BonusAnimSprite* sprite, int kind, short x, short y, short w, short h, int startFrame, int duration)
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

static void ResetAnimSpriteMotion(BonusAnimSprite* sprite)
{
	sprite->mulX = 0.0f;
	sprite->mulY = 0.0f;
	sprite->alpha = 0.0f;
	sprite->depth = 0.0f;
	sprite->scale = 1.0f;
}

static float s_bonusArtiBasePosStorage0[18];
static float s_bonusArtiBasePosStorage1[18];

static void FillBonusArtiBasePositions(float* out, const BonusAnimSprite* boardSprite, const BonusAnimSprite* itemSprite)
{
	if (out == 0 || boardSprite == 0) {
		return;
	}

	const float x = (float)boardSprite->x + boardSprite->mulX;
	const float y = (float)boardSprite->y + boardSprite->mulY;
	const float w = (boardSprite->w > 0) ? (float)boardSprite->w : 288.0f;
	const float h = (boardSprite->h > 0) ? (float)boardSprite->h : 208.0f;
	const float itemW = (itemSprite != 0 && itemSprite->w > 0) ? (float)itemSprite->w : 112.0f;
	const float itemH = (itemSprite != 0 && itemSprite->h > 0) ? (float)itemSprite->h : 104.0f;
	const float quarterW = w * 0.25f;
	const float quarterH = h * 0.25f;
	const float halfW = w * 0.5f;
	const float halfH = h * 0.5f;
	const float itemQuarterW = itemW * 0.25f;
	const float itemQuarterH = itemH * 0.25f;

	memset(out, 0, sizeof(float) * 18);

	out[0] = x + quarterW;
	out[1] = y + quarterH;
	out[2] = x + w - itemW;
	out[3] = y + quarterH - itemQuarterH;
	out[4] = x + quarterW * 3.0f - itemQuarterW;
	out[5] = y + quarterH * 3.0f - itemQuarterH;
	out[6] = x + quarterW - itemQuarterW;
	out[7] = y + h - itemH;
	out[8] = x + halfW - itemQuarterW;
	out[9] = y + quarterH * 3.0f - itemQuarterH;
	out[10] = x;
	out[11] = y + quarterH - itemQuarterH;
	out[12] = x + halfW - itemQuarterW;
	out[13] = y + halfH - itemQuarterH;
	out[14] = x + quarterW - itemQuarterW;
	out[15] = y;
	out[16] = x + quarterW * 3.0f - itemQuarterW;
	out[17] = y + halfH - itemQuarterH;
}

static float* GetBonusArtiBasePositions(const BonusAnimSprite* sprite)
{
	gBonusCheckMarkPosBuffer[0] = s_bonusArtiBasePosStorage0;
	gBonusCheckMarkPosBuffer[1] = s_bonusArtiBasePosStorage1;
	FillBonusArtiBasePositions(gBonusCheckMarkPosBuffer[0], sprite, sprite);
	memcpy(gBonusCheckMarkPosBuffer[1], gBonusCheckMarkPosBuffer[0], sizeof(s_bonusArtiBasePosStorage1));
	return gBonusCheckMarkPosBuffer[0];
}

static void InitSelectOpenPartyIcon(BonusAnimSprite* sprite, int slotIndex, short y)
{
	short x = ((0 < slotIndex) && (slotIndex < 3)) ? 0x30 : 0x48;

	InitAnimSprite(sprite, 0, x, y, 0x60, 0x58, 0, 8);
	ResetAnimSpriteMotion(sprite);
	sprite->mulX = (float)sprite->w;
	sprite->mulY = (float)sprite->h;
}

static void InitSelectOpenPartyName(BonusAnimSprite* sprite, const BonusAnimSprite* iconSprite, short xOffset, short yOffset, int startFrame)
{
	InitAnimSprite(sprite, -1, (short)(iconSprite->x + xOffset), (short)(iconSprite->y + yOffset), 0, 0, startFrame, 8);
	ResetAnimSpriteMotion(sprite);
	sprite->mulX = 24.0f;
}

static void ApplySelectOpenSpriteMotion(BonusAnimSprite* sprite, int frame)
{
	float progress = CalcBonusSpriteProgress(sprite, frame);

	if (progress < 0.0f) {
		sprite->alpha = 0.0f;
		return;
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

static void ApplySelectCloseSpriteMotion(BonusAnimSprite* sprite, int frame)
{
	float progress = CalcBonusSpriteProgress(sprite, frame);

	if (progress < 0.0f) {
		sprite->alpha = 1.0f;
		return;
	}

	sprite->alpha = 1.0f - progress;
	switch (sprite->kind) {
	case 0x16:
		sprite->scale = 3.0f + progress * 0.5f;
		break;
	case -3:
		sprite->mulY = progress * 24.0f;
		break;
	case 0x1f:
		sprite->mulX = -150.0f * progress;
		sprite->mulY = -150.0f * progress;
		sprite->scale = 1.0f + progress;
		break;
	case -4:
		sprite->mulY = progress * 20.0f;
		break;
	case 0:
		sprite->mulX = progress * sprite->w;
		sprite->mulY = progress * sprite->h;
		break;
	case 0x19:
		sprite->mulX = progress * 20.0f;
		sprite->scale = 1.0f - progress * 0.15f;
		break;
	case -1:
		sprite->mulX = progress * 24.0f;
		sprite->mulY = progress * 6.0f;
		break;
	case -2:
		sprite->scale = 1.0f - progress * 0.25f;
		break;
	case 0x20:
		sprite->mulY = progress * 16.0f;
		sprite->scale = 1.0f + progress * 0.2f;
		break;
	default:
		break;
	}
}

static void DrawBonusTexturedSprite(CMenuPcs* menu, const BonusAnimSprite* sprite, float alpha)
{
	GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(menu, sprite->tex);
	if (sprite->tex == 0x20) {
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
	}
	DrawRect__8CMenuPcsFUlfffffffff(menu, 0,
	    (float)sprite->x + sprite->mulX, (float)sprite->y + sprite->mulY,
	    (float)sprite->w, (float)sprite->h,
	    sprite->depth, sprite->depth, sprite->scale, sprite->scale, 0.0f);
	if (sprite->tex == 0x20) {
		GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	}
}

static void DrawBonusSweepSprite(CMenuPcs* menu, const BonusAnimSprite* sprite, float alpha, bool opening)
{
	if (menu == 0 || sprite == 0 || alpha <= 0.0f) {
		return;
	}

	float width = (float)sprite->w;
	float height = (float)sprite->h;
	int duration = (sprite->duration > 0) ? sprite->duration : 1;
	float timer = (sprite->timer > 0) ? (float)(sprite->timer - 1) : 0.0f;
	float progress = ClampBonusUnit(timer / (float)duration);
	float fillWidth = (opening ? progress : (1.0f - progress)) * width;
	float fadeWidth = width / (float)duration;
	float x = (float)sprite->x + sprite->mulX;
	float y = (float)sprite->y + sprite->mulY;
	GXColor solidColors[4] = {
		{0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)},
		{0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)},
		{0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)},
		{0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)},
	};

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(menu, sprite->tex);
	GXSetChanMatColor(GX_COLOR0A0, solidColors[0]);

	if (fillWidth > 0.0f) {
		DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(menu, 0, x, y, fillWidth, height,
		    sprite->depth, sprite->depth, solidColors, 1.0f, 1.0f, 0.0f);
		x += fillWidth;
	}

	if (fillWidth > 0.0f && fillWidth < width) {
		GXColor fadeColors[4] = {
			{0xFF, 0xFF, 0xFF, 0x00},
			{0xFF, 0xFF, 0xFF, 0x00},
			{0xFF, 0xFF, 0xFF, 0x00},
			{0xFF, 0xFF, 0xFF, 0x00},
		};
		DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(menu, 0, x, y, fadeWidth, height,
		    sprite->depth, sprite->depth, fadeColors, 1.0f, 1.0f, 0.0f);
	}
}

static void DrawBonusPartyModel(CMenuPcs* menu, int modelIndex, float alpha)
{
	int activePartyCount = GetActiveBonusPartyCount();

	if (modelIndex >= activePartyCount) {
		return;
	}

	int basePtr = GetBonusMenuMembers(menu).m_bonusListPtr;
	if (basePtr == 0) {
		return;
	}

	int slotPtr = basePtr + (modelIndex * 0x524);
	void* handle = *(void**)slotPtr;
	if (handle == 0) {
		return;
	}

	SetBonusPartyModelAlpha(menu, modelIndex, ClampBonusUnit(alpha));
	SetProjection__8CMenuPcsFi(menu, modelIndex);
	SetLight__8CMenuPcsFi(menu, 1);
	unsigned int oldFlags = *(unsigned int*)((char*)handle + 8);
	*(unsigned int*)((char*)handle + 8) = 0x300543;
	Draw__Q29CCharaPcs7CHandleFi(handle, 5);
	*(unsigned int*)((char*)handle + 8) = oldFlags;
	DrawMenuIdx__8CPartPcsFi(&PartPcs, *(int*)(slotPtr + 4));
	RestoreProjection__8CMenuPcsFv(menu);
}

static void SetBonusPartyModelAlpha(CMenuPcs* menu, int modelIndex, float alpha)
{
	int activePartyCount = GetActiveBonusPartyCount();

	if (modelIndex < 0 || modelIndex >= activePartyCount) {
		return;
	}

	int basePtr = GetBonusMenuMembers(menu).m_bonusListPtr;
	if (basePtr == 0) {
		return;
	}

	int slotPtr = basePtr + (modelIndex * 0x524);
	void* handle = *(void**)slotPtr;
	if (handle == 0) {
		return;
	}

	int modelPtr = *(int*)((char*)handle + 0x168);
	if (modelPtr != 0) {
		*(float*)(modelPtr + 0x9C) = ClampBonusUnit(alpha);
	}
}

static void DrawBonusActiveMarks(CMenuPcs* menu, int statePtr, float alpha)
{
	if (statePtr == 0 || alpha <= 0.0f) {
		return;
	}

	unsigned char activeMask = *(unsigned char*)(statePtr + 9);
	if (activeMask == 0) {
		return;
	}

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(menu, 0);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(menu, 0x23);
	GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);

	float* markPos = gBonusCheckMarkPosBuffer[0];
	if (markPos == 0) {
		return;
	}

	for (int i = 0; i < 8; i++) {
		if ((activeMask & (1 << i)) == 0) {
			continue;
		}
		float x = markPos[i * 2 + 0] + 4.0f;
		float y = markPos[i * 2 + 1] + 4.0f;
		DrawRect__8CMenuPcsFUlfffffffff(menu, 0, x, y, 24.0f, 24.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

static int FindFirstBonusActiveSlot(unsigned char activeMask)
{
	for (int i = 0; i < 8; i++) {
		if ((activeMask & (1 << i)) != 0) {
			return i;
		}
	}

	return -1;
}

static void DrawBonusPartyNames(CMenuPcs* menu, BonusAnimHeader* header, BonusAnimSprite* sprites)
{
	CFont* font = GetBonusMenuMembers(menu).m_font;
	int activePartyCount = GetActiveBonusPartyCount();

	if (font == 0 || activePartyCount <= 0) {
		return;
	}

	DrawInit__8CMenuPcsFv(menu);
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(1.0f);
	font->SetTlut(7);
	font->DrawInit();

	int nameIndex = 0;
	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (sprite->kind != -1) {
			continue;
		}

		const char* name = GetBonusPartyNameByActiveIndex(nameIndex % activePartyCount);
		GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(ClampBonusUnit(sprite->alpha) * 255.0f)};
		font->SetColor(color);
		if (name != 0) {
			font->SetPosX((float)sprite->x + sprite->mulX);
			font->SetPosY((float)sprite->y + sprite->mulY - 12.0f);
			font->Draw(const_cast<char*>(name));
		}
		nameIndex++;
	}
}

static void DrawBonusMcWinOverlay(CMenuPcs* menu, int statePtr)
{
	int auxPtr = GetBonusMenuMembers(menu).m_bonusAuxPtr;

	if (statePtr == 0 || auxPtr == 0 || *(short*)(auxPtr + 10) == 3) {
		return;
	}

	DrawInit__8CMenuPcsFv(menu);
	DrawMcWin__8CMenuPcsFss(menu, -1, 1);
	if (*(short*)(auxPtr + 10) == 1) {
		DrawMcWinMess__8CMenuPcsFii(menu, 0x18, 1);
		DrawInit__8CMenuPcsFv(menu);
		int cursorX = GetYesNoXPos__8CMenuPcsFi(menu, (int)*(short*)(statePtr + 0x28));
		float cursorY = (float)(*(short*)(auxPtr + 2) + *(short*)(auxPtr + 6) - 0x3e);
		DrawCursor__8CMenuPcsFiif(menu, cursorX, (int)cursorY, 1.0f);
	}
}

static BonusAnimSprite* GetSelectCursorSprite(BonusAnimHeader* header, BonusAnimSprite* sprites)
{
	if (header == 0 || sprites == 0 || header->count <= 0) {
		return 0;
	}

	BonusAnimSprite* cursor = &sprites[header->count - 1];
	return (cursor->kind == 0x20) ? cursor : 0;
}

static void UpdateSelectCursorSprite(int statePtr, BonusAnimHeader* header, BonusAnimSprite* sprites, int frame)
{
	BonusAnimSprite* cursor = GetSelectCursorSprite(header, sprites);
	if (statePtr == 0 || cursor == 0) {
		return;
	}

	int slot = (*(short*)(statePtr + 0x26)) & 7;
	float pulse = (float)(frame & 0x1f) / 31.0f;
	float* markPos = gBonusCheckMarkPosBuffer[0];

	if (markPos != 0) {
		cursor->x = (short)(markPos[slot * 2 + 0] - 4.0f);
		cursor->y = (short)(markPos[slot * 2 + 1] - 8.0f);
	} else {
		cursor->x = (short)(28 + (slot & 3) * 72);
		cursor->y = (short)(36 + ((slot >> 2) & 1) * 104);
	}

	cursor->w = 0x40;
	cursor->h = 0x30;
	cursor->mulX = 0.0f;
	cursor->mulY = -2.0f + pulse * 4.0f;
	cursor->alpha = 0.75f + pulse * 0.25f;
	cursor->depth = 1.0f;
	cursor->scale = 0.9f + pulse * 0.15f;
}

static void TickAnimSprites(int statePtr, int animPtr, int fadeDir)
{
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	int doneCount = 0;
	int frame;

	if (header->count <= 0) {
		header->finished = 1;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	frame = (int)*(short*)(statePtr + 0x22);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (frame < sprite->startFrame) {
			continue;
		}

		if (frame < (sprite->startFrame + sprite->duration)) {
			float t;
			sprite->timer++;
			t = (sprite->duration > 0) ? ((float)sprite->timer / (float)sprite->duration) : 1.0f;
			sprite->alpha = (fadeDir >= 0) ? t : (1.0f - t);
		} else {
			sprite->alpha = (fadeDir >= 0) ? 1.0f : 0.0f;
			doneCount++;
		}

		if (sprite->alpha < 0.0f) {
			sprite->alpha = 0.0f;
		}
		if (sprite->alpha > 1.0f) {
			sprite->alpha = 1.0f;
		}
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
	}
}

static int GetActiveBonusPartyCount()
{
	unsigned int* scriptFoodBase = Game.m_scriptFoodBase;
	int activePartyCount = 0;

	for (int i = 0; i < 4; i++) {
		if (scriptFoodBase[i] != 0) {
			activePartyCount++;
		}
	}

	return (activePartyCount > 0) ? activePartyCount : 1;
}

static float ClampBonusUnit(float value)
{
	if (value < 0.0f) {
		return 0.0f;
	}
	if (value > 1.0f) {
		return 1.0f;
	}
	return value;
}

static float CalcBonusSpriteProgress(const BonusAnimSprite* sprite, int frame)
{
	if (frame < sprite->startFrame) {
		return -1.0f;
	}
	if (sprite->duration <= 0) {
		return 1.0f;
	}

	return ClampBonusUnit((float)(frame - sprite->startFrame + 1) / (float)sprite->duration);
}

static void BuildDefaultResultSprites(BonusAnimSprite* sprites, int activePartyCount)
{
	InitAnimSprite(&sprites[0], 0x16, 0, 0, 0x280, 0x1c0, 0, 8);
	sprites[0].depth = 0.0f;
	sprites[0].scale = 3.0f;
	sprites[0].alpha = 1.0f;

	for (int i = 0; i < activePartyCount; i++) {
		int frameIdx = i + 1;
		int iconIdx = 1 + activePartyCount + i;
		int digitIdx = 1 + activePartyCount + activePartyCount + i;

		InitAnimSprite(&sprites[frameIdx], 0x17, 0x80, (short)(0x38 + i * 0x60), 0x1a0, 0x40, 0x16 + i * 3, 8);
		sprites[frameIdx].alpha = 1.0f;

		InitAnimSprite(&sprites[iconIdx], 0x18, 0x48, (short)(0x28 + i * 0x60), 0x60, 0x58, 0x40 + i * 3, 8);
		sprites[iconIdx].alpha = 1.0f;

		InitAnimSprite(&sprites[digitIdx], -2, (short)(0x1b8 + i * 8), (short)(0x4c + i * 0x60), 0x18, 0x18, 0x58 + i * 2, 8);
		sprites[digitIdx].alpha = 1.0f;
	}
}

static int GetBonusPartySlotByActiveIndex(int activeIndex)
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

static CCaravanWork* GetBonusActiveCaravanByActiveIndex(int activeIndex)
{
	int slot = GetBonusPartySlotByActiveIndex(activeIndex);
	if (slot < 0) {
		return 0;
	}

	return reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[slot]);
}

static const char* GetBonusPartyNameByActiveIndex(int activeIndex)
{
	CCaravanWork* caravanWork = GetBonusActiveCaravanByActiveIndex(activeIndex);
	if (caravanWork == 0) {
		return 0;
	}

	return reinterpret_cast<const char*>(caravanWork->unk_0x3ca_0x3dd);
}

static int GetBonusResultValueByActiveIndex(int activeIndex)
{
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

static const char* GetBonusResultLabelByActiveIndex(int activeIndex)
{
	CCaravanWork* caravanWork = GetBonusActiveCaravanByActiveIndex(activeIndex);
	if (caravanWork == 0) {
		return 0;
	}

	int labelIndex = (int)caravanWork->m_bonusCondition * 2 + 1;
	if (labelIndex < 0) {
		return 0;
	}

	BonusFlatDataRaw* flat = reinterpret_cast<BonusFlatDataRaw*>(&Game.m_cFlatDataArr[1]);
	if (flat->m_table[7].m_strings == 0 || labelIndex >= flat->m_table[7].m_numEntries) {
		return 0;
	}

	return flat->m_table[7].m_strings[labelIndex];
}

static int GetBonusDisplayValueForFrame(int statePtr, int activeIndex)
{
	int target = GetBonusResultValueByActiveIndex(activeIndex);
	if (statePtr == 0 || *(short*)(statePtr + 0x10) != 0) {
		return target;
	}

	int reveal = (int)*(short*)(statePtr + 0x22) - 8;
	if (reveal < 0) {
		return 0;
	}
	if (reveal > target) {
		return target;
	}
	return reveal;
}

static unsigned short GetBonusAdvanceButtons(CMenuPcs* menu)
{
	unsigned short buttons = 0;
	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] == 0) {
			continue;
		}
		buttons = (unsigned short)(buttons | GetButtonDown__8CMenuPcsFi(menu, i));
	}
	return buttons;
}

} // namespace

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
	gBonusMenuWork0 = 0;
	GetBonusMenuMembers(this).m_bonusAnimPtr = 0;
	gBonusCheckMarkPosBuffer[0] = 0;
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

	for (int i = 0; i < 4; i++) {
		OpenMenu__8GbaQueueFiii(&GbaQue, i, 0, 0);
		SetRadarMode__8GbaQueueFii(&GbaQue, i, 0);
	}

	loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(this, PTR_s_bonus_802128c0, 2, 1, &DAT_802128e4, 0x16, 0x12, 0);
	sprintf(fontPath, s_dvd__smenu_subfont_fnt_801e3020, GetLangString__5CGameFv(&Game));
	loadFont__8CMenuPcsFiPcii(this, 0, fontPath, 1, -1);

	if (statePtr == 0) {
		statePtr = reinterpret_cast<int>(new unsigned char[0x48]);
		GetBonusMenuMembers(this).m_bonusStatePtr = statePtr;
	}
	if (animPtr == 0) {
		animPtr = reinterpret_cast<int>(new unsigned char[0x1008]);
		GetBonusMenuMembers(this).m_bonusAnimPtr = animPtr;
	}
	if (listPtr == 0) {
		listPtr = reinterpret_cast<int>(new unsigned char[0xCDB0]);
		GetBonusMenuMembers(this).m_bonusListPtr = listPtr;
	}
	if (auxPtr == 0) {
		auxPtr = reinterpret_cast<int>(new unsigned char[0xC]);
		GetBonusMenuMembers(this).m_bonusAuxPtr = auxPtr;
	}
	if (boardPtr == 0) {
		boardPtr = reinterpret_cast<int>(new unsigned char[0x780]);
		GetBonusMenuMembers(this).m_bonusBoardPtr = boardPtr;
	}

	if (statePtr != 0) {
		memset((void*)statePtr, 0, 0x48);
		*(short*)(statePtr + 0x1c) = 0;
		*(short*)(statePtr + 0x22) = 0;
		*(unsigned char*)(statePtr + 0xb) = 0;
	}
	if (animPtr != 0) {
		memset((void*)animPtr, 0, 0x1008);
	}
	if (listPtr != 0) {
		memset((void*)listPtr, 0, 0xCDB0);
		for (int i = 0; i < 0x28; i++) {
			int slot = listPtr + i * 0x524;
			*(int*)(slot + 0x0) = -1;
			*(int*)(slot + 0x4) = -1;
			*(int*)(slot + 0x8) = -1;
		}
	}
	if (auxPtr != 0) {
		memset((void*)auxPtr, 0, 0xC);
		*(short*)(auxPtr + 10) = 3;
	}
	if (boardPtr != 0) {
		memset((void*)boardPtr, 0, 0x780);
	}

	GetBonusMenuMembers(this).m_bonusAlpha = 0;
	GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
	gBonusCheckMarkPosBuffer[0] = 0;
	gBonusCheckMarkPosBuffer[1] = 0;
	GetAllPadOn();
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
	int ptr = GetBonusMenuMembers(this).m_bonusListPtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusListPtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusStatePtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusStatePtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusAnimPtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusBoardPtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusBoardPtr = 0;
	}

	ptr = GetBonusMenuMembers(this).m_bonusAuxPtr;
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		GetBonusMenuMembers(this).m_bonusAuxPtr = 0;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	short state;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	if (*(short*)(animPtr + 6) != 0) {
		*(short*)(statePtr + 0x1c) = *(short*)(statePtr + 0x1c) + 1;
		*(short*)(animPtr + 6) = 0;
		*(unsigned char*)(statePtr + 0xb) = 0;
		*(short*)(statePtr + 0x10) = 0;
		*(short*)(statePtr + 0x22) = 0;
	}

	state = *(short*)(statePtr + 0x1c);
	switch (state) {
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
		if (*(short*)(animPtr + 6) != 0) {
			CallWorldParam__8CMenuPcsFiii(this, 8, 0, 0);
		}
		break;
	case 6:
		ClrBattleItem();
		changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(this, 0);
		break;
	default:
		break;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	gUtil.ClearZBufferRect(0.0f, 0.0f, 640.0f, 480.0f);

	if (System.m_execParam != 0) {
		Printf__7CSystemFPce(&System, s_drawBonusFmt, (int)*(short*)(statePtr + 0x1c));
	}

	switch (*(short*)(statePtr + 0x1c)) {
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

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	const int activePartyCount = GetActiveBonusPartyCount();
	const int frameBase = 1;
	const int iconBase = frameBase + activePartyCount;
	const int modelBase = iconBase + activePartyCount;
	const int nameBase = modelBase + activePartyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		GetBonusMenuMembers(this).m_bonusAlpha = 0;
		GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
		memset((void*)animPtr, 0, 0x1008);

		header->count = (short)(1 + activePartyCount * 4);
		header->unk02 = 0;
		header->unk04 = 0;
		header->finished = 0;

		*(short*)(statePtr + 0x22) = 0;
		InitAnimSprite(&sprites[0], 0x16, 0, 0, 0x280, 0x1c0, 0, 8);
		sprites[0].depth = 0.0f;
		sprites[0].scale = 0.0f;
		sprites[0].alpha = 0.0f;

		for (int i = 0; i < activePartyCount; i++) {
			int idx = frameBase + i;
			InitAnimSprite(&sprites[idx], 0x17, 0x80, (short)(0x38 + i * 0x60), 0x1a0, 0x40, 0x16 + i * 3, 8);
			sprites[idx].depth = 0.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = -24.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = iconBase + i;
			InitAnimSprite(&sprites[idx], 0x18, 0x48, (short)(0x28 + i * 0x60), 0x60, 0x58, 0x40 + i * 3, 8);
			sprites[idx].depth = 0.0f;
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
			int idx = nameBase + i;
			InitAnimSprite(&sprites[idx], -1, 0x108, (short)(0x6C + i * 0x60), 0, 0, 0x2E + i * 4, 0x18);
			sprites[idx].depth = 0.0f;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = 18.0f;
		}

		*(unsigned char*)(statePtr + 0xb) = 1;
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
			if (sprite->duration > 0) {
				sprite->alpha = (float)sprite->timer / (float)sprite->duration;
			}
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
		} else if (i >= modelBase && i < nameBase) {
			sprite->scale = 0.85f + sprite->alpha * 0.15f;
		} else if (i >= nameBase) {
			sprite->mulX = (1.0f - sprite->alpha) * 18.0f;
		}

		if (sprite->kind == 0x17 && sprite->timer == 1) {
			Sound.PlaySe(0x49, 0x40, 0x7f, 0);
		}
		if (sprite->kind == -2 && sprite->timer == 1) {
			Sound.PlaySe(0x47, 0x40, 0x7f, 0);
		}
		if (sprite->kind == -1 && sprite->timer == 1 && GetBonusMenuMembers(this).m_bonusCursorFlag == 0) {
			Sound.PlaySe(0x48, 0x40, 0x7f, 0);
			GetBonusMenuMembers(this).m_bonusCursorFlag = 1;
		}
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
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
	float strongest = 0.0f;
	float frameAlpha = 0.0f;
	int modelIndex = 0;
	int nameIndex = 0;

	if (animPtr == 0 || statePtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	CFont* font = GetBonusMenuMembers(this).m_font;

	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = sprite->alpha;

		if (alpha < 0.0f) {
			alpha = 0.0f;
		} else if (alpha > 1.0f) {
			alpha = 1.0f;
		}

		if (sprite->kind == -2) {
			int basePtr = GetBonusMenuMembers(this).m_bonusListPtr;
			if (basePtr != 0) {
				int slotPtr = basePtr + (modelIndex * 0x524);
				void* handle = *(void**)slotPtr;
				if (handle != 0) {
					SetProjection__8CMenuPcsFi(this, modelIndex);
					SetLight__8CMenuPcsFi(this, 1);
					unsigned int oldFlags = *(unsigned int*)((char*)handle + 8);
					*(unsigned int*)((char*)handle + 8) = 0x300543;
					if (*(int*)((char*)handle + 0x168) != 0) {
						*(float*)(*(int*)((char*)handle + 0x168) + 0x9C) = alpha;
					}
					Draw__Q29CCharaPcs7CHandleFi(handle, 5);
					DrawMenuIdx__8CPartPcsFi(&PartPcs, *(int*)(slotPtr + 4));
					*(unsigned int*)((char*)handle + 8) = oldFlags;
					RestoreProjection__8CMenuPcsFv(this);
				}
			}
			modelIndex++;
		} else if (sprite->kind == -1) {
			if (font != 0) {
				const char* partyName = GetBonusPartyNameByActiveIndex(nameIndex++);
				if (partyName != 0 && *partyName != '\0') {
					_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
					font->SetMargin(1.0f);
					font->SetShadow(1);
					font->SetScale(0.9f);
					font->SetTlut(7);
					font->SetColor(color);
					font->DrawInit();
					font->SetPosX((float)sprite->x + sprite->mulX);
					font->SetPosY((float)sprite->y + sprite->mulY);
					font->Draw(partyName);
				}
			}
		} else if (sprite->kind == 0x17) {
			DrawBonusSweepSprite(this, sprite, alpha, true);
		} else {
			GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
			GXSetChanMatColor(GX_COLOR0A0, color);
			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, sprite->tex);
			DrawRect__8CMenuPcsFUlfffffffff(this, 0,
			    (float)sprite->x + sprite->mulX, (float)sprite->y + sprite->mulY,
			    (float)sprite->w, (float)sprite->h,
			    sprite->depth, sprite->depth, sprite->scale, sprite->scale, 0.0f);
		}

		if (alpha > strongest) {
			strongest = alpha;
		}
		if (sprite->kind == 0x16 && alpha > frameAlpha) {
			frameAlpha = alpha;
		}
	}

	if (*(unsigned char*)(statePtr + 8) != 0 && frameAlpha > 0.0f) {
		DrawBonusChkMark(frameAlpha);
	}

	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
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
	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	const int activePartyCount = GetActiveBonusPartyCount();
	const int baseCount = 1 + activePartyCount * 4;
	const int detailBase = baseCount;
	const int digitBase = detailBase + activePartyCount;
	const int labelBase = digitBase + activePartyCount;
	const int totalCount = labelBase + activePartyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		BonusAnimSprite originals[0x20];
		int originalCount = header->count;

		memset(originals, 0, sizeof(originals));
		if (originalCount <= 0 || originalCount > (int)(sizeof(originals) / sizeof(originals[0]))) {
			originalCount = baseCount;
		}
		for (int i = 0; i < originalCount; i++) {
			originals[i] = sprites[i];
		}
		if (originalCount < baseCount || originals[0].w == 0) {
			memset(originals, 0, sizeof(originals));
			originalCount = baseCount;
			InitAnimSprite(&originals[0], 0x16, 0, 0, 0x280, 0x1c0, 0, 0);
			originals[0].depth = 0.0f;
			originals[0].scale = 3.0f;
			originals[0].alpha = 1.0f;
			for (int i = 0; i < activePartyCount; i++) {
				int frameIdx = 1 + i;
				int iconIdx = 1 + activePartyCount + i;
				int modelIdx = 1 + activePartyCount * 2 + i;
				int nameIdx = 1 + activePartyCount * 3 + i;

				InitAnimSprite(&originals[frameIdx], 0x17, 0x80, (short)(0x38 + i * 0x60), 0x1a0, 0x40, 0, 0);
				originals[frameIdx].alpha = 1.0f;
				InitAnimSprite(&originals[iconIdx], 0x18, 0x48, (short)(0x28 + i * 0x60), 0x60, 0x58, 0, 0);
				originals[iconIdx].alpha = 1.0f;
				InitAnimSprite(&originals[modelIdx], -2, 0, 0, 0, 0, 0, 0);
				originals[modelIdx].alpha = 1.0f;
				InitAnimSprite(&originals[nameIdx], -1, 0x108, (short)(0x6C + i * 0x60), 0, 0, 0, 0);
				originals[nameIdx].alpha = 1.0f;
			}
		}

		*(short*)(statePtr + 0x22) = 0;
		header->finished = 0;
		*(short*)(statePtr + 0x10) = 0;
		memset((void*)sprites, 0, sizeof(BonusAnimSprite) * totalCount);
		header->count = (short)totalCount;
		header->unk02 = 0;
		header->unk04 = 0;

		for (int i = 0; i < baseCount; i++) {
			sprites[i] = originals[i];
			sprites[i].timer = 0;
			sprites[i].startFrame = 0;
			sprites[i].duration = 0;
			sprites[i].alpha = 1.0f;
			sprites[i].mulX = 0.0f;
			sprites[i].mulY = 0.0f;
			sprites[i].scale = (sprites[i].scale <= 0.0f) ? 1.0f : sprites[i].scale;
		}
		for (int i = 0; i < activePartyCount; i++) {
			short stripX = ((0 < i) && (i < 3)) ? 8 : 0x20;
			short y = (short)(0x28 + i * 0x60);
			InitAnimSprite(&sprites[detailBase + i], 0x19, stripX, y, 0x38, 0x28, 8 + i * 2, 8);
			ResetAnimSpriteMotion(&sprites[detailBase + i]);
			sprites[detailBase + i].mulX = 18.0f;
			sprites[detailBase + i].scale = 0.85f;

			InitAnimSprite(&sprites[digitBase + i], -5, (short)(0x1b8 + i * 8), (short)(0x4c + i * 0x60), 0x18, 0x18, 10 + i * 2, 8);
			ResetAnimSpriteMotion(&sprites[digitBase + i]);
			sprites[digitBase + i].scale = 0.85f;

			InitAnimSprite(&sprites[labelBase + i], -6, 0x108, (short)(0x90 + i * 0x60), 0, 0, 12 + i * 2, 8);
			ResetAnimSpriteMotion(&sprites[labelBase + i]);
			sprites[labelBase + i].mulX = 18.0f;
		}
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int maxValue = 0;
	int doneCount = 0;

	for (int i = 0; i < activePartyCount; i++) {
		int value = GetBonusResultValueByActiveIndex(i);
		if (value > maxValue) {
			maxValue = value;
		}
	}

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		if (i < baseCount) {
			sprite->alpha = 1.0f;
			continue;
		}
		if (frame < sprite->startFrame) {
			continue;
		}
		if (frame < sprite->startFrame + sprite->duration) {
			sprite->timer++;
			sprite->alpha = (sprite->duration > 0) ? ((float)sprite->timer / (float)sprite->duration) : 1.0f;
		} else {
			sprite->alpha = 1.0f;
			doneCount++;
		}

		if (i >= detailBase && i < digitBase) {
			sprite->mulX = (1.0f - sprite->alpha) * 18.0f;
			sprite->scale = 0.85f + sprite->alpha * 0.15f;
		} else if (i >= digitBase && i < labelBase) {
			int displayValue = GetBonusDisplayValueForFrame(statePtr, i - digitBase);
			if ((int)sprite->depth != displayValue) {
				if (*(short*)(statePtr + 0x10) == 0 && displayValue == GetBonusResultValueByActiveIndex(i - digitBase) && displayValue > 0) {
					Sound.PlaySe(0x4b, 0x40, 0x7f, 0);
				}
				sprite->depth = (float)displayValue;
			}
			sprite->scale = 0.85f + sprite->alpha * 0.15f;
			sprite->mulY = (*(short*)(statePtr + 0x10) == 0 && displayValue < GetBonusResultValueByActiveIndex(i - digitBase)) ? -2.0f : 0.0f;
		} else {
			sprite->mulX = (1.0f - sprite->alpha) * 18.0f;
			sprite->mulY = (1.0f - sprite->alpha) * 4.0f;
		}
	}

	for (int i = 0; i < activePartyCount; i++) {
		float modelAlpha = 1.0f;
		if (*(short*)(statePtr + 0x10) == 0) {
			int target = GetBonusResultValueByActiveIndex(i);
			int shown = GetBonusDisplayValueForFrame(statePtr, i);
			modelAlpha = (target > 0 && shown < target) ? 0.9f : 1.0f;
		}
		SetBonusPartyModelAlpha(this, i, modelAlpha);
	}

	if (*(short*)(statePtr + 0x10) == 0 && frame >= maxValue + 10) {
		Sound.PlaySe(0x4a, 0x40, 0x7f, 0);
		*(short*)(statePtr + 0x10) = 1;
	}

	if (*(short*)(statePtr + 0x10) != 0) {
		unsigned short buttons = GetBonusAdvanceButtons(this);
		if ((buttons & 0x300) != 0) {
			Sound.PlaySe(2, 0x40, 0x7f, 0);
			*(short*)(animPtr + 6) = 1;
		}
	}

	if (doneCount >= activePartyCount * 3) {
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
	int partyNameIndex = 0;
	int valueIndex = 0;
	int labelIndex = 0;

	if (animPtr == 0 || statePtr == 0) {
		return;
	}
	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float strongest = 0.0f;
	CFont* font = GetBonusMenuMembers(this).m_font;
	CFont* fontWide = GetBonusMenuMembers(this).m_fontWide;

	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = sprite->alpha;

		if (alpha < 0.0f) {
			alpha = 0.0f;
		} else if (alpha > 1.0f) {
			alpha = 1.0f;
		}

		if (sprite->kind == -3) {
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
		} else if (sprite->kind == -4) {
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
		} else if (sprite->kind == -2) {
			DrawBonusPartyModel(this, modelIndex++, alpha);
		} else if (sprite->kind == -5) {
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, GetBonusDisplayValueForFrame(statePtr, valueIndex++));
		} else if (sprite->kind == -1) {
			if (font != 0) {
				const char* partyName = GetBonusPartyNameByActiveIndex(partyNameIndex++);
				if (partyName != 0 && *partyName != '\0') {
					_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
					font->SetMargin(1.0f);
					font->SetShadow(1);
					font->SetScale(0.9f);
					font->SetTlut(7);
					font->SetColor(color);
					font->DrawInit();
					font->SetPosX((float)sprite->x + sprite->mulX);
					font->SetPosY((float)sprite->y + sprite->mulY);
					font->Draw(const_cast<char*>(partyName));
				}
			}
		} else if (sprite->kind == -6) {
			CFont* labelFont = (fontWide != 0) ? fontWide : font;
			if (labelFont != 0) {
				const char* label = GetBonusResultLabelByActiveIndex(labelIndex++);
				if (label != 0 && *label != '\0') {
					_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
					labelFont->SetMargin(1.0f);
					labelFont->SetShadow(0);
					if (labelFont == fontWide) {
						labelFont->SetScaleX(0.7f);
						labelFont->SetScaleY(1.0f);
					} else {
						labelFont->SetScale(0.75f);
					}
					labelFont->SetTlut(7);
					labelFont->SetColor(color);
					labelFont->DrawInit();
					labelFont->SetPosX((float)sprite->x + sprite->mulX);
					labelFont->SetPosY((float)sprite->y + sprite->mulY);
					labelFont->Draw(const_cast<char*>(label));
				}
			}
		} else {
			DrawBonusTexturedSprite(this, sprite, alpha);
		}

		if (strongest < alpha) {
			strongest = alpha;
		}
	}

	if (*(unsigned char*)(statePtr + 8) != 0) {
		DrawBonusChkMark(strongest);
	}
	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
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
	const int activePartyCount = GetActiveBonusPartyCount();
	const int baseCount = 1 + activePartyCount * 3;
	const int frameBase = 1;
	const int iconBase = frameBase + activePartyCount;
	const int digitBase = iconBase + activePartyCount;
	const int frameEchoBase = digitBase + activePartyCount;
	const int iconEchoBase = frameEchoBase + activePartyCount;
	const int digitEchoBase = iconEchoBase + activePartyCount;
	const int closeCount = digitEchoBase + activePartyCount;

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		BonusAnimSprite originals[0x20];
		int originalCount = header->count;

		memset(originals, 0, sizeof(originals));
		if (originalCount <= 0 || originalCount > (int)(sizeof(originals) / sizeof(originals[0]))) {
			originalCount = baseCount;
		}
		for (int i = 0; i < originalCount; i++) {
			originals[i] = sprites[i];
		}
		if (originalCount == baseCount && originals[0].w == 0) {
			BuildDefaultResultSprites(originals, activePartyCount);
		}

		*(short*)(statePtr + 0x22) = 0;
		header->finished = 0;
		memset((void*)sprites, 0, sizeof(BonusAnimSprite) * closeCount);
		header->count = (short)closeCount;
		header->unk02 = 0;
		header->unk04 = 0;

		sprites[0] = originals[0];
		sprites[0].timer = 0;
		sprites[0].startFrame = 0;
		sprites[0].duration = 14;
		sprites[0].alpha = 1.0f;
		sprites[0].scale = (sprites[0].scale > 0.0f) ? sprites[0].scale : 3.0f;

		for (int i = 0; i < activePartyCount; i++) {
			int srcFrameIdx = (frameBase + i < originalCount) ? frameBase + i : 0;
			int srcIconIdx = (iconBase + i < originalCount) ? iconBase + i : 0;
			int srcDigitIdx = (digitBase + i < originalCount) ? digitBase + i : 0;

			sprites[frameBase + i] = originals[srcFrameIdx];
			sprites[frameBase + i].timer = 0;
			sprites[frameBase + i].startFrame = i * 2;
			sprites[frameBase + i].duration = 12;
			sprites[frameBase + i].alpha = 1.0f;
			sprites[frameBase + i].kind = 0x17;
			sprites[frameBase + i].tex = 0x17;

			sprites[iconBase + i] = originals[srcIconIdx];
			sprites[iconBase + i].timer = 0;
			sprites[iconBase + i].startFrame = 2 + i * 2;
			sprites[iconBase + i].duration = 10;
			sprites[iconBase + i].alpha = 1.0f;
			sprites[iconBase + i].kind = 0x18;
			sprites[iconBase + i].tex = 0x18;

			sprites[digitBase + i] = originals[srcDigitIdx];
			sprites[digitBase + i].timer = 0;
			sprites[digitBase + i].startFrame = 4 + i * 2;
			sprites[digitBase + i].duration = 12;
			sprites[digitBase + i].alpha = 1.0f;
			sprites[digitBase + i].kind = -2;
			sprites[digitBase + i].tex = -2;
			if (sprites[digitBase + i].w == 0) {
				sprites[digitBase + i].w = 0x18;
			}
			if (sprites[digitBase + i].h == 0) {
				sprites[digitBase + i].h = 0x18;
			}

			sprites[frameEchoBase + i] = sprites[frameBase + i];
			sprites[frameEchoBase + i].timer = 0;
			sprites[frameEchoBase + i].startFrame = 6 + i * 2;
			sprites[frameEchoBase + i].duration = 8;
			sprites[frameEchoBase + i].alpha = 0.9f;

			sprites[iconEchoBase + i] = sprites[iconBase + i];
			sprites[iconEchoBase + i].timer = 0;
			sprites[iconEchoBase + i].startFrame = 7 + i * 2;
			sprites[iconEchoBase + i].duration = 8;
			sprites[iconEchoBase + i].alpha = 0.8f;

			sprites[digitEchoBase + i] = sprites[digitBase + i];
			sprites[digitEchoBase + i].timer = 0;
			sprites[digitEchoBase + i].startFrame = 8 + i * 2;
			sprites[digitEchoBase + i].duration = 10;
			sprites[digitEchoBase + i].alpha = 0.75f;
		}

		Sound.PlaySe(0x4a, 0x40, 0x7f, 0);
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	int doneCount = 0;

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float progress = CalcBonusSpriteProgress(sprite, frame);
		float fade;

		if (progress < 0.0f) {
			continue;
		}

		sprite->timer = frame - sprite->startFrame + 1;
		fade = 1.0f - progress;
		if (i >= frameEchoBase) {
			fade *= 0.8f;
		}
		sprite->alpha = ClampBonusUnit(fade);

		if (i == 0) {
			sprite->mulX = 0.0f;
			sprite->mulY = 0.0f;
			sprite->scale = 3.0f - progress * 1.5f;
		} else if (i >= frameBase && i < iconBase) {
			float dir = (i & 1) ? 1.0f : -1.0f;
			sprite->mulX = (-36.0f - i * 2.0f) * progress;
			sprite->mulY = dir * 6.0f * progress;
			sprite->scale = 1.0f - progress * 0.08f;
		} else if (i >= iconBase && i < digitBase) {
			float dir = (i & 1) ? -1.0f : 1.0f;
			sprite->mulX = (42.0f + i * 3.0f) * dir * progress;
			sprite->mulY = -24.0f * progress;
			sprite->scale = 1.0f - progress * 0.12f;
		} else if (i >= digitBase && i < frameEchoBase) {
			sprite->mulX = 10.0f * progress;
			sprite->mulY = -38.0f * progress;
			sprite->scale = 1.0f - progress * 0.2f;
		} else if (i >= frameEchoBase && i < iconEchoBase) {
			sprite->mulX = -64.0f * progress;
			sprite->mulY = 18.0f * progress;
			sprite->scale = 0.96f - progress * 0.18f;
		} else if (i >= iconEchoBase && i < digitEchoBase) {
			sprite->mulX = 64.0f * progress;
			sprite->mulY = 10.0f * progress;
			sprite->scale = 0.92f - progress * 0.15f;
		} else {
			sprite->mulX = 18.0f * progress;
			sprite->mulY = -52.0f * progress;
			sprite->scale = 0.9f - progress * 0.2f;
		}

		if (sprite->scale < 0.0f) {
			sprite->scale = 0.0f;
		}
		if (progress >= 1.0f) {
			doneCount++;
		}
		if (sprite->timer == 1 && (i == frameBase || i == frameEchoBase)) {
			Sound.PlaySe(0x49, 0x40, 0x7f, 0);
		}
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
	}
	if (header->finished != 0) {
		*(short*)(animPtr + 6) = 1;
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
	int digitIndex = 0;

	if (animPtr == 0 || statePtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float strongest = 0.0f;

	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = sprite->alpha;
		if (alpha < 0.0f) {
			alpha = 0.0f;
		} else if (alpha > 1.0f) {
			alpha = 1.0f;
		}

		if (sprite->kind == -3) {
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
		} else if (sprite->kind == -4) {
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
		} else if (sprite->kind == -2) {
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, GetBonusResultValueByActiveIndex(digitIndex++));
		} else if (sprite->kind == 0x17) {
			DrawBonusSweepSprite(this, sprite, alpha, false);
		} else {
			GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
			GXSetChanMatColor(GX_COLOR0A0, color);
			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, sprite->tex);
			DrawRect__8CMenuPcsFUlfffffffff(this, 0,
			    (float)sprite->x + sprite->mulX, (float)sprite->y + sprite->mulY,
			    (float)sprite->w, (float)sprite->h,
			    sprite->depth, sprite->depth, sprite->scale, sprite->scale, 0.0f);
		}

		if (strongest < alpha) {
			strongest = alpha;
		}
	}

	if (*(unsigned char*)(statePtr + 8) != 0 && strongest > 0.0f) {
		DrawBonusChkMark(strongest);
	}
	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
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

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int activePartyCount = GetActiveBonusPartyCount();
		int idx;
		int iconBase;
		int detailBase;

		GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, 0x1008);
		*(short*)(statePtr + 0x22) = 0;

		header->count = (short)(12 + activePartyCount * 5);
		header->unk02 = 0;
		header->unk04 = 0;
		header->finished = 0;

		idx = 0;
		InitAnimSprite(&sprites[idx++], 0x16, 0, 0, 0x280, 0x1c0, 0, 0);
		sprites[0].scale = 3.0f;
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

		iconBase = idx;
		short y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			InitSelectOpenPartyIcon(&sprites[idx], i, y);
			idx++;
			y += 0x60;
		}

		for (int i = 0; i < activePartyCount; i++) {
			InitSelectOpenPartyName(&sprites[idx], &sprites[iconBase + i], 0x50, 0x18, sprites[iconBase + i].startFrame + 2);
			idx++;
		}

		for (int i = 0; i < 8; i++) {
			int start = (int)((float)(10 + i * 5) * 0.6f);
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, start, 0x21);
			sprites[idx].alpha = 0.0f;
			sprites[idx].scale = 0.75f;
			idx++;
		}

		detailBase = idx;
		for (int i = 0; i < activePartyCount; i++) {
			sprites[idx] = sprites[iconBase + i];
			sprites[idx].y = (short)(sprites[idx].y + 0x20);
			sprites[idx].w = 0xA8;
			sprites[idx].h = 0x38;
			sprites[idx].startFrame = sprites[iconBase + i].startFrame + 6;
			sprites[idx].duration = 8;
			sprites[idx].alpha = 0.0f;
			sprites[idx].mulX = 0.0f;
			sprites[idx].mulY = 56.0f;
			sprites[idx].scale = 1.0f;
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

		*(unsigned char*)(statePtr + 0xb) = 1;
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
		} else {
			doneCount++;
		}

		ApplySelectOpenSpriteMotion(sprite, frame);
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
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

	if (animPtr == 0 || statePtr == 0 || *(unsigned char*)(statePtr + 0xb) == 0) {
		return;
	}

	unsigned int* scriptFoodBase = Game.m_scriptFoodBase;
	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float strongest = 0.0f;
	float artiAlpha = 0.0f;
	int modelIndex = 0;
	int activePartyCount = 0;

	for (int i = 0; i < 4; i++) {
		if (scriptFoodBase[i] != 0) {
			activePartyCount++;
		}
	}
	if (activePartyCount <= 0) {
		activePartyCount = 1;
	}

	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = sprite->alpha;
		if (alpha < 0.0f) {
			alpha = 0.0f;
		} else if (alpha > 1.0f) {
			alpha = 1.0f;
		}
		switch (sprite->kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			if (artiAlpha < alpha) {
				artiAlpha = alpha;
			}
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			if (modelIndex < activePartyCount) {
				DrawBonusPartyModel(this, modelIndex, alpha);
			}
			modelIndex++;
			break;
		default:
			{
				GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, sprite->tex);
				if (sprite->tex == 0x20) {
					GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
				}
				DrawRect__8CMenuPcsFUlfffffffff(this, 0,
				    (float)sprite->x + sprite->mulX, (float)sprite->y + sprite->mulY,
				    (float)sprite->w, (float)sprite->h,
				    sprite->depth, sprite->depth, sprite->scale, sprite->scale, 0.0f);
				if (sprite->tex == 0x20) {
					GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
				}
			}
			break;
		}

		if (strongest < alpha) {
			strongest = alpha;
		}
	}

	DrawBonusActiveMarks(this, statePtr, artiAlpha);
	DrawBonusPartyNames(this, header, sprites);
	DrawBonusMcWinOverlay(this, statePtr);

	if (*(unsigned char*)(statePtr + 8) != 0) {
		DrawBonusChkMark(strongest);
	}
	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
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

	if (statePtr == 0 || animPtr == 0 || auxPtr == 0) {
		return;
	}

	header = (BonusAnimHeader*)animPtr;
	sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;
		*(short*)(statePtr + 0xe) = 0;
		*(short*)(statePtr + 0x18) = 0;
		*(short*)(statePtr + 0x1a) = 0;
		*(short*)(statePtr + 0x26) = 4;
		*(short*)(statePtr + 0x28) = 1;
		*(short*)(auxPtr + 10) = 3;
		header->finished = 0;
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].alpha = 1.0f;
			sprites[i].depth = 3.0f;
			sprites[i].scale = (sprites[i].scale <= 0.0f) ? 1.0f : sprites[i].scale;
		}
		if (GetSelectCursorSprite(header, sprites) == 0 && header->count < 0x3F) {
			InitAnimSprite(&sprites[header->count], 0x20, 0, 0, 0x40, 0x30, 0, 8);
			ResetAnimSpriteMotion(&sprites[header->count]);
			sprites[header->count].alpha = 1.0f;
			sprites[header->count].depth = 1.0f;
			header->count = (short)(header->count + 1);
		}
		UpdateSelectCursorSprite(statePtr, header, sprites, 0);
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	int frame = (int)*(short*)(statePtr + 0x22);
	unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);
	short& promptMode = *(short*)(auxPtr + 10);
	short& selection = *(short*)(statePtr + 0x26);
	short& confirmSel = *(short*)(statePtr + 0x28);
	short& delay = *(short*)(statePtr + 0x1a);

	switch (promptMode) {
	case 3:
		if (delay > 0) {
			delay = (short)(delay - 1);
			break;
		}

		if ((down & 9) != 0) {
			selection = (short)((selection + 1) & 7);
			Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
		} else if ((down & 6) != 0) {
			selection = (short)((selection + 7) & 7);
			Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
		}

		if ((down & 0x100) != 0) {
			unsigned char activeMask = *(unsigned char*)(statePtr + 9);
			unsigned char bit = (unsigned char)(1 << (selection & 7));
			if ((activeMask & bit) == 0) {
				*(unsigned char*)(statePtr + 9) = (unsigned char)(activeMask | bit);
				*(unsigned char*)(statePtr + 8) = 1;
				delay = 10;
				Sound.PlaySe(0x4f, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}
		} else if ((down & 0x200) != 0) {
			short winW = 0;
			short winH = 0;
			GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 1);
			SetMcWinInfo__8CMenuPcsFii(this, (int)winW, (int)winH);
			promptMode = 1;
			confirmSel = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
		}
		break;
	case 1:
		if ((down & 3) != 0) {
			confirmSel = (short)(confirmSel ^ 1);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((down & 0x100) != 0) {
			if (confirmSel == 0) {
				promptMode = 2;
				delay = 10;
				Sound.PlaySe(2, 0x40, 0x7f, 0);
			} else {
				promptMode = 3;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
			}
		} else if ((down & 0x200) != 0) {
			promptMode = 3;
			confirmSel = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
		}
		break;
	case 2:
		if (delay > 0) {
			delay = (short)(delay - 1);
			if (delay == 0) {
				header->finished = 1;
				*(short*)(animPtr + 6) = 1;
			}
		}
		break;
	default:
		promptMode = 3;
		break;
	}

	for (int i = 0; i < (int)header->count; i++) {
		float pulse = (float)((frame + i) & 0x1f) / 31.0f;
		if (sprites[i].kind != 0x20) {
			sprites[i].alpha = 0.75f + pulse * 0.25f;
		}
	}
	UpdateSelectCursorSprite(statePtr, header, sprites, frame);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::DrawSelectWait()
{
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	float strongest = 0.0f;
	float artiAlpha = 0.0f;
	int modelIndex = 0;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = ClampBonusUnit(sprite->alpha);

		switch (sprite->kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			if (artiAlpha < alpha) {
				artiAlpha = alpha;
			}
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			DrawBonusPartyModel(this, modelIndex, alpha);
			modelIndex++;
			break;
		default:
			DrawBonusTexturedSprite(this, sprite, alpha);
			break;
		}

		if (strongest < alpha) {
			strongest = alpha;
		}
	}

	DrawBonusActiveMarks(this, statePtr, artiAlpha);
	DrawBonusPartyNames(this, header, sprites);
	DrawBonusMcWinOverlay(this, statePtr);

	if (*(unsigned char*)(statePtr + 8) != 0) {
		DrawBonusChkMark(strongest);
	}
	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
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
	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;
		header->finished = 0;
		if (header->count > 0 && sprites[header->count - 1].kind == 0x20) {
			header->count = (short)(header->count - 1);
		}
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].x = (short)((float)sprites[i].x + sprites[i].mulX);
			sprites[i].y = (short)((float)sprites[i].y + sprites[i].mulY);
			sprites[i].mulX = 0.0f;
			sprites[i].mulY = 0.0f;
			sprites[i].alpha = 1.0f;
			sprites[i].timer = 0;
			sprites[i].duration = 8;
			if (sprites[i].kind == 0x16 || sprites[i].kind == -3 || sprites[i].kind == 0x1f || sprites[i].kind == -4) {
				sprites[i].startFrame = 0;
			} else if (sprites[i].kind == -2) {
				sprites[i].startFrame = 2 + (i & 3);
			} else {
				sprites[i].startFrame = 1 + (i & 3);
			}
		}
		*(unsigned char*)(statePtr + 0xb) = 1;
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
		} else {
			doneCount++;
		}

		ApplySelectCloseSpriteMotion(sprite, frame);
	}

	if (doneCount == (int)header->count) {
		header->finished = 1;
		*(short*)(animPtr + 6) = 1;
	}
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::DrawSelectCloseAnim()
{
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	float strongest = 0.0f;
	float artiAlpha = 0.0f;
	int modelIndex = 0;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	DrawInit__8CMenuPcsFv(this);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float alpha = ClampBonusUnit(sprite->alpha);

		switch (sprite->kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			if (artiAlpha < alpha) {
				artiAlpha = alpha;
			}
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			DrawBonusPartyModel(this, modelIndex, alpha);
			modelIndex++;
			break;
		default:
			DrawBonusTexturedSprite(this, sprite, alpha);
			break;
		}

		if (strongest < alpha) {
			strongest = alpha;
		}
	}

	DrawBonusActiveMarks(this, statePtr, artiAlpha);
	DrawBonusPartyNames(this, header, sprites);

	if (*(unsigned char*)(statePtr + 8) != 0 && strongest > 0.0f) {
		DrawBonusChkMark(strongest);
	}
	GetBonusMenuMembers(this).m_bonusAlpha = (unsigned char)(strongest * 255.0f);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::DrawBonusCnt(CMenuPcs::Sprt2* sprt, int value)
{
	BonusAnimSprite* sprite = (BonusAnimSprite*)sprt;
	int digitValue;
	int digits[3];
	int digitCount;
	float alpha;
	float baseX;
	float baseY;
	float digitW;
	float digitH;
	float scale;

	if (sprite == 0) {
		return;
	}

	digitValue = value;
	if (digitValue < 0) {
		digitValue = -digitValue;
	}
	digitValue = digitValue % 1000;

	alpha = ClampBonusUnit(sprite->alpha);
	baseX = (float)sprite->x + sprite->mulX;
	baseY = (float)sprite->y + sprite->mulY;
	digitW = (sprite->w > 0) ? (float)sprite->w : 24.0f;
	digitH = (sprite->h > 0) ? (float)sprite->h : 24.0f;
	scale = (sprite->scale > 0.0f) ? sprite->scale : 1.0f;

	if (digitValue >= 100) {
		digitCount = 3;
		digits[0] = digitValue / 100;
		digits[1] = (digitValue / 10) % 10;
		digits[2] = digitValue % 10;
	} else if (digitValue >= 10) {
		digitCount = 2;
		digits[0] = digitValue / 10;
		digits[1] = digitValue % 10;
	} else {
		digitCount = 1;
		digits[0] = digitValue;
	}

	baseX += ((3.0f * digitW) - ((float)digitCount * digitW)) * 0.5f;

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x19);
	_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(alpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);

	for (int i = 0; i < digitCount; i++) {
		DrawRect__8CMenuPcsFUlfffffffff(this, 0, baseX + digitW * (float)i, baseY, digitW, digitH,
		    digitW * (float)digits[i], 0.0f, scale, scale, 0.0f);
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

	_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(255.0f * alpha)};
	const float corner = 8.0f;
	const float right = (x + w) - corner;
	const float bottom = (y + h) - corner;
	const float innerW = w - (corner * 2.0f);
	const float innerH = h - (corner * 2.0f);

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
	GXSetChanMatColor(GX_COLOR0A0, color);

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x1B);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, corner, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, right, y, corner, corner, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, bottom, corner, corner, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, right, bottom, corner, corner, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x1C);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x + corner, y, innerW, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x22);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x + corner, bottom, innerW, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x1D);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y + corner, corner, innerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, right, y + corner, corner, innerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x1E);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, x + corner, y + corner, innerW, innerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
	if (sprt == 0 || alpha <= 0.0f) {
		return;
	}

	BonusAnimSprite* sprite = reinterpret_cast<BonusAnimSprite*>(sprt);
	float* pos = GetBonusArtiBasePositions(sprite);
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int selectedSlot = -1;
	unsigned char activeMask = 0;
	float width = (sprite->w > 0) ? (float)sprite->w : 0x70;
	float height = (sprite->h > 0) ? (float)sprite->h : 0x68;

	if (statePtr != 0) {
		selectedSlot = (*(short*)(statePtr + 0x26)) & 7;
		activeMask = *(unsigned char*)(statePtr + 9);
	}

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x1A);

	for (int i = 0; i < 8; i++) {
		float slotAlpha = ClampBonusUnit(alpha);

		if ((activeMask & (1 << i)) != 0) {
			slotAlpha = ClampBonusUnit(slotAlpha * 0.85f + 0.15f);
		} else {
			slotAlpha *= 0.65f;
		}
		if (i == selectedSlot) {
			slotAlpha = ClampBonusUnit(alpha * 1.2f);
		}

		_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(slotAlpha * 255.0f)};
		GXSetChanMatColor(GX_COLOR0A0, color);
		DrawRect__8CMenuPcsFUlfffffffff(this, 0, pos[i * 2 + 0], pos[i * 2 + 1], width, height,
		    0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::DrawBonusChkMark(float alpha)
{
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	float* currentPos = gBonusCheckMarkPosBuffer[0];
	float* previousPos = gBonusCheckMarkPosBuffer[1];
	float a = alpha;
	float strongest = a;
	float pulse = 0.0f;
	float slotAlpha;
	float slotScale;
	unsigned char activeMask;
	int slot;

	if (a < 0.0f) {
		a = 0.0f;
	}
	if (a > 1.0f) {
		a = 1.0f;
	}

	if (animPtr != 0) {
		BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
		BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
		for (int i = 0; i < (int)header->count; i++) {
			if (sprites[i].kind == -2 && sprites[i].alpha > strongest) {
				strongest = sprites[i].alpha;
			}
		}
	}

	if (statePtr == 0) {
		GetBonusMenuMembers(this).m_bonusCursorFlag = (unsigned char)(strongest > 0.5f ? 1 : 0);
		return;
	}

	activeMask = *(unsigned char*)(statePtr + 9);
	slot = (*(short*)(statePtr + 0x26)) & 7;
	if ((activeMask & (1 << slot)) == 0) {
		slot = FindFirstBonusActiveSlot(activeMask);
	}

	if (slot < 0 || currentPos == 0) {
		GetBonusMenuMembers(this).m_bonusCursorFlag = (unsigned char)(strongest > 0.5f ? 1 : 0);
		return;
	}

	if (statePtr != 0) {
		pulse = (float)((*(short*)(statePtr + 0x22)) & 0x1f) / 31.0f;
		strongest = strongest * (0.85f + pulse * 0.15f);
	}

	if (strongest > 1.0f) {
		strongest = 1.0f;
	}

	slotAlpha = ClampBonusUnit(strongest * (0.7f + pulse * 0.3f));
	slotScale = 0.95f + pulse * 0.15f;

	float currentX = currentPos[slot * 2 + 0] + 2.0f;
	float currentY = currentPos[slot * 2 + 1] + 2.0f;
	float drawX = currentX;
	float drawY = currentY;

	if (previousPos != 0) {
		float prevX = previousPos[slot * 2 + 0] + 2.0f;
		float prevY = previousPos[slot * 2 + 1] + 2.0f;
		drawX = prevX + (currentX - prevX) * a;
		drawY = prevY + (currentY - prevY) * a;
	}

	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x23);
	_GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(slotAlpha * 255.0f)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	DrawRect__8CMenuPcsFUlfffffffff(this, 0, drawX, drawY, 24.0f, 24.0f, 0.0f, 0.0f, slotScale, slotScale, 0.0f);

	GetBonusMenuMembers(this).m_bonusCursorFlag = (unsigned char)(strongest > 0.5f ? 1 : 0);
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
	BonusAnimSprite* currentSprite = reinterpret_cast<BonusAnimSprite*>(a);
	BonusAnimSprite* layoutSprite = reinterpret_cast<BonusAnimSprite*>(b);

	gBonusCheckMarkPosBuffer[0] = s_bonusArtiBasePosStorage0;
	gBonusCheckMarkPosBuffer[1] = s_bonusArtiBasePosStorage1;
	memset(gBonusCheckMarkPosBuffer[0], 0, sizeof(s_bonusArtiBasePosStorage0));
	memset(gBonusCheckMarkPosBuffer[1], 0, sizeof(s_bonusArtiBasePosStorage1));

	if (a != 0) {
		FillBonusArtiBasePositions(gBonusCheckMarkPosBuffer[0], currentSprite, (layoutSprite != 0) ? layoutSprite : currentSprite);
	}
	if (b != 0) {
		FillBonusArtiBasePositions(gBonusCheckMarkPosBuffer[1], layoutSprite, layoutSprite);
	} else if (a != 0) {
		memcpy(gBonusCheckMarkPosBuffer[1], gBonusCheckMarkPosBuffer[0], sizeof(s_bonusArtiBasePosStorage1));
	}
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::GetAllPadOn()
{
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	unsigned char activeMask = 0;
	int activePartyCount = 0;
	int anyReady = 0;
	int allReady = 1;

	if (statePtr == 0) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] != 0) {
			activeMask = (unsigned char)(activeMask | (1 << i));
			activePartyCount++;
			anyReady = 1;
		} else {
			allReady = 0;
		}
	}

	*(unsigned char*)(statePtr + 8) = (unsigned char)((anyReady != 0) ? 1 : 0);
	*(unsigned char*)(statePtr + 9) = activeMask;
	*(unsigned char*)(statePtr + 0xa) = (unsigned char)((allReady != 0 && activePartyCount >= 4) ? 1 : 0);
}

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
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
		if (caravanWork != 0) {
			caravanWork->SafeDeleteTempItem();
			caravanWork->SortBeforeReturnWorldMap();
		}
	}
}
