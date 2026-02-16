#include "ffcc/mapobj.h"
#include "ffcc/math.h"
#include <dolphin/mtx.h>

extern float lbl_8032F938;
extern float lbl_8032F93C;
extern float lbl_8032F944;
extern float lbl_8032F948;
extern float lbl_8032F950;
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

static inline CMapObj*& ObjAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<CMapObj**>(Ptr(self, offset));
}

static inline Mtx& MtxAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<Mtx*>(Ptr(self, offset));
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
 * PAL Address: 0x8002A258
 * PAL Size: 856b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CalcMtx(float (*parentMtx)[4], unsigned char inDirty)
{
    Mtx mtx0;
    Mtx mtx1;
    Mtx mtx2;
    CMapObj* obj = this;

    do {
        unsigned char dirty = inDirty;

        if (U8At(obj, 0x1B) != 0) {
            U8At(obj, 0x1B) = 0;
            if (U8At(obj, 0x1C) != 0) {
                PSMTXScale(MtxAt(obj, 0x88), F32At(obj, 0x7C), F32At(obj, 0x80), F32At(obj, 0x84));
                PSMTXRotRad(mtx2, 'x', lbl_8032F950 * F32At(obj, 0x70));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXRotRad(mtx2, 'y', lbl_8032F950 * F32At(obj, 0x74));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXRotRad(mtx2, 'z', lbl_8032F950 * F32At(obj, 0x78));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXTrans(mtx2, F32At(obj, 0x64), F32At(obj, 0x68), F32At(obj, 0x6C));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
            }

            dirty = 1;
        }

        if (dirty != 0) {
            PSMTXConcat(*reinterpret_cast<Mtx*>(parentMtx), MtxAt(obj, 0x88), MtxAt(obj, 0xB8));
        }

        for (CMapObj* child = ObjAt(obj, 0x4); child != 0; child = ObjAt(child, 0x8)) {
            unsigned char childDirty = dirty;

            if (U8At(child, 0x1B) != 0) {
                U8At(child, 0x1B) = 0;
                if (U8At(child, 0x1C) != 0) {
                    PSMTXScale(MtxAt(child, 0x88), F32At(child, 0x7C), F32At(child, 0x80), F32At(child, 0x84));
                    PSMTXRotRad(mtx1, 'x', lbl_8032F950 * F32At(child, 0x70));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXRotRad(mtx1, 'y', lbl_8032F950 * F32At(child, 0x74));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXRotRad(mtx1, 'z', lbl_8032F950 * F32At(child, 0x78));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXTrans(mtx1, F32At(child, 0x64), F32At(child, 0x68), F32At(child, 0x6C));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                }

                childDirty = 1;
            }

            if (childDirty != 0) {
                PSMTXConcat(MtxAt(obj, 0xB8), MtxAt(child, 0x88), MtxAt(child, 0xB8));
            }

            for (CMapObj* grandChild = ObjAt(child, 0x4); grandChild != 0; grandChild = ObjAt(grandChild, 0x8)) {
                unsigned char grandChildDirty = childDirty;

                if (U8At(grandChild, 0x1B) != 0) {
                    U8At(grandChild, 0x1B) = 0;
                    if (U8At(grandChild, 0x1C) != 0) {
                        PSMTXScale(
                            MtxAt(grandChild, 0x88), F32At(grandChild, 0x7C), F32At(grandChild, 0x80), F32At(grandChild, 0x84));
                        PSMTXRotRad(mtx0, 'x', lbl_8032F950 * F32At(grandChild, 0x70));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXRotRad(mtx0, 'y', lbl_8032F950 * F32At(grandChild, 0x74));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXRotRad(mtx0, 'z', lbl_8032F950 * F32At(grandChild, 0x78));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXTrans(mtx0, F32At(grandChild, 0x64), F32At(grandChild, 0x68), F32At(grandChild, 0x6C));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                    }

                    grandChildDirty = 1;
                }

                if (grandChildDirty != 0) {
                    PSMTXConcat(MtxAt(child, 0xB8), MtxAt(grandChild, 0x88), MtxAt(grandChild, 0xB8));
                }

                if (ObjAt(grandChild, 0x4) != 0) {
                    ObjAt(grandChild, 0x4)->CalcMtx(reinterpret_cast<float(*)[4]>(&MtxAt(grandChild, 0xB8)), grandChildDirty);
                }
            }
        }

        obj = ObjAt(obj, 0x8);
    } while (obj != 0);
}

/*
 * --INFO--
 * PAL Address: 0x8002A008
 * PAL Size: 592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow_r(int show)
{
    CMapObj* root = this;

    do {
        if (show == 0) {
            U8At(root, 0x18) &= 0xFE;
        } else {
            U8At(root, 0x18) |= 1;
        }

        for (CMapObj* c0 = ObjAt(root, 0x4); c0 != 0; c0 = ObjAt(c0, 0x8)) {
            if (show == 0) {
                U8At(c0, 0x18) &= 0xFE;
            } else {
                U8At(c0, 0x18) |= 1;
            }

            for (CMapObj* c1 = ObjAt(c0, 0x4); c1 != 0; c1 = ObjAt(c1, 0x8)) {
                if (show == 0) {
                    U8At(c1, 0x18) &= 0xFE;
                } else {
                    U8At(c1, 0x18) |= 1;
                }

                for (CMapObj* c2 = ObjAt(c1, 0x4); c2 != 0; c2 = ObjAt(c2, 0x8)) {
                    if (show == 0) {
                        U8At(c2, 0x18) &= 0xFE;
                    } else {
                        U8At(c2, 0x18) |= 1;
                    }

                    for (CMapObj* c3 = ObjAt(c2, 0x4); c3 != 0; c3 = ObjAt(c3, 0x8)) {
                        if (show == 0) {
                            U8At(c3, 0x18) &= 0xFE;
                        } else {
                            U8At(c3, 0x18) |= 1;
                        }

                        for (CMapObj* c4 = ObjAt(c3, 0x4); c4 != 0; c4 = ObjAt(c4, 0x8)) {
                            if (show == 0) {
                                U8At(c4, 0x18) &= 0xFE;
                            } else {
                                U8At(c4, 0x18) |= 1;
                            }

                            for (CMapObj* c5 = ObjAt(c4, 0x4); c5 != 0; c5 = ObjAt(c5, 0x8)) {
                                if (show == 0) {
                                    U8At(c5, 0x18) &= 0xFE;
                                } else {
                                    U8At(c5, 0x18) |= 1;
                                }

                                for (CMapObj* c6 = ObjAt(c5, 0x4); c6 != 0; c6 = ObjAt(c6, 0x8)) {
                                    if (show == 0) {
                                        U8At(c6, 0x18) &= 0xFE;
                                    } else {
                                        U8At(c6, 0x18) |= 1;
                                    }

                                    for (CMapObj* c7 = ObjAt(c6, 0x4); c7 != 0; c7 = ObjAt(c7, 0x8)) {
                                        if (show == 0) {
                                            U8At(c7, 0x18) &= 0xFE;
                                        } else {
                                            U8At(c7, 0x18) |= 1;
                                        }

                                        if (ObjAt(c7, 0x4) != 0) {
                                            ObjAt(c7, 0x4)->SetShow_r(show);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        root = ObjAt(root, 0x8);
    } while (root != 0);
}

/*
 * --INFO--
 * PAL Address: 0x80029FB8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow(int show)
{
    if (show == 0) {
        U8At(this, 0x18) &= 0xFE;
    } else {
        U8At(this, 0x18) |= 1;
    }

    if (ObjAt(this, 0x4) != 0) {
        ObjAt(this, 0x4)->SetShow_r(show);
    }
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

    if (target > *reinterpret_cast<int*>(mime + 0x28)) {
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
