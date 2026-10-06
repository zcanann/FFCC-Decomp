#include "ffcc/mes.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/mesmenu.h"
#include "ffcc/joybus.h"
#include "ffcc/strcase.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

// PAL map: CMes::m_tempVar in mes.o, .bss size 0x50.
int CMes::m_tempVar[0x14];

static const char s_This_TAG_is_not_created_pct02x_801D9E10[] = "This TAG is not created.[%02x]\n";
static const char s_Not_corresponding_TAG_is_used_pct02x_801D9E30[] = "Not corresponding TAG is used.[%02x]\n";
#ifdef VERSION_GCCJGC
static const char s_MessageSpeedTagUsed[] =
	"\x83\x81\x83\x62\x83\x5A\x81\x5B\x83\x57\x88\xEA\x8F\x75\x95\x5C\x8E\xA6"
	"\x83\x82\x81\x5B\x83\x68\x82\xC5<speed>\x83\x5E\x83\x4F\x82\xAA\x8E\x67"
	"\x97\x70\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42\n";
#else
static const char s_MessageSpeedTagUsed[] =
	"\x83\x81\x83\x62\x83\x5A\x81\x5B\x83\x57\x88\xEA\x8F\x75\x95\x8E\xA6"
	"\x83\x82\x81\x5B\x83\x68\x82\xC5<speed>\x83\x5E\x83\x4F\x82\xAA\x8E\x67"
	"\x97\x70\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\x81\x42\n";
#endif

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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMes::GET_2(char** text)
{
	short acc = (short)((*(*text)++ & 0x0F) << 4);
	acc = (short)(acc | (*(*text)++ & 0x0F));
	acc = (short)((short)(acc << 4) | (*(*text)++ & 0x0F));
	acc = (short)((short)(acc << 4) | (*(*text)++ & 0x0F));
	return (int)acc;
}

#ifdef VERSION_GCCE01
#define ApplyCaseMode(text, caseMode)                                     \
	if (caseMode != 0)                                                    \
	{                                                                     \
		if (caseMode == 1)                                                \
		{                                                                 \
			if ((text)[0] != '\0')                                        \
			{                                                             \
				strupr(text);                                            \
			}                                                             \
		}                                                                 \
		else if (caseMode == 2)                                           \
		{                                                                 \
			char* caseModePtr = (text);                                   \
			if (caseModePtr[0] != '\0')                                   \
			{                                                             \
				caseModePtr[0] = (char)std::toupper(caseModePtr[0]);        \
			}                                                             \
		}                                                                 \
		else                                                              \
		{                                                                 \
			if ((text)[0] != '\0')                                        \
			{                                                             \
				strlwr(text);                                            \
			}                                                             \
		}                                                                 \
		caseMode = 0;                                                     \
	}
#else
#define ApplyCaseMode(text, caseMode)                                     \
	if (caseMode != 0)                                                    \
	{                                                                     \
		if (caseMode == 1)                                                \
		{                                                                 \
			if ((text)[0] != '\0')                                        \
			{                                                             \
				toupper_name_conflict(text);                              \
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
#endif

static inline CColor& MesColorRef(const CColor& color)
{
	return (CColor&)color;
}


/*
 * --INFO--
 * PAL Address: 0x800981F0
 * PAL Size: 380b
 * EN Address: 0x80097B8C
 * EN Size: 380b
 * JP Address: 0x800976FC
 * JP Size: 444b
 */
#ifdef VERSION_GCCJGC
unsigned long CMes::drawTagString(CFont* font, char* text, int drawChars, int breakOnLineTag, int lineBaseY)
{
    int width = 0;
    bool continueDraw = true;
    unsigned short ch;
    int lineStartX = (int)font->posX;
    while (continueDraw) {
        unsigned short c = (unsigned char)*text++;
        if (c == 0) {
            continueDraw = false;
        } else if (((c >= 0x80) && (c <= 0x9F)) || ((c >= 0xE0) && (c <= 0xFF))) {
            ch = (c << 8) | (unsigned char)*text++;
            goto drawChar;
        } else if (c >= 0xA0) {
            int tag = (c - 0xA0) & 0xFFFF;
            switch (tag) {
            case 0:
                if (breakOnLineTag != 0) {
                    font->SetPosX((float)lineStartX);
                    float lineAdvance = (float)font->m_glyphHeight * font->scaleY;
                    font->SetPosY((float)lineBaseY + (font->posY + lineAdvance));
                }
                break;
            case 1:
                continueDraw = false;
                break;
            }
        } else {
            ch = gUtil.AsciiToMulti(c);
        drawChar:
            if (drawChars != 0) {
                font->Draw(ch);
            }
            width = (int)((float)width + font->GetWidth(ch));
        }
    }
    return width;
}
#else
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
#endif

/*
 * --INFO--
 * PAL Address: 0x8009836C
 * PAL Size: 2136b
 * EN Address: 0x80097D08
 * EN Size: 2144b
 * JP Address: 0x800978B8
 * JP Size: 1128b
 */
#ifdef VERSION_GCCJGC
void CMes::MakeAgbString(char* out, char* src)
{
    int charMode = 0;
    char c;
    while ((c = *src) != 0) {
        unsigned char ch = c;
        if (((charMode == 0) || (charMode == 2)) &&
            (((ch >= 0x81) && (ch <= 0x9F)) || ((ch >= 0xE0) && (ch <= 0xFC)))) {
            charMode = 1;
        } else if ((charMode == 1) && (ch != 0x7F) && (ch >= 0x40) && (ch <= 0xFC)) {
            charMode = 2;
        } else {
            charMode = 0;
        }

        if ((charMode == 0) && (ch >= 0xA0)) {
            unsigned int tag = static_cast<unsigned char>(c - 0xA0);
            switch (tag) {
            case 0:
                *out++ = '\n';
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
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, reinterpret_cast<char*>(Game.m_caravanWorkArr[m_tempVar[varIndex]].m_name));
                out += strlen(out);
                src += 4;
                break;
            }
            case 9:
            {
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, Game.GetItemName(m_tempVar[varIndex]));
                out += strlen(out);
                src += 4;
                break;
            }
            case 0x2A:
            {
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, Game.GetMonName(m_tempVar[varIndex]));
                out += strlen(out);
                src += 4;
                break;
            }
            case 0x2B:
            {
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, Game.GetNPCName(m_tempVar[varIndex]));
                out += strlen(out);
                src += 4;
                break;
            }
            case 0x2C:
            {
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, Game.GetPlaceName(m_tempVar[varIndex]));
                out += strlen(out);
                src += 4;
                break;
            }
            case 0x2D:
            {
                char varIndex = GetMesNibbleValue(src + 3);
                strcpy(out, (Game.m_cFlatDataArr[1].TableStrings(3) + 0x3C)[m_tempVar[varIndex]]);
                out += strlen(out);
                src += 4;
                break;
            }
            case 0x2E:
            {
                char varIndex = GetMesNibbleValue(src + 1);
                strcpy(out, Game.GetLetterSubject(m_tempVar[varIndex]));
                out += strlen(out);
                src += 2;
                break;
            }
            case 0x2F:
                strcpy(out, Game.m_gameWork.m_townName);
                out += strlen(out);
                break;
            case 0x30:
            {
                char varIndex = GetMesNibbleValue(src + 1);
                sprintf(out, "%d", m_tempVar[varIndex]);
                out += strlen(out);
                src += 2;
                break;
            }
            case 0x0C: case 0x0E: case 0x13: case 0x14:
                if (static_cast<unsigned int>(System.m_execParam) >= 2) {
                    System.Printf(const_cast<char*>(s_This_TAG_is_not_created_pct02x_801D9E10), tag + 0xA0);
                }
                break;
            case 2: case 3: case 7: case 0x0A: case 0x0B: case 0x0D:
            case 0x0F: case 0x10: case 0x11: case 0x12: case 0x15: case 0x16:
            case 0x17: case 0x18: case 0x19: case 0x1A: case 0x1B: case 0x1C:
            case 0x1D: case 0x1E: case 0x1F: case 0x20: case 0x21: case 0x22:
            case 0x23: case 0x24: case 0x25: case 0x26: case 0x27: case 0x28:
            case 0x29: case 0x37:
                if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                    System.Printf(const_cast<char*>(s_Not_corresponding_TAG_is_used_pct02x_801D9E30), tag + 0xA0);
                }
                break;
            default:
                break;
            }
        } else {
            *out++ = c;
        }
        src++;
    }
}
#else
void CMes::MakeAgbString(char* out, char* src, int playerIndex, int keepHyphenOnLineBreak)
{
	static char* ELLIPSIS_STR = "...";

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
#ifndef VERSION_GCCE01
			else if (out[-1] == '-')
			{
				out[-1] = '\0';
				out--;
			}
#endif
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
				strcpy(out, Game.GetItemName(value));
				break;
			case 0x39:
				strcpy(out, Game.GetItemNames(value));
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
				strcpy(out, Game.GetItemArt(value));
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
				strcpy(out, Game.GetMonName(value));
				break;
			case 0x3A:
				strcpy(out, Game.GetMonNames(value));
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
				strcpy(out, Game.GetMonArt(value));
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
			strcpy(out, Game.GetNPCName(CMes::m_tempVar[varIndex]));
			out += strlen(out);
			src += 4;
			break;
		}
		case 0x2C:
		{
			signed char varIndex = (signed char)GetMesNibbleValue((const char*)(op + 2));
			strcpy(out, Game.GetPlaceName(CMes::m_tempVar[varIndex]));
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
			strcpy(out, Game.GetLetterSubject(CMes::m_tempVar[varIndex]));
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
			sprintf(out, "%d", CMes::m_tempVar[varIndex]);
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
#ifdef VERSION_GCCE01
		case 0x44:
		{
			int newBranchMode = 2;
			if (Game.m_caravanWorkArr[CMes::m_tempVar[19]].m_genderFlag == 0)
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
			int newBranchMode = 2;
			if (playerIndex == 0)
			{
				newBranchMode = 1;
			}
			branchMode = newBranchMode;
			break;
		}
#else
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
#endif
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
			strcpy(out, ELLIPSIS_STR);
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
#endif

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
 * PAL Address: 0x80098BC4
 * PAL Size: 192b
 * EN Address: 0x80098568
 * EN Size: 192b
 * JP Address: 0x80097D20
 * JP Size: 192b
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
 * PAL Address: 0x80098C84
 * PAL Size: 12b
 * EN Address: 0x80098628
 * EN Size: 12b
 * JP Address: 0x80097DE0
 * JP Size: 12b
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
#ifdef VERSION_GCCJGC
	font->SetMargin(1.0f);
	font->SetScale(mScaleX);
#else
	font->SetMargin(0.0f);
	float scaleY = mScaleY;
	font->SetScaleX(mScaleX);
	font->SetScaleY(scaleY);
#endif
	if (draw)
	{
		font->DrawInit();
	}
	return font;
}

/*
 * --INFO--
 * PAL Address: 0x80098C90
 * PAL Size: 1600b
 * EN Address: 0x80098634
 * EN Size: 1228b
 * JP Address: 0x80097DEC
 * JP Size: 612b
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

		CFont* font = 0;
		CMesCharCell* glyph = m_chars;
		int activeTlut = 0xFFFFFFFF;
		int activeFontId = 0xFFFFFFFF;

		for (int i = 0; i < mCounter; i++, glyph++)
		{
			if (mDrawCursor >= glyph->m_reveal)
			{
#ifndef VERSION_GCCJGC
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
#endif
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
#ifdef VERSION_GCCJGC
					font->SetScale(glyph->m_scale);
#else
					float glyphScaleY = 0.01f * (float)glyph->m_scaleY;
					font->SetScaleX(0.01f * (float)glyph->m_scaleX);
					font->SetScaleY(glyphScaleY);
#endif
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
 * PAL Address: 0x800992D0
 * PAL Size: 368b
 * EN Address: 0x80098B00
 * EN Size: 368b
 * JP Address: 0x80098050
 * JP Size: 356b
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
 * EN Address: 0x80098C70
 * EN Size: 32b
 * JP Address: 0x800981B4
 * JP Size: 32b
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
 * EN Address: 0x80098C90
 * EN Size: 7076b
 * JP Address: 0x800981D4
 * JP Size: 3956b
 */
#ifdef VERSION_GCCJGC
#include "src/mes_jp.inc"
#else
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
				strcpy(namePtr, Game.GetItemName(value));
				break;
			case 0x39:
				strcpy(namePtr, Game.GetItemNames(value));
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
				strcpy(namePtr, Game.GetItemArt(value));
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
				strcpy(namePtr, Game.GetMonName(value));
				break;
			case 0x3A:
				strcpy(namePtr, Game.GetMonNames(value));
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
				strcpy(namePtr, Game.GetMonArt(value));
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
			int value = mFlagVars[GET_1(text)] & 0xFFFF;
			char* namePtr = nameTag2B;
			strcpy(namePtr, Game.GetNPCName(value));
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
			int value = mFlagVars[GET_1(text)] & 0xFFFF;
			char* namePtr = nameTag2C;
			strcpy(namePtr, Game.GetPlaceName(value));
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
			int value = mFlagVars[GET_1(text)] & 0xFFFF;
			char* namePtr = nameTag2D;
			strcpy(namePtr, Game.GetPlaceName(value + 0x3C));
			ApplyCaseMode(namePtr, caseMode);
			addString(&namePtr, branchMode);
			mColor = oldColor;
			break;
		}
		case 0x2E:
		{
			char* flatText = Game.GetLetterSubject(mFlagVars[GET_1(text)] & 0xFFFF);
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
			sprintf(number, "%d", mFlagVars[GET_1(text)]);
			numberPtr = number;
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
					System.Printf(const_cast<char*>(s_MessageSpeedTagUsed));
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
			char vowel = *Game.GetNPCName(mFlagVars[GET_1(text)]);
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
			char* src = "...";
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
#endif

/*
 * --INFO--
 * PAL Address: 0x8009AF54
 * PAL Size: 532b
 * EN Address: 0x8009A834
 * EN Size: 532b
 * JP Address: 0x80099148
 * JP Size: 524b
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
	char tempFlags[sizeof(mFlagVars)];

	if (mText != 0)
	{
		useFlag(mFlagCount, 1);
		mCounter = 0;
		halfVal = 0.0f;
		mFlagCursor = 0;
		mFlagCount = 0;
#ifdef VERSION_GCCJGC
		mCurrentX = mCurrentY = 0.0f;
		mLineWidth = mLineHeight = 0.0f;
#else
		mCurrentY = halfVal;
		mCurrentX = halfVal;
		mLineHeight = halfVal;
		mLineWidth = halfVal;
#endif
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
 * PAL Address: 0x8009B168
 * PAL Size: 436b
 * EN Address: 0x8009AA48
 * EN Size: 436b
 * JP Address: 0x80099354
 * JP Size: 404b
 */
void CMes::Set(char* text, int param)
{
	mText = text;
	mWaitActive = 0;
#ifdef VERSION_GCCJGC
	mMaxWidth = mMaxHeight = 0.0f;
#else
	mMaxHeight = 0.0f;
	mMaxWidth = 0.0f;
#endif
	mCounter = 0;
	mFlagCursor = 0;
	mFlagCount = 0;
	mRubyEnabled = 0;
	mFontCount = param;
#ifdef VERSION_GCCJGC
	mLineSpacing = 1.0f;
#else
	mLineSpacing = 0.0f;
#endif
	mFontIndex = 0;
	mScaleX = 1.0f;
#ifndef VERSION_GCCJGC
	mScaleY = 1.0f;
	mAdvanceEnabled = 1;
#endif

	if (text != 0) {
		unsigned char flagBackup[sizeof(mFlagVars)];
		memcpy(flagBackup, mFlagVars, sizeof(flagBackup));
		float lineZero = 0.0f;

		while (mWaitActive == 0) {
			mCounter = 0;
			mFlagCursor = 0;
			mFlagCount = 0;
#ifdef VERSION_GCCJGC
			mCurrentX = mCurrentY = 0.0f;
			mLineWidth = mLineHeight = 0.0f;
#else
			mCurrentY = lineZero;
			mCurrentX = lineZero;
			mLineHeight = lineZero;
			mLineWidth = lineZero;
#endif

			addString(&mText, 1);

			mMaxWidth = (mLineWidth < mMaxWidth) ? mMaxWidth : mLineWidth;
			mMaxHeight = (mLineHeight < mMaxHeight) ? mMaxHeight : mLineHeight;
		}

		memcpy(mFlagVars, flagBackup, sizeof(flagBackup));
#ifdef VERSION_GCCJGC
		float lineSkip = 8.0f;
#else
		float lineSkip = -2.0f;
#endif
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
#ifdef VERSION_GCCJGC
		mLineSpacing = 1.0f;
#else
		mLineSpacing = 0.0f;
#endif
		mFontIndex = 0;
		mScaleX = 1.0f;
#ifndef VERSION_GCCJGC
		mScaleY = 1.0f;
		mAdvanceEnabled = 1;
#endif
		Next();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009B31C
 * PAL Size: 60b
 * EN Address: 0x8009ABFC
 * EN Size: 60b
 * JP Address: 0x800994E8
 * JP Size: 60b
 */
CMes::~CMes()
{
}

/*
 * --INFO--
 * PAL Address: 0x8009B358
 * PAL Size: 92b
 * EN Address: 0x8009AC38
 * EN Size: 92b
 * JP Address: 0x80099524
 * JP Size: 92b
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
