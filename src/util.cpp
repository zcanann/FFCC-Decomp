#include "ffcc/util.h"
#include "ffcc/gxfunc.h"

extern float lbl_8032f888;
extern float lbl_8032f88c;
extern float lbl_8032f8a0;
extern float lbl_8032f8a4;
extern float lbl_8032f8a8;

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
} CameraPcs;

// Vec2d definition 
struct Vec2d {
	float x, y;
};

CUtil DAT_8032ec70;

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
 * PAL Address: 0x800249ac
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::GetSplinePos(Vec& out, Vec p0, Vec p1, Vec p2, Vec p3, float t, float scale)
{
	Vec tan0;
	Vec tan1;

	PSVECSubtract(&p2, &p0, &tan0);
	PSVECScale(&tan0, &tan0, scale);
	PSVECSubtract(&p3, &p1, &tan1);
	PSVECScale(&tan1, &tan1, scale);

	float t2 = t * t;
	float t3 = t2 * t;

	extern float lbl_8032f8ac;
	extern float lbl_8032f8b0;
	extern float lbl_8032f8b4;
	extern float lbl_8032f88c;

	float h01 = (lbl_8032f8b4 * t3) + (lbl_8032f8b0 * t2);
	float h00 = lbl_8032f88c + (lbl_8032f8ac * t3) - (lbl_8032f8b0 * t2);
	float h10 = t - ((lbl_8032f8ac * t2) - t3);
	float h11 = t3 - t2;

	out.x = (h11 * tan1.x) + (h10 * tan0.x) + (h00 * p1.x) + (h01 * p2.x);
	out.y = (h11 * tan1.y) + (h10 * tan0.y) + (h00 * p1.y) + (h01 * p2.y);
	out.z = (h11 * tan1.z) + (h10 * tan0.z) + (h00 * p1.z) + (h01 * p2.z);
}

/*
 * --INFO--
 * PAL Address: 0x800248fc
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::ConvI2FVector(Vec& out, S16Vec in, long shift)
{
	float scale = (float)(1 << shift);

	out.x = (float)in.x / scale;
	out.y = (float)in.y / scale;
	out.z = (float)in.z / scale;
}

/*
 * --INFO--
 * PAL Address: 0x80024864
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::ConvF2IVector(S16Vec& out, Vec in, long shift)
{
	float scale = (float)(1 << shift);

	out.x = (short)(in.x * scale);
	out.y = (short)(in.y * scale);
	out.z = (short)(in.z * scale);
}

/*
 * --INFO--
 * PAL Address: 0x800247f4
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::ConvF2IVector2d(S16Vec2d& out, Vec2d in, long shift)
{
	float scale = (float)(1 << shift);

	out.x = (short)(in.x * scale);
	out.y = (short)(in.y * scale);
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
 * PAL Address: 0x800242e8
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::BeginQuadEnv()
{
    Mtx modelMtx;
    Mtx44 orthoMtx;
    float indMtx[2][3] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(orthoMtx, lbl_8032f888, lbl_8032f8a0, lbl_8032f888, lbl_8032f8a4, lbl_8032f888,
               lbl_8032f88c);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE,
                  GX_AF_SPEC);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);
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
 * PAL Address: 0x80023ed0
 * PAL Size: 956b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::ClearZBufferRect(float x, float y, float width, float height)
{
    Mtx modelMtx;
    Mtx cameraMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    float indMtx[2][3] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };

    float x2 = x + width;
    float y2 = y + height;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(orthoMtx, lbl_8032f888, lbl_8032f8a0, lbl_8032f888, lbl_8032f8a4, lbl_8032f888, lbl_8032f88c);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetChanAmbColor(GX_COLOR0A0, white);
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(x, y, lbl_8032f8a8);
    GXColor1u32(*reinterpret_cast<u32*>(&white));
    GXPosition3f32(x2, y, lbl_8032f8a8);
    GXColor1u32(*reinterpret_cast<u32*>(&white));
    GXPosition3f32(x2, y2, lbl_8032f8a8);
    GXColor1u32(*reinterpret_cast<u32*>(&white));
    GXPosition3f32(x, y2, lbl_8032f8a8);
    GXColor1u32(*reinterpret_cast<u32*>(&white));

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
    GXSetColorUpdate(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
}

/*
 * --INFO--
 * PAL Address: 0x80023b4c
 * PAL Size: 900b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderColorQuad(float x, float y, float width, float height, _GXColor color)
{
    Mtx modelMtx;
    Mtx cameraMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;
    float indMtx[2][3] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
    };
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    float x2 = x + width;
    float y2 = y + height;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    GXSetCurrentMtx(0);

    C_MTXOrtho(orthoMtx, lbl_8032f888, lbl_8032f8a0, lbl_8032f888, lbl_8032f8a4, lbl_8032f888, lbl_8032f88c);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);

    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetChanAmbColor(GX_COLOR0A0, white);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetNumChans(1);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(x, y, lbl_8032f888);
    GXColor1u32(*reinterpret_cast<u32*>(&color));
    GXPosition3f32(x2, y, lbl_8032f888);
    GXColor1u32(*reinterpret_cast<u32*>(&color));
    GXPosition3f32(x2, y2, lbl_8032f888);
    GXColor1u32(*reinterpret_cast<u32*>(&color));
    GXPosition3f32(x, y2, lbl_8032f888);
    GXColor1u32(*reinterpret_cast<u32*>(&color));

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
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
