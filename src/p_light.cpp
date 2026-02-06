#include "ffcc/p_light.h"

#include <dolphin/mtx.h>
#include <dolphin/gx/GXVert.h>
#include <math.h>

#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"

extern "C" void __ct__Q29CLightPcs6CLightFv(void*);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801EA460;

extern unsigned int lbl_801EA298[];
extern unsigned int lbl_801EA2A4[];
extern unsigned int lbl_801EA2B0[];
extern unsigned int lbl_801EA2BC[];
extern unsigned int lbl_801EA2C8[];
extern unsigned int lbl_801EA2D4[];

extern unsigned int DAT_8032fc0c;
extern float FLOAT_8032fc14;
extern float FLOAT_8032fc18;
extern float FLOAT_8032fc1c;
extern float FLOAT_8032fc20;
extern float FLOAT_8032fc24;
extern float FLOAT_8032fc34;
extern float FLOAT_8032fc38;
extern float FLOAT_8032fc3c;
extern float FLOAT_8032fc40;
extern float FLOAT_8032fc44;
extern float FLOAT_8032fc60;
extern double DOUBLE_8032fc48;
extern double DOUBLE_8032fc50;
extern double DOUBLE_8032fc58;
extern double DOUBLE_8032fc68;
extern double DAT_8032ec20;
extern float DAT_801ea430;

extern class CCameraPcs {
public:
    Mtx m_cameraMatrix;
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;

CLightPcs LightPcs;

static inline double U32ToDouble(unsigned int value)
{
    union {
        unsigned long long u;
        double d;
    } conv;

    conv.u = 0x4330000000000000ULL | (unsigned long long)value;
    return conv.d - DOUBLE_8032fc68;
}

/*
 * --INFO--
 * PAL Address: 0x8004a348
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __sinit_p_light_cpp(void)
{
    char* lightBase = reinterpret_cast<char*>(&LightPcs);

    *reinterpret_cast<void**>(lightBase) = &__vt__8CManager;
    *reinterpret_cast<void**>(lightBase) = &lbl_801E8668;
    *reinterpret_cast<void**>(lightBase) = &lbl_801EA460;

    __construct_array(lightBase + 0xbc, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, 0xb0, 8);
    __construct_array(lightBase + 0x63c, (ConstructorDestructor)__ct__Q29CLightPcs6CLightFv, 0, 0xb0, 0x20);
    __construct_array(lightBase + 0x1c3c, (ConstructorDestructor)__ct__Q29CLightPcs10CBumpLightFv, 0, 0x138, 0x20);

    unsigned int a0 = lbl_801EA298[0];
    unsigned int a1 = lbl_801EA298[1];
    unsigned int a2 = lbl_801EA298[2];
    unsigned int b0 = lbl_801EA2A4[0];
    unsigned int b1 = lbl_801EA2A4[1];
    unsigned int b2 = lbl_801EA2A4[2];
    unsigned int c0 = lbl_801EA2B0[0];
    unsigned int c1 = lbl_801EA2B0[1];
    unsigned int c2 = lbl_801EA2B0[2];
    unsigned int d0 = lbl_801EA2BC[0];
    unsigned int d1 = lbl_801EA2BC[1];
    unsigned int d2 = lbl_801EA2BC[2];
    unsigned int e0 = lbl_801EA2C8[0];
    unsigned int e1 = lbl_801EA2C8[1];
    unsigned int e2 = lbl_801EA2C8[2];

    unsigned char* table = reinterpret_cast<unsigned char*>(lbl_801EA2D4);
    *reinterpret_cast<unsigned int*>(table + 0x04) = a0;
    *reinterpret_cast<unsigned int*>(table + 0x08) = a1;
    *reinterpret_cast<unsigned int*>(table + 0x0c) = a2;
    *reinterpret_cast<unsigned int*>(table + 0x10) = b0;
    *reinterpret_cast<unsigned int*>(table + 0x14) = b1;
    *reinterpret_cast<unsigned int*>(table + 0x18) = b2;
    *reinterpret_cast<unsigned int*>(table + 0x1c) = c0;
    *reinterpret_cast<unsigned int*>(table + 0x20) = c1;
    *reinterpret_cast<unsigned int*>(table + 0x24) = c2;
    *reinterpret_cast<unsigned int*>(table + 0x30) = d0;
    *reinterpret_cast<unsigned int*>(table + 0x34) = d1;
    *reinterpret_cast<unsigned int*>(table + 0x38) = d2;
    *reinterpret_cast<unsigned int*>(table + 0x44) = e0;
    *reinterpret_cast<unsigned int*>(table + 0x48) = e1;
    *reinterpret_cast<unsigned int*>(table + 0x4c) = e2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CLightPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::DestroyBumpLightAll(CLightPcs::TARGET)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Clear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::Add(CLightPcs::CLight*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::GetFreeBumpLight(CLightPcs::TARGET)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::AddBump(CLightPcs::CLight*, CLightPcs::TARGET, CMemory::CStage*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetMapColorAlpha(float (*) [4], _GXColor, _GXColor, unsigned char, float, float, float, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetAmbient(_GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetAmbientAlpha(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetNumDiffuse(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetDiffuseColor(unsigned long, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::EnableLight(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetDiffuse(unsigned long, _GXColor, Vec*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetPosition(CLightPcs::TARGET, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setchanctrl(CLightPcs::TARGET, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetBit32(CLightPcs::TARGET, unsigned long*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::SetPart(CLightPcs::TARGET, void*, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::InsertOctTree(CLightPcs::TARGET, COctTree&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80048644
 * PAL Size: 1656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::CBumpLight::MakeLightMap()
{
    if (*(int*)((char*)this + 0xb4) == 0) {
        return;
    }

    _GXColor chanAmb;
    _GXColor chanMat;
    _GXColor chanAmb2;
    _GXColor chanMat2;

    unsigned char u0 = *(unsigned char*)((char*)this + 0x68);
    unsigned char u1 = *(unsigned char*)((char*)this + 0x69);
    unsigned char u2 = *(unsigned char*)((char*)this + 0x6a);
    unsigned char u3 = *(unsigned char*)((char*)this + 0x6b);

    chanAmb.r = u0;
    chanAmb.g = u0;
    chanAmb.b = u0;
    chanAmb.a = u0;
    chanMat.r = u1;
    chanMat.g = u1;
    chanMat.b = u1;
    chanMat.a = u1;
    chanAmb2.r = u2;
    chanAmb2.g = u2;
    chanAmb2.b = u2;
    chanAmb2.a = u2;
    chanMat2.r = u3;
    chanMat2.g = u3;
    chanMat2.b = u3;
    chanMat2.a = u3;

    GXSetChanAmbColor((GXChannelID)0, chanAmb);
    GXSetChanMatColor((GXChannelID)0, chanMat);
    GXSetChanAmbColor((GXChannelID)2, chanAmb2);
    GXSetChanMatColor((GXChannelID)2, chanMat2);

    Vec eyeDir;
    if (*(char*)((char*)this + 0xb1) == 1) {
        Mtx tmp;
        PSMTXIdentity(tmp);
        PSMTXTrans(tmp, FLOAT_8032fc14, FLOAT_8032fc14, FLOAT_8032fc34);
        GXLoadPosMtxImm(tmp, 0);
        PSMTXIdentity(tmp);
        GXLoadNrmMtxImm(tmp, 0);

        Vec eye;
        Vec up;
        eye.x = FLOAT_8032fc14;
        eye.y = FLOAT_8032fc14;
        eye.z = FLOAT_8032fc14;
        up.x = FLOAT_8032fc14;
        up.y = FLOAT_8032fc1c;
        up.z = FLOAT_8032fc14;

        Mtx lookAt;
        C_MTXLookAt(lookAt, &eye, &up, (Vec*)((char*)this + 0x38));

        Vec camPos;
        camPos.x = CameraPcs._224_4_;
        camPos.y = CameraPcs._228_4_;
        camPos.z = CameraPcs._232_4_;

        Vec lightPos;
        PSVECSubtract((Vec*)((char*)this + 0x10), &camPos, &lightPos);
        PSVECNormalize(&lightPos, &lightPos);

        Vec nrm;
        PSVECNormalize((Vec*)((char*)this + 0x38), &nrm);

        Vec diff;
        PSVECSubtract(&lightPos, &nrm, &diff);

        float scale = FLOAT_8032fc1c;
        if (*(char*)((char*)this + 0xb2) == 1) {
            scale = FLOAT_8032fc38;
        }
        PSVECScale(&diff, &diff, scale);
        PSVECAdd(&nrm, &diff, &nrm);
        PSVECNormalize(&nrm, &nrm);

        PSMTXMultVecSR(lookAt, &nrm, &eyeDir);
    } else {
        Mtx tmp;
        PSMTXIdentity(tmp);
        GXLoadPosMtxImm(tmp, 0);
        GXLoadNrmMtxImm(tmp, 0);
        eyeDir.x = *(float*)((char*)this + 0x38);
        eyeDir.y = *(float*)((char*)this + 0x3c);
        eyeDir.z = *(float*)((char*)this + 0x40);
    }

    int copySize = GXGetTexBufferSize(0x40, 0x40, 3, 0, 0);
    unsigned int packedColor = DAT_8032fc0c;
    double dScale = (double)FLOAT_8032fc40;
    double dHalf = (double)FLOAT_8032fc1c;
    float* lightScale = &DAT_801ea430;
    double dFactor = (double)FLOAT_8032fc3c;
    double dInv = (double)FLOAT_8032fc44;
    int offset = 0;
    double dW = (double)FLOAT_8032fc60;

    for (int i = 0; i < (int)(unsigned int)*(unsigned char*)((char*)this + 0xb3); i++) {
        int texBase = *(int*)((char*)this + 0xb4);
        GXLightObj lightObj;
        GXInitSpecularDir(&lightObj, eyeDir.x, eyeDir.y, eyeDir.z);

        _GXColor lightColor;
        *reinterpret_cast<unsigned int*>(&lightColor) = packedColor;
        GXInitLightColor(&lightObj, lightColor);

        if (*(char*)((char*)this + 0xb2) == 1) {
            double d0 = (double)FLOAT_8032fc14;
            double d1 = (double)(*(float*)((char*)this + 0x48) * FLOAT_8032fc18);
            GXInitLightAttn(&lightObj, (float)d0, (float)d0, FLOAT_8032fc1c, (float)d1, (float)d0,
                            (float)((double)FLOAT_8032fc1c - d1));
        } else {
            double d0 = (double)FLOAT_8032fc14;
            double d1 = (double)(*lightScale * FLOAT_8032fc18);
            GXInitLightAttn(&lightObj, (float)d0, (float)d0, FLOAT_8032fc1c, (float)d1, (float)d0,
                            (float)((double)FLOAT_8032fc1c - d1));
        }

        GXLoadLightObjImm(&lightObj, (GXLightID)1);

        unsigned int y = 0;
        do {
            unsigned int yBase = y;
            GXBegin((GXPrimitive)0x98, (GXVtxFmt)0, 0x42);

            float x0 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(yBase)) * dScale - dHalf));
            double dx0 = (double)x0;
            float x1 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(yBase + 1)) * dScale - dHalf));
            double dx1 = (double)x1;

            int inner = 0x21;
            unsigned int x = 0;
            do {
                float z0 = (float)((double)(float)(dFactor * (double)(float)(U32ToDouble(x)) * dScale - dHalf));
                double dz0 = (double)z0;
                double dist0 = (double)(float)(dx0 * dx0 + (double)(float)(dz0 * dz0));
                if (dHalf <= dist0) {
                    dist0 = (double)FLOAT_8032fc14;
                } else {
                    float diff = (float)(dHalf - dist0);
                    dist0 = (double)diff;
                    if (dist0 <= (double)FLOAT_8032fc14) {
                        if (DOUBLE_8032fc58 <= dist0) {
                            unsigned int flags = (unsigned int)diff & 0x7f800000;
                            int classify;
                            if (flags == 0x7f800000) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 2;
                                } else {
                                    classify = 1;
                                }
                            } else if ((flags < 0x7f800000) && (flags == 0)) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 3;
                                } else {
                                    classify = 5;
                                }
                            } else {
                                classify = 4;
                            }
                            if (classify == 1) {
                                dist0 = DAT_8032ec20;
                            }
                        } else {
                            dist0 = DAT_8032ec20;
                        }
                    } else {
                        double inv = 1.0 / sqrt(dist0);
                        inv = DOUBLE_8032fc48 * inv * -(dist0 * inv * inv - DOUBLE_8032fc50);
                        inv = DOUBLE_8032fc48 * inv * -(dist0 * inv * inv - DOUBLE_8032fc50);
                        dist0 = (double)(float)(dist0 * DOUBLE_8032fc48 * inv *
                                               -(dist0 * inv * inv - DOUBLE_8032fc50));
                    }
                }

                GXWGFifo.f32 = x0;
                double dist1 = (double)(float)(dx1 * dx1 + (double)(float)(dz0 * dz0));
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = (float)dW;
                GXWGFifo.f32 = (float)(dx0 / dInv);
                GXWGFifo.f32 = (float)(dz0 / dInv);
                GXWGFifo.f32 = (float)dist0;

                if (dHalf <= dist1) {
                    dist1 = (double)FLOAT_8032fc14;
                } else {
                    float diff = (float)(dHalf - dist1);
                    dist1 = (double)diff;
                    if (dist1 <= (double)FLOAT_8032fc14) {
                        if (DOUBLE_8032fc58 <= dist1) {
                            unsigned int flags = (unsigned int)diff & 0x7f800000;
                            int classify;
                            if (flags == 0x7f800000) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 2;
                                } else {
                                    classify = 1;
                                }
                            } else if ((flags < 0x7f800000) && (flags == 0)) {
                                if (((unsigned int)diff & 0x7fffff) == 0) {
                                    classify = 3;
                                } else {
                                    classify = 5;
                                }
                            } else {
                                classify = 4;
                            }
                            if (classify == 1) {
                                dist1 = DAT_8032ec20;
                            }
                        } else {
                            dist1 = DAT_8032ec20;
                        }
                    } else {
                        double inv = 1.0 / sqrt(dist1);
                        inv = DOUBLE_8032fc48 * inv * -(dist1 * inv * inv - DOUBLE_8032fc50);
                        inv = DOUBLE_8032fc48 * inv * -(dist1 * inv * inv - DOUBLE_8032fc50);
                        dist1 = (double)(float)(dist1 * DOUBLE_8032fc48 * inv *
                                               -(dist1 * inv * inv - DOUBLE_8032fc50));
                    }
                }

                GXWGFifo.f32 = x1;
                GXWGFifo.f32 = z0;
                GXWGFifo.f32 = (float)dW;
                GXWGFifo.f32 = (float)(dx1 / dInv);
                GXWGFifo.f32 = (float)(dz0 / dInv);
                GXWGFifo.f32 = (float)dist1;

                inner--;
                x++;
            } while (inner != 0);

            y = yBase + 1;
        } while (y < 0x20);

        GXSetTexCopySrc(0, 0, 0x40, 0x40);
        GXSetTexCopyDst((unsigned short)0x40, (unsigned short)0x40, (GXTexFmt)3, (unsigned char)0);
        GXCopyTex(reinterpret_cast<void*>(texBase + offset), 1);
        GXPixModeSync();

        offset += copySize;
        lightScale++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::MakeLightMap()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80047ee0
 * PAL Size: 1180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CLightPcs::SetBumpTexMatirx(float (*mat)[4], CLightPcs::CBumpLight* bump, Vec* vec, unsigned char mode)
{
    Mtx* input = (Mtx*)mat;
    float* scale = (float*)vec;

    Mtx cam;
    PSMTXCopy(CameraPcs.m_cameraMatrix, cam);
    Mtx* out = (Mtx*)((char*)this + 0x30);

    if (mode == 0) {
        if (scale == nullptr ||
            ((FLOAT_8032fc14 == scale[0]) && (FLOAT_8032fc14 == scale[1]) && (FLOAT_8032fc14 == scale[2]))) {
            PSMTXConcat(cam, *input, *out);
        } else {
            Mtx tmp;
            PSMTXCopy(*input, tmp);
            Vec camPos;
            camPos.x = CameraPcs._224_4_;
            camPos.y = CameraPcs._228_4_;
            camPos.z = CameraPcs._232_4_;
            Vec objPos;
            objPos.x = tmp[0][3];
            objPos.y = tmp[1][3];
            objPos.z = tmp[2][3];
            PSVECSubtract(&camPos, &objPos, &camPos);
            camPos.x = camPos.x * scale[0];
            camPos.y = camPos.y * scale[1];
            camPos.z = camPos.z * scale[2];
            PSMTXMultVecSR(cam, &camPos, &camPos);
            PSMTXConcat(cam, tmp, *out);
            (*out)[0][3] += camPos.x;
            (*out)[1][3] += camPos.y;
            (*out)[2][3] += camPos.z;
        }
    } else {
        Vec pos;
        pos.x = (*input)[0][3];
        pos.y = (*input)[1][3];
        pos.z = (*input)[2][3];
        PSMTXMultVec(cam, &pos, &pos);

        if (mode == 1) {
            cam[0][1] = FLOAT_8032fc14;
            cam[0][0] = FLOAT_8032fc1c;
            cam[0][2] = FLOAT_8032fc14;
            cam[1][0] = FLOAT_8032fc14;
            cam[1][1] = FLOAT_8032fc1c;
            cam[1][2] = FLOAT_8032fc14;
            cam[2][0] = FLOAT_8032fc14;
            cam[2][1] = FLOAT_8032fc14;
            cam[2][2] = FLOAT_8032fc1c;
        } else if (mode == 2) {
            Vec yAxis;
            yAxis.x = cam[0][1];
            yAxis.y = cam[1][1];
            yAxis.z = cam[2][1];
            PSVECNormalize(&yAxis, &yAxis);
            Vec xAxis;
            xAxis.y = -yAxis.x;
            cam[0][1] = yAxis.x;
            cam[1][1] = yAxis.y;
            cam[2][1] = yAxis.z;
            xAxis.x = yAxis.y;
            xAxis.z = FLOAT_8032fc14;
            PSVECNormalize(&xAxis, &xAxis);
            cam[0][0] = xAxis.x;
            cam[1][0] = xAxis.y;
            cam[2][0] = xAxis.z;
            Vec zAxis;
            PSVECCrossProduct(&xAxis, &yAxis, &zAxis);
            PSVECNormalize(&zAxis, &zAxis);
            cam[0][2] = zAxis.x;
            cam[1][2] = zAxis.y;
            cam[2][2] = zAxis.z;
        }

        PSMTXConcat(cam, *input, *out);
        (*out)[0][3] = pos.x;
        (*out)[1][3] = pos.y;
        (*out)[2][3] = pos.z;
    }

    GXLoadPosMtxImm(*out, 0);

    Mtx nrm;
    nrm[0][0] = (*out)[0][0];
    nrm[1][0] = (*out)[1][0];
    nrm[2][0] = (*out)[2][0];
    nrm[0][1] = (*out)[0][1];
    nrm[1][1] = (*out)[1][1];
    nrm[2][1] = (*out)[2][1];
    nrm[0][2] = (*out)[0][2];
    nrm[1][2] = (*out)[1][2];
    nrm[2][2] = (*out)[2][2];
    nrm[0][3] = FLOAT_8032fc14;
    nrm[1][3] = FLOAT_8032fc14;
    nrm[2][3] = FLOAT_8032fc14;
    GXLoadNrmMtxImm(nrm, 0);

    if ((bump != nullptr) && (*(char*)((char*)bump + 0xb0) != 0)) {
        Mtx* bumpMat0 = (Mtx*)((char*)this + 4);
        Mtx* bumpMat1 = (Mtx*)((char*)this + 0x34);

        if (*(char*)((char*)bump + 0xb1) == 1) {
            Mtx tmp;
            PSMTXTrans(tmp, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(tmp, nrm, *bumpMat0);
            PSMTXScale(tmp, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, tmp, *bumpMat0);
            Mtx posOnly;
            PSMTXCopy(*out, posOnly);
            posOnly[0][3] = FLOAT_8032fc14;
            posOnly[1][3] = FLOAT_8032fc14;
            posOnly[2][3] = FLOAT_8032fc14;
            PSMTXConcat(posOnly, tmp, *bumpMat1);
        } else {
            Mtx tmp;
            Mtx ident;
            PSMTXIdentity(ident);
            PSMTXTrans(tmp, FLOAT_8032fc18, FLOAT_8032fc18, FLOAT_8032fc14);
            PSMTXConcat(tmp, ident, *bumpMat0);
            PSMTXScale(tmp, FLOAT_8032fc20, FLOAT_8032fc20, FLOAT_8032fc20);
            PSMTXConcat(*bumpMat0, tmp, *bumpMat0);

            double camX = (double)CameraPcs._224_4_;
            double camZ = (double)CameraPcs._232_4_;
            PSMTXIdentity(*(Mtx*)((char*)this + 100));

            float f0 = FLOAT_8032fc24;
            float f1 = FLOAT_8032fc14;
            *(float*)((char*)this + 100) = FLOAT_8032fc24;
            float f2 = FLOAT_8032fc18;
            *(float*)((char*)this + 0x7c) = f0;
            float f3 = FLOAT_8032fc20;
            *(float*)((char*)this + 0x8c) = f1;
            *(float*)((char*)this + 0x78) = f1;
            *(float*)((char*)this + 0x88) = f1;
            *(float*)((char*)this + 0x70) =
                -(f0 * (float)(camX + (double)*(float*)((char*)bump + 0x2c)) - f2);
            *(float*)((char*)this + 0x80) =
                -(f0 * (float)(camZ + (double)*(float*)((char*)bump + 0x30)) - f2);
            *(float*)((char*)this + 0x90) = f1;
            *(float*)((char*)this + 0xa4) = f3;
            *(float*)((char*)this + 0x94) = f3;
            *(float*)((char*)this + 0xa8) = f1;
            *(float*)((char*)this + 0xa0) = f1;
            *(float*)((char*)this + 0x9c) = f1;
            *(float*)((char*)this + 0x98) = f1;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CBumpLight::CBumpLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::CBumpLight::SetTexture(_GXTexMapID, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CLightPcs::CLight::CLight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CLightPcs::CLight::Set(CLightPcs::CLight*)
{
	// TODO
}
