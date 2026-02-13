#include "ffcc/mapobj.h"
#include "ffcc/math.h"

extern float lbl_8032F938;
extern float lbl_8032F93C;
extern float lbl_8032F944;
extern float lbl_8032F948;
extern float lbl_8032F958;

namespace {
static inline unsigned char* Ptr(CMapObj* self, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(self) + offset;
}

static inline void*& PtrAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline unsigned char& U8At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(self, offset));
}

static inline unsigned short& U16At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(self, offset));
}

static inline int& S32At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(self, offset));
}

static inline float& F32At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(self, offset));
}
}

extern "C" void __dl__FPv(void*);

template class CPtrArray<CMapAnimRun*>;
template class CPtrArray<CMapShadow*>;

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
 * PAL Address: 0x8002BEFC
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::CMapObj()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BE7C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::~CMapObj()
{
    void* attr = PtrAt(this, 0xEC);
    if (attr != 0) {
        (*(void (**)(void*, int))(*reinterpret_cast<unsigned int*>(attr) + 8))(attr, 1);
        PtrAt(this, 0xEC) = 0;
    }

    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BE7C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMapObj* dtor_8002BE7C(CMapObj* mapObj, short param_2)
{
    if (mapObj != 0) {
        void* attr = PtrAt(mapObj, 0xEC);
        if (attr != 0) {
            (*(void (**)(void*, int))(*reinterpret_cast<unsigned int*>(attr) + 8))(attr, 1);
            PtrAt(mapObj, 0xEC) = 0;
        }

        mapObj->Init();
        if (0 < param_2) {
            __dl__FPv(mapObj);
        }
    }

    return mapObj;
}

/*
 * --INFO--
 * PAL Address: 0x8002BF2C
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Init()
{
    U8At(this, 0x1B) = 1;
    U8At(this, 0x1C) = 1;
    S32At(this, 0x0) = 0;
    S32At(this, 0xC) = 0;
    S32At(this, 0xEC) = 0;

    U8At(this, 0x15) = 0x7E;
    U8At(this, 0x14) = 0x7E;
    U8At(this, 0x1F) = 0xFF;
    U8At(this, 0x20) = 0;
    U8At(this, 0x27) = 0;
    U8At(this, 0x21) = 0;

    U16At(this, 0x2E) = 0xFFFF;
    U16At(this, 0x30) = 0xFFFF;
    U16At(this, 0x32) = 0xFFFF;
    U8At(this, 0x18) = 1;
    U8At(this, 0x19) = 1;
    U16At(this, 0x34) = 0xFFFF;

    F32At(this, 0x48) = lbl_8032F948;
    F32At(this, 0x44) = lbl_8032F948;
    F32At(this, 0x4C) = lbl_8032F948;
    F32At(this, 0x50) = lbl_8032F958;

    U16At(this, 0x2C) = 0;
    U16At(this, 0x2A) = 0;
    U16At(this, 0x28) = 0;
    U8At(this, 0x24) = 0xFF;
    U8At(this, 0x23) = 0xFF;
    S32At(this, 0x10) = 0;
    U16At(this, 0x16) = 0xFFFF;
    U8At(this, 0x22) = 1;
    S32At(this, 0x3C) = -1;

    F32At(this, 0x60) = lbl_8032F944;
    F32At(this, 0x5C) = lbl_8032F944;
    F32At(this, 0x58) = lbl_8032F944;
    U8At(this, 0x1A) = 0;
    F32At(this, 0x40) = lbl_8032F944;
    U8At(this, 0x25) = 1;
    U8At(this, 0x26) = 0;
    S32At(this, 0x38) = -1;
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
 * PAL Address: 0x800287D0
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetMime(int mode, int target, int type)
{
    unsigned char* mime = reinterpret_cast<unsigned char*>(PtrAt(this, 0xEC));

    *reinterpret_cast<int*>(mime + 0x20) = mode;
    *reinterpret_cast<int*>(mime + 0x1C) = mode;

    if (*reinterpret_cast<int*>(mime + 0x28) < target) {
        target = *reinterpret_cast<int*>(mime + 0x28);
    }

    *reinterpret_cast<int*>(mime + 0x24) = target;
    *(mime + 0x17) = static_cast<unsigned char>(type);
    *(mime + 0x18) = 1;
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
