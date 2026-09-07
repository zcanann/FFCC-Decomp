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

		u8 _pad[0x64];
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

		union {
			u8 m_flags;                 // 0x08
			struct {
				u8 m_blendEnabled : 1;
				u8 m_clampFrames : 1;
				u8 m_reserved : 6;
			} m_flagsBits;
		};
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

		void Create(CChunkFile&);
		void mapping(CChara::CAnim*);
		void IsScale();
		void Interp(CChara::CAnim*, SRT*, float);

		char m_name[0x10];              // 0x00
		u32 m_dataOffset;               // 0x10
		union {
			u32 m_flags;                // 0x14
			struct {
				u8 m_hasScale : 1;
				u32 m_channelModes : 18;
				u32 m_reserved : 13;
			} m_flagsBits;
		};
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

			Mtx m_localMtx;                 // 0x00
			Mtx m_bindMtx;                  // 0x30
			float m_boneLen;                // 0x60
			s16 m_childBankOffset;          // 0x64
			s16 m_index;                    // 0x66
			s16 m_parentIndex;              // 0x68
			char m_name[0x10];              // 0x6A
			char m_altName[0x10];           // 0x7A
			u8 m_childCount;                // 0x8A
			u8 m_type;                      // 0x8B
			u8 m_bindFlags;                 // 0x8C
			s8 m_displayIndex;              // 0x8D
			u8 m_miscFlags;                 // 0x8E
			u8 m_usesParentLenX;            // 0x8F
			s8 m_dynParamIndex;             // 0x90
			u8 _pad91[0x03];                // 0x91
		};

		void Create(CChunkFile&, CChara::CModel*, CChara::CNode::TYPE, CMemory::CStage*);
		void Duplicate(CChara::CNode*, CMemory::CStage*);
		void CalcBind(CChara::CModel*);

		CRefData* m_refData;
		CMesh* m_displayMesh;
		u8 _pad08[0x0C];
		Mtx m_localRuntimeMtx;
		Quaternion m_previousQuat;
		Vec m_previousPosition;
		Vec m_previousScale;
		Mtx m_mtx;
		CAnimNode* m_animNode0;
		CAnimNode* m_animNode1;
		CVector m_dynPosition;
		CVector m_dynVel;
		union
		{
			u8 m_flags;
			struct
			{
				s8 m_flag_80 : 1;
				s8 m_flag_lo : 7;
			} m_flagsBits;
		};
		u8 _padBD[3];
	};

	class CModel : public CRef
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

			u32 m_nodeCount;            // 0x08
			u32 m_meshCount;           // 0x0C
			void* m_nodeRefData;       // 0x10
			void* m_meshRefData;       // 0x14
			void* m_bank;              // 0x18
			s16 m_headNodeIndex;       // 0x1C
			s16 m_chest3NodeIndex;     // 0x1E
			s16 m_chest2NodeIndex;     // 0x20
			s16 m_chest1NodeIndex;     // 0x22
			CMaterialSet* m_materialSet; // 0x24
			float m_baseScale;         // 0x28
			u8 _pad2C[0x8];            // 0x2C
			u32 m_posQuant;            // 0x34
			u32 m_normQuant;           // 0x38
			u32 m_dynCount;            // 0x3C
			void* m_dynParams;         // 0x40
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
		void CopyFurTex(int loadFromTexture);
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
		void SetBeforeCalcMatrixCallback(int (*callback)(CChara::CModel*, void*, void*))
		{
			m_beforeCalcMatrixCallback = callback;
		}
		void SetCallbackContext(void* context, void* param)
		{
			m_callbackContext = context;
			m_callbackParam = param;
		}

	public:
		Mtx m_matrix;
		Mtx m_worldBaseMtx;
		Mtx m_drawMtx;
		u32 m_meshVisibleMask;
		float m_lightAlpha;
		union
		{
			u8 m_flagsA0;
			struct
			{
				u8 m_flagA0_80 : 1;
				u8 m_flagA0_40 : 1;
				u8 m_flagA0_20 : 1;
				u8 m_flagA0_lo : 5;
			} m_flagsA0Bits;
		};
		u8 m_attachMode;
		u8 _padA2[0x2];
		CRefData* m_data;
		CNode* m_nodes;
		CMesh* m_meshes;
		CTextureSet* m_texSet;
		float m_time;
		float m_curFrame;
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
		union
		{
			u8 m_flags10C;
			struct
			{
				s8 m_flag10C_80 : 1;
				s8 m_flag10C_40 : 1;
				s8 m_flag10C_lo : 6;
			} m_flags10CBits;
		};
		u8 _pad10D[3];
		float m_furLenScale;
		float m_furStep;
		float m_furTarget;
		float m_furCur;
		float m_twistAngle;
	};

	class CMesh : public CRef
	{
	public:
		CMesh();
		~CMesh();

		class CDisplayList
		{
		public:
			CDisplayList();
			~CDisplayList();

			s32 m_size;
			void* m_data;
			u16 m_material;
			u16 _padA;
		};

		class CRefData
		{
		public:
			CRefData();
			~CRefData();

			char m_name[0x10];
			union
			{
				u8 m_flags;
				struct
				{
					s8 m_flag_80 : 1;
					s8 m_flag_40 : 1;
					s8 m_flag_lo : 6;
				} m_flagsBits;
			};
			u8 _pad11[3];
			u32 m_vertexCount;
			S16Vec* m_vertices;
			u32 m_normalCount;
			S16Vec* m_normals;
			u32 m_colorCount;
			u8* m_colors;
			u32 m_uvCount;
			u8* m_uvs;
			u32 m_oneWeightCountOrSize;
			void* m_oneWeightData;
			u32 m_twoWeightCountOrSize;
			void* m_twoWeightData;
			u32 m_threeWeightCountOrSize;
			void* m_threeWeightData;
			u32 m_displayListCount;
			CDisplayList* m_displayLists;
			u32 m_skinCount;
			CSkin* m_skins;
			u32 m_nodeIndex;
			u32 m_infoWord1;
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
    void SetAmemStage(CMemory::CStage* stage) { m_amemLoadStage = stage; }
    CMemory::CStage* GetMemoryStage() { return m_amemStage; }
    u32 GetAmemBaseAddress() const { return m_amemLoadStage->m_heapTop; }
    u32& AmemSize() { return m_amemSize; }
    int GetDrawBufferIndex() const { return m_drawBufferIndex; }
    u32& GetDrawBufferCursor(int index) { return m_drawBuffers[index].m_cursor; }
    u8* GetDrawBufferBase(int index) { return m_drawBuffers[index].m_base; }
    struct CDrawBuffer
    {
        u32 m_cursor;
        u8* m_base;
    };
    CDrawBuffer& GetDrawBuffer(int index) { return m_drawBuffers[index]; }
    u32& AmemAnimSize() { return m_amemAnimSize; }
    u32 GetAmemAnimSize() const { return m_amemAnimSize; }
    void ResetAmem(int) { m_amemSize = 0; }
    void TimeMogFur();
    void CalcMogScore();
    void ChangeMogMode(int);
public:
    struct MogFurState
    {
        u16 m_texels[0x1000];                 // 0x0000
        union
        {
            u32 m_dirty;                      // 0x2000
            int m_commandIndex;
        };
        union
        {
            u32 m_prevRadarType;              // 0x2004
            int m_trackedCommandIndex;
        };
        int m_cursorX;                        // 0x2008
        int m_cursorY;                        // 0x200C
        int m_timestamp;                      // 0x2010
        int m_score[3];                       // 0x2014
        int m_bitScore[3];                    // 0x2020
        int m_lineScore[3];                   // 0x202C
        int m_circleScore[3];                 // 0x2038
        int m_radarLevel[3];                  // 0x2044
        int m_alphaScore;                     // 0x2050
    };

    void freeFurTex();
    void makeFurTex();
    void InitFurTexBuffer();
    void SaveFurTexBuffer(unsigned short* outTexels);
    void LoadFurTexBuffer(unsigned short* inTexels);
    Mtx& FlatPosMtx() { return m_sharedState.m_flat.m_posMtx; }
    MogFurState& MogFur() { return m_sharedState.m_mogFur; }

private:
    union CSharedState
    {
        MogFurState m_mogFur;
        struct FlatState
        {
            u8 _pad00[0x8C];
            Mtx m_posMtx;
        } m_flat;
        u8 m_storage[0x2054];
    };

    CSharedState m_sharedState;               // 0x004
    CMemory::CStage* m_amemStage;             // 0x2058
    union
    {
        CMemory::CStage* m_amemLoadStage;     // 0x205C
        u32 m_amemSize;                       // 0x205C
    };
    int m_drawBufferIndex;                    // 0x2060
    CDrawBuffer m_drawBuffers[2];             // 0x2064
    u32 m_amemAnimSize;                       // 0x2074
};

extern CChara Chara;
extern CChara& gChara;

#endif // _FFCC_CHARA_H_
