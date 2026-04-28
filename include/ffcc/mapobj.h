#ifndef _FFCC_MAPOBJ_H_
#define _FFCC_MAPOBJ_H_

#include "ffcc/ptrarray.h"

class CChunkFile;
class CMapKeyFrame;
class CMapCylinder;
class CMapShadow;
class CMapAnimRun;
class CMapObjAtr;
class CMapObjAtrPlaySta;
class CMapObjAtrMime;
class CMapObjAtrSpotLight;
class CMapObjAtrPointLight;
class CMapObjAtrMeshName;
class CMaterialMan;
class CCameraPcs;
struct Vec;
struct _GXColor;

void calcColorKeyFrame(CMapKeyFrame*, _GXColor&, _GXColor*);

class CMapObjAtr
{
public:
    enum TYPE
    {
        POINT_LIGHT = 0,
        SPOT_LIGHT = 1,
        MIME = 2,
        MESH_NAME = 3,
        PLAY_STA = 4,
    };
    
    CMapObjAtr();
    virtual ~CMapObjAtr();
};

class CMapObjAtrPlaySta : public CMapObjAtr
{
public:
    CMapObjAtrPlaySta();
    ~CMapObjAtrPlaySta();
};

class CMapObjAtrMime : public CMapObjAtr
{
public:
    CMapObjAtrMime();
    ~CMapObjAtrMime();
};

class CMapObjAtrSpotLight : public CMapObjAtr
{
public:
    CMapObjAtrSpotLight()
    {
        unsigned char* self = reinterpret_cast<unsigned char*>(this);

        *reinterpret_cast<int*>(self + 0x4) = SPOT_LIGHT;
        *reinterpret_cast<int*>(self + 0x38) = 0;
        *reinterpret_cast<float*>(self + 0x20) = 1.0f;
        *reinterpret_cast<float*>(self + 0x24) = 1.0f;
        self[0x2C] = 0;
        self[0x2D] = 0;
        self[0x30] = 0;
        *reinterpret_cast<int*>(self + 0xD8) = 0;
        *reinterpret_cast<int*>(self + 0xDC) = 0;
        *reinterpret_cast<int*>(self + 0xE0) = 0;
        *reinterpret_cast<int*>(self + 0xE4) = 0;
        self[0xC3] = 1;
        self[0xC4] = 0;
        *reinterpret_cast<int*>(self + 0x100) = 0;
        *reinterpret_cast<int*>(self + 0x104) = 0;
        *reinterpret_cast<int*>(self + 0x108) = 0;
        *reinterpret_cast<int*>(self + 0x10C) = 0;
        self[0xEB] = 1;
        self[0xEC] = 0;
        for (int i = 0; i < 0x28; i += 4) {
            *reinterpret_cast<int*>(self + 0xC0 + i) = 0;
            *reinterpret_cast<int*>(self + 0xE8 + i) = 0;
        }
    }

    ~CMapObjAtrSpotLight();
};

class CMapObjAtrPointLight : public CMapObjAtr
{
public:
    CMapObjAtrPointLight()
    {
        unsigned char* self = reinterpret_cast<unsigned char*>(this);

        *reinterpret_cast<int*>(self + 0x4) = POINT_LIGHT;
        self[0x1C] = 0;
        self[0x20] = 0;
        *reinterpret_cast<int*>(self + 0xBC) = 0;
        *reinterpret_cast<int*>(self + 0xC0) = 0;
        *reinterpret_cast<int*>(self + 0xC4) = 0;
        *reinterpret_cast<int*>(self + 0xC8) = 0;
        self[0xA7] = 1;
        self[0xA8] = 0;
        *reinterpret_cast<int*>(self + 0xE4) = 0;
        *reinterpret_cast<int*>(self + 0xE8) = 0;
        *reinterpret_cast<int*>(self + 0xEC) = 0;
        *reinterpret_cast<int*>(self + 0xF0) = 0;
        self[0xCF] = 1;
        self[0xD0] = 0;
        for (int i = 0; i < 0x28; i += 4) {
            *reinterpret_cast<int*>(self + 0xA4 + i) = 0;
            *reinterpret_cast<int*>(self + 0xCC + i) = 0;
        }
    }

    ~CMapObjAtrPointLight();
};

class CMapObjAtrMeshName : public CMapObjAtr
{
public:
    CMapObjAtrMeshName();
    ~CMapObjAtrMeshName();
};

class CMapObj
{
public:
    void Init();
    CMapObj();
    ~CMapObj();
    void ReadOtmObj(CChunkFile&);
    void CalcMtx(float (*)[4], unsigned char);
    void SetShow_r(int);
    void SetShow(int);
    void SetLink();
    void Calc();
    void SetDrawEnv();
    void IsDrawAlphaLight();
    void Draw(unsigned char);
    void SetDrawFlag();
    void DrawHit();
    void DrawHitWire();
    void DrawHitNormal();
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    void GetHitFaceNormal(Vec*);
    int CalcHitSlide(Vec*, float);
    void CalcHitPosition(Vec*);
    void SetMime(int, int, int);
    void SetCalcMtx();
};
#endif // _FFCC_MAPOBJ_H_
