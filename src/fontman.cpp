#include "ffcc/fontman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/color.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_camera.h"
extern "C" {
unsigned char g_tFont22[0x10D40] = {
#include "src/font_res_archive.inc"
};
}
#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/math.h"
#include <dolphin/mtx.h>

extern "C" const float kFontZero = 0.0f;
extern "C" const double DOUBLE_803306C0 = 4503601774854144.0;
extern "C" const float kFontOne = 1.0f;
extern "C" const double DOUBLE_803306D0 = 4503599627370496.0;
extern "C" const float kFontOrthoHeight = 448.0f;
extern "C" const float kFontOrthoWidth = 640.0f;
extern "C" const unsigned int kYmTracerTopColorBase = 0xFFFFFF00;
extern "C" const unsigned int kYmTracerBottomColorBase = 0xFFFFFF00;
extern "C" const float FLOAT_803306e8 = 0.0f;
extern "C" const float FLOAT_803306ec = 1.0f;

extern "C" const char s_fontman_cpp[] = "fontman.cpp";

CFontMan FontMan;

namespace {
typedef void (*VirtualDtorFn)(void*, int);

struct CFontRenderFlagBits
{
	signed char shadow : 1;
	signed char zCompare : 1;
	signed char zUpdate : 1;
	signed char fixedWidth : 1;
	signed char snapPosition : 1;
	signed char pad : 3;
};

inline CFontRenderFlagBits& GetRenderFlagBits(unsigned char& flags)
{
	return reinterpret_cast<CFontRenderFlagBits&>(flags);
}

static inline float LoadFloat(const float& value)
{
	return value;
}
}

/*
 * --INFO--
 * PAL Address: 0x80091e58
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CFont::GetWidth(unsigned short ch)
{
	unsigned short* glyphBucket = m_glyphBuckets[ch & 0xFF];
	unsigned short* glyph = glyphBucket + 1;
	int count = static_cast<int>(*glyphBucket);

	for (; count > 0; count--) {
		if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) != ((ch >> 8) & 0xFF)) {
			glyph += 4;
		} else {
			goto found_glyph;
		}
	}
	glyph = 0;

found_glyph:
	if (glyph == 0) {
		goto find_fallback;
	}

found_fallback:
	int drawWidth;
	float localMargin = margin;
	float localScaleX = scaleX;
	CFontRenderFlagBits& renderFlagBits = GetRenderFlagBits(renderFlags);

	if (renderFlagBits.fixedWidth != 0) {
		drawWidth = static_cast<int>(m_glyphWidth);
	} else {
		signed char sign = static_cast<signed char>(renderFlagBits.shadow);
		unsigned int extra = static_cast<unsigned int>(-static_cast<int>(sign) | static_cast<int>(sign)) >> 30 & 2;
		drawWidth = static_cast<int>(*(reinterpret_cast<unsigned char*>(glyph) + extra + 4));
	}

	float width = localScaleX * (localMargin + static_cast<float>(drawWidth));
	if (renderFlagBits.snapPosition != 0) {
		width = static_cast<float>(floor(width));
	}

	return width;

find_fallback:
	glyphBucket = m_glyphBuckets[63];
	unsigned short* fallbackGlyph = glyphBucket + 1;
	for (count = static_cast<int>(*glyphBucket); count > 0; count--) {
		if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(fallbackGlyph + 1)) != 0) {
			fallbackGlyph += 4;
		} else {
			goto found_fallback_glyph;
		}
	}
	fallbackGlyph = 0;
found_fallback_glyph:
	glyph = fallbackGlyph;
	if (glyph != 0) {
		goto found_fallback;
	}
	return kFontZero;
}

/*
 * --INFO--
 * PAL Address: 0x80091f88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CFont::GetWidth(char* text)
{
	char* textPtr = text;
	float width = kFontZero;
	unsigned short ch;
	int hasChar;

	goto read_char;

	while (hasChar != 0) {
		unsigned short* currentBucket = m_glyphBuckets[ch & 0xFF];
		unsigned short* glyph = currentBucket + 1;
		int count = static_cast<int>(*currentBucket);
		float charWidth;

		for (; count > 0; count--) {
			if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) != ((ch >> 8) & 0xFF)) {
				glyph += 4;
			} else {
				goto found_glyph;
			}
		}
		glyph = 0;

found_glyph:
		if (glyph == 0) {
			goto find_fallback;
		}

use_glyph:
		CFontRenderFlagBits& renderFlagBits = GetRenderFlagBits(renderFlags);
		int drawWidth;
		float localMargin = margin;
		float localScaleX = scaleX;

		if (renderFlagBits.fixedWidth != 0) {
			drawWidth = static_cast<int>(m_glyphWidth);
		} else {
			signed char sign = static_cast<signed char>(renderFlagBits.shadow);
			drawWidth = static_cast<int>(
			    *(reinterpret_cast<unsigned char*>(glyph) +
			      ((static_cast<unsigned int>(-static_cast<int>(sign) | static_cast<int>(sign)) >> 30 & 2) + 4)));
		}

		charWidth = localScaleX * (localMargin + static_cast<float>(drawWidth));
		if (renderFlagBits.snapPosition != 0) {
			charWidth = static_cast<float>(floor(charWidth));
		}
		goto add_width;

find_fallback:
		unsigned short* glyphBucket = m_glyphBuckets[63];
		unsigned short* fallbackGlyph = glyphBucket + 1;
		count = static_cast<int>(*glyphBucket);
		for (; count > 0; count--) {
			if (*reinterpret_cast<unsigned char*>(fallbackGlyph + 1) != 0) {
				fallbackGlyph += 4;
			} else {
				goto use_fallback_glyph;
			}
		}
		fallbackGlyph = 0;
use_fallback_glyph:
		glyph = fallbackGlyph;
		if (glyph != 0) {
			goto use_glyph;
		}
		charWidth = kFontZero;

add_width:
		width += charWidth;
		goto read_char;

read_char:
		if (static_cast<unsigned char>(*textPtr) == 0) {
			hasChar = 0;
		} else {
			ch = static_cast<unsigned char>(*textPtr);
			hasChar = 1;
			textPtr++;
		}
	}

	return width;
}

/*
 * --INFO--
 * PAL Address: 0x8009211c
 * PAL Size: 1088b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Draw(unsigned short ch)
{
	unsigned short* glyph = m_glyphBuckets[ch & 0xFF] + 1;
	int count = static_cast<int>(m_glyphBuckets[ch & 0xFF][0]);

	for (; count > 0; count--) {
		if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) != ((ch >> 8) & 0xFF)) {
			glyph += 4;
		} else {
			goto found_glyph;
		}
	}
	glyph = 0;

found_glyph:
	if (glyph == 0) {
		unsigned short* glyphBucket = m_glyphBuckets[63];
		glyph = glyphBucket + 1;
		for (count = static_cast<int>(*glyphBucket); count > 0; count--) {
			if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) != 0) {
				glyph += 4;
			} else {
				goto found_fallback;
			}
		}
		glyph = 0;

found_fallback:
		if (glyph == 0) {
			return;
		}
	}

	unsigned char flags = renderFlags;
	CFontRenderFlagBits& renderFlagBits = GetRenderFlagBits(renderFlags);
	signed char sign = static_cast<signed char>(renderFlagBits.shadow);
	int drawWidth;
	unsigned char* glyphInfo = reinterpret_cast<unsigned char*>(glyph) +
	                           ((static_cast<unsigned int>(-static_cast<int>(sign) | static_cast<int>(sign)) >> 30 & 2) + 3);
	int glyphIndex;
	int row;
	float u0;
	float v0;

	if (renderFlagBits.fixedWidth == 0) {
		glyphIndex = static_cast<int>(*glyph);
		row = glyphIndex / m_glyphColumns;
		drawWidth = static_cast<int>(glyphInfo[1]);
		u0 = static_cast<float>((static_cast<int>(glyphInfo[0]) + m_glyphWidth * (glyphIndex - row * m_glyphColumns)) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	} else {
		drawWidth = static_cast<int>(m_glyphWidth);
		glyphIndex = static_cast<int>(*glyph);
		row = glyphIndex / m_glyphColumns;
		u0 = static_cast<float>(drawWidth * (glyphIndex - row * m_glyphColumns) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	}

	float x0 = posX;
	float y0 = posY;
	if (renderFlagBits.snapPosition != 0) {
		x0 = static_cast<float>(floor(x0));
		y0 = static_cast<float>(floor(y0));
	}

	float advance = scaleX * (margin + static_cast<float>(drawWidth));
	float u1 = u0 + static_cast<float>(drawWidth * 2);
	float v1 = v0 + static_cast<float>(m_glyphHeight * 2);
	float x1 = x0 + static_cast<float>(drawWidth) * scaleX;
	float y1 = y0 + static_cast<float>(m_glyphHeight) * scaleY;

	if (renderFlagBits.snapPosition != 0) {
		advance = static_cast<float>(floor(advance));
	}
	posX += advance;

	if (glyphInfo[0] == 0) {
		u0 += kFontOne;
	}
	if (m_glyphWidth == glyphInfo[0] + glyphInfo[1]) {
		u1 -= kFontOne;
	}

	v0 += kFontOne;
	v1 -= kFontOne;

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(x0, y0, posZ);
	GXTexCoord2u16(static_cast<unsigned short>(u0), static_cast<unsigned short>(v0));

	GXPosition3f32(x1, y0, posZ);
	GXTexCoord2u16(static_cast<unsigned short>(u1), static_cast<unsigned short>(v0));

	GXPosition3f32(x1, y1, posZ);
	GXTexCoord2u16(static_cast<unsigned short>(u1), static_cast<unsigned short>(v1));

	GXPosition3f32(x0, y1, posZ);
	GXTexCoord2u16(static_cast<unsigned short>(u0), static_cast<unsigned short>(v1));
}

/*
 * --INFO--
 * PAL Address: 0x8009255c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Draw(char* text)
{
	char* textPtr = text;
	unsigned short ch;
	int hasChar;

	goto read_char;

	while (hasChar != 0) {
		Draw(ch);

read_char:
		if (static_cast<unsigned char>(*textPtr) == 0) {
			hasChar = 0;
		} else {
			ch = static_cast<unsigned char>(*textPtr);
			hasChar = 1;
			textPtr++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800925d0
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::DrawQuit()
{
    Mtx44 screenMtx;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x8009260c
 * PAL Size: 768b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::DrawInit()
{
    Mtx texMtx;
    Mtx44 projMtx;
    Mtx identityMtx;

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    _GXColor localColor = m_color;
    GXSetChanMatColor(GX_COLOR0A0, localColor);
    GXSetChanAmbColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    CFontRenderFlagBits& renderFlagBits = GetRenderFlagBits(renderFlags);
    if (renderFlagBits.zCompare != 0 || renderFlagBits.zUpdate != 0) {
        C_MTXOrtho(projMtx, LoadFloat(kFontZero), LoadFloat(kFontOrthoHeight), LoadFloat(kFontZero),
            LoadFloat(kFontOrthoWidth), LoadFloat(kFontZero), LoadFloat(kFontOne));
        projMtx[2][2] = LoadFloat(kFontOne);
        projMtx[2][3] = LoadFloat(kFontZero);
    } else {
        C_MTXOrtho(projMtx, LoadFloat(kFontZero), LoadFloat(kFontOrthoHeight), LoadFloat(kFontZero),
            LoadFloat(kFontOrthoWidth), LoadFloat(kFontZero), LoadFloat(kFontOne));
    }
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetCurrentMtx(0);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    signed char zCompareFlag = renderFlagBits.zCompare;
    int zFunction = 7;
    int zUpdate = (zCompareFlag != 0) ? 1 : 0;
    signed char zUpdateFlag = renderFlagBits.zUpdate;
    if (zUpdateFlag != 0) {
        zFunction = 3;
    }
    signed char zEnable = (zCompareFlag != 0 || zUpdateFlag != 0) ? 1 : 0;
    GXSetZMode(zEnable, (GXCompare)zFunction, zUpdate);

    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetCullMode(GX_CULL_NONE);

    TextureMan.SetTexture(GX_TEXMAP0, texturePtr);

    float texWidth = static_cast<float>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x64));
    float texHeight = static_cast<float>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x68));
    PSMTXScale(texMtx, LoadFloat(kFontOne) / texWidth, LoadFloat(kFontOne) / texHeight, LoadFloat(kFontOne));
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);

    TextureMan.SetTextureTev(texturePtr);

    renderFlagBits.fixedWidth = 0;
    renderFlagBits.snapPosition = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8009290c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::FlushTlutColor()
{
	texturePtr->FlushExternalTlut(m_tlutData);
}

/*
 * --INFO--
 * PAL Address: 0x80092938
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetTlutColor(int tlutIndex, int colorIndex, _GXColor color)
{
	unsigned int format = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x60);
	int colorCount;

	if (format == 9) {
		colorCount = 0x100;
	} else if (format == 8) {
		colorCount = 0x10;
	} else {
		colorCount = 0;
	}

	texturePtr->SetExternalTlutColor(&m_tlutData[tlutIndex * 0x40], colorCount, colorIndex, color);
}

/*
 * --INFO--
 * PAL Address: 0x80092998
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetTlut(int index)
{
	unsigned char* tlut;
	if (index < 0) {
		tlut = 0;
	} else {
		tlut = &m_tlutData[index * 0x40];
	}
	texturePtr->SetExternalTlut(tlut, 1);
}

/*
 * --INFO--
 * PAL Address: 0x800929e0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetColor(_GXColor color)
{
	unsigned char red = color.r;
	m_color.r = red;
	unsigned char blue = color.b;
	unsigned char green = color.g;
	m_color.g = green;
	unsigned char alpha = color.a;
	m_color.b = blue;
	m_color.a = alpha;
	_GXColor localColor = m_color;
	GXSetChanMatColor(GX_COLOR0A0, localColor);
}

/*
 * --INFO--
 * PAL Address: 0x80092a30
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetShadow(int enabled)
{
	signed char shadow = static_cast<signed char>(enabled);
	GetRenderFlagBits(renderFlags).shadow = shadow;
}

/*
 * --INFO--
 * PAL Address: 0x80092a44
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetScaleY(float value)
{
	scaleY = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092a4c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetScaleX(float value)
{
	scaleX = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092a54
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetScale(float value)
{
	scaleY = value;
	scaleX = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092a60
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetMargin(float value)
{
	margin = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092a68
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetZMode(int compareEnable, int updateEnable)
{
	GetRenderFlagBits(renderFlags).zCompare = static_cast<signed char>(compareEnable);
	GetRenderFlagBits(renderFlags).zUpdate = static_cast<signed char>(updateEnable);
}

/*
 * --INFO--
 * PAL Address: 0x80092a8c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosZ(float z)
{
	posZ = z;
}

/*
 * --INFO--
 * PAL Address: 0x80092a94
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosY(float y)
{
	posY = y;
}

/*
 * --INFO--
 * PAL Address: 0x80092a9c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosX(float x)
{
	posX = x;
}

/*
 * --INFO--
 * PAL Address: 0x80092aa4
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Create(void* filePtr, CMemory::CStage* stage)
{
    CChunkFile::CChunk chunk;

    m_usesEmbeddedData = static_cast<unsigned char>((filePtr == 0) && (stage == 0));

    CChunkFile chunkFile(m_usesEmbeddedData != 0 ? g_tFont22 : filePtr);
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'FONT':
            chunkFile.PushChunk();
            const unsigned long infoChunkId = 'INFO';
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case infoChunkId:
                    m_glyphWidth = static_cast<unsigned short>(chunkFile.Get4());
                    m_glyphHeight = static_cast<unsigned short>(chunkFile.Get4());
                    m_glyphColumns = static_cast<unsigned short>(chunkFile.Get4());
                    break;
                case 'DATA':
                    if (m_usesEmbeddedData != 0) {
                        m_glyphData = chunkFile.GetAddress();
                    } else {
                        m_glyphData = new (stage, const_cast<char*>(s_fontman_cpp), 0xCF) unsigned char[chunk.m_size];
                        chunkFile.Get(m_glyphData, chunk.m_size);
                    }

                    CFont* font = this;
                    unsigned short* bucket = static_cast<unsigned short*>(m_glyphData);
                    for (int i = 0; i < 32; i++) {
                        font->m_glyphBuckets[0] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[1] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[2] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[3] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[4] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[5] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[6] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font->m_glyphBuckets[7] = bucket;
                        bucket = bucket + static_cast<unsigned int>(*bucket) * 4;
                        bucket++;
                        font = reinterpret_cast<CFont*>(&font->margin);
                    }
                    break;
                case 'TXTR':
                    texturePtr = new (FontMan.m_stage, const_cast<char*>(s_fontman_cpp), 0xDF) CTexture;
                    texturePtr->Create(chunkFile, stage, 0, 0, m_usesEmbeddedData != 0);
                    break;
                }
            }
            chunkFile.PopChunk();
            break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80092d2c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CFont::operator new(unsigned long size, CMemory::CStage* stage, char* file, int line)
{
	return Memory._Alloc(size, FontMan.m_stage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80092d74
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFont::~CFont()
{
	if (texturePtr != 0) {
		CTexture* texture = texturePtr;
		int* textureRef = reinterpret_cast<int*>(texture);
		int nextRefCount = textureRef[1] - 1;
		textureRef[1] = nextRefCount;
		if (nextRefCount == 0) {
			delete texture;
		}
		texturePtr = 0;
	}

	if (m_usesEmbeddedData == 0 && m_glyphData != 0) {
		delete[] static_cast<unsigned char*>(m_glyphData);
		m_glyphData = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80092e3c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFont::CFont()
{
	m_glyphData = 0;
	texturePtr = 0;
	margin = kFontZero;
	posZ = kFontZero;
	posY = kFontZero;
	posX = kFontZero;
	CFontRenderFlagBits& bits = GetRenderFlagBits(renderFlags);
	bits.shadow = 0;
	scaleY = kFontOne;
	scaleX = kFontOne;
	bits.snapPosition = 0;
	m_color.r = 0xFF;
	m_color.g = 0xFF;
	m_color.b = 0xFF;
	m_color.a = 0xFF;
	bits.zCompare = 0;
	bits.zUpdate = 0;
	m_usesEmbeddedData = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80092eec
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CFontMan::GetInternal22Size()
{
	return 0x10D40;
}

/*
 * --INFO--
 * PAL Address: 0x80092ef8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFontMan::Quit()
{
	CFont* font = m_font;
	if (font != 0) {
		int* ref = reinterpret_cast<int*>(font);
		int nextRefCount = ref[1] - 1;
		ref[1] = nextRefCount;
		if (nextRefCount == 0) {
			delete font;
		}
		m_font = 0;
	}

	Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * PAL Address: 0x80092f70
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFontMan::Init()
{
	m_font = 0;

	CMemory::CStage* stage = Memory.CreateStage(0x8000, const_cast<char*>("CFontMan"), 0);
	m_stage = stage;

	CFont* font = new (stage, const_cast<char*>(s_fontman_cpp), 0x3D) CFont;

	m_font = font;
	m_font->Create(0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80093098
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFontMan::~CFontMan()
{
}
