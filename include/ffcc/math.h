#ifndef _FFCC_CMATH_H_
#define _FFCC_CMATH_H_

#include "ffcc/mapocttree.h"
#include "ffcc/manager.h"
#include "ffcc/pppVec.h"

struct Vec;

void VECMultAdd(Vec*, Vec*, Vec*, float);

class SRT
{
public:
    /*
     * --INFO--
     * PAL Address: TODO
     * PAL Size: TODO
     * EN Address: 0x80044344
     * EN Size: 52b
     * JP Address: TODO
     * JP Size: TODO
     */
    void Identity()
    {
        m_position.x = m_position.y = m_position.z = 0.0f;
        m_rotation.x = m_rotation.y = m_rotation.z = 0.0f;
        m_scale.x = m_scale.y = m_scale.z = 1.0f;
    }

    Vec m_position;
    Vec m_rotation;
    Vec m_scale;
};

typedef char SRT_size_check[(sizeof(SRT) == 0x24) ? 1 : -1];

class CMath : public CManager
{
public:
    void Init();
    void Quit();
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
    int CrossCheckSphereVector(Vec*, float*, Vec*, Vec*, Vec*, float);
    int CrossCheckEllipseCapsule(Vec*, float*, Vec*, Vec*, float, Vec*, float, float);
    void CalcSpline(Vec*, Vec*, Vec*, Vec*, Vec*, float, float, float, float, float);
    void MakeSpline1Dtable(int, float*, float*, float*);
    float Spline1D(int, float, float*, float*, float*);
    float Line1D(int, float, float*, float*);
    unsigned int Hsb2Rgb(int, int, int);
    float DstRot(float, float);

private:
    float m_localMtx[3][4];      // 0x04
    unsigned char m_scratch[0x30]; // 0x34
};

extern CMath Math;

#endif // _FFCC_CMATH_H_
