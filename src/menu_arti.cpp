#include "ffcc/menu_arti.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern const double DOUBLE_80332fb0;
extern const double DOUBLE_80332fb8;
extern const double DOUBLE_80332fe0;
static const float FLOAT_80332fa8 = 0.0f;
extern const float FLOAT_80332fac;
extern const float FLOAT_80332fc0;
extern const float FLOAT_80332fc4;
extern const float FLOAT_80332fc8;
extern const float FLOAT_80332fcc;
extern const float FLOAT_80332fd0;
extern const float FLOAT_80332fd4;
extern const float FLOAT_80332fd8;
extern const float FLOAT_80332fe8;
extern const float FLOAT_80332fec;
extern const float FLOAT_80332ff0;

extern "C" {
extern const float kMenuArtiNegativeOne = -1.0f;
extern const float kMenuArtiDefaultScale = 1.2f;
extern const float kMenuArtiBoundsMax = 10000000000.0f;
extern const float kMenuArtiBoundsMin = -10000000000.0f;
extern const float kMenuArtiHalfTileOffset = 15.5f;
extern const float kMenuArtiTau = 6.2831855f;
extern const char s_MenuOptionMusic[] = "Music";
extern const char s_MenuOptionOn[] = "On";
extern const char s_MenuOptionOff[] = "Off";
extern const char s_MenuOptionStereo[] = "Stereo";
extern const char s_MenuOptionMin[] = "Min";
extern const char s_MenuOptionMax[] = "Max";
extern const char s_MenuOptionStrengthDe[] = {'S', 't', '\xe4', 'r', 'k', 'e', '\0', '\0'};
extern const char s_MenuOptionDefenceDe[] = "Abwehr";
extern const char s_MenuOptionMusicDe[] = "Musik";
extern const char s_MenuOptionOnDe[] = "AN";
extern const char s_MenuOptionOffDe[] = "AUS";
extern const char s_MenuOptionStereoDe[] = "STEREO";
}

namespace {
struct ArtiState {
	unsigned char pad_0000[0xB];
	char initialized;
	unsigned char pad_000C;
	unsigned char closeRequested;
	unsigned char pad_000E[2];
	short state;
	unsigned char pad_0012[0x0C];
	short moveDirection;
	unsigned char pad_0020[2];
	short frame;
	unsigned char pad_0024[2];
	short selections[5];
	short currentSelection;
	short prevSelection;
	short scrollOffset;
};

struct ArtiOpenAnim {
	short x;
	short y;
	short w;
	short h;
	float u;
	float v;
	float alpha;
	float scale;
	int unk;
	int tex;
	int step;
	int startFrame;
	int duration;
	unsigned int flags;
	float dx;
	float dy;
	float targetX;
	float targetY;
};

struct ArtiOpenAnimList {
	short count;
	unsigned char pad_0002[6];
	ArtiOpenAnim entries[64];
};

STATIC_ASSERT(offsetof(CMenuPcs, m_artiState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_artiList) == 0x850);
STATIC_ASSERT(offsetof(ArtiState, initialized) == 0xB);
STATIC_ASSERT(offsetof(ArtiState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(ArtiState, state) == 0x10);
STATIC_ASSERT(offsetof(ArtiState, moveDirection) == 0x1E);
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

static inline ArtiState* GetArtiStateStruct(CMenuPcs* menu)
{
	return reinterpret_cast<ArtiState*>(menu->m_artiState);
}

static inline s16* GetArtiState(CMenuPcs* menu)
{
	return menu->m_artiState;
}

static inline s16* GetArtiList(CMenuPcs* menu)
{
	return menu->m_artiList;
}

static inline ArtiOpenAnimList* GetArtiOpenAnimList(CMenuPcs* menu)
{
	return reinterpret_cast<ArtiOpenAnimList*>(menu->m_artiList);
}

static inline ArtiOpenAnim* GetArtiOpenAnim(CMenuPcs* menu, int index)
{
	return reinterpret_cast<ArtiOpenAnim*>((unsigned char*)GetArtiList(menu) + 8 + index * sizeof(ArtiOpenAnim));
}

static inline int GetArtiStateBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(GetArtiState(menu));
}

static inline int GetArtiListBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(GetArtiList(menu));
}

static inline CFont* GetArtiListFont(CMenuPcs* menu)
{
	return menu->m_fonts[1];
}

static inline CFont* GetArtiHelpFont(CMenuPcs* menu)
{
	return menu->m_fonts[0];
}
} // namespace

struct ArtiFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct ArtiFlatData
{
	char pad0[0x6C];
	ArtiFlatTableEntry table[8];
};
static inline double IntToF64(unsigned int value)
{
	unsigned long long bits = ((unsigned long long)0x43300000 << 32) | (unsigned long long)(value ^ 0x80000000);
	return (double)bits - DOUBLE_80332fe0;
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
	int iVar5;
	int iVar6;
	int padLock;
	int selection;

	bVar2 = false;
	padLock = Pad._452_4_;
	if ((padLock != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar3 = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		uVar3 = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}

	bVar2 = false;
	if ((padLock != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar4 = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		uVar4 = Pad.GetPadInputs()[padIndex].repeatButton;
	}

	if (uVar4 == 0) {
		return 0;
	}

	iVar5 = GetArtiStateBase(this);
	selection = *(short*)(iVar5 + 0x30);
	if ((uVar4 & 8) != 0) {
		iVar6 = iVar5 + selection * 2;
		sVar1 = *(short*)(iVar6 + 0x26);
		if (sVar1 != 0) {
			*(short*)(iVar6 + 0x26) = sVar1 + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if (*(short*)(iVar5 + 0x34) != 0) {
			*(short*)(iVar5 + 0x34) = *(short*)(iVar5 + 0x34) + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	} else if ((uVar4 & 4) != 0) {
		iVar6 = iVar5 + selection * 2;
		sVar1 = *(short*)(iVar6 + 0x26);
		if (sVar1 < 7) {
			*(short*)(iVar6 + 0x26) = sVar1 + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((int)*(short*)(iVar5 + 0x34) + (int)sVar1 < 0x48) {
			*(short*)(iVar5 + 0x34) = *(short*)(iVar5 + 0x34) + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	}

	if ((uVar4 & 0xc) == 0) {
		if ((uVar3 & 0x20) != 0) {
			*(short*)(GetArtiStateBase(this) + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x40) != 0) {
			*(short*)(GetArtiStateBase(this) + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((uVar3 & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((uVar3 & 0x200) != 0) {
			*(char*)(GetArtiStateBase(this) + 0xd) = 1;
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

	u32 scriptFood = Game.m_scriptFoodBase[0];
	short state = *(short*)(GetArtiStateBase(this) + 0x10);
	short* entry = (short*)(GetArtiListBase(this) + 8);
	int drawIndex = 0;
	float helpWidth;

	for (int i = 0; i < *GetArtiList(this); i++) {
		int tex = *(int*)(entry + 0xe);
		if (tex >= 0) {
			float x = (float)entry[0];
			float y = (float)entry[1];
			float w = (float)entry[2];
			float h = (float)entry[3];
			float u = *(float*)(entry + 4);
			float v = *(float*)(entry + 6);
			helpWidth = w;

			if (i == 0) {
				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

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

				float fillW = *(float*)(entry + 8) * w;
				if (fillW > 0.0f) {
					MenuPcs.DrawRect(0, x, y, fillW, h, u, v, colors, 1.0f, 1.0f, 0.0f);
					x += fillW;
					u += fillW;
				}

				if (fillW > 0.0f && fillW < (float)entry[2]) {
					colors[0].a = 0;
					colors[1].a = 0;
					colors[2].a = 0;
					colors[3].a = 0;
					float remainW = (float)(DOUBLE_80332fb0 / (double)*(int*)(entry + 0x14)) * (float)entry[2];
					MenuPcs.DrawRect(0, x, y, remainW, h, u, v, colors, 1.0f, 1.0f, 0.0f);
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				float itemAlpha = *(float*)(entry + 8);
				if (tex == 0x37) {
					short itemCount = *(short*)(scriptFood + (drawIndex + *(short*)(GetArtiStateBase(this) + 0x34)) * 2 + 0x136);
					if (itemCount < 1) {
						tex = 0x34;
						itemAlpha = (float)(DOUBLE_80332fb8 * (double)itemAlpha);
					}

					if (tex == 0x37 && drawIndex == *(short*)(GetArtiStateBase(this) + 0x26)) {
						v += h;
					}
					drawIndex++;
				}

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (u8)(FLOAT_80332fc0 * itemAlpha);
				GXSetChanMatColor(GX_COLOR0A0, color);
				float uvScale = *(float*)(entry + 10);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}
		entry += 0x20;
	}

	CFont* listFont = GetArtiListFont(this);
	listFont->SetMargin(1.0f);
	listFont->SetShadow(0);
	listFont->SetScale(FLOAT_80332fc4);
	listFont->DrawInit();

	short* listStart = (short*)(GetArtiListBase(this) + 8);
	int listCount = *GetArtiList(this);
	for (int i = 0; i < listCount; i++) {
		if (*(int*)(listStart + 0xe) == 0x37) {
			break;
		}
		listStart += 0x20;
	}

	short* textEntry = listStart;
	const ArtiFlatData* flatData = reinterpret_cast<const ArtiFlatData*>(&Game.m_cFlatDataArr[1]);
	for (int i = 0; i < 8; i++) {
		u8 alpha = (u8)(255.0f * *(float*)(textEntry + 8));
		CColor color(0xFF, 0xFF, 0xFF, alpha);
		listFont->SetColor(color.color);

		int menuIndex = i + *(short*)(GetArtiStateBase(this) + 0x34);
		short itemCount = *(short*)(scriptFood + menuIndex * 2 + 0x136);
		const char* text;
		if (itemCount < 1) {
			text = GetMenuStr(0x14);
		} else {
			text = flatData->table[0].strings[itemCount * 5 + 4];
			if (menuIndex == (int)*(short*)(GetArtiStateBase(this) + 0x26) + (int)*(short*)(GetArtiStateBase(this) + 0x34)) {
				hasSelectedArtifact = 1;
				selectedArtifactId = itemCount;
			}
		}

		listFont->GetWidth(text);
		float posX = (float)(textEntry[0] + 0x1c);
		float posY = (float)(textEntry[1] + 0xb);
		listFont->SetPosX(posX);
		listFont->SetPosY(posY - FLOAT_80332fc8);
		listFont->Draw(text);
		textEntry += 0x20;
	}

	DrawInit();

	short* iconEntry = listStart;
	for (int i = 0; i < 8; i++) {
		short itemCount = *(short*)(scriptFood + (i + *(short*)(GetArtiStateBase(this) + 0x34)) * 2 + 0x136);
		if (itemCount > 0) {
			int iconY = (int)((float)(iconEntry[1] + 6) - FLOAT_80332fac);
			int iconX = (int)((float)(iconEntry[0] + iconEntry[2] - 0x10));
			DrawSingleIcon(itemCount, iconX, iconY, *(float*)(iconEntry + 8), 0, 0.0f);
		}
		iconEntry += 0x20;
	}

	if (state == 1) {
		int menuData = GetArtiListBase(this);
		float mark = static_cast<float>(CalcListPos(*(short*)(GetArtiStateBase(this) + 0x34), 0x49, 0));
		if (mark > 0.0f) {
			DrawListPosMark((float)*(short*)(menuData + 8), (float)*(short*)(menuData + 10), mark);
		}
	}

	if (state == 1) {
		short* cursorBase = (short*)(GetArtiListBase(this) + 8);
		int cursorCount = *GetArtiList(this);
		for (int i = 0; i < cursorCount; i++) {
			if (*(int*)(cursorBase + 0xe) == 0x37) {
				break;
			}
			cursorBase += 0x20;
		}

		cursorBase += *(short*)(GetArtiStateBase(this) + 0x26) * 0x20;
		int cursorY = (int)(float)((double)(cursorBase[3] - 0x20) * DOUBLE_80332fb8 + (double)cursorBase[1]);
		int cursorX = (int)((float)(cursorBase[0] - 0x14) + (float)(System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, FLOAT_80332fac);
	}

	CFont* helpFont = GetArtiHelpFont(this);
	u8 helpAlpha = (u8)(FLOAT_80332fc0 * *(float*)(GetArtiListBase(this) + 0x18));
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		const char* text = GetMenuStr(0x14);
		CColor color(0xFF, 0xFF, 0xFF, helpAlpha);
		int x = (int)CalcCenteringPos(const_cast<char*>(text), helpFont);
		DrawFont(x, (int)FLOAT_80332fcc, color.color, 10, const_cast<char*>(text), FLOAT_80332fac,
		         FLOAT_80332fd0);
	} else {
		CColor helpColor(0xFF, 0xFF, 0xFF, helpAlpha);
		int x = (int)-(helpWidth * FLOAT_80332fd8 - FLOAT_80332fd4);
		DrawHelpMessage(selectedArtifactId, helpFont, x, (int)FLOAT_80332fcc, helpColor.color, 10,
		                FLOAT_80332fac, FLOAT_80332fd0);
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
	int count;
	int finished;
	int frame;

	GetArtiState(this)[0x11]++;
	finished = 0;

	count = GetArtiList(this)[0];
	ArtiOpenAnim* anim = (ArtiOpenAnim*)((u8*)GetArtiList(this) + 8);
	frame = GetArtiState(this)[0x11];

	for (int i = 0; i < count; i++, anim++) {
		float zeroF = FLOAT_80332fa8;
		if (frame >= anim->startFrame) {
			if (anim->startFrame + anim->duration <= frame) {
				finished++;
				anim->alpha = FLOAT_80332fa8;
				anim->dx = zeroF;
				anim->dy = zeroF;
			} else {
				anim->step++;
				double oneD = DOUBLE_80332fb0;
				anim->alpha = (float)-((DOUBLE_80332fb0 / (double)anim->duration) * (double)anim->step - DOUBLE_80332fb0);
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
	ArtiState* state = GetArtiStateStruct(this);
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
	int count;
	int finished;
	int frame;

	if (*(char*)(GetArtiStateBase(this) + 0xb) == '\0') {
		ArtiInit();
	}

	*(short*)(GetArtiStateBase(this) + 0x22) = *(short*)(GetArtiStateBase(this) + 0x22) + 1;
	finished = 0;
	count = *GetArtiList(this);
	ArtiOpenAnim* entry = (ArtiOpenAnim*)((u8*)GetArtiList(this) + 8);
	frame = (int)*(short*)(GetArtiStateBase(this) + 0x22);

	for (int i = 0; i < count; i++, entry++) {
		float zero = FLOAT_80332fa8;
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finished++;
				entry->alpha = FLOAT_80332fac;
				entry->dx = zero;
				entry->dy = zero;
			} else {
				entry->step++;
				double one = DOUBLE_80332fb0;
				entry->alpha = (float)((DOUBLE_80332fb0 / (double)entry->duration) * (double)entry->step);
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
	unsigned int uVar4;
	unsigned int uVar5;
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
	fVar1 = FLOAT_80332fac;
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
	uVar4 = (unsigned int)list->count;
	entry = list->entries;
	if (0 < (int)uVar4) {
		uVar5 = uVar4 >> 3;
		if (uVar5 != 0) {
			do {
				entry[0].step = 0;
				entry[0].alpha = fVar1;
				entry[1].step = 0;
				entry[1].alpha = fVar1;
				entry[2].step = 0;
				entry[2].alpha = fVar1;
				entry[3].step = 0;
				entry[3].alpha = fVar1;
				entry[4].step = 0;
				entry[4].alpha = fVar1;
				entry[5].step = 0;
				entry[5].alpha = fVar1;
				entry[6].step = 0;
				entry[6].alpha = fVar1;
				entry[7].step = 0;
				entry[7].alpha = fVar1;
				entry += 8;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
			uVar4 = uVar4 & 7;
			if (uVar4 == 0) {
				return;
			}
		}
		do {
			entry->step = 0;
			entry->alpha = fVar1;
			entry++;
			uVar4 = uVar4 - 1;
		} while (uVar4 != 0);
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
	short sVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	int iVar5;
	int sVar6;
	short sVar7;
	short* psVar8;
	int iVar9;
	int iVar10;
	int iVar11;

	memset(GetArtiOpenAnimList(this), 0, sizeof(*GetArtiOpenAnimList(this)));
	fVar2 = FLOAT_80332fac;
	iVar5 = GetArtiListBase(this) + 8;
	iVar10 = 8;
	do {
		*(float*)(iVar5 + 0x14) = fVar2;
		*(float*)(iVar5 + 0x54) = fVar2;
		*(float*)(iVar5 + 0x94) = fVar2;
		*(float*)(iVar5 + 0xd4) = fVar2;
		*(float*)(iVar5 + 0x114) = fVar2;
		*(float*)(iVar5 + 0x154) = fVar2;
		*(float*)(iVar5 + 0x194) = fVar2;
		*(float*)(iVar5 + 0x1d4) = fVar2;
		iVar5 = iVar5 + 0x200;
		iVar10 = iVar10 - 1;
	} while (iVar10 != 0);

	iVar5 = GetArtiListBase(this);
	*(int*)(iVar5 + 0x24) = 0x2e;
	*(short*)(iVar5 + 8) = 0x68;
	*(short*)(iVar5 + 10) = 0x28;
	*(short*)(iVar5 + 0xc) = 0x78;
	fVar2 = FLOAT_80332fe8;
	*(short*)(iVar5 + 0xe) = 0x108;
	fVar4 = FLOAT_80332fec;
	*(float*)(iVar5 + 0x10) = fVar2;
	fVar3 = FLOAT_80332fac;
	*(float*)(iVar5 + 0x14) = fVar4;
	fVar2 = FLOAT_80332fa8;
	sVar6 = 0;
	*(float*)(iVar5 + 0x1c) = fVar3;
	fVar4 = FLOAT_80332ff0;
	sVar7 = 4;
	*(int*)(iVar5 + 0x2c) = 5;
	*(int*)(iVar5 + 0x30) = 5;
	iVar5 = 0x100;
	iVar10 = GetArtiListBase(this);
	*(int*)(iVar10 + 100) = 0x44;
	*(short*)(iVar10 + 0x48) = 0x50;
	*(short*)(iVar10 + 0x4a) = 0xe;
	*(short*)(iVar10 + 0x4c) = 0x30;
	*(short*)(iVar10 + 0x4e) = 0x30;
	*(float*)(iVar10 + 0x50) = fVar2;
	*(float*)(iVar10 + 0x54) = fVar2;
	*(float*)(iVar10 + 0x5c) = fVar3;
	*(int*)(iVar10 + 0x6c) = 0;
	*(int*)(iVar10 + 0x70) = 5;

	iVar10 = GetArtiListBase(this);
	*(int*)(iVar10 + 0xa4) = 0x44;
	*(short*)(iVar10 + 0x88) = 0x55;
	*(short*)(iVar10 + 0x8c) = 0x30;
	*(short*)(iVar10 + 0x8e) = 0x30;
	*(short*)(iVar10 + 0x8a) = 0x150 - *(short*)(iVar10 + 0x8e);
	*(float*)(iVar10 + 0x90) = fVar2;
	*(float*)(iVar10 + 0x94) = fVar2;
	*(float*)(iVar10 + 0x9c) = fVar4;
	*(int*)(iVar10 + 0xac) = 0;
	*(int*)(iVar10 + 0xb0) = 5;

	iVar10 = GetArtiListBase(this);
	*(int*)(iVar10 + 0xf4) = 2;
	*(int*)(iVar10 + 0xe4) = 0x2e;
	*(short*)(iVar10 + 200) = 0x50;
	*(short*)(iVar10 + 0xca) = 8;
	*(short*)(iVar10 + 0xcc) = 0x48;
	*(short*)(iVar10 + 0xce) = 0x140;
	*(float*)(iVar10 + 0xd0) = fVar2;
	*(float*)(iVar10 + 0xd4) = fVar2;
	*(int*)(iVar10 + 0xec) = 0;
	*(int*)(iVar10 + 0xf0) = 5;

	iVar10 = GetArtiListBase(this);
	iVar11 = 4;
	do {
		psVar8 = (short*)(GetArtiListBase(this) + iVar5 + 8);
		*(int*)(psVar8 + 0x16) = 2;
		*(int*)(psVar8 + 0xe) = 0x37;
		sVar7 = sVar7 + 2;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar1 = sVar6 + 0x20;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar6;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		reinterpret_cast<ArtiOpenAnim*>(psVar8)->startFrame = 7;
		reinterpret_cast<ArtiOpenAnim*>(psVar8)->duration = 5;
		iVar9 = iVar5 + 0x48;
		iVar5 = iVar5 + 0x80;
		psVar8 = (short*)(GetArtiListBase(this) + iVar9);
		*(int*)(psVar8 + 0x16) = 2;
		*(int*)(psVar8 + 0xe) = 0x37;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar6 = sVar6 + 0x40;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar1;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		reinterpret_cast<ArtiOpenAnim*>(psVar8)->startFrame = 7;
		reinterpret_cast<ArtiOpenAnim*>(psVar8)->duration = 5;
		iVar11 = iVar11 - 1;
	} while (iVar11 != 0);

	*GetArtiList(this) = sVar7;
	*(short*)(GetArtiStateBase(this) + 0x26) = 0;
	*(char*)(GetArtiStateBase(this) + 0xb) = 1;
}
