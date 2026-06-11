#include "ffcc/menu_arti.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef unsigned char u8;

static const float kArtiZero = 0.0f;
static const float kArtiOne = 1.0f;
static const double kArtiOneDouble = 1.0;
static const double kArtiHalfDouble = 0.5;
static const float kArtiColorMax = 255.0f;
static const float kArtiListFontScale = 0.9f;
static const float kArtiTextYOffset = 4.0f;
static const float kArtiHelpY = 352.0f;
static const float kArtiHelpScale = 3.0f;
static const float kArtiHelpCenterX = 320.0f;
static const float kArtiHalf = 0.5f;
static const double kArtiIntToDoubleBias = 4503601774854144.0;
static const float kArtiInitX = 128.0f;
static const float kArtiInitYOffset = 8.0f;
static const float kArtiInitScale = 0.75f;

extern "C" {
extern const char s_MenuOptionMusic[];
extern const char s_MenuOptionOn[];
extern const char s_MenuOptionOff[];
extern const char s_MenuOptionStereo[];
extern const char s_MenuOptionMin[];
extern const char s_MenuOptionMax[];
extern const char s_MenuOptionStrengthDe[];
extern const char s_MenuOptionDefenceDe[];
extern const char s_MenuOptionMusicDe[];
extern const char s_MenuOptionOnDe[];
extern const char s_MenuOptionOffDe[];
extern const char s_MenuOptionStereoDe[];
}

namespace {
STATIC_ASSERT(offsetof(CMenuPcs, m_artiState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_artiList) == 0x850);
STATIC_ASSERT(offsetof(ArtiState, initialized) == 0xB);
STATIC_ASSERT(offsetof(ArtiState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(ArtiState, state) == 0x10);
STATIC_ASSERT(offsetof(ArtiState, moveDirection) == 0x1E);
STATIC_ASSERT(offsetof(ArtiState, optionCloseReady) == 0x20);
STATIC_ASSERT(offsetof(ArtiState, frame) == 0x22);
STATIC_ASSERT(offsetof(ArtiState, selections) == 0x26);
STATIC_ASSERT(offsetof(ArtiState, currentSelection) == 0x30);
STATIC_ASSERT(offsetof(ArtiState, prevSelection) == 0x32);
STATIC_ASSERT(offsetof(ArtiState, scrollOffset) == 0x34);
STATIC_ASSERT(offsetof(ArtiOpenAnim, alpha) == 0x10);
STATIC_ASSERT(offsetof(ArtiOpenAnim, scale) == 0x14);
STATIC_ASSERT(offsetof(ArtiOpenAnim, unk) == 0x18);
STATIC_ASSERT(offsetof(ArtiOpenAnim, tex) == 0x1C);
STATIC_ASSERT(offsetof(ArtiOpenAnim, step) == 0x20);
STATIC_ASSERT(offsetof(ArtiOpenAnim, startFrame) == 0x24);
STATIC_ASSERT(offsetof(ArtiOpenAnim, duration) == 0x28);
STATIC_ASSERT(offsetof(ArtiOpenAnim, flags) == 0x2C);
STATIC_ASSERT(offsetof(ArtiOpenAnim, dx) == 0x30);
STATIC_ASSERT(offsetof(ArtiOpenAnim, dy) == 0x34);
STATIC_ASSERT(offsetof(ArtiOpenAnim, targetX) == 0x38);
STATIC_ASSERT(offsetof(ArtiOpenAnim, targetY) == 0x3C);
STATIC_ASSERT(sizeof(ArtiOpenAnim) == 0x40);
STATIC_ASSERT(offsetof(ArtiOpenAnimList, entries) == 8);
STATIC_ASSERT(sizeof(ArtiOpenAnimList) == 0x1008);

static inline ArtiState* GetArtiState(CMenuPcs* menu)
{
	return menu->m_artiState;
}

static inline ArtiOpenAnimList* GetArtiOpenAnimList(CMenuPcs* menu)
{
	return menu->m_artiList;
}

static inline ArtiOpenAnim* GetArtiOpenAnim(CMenuPcs* menu, int index)
{
	return &GetArtiOpenAnimList(menu)->entries[index];
}

static inline CFont* GetArtiListFont(CMenuPcs* menu)
{
	return menu->m_fonts[4];
}

static inline CFont* GetArtiHelpFont(CMenuPcs* menu)
{
	return menu->m_fonts[0];
}
} // namespace

static inline float LoadFloat(const float& value)
{
	return value;
}

static inline double IntToF64(unsigned int value)
{
	unsigned long long bits = ((unsigned long long)0x43300000 << 32) | (unsigned long long)(value ^ 0x80000000);
	return (double)bits - kArtiIntToDoubleBias;
}

static inline float IntToF32(int value)
{
	return (float)IntToF64((unsigned int)value);
}

static inline double LoadDouble(const double& value)
{
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x8015fa28
 * PAL Size: 812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiCtrlCur()
{
	int sVar1;
	bool bVar2;
	u16 uVar4;
	int uVar3;
	int padLock;
	int selection;

	bVar2 = false;
	padLock = Pad.m_debugPadLock;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar3 = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		uVar3 = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}

	bVar2 = false;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar4 = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		uVar4 = Pad.GetPadInputs()[padIndex].repeatButton;
	}

	if (uVar4 == 0) {
		return 0;
	}

	selection = GetArtiState(this)->currentSelection;
	if ((uVar4 & 8) != 0) {
		sVar1 = GetArtiState(this)->selections[selection];
		if (sVar1 != 0) {
			GetArtiState(this)->selections[selection] = sVar1 + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if (GetArtiState(this)->scrollOffset != 0) {
			GetArtiState(this)->scrollOffset = GetArtiState(this)->scrollOffset + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	} else if ((uVar4 & 4) != 0) {
		sVar1 = GetArtiState(this)->selections[selection];
		if (sVar1 < 7) {
			GetArtiState(this)->selections[selection] = sVar1 + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((int)GetArtiState(this)->scrollOffset + (int)sVar1 < 0x48) {
			GetArtiState(this)->scrollOffset = GetArtiState(this)->scrollOffset + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	}

	if ((uVar4 & 0xc) == 0) {
		if ((uVar3 & 0x20) != 0) {
			GetArtiState(this)->moveDirection = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x40) != 0) {
			GetArtiState(this)->moveDirection = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((uVar3 & 0x200) != 0) {
			GetArtiState(this)->closeRequested = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015fd54
 * PAL Size: 2308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiDraw()
{
	int hasSelectedArtifact = 0;
	int selectedArtifactId;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	short artiState = m_artiState->state;
	ArtiOpenAnim* entry = GetArtiOpenAnimList(this)->entries;
	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int drawIndex = 0;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;

	for (int i = 0; i < GetArtiOpenAnimList(this)->count; i++) {
		int tex = entry->tex;
		if (tex >= 0) {
			x = (float)entry->x;
			y = (float)entry->y;
			w = (float)entry->w;
			h = (float)entry->h;
			u = entry->u;
			v = entry->v;

			if (i == 0) {
				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));

				GXColor colors[4];
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

				w = entry->alpha * w;
				if (w > LoadFloat(kArtiZero)) {
					MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, LoadFloat(kArtiOne), LoadFloat(kArtiOne), LoadFloat(kArtiZero));
					x += w;
					u += w;
				}

				int wInt = entry->w;
				if (w > LoadFloat(kArtiZero) && w < (float)wInt) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					w = (float)(LoadDouble(kArtiOneDouble) / (double)entry->duration);
					w = w * wInt;
					MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, LoadFloat(kArtiOne), LoadFloat(kArtiOne), LoadFloat(kArtiZero));
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				float animAlpha = entry->alpha;
				int texId = tex;
				float itemAlpha = animAlpha;
				if (tex == 0x37) {
					int itemCount = caravanWork->m_artifacts[drawIndex + m_artiState->scrollOffset];
					if (itemCount > 0) {
					} else {
						texId = 0x34;
						itemAlpha = (float)(LoadDouble(kArtiHalfDouble) * (double)animAlpha);
					}

					if (texId == 0x37 && drawIndex == m_artiState->selections[0]) {
						v += h;
					}
					drawIndex++;
				}

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(texId));
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (u8)(LoadFloat(kArtiColorMax) * itemAlpha);
				GXSetChanMatColor(GX_COLOR0A0, color);
				float uvScale = entry->scale;
				MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, LoadFloat(kArtiZero));
			}
		}
		entry++;
	}

	CFont* listFont = GetArtiListFont(this);
	listFont->SetMargin(LoadFloat(kArtiOne));
	listFont->SetShadow(0);
	listFont->SetScale(LoadFloat(kArtiListFontScale));
	listFont->DrawInit();

	ArtiOpenAnimList* list = GetArtiOpenAnimList(this);
	for (int li = 0; li < list->count; li++) {
		entry = &list->entries[li];
		if (entry->tex == 0x37) {
			break;
		}
	}

	ArtiOpenAnim* textEntry = entry;
	for (int i = 0; i < 8; i++) {
		u8 alpha = (u8)(LoadFloat(kArtiColorMax) * textEntry->alpha);
		int menuIndex = i + m_artiState->scrollOffset;
		listFont->SetColor(CColor(0xFF, 0xFF, 0xFF, alpha).color);

		short itemCount = caravanWork->m_artifacts[menuIndex];
		const char* text;
		if (itemCount <= 0) {
			text = GetMenuStr(0x14);
		} else {
			text = Game.m_cFlatDataArr[1].TableStrings(0)[itemCount * 5 + 4];
			if (menuIndex == (int)m_artiState->selections[0] + (int)m_artiState->scrollOffset) {
				selectedArtifactId = itemCount;
				hasSelectedArtifact = 1;
			}
		}

		listFont->GetWidth(text);
		float posX = (float)(textEntry->x + 0x1c);
		float posY = (float)(textEntry->y + 0xb);
		listFont->SetPosX(posX);
		listFont->SetPosY(posY - LoadFloat(kArtiTextYOffset));
		listFont->Draw(text);
		textEntry++;
	}

	DrawInit();

	ArtiOpenAnim* iconEntry = entry;
	for (int i = 0; i < 8; i++) {
		short itemCount = caravanWork->m_artifacts[i + m_artiState->scrollOffset];
		if (itemCount > 0) {
			int iconY = (int)((float)(iconEntry->y + 6) - LoadFloat(kArtiOne));
			int iconX = (int)((float)(iconEntry->x + iconEntry->w - 0x10));
			DrawSingleIcon(itemCount, iconX, iconY, entry->alpha, 0, LoadFloat(kArtiZero));
		}
		iconEntry++;
	}

	if (artiState == 1) {
		entry = GetArtiOpenAnimList(this)->entries;
		float mark = static_cast<float>(CalcListPos(m_artiState->scrollOffset, 0x49, 0));
		if (mark > LoadFloat(kArtiZero)) {
			DrawListPosMark((float)entry->x, (float)entry->y, mark);
		}
	}

	if (artiState == 1) {
		ArtiOpenAnimList* cursorList = GetArtiOpenAnimList(this);
		for (int i = 0; i < cursorList->count; i++) {
			entry = &cursorList->entries[i];
			if (cursorList->entries[i].tex == 0x37) {
				break;
			}
		}

		entry += m_artiState->selections[0];
		int cursorY = (int)(float)((double)(entry->h - 0x20) * LoadDouble(kArtiHalfDouble) + (double)entry->y);
		int cursorX = (int)((float)(entry->x - 0x14) + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, LoadFloat(kArtiOne));
	}

	CFont* helpFont = GetArtiHelpFont(this);
	s8 helpAlpha = (s8)(LoadFloat(kArtiColorMax) * GetArtiOpenAnimList(this)->entries[0].alpha);
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		const char* text = GetMenuStr(0x14);
		CColor color(0xFF, 0xFF, 0xFF, helpAlpha);
		int x = (int)CalcCenteringPos(const_cast<char*>(text), helpFont);
		float helpY = LoadFloat(kArtiHelpY);
		DrawFont(x, (int)helpY, color.color, 10, const_cast<char*>(text), LoadFloat(kArtiOne),
		         LoadFloat(kArtiHelpScale));
	} else {
		CColor helpColor(0xFF, 0xFF, 0xFF, helpAlpha);
		int x = (int)(LoadFloat(kArtiHelpCenterX) - w * LoadFloat(kArtiHalf));
		float helpY = LoadFloat(kArtiHelpY);
		DrawHelpMessage(selectedArtifactId, helpFont, x, (int)helpY, helpColor.color, 10,
		                LoadFloat(kArtiOne), LoadFloat(kArtiHelpScale));
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160658
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiClose()
{
	ArtiOpenAnim* anim;
	int count;
	int frame;
	int finished;

	GetArtiState(this)->frame++;
	finished = 0;

	count = GetArtiOpenAnimList(this)->count;
	anim = GetArtiOpenAnimList(this)->entries;
	frame = GetArtiState(this)->frame;

	for (int i = 0; i < count; i++, anim++) {
		if (frame >= anim->startFrame) {
			if (anim->startFrame + anim->duration <= frame) {
				float zeroF = LoadFloat(kArtiZero);
				finished++;
				anim->alpha = zeroF;
				anim->dx = zeroF;
				anim->dy = zeroF;
			} else {
				anim->step++;
				double oneD = LoadDouble(kArtiOneDouble);
				anim->alpha = (float)-((oneD / (double)anim->duration) * (double)anim->step - oneD);
				if ((anim->flags & 2) == 0) {
					float ratio = (float)-((oneD / (double)anim->duration) * (double)anim->step - oneD);
					float dx = anim->targetX - (float)anim->x;
					float dy = anim->targetY - (float)anim->y;
					anim->dx = dx * ratio;
					anim->dy = dy * ratio;
				}
			}
		}
	}

	int result = 0;
	if (count == finished) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801607d4
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiCtrl()
{
	ArtiState* state = GetArtiState(this);
	int result;

	state->prevSelection = state->currentSelection;
	result = ArtiCtrlCur();
	if (result != 0) {
		ArtiInit1();
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80160828
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiOpen()
{
	ArtiOpenAnim* entry;
	int finished;
	int count;
	int frame;

	if (GetArtiState(this)->initialized == '\0') {
		ArtiInit();
	}

	GetArtiState(this)->frame = GetArtiState(this)->frame + 1;
	finished = 0;
	entry = GetArtiOpenAnimList(this)->entries;
	count = GetArtiOpenAnimList(this)->count;
	frame = (int)GetArtiState(this)->frame;

	for (int i = 0; i < count; i++, entry++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				float zero = LoadFloat(kArtiZero);
				finished++;
				entry->alpha = LoadFloat(kArtiOne);
				entry->dx = zero;
				entry->dy = zero;
			} else {
				entry->step++;
				double one = LoadDouble(kArtiOneDouble);
				entry->alpha = (float)((one / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float ratio = (float)((one / (double)entry->duration) * (double)entry->step);
					float dx = entry->targetX - (float)entry->x;
					float dy = entry->targetY - (float)entry->y;
					entry->dx = dx * ratio;
					entry->dy = dy * ratio;
				}
			}
		}
	}

	int result = 0;
	if (count == finished) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801609d8
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit1()
{
	float fVar1;
	int index;
	ArtiOpenAnim* entry;
	ArtiOpenAnimList* list;

	index = 0;
	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x2e;
	entry->startFrame = 2;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x44;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x44;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	fVar1 = LoadFloat(kArtiOne);
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = GetArtiOpenAnim(this, index);
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	list = GetArtiOpenAnimList(this);
	ArtiOpenAnim* p = list->entries;
	for (index = list->count; index > 0; index--, p++) {
		p->step = 0;
		p->alpha = fVar1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160c34
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit()
{
	int index;
	ArtiOpenAnim* entry;

	memset(GetArtiOpenAnimList(this), 0, sizeof(*GetArtiOpenAnimList(this)));
	{
		float one = LoadFloat(kArtiOne);
		ArtiOpenAnim* p = GetArtiOpenAnimList(this)->entries;
		for (int i = 0; i < 64; i++, p++) {
			p->scale = one;
		}
	}

	index = 0;
	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x2e;
	entry->x = 0x68;
	entry->y = 0x28;
	entry->w = 0x78;
	entry->h = 0x108;
	float titleAlpha = LoadFloat(kArtiInitX);
	float titleScale = LoadFloat(kArtiInitYOffset);
	float one = LoadFloat(kArtiOne);
	float zero = LoadFloat(kArtiZero);
	entry->u = titleAlpha;
	entry->v = titleScale;
	entry->scale = one;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x44;
	entry->x = 0x50;
	entry->y = 0xe;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->u = zero;
	entry->v = zero;
	entry->scale = one;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = GetArtiOpenAnim(this, index++);
	entry->tex = 0x44;
	entry->x = 0x55;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->y = 0x150 - entry->h;
	float rightScale = LoadFloat(kArtiInitScale);
	entry->u = zero;
	entry->v = zero;
	entry->scale = rightScale;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = GetArtiOpenAnim(this, index++);
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->x = 0x50;
	entry->y = 8;
	entry->w = 0x48;
	entry->h = 0x140;
	entry->u = zero;
	entry->v = zero;
	entry->startFrame = 0;
	entry->duration = 5;

	ArtiOpenAnim* entry0 = GetArtiOpenAnimList(this)->entries;
	for (int loopCount = 0; loopCount < 8; loopCount++) {
		entry = GetArtiOpenAnim(this, index++);
		entry->flags = 2;
		entry->tex = 0x37;
		entry->x = entry0->x + 0x24;
		entry->y = entry0->y + loopCount * 0x20;
		entry->w = 200;
		entry->h = 0x28;
		entry->u = zero;
		entry->v = zero;
		entry->startFrame = 7;
		entry->duration = 5;
	}

	GetArtiOpenAnimList(this)->count = index;
	GetArtiState(this)->selections[0] = 0;
	GetArtiState(this)->initialized = 1;
}
