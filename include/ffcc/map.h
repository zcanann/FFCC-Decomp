#ifndef _FFCC_MAP_H_
#define _FFCC_MAP_H_

#include "ffcc/mapobj.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CChunkFile;
class CMapObj;
class CMapHit;
class CMapCylinder;
class CMapLightHolder;
class CMaterial;
class CMapAnimRun;
class CMapAnim;
class CMapAnimNode;
class CMapAnimKeyDt;
class CMapShadow;
class CMemory;

void setDbgLight(int, Vec&, _GXColor&);
void GXSetTexCoordGen();

class CMapKeyFrame
{
public:
    CMapKeyFrame();
    ~CMapKeyFrame();

    float Get();
    int Get(int&, int&, float&);
    void Calc();
    int IsRun();
    void ReadJun(CChunkFile&, int);
    void ReadFrame(CChunkFile&, int);
    void ReadKey(CChunkFile&, int);
};

class CMapIdGrp
{
public:
    CMapIdGrp();
};

class CMapMng
{
public:
    ~CMapMng();
    CMapMng();
	
    void Create();
    void DestroyOctTree();
    void DestroyMapHit();
    void DestroyMapObj();
    void DestroyMapMesh();
    void DestroyTextureSet();
    void DestroyMaterialSet();
    void DestroyMapTexAnimSet();
    void DestroyAnimation();
    void DestroyMapShadow();
    void DestroyMapLightHolder();
    void DestroyMap();
    void Destroy();
    void MapFileRead(char*, unsigned long&);
    void MapCheckFileRead(char*);
    void LoadMapNoSyncCalc();
    CMapObj* SearchChildMapObj(CMapObj*, CMapObj*);
    void SearchAtribMapObj(CMapObj*, CMapObjAtr::TYPE);
    void AttachMapHit(CMapHit*, char*);
    int GetDebugPlaySta(int, Vec*);
    void SetLightSource();
    void SetBumpLightSource();
    void InitMapShadow();
    void ReadMtx(char*);
    void ReadMpl(char*);
    void ReadOtm(char*);
    void ReadMid(char*);
    void Calc();
    void DrawMapShadow();
    void DrawBefore();
    void Draw();
    void DrawAfter();
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    void GetAnimRunMapObj(CMapObj*);
    void GetAnimRunID(int);
    void SetViewMtx(float (*)[4], float (*)[4]);
    void SetIdGrpMask(int, unsigned long);
    void SetIdGrpColor(int, int, _GXColor);
    void SetMeshCameraSemiTransRange(unsigned short, float, float, float, float, float);
    void SetMeshCameraSemiTransAlpha(unsigned short, int, int);
    int GetMapObjIdx(unsigned short);
    CMaterial* GetMaterialID(unsigned char);
    int GetMapObjEffectIdx(unsigned short);
    void SetMapObjLMtx(int, float (*)[4]);
    void GetMapObjWMtx(int, float (*)[4]);
    void SetMapObjAnim(int, int, int, int);
    void SetMapAnimID(int, int, int, int);
    void SetMapObjMime(int, int, int, int);
    void SetMapTexAnim(int, int, int, int);
    void ShowMapObj(int, int);
    void ShowMapObjID(int, int);
    void ShowMapObjChild(int, int);
    void ShowMapObjChildID(int, int);
    void ShowMapMeshID(int, int);
    void SetMapObjPrioID(int, unsigned char);
    void SetMapObjTransRate(int, float, float, float);
    void SetMapObjWorldMapLightIdx(int, _GXColor, Vec);
    void SetMapObjWorldMapLightID(int, _GXColor, Vec);
    void SetDrawRangeOctTree(float);
    void SetDrawRangeMapObj(float);
    void SetDraw(unsigned char);
    void GetFogEnable();
};

extern CMapMng MapMng;

#endif // _FFCC_MAP_H_
