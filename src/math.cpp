#include "ffcc/math.h"

#include "dolphin/mtx.h"
#include "math.h"
#include "string.h"

extern "C" int rand(void);
extern "C" int __cntlzw(unsigned int);

CMath math;
static Vec s_f_vpos;
static Mtx s_f_lvmtx;

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
 * PAL Address: 0x8001bf9c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMath::Rand(unsigned long max)
{
    if (max == 0) {
        return 0;
    }

    return rand() % max;
}

/*
 * --INFO--
 * PAL Address: 0x8001bf30
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::RandF(float scale)
{
    if (scale == 0.0f) {
        return 0.0f;
    }

    return scale * ((float)rand() * (1.0f / 32768.0f));
}

/*
 * --INFO--
 * PAL Address: 0x8001beec
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::RandF()
{
    return (float)rand() * (1.0f / 32768.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8001be98
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMath::RandPM(unsigned long max)
{
    unsigned int value;

    if (max == 0) {
        return 0;
    }

    value = (unsigned int)rand() * 0xFFFE - 0x7FFF;
    return (int)(value - (value / max) * max);
}

/*
 * --INFO--
 * PAL Address: 0x8001be28
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::RandFPM(float scale)
{
    if (scale == 0.0f) {
        return 0.0f;
    }

    return scale * (((float)rand() * (2.0f / 32768.0f)) - 1.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8001bdd8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CBound::SetFrustum(Vec& viewPos, float (*viewMatrix)[4])
{
    s_f_vpos.x = viewPos.x;
    s_f_vpos.y = viewPos.y;
    s_f_vpos.z = viewPos.z;
    PSMTXCopy(viewMatrix, s_f_lvmtx);
}

/*
 * --INFO--
 * PAL Address: 0x8001b99c
 * PAL Size: 1084b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CBound::CheckFrustum0(CBound& outBound)
{
    float* const in = reinterpret_cast<float*>(this);
    float* const out = reinterpret_cast<float*>(&outBound);
    Vec inVec;
    Vec outVec;
    out[0] = 3.40282347e38f;
    out[1] = 3.40282347e38f;
    out[2] = 3.40282347e38f;
    out[3] = -3.40282347e38f;
    out[4] = -3.40282347e38f;
    out[5] = -3.40282347e38f;

    if ((in[3] < s_f_vpos.x) || (in[4] < s_f_vpos.y) || (in[5] < s_f_vpos.z) || (s_f_vpos.x < in[0]) || (s_f_vpos.y < in[1]) ||
        (s_f_vpos.z < in[2])) {
        unsigned int andMask = 0xF;
        unsigned int orMask = 0;

        for (int i = 0; i < 2; ++i) {
            inVec.x = in[(i == 0) ? 0 : 3];
            for (int j = 0; j < 2; ++j) {
                inVec.y = in[(j == 0) ? 1 : 4];
                for (int k = 0; k < 2; ++k) {
                    inVec.z = in[(k == 0) ? 2 : 5];
                    PSMTXMultVec(s_f_lvmtx, &inVec, &outVec);

                    if (out[0] < outVec.x) {
                        outVec.x = out[0];
                    }
                    out[0] = outVec.x;
                    if (out[1] < outVec.y) {
                        outVec.y = out[1];
                    }
                    out[1] = outVec.y;
                    if (out[2] < outVec.z) {
                        outVec.z = out[2];
                    }
                    out[2] = outVec.z;

                    if (outVec.x < out[3]) {
                        outVec.x = out[3];
                    }
                    out[3] = outVec.x;
                    if (outVec.y < out[4]) {
                        outVec.y = out[4];
                    }
                    out[4] = outVec.y;
                    if (outVec.z < out[5]) {
                        outVec.z = out[5];
                    }
                    out[5] = outVec.z;

                    const double z = (double)outVec.z;
                    unsigned int code;
                    if (z <= 0.0) {
                        if ((double)outVec.x <= -z) {
                            if (z <= (double)outVec.x) {
                                code = 0;
                            } else {
                                code = 2;
                            }
                        } else {
                            code = 1;
                        }
                        if ((double)outVec.y <= -z) {
                            if ((double)outVec.y < z) {
                                code |= 8;
                            }
                        } else {
                            code |= 4;
                        }
                    } else {
                        if ((double)outVec.x <= -z) {
                            if (z <= (double)outVec.x) {
                                code = 0x10;
                            } else {
                                code = 0x12;
                            }
                        } else {
                            code = 0x11;
                        }
                        if ((double)outVec.y <= -z) {
                            if ((double)outVec.y < z) {
                                code |= 0x18;
                            }
                        } else {
                            code |= 0x14;
                        }
                    }

                    andMask &= code;
                    orMask |= code;
                }
            }
        }

        if (andMask == 0) {
            return ((__cntlzw(orMask) >> 5) + 1);
        }
        return 0;
    }

    for (int i = 0; i < 2; ++i) {
        inVec.x = in[(i == 0) ? 0 : 3];
        for (int j = 0; j < 2; ++j) {
            inVec.y = in[(j == 0) ? 1 : 4];
            for (int k = 0; k < 2; ++k) {
                inVec.z = in[(k == 0) ? 2 : 5];
                PSMTXMultVec(s_f_lvmtx, &inVec, &outVec);

                if (out[0] < outVec.x) {
                    outVec.x = out[0];
                }
                out[0] = outVec.x;
                if (out[1] < outVec.y) {
                    outVec.y = out[1];
                }
                out[1] = outVec.y;
                if (out[2] < outVec.z) {
                    outVec.z = out[2];
                }
                out[2] = outVec.z;

                if (outVec.x < out[3]) {
                    outVec.x = out[3];
                }
                out[3] = outVec.x;
                if (outVec.y < out[4]) {
                    outVec.y = out[4];
                }
                out[4] = outVec.y;
                if (outVec.z < out[5]) {
                    outVec.z = out[5];
                }
                out[5] = outVec.z;
            }
        }
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8001b728
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CBound::CheckFrustum0(float farPlane)
{
    float* const in = reinterpret_cast<float*>(this);
    Vec inVec;
    Vec outVec;

    if ((in[3] < s_f_vpos.x) || (in[4] < s_f_vpos.y) || (in[5] < s_f_vpos.z) || (s_f_vpos.x < in[0]) || (s_f_vpos.y < in[1]) ||
        (s_f_vpos.z < in[2])) {
        double maxZ = -3.40282347e38;
        unsigned int andMask = 0xF;
        unsigned int orMask = 0;

        for (int i = 0; i < 2; ++i) {
            inVec.x = in[(i == 0) ? 0 : 3];
            for (int j = 0; j < 2; ++j) {
                inVec.y = in[(j == 0) ? 1 : 4];
                for (int k = 0; k < 2; ++k) {
                    inVec.z = in[(k == 0) ? 2 : 5];
                    PSMTXMultVec(s_f_lvmtx, &inVec, &outVec);

                    const double z = (double)outVec.z;
                    if (maxZ < z) {
                        maxZ = z;
                    }

                    unsigned int code;
                    if (z <= 0.0) {
                        if ((double)outVec.x <= -z) {
                            if (z <= (double)outVec.x) {
                                code = 0;
                            } else {
                                code = 2;
                            }
                        } else {
                            code = 1;
                        }
                        if ((double)outVec.y <= -z) {
                            if ((double)outVec.y < z) {
                                code |= 8;
                            }
                        } else {
                            code |= 4;
                        }
                    } else {
                        if ((double)outVec.x <= -z) {
                            if (z <= (double)outVec.x) {
                                code = 0x10;
                            } else {
                                code = 0x12;
                            }
                        } else {
                            code = 0x11;
                        }
                        if ((double)outVec.y <= -z) {
                            if ((double)outVec.y < z) {
                                code |= 0x18;
                            }
                        } else {
                            code |= 0x14;
                        }
                    }

                    andMask &= code;
                    orMask |= code;
                }
            }
        }

        if ((double)farPlane <= maxZ) {
            if (andMask == 0) {
                return ((__cntlzw(orMask) >> 5) + 1);
            }
            return 0;
        }
        return 0;
    }
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8001b6ac
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CBound::CheckFrustum(Vec& viewPos, float (*viewMatrix)[4], float farPlane)
{
    s_f_vpos.x = viewPos.x;
    s_f_vpos.y = viewPos.y;
    s_f_vpos.z = viewPos.z;
    PSMTXCopy(viewMatrix, s_f_lvmtx);
    return CheckFrustum0(farPlane);
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
 * PAL Address: 0x8001b544
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::MTXGetScale(float (*mtx)[4], Vec* outScale)
{
    Vec xAxis;
    Vec yAxis;
    Vec zAxis;
    Vec temp;

    xAxis.x = mtx[0][0];
    xAxis.y = mtx[1][0];
    xAxis.z = mtx[2][0];
    yAxis.x = mtx[0][1];
    yAxis.y = mtx[1][1];
    yAxis.z = mtx[2][1];
    zAxis.x = mtx[0][2];
    zAxis.y = mtx[1][2];
    zAxis.z = mtx[2][2];

    outScale->x = PSVECMag(&xAxis);
    PSVECNormalize(&xAxis, &xAxis);

    PSVECScale(&xAxis, &temp, PSVECDotProduct(&xAxis, &yAxis));
    PSVECSubtract(&yAxis, &temp, &yAxis);
    outScale->y = PSVECMag(&yAxis);
    PSVECNormalize(&yAxis, &yAxis);

    PSVECScale(&yAxis, &temp, PSVECDotProduct(&yAxis, &zAxis));
    PSVECSubtract(&zAxis, &temp, &zAxis);
    PSVECScale(&xAxis, &temp, PSVECDotProduct(&xAxis, &zAxis));
    PSVECSubtract(&zAxis, &temp, &zAxis);
    outScale->z = PSVECMag(&zAxis);
    PSVECNormalize(&zAxis, &zAxis);

    PSVECCrossProduct(&yAxis, &zAxis, &temp);
    if (PSVECDotProduct(&xAxis, &temp) < 0.0f) {
        PSVECScale(outScale, outScale, -1.0f);
    }
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
 * PAL Address: 0x8001a3e4
 * PAL Size: 412b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMath::Hsb2Rgb(int hue, int saturation, int brightness)
{
    int sat = (saturation * 0xFF) / 100;
    int val = (brightness * 0xFF) / 100;

    if (sat < 0) {
        sat = -sat;
    }
    if (val < 0) {
        val = -val;
    }

    unsigned char v = (unsigned char)val;
    unsigned int rgba;
    if (sat == 0) {
        rgba = ((unsigned int)v << 24) | ((unsigned int)v << 16) | ((unsigned int)v << 8);
    }
    else {
        int m = ((0xFF - sat) * val) / 0xFF;
        int sector = hue / 60;
        int fraction = (hue - (sector * 60)) * (val - m);
        int x = fraction / 60;

        unsigned char lo = (unsigned char)m;
        unsigned char hi = (unsigned char)val;
        unsigned char midUp = (unsigned char)(m + x);
        unsigned char midDown = (unsigned char)(val - x);

        if (hue < 60) {
            rgba = ((unsigned int)midUp << 24) | ((unsigned int)lo << 16) | ((unsigned int)lo << 8);
        }
        else if (hue < 120) {
            rgba = ((unsigned int)hi << 24) | ((unsigned int)lo << 16) | ((unsigned int)midDown << 8);
        }
        else if (hue < 180) {
            rgba = ((unsigned int)hi << 16) | ((unsigned int)midUp << 8) | (unsigned int)lo;
            rgba <<= 8;
        }
        else if (hue < 240) {
            rgba = ((unsigned int)midDown << 16) | ((unsigned int)hi << 8) | (unsigned int)lo;
            rgba <<= 8;
        }
        else if (hue < 300) {
            rgba = ((unsigned int)lo << 16) | ((unsigned int)hi << 8) | (unsigned int)midUp;
            rgba <<= 8;
        }
        else if (hue < 360) {
            rgba = ((unsigned int)lo << 24) | ((unsigned int)midDown << 16) | ((unsigned int)hi << 8);
        }
        else {
            rgba = 0;
        }
    }

    return rgba | 0xFF;
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
