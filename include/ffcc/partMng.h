#ifndef _FFCC_PARTMNG_H_
#define _FFCC_PARTMNG_H_

#include "ffcc/mapmesh.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"
#include "ffcc/pppcolor.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CChara;
class CChunkFile;
class CTexture;
class CTextureSet;

struct PPPSEST
{
    int m_soundEffectSlot;                  // 0x0
    unsigned char m_soundEffectStopFlag;    // 0x4
    unsigned char m_soundEffectKind;        // 0x5
    unsigned char m_soundEffectStartedOnce; // 0x6
    unsigned char unkSoundEffectRelated;    // 0x7
    int m_soundEffectStartFrame;            // 0x8
    int m_soundEffectFadeFrames;            // 0xc
    int m_soundEffectHandle;                // 0x10
}; // Size 0x14

struct pppShapeSt
{
    void* m_animData;        // 0x0
    void* m_displayListData; // 0x4
    char m_name[32];         // 0x8
    short m_refCount;        // 0x28
    unsigned char m_inUse;   // 0x2a
}; // Size 0x2c

struct pppModelSt
{
    CMapMesh m_mapMesh;     // 0x0
    char m_name[32];        // 0x44
    short m_refCount;       // 0x64
    short m_cacheId;        // 0x66
    unsigned char m_isUsed; // 0x68
}; // Size 0x6c

struct PPPCREATEPARAM
{
    Vec* m_positionOffsetPtr;         // 0x0
    Vec* m_rotationPtr;               // 0x4
    Vec* m_scalePtr;                  // 0x8
    Vec* m_extraPositionPtr;          // 0xc
    unsigned int m_paramA;            // 0x10
    unsigned int m_paramB;            // 0x14
    void* m_lookTargetPtr;            // 0x18
    unsigned int m_objectHitMask;     // 0x1c
    unsigned int m_cylinderAttribute; // 0x20
    float m_paramC;                   // 0x24
    float m_paramD;                   // 0x28
    void* m_owner;                    // 0x2c
    PPPSEST m_soundEffectParams;      // 0x30
    int m_hitParamA;                  // 0x44
    unsigned short m_hitParamB;       // 0x48
    unsigned char m_hitObjectCount;   // 0x4a
    unsigned char m_hitFlags;         // 0x4b
    int m_hitObjectIds[8];            // 0x4c
    int m_unk;                        // 0x6c
}; // SIze 0x70

typedef Mtx pppFMATRIX;     // Size 0x30
typedef Mtx PARTICLE_WMAT;  // Size 0x30

struct _PARTICLE_COLOR
{
    float m_color[4];            // 0x0
    float m_colorFrameDeltas[4]; // 0x10
};

struct _PARTICLE_DATA
{
};

struct _pppPObject
{
};

struct VColor
{
    unsigned char m_unknown[11]; // 0x0
    unsigned char m_alpha;       // 0xb
}; // Size 0xC

struct PPPIFPARAM
{
    int m_particleIndex;            // 0x0
    short m_classId;                // 0x4
    unsigned char m_hitObjectCount; // 0x6
    unsigned char m_hitFlags;       // 0x7
}; // Size 0x8

struct pppProg
{
    char* m_functionNameTable; // 0x0
    int m_unk1;                // 0x4
    void* m_func;              // 0x8
    int m_unk2[8];             // 0xc
}; // Size 0x2c

struct _pppDataHead
{
    unsigned int m_version;           // 0x0
    unsigned short m_partCount;       // 0x4
    unsigned short m_cacheChunkCount; // 0x6
    unsigned short m_modelCount;      // 0x8
    unsigned short m_shapeCount;      // 0xa
    unsigned short m_shapeGroupCount; // 0xc
    // Padding                        // 0xe
    unsigned int m_cacheChunks;       // 0x10
    unsigned int m_modelNames;        // 0x14
    unsigned int m_shapeNames;        // 0x18
    unsigned int m_shapeGroups;       // 0x1c
}; // Size 0x20

struct _pppEnvSt
{
    CMemory::CStage* m_stagePtr;    // 0x0
    CMaterialSet* m_materialSetPtr; // 0x4
    CMapMesh* m_mapMeshPtr;         // 0x8
    _pppColor m_particleColors[10];  // 0xc
    unsigned int m_mngStCount;      // 0x34
    unsigned int m_debugCounter;    // 0x38
    unsigned int m_isEditMode;      // 0x3c
    int m_unknown;                  // 0x40
    int m_lastEnvCmd;               // 0x44
    float m_envParam;               // 0x48
    float m_boxMinX;                // 0x4c
    float m_boxMinY;                // 0x50
    float m_boxMinZ;                // 0x54
    float m_soundVolumeTable[5];    // 0x58
    float m_boxMaxX;                // 0x6c
    float m_boxMaxY;                // 0x70
    float m_boxMaxZ;                // 0x74
    float m_soundPitchTable[5];     // 0x78
}; // Size 0x8c

struct _pppMngSt
{
}; // Size: 0x158

void Screen2world(Vec&, Vec&);
void pppEditGetViewPos(Vec*);
void pppEditGetViewMatrix(float (*)[4]);
void pppEditGetProjectionMatrix(float (*)[4]);
void pppEditSetProjection2D();
void pppSetProjection();
void CheckSum(char*, unsigned long, unsigned long);
void pppSetFog(unsigned char, unsigned char, unsigned char, unsigned char, float, float);

class CPartMng
{
public:
    CPartMng();

    void Create();
    void Destroy();

    void pppDumpMngSt();
    void pppAmemCacheClear();
    void pppAmemCacheCountStart();
    void pppAmemCacheCountEnd();

    void pppReleasePmng(int);
    void pppReleasePdt(int);

    void pppGetFreePppMngSt();
    void pppGetNumFreePppMngSt();
    void pppGetFreePppDataMngSt();

    void drawLine(int, int, int, int, _GXColor&);
    void drawLine3D(Vec*, Vec*, _GXColor&);
    void drawCursor();
    void render3Dcursor();

    void pppGet2Dpos();
    void drawStart();
    void setProcSpeed(struct ProcSpdSt*, int);
    void drawEnd();

    void initGraphicSystem();
    void allFreeFPrim();
    void SetFp();
    void fpIDon(unsigned short);
    void fpIDoff(unsigned short);

    void InitMaterialSet();
    void ReadTex(CChunkFile&);
    void pppReadRsd(CChunkFile&, pppModelSt*);
    void pppReadShp(CChunkFile&, pppShapeSt*);

    void pppEditAllReleaseResource();

    void pppDataRcv(unsigned long, char*, unsigned long);

    void pppEditBeforeCalc();
    void pppEditPartCalc();
    void pppEditDrawShadow();
    void pppEditDraw();
    void pppEditPartDrawAfter();

    void pppSetRendMatrix();
    void pppPartCalc();
    void pppRefCnt0Up();
    void pppDumpCacheIdx();

    void pppDrawPppMngSt(Vec&, _pppMngSt*);
    void pppDrawPrio(unsigned char);
    void pppDrawPrioPdtFpno(unsigned char, short, short);
    void pppDrawIdx(int);
    void pppDraw();
    void pppPartDrawAfter();
    void pppPartDead();
    void pppPartInit();

    void pppInitEnv(_pppEnvSt*, _pppDataHead*, unsigned int);
    void pppFileRead(char*, unsigned long&, void*, int);
    void LoadPartNoSyncCalc();
    void pppLoadPtx(const char*, int, int, void*, int);

    void pppLoadPmd(CChunkFile&);
    void pppLoadPmd(const char*);
    void pppLoadPan(CChunkFile&);
    void pppLoadPan(const char*);
    void pppLoadPdt(const char*, int, int, void*, int);

    void pppGetFreeDataMng();
    void pppGetDefaultCreateParam();

    void pppCreate0(int, int, PPPCREATEPARAM*, int);
    void pppCreate(int, int, PPPCREATEPARAM*, int);

    void pppGetFreeSlot();
    void pppDeleteSlot(int, int);
    void pppEndSlot(int, int);
    void pppShowSlot(int, unsigned char);

    void pppDeletePart(int);
    void pppEndPart(int);

    void pppGetIfDt(short);
    void pppShowIdx(short, unsigned char);
    void pppFieldShowFpNo(short, unsigned char);
    void pppFieldEndFpNo(short);

    void pppSetDeltaIdx(short, long);
    void pppSetDeltaSlot(int, long);
    void pppSetLocSlot(int, Vec*);

    void pppDeleteCHandle(CCharaPcs::CHandle*);
    void pppEndCHandle(CCharaPcs::CHandle*);
    void pppIsDeadCHandle(CCharaPcs::CHandle*);

    void pppDeleteAll();
    void pppDestroyAll();
};

#endif
