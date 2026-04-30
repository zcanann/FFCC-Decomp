#ifndef _FFCC_CHARA_H_
#define _FFCC_CHARA_H_

#include "ffcc/memory.h"
#include "ffcc/ref.h"

#include <dolphin/mtx.h>

class CChunkFile;
class CMaterialSet;
class CTextureSet;
class CMemory;
class CTexAnimSet;
struct Vec;

struct CCharaModelData
{
    u8 _pad0[0x24];
    CMaterialSet* m_materialSet;
};

void D3DXMatrixMultiplyRotate(float (*)[4], float (*)[4], float (*)[4]);
void VECLerp(Vec*, Vec*, Vec*, float);

class CChara : public CManager
{
public:
	class CModel;
	class CMesh;

	class CSkin
	{
		CSkin();
		~CSkin();

		void Create(CChunkFile&, CMemory::CStage*);
	};

	class CAnim : public CRef
	{
		CAnim();
		~CAnim();

        void SetAmemAddress(int);
        void GetBankSize();
        void GetAmemAddress();
        void AddHistory();
        void ReleaseBank();
        void GetHistory();
        void IsBanked();
        void SetLastFrame(int);
        void SetInterp(int);
	};

	class CAnimNode
	{
		CAnimNode();
		~CAnimNode();

		void IsScale();
	};

	class CNode
	{
		enum TYPE
		{
			TODO,
		};

		CNode();
		~CNode();

		class CRefData
		{
			CRefData();
			~CRefData();
		};

		void Create(CChunkFile&, CChara::CModel*, CChara::CNode::TYPE, CMemory::CStage*);
		void Duplicate(CChara::CNode*, CMemory::CStage*);
		void CalcBind(CChara::CModel*);
	};

	class CModel
	{
		CModel();
		~CModel();

		class CRefData
		{
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
		int GetDispIndex(CChara::CNode*);
		void GetMatrix();
		void GetMatrix(float(*)[4]);
		void GetMatrixT(float (*)[4]);
		void SetBeforeMeshLockEnvCallback(void (*)(CChara::CModel*, void*, void*, int));
		void SetDrawMeshDLCallback(void (*)(CChara::CModel*, void*, void*, int, int, float (*)[4]));
		void SetAfterDrawMeshCallback(void (*)(CChara::CModel*, void*, void*, int, float (*)[4]));
		void SetCallbackContext(void*, void*);

	private:
		u8 _pad0[0x68];
		Mtx m_matrix;
		u8 _pad98[0xC];
		CCharaModelData* m_data;
		u8 _padA8[4];
		CMesh* m_meshes;
		CTextureSet* m_texSet;
		float m_curFrame;
		CAnim* m_anim;
		float m_time;
		float m_animStart;
		float m_animEnd;
		u8 _padC8[0x1C];
		void* m_callbackContext;
		void* m_callbackParam;
		u8 _padEC[0x8];
		void (*m_beforeMeshLockEnvCallback)(CChara::CModel*, void*, void*, int);
		u8 _padF8[4];
		void (*m_drawMeshDLCallback)(CChara::CModel*, void*, void*, int, int, float (*)[4]);
		u8 _pad100[4];
		void (*m_afterDrawMeshCallback)(CChara::CModel*, void*, void*, int, float (*)[4]);
	};

	class CMesh : public CRef
	{
		CMesh();
		~CMesh();

		class CRefData
		{
			CRefData();
			~CRefData();
		};

		class CDisplayList
		{
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
    void SetAmemStage(CMemory::CStage*);
    void GetMemoryStage();
    void ResetAmem(int);
    void TimeMogFur();
    void CalcMogScore();
    void ChangeMogMode(int);
public:
    void InitFurTexBuffer();
    void SaveFurTexBuffer(unsigned short* outTexels);
    void LoadFurTexBuffer(unsigned short* inTexels);

private:
    u8 m_work[0x2074];
};

extern CChara Chara;
extern CChara& gChara;

#endif // _FFCC_CHARA_H_
