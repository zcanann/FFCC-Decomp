#include "ffcc/mapshadow.h"

/*
 * --INFO--
 * Address:	8004C71C
 * Size:	0xEC
 */
void CMapShadowInsertOctTree(CMapShadow::TARGET target, COctTree& octree)
{
	// TODO: Implement shadow insertion into octree
}

/*
 * --INFO--
 * Address:	8004C91C
 * Size:	0xEC
 */
void CMapShadow::Init()
{
	// Initialize shadow parameters and projection matrix
	if (field_0x6 != 0) {
		C_MTXLightFrustum(field_0x48, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, field_0xa8, 1.0f, 0.0f, 0.0f);
	} else {
		C_MTXLightOrtho(field_0x48, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, field_0xa8, 1.0f, 0.0f);
	}
}

/*
 * --INFO--
 * Address:	8004C8C8
 * Size:	0x54
 */
void CMapShadow::Calc()
{
	field_0x54 += field_0xb8;
	if (field_0x54 > 360.0f) {
		field_0x54 -= 360.0f;
	}
	
	field_0x64 += field_0xbc;
	if (field_0x64 > 360.0f) {
		field_0x64 -= 360.0f;
	}
}

/*
 * --INFO--
 * Address:	8004C808
 * Size:	0xC0
 */
void CMapShadow::Draw()
{
	Vec pos1, pos2, up;
	
	// Build view matrix for shadow rendering
	PSVECSubtract(&pos2, &pos1, &up);
	C_MTXLookAt(field_0x18, &pos1, &up, &pos1);
	PSMTXConcat(field_0x48, field_0x18, field_0x78);
}
