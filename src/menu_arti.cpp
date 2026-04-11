#include "ffcc/menu_arti.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

static const double DOUBLE_80332fb0 = 1.0;
static const double DOUBLE_80332fb8 = 0.5;
static const double DOUBLE_80332fe0 = 4503601774854144.0;
static const float FLOAT_80332fa8 = 0.0f;
static const float FLOAT_80332fac = 1.0f;
static const float FLOAT_80332fc0 = 255.0f;
static const float FLOAT_80332fc4 = 0.8999999761581421f;
static const float FLOAT_80332fc8 = 4.0f;
static const float FLOAT_80332fcc = 352.0f;
static const float FLOAT_80332fd0 = 3.0f;
static const float FLOAT_80332fd4 = 320.0f;
static const float FLOAT_80332fd8 = 0.5f;
static const float FLOAT_80332fe8 = 128.0f;
static const float FLOAT_80332fec = 8.0f;
static const float FLOAT_80332ff0 = 0.75f;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" float CalcListPos__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void DrawListPosMark__8CMenuPcsFfff(CMenuPcs*, float, float, float);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int, CFont*, int, int, GXColor, int, float, float);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);


namespace {
struct MenuArtiMembers {
	unsigned char pad_0000[0xF8];
	CFont* m_helpFont;
	unsigned char pad_00FC[0x0C];
	CFont* m_listFont;
	unsigned char pad_010C[0x720];
	s16* m_artiState;
	unsigned char pad_0830[0x20];
	s16* m_artiList;
};

STATIC_ASSERT(offsetof(MenuArtiMembers, m_helpFont) == 0xF8);
STATIC_ASSERT(offsetof(MenuArtiMembers, m_listFont) == 0x108);
STATIC_ASSERT(offsetof(MenuArtiMembers, m_artiState) == 0x82C);
STATIC_ASSERT(offsetof(MenuArtiMembers, m_artiList) == 0x850);

static inline MenuArtiMembers& GetMenuArtiMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<MenuArtiMembers*>(menu);
}

static inline s16* GetArtiState(CMenuPcs* menu)
{
	return GetMenuArtiMembers(menu).m_artiState;
}

static inline s16* GetArtiList(CMenuPcs* menu)
{
	return GetMenuArtiMembers(menu).m_artiList;
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
	return GetMenuArtiMembers(menu).m_listFont;
}

static inline CFont* GetArtiHelpFont(CMenuPcs* menu)
{
	return GetMenuArtiMembers(menu).m_helpFont;
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

struct ArtiOpenAnim {
	s16 x;
	s16 y;
	s16 w;
	s16 h;
	float u;
	float v;
	float alpha;
	float scale;
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

static inline double IntToF64(unsigned int value)
{
	unsigned long long bits = ((unsigned long long)0x43300000 << 32) | (unsigned long long)(value ^ 0x80000000);
	return (double)bits - DOUBLE_80332fe0;
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
	short sVar6;
	short sVar7;
	short* psVar8;
	int iVar9;
	int iVar10;
	int iVar11;

	memset((void*)GetArtiList(this), 0, 0x1008);
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
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		sVar7 = sVar7 + 2;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar1 = sVar6 + 0x20;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar6;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		psVar8[0x15] = 5;
		iVar9 = iVar5 + 0x48;
		iVar5 = iVar5 + 0x80;
		psVar8 = (short*)(GetArtiListBase(this) + iVar9);
		psVar8[0x16] = 0;
		psVar8[0x17] = 2;
		psVar8[0xe] = 0;
		psVar8[0xf] = 0x37;
		*psVar8 = *(short*)(iVar10 + 8) + 0x24;
		sVar6 = sVar6 + 0x40;
		psVar8[1] = *(short*)(iVar10 + 10) + sVar1;
		psVar8[2] = 200;
		psVar8[3] = 0x28;
		*(float*)(psVar8 + 4) = fVar2;
		*(float*)(psVar8 + 6) = fVar2;
		psVar8[0x12] = 0;
		psVar8[0x13] = 7;
		psVar8[0x14] = 0;
		psVar8[0x15] = 5;
		iVar11 = iVar11 - 1;
	} while (iVar11 != 0);

	*GetArtiList(this) = sVar7;
	*(short*)(GetArtiStateBase(this) + 0x26) = 0;
	*(char*)(GetArtiStateBase(this) + 0xb) = 1;
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
	float alpha;
	ArtiOpenAnim* anims;
	unsigned int count;
	unsigned int blocks;

	anims = reinterpret_cast<ArtiOpenAnim*>(GetArtiList(this) + 4);
	anims[0].tex = 0x2e;
	anims[0].startFrame = 2;
	anims[0].duration = 5;
	anims[1].tex = 0x44;
	anims[1].startFrame = 7;
	anims[1].duration = 5;
	anims[2].tex = 0x44;
	anims[2].startFrame = 7;
	anims[2].duration = 5;
	anims[3].flags = 2;
	anims[3].tex = 0x2e;
	anims[3].startFrame = 7;
	anims[3].duration = 5;
	anims[4].flags = 2;
	anims[4].tex = 0x37;
	anims[4].startFrame = 0;
	anims[4].duration = 5;
	anims[5].flags = 2;
	anims[5].tex = 0x37;
	anims[5].startFrame = 0;
	anims[5].duration = 5;
	anims[6].flags = 2;
	anims[6].tex = 0x37;
	anims[6].startFrame = 0;
	anims[6].duration = 5;
	anims[7].flags = 2;
	anims[7].tex = 0x37;
	alpha = FLOAT_80332fac;
	anims[7].startFrame = 0;
	anims[7].duration = 5;
	anims[8].flags = 2;
	anims[8].tex = 0x37;
	anims[8].startFrame = 0;
	anims[8].duration = 5;
	anims[9].flags = 2;
	anims[9].tex = 0x37;
	anims[9].startFrame = 0;
	anims[9].duration = 5;
	anims[10].flags = 2;
	anims[10].tex = 0x37;
	anims[10].startFrame = 0;
	anims[10].duration = 5;
	anims[11].flags = 2;
	anims[11].tex = 0x37;
	anims[11].startFrame = 0;
	anims[11].duration = 5;

	count = (unsigned int)*GetArtiList(this);
	if (0 < (int)count) {
		blocks = count >> 3;
		if (blocks != 0) {
			do {
				anims[0].step = 0;
				anims[0].alpha = alpha;
				anims[1].step = 0;
				anims[1].alpha = alpha;
				anims[2].step = 0;
				anims[2].alpha = alpha;
				anims[3].step = 0;
				anims[3].alpha = alpha;
				anims[4].step = 0;
				anims[4].alpha = alpha;
				anims[5].step = 0;
				anims[5].alpha = alpha;
				anims[6].step = 0;
				anims[6].alpha = alpha;
				anims[7].step = 0;
				anims[7].alpha = alpha;
				anims += 8;
				blocks--;
			} while (blocks != 0);
			count &= 7;
			if (count == 0) {
				return;
			}
		}
		do {
			anims->step = 0;
			anims->alpha = alpha;
			anims++;
			count--;
		} while (count != 0);
	}
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
unsigned int CMenuPcs::ArtiOpen()
{
	float ratio;
	double dVar2;
	double dVar3;
	short* entry;
	int finished;
	unsigned int count;
	int frame;
	unsigned int remaining;

	if (*(char*)(GetArtiStateBase(this) + 0xb) == '\0') {
		ArtiInit();
	}

	finished = 0;
	*(short*)(GetArtiStateBase(this) + 0x22) = *(short*)(GetArtiStateBase(this) + 0x22) + 1;
	count = (unsigned int)*GetArtiList(this);
	entry = GetArtiList(this) + 4;
	frame = (int)*(short*)(GetArtiStateBase(this) + 0x22);
	remaining = count;
	if (0 < (int)count) {
		do {
			ratio = FLOAT_80332fa8;
			if (*(int*)(entry + 0x12) <= frame) {
				if (frame < *(int*)(entry + 0x12) + *(int*)(entry + 0x14)) {
					*(int*)(entry + 0x10) = *(int*)(entry + 0x10) + 1;
					dVar2 = DOUBLE_80332fb0;
					*(float*)(entry + 8) =
					    (float)((DOUBLE_80332fb0 / (double)*(int*)(entry + 0x14)) * (double)*(int*)(entry + 0x10));
					if ((*(unsigned int*)(entry + 0x16) & 2) == 0) {
						ratio = (float)((dVar2 / (double)*(int*)(entry + 0x14)) * (double)*(int*)(entry + 0x10));
						*(float*)(entry + 0x18) = (*(float*)(entry + 0x1c) - (float)*entry) * ratio;
						*(float*)(entry + 0x1a) = (*(float*)(entry + 0x1e) - (float)entry[1]) * ratio;
					}
				} else {
					finished = finished + 1;
					*(float*)(entry + 8) = FLOAT_80332fac;
					*(float*)(entry + 0x18) = ratio;
					*(float*)(entry + 0x1a) = ratio;
				}
			}
			entry = entry + 0x20;
			remaining = remaining - 1;
		} while (remaining != 0);
	}

	return (unsigned int)(count == finished);
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
	int result;

	*(short*)(GetArtiStateBase(this) + 0x32) = *(short*)(GetArtiStateBase(this) + 0x30);
	result = ArtiCtrlCur();
	if (result != 0) {
		ArtiInit1();
	}

	return result;
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
bool CMenuPcs::ArtiClose()
{
	int finished = 0;
	GetArtiState(this)[0x11]++;

	int count = GetArtiList(this)[0];
	ArtiOpenAnim* anim = (ArtiOpenAnim*)((u8*)GetArtiList(this) + 8);
	int frame = GetArtiState(this)[0x11];

	for (int i = 0; i < count; i++, anim++) {
		float zeroF = FLOAT_80332fa8;
		if (anim->startFrame <= frame) {
			if (!(frame < anim->startFrame + anim->duration)) {
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
					anim->dx = (anim->targetX - (float)anim->x) * ratio;
					anim->dy = (anim->targetY - (float)anim->y) * ratio;
				}
			}
		}
	}

	return count == finished;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiDraw()
{
	bool hasSelectedArtifact = false;
	int selectedArtifactId = -1;
	u32 scriptFood = Game.m_scriptFoodBase[0];

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	short state = *(short*)(GetArtiStateBase(this) + 0x10);
	short* entry = (short*)(GetArtiListBase(this) + 8);
	int count = *GetArtiList(this);
	int drawIndex = 0;

	for (int i = 0; i < count; i++) {
		int tex = *(int*)(entry + 0xe);
		if (tex >= 0) {
			float x = (float)entry[0];
			float y = (float)entry[1];
			float w = (float)entry[2];
			float h = (float)entry[3];
			float u = *(float*)(entry + 4);
			float v = *(float*)(entry + 6);
			float alpha = *(float*)(entry + 8);
			float uvScale = *(float*)(entry + 10);

			if (i == 0) {
				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 1);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);

				GXColor colors[4] = {
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
					{0xFF, 0xFF, 0xFF, 0xFF},
				};
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				float fillW = alpha * w;
				if (fillW > 0.0f) {
					DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						this, 0, x, y, fillW, h, u, v, colors, 1.0f, 1.0f, 0.0f);
					x += fillW;
					u += fillW;
				}

				if (fillW > 0.0f && fillW < w) {
					GXColor fadeColors[4] = {
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
						{0xFF, 0xFF, 0xFF, 0x00},
					};
					float remainW = (48.0f / (float)*(int*)(entry + 0x14)) * w;
					DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						this, 0, x, y, remainW, h, u, v, fadeColors, 1.0f, 1.0f, 0.0f);
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
			} else {
				float itemAlpha = alpha;
				if (tex == 0x37) {
					short itemCount = *(short*)(scriptFood + (drawIndex + *(short*)(GetArtiStateBase(this) + 0x34)) * 2 + 0x136);
					if (itemCount < 1) {
						tex = 0x34;
						itemAlpha *= 0.5f;
					}

					if (tex == 0x37 && drawIndex == *(short*)(GetArtiStateBase(this) + 0x26)) {
						v += h;
					}
					drawIndex++;
				}

				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
				GXColor color = {0xFF, 0xFF, 0xFF, (u8)(255.0f * itemAlpha)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
			}
		}
		entry += 0x20;
	}

	CFont* listFont = GetArtiListFont(this);
	listFont->SetMargin(0.0f);
	listFont->SetShadow(0);
	listFont->SetScale(0.875f);
	listFont->DrawInit();

	short* listStart = (short*)(GetArtiListBase(this) + 8);
	int listCount = *GetArtiList(this);
	for (int i = 0; i < listCount; i++) {
		if (*(int*)(listStart + 0xe) == 0x37) {
			break;
		}
		listStart += 0x20;
	}

	const ArtiFlatData* flatData = reinterpret_cast<const ArtiFlatData*>(&Game.m_cFlatDataArr[1]);
	for (int i = 0; i < 8; i++) {
		u8 alpha = (u8)(255.0f * *(float*)(listStart + 8));
		GXColor color = {0xFF, 0xFF, 0xFF, alpha};
		listFont->SetColor(color);

		int menuIndex = i + *(short*)(GetArtiStateBase(this) + 0x34);
		short itemCount = *(short*)(scriptFood + menuIndex * 2 + 0x136);
		const char* text;
		if (itemCount < 1) {
			text = GetMenuStr__8CMenuPcsFi(this, 0x14);
		} else {
			text = flatData->table[0].strings[itemCount * 5 + 4];
			if (menuIndex == (int)*(short*)(GetArtiStateBase(this) + 0x26) + (int)*(short*)(GetArtiStateBase(this) + 0x34)) {
				hasSelectedArtifact = true;
				selectedArtifactId = itemCount;
			}
		}

		listFont->GetWidth(text);
		listFont->SetPosX((float)(listStart[0] + 0x1c));
		listFont->SetPosY((float)(listStart[1] + 0xb) - 5.0f);
		listFont->Draw(text);
		listStart += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);

	listStart = (short*)(GetArtiListBase(this) + 8);
	listCount = *GetArtiList(this);
	for (int i = 0; i < listCount; i++) {
		if (*(int*)(listStart + 0xe) == 0x37) {
			break;
		}
		listStart += 0x20;
	}

	for (int i = 0; i < 8; i++) {
		short itemCount = *(short*)(scriptFood + (i + *(short*)(GetArtiStateBase(this) + 0x34)) * 2 + 0x136);
		if (itemCount > 0) {
			int iconY = (int)((float)listStart[1] + 6.0f - 1.0f);
			int iconX = (int)((float)(listStart[0] + listStart[2] - 0x10));
			DrawSingleIcon__8CMenuPcsFiiifif(this, itemCount, iconX, iconY, *(float*)(listStart + 8), 0, 0.0f);
		}
		listStart += 0x20;
	}

	if (state == 1) {
		int menuData = GetArtiListBase(this);
		float mark = CalcListPos__8CMenuPcsFiii(this, *(short*)(GetArtiStateBase(this) + 0x34), 0x49, 0);
		if (mark > 0.0f) {
			DrawListPosMark__8CMenuPcsFfff(this, (float)*(short*)(menuData + 8), (float)*(short*)(menuData + 10), mark);
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
		int cursorY = (int)(((float)(cursorBase[3] - 0x20) * 0.5f) + (float)cursorBase[1]);
		int cursorX = (int)((float)(cursorBase[0] - 0x14) + (float)(System.m_frameCounter & 7));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, 1.0f);
	}

	CFont* helpFont = GetArtiHelpFont(this);
	u8 helpAlpha = (u8)(FLOAT_80332fc0 * *(float*)(GetArtiListBase(this) + 0x18));
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		const char* text = GetMenuStr__8CMenuPcsFi(this, 0x14);
		GXColor color = {0xFF, 0xFF, 0xFF, helpAlpha};
		helpFont->SetColor(color);
		helpFont->SetPosX(0.0f);
		helpFont->SetPosY(FLOAT_80332fcc);
		helpFont->Draw(text);
	} else {
		GXColor helpColor = {0xFF, 0xFF, 0xFF, helpAlpha};
		DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, selectedArtifactId, helpFont, 0, -20, helpColor, 0, 1.0f, 0.0f);
	}
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
	short sVar1;
	bool bVar2;
	unsigned short uVar3;
	unsigned short uVar4;
	int iVar5;
	int iVar6;

	bVar2 = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar3 = 0;
	} else {
		uVar3 = Pad._8_2_;
	}

	bVar2 = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		bVar2 = true;
	}
	if (bVar2) {
		uVar4 = 0;
	} else {
		uVar4 = *(unsigned short*)((char*)&Pad + 0x20);
	}

	if (uVar4 == 0) {
		return 0;
	}

	iVar5 = GetArtiStateBase(this);
	if ((uVar4 & 8) == 0) {
		if ((uVar4 & 4) != 0) {
			iVar6 = iVar5 + *(short*)(iVar5 + 0x30) * 2;
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
	} else {
		iVar6 = iVar5 + *(short*)(iVar5 + 0x30) * 2;
		sVar1 = *(short*)(iVar6 + 0x26);
		if (sVar1 == 0) {
			if (*(short*)(iVar5 + 0x34) == 0) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				*(short*)(iVar5 + 0x34) = *(short*)(iVar5 + 0x34) + -1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			*(short*)(iVar6 + 0x26) = sVar1 + -1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
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
		if ((uVar3 & 0x100) == 0) {
			if ((uVar3 & 0x200) != 0) {
				*(char*)(GetArtiStateBase(this) + 0xd) = 1;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				return 1;
			}
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	}

	return 0;
}
