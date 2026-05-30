#include "ffcc/mes.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/mesmenu.h"
#include "ffcc/joybus.h"
#include "ffcc/strcase.h"
#include "ffcc/system.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern float FLOAT_80330890;
extern float FLOAT_80330894;
extern float FLOAT_80330898;
extern float FLOAT_8033089c;
extern float FLOAT_803308a0;
extern float FLOAT_803308a4;
extern float FLOAT_803308A8;
extern float FLOAT_803308ac;
extern float FLOAT_803308b0;
// PAL map: CMes::m_tempVar in mes.o, .bss size 0x50.
int CMes::m_tempVar[0x14];

static const char s_mesTagUnknown[] = "Not corresponding TAG is used. %02x\n";
static const char s_mesTagMissing[] = "This TAG is not created. %02x\n";
static const char s_mesNumFmt[] = "%d";
static const char s_mesFallback[] = "---";
static const char s_mesEmpty[] = "";
static char* sTag54Source;
static char sTag54Init;

struct CMesFlatTableView
{
	int m_numEntries;
	char** m_strings;
	char* m_stringBuf;
};

struct CMesFlatDataView
{
	int m_dataCount;
	unsigned char _pad[0x68 - 4];
	int m_tableCount;
	CMesFlatTableView m_tabl[8];
};

static inline int GetMesNibbleValue(const char* data)
{
	unsigned char high = (unsigned char)data[0];
	unsigned char low = (unsigned char)data[1];
	return (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
}

static int ReadTagU8(char** text)
{
	unsigned char high = (unsigned char)(*text)[0];
	unsigned char low = (unsigned char)(*text)[1];
	int value = (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
	*text += 2;
	return value;
}

static int ReadTagS8(char** text)
{
	unsigned char high = (unsigned char)(*text)[0];
	unsigned char low = (unsigned char)(*text)[1];
	int value = (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
	*text += 2;
	return (int)(signed char)value;
}

static int ReadTagS16(char** text)
{
	int a = (unsigned char)(*text)[0] & 0x0F;
	int b = (unsigned char)(*text)[1] & 0x0F;
	int c = (unsigned char)(*text)[2] & 0x0F;
	int d = (unsigned char)(*text)[3] & 0x0F;
	*text += 4;
	return (int)(short)((a << 12) | (b << 8) | (c << 4) | d);
}

static void ApplyCaseMode(char* text, int& caseMode)
{
	if ((text[0] == '\0') || (caseMode == 0))
	{
		return;
	}

	if (caseMode == 1)
	{
		toupper(text);
	}
	else if (caseMode == 2)
	{
		text[0] = (char)toupperLatin1((unsigned char)text[0]);
	}
	else
	{
		tolower_name_conflict(text);
	}

	caseMode = 0;
}

#define FLAT_NAME_DIRECT(tableIdx, entryIdx) (((CMesFlatDataView*)&Game.m_cFlatDataArr[1])->m_tabl[(tableIdx)].m_strings[(entryIdx)])

static void AdvanceMesLine(CMes* mes, CFont* font)
{
	*(float*)((char*)mes + 0x3C84) = FLOAT_8033089c;
	*(float*)((char*)mes + 0x3C88) =
	    *(float*)((char*)mes + 0x3C88) + FLOAT_803308a4 + (float)font->m_glyphHeight * font->scaleY;

	if (*(int*)((char*)mes + 0x3D10) != 0)
	{
		*(int*)((char*)mes + 0x3D14) = *(int*)((char*)mes + 0x3D14) + 1;
		*(float*)((char*)mes + 0x3C84) =
		    *(float*)((char*)mes + 0x3C84) + FLOAT_803308A8 + *(float*)((char*)mes + 0x3D3C);
	}
}

static void AddMesFlag(CMes* mes, unsigned char type, unsigned char index, short value)
{
	int count = *(int*)((char*)mes + 0x3C0C);
	unsigned char* entry = (unsigned char*)mes + count * 6 + 0x3C14;
	entry[0] = type;
	entry[1] = 0;
	entry[2] = index;
	entry[3] = 0;
	*(short*)(entry + 4) = value;
	*(int*)((char*)mes + 0x3C0C) = count + 1;
}

/*
 * --INFO--
 * PAL Address: 0x800981f0
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMes::drawTagString(CFont* font, char* text, int drawChars, int breakOnLineTag, int lineBaseY)
{
	int width = 0;
	bool continueDraw = true;
	float lineStartX = font->posX;
	unsigned char* src = (unsigned char*)text;

	while (continueDraw)
	{
		unsigned short ch = *src++;

		if (ch == 0)
		{
			continueDraw = false;
		}
		else if (ch == 0xFF)
		{
			int tag = ((int)*src++ - 0xA0) & 0xFFFF;
			if (tag != 1)
			{
				if ((tag == 0) && (breakOnLineTag != 0))
				{
					font->SetPosX((float)(int)lineStartX);
					font->SetPosY((float)lineBaseY + font->posY + (float)font->m_glyphHeight * font->scaleY);
				}
			}
			else
			{
				continueDraw = false;
			}
		}
		else
		{
			if (drawChars != 0)
			{
				font->Draw(ch);
			}
			width = (int)((float)width + font->GetWidth(ch));
		}
	}

	return width;
}
/*
 * --INFO--
 * PAL Address: 0x8009836c
 * PAL Size: 2136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::MakeAgbString(char* out, char* src, int playerIndex, int keepHyphenOnLineBreak)
{
	const unsigned char* in = (const unsigned char*)src;
	char* dst = out;

	if (sTag54Init == 0)
	{
		sTag54Source = (char*)s_mesEmpty;
		sTag54Init = 1;
	}

	int caseMode = 0;
	int branchMode = 0;

	while (true)
	{
		unsigned char c = in[0];
		if (c == 0)
		{
			return;
		}

		if (c != 0xFF)
		{
			if (branchMode != 2)
			{
				*dst = (char)c;
				dst++;
			}
			in++;
			continue;
		}

		unsigned int tag = ((unsigned int)in[1] - 0xA0U) & 0xFFU;
		const unsigned char* next = in + 2;

		switch (tag)
		{
		case 0:
			if (keepHyphenOnLineBreak == 0)
			{
				*dst++ = '\n';
			}
			else if (dst[-1] == '-')
			{
				dst[-1] = '\0';
				dst--;
			}
			break;
		case 4:
			*dst++ = 0x1D;
			break;
		case 5:
			*dst++ = 0x1C;
			break;
		case 6:
			*dst++ = 0x1E;
			break;
		case 8:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			const char* text = FLAT_NAME_DIRECT(5, CMes::m_tempVar[varIndex]);
			strcpy(dst, text);
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 9:
		case 0x1D:
		case 0x37:
		case 0x39:
		case 0x3B:
		case 0x3D:
		case 0x3F:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			int value = CMes::m_tempVar[varIndex];
			if ((tag == 9) || (tag == 0x37))
			{
				strcpy(dst, FLAT_NAME_DIRECT(0, value * 5 + 1));
			}
			else if (tag == 0x1D)
			{
				strcpy(dst, FLAT_NAME_DIRECT(0, value * 5));
			}
			else if (tag == 0x39)
			{
				strcpy(dst, FLAT_NAME_DIRECT(0, value * 5 + 3));
			}
			else if (tag == 0x3B)
			{
				Game.MakeArtItemName(dst, value, 1);
			}
			else if (tag == 0x3D)
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtItemName(dst, value, count);
			}
			else
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumItemName(dst, value, count);
			}
			ApplyCaseMode(dst, caseMode);
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x1E:
		case 0x2A:
		case 0x38:
		case 0x3A:
		case 0x3C:
		case 0x3E:
		case 0x40:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			int value = CMes::m_tempVar[varIndex];
			if ((tag == 0x2A) || (tag == 0x38))
			{
				strcpy(dst, FLAT_NAME_DIRECT(1, value * 5 + 1));
			}
			else if (tag == 0x1E)
			{
				strcpy(dst, FLAT_NAME_DIRECT(1, value * 5));
			}
			else if (tag == 0x3A)
			{
				strcpy(dst, FLAT_NAME_DIRECT(1, value * 5 + 3));
			}
			else if (tag == 0x3C)
			{
				Game.MakeArtMonName(dst, value, 1);
			}
			else if (tag == 0x3E)
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtMonName(dst, value, count);
			}
			else
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumMonName(dst, value, count);
			}
			ApplyCaseMode(dst, caseMode);
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2B:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, FLAT_NAME_DIRECT(2, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2C:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, FLAT_NAME_DIRECT(3, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2D:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, FLAT_NAME_DIRECT(3, CMes::m_tempVar[varIndex] + 0x3C));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2E:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 2);
			strcpy(dst, FLAT_NAME_DIRECT(5, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			next = in + 4;
			break;
		}
		case 0x2F:
			strcpy(dst, s_mesFallback);
			dst += strlen(dst);
			break;
		case 0x30:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 2);
			sprintf(dst, s_mesNumFmt, CMes::m_tempVar[varIndex]);
			dst += strlen(dst);
			next = in + 4;
			break;
		}
		case 0x41:
		{
			unsigned char mode = (unsigned char)GetMesNibbleValue((const char*)in + 2);
			if (mode == 1)
			{
				caseMode = 1;
			}
			else if (mode == 0)
			{
				caseMode = 3;
			}
			else
			{
				caseMode = 2;
			}
			next = in + 4;
			break;
		}
		case 0x42:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 2);
			branchMode = (CMes::m_tempVar[varIndex] == 1) ? 1 : 2;
			next = in + 4;
			break;
		}
		case 0x44:
			branchMode = (playerIndex == 0) ? 1 : 2;
			break;
		case 0x45:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 2);
			int caravanIdx = CMes::m_tempVar[varIndex];
			branchMode = (Game.m_caravanWorkArr[caravanIdx].m_genderFlag == 0) ? 1 : 2;
			next = in + 4;
			break;
		}
		case 0x46:
			if (branchMode == 1)
			{
				branchMode = 2;
			}
			else if (branchMode == 2)
			{
				branchMode = 1;
			}
			break;
		case 0x47:
			branchMode = 0;
			break;
		case 0x54:
			strcpy(dst, sTag54Source);
			dst += strlen(dst);
			break;
		case 0x0C:
		case 0x0E:
		case 0x13:
		case 0x14:
			if ((unsigned int)System.m_execParam > 1U)
			{
				System.Printf(const_cast<char*>(s_mesTagMissing), tag + 0xA0);
			}
			break;
		case 2:
		case 3:
		case 7:
		case 0x0A:
		case 0x0B:
		case 0x0D:
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x29:
		case 0x55:
			if (System.m_execParam != 0)
			{
				System.Printf(const_cast<char*>(s_mesTagUnknown), tag + 0xA0);
			}
			break;
		default:
			break;
		}

		in = next;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80098bc4
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMes::useFlag(int maxCount, int stopOnClear)
{
	unsigned char* flagEntry = (unsigned char*)((char*)this + *(int*)((char*)this + 0x3c10) * 6 + 0x3c14);
	while (*(int*)((char*)this + 0x3c10) < maxCount)
	{
		int type = *flagEntry;

		if (type != 3)
		{
			if (type < 3)
			{
				if (type != 1)
				{
					if (type != 0)
					{
						*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0) =
						    (int)*(short*)(flagEntry + 4);
					}
				}
				else
				{
					int* slot = (int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0);
					*slot = *slot + 1;
				}
			}
			else if ((type < 5) &&
			         (*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0) == 0) &&
			         (stopOnClear == 0))
			{
				return 0;
			}
		}

		flagEntry += 6;
		*(int*)((char*)this + 0x3c10) = *(int*)((char*)this + 0x3c10) + 1;
	}

	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::SetPosition(float x, float y)
{
	*(float*)&mData[0x3c8c] = x;
	*(float*)&mData[0x3c90] = y;
}

/*
 * --INFO--
 * PAL Address: 0x80098c90
 * PAL Size: 1600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::Draw()
{
	if (*(int*)((char*)this + 8) != 0)
	{
		int globalAlpha;
		bool fading = false;
		if ((*(int*)((char*)this + 0x3CAC) != 0) && (*(int*)((char*)this + 0x3CB8) != 0))
		{
			fading = true;
		}
		if (fading)
		{
			globalAlpha = 0xFF - (*(int*)((char*)this + 0x3CBC) * 0xFF) / *(int*)((char*)this + 0x3CB8);
		}
		else
		{
			globalAlpha = 0xFF;
		}

		unsigned char* menuPcs = reinterpret_cast<unsigned char*>(&MenuPcs);
		float* glyph = (float*)((char*)this + 0x0C);
		CFont* font = 0;
		unsigned int activeTlut = 0xFFFFFFFF;
		unsigned int activeFontId = 0xFFFFFFFF;

		for (int i = 0; i < *(int*)((char*)this + 8); i++)
		{
			CFont* nextFont = font;
			if (*(int*)((char*)this + 0x3C80) >= (int)(unsigned int)*(unsigned short*)((char*)glyph + 0x0C))
			{
				unsigned int ch = (unsigned int)*(unsigned char*)(glyph + 4);
				if (ch < 0x20)
				{
					if (font != 0)
					{
						font->DrawQuit();
					}
					MenuPcs.DrawInit();

					int iconId = ch;
					switch (ch + 0x48)
					{
					case 0x4F:
					{
						int mode;
						bool specialPad = false;
						if ((Game.m_currentMapId == 0x21) && (Joybus.GetPadType(0) != 0x40))
						{
							specialPad = true;
						}
						if (specialPad)
						{
							int padType = Joybus.GetPadType(0);
							mode = (unsigned int)(((0x40000 - padType) | (padType - 0x40000)) >> 31);
						}
						else
						{
							mode = (unsigned int)Game.m_gameWork.m_menuStageMode;
						}
						iconId = (mode != 0) ? 7 : 0x0B;
						break;
					}
					case 0x50:
					{
						int mode;
						bool specialPad = false;
						if ((Game.m_currentMapId == 0x21) && (Joybus.GetPadType(0) != 0x40))
						{
							specialPad = true;
						}
						if (specialPad)
						{
							int padType = Joybus.GetPadType(0);
							mode = (unsigned int)(((0x40000 - padType) | (padType - 0x40000)) >> 31);
						}
						else
						{
							mode = (unsigned int)Game.m_gameWork.m_menuStageMode;
						}
						iconId = (mode != 0) ? 8 : 0x0C;
						break;
					}
					case 0x52:
					{
						int mode;
						bool specialPad = false;
						if ((Game.m_currentMapId == 0x21) && (Joybus.GetPadType(0) != 0x40))
						{
							specialPad = true;
						}
						if (specialPad)
						{
							int padType = Joybus.GetPadType(0);
							mode = (unsigned int)(((0x40000 - padType) | (padType - 0x40000)) >> 31);
						}
						else
						{
							mode = (unsigned int)Game.m_gameWork.m_menuStageMode;
						}
						iconId = (mode != 0) ? 9 : 0x0D;
						break;
					}
					case 0x53:
					{
						int mode;
						bool specialPad = false;
						if ((Game.m_currentMapId == 0x21) && (Joybus.GetPadType(0) != 0x40))
						{
							specialPad = true;
						}
						if (specialPad)
						{
							int padType = Joybus.GetPadType(0);
							mode = (unsigned int)(((0x40000 - padType) | (padType - 0x40000)) >> 31);
						}
						else
						{
							mode = (unsigned int)Game.m_gameWork.m_menuStageMode;
						}
						iconId = (mode != 0) ? 0x0A : 0x0E;
						break;
					}
					}

					CColor color(0xFF, 0xFF, 0xFF, 0xFF);
					MenuPcs.SetColor(color);
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x15));

					MenuPcs.DrawRect(
					    0, *(float*)((char*)this + 0x3C9C) + *glyph,
					    FLOAT_80330890 + *(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2),
					    FLOAT_80330894, FLOAT_80330894, (float)((iconId % 5) * 0x16),
					    (float)((iconId / 5) * 0x16), FLOAT_80330898, FLOAT_80330898, 0.0f);

					if (font != 0)
					{
						font->DrawInit();
					}
				}
				else
				{
					unsigned int fontId = (unsigned int)*(unsigned char*)((char*)glyph + 0x0E) & 0x0F;
					if (activeFontId != fontId)
					{
						nextFont = *reinterpret_cast<CFont**>(menuPcs + 0x100);
						if (fontId != 2)
						{
							if (fontId < 2)
							{
								nextFont = *reinterpret_cast<CFont**>(menuPcs + 0x0F8);
								if (fontId != 0)
								{
									nextFont = font;
								}
							}
							else
							{
								nextFont = font;
								if (fontId < 4)
								{
									nextFont = *reinterpret_cast<CFont**>(menuPcs + 0x100);
								}
							}
						}

						nextFont->SetShadow(*(int*)((char*)this + 0x3D38));
						nextFont->SetMargin(FLOAT_8033089c);
						float fontScaleY = *(float*)((char*)this + 0x3D48);
						nextFont->SetScaleX(*(float*)((char*)this + 0x3D44));
						nextFont->SetScaleY(fontScaleY);
						nextFont->DrawInit();
						activeFontId = fontId;
						font = nextFont;
					}

					unsigned int fadeCur = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) & 0x0F;
					unsigned int fadeMax = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) >> 4;
					float ratio = (float)fadeCur / (float)fadeMax;
					unsigned char alpha;
					if (ratio >= FLOAT_80330898)
					{
						alpha = (unsigned char)globalAlpha;
					}
					else
					{
						alpha = (unsigned char)((float)globalAlpha * ratio);
					}

					_GXColor color = {0xFF, 0xFF, 0xFF, alpha};
					font->SetColor(color);

					unsigned int tlut = (unsigned int)*(unsigned char*)((char*)glyph + 0x12);
					if ((activeTlut != tlut) && (((unsigned int)*(unsigned char*)((char*)glyph + 0x0E) & 0x0F) < 2))
					{
						font->SetTlut((int)tlut + *(int*)((char*)this + 0x3D34));
						activeTlut = tlut;
					}

					font->SetPosX(*(float*)((char*)this + 0x3C9C) + *glyph);
					font->SetPosY(*(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2));
					float glyphScaleY = FLOAT_803308a0 * (float)*(unsigned char*)((char*)glyph + 0x11);
					font->SetScaleX(FLOAT_803308a0 * (float)*(unsigned char*)((char*)glyph + 0x0A));
					font->SetScaleY(glyphScaleY);
					font->renderFlags = font->renderFlags & 0xF7 | 8;
					font->Draw((unsigned short)ch);
					font->renderFlags &= 0xF7;
				}
			}

			glyph += 5;
			font = nextFont;
		}

		font->DrawQuit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800992d0
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::Calc()
{
	if (*(int*)((char*)this + 8) == 0)
	{
		return;
	}

	int textEntry = (int)((char*)this + 0xC);
	unsigned int maxAdvance = 0;
	for (int i = 0; i < *(int*)((char*)this + 8); i++)
	{
		if ((int)(unsigned int)*(unsigned short*)(textEntry + 0xC) <= *(int*)((char*)this + 0x3C80))
		{
			int fadeMax = *(unsigned char*)(textEntry + 0xF) >> 4;
			int fadeCurr = (*(unsigned char*)(textEntry + 0xF) & 0xF) + 1;
			if (fadeCurr < fadeMax)
			{
				fadeMax = fadeCurr;
			}
			*(unsigned char*)(textEntry + 0xF) =
			    (unsigned char)((fadeMax & 0xF) | (*(unsigned char*)(textEntry + 0xF) & 0xF0));
			maxAdvance = (unsigned int)*(unsigned char*)(textEntry + 0x13);
		}
		textEntry += 0x14;
	}

	unsigned char* flagEntry =
	    (unsigned char*)((char*)this + *(int*)((char*)this + 0x3C10) * 6 + 0x3C14);
	while ((int)maxAdvance > *(int*)((char*)this + 0x3C10))
	{
		int type = *flagEntry;
		if (type != 3)
		{
			if (type < 3)
			{
				if (type != 1)
				{
					if (type != 0)
					{
						*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0) =
						    (int)*(short*)(flagEntry + 4);
					}
				}
				else
				{
					int* slot = (int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0);
					*slot = *slot + 1;
				}
			}
			else if ((type < 5) &&
			         (*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0) == 0))
			{
				goto doneAdvance;
			}
		}

		flagEntry += 6;
		*(int*)((char*)this + 0x3C10) = *(int*)((char*)this + 0x3C10) + 1;
	}

	{
		int next = *(int*)((char*)this + 0x3C80) + 1;
		int max = 0x7FFF;
		if (next < 0x7FFF)
		{
			max = next;
		}
		*(int*)((char*)this + 0x3C80) = max;
	}

doneAdvance:
	if (*(int*)((char*)this + 0x3CAC) != 0)
	{
		int next = *(int*)((char*)this + 0x3CBC) + 1;
		int max = *(int*)((char*)this + 0x3CB8);
		if (next < max)
		{
			max = next;
		}
		*(int*)((char*)this + 0x3CBC) = max;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80099440
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMes::GetWait()
{
	if (*(int*)((char*)this + 0x3c7c) < *(int*)((char*)this + 0x3c80))
	{
		return *(int*)((char*)this + 0x3c78);
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80099460
 * PAL Size: 6900b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::addString(char** text, int branchMode)
{
	unsigned char* menuPcs = reinterpret_cast<unsigned char*>(&MenuPcs);
	CFont* font = *reinterpret_cast<CFont**>(menuPcs + 0x100);
	int fontSel = *(int*)((char*)this + 0x3D40);
	int caseMode = 0;
	int flowMode = branchMode;
	if (fontSel == 0)
	{
		font = *reinterpret_cast<CFont**>(menuPcs + 0x0F8);
	}
	else if ((fontSel == 1) || (fontSel >= 4))
	{
		// Keep current font pointer selection for unsupported modes.
	}
	else
	{
		font = *reinterpret_cast<CFont**>(menuPcs + 0x100);
	}

	font->SetShadow(*(int*)((char*)this + 0x3D38));
	font->SetMargin(FLOAT_8033089c);
	font->SetScaleX(*(float*)((char*)this + 0x3D44));
	font->SetScaleY(*(float*)((char*)this + 0x3D48));

	for (;;)
	{
		unsigned char ch = (unsigned char)**text;
		*text = *text + 1;

		if (ch == 0)
		{
			return;
		}

		if (ch == 0xFF)
		{
			unsigned int tag = ((unsigned int)(unsigned char)**text - 0xA0U) & 0xFFFFU;
			*text = *text + 1;

			switch (tag)
			{
			case 0:
				AdvanceMesLine(this, font);
				break;
			case 1:
			{
				int wait = 2;
				if (*(int*)((char*)this + 0x3D10) != 0)
				{
					wait = 3;
				}
				*(int*)((char*)this + 0x3C78) = wait;
				*(int*)((char*)this + 0x3C74) = 1;
				AdvanceMesLine(this, font);
				return;
			}
			case 2:
				*(int*)((char*)this + 0x3C78) = 4;
				*(int*)((char*)this + 0x3C74) = 1;
				AdvanceMesLine(this, font);
				return;
			case 0x24:
				*(int*)((char*)this + 0x3C78) = 2;
				AdvanceMesLine(this, font);
				return;
			case 0x28:
				*(int*)((char*)this + 0x3C78) = 1;
				AdvanceMesLine(this, font);
				return;
			case 0x29:
				*(int*)((char*)this + 0x3C78) = 5;
				*(int*)((char*)this + 0x3C74) = 1;
				AdvanceMesLine(this, font);
				return;
			case 3:
				*(int*)((char*)this + 0x3C7C) = *(int*)((char*)this + 0x3C7C) + ReadTagS8(text);
				break;
			case 4:
				*(int*)((char*)this + 0x3D2C) = 0;
				break;
			case 5:
				*(int*)((char*)this + 0x3D2C) = 2;
				break;
			case 6:
				*(int*)((char*)this + 0x3D2C) = 1;
				break;
			case 7:
				*(int*)((char*)this + 0x3D10) = 1;
				*(int*)((char*)this + 0x3D14) = 0;
				*(int*)((char*)this + 0x3D18) = ReadTagS8(text);
				*(int*)((char*)this + 0x3D24) =
				    (int)(FLOAT_803308a4 + (float)font->m_glyphHeight * font->scaleY);
				*(int*)((char*)this + 0x3D20) = *(int*)((char*)this + 0x3C88);
				*(int*)((char*)this + 0x3D1C) = ReadTagS8(text);
				*(float*)((char*)this + 0x3C84) =
				    *(float*)((char*)this + 0x3C84) + FLOAT_803308A8 + *(float*)((char*)this + 0x3D3C);
				break;
			case 8:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 6;
				}
				char* flatText = FLAT_NAME_DIRECT(5, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
				addString(&flatText, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 9:
			case 0x19:
			case 0x1D:
			case 0x37:
			case 0x39:
			case 0x3B:
			case 0x3D:
			case 0x3F:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 5;
				}
				char name[32];
				char* namePtr = name;
				int value = CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF;
				switch (tag)
				{
				case 9:
				case 0x37:
					strcpy(namePtr, FLAT_NAME_DIRECT(0, value * 5 + 1));
					break;
				case 0x1D:
					strcpy(namePtr, FLAT_NAME_DIRECT(0, value * 5));
					break;
				case 0x3B:
					Game.MakeArtItemName(namePtr, value, 1);
					break;
				case 0x19:
					Game.MakeArtsItemNames(namePtr, value);
					break;
				case 0x3D:
					Game.MakeArtItemName(namePtr, value, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
					break;
				case 0x3F:
					Game.MakeNumItemName(namePtr, value, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
					break;
				case 0x39:
					strcpy(namePtr, FLAT_NAME_DIRECT(0, value * 5 + 3));
					break;
				}
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 0x1E:
			case 0x1F:
			case 0x2A:
			case 0x38:
			case 0x3A:
			case 0x3C:
			case 0x3E:
			case 0x40:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 0;
				}
				char name[32];
				char* namePtr = name;
				int value = CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF;
				switch (tag)
				{
				case 0x1E:
					strcpy(namePtr, FLAT_NAME_DIRECT(1, value * 5));
					break;
				case 0x2A:
				case 0x38:
					strcpy(namePtr, FLAT_NAME_DIRECT(1, value * 5 + 1));
					break;
				case 0x3C:
					Game.MakeArtMonName(namePtr, value, 1);
					break;
				case 0x1F:
					Game.MakeArtsMonNames(namePtr, value);
					break;
				case 0x3E:
					Game.MakeArtMonName(namePtr, value, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
					break;
				case 0x40:
					Game.MakeNumMonName(namePtr, value, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
					break;
				case 0x3A:
					strcpy(namePtr, FLAT_NAME_DIRECT(1, value * 5 + 3));
					break;
				}
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 0x2B:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 6;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FLAT_NAME_DIRECT(2, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 0x2C:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 4;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FLAT_NAME_DIRECT(3, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 0x2D:
			{
				int oldColor = *(int*)((char*)this + 0x3D28);
				if (ReadTagU8(text) != 0)
				{
					*(int*)((char*)this + 0x3D28) = 3;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FLAT_NAME_DIRECT(3, (CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF) + 0x3C));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				*(int*)((char*)this + 0x3D28) = oldColor;
				break;
			}
			case 0x2E:
			{
				char* flatText = FLAT_NAME_DIRECT(5, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
				addString(&flatText, branchMode);
				break;
			}
			case 0x2F:
			{
				char* fallback = (char*)s_mesFallback;
				addString(&fallback, branchMode);
				break;
			}
			case 0x30:
			{
				char number[256];
				char* numberPtr = number;
				sprintf(numberPtr, s_mesNumFmt, CMes::m_tempVar[(signed char)ReadTagU8(text)]);
				addString(&numberPtr, branchMode);
				break;
			}
			case 0x0A:
			{
				unsigned char idx = (unsigned char)ReadTagU8(text);
				short value = (short)ReadTagS16(text);
				CMes::m_tempVar[idx] = value;
				if (branchMode == 0)
				{
					AddMesFlag(this, 2, idx, value);
				}
				break;
			}
			case 0x0B:
			{
				unsigned char idx = (unsigned char)ReadTagU8(text);
				CMes::m_tempVar[idx] = CMes::m_tempVar[idx] + 1;
				if (branchMode == 0)
				{
					AddMesFlag(this, 1, idx, 0);
				}
				break;
			}
			case 0x0C:
			case 0x0D:
			case 0x0E:
			case 0x0F:
			case 0x10:
			case 0x11:
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
				*(int*)((char*)this + 0x3D28) = (int)tag - 0x0C;
				break;
			case 0x1A:
				*(float*)((char*)this + 0x3D44) = FLOAT_803308a0 * (float)ReadTagS16(text);
				font->SetScaleX(*(float*)((char*)this + 0x3D44));
				font->SetScaleY(*(float*)((char*)this + 0x3D48));
				break;
			case 0x1B:
			{
				int idx = ReadTagU8(text);
				flowMode = ((CMes::m_tempVar[idx] & 1) == 0) ? 1 : 2;
				break;
			}
			case 0x1C:
			{
				int idx = ReadTagU8(text);
				flowMode = ((CMes::m_tempVar[idx] & 1) != 0) ? 1 : 2;
				break;
			}
			case 0x25:
			{
				int value = ReadTagS8(text);
				if (*(int*)((char*)this + 0x3D30) == 0)
				{
					if (value == 0x7F)
					{
						*(int*)((char*)this + 0x3D4C) = 0;
					}
					else
					{
						*(int*)((char*)this + 0x3CB0) = value;
					}
				}
				else if (System.m_execParam != 0)
				{
					System.Printf(const_cast<char*>(s_mesTagUnknown), tag + 0xA0);
				}
				break;
			}
			case 0x26:
				*(int*)((char*)this + 0x3CB4) = ReadTagS8(text);
				break;
			case 0x27:
				*(int*)((char*)this + 0x3CB8) = ReadTagS8(text);
				break;
			case 0x31:
				*(float*)((char*)this + 0x3C84) = (float)ReadTagS16(text);
				*(float*)((char*)this + 0x3C88) = (float)ReadTagS16(text);
				break;
			case 0x32:
				*(int*)((char*)this + 0x3D28) = 9;
				break;
			case 0x33:
				*(float*)((char*)this + 0x3D3C) = (float)ReadTagS8(text);
				break;
			case 0x34:
			{
				*(int*)((char*)this + 0x3D40) = ReadTagS8(text);
				int nextFontSel = *(int*)((char*)this + 0x3D40);
				if (nextFontSel == 0)
				{
					font = *reinterpret_cast<CFont**>(menuPcs + 0x0F8);
				}
				else
				{
					font = *reinterpret_cast<CFont**>(menuPcs + 0x100);
				}
				font->SetShadow(*(int*)((char*)this + 0x3D38));
				font->SetMargin(FLOAT_8033089c);
				font->SetScaleX(*(float*)((char*)this + 0x3D44));
				font->SetScaleY(*(float*)((char*)this + 0x3D48));
				break;
			}
			case 0x35:
			{
				float scale = FLOAT_803308a0 * (float)ReadTagS16(text);
				*(float*)((char*)this + 0x3D48) = scale;
				*(float*)((char*)this + 0x3D44) = scale;
				font->SetScaleX(*(float*)((char*)this + 0x3D44));
				font->SetScaleY(*(float*)((char*)this + 0x3D48));
				break;
			}
			case 0x36:
			{
				unsigned char idx = (unsigned char)ReadTagU8(text);
				if (branchMode == 0)
				{
					AddMesFlag(this, 4, idx, 0);
				}
				break;
			}
			case 0x41:
			{
				int mode = ReadTagU8(text);
				if (mode == 1)
				{
					caseMode = 1;
				}
				else if (mode == 0)
				{
					caseMode = 3;
				}
				else
				{
					caseMode = 2;
				}
				break;
			}
			case 0x42:
			{
				int idx = ReadTagU8(text);
				flowMode = (CMes::m_tempVar[idx] == 1) ? 1 : 2;
				break;
			}
			case 0x43:
				flowMode = (Game.m_gameWork.m_menuStageMode != 0) ? 1 : 2;
				break;
			case 0x44:
				flowMode = (Game.m_caravanWorkArr[*(int*)((char*)this + 0x3D0C)].m_genderFlag == 0) ? 1 : 2;
				break;
			case 0x45:
			{
				int idx = ReadTagU8(text);
				flowMode = (Game.m_caravanWorkArr[CMes::m_tempVar[idx]].m_genderFlag == 0) ? 1 : 2;
				break;
			}
			case 0x46:
				if (flowMode == 1)
				{
					flowMode = 2;
				}
				else if (flowMode == 2)
				{
					flowMode = 1;
				}
				break;
			case 0x47:
				flowMode = 0;
				break;
			case 0x48:
			case 0x49:
			case 0x4A:
			case 0x4B:
			case 0x4C:
			case 0x4D:
			case 0x4E:
			case 0x4F:
			case 0x50:
			case 0x52:
			case 0x53:
				ch = (unsigned char)(tag - 0x48U);
				goto render_char;
			default:
				break;
			}
			continue;
		}

render_char:
		if (flowMode == 2)
		{
			continue;
		}

		float* glyph = (float*)((char*)this + *(int*)((char*)this + 8) * 0x14 + 0x0C);
		*(unsigned char*)((char*)glyph + 0x12) = (unsigned char)*(int*)((char*)this + 0x3D28);
		*(unsigned char*)((char*)glyph + 0x10) = ch;
		glyph[0] = *(float*)((char*)this + 0x3C84);
		glyph[2] = *(float*)((char*)this + 0x3C88);

		font->renderFlags = (font->renderFlags & 0xF7) | 8;
		if (ch < 0x20)
		{
			glyph[1] = FLOAT_80330894;
		}
		else
		{
			glyph[1] = font->GetWidth(ch);
		}
		font->renderFlags &= 0xF7;

		*(unsigned short*)((char*)glyph + 0x0C) = (unsigned short)*(int*)((char*)this + 0x3C7C);
		*(unsigned char*)((char*)glyph + 0x0F) =
		    (unsigned char)(*(int*)((char*)this + 0x3CB4) << 4) | (*(unsigned char*)((char*)glyph + 0x0F) & 0x0F);
		*(unsigned char*)((char*)glyph + 0x0F) = *(unsigned char*)((char*)glyph + 0x0F) & 0xF0;
		*(unsigned char*)((char*)glyph + 0x13) = (unsigned char)*(int*)((char*)this + 0x3C0C);
		*(unsigned char*)((char*)glyph + 0x0E) =
		    (unsigned char)(*(int*)((char*)this + 0x3D2C) << 4) | (*(unsigned char*)((char*)glyph + 0x0E) & 0x0F);
		*(unsigned char*)((char*)glyph + 0x0E) =
		    (unsigned char)((*(int*)((char*)this + 0x3D40) & 0x0F) | (*(unsigned char*)((char*)glyph + 0x0E) & 0xF0));
		*(unsigned char*)((char*)glyph + 0x0A) = (unsigned char)(FLOAT_803308ac * *(float*)((char*)this + 0x3D44));
		*(unsigned char*)((char*)glyph + 0x11) = (unsigned char)(FLOAT_803308ac * *(float*)((char*)this + 0x3D48));

		*(float*)((char*)this + 0x3C84) =
		    *(float*)((char*)this + 0x3C84) + glyph[1] + *(float*)((char*)this + 0x3D3C);
		if (*(int*)((char*)this + 0x3D4C) == 0)
		{
			*(int*)((char*)this + 0x3C7C) = *(int*)((char*)this + 0x3C7C) + *(int*)((char*)this + 0x3CB0);
		}
		else
		{
			int step = *(int*)((char*)this + 0x3CB0);
			if ((*(int*)((char*)this + 8) & 1) == 0)
			{
				*(int*)((char*)this + 0x3C7C) = *(int*)((char*)this + 0x3C7C) + (step / 2);
			}
			else
			{
				*(int*)((char*)this + 0x3C7C) = *(int*)((char*)this + 0x3C7C) + (step - (step / 2));
			}
		}
		*(int*)((char*)this + 8) = *(int*)((char*)this + 8) + 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009af54
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMes::Next()
{
	unsigned int type;
	float groupWidth;
	float halfVal;
	int remaining;
	unsigned int runLength;
	int i;
	unsigned char* flagEntry;
	float* start;
	int entryCount;
	float* curr;
	char* mesFlags = (char*)this + 0x3cc0;
	char** mesText = (char**)((char*)this + 4);
	char tempFlags[0x50];

	if (*mesText != 0)
	{
		entryCount = *(int*)((char*)this + 0x3c0c);
		flagEntry = (unsigned char*)((char*)this + *(int*)((char*)this + 0x3c10) * 6 + 0x3c14);
		while ((halfVal = FLOAT_8033089c, *(int*)((char*)this + 0x3c10) < entryCount))
		{
			type = *flagEntry;
			if ((type != 3) && (type < 3))
			{
				if (type != 1)
				{
					if (type != 0)
					{
						*(int*)(mesFlags + (unsigned int)flagEntry[2] * 4) =
						    (int)*(short*)(flagEntry + 4);
					}
				}
				else
				{
					int* slot = (int*)(mesFlags + (unsigned int)flagEntry[2] * 4);
					*slot = *slot + 1;
				}
			}
			flagEntry += 6;
			*(int*)((char*)this + 0x3c10) = *(int*)((char*)this + 0x3c10) + 1;
		}
		*(int*)((char*)this + 8) = 0;
		*(int*)((char*)this + 0x3c10) = 0;
		*(int*)((char*)this + 0x3c0c) = 0;
		*(float*)((char*)this + 0x3c88) = halfVal;
		*(float*)((char*)this + 0x3c84) = halfVal;
		*(float*)((char*)this + 0x3c90) = halfVal;
		*(float*)((char*)this + 0x3c8c) = halfVal;
		*(int*)((char*)this + 0x3c80) = 0;
		*(int*)((char*)this + 0x3c7c) = 0;
		*(int*)((char*)this + 0x3cac) = 0;
		memcpy(tempFlags, mesFlags, sizeof(tempFlags));
		addString(mesText, 0);
		memcpy(mesFlags, tempFlags, sizeof(tempFlags));
		halfVal = FLOAT_803308b0;
		i = 0;
		curr = (float*)((char*)this + 0xc);
		while ((start = curr, remaining = *(int*)((char*)this + 8), i < remaining))
		{
			i = i + 1;
			curr = start + 5;
			entryCount = remaining - i;
			if (i < remaining)
			{
				do
				{
					if (((*(unsigned char*)((char*)start + 0xe) >> 4) != (*(unsigned char*)((char*)curr + 0xe) >> 4)) ||
					    (*(short*)(start + 2) != *(short*)(curr + 2)))
					{
						break;
					}
					i = i + 1;
					curr = curr + 5;
					entryCount = entryCount + -1;
				} while (entryCount != 0);
			}
			runLength = (unsigned int)((int)curr - (int)start) / 0x14;
			groupWidth = (curr[-5] - *start) + start[1] + *(float*)((char*)this + 0x3d3c);
			if (start <= curr - 5)
			{
				do
				{
					type = (unsigned int)*(unsigned char*)((char*)start + 0xe) >> 4;
					if (type == 1)
					{
						*start = halfVal * (*(float*)((char*)this + 0x3ca4) - groupWidth) + *start;
					}
					else if (type == 2)
					{
						*start = *start + (*(float*)((char*)this + 0x3ca4) - groupWidth);
					}
					start = start + 5;
					runLength = runLength - 1;
				} while (runLength != 0);
			}
		}
	}
}

/*
 * --INFO--
 * Address: 8009b168
 * Size: 436b
 */
void CMes::Set(char* text, int param)
{
	float zero = FLOAT_8033089c;
	float one = FLOAT_80330898;
	*(int*)((char*)this + 4) = (int)text;
	*(int*)((char*)this + 0x3c74) = 0;
	*(float*)((char*)this + 0x3ca8) = zero;
	*(float*)((char*)this + 0x3ca4) = zero;
	*(int*)((char*)this + 8) = 0;
	*(int*)((char*)this + 0x3c10) = 0;
	*(int*)((char*)this + 0x3c0c) = 0;
	*(int*)((char*)this + 0x3d10) = 0;
	*(int*)((char*)this + 0x3d30) = param;
	*(float*)((char*)this + 0x3d3c) = zero;
	*(int*)((char*)this + 0x3d40) = 0;
	*(float*)((char*)this + 0x3d44) = one;
	*(float*)((char*)this + 0x3d48) = one;
	*(int*)((char*)this + 0x3d4c) = 1;

	if (text != 0) {
		unsigned char flagBackup[0x50];
		memcpy(flagBackup, (char*)this + 0x3cc0, sizeof(flagBackup));
		float lineZero = FLOAT_8033089c;

		while (*(int*)((char*)this + 0x3c74) == 0) {
			*(int*)((char*)this + 8) = 0;
			*(int*)((char*)this + 0x3c10) = 0;
			*(int*)((char*)this + 0x3c0c) = 0;
			*(float*)((char*)this + 0x3c88) = lineZero;
			*(float*)((char*)this + 0x3c84) = lineZero;
			*(float*)((char*)this + 0x3c90) = lineZero;
			*(float*)((char*)this + 0x3c8c) = lineZero;

			addString((char**)((char*)this + 4), 1);

			float width = *(float*)((char*)this + 0x3c8c);
			if (width < *(float*)((char*)this + 0x3ca4)) {
				width = *(float*)((char*)this + 0x3ca4);
			}
			*(float*)((char*)this + 0x3ca4) = width;

			float height = *(float*)((char*)this + 0x3c90);
			if (height < *(float*)((char*)this + 0x3ca8)) {
				height = *(float*)((char*)this + 0x3ca8);
			}
			*(float*)((char*)this + 0x3ca8) = height;
		}

		memcpy((char*)this + 0x3cc0, flagBackup, sizeof(flagBackup));
		float lineSkip = FLOAT_803308a4;
		zero = FLOAT_8033089c;
		one = FLOAT_80330898;
		*(float*)((char*)this + 0x3ca4) = *(float*)((char*)this + 0x3ca4) - *(float*)((char*)this + 0x3d3c);
		*(float*)((char*)this + 0x3ca8) = *(float*)((char*)this + 0x3ca8) - lineSkip;

		*(int*)((char*)this + 4) = (int)text;
		*(int*)((char*)this + 0x3c74) = 0;
		*(int*)((char*)this + 0x3cb0) = (unsigned int)__cntlzw((unsigned int)param) >> 5;
		*(int*)((char*)this + 0x3cb4) = 3;
		*(int*)((char*)this + 0x3cb8) = 0;
		*(int*)((char*)this + 0x3d10) = 0;
		*(int*)((char*)this + 0x3d2c) = 0;
		*(int*)((char*)this + 0x3d28) = 7;
		*(float*)((char*)this + 0x3d3c) = zero;
		*(int*)((char*)this + 0x3d40) = 0;
		*(float*)((char*)this + 0x3d44) = one;
		*(float*)((char*)this + 0x3d48) = one;
		*(int*)((char*)this + 0x3d4c) = 1;
		Next();
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMes::~CMes()
{
	// Destructor - no dynamic allocation to clean up in basic implementation
}

/*
 * --INFO--
 * Address: 8009b358
 * Size: 92b
 */
CMes::CMes()
{
	mText = 0;
	mCounter = 0;
	*(int*)((char*)this + 0x3c10) = 0;
	*(int*)((char*)this + 0x3c0c) = 0;
	*(int*)((char*)this + 0x3d34) = 0;
	*(int*)((char*)this + 0x3d38) = 1;
	memset((char*)this + 0x3cc0, 0, 0x50);
}
