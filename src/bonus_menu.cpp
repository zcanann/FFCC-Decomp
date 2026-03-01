#include "ffcc/bonus_menu.h"
#include "ffcc/gobjwork.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

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

} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::BonusInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::createBonus()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroyBonus()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcBonus()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawBonus()
{
	// TODO
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int activePartyCount = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		*(unsigned char*)((char*)this + 0x8c) = 0;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawResultOpenAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcResultCountAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawResultCountAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcResultCloseAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawResultCloseAnim()
{
	// TODO
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
	// Simplified implementation to get basic structure compiling
	// TODO: Expand based on Ghidra decompilation patterns
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSelectOpenAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSelectWait()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSelectWait()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSelectCloseAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSelectCloseAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBonusCnt(CMenuPcs::Sprt2*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBonusFrame(float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawArtiBase(CMenuPcs::Sprt2*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBonusChkMark(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiBaseInfoInit(CMenuPcs::Sprt2*, CMenuPcs::Sprt2*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetAllPadOn()
{
	// TODO
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
