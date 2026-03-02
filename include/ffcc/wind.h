#ifndef _FFCC_PPP_WIND_H_
#define _FFCC_PPP_WIND_H_

#include "types.h"
#include <dolphin/mtx.h>

struct WindObject
{
    u8 flags;
    u8 _pad01[3];
    f32 centerX;
    f32 centerZ;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 type;
    s32 id;
    s32 life;
    s32 lifeTimer;
    f32 baseRadius;
    f32 radius;
    f32 radiusSq;
    f32 lifeRatio;
    f32 _unk3C;
    f32 baseDir;
    f32 curDir;
    f32 targetDir;
    f32 basePower;
    f32 curPower;
    f32 targetPower;
    Vec force;
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
    s32 m_nextId;
    u8 _padC84[0x7000];
    u32 m_unk7C84;
};

#endif // _FFCC_PPP_WIND_H_
