#include "ffcc/math.h"

#include "dolphin/mtx.h"
#include "math.h"
#include "string.h"

extern "C" int rand(void);
extern "C" int __cntlzw(unsigned int);

CMath math;
static Vec s_f_vpos;
static Mtx s_f_lvmtx;

struct Vec4d {
    float x;
    float y;
    float z;
    float w;
};

extern void* __vt__8CManager[];
extern void* __vt__5CMath[];

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
    volatile void** base = (volatile void**)&math;
    *base = __vt__8CManager;
    *base = __vt__5CMath;
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
 * PAL Address: 0x8001c124
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::SRTToMatrix(float (*out)[4], SRT* srt)
{
    float* const s = reinterpret_cast<float*>(srt);
    Mtx rot;

    PSMTXScale(out, s[6], s[7], s[8]);

    const double sx = (double)(float)sin((double)s[3]);
    const double cx = (double)(float)cos((double)s[3]);
    const double sy = (double)(float)sin((double)s[4]);
    const double cy = (double)(float)cos((double)s[4]);
    const double sz = (double)(float)sin((double)s[5]);
    const double cz = (double)(float)cos((double)s[5]);

    rot[1][0] = (float)(cy * sz);
    rot[2][0] = (float)-sy;
    rot[0][0] = (float)(cy * cz);
    rot[0][1] = (float)(cz * (double)(float)(sx * sy) - (double)(float)(cx * sz));
    rot[1][1] = (float)(sz * (double)(float)(sx * sy) + (double)(float)(cx * cz));
    rot[2][1] = (float)(sx * cy);
    rot[2][2] = (float)(cx * cy);
    rot[0][2] = (float)(cz * (double)(float)(cx * sy) + (double)(float)(sx * sz));
    rot[1][2] = (float)(sz * (double)(float)(cx * sy) - (double)(float)(sx * cz));
    rot[0][3] = s[0];
    rot[1][3] = s[1];
    rot[2][3] = s[2];

    PSMTXConcat(rot, out, out);
}

/*
 * --INFO--
 * PAL Address: 0x8001bfe0
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::SRTToMatrixRT(float (*out)[4], SRT* srt)
{
    float* const s = reinterpret_cast<float*>(srt);

    const double sx = (double)(float)sin((double)s[3]);
    const double cx = (double)(float)cos((double)s[3]);
    const double sy = (double)(float)sin((double)s[4]);
    const double cy = (double)(float)cos((double)s[4]);
    const double sz = (double)(float)sin((double)s[5]);
    const double cz = (double)(float)cos((double)s[5]);

    out[0][0] = (float)(cy * cz);
    out[1][0] = (float)(cy * sz);
    out[2][0] = (float)-sy;
    out[0][1] = (float)(cz * (double)(float)(sx * sy) - (double)(float)(cx * sz));
    out[1][1] = (float)(sz * (double)(float)(sx * sy) + (double)(float)(cx * cz));
    out[2][1] = (float)(sx * cy);
    out[0][2] = (float)(cz * (double)(float)(cx * sy) + (double)(float)(sx * sz));
    out[1][2] = (float)(sz * (double)(float)(cx * sy) - (double)(float)(sx * cz));
    out[2][2] = (float)(cx * cy);
    out[0][3] = s[0];
    out[1][3] = s[1];
    out[2][3] = s[2];
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
    float fVar1;
    float fVar2;
    unsigned int uVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar6;
    unsigned int uVar7;
    int iVar8;
    double dVar9;
    double dVar10;
    float* param_1 = reinterpret_cast<float*>(this);
    float* param_2 = reinterpret_cast<float*>(&outBound);
    Vec local_48;
    Vec local_3c;

    fVar2 = -3.40282347e38f;
    fVar1 = 3.40282347e38f;
    param_2[2] = 3.40282347e38f;
    param_2[1] = fVar1;
    *param_2 = fVar1;
    param_2[5] = fVar2;
    param_2[4] = fVar2;
    param_2[3] = fVar2;
    if ((((param_1[3] < s_f_vpos.x) || (param_1[4] < s_f_vpos.y)) || (param_1[5] < s_f_vpos.z)) ||
        ((s_f_vpos.x < *param_1 || (s_f_vpos.y < param_1[1])) || (s_f_vpos.z < param_1[2]))) {
        dVar10 = (double)0.0f;
        uVar5 = 0xF;
        uVar7 = 0;
        iVar8 = 0;
        do {
            if (iVar8 == 0) {
                local_3c.x = *param_1;
            } else {
                local_3c.x = param_1[3];
            }
            iVar6 = 0;
            do {
                if (iVar6 == 0) {
                    local_3c.y = param_1[1];
                } else {
                    local_3c.y = param_1[4];
                }
                iVar4 = 0;
                do {
                    if (iVar4 == 0) {
                        local_3c.z = param_1[2];
                    } else {
                        local_3c.z = param_1[5];
                    }
                    PSMTXMultVec(s_f_lvmtx, &local_3c, &local_48);
                    fVar1 = local_48.x;
                    if (*param_2 < local_48.x) {
                        fVar1 = *param_2;
                    }
                    *param_2 = fVar1;
                    fVar1 = local_48.y;
                    if (param_2[1] < local_48.y) {
                        fVar1 = param_2[1];
                    }
                    param_2[1] = fVar1;
                    fVar1 = local_48.z;
                    if (param_2[2] < local_48.z) {
                        fVar1 = param_2[2];
                    }
                    param_2[2] = fVar1;
                    fVar1 = local_48.x;
                    if (local_48.x < param_2[3]) {
                        fVar1 = param_2[3];
                    }
                    param_2[3] = fVar1;
                    fVar1 = local_48.y;
                    if (local_48.y < param_2[4]) {
                        fVar1 = param_2[4];
                    }
                    param_2[4] = fVar1;
                    fVar1 = local_48.z;
                    if (local_48.z < param_2[5]) {
                        fVar1 = param_2[5];
                    }
                    param_2[5] = fVar1;
                    dVar9 = (double)local_48.z;
                    if (dVar9 <= dVar10) {
                        if ((double)local_48.x <= -dVar9) {
                            if (dVar9 <= (double)local_48.x) {
                                uVar3 = 0;
                            } else {
                                uVar3 = 2;
                            }
                        } else {
                            uVar3 = 1;
                        }
                        if ((double)local_48.y <= -dVar9) {
                            if ((double)local_48.y < dVar9) {
                                uVar3 = uVar3 | 8;
                            }
                        } else {
                            uVar3 = uVar3 | 4;
                        }
                    } else {
                        if ((double)local_48.x <= -dVar9) {
                            if (dVar9 <= (double)local_48.x) {
                                uVar3 = 0x10;
                            } else {
                                uVar3 = 0x12;
                            }
                        } else {
                            uVar3 = 0x11;
                        }
                        if ((double)local_48.y <= -dVar9) {
                            if ((double)local_48.y < dVar9) {
                                uVar3 = uVar3 | 0x18;
                            }
                        } else {
                            uVar3 = uVar3 | 0x14;
                        }
                    }
                    iVar4 = iVar4 + 1;
                    uVar5 = uVar5 & uVar3;
                    uVar7 = uVar7 | uVar3;
                } while (iVar4 < 2);
                iVar6 = iVar6 + 1;
            } while (iVar6 < 2);
            iVar8 = iVar8 + 1;
        } while (iVar8 < 2);
        if (uVar5 == 0) {
            uVar5 = (unsigned int)__cntlzw(uVar7);
            iVar8 = (int)(uVar5 >> 5) + 1;
        } else {
            iVar8 = 0;
        }
    } else {
        iVar8 = 0;
        do {
            if (iVar8 == 0) {
                local_3c.x = *param_1;
            } else {
                local_3c.x = param_1[3];
            }
            iVar6 = 0;
            do {
                if (iVar6 == 0) {
                    local_3c.y = param_1[1];
                } else {
                    local_3c.y = param_1[4];
                }
                iVar4 = 0;
                do {
                    if (iVar4 == 0) {
                        local_3c.z = param_1[2];
                    } else {
                        local_3c.z = param_1[5];
                    }
                    PSMTXMultVec(s_f_lvmtx, &local_3c, &local_48);
                    fVar1 = local_48.x;
                    if (*param_2 < local_48.x) {
                        fVar1 = *param_2;
                    }
                    *param_2 = fVar1;
                    fVar1 = local_48.y;
                    if (param_2[1] < local_48.y) {
                        fVar1 = param_2[1];
                    }
                    param_2[1] = fVar1;
                    fVar1 = local_48.z;
                    if (param_2[2] < local_48.z) {
                        fVar1 = param_2[2];
                    }
                    param_2[2] = fVar1;
                    fVar1 = local_48.x;
                    if (local_48.x < param_2[3]) {
                        fVar1 = param_2[3];
                    }
                    param_2[3] = fVar1;
                    fVar1 = local_48.y;
                    if (local_48.y < param_2[4]) {
                        fVar1 = param_2[4];
                    }
                    param_2[4] = fVar1;
                    fVar1 = local_48.z;
                    if (local_48.z < param_2[5]) {
                        fVar1 = param_2[5];
                    }
                    iVar4 = iVar4 + 1;
                    param_2[5] = fVar1;
                } while (iVar4 < 2);
                iVar6 = iVar6 + 1;
            } while (iVar6 < 2);
            iVar8 = iVar8 + 1;
        } while (iVar8 < 2);
        iVar8 = 1;
    }
    return iVar8;
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
    unsigned int uVar1;
    int iVar2;
    unsigned int uVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar6;
    double dVar7;
    double dVar8;
    double dVar9;
    float* param_1 = reinterpret_cast<float*>(this);
    Vec local_48;
    Vec local_3c;

    if ((((param_1[3] < s_f_vpos.x) || (param_1[4] < s_f_vpos.y)) || (param_1[5] < s_f_vpos.z)) ||
        ((s_f_vpos.x < *param_1 || (s_f_vpos.y < param_1[1])) || (s_f_vpos.z < param_1[2]))) {
        dVar8 = (double)-3.40282347e38f;
        dVar9 = (double)0.0f;
        uVar3 = 0xF;
        uVar5 = 0;
        iVar6 = 0;
        do {
            if (iVar6 == 0) {
                local_3c.x = *param_1;
            } else {
                local_3c.x = param_1[3];
            }
            iVar4 = 0;
            do {
                if (iVar4 == 0) {
                    local_3c.y = param_1[1];
                } else {
                    local_3c.y = param_1[4];
                }
                iVar2 = 0;
                do {
                    if (iVar2 == 0) {
                        local_3c.z = param_1[2];
                    } else {
                        local_3c.z = param_1[5];
                    }
                    PSMTXMultVec(s_f_lvmtx, &local_3c, &local_48);
                    dVar7 = (double)local_48.z;
                    if (dVar8 < dVar7) {
                        dVar8 = dVar7;
                    }
                    if (dVar7 <= dVar9) {
                        if ((double)local_48.x <= -dVar7) {
                            if (dVar7 <= (double)local_48.x) {
                                uVar1 = 0;
                            } else {
                                uVar1 = 2;
                            }
                        } else {
                            uVar1 = 1;
                        }
                        if ((double)local_48.y <= -dVar7) {
                            if ((double)local_48.y < dVar7) {
                                uVar1 = uVar1 | 8;
                            }
                        } else {
                            uVar1 = uVar1 | 4;
                        }
                    } else {
                        if ((double)local_48.x <= -dVar7) {
                            if (dVar7 <= (double)local_48.x) {
                                uVar1 = 0x10;
                            } else {
                                uVar1 = 0x12;
                            }
                        } else {
                            uVar1 = 0x11;
                        }
                        if ((double)local_48.y <= -dVar7) {
                            if ((double)local_48.y < dVar7) {
                                uVar1 = uVar1 | 0x18;
                            }
                        } else {
                            uVar1 = uVar1 | 0x14;
                        }
                    }
                    iVar2 = iVar2 + 1;
                    uVar3 = uVar3 & uVar1;
                    uVar5 = uVar5 | uVar1;
                } while (iVar2 < 2);
                iVar4 = iVar4 + 1;
            } while (iVar4 < 2);
            iVar6 = iVar6 + 1;
        } while (iVar6 < 2);
        if ((double)farPlane <= dVar8) {
            if (uVar3 == 0) {
                uVar3 = (unsigned int)__cntlzw(uVar5);
                iVar6 = (int)(uVar3 >> 5) + 1;
            } else {
                iVar6 = 0;
            }
        } else {
            iVar6 = 0;
        }
    } else {
        iVar6 = 1;
    }
    return iVar6;
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
 * PAL Address: 0x8001a230
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::MTX44MultVec4(float (*mtx)[4], Vec* src, Vec4d* dst)
{
    const float x = src->x;
    const float y = src->y;
    const float z = src->z;

    const float m10 = mtx[1][0];
    const float m11 = mtx[1][1];
    const float m12 = mtx[1][2];
    const float m13 = mtx[1][3];
    const float m20 = mtx[2][0];
    const float m21 = mtx[2][1];
    const float m22 = mtx[2][2];
    const float m23 = mtx[2][3];
    const float m30 = mtx[3][0];
    const float m31 = mtx[3][1];
    const float m32 = mtx[3][2];
    const float m33 = mtx[3][3];

    dst->x = z * mtx[0][2] + x * mtx[0][0] + mtx[0][3] + y * mtx[0][1];
    dst->y = z * m12 + x * m10 + m13 + y * m11;
    dst->z = z * m22 + x * m20 + m23 + y * m21;
    dst->w = z * m32 + x * m30 + m33 + y * m31;
}

/*
 * --INFO--
 * PAL Address: 0x8001a294
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::MTX44MultVec4(float (*mtx)[4], Vec4d* src, Vec4d* dst)
{
    const float x = src->x;
    const float y = src->y;
    const float z = src->z;
    const float w = src->w;

    const float m10 = mtx[1][0];
    const float m11 = mtx[1][1];
    const float m12 = mtx[1][2];
    const float m13 = mtx[1][3];
    const float m20 = mtx[2][0];
    const float m21 = mtx[2][1];
    const float m22 = mtx[2][2];
    const float m23 = mtx[2][3];
    const float m30 = mtx[3][0];
    const float m31 = mtx[3][1];
    const float m32 = mtx[3][2];
    const float m33 = mtx[3][3];

    dst->x = z * mtx[0][2] + x * mtx[0][0] + w * mtx[0][3] + y * mtx[0][1];
    dst->y = z * m12 + x * m10 + w * m13 + y * m11;
    dst->z = z * m22 + x * m20 + w * m23 + y * m21;
    dst->w = z * m32 + x * m30 + w * m33 + y * m31;
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
 * PAL Address: 0x8001b240
 * PAL Size: 772b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMath::CrossCheckSphereVector(Vec* outPos, float* outT, Vec* p0, Vec* p1, Vec* ellipseScale, float scale)
{
    const float sumA = scale + p0->x;
    const float yScale = sumA / (p1->x + p0->x);
    const float radiusSq = sumA * sumA;

    Vec rel;
    PSVECSubtract(p1, ellipseScale, &rel);

    Vec relScaled = rel;
    relScaled.y *= yScale;

    Vec dir;
    dir.x = p0->y;
    dir.y = p0->z * yScale;
    dir.z = p1->z;

    if (PSVECDotProduct(&relScaled, &relScaled) < radiusSq) {
        if (outT != NULL) {
            *outT = 0.0f;
        }
        if (outPos != NULL) {
            *outPos = rel;
        }
    }
    else {
        const float proj = PSVECDotProduct(&dir, &relScaled);
        if (proj > 0.0f) {
            return 0;
        }

        const float dirLenSq = PSVECDotProduct(&dir, &dir);
        const float det = proj * proj - dirLenSq * (PSVECDotProduct(&relScaled, &relScaled) - radiusSq);
        if (det < 0.0f) {
            return 0;
        }

        const float dist = -proj - sqrtf(det);
        if (dist <= 0.0f || dirLenSq < dist) {
            return 0;
        }

        if (outT != NULL) {
            *outT = dist / dirLenSq;
        }
        if (outPos != NULL) {
            Vec offset;
            PSVECScale(&dir, &offset, dist / dirLenSq);
            PSVECAdd(&rel, &offset, outPos);
        }
    }

    if (outPos != NULL) {
        PSVECSubtract(outPos, &rel, outPos);
        outPos->y /= yScale;
        PSVECAdd(outPos, p1, outPos);
    }
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8001b020
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMath::CrossCheckEllipseCapsule(Vec* outCoeffs, float* outCoeffScalar, Vec* p0, Vec* p1, float radius, Vec* p2,
                                     float scaleA, float scaleB)
{
    const float r2 = radius * radius;
    Vec4d coeffs;
    coeffs.w = radius * r2;
    coeffs.z = (2.0f * coeffs.w) - (3.0f * r2);
    coeffs.x = 1.0f + ((3.0f * coeffs.w) - (3.0f * r2));
    coeffs.y = radius - ((3.0f * r2) - coeffs.w);
    coeffs.w = coeffs.w - r2;

    Mtx44 control;
    control[0][0] = p1->x;
    control[1][0] = p1->y;
    control[2][0] = p1->z;
    control[3][0] = 1.0f;
    control[0][2] = p2->x;
    control[1][2] = p2->y;
    control[2][2] = p2->z;
    control[3][2] = 1.0f;

    float t0 = 0.0f;
    if (scaleA + radius != 0.0f) {
        t0 = scaleA / (scaleA + radius);
    }

    Vec tangent;
    Vec tmp;
    PSVECSubtract(p2, p1, &tangent);
    PSVECSubtract(p1, p0, &tmp);
    PSVECAdd(&tangent, &tmp, &tangent);
    PSVECScale(&tangent, &tangent, t0 * scaleA);
    control[0][1] = tangent.x;
    control[1][1] = tangent.y;
    control[2][1] = tangent.z;
    control[3][1] = 1.0f;

    float t1 = 0.0f;
    if (scaleA + scaleB != 0.0f) {
        t1 = scaleA / (scaleA + scaleB);
    }

    PSVECSubtract(outCoeffs, p2, &tangent);
    PSVECSubtract(p2, p1, &tmp);
    PSVECAdd(&tangent, &tmp, &tangent);
    PSVECScale(&tangent, &tangent, t1 * scaleA);
    control[0][3] = tangent.x;
    control[1][3] = tangent.y;
    control[2][3] = tangent.z;
    control[3][3] = 1.0f;

    MTX44MultVec4(control, &coeffs, &coeffs);
    outCoeffScalar[0] = coeffs.x;
    outCoeffScalar[1] = coeffs.y;
    outCoeffScalar[2] = coeffs.z;
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
 * PAL Address: 0x8001a62c
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::Spline1D(int lastIndex, float t, float* x, float* y, float* secondDerivatives)
{
    float period = x[lastIndex] - x[0];

    while (x[lastIndex] < t) {
        t -= period;
    }

    while (t < x[0]) {
        t += period;
    }

    int low = 0;
    int high = lastIndex;
    while (low < high) {
        int mid = (low + high) / 2;
        if (x[mid] < t) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    if (low > 0) {
        low--;
    }

    float sd0 = secondDerivatives[low];
    float dt = t - x[low];
    float dx = x[low + 1] - x[low];

    return dt * (dt * (0.5f * sd0 + (dt * (secondDerivatives[low + 1] - sd0)) / dx) -
                 (dx * (0.33333334f * sd0 + secondDerivatives[low + 1]) -
                  (y[low + 1] - y[low]) / dx)) +
           y[low];
}

/*
 * --INFO--
 * PAL Address: 0x8001a580
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::Line1D(int lastIndex, float x, float* x_arr, float* y_arr)
{
    float period = x_arr[lastIndex] - x_arr[0];

    while (x_arr[lastIndex] < x) {
        x -= period;
    }

    while (x < x_arr[0]) {
        x += period;
    }

    int low = 0;
    int high = lastIndex;
    while (low < high) {
        int mid = (low + high) / 2;
        if (x_arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (low > 0) {
        low--;
    }

    return ((x - x_arr[low]) / (x_arr[low + 1] - x_arr[low])) * (y_arr[low + 1] - y_arr[low]) + y_arr[low];
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
 * PAL Address: 0x8001a2f8
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMath::DstRot(float from, float to)
{
    const float s0 = (float)sin((double)from);
    const float c0 = (float)cos((double)from);
    const float s1 = (float)sin((double)to);
    const float c1 = (float)cos((double)to);
    const float dot = s0 * s1 + c0 * c1;
    float angle = 0.0f;

    if (angle != dot) {
        angle = -1.0f;
        if (angle <= dot) {
            angle = dot;
            if (1.0f < dot) {
                angle = 1.0f;
            }
        }
        angle = (float)acos((double)angle);
        if (s0 * c1 - s1 * c0 < 0.0f) {
            angle = -angle;
        }
    }

    return angle;
}
