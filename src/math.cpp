#include "ffcc/math.h"

#include "dolphin/mtx.h"
#include "math.h"
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
 * PAL Address: 0x8001a708
 * PAL Size: 2328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::MakeSpline1Dtable(int count, float* x, float* y, float* outSecondDerivatives)
{
    if (count <= 0) {
        return;
    }

    const int n = count;
    float* h = new float[n];
    float* slope = new float[n];
    float* matrix = new float[n * n];
    float* rhs = new float[n];

    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
        slope[i] = (y[i + 1] - y[i]) / h[i];
    }

    memset(matrix, 0, sizeof(float) * n * n);
    for (int i = 0; i < n; ++i) {
        const int prev = (i + n - 1) % n;
        const int next = (i + 1) % n;
        matrix[i * n + prev] = h[prev];
        matrix[i * n + i] = 2.0f * (h[prev] + h[i]);
        matrix[i * n + next] = h[i];
        rhs[i] = 6.0f * (slope[i] - slope[prev]);
    }

    for (int col = 0; col < n; ++col) {
        int pivotRow = col;
        float pivotAbs = fabsf(matrix[col * n + col]);
        for (int row = col + 1; row < n; ++row) {
            const float candAbs = fabsf(matrix[row * n + col]);
            if (pivotAbs < candAbs) {
                pivotAbs = candAbs;
                pivotRow = row;
            }
        }

        if (pivotRow != col) {
            for (int k = col; k < n; ++k) {
                const float tmp = matrix[col * n + k];
                matrix[col * n + k] = matrix[pivotRow * n + k];
                matrix[pivotRow * n + k] = tmp;
            }
            const float tmpRhs = rhs[col];
            rhs[col] = rhs[pivotRow];
            rhs[pivotRow] = tmpRhs;
        }

        const float pivot = matrix[col * n + col];
        for (int row = col + 1; row < n; ++row) {
            const float scale = matrix[row * n + col] / pivot;
            matrix[row * n + col] = 0.0f;
            for (int k = col + 1; k < n; ++k) {
                matrix[row * n + k] -= scale * matrix[col * n + k];
            }
            rhs[row] -= scale * rhs[col];
        }
    }

    for (int row = n - 1; row >= 0; --row) {
        float value = rhs[row];
        for (int col = row + 1; col < n; ++col) {
            value -= matrix[row * n + col] * outSecondDerivatives[col];
        }
        outSecondDerivatives[row] = value / matrix[row * n + row];
    }
    outSecondDerivatives[n] = outSecondDerivatives[0];

    delete[] rhs;
    delete[] matrix;
    delete[] slope;
    delete[] h;
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
