#ifndef _FFCC_CMATH_H_
#define _FFCC_CMATH_H_

struct Vec;
struct Vec4d;
struct SRT;

void VECMultAdd(Vec*, Vec*, Vec*, float);

class CBound
{
public:
    CBound();
    void SetFrustum(Vec&, float(*)[4]);
    int CheckFrustum0(CBound&);
    int CheckFrustum0(float);
    int CheckFrustum(Vec&, float(*)[4], float);
};

class SRT
{
public:
    void operator=(const SRT&);
    void Identity();
};

class CMath
{
public:
    CMath();
    void Init();
    void Quit();
    void rotateToMatrix(float(*)[4], Vec*);
    void SRTToMatrix(float(*)[4], SRT*);
    void SRTToMatrixRT(float(*)[4], SRT*);
    int Rand(unsigned long);
    float RandF(float);
    float RandF();
    int RandPM(unsigned long);
    float RandFPM(float);
    void MTX44MultVec4(float(*)[4], Vec*, Vec4d*);
    void MTX44MultVec4(float(*)[4], Vec4d*, Vec4d*);
    void MTXGetScale(float(*)[4], Vec*);
    void CrossCheckSphereVector(Vec*, float*, Vec*, Vec*, Vec*, float);
    void CrossCheckEllipseCapsule(Vec*, float*, Vec*, Vec*, float, Vec*, float, float);
    void CalcSpline(Vec*, Vec*, Vec*, Vec*, Vec*, float, float, float, float, float);
    void MakeSpline1Dtable(int, float*, float*, float*);
    float Spline1D(int, float, float*, float*, float*);
    void Line1D(int, float, float*, float*);
    unsigned int Hsb2Rgb(int, int, int);
    float DstRot(float, float);
};

#endif // _FFCC_CMATH_H_
