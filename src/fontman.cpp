#include "ffcc/fontman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/p_camera.h"
extern "C" {
unsigned char g_tFont22[0x10D40] ATTRIBUTE_ALIGN(32) = {
#include "src/font_res_archive.inc"
};
}
#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include <dolphin/mtx.h>
#include <math.h>

extern "C" void __dt__8CFontManFv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void* __vt__5CFont[];

static const char s_fontman_cpp[] = "fontman.cpp";
static const char s_CFontMan[] = "CFontMan";

CFontMan FontMan;

namespace {
typedef void (*VirtualDtorFn)(void*, int);

struct CFontRenderFlagBits
{
	unsigned char shadow : 1;
	unsigned char zCompare : 1;
	unsigned char zUpdate : 1;
	unsigned char snapPosition : 1;
	unsigned char fixedWidth : 1;
	unsigned char pad : 3;
};

static CFontRenderFlagBits& GetRenderFlagBits(unsigned char& flags)
{
	return reinterpret_cast<CFontRenderFlagBits&>(flags);
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
	unsigned char flags = renderFlags;
	unsigned int drawWidth;

	if (static_cast<int>((static_cast<unsigned int>(flags) << 27) | static_cast<unsigned int>(flags >> 5)) < 0) {
		drawWidth = static_cast<unsigned int>(m_glyphWidth);
	} else {
		signed char sign = static_cast<signed char>(flags) >> 7;
		unsigned int extra =
		    static_cast<unsigned int>((-static_cast<int>(sign) | static_cast<int>(sign))) >> 30 & 2;
		drawWidth = static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(glyph) + extra + 4));
	}

	double width = static_cast<double>(scaleX * (margin + static_cast<float>(drawWidth)));
	if (static_cast<int>((static_cast<unsigned int>(flags) << 28) | static_cast<unsigned int>(flags >> 4)) < 0) {
		width = static_cast<double>(static_cast<float>(floor(width)));
	}

	return static_cast<float>(width);

find_fallback:
	glyphBucket = m_glyphBuckets[63];
	unsigned short* fallbackGlyph = glyphBucket + 1;
	for (count = static_cast<int>(*glyphBucket); count > 0; count--) {
		if (*reinterpret_cast<char*>(fallbackGlyph + 1) != '\0') {
			fallbackGlyph += 4;
		} else {
			break;
		}
	}
	if (count == 0) {
		fallbackGlyph = 0;
	}
	glyph = fallbackGlyph;
	if (glyph != 0) {
		goto found_fallback;
	}
	return 0.0f;
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
	float width = 0.0f;
	unsigned short ch;

	while (true) {
		ch = static_cast<unsigned char>(*text);
		if (ch == '\0') {
			break;
		}
		unsigned short* glyph = m_glyphBuckets[ch] + 1;
		int count = static_cast<int>(m_glyphBuckets[ch][0]);
		text++;

		for (; count > 0; count--) {
			if (*reinterpret_cast<char*>(glyph + 1) != '\0') {
				glyph += 4;
			} else {
				goto use_glyph;
			}
		}

		goto find_fallback;

use_glyph:
		unsigned char flags = renderFlags;
		unsigned int drawWidth;

		if (static_cast<int>((static_cast<unsigned int>(flags) << 27) | static_cast<unsigned int>(flags >> 5)) < 0) {
			drawWidth = static_cast<unsigned int>(m_glyphWidth);
		} else {
			signed char sign = static_cast<signed char>(flags);
			sign >>= 7;
			drawWidth = static_cast<unsigned int>(
			    *(reinterpret_cast<unsigned char*>(glyph) +
			      ((static_cast<unsigned int>(-static_cast<int>(sign) | static_cast<int>(sign)) >> 30 & 2) + 4)));
		}

		float charWidth = scaleX * (margin + static_cast<float>(drawWidth));
		if (static_cast<int>((static_cast<unsigned int>(flags) << 28) | static_cast<unsigned int>(flags >> 4)) < 0) {
			charWidth = static_cast<float>(floor(charWidth));
		}

		width += charWidth;
		continue;

find_fallback:
		unsigned short* glyphBucket = m_glyphBuckets[63];
		unsigned short* fallbackGlyph = glyphBucket + 1;
		for (count = static_cast<int>(*glyphBucket); count > 0; count--) {
			if (*reinterpret_cast<char*>(fallbackGlyph + 1) != '\0') {
				fallbackGlyph += 4;
			} else {
				break;
			}
		}
		if (count == 0) {
			fallbackGlyph = 0;
		}
		glyph = fallbackGlyph;
		if (glyph != 0) {
			goto use_glyph;
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
	unsigned int count = static_cast<unsigned int>(m_glyphBuckets[ch & 0xFF][0]);

	for (; count != 0; count--) {
		if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) == ((ch >> 8) & 0xFF)) {
			goto found_glyph;
		}
		glyph += 4;
	}
	glyph = 0;

found_glyph:
	if (glyph == 0) {
		unsigned short* glyphBucket = m_glyphBuckets[63];
		glyph = glyphBucket + 1;
		for (count = static_cast<unsigned int>(*glyphBucket); count != 0; count--) {
			if (*reinterpret_cast<unsigned char*>(glyph + 1) == '\0') {
				goto found_fallback;
			}
			glyph += 4;
		}
		glyph = 0;

found_fallback:
		if (glyph == 0) {
			return;
		}
	}

	unsigned char flags = renderFlags;
	signed char sign = static_cast<signed char>(flags) >> 7;
	unsigned char* glyphInfo = reinterpret_cast<unsigned char*>(glyph) +
	                           ((static_cast<unsigned int>(-static_cast<int>(sign) | static_cast<int>(sign)) >> 30 & 2) + 3);
	unsigned int drawWidth;
	unsigned int glyphIndex;
	unsigned int row;
	float u0;
	float v0;

	if (static_cast<int>((static_cast<unsigned int>(flags) << 27) | static_cast<unsigned int>(flags >> 5)) < 0) {
		drawWidth = static_cast<unsigned int>(m_glyphWidth);
		glyphIndex = static_cast<unsigned int>(*glyph);
		row = glyphIndex / m_glyphColumns;
		u0 = static_cast<float>(drawWidth * (glyphIndex - row * m_glyphColumns) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	} else {
		glyphIndex = static_cast<unsigned int>(*glyph);
		row = glyphIndex / m_glyphColumns;
		drawWidth = static_cast<unsigned int>(glyphInfo[1]);
		u0 = static_cast<float>((static_cast<unsigned int>(glyphInfo[0]) + m_glyphWidth * (glyphIndex - row * m_glyphColumns)) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	}

	float x0 = posX;
	float y0 = posY;
	if (static_cast<int>((static_cast<unsigned int>(flags) << 28) | static_cast<unsigned int>(flags >> 4)) < 0) {
		x0 = static_cast<float>(floor(x0));
		y0 = static_cast<float>(floor(y0));
	}

	float advance = scaleX * (margin + static_cast<float>(drawWidth));
	float x1 = x0 + static_cast<float>(drawWidth) * scaleX;
	float y1 = y0 + static_cast<float>(m_glyphHeight) * scaleY;
	float u1 = u0 + static_cast<float>(drawWidth * 2);
	float v1 = v0 + static_cast<float>(m_glyphHeight * 2);

	if (static_cast<int>((static_cast<unsigned int>(flags) << 28) | static_cast<unsigned int>(flags >> 4)) < 0) {
		advance = static_cast<float>(floor(advance));
	}
	posX += advance;

	if (glyphInfo[0] == 0) {
		u0 += 1.0f;
	}
	if (m_glyphWidth == static_cast<unsigned short>(glyphInfo[0] + glyphInfo[1])) {
		u1 -= 1.0f;
	}

	v0 += 1.0f;
	v1 -= 1.0f;

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
	unsigned char ch;
	do {
		ch = static_cast<unsigned char>(*text);
		if (ch != '\0') {
			Draw(static_cast<unsigned short>(ch));
			text++;
		}
	} while (ch != '\0');
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

    PSMTX44Copy(reinterpret_cast<Mtx44Ptr>(reinterpret_cast<u8*>(&CameraPcs) + 0x94), screenMtx);
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
    Mtx identityMtx;
    Mtx44 projMtx;
    Mtx texMtx;
    _GXColor white = { 0xFF, 0xFF, 0xFF, 0xFF };

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, m_color);
    GXSetChanAmbColor(GX_COLOR0A0, white);

    C_MTXOrtho(projMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    if ((renderFlags & 0x80) != 0 || (renderFlags & 0x40) != 0) {
        projMtx[2][2] = 1.0f;
        projMtx[2][3] = 0.0f;
    }
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetCurrentMtx(0);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);

    int zFunction = 7;
    if ((renderFlags & 0x40) != 0) {
        zFunction = 3;
    }
    int zEnable = ((renderFlags & 0x80) != 0 || (renderFlags & 0x40) != 0) ? 1 : 0;
    int zUpdate = ((renderFlags & 0x40) != 0) ? 1 : 0;
    GXSetZMode(zEnable, (GXCompare)zFunction, zUpdate);

    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetCullMode(GX_CULL_NONE);

    TextureMan.SetTexture(GX_TEXMAP0, texturePtr);

    float texWidth = static_cast<float>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x64));
    float texHeight = static_cast<float>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x68));
    PSMTXScale(texMtx, 1.0f / texWidth, 1.0f / texHeight, 1.0f);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 1);

    TextureMan.SetTextureTev(texturePtr);

    renderFlags &= static_cast<unsigned char>(~0x10);
    renderFlags &= 0xF7;
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
	unsigned char green = color.g;
	m_color.r = color.r;
	unsigned char blue = color.b;
	m_color.g = green;
	green = color.a;
	m_color.b = blue;
	m_color.a = green;
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
	signed char compare = static_cast<signed char>(compareEnable);
	signed char update = static_cast<signed char>(updateEnable);
	CFontRenderFlagBits& bits = GetRenderFlagBits(renderFlags);
	bits.zCompare = compare;
	bits.zUpdate = update;
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
    if (m_usesEmbeddedData != 0) {
        filePtr = g_tFont22;
    }

    CChunkFile chunkFile(filePtr);
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id == 0x464F4E54) {
            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 0x494E464F) {
                    m_glyphWidth = static_cast<unsigned short>(chunkFile.Get4());
                    m_glyphHeight = static_cast<unsigned short>(chunkFile.Get4());
                    m_glyphColumns = static_cast<unsigned short>(chunkFile.Get4());
                } else if (chunk.m_id == 0x44415441) {
                    if (m_usesEmbeddedData == 0) {
                        m_glyphData = ::operator new(chunk.m_size, stage, const_cast<char*>(s_fontman_cpp), 0xCF);
                        chunkFile.Get(m_glyphData, chunk.m_size);
                    } else {
                        m_glyphData = chunkFile.GetAddress();
                    }

                    unsigned short* bucket = static_cast<unsigned short*>(m_glyphData);
                    for (int i = 0; i < 64; i++) {
                        m_glyphBuckets[i] = bucket;
                        bucket = reinterpret_cast<unsigned short*>(
                            reinterpret_cast<unsigned char*>(bucket) + static_cast<unsigned int>(*bucket) * 8 + 2);
                    }
                } else if (chunk.m_id == 0x54585452) {
                    texturePtr = new (FontMan.m_stage, const_cast<char*>(s_fontman_cpp), 0xDF) CTexture;
                    texturePtr->Create(chunkFile, stage, 0, 0, m_usesEmbeddedData != 0);
                }
            }
            chunkFile.PopChunk();
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
	return _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, size, FontMan.m_stage, file, line, 0);
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
		::operator delete[](m_glyphData);
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
	margin = 0.0f;
	posZ = 0.0f;
	posY = 0.0f;
	posX = 0.0f;
	renderFlags &= 0x7F;
	scaleY = 1.0f;
	scaleX = 1.0f;
	renderFlags &= 0xF7;
	m_color.r = 0xFF;
	m_color.g = 0xFF;
	m_color.b = 0xFF;
	m_color.a = 0xFF;
	renderFlags &= 0xBF;
	renderFlags &= 0xDF;
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

	CMemory::CStage* stage = Memory.CreateStage(0x8000, const_cast<char*>(s_CFontMan), 0);
	m_stage = stage;

	CFont* font = reinterpret_cast<CFont*>(
	    _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
	        &Memory,
	        sizeof(CFont),
	        FontMan.m_stage,
	        const_cast<char*>(s_fontman_cpp),
	        0x3D,
	        0));

	if (font != 0) {
		__ct__4CRefFv(font);
		*reinterpret_cast<void**>(font) = __vt__5CFont;
		font->m_glyphData = 0;
		font->texturePtr = 0;
		font->margin = 0.0f;
		font->posZ = 0.0f;
		font->posY = 0.0f;
		font->posX = 0.0f;
		font->renderFlags &= 0x7F;
		font->scaleY = 1.0f;
		font->scaleX = 1.0f;
		font->renderFlags &= 0xF7;
		font->m_color.r = 0xFF;
		font->m_color.g = 0xFF;
		font->m_color.b = 0xFF;
		font->m_color.a = 0xFF;
		font->renderFlags &= 0xBF;
		font->renderFlags &= 0xDF;
		font->m_usesEmbeddedData = 0;
	}

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
