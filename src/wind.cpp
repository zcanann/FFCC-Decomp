#include "ffcc/wind.h"

#include <string.h>
#include <math.h>
#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/p_camera.h"
#include "ffcc/math.h"

extern CGraphic Graphic;
extern CCameraPcs CameraPcs;
extern u32 CFlat; // Temporary - needs proper declaration

/*
 * --INFO--
 * Address:	800da05c
 * Size:	88
 */
void CWind::ClearAll()
{
	memset(this, 0, 0xc80);
	*(u32*)((char*)this + 0xc80) = 1;
	memset((char*)this + 0xc84, 0, 0x7000);
	*(u32*)((char*)this + 0x7c84) = 10000000;
}

/*
 * --INFO--
 * Address:	800d9d60
 * Size:	764
 */
void CWind::Frame()
{
	// Basic loop structure to get started
	for (int i = 0; i < 32; i++) {
		WindObject* obj = &m_objects[i];
		if (obj->flags & 0x80) {
			// Wind object processing - TODO: implement full logic
		}
	}
}

/*
 * --INFO--
 * Address:	800d9b2c
 * Size:	564
 */
void CWind::Draw()
{
	// TODO: Implement wind rendering
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::Calc(Vec*, const Vec*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::searchFreeObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::getObj(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddAmbient(float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddDiffuse(const Vec*, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::AddSphere(const Vec*, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CWind::ChangePower(int, float)
{
	// TODO
}
