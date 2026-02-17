#include "ffcc/fontman.h"
#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include <dolphin/mtx.h>

extern CFontMan FontMan;
extern void* ARRAY_802ea170;
extern "C" void __dt__8CFontManFv(void*);
extern unsigned char CameraPcs[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFontMan::CFontMan()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFontMan::~CFontMan()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFontMan::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFontMan::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFontMan::GetInternal22Size()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFont::CFont()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFont::~CFont()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFont::Create(void*, CMemory::CStage*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFont::DrawInit()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFont::Draw(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFont::GetWidth(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFont::GetWidth(unsigned short)
{
	// TODO
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
