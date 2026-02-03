#ifndef _FFCC_CHARA_H_
#define _FFCC_CHARA_H_

#include "ffcc/memory.h"

#include <dolphin/mtx.h>

class CChunkFile;
class CTextureSet;
class CMemory;
class CTexAnimSet;
struct Vec;

void D3DXMatrixMultiplyRotate(float (*)[4], float (*)[4], float (*)[4]);
void VECLerp(Vec*, Vec*, Vec*, float);

class CChara
{
	class CModel;

	class CSkin
	{
		CSkin();
		~CSkin();

		void Create(CChunkFile&, CMemory::CStage*);
	};

	class CAnim
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
		void Duplicate(CMemory::CStage*);
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
		void SearchNode(char*);
		void SearchNodeSk(char*);
		void Draw(float (*)[4], int, int);
		void DrawShadow(float (*)[4], int);
		void CalcInterpFrame();
		void CalcSafeNodeWorldMatrix(float (*)[4], CChara::CNode*);
		void AttachAnim(CChara::CAnim*, int, int, int);
		void AttachTextureSet(CTextureSet*);
		void AddFrame(float);
		void SetFrame(float);
		void CalcFurColor();
		void GetDispIndex(CChara::CNode*);
        void GetMatrix();
        void GetMatrix(float(*)[4]);

	private:
		float m_curFrame;
		CAnim* m_anim;
		float m_time;
		float m_animStart;
		float m_animEnd;
	};

	class CMesh
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
	};
	
	CChara();
	~CChara();

	void Init();
	void Quit();
	void Create();
	void Destroy();
	void FlipDBuffer();
	void gqrInit(unsigned long, unsigned long, unsigned long);
    void SetAmemStage(CMemory::CStage*);
    void GetMemoryStage();
    void ResetAmem(int);
};

#endif // _FFCC_CHARA_H_
