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

// PAL map: CMes::m_tempVar in mes.o, .bss size 0x50.
int CMes::m_tempVar[0x14];

static const char s_Not_corresponding_TAG_is_used_pct02x_801D9E30[] = "Not corresponding TAG is used.[%02x]\n";
static const char s_This_TAG_is_not_created_pct02x_801D9E10[] = "This TAG is not created.[%02x]\n";
static char s_MessageSpeedTagUsed[] =
	"\x83\x81\x83\x62\x83\x5A\x81\x5B\x83\x57\x88\xEA\x8F\x9F\x95\x5C\x8E\xA6"
	"\x83\x82\x81\x5B\x83\x68\x82\xC5<speed>\x83\x5E\x83\x4F\x82\xAA\x8E\x67"
	"\x97\x70\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42\n";
static const char s_mesNumFmt[] = "%d";
static const char s_mesFallback[] = "---";
static const char s_mesEmpty[] = "";
static char* sTag54Source;
static char sTag54Init;

static inline char GetMesNibbleValue(const char* data)
{
	signed char val = (signed char)(((unsigned char)data[0] & 0x0F) << 4);
	val = (signed char)(val | ((unsigned char)data[1] & 0x0F));
	return val;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x800acce4
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
inline char CMes::GET_1(char** text)
{
	char* p0 = *text;
	*text = p0 + 1;
	signed char val = (signed char)((*p0 & 0x0F) << 4);
	char* p1 = *text;
	*text = p1 + 1;
	val = (signed char)(val | (*p1 & 0x0F));
	return val;
}

static inline int ReadTagNibble(char** text)
{
	char* p = *text;
	*text = p + 1;
	return *p & 0x0F;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x800acc38
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMes::GET_2(char** text)
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
	if (sTag54Init == 0)
	{
		sTag54Source = (char*)s_mesEmpty;
		sTag54Init = 1;
	}

	unsigned char caseMode = 0;
	unsigned char branchMode = 0;

	char c;
	while ((c = *src) != 0)
	{
		if ((unsigned char)c == 0xFF)
		{
		unsigned int tag = ((unsigned int)(unsigned char)src[1] - 0xA0U) & 0xFFU;
		const unsigned char* op = (const unsigned char*)src + 2;
		src++;

		switch (tag)
		{
		case 0:
			if (keepHyphenOnLineBreak == 0)
			{
				*out++ = '\n';
			}
			else if (out[-1] == '-')
			{
				out[-1] = '\0';
				out--;
			}
			break;
		case 4:
			*out++ = 0x1D;
			break;
		case 5:
			*out++ = 0x1C;
			break;
		case 6:
			*out++ = 0x1E;
			break;
		case 8:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(out, (char*)Game.m_caravanWorkArr[CMes::m_tempVar[varIndex]].m_name);
			out += strlen(out);
			src += 4;
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
				strcpy(out, FlatNameDirect(0, value * 5 + 1));
				break;
			case 0x39:
				strcpy(out, FlatNameDirect(0, value * 5 + 3));
				break;
			case 0x3B:
				Game.MakeArtItemName(out, value, 1);
				break;
			case 0x3D:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtItemName(out, value, count);
				break;
			}
			case 0x3F:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumItemName(out, value, count);
				break;
			}
			case 0x1D:
				strcpy(out, FlatNameDirect(0, value * 5));
				break;
			}
			ApplyCaseMode(out, caseMode);
			out += strlen(out);
			src += 4;
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
				strcpy(out, FlatNameDirect(1, value * 5 + 1));
				break;
			case 0x3A:
				strcpy(out, FlatNameDirect(1, value * 5 + 3));
				break;
			case 0x3C:
				Game.MakeArtMonName(out, value, 1);
				break;
			case 0x3E:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeArtMonName(out, value, count);
				break;
			}
			case 0x40:
			{
				signed char countIdx = (signed char)GetMesNibbleValue((const char*)(op + 4));
				int count = (unsigned int)CMes::m_tempVar[countIdx] & 0xFFFF;
				Game.MakeNumMonName(out, value, count);
				break;
			}
			case 0x1E:
				strcpy(out, FlatNameDirect(1, value * 5));
				break;
			}
			ApplyCaseMode(out, caseMode);
			out += strlen(out);
			src += 4;
			break;
		}
		case 0x2B:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(out, FlatNameDirect(2, CMes::m_tempVar[varIndex]));
			out += strlen(out);
			src += 4;
			break;
		}
		case 0x2C:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(out, FlatNameDirect(3, CMes::m_tempVar[varIndex]));
			out += strlen(out);
			src += 4;
			break;
		}
		case 0x2D:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(out, (Game.m_cFlatDataArr[1].TableStrings(3) + 0x3C)[CMes::m_tempVar[varIndex]]);
			out += strlen(out);
			src += 4;
			break;
		}
		case 0x2E:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			strcpy(out, FlatNameDirect(5, CMes::m_tempVar[varIndex]));
			out += strlen(out);
			src += 2;
			break;
		}
		case 0x2F:
		{
			char* townName = Game.m_gameWork.m_townName;
			strcpy(out, townName);
			out += strlen(out);
			break;
		}
		case 0x30:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			sprintf(out, s_mesNumFmt, CMes::m_tempVar[varIndex]);
			out += strlen(out);
			src += 2;
			break;
		}
		case 0x41:
		{
			int mode = (signed char)GetMesNibbleValue((const char*)op);
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
		case 0x44:
		{
			int newBranchMode = 2;
			if (playerIndex == 0)
			{
				newBranchMode = 1;
			}
			branchMode = newBranchMode;
			break;
		}
		case 0x42:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			int newBranchMode = 2;
			if (CMes::m_tempVar[varIndex] == 1)
			{
				newBranchMode = 1;
			}
			branchMode = newBranchMode;
			break;
		}
		case 0x45:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)op);
			int newBranchMode = 2;
			if (Game.m_caravanWorkArr[CMes::m_tempVar[varIndex]].m_genderFlag == 0)
			{
				newBranchMode = 1;
			}
			branchMode = newBranchMode;
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
			strcpy(out, sTag54Source);
			out += strlen(out);
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
		}
		else if (branchMode != 2)
		{
			*out = c;
			out++;
		}
		src++;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 132b
 * EN Address: 0x800ad4cc
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMes::addFlag(CFlag& flag)
{
	mFlagEntries[mFlagCount++] = flag;
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
 * PAL Address: UNUSED
 * PAL Size: 256b
 * EN Address: 0x800ab74c
 * EN Size: 280b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CFont* CMes::getFont(int fontIndex, int draw)
{
	CFont* font;
	switch (fontIndex)
	{
	case 0:
		font = MenuPcs.m_fonts[0];
		break;
	case 2:
		font = MenuPcs.m_fonts[2];
		break;
	case 3:
		font = MenuPcs.m_fonts[2];
		break;
	}
	font->SetShadow(mShadow);
	font->SetMargin(0.0f);
	float scaleY = mScaleY;
	font->SetScaleX(mScaleX);
	font->SetScaleY(scaleY);
	if (draw)
	{
		font->DrawInit();
	}
	return font;
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

		CMesCharCell* glyph = m_chars;
		CFont* font = 0;
		int activeTlut = 0xFFFFFFFF;
		int activeFontId = 0xFFFFFFFF;

		for (int i = 0; i < mCounter; i++, glyph++)
		{
			if (mDrawCursor >= glyph->m_reveal)
			{
				if ((unsigned int)glyph->m_char < 0x20)
				{
					if (font != 0)
					{
						font->DrawQuit();
					}
					MenuPcs.DrawInit();

					int iconId = glyph->m_char;
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

					MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x15));

					MenuPcs.DrawRect(
					    0, mBaseX + glyph->m_x,
					    8.0f + (mBaseY + (float)glyph->m_y),
					    22.0f, 22.0f, (float)((iconId % 5) * 0x16),
					    (float)((iconId / 5) * 0x16), 1.0f, 1.0f, 0.0f);

					if (font != 0)
					{
						font->DrawInit();
					}
				}
				else
				{
					int fontId = (int)glyph->m_fontIndex;
					if (activeFontId != fontId)
					{
						activeFontId = fontId;
						font = getFont(fontId, 1);
					}

					unsigned int fadeCur = glyph->m_fadeCursor;
					unsigned int fadeMax = glyph->m_fadeFrames;
					float ratio = (float)fadeCur / (float)fadeMax;
					_GXColor color;
					color.r = 0xFF;
					color.g = 0xFF;
					color.b = 0xFF;
					int alpha;
					if (ratio < 1.0f)
					{
						alpha = (unsigned char)(ratio * (float)globalAlpha);
					}
					else
					{
						alpha = globalAlpha;
					}
					color.a = alpha;
					font->SetColor(color);

					int tlut = (int)glyph->m_color;
					if ((activeTlut != tlut) && (glyph->m_fontIndex < 2))
					{
						activeTlut = tlut;
						font->SetTlut(tlut + mTlutBase);
					}

					font->SetPosX(mBaseX + glyph->m_x);
					font->SetPosY(mBaseY + (float)glyph->m_y);
					float glyphScaleY = 0.01f * (float)glyph->m_scaleY;
					font->SetScaleX(0.01f * (float)glyph->m_scaleX);
					font->SetScaleY(glyphScaleY);
					font->renderFlags.snapPosition = 1;
					font->Draw((unsigned short)glyph->m_char);
					font->renderFlags.snapPosition = 0;
				}
			}
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

	int fadeCurr;
	int fadeMax;
	CMesCharCell* cell = m_chars;
	unsigned int maxAdvance = 0;
	for (int i = 0; i < mCounter; i++, cell++)
	{
		if (cell->m_reveal <= mDrawCursor)
		{
			fadeCurr = cell->m_fadeCursor + 1;
			fadeMax = cell->m_fadeFrames;
			if (fadeCurr < fadeMax)
			{
				fadeMax = fadeCurr;
			}
			cell->m_fadeCursor = fadeMax;
			maxAdvance = (unsigned int)cell->m_flagCount;
		}
	}

	int advance = useFlag(maxAdvance, 0);

	if (advance)
	{
		int max = 0x7FFF;
		int next = mDrawCursor + 1;
		if (next < 0x7FFF)
		{
			max = next;
		}
		mDrawCursor = max;
	}

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
	CFont* font = getFont(mFontIndex, 0);

	int running = 1;
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
		if ((uch = *(unsigned char*)(*text)++) == 0)
		{
			running = 0;
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
			mCurrentX = 0.0f;
			float lineAdvance = (float)font->m_glyphHeight * font->scaleY;
			mCurrentY = mCurrentY + (-2.0f + lineAdvance);
			if (mRubyEnabled != 0)
			{
				mRubyLine = mRubyLine + 1;
				mCurrentX = mCurrentX + (28.0f + mLineSpacing);
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
			running = 0;
			mWaitActive = 1;
			goto advanceLine;
		}
		case 0x29:
			mWaitFrames = 5;
			running = 0;
			mWaitActive = 1;
			goto advanceLine;
		case 2:
			mWaitFrames = 4;
			running = 0;
			mWaitActive = 1;
			goto advanceLine;
		case 3:
			mRevealCursor = mRevealCursor + GET_1(text);
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
			mRubyHeight = GET_1(text);
			{
				float rubyAdvance = (float)font->m_glyphHeight * font->scaleY;
				mRubySpacing = -2.0f + rubyAdvance;
			}
			mRubyY = mCurrentY;
			mRubyOffset = GET_1(text);
			mCurrentX = mCurrentX + (28.0f + mLineSpacing);
			break;
		case 8:
		{
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 6;
			}
			char* flatText = (char*)Game.m_caravanWorkArr[mFlagVars[GET_1(text)] & 0xFFFF].m_name;
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
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 5;
			}
			int value = mFlagVars[GET_1(text)] & 0xFFFF;
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
				Game.MakeArtItemName(namePtr, value, mFlagVars[GET_1(text)] & 0xFFFF);
				break;
			case 0x3F:
				Game.MakeNumItemName(namePtr, value, mFlagVars[GET_1(text)] & 0xFFFF);
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
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 0;
			}
			int value = mFlagVars[GET_1(text)] & 0xFFFF;
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
				Game.MakeArtMonName(namePtr, value, mFlagVars[GET_1(text)] & 0xFFFF);
				break;
			case 0x40:
				Game.MakeNumMonName(namePtr, value, mFlagVars[GET_1(text)] & 0xFFFF);
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
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 6;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2B, FlatNameDirect(2, mFlagVars[GET_1(text)] & 0xFFFF));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2C:
		{
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 4;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2C, FlatNameDirect(3, mFlagVars[GET_1(text)] & 0xFFFF));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2D:
		{
			char colorTag = GET_1(text);
			int oldColor = mColor;
			if (colorTag != 0)
			{
				mColor = 3;
			}
			char* namePtr;
			strcpy(namePtr = nameTag2D, FlatNameDirect(3, (mFlagVars[GET_1(text)] & 0xFFFF) + 0x3C));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2E:
		{
			char* flatText = FlatNameDirect(5, mFlagVars[GET_1(text)] & 0xFFFF);
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
			sprintf(numberPtr = number, s_mesNumFmt, mFlagVars[GET_1(text)]);
			addString(&numberPtr, branchMode);
			break;
		}
		case 0x0A:
		{
			unsigned char idx = (unsigned char)GET_1(text);
			short value = (short)GET_2(text);
			mFlagVars[idx] = value;
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_param.m_value = value;
				flag.m_type = 2;
				addFlag(flag);
			}
			break;
		}
		case 0x0B:
		{
			unsigned char idx = (unsigned char)GET_1(text);
			mFlagVars[idx] = mFlagVars[idx] + 1;
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_type = 1;
				addFlag(flag);
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
			mColor = (unsigned int)uch - 0x0C;
			break;
		case 0x24:
			running = 0;
			mWaitFrames = 2;
			goto advanceLine;
		case 0x28:
			running = 0;
			mWaitFrames = 1;
			goto advanceLine;
		case 0x26:
			mTextAlign = GET_1(text);
			break;
		case 0x27:
			mFadeFrames = GET_1(text);
			break;
		case 0x25:
		{
			int value = GET_1(text);
			if (mFontCount != 0)
			{
				if ((unsigned int)System.m_execParam >= 1U)
				{
					System.Printf(s_MessageSpeedTagUsed);
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
			mCurrentX = (float)GET_2(text);
			mCurrentY = (float)GET_2(text);
			break;
		case 0x22:
		{
			float x = (float)GET_2(text);
			float y = (float)GET_2(text);
			MenuPcs.m_battleMesMenus[m_playerIndex]->SetPos(x, y);
			break;
		}
		case 0x32:
			mColor = 9;
			break;
		case 0x33:
			mLineSpacing = (float)GET_1(text);
			break;
		case 0x34:
		{
			mFontIndex = GET_1(text);
			font = getFont(mFontIndex, 0);
			break;
		}
		case 0x35:
		{
			float scale = 0.01f * (float)GET_2(text);
			mScaleY = scale;
			mScaleX = scale;
			float tagScaleY = mScaleY;
			font->SetScaleX(mScaleX);
			font->SetScaleY(tagScaleY);
			break;
		}
		case 0x1A:
		{
			mScaleX = 0.01f * (float)GET_2(text);
			float tagScaleY = mScaleY;
			font->SetScaleX(mScaleX);
			font->SetScaleY(tagScaleY);
			break;
		}
		case 0x36:
		{
			signed char idx = (unsigned char)GET_1(text);
			if (branchMode == 0)
			{
				CFlag flag;
				flag.m_param.m_index = idx;
				flag.m_type = 4;
				addFlag(flag);
			}
			break;
		}
		case 0x41:
		{
			int mode = GET_1(text);
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
			if (mFlagVars[GET_1(text)] == 1)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x45:
		{
			int newFlowMode = 2;
			if (Game.m_caravanWorkArr[mFlagVars[GET_1(text)]].m_genderFlag == 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x20:
		{
			signed char vowel =
			    (signed char)Game.m_caravanWorkArr[mFlagVars[GET_1(text)]].m_name[0];
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
			char vowel = *FlatNameDirect(2, mFlagVars[GET_1(text)]);
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
			if ((mFlagVars[GET_1(text)] & 1) == 0)
			{
				newFlowMode = 1;
			}
			flowMode = newFlowMode;
			break;
		}
		case 0x1C:
		{
			int newFlowMode = 2;
			if ((mFlagVars[GET_1(text)] & 1) == 1)
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
			CMesCharCell* glyph = &m_chars[mCounter];
			glyph->m_color = mColor;
			glyph->m_char = uch;
			glyph->m_x = mCurrentX;
			glyph->m_y = (short)(int)mCurrentY;

			font->renderFlags.snapPosition = 1;
			float width;
			if (uch < 0x20)
			{
				width = 22.0f;
			}
			else
			{
				width = font->GetWidth(uch);
			}
			glyph->m_width = width;
			float packedScale = 100.0f;
			font->renderFlags.snapPosition = 0;

			glyph->m_reveal = mRevealCursor;
			glyph->m_fadeFrames = mTextAlign;
			glyph->m_fadeCursor = 0;
			glyph->m_flagCount = mFlagCount;
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
		mLineWidth = (mCurrentX < mLineWidth) ? mLineWidth : mCurrentX;
		mLineHeight = (mCurrentY < mLineHeight) ? mLineHeight : mCurrentY;
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
	int i;
	CMesCharCell* start;
	CMesCharCell* curr;
	char tempFlags[0x50];

	if (mText != 0)
	{
		useFlag(mFlagCount, 1);
		mCounter = 0;
		halfVal = 0.0f;
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
		halfVal = 0.5f;
		i = 0;
		start = m_chars;
		while ((remaining = mCounter, i < remaining))
		{
			int j = i + 1;
			curr = start + 1;
			for (; j < remaining; j = j + 1, curr++)
			{
				if ((start->m_fontAlign != curr->m_fontAlign) ||
				    (start->m_y != curr->m_y))
				{
					break;
				}
			}
			groupWidth = (curr[-1].m_x - start->m_x) + (start->m_width + mLineSpacing);
			for (; start <= curr - 1; start++)
			{
				type = start->m_fontAlign;
				if (type == 1)
				{
					start->m_x = halfVal * (mMaxWidth - groupWidth) + start->m_x;
				}
				else if ((unsigned int)type == 2)
				{
					start->m_x = start->m_x + (mMaxWidth - groupWidth);
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
	mText = text;
	mWaitActive = 0;
	mMaxHeight = 0.0f;
	mMaxWidth = 0.0f;
	mCounter = 0;
	mFlagCursor = 0;
	mFlagCount = 0;
	mRubyEnabled = 0;
	mFontCount = param;
	mLineSpacing = 0.0f;
	mFontIndex = 0;
	mScaleX = 1.0f;
	mScaleY = 1.0f;
	mAdvanceEnabled = 1;

	if (text != 0) {
		unsigned char flagBackup[0x50];
		memcpy(flagBackup, mFlagVars, sizeof(flagBackup));
		float lineZero = 0.0f;

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
		float lineSkip = -2.0f;
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
		mLineSpacing = 0.0f;
		mFontIndex = 0;
		mScaleX = 1.0f;
		mScaleY = 1.0f;
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
