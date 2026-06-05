#include "ffcc/menu_tmparti.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include <string.h>

static const double DOUBLE_80332f20 = 0.5;
static const float FLOAT_80332F28 = 255.0f;
static const float FLOAT_80332f2c = 0.0f;
static const float FLOAT_80332f30 = 1.0f;
static const float FLOAT_80332F34 = 0.9f;
static const float FLOAT_80332F38 = 4.0f;
static const double DOUBLE_80332f40 = 4503601774854144.0;
static const double DOUBLE_80332f48 = 1.0;
static const double DOUBLE_80332f50 = 0.0;
static const double DOUBLE_80332f58 = 216.0;

static inline float TmpArtiIntToFloat(int value)
{
    return (float)value;
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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::TmpArtiCtrlCur()
{
    bool hasInput = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        hasInput = true;
    }

    unsigned short buttonDown;
    if (hasInput) {
        buttonDown = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
        buttonDown = Pad.GetPadInputs()[padIndex].buttonDown[0];
    }

    if (buttonDown == 0) {
        return 0;
    }

    if ((buttonDown & 0x20) != 0) {
        m_tmpArtiState->moveDirection = 1;
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        return 1;
    }

    if ((buttonDown & 0x40) != 0) {
        m_tmpArtiState->moveDirection = -1;
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        return 1;
    }

    if ((buttonDown & 0x100) != 0) {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    if ((buttonDown & 0x200) != 0) {
        m_tmpArtiState->closeRequested = 1;
        Sound.PlaySe(3, 0x40, 0x7f, 0);
        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::TmpArtiInit0()
{
    TmpArtiEntry* entry = GetTmpArtiEntries(this);
    unsigned int count = GetTmpArtiList(this)->count;
    float alpha = FLOAT_80332f30;

    if ((int)count > 0) {
        unsigned int blockCount = count >> 3;
        for (; blockCount != 0; blockCount--) {
            entry[0].startFrame = 0;
            entry[0].duration = 1;
            entry[0].alpha = alpha;
            entry[1].startFrame = 0;
            entry[1].duration = 1;
            entry[1].alpha = alpha;
            entry[2].startFrame = 0;
            entry[2].duration = 1;
            entry[2].alpha = alpha;
            entry[3].startFrame = 0;
            entry[3].duration = 1;
            entry[3].alpha = alpha;
            entry[4].startFrame = 0;
            entry[4].duration = 1;
            entry[4].alpha = alpha;
            entry[5].startFrame = 0;
            entry[5].duration = 1;
            entry[5].alpha = alpha;
            entry[6].startFrame = 0;
            entry[6].duration = 1;
            entry[6].alpha = alpha;
            entry[7].startFrame = 0;
            entry[7].duration = 1;
            entry[7].alpha = alpha;
            entry += 8;
        }

        count &= 7;
        if (count != 0) {
            do {
                entry->startFrame = 0;
                entry->duration = 1;
                entry->alpha = alpha;
                entry++;
                count--;
            } while (count != 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::TmpArtiInit()
{
    memset(m_tmpArtiList, 0, sizeof(TmpArtiList));

    float one = FLOAT_80332f30;
    TmpArtiEntry* entry = GetTmpArtiEntries(this);
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

    double center = DOUBLE_80332f58;
    double half = DOUBLE_80332f20;
    float zero = FLOAT_80332f2c;
    int row = 0;
    entry = GetTmpArtiEntries(this);
    for (int pairCount = 0; pairCount < 2; pairCount++) {
        entry[0].tex = 0x37;
        entry[0].width = 200;
        entry[0].height = 0x28;
        entry[0].x = (short)(int)-(((double)entry[0].width * half) - center);
        entry[0].y = row * (entry[0].height - 8) + 0x60;
        entry[0].s = zero;
        entry[0].t = zero;
        entry[0].startFrame = row++;
        entry[0].duration = 3;
        entry[1].tex = 0x37;
        entry[1].width = 200;
        entry[1].height = 0x28;
        entry[1].x = (short)(int)-(((double)entry[1].width * half) - center);
        entry[1].y = row * (entry[1].height - 8) + 0x60;
        entry[1].s = zero;
        entry[1].t = zero;
        entry[1].startFrame = row++;
        entry[1].duration = 3;
        entry += 2;
    }

    m_tmpArtiList->count = 4;
    m_tmpArtiState->unk_26 = 0;
    m_tmpArtiState->initialized = 1;
}

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

	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	TmpArtiEntry* entry = GetTmpArtiEntries(this);

	for (int i = 0; i < GetTmpArtiList(this)->count; i++) {
		int tex = entry->tex;
		if (tex >= 0) {
			float alpha = entry->alpha;
			float left = (float)entry->x;
			float top = (float)entry->y;
			float width = (float)entry->width;
			float height = (float)entry->height;
			float s = entry->s;
			float t = entry->t;

			if (caravanWork->m_treasures[i] < 0) {
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

			float z = entry->z;
			MenuPcs.DrawRect(0, left, top, width, height, s, t, z, z, FLOAT_80332f2c);
		}
		entry++;
	}

	entry = GetTmpArtiEntries(this);
	for (int i = 0; i < 4; i++) {
		short icon = caravanWork->m_treasures[i];
		if (icon >= 0) {
			int posX = (int)TmpArtiIntToFloat(entry->x + entry->width - 0x10);
			int posY = (int)(TmpArtiIntToFloat(entry->y + 6) - FLOAT_80332f30);
			DrawSingleIcon(icon, posX, posY, entry->alpha, 0, FLOAT_80332f2c);
		}
		entry++;
	}

	CFont* font = GetTmpArtiFont(this);
	font->SetMargin(FLOAT_80332f30);
	font->SetShadow(0);
	font->SetScale(FLOAT_80332F34);
	font->DrawInit();

	entry = GetTmpArtiEntries(this);
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_treasures[i] >= 0) {
			float alpha = entry->alpha;
			CColor textColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80332F28 * alpha));
			font->SetColor(textColor.color);

			const char* text = Game.m_cFlatDataArr[1].TableStrings(0)[caravanWork->m_treasures[i] * 5 + 4];
			float width = font->GetWidth(text);
			float posX = (float)((((float)entry->width - width) * DOUBLE_80332f20) + (float)entry->x);
			float posY = (float)(entry->y + 11);

			font->SetPosX(posX);
			font->SetPosY(posY - FLOAT_80332F38);
			font->Draw(text);
		}
		entry++;
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
	unsigned int result;

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

	result = 0;
	if (this->m_tmpArtiList->count == completedItems) {
		zero = FLOAT_80332f2c;
		entry = this->m_tmpArtiList->entries;
		count = itemCount;
		if ((int)count > 0) {
			itemCount = count >> 3;
			for (; itemCount != 0; itemCount--) {
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
			count &= 7;
			if (count != 0) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = zero;
					entry++;
					count--;
				} while (count != 0);
			}
		}
		result = 1;
	}

	return result;
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
int CMenuPcs::TmpArtiCtrl()
{
	int hasInput;
	unsigned int uVar5;
	int iVar7;
	unsigned int uVar9;

	this->m_tmpArtiState->selection = this->m_tmpArtiState->prevSelection;
	hasInput = TmpArtiCtrlCur();

	if (hasInput) {
		float fVar2 = FLOAT_80332f30;
		const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

		TmpArtiEntry* entry = this->m_tmpArtiList->entries;
		for (iVar7 = 0; iVar7 < this->m_tmpArtiList->count; iVar7 = iVar7 + 1) {
			entry->alpha = fVar2;
			entry->z = fVar2;
			entry++;
		}

		uVar5 = static_cast<unsigned int>(caravanWork->m_numCmdListSlots);
		iVar7 = 0;
		TmpArtiEntry* entries = GetTmpArtiEntries(this);
		int setupIndex = uVar5 - 1;
		if (-1 < (int)(uVar5 - 1)) {
			uVar9 = uVar5 >> 3;
			if (uVar9 != 0) {
				do {
					TmpArtiEntry* setupEntry = entries + setupIndex;
					setupEntry[0].startFrame = iVar7++;
					setupEntry[0].duration = 3;
					setupEntry[-1].startFrame = iVar7++;
					setupEntry[-1].duration = 3;
					setupEntry[-2].startFrame = iVar7++;
					setupEntry[-2].duration = 3;
					setupEntry[-3].startFrame = iVar7++;
					setupEntry[-3].duration = 3;
					setupEntry[-4].startFrame = iVar7++;
					setupEntry[-4].duration = 3;
					setupEntry[-5].startFrame = iVar7++;
					setupEntry[-5].duration = 3;
					setupEntry[-6].startFrame = iVar7++;
					setupEntry[-6].duration = 3;
					setupEntry[-7].startFrame = iVar7++;
					setupEntry[-7].duration = 3;
					setupIndex -= 8;
					uVar9 = uVar9 - 1;
				} while (uVar9 != 0);
				uVar5 = uVar5 & 7;
				if (uVar5 == 0) {
					return hasInput;
				}
			}
			do {
				entries[setupIndex].startFrame = iVar7;
				iVar7 = iVar7 + 1;
				entries[setupIndex].duration = 3;
				setupIndex--;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
		}
	}

	return hasInput;
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
	int completedItems;
	TmpArtiEntry* entry;
	unsigned int itemCount;
	int currentFrame;
	unsigned int result;

	if (this->m_tmpArtiState->initialized == '\0') {
		TmpArtiInit();
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

	result = 0;
	if (this->m_tmpArtiList->count == completedItems) {
		TmpArtiInit0();
		result = 1;
	}

	return result;
}
