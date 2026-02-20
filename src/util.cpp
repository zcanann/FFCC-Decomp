#include "ffcc/util.h"
#include "ffcc/gxfunc.h"
#include <string.h>

extern float lbl_8032f888;
extern float lbl_8032f88c;
extern float lbl_8032f8a0;
extern float lbl_8032f8a4;
extern float lbl_8032f8a8;
extern CMath Math;

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

struct CTextureLite {
    u8 pad_0x0[0x28];
    GXTexObj m_texObj;
    GXTlutObj m_tlutObj0;
    GXTlutObj m_tlutObj1;
};

extern void* lbl_801E88C4[];

CUtil DAT_8032ec70;

/*
 * --INFO--
 * PAL Address: 0x80024e48
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_util_cpp(void)
{
    *reinterpret_cast<void**>(&DAT_8032ec70) = lbl_801E88C4;
}

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
 * PAL Address: 0x80024de0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetVtxFmt_POS_CLR()
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80024d54
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetVtxFmt_POS_CLR_TEX()
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80024cc8
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetVtxFmt_POS_TEX0_TEX1()
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80024c18
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetVtxFmt_POS_CLR_TEX0_TEX1()
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80024bb4
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetOrthoEnv()
{
    Mtx modelMtx;
    Mtx44 orthoMtx;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    GXSetCurrentMtx(0);
    C_MTXOrtho(orthoMtx, lbl_8032f888, lbl_8032f8a0, lbl_8032f888, lbl_8032f8a4, lbl_8032f888,
               lbl_8032f88c);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
}

/*
 * --INFO--
 * PAL Address: 0x80024b38
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUtil::GetNoise(unsigned char noise)
{
    float maxNoise = (float)(noise * 2);
    float minNoise = (float)(noise >> 1);
    return (int)(maxNoise * Math.RandF() - minNoise);
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
    unsigned int scaleInt = (unsigned int)(1 << shift);
    double y = (double)in.y;
    double scale = (double)scaleInt;
    double z = (double)in.z;

    out.x = (float)((double)in.x / (double)scaleInt);
    out.y = (float)(y / scale);
    out.z = (float)(z / (double)scaleInt);
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
    unsigned int scaleInt = (unsigned int)(1 << shift);
    float y = in.y;
    float z = in.z;
    double scaleY = (double)scaleInt;
    double scaleZ = (double)scaleInt;

    out.x = (short)(int)(in.x * (float)((double)scaleInt));
    out.y = (short)(int)(y * (float)scaleY);
    out.z = (short)(int)(z * (float)scaleZ);
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
	out.x = (short)(int)(in.x * (float)(1 << shift));
	out.y = (short)(int)(in.y * (float)(1 << shift));
}

/*
 * --INFO--
 * PAL Address: 0x80024748
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderQuadNoTex(Vec pos1, Vec pos2, _GXColor color)
{
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);

    GXPosition3f32(pos1.x, pos1.y, pos1.z);
    GXColor1u32(*reinterpret_cast<u32*>(&color));

    GXPosition3f32(pos2.x, pos1.y, pos1.z);
    GXColor1u32(*reinterpret_cast<u32*>(&color));

    GXPosition3f32(pos2.x, pos2.y, pos1.z);
    GXColor1u32(*reinterpret_cast<u32*>(&color));

    GXPosition3f32(pos1.x, pos2.y, pos1.z);
    GXColor1u32(*reinterpret_cast<u32*>(&color));
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
 * PAL Address: 0x80024444
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::DisableIndMtx()
{
    float indMtx[2][3];

    GXSetNumIndStages(0);
    memset(indMtx, 0, sizeof(indMtx));
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);
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
 * PAL Address: 0x8002428c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::EndQuadEnv()
{
    Mtx cameraMtx;
    Mtx44 screenMtx;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
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
 * PAL Address: 0x800235c0
 * PAL Size: 1420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderTextureQuad(float x, float y, float width, float height, _GXTexObj* texObj, Vec2d* uv1, Vec2d* uv2,
                              _GXColor* color, _GXBlendFactor srcBlend, _GXBlendFactor dstBlend)
{
    Mtx modelMtx;
    Mtx cameraMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;
    float indMtx[2][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXLoadTexObj(texObj, GX_TEXMAP0);

    GXSetChanAmbColor(GX_COLOR0A0, white);
    GXSetChanMatColor(GX_COLOR0A0, white);
    _GXSetBlendMode(GX_BM_BLEND, srcBlend, dstBlend, GX_LO_SET);

    if (GXGetTexObjFmt(texObj) == GX_TF_I8) {
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_RED);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    }

    float u1 = lbl_8032f888;
    float v1 = lbl_8032f888;
    float u2 = lbl_8032f88c;
    float v2 = lbl_8032f88c;
    if (uv1 != 0 && uv2 != 0) {
        u1 = uv1->x;
        v1 = uv1->y;
        u2 = uv2->x;
        v2 = uv2->y;
    }

    u32 colorValue = 0xFFFFFFFF;
    if (color != 0) {
        colorValue = *reinterpret_cast<u32*>(color);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(x, y, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u1, v1);

    GXPosition3f32(x2, y, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u2, v1);

    GXPosition3f32(x2, y2, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u2, v2);

    GXPosition3f32(x, y2, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u1, v2);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);

    if (GXGetTexObjFmt(texObj) == GX_TF_I8) {
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80023014
 * PAL Size: 1452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::RenderTextureQuad(float x, float y, float width, float height, CTexture* texture, Vec2d* uv1, Vec2d* uv2,
                              _GXColor* color, _GXBlendFactor srcBlend, _GXBlendFactor dstBlend)
{
    CTextureLite* textureLite = reinterpret_cast<CTextureLite*>(texture);

    Mtx modelMtx;
    Mtx cameraMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;
    float indMtx[2][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, indMtx, 1);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP0);

    GXSetChanAmbColor(GX_COLOR0A0, white);
    GXSetChanMatColor(GX_COLOR0A0, white);
    _GXSetBlendMode(GX_BM_BLEND, srcBlend, dstBlend, GX_LO_SET);

    u8 textureFormat = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(texture) + 0x60);
    if (textureFormat == 1) {
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_RED);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    } else if (textureFormat == 8 || textureFormat == 9) {
        SetPaletteEnv(texture);
    }

    float u1 = lbl_8032f888;
    float v1 = lbl_8032f888;
    float u2 = lbl_8032f88c;
    float v2 = lbl_8032f88c;
    if (uv1 != 0 && uv2 != 0) {
        u1 = uv1->x;
        v1 = uv1->y;
        u2 = uv2->x;
        v2 = uv2->y;
    }

    u32 colorValue = 0xFFFFFFFF;
    if (color != 0) {
        colorValue = *reinterpret_cast<u32*>(color);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(x, y, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u1, v1);

    GXPosition3f32(x2, y, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u2, v1);

    GXPosition3f32(x2, y2, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u2, v2);

    GXPosition3f32(x, y2, lbl_8032f888);
    GXColor1u32(colorValue);
    GXTexCoord2f32(u1, v2);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);

    if (GXGetTexObjFmt(&textureLite->m_texObj) == GX_TF_I8) {
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80022d70
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::SetPaletteEnv(CTexture* texture)
{
    CTextureLite* textureLite = reinterpret_cast<CTextureLite*>(texture);
    GXColor tevColor2 = {0xFF, 0xFF, 0x00, 0x00};
    GXColor tevColor3 = {0x00, 0x00, 0xFF, 0xFF};

    GXSetNumTevStages(3);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG1, tevColor2);
    GXSetTevColor(GX_TEVREG2, tevColor3);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);

    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

    GXSetTevDirect(GX_TEVSTAGE1);
    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);

    GXSetTevDirect(GX_TEVSTAGE2);
    _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT0);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP0);
    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT1);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP1);
    GXLoadTlut(&textureLite->m_tlutObj0, GX_TLUT0);
    GXLoadTlut(&textureLite->m_tlutObj1, GX_TLUT1);
}

/*
 * --INFO--
 * PAL Address: 0x80022d0c
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::CalcUV(float& u, float& v, unsigned long x, unsigned long y, unsigned long width, unsigned long height)
{
    u = (float)x / (float)width;
    v = (float)y / (float)height;
}

/*
 * --INFO--
 * PAL Address: 0x80022ca4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUtil::IsHasDrawFmtDL(unsigned char cmd)
{
    switch (cmd & 0xF8) {
    case 0x80:
    case 0x90:
    case 0x98:
    case 0xA0:
    case 0xA8:
    case 0xB0:
    case 0xB8:
        return 1;
    default:
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80022b80
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::ReWriteDisplayList(void* dlData, unsigned long dlSize, unsigned long copyFlags)
{
	u8* data = (u8*)dlData;
	u8* current = data;
	u8* end = data + dlSize;

	while (current < end) {
		u8 cmd = *current;
		u32 count = *(u16*)(current + 1);
		u8 primitive = cmd & 0xF8;
		bool isPrimitive = false;
		current += 3;

		switch (primitive) {
			case 0x80:
			case 0x90:
			case 0x98:
			case 0xA0:
			case 0xA8:
			case 0xB0:
			case 0xB8:
				isPrimitive = true;
				break;
		}

		if (!isPrimitive) {
			break;
		}

		while (count != 0) {
			u16 value = *(u16*)current;

			if ((copyFlags & 1) != 0) {
				*(u16*)(current + 4) = value;
			}
			if ((copyFlags & 2) != 0) {
				*(u16*)(current + 6) = value;
			}

			if ((cmd & 7) == 2) {
				if ((copyFlags & 2) != 0) {
					*(u16*)(current + 8) = value;
				}
				current += 10;
			} else {
				current += 8;
			}

			count--;
		}
	}

	DCFlushRange(dlData, dlSize);
}

/*
 * --INFO--
 * PAL Address: 0x8002295c
 * PAL Size: 548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::CalcBoundaryBoxQuantized(Vec* minOut, Vec* maxOut, S16Vec* vecs, unsigned long count, unsigned long shift)
{
	s16 minX = 0x7FFF;
	s16 minY = 0x7FFF;
	s16 minZ = 0x7FFF;
	s16 maxX = -0x7FFF;
	s16 maxY = -0x7FFF;
	s16 maxZ = -0x7FFF;

	for (unsigned long i = 0; i < count; i++) {
		if (minX > vecs->x) {
			minX = vecs->x;
		}
		if (minY > vecs->y) {
			minY = vecs->y;
		}
		if (minZ > vecs->z) {
			minZ = vecs->z;
		}
		if (vecs->x > maxX) {
			maxX = vecs->x;
		}
		if (vecs->y > maxY) {
			maxY = vecs->y;
		}
		if (vecs->z > maxZ) {
			maxZ = vecs->z;
		}
		vecs++;
	}

	minOut->x = (float)minX / (float)(1 << shift);
	minOut->y = (float)minY / (float)(1 << shift);
	minOut->z = (float)minZ / (float)(1 << shift);
	maxOut->x = (float)maxX / (float)(1 << shift);
	maxOut->y = (float)maxY / (float)(1 << shift);
	maxOut->z = (float)maxZ / (float)(1 << shift);
}

/*
 * --INFO--
 * PAL Address: 0x80022818
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUtil::GetNumPolygonFromDL(void* dlData, unsigned long)
{
    u8 cmd;
    u16 vertexCount16;
    bool isPrimitive;
    bool running;
    int polygonCount;
    u8 primitive;
    u32 vertexCount;
    u32 blockCount;
    u8* data = static_cast<u8*>(dlData);

    running = true;
    polygonCount = 0;
LOOP:
    do {
        if (!running) {
            return polygonCount;
        }
        cmd = *data;
        vertexCount16 = *(u16*)(data + 1);
        vertexCount = (u32)vertexCount16;
        data += 3;
        primitive = cmd & 0xF8;
        if (primitive == 0xA0) {
VALID:
            isPrimitive = true;
        } else {
            if (0x9F < primitive) {
                if (primitive != 0xB0) {
                    if (primitive < 0xB0) {
                        if (primitive == 0xA8) {
                            goto VALID;
                        }
                    } else if (primitive == 0xB8) {
                        goto VALID;
                    }
                    goto INVALID;
                }
                goto VALID;
            }
            if (primitive == 0x90) {
                goto VALID;
            }
            if (primitive < 0x90) {
                if (primitive == 0x80) {
                    goto VALID;
                }
            } else if (primitive == 0x98) {
                goto VALID;
            }
INVALID:
            isPrimitive = false;
        }
        if (isPrimitive) {
            if (primitive == 0x90) {
                polygonCount += vertexCount / 3;
            } else if (primitive == 0x98) {
                polygonCount = vertexCount + polygonCount - 2;
            }
            if ((cmd & 7) != 2) {
                if (vertexCount != 0) {
                    blockCount = (u32)(vertexCount16 >> 3);
                    if ((vertexCount16 >> 3) != 0) {
                        do {
                            data += 0x40;
                            blockCount--;
                        } while (blockCount != 0);
                        vertexCount &= 7;
                        if ((vertexCount16 & 7) == 0) {
                            goto LOOP;
                        }
                    }
                    do {
                        data += 8;
                        vertexCount--;
                    } while (vertexCount != 0);
                }
                goto LOOP;
            }
            if (vertexCount != 0) {
                blockCount = (u32)(vertexCount16 >> 3);
                if ((vertexCount16 >> 3) != 0) {
                    do {
                        data += 0x50;
                        blockCount--;
                    } while (blockCount != 0);
                    vertexCount &= 7;
                    if ((vertexCount16 & 7) == 0) {
                        goto LOOP;
                    }
                }
                do {
                    data += 10;
                    vertexCount--;
                } while (vertexCount != 0);
            }
            goto LOOP;
        }
        running = false;
    } while (true);
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

    extern Vec lbl_801d7070;

    local_vec = lbl_801d7070;

    PSVECCrossProduct(&param_4, &local_vec, param_2);
    PSVECNormalize(param_2, param_2);
    PSVECCrossProduct(param_2, &param_4, param_3);
    PSVECNormalize(param_3, param_3);
}

/*
 * --INFO--
 * PAL Address: 0x80022724
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUtil::InitConstantRegister()
{
    int i = 0;

    do {
        GXSetTevKColorSel((GXTevStageID)i, (GXTevKColorSel)6);
        GXSetTevKAlphaSel((GXTevStageID)i, (GXTevKAlphaSel)0);
        _GXSetTevSwapMode((GXTevStageID)i, (_GXTevSwapSel)0, (_GXTevSwapSel)0);
        i++;
    } while (i < 0x10);
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
