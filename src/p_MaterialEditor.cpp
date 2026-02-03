#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>

extern CUSBPcs USBPcs;
extern class CCameraPcs {
public:
    Mtx m_cameraMatrix;
} CameraPcs;

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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::Init()
{
	// TODO
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
