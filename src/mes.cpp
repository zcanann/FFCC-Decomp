#include "ffcc/mes.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"
#include "ffcc/joybus.h"
#include <string.h>

extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFUs(CFont*, unsigned short);
extern "C" float GetWidth__5CFontFUs(CFont*, unsigned short);
extern "C" void SetShadow__5CFontFi(int, CFont*);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetScaleX__5CFontFf(float, CFont*);
extern "C" void SetScaleY__5CFontFf(float, CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, _GXColor*);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void DrawQuit__5CFontFv(CFont*);
extern "C" int GetPadType__6JoyBusFi(void*, int);
extern "C" void DrawInit__8CMenuPcsFv(void*);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void SetColor__8CMenuPcsFR6CColor(void*, void*);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(
    void*, unsigned long, float, float, float, float, float, float, float, float, float);
extern unsigned char MenuPcs[];
extern float FLOAT_80330890;
extern float FLOAT_80330894;
extern float FLOAT_80330898;
extern float FLOAT_8033089c;
extern float FLOAT_803308a0;
extern float FLOAT_803308ac;
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" int m_tempVar__4CMes[];
extern "C" int sprintf(char*, const char*, ...);
extern "C" int toupper(int);
extern "C" int tolower(int);

static const char s_mesTagUnknown[] = "Not corresponding TAG is used. %02x\n";
static const char s_mesTagMissing[] = "This TAG is not created. %02x\n";
static const char s_mesNumFmt[] = "%d";
static const char s_mesFallback[] = "---";
static const char s_mesEmpty[] = "";

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

static int GetMesNibbleValue(const char* data)
{
	unsigned char high = (unsigned char)data[0];
	unsigned char low = (unsigned char)data[1];
	return (int)((unsigned int)(high << 4) | ((unsigned int)low & 0x0F));
}

static int ReadTagU8(char** text)
{
	int value = GetMesNibbleValue(*text);
	*text += 2;
	return value;
}

static int ReadTagS8(char** text)
{
	int value = GetMesNibbleValue(*text);
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
		for (char* p = text; *p != '\0'; ++p)
		{
			*p = (char)toupper((unsigned char)*p);
		}
	}
	else if (caseMode == 2)
	{
		text[0] = (char)toupper((unsigned char)text[0]);
	}
	else
	{
		for (char* p = text; *p != '\0'; ++p)
		{
			*p = (char)tolower((unsigned char)*p);
		}
	}

	caseMode = 0;
}

static char* GetFlatName(int tableIdx, int entryIdx)
{
	CMesFlatDataView* flat = (CMesFlatDataView*)&Game.game.m_cFlatDataArr[1];
	if ((unsigned int)tableIdx >= 8U)
	{
		return (char*)s_mesEmpty;
	}
	if ((unsigned int)entryIdx >= (unsigned int)flat->m_tabl[tableIdx].m_numEntries)
	{
		return (char*)s_mesEmpty;
	}
	return flat->m_tabl[tableIdx].m_strings[entryIdx];
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
 * Address: 8009b168
 * Size: 436b
 */
void CMes::Set(char* text, int param)
{
	*(int*)((char*)this + 4) = (int)text;
	*(int*)((char*)this + 0x3c74) = 0;
	*(float*)((char*)this + 0x3ca8) = 0.0f;
	*(float*)((char*)this + 0x3ca4) = 0.0f;
	*(int*)((char*)this + 8) = 0;
	*(int*)((char*)this + 0x3c10) = 0;
	*(int*)((char*)this + 0x3c0c) = 0;
	*(int*)((char*)this + 0x3d10) = 0;
	*(int*)((char*)this + 0x3d30) = param;
	*(float*)((char*)this + 0x3d3c) = 0.0f;
	*(int*)((char*)this + 0x3d40) = 0;
	*(float*)((char*)this + 0x3d44) = 1.0f;
	*(float*)((char*)this + 0x3d48) = 1.0f;
	*(int*)((char*)this + 0x3d4c) = 1;
	
	if (text != 0)
	{
		// Copy data and process text
		memcpy((char*)this + 0x3cc0, (char*)this + 0x3cc0, 0x50);
		
		while (*(int*)((char*)this + 0x3c74) == 0)
		{
			*(int*)((char*)this + 8) = 0;
			*(int*)((char*)this + 0x3c10) = 0;
			*(int*)((char*)this + 0x3c0c) = 0;
			*(float*)((char*)this + 0x3c88) = 0.0f;
			*(float*)((char*)this + 0x3c84) = 0.0f;
			*(float*)((char*)this + 0x3c90) = 0.0f;
			*(float*)((char*)this + 0x3c8c) = 0.0f;
			
			// Call addString - simplified
			break; // Avoid infinite loop for now
		}
		
		// Final setup
		*(int*)((char*)this + 4) = (int)text;
		*(int*)((char*)this + 0x3c74) = 0;
		*(int*)((char*)this + 0x3cb0) = 0;
		*(int*)((char*)this + 0x3cb4) = 3;
		*(int*)((char*)this + 0x3cb8) = 0;
		*(int*)((char*)this + 0x3d10) = 0;
		*(int*)((char*)this + 0x3d2c) = 0;
		*(int*)((char*)this + 0x3d28) = 7;
		*(float*)((char*)this + 0x3d3c) = 0.0f;
		*(int*)((char*)this + 0x3d40) = 0;
		*(float*)((char*)this + 0x3d44) = 1.0f;
		*(float*)((char*)this + 0x3d48) = 1.0f;
		*(int*)((char*)this + 0x3d4c) = 1;
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
	if (*(int*)((char*)this + 4) != 0)
	{
		int entryCount = *(int*)((char*)this + 0x3c0c);
		unsigned char* flagEntry = (unsigned char*)((char*)this + *(int*)((char*)this + 0x3c10) * 6 + 0x3c14);

		while (*(int*)((char*)this + 0x3c10) < entryCount)
		{
			unsigned char type = flagEntry[0];
			if (type != 3)
			{
				if (type == 1)
				{
					int idx = (unsigned int)flagEntry[2] * 4 + 0x3cc0;
					*(int*)((char*)this + idx) = *(int*)((char*)this + idx) + 1;
				}
				else if (type != 0)
				{
					*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0) = (int)*(short*)(flagEntry + 4);
				}
			}

			flagEntry += 6;
			*(int*)((char*)this + 0x3c10) = *(int*)((char*)this + 0x3c10) + 1;
		}

		*(int*)((char*)this + 8) = 0;
		*(int*)((char*)this + 0x3c10) = 0;
		*(int*)((char*)this + 0x3c0c) = 0;
		*(float*)((char*)this + 0x3c88) = 0.0f;
		*(float*)((char*)this + 0x3c84) = 0.0f;
		*(float*)((char*)this + 0x3c90) = 0.0f;
		*(float*)((char*)this + 0x3c8c) = 0.0f;
		*(int*)((char*)this + 0x3c80) = 0;
		*(int*)((char*)this + 0x3c7c) = 0;
		*(int*)((char*)this + 0x3cac) = 0;

		char tempFlags[0x50];
		memcpy(tempFlags, (char*)this + 0x3cc0, sizeof(tempFlags));
		addString((char**)((char*)this + 4), 0);
		memcpy((char*)this + 0x3cc0, tempFlags, sizeof(tempFlags));

		int i = 0;
		float* curr = (float*)((char*)this + 0xc);
		while (i < *(int*)((char*)this + 8))
		{
			float* start = curr;
			i++;
			curr = start + 5;

			int remaining = *(int*)((char*)this + 8) - i;
			if (i < *(int*)((char*)this + 8))
			{
				do
				{
					if (((*(unsigned char*)((char*)start + 0xe) >> 4) != (*(unsigned char*)((char*)curr + 0xe) >> 4)) ||
					    (*(short*)(start + 2) != *(short*)(curr + 2)))
					{
						break;
					}
					i++;
					curr += 5;
					remaining--;
				} while (remaining != 0);
			}

			unsigned int runLength = (unsigned int)(((char*)curr - (char*)start) / 0x14);
			float groupWidth = (curr[-5] - start[0]) + start[1] + *(float*)((char*)this + 0x3d3c);
			while (runLength != 0)
			{
				unsigned char align = *(unsigned char*)((char*)start + 0xe) >> 4;
				if (align == 1)
				{
					start[0] = 0.5f * (*(float*)((char*)this + 0x3ca4) - groupWidth) + start[0];
				}
				else if (align == 2)
				{
					start[0] = start[0] + (*(float*)((char*)this + 0x3ca4) - groupWidth);
				}
				start += 5;
				runLength--;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::getFont(int, int)
{
	// TODO
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
	CFont* font = *(CFont**)(MenuPcs + 0x100);
	int fontSel = *(int*)((char*)this + 0x3D40);
	int caseMode = 0;
	int flowMode = branchMode;
	if (fontSel == 0)
	{
		font = *(CFont**)(MenuPcs + 0x0F8);
	}
	else if ((fontSel == 1) || (fontSel >= 4))
	{
		// Keep current font pointer selection for unsupported modes.
	}
	else
	{
		font = *(CFont**)(MenuPcs + 0x100);
	}

	if (font == 0)
	{
		return;
	}

	SetShadow__5CFontFi(*(int*)((char*)this + 0x3D38), font);
	SetMargin__5CFontFf(FLOAT_8033089c, font);
	SetScaleX__5CFontFf(*(float*)((char*)this + 0x3D44), font);
	SetScaleY__5CFontFf(*(float*)((char*)this + 0x3D48), font);

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
			unsigned int tag = ((unsigned int)(unsigned char)**text - 0xA0U) & 0xFFU;
			*text = *text + 1;

			switch (tag)
			{
			case 0:
				*(int*)((char*)this + 0x3C84) = 0;
				*(int*)((char*)this + 0x3C88) = *(int*)((char*)this + 0x3C88) + *(int*)((char*)this + 0x3CB0);
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
				return;
			}
			case 2:
				*(int*)((char*)this + 0x3C78) = 4;
				*(int*)((char*)this + 0x3C74) = 1;
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
				SetScaleX__5CFontFf(*(float*)((char*)this + 0x3D44), font);
				SetScaleY__5CFontFf(*(float*)((char*)this + 0x3D48), font);
				break;
			case 0x1B:
			{
				int idx = ReadTagU8(text);
				flowMode = ((m_tempVar__4CMes[idx] & 1) == 0) ? 1 : 2;
				break;
			}
			case 0x1C:
			{
				int idx = ReadTagU8(text);
				flowMode = ((m_tempVar__4CMes[idx] & 1) != 0) ? 1 : 2;
				break;
			}
			case 0x25:
			{
				int value = ReadTagS8(text);
				if (*(int*)((char*)this + 0x3D4C) == 0)
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
				break;
			}
			case 0x26:
				*(int*)((char*)this + 0x3CB4) = ReadTagS8(text);
				break;
			case 0x27:
				*(int*)((char*)this + 0x3CB8) = ReadTagS8(text);
				break;
			case 0x31:
				*(int*)((char*)this + 0x3C84) = ReadTagS16(text);
				*(int*)((char*)this + 0x3C88) = ReadTagS16(text);
				break;
			case 0x33:
				*(int*)((char*)this + 0x3D3C) = ReadTagS8(text);
				break;
			case 0x34:
			{
				*(int*)((char*)this + 0x3D40) = ReadTagS8(text);
				int nextFontSel = *(int*)((char*)this + 0x3D40);
				if (nextFontSel == 0)
				{
					font = *(CFont**)(MenuPcs + 0x0F8);
				}
				else
				{
					font = *(CFont**)(MenuPcs + 0x100);
				}
				SetShadow__5CFontFi(*(int*)((char*)this + 0x3D38), font);
				SetMargin__5CFontFf(FLOAT_8033089c, font);
				SetScaleX__5CFontFf(*(float*)((char*)this + 0x3D44), font);
				SetScaleY__5CFontFf(*(float*)((char*)this + 0x3D48), font);
				break;
			}
			case 0x35:
			{
				float scale = FLOAT_803308a0 * (float)ReadTagS16(text);
				*(float*)((char*)this + 0x3D44) = scale;
				*(float*)((char*)this + 0x3D48) = scale;
				SetScaleX__5CFontFf(*(float*)((char*)this + 0x3D44), font);
				SetScaleY__5CFontFf(*(float*)((char*)this + 0x3D48), font);
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
				flowMode = (m_tempVar__4CMes[idx] == 1) ? 1 : 2;
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

		char tmpCharBuf[2];
		tmpCharBuf[0] = (char)ch;
		tmpCharBuf[1] = '\0';
		ApplyCaseMode(tmpCharBuf, caseMode);
		ch = (unsigned char)tmpCharBuf[0];

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
			glyph[1] = GetWidth__5CFontFUs(font, ch);
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
 * Address:	TODO
 * Size:	TODO
 */
void CMes::GET_2(char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::GET_1(char **)
{
	// TODO
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
			unsigned char fadeMax = *(unsigned char*)(textEntry + 0xF) >> 4;
			unsigned char fadeCurr = (*(unsigned char*)(textEntry + 0xF) & 0xF) + 1;
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
	while (true)
	{
		if ((int)maxAdvance <= *(int*)((char*)this + 0x3C10))
		{
			break;
		}

		unsigned char type = *flagEntry;
		if (type != 3)
		{
			if (type < 3)
			{
				if (type == 1)
				{
					int idx = (unsigned int)flagEntry[2] * 4 + 0x3CC0;
					*(int*)((char*)this + idx) = *(int*)((char*)this + idx) + 1;
				}
				else if (type != 0)
				{
					*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3CC0) =
					    (int)*(short*)(flagEntry + 4);
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
		if (next > 0x7FFE)
		{
			next = 0x7FFF;
		}
		*(int*)((char*)this + 0x3C80) = next;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMes::Draw()
{
	int glyphCount = *(int*)((char*)this + 8);
	if (glyphCount == 0)
	{
		return;
	}

	unsigned int globalAlpha = 0xFF;
	if ((*(int*)((char*)this + 0x3CAC) != 0) && (*(int*)((char*)this + 0x3CB8) != 0))
	{
		globalAlpha = 0xFF - (unsigned int)(*(int*)((char*)this + 0x3CBC) * 0xFF) /
		                        (unsigned int)*(int*)((char*)this + 0x3CB8);
	}

	float* glyph = (float*)((char*)this + 0x0C);
	CFont* activeFont = 0;
	unsigned int activeFontId = 0xFFFFFFFF;
	unsigned int activeTlut = 0xFFFFFFFF;

	for (int i = 0; i < glyphCount; i++)
	{
		if ((unsigned int)(unsigned short)*(short*)(glyph + 2) <= *(unsigned int*)((char*)this + 0x3C80))
		{
			unsigned char ch = *(unsigned char*)(glyph + 4);
			if (ch < 0x20)
			{
				if (activeFont != 0)
				{
					DrawQuit__5CFontFv(activeFont);
					activeFontId = 0xFFFFFFFF;
				}

				DrawInit__8CMenuPcsFv(MenuPcs);

				unsigned int iconId = ch;
				if ((ch == 7) || (ch == 8) || (ch == 0x0A) || (ch == 0x0B))
				{
					unsigned int mode = (unsigned int)Game.game.m_gameWork.m_menuStageMode;
					if ((Game.game.m_currentMapId == 0x21) && (GetPadType__6JoyBusFi(&Joybus, 0) != 0x40))
					{
						int padType = GetPadType__6JoyBusFi(&Joybus, 0);
						mode = (unsigned int)((0x40000U - (unsigned int)padType |
						                       (unsigned int)padType - 0x40000U) >>
						                      31);
					}

					if (ch == 7)
					{
						iconId = (mode != 0) ? 7 : 0x0B;
					}
					else if (ch == 8)
					{
						iconId = (mode != 0) ? 8 : 0x0C;
					}
					else if (ch == 0x0A)
					{
						iconId = (mode != 0) ? 9 : 0x0D;
					}
					else
					{
						iconId = (mode != 0) ? 0x0A : 0x0E;
					}
				}

				unsigned char colorStorage[8];
				__ct__6CColorFUcUcUcUc(colorStorage, 0xFF, 0xFF, 0xFF, 0xFF);
				SetColor__8CMenuPcsFR6CColor(MenuPcs, colorStorage);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x15);

				float x = *(float*)((char*)this + 0x3C9C) + *glyph;
				float y = FLOAT_80330890 + *(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2);
				float u = (float)((iconId % 5) * 0x16);
				float v = (float)((iconId / 5) * 0x16);

				DrawRect__8CMenuPcsFUlfffffffff(
				    MenuPcs, 0, x, y, FLOAT_80330894, FLOAT_80330894, u, v, FLOAT_80330898, FLOAT_80330898,
				    0.0f);

				if (activeFont != 0)
				{
					DrawInit__5CFontFv(activeFont);
				}
			}
			else
			{
				unsigned int fontId = *(unsigned char*)((char*)glyph + 0x0E) & 0x0F;
				if (activeFontId != fontId)
				{
					CFont* selectedFont = *(CFont**)(MenuPcs + 0x100);
					if (fontId == 0)
					{
						selectedFont = *(CFont**)(MenuPcs + 0x0F8);
					}
					else if ((fontId == 1) || (fontId >= 4))
					{
						selectedFont = activeFont;
					}

					activeFont = selectedFont;
					if (activeFont == 0)
					{
						glyph += 5;
						continue;
					}

					SetShadow__5CFontFi(*(int*)((char*)this + 0x3D38), activeFont);
					SetMargin__5CFontFf(FLOAT_8033089c, activeFont);
					SetScaleX__5CFontFf(*(float*)((char*)this + 0x3D44), activeFont);
					SetScaleY__5CFontFf(*(float*)((char*)this + 0x3D48), activeFont);
					DrawInit__5CFontFv(activeFont);

					activeFontId = fontId;
				}

				unsigned int fadeCur = *(unsigned char*)((char*)glyph + 0x0F) & 0x0F;
				unsigned int fadeMax = (unsigned int)*(unsigned char*)((char*)glyph + 0x0F) >> 4;
				unsigned char alpha = (unsigned char)globalAlpha;
				if (fadeMax != 0)
				{
					float ratio = (float)fadeCur / (float)fadeMax;
					if (ratio < FLOAT_80330898)
					{
						alpha = (unsigned char)((float)globalAlpha * ratio);
					}
				}

				_GXColor color = {0xFF, 0xFF, 0xFF, alpha};
				SetColor__5CFontF8_GXColor(activeFont, &color);

				unsigned int tlut = (unsigned int)*(unsigned char*)((char*)glyph + 0x12);
				if ((activeTlut != tlut) && (activeFontId < 2))
				{
					SetTlut__5CFontFi(activeFont, (int)tlut + *(int*)((char*)this + 0x3D34));
					activeTlut = tlut;
				}

				SetPosX__5CFontFf(*(float*)((char*)this + 0x3C9C) + *glyph, activeFont);
				SetPosY__5CFontFf(*(float*)((char*)this + 0x3CA0) + (float)*(short*)(glyph + 2), activeFont);

				SetScaleX__5CFontFf(FLOAT_803308a0 * (float)*(unsigned char*)((char*)glyph + 0x0A), activeFont);
				SetScaleY__5CFontFf(FLOAT_803308a0 * (float)*(unsigned char*)((char*)glyph + 0x11), activeFont);

				activeFont->renderFlags = activeFont->renderFlags & 0xF7 | 8;
				Draw__5CFontFUs(activeFont, ch);
				activeFont->renderFlags &= 0xF7;
			}
		}

		glyph += 5;
	}

	if (activeFont != 0)
	{
		DrawQuit__5CFontFv(activeFont);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::SetPosition(float x, float y)
{
	*(float*)&mData[0x3c90] = x;
	*(float*)&mData[0x3c94] = y;
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
	while (true)
	{
		if (maxCount <= *(int*)((char*)this + 0x3c10))
		{
			return 1;
		}

		unsigned char type = flagEntry[0];
		if (type != 3)
		{
			if (type < 3)
			{
				if (type == 1)
				{
					int idx = (unsigned int)flagEntry[2] * 4 + 0x3cc0;
					*(int*)((char*)this + idx) = *(int*)((char*)this + idx) + 1;
				}
				else if (type != 0)
				{
					*(int*)((char*)this + (unsigned int)flagEntry[2] * 4 + 0x3cc0) = (int)*(short*)(flagEntry + 4);
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::addFlag(CMes::CFlag&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::CFlag::operator= (const CMes::CFlag&)
{
	// TODO
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
	static char* sTag54Source = (char*)s_mesEmpty;
	static int sTag54Init = 0;
	if (sTag54Init == 0)
	{
		sTag54Source = (char*)s_mesEmpty;
		sTag54Init = 1;
	}

	int caseMode = 0;
	int branchMode = 0;
	const unsigned char* in = (const unsigned char*)src;
	char* dst = out;

	while (true)
	{
		unsigned char c = in[0];
		if (c == 0)
		{
			*dst = '\0';
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
			else if ((dst > out) && (dst[-1] == '-'))
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
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			const char* text = GetFlatName(5, m_tempVar__4CMes[varIndex]);
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
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			int value = m_tempVar__4CMes[varIndex];
			if ((tag == 9) || (tag == 0x37))
			{
				strcpy(dst, GetFlatName(0, value * 5 + 1));
			}
			else if (tag == 0x1D)
			{
				strcpy(dst, GetFlatName(0, value * 5));
			}
			else if (tag == 0x39)
			{
				strcpy(dst, GetFlatName(0, value * 5 + 3));
			}
			else if (tag == 0x3B)
			{
				Game.game.MakeArtItemName(dst, value, 1);
			}
			else if (tag == 0x3D)
			{
				int countIdx = GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)m_tempVar__4CMes[countIdx] & 0xFFFF;
				Game.game.MakeArtItemName(dst, value, count);
			}
			else
			{
				int countIdx = GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)m_tempVar__4CMes[countIdx] & 0xFFFF;
				Game.game.MakeNumItemName(dst, value, count);
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
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			int value = m_tempVar__4CMes[varIndex];
			if ((tag == 0x2A) || (tag == 0x38))
			{
				strcpy(dst, GetFlatName(1, value * 5 + 1));
			}
			else if (tag == 0x1E)
			{
				strcpy(dst, GetFlatName(1, value * 5));
			}
			else if (tag == 0x3A)
			{
				strcpy(dst, GetFlatName(1, value * 5 + 3));
			}
			else if (tag == 0x3C)
			{
				Game.game.MakeArtMonName(dst, value, 1);
			}
			else if (tag == 0x3E)
			{
				int countIdx = GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)m_tempVar__4CMes[countIdx] & 0xFFFF;
				Game.game.MakeArtMonName(dst, value, count);
			}
			else
			{
				int countIdx = GetMesNibbleValue((const char*)in + 6);
				int count = (unsigned int)m_tempVar__4CMes[countIdx] & 0xFFFF;
				Game.game.MakeNumMonName(dst, value, count);
			}
			ApplyCaseMode(dst, caseMode);
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2B:
		{
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, GetFlatName(2, m_tempVar__4CMes[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2C:
		{
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, GetFlatName(3, m_tempVar__4CMes[varIndex]));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2D:
		{
			int varIndex = GetMesNibbleValue((const char*)in + 4);
			strcpy(dst, GetFlatName(3, m_tempVar__4CMes[varIndex] + 0x3C));
			dst += strlen(dst);
			next = in + 6;
			break;
		}
		case 0x2E:
		{
			int varIndex = GetMesNibbleValue((const char*)in + 2);
			strcpy(dst, GetFlatName(5, m_tempVar__4CMes[varIndex]));
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
			int varIndex = GetMesNibbleValue((const char*)in + 2);
			sprintf(dst, s_mesNumFmt, m_tempVar__4CMes[varIndex]);
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
			int varIndex = GetMesNibbleValue((const char*)in + 2);
			branchMode = (m_tempVar__4CMes[varIndex] == 1) ? 1 : 2;
			next = in + 4;
			break;
		}
		case 0x44:
			branchMode = (playerIndex == 0) ? 1 : 2;
			break;
		case 0x45:
		{
			int varIndex = GetMesNibbleValue((const char*)in + 2);
			int caravanIdx = m_tempVar__4CMes[varIndex];
			branchMode = (Game.game.m_caravanWorkArr[caravanIdx].m_genderFlag == 0) ? 1 : 2;
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
				Printf__7CSystemFPce(&System, s_mesTagMissing, tag + 0xA0);
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
				Printf__7CSystemFPce(&System, s_mesTagUnknown, tag + 0xA0);
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
 * PAL Address: 0x800981f0
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMes::drawTagString(CFont* font, char* text, int drawChars, int breakOnLineTag, int lineBaseY)
{
	u32 width = 0;
	u8* src = (u8*)text;
	bool continueDraw = true;
	float lineStartX = font->posX;

	while (continueDraw)
	{
		u8 ch = *src;
		u8* next = src + 1;

		if (ch == 0)
		{
			continueDraw = false;
			src = next;
		}
		else if (ch == 0xFF)
		{
			u8 tag = *next;
			src += 2;
			if (tag == 0xA1)
			{
				continueDraw = false;
			}
			else if ((tag == 0xA0) && (breakOnLineTag != 0))
			{
				SetPosX__5CFontFf(lineStartX, font);
				SetPosY__5CFontFf((float)(double)lineBaseY + font->posY + (float)(double)font->m_glyphWidth * font->scaleY, font);
			}
		}
		else
		{
			if (drawChars != 0)
			{
				Draw__5CFontFUs(font, (unsigned short)ch);
			}
			width = (u32)((double)(float)(int)width + (double)GetWidth__5CFontFUs(font, (unsigned short)ch));
			src = next;
		}
	}

	return (unsigned long)width;
}
