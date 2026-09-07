#include "ffcc/fontman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/color.h"
#include "ffcc/gxfunc.h"
#include "global.h"
#include "ffcc/p_camera.h"
extern "C" {
unsigned char g_tFont22[0x10D40] = {
#include "src/font_res_archive.inc"
};
}
#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/math.h"
#include <dolphin/mtx.h>

static const char s_fontman_cpp[] = "fontman.cpp";

CFontMan FontMan;

struct CFontGlyphEntry
{
	u16 m_textureIndex;
	u8 m_codeHigh;
	struct Metrics {
		u8 m_left;
		u8 m_width;
	};
	Metrics m_metrics[2];
	u8 m_pad;
};

STATIC_ASSERT(sizeof(CFontGlyphEntry) == 8);
STATIC_ASSERT(sizeof(CFontGlyphEntry::Metrics) == 2);
STATIC_ASSERT(offsetof(CFontGlyphEntry, m_metrics) == 3);

namespace {
static inline CFontGlyphEntry* FirstGlyph(unsigned short* bucket)
{
	return reinterpret_cast<CFontGlyphEntry*>(bucket + 1);
}

static inline float FloorF(float value)
{
	return static_cast<float>(floor(value));
}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: 0x800A5C14
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CFont::getNextChar(char** text, unsigned short* ch)
{
	if (static_cast<unsigned char>(**text) == 0) {
		return 0;
	}
	*ch = static_cast<unsigned char>(**text);
	(*text)++;
	return 1;
}

inline CFontGlyphEntry* CFont::searchChar(unsigned short ch)
{
	unsigned short* glyphBucket = m_glyphBuckets[ch & 0xFF];
	CFontGlyphEntry* glyph = FirstGlyph(glyphBucket);
	int count = static_cast<int>(*glyphBucket);
	unsigned int code = (ch >> 8) & 0xFF;

	for (int i = 0; i < count; i++) {
		if (static_cast<unsigned int>(glyph->m_codeHigh) == code) {
			return glyph;
		}
		glyph++;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80093098
 * PAL Size: 72b
 * EN Address: 0x800A49A8
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
CFontMan::~CFontMan()
{
}

/*
 * --INFO--
 * PAL Address: 0x80092F70
 * PAL Size: 296b
 * EN Address: 0x800A4A00
 * EN Size: 84b
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
 * PAL Address: 0x80092EF8
 * PAL Size: 120b
 * EN Address: 0x800A4A54
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFontMan::Quit()
{
	CFont* font = m_font;
	if (font != 0) {
		if (font->DecRef() == 0) {
			delete font;
		}
		m_font = 0;
	}

	Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * PAL Address: 0x80092EEC
 * PAL Size: 12b
 * EN Address: 0x800A4AA8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CFontMan::GetInternal22Size()
{
	return 0x10D40;
}

/*
 * --INFO--
 * PAL Address: 0x80092E3C
 * PAL Size: 176b
 * EN Address: 0x800A4AB0
 * EN Size: 224b
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
	CFontRenderFlagBits& bits = renderFlags;
	bits.shadow = 0;
	scaleY = 1.0f;
	scaleX = 1.0f;
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
 * PAL Address: 0x80092D74
 * PAL Size: 200b
 * EN Address: 0x800A4B90
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
CFont::~CFont()
{
	if (texturePtr != 0) {
		CTexture* texture = texturePtr;
		if (texture->DecRef() == 0) {
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
 * PAL Address: 0x80092D2C
 * PAL Size: 72b
 * EN Address: 0x800A4C38
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CFont::operator new(unsigned long size, CMemory::CStage* stage, char* file, int line)
{
	return Memory._Alloc(size, FontMan.m_stage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80092AA4
 * PAL Size: 648b
 * EN Address: 0x800A4C88
 * EN Size: 544b
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

                    unsigned short* bucket = static_cast<unsigned short*>(m_glyphData);
                    for (int i = 0; i < 256; i++) {
                        m_glyphBuckets[i] = bucket;
                        bucket += *bucket * (sizeof(CFontGlyphEntry) / sizeof(unsigned short));
                        bucket++;
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
 * PAL Address: 0x80092A9C
 * PAL Size: 8b
 * EN Address: 0x800A4EA8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosX(float x)
{
	posX = x;
}

/*
 * --INFO--
 * PAL Address: 0x80092A94
 * PAL Size: 8b
 * EN Address: 0x800A4EB0
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosY(float y)
{
	posY = y;
}

/*
 * --INFO--
 * PAL Address: 0x80092A8C
 * PAL Size: 8b
 * EN Address: 0x800A4EB8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetPosZ(float z)
{
	posZ = z;
}

/*
 * --INFO--
 * PAL Address: 0x80092A68
 * PAL Size: 36b
 * EN Address: 0x800A4EC0
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetZMode(int compareEnable, int updateEnable)
{
	renderFlags.zCompare = static_cast<signed char>(compareEnable);
	renderFlags.zUpdate = static_cast<signed char>(updateEnable);
}

/*
 * --INFO--
 * PAL Address: 0x80092A60
 * PAL Size: 8b
 * EN Address: 0x800A4EE4
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetMargin(float value)
{
	margin = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092A54
 * PAL Size: 12b
 * EN Address: 0x800A4EEC
 * EN Size: 12b
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
 * PAL Address: 0x80092A4C
 * PAL Size: 8b
 * EN Address: 0x800A4EF8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetScaleX(float value)
{
	scaleX = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092A44
 * PAL Size: 8b
 * EN Address: 0x800A4F00
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetScaleY(float value)
{
	scaleY = value;
}

/*
 * --INFO--
 * PAL Address: 0x80092A30
 * PAL Size: 20b
 * EN Address: 0x800A4F08
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetShadow(int enabled)
{
	signed char shadow = static_cast<signed char>(enabled);
	renderFlags.shadow = shadow;
}

/*
 * --INFO--
 * PAL Address: 0x800929E0
 * PAL Size: 80b
 * EN Address: 0x800A4F1C
 * EN Size: 112b
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
 * PAL Address: 0x80092998
 * PAL Size: 72b
 * EN Address: 0x800A4F8C
 * EN Size: 104b
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
 * PAL Address: 0x80092938
 * PAL Size: 96b
 * EN Address: 0x800A4FF4
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetTlutColor(int tlutIndex, int colorIndex, _GXColor color)
{
	unsigned int format = texturePtr->m_format;
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
 * PAL Address: 0x8009290C
 * PAL Size: 44b
 * EN Address: 0x800A5048
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::FlushTlutColor()
{
	texturePtr->FlushExternalTlut(m_tlutData);
}

/*
 * --INFO--
 * PAL Address: 0x8009260C
 * PAL Size: 768b
 * EN Address: 0x800A507C
 * EN Size: 932b
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

    CFontRenderFlagBits& renderFlagBits = renderFlags;
    if (renderFlagBits.zCompare != 0 || renderFlagBits.zUpdate != 0) {
        C_MTXOrtho(projMtx, 0.0f, 448.0f, 0.0f,
            640.0f, 0.0f, 1.0f);
        projMtx[2][2] = 1.0f;
        projMtx[2][3] = 0.0f;
    } else {
        C_MTXOrtho(projMtx, 0.0f, 448.0f, 0.0f,
            640.0f, 0.0f, 1.0f);
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

    float texWidth = static_cast<float>(texturePtr->m_width);
    float texHeight = static_cast<float>(texturePtr->m_height);
    PSMTXScale(texMtx, 1.0f / texWidth, 1.0f / texHeight, 1.0f);
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
 * PAL Address: 0x800925D0
 * PAL Size: 60b
 * EN Address: 0x800A5420
 * EN Size: 56b
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
 * PAL Address: 0x8009255C
 * PAL Size: 116b
 * EN Address: 0x800A5458
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Draw(char* text)
{
	char* textPtr = text;
	unsigned short ch;
	while (getNextChar(&textPtr, &ch)) {
		Draw(ch);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8009211C
 * PAL Size: 1088b
 * EN Address: 0x800A54B4
 * EN Size: 1172b
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Draw(unsigned short ch)
{
	CFontGlyphEntry* drawGlyph = searchChar(ch);
	if (drawGlyph == 0) {
		drawGlyph = searchChar('?');
		if (drawGlyph == 0) {
			return;
		}
	}

	CFontRenderFlagBits& renderFlagBits = renderFlags;
	int drawWidth;
	CFontGlyphEntry::Metrics* glyphInfo = &drawGlyph->m_metrics[renderFlagBits.shadow != 0];
	int row;
	int glyphIndex;
	float u0;
	float v0;

	if (renderFlagBits.fixedWidth == 0) {
		glyphIndex = static_cast<int>(drawGlyph->m_textureIndex);
		row = glyphIndex / m_glyphColumns;
		drawWidth = static_cast<int>(glyphInfo->m_width);
		u0 = static_cast<float>((static_cast<int>(glyphInfo->m_left) + m_glyphWidth * (glyphIndex - m_glyphColumns * row)) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	} else {
		drawWidth = static_cast<int>(m_glyphWidth);
		glyphIndex = static_cast<int>(drawGlyph->m_textureIndex);
		row = glyphIndex / m_glyphColumns;
		u0 = static_cast<float>(m_glyphWidth * (glyphIndex - m_glyphColumns * row) * 2);
		v0 = static_cast<float>(m_glyphHeight * row * 2);
	}

	float x0 = posX;
	float y0 = posY;
	if (renderFlagBits.snapPosition != 0) {
		x0 = FloorF(x0);
		y0 = FloorF(y0);
	}

	float u1 = u0 + static_cast<float>(drawWidth * 2);
	float v1 = v0 + static_cast<float>(m_glyphHeight * 2);
	float x1 = x0 + static_cast<float>(drawWidth) * scaleX;
	float y1 = y0 + static_cast<float>(m_glyphHeight) * scaleY;
	float advance = scaleX * (static_cast<float>(drawWidth) + margin);

	if (renderFlagBits.snapPosition != 0) {
		advance = FloorF(advance);
	}
	posX += advance;

	if (glyphInfo->m_left == 0) {
		u0 += 1.0f;
	}
	if (m_glyphWidth == glyphInfo->m_left + glyphInfo->m_width) {
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
 * PAL Address: 0x80091F88
 * PAL Size: 404b
 * EN Address: 0x800A59E8
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
float CFont::GetWidth(char* text)
{
	char* textPtr = text;
	float width = 0.0f;
	unsigned short ch;
	while (getNextChar(&textPtr, &ch)) {
		width += GetWidth(ch);
	}
	return width;
}

/*
 * --INFO--
 * PAL Address: 0x80091E58
 * PAL Size: 304b
 * EN Address: 0x800A5A60
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
float CFont::GetWidth(unsigned short ch)
{
	CFontGlyphEntry* glyph = searchChar(ch);

	if (glyph == 0) {
		goto find_fallback;
	}

found_fallback:
	int drawWidth;
	float localMargin;
	float localScaleX;
	localScaleX = scaleX;
	localMargin = margin;
	CFontRenderFlagBits& renderFlagBits = renderFlags;

	if (renderFlagBits.fixedWidth != 0) {
		drawWidth = static_cast<int>(m_glyphWidth);
	} else {
		drawWidth = glyph->m_metrics[renderFlagBits.shadow != 0].m_width;
	}

	float width = localScaleX * (localMargin + static_cast<float>(drawWidth));
	if (renderFlagBits.snapPosition != 0) {
		width = static_cast<float>(floor(width));
	}

	return width;

find_fallback:
	glyph = searchChar('?');
	if (glyph != 0) {
		goto found_fallback;
	}
	return 0.0f;
}
