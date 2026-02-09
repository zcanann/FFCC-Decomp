#ifndef _FFCC_PPP_WIND_H_
#define _FFCC_PPP_WIND_H_

#include "types.h"
#include <dolphin/mtx.h>

struct WindObject
{
    u8 flags;
    u8 pad1[3];
    Vec pos;
    u8 pad2[16];
    s32 type;
    u8 pad3[16];
    f32 radius;
    u8 pad4[4];
    f32 intensity;
    u8 pad5[56]; // Total size: 100 bytes
};

class CWind
{
public:
    void ClearAll();
    void Frame();
    void Draw();
    void Calc(Vec*, const Vec*, int);
    void searchFreeObj();
    void getObj(int);
    int AddAmbient(float, float);
    int AddDiffuse(const Vec*, float, float, float);
    int AddSphere(const Vec*, float, float, int);
    void ChangePower(int, float);

private:
    WindObject m_objects[32];
};

#endif // _FFCC_PPP_WIND_H_
