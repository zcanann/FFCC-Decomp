#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>

extern "C" int __cntlzw(unsigned int);

extern CUSBPcs USBPcs;
extern class CCameraPcs {
public:
    Mtx m_cameraMatrix;
} CameraPcs;

static void WriteU8(void* base, unsigned int offset, unsigned char value) {
    reinterpret_cast<unsigned char*>(base)[offset] = value;
}

static void WriteU32(void* base, unsigned int offset, unsigned int value) {
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

static void WriteF32(void* base, unsigned int offset, float value) {
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialEditorPcs::CMaterialEditorPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialEditorPcs::~CMaterialEditorPcs()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004c3c4
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::Init()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    const float kZero = 0.0f;
    const float kOne = 1.0f;
    const float kNegOne = -1.0f;

    const unsigned int clz0 = static_cast<unsigned int>(__cntlzw(0));
    const unsigned int clz1 = static_cast<unsigned int>(__cntlzw(1));
    const unsigned int clz2 = static_cast<unsigned int>(__cntlzw(2));

    WriteU8(self, 0x8, 0x7f);
    WriteU8(self, 0x9, 0x7f);
    WriteU8(self, 0xA, 0x7f);
    WriteU8(self, 0xB, 0xff);

    unsigned char level = static_cast<unsigned char>(-static_cast<int>((clz0 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0xC, level);
    WriteU8(self, 0xD, level);
    WriteU8(self, 0xE, level);
    WriteU8(self, 0xF, 0xff);

    WriteF32(self, 0x18, kZero);
    WriteF32(self, 0x1C, kZero);
    WriteF32(self, 0x20, kNegOne);

    level = static_cast<unsigned char>(-static_cast<int>((clz1 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0x10, level);
    WriteU8(self, 0x11, level);
    WriteU8(self, 0x12, level);
    WriteU8(self, 0x13, 0xff);

    WriteF32(self, 0x24, kZero);
    WriteF32(self, 0x28, kZero);
    WriteF32(self, 0x2C, kNegOne);

    level = static_cast<unsigned char>(-static_cast<int>((clz2 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0x14, level);
    WriteU8(self, 0x15, level);
    WriteU8(self, 0x16, level);
    WriteU8(self, 0x17, 0xff);

    WriteF32(self, 0x30, kZero);
    WriteF32(self, 0x34, kZero);
    WriteF32(self, 0x38, kNegOne);
    WriteF32(self, 0x3C, kZero);
    WriteF32(self, 0x40, kZero);
    WriteF32(self, 0x44, kZero);
    WriteF32(self, 0x48, kZero);
    WriteF32(self, 0x4C, kZero);
    WriteF32(self, 0x50, kZero);
    WriteF32(self, 0x54, kOne);
    WriteF32(self, 0x58, kOne);
    WriteF32(self, 0x5C, kOne);

    WriteU32(self, 0xBC, 0);

    int remaining = 2;
    CMaterialEditorPcs* cursor = this;
    do {
        unsigned char* block = reinterpret_cast<unsigned char*>(cursor);

        *reinterpret_cast<unsigned int*>(block + 0x2BC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2FC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x23C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x33C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x37C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x27C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C0) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x300) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x240) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x340) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x380) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x280) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C4) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x304) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x244) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x344) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x384) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x284) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C8) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x308) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x248) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x348) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x388) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x288) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2CC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x30C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x24C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x34C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x38C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x28C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D0) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x310) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x250) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x350) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x390) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x290) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D4) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x314) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x254) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x354) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x394) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x294) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D8) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x318) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x258) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x358) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x398) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x298) = 0;

        cursor = reinterpret_cast<CMaterialEditorPcs*>(block + 0x20);
        remaining -= 1;
    } while (remaining != 0);

    WriteU32(self, 0x3BC, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::createViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::destroyViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::ClearTextureData()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004bec8
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::calcViewer()
{
	USBPcs.mccReadData();
	
	if (m_usbStream.IsUSBStreamDataDone()) {
		SetUSBData();
		m_usbStream.SetUSBStreamDataDone();
	}
	
	// Set up scaling and translation vectors
	float scaleX = 4.0f;
	float scaleY = 4.0f; 
	float scaleZ = 4.0f;
	float transX = 1.0f;
	float transY = 1.0f;
	float transZ = 1.0f;
	
	// Set viewer position
	float posX = field268_0x15c.x;
	float posY = field268_0x15c.y;
	float posZ = -field268_0x15c.z;
	
	// Call SetViewerSRT with SRT structure
	struct SRT {
		float x, y, z;
	} srtPos = { posX, posY, posZ };
	// CameraPcs.SetViewerSRT(&srtPos);
	
	Mtx cameraMatrix;
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMatrix);
	
	// Copy matrix data from fields to m_unkMatrix
	m_unkMatrix.value[0][0] = *(float*)&field_0x12c;
	m_unkMatrix.value[0][1] = *(float*)&field_0x130;
	m_unkMatrix.value[0][2] = *(float*)&field_0x134;
	m_unkMatrix.value[0][3] = *(float*)&field_0x138;
	m_unkMatrix.value[1][0] = *(float*)&field_0x13c;
	m_unkMatrix.value[1][1] = *(float*)&field_0x140;
	m_unkMatrix.value[1][2] = *(float*)&field_0x144;
	m_unkMatrix.value[1][3] = *(float*)&field_0x148;
	m_unkMatrix.value[2][0] = *(float*)&field_0x14c;
	m_unkMatrix.value[2][1] = *(float*)&field_0x150;
	m_unkMatrix.value[2][2] = *(float*)&field_0x154;
	m_unkMatrix.value[2][3] = *(float*)&field_0x158;
	
	PSMTXTranspose(m_unkMatrix.value, m_unkMatrix.value);
	
	// Negate specific matrix elements
	m_unkMatrix.value[0][1] = -m_unkMatrix.value[0][1];
	m_unkMatrix.value[1][1] = -m_unkMatrix.value[1][1]; 
	m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
	m_unkMatrix.value[2][0] = -m_unkMatrix.value[2][0];
	m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
	m_unkMatrix.value[2][2] = -m_unkMatrix.value[2][2];
	
	// Apply scaling transformations
	Mtx scaleMatrix;
	PSMTXIdentity(scaleMatrix);
	scaleMatrix[1][1] = -1.0f;
	PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);
	
	PSMTXIdentity(scaleMatrix);
	scaleMatrix[2][2] = -1.0f;
	PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);
	
	PSMTXConcat(cameraMatrix, m_unkMatrix.value, cameraMatrix);
	GXLoadPosMtxImm(cameraMatrix, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::drawViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::CreateBoundaryBox(Vec&, Vec&, long, const Vec*)
{
	// TODO
}
