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

extern float kMesIconDrawYOffset;
extern float kMesIconDefaultWidth;
extern float kMesOne;
extern float kMesZero;
extern float kMesTagScaleStep;
extern float kMesLineHeightAdjust;
extern float kMesRubyLineIndent;
extern float kMesPackedScaleFactor;
extern float kMesHalf;
// PAL map: CMes::m_tempVar in mes.o, .bss size 0x50.
int CMes::m_tempVar[0x14];

extern char lbl_801D9E58[];

static const char s_Not_corresponding_TAG_is_used_pct02x_801D9E30[] = "Not corresponding TAG is used. %02x\n";
static const char s_This_TAG_is_not_created_pct02x_801D9E10[] = "This TAG is not created. %02x\n";
static const char s_mesNumFmt[] = "%d";
static const char s_mesFallback[] = "---";
static const char s_mesEmpty[] = "";
static char* sTag54Source;
static char sTag54Init;

struct CFontRenderFlagBits
{
	signed char shadow : 1;
	signed char zCompare : 1;
	signed char zUpdate : 1;
	signed char fixedWidth : 1;
	signed char snapPosition : 1;
	signed char pad : 3;
};

static inline CFontRenderFlagBits& GetRenderFlagBits(unsigned char& flags)
{
	return reinterpret_cast<CFontRenderFlagBits&>(flags);
}

// One drawn character record inside CMes (this+0xC, stride 0x14).
struct CMesCharCell
{
	float m_x;                     // 0x00
	float m_width;                 // 0x04
	short m_y;                     // 0x08
	unsigned char m_scaleX;        // 0x0A
	char m_pad0B;                  // 0x0B
	short m_reveal;                // 0x0C
	unsigned char m_fontAlign : 4; // 0x0E hi
	unsigned char m_fontIndex : 4; // 0x0E lo
	unsigned char m_textAlign : 4; // 0x0F hi
	unsigned char m_pad0F : 4;     // 0x0F lo
	char m_char;                   // 0x10
	unsigned char m_scaleY;        // 0x11
	char m_color;                  // 0x12
	char m_flagCount;              // 0x13
};

static inline int GetMesNibbleValue(const char* data)
{
	signed char high = (signed char)(((unsigned char)data[0] & 0x0F) << 4);
	int low = (unsigned char)data[1] & 0x0F;
	return (int)high | low;
}

static inline char ReadTagByte(char** text)
{
	char* p0 = *text;
	*text = p0 + 1;
	signed char hi = (signed char)((*p0 & 0x0F) << 4);
	char* p1 = *text;
	*text = p1 + 1;
	return (char)(hi | (*p1 & 0x0F));
}

static inline int ReadTagU8(char** text)
{
	return (unsigned char)ReadTagByte(text);
}

static inline int ReadTagS8(char** text)
{
	return (int)ReadTagByte(text);
}

static inline int ReadTagNibble(char** text)
{
	char* p = *text;
	*text = p + 1;
	return *p & 0x0F;
}

static inline int ReadTagS16(char** text)
{
	short acc = (short)(ReadTagNibble(text) << 4);
	acc = (short)(acc | ReadTagNibble(text));
	acc = (short)((short)(acc << 4) | ReadTagNibble(text));
	acc = (short)((short)(acc << 4) | ReadTagNibble(text));
	return (int)acc;
}

#define ApplyCaseMode(text, caseMode)                                     \
	if (caseMode != 0)                                                    \
	{                                                                     \
		if (caseMode == 1)                                                \
		{                                                                 \
			if ((text)[0] != '\0')                                        \
			{                                                             \
				toupper(text);                                            \
			}                                                             \
		}                                                                 \
		else if (caseMode == 2)                                           \
		{                                                                 \
			char* caseModePtr = (text);                                   \
			if (caseModePtr[0] != '\0')                                   \
			{                                                             \
				caseModePtr[0] = (char)toupperLatin1((unsigned char)caseModePtr[0]); \
			}                                                             \
		}                                                                 \
		else                                                              \
		{                                                                 \
			if ((text)[0] != '\0')                                        \
			{                                                             \
				tolower_name_conflict(text);                              \
			}                                                             \
		}                                                                 \
		caseMode = 0;                                                     \
	}

static inline CColor& MesColorRef(const CColor& color)
{
	return (CColor&)color;
}

static inline char* FlatNameDirect(int tableIndex, int entryIndex)
{
	return Game.m_cFlatDataArr[1].TableStrings(tableIndex)[entryIndex];
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
	unsigned short ch;
	float lineStartX = font->posX;

	while (continueDraw)
	{
		ch = (unsigned char)*text++;

		if (ch == 0)
		{
			continueDraw = false;
		}
		else if (ch == 0xFF)
		{
			int tag = ((int)(unsigned char)*text++ - 0xA0) & 0xFFFF;
			switch (tag)
			{
			case 0:
				if (breakOnLineTag != 0)
				{
					font->SetPosX((float)(int)lineStartX);
					float lineAdvance = (float)font->m_glyphHeight * font->scaleY;
					font->SetPosY((float)lineBaseY + (font->posY + lineAdvance));
				}
				break;
			case 1:
				continueDraw = false;
				break;
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
	char* dst = out;
	const unsigned char* in = (const unsigned char*)src;

	if (sTag54Init == 0)
	{
		sTag54Source = (char*)s_mesEmpty;
		sTag54Init = 1;
	}

	unsigned char caseMode = 0;
	unsigned char branchMode = 0;

	const unsigned char* op;
	while ((signed char)*in != 0)
	{
		if (*in == 0xFF)
		{
		unsigned int tag = ((unsigned int)in[1] - 0xA0U) & 0xFFU;
		op = in + 2;
		in++;

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
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(dst, (char*)Game.m_caravanWorkArr[CMes::m_tempVar[varIndex]].m_name);
			dst += strlen(dst);
			in += 4;
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
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			int value = CMes::m_tempVar[varIndex];
			switch (tag)
			{
			case 9:
			case 0x37:
				strcpy(dst, FlatNameDirect(0, value * 5 + 1));
				break;
			case 0x39:
				strcpy(dst, FlatNameDirect(0, value * 5 + 3));
				break;
			case 0x3B:
				Game.MakeArtItemName(dst, value, 1);
				break;
			case 0x3D:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtItemName(dst, value, count);
				break;
			}
			case 0x3F:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumItemName(dst, value, count);
				break;
			}
			case 0x1D:
				strcpy(dst, FlatNameDirect(0, value * 5));
				break;
			}
			ApplyCaseMode(dst, caseMode);
			dst += strlen(dst);
			in += 4;
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
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			int value = CMes::m_tempVar[varIndex];
			switch (tag)
			{
			case 0x2A:
			case 0x38:
				strcpy(dst, FlatNameDirect(1, value * 5 + 1));
				break;
			case 0x3A:
				strcpy(dst, FlatNameDirect(1, value * 5 + 3));
				break;
			case 0x3C:
				Game.MakeArtMonName(dst, value, 1);
				break;
			case 0x3E:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtMonName(dst, value, count);
				break;
			}
			case 0x40:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumMonName(dst, value, count);
				break;
			}
			case 0x1E:
				strcpy(dst, FlatNameDirect(1, value * 5));
				break;
			}
			ApplyCaseMode(dst, caseMode);
			dst += strlen(dst);
			in += 4;
			break;
		}
		case 0x2B:
		{
			signed char varIndex = (unsigned char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(dst, FlatNameDirect(2, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			in += 4;
			break;
		}
		case 0x2C:
		{
			signed char varIndex = (unsigned char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(dst, FlatNameDirect(3, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			in += 4;
			break;
		}
		case 0x2D:
		{
			signed char varIndex = (unsigned char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(dst, FlatNameDirect(3, CMes::m_tempVar[varIndex] + 0x3C));
			dst += strlen(dst);
			in += 4;
			break;
		}
		case 0x2E:
		{
			signed char varIndex = (unsigned char)GetMesNibbleValue((const char*)op);
			strcpy(dst, FlatNameDirect(5, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			in += 2;
			break;
		}
		case 0x2F:
		{
			char* townName = Game.m_gameWork.m_townName;
			strcpy(dst, townName);
			dst += strlen(dst);
			break;
		}
		case 0x30:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			sprintf(dst, s_mesNumFmt, CMes::m_tempVar[varIndex]);
			dst += strlen(dst);
			in += 2;
			break;
		}
		case 0x41:
		{
			signed char mode = (signed char)GetMesNibbleValue((const char*)op);
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
			in += 2;
			break;
		}
		case 0x44:
			branchMode = (playerIndex == 0) ? 1 : 2;
			break;
		case 0x42:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			branchMode = (CMes::m_tempVar[varIndex] == 1) ? 1 : 2;
			in += 2;
			break;
		}
		case 0x45:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			int caravanIdx = CMes::m_tempVar[varIndex];
			branchMode = (Game.m_caravanWorkArr[caravanIdx].m_genderFlag == 0) ? 1 : 2;
			in += 2;
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
			if ((unsigned int)System.m_execParam >= 2U)
			{
				System.Printf(const_cast<char*>(s_This_TAG_is_not_created_pct02x_801D9E10), tag + 0xA0);
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
			if ((unsigned int)System.m_execParam >= 1U)
			{
				System.Printf(const_cast<char*>(s_Not_corresponding_TAG_is_used_pct02x_801D9E30), tag + 0xA0);
			}
			break;
		default:
			break;
		}

		continue;
		}

		if (branchMode != 2)
		{
			*dst = (char)*in;
			dst++;
		}
		in++;
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
	CFlag* flagEntry = &mFlagEntries[mFlagCursor];
	while (mFlagCursor < maxCount)
	{
		int type = flagEntry->m_type;

		switch (type)
		{
		case 2:
			mFlagVars[flagEntry->m_param.m_index] = flagEntry->m_param.m_value;
			break;
		case 1:
		{
			int* slot = &mFlagVars[flagEntry->m_param.m_index];
			*slot = *slot + 1;
			break;
		}
		case 4:
			if ((mFlagVars[flagEntry->m_param.m_index] == 0) && (stopOnClear == 0))
			{
				return 0;
			}
			break;
		}

		flagEntry++;
		mFlagCursor = mFlagCursor + 1;
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
	mBaseX = x;
	mBaseY = y;
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

		float* glyph = (float*)((char*)this + 0x0C);
		CFont* font = 0;
		CFont* nextFont;
		int activeTlut = 0xFFFFFFFF;
		int activeFontId = 0xFFFFFFFF;

		for (int i = 0; i < *(int*)((char*)this + 8); i++)
		{
			if (*(int*)((char*)this + 0x3C80) >= (int)(unsigned int)*(unsigned short*)((char*)glyph + 0x0C))
			{
				if ((unsigned int)*(unsigned char*)(glyph + 4) < 0x20)
				{
					if (font != 0)
					{
						font->DrawQuit();
					}
					MenuPcs.DrawInit();

					int iconId = *(unsigned char*)(glyph + 4);
					switch (iconId + 0x48)
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
							mode = (Joybus.GetPadType(0) != 0x40000);
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
							mode = (Joybus.GetPadType(0) != 0x40000);
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
							mode = (Joybus.GetPadType(0) != 0x40000);
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
							mode = (Joybus.GetPadType(0) != 0x40000);
						}
						else
						{
							mode = (unsigned int)Game.m_gameWork.m_menuStageMode;
						}
						iconId = (mode != 0) ? 0x0A : 0x0E;
						break;
					}
					}

					MenuPcs.SetColor(MesColorRef(CColor(0xFF, 0xFF, 0xFF, 0xFF)));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x15));

					MenuPcs.DrawRect(
					    0, *(float*)((char*)this + 0x3C9C) + *glyph,
					    kMesIconDrawYOffset + (*(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2)),
					    kMesIconDefaultWidth, kMesIconDefaultWidth, (float)((iconId % 5) * 0x16),
					    (float)((iconId / 5) * 0x16), kMesOne, kMesOne, kMesZero);

					if (font != 0)
					{
						font->DrawInit();
					}
				}
				else
				{
					int fontId = (int)((unsigned int)*(unsigned char*)((char*)glyph + 0x0E) & 0x0F);
					if (activeFontId != fontId)
					{
						activeFontId = fontId;
						switch (fontId)
						{
						case 0:
							nextFont = MenuPcs.m_fonts[0];
							break;
						case 2:
							nextFont = MenuPcs.m_fonts[2];
							break;
						case 3:
							nextFont = MenuPcs.m_fonts[2];
							break;
						}

						nextFont->SetShadow(*(int*)((char*)this + 0x3D38));
						nextFont->SetMargin(kMesZero);
						float fontScaleY = *(float*)((char*)this + 0x3D48);
						nextFont->SetScaleX(*(float*)((char*)this + 0x3D44));
						nextFont->SetScaleY(fontScaleY);
						nextFont->DrawInit();
						font = nextFont;
					}

					unsigned int fadeCur = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) & 0x0F;
					unsigned int fadeMax = (*(unsigned char*)((char*)glyph + 0x0F) >> 4) & 0xF;
					float ratio = (float)fadeCur / (float)fadeMax;
					_GXColor color;
					color.r = 0xFF;
					color.g = 0xFF;
					color.b = 0xFF;
					int alpha;
					if (ratio < kMesOne)
					{
						alpha = (unsigned char)(ratio * (float)globalAlpha);
					}
					else
					{
						alpha = globalAlpha;
					}
					color.a = alpha;
					font->SetColor(color);

					int tlut = (int)*(unsigned char*)((char*)glyph + 0x12);
					if ((activeTlut != tlut) && (((unsigned int)*(unsigned char*)((char*)glyph + 0x0E) & 0x0F) < 2))
					{
						activeTlut = tlut;
						font->SetTlut(tlut + *(int*)((char*)this + 0x3D34));
					}

					font->SetPosX(*(float*)((char*)this + 0x3C9C) + *glyph);
					font->SetPosY(*(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2));
					float glyphScaleY = kMesTagScaleStep * (float)*(unsigned char*)((char*)glyph + 0x11);
					font->SetScaleX(kMesTagScaleStep * (float)*(unsigned char*)((char*)glyph + 0x0A));
					font->SetScaleY(glyphScaleY);
					GetRenderFlagBits(font->renderFlags).snapPosition = 1;
					font->Draw((unsigned short)*(unsigned char*)(glyph + 4));
					GetRenderFlagBits(font->renderFlags).snapPosition = 0;
				}
			}

			glyph += 5;
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

	int fadeCurr;
	int fadeMax;
	int textEntry = (int)((char*)this + 0xC);
	unsigned int maxAdvance = 0;
	for (int i = 0; i < *(int*)((char*)this + 8); i++, textEntry += 0x14)
	{
		if ((int)(unsigned int)*(unsigned short*)(textEntry + 0xC) <= *(int*)((char*)this + 0x3C80))
		{
			CMesCharCell* cell = (CMesCharCell*)textEntry;
			fadeCurr = cell->m_pad0F + 1;
			fadeMax = cell->m_textAlign;
			if (fadeCurr < fadeMax)
			{
				fadeMax = fadeCurr;
			}
			cell->m_pad0F = fadeMax;
			maxAdvance = (unsigned int)*(unsigned char*)(textEntry + 0x13);
		}
	}

	unsigned char* flagEntry =
	    (unsigned char*)((char*)this + *(int*)((char*)this + 0x3C10) * 6 + 0x3C14);
	int advance;
	while (*(int*)((char*)this + 0x3C10) < (int)maxAdvance)
	{
		int type = *flagEntry;
		switch (type)
		{
		case 2:
			*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0) =
			    (int)*(short*)(flagEntry + 4);
			break;
		case 1:
		{
			int* slot = (int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0);
			*slot = *slot + 1;
			break;
		}
		case 4:
			if (*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0) == 0)
			{
				advance = 0;
				goto doneAdvance;
			}
			break;
		}

		flagEntry += 6;
		*(int*)((char*)this + 0x3C10) = *(int*)((char*)this + 0x3C10) + 1;
	}
	advance = 1;

doneAdvance:
	if (advance)
	{
		int next = *(int*)((char*)this + 0x3C80) + 1;
		int max = 0x7FFF;
		if (next < 0x7FFF)
		{
			max = next;
		}
		*(int*)((char*)this + 0x3C80) = max;
	}

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
	if (mRevealCursor < mDrawCursor)
	{
		return mWaitFrames;
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
	int fontSel = mFontIndex;
	CFont* setupFont;
	switch (fontSel)
	{
	case 0:
		setupFont = MenuPcs.m_fonts[0];
		break;
	case 2:
		setupFont = MenuPcs.m_fonts[2];
		break;
	case 3:
		setupFont = MenuPcs.m_fonts[2];
		break;
	}

	setupFont->SetShadow(mShadow);
	setupFont->SetMargin(kMesZero);
	float setupScaleY = mScaleY;
	setupFont->SetScaleX(mScaleX);
	setupFont->SetScaleY(setupScaleY);
	CFont* font = setupFont;

	bool running = true;
	unsigned char caseMode = 0;
	unsigned char flowMode = 0;
	char nameItem[32];
	char nameMon[32];
	char nameTag2B[32];
	char nameTag2C[32];
	char nameTag2D[32];

	unsigned short uch;
	while (running)
	{
		unsigned char* p = (unsigned char*)*text;
		*text = (char*)(p + 1);
		uch = *p;

		if (uch == 0)
		{
			running = false;
			goto updateBounds;
		}

		if (uch != 0xFF)
		{
			goto renderChar;
		}

		{
			unsigned char* q = (unsigned char*)*text;
			*text = (char*)(q + 1);
			uch = *q - 0xA0;
		}

		switch (uch)
		{
		case 0:
		advanceLine:
		{
			mCurrentX = kMesZero;
			float lineAdvance = (float)font->m_glyphHeight * font->scaleY;
			mCurrentY = mCurrentY + (kMesLineHeightAdjust + lineAdvance);
			if (mRubyEnabled != 0)
			{
				mRubyLine = mRubyLine + 1;
				mCurrentX = mCurrentX + (kMesRubyLineIndent + mLineSpacing);
			}
			break;
		}
		case 1:
		{
			int wait = 2;
			if (mRubyEnabled != 0)
			{
				wait = 3;
			}
			mWaitFrames = wait;
			running = false;
			mWaitActive = 1;
			goto advanceLine;
		}
		case 0x29:
			mWaitFrames = 5;
			running = false;
			mWaitActive = 1;
			goto advanceLine;
		case 2:
			mWaitFrames = 4;
			running = false;
			mWaitActive = 1;
			goto advanceLine;
		case 3:
			mRevealCursor = mRevealCursor + ReadTagS8(text);
			break;
		case 4:
			mFontAlign = 0;
			break;
		case 5:
			mFontAlign = 2;
			break;
		case 6:
			mFontAlign = 1;
			break;
		case 7:
			mRubyEnabled = 1;
			mRubyLine = 0;
			mRubyHeight = ReadTagS8(text);
			{
				float rubyAdvance = (float)font->m_glyphHeight * font->scaleY;
				mRubySpacing = kMesLineHeightAdjust + rubyAdvance;
			}
			mRubyY = mCurrentY;
			mRubyOffset = ReadTagS8(text);
			mCurrentX = mCurrentX + kMesRubyLineIndent + mLineSpacing;
			break;
		case 8:
		{
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 6;
			}
			char* flatText = (char*)Game.m_caravanWorkArr[mFlagVars[ReadTagS8(text)] & 0xFFFF].m_name;
			addString(&flatText, branchMode);
			mColor = oldColor;
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
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 5;
			}
			int value = mFlagVars[ReadTagS8(text)] & 0xFFFF;
			char* namePtr = nameItem;
			switch (uch)
			{
			case 9:
			case 0x37:
				strcpy(namePtr, FlatNameDirect(0, value * 5 + 1));
				break;
			case 0x39:
				strcpy(namePtr, FlatNameDirect(0, value * 5 + 3));
				break;
			case 0x3B:
				Game.MakeArtItemName(namePtr, value, 1);
				break;
			case 0x19:
				Game.MakeArtsItemNames(namePtr, value);
				break;
			case 0x3D:
				Game.MakeArtItemName(namePtr, value, mFlagVars[ReadTagS8(text)] & 0xFFFF);
				break;
			case 0x3F:
				Game.MakeNumItemName(namePtr, value, mFlagVars[ReadTagS8(text)] & 0xFFFF);
				break;
			case 0x1D:
				strcpy(namePtr, FlatNameDirect(0, value * 5));
				break;
			}
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
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
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 0;
			}
			int value = mFlagVars[ReadTagS8(text)] & 0xFFFF;
			char* namePtr = nameMon;
			switch (uch)
			{
			case 0x2A:
			case 0x38:
				strcpy(namePtr, FlatNameDirect(1, value * 5 + 1));
				break;
			case 0x3A:
				strcpy(namePtr, FlatNameDirect(1, value * 5 + 3));
				break;
			case 0x3C:
				Game.MakeArtMonName(namePtr, value, 1);
				break;
			case 0x1F:
				Game.MakeArtsMonNames(namePtr, value);
				break;
			case 0x3E:
				Game.MakeArtMonName(namePtr, value, mFlagVars[ReadTagS8(text)] & 0xFFFF);
				break;
			case 0x40:
				Game.MakeNumMonName(namePtr, value, mFlagVars[ReadTagS8(text)] & 0xFFFF);
				break;
			case 0x1E:
				strcpy(namePtr, FlatNameDirect(1, value * 5));
				break;
			default:
				break;
			}
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2B:
		{
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 6;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2B, FlatNameDirect(2, mFlagVars[ReadTagS8(text)] & 0xFFFF));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2C:
		{
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 4;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2C, FlatNameDirect(3, mFlagVars[ReadTagS8(text)] & 0xFFFF));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2D:
		{
			int oldColor = mColor;
			if (ReadTagByte(text) != 0)
			{
				mColor = 3;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2D, FlatNameDirect(3, (mFlagVars[ReadTagS8(text)] & 0xFFFF) + 0x3C));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2E:
		{
			char* flatText = FlatNameDirect(5, mFlagVars[ReadTagS8(text)] & 0xFFFF);
			addString(&flatText, branchMode);
			break;
		}
		case 0x2F:
		{
			char* townName = Game.m_gameWork.m_townName;
			addString(&townName, branchMode);
			break;
		}
		case 0x30:
		{
			char number[256];
			char* numberPtr;
			sprintf(numberPtr = number, s_mesNumFmt, mFlagVars[ReadTagS8(text)]);
			addString(&numberPtr, branchMode);
			break;
		}
		case 0x0A:
		{
			unsigned char idx = (unsigned char)ReadTagU8(text);
			short value = (short)ReadTagS16(text);
			mFlagVars[idx] = value;
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_param.m_value = value;
				flag.m_type = 2;
				mFlagEntries[mFlagCount++] = flag;
			}
			break;
		}
		case 0x0B:
		{
			unsigned char idx = (unsigned char)ReadTagU8(text);
			mFlagVars[idx] = mFlagVars[idx] + 1;
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_type = 1;
				mFlagEntries[mFlagCount++] = flag;
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
			mColor = (int)uch - 0x0C;
			break;
		case 0x24:
			running = false;
			mWaitFrames = 2;
			goto advanceLine;
		case 0x28:
			running = false;
			mWaitFrames = 1;
			goto advanceLine;
		case 0x26:
			mTextAlign = ReadTagS8(text);
			break;
		case 0x27:
			mFadeFrames = ReadTagS8(text);
			break;
		case 0x25:
		{
			int value = ReadTagS8(text);
			if (mFontCount != 0)
			{
				if (System.m_execParam != 0)
				{
					System.Printf(lbl_801D9E58);
				}
			}
			else if (value == 0x7F)
			{
				mAdvanceEnabled = 0;
			}
			else
			{
				mAdvanceStep = value;
			}
			break;
		}
		case 0x31:
			mCurrentX = (float)ReadTagS16(text);
			mCurrentY = (float)ReadTagS16(text);
			break;
		case 0x22:
		{
			float x = (float)ReadTagS16(text);
			float y = (float)ReadTagS16(text);
			MenuPcs.m_battleMesMenus[m_playerIndex]->SetPos(x, y);
			break;
		}
		case 0x32:
			mColor = 9;
			break;
		case 0x33:
			mLineSpacing = (float)ReadTagS8(text);
			break;
		case 0x34:
		{
			mFontIndex = ReadTagS8(text);
			CFont* newFont;
			switch (mFontIndex)
			{
			case 0:
				newFont = MenuPcs.m_fonts[0];
				break;
			case 2:
				newFont = MenuPcs.m_fonts[2];
				break;
			case 3:
				newFont = MenuPcs.m_fonts[2];
				break;
			}
			newFont->SetShadow(mShadow);
			newFont->SetMargin(kMesZero);
			float newScaleY = mScaleY;
			newFont->SetScaleX(mScaleX);
			newFont->SetScaleY(newScaleY);
			font = newFont;
			break;
		}
		case 0x35:
		{
			float scale = kMesTagScaleStep * (float)ReadTagS16(text);
			mScaleY = scale;
			mScaleX = scale;
			float tagScaleY = mScaleY;
			font->SetScaleX(mScaleX);
			font->SetScaleY(tagScaleY);
			break;
		}
		case 0x1A:
		{
			mScaleX = kMesTagScaleStep * (float)ReadTagS16(text);
			float tagScaleY = mScaleY;
			font->SetScaleX(mScaleX);
			font->SetScaleY(tagScaleY);
			break;
		}
		case 0x36:
		{
			unsigned char idx = (unsigned char)ReadTagU8(text);
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_type = 4;
				mFlagEntries[mFlagCount++] = flag;
			}
			break;
		}
		case 0x41:
		{
			int mode = ReadTagS8(text);
			int newCaseMode;
			if (mode == 1)
			{
				newCaseMode = 1;
			}
			else
			{
				newCaseMode = 2;
				if (mode == 0)
				{
					newCaseMode = 3;
				}
			}
			caseMode = newCaseMode;
			break;
		}
		case 0x43:
		{
			int newFlowMode = 2;
			if (Game.m_gameWork.m_menuStageMode != 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x44:
		{
			int newFlowMode = 2;
			if (Game.m_caravanWorkArr[mFlagVars[0x13]].m_genderFlag == 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x42:
		{
			int newFlowMode = 2;
			if (mFlagVars[ReadTagS8(text)] == 1)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x45:
		{
			int newFlowMode = 2;
			if (Game.m_caravanWorkArr[mFlagVars[ReadTagS8(text)]].m_genderFlag == 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x20:
		{
			signed char vowel =
			    (signed char)Game.m_caravanWorkArr[mFlagVars[ReadTagS8(text)]].m_name[0];
			if ((vowel == 'A') || (vowel == 'I') || (vowel == 'U') ||
			    (vowel == 'E') || (vowel == 'O') || (vowel == 'Y'))
			{
				flowMode = 1;
			}
			else
			{
				flowMode = 2;
			}
			break;
		}
		case 0x21:
		{
			char vowel = *FlatNameDirect(2, mFlagVars[ReadTagS8(text)]);
			if ((vowel == 'A') || (vowel == 'I') || (vowel == 'U') ||
			    (vowel == 'E') || (vowel == 'O') || (vowel == 'Y'))
			{
				flowMode = 1;
			}
			else
			{
				flowMode = 2;
			}
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
		case 0x1B:
		{
			int newFlowMode = 2;
			if ((mFlagVars[ReadTagS8(text)] & 1) == 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x1C:
		{
			int newFlowMode = 2;
			if ((mFlagVars[ReadTagS8(text)] & 1) == 1)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
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
			uch = uch - 0x48;
			goto renderTag;
		case 0x54:
		{
			char* src = (char*)s_mesEmpty;
			addString(&src, branchMode);
			break;
		}
		}

		goto updateBounds;

	renderChar:
	renderTag:
		if (flowMode != 2)
		{
			CMesCharCell* glyph = (CMesCharCell*)((int*)this + mCounter * 5 + 3);
			glyph->m_color = (char)mColor;
			glyph->m_char = (char)uch;
			glyph->m_x = mCurrentX;
			glyph->m_y = (short)(int)mCurrentY;

			GetRenderFlagBits(font->renderFlags).snapPosition = 1;
			float width;
			if (uch < 0x20)
			{
				width = kMesIconDefaultWidth;
			}
			else
			{
				width = font->GetWidth(uch);
			}
			glyph->m_width = width;
			float packedScale = kMesPackedScaleFactor;
			GetRenderFlagBits(font->renderFlags).snapPosition = 0;

			glyph->m_reveal = (short)mRevealCursor;
			glyph->m_textAlign = mTextAlign;
			glyph->m_pad0F = 0;
			glyph->m_flagCount = (char)mFlagCount;
			glyph->m_fontAlign = mFontAlign;
			glyph->m_fontIndex = mFontIndex;
			glyph->m_scaleX = (char)(int)(packedScale * mScaleX);
			glyph->m_scaleY = (char)(int)(packedScale * mScaleY);

			mCurrentX = mCurrentX + (glyph->m_width + mLineSpacing);
			if (mAdvanceEnabled != 0)
			{
				int step = mAdvanceStep;
				float half = (float)(step >> 1);
				if ((mCounter & 1) != 0)
				{
					mRevealCursor = (int)((float)mRevealCursor + ((float)step - half));
				}
				else
				{
					mRevealCursor = (int)((float)mRevealCursor + half);
				}
			}
			else
			{
				mRevealCursor = mRevealCursor + mAdvanceStep;
			}
			mCounter = mCounter + 1;
		}

	updateBounds:
		{
			float w = mCurrentX;
			if (w < mLineWidth)
			{
				w = mLineWidth;
			}
			mLineWidth = w;
			float h = mCurrentY;
			if (h < mLineHeight)
			{
				h = mLineHeight;
			}
			mLineHeight = h;
		}
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
	int type;
	float groupWidth;
	float halfVal;
	int remaining;
	unsigned int runLength;
	int i;
	unsigned char* flagEntry;
	float* start;
	int entryCount;
	float* curr;
	char tempFlags[0x50];

	if (mText != 0)
	{
		entryCount = *(int*)((char*)this + 0x3c0c);
		flagEntry = (unsigned char*)((char*)this + *(int*)((char*)this + 0x3c10) * 6 + 0x3c14);
		while (*(int*)((char*)this + 0x3c10) < entryCount)
		{
			type = *flagEntry;
			switch (type)
			{
			case 2:
				*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0) =
				    (int)*(short*)(flagEntry + 4);
				break;
			case 1:
			{
				int* slot = (int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0);
				*slot = *slot + 1;
				break;
			}
			case 4:
				break;
			}
			flagEntry += 6;
			*(int*)((char*)this + 0x3c10) = *(int*)((char*)this + 0x3c10) + 1;
		}
		mCounter = 0;
		halfVal = kMesZero;
		mFlagCursor = 0;
		mFlagCount = 0;
		mCurrentY = halfVal;
		mCurrentX = halfVal;
		mLineHeight = halfVal;
		mLineWidth = halfVal;
		mDrawCursor = 0;
		mRevealCursor = 0;
		mFadeEnabled = 0;
		memcpy(tempFlags, mFlagVars, sizeof(tempFlags));
		addString(&mText, 0);
		memcpy(mFlagVars, tempFlags, sizeof(tempFlags));
		halfVal = kMesHalf;
		i = 0;
		start = (float*)((char*)this + 0xc);
		while ((remaining = mCounter, i < remaining))
		{
			int j = i + 1;
			curr = start + 5;
			for (; j < remaining; j = j + 1, curr = curr + 5)
			{
				if ((((unsigned int)*(unsigned char*)((char*)start + 0xe) >> 4 & 0xF) != ((unsigned int)*(unsigned char*)((char*)curr + 0xe) >> 4 & 0xF)) ||
				    (*(short*)(start + 2) != *(short*)(curr + 2)))
				{
					break;
				}
			}
			groupWidth = (curr[-5] - *start) + (start[1] + *(float*)((char*)this + 0x3d3c));
			for (; start <= curr - 5; start = start + 5)
			{
				type = (*(unsigned char*)((char*)start + 0xe) >> 4) & 0xF;
				if (type == 1)
				{
					*start = halfVal * (*(float*)((char*)this + 0x3ca4) - groupWidth) + *start;
				}
				else if ((unsigned int)type == 2)
				{
					*start = *start + (*(float*)((char*)this + 0x3ca4) - groupWidth);
				}
			}
			i = j;
			start = curr;
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
	float one = kMesOne;
	float zero = kMesZero;
	mText = text;
	mWaitActive = 0;
	mMaxHeight = zero;
	mMaxWidth = zero;
	mCounter = 0;
	mFlagCursor = 0;
	mFlagCount = 0;
	mRubyEnabled = 0;
	mFontCount = param;
	mLineSpacing = zero;
	mFontIndex = 0;
	mScaleX = one;
	mScaleY = one;
	mAdvanceEnabled = 1;

	if (text != 0) {
		unsigned char flagBackup[0x50];
		memcpy(flagBackup, mFlagVars, sizeof(flagBackup));
		float lineZero = kMesZero;

		while (mWaitActive == 0) {
			mCounter = 0;
			mFlagCursor = 0;
			mFlagCount = 0;
			mCurrentY = lineZero;
			mCurrentX = lineZero;
			mLineHeight = lineZero;
			mLineWidth = lineZero;

			addString(&mText, 1);

			mMaxWidth = (mLineWidth < mMaxWidth) ? mMaxWidth : mLineWidth;
			mMaxHeight = (mLineHeight < mMaxHeight) ? mMaxHeight : mLineHeight;
		}

		memcpy(mFlagVars, flagBackup, sizeof(flagBackup));
		float lineSkip = kMesLineHeightAdjust;
		zero = kMesZero;
		one = kMesOne;
		mMaxWidth = mMaxWidth - mLineSpacing;
		mMaxHeight = mMaxHeight - lineSkip;

		mText = text;
		mWaitActive = 0;
		mAdvanceStep = (unsigned int)__cntlzw((unsigned int)param) >> 5;
		mTextAlign = 3;
		mFadeFrames = 0;
		mRubyEnabled = 0;
		mFontAlign = 0;
		mColor = 7;
		mLineSpacing = zero;
		mFontIndex = 0;
		mScaleX = one;
		mScaleY = one;
		mAdvanceEnabled = 1;
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
	mFlagCursor = 0;
	mFlagCount = 0;
	mTlutBase = 0;
	mShadow = 1;
	memset(mFlagVars, 0, sizeof(mFlagVars));
}
