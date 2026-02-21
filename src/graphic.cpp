#include "ffcc/graphic.h"

#include <string.h>

#include "ffcc/memory.h"
#include "ffcc/pppfunctbl.h"
#include "ffcc/system.h"
#include "ffcc/util.h"

extern void* lbl_801E8408;
extern char DAT_80238030[];
extern CUtil DAT_8032ec70;

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
} CameraPcs;

extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dla__FPv(void*);
extern "C" char lbl_801D6348[];

static inline void*& PtrAt(CGraphic* self, u32 offset) {
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + offset);
}

static inline u16 U16At(void* p, u32 offset) {
    return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(p) + offset);
}

extern "C" {
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int,
                                                                                                             int, int,
                                                                                                             int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int,
                                                                                                             int, int,
                                                                                                             int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
}

/*
 * --INFO--
 * PAL Address: 0x80019f68
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_graphic_cpp(void)
{
	*(void**)&Graphic = &lbl_801E8408;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void checkThread(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGraphic::CGraphic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::GetProgressive()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::ChangeProgressive(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetCopyClear(_GXColor, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8001992c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdDispCopySrc()
{
    void* renderMode = PtrAt(this, 0x71E0);
    GXSetDispCopySrc(0, 0, U16At(renderMode, 4), U16At(renderMode, 6));
}

/*
 * --INFO--
 * PAL Address: 0x80019900
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdDispCopyDst()
{
    void* renderMode = PtrAt(this, 0x71E0);
    GXSetDispCopyDst(U16At(renderMode, 4), U16At(renderMode, 6));
}

/*
 * --INFO--
 * PAL Address: 0x800198b8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdPixelFmt()
{
    void* renderMode = PtrAt(this, 0x71E0);
    if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(renderMode) + 0x19) == 0) {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetViewport()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::BeginFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::EndFrame()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800196e0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetDrawDoneDebugData(signed char drawDoneId)
{
	GXSetDrawSync((u16)(((System.m_currentOrderIndex & 0xFF) << 8) | (drawDoneId & 0xFF)));
}

/*
 * --INFO--
 * PAL Address: 0x800196b8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetDrawDoneDebugDataPartControl(int partControl)
{
	GXSetDrawSync((u16)(partControl | 0x8000));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void wakeup(OSAlarm*, OSContext*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void sleep()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::_WaitDrawDone(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Thread()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
u8 CGraphic::IsFifoOver()
{
	GXBool fifoWrap;
	GXBool gpRead;
	GXBool cpuWrite;
	GXBool underflow;
	GXBool overhi;
	u32 fifoCount;

	GXGetFifoStatus(GXGetCPUFifo(), &overhi, &underflow, &fifoCount, &cpuWrite, &gpRead, &fifoWrap);
	return fifoWrap;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
u32 CGraphic::IsFrameRateOver()
{
	return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x7350);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Flip()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Printf(char*, ...)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::Printf(unsigned long, unsigned long, char*, ...)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawDebugString()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::InitDebugString()
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
void CGraphic::DrawDebugStringDirect(unsigned long, unsigned long, char*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SaveFrameBuffer(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawSphere()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawSphere(float (*) [4], Vec*, float, _GXColor*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawSphere(float (*) [4], Vec*, Vec*, _GXColor*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawSphere(float (*) [4], _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::makeSphere()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawBound(CBound&, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetFogColor(_GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetFogParam(float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetFog(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::CopySaveFrameBuffer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::GetBackBufferRect(int&, int&, int&, int&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::GetBackBufferRect2(void*, _GXTexObj*, int, int, int, int, int, _GXTexFilter, _GXTexFmt, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 800178a4
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderTexQuadGrouad(Vec pos1, Vec pos2, _GXColor color1, _GXColor color2, _GXColor color3, _GXColor color4)
{
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	
	// Vertex 1
	GXPosition3f32(pos1.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color1);
	GXTexCoord2f32(0.0f, 0.0f);
	
	// Vertex 2
	GXPosition3f32(pos2.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color2);
	GXTexCoord2f32(1.0f, 0.0f);
	
	// Vertex 3
	GXPosition3f32(pos2.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color4);
	GXTexCoord2f32(1.0f, 1.0f);
	
	// Vertex 4
	GXPosition3f32(pos1.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color3);
	GXTexCoord2f32(0.0f, 1.0f);
}

/*
 * --INFO--
 * PAL Address: 800177f0
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderNoTexQuadGrouad(Vec pos1, Vec pos2, _GXColor color1, _GXColor color2, _GXColor color3, _GXColor color4)
{
	GXBegin(GX_QUADS, GX_VTXFMT6, 4);
	
	// Vertex 1
	GXPosition3f32(pos1.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color1);
	
	// Vertex 2  
	GXPosition3f32(pos2.x, pos1.y, pos1.z);
	GXColor1u32(*(u32*)&color2);
	
	// Vertex 3
	GXPosition3f32(pos2.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color4);
	
	// Vertex 4
	GXPosition3f32(pos1.x, pos2.y, pos1.z);
	GXColor1u32(*(u32*)&color3);
}

/*
 * --INFO--
 * PAL Address: 0x80016fb0
 * PAL Size: 2112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderDOF(signed char mode, signed char blurWidth, float nearDist, float farDist, Vec targetPos, int blurPasses)
{
	_GXTexObj smallBackTex;
	_GXTexObj backBufferTex;
	_GXColor dofColor;
	Vec cameraPos;
	Vec cameraToTarget;
	Vec scaledDir;
	Vec quadMin;
	Vec quadMax;
	float gxProjection[7];
	float gxViewport[6];
	Mtx cameraMtx;
	float projX;
	float projY;
	float projZ;
	unsigned int texBufferSize;
	unsigned int depthAlphaNear;
	unsigned int depthAlphaFar;
	unsigned char nearAlpha;
	unsigned char farAlpha;
	float xOffset;
	float yOffset;
	bool hasNearAlpha;
	bool hasFarAlpha;

	if (mode >= 4) {
		return;
	}

	if (nearDist < 0.0f) {
		nearDist = 0.0f;
	}
	if (nearDist > 1.0f) {
		nearDist = 1.0f;
	}
	if (farDist < nearDist) {
		farDist = nearDist;
	}
	if (blurWidth < 1) {
		blurWidth = 1;
	}

	nearAlpha = 0;
	farAlpha = 0;
	hasNearAlpha = false;
	hasFarAlpha = false;
	texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

	cameraPos.x = CameraPcs._224_4_;
	cameraPos.y = 0.0f;
	cameraPos.z = CameraPcs._232_4_;

	targetPos.y = 0.0f;
	PSVECSubtract(&targetPos, &cameraPos, &cameraToTarget);

	GXGetProjectionv(gxProjection);
	GXGetViewportv(gxViewport);
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

	if (mode != 2) {
		PSVECScale(&cameraToTarget, &scaledDir, nearDist);
		GXProject(cameraPos.x + scaledDir.x, targetPos.y, cameraPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		depthAlphaNear = (unsigned int)(projZ * 255.0f);
		if (depthAlphaNear > 0xFF) {
			depthAlphaNear = 0xFF;
		}
		nearAlpha = (unsigned char)depthAlphaNear;
		hasNearAlpha = true;
	}

	if (mode != 1) {
		float targetMag = PSVECMag(&cameraToTarget);
		if (targetMag > 0.0f) {
			PSVECScale(&cameraToTarget, &scaledDir, farDist / targetMag);
		} else {
			scaledDir.x = 0.0f;
			scaledDir.y = 0.0f;
			scaledDir.z = 0.0f;
		}

		GXProject(targetPos.x + scaledDir.x, targetPos.y, targetPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		depthAlphaFar = (unsigned int)(projZ * 255.0f);
		if (depthAlphaFar == 0) {
			depthAlphaFar = 0xFF;
		}
		if (depthAlphaFar > 0xFF) {
			depthAlphaFar = 0xFF;
		}
		farAlpha = (unsigned char)depthAlphaFar;
		hasFarAlpha = true;
	}

	if (!hasNearAlpha) {
		nearAlpha = 0;
	}
	if (!hasFarAlpha) {
		farAlpha = 0xFF;
	}

	DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
	CreateSmallBackTexture(DAT_80238030, &smallBackTex, 0x140, 0xE0, GX_NEAR, GX_TF_I8, 0);
	GetBackBufferRect2(DAT_80238030, &backBufferTex, 0, 0, 0x280, 0x1C0, texBufferSize, GX_NEAR, (_GXTexFmt)0x11, 0);
	DAT_8032ec70.SetVtxFmt_POS_CLR_TEX0_TEX1();
	DAT_8032ec70.SetOrthoEnv();

	xOffset = (float)blurWidth;
	yOffset = xOffset * (224.0f / 640.0f);

	for (int pass = 0; pass < 2; pass++) {
		int kColorSel = 0x0C;
		int kAlphaSel = 0x1C;
		unsigned char passAlpha = nearAlpha;

		if ((pass == 0) && !((mode != 2) && hasNearAlpha && (mode != 1) && hasFarAlpha)) {
			continue;
		}

		if (pass != 0) {
			kColorSel = 0x0D;
			kAlphaSel = 0x1D;
			passAlpha = farAlpha;
		}

		dofColor.r = passAlpha;
		dofColor.g = passAlpha;
		dofColor.b = passAlpha;
		dofColor.a = passAlpha;
		GXSetTevKColor((GXTevKColorID)pass, dofColor);

		dofColor.a = 0x80;
		GXSetChanAmbColor(GX_COLOR0A0, dofColor);
		GXSetChanMatColor(GX_COLOR0A0, dofColor);

		_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 5);

		GXSetTevDirect(GX_TEVSTAGE0);
		GXLoadTexObj(&backBufferTex, GX_TEXMAP0);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		GXSetTevKColorSel(GX_TEVSTAGE0, (GXTevKColorSel)kColorSel);
		GXSetTevKAlphaSel(GX_TEVSTAGE0, (GXTevKAlphaSel)kAlphaSel);

		if (pass == 0) {
			_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0,
			                                                                                                         0x0E, 8,
			                                                                                                         0x0C,
			                                                                                                         0x0F);
		} else {
			_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 8,
			                                                                                                         0x0E,
			                                                                                                         0x0C,
			                                                                                                         0x0F);
		}
		_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 8, 0, 0, 1, 0);
		_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 4, 6, 6,
		                                                                                                       7);
		_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 8, 0, 0, 1, 0);

		GXSetTevDirect(GX_TEVSTAGE1);
		GXLoadTexObj(&smallBackTex, GX_TEXMAP1);
		GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
		_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0x0F,
		                                                                                                       0x0F, 0x0F,
		                                                                                                       8);
		_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
		_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 5, 0,
		                                                                                                       7);
		_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);

		GXSetNumTevStages(2);
		GXSetNumTexGens(2);

		quadMin.x = 0.0f;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = -xOffset;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f - xOffset;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = xOffset;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f + xOffset;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = 0.0f;
		quadMin.y = -yOffset;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f - yOffset;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = 0.0f;
		quadMin.y = yOffset;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f + yOffset;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::CreateSmallBackTexture(void*, _GXTexObj*, long, long, _GXTexFilter, _GXTexFmt, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::InitBlurParameter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::RenderBlur(int, unsigned char, unsigned char, unsigned char, unsigned char, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::CreateTempBuffer()
{
	u32 bufferSize = ((U16At(PtrAt(this, 0x71E0), 4) + 0xF) & 0xFFF0) * U16At(PtrAt(this, 0x71E0), 6) * 2 + 0x46000;
	u8* tempBuffer = reinterpret_cast<u8*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
	    &Memory, bufferSize, reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x8)), lbl_801D6348, 0xB53, 0));

	PtrAt(this, 0x71E8) = tempBuffer;
	memset(tempBuffer, 0, 0x46004);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DestroyTempBuffer()
{
	if (PtrAt(this, 0x71E8) != nullptr) {
		__dla__FPv(PtrAt(this, 0x71E8));
		PtrAt(this, 0x71E8) = nullptr;
	}
}
