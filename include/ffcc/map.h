#ifndef _FFCC_MAP_H_
#define _FFCC_MAP_H_

#include "ffcc/mapobj.h"
#include "ffcc/memory.h"

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

class CMapKeyFrame
{
public:
    ~CMapKeyFrame()
    {
        if (m_junTable != 0) {
            delete m_junTable;
            m_junTable = 0;
        }
        if (m_keyFrame != 0) {
            delete m_keyFrame;
            m_keyFrame = 0;
        }
        if (m_keyValue != 0) {
            delete m_keyValue;
            m_keyValue = 0;
        }
        if (m_splineTable != 0) {
            delete m_splineTable;
            m_splineTable = 0;
        }
    }

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
    unsigned short m_unknown10;        // 0x00010
    unsigned char m_pad012[0x213D4 - 0x12];
    CMaterialSet* m_materialSet;       // 0x213D4
    CTextureSet* m_textureSet;         // 0x213D8
    CMapTexAnimSet* m_mapTexAnimSet;   // 0x213DC
    unsigned char m_pad213E0[0x228E8 - 0x213E0];
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

    COctTree* GetOctTreeArray() { return reinterpret_cast<COctTree*>(reinterpret_cast<unsigned char*>(this) + 0x14); }
    CMapHit* GetMapHitArray() { return reinterpret_cast<CMapHit*>(reinterpret_cast<unsigned char*>(this) + 0x4D4); }
    CMapObj* GetMapObjArray() { return reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + 0x954); }
    CMapMesh* GetMapMeshArray() { return reinterpret_cast<CMapMesh*>(reinterpret_cast<unsigned char*>(this) + 0x1E954); }
    CPtrArray<CMapAnimRun*>& GetMapAnimRunArray()
    {
        return *reinterpret_cast<CPtrArray<CMapAnimRun*>*>(reinterpret_cast<unsigned char*>(this) + 0x213E0);
    }
    CPtrArray<CMapAnim*>& GetMapAnimArray()
    {
        return *reinterpret_cast<CPtrArray<CMapAnim*>*>(reinterpret_cast<unsigned char*>(this) + 0x213FC);
    }
    CPtrArray<CMapAnimKeyDt*>& GetMapAnimKeyDtArray()
    {
        return *reinterpret_cast<CPtrArray<CMapAnimKeyDt*>*>(reinterpret_cast<unsigned char*>(this) + 0x21418);
    }
    CPtrArray<CMapShadow*>& GetMapShadowArray()
    {
        return *reinterpret_cast<CPtrArray<CMapShadow*>*>(reinterpret_cast<unsigned char*>(this) + 0x21434);
    }
    CPtrArray<CMapLightHolder*>& GetMapLightHolderArray(int index)
    {
        return *reinterpret_cast<CPtrArray<CMapLightHolder*>*>(
            reinterpret_cast<unsigned char*>(this) + 0x21450 + (index * 0x1C));
    }
    CMapIdGrp* GetMapIdGrpArray() { return reinterpret_cast<CMapIdGrp*>(reinterpret_cast<unsigned char*>(this) + 0x214E8); }

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
