#include "ffcc/menu_favo.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

typedef signed short s16;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern CMenuPcs MenuPcs;

unsigned char s_rank[0x20];

extern float FLOAT_80333040;
extern float FLOAT_80333044;
extern float FLOAT_80333048;
extern double DOUBLE_80333050;
extern float FLOAT_80333058;
extern float FLOAT_8033305C;
extern double DOUBLE_80333060;
extern const char lbl_80333068[];
extern float FLOAT_8033306C;
extern float FLOAT_80333070;
extern double DOUBLE_80333078;
extern float FLOAT_80333080;
extern float FLOAT_80333084;

struct FavoFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct FavoFlatData
{
	char pad0[0x6C];
	FavoFlatTableEntry table[8];
};

struct FavoEntry {
	short x;
	short y;
	short w;
	short h;
	float u;
	float v;
	float alpha;
	float uvScale;
	int drawFlags;
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

/*
 * --INFO--
 * PAL Address: 0x80162360
 * PAL Size: 2488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoDraw()
{
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

	short* entry = reinterpret_cast<short*>((int)favoList + 8);
	int count = *favoList;
	for (int i = 0; i < count; i++) {
		int tex = *reinterpret_cast<int*>(entry + 0xE);
		if (tex >= 0) {
			float x = static_cast<float>(entry[0]);
			float y = static_cast<float>(entry[1]);
			float w = static_cast<float>(entry[2]);
			float h = static_cast<float>(entry[3]);
			float u = *reinterpret_cast<float*>(entry + 4);
			float v = *reinterpret_cast<float*>(entry + 6);
			float alpha = *reinterpret_cast<float*>(entry + 8);
			float uvScale = *reinterpret_cast<float*>(entry + 10);

			if (i < 3) {
				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 1);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);

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

				float fillW = alpha * w;
				if (fillW > FLOAT_80333040) {
					if (tex == 0x32) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > FLOAT_80333044) {
								tileH = FLOAT_80333044;
							}
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							    &MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, fillW, tileH, u,
							    v, colors, uvScale, FLOAT_80333048, FLOAT_80333040);
							yStep += FLOAT_80333044;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						    &MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, fillW, h, u, v, colors,
						    uvScale, FLOAT_80333048, FLOAT_80333040);
					}

					x += fillW * uvScale;
				}

				if (fillW > FLOAT_80333040 && fillW < w) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					float remainW = (static_cast<float>(DOUBLE_80333050) / static_cast<float>(*reinterpret_cast<int*>(entry + 0x14))) * w;
					if (tex == 0x32) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > FLOAT_80333044) {
								tileH = FLOAT_80333044;
							}
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							    &MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, yStep, remainW, tileH,
							    u, v, colors, uvScale, FLOAT_80333048, FLOAT_80333040);
							yStep += FLOAT_80333044;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
						    &MenuPcs, static_cast<unsigned long>(*reinterpret_cast<int*>(entry + 0xC)), x, y, remainW, h, u, v,
						    colors, uvScale, FLOAT_80333048, FLOAT_80333040);
					}
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);
			} else {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = static_cast<unsigned char>(alpha * FLOAT_80333058);
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80333040);
			}
		}

		entry += 0x20;
	}

	short* rankEntry = reinterpret_cast<short*>((int)favoList + 8);
	int remaining = count;
	while (0 < remaining) {
		if (*reinterpret_cast<int*>(rankEntry + 0xE) == 0x37) {
			break;
		}
		rankEntry += 0x20;
		remaining--;
	}

	unsigned char* rank = s_rank;
	short* drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		int barX = drawEntry[0] + drawEntry[2] + 0x18;
		int barY = static_cast<int>((static_cast<float>(drawEntry[3]) - FLOAT_8033305C) * static_cast<float>(DOUBLE_80333060) +
		                            static_cast<float>(drawEntry[1]));
		DrawSingBar(barX, barY, *reinterpret_cast<short*>(rank + 2), *reinterpret_cast<float*>(drawEntry + 8));
		rank += 4;
		drawEntry += 0x20;
	}

	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		int iconX = drawEntry[0] + drawEntry[2] - 0x10;
		int iconY = static_cast<int>((static_cast<float>(drawEntry[3]) - FLOAT_80333044) * static_cast<float>(DOUBLE_80333060) +
		                             static_cast<float>(drawEntry[1]));
		DrawSingleIcon__8CMenuPcsFiiifif(this, static_cast<char>(rank[1]) + 0x14, iconX, iconY, *reinterpret_cast<float*>(drawEntry + 8), 1,
		                                 FLOAT_80333048);
		rank += 4;
		drawEntry += 0x20;
	}

	CFont* rankFont = font22;
	rankFont->SetShadow(1);
	rankFont->SetScale(FLOAT_80333048);
	rankFont->DrawInit();

	char textBuf[0x10];
	memset(textBuf, 0, sizeof(textBuf));
	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		rankFont->SetTlut(6);
		GXColor textColor;
		textColor.r = 0xFF;
		textColor.g = 0xFF;
		textColor.b = 0xFF;
		textColor.a = static_cast<unsigned char>(FLOAT_80333058 * *reinterpret_cast<float*>(drawEntry + 8));
		rankFont->SetColor(textColor);
		rankFont->SetMargin(FLOAT_80333048);
		sprintf(textBuf, lbl_80333068, static_cast<int>(*rank));
		rankFont->SetPosX(static_cast<float>(drawEntry[0] - 0xC));
		rankFont->SetPosY(static_cast<float>(drawEntry[1]) - FLOAT_8033306C);
		rankFont->Draw(textBuf);
		rankFont->SetShadow(0);
		rank += 4;
		drawEntry += 0x20;
	}

	CFont* nameFont = font16;
	nameFont->SetShadow(0);
	nameFont->SetScale(FLOAT_80333070);
	nameFont->SetMargin(FLOAT_80333048);
	nameFont->DrawInit();

	const FavoFlatData* flatData = reinterpret_cast<const FavoFlatData*>(&Game.m_cFlatDataArr[1]);
	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		GXColor textColor;
		textColor.r = 0xFF;
		textColor.g = 0xFF;
		textColor.b = 0xFF;
		textColor.a = static_cast<unsigned char>(FLOAT_80333058 * *reinterpret_cast<float*>(drawEntry + 8));
		nameFont->SetColor(textColor);
		const char* name = flatData->table[0].strings[(static_cast<char>(rank[1]) + 0x17D) * 5 + 4];
		nameFont->SetPosX(static_cast<float>(drawEntry[0] + 0x1C));
		nameFont->SetPosY(static_cast<float>(drawEntry[1]) - FLOAT_8033306C);
		nameFont->Draw(const_cast<char*>(name));
		rank += 4;
		drawEntry += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);
}
/*
 * --INFO--
 * PAL Address: 0x80162d18
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::FavoClose()
{
    int finishedCount;
    int count;
    int frame;
    int remaining;
    FavoEntry* entry;

    finishedCount = 0;
	singMenuState->frame = singMenuState->frame + 1;
    count = static_cast<unsigned short>(*favoList);
    entry = reinterpret_cast<FavoEntry*>(favoList + 4);
    frame = singMenuState->frame;
    remaining = count;
    if (0 < count) {
        do {
            float step = FLOAT_80333040;
            if (entry->startFrame <= frame) {
                if (frame < entry->startFrame + entry->duration) {
                    entry->step = entry->step + 1;
                    entry->alpha =
                        (float)-((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step - DOUBLE_80333050);
                    if ((entry->flags & 2) == 0) {
                        step =
                            (float)-((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step - DOUBLE_80333050);
                        entry->dx = (entry->targetX - (float)entry->x) * step;
                        entry->dy = (entry->targetY - (float)entry->y) * step;
                    }
                } else {
                    finishedCount = finishedCount + 1;
                    entry->alpha = FLOAT_80333040;
                    entry->dx = step;
                    entry->dy = step;
                }
            }
            entry++;
            remaining = remaining + -1;
        } while (remaining != 0);
    }

	return count == finishedCount;
}

/*
 * --INFO--
 * PAL Address: 0x80162e94
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::FavoCtrl()
{
	bool activeInput = false;
	short press;
	int doReset;

	if (Pad._452_4_ == 0) {
		if (Pad._448_4_ != -1) {
			activeInput = true;
		}
	} else {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		unsigned int port = 0;
		int mask = -((__cntlzw((unsigned int)Pad._448_4_) >> 5) & 1);
		port &= ~mask;
		press = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(&Pad) + port * 0x54 + 8);
	}

	if (press == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		singMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		singMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		doReset = 0;
	} else if ((press & 0x200) != 0) {
		singMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		doReset = 0;
	}

	if (doReset != 0) {
		FavoInit0();
	}

	return doReset;
}

/*
 * --INFO--
 * PAL Address: 0x80163024
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::FavoOpen()
{
    int finishedCount;
    int count;
    int frame;
    int remaining;
    FavoEntry* entry;

	if (singMenuState->initialized == 0) {
		FavoInit();
	}

    finishedCount = 0;
	singMenuState->frame = singMenuState->frame + 1;
    count = static_cast<unsigned short>(*favoList);
    entry = reinterpret_cast<FavoEntry*>(favoList + 4);
    frame = singMenuState->frame;
    remaining = count;
    if (0 < count) {
        do {
            float step = FLOAT_80333040;
            if (entry->startFrame <= frame) {
                if (frame < entry->startFrame + entry->duration) {
                    entry->step = entry->step + 1;
                    entry->alpha = (float)((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
                    if ((entry->flags & 2) == 0) {
                        step = (float)((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
                        entry->dx = (entry->targetX - (float)entry->x) * step;
                        entry->dy = (entry->targetY - (float)entry->y) * step;
                    }
                } else {
                    finishedCount = finishedCount + 1;
                    entry->alpha = FLOAT_80333048;
                    entry->dx = step;
                    entry->dy = step;
                }
            }
            entry++;
            remaining = remaining + -1;
        } while (remaining != 0);
    }

	return count == finishedCount;
}

/*
 * --INFO--
 * PAL Address: 801631d4
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoInit0()
{
	float alpha;
	unsigned int count;
	unsigned int blockCount;
	FavoEntry* entry;

	entry = reinterpret_cast<FavoEntry*>(favoList + 4);
	entry[0].startFrame = 2;
	entry[0].duration = 5;
	entry[1].startFrame = 2;
	entry[1].duration = 5;
	entry[2].startFrame = 2;
	entry[2].duration = 5;
	entry[3].startFrame = 7;
	entry[3].duration = 5;
	entry[4].startFrame = 7;
	entry[4].duration = 5;
	entry[5].flags = 2;
	entry[5].startFrame = 7;
	entry[5].duration = 5;
	entry[6].flags = 2;
	entry[6].startFrame = 0;
	entry[6].duration = 5;
	entry[7].flags = 2;
	entry[7].startFrame = 0;
	entry[7].duration = 5;
	entry[8].flags = 2;
	entry[8].startFrame = 0;
	entry[8].duration = 5;
	entry[9].flags = 2;
	alpha = FLOAT_80333048;
	entry[9].startFrame = 0;
	entry[9].duration = 5;
	entry[10].flags = 2;
	entry[10].startFrame = 0;
	entry[10].duration = 5;
	entry[11].flags = 2;
	entry[11].startFrame = 0;
	entry[11].duration = 5;
	entry[12].flags = 2;
	entry[12].startFrame = 0;
	entry[12].duration = 5;
	entry[13].flags = 2;
	entry[13].startFrame = 0;
	entry[13].duration = 5;

	count = (unsigned int)*favoList;
	entry = reinterpret_cast<FavoEntry*>(favoList + 4);
	if (0 < (int)count) {
		blockCount = count >> 3;
		if (blockCount != 0) {
			do {
				entry[0].step = 0;
				entry[0].alpha = alpha;
				entry[1].step = 0;
				entry[1].alpha = alpha;
				entry[2].step = 0;
				entry[2].alpha = alpha;
				entry[3].step = 0;
				entry[3].alpha = alpha;
				entry[4].step = 0;
				entry[4].alpha = alpha;
				entry[5].step = 0;
				entry[5].alpha = alpha;
				entry[6].step = 0;
				entry[6].alpha = alpha;
				entry[7].step = 0;
				entry[7].alpha = alpha;
				entry += 8;
				blockCount = blockCount - 1;
			} while (blockCount != 0);
			count = count & 7;
			if (count == 0) {
				return;
			}
		}
		do {
			entry->step = 0;
			entry->alpha = alpha;
			entry++;
			count = count - 1;
		} while (count != 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8016343c
 * PAL Size: 1296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoInit()
{
	unsigned char uVar1;
	unsigned char uVar2;
	unsigned int uVar3;
	float fVar4;
	float fVar5;
	float fVar7;
	int iVar8;
	short sVar9;
	short sVar10;
	short sVar11;
	unsigned char* puVar12;
	unsigned char* puVar13;
	short* psVar14;
	int iVar15;
	int iVar16;
	int iVar17;

	uVar3 = Game.m_scriptFoodBase[0];
	memset(favoList, 0, 0x1008);
	fVar4 = FLOAT_80333048;
	iVar8 = (int)favoList + 8;
	iVar16 = 8;
	do {
		*(float*)(iVar8 + 0x14) = fVar4;
		*(float*)(iVar8 + 0x54) = fVar4;
		*(float*)(iVar8 + 0x94) = fVar4;
		*(float*)(iVar8 + 0xd4) = fVar4;
		*(float*)(iVar8 + 0x114) = fVar4;
		*(float*)(iVar8 + 0x154) = fVar4;
		*(float*)(iVar8 + 0x194) = fVar4;
		*(float*)(iVar8 + 0x1d4) = fVar4;
		iVar8 = iVar8 + 0x200;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 0x24) = 0x33;
	*(int*)(iVar8 + 0x20) = 4;
	*(short*)(iVar8 + 8) = 0x30;
	fVar4 = 0.0f;
	*(short*)(iVar8 + 10) = 0x28;
	fVar5 = FLOAT_80333080;
	*(short*)(iVar8 + 0xc) = 0x158;
	*(short*)(iVar8 + 0xe) = 0x20;
	*(float*)(iVar8 + 0x10) = fVar4;
	*(float*)(iVar8 + 0x14) = fVar4;
	*(float*)(iVar8 + 0x1c) = fVar5 / (float)*(short*)(iVar8 + 0xc);
	*(int*)(iVar8 + 0x2c) = 5;
	*(int*)(iVar8 + 0x30) = 5;

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 100) = 0x32;
	*(short*)(iVar8 + 0x48) = 0x30;
	*(short*)(iVar8 + 0x4a) = 0x48;
	*(short*)(iVar8 + 0x4c) = 0x158;
	*(short*)(iVar8 + 0x4e) = 200;
	*(float*)(iVar8 + 0x50) = fVar4;
	*(float*)(iVar8 + 0x54) = fVar4;
	*(float*)(iVar8 + 0x5c) = fVar5 / (float)*(short*)(iVar8 + 0x4c);
	*(int*)(iVar8 + 0x6c) = 5;
	*(int*)(iVar8 + 0x70) = 5;

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 0xa4) = 0x33;
	*(short*)(iVar8 + 0x88) = 0x30;
	*(short*)(iVar8 + 0x8a) = 0x110;
	*(short*)(iVar8 + 0x8c) = 0x158;
	*(short*)(iVar8 + 0x8e) = 0x20;
	*(float*)(iVar8 + 0x90) = fVar4;
	*(float*)(iVar8 + 0x94) = fVar4;
	*(float*)(iVar8 + 0x9c) = fVar5 / (float)*(short*)(iVar8 + 0x8c);
	*(int*)(iVar8 + 0xac) = 5;
	*(int*)(iVar8 + 0xb0) = 5;

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 0xe4) = 0x45;
	fVar5 = FLOAT_80333048;
	sVar9 = 0;
	*(short*)(iVar8 + 200) = 0x18;
	fVar7 = FLOAT_80333084;
	sVar11 = 6;
	*(short*)(iVar8 + 0xca) = 0xe;
	*(short*)(iVar8 + 0xcc) = 0x30;
	iVar16 = 0x180;
	*(short*)(iVar8 + 0xce) = 0x30;
	*(float*)(iVar8 + 0xd0) = fVar4;
	*(float*)(iVar8 + 0xd4) = fVar4;
	*(float*)(iVar8 + 0xdc) = fVar5;
	*(int*)(iVar8 + 0xec) = 0;
	*(int*)(iVar8 + 0xf0) = 5;

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 0x124) = 0x45;
	*(short*)(iVar8 + 0x108) = 0x1d;
	*(short*)(iVar8 + 0x10c) = 0x30;
	*(short*)(iVar8 + 0x10e) = 0x30;
	*(short*)(iVar8 + 0x10a) = 0x150 - *(short*)(iVar8 + 0x10e);
	*(float*)(iVar8 + 0x110) = fVar4;
	*(float*)(iVar8 + 0x114) = fVar4;
	*(float*)(iVar8 + 0x11c) = fVar7;
	*(int*)(iVar8 + 300) = 0;
	*(int*)(iVar8 + 0x130) = 5;

	iVar8 = (int)favoList;
	*(int*)(iVar8 + 0x174) = 2;
	*(int*)(iVar8 + 0x164) = 0x2e;
	*(short*)(iVar8 + 0x148) = 0x18;
	*(short*)(iVar8 + 0x14a) = 8;
	*(short*)(iVar8 + 0x14c) = 0x48;
	*(short*)(iVar8 + 0x14e) = 0x140;
	*(float*)(iVar8 + 0x150) = fVar4;
	*(float*)(iVar8 + 0x154) = fVar4;
	*(int*)(iVar8 + 0x16c) = 0;
	*(int*)(iVar8 + 0x170) = 5;

	iVar8 = (int)favoList;
	iVar17 = 4;
	do {
		psVar14 = (short*)((int)favoList + iVar16 + 8);
		psVar14[0x16] = 0;
		psVar14[0x17] = 2;
		psVar14[0xe] = 0;
		psVar14[0xf] = 0x37;
		sVar11 = sVar11 + 2;
		*psVar14 = *(short*)(iVar8 + 8) + 0x28;
		sVar10 = sVar9 + 0x20;
		psVar14[1] = *(short*)(iVar8 + 10) + sVar9;
		psVar14[2] = 200;
		psVar14[3] = 0x28;
		*(float*)(psVar14 + 4) = fVar4;
		*(float*)(psVar14 + 6) = fVar4;
		psVar14[0x12] = 0;
		psVar14[0x13] = 7;
		psVar14[0x14] = 0;
		psVar14[0x15] = 5;

		iVar15 = iVar16 + 0x48;
		iVar16 = iVar16 + 0x80;
		psVar14 = (short*)((int)favoList + iVar15);
		psVar14[0x16] = 0;
		psVar14[0x17] = 2;
		psVar14[0xe] = 0;
		psVar14[0xf] = 0x37;
		*psVar14 = *(short*)(iVar8 + 8) + 0x28;
		sVar9 = sVar9 + 0x40;
		psVar14[1] = *(short*)(iVar8 + 10) + sVar10;
		psVar14[2] = 200;
		psVar14[3] = 0x28;
		*(float*)(psVar14 + 4) = fVar4;
		*(float*)(psVar14 + 6) = fVar4;
		psVar14[0x12] = 0;
		psVar14[0x13] = 7;
		psVar14[0x14] = 0;
		psVar14[0x15] = 5;
		iVar17 = iVar17 - 1;
	} while (iVar17 != 0);

	*favoList = sVar11;

	memset(s_rank, 0, 0x20);
	iVar8 = 0;
	puVar13 = s_rank;
	s_rank[1] = 0;
	*(short*)&s_rank[2] = *(short*)(uVar3 + 0x3b8);
	s_rank[5] = 1;
	*(short*)&s_rank[6] = *(short*)(uVar3 + 0x3ba);
	s_rank[9] = 2;
	*(short*)&s_rank[10] = *(short*)(uVar3 + 0x3bc);
	s_rank[0xd] = 3;
	*(short*)&s_rank[14] = *(short*)(uVar3 + 0x3be);
	s_rank[0x11] = 4;
	*(short*)&s_rank[18] = *(short*)(uVar3 + 0x3c0);
	s_rank[0x15] = 5;
	*(short*)&s_rank[22] = *(short*)(uVar3 + 0x3c2);
	s_rank[0x19] = 6;
	*(short*)&s_rank[26] = *(short*)(uVar3 + 0x3c4);
	s_rank[0x1d] = 7;
	*(short*)&s_rank[30] = *(short*)(uVar3 + 0x3c6);

	do {
		iVar17 = iVar8 + 1;
		iVar16 = 8 - iVar17;
		puVar12 = s_rank + iVar17 * 4;
		if (iVar17 < 8) {
			do {
				sVar9 = *(short*)(puVar13 + 2);
				if (sVar9 < *(short*)(puVar12 + 2)) {
					uVar1 = *puVar13;
					uVar2 = puVar13[1];
					*puVar13 = *puVar12;
					puVar13[1] = puVar12[1];
					*(short*)(puVar13 + 2) = *(short*)(puVar12 + 2);
					*puVar12 = uVar1;
					puVar12[1] = uVar2;
					*(short*)(puVar12 + 2) = sVar9;
				}
				puVar12 = puVar12 + 4;
				iVar16 = iVar16 - 1;
			} while (iVar16 != 0);
		}
		iVar8 = iVar8 + 1;
		puVar13 = puVar13 + 4;
	} while (iVar8 < 8);

	iVar8 = 0;
	iVar17 = 0;
	iVar16 = 8;
	puVar13 = s_rank;
	do {
		if ((iVar17 != 0) && (*(short*)(puVar13 - 2) != *(short*)(puVar13 + 2))) {
			iVar8 = iVar17;
		}
		iVar17 = iVar17 + 1;
		*puVar13 = (char)iVar8 + 1;
		puVar13 = puVar13 + 4;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	singMenuState->selectedIndex = 0;
	singMenuState->initialized = 1;
}
