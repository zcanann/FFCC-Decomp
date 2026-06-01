#ifndef _FFCC_CHARA_H_
#define _FFCC_CHARA_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"
#include "ffcc/vector.h"

#include <dolphin/mtx.h>

class CChunkFile;
class CGObject;
class CMaterialSet;
class CTextureSet;
class CMemory;
class CTexAnimSet;
class SRT;
struct _GXColor;
struct Vec;

struct CCharaModelData
{
    u8 _pad0[0xC];
    u32 m_meshCount;
    u8 _pad10[0x14];
    CMaterialSet* m_materialSet;
    u8 _pad28[0xC];
    u32 m_posQuant;
    u32 m_normQuant;
};

void D3DXMatrixMultiplyRotate(float (*)[4], float (*)[4], float (*)[4]);
void VECLerp(Vec*, Vec*, Vec*, float);

class CChara : public CManager
{
public:
	class CModel;
	class CMesh;
	class CAnimNode;

	class CSkin
	{
	public:
		CSkin();
		~CSkin();

		void Create(CChunkFile&, CMemory::CStage*);
	};

	class CAnim : public CRef
	{
	public:
		CAnim();
		~CAnim();

		void Create(void*, CMemory::CStage*);
        void SetAmemAddress(int);
        void GetBankSize();
        void GetAmemAddress();
        void AddHistory();
        void ReleaseBank();
        void GetHistory();
        void IsBanked();
        void SetLastFrame(int);
        void SetInterp(int);
        void InitQuantize();

		u8 m_flags;                     // 0x08
		char m_interp;                  // 0x09
		u8 m_quantizeX;                 // 0x0A
		u8 m_quantizeY;                 // 0x0B
		u8 m_quantizeZ;                 // 0x0C
		u8 _pad0D;                      // 0x0D
		u16 m_nodeCount;                // 0x0E
		u16 m_frameCount;               // 0x10
		u8 _pad12[0x2];                 // 0x12
		CAnimNode* m_nodes;             // 0x14
		u32 m_interpOffset;             // 0x18
		u32 m_bankSize;                 // 0x1C
		void* m_bank;                   // 0x20
		int m_lastFrame;                // 0x24
		int m_bankAddress;              // 0x28
		CMemory::CStage* m_stage;       // 0x2C
	};

	class CAnimNode
	{
	public:
		CAnimNode();
		~CAnimNode();

		void IsScale();
		void Interp(CChara::CAnim*, SRT*, float);
	};

	class CNode
	{
	public:
		enum TYPE
		{
			TODO,
		};

		CNode();
		~CNode();

		class CRefData
		{
		public:
			CRefData();
			~CRefData();
		};

		void Create(CChunkFile&, CChara::CModel*, CChara::CNode::TYPE, CMemory::CStage*);
		void Duplicate(CChara::CNode*, CMemory::CStage*);
		void CalcBind(CChara::CModel*);

		u8 _pad0[0x14];
		Mtx m_localRuntimeMtx;
		u8 _pad44[0x28];
		Mtx m_mtx;
		u8 _pad9C[0x8];
		CVector m_dynPosition;
		CVector m_dynVel;
		u8 m_flags;
		u8 _padBD[3];
	};

	class CModel
	{
	public:
		typedef int (*BeforeCalcMatrixCallback)(CChara::CModel*, void*, void*);
		typedef void (*AfterMeshDrawCallback)(CChara::CModel*, void*, void*, unsigned int, unsigned int, float (*)[4]);
		typedef void (*BeforeMeshLockEnvCallback)(CChara::CModel*, void*, void*, int);
		typedef void (*DrawMeshDLCallback)(CChara::CModel*, void*, void*, int, int, float (*)[4]);
		typedef void (*AfterDrawMeshCallback)(CChara::CModel*, void*, void*, int, float (*)[4]);

		CModel();
		~CModel();

		class CRefData : public CRef
		{
		public:
			CRefData();
			~CRefData();
		};

		void Init();
		void Create(void*, CMemory::CStage*);
		void CreateDynamics(void*, CMemory::CStage*);
		void setup();
		CChara::CModel* Duplicate(CMemory::CStage*);
		void calcBindMatrix();
		void CalcMatrix();
		void CalcSkin();
		void calcNowFrame();
		void calcMatrix();
		void CalcNodeWorldMatrix(float (*) [4], CChara::CNode*);
		void CalcFrameMatrix(float, CChara::CNode*, float (*)[4]);
		void dynamics(CChara::CNode*, CChara::CNode*);
		void calcSkin();
		void SetMatrix(float (*)[4]);
		int SearchNode(char*);
		int SearchNodeSk(char*);
		void Draw(float (*)[4], int, int);
		void DrawShadow(float (*)[4], int);
		void CalcInterpFrame();
		void CalcSafeNodeWorldMatrix(float (*)[4], CChara::CNode*);
		void AttachAnim(CChara::CAnim*, int, int, int);
		void AttachTextureSet(CTextureSet*);
		CMesh* GetMesh();
		void AddFrame(float);
		void SetFrame(float);
		void CalcFurColor();
		void InitMogFurTex();
		void MogFurFrame(CGObject*);
		int PickFur(float (*)[4], _GXColor, int, int, _GXColor*, _GXColor*, Vec*);
		void DrawFur(float (*)[4], int);
		int GetDispIndex(CChara::CNode*);
		void GetMatrix();
		void GetMatrix(float(*)[4]);
		void GetMatrixT(float (*)[4]);
		void SetBeforeMeshLockEnvCallback(void (*callback)(CChara::CModel*, void*, void*, int))
		{
			m_beforeMeshLockEnvCallback = callback;
		}
		void SetDrawMeshDLCallback(void (*callback)(CChara::CModel*, void*, void*, int, int, float (*)[4]))
		{
			m_drawMeshDLCallback = callback;
		}
		void SetAfterDrawMeshCallback(void (*callback)(CChara::CModel*, void*, void*, int, float (*)[4]))
		{
			m_afterDrawMeshCallback = callback;
		}
		void SetCallbackContext(void* context, void* param)
		{
			m_callbackContext = context;
			m_callbackParam = param;
		}

	public:
		u8 _pad0[0x8];
		Mtx m_matrix;
		u8 _pad38[0xC];
		Mtx m_worldBaseMtx;
		u8 _pad74[0x24];
		u32 m_meshVisibleMask;
		float m_lightAlpha;
		u8 m_flagsA0;
		u8 m_attachMode;
		u8 _padA2[0x2];
		CCharaModelData* m_data;
		CNode* m_nodes;
		CMesh* m_meshes;
		CTextureSet* m_texSet;
		float m_curFrame;
		float m_time;
		float m_animStart;
		float m_animEnd;
		CVector m_dynJitter;
		CAnim* m_anim;
		CTexAnimSet* m_texAnimSet;
		u16 m_blendCur;
		u16 m_blendMax;
		float m_chestTilt;
		float m_chestAmp;
		void* m_callbackContext;
		void* m_callbackParam;
		BeforeCalcMatrixCallback m_beforeCalcMatrixCallback;
		AfterMeshDrawCallback m_afterMeshDrawCallback;
		BeforeMeshLockEnvCallback m_beforeMeshLockEnvCallback;
		BeforeMeshLockEnvCallback m_beforeDrawShadowLockEnvCallback;
		DrawMeshDLCallback m_drawMeshDLCallback;
		DrawMeshDLCallback m_drawShadowMeshDLCallback;
		AfterDrawMeshCallback m_afterDrawMeshCallback;
		void (*m_afterDrawModelCallback)(CChara::CModel*, void*, void*);
		u8 m_flags10C;
		u8 _pad10D[3];
		float m_furStep;
		float m_furLenScale;
		float m_furTarget;
		float m_furCur;
		float m_twistAngle;
	};

	class CMesh : public CRef
	{
	public:
		CMesh();
		~CMesh();

		class CRefData
		{
		public:
			CRefData();
			~CRefData();
		};

		class CDisplayList
		{
		public:
			CDisplayList();
			~CDisplayList();
		};

		void Create(CChara::CModel*, CChunkFile&, CMemory::CStage*);
		void Duplicate(CChara::CMesh*, CMemory::CStage*);
		void skin(int, int, int, CChara::CSkin*, void*, void*, void*, S16Vec*, S16Vec*, S16Vec*, S16Vec*);
		void Calc(CChara::CModel*);
		CRefData* GetRefData();
		S16Vec* GetVertex();

		CRefData* m_data;
		S16Vec* m_workPositions;
		S16Vec* m_workNormals;
	};
	
	CChara() {}

	void Init();
	void Quit();
	void Create();
	void Destroy();
	void FlipDBuffer();
	void gqrInit(unsigned long, unsigned long, unsigned long);
    void SetAmemStage(CMemory::CStage* stage) { m_amemStage = stage; }
    CMemory::CStage* GetMemoryStage() { return m_amemStage; }
    u32& AmemSize() { return m_amemSize; }
    int GetDrawBufferIndex() const { return m_drawBufferIndex; }
    u32& GetDrawBufferCursor(int index) { return m_drawBuffers[index].m_cursor; }
    u8* GetDrawBufferBase(int index) { return m_drawBuffers[index].m_base; }
    u32 GetAmemAnimSize() const { return m_amemAnimSize; }
    void ResetAmem(int) { m_amemSize = 0; }
    void TimeMogFur();
    void CalcMogScore();
    void ChangeMogMode(int);
public:
    void freeFurTex();
    void makeFurTex();
    void InitFurTexBuffer();
    void SaveFurTexBuffer(unsigned short* outTexels);
    void LoadFurTexBuffer(unsigned short* inTexels);
    Mtx& FlatPosMtx() { return m_flatPosMtx; }

private:
    struct CDrawBuffer
    {
        u32 m_cursor;
        u8* m_base;
    };

    u8 _pad004[0x8C];                         // 0x004
    Mtx m_flatPosMtx;                         // 0x090
    u8 _pad0C0[0x1F98];                       // 0x0C0
    CMemory::CStage* m_amemStage;             // 0x2058
    u32 m_amemSize;                           // 0x205C
    int m_drawBufferIndex;                    // 0x2060
    CDrawBuffer m_drawBuffers[2];             // 0x2064
    u32 m_amemAnimSize;                       // 0x2074
};

extern CChara Chara;
extern CChara& gChara;

#endif // _FFCC_CHARA_H_
