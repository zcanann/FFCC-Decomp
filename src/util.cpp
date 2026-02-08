#include "ffcc/util.h"

// Vec2d definition 
struct Vec2d {
	float x, y;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CUtil::CUtil()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetVtxFmt_POS_CLR()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetVtxFmt_POS_CLR_TEX()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetVtxFmt_POS_TEX0_TEX1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetVtxFmt_POS_CLR_TEX0_TEX1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetOrthoEnv()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::GetNoise(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::GetSplinePos(Vec&, Vec&, Vec&, Vec&, Vec&, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::ConvI2FVector(Vec&, S16Vec&, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::ConvF2IVector(S16Vec&, Vec&, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::ConvF2IVector2d(S16Vec2d&, Vec2d&, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::RenderQuadNoTex(Vec, Vec, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80024608
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderQuad(Vec pos1, Vec pos2, _GXColor color, Vec2d* uv1, Vec2d* uv2)
{
	float u1, v1, u2, v2;
	
	// Default UV coordinates if null
	extern float lbl_8032f888;  // 0.0f
	extern float lbl_8032f88c;  // 1.0f
	
	if (uv1 == NULL || uv2 == NULL) {
		u1 = lbl_8032f888;  // 0.0f
		v1 = lbl_8032f888;  // 0.0f  
		u2 = lbl_8032f88c;  // 1.0f
		v2 = lbl_8032f88c;  // 1.0f
	} else {
		u1 = uv1->x;
		v1 = uv1->y;
		u2 = uv2->x;
		v2 = uv2->y;
	}
	
	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	
	// Vertex 1: pos1.x, pos1.y, pos1.z, color, u1, v1
	GXPosition3f32(pos1.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u1, v1);
	
	// Vertex 2: pos2.x, pos1.y, pos1.z, color, u2, v1  
	GXPosition3f32(pos2.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u2, v1);
	
	// Vertex 3: pos2.x, pos2.y, pos1.z, color, u2, v2
	GXPosition3f32(pos2.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u2, v2);
	
	// Vertex 4: pos1.x, pos2.y, pos1.z, color, u1, v2
	GXPosition3f32(pos1.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u1, v2);
}

/*
 * --INFO--
 * PAL Address: 0x800244a8
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderQuadTex2(Vec pos1, Vec pos2, _GXColor color, Vec2d* uv1, Vec2d* uv2)
{
	float u1, v1, u2, v2;
	
	// Default UV coordinates if null
	extern float lbl_8032f888;  // 0.0f
	extern float lbl_8032f88c;  // 1.0f
	
	if (uv1 == NULL || uv2 == NULL) {
		u1 = lbl_8032f888;  // 0.0f
		v1 = lbl_8032f888;  // 0.0f
		u2 = lbl_8032f88c;  // 1.0f
		v2 = lbl_8032f88c;  // 1.0f
	} else {
		u1 = uv1->x;
		v1 = uv1->y;
		u2 = uv2->x;
		v2 = uv2->y;
	}
	
	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	
	// Vertex 1: pos1.x, pos1.y, pos1.z, color, u1,v1, u1,v1
	GXPosition3f32(pos1.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u1, v1);  // TEX0
	GXTexCoord2f32(u1, v1);  // TEX1
	
	// Vertex 2: pos2.x, pos1.y, pos1.z, color, u2,v1, u2,v1
	GXPosition3f32(pos2.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u2, v1);  // TEX0
	GXTexCoord2f32(u2, v1);  // TEX1
	
	// Vertex 3: pos2.x, pos2.y, pos1.z, color, u2,v2, u2,v2
	GXPosition3f32(pos2.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u2, v2);  // TEX0
	GXTexCoord2f32(u2, v2);  // TEX1
	
	// Vertex 4: pos1.x, pos2.y, pos1.z, color, u1,v2, u1,v2
	GXPosition3f32(pos1.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(u1, v2);  // TEX0
	GXTexCoord2f32(u1, v2);  // TEX1
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::DisableIndMtx()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::BeginQuadEnv()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::EndQuadEnv()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::ClearZBufferRect(float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::RenderColorQuad(float, float, float, float, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::RenderTextureQuad(float, float, float, float, _GXTexObj*, Vec2d*, Vec2d*, _GXColor*, _GXBlendFactor, _GXBlendFactor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::RenderTextureQuad(float, float, float, float, CTexture*, Vec2d*, Vec2d*, _GXColor*, _GXBlendFactor, _GXBlendFactor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SetPaletteEnv(CTexture*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::CalcUV(float&, float&, unsigned long, unsigned long, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::IsHasDrawFmtDL(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::ReWriteDisplayList(void*, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::CalcBoundaryBoxQuantized(Vec*, Vec*, S16Vec*, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::GetNumPolygonFromDL(void*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80022780
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::GetDirectVector(Vec* param_2, Vec* param_3, Vec param_4)
{
	Vec local_vec;
	
	// Use up vector constant
	extern float lbl_801d7070;  // x component
	extern float lbl_801d7074;  // y component  
	extern float lbl_801d7078;  // z component
	
	local_vec.x = lbl_801d7070;
	local_vec.y = lbl_801d7074;
	local_vec.z = lbl_801d7078;
	
	PSVECCrossProduct(&param_4, &local_vec, param_2);
	PSVECNormalize(param_2, param_2);
	PSVECCrossProduct(param_2, &param_4, param_3);
	PSVECNormalize(param_3, param_3);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::InitConstantRegister()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SSepa(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUtil::SNl()
{
	// TODO
}
