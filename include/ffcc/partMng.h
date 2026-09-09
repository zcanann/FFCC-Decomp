#ifndef _FFCC_PARTMNG_H_
#define _FFCC_PARTMNG_H_

#include "ffcc/mapmesh.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"
#include "ffcc/pppColor.h"
#include "ffcc/pppTypes.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>

class CChara;
class CChunkFile;
class CGObject;
class CMaterialSet;
class CTexture;
class CTextureSet;
class CProfile;

struct _pppMngSt;

struct _PARTICLE_WMAT
{
    Mtx value;
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
    void Release();
    void AddRef() { m_refCount++; }
    void SetUse() { m_refCount = 0; m_inUse = 1; }

    CTexture* GetTexture(long*, CMaterialSet*, int&);
}; // Size 0x2c

struct pppModelSt : public CMapMesh
{
    char m_name[32];        // 0x44
    short m_refCount;       // 0x64
    short m_cacheId;        // 0x66
    unsigned char m_isUsed; // 0x68

    pppModelSt();
    ~pppModelSt();
    void Release();
    void AddRef() { m_refCount++; }
    void SetUse() { m_refCount = 0; m_isUsed = 1; }
}; // Size 0x6c

class CParModelSet
{
public:
    CParModelSet();
    ~CParModelSet();
    pppModelSt* GetFree();
    void Create(CChunkFile&, int, int);
    int GetNumModel() { return 0x100; }

    pppModelSt m_models[0x100];
};

class CParShapeSet
{
public:
    CParShapeSet();
    ~CParShapeSet();
    pppShapeSt* GetFree();
    void Create(CChunkFile&, int);
    int GetNumShape() { return 0x100; }

    pppShapeSt m_shapes[0x100];
};

struct PPPCREATEPARAM
{
    PPPCREATEPARAM();

    Vec* m_positionOffsetPtr;         // 0x0
    Vec* m_rotationPtr;               // 0x4
    Vec* m_scalePtr;                  // 0x8
    Vec* m_extraPositionPtr;          // 0xc
    int m_paramA;                     // 0x10
    unsigned int m_paramB;            // 0x14
    CGObject* m_lookTargetPtr;        // 0x18
    unsigned int m_objectHitMask;     // 0x1c
    unsigned int m_cylinderAttribute; // 0x20
    float m_paramC;                   // 0x24
    float m_paramD;                   // 0x28
    void* m_owner;                    // 0x2c
    PPPSEST m_soundEffectParams;      // 0x30
    int m_hitParamA;                  // 0x44
    short m_hitParamB;                // 0x48
    unsigned char m_hitObjectCount;   // 0x4a
    unsigned char m_hitFlags;         // 0x4b
    int m_hitObjectIds[8];            // 0x4c
}; // Size 0x6c

inline PPPCREATEPARAM::PPPCREATEPARAM()
{
    m_soundEffectParams.m_soundEffectHandle = -1;
    m_soundEffectParams.m_soundEffectSlot = -1;
    m_soundEffectParams.m_soundEffectStopFlag = 0;
    m_soundEffectParams.m_soundEffectKind = 1;
    m_soundEffectParams.m_soundEffectStartFrame = 0;
    m_soundEffectParams.m_soundEffectStartedOnce = 0;
    m_soundEffectParams.m_soundEffectFadeFrames = 30;
    m_hitParamA = 0;
    m_hitParamB = 0;
    m_hitObjectCount = 0;
    m_hitFlags = 0;
    m_positionOffsetPtr = 0;
    m_rotationPtr = 0;
    m_scalePtr = 0;
    m_extraPositionPtr = 0;
    m_paramA = 0;
    m_paramB = 0;
    m_lookTargetPtr = 0;
    m_objectHitMask = 0;
    m_cylinderAttribute = 0;
    m_paramC = 1.0f;
    m_paramD = 1.0f;
    *reinterpret_cast<unsigned char*>(&m_owner) = 0;
}

extern CProfile g_par_calc_prof;
extern CProfile g_par_draw_prof;
extern int gPppHeapUseRateWords[3];

struct _PARTICLE_COLOR
{
    float m_color[4];            // 0x0
    float m_colorFrameDeltas[4]; // 0x10
};

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
struct _pppPDataVal;
struct _pppCtrlTable;

// The fixed 0x34-byte prefix that wrapper types embed by value when they
// continue with their own fields after it. Allocated _pppPObject instances
// include link fields before this graph id and matrix block.
struct _pppPObjectHead
{
    s32 m_graphId;              // 0x0
    pppFMATRIX m_localMatrix;   // 0x4 (size 0x30)
};

// Doubly-linked list head for the active _pppPObject instances owned by
// a _pppPDataVal. The head sits inline inside _pppMngSt at 0xC4.
struct _pppPObjLink
{
    _pppPObjLink* m_next;     // 0x0
    _pppPObjLink* m_previous; // 0x4
    _pppPDataVal* m_owner;    // 0x8
}; // Size 0xc

struct _pppPObject
{
    _pppPObjLink m_link;        // 0x0
    s32 m_graphId;              // 0xc
    pppFMATRIX m_localMatrix;   // 0x10 (size 0x30)
    pppFMATRIX m_drawMatrix;    // 0x40 (size 0x30)
    Vec* m_drawMatrixPtr;       // 0x70
    void* m_field74;            // 0x74
    char m_pad78[0x7C - 0x78];  // 0x78
    u8 m_field7C;               // 0x7C
    u8 m_field7D;               // 0x7D
    char m_pad7E[0x80 - 0x7E];  // 0x7E
    u8 m_workArea[1];           // 0x80 - per-instance work block, indexed by _pppCtrlTable::m_serializedDataOffsets[N]
};

typedef void (*pppProgAnyCallback)(void);
typedef void (*pppProgInitCallback)(_pppMngSt*);
typedef void (*pppProgOperationCallback)(_pppPObject*, void*, _pppCtrlTable*);
typedef void (*pppProgOperation2Callback)(_pppPObject*, void*);
typedef void (*pppProgRenderCallback)(_pppPObject*, void*, _pppCtrlTable*);
typedef void (*pppProgConstructCallback)(_pppPObjLink*, _pppCtrlTable*);
typedef void (*pppProgConstruct2Callback)(_pppPObject*);
typedef void (*pppProgConstruct3Callback)(_pppPObject*, _pppCtrlTable*);
typedef void (*pppProgDestructCallback)(_pppPObjLink*, _pppCtrlTable*);

struct pppFVECTOR4
{
    float x;
    float y;
    float z;
    float w;
};

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
    pppProgInitCallback m_pppFunctionInit;        // 0x10
    void* m_unk14;                              // 0x14
    void* m_unk18;                              // 0x18
    pppProgAnyCallback m_pppFunctionConstructor;  // 0x1C
    pppProgAnyCallback m_pppFunctionConstructor2; // 0x20
    pppProgAnyCallback m_pppFunctionConstructor3; // 0x24
    pppProgAnyCallback m_pppFunctionDestructor;   // 0x28
}; // Size 0x2c

struct _pppCtrlTable
{
    pppProg* m_prog;                    // 0x0
    unsigned short m_workOffset;        // 0x4
    unsigned short m_workFlags;         // 0x6
    int m_unk8;                         // 0x8
    int* m_serializedDataOffsets;       // 0xC
};

struct pppCacheChunk
{
    s16 m_cacheIndex; // 0x0
    long* m_pdt;      // 0x4
}; // Size 0x8

struct pppShapeGroupRaw;

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
    pppShapeGroupRaw* m_shapeGroups;  // 0x1c
}; // Size 0x20

struct pppIVECTOR3
{
    s32 x;
    s32 y;
    s32 z;
};

struct _pppFieldParticleData
{
    Vec m_position;                        // 0x00
    unsigned char m_pad0C[4];
    pppIVECTOR3 m_rotation;                // 0x10
    unsigned char m_pad1C[4];
    Vec m_scale;                           // 0x20
    int m_autoCreateMarker;                // 0x2C
    int m_partIndex;                       // 0x30
    float m_cullDistance;                  // 0x34
    float m_cullRadius;                    // 0x38
    float m_cullYOffset;                   // 0x3C
    unsigned short m_fieldId;              // 0x40
    unsigned short m_field118;             // 0x42
    unsigned char m_drawPass;              // 0x44
    unsigned char m_matrixMode;            // 0x45
    unsigned char m_drawVariant;           // 0x46
    unsigned char m_rotationOrder;         // 0x47
    short m_mapObjIndex;                   // 0x48
    unsigned char m_fpBillboard;           // 0x4A
    unsigned char m_prio;                  // 0x4B
    signed char m_drawSubType;             // 0x4C
    unsigned char m_ownerFlagsInitialized; // 0x4D
    unsigned char m_nodeScaleInitialized;  // 0x4E
    unsigned char m_fieldF2;               // 0x4F
    char m_nodeName[0x10];                 // 0x50
}; // Size 0x60
typedef int _pppFieldParticleData_size_mismatch[(sizeof(_pppFieldParticleData) == 0x60) ? 1 : -1];

struct pppShapeGroupRaw
{
    s16 m_meshIndex;       // 0x0
    s16 m_vertexCount;     // 0x2
    u16* m_vertexIndices;  // 0x4
}; // Size 0x8

struct pppIVECTOR4
{
    s32 x;
    s32 y;
    s32 z;
    s32 w;
};

struct _pppEnvSt
{
    CMemory::CStage* m_stagePtr;       // 0x0
    CMaterialSet* m_materialSetPtr;    // 0x4
    CMapMesh** m_mapMeshPtr;           // 0x8
    pppShapeSt** m_shapeTablePtr;       // 0xC
    pppShapeGroupRaw* m_shapeGroupPtr;  // 0x10
}; // Size 0x14

struct _pppMngSt
{
    _pppMngSt();

    void* m_pppResSet;                 // 0x00
    int m_partIndex;                   // 0x04
    Vec m_position;                    // 0x08
    int m_baseTime;                    // 0x14
    pppIVECTOR3 m_rotation;            // 0x18
    int m_lifeEnd;                     // 0x24
    Vec m_scale;                       // 0x28
    int m_currentFrame;                // 0x34
    float m_userFloat0;                // 0x38
    float m_userFloat1;                // 0x3C
    float m_scaleFactor;               // 0x40
    float m_ownerScale;                // 0x44
    Vec m_userPosition;                // 0x48
    float m_movementScale;             // 0x54
    Vec m_basePosition;                // 0x58
    float m_hitScale;                  // 0x64
    Vec m_paramVec0;                   // 0x68
    short m_kind;                      // 0x74
    short m_nodeIndex;                 // 0x76
    pppFMATRIX m_matrix;               // 0x78
    long m_deltaTime;                  // 0xA8
    int m_spawnedCount;                // 0xAC
    int m_previousFrame2;              // 0xB0
    int m_numControlPrograms;          // 0xB4
    int m_numPrograms;                 // 0xB8
    unsigned int m_objHitMask;         // 0xBC
    unsigned int m_cylinderAttribute;  // 0xC0
    _pppPObjLink m_pppPObjLinkHead;    // 0xC4 (size 0xC)
    void* m_programTable;              // 0xD0
    _pppPDataVal* m_pppPDataVals;      // 0xD4
    CGObject* m_owner;                 // 0xD8
    CGObject* m_lookTarget;            // 0xDC
    CChara::CNode* m_bindNode;         // 0xE0
    unsigned char m_mode;              // 0xE4
    unsigned char m_particleEnded;     // 0xE5
    unsigned char m_isFinished;        // 0xE6
    unsigned char m_matrixMode;        // 0xE7
    unsigned char m_hitBgFlag;         // 0xE8
    unsigned char m_slotVisible;       // 0xE9
    unsigned char m_ownerFacing;       // 0xEA
    unsigned char m_drawVariant;       // 0xEB
    unsigned char m_rotationOrder;     // 0xEC
    signed char m_drawPass;            // 0xED
    signed char m_drawSubType;         // 0xEE
    unsigned char m_useOwnerScaleSign; // 0xEF
    unsigned char m_ownerFlagsInitialized; // 0xF0
    unsigned char m_nodeScaleInitialized;  // 0xF1
    unsigned char m_fieldF2;           // 0xF2
    unsigned char m_padF3[2];          // 0xF3
    unsigned char m_mapTexLoaded;      // 0xF5
    unsigned char m_hasMapRef;         // 0xF6
    unsigned char m_fpBillboard;       // 0xF7
    unsigned char m_prio;              // 0xF8
    unsigned char m_padF9;             // 0xF9
    unsigned short m_prioTime;         // 0xFA
    unsigned char m_padFC[4];          // 0xFC
    int m_paramA;                      // 0x100
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

    Vec& UserPosition() { return m_userPosition; }
    Vec& BasePosition() { return m_basePosition; }
    const Vec& UserPosition() const { return m_userPosition; }
    const Vec& BasePosition() const { return m_basePosition; }
}; // Size: 0x158

void pppEditGetViewPos(Vec*);
void pppEditGetViewMatrix(float (*)[4]);
void pppEditGetProjectionMatrix(float (*)[4]);
void pppEditSetProjection2D();
void pppSetProjection();

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

    _pppMngSt* pppGetFreePppMngSt();
    int pppGetNumFreePppMngSt();
    struct PppPdtSlot;
    PppPdtSlot* pppGetFreePppDataMngSt();

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
    unsigned int pppReadRsd(CChunkFile&, pppModelSt*);
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
    void* pppFileRead(char*, unsigned long&, void*, int);
    void LoadPartNoSyncCalc();
    int pppLoadPtx(const char*, int, int, void*, int);

    void pppLoadPmd(CChunkFile&);
    int pppLoadPmd(const char*);
    void pppLoadPan(CChunkFile&);
    int pppLoadPan(const char*);
    int pppLoadPdt(const char*, int, int, void*, int);

    int pppGetFreeDataMng();
    PPPCREATEPARAM* pppGetDefaultCreateParam();

    int pppCreate0(int, int, PPPCREATEPARAM*, int);
    int pppCreate(int, int, PPPCREATEPARAM*, int);

    int pppGetFreeSlot();
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
    int pppIsDeadCHandle(CCharaPcs::CHandle*);

    void pppDeleteAll();
    void pppDestroyAll();

    int m_editProgramCount;             // 0x00
    int m_editParticleCount;            // 0x04
    unsigned char m_unk8[4];
    int m_editCursorEnabled;            // 0x0C
    int m_cursorRequest;                // 0x10
    unsigned char m_unk14[4];
    Vec m_editorCursorPosition;          // 0x18
    unsigned char m_unk24[4];
    int m_editorCursorX;                // 0x28
    int m_editorCursorY;                // 0x2C
    unsigned char m_unk30[0x174 - 0x30];
    int m_editDrawMode;                 // 0x174
    unsigned char m_unk178[0x1C8 - 0x178];
    unsigned char* m_editNodeNameBuffer;  // 0x1C8
    unsigned char* m_editReceiveCursor; // 0x1CC
    unsigned char m_unk1D0[4];
    void* m_editDataBuffers[0x80];       // 0x1D4
    unsigned char m_unk3D4[4];
    void* m_editTextBuffers[0x80];       // 0x3D8
    unsigned char m_unk5D8[4];
    long* m_editProgramData[0x80];       // 0x5DC
    unsigned char m_unk7DC[8];
    CMaterialSet* m_materialSet;          // 0x7E4
    CTextureSet* m_textureSet;            // 0x7E8
    CParModelSet* m_modelSet;          // 0x7EC
    CParShapeSet* m_shapeSet;          // 0x7F0
    pppModelSt** m_editModelSlots;       // 0x7F4
    pppShapeSt** m_editShapeSlots;       // 0x7F8
    pppShapeGroupRaw* m_editShapeGroups; // 0x7FC
    unsigned char m_unk800[8];
    unsigned char m_editorFlags[3];     // 0x808
    unsigned char m_unk80B;
    CGObject* m_editorObject;           // 0x80C
    unsigned char m_unk810[0x2A18 - 0x810];
    _pppMngSt m_pppMng[0x180];           // 0x2A18

    struct PppPdtSlot
    {
        _pppDataHead* m_pppDataHead;      // 0x00
        _pppEnvSt m_env;                // 0x04
        char m_name[0x20];                // 0x18
    }; // Size 0x38

    PppPdtSlot m_pdtSlots[0x20];          // 0x22E18
    unsigned char m_unk23518[0x4];        // 0x23518
    _pppEnvSt m_pppEnvSt;                 // 0x2351C
    unsigned char m_unk23530[0x20];
    unsigned int m_mngStCount;      // 0x23550
    unsigned int m_debugCounter;    // 0x23554
    int m_isEditMode;               // 0x23558
    int m_unknown;                  // 0x2355C
    int m_lastEnvCmd;               // 0x23560
    float m_envParam;               // 0x23564
    float m_soundNearDistance[8];  // 0x23568
    float m_soundFarDistance[8];   // 0x23588
    unsigned char m_unk235A8[0x14C];      // 0x235A8
    unsigned int m_partAMemBase;          // 0x236F4
    unsigned int m_partAMemCursor;        // 0x236F8
    unsigned int m_partLoadCacheParam;    // 0x236FC
    unsigned int m_partChunkIndex;        // 0x23700
    unsigned int m_asyncHandleCount;      // 0x23704
    int m_partLoadMode;                   // 0x23708
    unsigned int m_partChunkSize[16];     // 0x2370C
    unsigned int m_partChunkChecksum[16]; // 0x2374C
    CFile::CHandle* m_partAsyncBusy[16];  // 0x2378C
    unsigned char m_unk237CC[0x80C];      // 0x237CC
};

extern Mtx ppvCameraMatrix0;
extern Mtx ppvCameraMatrix;
extern Mtx ppvWorldMatrix;
extern Mtx ppvWorldMatrixWood;
extern Mtx ppvFpCameraMatrixWood;
extern Mtx44 ppvScreenMatrix;
extern float ppvScreenMatrix0[4][4];
extern Mtx ppvLightMatrix;
extern Mtx ppvColorMatrix;
extern float ppvChrScl[3];
extern float ppvSinTbl[];
extern CPartMng PartMng;

extern _pppEnvSt* ppvEnv;
extern _pppMngSt* ppvMng;
extern int ppvUserStopPartF;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;

#endif
