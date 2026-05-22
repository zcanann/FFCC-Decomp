#include "ffcc/menu_tmparti.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include <string.h>

extern "C" int __cntlzw(unsigned int);

extern const double DOUBLE_80332f20;
extern const float FLOAT_80332F28;
extern const float FLOAT_80332f2c;
extern const float FLOAT_80332f30;
extern const float FLOAT_80332F34;
extern const float FLOAT_80332F38;
extern const double DOUBLE_80332f48;
extern const double DOUBLE_80332f50;
extern const double DOUBLE_80332f58;
extern const double DOUBLE_80333418 = 0.0;
extern const double DOUBLE_80333420 = 216.0;

static inline double TmpArtiIntToDouble(int value)
{
    return (double)value;
}

STATIC_ASSERT(offsetof(TmpArtiState, initialized) == 0xB);
STATIC_ASSERT(offsetof(TmpArtiState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(TmpArtiState, moveDirection) == 0x1E);
STATIC_ASSERT(offsetof(TmpArtiState, frame) == 0x22);
STATIC_ASSERT(offsetof(TmpArtiState, unk_26) == 0x26);
STATIC_ASSERT(offsetof(TmpArtiState, prevSelection) == 0x30);
STATIC_ASSERT(offsetof(TmpArtiState, selection) == 0x32);
STATIC_ASSERT(offsetof(TmpArtiEntry, alpha) == 0x10);
STATIC_ASSERT(offsetof(TmpArtiEntry, z) == 0x14);
STATIC_ASSERT(offsetof(TmpArtiEntry, tex) == 0x1C);
STATIC_ASSERT(offsetof(TmpArtiEntry, timer) == 0x20);
STATIC_ASSERT(offsetof(TmpArtiEntry, startFrame) == 0x24);
STATIC_ASSERT(offsetof(TmpArtiEntry, duration) == 0x28);
STATIC_ASSERT(sizeof(TmpArtiEntry) == 0x40);
STATIC_ASSERT(sizeof(TmpArtiList) == 0x1008);

namespace {
static inline TmpArtiList* GetTmpArtiList(CMenuPcs* menu)
{
    return menu->m_tmpArtiList;
}

static inline TmpArtiEntry* GetTmpArtiEntries(CMenuPcs* menu)
{
    return GetTmpArtiList(menu)->entries;
}

static inline CFont* GetTmpArtiFont(CMenuPcs* menu)
{
    return menu->m_tmpArtiFont;
}
} // namespace

struct TmpArtiTableEntry {
    int count;
    const char** strings;
    char* stringBuf;
};

struct TmpArtiFlatData {
    char pad0[0x6C];
    TmpArtiTableEntry table[8];
};

/*
 * --INFO--
 * PAL Address: 0x8015d798
 * PAL Size: 1056b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::TmpArtiDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	unsigned int scriptFood = Game.m_scriptFoodBase[0];
	short* entry = reinterpret_cast<short*>(GetTmpArtiEntries(this));
	unsigned int foodPtr = scriptFood;

	for (int i = 0; i < GetTmpArtiList(this)->count; i++) {
		int tex = *(int*)(entry + 0xE);
		if (tex >= 0) {
			float alpha = *(float*)(entry + 8);
			float left = (float)entry[0];
			float top = (float)entry[1];
			float width = (float)entry[2];
			float height = (float)entry[3];
			float s = *(float*)(entry + 4);
			float t = *(float*)(entry + 6);

			if (*(short*)(foodPtr + 0x1F6) < 0) {
				tex = 0x34;
				alpha = (float)(DOUBLE_80332f20 * (double)alpha);
			}

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			GXColor color;
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = (unsigned char)(int)(FLOAT_80332F28 * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float z = *(float*)(entry + 10);
			MenuPcs.DrawRect(0, left, top, width, height, s, t, z, z, FLOAT_80332f2c);
		}
		foodPtr += 2;
		entry += 0x20;
	}

	entry = reinterpret_cast<short*>(GetTmpArtiEntries(this));
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		short icon = *(short*)(foodPtr + 0x1F6);
		if (icon >= 0) {
			int posX = (int)TmpArtiIntToDouble(entry[0] + entry[2] - 0x10);
			int posY = (int)((float)TmpArtiIntToDouble(entry[1] + 6) - FLOAT_80332f30);
			DrawSingleIcon(icon, posX, posY, *(float*)(entry + 8), 0, FLOAT_80332f2c);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	CFont* font = GetTmpArtiFont(this);
	font->SetMargin(FLOAT_80332f30);
	font->SetShadow(0);
	font->SetScale(FLOAT_80332F34);
	font->DrawInit();

	const TmpArtiFlatData* flatData = (const TmpArtiFlatData*)&Game.m_cFlatDataArr[1];
	entry = reinterpret_cast<short*>(GetTmpArtiEntries(this));
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		if (*(short*)(foodPtr + 0x1F6) >= 0) {
			float alpha = *(float*)(entry + 8);
			CColor textColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80332F28 * alpha));
			font->SetColor(textColor.color);

			const char* text = flatData->table[0].strings[*(short*)(foodPtr + 0x1F6) * 5 + 4];
			float width = font->GetWidth(text);
			float posX = (float)(((TmpArtiIntToDouble(entry[2]) - width) * DOUBLE_80332f20) +
			                       TmpArtiIntToDouble(entry[0]));
			double posY = TmpArtiIntToDouble(entry[1] + 11);

			font->SetPosX(posX);
			font->SetPosY((float)posY - FLOAT_80332F38);
			font->Draw(text);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x8015dbb8
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiClose()
{
	float zero;
	TmpArtiEntry* entry;
	int completedItems;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;

	completedItems = 0;
	this->m_tmpArtiState->frame = this->m_tmpArtiState->frame + 1;
	itemCount = (unsigned int)this->m_tmpArtiList->count;
	entry = this->m_tmpArtiList->entries;
	currentFrame = (int)this->m_tmpArtiState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = FLOAT_80332f2c;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = DOUBLE_80332f48 / (double)entry->duration;
				entry->alpha = (float)(DOUBLE_80332f48 - ratio * (double)entry->timer);
				if ((double)entry->alpha < DOUBLE_80332f50) {
					entry->alpha = FLOAT_80332f2c;
				}
			}
		}
		entry++;
	}

	if (this->m_tmpArtiList->count == completedItems) {
		zero = FLOAT_80332f2c;
		entry = this->m_tmpArtiList->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			for (; count != 0; count--) {
				entry[0].startFrame = 0;
				entry[0].duration = 1;
				entry[0].alpha = zero;
				entry[1].startFrame = 0;
				entry[1].duration = 1;
				entry[1].alpha = zero;
				entry[2].startFrame = 0;
				entry[2].duration = 1;
				entry[2].alpha = zero;
				entry[3].startFrame = 0;
				entry[3].duration = 1;
				entry[3].alpha = zero;
				entry[4].startFrame = 0;
				entry[4].duration = 1;
				entry[4].alpha = zero;
				entry[5].startFrame = 0;
				entry[5].duration = 1;
				entry[5].alpha = zero;
				entry[6].startFrame = 0;
				entry[6].duration = 1;
				entry[6].alpha = zero;
				entry[7].startFrame = 0;
				entry[7].duration = 1;
				entry[7].alpha = zero;
				entry += 8;
			}
			itemCount &= 7;
			if (itemCount != 0) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = zero;
					entry++;
					itemCount--;
				} while (itemCount != 0);
			}
		}
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015dd64
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::TmpArtiCtrl()
{
	bool hasInput;
	unsigned short uVar3;
	unsigned int uVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	unsigned int uVar9;

	hasInput = false;
	this->m_tmpArtiState->selection = this->m_tmpArtiState->prevSelection;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		hasInput = true;
	}

	if (hasInput) {
		uVar3 = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		uVar3 = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&Pad) + padIndex * 0x54 + 8);
	}

	if (uVar3 == 0) {
		hasInput = false;
	} else if ((uVar3 & 0x20) != 0) {
		this->m_tmpArtiState->moveDirection = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x40) != 0) {
		this->m_tmpArtiState->moveDirection = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		hasInput = false;
	} else if ((uVar3 & 0x200) != 0) {
		this->m_tmpArtiState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		hasInput = true;
	} else {
		hasInput = false;
	}

	if (hasInput) {
		float fVar2 = FLOAT_80332f30;
		unsigned int uVar4 = Game.m_scriptFoodBase[0];

		iVar6 = reinterpret_cast<int>(this->m_tmpArtiList) + 8;
		for (iVar7 = 0; iVar7 < this->m_tmpArtiList->count; iVar7 = iVar7 + 1) {
			*(float *)(iVar6 + 0x10) = fVar2;
			*(float *)(iVar6 + 0x14) = fVar2;
			iVar6 = iVar6 + 0x40;
		}

		uVar5 = (unsigned int)*(short *)(uVar4 + 0xbaa);
		iVar7 = 0;
		iVar6 = (uVar5 - 1) * 0x40;
		if (-1 < (int)(uVar5 - 1)) {
			uVar9 = uVar5 >> 3;
			if (uVar9 != 0) {
				do {
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + 8;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x38;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x78;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0xb8;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0xf8;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x138;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x178;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = iVar6 + -0x1b8;
					iVar6 = iVar6 + -0x200;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar8;
					*(int *)(iVar8 + 0x24) = iVar7++;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					uVar9 = uVar9 - 1;
				} while (uVar9 != 0);
				uVar5 = uVar5 & 7;
				if (uVar5 == 0) {
					return;
				}
			}
			do {
				iVar8 = iVar6 + 8;
				iVar6 = iVar6 + -0x40;
				iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar8;
				*(int *)(iVar8 + 0x24) = iVar7;
				iVar7 = iVar7 + 1;
				*(unsigned int *)(iVar8 + 0x28) = 3;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015e04c
 * PAL Size: 816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiOpen()
{
	double half;
	float zero;
	float one;
	double center;
	int completedItems;
	TmpArtiEntry* entry;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;

	if (this->m_tmpArtiState->initialized == '\0') {
		memset(this->m_tmpArtiList, 0, sizeof(TmpArtiList));
		one = FLOAT_80332f30;
		entry = this->m_tmpArtiList->entries;
		int i = 8;
		do {
			entry[0].z = one;
			entry[1].z = one;
			entry[2].z = one;
			entry[3].z = one;
			entry[4].z = one;
			entry[5].z = one;
			entry[6].z = one;
			entry[7].z = one;
			entry += 8;
			i--;
		} while (i != 0);

		center = DOUBLE_80332f58;
		zero = FLOAT_80332f2c;
		half = DOUBLE_80332f20;
		int row = 0;
		entry = this->m_tmpArtiList->entries;
		int pairCount = 2;
		do {
			entry[0].tex = 0x37;
			entry[0].width = 200;
			entry[0].height = 0x28;
			entry[0].x = (short)(int)-(((double)entry[0].width * half) - center);
			entry[0].y = (short)row * (entry[0].height - 8) + 0x60;
			entry[0].s = zero;
			entry[0].t = zero;
			entry[0].startFrame = row++;
			entry[0].duration = 3;
			entry[1].tex = 0x37;
			entry[1].width = 200;
			entry[1].height = 0x28;
			entry[1].x = (short)(int)-(((double)entry[1].width * half) - center);
			entry[1].y = (short)row * (entry[1].height - 8) + 0x60;
			entry[1].s = zero;
			entry[1].t = zero;
			entry[1].startFrame = row++;
			entry[1].duration = 3;
			entry += 2;
			pairCount--;
		} while (pairCount != 0);
		this->m_tmpArtiList->count = 4;
		this->m_tmpArtiState->unk_26 = 0;
		this->m_tmpArtiState->initialized = 1;
	}

	completedItems = 0;
	this->m_tmpArtiState->frame = this->m_tmpArtiState->frame + 1;
	itemCount = (unsigned int)this->m_tmpArtiList->count;
	entry = this->m_tmpArtiList->entries;
	currentFrame = (int)this->m_tmpArtiState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = FLOAT_80332f30;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = DOUBLE_80332f48 / (double)entry->duration;
				entry->alpha = (float)(ratio * (double)entry->timer);
			}
		}
		entry++;
	}

	if (this->m_tmpArtiList->count == completedItems) {
		one = FLOAT_80332f30;
		entry = this->m_tmpArtiList->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			for (; count != 0; count--) {
				entry[0].startFrame = 0;
				entry[0].duration = 1;
				entry[0].alpha = one;
				entry[1].startFrame = 0;
				entry[1].duration = 1;
				entry[1].alpha = one;
				entry[2].startFrame = 0;
				entry[2].duration = 1;
				entry[2].alpha = one;
				entry[3].startFrame = 0;
				entry[3].duration = 1;
				entry[3].alpha = one;
				entry[4].startFrame = 0;
				entry[4].duration = 1;
				entry[4].alpha = one;
				entry[5].startFrame = 0;
				entry[5].duration = 1;
				entry[5].alpha = one;
				entry[6].startFrame = 0;
				entry[6].duration = 1;
				entry[6].alpha = one;
				entry[7].startFrame = 0;
				entry[7].duration = 1;
				entry[7].alpha = one;
				entry += 8;
			}
			itemCount &= 7;
			if (itemCount != 0) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = one;
					entry++;
					itemCount--;
				} while (itemCount != 0);
			}
		}
		return 1;
	}

	return 0;
}
