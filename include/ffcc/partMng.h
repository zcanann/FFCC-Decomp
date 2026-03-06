#ifndef _FFCC_PARTMNG_H_
#define _FFCC_PARTMNG_H_

#include "ffcc/mapmesh.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"
#include "ffcc/pppcolor.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>

class CChara;
class CChunkFile;
class CGObject;
class CTexture;
class CTextureSet;

struct _PARTICLE_WMAT
{
};

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

    pppShapeSt();
    ~pppShapeSt();

    void* GetTexture(long*, CMaterialSet*, int&);
}; // Size 0x2c

struct pppModelSt
{
    CMapMesh m_mapMesh;     // 0x0
    char m_name[32];        // 0x44
    short m_refCount;       // 0x64
    short m_cacheId;        // 0x66
    unsigned char m_isUsed; // 0x68

    pppModelSt();
    ~pppModelSt();
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

struct pppFMATRIX
{
    Mtx value;
};
typedef Mtx PARTICLE_WMAT;  // Size 0x30

struct _PARTICLE_COLOR
{
    float m_color[4];            // 0x0
    float m_colorFrameDeltas[4]; // 0x10
};
typedef _PARTICLE_COLOR PARTICLE_COLOR;

struct _PARTICLE_DATA
{
    Mtx m_matrix;          // 0x0 - 0x30
    Vec m_velocity;        // 0x30 - 0x3c
    Vec m_directionTail;   // 0x3c - 0x48
    float m_colorDeltaAdd[4]; // 0x48 - 0x58
    float m_sizeStart;     // 0x58 - 0x5c
    float m_sizeEnd;       // 0x5c - 0x60
    float m_sizeVal;       // 0x60 - 0x64
    int m_lifeTime;        // 0x64 - 0x68
    int m_age;             // 0x68 - 0x6c
    char m_padding[0x140 - 0x6c]; // Pad to 0x140 bytes total
};
typedef _PARTICLE_DATA PARTICLE_DATA;

struct _pppPObject
{
    s32 m_graphId;              // 0x0
    pppFMATRIX m_localMatrix;   // 0x4 (size 0x30)
    // Additional members may exist
};

struct _pppPObjLink;
struct _pppCtrlTable;

typedef void (*pppProgAnyCallback)(void);
typedef void (*pppProgOperationCallback)(_pppPObject*, void*, _pppCtrlTable*);
typedef void (*pppProgOperation2Callback)(_pppPObject*, void*);
typedef void (*pppProgRenderCallback)(_pppPObject*, void*, _pppCtrlTable*);
typedef void (*pppProgConstructCallback)(_pppPObjLink*, _pppCtrlTable*);
typedef void (*pppProgConstruct2Callback)(_pppPObject*);
typedef void (*pppProgConstruct3Callback)(_pppPObject*, _pppCtrlTable*);
typedef void (*pppProgDestructCallback)(_pppPObjLink*, _pppCtrlTable*);

struct pppFVECTOR4
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
    char* m_pppName;                            // 0x0
    char* m_unkPtr;                             // 0x4
    pppProgAnyCallback m_pppFunctionOperation;  // 0x8
    pppProgAnyCallback m_pppFunctionRender;     // 0xC
    CGObject* m_objects[3];                     // 0x10
    pppProgAnyCallback m_pppFunctionConstructor;  // 0x1C
    pppProgAnyCallback m_pppFunctionConstructor2; // 0x20
    pppProgAnyCallback m_pppFunctionConstructor3; // 0x24
    pppProgAnyCallback m_pppFunctionDestructor;   // 0x28
}; // Size 0x2c

struct _pppCtrlTableData
{
    int m_workOffset;       // 0x0
    int m_workOffsetAlt;    // 0x4
    int m_ownerWorkOffset;  // 0x8
};

struct _pppCtrlTable
{
    pppProg* m_prog;                    // 0x0
    union {
        int m_initialWork;              // 0x4
        struct {
            unsigned short m_workOffset; // 0x4
            unsigned short m_workFlags;  // 0x6
        } m_workInfo;
    };
    int m_unk8;                         // 0x8
    union {
        _pppCtrlTableData* m_serializedDef; // 0xC
        int* m_serializedDataOffsets;       // 0xC
    };
};

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

struct pppIVECTOR4
{
    short x;
    short y;
    short z;
    short w;
};

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
    void* m_pppResSet;                 // 0x00
    int m_partIndex;                   // 0x04
    Vec m_position;                    // 0x08
    int m_baseTime;                    // 0x14
    pppIVECTOR4 m_rotation;            // 0x18
    int m_rotationSpeed;               // 0x20
    int m_lifeEnd;                     // 0x24
    Vec m_scale;                       // 0x28
    int m_currentFrame;                // 0x34
    int m_previousFrame;               // 0x38
    int m_numControlPrograms;          // 0x3C
    float m_scaleFactor;               // 0x40
    float m_ownerScale;                // 0x44
    float m_userFloat0;                // 0x48
    float m_userFloat1;                // 0x4C
    Vec m_savedPosition;               // 0x50
    Vec m_previousPosition;            // 0x5C
    Vec m_paramVec0;                   // 0x68
    short m_kind;                      // 0x74
    short m_nodeIndex;                 // 0x76
    pppFMATRIX m_matrix;               // 0x78
    unsigned char m_envColorR;         // 0xA8
    unsigned char m_envColorG;         // 0xA9
    unsigned char m_envColorB;         // 0xAA
    unsigned char m_envColorA;         // 0xAB
    union {
        int m_prioTime;                // 0xAC
        int m_spawnedCount;
    };
    int m_previousFrame2;              // 0xB0
    int m_numPrograms;                 // 0xB4
    int m_reservedB8;                  // 0xB8
    unsigned int m_objHitMask;         // 0xBC
    unsigned int m_cylinderAttribute;  // 0xC0
    unsigned char m_pObjList[0xC];     // 0xC4
    void* m_pDataValList;              // 0xCC
    void* m_controlProgramTable;       // 0xD0
    void* m_programInfoTable;          // 0xD4
    void* m_programControlArray;       // 0xD8
    void* m_owner;                     // 0xDC
    void* m_lookTarget;                // 0xE0
    CChara::CNode* m_bindNode;         // 0xE4
    unsigned char m_mode;              // 0xE8
    unsigned char m_particleEnded;     // 0xE9
    unsigned char m_isFinished;        // 0xEA
    unsigned char m_matrixMode;        // 0xEB
    unsigned char m_hitBgFlag;         // 0xEC
    unsigned char m_slotVisible;       // 0xED
    unsigned char m_ownerFacing;       // 0xEE
    unsigned char m_drawVariant;       // 0xEF
    unsigned char m_rotationOrder;     // 0xF0
    unsigned char m_drawPass;          // 0xF1
    signed char m_drawSubType;         // 0xF2
    unsigned char m_useOwnerScaleSign; // 0xF3
    unsigned char m_ownerFlagsInitialized; // 0xF4
    unsigned char m_nodeScaleInitialized;  // 0xF5
    unsigned char m_fieldF6;           // 0xF6
    unsigned char m_mapTexLoaded;      // 0xF7
    unsigned char m_hasMapRef;         // 0xF8
    unsigned char m_fpBillboard;       // 0xF9
    unsigned char m_prio;              // 0xFA
    short m_frameCounter;              // 0xFB
    unsigned char m_padFD[3];          // 0xFD
    unsigned int m_paramA;             // 0x100
    unsigned int m_paramB;             // 0x104
    float m_cullRadiusSq;              // 0x108
    float m_cullRadius;                // 0x10C
    float m_cullYOffset;               // 0x110
    float m_sortDepth;                 // 0x114
    unsigned short m_field118;         // 0x118
    short m_mapObjIndex;               // 0x11A
    PPPSEST m_soundEffectData;         // 0x11C
    PPPIFPARAM m_hitParams;            // 0x130
    short m_hitObjectIds[0x10];        // 0x138
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
    int pppGetNumFreePppMngSt();
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

    int pppGetFreeDataMng();
    void pppGetDefaultCreateParam();

    int pppCreate0(int, int, PPPCREATEPARAM*, int);
    int pppCreate(int, int, PPPCREATEPARAM*, int);

    void pppGetFreeSlot();
    void pppDeleteSlot(int, int);
    void pppEndSlot(int, int);
    void pppShowSlot(int, unsigned char);

    void pppDeletePart(int);
    void pppEndPart(int);

    PPPIFPARAM* pppGetIfDt(short);
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

    _pppMngSt m_pppMng[0x60];
};

extern Mtx ppvCameraMatrix0;
extern Mtx ppvWorldMatrix;
extern Mtx ppvWorldMatrixWood;
extern CPartMng PartMng;

extern _pppEnvSt* pppEnvStPtr;
extern _pppMngSt* pppMngStPtr;

#endif
