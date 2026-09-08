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

static const double kTmpArtiHalfDouble = 0.5;
static const float kTmpArtiColorMax = 255.0f;
static const float kTmpArtiZero = 0.0f;
static const float kTmpArtiOne = 1.0f;
static const float kTmpArtiFontScale = 0.9f;
static const float kTmpArtiTextYOffset = 4.0f;
static const double kTmpArtiOneDouble = 1.0;
static const double kTmpArtiZeroDouble = 0.0;
static const double kTmpArtiCenterX = 216.0;

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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 360b
 * EN Address: 0x801803BC
 * EN Size: 328b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::TmpArtiCtrlCur()
{
    short buttonDown = Pad.GetButtonDown(0);

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
    } else if ((buttonDown & 0x200) != 0) {
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
 * EN Address: 0x8017FA84
 * EN Size: 188b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::TmpArtiInit0()
{
    TmpArtiEntry* entry = m_tmpArtiList->entries;
    float alpha = kTmpArtiOne;

    for (int count = m_tmpArtiList->count; count > 0; count--) {
        entry->startFrame = 0;
        entry->duration = 1;
        entry->alpha = alpha;
        entry++;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 408b
 * EN Address: 0x8017F928
 * EN Size: 348b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::TmpArtiInit()
{
    memset(m_tmpArtiList, 0, sizeof(TmpArtiList));

    float one = kTmpArtiOne;
    TmpArtiEntry* entry = m_tmpArtiList->entries;
    for (int i = 0; i < 64; i++, entry++) {
        entry->z = one;
    }

    double center = kTmpArtiCenterX;
    double half = kTmpArtiHalfDouble;
    float zero = kTmpArtiZero;
    entry = m_tmpArtiList->entries;
    for (int row = 0; row < 4; row++, entry++) {
        entry->tex = 0x37;
        entry->width = 200;
        entry->height = 0x28;
        entry->x = (short)(int)(center - (double)entry->width * half);
        entry->y = row * (entry->height - 8) + 0x60;
        entry->s = zero;
        entry->t = zero;
        entry->startFrame = row;
        entry->duration = 3;
    }

    m_tmpArtiList->count = 4;
    m_tmpArtiState->unk_26 = 0;
    m_tmpArtiState->initialized = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8015d798
 * PAL Size: 1056b
 * EN Address: 0x8017FE9C
 * EN Size: 1312b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::TmpArtiDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	TmpArtiEntry* entry = m_tmpArtiList->entries;
	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	for (int i = 0; i < m_tmpArtiList->count; i++) {
		if (entry->tex >= 0) {
			int tex = entry->tex;
			float left = (float)entry->x;
			float top = (float)entry->y;
			float width = (float)entry->width;
			float height = (float)entry->height;
			float s = entry->s;
			float t = entry->t;
			float rawAlpha = entry->alpha;
			float alpha = rawAlpha;

			if (caravanWork->m_artifacts[CCaravanWork::kPermanentArtifactCount + i] < 0) {
				tex = 0x34;
				alpha = (float)(kTmpArtiHalfDouble * (double)rawAlpha);
			}

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			GXColor color;
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = (unsigned char)(int)(kTmpArtiColorMax * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float z = entry->z;
			MenuPcs.DrawRect(0, left, top, width, height, s, t, z, z, kTmpArtiZero);
		}
		entry++;
	}

	entry = m_tmpArtiList->entries;
	for (int i = 0; i < 4; i++) {
		short icon = caravanWork->m_artifacts[CCaravanWork::kPermanentArtifactCount + i];
		if (icon >= 0) {
			int posX = (int)static_cast<float>(entry->x + entry->width - 0x10);
			int posY = (int)(static_cast<float>(entry->y + 6) - kTmpArtiOne);
			DrawSingleIcon(icon, posX, posY, entry->alpha, 0, kTmpArtiZero);
		}
		entry++;
	}

	CFont* font = m_fonts[4];
	font->SetMargin(kTmpArtiOne);
	font->SetShadow(0);
	font->SetScale(kTmpArtiFontScale);
	font->DrawInit();

	entry = m_tmpArtiList->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_artifacts[CCaravanWork::kPermanentArtifactCount + i] >= 0) {
			float alpha = entry->alpha;
			CColor textColor(0xFF, 0xFF, 0xFF, kTmpArtiColorMax * alpha);
			font->SetColor(textColor.color);

			const char* text = Game.m_cFlatDataArr[1].TableStrings(0)[caravanWork->m_artifacts[CCaravanWork::kPermanentArtifactCount + i] * 5 + 4];
			float width = font->GetWidth(text);
			float posX = (float)((((float)entry->width - width) * kTmpArtiHalfDouble) + (float)entry->x);
			float posY = (float)(entry->y + 11);

			font->SetPosX(posX);
			font->SetPosY(posY - kTmpArtiTextYOffset);
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
 * EN Address: 0x8017FD20
 * EN Size: 380b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiClose()
{
	float zero;
	TmpArtiEntry* entry;
	int completedItems;
	int itemCount;
	int currentFrame;
	int count;
	unsigned int result;

	completedItems = 0;
	this->m_tmpArtiState->frame = this->m_tmpArtiState->frame + 1;
	itemCount = this->m_tmpArtiList->count;
	entry = this->m_tmpArtiList->entries;
	currentFrame = this->m_tmpArtiState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = kTmpArtiZero;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = kTmpArtiOneDouble / (double)entry->duration;
				entry->alpha = (float)(kTmpArtiOneDouble - ratio * (double)entry->timer);
				if ((double)entry->alpha < kTmpArtiZeroDouble) {
					entry->alpha = kTmpArtiZero;
				}
			}
		}
		entry++;
	}

	result = 0;
	if (this->m_tmpArtiList->count == completedItems) {
		zero = kTmpArtiZero;
		entry = this->m_tmpArtiList->entries;
		for (count = itemCount; count > 0; count--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = zero;
			entry++;
		}
		result = 1;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015dd64
 * PAL Size: 744b
 * EN Address: 0x8017FCBC
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::TmpArtiCtrl()
{
	int hasInput;
	int itemCount;
	int startFrame;

	this->m_tmpArtiState->selection = this->m_tmpArtiState->prevSelection;
	hasInput = TmpArtiCtrlCur();

	if (hasInput) {
		float alpha = kTmpArtiOne;
		const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

		TmpArtiEntry* entry = this->m_tmpArtiList->entries;
		for (int i = 0; i < this->m_tmpArtiList->count; i = i + 1) {
			entry->alpha = alpha;
			entry->z = alpha;
			entry++;
		}

		itemCount = caravanWork->m_numCmdListSlots;
		startFrame = 0;
		for (int setupIndex = itemCount - 1; setupIndex >= 0; setupIndex--) {
			TmpArtiEntry* setupEntry = &this->m_tmpArtiList->entries[setupIndex];
			setupEntry->startFrame = startFrame;
			startFrame = startFrame + 1;
			setupEntry->duration = 3;
		}
	}

	return hasInput;
}

/*
 * --INFO--
 * PAL Address: 0x8015e04c
 * PAL Size: 816b
 * EN Address: 0x8017FB40
 * EN Size: 380b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::TmpArtiOpen()
{
	int completedItems;
	TmpArtiEntry* entry;
	int itemCount;
	int currentFrame;
	unsigned int result;

	if (this->m_tmpArtiState->initialized == '\0') {
		TmpArtiInit();
	}

	completedItems = 0;
	this->m_tmpArtiState->frame = this->m_tmpArtiState->frame + 1;
	itemCount = this->m_tmpArtiList->count;
	entry = this->m_tmpArtiList->entries;
	currentFrame = this->m_tmpArtiState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = kTmpArtiOne;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = kTmpArtiOneDouble / (double)entry->duration;
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
