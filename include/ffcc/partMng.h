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

struct _pppPObject
{
    s32 m_graphId;              // 0x0
    pppFMATRIX m_localMatrix;   // 0x4 (size 0x30)
    // Additional members may exist
};

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
    char* m_pppName;                 // 0x0
    char* m_unkPtr;                  // 0x4
    void* m_pppFunctionOperation;    // 0x8
    void* m_unkPtr2;                 // 0xC
    CGObject* m_objects[3];          // 0x10
    void* m_pppFunctionConstructor;  // 0x1C
    void* m_pppFunctionConstructor2; // 0x20
    void* m_pppFunctionConstructor3; // 0x24
    void* m_pppFunctionDestructor;   // 0x28
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
    // WIP
    unsigned char m_rotationOrder;
    unsigned char m_matrixMode;
    pppFMATRIX m_matrix;
    pppIVECTOR4 m_rotation;
    void* m_owner;
    unsigned char m_ownerFacing;
    unsigned char m_ownerFlagsInitialized;
    unsigned char m_slotVisible;
    unsigned char m_nodeScaleInitialized;
    unsigned char m_fpBillboard;
    float m_ownerScale;
    unsigned char m_useOwnerScaleSign;
    CChara::CNode* m_bindNode;
    Vec m_position;
    short m_mapObjIndex;
    Vec m_scale;
    // Additional fields (based on offset layout in comments below)
    char padding[0x74 - (0x28 + sizeof(Vec))]; // Fill to offset 0x74
    short m_kind;        // 0x74
    short m_nodeIndex;   // 0x76
    /*
    0x0	0x4	void *	void *	m_pppResSet	
0x4	0x4	int32_t	typedef int32_t int	m_partIndex	
0x8	0xc	Vec	/Dolphin/OS/Math/Vec
pack(disabled)
Structure Vec {
   0   float   4   x   ""
   4   float   4   y   ""
   8   float   4   z   ""
}
Length: 12 Alignment: 1
	m_position	
0x14	0x4	int32_t	typedef int32_t int	m_baseTime	
0x18	0x2	int16_t	typedef int16_t short	m_rotationX	
0x1a	0x2	int16_t	typedef int16_t short	m_rotationY	
0x1c	0x2	int16_t	typedef int16_t short	m_rotationZ	
0x1e	0x2	int16_t	typedef int16_t short	m_rotationW	
0x20	0x4	int32_t	typedef int32_t int		
0x24	0x4	int32_t	typedef int32_t int	m_lifeEnd	
0x28	0xc	Vec	/Dolphin/OS/Math/Vec
pack(disabled)
Structure Vec {
   0   float   4   x   ""
   4   float   4   y   ""
   8   float   4   z   ""
}
Length: 12 Alignment: 1
	m_scale	
0x34	0x4	int32_t	typedef int32_t int	m_currentFrame	
0x38	0x4	int32_t	typedef int32_t int		
0x3c	0x4	int32_t	typedef int32_t int		
0x40	0x4	float	float	m_scaleFactor	
0x44	0x4	float	float	m_ownerScale	
0x48	0x1	??	undefined		
0x49	0x1	??	undefined		
0x4a	0x1	??	undefined		
0x4b	0x1	??	undefined		
0x4c	0x1	??	undefined		
0x4d	0x1	??	undefined		
0x4e	0x1	??	undefined		
0x4f	0x1	??	undefined		
0x50	0x1	??	undefined		
0x51	0x1	??	undefined		
0x52	0x1	??	undefined		
0x53	0x1	??	undefined		
0x54	0x1	??	undefined		
0x55	0x1	??	undefined		
0x56	0x1	??	undefined		
0x57	0x1	??	undefined		
0x58	0x1	??	undefined		
0x59	0x1	??	undefined		
0x5a	0x1	??	undefined		
0x5b	0x1	??	undefined		
0x5c	0x1	??	undefined		
0x5d	0x1	??	undefined		
0x5e	0x1	??	undefined		
0x5f	0x1	??	undefined		
0x60	0x1	??	undefined		
0x61	0x1	??	undefined		
0x62	0x1	??	undefined		
0x63	0x1	??	undefined		
0x64	0x1	??	undefined		
0x65	0x1	??	undefined		
0x66	0x1	??	undefined		
0x67	0x1	??	undefined		
0x68	0x1	??	undefined		
0x69	0x1	??	undefined		
0x6a	0x1	??	undefined		
0x6b	0x1	??	undefined		
0x6c	0x1	??	undefined		
0x6d	0x1	??	undefined		
0x6e	0x1	??	undefined		
0x6f	0x1	??	undefined		
0x70	0x1	??	undefined		
0x71	0x1	??	undefined		
0x72	0x1	??	undefined		
0x73	0x1	??	undefined		
0x74	0x2	int16_t	typedef int16_t short	m_kind	
0x76	0x2	int16_t	typedef int16_t short	m_nodeIndex	
0x78	0x30	pppFMATRIX	typedef pppFMATRIX Mat3x4	m_matrix	
0xa8	0x1	uint8_t	typedef uint8_t uchar	m_envColorR	
0xa9	0x1	uint8_t	typedef uint8_t uchar	m_envColorG	
0xaa	0x1	uint8_t	typedef uint8_t uchar	m_envColorB	
0xab	0x1	uint8_t	typedef uint8_t uchar	m_envColorA	
0xac	0x4	int32_t	typedef int32_t int	m_spawnedCount	
0xb0	0x4	int32_t	typedef int32_t int	m_previousFrame	
0xb4	0x4	int32_t	typedef int32_t int	m_numControlPrograms	
0xb8	0x4	int32_t	typedef int32_t int	m_numPrograms	
0xbc	0x4	uint32_t	typedef uint32_t uint	m_objHitMask	
0xc0	0x4	uint32_t	typedef uint32_t uint	m_cylinderAttribute	
0xc4	0x4	void *	void *	m_pObjList	TODO: _pppPObject* type
0xc8	0x4	void *	void *	m_pDataValList	TODO: _pppPDataVal* type
0xcc	0x4	void *	void *	m_controlProgramTable	
0xd0	0x4	void *	void *	m_programInfoTable	
0xd4	0x4	void *	void *	m_programControlArray
0xd8	0x4	void *	void *	m_owner	
0xdc	0x4	void *	void *	m_lookTarget	
0xe0	0x4	CNode *	CNode *	m_bindNode	
0xe4	0x1	uint8_t	typedef uint8_t uchar	m_mode	
0xe5	0x1	uint8_t	typedef uint8_t uchar	m_particleEnded	
0xe6	0x1	uint8_t	typedef uint8_t uchar	m_isFinished	
0xe7	0x1	uint8_t	typedef uint8_t uchar	m_matrixMode	
0xe8	0x1	uint8_t	typedef uint8_t uchar	m_hitBgFlag	
0xe9	0x1	uint8_t	typedef uint8_t uchar	m_slotVisible	
0xea	0x1	uint8_t	typedef uint8_t uchar	m_ownerFacing	
0xeb	0x1	uint8_t	typedef uint8_t uchar	m_drawVariant	
0xec	0x1	uint8_t	typedef uint8_t uchar	m_rotationOrder	
0xed	0x1	uint8_t	typedef uint8_t uchar	m_drawPass	
0xee	0x1	uint8_t	typedef uint8_t uchar	m_drawSubType	
0xef	0x1	uint8_t	typedef uint8_t uchar	m_useOwnerScaleSign	
0xf0	0x1	uint8_t	typedef uint8_t uchar	m_ownerFlagsInitialized	
0xf1	0x1	uint8_t	typedef uint8_t uchar	m_nodeScaleInitialized	
0xf2	0x1	uint8_t	typedef uint8_t uchar		
0xf3	0x1	uint8_t	typedef uint8_t uchar		
0xf4	0x1	uint8_t	typedef uint8_t uchar		
0xf5	0x1	uint8_t	typedef uint8_t uchar	m_mapTexLoaded	
0xf6	0x1	uint8_t	typedef uint8_t uchar	m_hasMapRef	
0xf7	0x1	uint8_t	typedef uint8_t uchar	m_fpBillboard	
0xf8	0x1	uint8_t	typedef uint8_t uchar	m_prio	
0xf9	0x2	int16_t	typedef int16_t short	m_frameCounter	
0xfb	0x1	??	undefined		
0xfc	0x1	??	undefined		
0xfd	0x1	??	undefined		
0xfe	0x1	??	undefined		
0xff	0x1	??	undefined		
0x100	0x1	??	undefined		
0x101	0x1	??	undefined		
0x102	0x1	??	undefined		
0x103	0x1	??	undefined		
0x104	0x1	??	undefined		
0x105	0x1	??	undefined		
0x106	0x1	??	undefined		
0x107	0x1	??	undefined		
0x108	0x4	float	float	m_cullRadiusSq	
0x10c	0x4	float	float	m_cullRadius	
0x110	0x4	float	float	m_cullYOffset	
0x114	0x4	float	float	m_sortDepth	
0x118	0x1	??	undefined		
0x119	0x1	??	undefined		
0x11a	0x2	int16_t	typedef int16_t short	m_mapObjIndex	
0x11c	0x14	PPPSEST	/Game/Classes/partMng/PPPSEST
pack(disabled)
Structure PPPSEST {
   0   int32_t   4   m_soundEffectSlot   ""
   4   uint8_t   1   m_soundEffectStopFlag   ""
   5   uint8_t   1   m_soundEffectKind   ""
   6   uint8_t   1   m_soundEffectStartedOnce   ""
   7   uint8_t   1   unkSoundEffectRelated   ""
   8   int32_t   4   m_soundEffectStartFrame   ""
   12   int32_t   4   m_soundEffectFadeFrames   ""
   16   int32_t   4   m_soundEffectHandle   ""
}
Length: 20 Alignment: 1
	m_soundEffectData	
0x130	0x8	PPPIFPARAM	/Game/Classes/partMng/PPPIFPARAM
pack(disabled)
Structure PPPIFPARAM {
   0   int32_t   4   m_particleIndex   ""
   4   int16_t   2   m_classId   ""
   6   uint8_t   1   m_hitObjectCount   ""
   7   uint8_t   1   m_hitFlags   ""
}
Length: 8 Alignment: 1
	m_hitParams	
0x138	0x20	int16_t[16]	int16_t[16]	m_hitObjectIds	
    */
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
};

Mtx ppvCameraMatrix0;
Mtx ppvWorldMatrix;
Mtx ppvWorldMatrixWood;

_pppEnvSt* pppEnvStPtr;
_pppMngSt* pppMngStPtr;

#endif
