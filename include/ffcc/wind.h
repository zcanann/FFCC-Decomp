#ifndef _FFCC_PPP_WIND_H_
#define _FFCC_PPP_WIND_H_

#include "types.h"
#include <dolphin/mtx.h>

struct WindObjectFlags
{
    s8 active : 1;
    u8 secondary : 1;
    u8 _unused : 6;
};

struct WindObject
{
    union {
        u8 flags;
        WindObjectFlags flagBits;
    };
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
    union {
        u8 flags;
        WindObjectFlags flagBits;
    };
    u8 _pad01[3];
    Vec pos;
    s32 id;
    u8 _pad14[0x24];
};

typedef int WindObjectFlags_size_mismatch[(sizeof(WindObjectFlags) == 1) ? 1 : -1];
typedef int WindObject_size_mismatch[(sizeof(WindObject) == 0x64) ? 1 : -1];
typedef int WindGrassObject_size_mismatch[(sizeof(WindGrassObject) == 0x38) ? 1 : -1];

class CWind
{
public:
    void ClearAll();
    void Frame();
    void Draw();
    void Calc(Vec*, const Vec*, int);
    int AddAmbient(float, float);
    int AddDiffuse(const Vec*, float, float, float);
    int AddSphere(const Vec*, float, float, int);
    void ChangePower(int, float);
    int AddGrass(const Vec*);

private:
    WindObject* getObj(int);
    WindObject* searchFreeObj();
    WindGrassObject* getGrass(int);
    WindGrassObject* searchFreeGrass();

    WindObject m_objects[32];
    s32 m_nextId;
    WindGrassObject m_grass[512];
    u32 m_nextGrassId;
};

extern CWind Wind;

#endif // _FFCC_PPP_WIND_H_
