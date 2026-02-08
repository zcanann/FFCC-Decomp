#include "ffcc/mapobj.h"
#include "ffcc/math.h"

extern float lbl_8032F938;
extern float lbl_8032F93C;

/*
 * --INFO--
 * PAL Address: 0x8002BE10
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CBound::CBound()
{
    float* bounds = (float*)this;
    float max = lbl_8032F93C;
    float min = lbl_8032F938;

    bounds[2] = min;
    bounds[1] = min;
    bounds[0] = min;
    bounds[5] = max;
    bounds[4] = max;
    bounds[3] = max;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObj::CMapObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObj::~CMapObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::ReadOtmObj(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::CalcMtx(float (*) [4], unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetShow_r(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetShow(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetLink()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcColorKeyFrame(CMapKeyFrame*, _GXColor&, _GXColor*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetDrawEnv()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::IsDrawAlphaLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::Draw(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetDrawFlag()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::DrawHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::DrawHitWire()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::DrawHitNormal()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapObj::CheckHitCylinder(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapObj::CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::GetHitFaceNormal(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::CalcHitSlide(Vec*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::CalcHitPosition(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetMime(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtr::~CMapObjAtr()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrPlaySta::CMapObjAtrPlaySta()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtr::CMapObjAtr()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMime::CMapObjAtrMime()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetCalcMtx()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMeshName::CMapObjAtrMeshName()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMeshName::~CMapObjAtrMeshName()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrPointLight::~CMapObjAtrPointLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrSpotLight::~CMapObjAtrSpotLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMime::~CMapObjAtrMime()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrPlaySta::~CMapObjAtrPlaySta()
{
	// TODO
}
