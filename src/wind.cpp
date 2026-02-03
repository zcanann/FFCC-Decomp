#include "ffcc/wind.h"

#include "ffcc/graphic.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/camera.h"

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
 * Address:	TODO
 * Size:	TODO
 */
void CWind::Frame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	800d9b2c
 * Size:	564
 */
void CWind::Draw()
{
	Mtx cameraMatrix;
	PSMTXCopy(&CameraPcs.m_cameraMatrix, &cameraMatrix);
	
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_LEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GXSetCullMode(GX_CULL_BACK);
	
	GXSetNumTevStages(1);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
	GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	
	if (CFlat._4764_4_ & 0x800000) {
		for (int i = 0; i < 32; i++) {
			WindObject* obj = &m_objects[i];
			if (obj->flags & 0x80) {
				CColor color;
				CVector position;
				
				if (obj->type == 1) {
					color = CColor(0xff, 0xff, 0x00, 0xff);
					position = CVector(obj->pos.x, 100.0f, obj->pos.z);
					Graphic.DrawSphere(&cameraMatrix, &position, obj->radius, &color);
				} else {
					int alpha = (int)(255.0f * (1.0f - obj->intensity));
					color = CColor(0xff, 0xff, 0x80, alpha);
					position = CVector(obj->pos.x, 100.0f, obj->pos.z);
					Graphic.DrawSphere(&cameraMatrix, &position, obj->radius, &color);
				}
			}
		}
	}
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
