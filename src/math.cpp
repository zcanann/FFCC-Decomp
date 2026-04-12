#include "ffcc/math.h"

#include "dolphin/mtx.h"
#include "math.h"
#include "string.h"

extern "C" int rand(void);
extern "C" float kZeroF;
extern "C" float kNegOneF;
extern "C" double DOUBLE_8032F778;
extern "C" float FLOAT_8032F780;
extern "C" float FLOAT_8032F788;
extern "C" float FLOAT_8032F748;
extern "C" float FLOAT_8032F758;
extern "C" float FLOAT_8032F75C;
extern "C" float kRandSignedScaleF;
extern "C" float kRandScaleF;

CMath Math;
static Vec s_f_vpos;
static Mtx s_f_lvmtx;
static float s_hSpline[128];
static float s_wSpline[128];
static float s_dSpline[128];

struct Vec4d {
    float x;
    float y;
    float z;
    float w;
};

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
	PSMTXIdentity(m_localMtx);
	memset(m_scratch, 0, sizeof(m_scratch));
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
    float* s = reinterpret_cast<float*>(srt);
    Mtx rot;
    float sx;
    float cx;
    float sy;
    float cy;
    float sz;
    float cz;

    PSMTXScale(out, s[6], s[7], s[8]);
    sx = (float)sin((double)s[3]);
    cx = (float)cos((double)s[3]);
    sy = (float)sin((double)s[4]);
    cy = (float)cos((double)s[4]);
    sz = (float)sin((double)s[5]);
    cz = (float)cos((double)s[5]);

    rot[1][0] = cy * sz;
    rot[2][0] = -sy;
    rot[0][0] = cy * cz;
    rot[0][1] = cz * (sx * sy) - (cx * sz);
    rot[1][1] = sz * (sx * sy) + (cx * cz);
    rot[2][1] = sx * cy;
    rot[2][2] = cx * cy;
    rot[0][2] = cz * (cx * sy) + (sx * sz);
    rot[1][2] = sz * (cx * sy) - (sx * cz);
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
    float sinX;
    float cosX;
    float sinY;
    float cosY;
    float sinZ;
    float cosZ;
    float* matrix = &out[0][0];
    float* values = reinterpret_cast<float*>(srt);

    sinX = (float)sin((double)values[3]);
    cosX = (float)cos((double)values[3]);
    sinY = (float)sin((double)values[4]);
    cosY = (float)cos((double)values[4]);
    sinZ = (float)sin((double)values[5]);
    cosZ = (float)cos((double)values[5]);

    matrix[0] = cosY * cosZ;
    matrix[4] = cosY * sinZ;
    matrix[8] = -sinY;
    matrix[1] = cosZ * sinX * sinY - cosX * sinZ;
    matrix[5] = sinZ * sinX * sinY + cosX * cosZ;
    matrix[9] = sinX * cosY;
    matrix[2] = cosZ * cosX * sinY + sinX * sinZ;
    matrix[6] = sinZ * cosX * sinY - sinX * cosZ;
    matrix[10] = cosX * cosY;
    matrix[3] = values[0];
    matrix[7] = values[1];
    matrix[11] = values[2];
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
    if (kZeroF == scale) {
        return kZeroF;
    }

    return scale * ((float)rand() * kRandScaleF);
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
    return (float)rand() * kRandScaleF;
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
    unsigned int quotient = value / max;
    return (int)(value - quotient * max);
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
    if (kZeroF == scale) {
        return kZeroF;
    }

    return scale * (((float)rand() * kRandSignedScaleF) + kNegOneF);
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
    if (!((s_f_vpos.x <= param_1[3] && s_f_vpos.y <= param_1[4] && s_f_vpos.z <= param_1[5]) &&
          (*param_1 <= s_f_vpos.x && param_1[1] <= s_f_vpos.y && param_1[2] <= s_f_vpos.z))) {
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

    if ((param_1[3] >= s_f_vpos.x) && (param_1[4] >= s_f_vpos.y) && (param_1[5] >= s_f_vpos.z) &&
        (s_f_vpos.x >= *param_1) && (s_f_vpos.y >= param_1[1]) && (s_f_vpos.z >= param_1[2])) {
        return 1;
    }

    dVar8 = (double)FLOAT_8032F780;
    dVar9 = (double)kZeroF;
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
extern "C" asm void MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(register void* self, register float (*mtx)[4], register Vec* src,
                                                              register Vec4d* dst) {
    nofralloc
    psq_l f0, 0x0(src), 0, 0
    psq_l f1, 0x8(src), 1, 0
    psq_l f2, 0x0(mtx), 0, 0
    psq_l f3, 0x8(mtx), 0, 0
    ps_mul f12, f0, f2
    psq_l f4, 0x10(mtx), 0, 0
    ps_madd f13, f1, f3, f12
    psq_l f5, 0x18(mtx), 0, 0
    ps_sum0 f2, f13, f13, f13
    psq_l f6, 0x20(mtx), 0, 0
    ps_mul f12, f0, f4
    psq_l f7, 0x28(mtx), 0, 0
    ps_madd f13, f1, f5, f12
    psq_l f8, 0x30(mtx), 0, 0
    ps_sum1 f2, f13, f2, f13
    psq_l f9, 0x38(mtx), 0, 0
    psq_st f2, 0x0(dst), 0, 0
    ps_mul f12, f0, f6
    ps_madd f13, f1, f7, f12
    ps_sum0 f2, f13, f13, f13
    ps_mul f12, f0, f8
    ps_madd f13, f1, f9, f12
    ps_sum1 f2, f13, f2, f13
    psq_st f2, 0x8(dst), 0, 0
    blr
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
extern "C" asm void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(register void* self, register float (*mtx)[4],
                                                                register Vec4d* src, register Vec4d* dst) {
    nofralloc
    psq_l f0, 0x0(src), 0, 0
    psq_l f1, 0x8(src), 0, 0
    psq_l f2, 0x0(mtx), 0, 0
    psq_l f3, 0x8(mtx), 0, 0
    ps_mul f12, f0, f2
    psq_l f4, 0x10(mtx), 0, 0
    ps_madd f13, f1, f3, f12
    psq_l f5, 0x18(mtx), 0, 0
    ps_sum0 f2, f13, f13, f13
    psq_l f6, 0x20(mtx), 0, 0
    ps_mul f12, f0, f4
    psq_l f7, 0x28(mtx), 0, 0
    ps_madd f13, f1, f5, f12
    psq_l f8, 0x30(mtx), 0, 0
    ps_sum1 f2, f13, f2, f13
    psq_l f9, 0x38(mtx), 0, 0
    psq_st f2, 0x0(dst), 0, 0
    ps_mul f12, f0, f6
    ps_madd f13, f1, f7, f12
    ps_sum0 f2, f13, f13, f13
    ps_mul f12, f0, f8
    ps_madd f13, f1, f9, f12
    ps_sum1 f2, f13, f2, f13
    psq_st f2, 0x8(dst), 0, 0
    blr
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
    if ((double)PSVECDotProduct(&xAxis, &temp) < DOUBLE_8032F778) {
        PSVECScale(outScale, outScale, kNegOneF);
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
extern "C" int CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf(
    CMath* math, Vec* outPos, float* outT, Vec* origin, Vec* vector, Vec* ellipseScale, float scale,
    float innerRadius, float outerRadius)
{
    (void)math;

    bool hit;
    Vec local_60;
    Vec local_6c;
    Vec local_78;
    Vec local_84;
    float scaledInner = innerRadius + scale;
    float scaleY = scaledInner / (outerRadius + scale);
    float scaleSq = scaledInner * scaledInner;
    float dot;
    float proj;
    float lenSq;
    float discriminant;
    float root;

    PSVECSubtract(origin, ellipseScale, &local_60);
    local_78.y = local_60.y * scaleY;
    local_6c.x = vector->x;
    local_6c.y = vector->y * scaleY;
    local_6c.z = vector->z;
    local_78.x = local_60.x;
    local_78.z = local_60.z;
    local_60.y = local_78.y;
    dot = PSVECDotProduct(&local_78, &local_78);
    if (dot < scaleSq) {
        if (outT != NULL) {
            *outT = 0.0f;
        }
        if (outPos != NULL) {
            outPos->x = local_60.x;
            outPos->y = local_60.y;
            outPos->z = local_60.z;
        }
        hit = true;
    } else {
        proj = PSVECDotProduct(&local_6c, &local_78);
        if (0.0f < proj) {
            hit = false;
        } else {
            lenSq = PSVECDotProduct(&local_6c, &local_6c);
            discriminant = proj * proj - lenSq * (dot - scaleSq);
            if (discriminant < 0.0f) {
                hit = false;
            } else {
                root = -proj - sqrtf(discriminant);
                if ((root <= 0.0f) || (lenSq < root)) {
                    hit = false;
                } else {
                    if (outT != NULL) {
                        *outT = root / lenSq;
                    }
                    if (outPos != NULL) {
                        PSVECScale(&local_6c, &local_84, root / lenSq);
                        PSVECAdd(&local_60, &local_84, outPos);
                    }
                    hit = true;
                }
            }
        }
    }

    if (hit) {
        if (outPos != NULL) {
            PSVECSubtract(outPos, &local_60, outPos);
            outPos->y = outPos->y / scaleY;
            PSVECAdd(outPos, origin, outPos);
        }
        return 1;
    }

    return 0;
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
    int i;
    for (i = 0; i < count; ++i) {
        s_hSpline[i] = x[i + 1] - x[i];
        s_wSpline[i] = (y[i + 1] - y[i]) / s_hSpline[i];
    }
    s_wSpline[count] = s_wSpline[0];

    for (i = 1; i < count; ++i) {
        s_dSpline[i] = 2.0f * (x[i + 1] - x[i - 1]);
    }
    s_dSpline[count] = 2.0f * (s_hSpline[count - 1] + s_hSpline[0]);

    for (i = 1; i <= count; ++i) {
        outSecondDerivatives[i] = s_wSpline[i] - s_wSpline[i - 1];
    }

    s_wSpline[0] = s_hSpline[0];
    s_wSpline[count] = s_dSpline[count];
    for (i = 1; i < count; ++i) {
        s_wSpline[i] = 0.0f;
    }

    for (i = 1; i < count; ++i) {
        float r = s_hSpline[i] / s_dSpline[i];
        outSecondDerivatives[i + 1] = -(r * outSecondDerivatives[i] - outSecondDerivatives[i + 1]);
        s_dSpline[i + 1] = -(r * s_hSpline[i] - s_dSpline[i + 1]);
        s_wSpline[i + 1] = -(r * s_wSpline[i] - s_wSpline[i + 1]);
    }

    s_wSpline[0] = s_wSpline[count];
    outSecondDerivatives[0] = outSecondDerivatives[count];
    for (i = count - 1; i >= 1; --i) {
        float r = s_wSpline[i + 1] / s_dSpline[i + 1];
        outSecondDerivatives[i] = -(r * outSecondDerivatives[i + 1] - outSecondDerivatives[i]);
        s_dSpline[i] = -(r * s_dSpline[i + 1] - s_dSpline[i]);
    }

    outSecondDerivatives[0] /= s_wSpline[0];
    outSecondDerivatives[count] = outSecondDerivatives[0];
    for (i = 1; i < count; ++i) {
        outSecondDerivatives[i] =
            -(outSecondDerivatives[0] * s_wSpline[i] - outSecondDerivatives[i]) / s_dSpline[i];
    }
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

    return dt * (dt * (FLOAT_8032F758 * sd0 + (dt * (secondDerivatives[low + 1] - sd0)) / dx) +
                 -(dx * (FLOAT_8032F75C * sd0 + secondDerivatives[low + 1]) -
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

    while (x > x_arr[lastIndex]) {
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
    int satScaled = saturation * 0xFF;
    int sat = satScaled / 100 + (satScaled >> 31);

    int valScaled = brightness * 0xFF;
    int val = valScaled / 100 + (valScaled >> 31);

    unsigned char rgba[4];
    if ((float)sat == 0.0f) {
        rgba[0] = (unsigned char)val;
        rgba[1] = (unsigned char)val;
        rgba[2] = (unsigned char)val;
    } else {
        int low = (0xFF - sat) * val;
        low = low / 0xFF + (low >> 31);
        int sector = hue / 0x3C + (hue >> 31);
        int delta;

        low -= low >> 31;
        sector -= sector >> 31;
        delta = (hue - sector * 0x3C) * (val - low);
        delta = delta / 0x3C + (delta >> 31);

        if (hue < 60) {
            rgba[0] = (unsigned char)val;
            rgba[1] = (unsigned char)(low + delta);
            rgba[2] = (unsigned char)low;
        } else if (hue < 120) {
            rgba[0] = (unsigned char)(val - delta);
            rgba[1] = (unsigned char)val;
            rgba[2] = (unsigned char)low;
        } else if (hue < 180) {
            rgba[0] = (unsigned char)low;
            rgba[1] = (unsigned char)val;
            rgba[2] = (unsigned char)(low + delta);
        } else if (hue < 240) {
            rgba[0] = (unsigned char)low;
            rgba[1] = (unsigned char)(val - delta);
            rgba[2] = (unsigned char)val;
        } else if (hue < 300) {
            rgba[0] = (unsigned char)(low + delta);
            rgba[1] = (unsigned char)low;
            rgba[2] = (unsigned char)val;
        } else if (hue < 360) {
            rgba[0] = (unsigned char)val;
            rgba[1] = (unsigned char)low;
            rgba[2] = (unsigned char)(val - delta);
        } else {
            rgba[0] = 0;
            rgba[1] = 0;
            rgba[2] = 0;
        }
    }

    rgba[3] = 0xFF;
    return *(unsigned int*)rgba;
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

    if (dot == 0.0f) {
        return 0.0f;
    }

    float clamped;
    if (dot < -1.0f) {
        clamped = -1.0f;
    } else {
        if (FLOAT_8032F748 < dot) {
            clamped = FLOAT_8032F748;
        } else {
            clamped = dot;
        }
    }

    float angle = (float)acos((double)clamped);
    if (s0 * c1 - s1 * c0 < 0.0f) {
        angle = -angle;
    }

    return angle;
}
