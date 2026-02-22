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
        TODO,
    };
    
    CMapObjAtr();
    ~CMapObjAtr();
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
    CMapObjAtrSpotLight();
    ~CMapObjAtrSpotLight();
};

class CMapObjAtrPointLight : public CMapObjAtr
{
public:
    CMapObjAtrPointLight();
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
