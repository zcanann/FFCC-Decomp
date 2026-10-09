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

#ifdef VERSION_GCCJGC
enum {
    kTmpArtiRowTexture = 0x36,
    kTmpArtiEmptyRowTexture = 0x33
};
#else
enum {
    kTmpArtiRowTexture = 0x37,
    kTmpArtiEmptyRowTexture = 0x34
};
#endif

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
    float alpha;
    int i;
    TmpArtiEntry* entry;
    int startFrame;
    int itemCount;
    const CCaravanWork* caravanWork;

    alpha = 1.0f;
    caravanWork = Game.m_scriptFoodBase[0];
    entry = this->m_tmpArtiList->entries;
    for (i = 0; i < this->m_tmpArtiList->count; i++) {
        entry->alpha = alpha;
        entry->z = alpha;
        entry++;
    }

    itemCount = caravanWork->m_numCmdListSlots;
    startFrame = 0;
    for (int idx = itemCount - 1; idx >= 0; idx--) {
        entry = &this->m_tmpArtiList->entries[idx];
        entry->startFrame = startFrame++;
        entry->duration = 3;
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

    float one = 1.0f;
    TmpArtiEntry* entry = m_tmpArtiList->entries;
    for (int i = 0; i < 64; i++, entry++) {
        entry->z = one;
    }

    double center = 216.0;
    double half = 0.5;
    float zero = 0.0f;
    entry = m_tmpArtiList->entries;
    for (int row = 0; row < 4; row++, entry++) {
        entry->tex = kTmpArtiRowTexture;
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
 * EN Address: 0x8015C814
 * EN Size: 1056b
 * JP Address: 0x80158124
 * JP Size: 1048b
 */
void CMenuPcs::TmpArtiDraw()
{
	int i;
	TmpArtiEntry* entry;
	const CCaravanWork* caravanWork;
	CFont* font;
	GXColor colors[4];
	float left;
	float top;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	caravanWork = Game.m_scriptFoodBase[0];
	entry = m_tmpArtiList->entries;

	for (i = 0; i < m_tmpArtiList->count; i++, entry++) {
		if (entry->tex >= 0) {
			int tex = entry->tex;
			left = (float)entry->x;
			top = (float)entry->y;
			float width = (float)entry->width;
			float height = (float)entry->height;
			float s = entry->s;
			float t = entry->t;
			float rawAlpha = entry->alpha;
			float alpha = rawAlpha;

			if (caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i] < 0) {
				tex = kTmpArtiEmptyRowTexture;
				alpha = (float)(0.5 * (double)rawAlpha);
			}

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			colors[0].r = 0xFF;
			colors[0].g = 0xFF;
			colors[0].b = 0xFF;
			colors[0].a = (unsigned char)(int)(255.0f * alpha);
			GXSetChanMatColor(GX_COLOR0A0, colors[0]);

			float z = entry->z;
			MenuPcs.DrawRect(0, left, top, width, height, s, t, z, z, 0.0f);
		}
	}

	entry = m_tmpArtiList->entries;
	for (i = 0; i < 4; i++, entry++) {
		if (caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i] >= 0) {
			int posX = (int)static_cast<float>(entry->x + entry->width - 0x10);
			int posY = (int)(static_cast<float>(entry->y + 6) - 1.0f);
			DrawSingleIcon(caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i], posX, posY,
			               entry->alpha, 0, 1.0f);
		}
	}

	font = GetFontItem();
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->DrawInit();

	entry = m_tmpArtiList->entries;
	for (i = 0; i < 4; i++, entry++) {
		if (caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i] >= 0) {
			float alpha = entry->alpha;
			font->SetColor(CColor(0xFF, 0xFF, 0xFF, 255.0f * alpha).color);

			const char* text = Game.GetShortItemName(caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i]);
			float width = font->GetWidth(text);
			float posX = (entry->width - width) / 2.0 + entry->x;
			top = (float)(entry->y + 11);

			font->SetPosX(posX);
#ifdef VERSION_GCCJGC
			font->SetPosY(top);
#else
			font->SetPosY(top - 4.0f);
#endif
			font->Draw(text);
		}
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x8015dbb8
 * PAL Size: 428b
 * EN Address: 0x8015CC34
 * EN Size: 428b
 * JP Address: 0x8015853C
 * JP Size: 460b
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
				entry->alpha = 0.0f;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = 1.0 / (double)entry->duration;
				entry->alpha = (float)(1.0 - ratio * (double)entry->timer);
				if ((double)entry->alpha < 0.0) {
					entry->alpha = 0.0f;
				}
			}
		}
		entry++;
	}

	result = 0;
	if (this->m_tmpArtiList->count == completedItems) {
		zero = 0.0f;
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
 * EN Address: 0x8015CDE0
 * EN Size: 744b
 * JP Address: 0x80158708
 * JP Size: 748b
 */
int CMenuPcs::TmpArtiCtrl()
{
	int hasInput;

	this->m_tmpArtiState->selection = this->m_tmpArtiState->prevSelection;
	hasInput = TmpArtiCtrlCur();

	if (hasInput) {
		TmpArtiInit0();
	}

	return hasInput;
}

/*
 * --INFO--
 * PAL Address: 0x8015e04c
 * PAL Size: 816b
 * EN Address: 0x8015D0C8
 * EN Size: 816b
 * JP Address: 0x801589F4
 * JP Size: 900b
 */
unsigned int CMenuPcs::TmpArtiOpen()
{
	TmpArtiEntry* entry;
	int completedItems;
	int itemCount;
	int currentFrame;
	unsigned int result;

	if (this->m_tmpArtiState->initialized == '\0') {
		memset(m_tmpArtiList, 0, sizeof(TmpArtiList));
		float one = 1.0f;
		entry = m_tmpArtiList->entries;
		for (int k = 64; k != 0; k--) {
			entry->z = one;
			entry++;
		}

		double half = 0.5;
		double center = 216.0;
		float zero = 0.0f;
		int row = 0;
		entry = m_tmpArtiList->entries;
		for (int k = 4; k != 0; k--) {
			entry->tex = kTmpArtiRowTexture;
			entry->width = 200;
			entry->height = 0x28;
			entry->x = (short)(int)-((double)entry->width * half - center);
			entry->y = row * (entry->height - 8) + 0x60;
			entry->s = zero;
			entry->t = zero;
			entry->startFrame = row;
			row++;
			entry->duration = 3;
			entry++;
		}

		m_tmpArtiList->count = 4;
		m_tmpArtiState->unk_26 = 0;
		m_tmpArtiState->initialized = 1;
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
				entry->alpha = 1.0f;
			} else {
				entry->timer = entry->timer + 1;
				entry->alpha = (1.0 / entry->duration) * entry->timer;
			}
		}
		entry++;
	}

	result = 0;
	if (this->m_tmpArtiList->count == completedItems) {
		float one = 1.0f;
		entry = this->m_tmpArtiList->entries;
		for (int count = itemCount; count > 0; count--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = one;
			entry++;
		}
		result = 1;
	}

	return result;
}
