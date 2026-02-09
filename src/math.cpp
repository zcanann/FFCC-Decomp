#include "ffcc/math.h"

#include "dolphin/mtx.h"
#include "string.h"

CMath math;

extern void* __vt__8CManager;
extern void* __vt__5CMath;

/*
 * --INFO--
 * PAL Address: 0x8001c2d0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_math_cpp()
{
    char* const base = reinterpret_cast<char*>(&math);
    *reinterpret_cast<void**>(base) = &__vt__8CManager;
    *reinterpret_cast<void**>(base) = &__vt__5CMath;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void VECMultAdd(Vec*, Vec*, Vec*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMath::CMath()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8001c290
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::Init()
{
	PSMTXIdentity((MtxPtr)((char*)this + 4));
	memset((char*)this + 0x34, 0, 0x30);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::rotateToMatrix(float (*) [4], Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::SRTToMatrix(float (*) [4], SRT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::SRTToMatrixRT(float (*) [4], SRT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::Rand(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::RandF(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::RandF()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::RandPM(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::RandFPM(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CBound::SetFrustum(Vec&, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CBound::CheckFrustum0(CBound&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CBound::CheckFrustum0(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CBound::CheckFrustum(Vec&, float (*) [4], float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::MTX44MultVec4(float (*) [4], Vec*, Vec4d*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::MTX44MultVec4(float (*) [4], Vec4d*, Vec4d*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::MTXGetScale(float (*) [4], Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::CrossCheckSphereVector(Vec*, float*, Vec*, Vec*, Vec*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::CrossCheckEllipseCapsule(Vec*, float*, Vec*, Vec*, float, Vec*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::CalcSpline(Vec*, Vec*, Vec*, Vec*, Vec*, float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::MakeSpline1Dtable(int, float*, float*, float*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::Spline1D(int, float, float*, float*, float*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::Line1D(int, float, float*, float*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::Hsb2Rgb(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMath::DstRot(float, float)
{
	// TODO
}
