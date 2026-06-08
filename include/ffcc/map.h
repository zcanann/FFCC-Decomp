#ifndef _FFCC_MAP_H_
#define _FFCC_MAP_H_

#include "ffcc/mapkeyframe.h"
#include "ffcc/mapobj.h"
#include "ffcc/memory.h"
#include "ffcc/mapocttree.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/mapanim.h"
#include "ffcc/mapshadow.h"
#include "ffcc/maplight.h"
#include "ffcc/ptrarray.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CChunkFile;
class CMapObj;
class CMapHit;
class CMapCylinder;
class CMapLightHolder;
class CMapMesh;
class CMaterial;
class CMaterialSet;
class CMapTexAnimSet;
class CMapAnimRun;
class CMapAnim;
class CMapAnimNode;
class CMapAnimKeyDt;
class CMapShadow;
class CMemory;
class CTextureSet;
class COctTree;
template <class T>
class CPtrArray;

void setDbgLight(int, Vec&, _GXColor&);
void GXSetTexCoordGen();

class CMapIdGrp
{
public:
    unsigned long m_mask;
    _GXColor m_primaryColor;
    _GXColor m_secondaryColor;
    _GXColor m_tertiaryColor;
    _GXColor m_quaternaryColor;

    CMapIdGrp();
};

struct CMapMngAsyncLoadState
{
    void* m_mapLoadStart;
    void* m_mapLoadCursor;
    unsigned int m_mapLoadSize;
    int m_asyncReadIndex;
    int m_asyncOpenIndex;
    int m_mapReadMode;
    int m_fileSizes[16];
    unsigned int m_fileChecksums[16];
    void* m_asyncHandles[16];
};

struct CMapShadowKeyInfo
{
    unsigned long m_key;              // 0x00
    short m_frame;                    // 0x04
    unsigned char m_unknown06;        // 0x06
    unsigned char m_unknown07;        // 0x07
    unsigned char m_pad08[8];         // 0x08
    _GXColor m_primaryColor;          // 0x10
    _GXColor m_secondaryColor;        // 0x14
};

typedef char CMapShadowKeyInfo_size_check[(sizeof(CMapShadowKeyInfo) == 0x18) ? 1 : -1];

class CMapMng
{
public:
    // Placeholder storage for the full map manager until concrete members are recovered.
    CMemory::CStage* m_stage;          // 0x00000
    int m_calcCount;                   // 0x00004
    short m_octTreeCount;              // 0x00008
    short m_mapHitCount;               // 0x0000A
    short m_mapObjCount;               // 0x0000C
    short m_mapMeshCount;              // 0x0000E
    short m_shadowKeyInfoCount; // 0x00010
    unsigned char m_pad012[0x14 - 0x12];
    COctTree m_octTreeArray[16];       // 0x00014
    CMapHit m_mapHitArray[32];         // 0x004D4
    CMapObj m_mapObjArray[512];        // 0x00954
    CMapMesh m_mapMeshArray[160];      // 0x1E954
    CMaterialSet* m_materialSet;       // 0x213D4
    CTextureSet* m_textureSet;         // 0x213D8
    CMapTexAnimSet* m_mapTexAnimSet;   // 0x213DC
    CPtrArray<CMapAnimRun*> m_mapAnimRunArray;      // 0x213E0
    CPtrArray<CMapAnim*> m_mapAnimArray;            // 0x213FC
    CPtrArray<CMapAnimKeyDt*> m_mapAnimKeyDtArray;  // 0x21418
    CPtrArray<CMapShadow*> m_mapShadowArray;        // 0x21434
    CPtrArray<CMapLightHolder*> m_mapLightHolderArrays[2]; // 0x21450
    CMapShadowKeyInfo m_shadowKeyInfos[4]; // 0x21488
    CMapIdGrp m_mapIdGrpArray[256];     // 0x214E8
    CMapObj* m_rootMapObj;             // 0x228E8
    Vec m_cameraPosition;              // 0x228EC
    Mtx m_viewMtx;                     // 0x228F8
    Mtx m_scaledViewMtxPrimary;        // 0x22928
    Mtx m_scaledViewMtxSecondary;      // 0x22958
    unsigned char m_fogEnable;         // 0x22988
    unsigned char m_colorScaleEnable;  // 0x22989
    unsigned char m_underWaterTexPending; // 0x2298A
    unsigned char m_mapReadReady;      // 0x2298B
    _GXColor m_mapColor;               // 0x2298C
    _GXColor m_colorScale;             // 0x22990
    CMapMngAsyncLoadState m_asyncLoadState; // 0x22994
    int m_mapAnimFrame;                // 0x22A6C
    float m_octTreeDrawMinDepth;       // 0x22A70
    float m_octTreeFrustumRange;       // 0x22A74
    CMapObj* m_hitMapObj;              // 0x22A78

    COctTree* GetOctTreeArray() { return m_octTreeArray; }
    CMapHit* GetMapHitArray() { return m_mapHitArray; }
    CMapObj* GetMapObjArray() { return m_mapObjArray; }
    CMapObj* GetMapObj(int index)
    {
        return &m_mapObjArray[index];
    }
    CMapMesh* GetMapMeshArray() { return m_mapMeshArray; }
    CPtrArray<CMapAnimRun*>& GetMapAnimRunArray()
    {
        return m_mapAnimRunArray;
    }
    CPtrArray<CMapAnim*>& GetMapAnimArray()
    {
        return m_mapAnimArray;
    }
    CPtrArray<CMapAnimKeyDt*>& GetMapAnimKeyDtArray()
    {
        return m_mapAnimKeyDtArray;
    }
    CPtrArray<CMapShadow*>& GetMapShadowArray()
    {
        return m_mapShadowArray;
    }
    CPtrArray<CMapLightHolder*>& GetMapLightHolderArray(int index)
    {
        return m_mapLightHolderArrays[index];
    }
    CPtrArray<CMapLightHolder*>* GetMapLightHolderArrays()
    {
        return m_mapLightHolderArrays;
    }
    CMapIdGrp* GetMapIdGrpArray()
    {
        return m_mapIdGrpArray;
    }

    ~CMapMng();
	
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
    int ReadMtx(char*);
    int ReadMpl(char*);
    int ReadOtm(char*);
    int ReadMid(char*);
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
