#ifndef _FFCC_PPP_UTIL_H_
#define _FFCC_PPP_UTIL_H_

#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CTexture;
struct Vec;
struct Vec2d;

class CUtil
{
public:
    CUtil();

    void SetVtxFmt_POS_CLR();
    void SetVtxFmt_POS_CLR_TEX();
    void SetVtxFmt_POS_TEX0_TEX1();
    void SetVtxFmt_POS_CLR_TEX0_TEX1();
    void SetOrthoEnv();
    int GetNoise(unsigned char);
    void GetSplinePos(Vec&, Vec, Vec, Vec, Vec, float, float);
    void ConvI2FVector(Vec&, S16Vec, long);
    void ConvF2IVector(S16Vec&, Vec, long);
    void ConvF2IVector2d(S16Vec2d&, Vec2d, long);
    void RenderQuadNoTex(Vec, Vec, _GXColor);
    void RenderQuad(Vec, Vec, _GXColor, Vec2d*, Vec2d*);
    void RenderQuadTex2(Vec, Vec, _GXColor, Vec2d*, Vec2d*);
    void DisableIndMtx();
    void BeginQuadEnv();
    void EndQuadEnv();
    void ClearZBufferRect(float, float, float, float);
    void RenderColorQuad(float, float, float, float, _GXColor);
    void RenderTextureQuad(float, float, float, float, _GXTexObj*, Vec2d*, Vec2d*, _GXColor*, _GXBlendFactor, _GXBlendFactor);
    void RenderTextureQuad(float, float, float, float, CTexture*, Vec2d*, Vec2d*, _GXColor*, _GXBlendFactor, _GXBlendFactor);
    void SetPaletteEnv(CTexture*);
    void CalcUV(float&, float&, unsigned long, unsigned long, unsigned long, unsigned long);
    int IsHasDrawFmtDL(unsigned char);
    void ReWriteDisplayList(void*, unsigned long, unsigned long);
    void CalcBoundaryBoxQuantized(Vec*, Vec*, S16Vec*, unsigned long, unsigned long);
    int GetNumPolygonFromDL(void*, unsigned long);
    void GetDirectVector(Vec*, Vec*, Vec);
    void InitConstantRegister();
    void SSepa(char*);
    void SNl();
    void Init();
    void Quit();
};

#endif // _FFCC_PPP_UTIL_H_
