#include "ffcc/bonus_menu.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/p_game.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include <string.h>

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawMcWin__8CMenuPcsFss(CMenuPcs*, short, short);
extern "C" void DrawMcWinMess__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetYesNoXPos__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void SetProjection__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetLight__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void RestoreProjection__8CMenuPcsFv(CMenuPcs*);
extern "C" void Draw__Q29CCharaPcs7CHandleFi(void*, int);
extern "C" void DrawMenuIdx__8CPartPcsFi(CPartPcs*, int);
extern "C" {
extern int gBonusMenuWork0;
extern float* gBonusCheckMarkPosBuffer;
extern CPartPcs PartPcs;
}

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

struct BonusMenuMembers {
	unsigned char pad_0000[0x8C];
	unsigned char m_bonusAlpha;
	unsigned char m_bonusCursorFlag;
	unsigned char pad_008E[0x6A];
	CFont* m_font;
	unsigned char pad_00FC[0x718];
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
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusBoardPtr) == 0x814);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusStatePtr) == 0x82C);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusListPtr) == 0x840);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusAuxPtr) == 0x848);
STATIC_ASSERT(offsetof(BonusMenuMembers, m_bonusAnimPtr) == 0x84C);

static inline BonusMenuMembers& GetBonusMenuMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<BonusMenuMembers*>(menu);
}

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
	gBonusCheckMarkPosBuffer = 0;
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
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;
	int auxPtr = GetBonusMenuMembers(this).m_bonusAuxPtr;
	int boardPtr = GetBonusMenuMembers(this).m_bonusBoardPtr;

	if (statePtr == 0) {
		statePtr = (int)(new unsigned char[0x48]);
		GetBonusMenuMembers(this).m_bonusStatePtr = statePtr;
	}
	if (animPtr == 0) {
		animPtr = (int)(new unsigned char[0x1008]);
		GetBonusMenuMembers(this).m_bonusAnimPtr = animPtr;
	}
	if (auxPtr == 0) {
		auxPtr = (int)(new unsigned char[0xc]);
		GetBonusMenuMembers(this).m_bonusAuxPtr = auxPtr;
	}
	if (boardPtr == 0) {
		boardPtr = (int)(new unsigned char[0x780]);
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
	if (auxPtr != 0) {
		memset((void*)auxPtr, 0, 0xc);
	}
	if (boardPtr != 0) {
		memset((void*)boardPtr, 0, 0x780);
	}

	GetBonusMenuMembers(this).m_bonusAlpha = 0;
	GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
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
		break;
	case 6:
		ClrBattleItem();
		*(short*)(statePtr + 0x1c) = 0;
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
	if (statePtr == 0) {
		return;
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
		DrawSelectWait();
		break;
	case 5:
		DrawSelectCloseAnim();
		break;
	default:
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
	unsigned int* scriptFoodBase = Game.game.m_scriptFoodBase;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int activePartyCount = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		GetBonusMenuMembers(this).m_bonusAlpha = 0;
		memset((void*)animPtr, 0, 0x1008);

		for (int i = 0; i < 4; i++) {
			if (scriptFoodBase[i] != 0) {
				activePartyCount++;
			}
		}
		if (activePartyCount <= 0) {
			activePartyCount = 1;
		}

		header->count = (short)(1 + activePartyCount + activePartyCount + activePartyCount);
		header->unk02 = 0;
		header->unk04 = 0;
		header->finished = 0;

		*(short*)(statePtr + 0x22) = 0;
		InitAnimSprite(&sprites[0], 0x16, 0, 0, 0x280, 0x1c0, 0, 8);
		sprites[0].depth = 0.0f;
		sprites[0].scale = 0.0f;

		for (int i = 0; i < activePartyCount; i++) {
			int idx = i + 1;
			InitAnimSprite(&sprites[idx], 0x17, 0x80, (short)(0x38 + i * 0x60), 0x1a0, 0x40, 0x16 + i * 3, 8);
			sprites[idx].depth = 0.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = 1 + activePartyCount + i;
			InitAnimSprite(&sprites[idx], 0x18, 0x48, (short)(0x28 + i * 0x60), 0x60, 0x58, 0x40 + i * 3, 8);
			sprites[idx].depth = 0.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			int idx = 1 + activePartyCount + activePartyCount + i;
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, 0x58 + i * 2, 8);
			sprites[idx].depth = 0.0f;
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

		if (sprite->kind == 0x17 && sprite->timer == 1) {
			Sound.PlaySe(0x49, 0x40, 0x7f, 0);
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

	if (animPtr == 0 || statePtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

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
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, i);
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

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;
		header->finished = 0;
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].timer = 0;
			sprites[i].startFrame = i * 2;
			sprites[i].duration = 10;
			sprites[i].alpha = 0.0f;
		}
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	TickAnimSprites(statePtr, animPtr, 1);
	if (header->finished != 0) {
		*(short*)(animPtr + 6) = 1;
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

	if (animPtr == 0 || statePtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float strongest = 0.0f;
	int digitIndex = 0;

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
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, digitIndex++);
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

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;
		header->finished = 0;
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].timer = 0;
			sprites[i].duration = 8;
			sprites[i].startFrame = i;
		}
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	TickAnimSprites(statePtr, animPtr, -1);
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

	if (animPtr == 0 || statePtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);
	float strongest = 0.0f;

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
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, i);
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
	unsigned int* scriptFoodBase = Game.game.m_scriptFoodBase;
	int statePtr = GetBonusMenuMembers(this).m_bonusStatePtr;
	int animPtr = GetBonusMenuMembers(this).m_bonusAnimPtr;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int activePartyCount = 0;
		int idx;

		GetBonusMenuMembers(this).m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset((void*)animPtr, 0, 0x1008);

		for (int i = 0; i < 4; i++) {
			if (scriptFoodBase[i] != 0) {
				activePartyCount++;
			}
		}
		if (activePartyCount <= 0) {
			activePartyCount = 1;
		}

		header->count = (short)(12 + activePartyCount * 3);
		header->unk02 = 0;
		header->unk04 = 0;
		header->finished = 0;

		idx = 0;
		InitAnimSprite(&sprites[idx++], 0x16, 0, 0, 0x280, 0x1c0, 0, 0);
		sprites[0].scale = 3.0f;

		InitAnimSprite(&sprites[idx++], -3, 0xf0, 0x38, 0x168, 0x148, 0, 8);
		InitAnimSprite(&sprites[idx++], 0x1f, 0, 0, 0x80, 0x78, 9999, 8);
		sprites[2].mulX = -150.0f;
		sprites[2].mulY = -150.0f;
		sprites[2].scale = 2.0f;
		InitAnimSprite(&sprites[idx++], -4, 0, 0, 0x70, 0x68, 0, 8);

		short y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			short x = ((0 < i) && (i < 3)) ? 0x30 : 0x48;
			InitAnimSprite(&sprites[idx], 0, x, y, 0x60, 0x58, 0, 0x18);
			sprites[idx].mulX = 96.0f;
			sprites[idx].mulY = 88.0f;
			sprites[idx].timer = 0;
			idx++;
			y += 0x60;
		}

		const int iconBase = idx - activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			InitAnimSprite(&sprites[idx], -1, 0, 0, 0, 0, sprites[iconBase + i].timer, 8);
			sprites[idx].timer = 0;
			idx++;
		}

		for (int i = 0; i < 8; i++) {
			int start = (int)((float)(10 + i * 5) * 0.6f);
			InitAnimSprite(&sprites[idx], -2, 0, 0, 0, 0, start, 0x21);
			sprites[idx].scale = 1.0f;
			idx++;
		}

		const int copyBase = iconBase;
		for (int i = 0; i < activePartyCount; i++) {
			sprites[idx] = sprites[copyBase + i];
			sprites[idx].timer = 0;
			sprites[idx].startFrame = 1;
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
			if (sprite->duration > 0) {
				sprite->alpha = (float)sprite->timer / (float)sprite->duration;
			}
		} else {
			sprite->alpha = 1.0f;
			doneCount++;
		}
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

	unsigned int* scriptFoodBase = Game.game.m_scriptFoodBase;
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
				int basePtr = GetBonusMenuMembers(this).m_bonusListPtr;
				if (basePtr != 0) {
					int slotPtr = basePtr + (modelIndex * 0x524);
					void* handle = *(void**)slotPtr;
					if (handle != 0) {
						SetProjection__8CMenuPcsFi(this, modelIndex);
						SetLight__8CMenuPcsFi(this, 1);
						unsigned int oldFlags = *(unsigned int*)((char*)handle + 8);
						*(unsigned int*)((char*)handle + 8) = 0x300543;
						Draw__Q29CCharaPcs7CHandleFi(handle, 5);
						*(unsigned int*)((char*)handle + 8) = oldFlags;
						DrawMenuIdx__8CPartPcsFi(&PartPcs, *(int*)(slotPtr + 4));
						RestoreProjection__8CMenuPcsFv(this);
					}
				}
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

	if (artiAlpha > 0.0f) {
		unsigned char activeMask = *(unsigned char*)(statePtr + 9);
		if (activeMask == 0) {
			for (int i = 0; i < 4; i++) {
				if (scriptFoodBase[i] != 0) {
					activeMask = (unsigned char)(activeMask | (1 << i));
				}
			}
		}

		SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
		SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x23);
		GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(artiAlpha * 255.0f)};
		GXSetChanMatColor(GX_COLOR0A0, color);

		float* markPos = gBonusCheckMarkPosBuffer;
		if (markPos != 0) {
			for (int i = 0; i < 8; i++) {
				if ((activeMask & (1 << i)) != 0) {
					float x = markPos[i * 2 + 0] + 4.0f;
					float y = markPos[i * 2 + 1] + 4.0f;
					DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, 24.0f, 24.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
				}
			}
		}
	}

	DrawInit__8CMenuPcsFv(this);
	CFont* font = GetBonusMenuMembers(this).m_font;
	if (font != 0) {
		font->SetMargin(1.0f);
		font->SetShadow(1);
		font->SetScale(1.0f);
		font->SetTlut(7);
		font->DrawInit();

		int nameIndex = 0;
		for (int i = 0; i < (int)header->count && nameIndex < activePartyCount; i++) {
			BonusAnimSprite* sprite = &sprites[i];
			if (sprite->kind != -1) {
				continue;
			}

			GXColor color = {0xFF, 0xFF, 0xFF, (unsigned char)(sprite->alpha * 255.0f)};
			font->SetColor(color);
			if (scriptFoodBase[nameIndex] != 0) {
				char* name = (char*)(scriptFoodBase[nameIndex] + 0x3ca);
				font->SetPosX((float)sprite->x + sprite->mulX);
				font->SetPosY((float)sprite->y + sprite->mulY - 12.0f);
				font->Draw(name);
			}
			nameIndex++;
		}
	}

	DrawInit__8CMenuPcsFv(this);
	if (*(short*)(GetBonusMenuMembers(this).m_bonusAuxPtr + 10) != 3) {
		DrawMcWin__8CMenuPcsFss(this, -1, 1);
		if (*(short*)(GetBonusMenuMembers(this).m_bonusAuxPtr + 10) == 1) {
			DrawMcWinMess__8CMenuPcsFii(this, 0x18, 1);
			DrawInit__8CMenuPcsFv(this);
			int cursorX = GetYesNoXPos__8CMenuPcsFi(this, (int)*(short*)(statePtr + 0x28));
			float cursorY = (float)(*(short*)(GetBonusMenuMembers(this).m_bonusAuxPtr + 2) + *(short*)(GetBonusMenuMembers(this).m_bonusAuxPtr + 6) - 0x3e);
			DrawCursor__8CMenuPcsFiif(this, cursorX, (int)cursorY, 1.0f);
		}
	}

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
	BonusAnimHeader* header;
	BonusAnimSprite* sprites;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	header = (BonusAnimHeader*)animPtr;
	sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		*(short*)(statePtr + 0x22) = 0;
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	*(short*)(statePtr + 0x22) = *(short*)(statePtr + 0x22) + 1;
	for (int i = 0; i < (int)header->count; i++) {
		float pulse = (float)((*(short*)(statePtr + 0x22) + i) & 0xf) / 15.0f;
		sprites[i].alpha = 0.5f + (pulse * 0.5f);
	}

	if (*(short*)(statePtr + 0x22) > 60) {
		*(short*)(animPtr + 6) = 1;
	}
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
	int pulseFrame;

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	pulseFrame = (int)*(short*)(statePtr + 0x22);
	for (int i = 0; i < (int)header->count; i++) {
		BonusAnimSprite* sprite = &sprites[i];
		float pulse = (float)((pulseFrame + i) & 0x1f) / 31.0f;
		float alpha = 0.65f + pulse * 0.35f;

		if (alpha < sprite->alpha) {
			alpha = sprite->alpha;
		}
		if (alpha > 1.0f) {
			alpha = 1.0f;
		}

		switch (sprite->kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, i);
			break;
		default:
			break;
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
		for (int i = 0; i < (int)header->count; i++) {
			sprites[i].timer = 0;
			sprites[i].duration = 8;
			sprites[i].startFrame = i;
		}
		*(unsigned char*)(statePtr + 0xb) = 1;
		return;
	}

	TickAnimSprites(statePtr, animPtr, -1);
	if (header->finished != 0) {
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

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

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
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, i);
			break;
		default:
			break;
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
 * Address: TODO
 * Size: TODO
 */
void CMenuPcs::DrawBonusCnt(CMenuPcs::Sprt2* sprt, int value)
{
	BonusAnimSprite* sprite = (BonusAnimSprite*)sprt;
	int digitValue;
	int ones;
	int tens;
	float fade;
	float baseX;
	float baseY;
	float digitW;
	float digitH;

	if (sprite == 0) {
		return;
	}

	digitValue = value;
	if (digitValue < 0) {
		digitValue = -digitValue;
	}
	digitValue = digitValue % 100;

	fade = sprite->alpha;
	if (fade < 0.0f) {
		fade = 0.0f;
	}
	if (fade > 1.0f) {
		fade = 1.0f;
	}

	ones = digitValue % 10;
	tens = (digitValue / 10) % 10;
	baseX = (float)sprite->x + sprite->mulX;
	baseY = (float)sprite->y + sprite->mulY;
	digitW = (sprite->w > 0) ? (float)sprite->w : 24.0f;
	digitH = (sprite->h > 0) ? (float)sprite->h : 24.0f;

	sprite->mulX = (float)tens * 0.1f;
	sprite->mulY = (float)ones * 0.1f;
	sprite->depth = fade;
	sprite->scale = 0.95f + (fade * 0.2f);

	if (tens > 0) {
		DrawBonusFrame(baseX, baseY, digitW, digitH, fade);
	}
	DrawBonusFrame(baseX + digitW * 0.7f, baseY, digitW, digitH, fade);

	if (fade > 0.99f) {
		DrawBonusChkMark(fade);
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
	if (sprt == 0) {
		return;
	}

	unsigned int* out = (unsigned int*)sprt;
	out[0] = (unsigned int)(alpha * 255.0f);
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
	float a = alpha;
	float strongest = a;
	float pulse;

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

	if (statePtr != 0) {
		pulse = (float)((*(short*)(statePtr + 0x22)) & 0x1f) / 31.0f;
		strongest = strongest * (0.85f + pulse * 0.15f);
	}

	if (strongest > 1.0f) {
		strongest = 1.0f;
	}
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
	if (a != 0) {
		memset(a, 0, 0x40);
	}
	if (b != 0) {
		memset(b, 0, 0x40);
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
		if (Game.game.m_scriptFoodBase[i] != 0) {
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
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[i]);
		if (caravanWork != 0) {
			caravanWork->SafeDeleteTempItem();
			caravanWork->SortBeforeReturnWorldMap();
		}
	}
}

