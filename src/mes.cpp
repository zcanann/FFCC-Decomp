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

static const char s_mesTagUnknown[] = "Not corresponding TAG is used. %02x\n";
static const char s_mesTagMissing[] = "This TAG is not created. %02x\n";
static const char s_mesNumFmt[] = "%d";
static const char s_mesFallback[] = "---";
static const char s_mesEmpty[] = "";
static char* sTag54Source;
static char sTag54Init;

static inline int GetMesNibbleValue(const char* data)
{
	int low = (unsigned char)data[1] & 0x0F;
	int high = (unsigned char)data[0] & 0x0F;
	return low | (high << 4);
}

static inline int ReadTagU8(char** text)
{
	unsigned char high = (unsigned char)(*text)[0];
	unsigned char low = (unsigned char)(*text)[1];
	int value = (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
	*text += 2;
	return value;
}

static inline int ReadTagS8(char** text)
{
	unsigned char high = (unsigned char)(*text)[0];
	unsigned char low = (unsigned char)(*text)[1];
	int value = (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
	*text += 2;
	return (int)(signed char)value;
}

static inline int ReadTagS16(char** text)
{
	int a = (unsigned char)(*text)[0] & 0x0F;
	int b = (unsigned char)(*text)[1] & 0x0F;
	int c = (unsigned char)(*text)[2] & 0x0F;
	int d = (unsigned char)(*text)[3] & 0x0F;
	*text += 4;
	return (int)(short)((a << 12) | (b << 8) | (c << 4) | d);
}

static inline void ApplyCaseMode(char* text, int& caseMode)
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

static inline char* FlatNameDirect(int tableIndex, int entryIndex)
{
	return Game.m_cFlatDataArr[1].TableStrings(tableIndex)[entryIndex];
}

inline void CMes::advanceLine(CFont* font)
{
	mCurrentX = kMesZero;
	mCurrentY = mCurrentY + kMesLineHeightAdjust + (float)font->m_glyphHeight * font->scaleY;

	if (mRubyEnabled != 0)
	{
		mRubyLine++;
		mCurrentX += kMesRubyLineIndent + mLineSpacing;
	}
}

inline void CMes::addFlagEntry(unsigned char type, unsigned char index, short value)
{
	int count = mFlagCount;
	CFlag* entry = &mFlagEntries[count];
	entry->m_type = type;
	entry->m_pad01 = 0;
	entry->m_index = index;
	entry->m_pad03 = 0;
	entry->m_value = value;
	mFlagCount = count + 1;
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
			const char* text = FlatNameDirect(5, CMes::m_tempVar[varIndex]);
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
				strcpy(dst, FlatNameDirect(0, value * 5 + 1));
			}
			else if (tag == 0x1D)
			{
				strcpy(dst, FlatNameDirect(0, value * 5));
			}
			else if (tag == 0x39)
			{
				strcpy(dst, FlatNameDirect(0, value * 5 + 3));
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
				strcpy(dst, FlatNameDirect(1, value * 5 + 1));
			}
			else if (tag == 0x1E)
			{
				strcpy(dst, FlatNameDirect(1, value * 5));
			}
			else if (tag == 0x3A)
			{
				strcpy(dst, FlatNameDirect(1, value * 5 + 3));
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
			strcpy(dst, FlatNameDirect(2, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2C:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, FlatNameDirect(3, CMes::m_tempVar[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2D:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, FlatNameDirect(3, CMes::m_tempVar[varIndex] + 0x3C));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2E:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)in + 2);
			strcpy(dst, FlatNameDirect(5, CMes::m_tempVar[varIndex]));
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
	CFlag* flagEntry = &mFlagEntries[mFlagCursor];
	while (mFlagCursor < maxCount)
	{
		int type = flagEntry->m_type;

		if (type != 3)
		{
			if (type < 3)
			{
				if (type != 1)
				{
					if (type != 0)
					{
						mFlagVars[flagEntry->m_index] = flagEntry->m_value;
					}
				}
				else
				{
					int* slot = &mFlagVars[flagEntry->m_index];
					*slot = *slot + 1;
				}
			}
			else if ((type < 5) &&
			         (mFlagVars[flagEntry->m_index] == 0) &&
			         (stopOnClear == 0))
			{
				return 0;
			}
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
	if (mCounter != 0)
	{
		int globalAlpha;
		bool fading = false;
		if ((mFadeEnabled != 0) && (mFadeFrames != 0))
		{
			fading = true;
		}
		if (fading)
		{
			globalAlpha = 0xFF - (mFadeCursor * 0xFF) / mFadeFrames;
		}
		else
		{
			globalAlpha = 0xFF;
		}

		float* glyph = (float*)((char*)this + 0x0C);
		CFont* font = 0;
		unsigned int activeTlut = 0xFFFFFFFF;
		unsigned int activeFontId = 0xFFFFFFFF;

		for (int i = 0; i < mCounter; i++)
		{
			CFont* nextFont = font;
			if (mDrawCursor >= (int)(unsigned int)*(unsigned short*)((char*)glyph + 0x0C))
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
					    0, mBaseX + *glyph,
					    kMesIconDrawYOffset + mBaseY + (float)*(short*)(glyph + 2),
					    kMesIconDefaultWidth, kMesIconDefaultWidth, (float)((iconId % 5) * 0x16),
					    (float)((iconId / 5) * 0x16), kMesOne, kMesOne, 0.0f);

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
						nextFont = MenuPcs.m_fonts[2];
						if (fontId != 2)
						{
							if (fontId < 2)
							{
								nextFont = MenuPcs.m_fonts[0];
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
									nextFont = MenuPcs.m_fonts[2];
								}
							}
						}

						nextFont->SetShadow(mShadow);
						nextFont->SetMargin(kMesZero);
						float fontScaleY = mScaleY;
						nextFont->SetScaleX(mScaleX);
						nextFont->SetScaleY(fontScaleY);
						nextFont->DrawInit();
						activeFontId = fontId;
						font = nextFont;
					}

					unsigned int fadeCur = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) & 0x0F;
					unsigned int fadeMax = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) >> 4;
					float ratio = (float)fadeCur / (float)fadeMax;
					unsigned char alpha;
					if (ratio >= kMesOne)
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
						font->SetTlut((int)tlut + mTlutBase);
						activeTlut = tlut;
					}

					font->SetPosX(mBaseX + *glyph);
					font->SetPosY(mBaseY + (float)*(short*)(glyph + 2));
					float glyphScaleY = kMesTagScaleStep * (float)*(unsigned char*)((char*)glyph + 0x11);
					font->SetScaleX(kMesTagScaleStep * (float)*(unsigned char*)((char*)glyph + 0x0A));
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
	if (mCounter == 0)
	{
		return;
	}

	int textEntry = (int)((char*)this + 0xC);
	unsigned int maxAdvance = 0;
	for (int i = 0; i < mCounter; i++)
	{
		if ((int)(unsigned int)*(unsigned short*)(textEntry + 0xC) <= mDrawCursor)
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

	CFlag* flagEntry = &mFlagEntries[mFlagCursor];
	while ((int)maxAdvance > mFlagCursor)
	{
		int type = flagEntry->m_type;
		if (type != 3)
		{
			if (type < 3)
			{
				if (type != 1)
				{
					if (type != 0)
					{
						mFlagVars[flagEntry->m_index] = flagEntry->m_value;
					}
				}
				else
				{
					int* slot = &mFlagVars[flagEntry->m_index];
					*slot = *slot + 1;
				}
			}
			else if ((type < 5) && (mFlagVars[flagEntry->m_index] == 0))
			{
				goto doneAdvance;
			}
		}

		flagEntry++;
		mFlagCursor++;
	}

	{
		int next = mDrawCursor + 1;
		int max = 0x7FFF;
		if (next < 0x7FFF)
		{
			max = next;
		}
		mDrawCursor = max;
	}

doneAdvance:
	if (mFadeEnabled != 0)
	{
		int next = mFadeCursor + 1;
		int max = mFadeFrames;
		if (next < max)
		{
			max = next;
		}
		mFadeCursor = max;
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
	CFont* font = MenuPcs.m_fonts[2];
	int fontSel = mFontIndex;
	int caseMode = 0;
	int flowMode = branchMode;
	if (fontSel == 0)
	{
		font = MenuPcs.m_fonts[0];
	}
	else if ((fontSel == 1) || (fontSel >= 4))
	{
		// Keep current font pointer selection for unsupported modes.
	}
	else
	{
		font = MenuPcs.m_fonts[2];
	}

	font->SetShadow(mShadow);
	font->SetMargin(kMesZero);
	font->SetScaleX(mScaleX);
	font->SetScaleY(mScaleY);

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
				advanceLine(font);
				break;
			case 1:
			{
				int wait = 2;
				if (mRubyEnabled != 0)
				{
					wait = 3;
				}
				mWaitFrames = wait;
				mWaitActive = 1;
				advanceLine(font);
				return;
			}
			case 2:
				mWaitFrames = 4;
				mWaitActive = 1;
				advanceLine(font);
				return;
			case 0x24:
				mWaitFrames = 2;
				advanceLine(font);
				return;
			case 0x28:
				mWaitFrames = 1;
				advanceLine(font);
				return;
			case 0x29:
				mWaitFrames = 5;
				mWaitActive = 1;
				advanceLine(font);
				return;
			case 3:
				mRevealCursor += ReadTagS8(text);
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
				mRubySpacing = (int)(kMesLineHeightAdjust + (float)font->m_glyphHeight * font->scaleY);
				mRubyY = mCurrentY;
				mRubyOffset = ReadTagS8(text);
				mCurrentX += kMesRubyLineIndent + mLineSpacing;
				break;
			case 8:
			{
				int oldColor = mColor;
				if (ReadTagU8(text) != 0)
				{
					mColor = 6;
				}
				char* flatText = FlatNameDirect(5, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
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
				if (ReadTagU8(text) != 0)
				{
					mColor = 5;
				}
				char name[32];
				char* namePtr = name;
				int value = CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF;
				switch (tag)
				{
				case 9:
				case 0x37:
					strcpy(namePtr, FlatNameDirect(0, value * 5 + 1));
					break;
				case 0x1D:
					strcpy(namePtr, FlatNameDirect(0, value * 5));
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
					strcpy(namePtr, FlatNameDirect(0, value * 5 + 3));
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
				if (ReadTagU8(text) != 0)
				{
					mColor = 0;
				}
				char name[32];
				char* namePtr = name;
				int value = CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF;
				switch (tag)
				{
				case 0x1E:
					strcpy(namePtr, FlatNameDirect(1, value * 5));
					break;
				case 0x2A:
				case 0x38:
					strcpy(namePtr, FlatNameDirect(1, value * 5 + 1));
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
					strcpy(namePtr, FlatNameDirect(1, value * 5 + 3));
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
				if (ReadTagU8(text) != 0)
				{
					mColor = 6;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FlatNameDirect(2, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				mColor = oldColor;
				break;
			}
			case 0x2C:
			{
				int oldColor = mColor;
				if (ReadTagU8(text) != 0)
				{
					mColor = 4;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FlatNameDirect(3, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				mColor = oldColor;
				break;
			}
			case 0x2D:
			{
				int oldColor = mColor;
				if (ReadTagU8(text) != 0)
				{
					mColor = 3;
				}
				char name[32];
				char* namePtr = name;
				strcpy(namePtr, FlatNameDirect(3, (CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF) + 0x3C));
				ApplyCaseMode(namePtr, caseMode);
				addString(&namePtr, branchMode);
				mColor = oldColor;
				break;
			}
			case 0x2E:
			{
				char* flatText = FlatNameDirect(5, CMes::m_tempVar[(signed char)ReadTagU8(text)] & 0xFFFF);
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
					addFlagEntry(2, idx, value);
				}
				break;
			}
			case 0x0B:
			{
				unsigned char idx = (unsigned char)ReadTagU8(text);
				CMes::m_tempVar[idx] = CMes::m_tempVar[idx] + 1;
				if (branchMode == 0)
				{
					addFlagEntry(1, idx, 0);
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
				mColor = (int)tag - 0x0C;
				break;
			case 0x1A:
				mScaleX = kMesTagScaleStep * (float)ReadTagS16(text);
				font->SetScaleX(mScaleX);
				font->SetScaleY(mScaleY);
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
				if (mFontCount == 0)
				{
					if (value == 0x7F)
					{
						mAdvanceEnabled = 0;
					}
					else
					{
						mAdvanceStep = value;
					}
				}
				else if (System.m_execParam != 0)
				{
					System.Printf(const_cast<char*>(s_mesTagUnknown), tag + 0xA0);
				}
				break;
			}
			case 0x26:
				mTextAlign = ReadTagS8(text);
				break;
			case 0x27:
				mFadeFrames = ReadTagS8(text);
				break;
			case 0x31:
				mCurrentX = (float)ReadTagS16(text);
				mCurrentY = (float)ReadTagS16(text);
				break;
			case 0x32:
				mColor = 9;
				break;
			case 0x33:
				mLineSpacing = (float)ReadTagS8(text);
				break;
			case 0x34:
			{
				mFontIndex = ReadTagS8(text);
				int nextFontSel = mFontIndex;
				if (nextFontSel == 0)
				{
					font = MenuPcs.m_fonts[0];
				}
				else
				{
					font = MenuPcs.m_fonts[2];
				}
				font->SetShadow(mShadow);
				font->SetMargin(kMesZero);
				font->SetScaleX(mScaleX);
				font->SetScaleY(mScaleY);
				break;
			}
			case 0x35:
			{
				float scale = kMesTagScaleStep * (float)ReadTagS16(text);
				mScaleY = scale;
				mScaleX = scale;
				font->SetScaleX(mScaleX);
				font->SetScaleY(mScaleY);
				break;
			}
			case 0x36:
			{
				unsigned char idx = (unsigned char)ReadTagU8(text);
				if (branchMode == 0)
				{
					addFlagEntry(4, idx, 0);
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
				flowMode = (Game.m_caravanWorkArr[mFlagVars[0x13]].m_genderFlag == 0) ? 1 : 2;
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

		float* glyph = (float*)((char*)this + mCounter * 0x14 + 0x0C);
		*(unsigned char*)((char*)glyph + 0x12) = (unsigned char)mColor;
		*(unsigned char*)((char*)glyph + 0x10) = ch;
		glyph[0] = mCurrentX;
		glyph[2] = mCurrentY;

		font->renderFlags = (font->renderFlags & 0xF7) | 8;
		if (ch < 0x20)
		{
			glyph[1] = kMesIconDefaultWidth;
		}
		else
		{
			glyph[1] = font->GetWidth(ch);
		}
		font->renderFlags &= 0xF7;

		*(unsigned short*)((char*)glyph + 0x0C) = (unsigned short)mRevealCursor;
		*(unsigned char*)((char*)glyph + 0x0F) =
		    (unsigned char)(mTextAlign << 4) | (*(unsigned char*)((char*)glyph + 0x0F) & 0x0F);
		*(unsigned char*)((char*)glyph + 0x0F) = *(unsigned char*)((char*)glyph + 0x0F) & 0xF0;
		*(unsigned char*)((char*)glyph + 0x13) = (unsigned char)mFlagCount;
		*(unsigned char*)((char*)glyph + 0x0E) =
		    (unsigned char)(mFontAlign << 4) | (*(unsigned char*)((char*)glyph + 0x0E) & 0x0F);
		*(unsigned char*)((char*)glyph + 0x0E) =
		    (unsigned char)((mFontIndex & 0x0F) | (*(unsigned char*)((char*)glyph + 0x0E) & 0xF0));
		*(unsigned char*)((char*)glyph + 0x0A) = (unsigned char)(kMesPackedScaleFactor * mScaleX);
		*(unsigned char*)((char*)glyph + 0x11) = (unsigned char)(kMesPackedScaleFactor * mScaleY);

		mCurrentX += glyph[1] + mLineSpacing;
		if (mAdvanceEnabled == 0)
		{
			mRevealCursor += mAdvanceStep;
		}
		else
		{
			int step = mAdvanceStep;
			if ((mCounter & 1) == 0)
			{
				mRevealCursor += step / 2;
			}
			else
			{
				mRevealCursor += step - (step / 2);
			}
		}
		mCounter++;
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
	CFlag* flagEntry;
	float* start;
	int entryCount;
	float* curr;
	char tempFlags[0x50];

	if (mText != 0)
	{
		entryCount = mFlagCount;
		flagEntry = &mFlagEntries[mFlagCursor];
		while ((halfVal = kMesZero, mFlagCursor < entryCount))
		{
			type = flagEntry->m_type;
			if ((type != 3) && (type < 3))
			{
				if (type != 1)
				{
					if (type != 0)
					{
						mFlagVars[flagEntry->m_index] = flagEntry->m_value;
					}
				}
				else
				{
					int* slot = &mFlagVars[flagEntry->m_index];
					*slot = *slot + 1;
				}
			}
			flagEntry++;
			mFlagCursor++;
		}
		mCounter = 0;
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
		curr = (float*)((char*)this + 0xc);
		while ((start = curr, remaining = mCounter, i < remaining))
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
			groupWidth = (curr[-5] - *start) + start[1] + mLineSpacing;
			if (start <= curr - 5)
			{
				do
				{
					type = (int)((unsigned int)*(unsigned char*)((char*)start + 0xe) >> 4);
					if (type == 1)
					{
						*start = halfVal * (mMaxWidth - groupWidth) + *start;
					}
					else if (type == 2)
					{
						*start = *start + (mMaxWidth - groupWidth);
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
	float zero = kMesZero;
	float one = kMesOne;
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

			float width = mLineWidth;
			if (width < mMaxWidth) {
				width = mMaxWidth;
			}
			mMaxWidth = width;

			float height = mLineHeight;
			if (height < mMaxHeight) {
				height = mMaxHeight;
			}
			mMaxHeight = height;
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
