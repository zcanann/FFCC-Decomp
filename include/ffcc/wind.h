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

struct WindGrassObject
{
    u8 flags;
    u8 _pad01[3];
    Vec pos;
    s32 id;
    u8 _pad14[0x24];
};

class CWind
{
public:
    void ClearAll();
    void Frame();
    void Draw();
    void Calc(Vec*, const Vec*, int);
#ifndef VERSION_GCCP01
    WindObject* searchFreeObj();
    WindObject* getObj(int);
#endif
    int AddAmbient(float, float);
    int AddDiffuse(const Vec*, float, float, float);
    int AddSphere(const Vec*, float, float, int);
    void ChangePower(int, float);
#ifndef VERSION_GCCP01
    WindGrassObject* searchFreeGrass();
    WindGrassObject* getGrass(int);
    int AddGrass(const Vec*);
#endif

private:
    WindObject m_objects[32];
    s32 m_nextId;
    WindGrassObject m_grass[512];
    u32 m_nextGrassId;
};

extern CWind Wind;

#endif // _FFCC_PPP_WIND_H_
