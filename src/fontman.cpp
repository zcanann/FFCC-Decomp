#include "ffcc/fontman.h"
#include "ffcc/chunkfile.h"
#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include <dolphin/mtx.h>
#include <math.h>

extern CFontMan FontMan;
extern CTextureMan TextureMan;
extern void* ARRAY_802ea170;
extern "C" unsigned char lbl_801FE080[];
extern "C" void __dt__8CFontManFv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* __vt__5CFont[];
extern unsigned char CameraPcs[];
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);

static const char s_fontman_cpp[] = "fontman.cpp";
static const char s_CFontMan[] = "CFontMan";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
	return reinterpret_cast<unsigned char*>(p) + offset;
}

typedef void (*VirtualDtorFn)(void*, int);
}

/*
 * --INFO--
 * PAL Address: 0x80092f14
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFontMan::CFontMan()
{
	m_stage = 0;
	m_font = 0;
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
	*reinterpret_cast<CFont**>(Ptr(this, 8)) = 0;

	CMemory::CStage* stage = Memory.CreateStage(0x8000, const_cast<char*>(s_CFontMan), 0);
	*reinterpret_cast<CMemory::CStage**>(Ptr(this, 4)) = stage;

	CFont* font = reinterpret_cast<CFont*>(
	    _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
	        &Memory,
	        sizeof(CFont),
	        *reinterpret_cast<CMemory::CStage**>(Ptr(&FontMan, 4)),
	        const_cast<char*>(s_fontman_cpp),
	        0x3D,
	        0));

	if (font != 0) {
		__ct__4CRefFv(font);
		*reinterpret_cast<void**>(font) = __vt__5CFont;
		font->texturePtr = 0;
		font->m_glyphData = 0;
		font->posX = 0.0f;
		font->posY = 0.0f;
		font->posZ = 0.0f;
		font->margin = 0.0f;
		font->scaleX = 1.0f;
		font->scaleY = 1.0f;
		font->renderFlags &= static_cast<unsigned char>(~0x80);
		font->renderFlags &= static_cast<unsigned char>(~0x08);
		font->m_color.r = 0xFF;
		font->m_color.g = 0xFF;
		font->m_color.b = 0xFF;
		font->m_color.a = 0xFF;
		font->renderFlags &= static_cast<unsigned char>(~0x40);
		font->renderFlags &= static_cast<unsigned char>(~0x20);
		font->m_usesEmbeddedData = 0;
		font->m_pad0f = 0;
	}

	*reinterpret_cast<CFont**>(Ptr(this, 8)) = font;
	reinterpret_cast<CFont*>(*reinterpret_cast<void**>(Ptr(this, 8)))->Create(0, 0);
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
	int* font = reinterpret_cast<int*>(m_font);
	if (font != 0) {
		int refCount = font[1];
		font[1] = refCount - 1;
		if ((refCount - 1 == 0) && (font != 0)) {
			(*(void (**)(int*, int))(*font + 8))(font, 1);
		}
		m_font = 0;
	}

	Memory.DestroyStage(m_stage);
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
 * PAL Address: 0x80092e3c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFont::CFont()
{
	texturePtr = 0;
	m_glyphData = 0;
	margin = 0.0f;
	posZ = 0.0f;
	posY = 0.0f;
	posX = 0.0f;
	renderFlags &= static_cast<unsigned char>(~0x80);
	scaleY = 1.0f;
	scaleX = 1.0f;
	renderFlags &= static_cast<unsigned char>(~0x08);
	m_color.r = 0xFF;
	m_color.g = 0xFF;
	m_color.b = 0xFF;
	m_color.a = 0xFF;
	renderFlags &= static_cast<unsigned char>(~0x40);
	renderFlags &= static_cast<unsigned char>(~0x20);
	m_usesEmbeddedData = 0;
	m_pad0f = 0;
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
		int* texture = reinterpret_cast<int*>(texturePtr);
		int refCount = texture[1];
		texture[1] = refCount - 1;
		if ((refCount - 1 == 0) && (texture != 0)) {
			(*(void (**)(int*, int))(*texture + 8))(texture, 1);
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
 * PAL Address: 0x80092aa4
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::Create(void* filePtr, CMemory::CStage* stage)
{
    CChunkFile chunkFile;
    CChunkFile::CChunk chunk;

    m_usesEmbeddedData = static_cast<unsigned char>((filePtr == 0) && (stage == 0));
    if (m_usesEmbeddedData != 0) {
        filePtr = lbl_801FE080;
    }

    chunkFile.SetBuf(filePtr);
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
                        bucket += static_cast<unsigned int>(*bucket) * 4 + 1;
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
 * PAL Address: 0x80092a68
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetZMode(int compareEnable, int updateEnable)
{
	renderFlags = (static_cast<unsigned char>(compareEnable) << 6 & 0x40) | (renderFlags & 0xBF);
	renderFlags = (static_cast<unsigned char>(updateEnable) << 5 & 0x20) | (renderFlags & 0xDF);
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
 * PAL Address: 0x80092a30
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFont::SetShadow(int enabled)
{
	renderFlags = (static_cast<unsigned char>(enabled) << 7) | (renderFlags & 0x7F);
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
	m_color = color;
	GXSetChanMatColor(GX_COLOR0A0, m_color);
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
	unsigned char* tlut = 0;
	if (index >= 0) {
		tlut = &m_tlutData[index * 0x40];
	}
	texturePtr->SetExternalTlut(tlut, 1);
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
	int format = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texturePtr) + 0x60);
	int colorCount = 0;

	if (format == 9) {
		colorCount = 0x100;
	} else if (format == 8) {
		colorCount = 0x10;
	}

	texturePtr->SetExternalTlutColor(&m_tlutData[tlutIndex * 0x40], colorCount, colorIndex, color);
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
    renderFlags &= static_cast<unsigned char>(~0x08);
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

    PSMTX44Copy((float(*)[4])(CameraPcs + 0x48), screenMtx);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
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
	unsigned char* cursor = reinterpret_cast<unsigned char*>(text);
	for (; *cursor != '\0'; cursor++) {
		Draw(static_cast<unsigned short>(*cursor));
	}
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
    unsigned short* glyphBucket = m_glyphBuckets[ch & 0xFF];
    unsigned short* glyph = glyphBucket + 1;
    unsigned int count = static_cast<unsigned int>(glyphBucket[0]);

    for (; count != 0; count--) {
        if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) == ((ch >> 8) & 0xFF)) {
            break;
        }
        glyph += 4;
    }

    if (count == 0) {
        unsigned short* fallback = m_glyphBuckets[63] + 1;
        unsigned int fallbackCount = static_cast<unsigned int>(m_glyphBuckets[63][0]);
        for (; fallbackCount != 0; fallbackCount--) {
            if (*reinterpret_cast<char*>(fallback + 1) == '\0') {
                glyph = fallback;
                break;
            }
            fallback += 4;
        }
        if (fallbackCount == 0) {
            return;
        }
    }

    unsigned char* glyphInfo = reinterpret_cast<unsigned char*>(glyph) + ((renderFlags & 0x80) ? 5 : 3);

    unsigned int texX;
    unsigned int texY;
    unsigned int drawWidth;
    unsigned int glyphIndex = static_cast<unsigned int>(*glyph);
    unsigned int row = glyphIndex / m_glyphColumns;

    if ((renderFlags & 0x10) != 0) {
        drawWidth = m_glyphWidth;
        texX = drawWidth * (glyphIndex - row * m_glyphColumns);
        texY = m_glyphHeight * row;
    } else {
        drawWidth = glyphInfo[1];
        texX = static_cast<unsigned int>(glyphInfo[0]) + m_glyphWidth * (glyphIndex - row * m_glyphColumns);
        texY = m_glyphHeight * row;
    }

    float x0 = posX;
    float y0 = posY;
    if ((renderFlags & 0x08) != 0) {
        x0 = floorf(x0);
        y0 = floorf(y0);
    }

    float advance = scaleX * (static_cast<float>(drawWidth) + margin);
    if ((renderFlags & 0x08) != 0) {
        advance = floorf(advance);
    }
    posX += advance;

    unsigned short u0 = static_cast<unsigned short>(texX * 2);
    if (glyphInfo[0] == 0) {
        u0 = static_cast<unsigned short>(u0 + 1);
    }

    unsigned short u1 = static_cast<unsigned short>((texX + drawWidth) * 2);
    if (m_glyphWidth == static_cast<unsigned short>(glyphInfo[0] + glyphInfo[1])) {
        u1 = static_cast<unsigned short>(u1 - 1);
    }

    unsigned short v0 = static_cast<unsigned short>(texY * 2 + 1);
    unsigned short v1 = static_cast<unsigned short>((texY + m_glyphHeight) * 2 - 1);

    float x1 = x0 + static_cast<float>(drawWidth) * scaleX;
    float y1 = y0 + static_cast<float>(m_glyphHeight) * scaleY;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, posZ);
    GXTexCoord2u16(u0, v0);

    GXPosition3f32(x1, y0, posZ);
    GXTexCoord2u16(u1, v0);

    GXPosition3f32(x1, y1, posZ);
    GXTexCoord2u16(u1, v1);

    GXPosition3f32(x0, y1, posZ);
    GXTexCoord2u16(u0, v1);
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
	unsigned char* cursor = reinterpret_cast<unsigned char*>(text);

	while (*cursor != '\0') {
		unsigned char ch = *cursor++;
		unsigned short* glyphBucket = m_glyphBuckets[ch];
		unsigned short* glyph = glyphBucket + 1;
		unsigned int count = static_cast<unsigned int>(glyphBucket[0]);

		for (; count != 0; count--) {
			if (*reinterpret_cast<char*>(glyph + 1) == '\0') {
				break;
			}
			glyph += 4;
		}

		if (count == 0) {
			unsigned short* fallback = m_glyphBuckets[63] + 1;
			unsigned int fallbackCount = static_cast<unsigned int>(m_glyphBuckets[63][0]);
			for (; fallbackCount != 0; fallbackCount--) {
				if (*reinterpret_cast<char*>(fallback + 1) == '\0') {
					glyph = fallback;
					break;
				}
				fallback += 4;
			}
			if (fallbackCount == 0) {
				continue;
			}
		}

		unsigned int drawWidth;
		if ((renderFlags & 0x10) != 0) {
			drawWidth = m_glyphWidth;
		} else {
			drawWidth = *(reinterpret_cast<unsigned char*>(glyph) + 4 +
			             ((static_cast<signed char>(renderFlags) >> 7) & 2));
		}

		float charWidth = scaleX * (margin + static_cast<float>(drawWidth));
		if ((renderFlags & 0x08) != 0) {
			charWidth = floorf(charWidth);
		}
		width += charWidth;
	}

	return width;
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
	unsigned int count = static_cast<unsigned int>(glyphBucket[0]);

	for (; count != 0; count--) {
		if (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(glyph + 1)) == ((ch >> 8) & 0xFF)) {
			break;
		}
		glyph += 4;
	}

	if (count == 0) {
		glyph = 0;
	}

	if (glyph == 0) {
		glyphBucket = m_glyphBuckets[63];
		glyph = glyphBucket + 1;
		for (count = static_cast<unsigned int>(glyphBucket[0]); count != 0; count--) {
			if (*reinterpret_cast<char*>(glyph + 1) == '\0') {
				break;
			}
			glyph += 4;
		}
		if (count == 0) {
			return 0.0f;
		}
	}

	unsigned char flags = renderFlags;
	unsigned int drawWidth;
	if (static_cast<int>((static_cast<unsigned int>(flags) << 27) | (static_cast<unsigned int>(flags) >> 5)) < 0) {
		drawWidth = static_cast<unsigned int>(m_glyphWidth);
	} else {
		signed char sign = static_cast<signed char>(flags) >> 7;
		unsigned int extra = static_cast<unsigned int>((-static_cast<int>(sign) | static_cast<int>(sign))) >> 30 & 2;
		drawWidth = static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(glyph) + extra + 4));
	}

	float width = scaleX * (margin + static_cast<float>(drawWidth));
	if (static_cast<int>((static_cast<unsigned int>(renderFlags) << 28) | (static_cast<unsigned int>(renderFlags) >> 4)) < 0) {
		width = static_cast<float>(floor(static_cast<double>(width)));
	}
	return width;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFont::searchChar(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFont::getNextChar(char **, unsigned short*)
{
	// TODO
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
	return ::operator new(size, stage, file, line);
}

/*
 * --INFO--
 * PAL Address: 0x800930e0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_fontman_cpp(void)
{
	__register_global_object(&FontMan, __dt__8CFontManFv, &ARRAY_802ea170);
}
