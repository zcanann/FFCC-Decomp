#include "ffcc/menu_tmparti.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include "ffcc/pad.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include <string.h>

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" int __cntlzw(unsigned int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" float GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);


extern float FLOAT_80332f2c;
extern float FLOAT_80332F28;
extern float FLOAT_80332f30;
extern float FLOAT_80332F34;
extern float FLOAT_80332F38;
extern double DOUBLE_80332f20;
extern double DOUBLE_80332f40;
extern double DOUBLE_80332f48;
extern double DOUBLE_80332f50;
extern double DOUBLE_80332f58;

extern const double DOUBLE_80333418 = 0.0;
extern const double DOUBLE_80333420 = 216.0;

static inline double TmpArtiIntToDouble(int value)
{
    union {
        unsigned long long bits;
        double value;
    } conv;

    conv.bits = 0x4330000000000000ULL | (unsigned int)(value ^ 0x80000000U);
    return conv.value - DOUBLE_80332f40;
}

namespace {
struct TmpArtiState {
    unsigned char pad_0000[0xB];
    char initialized;
    unsigned char pad_000C;
    unsigned char closeRequested;
    unsigned char pad_000E[0x10];
    short moveDirection;
    unsigned char pad_0020[2];
    short frame;
    unsigned char pad_0024[2];
    short unk_26;
    unsigned char pad_0028[8];
    short prevSelection;
    short selection;
};

struct TmpArtiEntry {
    short x;
    short y;
    short width;
    short height;
    float s;
    float t;
    float alpha;
    float z;
    int unk_18;
    int tex;
    int timer;
    int startFrame;
    int duration;
    unsigned char pad_002C[0x14];
};

struct TmpArtiList {
    unsigned short count;
    unsigned short pad_0002;
    unsigned int pad_0004;
    TmpArtiEntry entries[64];
};

struct MenuTmpArtiMembers {
    unsigned char pad_0000[0x108];
    CFont* m_tmpArtiFont;
    unsigned char pad_010C[0x720];
    short* m_tmpArtiState;
    unsigned char pad_0830[0x20];
    short* m_tmpArtiList;
};

STATIC_ASSERT(offsetof(MenuTmpArtiMembers, m_tmpArtiFont) == 0x108);
STATIC_ASSERT(offsetof(MenuTmpArtiMembers, m_tmpArtiState) == 0x82C);
STATIC_ASSERT(offsetof(MenuTmpArtiMembers, m_tmpArtiList) == 0x850);
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

static inline MenuTmpArtiMembers& GetMenuTmpArtiMembers(CMenuPcs* menu)
{
    return *reinterpret_cast<MenuTmpArtiMembers*>(menu);
}

static inline short* GetTmpArtiList(CMenuPcs* menu)
{
    return GetMenuTmpArtiMembers(menu).m_tmpArtiList;
}

static inline int GetTmpArtiListBase(CMenuPcs* menu)
{
    return reinterpret_cast<int>(GetTmpArtiList(menu));
}

static inline CFont* GetTmpArtiFont(CMenuPcs* menu)
{
    return GetMenuTmpArtiMembers(menu).m_tmpArtiFont;
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
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

	unsigned int scriptFood = Game.m_scriptFoodBase[0];
	short* entry = (short*)(GetTmpArtiListBase(this) + 8);
	unsigned int foodPtr = scriptFood;

	for (int i = 0; i < *GetTmpArtiList(this); i++) {
		int tex = *(int*)(entry + 0xE);
		if (-1 < tex) {
			float alpha = *(float*)(entry + 8);
			float left = (float)entry[0];
			float top = (float)entry[1];
			float width = (float)entry[2];
			float height = (float)entry[3];
			float s = *(float*)(entry + 4);
			float t = *(float*)(entry + 6);
			float z = *(float*)(entry + 10);

			if (*(short*)(foodPtr + 0x1F6) < 0) {
				tex = 0x34;
				alpha = (float)(DOUBLE_80332f20 * (double)alpha);
			}

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);

			CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80332F28 * alpha));
			GXSetChanMatColor(GX_COLOR0A0, color.color);

			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, left, top, width, height, s, t, z, z, FLOAT_80332f2c);
		}
		foodPtr += 2;
		entry += 0x20;
	}

	entry = GetTmpArtiList(this) + 4;
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		short icon = *(short*)(foodPtr + 0x1F6);
		if (-1 < icon) {
			int posX = (int)entry[0] + (int)entry[2] - 0x10;
			int posY = (int)((float)TmpArtiIntToDouble(entry[1] + 6) - FLOAT_80332f30);
			DrawSingleIcon__8CMenuPcsFiiifif(this, icon, posX, posY, *(float*)(entry + 8), 0, FLOAT_80332f2c);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	CFont* font = GetTmpArtiFont(this);
	SetMargin__5CFontFf(FLOAT_80332f30, font);
	SetShadow__5CFontFi(font, 0);
	SetScale__5CFontFf(FLOAT_80332F34, font);
	DrawInit__5CFontFv(font);

	const TmpArtiFlatData* flatData = (const TmpArtiFlatData*)&Game.m_cFlatDataArr[1];
	entry = (short*)(GetTmpArtiListBase(this) + 8);
	foodPtr = scriptFood;
	for (int i = 0; i < 4; i++) {
		short itemId = *(short*)(foodPtr + 0x1F6);
		if (-1 < itemId) {
			float alpha = *(float*)(entry + 8);
			CColor textColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80332F28 * alpha));
			SetColor__5CFontF8_GXColor(font, &textColor.color);

			const char* text = flatData->table[0].strings[itemId * 5 + 4];
			int width = GetWidth__5CFontFPc(font, text);
			float posX = (float)(((TmpArtiIntToDouble(entry[2]) - TmpArtiIntToDouble(width)) * DOUBLE_80332f20) +
			                       TmpArtiIntToDouble(entry[0]));
			float posY = (float)TmpArtiIntToDouble(entry[1] + 11) - FLOAT_80332F38;

			SetPosX__5CFontFf(posX, font);
			SetPosY__5CFontFf(posY, font);
			Draw__5CFontFPc(font, text);
		}
		entry += 0x20;
		foodPtr += 2;
	}

	DrawInit__8CMenuPcsFv(this);
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
	float fVar1;
	double dVar2;
	double dVar3;
	short *psVar4;
	int iVar5;
	unsigned int uVar6;
	int iVar7;
	unsigned int uVar8;

	iVar5 = 0;
	*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22) = *(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22) + 1;
	uVar6 = (unsigned int)*this->m_tmpArtiList;
	psVar4 = this->m_tmpArtiList + 4;
	iVar7 = (int)*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22);
	uVar8 = uVar6;

	if (0 < (int)uVar6) {
		do {
			dVar2 = DOUBLE_80332f40;
			if (*(int *)(psVar4 + 0x12) <= iVar7) {
				if (*(int *)(psVar4 + 0x12) + *(int *)(psVar4 + 0x14) <= iVar7) {
					iVar5 = iVar5 + 1;
					*(float *)(psVar4 + 8) = FLOAT_80332f2c;
				}
				else {
					*(int *)(psVar4 + 0x10) = *(int *)(psVar4 + 0x10) + 1;
					dVar3 = DOUBLE_80332f50;
					*(float *)(psVar4 + 8) =
					    (float)(DOUBLE_80332f48 -
					            (DOUBLE_80332f48 /
					             ((double)*(int *)(psVar4 + 0x14) - dVar2)) *
					                ((double)*(int *)(psVar4 + 0x10) - dVar2));
					if ((double)*(float *)(psVar4 + 8) < dVar3) {
						*(float *)(psVar4 + 8) = FLOAT_80332f2c;
					}
				}
			}
			psVar4 = psVar4 + 0x20;
			uVar8 = uVar8 - 1;
		} while (uVar8 != 0);
	}

	fVar1 = FLOAT_80332f2c;
	if (*this->m_tmpArtiList == iVar5) {
		psVar4 = this->m_tmpArtiList + 4;
		if (0 < (int)uVar6) {
			uVar8 = uVar6 >> 3;
			if (uVar8 != 0) {
				do {
					*(int *)(psVar4 + 0x12) = 0;
					*(int *)(psVar4 + 0x14) = 1;
					*(float *)(psVar4 + 8) = fVar1;
					*(int *)(psVar4 + 0x32) = 0;
					*(int *)(psVar4 + 0x34) = 1;
					*(float *)(psVar4 + 0x28) = fVar1;
					*(int *)(psVar4 + 0x52) = 0;
					*(int *)(psVar4 + 0x54) = 1;
					*(float *)(psVar4 + 0x48) = fVar1;
					*(int *)(psVar4 + 0x72) = 0;
					*(int *)(psVar4 + 0x74) = 1;
					*(float *)(psVar4 + 0x68) = fVar1;
					*(int *)(psVar4 + 0x92) = 0;
					*(int *)(psVar4 + 0x94) = 1;
					*(float *)(psVar4 + 0x88) = fVar1;
					*(int *)(psVar4 + 0xb2) = 0;
					*(int *)(psVar4 + 0xb4) = 1;
					*(float *)(psVar4 + 0xa8) = fVar1;
					*(int *)(psVar4 + 0xd2) = 0;
					*(int *)(psVar4 + 0xd4) = 1;
					*(float *)(psVar4 + 200) = fVar1;
					*(int *)(psVar4 + 0xf2) = 0;
					*(int *)(psVar4 + 0xf4) = 1;
					*(float *)(psVar4 + 0xe8) = fVar1;
					psVar4 = psVar4 + 0x100;
					uVar8 = uVar8 - 1;
				} while (uVar8 != 0);
				uVar6 = uVar6 & 7;
				if (uVar6 == 0) {
					return 1;
				}
			}
			do {
				*(int *)(psVar4 + 0x12) = 0;
				*(int *)(psVar4 + 0x14) = 1;
				*(float *)(psVar4 + 8) = fVar1;
				psVar4 = psVar4 + 0x20;
				uVar6 = uVar6 - 1;
			} while (uVar6 != 0);
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
	*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x32) = *(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x30);
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		hasInput = true;
	}

	if (hasInput) {
		uVar3 = 0;
	} else {
		int padIndex = hasInput;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		uVar3 = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&Pad) + padIndex * 0x54 + 8);
	}

	if (uVar3 == 0) {
		hasInput = false;
	} else if ((uVar3 & 0x20) != 0) {
		*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x1e) = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x40) != 0) {
		*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x1e) = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		hasInput = true;
	} else if ((uVar3 & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		hasInput = false;
	} else if ((uVar3 & 0x200) != 0) {
		*(unsigned char *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0xd) = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		hasInput = true;
	} else {
		hasInput = false;
	}

	if (hasInput) {
		float fVar2 = FLOAT_80332f30;
		unsigned int uVar4 = Game.m_scriptFoodBase[0];

		iVar6 = reinterpret_cast<int>(this->m_tmpArtiList) + 8;
		for (iVar7 = 0; iVar7 < *this->m_tmpArtiList; iVar7 = iVar7 + 1) {
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
					*(int *)(iVar8 + 0x24) = iVar7;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x38;
					*(int *)(iVar8 + 0x24) = iVar7 + 1;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x78;
					*(int *)(iVar8 + 0x24) = iVar7 + 2;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0xb8;
					*(int *)(iVar8 + 0x24) = iVar7 + 3;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0xf8;
					*(int *)(iVar8 + 0x24) = iVar7 + 4;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x138;
					*(int *)(iVar8 + 0x24) = iVar7 + 5;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar6 + -0x178;
					*(int *)(iVar8 + 0x24) = iVar7 + 6;
					*(unsigned int *)(iVar8 + 0x28) = 3;
					iVar8 = iVar6 + -0x1b8;
					iVar6 = iVar6 + -0x200;
					iVar8 = reinterpret_cast<int>(this->m_tmpArtiList) + iVar8;
					*(int *)(iVar8 + 0x24) = iVar7 + 7;
					iVar7 = iVar7 + 8;
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
	double dVar1;
	float fVar2;
	float fVar3;
	double dVar5;
	int iVar6;
	short* psVar7;
	unsigned int uVar8;
	int iVar10;
	unsigned int uVar11;

	if (*(char *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0xb) == '\0') {
		memset(this->m_tmpArtiList, 0, sizeof(TmpArtiList));
		fVar3 = FLOAT_80332f30;
		iVar6 = reinterpret_cast<int>(this->m_tmpArtiList) + 8;
		iVar10 = 8;
		do {
			*(float *)(iVar6 + 0x14) = fVar3;
			*(float *)(iVar6 + 0x54) = fVar3;
			*(float *)(iVar6 + 0x94) = fVar3;
			*(float *)(iVar6 + 0xd4) = fVar3;
			*(float *)(iVar6 + 0x114) = fVar3;
			*(float *)(iVar6 + 0x154) = fVar3;
			*(float *)(iVar6 + 0x194) = fVar3;
			*(float *)(iVar6 + 0x1d4) = fVar3;
			iVar6 = iVar6 + 0x200;
			iVar10 = iVar10 - 1;
		} while (iVar10 != 0);
		dVar5 = DOUBLE_80332f58;
		fVar2 = FLOAT_80332f2c;
		dVar1 = DOUBLE_80332f20;
		iVar6 = 0;
		psVar7 = this->m_tmpArtiList + 4;
		iVar10 = 2;
		do {
			*(int *)(psVar7 + 0xe) = 0x37;
			psVar7[2] = 200;
			psVar7[3] = 0x28;
			psVar7[0] = (short)(int)-(((double)psVar7[2] * dVar1) - dVar5);
			psVar7[1] = (short)iVar6 * (psVar7[3] + -8) + 0x60;
			*(float *)(psVar7 + 4) = fVar2;
			*(float *)(psVar7 + 6) = fVar2;
			*(int *)(psVar7 + 0x12) = iVar6;
			*(int *)(psVar7 + 0x14) = 3;
			*(int *)(psVar7 + 0x2e) = 0x37;
			psVar7[0x22] = 200;
			psVar7[0x23] = 0x28;
			psVar7[0x20] = (short)(int)-(((double)psVar7[0x22] * dVar1) - dVar5);
			psVar7[0x21] = (short)(iVar6 + 1) * (psVar7[0x23] + -8) + 0x60;
			*(float *)(psVar7 + 0x24) = fVar2;
			*(float *)(psVar7 + 0x26) = fVar2;
			*(int *)(psVar7 + 0x32) = iVar6 + 1;
			iVar6 = iVar6 + 2;
			*(int *)(psVar7 + 0x34) = 3;
			psVar7 = psVar7 + 0x40;
			iVar10 = iVar10 - 1;
		} while (iVar10 != 0);
		*this->m_tmpArtiList = 4;
		*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x26) = 0;
		*(char *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0xb) = 1;
	}
	iVar6 = 0;
	*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22) = *(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22) + 1;
	uVar8 = (unsigned int)*this->m_tmpArtiList;
	psVar7 = this->m_tmpArtiList + 4;
	iVar10 = (int)*(short *)(reinterpret_cast<int>(this->m_tmpArtiState) + 0x22);
	uVar11 = uVar8;
	if (0 < (int)uVar8) {
		do {
			dVar1 = DOUBLE_80332f40;
			if (*(int *)(psVar7 + 0x12) <= iVar10) {
				if (*(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14) <= iVar10) {
					iVar6 = iVar6 + 1;
					*(float *)(psVar7 + 8) = FLOAT_80332f30;
				}
				else {
					*(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
					*(float *)(psVar7 + 8) =
					    (float)((DOUBLE_80332f48 / (double)*(int *)(psVar7 + 0x14)) *
					            (double)*(int *)(psVar7 + 0x10));
				}
			}
			psVar7 = psVar7 + 0x20;
			uVar11 = uVar11 - 1;
		} while (uVar11 != 0);
	}
	fVar3 = FLOAT_80332f30;
	if (*this->m_tmpArtiList == iVar6) {
		psVar7 = this->m_tmpArtiList + 4;
		if (0 < (int)uVar8) {
			uVar11 = uVar8 >> 3;
			if (uVar11 != 0) {
				do {
					*(int *)(psVar7 + 0x12) = 0;
					*(int *)(psVar7 + 0x14) = 1;
					*(float *)(psVar7 + 8) = fVar3;
					*(int *)(psVar7 + 0x32) = 0;
					*(int *)(psVar7 + 0x34) = 1;
					*(float *)(psVar7 + 0x28) = fVar3;
					*(int *)(psVar7 + 0x52) = 0;
					*(int *)(psVar7 + 0x54) = 1;
					*(float *)(psVar7 + 0x48) = fVar3;
					*(int *)(psVar7 + 0x72) = 0;
					*(int *)(psVar7 + 0x74) = 1;
					*(float *)(psVar7 + 0x68) = fVar3;
					*(int *)(psVar7 + 0x92) = 0;
					*(int *)(psVar7 + 0x94) = 1;
					*(float *)(psVar7 + 0x88) = fVar3;
					*(int *)(psVar7 + 0xb2) = 0;
					*(int *)(psVar7 + 0xb4) = 1;
					*(float *)(psVar7 + 0xa8) = fVar3;
					*(int *)(psVar7 + 0xd2) = 0;
					*(int *)(psVar7 + 0xd4) = 1;
					*(float *)(psVar7 + 200) = fVar3;
					*(int *)(psVar7 + 0xf2) = 0;
					*(int *)(psVar7 + 0xf4) = 1;
					*(float *)(psVar7 + 0xe8) = fVar3;
					psVar7 = psVar7 + 0x100;
					uVar11 = uVar11 - 1;
				} while (uVar11 != 0);
				uVar8 = uVar8 & 7;
				if (uVar8 == 0) {
					return 1;
				}
			}
			do {
				*(int *)(psVar7 + 0x12) = 0;
				*(int *)(psVar7 + 0x14) = 1;
				*(float *)(psVar7 + 8) = fVar3;
				psVar7 = psVar7 + 0x20;
				uVar8 = uVar8 - 1;
			} while (uVar8 != 0);
		}
		return 1;
	}
	return 0;
}
