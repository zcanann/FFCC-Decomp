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

    unsigned char m_mode;      // 0x00
    unsigned char m_junCount;  // 0x01
    unsigned char m_keyCount;  // 0x02
    unsigned char m_loop;      // 0x03
    unsigned char m_isRun;     // 0x04
    unsigned char m_pad05[3];  // 0x05
    int m_currentFrame;        // 0x08
    int m_startFrame;          // 0x0C
    int m_endFrame;            // 0x10
    int m_frameCount;          // 0x14
    unsigned char* m_junTable; // 0x18
    float* m_keyFrame;         // 0x1C
    float* m_keyValue;         // 0x20
    float* m_splineTable;      // 0x24
};

class CMapIdGrp
{
public:
    unsigned long mMask;
    _GXColor mPrimaryColor;
    _GXColor mSecondaryColor;
    _GXColor mTertiaryColor;
    _GXColor mQuaternaryColor;

    CMapIdGrp();
};

class CMapMng
{
public:
    // Placeholder storage for the full map manager until concrete members are recovered.
    unsigned char m_raw[0x22A7C];

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
