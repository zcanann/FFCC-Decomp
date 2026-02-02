#include "ffcc/mapobj.h"

/*
 * --INFO--
 * Address:	8002BEFC
 * Size:	48
 */
CMapObj::CMapObj()
{
	Init();
}

/*
 * --INFO--
 * Address:	8002BE7C
 * Size:	128
 */
CMapObj::~CMapObj()
{
	void** member = (void**)(((char*)this) + 0xEC);
	if (*member != 0) {
		void* obj = *member;
		if (obj != 0) {
			// Call virtual destructor
			((void(**)(void*, int))((*(void**)obj)))[1](obj, 1);
		}
		*member = 0;
	}
	Init();
}

/*
 * --INFO--
 * Address:	8002BF2C
 * Size:	196
 */
void CMapObj::Init()
{
	// Initialize various members to default values
	char* self = (char*)this;
	
	// Clear important pointers
	*(int*)(self + 0x0) = 0;
	*(int*)(self + 0xC) = 0;
	*(int*)(self + 0xEC) = 0;
	*(int*)(self + 0x3C) = 0xFFFFFFFF;
	*(int*)(self + 0x38) = 0xFFFFFFFF;
	
	// Initialize various flags and bytes
	*(char*)(self + 0x1B) = 1;
	*(char*)(self + 0x1C) = 1; 
	*(char*)(self + 0x15) = 0x7E;
	*(char*)(self + 0x14) = 0x7E;
	*(char*)(self + 0x1F) = 0xFF;
	*(char*)(self + 0x20) = 0;
	*(char*)(self + 0x27) = 0;
	*(char*)(self + 0x21) = 0;
	*(char*)(self + 0x18) = 1;
	*(char*)(self + 0x19) = 1;
	*(char*)(self + 0x1A) = 0;
	*(char*)(self + 0x22) = 1;
	*(char*)(self + 0x24) = 0xFF;
	*(char*)(self + 0x23) = 0xFF;
	*(char*)(self + 0x25) = 1;
	*(char*)(self + 0x26) = 0;
	
	// Initialize 16-bit values
	*(short*)(self + 0x2E) = 0xFFFF;
	*(short*)(self + 0x30) = 0xFFFF;
	*(short*)(self + 0x32) = 0xFFFF;
	*(short*)(self + 0x34) = 0xFFFF;
	*(short*)(self + 0x16) = 0xFFFF;
	*(short*)(self + 0x2C) = 0;
	*(short*)(self + 0x2A) = 0;
	*(short*)(self + 0x28) = 0;
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
