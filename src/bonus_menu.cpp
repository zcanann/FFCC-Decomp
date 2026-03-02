#include "ffcc/bonus_menu.h"
#include "ffcc/gobjwork.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

extern "C" {
extern int lbl_8032EEA8;
extern int lbl_8032EEB0;
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
	lbl_8032EEA8 = 0;
	*(int*)((char*)this + 0x84c) = 0;
	lbl_8032EEB0 = 0;
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
	int auxPtr = *(int*)((char*)this + 0x848);
	int boardPtr = *(int*)((char*)this + 0x814);

	if (statePtr == 0) {
		statePtr = (int)(new unsigned char[0x48]);
		*(int*)((char*)this + 0x82c) = statePtr;
	}
	if (animPtr == 0) {
		animPtr = (int)(new unsigned char[0x1008]);
		*(int*)((char*)this + 0x84c) = animPtr;
	}
	if (auxPtr == 0) {
		auxPtr = (int)(new unsigned char[0xc]);
		*(int*)((char*)this + 0x848) = auxPtr;
	}
	if (boardPtr == 0) {
		boardPtr = (int)(new unsigned char[0x780]);
		*(int*)((char*)this + 0x814) = boardPtr;
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

	*(unsigned char*)((char*)this + 0x8c) = 0;
	*(unsigned char*)((char*)this + 0x8d) = 0;
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
	int ptr = *(int*)((char*)this + 0x840);
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		*(int*)((char*)this + 0x840) = 0;
	}

	ptr = *(int*)((char*)this + 0x82c);
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		*(int*)((char*)this + 0x82c) = 0;
	}

	ptr = *(int*)((char*)this + 0x84c);
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		*(int*)((char*)this + 0x84c) = 0;
	}

	ptr = *(int*)((char*)this + 0x814);
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		*(int*)((char*)this + 0x814) = 0;
	}

	ptr = *(int*)((char*)this + 0x848);
	if (ptr != 0) {
		delete[] (unsigned char*)ptr;
		*(int*)((char*)this + 0x848) = 0;
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	int statePtr = *(int*)((char*)this + 0x82c);
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
 * PAL Address: 0x8013a8f4
 * PAL Size: 2136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultOpenAnim()
{
	int animPtr = *(int*)((char*)this + 0x84c);
	int statePtr = *(int*)((char*)this + 0x82c);
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

	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	int animPtr = *(int*)((char*)this + 0x84c);
	int statePtr = *(int*)((char*)this + 0x82c);

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
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	int animPtr = *(int*)((char*)this + 0x84c);
	int statePtr = *(int*)((char*)this + 0x82c);

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
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);

	if (statePtr == 0 || animPtr == 0) {
		return;
	}

	BonusAnimHeader* header = (BonusAnimHeader*)animPtr;
	BonusAnimSprite* sprites = (BonusAnimSprite*)(animPtr + 8);

	if (*(unsigned char*)(statePtr + 0xb) == 0) {
		int activePartyCount = 0;
		int idx;

		*(unsigned char*)((char*)this + 0x8d) = 0;
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
	int animPtr = *(int*)((char*)this + 0x84c);
	int statePtr = *(int*)((char*)this + 0x82c);

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
		switch (sprite->kind) {
		case -4:
			DrawArtiBase((CMenuPcs::Sprt2*)sprite, alpha);
			break;
		case -3:
			DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, alpha);
			break;
		case -2:
			DrawBonusCnt((CMenuPcs::Sprt2*)sprite, digitIndex++);
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
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	int statePtr = *(int*)((char*)this + 0x82c);
	int animPtr = *(int*)((char*)this + 0x84c);
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
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)(strongest * 255.0f);
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
	float area = w * h * alpha;
	if (area < 0.0f) {
		area = 0.0f;
	}
	(void)x;
	(void)y;
	*(unsigned char*)((char*)this + 0x8c) = (unsigned char)((int)area & 0xff);
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
	int animPtr = *(int*)((char*)this + 0x84c);
	int statePtr = *(int*)((char*)this + 0x82c);
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
	*(unsigned char*)((char*)this + 0x8d) = (unsigned char)(strongest > 0.5f ? 1 : 0);
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
	int statePtr = *(int*)((char*)this + 0x82c);
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
