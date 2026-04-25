#include "ffcc/chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_light.h"
#include "ffcc/texanim.h"

#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <math.h>
#include <string.h>

extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, void*);
extern "C" void freeFurTex__6CCharaFv();
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);
extern "C" void Calc__Q26CChara5CMeshFPQ26CChara6CModel(void*, void*);
extern "C" void Create__Q26CChara5CNodeFR10CChunkFilePQ26CChara6CModelQ36CChara5CNode4TYPEPQ27CMemory6CStage(
    void*, CChunkFile&, void*, int, CMemory::CStage*);
extern "C" void Create__Q26CChara5CMeshFPQ26CChara6CModelR10CChunkFilePQ27CMemory6CStage(
    void*, void*, CChunkFile&, CMemory::CStage*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __ct__Q26CChara5CNodeFv(void*);
extern "C" void __dt__Q26CChara5CNodeFv(void*, int);
extern "C" void __ct__Q26CChara5CMeshFv(void*);
extern "C" void __dt__Q26CChara5CMeshFv(void*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __ct__7CVectorFv(void*);
extern "C" void Printf__7CSystemFPce(CSystem*, const char*, ...);
extern "C" void InitQuantize__Q26CChara5CAnimFv(void*);
extern "C" void Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf(void*, void*, void*, float);
extern "C" void SetTextureSet__12CMaterialSetFP11CTextureSet(CMaterialSet*, CTextureSet*);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" float FLOAT_803301b0;
extern "C" float FLOAT_803301bc;
extern "C" float FLOAT_803301c8;
extern "C" float FLOAT_803301cc;
extern "C" float FLOAT_803301d0;
extern "C" float FLOAT_803301e4;
extern "C" float FLOAT_803301e8;
extern "C" float FLOAT_803301f8;
extern "C" CLightPcs::CBumpLight* DAT_8032edc0;

namespace {

struct CCharaDisplayListRaw
{
	void* m_data;
	s32 m_size;
	u16 m_material;
	u16 _padA;
};

struct SRTView
{
	Vec m_position;
	Vec m_rotation;
	Vec m_scale;
};

struct CCharaMeshRefRaw
{
	char m_name[0x10];
	u8 m_flags;
	u8 _pad11[3];
	u32 m_vertexCount;
	S16Vec* m_vertices;
	u32 m_normalCount;
	S16Vec* m_normals;
	u32 m_colorCount;
	void* m_colors;
	u32 m_uvCount;
	void* m_uvs;
	u32 m_oneWeightCountOrSize;
	void* m_oneWeightData;
	u32 m_twoWeightCountOrSize;
	void* m_twoWeightData;
	u32 m_threeWeightCountOrSize;
	void* m_threeWeightData;
	u32 m_displayListCount;
	CCharaDisplayListRaw* m_displayLists;
	u32 m_skinCount;
	CLightPcs::CBumpLight* m_skins;
	u32 m_infoWord1;
	u32 m_nodeIndex;
};

struct CCharaMeshRaw
{
	CCharaMeshRefRaw* m_data;
	S16Vec* m_workPositions;
	S16Vec* m_workNormals;
	u8 _padC[8];
};

typedef void (*BeforeDrawModelCallback)(CChara::CModel*, void*, void*, float (*)[4], unsigned int);
typedef void (*AfterDrawModelCallback)(CChara::CModel*, void*, void*);
typedef int (*BeforeCalcMatrixCallback)(CChara::CModel*, void*, void*);
typedef void (*BeforeMeshCallback)(CChara::CModel*, void*, void*, unsigned int);
typedef void (*AfterMeshDrawCallback)(CChara::CModel*, void*, void*, unsigned int, unsigned int, float (*)[4]);
typedef void (*AfterMeshEnvCallback)(CChara::CModel*, void*, void*, unsigned int, float (*)[4]);
typedef void (*CustomMeshDrawCallback)(CChara::CModel*, void*, void*, unsigned int);

static inline u8* ModelRaw(CChara::CModel* model)
{
	return reinterpret_cast<u8*>(model);
}

static inline void* ModelRef(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0xA4);
}

static inline u16 ModelMeshCount(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x0A);
}

static inline u16 ModelNodeCount(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x08);
}

static inline CMaterialSet* ModelMaterialSet(CChara::CModel* model)
{
	return *reinterpret_cast<CMaterialSet**>(reinterpret_cast<u8*>(ModelRef(model)) + 0x20);
}

static inline int ModelPosQuant(CChara::CModel* model)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x2C);
}

static inline int ModelNormQuant(CChara::CModel* model)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x30);
}

static inline CCharaMeshRaw* ModelMeshes(CChara::CModel* model)
{
	return *reinterpret_cast<CCharaMeshRaw**>(ModelRaw(model) + 0xAC);
}

static inline CChara::CNode* ModelNodes(CChara::CModel* model)
{
	return *reinterpret_cast<CChara::CNode**>(ModelRaw(model) + 0xA8);
}

static inline void* ModelBank(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(reinterpret_cast<u8*>(ModelRef(model)) + 0x14);
}

static inline float (*ModelDrawMtx(CChara::CModel* model))[4]
{
	return reinterpret_cast<float(*)[4]>(ModelRaw(model) + 0x08);
}

static inline float (*ModelWorldBaseMtx(CChara::CModel* model))[4]
{
	return reinterpret_cast<float(*)[4]>(ModelRaw(model) + 0x44);
}

static inline float ModelLightAlpha(CChara::CModel* model)
{
	return *reinterpret_cast<float*>(ModelRaw(model) + 0x9C);
}

static inline u32 ModelMeshVisibleMask(CChara::CModel* model)
{
	return *reinterpret_cast<u32*>(ModelRaw(model) + 0x98);
}

static inline void*& ModelDynParams(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(reinterpret_cast<u8*>(ModelRef(model)) + 0x34);
}

static inline u32& ModelDynCount(CChara::CModel* model)
{
	return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x38);
}

static inline u8 ModelFlagsA0(CChara::CModel* model)
{
	return *(ModelRaw(model) + 0xA0);
}

static inline u8& ModelFlags10C(CChara::CModel* model)
{
	return *(ModelRaw(model) + 0x10C);
}

static inline Vec& ModelDynJitter(CChara::CModel* model)
{
	return *reinterpret_cast<Vec*>(ModelRaw(model) + 0xC4);
}

static inline CTexAnimSet* ModelTexAnimSet(CChara::CModel* model)
{
	return *reinterpret_cast<CTexAnimSet**>(ModelRaw(model) + 0xD4);
}

static inline u16& ModelBlendCur(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(ModelRaw(model) + 0xD8);
}

static inline u16& ModelBlendMax(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(ModelRaw(model) + 0xDA);
}

static inline float& ModelChestTilt(CChara::CModel* model)
{
	return *reinterpret_cast<float*>(ModelRaw(model) + 0xDC);
}

static inline float& ModelChestAmp(CChara::CModel* model)
{
	return *reinterpret_cast<float*>(ModelRaw(model) + 0xE0);
}

static inline void* ModelCalcCbUser0(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0xE4);
}

static inline void* ModelCalcCbUser1(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0xE8);
}

static inline BeforeCalcMatrixCallback ModelBeforeCalcMatrixCallback(CChara::CModel* model)
{
	return *reinterpret_cast<BeforeCalcMatrixCallback*>(ModelRaw(model) + 0xEC);
}

static inline BeforeDrawModelCallback ModelBeforeDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<BeforeDrawModelCallback*>(ModelRaw(model) + 0xE4);
}

static inline AfterDrawModelCallback ModelAfterDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterDrawModelCallback*>(ModelRaw(model) + 0xE8);
}

static inline BeforeMeshCallback ModelBeforeMeshCallback(CChara::CModel* model)
{
	return *reinterpret_cast<BeforeMeshCallback*>(ModelRaw(model) + 0xEC);
}

static inline AfterMeshDrawCallback ModelAfterMeshDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshDrawCallback*>(ModelRaw(model) + 0xF0);
}

static inline AfterMeshEnvCallback ModelAfterMeshEnvCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshEnvCallback*>(ModelRaw(model) + 0xF4);
}

static inline CustomMeshDrawCallback ModelCustomMeshDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<CustomMeshDrawCallback*>(ModelRaw(model) + 0xFC);
}

static inline AfterMeshDrawCallback ModelShadowDisplayListCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshDrawCallback*>(ModelRaw(model) + 0x100);
}

static inline void* ModelCbUser0(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0x104);
}

static inline void* ModelCbUser1(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0x108);
}

static inline float& ModelTwistAngle(CChara::CModel* model)
{
	return *reinterpret_cast<float*>(ModelRaw(model) + 0x120);
}

static inline u8* MaterialManRaw()
{
	return reinterpret_cast<u8*>(&MaterialMan);
}

static inline u8* CharaRaw()
{
	return reinterpret_cast<u8*>(&gChara);
}

static inline int CharaDrawBufferIndex()
{
	return *reinterpret_cast<int*>(CharaRaw() + 0x2060);
}

static inline u32& CharaDrawBufferCursor(int bufferIndex)
{
	return *reinterpret_cast<u32*>(CharaRaw() + 0x2064 + bufferIndex * 8);
}

static inline u8* CharaDrawBufferBase(int bufferIndex)
{
	return *reinterpret_cast<u8**>(CharaRaw() + 0x2068 + bufferIndex * 8);
}

static inline u32 AlignCharaWorkBytes(u32 size)
{
	return (size + 0x1F) & ~0x1Fu;
}

static inline void InitCharaMaterialState()
{
	u8* raw = MaterialManRaw();

	*reinterpret_cast<u32*>(raw + 72) = 0x000ACE0F;
	*reinterpret_cast<u32*>(raw + 68) = 0xFFFFFFFF;
	raw[76] = 0xFF;
	*reinterpret_cast<u32*>(raw + 296) = 0;
	*reinterpret_cast<u32*>(raw + 284) = 0;
	*reinterpret_cast<u32*>(raw + 300) = 0x1E;
	*reinterpret_cast<u32*>(raw + 288) = 0x1E;
	*reinterpret_cast<u32*>(raw + 304) = 0;
	*reinterpret_cast<u32*>(raw + 292) = 0;
	raw[517] = 0xFF;
	raw[518] = 0xFF;
	*reinterpret_cast<u32*>(raw + 88) = 0;
	*reinterpret_cast<u32*>(raw + 92) = 0;
	raw[520] = 0;
}

static inline void CopyCharaMaterialEnv()
{
	u8* raw = MaterialManRaw();

	*reinterpret_cast<u32*>(raw + 296) = *reinterpret_cast<u32*>(raw + 284);
	*reinterpret_cast<u32*>(raw + 300) = *reinterpret_cast<u32*>(raw + 288);
	*reinterpret_cast<u32*>(raw + 304) = *reinterpret_cast<u32*>(raw + 292);
	*reinterpret_cast<u32*>(raw + 64) = *reinterpret_cast<u32*>(raw + 72);
}

static inline void SetMaterialManNormalArray(void* normals)
{
	*reinterpret_cast<void**>(MaterialManRaw() + 4) = normals;
}

static inline u32 CharaFourCC(char a, char b, char c, char d)
{
	return (static_cast<u32>(a) << 24) | (static_cast<u32>(b) << 16) | (static_cast<u32>(c) << 8) | static_cast<u32>(d);
}

static inline char* NodeRefName(CChara::CNode* node)
{
	return reinterpret_cast<char*>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x74);
}

static inline char* NodeRefAltName(CChara::CNode* node)
{
	return reinterpret_cast<char*>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x84);
}

static inline u8& NodeDynParamIndex(CChara::CNode* node)
{
	return *(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x64);
}

static inline u16 NodeRefIndex(CChara::CNode* node)
{
	return *reinterpret_cast<u16*>(*reinterpret_cast<void**>(node));
}

static inline s16 NodeParentIndex(CChara::CNode* node)
{
	return *reinterpret_cast<s16*>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x68);
}

static inline u8 NodeChildCount(CChara::CNode* node)
{
	return *(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x6A);
}

static inline u16 NodeChildBankOffset(CChara::CNode* node)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x6C);
}

static inline u8 NodeUsesParentLenX(CChara::CNode* node)
{
	return *(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x6E);
}

static inline float NodeBoneLen(CChara::CNode* node)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x70);
}

static inline MtxPtr NodeWorldMtx(CChara::CNode* node)
{
	return reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(node) + 0x44);
}

static inline MtxPtr NodeLocalRuntimeMtx(CChara::CNode* node)
{
	return reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(node) + 0x14);
}

static inline Vec& NodeDynPosition(CChara::CNode* node)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(node) + 0xA4);
}

static inline Vec& NodeDynVelocity(CChara::CNode* node)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(node) + 0xB0);
}

static inline MtxPtr NodeRefLocalMtx(CChara::CNode* node)
{
	return reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(node)) + 0x0C);
}

static inline float ModelBaseScale(CChara::CModel* model)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x28);
}

static inline u16& ModelHeadIndex(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x16);
}

static inline u16& ModelChest3Index(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x18);
}

static inline u16& ModelChest2Index(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x1A);
}

static inline u16& ModelChest1Index(CChara::CModel* model)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(ModelRef(model)) + 0x1C);
}

static inline float TexAnimSetChin(CTexAnimSet* texAnimSet)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(texAnimSet) + 0x24);
}

static inline Quaternion& NodePreviousQuat(CChara::CNode* node)
{
	return *reinterpret_cast<Quaternion*>(reinterpret_cast<u8*>(node) + 0x74);
}

static inline Vec& NodePreviousPosition(CChara::CNode* node)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(node) + 0x84);
}

static inline Vec& NodePreviousScale(CChara::CNode* node)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<u8*>(node) + 0x90);
}

static inline CChara::CAnimNode*& NodeAnimNode0(CChara::CNode* node)
{
	return *reinterpret_cast<CChara::CAnimNode**>(reinterpret_cast<u8*>(node) + 0x9C);
}

static inline CChara::CAnimNode*& NodeAnimNode1(CChara::CNode* node)
{
	return *reinterpret_cast<CChara::CAnimNode**>(reinterpret_cast<u8*>(node) + 0xA0);
}

static inline u8& NodeRuntimeFlags(CChara::CNode* node)
{
	return *(reinterpret_cast<u8*>(node) + 0xBC);
}

static inline u8 AnimFlags(CChara::CAnim* anim)
{
	return *(reinterpret_cast<u8*>(anim) + 0x08);
}

static inline u8 AnimInterpCount(CChara::CAnim* anim)
{
	return *(reinterpret_cast<u8*>(anim) + 0x09);
}

static inline u16 AnimFrameCount(CChara::CAnim* anim)
{
	return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(anim) + 0x10);
}

static inline CChara::CAnimNode* AnimNodes(CChara::CAnim* anim)
{
	return *reinterpret_cast<CChara::CAnimNode**>(reinterpret_cast<u8*>(anim) + 0x14);
}

static inline u32 AnimInterpOffset(CChara::CAnim* anim)
{
	return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(anim) + 0x18);
}

static inline void* AnimBank(CChara::CAnim* anim)
{
	return *reinterpret_cast<void**>(reinterpret_cast<u8*>(anim) + 0x20);
}

static inline char* AnimNodeName(CChara::CAnimNode* node)
{
	return reinterpret_cast<char*>(node);
}

static inline bool AnimNodeUsesScale(CChara::CAnimNode* node)
{
	return *reinterpret_cast<s8*>(reinterpret_cast<u8*>(node) + 0x14) < 0;
}

static inline u8 ModelAttachMode(CChara::CModel* model)
{
	return *(reinterpret_cast<u8*>(model) + 0xA1);
}

static inline void ReleaseRefCounted(void* refObject)
{
	if (refObject == 0) {
		return;
	}

	int* refData = reinterpret_cast<int*>(refObject);
	int refCount = refData[1] - 1;
	refData[1] = refCount;
	if (refCount == 0) {
		(*(void (**)(void*, int))(*refData + 8))(refObject, 1);
	}
}

static inline void RetainRefCounted(void* refObject)
{
	if (refObject != 0) {
		reinterpret_cast<int*>(refObject)[1]++;
	}
}

static CChara::CNode* AllocateCharaNodeArray(u16 nodeCount, CMemory::CStage* stage)
{
	void* block = __nwa__FUlPQ27CMemory6CStagePci(
	    static_cast<unsigned long>(nodeCount) * 0xC0 + 0x10, stage, const_cast<char*>("chara.cpp"), 0x263);
	if (block == 0) {
		return 0;
	}

	return reinterpret_cast<CChara::CNode*>(__construct_new_array(
	    block, reinterpret_cast<ConstructorDestructor>(__ct__Q26CChara5CNodeFv),
	    reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara5CNodeFv), 0xC0, nodeCount));
}

static CChara::CMesh* AllocateCharaMeshArray(u16 meshCount, CMemory::CStage* stage)
{
	void* block = __nwa__FUlPQ27CMemory6CStagePci(
	    static_cast<unsigned long>(meshCount) * 0x14 + 0x10, stage, const_cast<char*>("chara.cpp"), 0x26C);
	if (block == 0) {
		return 0;
	}

	return reinterpret_cast<CChara::CMesh*>(__construct_new_array(
	    block, reinterpret_cast<ConstructorDestructor>(__ct__Q26CChara5CMeshFv),
	    reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara5CMeshFv), 0x14, meshCount));
}

static void CopyDuplicatedNodeState(CChara::CNode* dst, CChara::CNode* src)
{
	*reinterpret_cast<void**>(dst) = *reinterpret_cast<void**>(src);
	PSMTXCopy(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(src) + 8),
	          reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(dst) + 8));
	PSMTXCopy(NodeWorldMtx(src), NodeWorldMtx(dst));
	NodePreviousQuat(dst) = NodePreviousQuat(src);
	NodePreviousPosition(dst) = NodePreviousPosition(src);
	NodePreviousScale(dst) = NodePreviousScale(src);
	NodeAnimNode0(dst) = 0;
	NodeAnimNode1(dst) = 0;
	NodeRuntimeFlags(dst) = (NodeRuntimeFlags(dst) & 0x7F) | (NodeRuntimeFlags(src) & 0x80);
}

static void CalcOneBindNode(CChara::CNode* node, CChara::CModel* model)
{
	void* ref = *reinterpret_cast<void**>(node);
	s16 parent = NodeParentIndex(node);
	if (parent < 0) {
		PSMTXCopy(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(ref) + 0xC),
		          reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(ref) + 0x3C));
	} else {
		CChara::CNode* parentNode = ModelNodes(model) + parent;
		PSMTXConcat(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(parentNode)) + 0x3C),
		            reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(ref) + 0xC),
		            reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(ref) + 0x3C));
	}
	PSMTXCopy(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(ref) + 0x3C), NodeWorldMtx(node));
}

static CChara::CNode* GetBindChildNode(CChara::CModel* model, CChara::CNode* node, int childIndex)
{
	u8* bank = reinterpret_cast<u8*>(ModelBank(model));
	u16 nodeIndex = *reinterpret_cast<u16*>(bank + NodeChildBankOffset(node) + childIndex * 2);
	return ModelNodes(model) + nodeIndex;
}

static void CopyDuplicatedMeshState(CChara::CMesh* dst, CChara::CMesh* src)
{
	u8* srcRaw = reinterpret_cast<u8*>(src);
	u8* dstRaw = reinterpret_cast<u8*>(dst);

	*reinterpret_cast<void**>(dstRaw) = *reinterpret_cast<void**>(srcRaw);
	*reinterpret_cast<void**>(dstRaw + 4) = 0;
	*reinterpret_cast<void**>(dstRaw + 8) = 0;
}

static const char s_chara_cpp_801d90c8[] = "chara.cpp";
static const char s_charaMeshWorkOverflow[] = "chara mesh work buffer overflow\n";
static int s_charaMeshWorkWarnArmed = 1;
static bool s_charaMeshWorkOverflowSeen = false;

} // namespace

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void D3DXMatrixMultiplyRotate(float (*out)[4], float (*a)[4], float (*b)[4])
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			out[r][c] = (a[r][0] * b[0][c]) + (a[r][1] * b[1][c]) + (a[r][2] * b[2][c]);
		}
	}
	out[0][3] = a[0][3];
	out[1][3] = a[1][3];
	out[2][3] = a[2][3];
}


/*
 * --INFO--
 * PAL Address: 0x80073a0c
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::Init()
{
	*(void**)((u8*)this + 0x2058) = 0;
	*(u32*)((u8*)this + 0x205c) = 0;
	*(void**)((u8*)this + 0x2068) = new u8[0x58000];
	*(void**)((u8*)this + 0x2070) = new u8[0x58000];
	*(s32*)((u8*)this + 0x2060) = 1;
	FlipDBuffer();
	*(u32*)((u8*)this + 0x2074) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800739a4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::Quit()
{
	void** buf0 = (void**)((u8*)this + 0x2068);
	void** buf1 = (void**)((u8*)this + 0x2070);
	if (*buf0 != 0) {
		__dla__FPv(*buf0);
		*buf0 = 0;
	}
	if (*buf1 != 0) {
		__dla__FPv(*buf1);
		*buf1 = 0;
	}
	*(void**)((u8*)this + 0x2058) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80073970
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::Create()
{
	InitFurTexBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x80073950
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::Destroy()
{
	freeFurTex__6CCharaFv();
}

/*
 * --INFO--
 * PAL Address: 0x8007392c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::FlipDBuffer()
{
	s32* dbufferIndex = (s32*)((u8*)this + 0x2060);
	*dbufferIndex = 1 - *dbufferIndex;

	u8* self = (u8*)this;
	self += *dbufferIndex << 3;
	*(u32*)(self + 0x2064) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006eb04
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::gqrInit(unsigned long, unsigned long, unsigned long)
{
	asm {
		mtspr GQR5, r4
		mtspr GQR6, r5
		mtspr GQR7, r6
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel::CRefData::CRefData()
{
	memset(this, 0, 0x44);
	*(u16*)((u8*)this + 0x16) = 0xFFFF;
	*(u16*)((u8*)this + 0x18) = 0xFFFF;
	*(u16*)((u8*)this + 0x1A) = 0xFFFF;
	*(u16*)((u8*)this + 0x1C) = 0xFFFF;
	*(float*)((u8*)this + 0x28) = 1.0f;
	*(u32*)((u8*)this + 0x2C) = 7;
	*(u32*)((u8*)this + 0x30) = 0xC;
}

/*
 * --INFO--
 * PAL Address: 0x80073818
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel::CRefData::~CRefData()
{
	void** data = (void**)this;
	for (int i = 0; i < 5; i++) {
		if (data[i] != 0) {
			__dla__FPv(data[i]);
			data[i] = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800736e4
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel::CModel()
{
	memset(this, 0, 0x124);
	PSMTXIdentity((float(*)[4])((u8*)this + 0x14));
	*(float*)((u8*)this + 0x110) = 0.0f;
	*(float*)((u8*)this + 0x114) = 1.0f;
	*(u8*)((u8*)this + 0x10C) = (*(u8*)((u8*)this + 0x10C) & 0x7F) | 0x80;
	*(u8*)((u8*)this + 0xA0) &= 0x7F;
	*(u8*)((u8*)this + 0xA0) &= 0xBF;
	*(u8*)((u8*)this + 0xA0) = (*(u8*)((u8*)this + 0xA0) & 0xDF) | 0x20;
	*(u8*)((u8*)this + 0x10C) &= 0xBF;
	*(float*)((u8*)this + 0x118) = 1.0f;
	*(float*)((u8*)this + 0x11C) = 1.0f;
	*(u8*)((u8*)this + 0xA1) = 0;
	*(float*)((u8*)this + 0x120) = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80073540
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel::~CModel()
{
	void*& texSet = *reinterpret_cast<void**>((u8*)this + 0xB4);
	if (texSet != 0) {
		ReleaseRefCounted(texSet);
		texSet = 0;
	}

	void*& anim = *reinterpret_cast<void**>((u8*)this + 0xD0);
	if (anim != 0) {
		ReleaseRefCounted(anim);
		anim = 0;
	}

	void*& texAnimSet = *reinterpret_cast<void**>((u8*)this + 0xD4);
	if (texAnimSet != 0) {
		ReleaseRefCounted(texAnimSet);
		texAnimSet = 0;
	}

	void*& refData = *reinterpret_cast<void**>((u8*)this + 0xA4);
	if (refData != 0) {
		ReleaseRefCounted(refData);
		refData = 0;
	}

	void*& nodes = *reinterpret_cast<void**>((u8*)this + 0xA8);
	if (nodes != 0) {
		__destroy_new_array(nodes, reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara5CNodeFv));
		nodes = 0;
	}

	void*& meshes = *reinterpret_cast<void**>((u8*)this + 0xAC);
	if (meshes != 0) {
		__destroy_new_array(meshes, reinterpret_cast<ConstructorDestructor>(__dt__Q26CChara5CMeshFv));
		meshes = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80073480
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::Init()
{
	*(float*)((u8*)this + 0xB4) = 0.0f;
	*(float*)((u8*)this + 0xB8) = 0.0f;
	*(float*)((u8*)this + 0xC4) = 0.0f;
	*(float*)((u8*)this + 0xC8) = 0.0f;
	*(float*)((u8*)this + 0xCC) = 0.0f;
	*(u16*)((u8*)this + 0xD8) = 0;
	*(u16*)((u8*)this + 0xDA) = 0;
	*(u32*)((u8*)this + 0x98) = 0xFFFFFFFF;
	*(float*)((u8*)this + 0xBC) = 0.0f;
	*(float*)((u8*)this + 0xC0) = 0.0f;
	*(float*)((u8*)this + 0xE0) = 0.0f;
	*(float*)((u8*)this + 0xDC) = 0.0f;
	*(float*)((u8*)this + 0x9C) = 1.0f;
	*(void**)((u8*)this + 0xE4) = 0;
	*(void**)((u8*)this + 0xE8) = 0;
	*(void**)((u8*)this + 0xEC) = 0;
	*(void**)((u8*)this + 0xF0) = 0;
	*(void**)((u8*)this + 0xF4) = 0;
	*(void**)((u8*)this + 0xF8) = 0;
	*(void**)((u8*)this + 0xFC) = 0;
	*(void**)((u8*)this + 0x100) = 0;
	*(void**)((u8*)this + 0x104) = 0;
	*(void**)((u8*)this + 0x108) = 0;
	*(u8*)((u8*)this + 0x10C) = (*(u8*)((u8*)this + 0x10C) & 0x7F) | 0x80;
	*(u8*)((u8*)this + 0xA0) &= 0x7F;
	*(u8*)((u8*)this + 0xA0) &= 0xBF;
	*(u8*)((u8*)this + 0xA0) = (*(u8*)((u8*)this + 0xA0) & 0xDF) | 0x20;
	*(u8*)((u8*)this + 0x10C) &= 0xBF;
	*(float*)((u8*)this + 0x118) = 1.0f;
	*(float*)((u8*)this + 0x11C) = 1.0f;
	*(u8*)((u8*)this + 0xA1) = 0;
	*(float*)((u8*)this + 0x120) = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80072ea8
 * PAL Size: 1496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::Create(void* fileData, CMemory::CStage* stage)
{
	void* ref = new u8[0x44];
	memset(ref, 0, 0x44);
	*(u16*)((u8*)ref + 0x16) = 0xFFFF;
	*(u16*)((u8*)ref + 0x18) = 0xFFFF;
	*(u16*)((u8*)ref + 0x1A) = 0xFFFF;
	*(u16*)((u8*)ref + 0x1C) = 0xFFFF;
	*(float*)((u8*)ref + 0x28) = 1.0f;
	*(u32*)((u8*)ref + 0x2C) = 7;
	*(u32*)((u8*)ref + 0x30) = 0xC;
	*(void**)((u8*)this + 0xA4) = ref;
	*(void**)((u8*)this + 0xA8) = 0;
	*(void**)((u8*)this + 0xAC) = 0;
	*(void**)((u8*)this + 0xB0) = 0;
	*(void**)((u8*)this + 0xB4) = 0;

	CChunkFile chunkFile(fileData);
	CChunkFile::CChunk chunk;

	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != CharaFourCC('C', 'H', 'M', ' ')) {
			continue;
		}
		if (chunk.m_version < 5) {
			break;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			switch (chunk.m_id) {
			case 0x494E464F:
				*(float*)((u8*)ref + 0x28) = chunkFile.GetF4();
				*(float*)((u8*)this + 0x110) = chunkFile.GetF4();
				*(float*)((u8*)this + 0x114) = chunkFile.GetF4();
				break;

			case 0x5155414E:
				*(u32*)((u8*)ref + 0x2C) = chunkFile.Get4();
				*(u32*)((u8*)ref + 0x30) = chunkFile.Get4();
				break;

			case 0x4D534554: {
				CMaterialSet* materialSet =
				    new(stage, const_cast<char*>("src/chara.cpp"), 0x132) CMaterialSet();
				*(CMaterialSet**)((u8*)ref + 0x20) = materialSet;
				if (materialSet != 0) {
					materialSet->Create(chunkFile, 0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0), DAT_8032edc0);
				}
				break;
			}

			case 0x54415354:
				if (chunk.m_arg0 != 0) {
					CTexAnimSet* texAnimSet = new CTexAnimSet();
					*reinterpret_cast<CTexAnimSet**>((u8*)this + 0xD4) = texAnimSet;
					if (texAnimSet != 0) {
						texAnimSet->Create(chunkFile, stage);
					}
				}
				break;

			case 0x4E534554: {
				const u32 nodeCapacity = chunk.m_arg0;
				*(u16*)((u8*)ref + 0x08) = 0;
				if (nodeCapacity != 0) {
					void* nodeRefs = new u8[nodeCapacity * 0x94];
					void* nodes = new u8[nodeCapacity * 0xC0];
					memset(nodeRefs, 0, nodeCapacity * 0x94);
					memset(nodes, 0, nodeCapacity * 0xC0);
					*(void**)((u8*)ref + 0x0C) = nodeRefs;
					*(void**)((u8*)this + 0xA8) = nodes;
				}

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x4E4F4445 && *(void**)((u8*)this + 0xA8) != 0) {
						u16 nodeCount = *(u16*)((u8*)ref + 0x08);
						CNode* node = reinterpret_cast<CNode*>((u8*)*(void**)((u8*)this + 0xA8) + (nodeCount * 0xC0));
						Create__Q26CChara5CNodeFR10CChunkFilePQ26CChara6CModelQ36CChara5CNode4TYPEPQ27CMemory6CStage(
						    node, chunkFile, this, chunk.m_arg0, stage);
						*(u16*)((u8*)ref + 0x08) = nodeCount + 1;
					}
				}
				chunkFile.PopChunk();
				break;
			}

			case 0x4D535354: {
				const u32 meshCapacity = chunk.m_arg0;
				*(u16*)((u8*)ref + 0x0A) = 0;
				if (meshCapacity != 0) {
					void* meshRefs = new u8[meshCapacity * 0x64];
					void* meshes = new u8[meshCapacity * 0x14];
					memset(meshRefs, 0, meshCapacity * 0x64);
					memset(meshes, 0, meshCapacity * 0x14);
					*(void**)((u8*)ref + 0x10) = meshRefs;
					*(void**)((u8*)this + 0xAC) = meshes;
				}

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x4D455348 && *(void**)((u8*)this + 0xAC) != 0) {
						u16 meshCount = *(u16*)((u8*)ref + 0x0A);
						CMesh* mesh = reinterpret_cast<CMesh*>((u8*)*(void**)((u8*)this + 0xAC) + (meshCount * 0x14));
						Create__Q26CChara5CMeshFPQ26CChara6CModelR10CChunkFilePQ27CMemory6CStage(mesh, this, chunkFile, stage);
						*(u16*)((u8*)ref + 0x0A) = meshCount + 1;
					}
				}
				chunkFile.PopChunk();
				break;
			}

			case 0x42414E4B:
				if (chunk.m_size != 0) {
					void* bank = new u8[chunk.m_size];
					*(void**)((u8*)ref + 0x14) = bank;
					chunkFile.Get(bank, chunk.m_size);
				}
				break;
			}
		}
		chunkFile.PopChunk();
		break;
	}

	setup();
	CTexAnimSet* texAnimSet = *reinterpret_cast<CTexAnimSet**>((u8*)this + 0xD4);
	CMaterialSet* materialSet = *reinterpret_cast<CMaterialSet**>((u8*)ref + 0x20);
	if (texAnimSet != 0 && materialSet != 0) {
		texAnimSet->AttachMaterialSet(materialSet);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80072ae4
 * PAL Size: 964b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CreateDynamics(void* dynData, CMemory::CStage* stage)
{
	if (ModelRef(this) == 0 || dynData == 0) {
		return;
	}

	CChunkFile chunkFile(dynData);
	CChunkFile::CChunk chunk;
	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != CharaFourCC('C', 'H', 'D', ' ')) {
			continue;
		}

		if (ModelDynParams(this) != 0) {
			__dla__FPv(ModelDynParams(this));
			ModelDynParams(this) = 0;
		}
		ModelDynCount(this) = 0;

		CNode* nodes = ModelNodes(this);
		for (u32 i = 0; i < ModelNodeCount(this); i++) {
			NodeDynParamIndex(&nodes[i]) = 0xFF;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			if (chunk.m_id == CharaFourCC('D', 'G', 'R', 'P')) {
				if (chunk.m_size == 0) {
					continue;
				}

				ModelDynCount(this) = 0;
				ModelDynParams(this) = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
				    &Memory, chunk.m_size * 0x24, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x1E7, 0);
				if (ModelDynParams(this) == 0) {
					continue;
				}

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id != CharaFourCC('D', 'Y', 'N', ' ')) {
						continue;
					}

					float* dynParam = reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24);
					chunkFile.PushChunk();
					while (chunkFile.GetNextChunk(chunk)) {
						if (chunk.m_id == CharaFourCC('P', 'A', 'R', 'M')) {
							dynParam[0] = chunkFile.GetF4();
							dynParam[1] = chunkFile.GetF4();
							dynParam[2] = chunkFile.GetF4();
							*reinterpret_cast<u32*>(dynParam + 3) = chunkFile.Get4();
							*reinterpret_cast<u32*>(dynParam + 4) = chunkFile.Get4();
							dynParam[5] = chunkFile.GetF4();
							dynParam[7] = chunkFile.GetF4();
							dynParam[6] = chunkFile.GetF4();
							dynParam[8] = chunkFile.GetF4();
						}
					}
					chunkFile.PopChunk();
					ModelDynCount(this)++;
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == CharaFourCC('N', 'S', 'E', 'T')) {
				int currentNode = -1;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == CharaFourCC('N', 'A', 'M', 'E')) {
						currentNode = -1;
						char* name = chunkFile.GetString();
						for (u32 i = 0; i < ModelNodeCount(this); i++) {
							if (strcmp(NodeRefName(&nodes[i]), name) == 0) {
								currentNode = static_cast<int>(i);
								break;
							}
						}
					} else if (chunk.m_id == CharaFourCC('D', 'Y', 'N', ' ')) {
						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(chunk)) {
							if (chunk.m_id == CharaFourCC('P', 'A', 'R', 'M') && currentNode >= 0) {
								NodeDynParamIndex(&nodes[currentNode]) = static_cast<u8>(chunkFile.Get4());
							}
						}
						chunkFile.PopChunk();
					}
				}
				chunkFile.PopChunk();
			}
		}
		chunkFile.PopChunk();
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80072928
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::setup()
{
	CNode* node = ModelNodes(this);
	CMesh* mesh = reinterpret_cast<CMesh*>(ModelMeshes(this));
	u32 nodeCount = ModelNodeCount(this);
	u32 meshCount = ModelMeshCount(this);
	for (u32 i = 0; i < nodeCount; i++) {
		PSMTXCopy(NodeRefLocalMtx(node), NodeLocalRuntimeMtx(node));
		s8 disp = *(s8*)((u8*)*(void**)node + 4);
		if (disp >= 0 && static_cast<u32>(disp) < meshCount) {
			*(void**)((u8*)node + 4) = (u8*)mesh + (disp * 0x14);
		}
		node = (CNode*)((u8*)node + 0xC0);
	}

	calcBindMatrix();

	CCharaMeshRaw* meshRaw = ModelMeshes(this);
	for (u32 i = 0; i < meshCount; i++) {
		CCharaMeshRefRaw* meshData = meshRaw->m_data;
		u8* skin = reinterpret_cast<u8*>(meshData->m_skins);
		for (u32 j = 0; j < meshData->m_skinCount; j++) {
			u32 skinNodeIndex = *reinterpret_cast<u32*>(skin + 0x60);
			MtxPtr skinInvBind = reinterpret_cast<MtxPtr>(skin + 0x30);
			PSMTXInverse(reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(&ModelNodes(this)[skinNodeIndex])) + 0x3C),
			             skinInvBind);
			PSMTXConcat(skinInvBind,
			            reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(*reinterpret_cast<void**>(&ModelNodes(this)[meshData->m_nodeIndex])) + 0x3C),
			            skinInvBind);
			skin += 0x64;
		}
		meshRaw++;
	}

	AttachAnim(*(CAnim**)((u8*)this + 0xD0), -1, -1, 0);

	CMaterialSet* materialSet = ModelMaterialSet(this);
	if (materialSet != 0) {
		SetTextureSet__12CMaterialSetFP11CTextureSet(materialSet, *reinterpret_cast<CTextureSet**>((u8*)this + 0xB4));
	}
}

/*
 * --INFO--
 * PAL Address: 0x80072530
 * PAL Size: 1016b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel* CChara::CModel::Duplicate(CMemory::CStage* stage)
{
	if (ModelRef(this) == 0) {
		return 0;
	}

	CModel* clone = new (stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x25A) CModel();
	if (clone == 0) {
		return 0;
	}

	clone->Init();
	*reinterpret_cast<void**>(ModelRaw(clone) + 0xA4) = ModelRef(this);
	RetainRefCounted(ModelRef(clone));

	const u16 nodeCount = ModelNodeCount(this);
	if (nodeCount != 0) {
		CChara::CNode* cloneNodes = AllocateCharaNodeArray(nodeCount, stage);
		if (cloneNodes != 0) {
			*reinterpret_cast<CChara::CNode**>(ModelRaw(clone) + 0xA8) = cloneNodes;
			for (u32 i = 0; i < nodeCount; i++) {
				CChara::CNode* dst = &cloneNodes[i];
				CChara::CNode* src = &ModelNodes(this)[i];
				*reinterpret_cast<void**>(dst) = *reinterpret_cast<void**>(src);
				PSMTXCopy(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(src) + 8),
				          reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(dst) + 8));
				PSMTXCopy(NodeWorldMtx(src), NodeWorldMtx(dst));
				NodePreviousQuat(dst) = NodePreviousQuat(src);
				NodePreviousPosition(dst) = NodePreviousPosition(src);
				NodePreviousScale(dst) = NodePreviousScale(src);
				NodeAnimNode0(dst) = 0;
				NodeAnimNode1(dst) = 0;
				NodeRuntimeFlags(dst) = (NodeRuntimeFlags(dst) & 0x7F) | (NodeRuntimeFlags(src) & 0x80);
			}
		}
	}

	const u16 meshCount = ModelMeshCount(this);
	if (meshCount != 0) {
		CChara::CMesh* cloneMeshes = AllocateCharaMeshArray(meshCount, stage);
		if (cloneMeshes != 0) {
			*reinterpret_cast<CChara::CMesh**>(ModelRaw(clone) + 0xAC) = cloneMeshes;
			for (u32 i = 0; i < meshCount; i++) {
				CChara::CMesh* dst = &cloneMeshes[i];
				CChara::CMesh* src = &reinterpret_cast<CChara::CMesh*>(ModelMeshes(this))[i];
				u8* dstRaw = reinterpret_cast<u8*>(dst);
				u8* srcRaw = reinterpret_cast<u8*>(src);
				*reinterpret_cast<void**>(dstRaw) = *reinterpret_cast<void**>(srcRaw);
				*reinterpret_cast<void**>(dstRaw + 4) = 0;
				*reinterpret_cast<void**>(dstRaw + 8) = 0;
			}
		}
	}

	if (m_texSet != 0) {
		clone->AttachTextureSet(m_texSet);
	}
	*reinterpret_cast<CTexAnimSet**>(ModelRaw(clone) + 0xD4) =
	    (ModelTexAnimSet(this) != 0) ? ModelTexAnimSet(this)->Duplicate(stage) : 0;

	if ((nodeCount == 0 || ModelNodes(clone) != 0) && (meshCount == 0 || ModelMeshes(clone) != 0)) {
		clone->setup();
	}
	return clone;
}

/*
 * --INFO--
 * PAL Address: 0x800724b8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::calcBindMatrix()
{
	CNode* node = *(CNode**)((u8*)this + 0xA8);
	u32 i = 0;

	while (i < *(u32*)((u8*)*(void**)((u8*)this + 0xA4) + 8)) {
		if (*(s16*)((u8*)*(void**)node + 0x68) < 0) {
			CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(node, this);
		}
		i++;
		node = (CNode*)((u8*)node + 0xC0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800723a4
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcMatrix()
{
	float(*localMtx)[4] = (float(*)[4])((u8*)this + 0x14);
	float(*worldBaseMtx)[4] = (float(*)[4])((u8*)this + 0x44);
	float(*drawMtx)[4] = (float(*)[4])((u8*)this + 0x74);
	const float zero = FLOAT_803301b0;
	const float one = FLOAT_803301bc;

	worldBaseMtx[0][0] = localMtx[0][0];
	worldBaseMtx[1][0] = localMtx[1][0];
	worldBaseMtx[2][0] = localMtx[2][0];
	worldBaseMtx[0][1] = localMtx[0][1];
	worldBaseMtx[1][1] = localMtx[1][1];
	worldBaseMtx[2][1] = localMtx[2][1];
	worldBaseMtx[0][2] = localMtx[0][2];
	worldBaseMtx[1][2] = localMtx[1][2];
	worldBaseMtx[2][2] = localMtx[2][2];
	worldBaseMtx[0][3] = zero;
	worldBaseMtx[1][3] = zero;
	worldBaseMtx[2][3] = zero;

	drawMtx[0][0] = one;
	drawMtx[1][0] = zero;
	drawMtx[2][0] = zero;
	drawMtx[0][1] = zero;
	drawMtx[1][1] = one;
	drawMtx[2][1] = zero;
	drawMtx[0][2] = zero;
	drawMtx[1][2] = zero;
	drawMtx[2][2] = one;
	drawMtx[0][3] = localMtx[0][3];
	drawMtx[1][3] = localMtx[1][3];
	drawMtx[2][3] = localMtx[2][3];

	u16& blendCur = ModelBlendCur(this);
	if (blendCur != 0) {
		blendCur--;
	}

	BeforeCalcMatrixCallback beforeCalcMatrix = ModelBeforeCalcMatrixCallback(this);
	if (beforeCalcMatrix == 0 || beforeCalcMatrix(this, ModelCalcCbUser0(this), ModelCalcCbUser1(this)) != 0) {
		calcMatrix();

		CTexAnimSet* texAnimSet = ModelTexAnimSet(this);
		if (texAnimSet != 0) {
			texAnimSet->AddFrame();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800722f4
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcSkin()
{
	void* mesh = *(void**)((u8*)this + 0xAC);
	u32 posQuant = ModelPosQuant(this);
	u32 normQuant = ModelNormQuant(this);
	u16 meshCount = ModelMeshCount(this);
	u32 i = 0;

	gqrInit__6CCharaFUlUlUl(&gChara, (posQuant << 24) | 0x70000 | (posQuant << 8) | 7,
	                        (normQuant << 24) | 0x70000 | (normQuant << 8) | 7, 0x0C070C07);

	while (i < meshCount) {
		Calc__Q26CChara5CMeshFPQ26CChara6CModel(mesh, this);
		mesh = (u8*)mesh + 0x14;
		i++;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::calcNowFrame()
{
	if (m_anim == 0) {
		m_curFrame = 0.0f;
		return;
	}

	float total = 1.0f + (m_animEnd - m_animStart);
	if ((((u8*)m_anim)[8] & 0x40) == 0) {
		if (m_time >= 0.0f) {
			m_curFrame = m_animStart + static_cast<float>(fmod(m_time, total));
		} else {
			m_curFrame = ((m_animStart + total) - 1.0f) - static_cast<float>(fmod(-m_time, total));
		}
	} else if (m_time >= 0.0f) {
		float clamped = total - 1.0f;
		if (m_time < clamped) {
			clamped = m_time;
		}
		m_curFrame = m_animStart + clamped;
	} else {
		float clamped = total - 1.0f;
		if (-m_time < clamped) {
			clamped = -m_time;
		}
		m_curFrame = ((m_animStart + total) - 1.0f) - clamped;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80071b64
 * PAL Size: 1936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::calcMatrix()
{
	calcNowFrame();
	if (m_anim != 0) {
		InitQuantize__Q26CChara5CAnimFv(m_anim);
	}

	CNode* nodes = ModelNodes(this);
	u16 nodeCount = ModelNodeCount(this);
	Vec twistAxisBase = {FLOAT_803301b0, FLOAT_803301bc, FLOAT_803301b0};
	for (u32 i = 0; i < nodeCount; i++) {
		CNode* node = (CNode*)((u8*)nodes + (i * 0xC0));
		s16 parentIndex = NodeParentIndex(node);
		CNode* parentNode = 0;
		if (parentIndex >= 0) {
			parentNode = reinterpret_cast<CNode*>(reinterpret_cast<u8*>(nodes) + parentIndex * 0xC0);
		}

		CalcFrameMatrix(m_curFrame, node, NodeWorldMtx(node));
		if (NodeDynParamIndex(node) != 0xFF) {
			dynamics(node, parentNode);
		}

		if (NodeRefIndex(node) == ModelChest1Index(this) && ModelTwistAngle(this) != FLOAT_803301b0) {
			Vec twistAxis = twistAxisBase;
			Mtx twistRotate;
			Mtx nodeBase;
			Mtx axisBase;
			PSMTXMultVecSR(ModelWorldBaseMtx(this), &twistAxis, &twistAxis);
			PSMTXRotAxisRad(twistRotate, &twistAxis, ModelTwistAngle(this));
			PSMTXCopy(NodeWorldMtx(node), nodeBase);
			PSMTXCopy(twistRotate, axisBase);
			nodeBase[0][3] = FLOAT_803301b0;
			nodeBase[1][3] = FLOAT_803301b0;
			nodeBase[2][3] = FLOAT_803301b0;
			axisBase[0][3] = FLOAT_803301b0;
			axisBase[1][3] = FLOAT_803301b0;
			axisBase[2][3] = FLOAT_803301b0;
			PSMTXConcat(axisBase, nodeBase, twistRotate);
			NodeWorldMtx(node)[0][0] = twistRotate[0][0];
			NodeWorldMtx(node)[1][0] = twistRotate[1][0];
			NodeWorldMtx(node)[2][0] = twistRotate[2][0];
			NodeWorldMtx(node)[0][1] = twistRotate[0][1];
			NodeWorldMtx(node)[1][1] = twistRotate[1][1];
			NodeWorldMtx(node)[2][1] = twistRotate[2][1];
			NodeWorldMtx(node)[0][2] = twistRotate[0][2];
			NodeWorldMtx(node)[1][2] = twistRotate[1][2];
			NodeWorldMtx(node)[2][2] = twistRotate[2][2];
		}
	}

	ModelFlags10C(this) &= 0x7F;
}

/*
 * --INFO--
 * PAL Address: 0x800716c4
 * PAL Size: 1184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcFrameMatrix(float frame, CChara::CNode* node, float (*out)[4])
{
	if (m_anim != 0) {
		InitQuantize__Q26CChara5CAnimFv(m_anim);
	}

	PSMTXIdentity(out);

	CNode* nodes = ModelNodes(this);
	CNode* cur = node;
	bool reuseAnimNode0Srt = false;
	SRTView parentScaleSrt;
	while (cur != 0) {
		CNode* parentNode = 0;
		s16 parent = NodeParentIndex(cur);
		if (parent < 0) {
			parentNode = 0;
		} else {
			parentNode = reinterpret_cast<CNode*>(reinterpret_cast<u8*>(nodes) + parent * 0xC0);
		}

		Mtx localMtx;
		CChara::CAnimNode* animNode0 = NodeAnimNode0(cur);
		CChara::CAnimNode* animNode1 = NodeAnimNode1(cur);
		SRTView cachedParentScaleSrt = parentScaleSrt;
		bool nextReuseAnimNode0Srt = false;

		if (animNode0 == 0 && animNode1 == 0) {
			PSMTXCopy(NodeRefLocalMtx(cur), localMtx);
		} else {
			CChara::CAnimNode* parentAnimNode0 = parentNode != 0 ? NodeAnimNode0(parentNode) : 0;
			if (parentNode == 0 || parentAnimNode0 == 0 || !AnimNodeUsesScale(parentAnimNode0)) {
				if (parentNode == 0) {
					float baseScale = ModelBaseScale(this);
					if (baseScale != FLOAT_803301bc) {
						PSMTXScale(localMtx, baseScale, baseScale, baseScale);
					} else {
						PSMTXIdentity(localMtx);
					}
				} else {
					PSMTXIdentity(localMtx);
				}
			} else {
				Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf(parentAnimNode0, m_anim,
				                                                   reinterpret_cast<SRT*>(&parentScaleSrt), frame);
				nextReuseAnimNode0Srt = true;
				PSMTXScale(localMtx,
				           FLOAT_803301bc / parentScaleSrt.m_scale.x,
				           FLOAT_803301bc / parentScaleSrt.m_scale.y,
				           FLOAT_803301bc / parentScaleSrt.m_scale.z);
			}

			if (NodeUsesParentLenX(cur) != 0) {
				localMtx[0][3] = NodeBoneLen(parentNode);
			}

			if (animNode1 != 0) {
				SRTView srt1;
				Mtx animMtx;
				Mtx invScaleMtx;

				Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf(animNode1, m_anim,
				                                                   reinterpret_cast<SRT*>(&srt1), frame);
				if (AnimNodeUsesScale(animNode1)) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt1));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt1));
				}
				PSMTXConcat(localMtx, animMtx, localMtx);

				float invX = (srt1.m_scale.x != 0.0f) ? (FLOAT_803301bc / srt1.m_scale.x) : FLOAT_803301bc;
				float invY = (srt1.m_scale.y != 0.0f) ? (FLOAT_803301bc / srt1.m_scale.y) : FLOAT_803301bc;
				float invZ = (srt1.m_scale.z != 0.0f) ? (FLOAT_803301bc / srt1.m_scale.z) : FLOAT_803301bc;
				PSMTXScale(invScaleMtx, invX, invY, invZ);
				PSMTXConcat(localMtx, invScaleMtx, localMtx);
			}

			if (animNode0 != 0) {
				SRTView srt0;
				Mtx animMtx;
				u16 nodeIndex;

				if (reuseAnimNode0Srt) {
					srt0 = cachedParentScaleSrt;
				} else {
					Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf(animNode0, m_anim,
					                                                   reinterpret_cast<SRT*>(&srt0), frame);
				}
				nodeIndex = NodeRefIndex(cur);
				if (nodeIndex == ModelChest1Index(this) || nodeIndex == ModelChest2Index(this) ||
				    nodeIndex == ModelChest3Index(this)) {
					float tiltScale;
					if (nodeIndex == ModelChest3Index(this)) {
						srt0.m_rotation.y = -(ModelChestAmp(this) * FLOAT_803301d0 - srt0.m_rotation.y);
						tiltScale = FLOAT_803301d0;
					} else {
						srt0.m_rotation.x = ModelChestAmp(this) * FLOAT_803301f8 + srt0.m_rotation.x;
						tiltScale = FLOAT_803301f8;
					}
					srt0.m_rotation.z = ModelChestTilt(this) * tiltScale + srt0.m_rotation.z;
				} else if (nodeIndex == ModelHeadIndex(this) && ModelTexAnimSet(this) != 0) {
					srt0.m_rotation.z += TexAnimSetChin(ModelTexAnimSet(this));
				}
				if (AnimNodeUsesScale(animNode0)) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt0));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt0));
				}
				PSMTXConcat(localMtx, animMtx, localMtx);
			}
		}
		reuseAnimNode0Srt = nextReuseAnimNode0Srt;

		u16 blendCur = ModelBlendCur(this);
		if (blendCur != 0) {
			u16 blendMax = ModelBlendMax(this);
			float alpha = FLOAT_803301bc - (static_cast<float>(blendCur) * (FLOAT_803301bc / static_cast<float>(blendMax)));
			Vec targetPos = {localMtx[0][3], localMtx[1][3], localMtx[2][3]};
			Vec targetScale;
			Quaternion targetQuat;
			Vec positionScaleA;
			Vec positionScaleB;
			Vec blendedPos;
			Mtx quatMtx;
			Mtx scaleMtx;

			Math.MTXGetScale(localMtx, &targetScale);
			if (FLOAT_803301e4 <= targetScale.x) {
				PSVECScale(&NodePreviousScale(cur), &positionScaleA, FLOAT_803301bc - alpha);
				PSVECScale(&targetScale, &positionScaleB, alpha);
				PSVECAdd(&positionScaleA, &positionScaleB, &targetScale);
			} else {
				targetScale.y = FLOAT_803301e8;
				targetScale.z = FLOAT_803301e8;
			}
			PSVECScale(&NodePreviousPosition(cur), &positionScaleA, FLOAT_803301bc - alpha);
			PSVECScale(&targetPos, &positionScaleB, alpha);
			PSVECAdd(&positionScaleA, &positionScaleB, &blendedPos);
			C_QUATMtx(&targetQuat, localMtx);
			C_QUATSlerp(&NodePreviousQuat(cur), &targetQuat, &targetQuat, alpha);
			PSMTXScale(scaleMtx, targetScale.x, targetScale.y, targetScale.z);
			PSMTXQuat(quatMtx, &targetQuat);
			PSMTXConcat(quatMtx, scaleMtx, localMtx);
			localMtx[0][3] = blendedPos.x;
			localMtx[1][3] = blendedPos.y;
			localMtx[2][3] = blendedPos.z;
		}

		PSMTXConcat(localMtx, out, out);

		if (parentNode == 0) {
			break;
		}
		cur = parentNode;
	}

	PSMTXConcat(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(this) + 0x08), out, out);
}

/*
 * --INFO--
 * PAL Address: 0x80071078
 * PAL Size: 1612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::dynamics(CChara::CNode* node, CChara::CNode* parent)
{
	(void)parent;
	if (node == 0 || ModelDynParams(this) == 0) {
		return;
	}

	u8 dynIndex = NodeDynParamIndex(node);
	if (dynIndex == 0xFF || dynIndex >= ModelDynCount(this)) {
		return;
	}

	float* dynParam = reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + dynIndex * 0x24);
	MtxPtr nodeMtx = NodeWorldMtx(node);
	Vec forward = {nodeMtx[0][0], nodeMtx[1][0], nodeMtx[2][0]};
	Vec right = {nodeMtx[0][1], nodeMtx[1][1], nodeMtx[2][1]};
	Vec up = {nodeMtx[0][2], nodeMtx[1][2], nodeMtx[2][2]};
	Vec origin = {nodeMtx[0][3], nodeMtx[1][3], nodeMtx[2][3]};
	float boneLen = NodeBoneLen(node);

	PSVECNormalize(&forward, &forward);
	Vec target;
	PSVECScale(&forward, &target, boneLen);
	PSVECAdd(&origin, &target, &target);

	if ((ModelFlags10C(this) & 0x80) != 0) {
		NodeDynPosition(node) = target;
		NodeDynVelocity(node).x = 0.0f;
		NodeDynVelocity(node).y = 0.0f;
		NodeDynVelocity(node).z = 0.0f;
		return;
	}

	float randomScale = FLOAT_803301d0 * Math.RandF() + FLOAT_803301d0;
	Vec windForce;
	PSVECScale(&ModelDynJitter(this), &windForce, randomScale);
	Vec windImpulse;
	PSVECScale(&windForce, &windImpulse, dynParam[2]);

	Vec targetDelta;
	PSVECSubtract(&target, &NodeDynPosition(node), &targetDelta);
	Vec accel;
	PSVECAdd(&targetDelta, &windImpulse, &accel);
	PSVECAdd(&NodeDynVelocity(node), &accel, &NodeDynVelocity(node));

	Vec step;
	PSVECScale(&NodeDynVelocity(node), &step, dynParam[0]);
	Vec predicted;
	PSVECAdd(&NodeDynPosition(node), &step, &predicted);
	PSVECScale(&NodeDynVelocity(node), &NodeDynVelocity(node), dynParam[1]);

	Vec direction;
	PSVECSubtract(&predicted, &origin, &direction);
	for (int axis = 0; axis < 2; axis++, dynParam++) {
		if (dynParam[3] != 0.0f) {
			float dotForward = PSVECDotProduct(&forward, &direction);
			float dotSide = PSVECDotProduct(axis == 0 ? &up : &right, &direction);
			float angle = axis == 0 ? -atan2f(dotSide, dotForward) : atan2f(dotSide, dotForward);
			float limit = 0.01745329252f * dynParam[5];
			if (angle <= limit || 0.01745329252f * dynParam[7] <= angle) {
				if (limit < angle) {
					limit = 0.01745329252f * dynParam[7];
				}

				Mtx rotate;
				PSMTXRotAxisRad(rotate, axis == 0 ? &right : &up, limit - angle);
				PSMTXMultVecSR(rotate, &direction, &direction);
			}
		}
	}

	PSVECNormalize(&direction, &direction);
	float align = PSVECDotProduct(&forward, &direction);
	if (align <= 0.9999f) {
		float rotateAngle = 3.14159274f;
		if (-1.0f <= align) {
			rotateAngle = acosf(align);
		}

		Vec axis;
		PSVECCrossProduct(&forward, &direction, &axis);
		Mtx rotate;
		Mtx base;
		Mtx axisBase;
		Mtx combined;
		PSMTXRotAxisRad(rotate, &axis, rotateAngle);
		PSMTXCopy(nodeMtx, base);
		PSMTXCopy(rotate, axisBase);
		base[0][3] = FLOAT_803301b0;
		base[1][3] = FLOAT_803301b0;
		base[2][3] = FLOAT_803301b0;
		axisBase[0][3] = FLOAT_803301b0;
		axisBase[1][3] = FLOAT_803301b0;
		axisBase[2][3] = FLOAT_803301b0;
		PSMTXConcat(axisBase, base, combined);
		nodeMtx[0][0] = combined[0][0];
		nodeMtx[1][0] = combined[1][0];
		nodeMtx[2][0] = combined[2][0];
		nodeMtx[0][1] = combined[0][1];
		nodeMtx[1][1] = combined[1][1];
		nodeMtx[2][1] = combined[2][1];
		nodeMtx[0][2] = combined[0][2];
		nodeMtx[1][2] = combined[1][2];
		nodeMtx[2][2] = combined[2][2];
	}

	Vec dynOffset;
	PSVECScale(&direction, &dynOffset, boneLen);
	PSVECAdd(&origin, &dynOffset, &NodeDynPosition(node));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::calcSkin()
{
	CalcSkin();
}

/*
 * --INFO--
 * PAL Address: 0x8007104c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::SetMatrix(float (*mtx) [4])
{
	PSMTXCopy(mtx, (float(*)[4])((u8*)this + 0x8));
}

/*
 * --INFO--
 * PAL Address: 0x80070fc0
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CChara::CModel::SearchNode(char* name)
{
	u32 index = 0;
	CNode* node = *(CNode**)((u8*)this + 0xA8);
	u32 nodeCount = *(u32*)((u8*)*(void**)((u8*)this + 0xA4) + 8);

	while (index < nodeCount) {
		if (strcmp((char*)((u8*)*(void**)node + 0x6C), name) == 0) {
			return (int)index;
		}
		index++;
		node = (CNode*)((u8*)node + 0xC0);
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x80070e14
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CChara::CModel::SearchNodeSk(char* name)
{
	if (*name == '_') {
		if (name[1] == 's' && name[2] == 'k') {
			CNode* node = *(CNode**)((u8*)this + 0xA8);
			u32 nodeCount = *(u32*)((u8*)*(void**)((u8*)this + 0xA4) + 8);
			for (u32 i = 0; i < nodeCount; i++) {
				char* nodeName = (char*)((u8*)*(void**)node + 0x6C);
				int len = strlen(nodeName);
				if ((len - 3) > 0 && strcmp(nodeName + len - 3, name) == 0) {
					return (int)i;
				}
				node = (CNode*)((u8*)node + 0xC0);
			}
		} else if (name[1] == 'r' && name[2] == 'o' && name[3] == 'o' && name[4] == 't') {
			CNode* node = *(CNode**)((u8*)this + 0xA8);
			u32 nodeCount = *(u32*)((u8*)*(void**)((u8*)this + 0xA4) + 8);
			for (u32 i = 0; i < nodeCount; i++) {
				char* nodeName = (char*)((u8*)*(void**)node + 0x6C);
				int len = strlen(nodeName);
				if ((len - 5) > 0 && strcmp(nodeName + len - 5, name) == 0) {
					return (int)i;
				}
				node = (CNode*)((u8*)node + 0xC0);
			}
		}
	} else {
		CNode* node = *(CNode**)((u8*)this + 0xA8);
		u32 nodeCount = *(u32*)((u8*)*(void**)((u8*)this + 0xA4) + 8);
		for (u32 i = 0; i < nodeCount; i++) {
			if (strcmp((char*)((u8*)*(void**)node + 0x6C), name) == 0) {
				return (int)i;
			}
			node = (CNode*)((u8*)node + 0xC0);
		}
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8007096c
 * PAL Size: 1192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::Draw(float (*view)[4], int flags, int pass)
{
	calcSkin();

	if (ModelLightAlpha(this) == FLOAT_803301b0) {
		return;
	}

	const unsigned int cullFlag = static_cast<unsigned int>(flags) & 1;
	BeforeDrawModelCallback beforeDrawModel = ModelBeforeDrawCallback(this);
	if (beforeDrawModel != 0 && pass == 0) {
		beforeDrawModel(this, ModelCbUser0(this), ModelCbUser1(this), view, cullFlag);
	}

	CMaterialSet* materialSet = ModelMaterialSet(this);
	if (materialSet == 0) {
		return;
	}

	SetTextureSet__12CMaterialSetFP11CTextureSet(materialSet, m_texSet);
	CTexAnimSet* texAnimSet = ModelTexAnimSet(this);
	if (texAnimSet != 0) {
		texAnimSet->SetTexGen();
	}

	MaterialMan.InitVtxFmt(-1, (_GXCompType)3, ModelPosQuant(this), (_GXCompType)3, ModelNormQuant(this), (_GXCompType)3, 0xC);
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
	GXSetZMode((u8)1, (GXCompare)3, (u8)1);
	GXSetCullMode(static_cast<GXCullMode>(cullFlag != 0 ? 2 : 1));
	LightPcs.SetAmbientAlpha(ModelLightAlpha(this));

	CCharaMeshRaw* mesh = ModelMeshes(this);
	CNode* nodes = ModelNodes(this);
	const u16 meshCount = ModelMeshCount(this);
	int lastLightEnable = -1;
	int lastZWrite = -1;
	BeforeMeshCallback beforeMesh = ModelBeforeMeshCallback(this);
	AfterMeshDrawCallback afterMeshDraw = ModelAfterMeshDrawCallback(this);
	AfterMeshEnvCallback afterMeshEnv = ModelAfterMeshEnvCallback(this);

	for (u32 meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0 || mesh->m_data == 0) {
			continue;
		}
		if (meshIndex <= 0x1F && ((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		InitCharaMaterialState();

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(this), reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(nodes + mesh->m_data->m_nodeIndex) + 0x44), meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		}

		if (((cullFlag == 0) && (((flags >> 1) & 1) == 0)) || ((cullFlag != 0) && (((flags >> 3) & 1) != 0))) {
			CameraPcs.SetFullScreenShadow(meshMtx, 0);
		}

		if (((flags >> 4) & 1) == 0) {
			Vec position;
			position.x = ModelDrawMtx(this)[0][3];
			position.y = ModelDrawMtx(this)[1][3];
			position.z = ModelDrawMtx(this)[2][3];
			MaterialMan.SetPosition(static_cast<CMapShadow::TARGET>(0), &position, FLOAT_803301c8, FLOAT_803301cc, meshMtx,
			                        (ModelFlagsA0(this) & 0x80) != 0);
		}

		const int lightEnable = (mesh->m_data->m_flags & 0x80) == 0;
		if (lightEnable != lastLightEnable) {
			LightPcs.EnableLight(lightEnable, 0);
			lastLightEnable = lightEnable;
		}

		const int zWriteEnable = (mesh->m_data->m_flags & 0x40) == 0;
		if (zWriteEnable != lastZWrite) {
			GXSetZMode((u8)1, (GXCompare)3, (u8)zWriteEnable);
			lastZWrite = zWriteEnable;
		}

		if (beforeMesh != 0) {
			beforeMesh(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex);
		}

		CopyCharaMaterialEnv();
		if (mesh->m_data->m_infoWord1 != 0) {
			LightPcs.SetBumpTexMatirx(meshMtx, DAT_8032edc0, 0, 0);
		}
		MaterialMan.SetObjMatrix(view, meshMtx);
		GXSetArray((GXAttr)9, mesh->m_workPositions, 6);
		SetMaterialManNormalArray(mesh->m_workNormals);
		GXSetArray((GXAttr)0xB, mesh->m_data->m_colors, 4);
		GXSetArray((GXAttr)0xD, mesh->m_data->m_uvs, 4);
		GXSetArray((GXAttr)0xE, mesh->m_data->m_uvs, 4);

		CCharaDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (int displayListIndex = static_cast<int>(mesh->m_data->m_displayListCount) - 1; displayListIndex >= 0; displayListIndex--, displayList++) {
			if (afterMeshDraw == 0) {
				MaterialMan.SetMaterial(materialSet, displayList->m_material, (flags >> 2) & 1, (_GXTevScale)0);
				GXCallDisplayList(displayList->m_data, displayList->m_size);
			} else {
				afterMeshDraw(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex, static_cast<unsigned int>(displayListIndex), meshMtx);
			}
		}

		if (afterMeshEnv != 0) {
			afterMeshEnv(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex, meshMtx);
		}
	}

	AfterDrawModelCallback afterDrawModel = ModelAfterDrawCallback(this);
	if (afterDrawModel != 0) {
		afterDrawModel(this, ModelCbUser0(this), ModelCbUser1(this));
	}
}

/*
 * --INFO--
 * PAL Address: 0x80070690
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::DrawShadow(float (*view)[4], int zMode)
{
	calcSkin();

	if (ModelLightAlpha(this) != FLOAT_803301bc) {
		return;
	}

	CMaterialSet* materialSet = ModelMaterialSet(this);
	if (materialSet == 0) {
		return;
	}

	SetTextureSet__12CMaterialSetFP11CTextureSet(materialSet, m_texSet);
	LightPcs.SetAmbientAlpha(FLOAT_803301bc);
	MaterialMan.InitVtxFmt(-1, (_GXCompType)3, ModelPosQuant(this), (_GXCompType)3, ModelNormQuant(this), (_GXCompType)3, 0xC);
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
	GXSetZMode((u8)zMode, (GXCompare)3, (u8)zMode);
	GXSetCullMode((GXCullMode)1);

	CCharaMeshRaw* mesh = ModelMeshes(this);
	CNode* nodes = ModelNodes(this);
	const u16 meshCount = ModelMeshCount(this);
	CustomMeshDrawCallback customMeshDraw = ModelCustomMeshDrawCallback(this);
	AfterMeshDrawCallback shadowDisplayList = ModelShadowDisplayListCallback(this);

	for (u32 meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0 || mesh->m_data == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		InitCharaMaterialState();

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(this), reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(nodes + mesh->m_data->m_nodeIndex) + 0x44), meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		}

		if (customMeshDraw != 0) {
			customMeshDraw(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex);
		}

		CopyCharaMaterialEnv();
		MaterialMan.SetObjMatrix(view, meshMtx);
		GXSetArray((GXAttr)9, mesh->m_workPositions, 6);
		SetMaterialManNormalArray(mesh->m_workNormals);
		GXSetArray((GXAttr)0xB, mesh->m_data->m_colors, 4);
		GXSetArray((GXAttr)0xD, mesh->m_data->m_uvs, 4);
		GXSetArray((GXAttr)0xE, mesh->m_data->m_uvs, 4);

		CCharaDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (int displayListIndex = static_cast<int>(mesh->m_data->m_displayListCount) - 1; displayListIndex >= 0; displayListIndex--, displayList++) {
			if (shadowDisplayList == 0) {
				MaterialMan.SetMaterial(materialSet, displayList->m_material, 1, (_GXTevScale)0);
				GXCallDisplayList(displayList->m_data, displayList->m_size);
			} else {
				shadowDisplayList(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex, static_cast<unsigned int>(displayListIndex), meshMtx);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcInterpFrame()
{
	u16* blendCur = (u16*)((u8*)this + 0xD8);
	if (*blendCur != 0) {
		(*blendCur)--;
	}
	m_curFrame = m_time;
}

/*
 * --INFO--
 * PAL Address: 0x80070604
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcSafeNodeWorldMatrix(float (*outMtx) [4], CChara::CNode* node)
{
	u8 flags = *(u8*)((u8*)this + 0xA0);
	if ((flags & 0x40) != 0) {
		PSMTXCopy((float(*)[4])((u8*)node + 0x44), outMtx);
		outMtx[0][3] += *(float*)((u8*)this + 0x80);
		outMtx[1][3] += *(float*)((u8*)this + 0x90);
		outMtx[2][3] += *(float*)((u8*)this + 0xA0);
	} else {
		PSMTXCopy((float(*)[4])((u8*)this + 0x14), outMtx);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800702b4
 * PAL Size: 848b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::AttachAnim(CChara::CAnim* anim, int startFrame, int endFrame, int blendMode)
{
	if (blendMode < 0) {
		CAnim* currentAnim = m_anim;
		if (currentAnim == 0) {
			blendMode = 0;
		} else if (AnimInterpCount(currentAnim) == 0 || AnimBank(currentAnim) == 0) {
			blendMode = 4;
		} else {
			blendMode = 4;

			u8 interpCount = AnimInterpCount(currentAnim);
			u16* interpTable = reinterpret_cast<u16*>(reinterpret_cast<u8*>(AnimBank(currentAnim)) + AnimInterpOffset(currentAnim));
			int frame = static_cast<int>(m_curFrame);

			for (u32 i = 0; i < interpCount; i++) {
				int start = (i == 0) ? 0 : interpTable[i * 2];
				int end = (i + 1 < interpCount) ? interpTable[i * 2 + 2] : 10000000;
				if (start <= frame && frame < end) {
					blendMode = interpTable[i * 2 + 1];
					break;
				}
			}
		}
	}

	if (anim != m_anim) {
		ReleaseRefCounted(m_anim);
		m_anim = anim;
		RetainRefCounted(m_anim);
	}

	CNode* nodes = ModelNodes(this);
	u16 nodeCount = ModelNodeCount(this);
	for (u32 i = 0; i < nodeCount; i++) {
		CNode* node = reinterpret_cast<CNode*>(reinterpret_cast<u8*>(nodes) + i * 0xC0);

		NodeAnimNode0(node) = 0;
		NodeAnimNode1(node) = 0;

		MtxPtr localMtx = NodeRefLocalMtx(node);
		C_QUATMtx(&NodePreviousQuat(node), localMtx);
		NodePreviousPosition(node).x = localMtx[0][3];
		NodePreviousPosition(node).y = localMtx[1][3];
		NodePreviousPosition(node).z = localMtx[2][3];
		Math.MTXGetScale(localMtx, &NodePreviousScale(node));

		if (m_anim == 0) {
			continue;
		}

		CAnimNode* animNodes = AnimNodes(m_anim);
		u16 animNodeCount = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(m_anim) + 0x0E);
		char* primaryName = NodeRefName(node);
		char* secondaryName = NodeRefAltName(node);

		for (u32 animIndex = 0; animIndex < animNodeCount; animIndex++) {
			CAnimNode* animNode = reinterpret_cast<CAnimNode*>(reinterpret_cast<u8*>(animNodes) + animIndex * 0x18);
			char* animName = AnimNodeName(animNode);

			if (NodeAnimNode0(node) == 0 && primaryName[0] != '\0' && strcmp(primaryName, animName) == 0) {
				NodeAnimNode0(node) = animNode;
			} else if (NodeAnimNode1(node) == 0 && secondaryName[0] != '\0' && strcmp(secondaryName, animName) == 0) {
				NodeAnimNode1(node) = animNode;
			}

			if (NodeAnimNode0(node) != 0 && NodeAnimNode1(node) != 0) {
				break;
			}
		}
	}

	if (m_anim == 0) {
		m_curFrame = 0.0f;
		m_time = 0.0f;
		m_animEnd = 0.0f;
		m_animStart = 0.0f;
		return;
	}

	u16 blendFrames = 0;
	if (ModelAttachMode(this) == 0) {
		blendFrames = (AnimFlags(m_anim) & 0x80) != 0 ? static_cast<u16>(blendMode) : 0;
	} else if (ModelAttachMode(this) == 1) {
		blendFrames = static_cast<u16>(blendMode);
	}

	*reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0xD8) = blendFrames;
	*reinterpret_cast<u16*>(reinterpret_cast<u8*>(this) + 0xDA) = blendFrames;

	if (startFrame < 0) {
		startFrame = 0;
	}
	if (endFrame < 0) {
		endFrame = static_cast<int>(AnimFrameCount(m_anim)) - 1;
	}

	m_animStart = static_cast<float>(startFrame);
	m_curFrame = m_animStart;
	m_time = m_animStart;
	m_animEnd = static_cast<float>(endFrame);
}

/*
 * --INFO--
 * PAL Address: 0x80070204
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::AttachTextureSet(CTextureSet* texSet)
{
	CTextureSet* oldTexSet = m_texSet;

	if (texSet != oldTexSet) {
		if (oldTexSet != 0) {
			int* refData = reinterpret_cast<int*>(oldTexSet);
			int refCount = refData[1] - 1;
			refData[1] = refCount;
			if ((refCount == 0) && (oldTexSet != 0)) {
				(*(void (**)(void*, int))(*refData + 8))(oldTexSet, 1);
			}
			m_texSet = 0;
		}
		m_texSet = texSet;
		if (m_texSet != 0) {
			int* refData = reinterpret_cast<int*>(m_texSet);
			refData[1] = refData[1] + 1;
		}
	}
	if (m_data->m_materialSet != 0) {
		SetTextureSet__12CMaterialSetFP11CTextureSet(m_data->m_materialSet, m_texSet);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800701f4
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::AddFrame(float frame)
{
	m_curFrame += frame;
}

/*
 * --INFO--
 * PAL Address: 0x800701ec
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::SetFrame(float frame)
{
	m_curFrame = frame;
}

/*
 * --INFO--
 * PAL Address: 0x80070180
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcFurColor()
{
	float* furTarget = (float*)((u8*)this + 0x118);
	float* furCur = (float*)((u8*)this + 0x11C);
	float delta = *furTarget - *furCur;
	float step = -0.01f;
	if (delta >= -0.01f) {
		step = delta;
		if (0.01f < delta) {
			step = 0.01f;
		}
	}
	*furCur += step;
	if (*furCur < 0.0f) {
		*furCur = 0.0f;
	} else if (*furCur > 1.0f) {
		*furCur = 1.0f;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80070170
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CChara::CModel::GetDispIndex(CChara::CNode* node)
{
	struct CNodeRefDataDisplay {
		u8 _pad[0x8D];
		s8 m_displayIndex;
	};

	struct CNodeDisplayView {
		CNodeRefDataDisplay* m_refData;
	};

	CNodeDisplayView* nodeView = (CNodeDisplayView*)node;
	return (int)nodeView->m_refData->m_displayIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80070110
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CNode::CNode()
{
	__ct__7CVectorFv((u8*)this + 0xA4);
	__ct__7CVectorFv((u8*)this + 0xB0);
	*(u32*)((u8*)this + 0x0) = 0;
	*(u32*)((u8*)this + 0x4) = 0;
	*(u32*)((u8*)this + 0x9C) = 0;
	*(u32*)((u8*)this + 0xA0) = 0;
	*(u8*)((u8*)this + 0xBC) = (*(u8*)((u8*)this + 0xBC) & 0x7F) | 0x80;
}

/*
 * --INFO--
 * PAL Address: 0x800700d4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CNode::~CNode()
{
}

/*
 * --INFO--
 * PAL Address: 0x8006fef0
 * PAL Size: 484b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CNode::Create(CChunkFile& chunk, CChara::CModel* model, CChara::CNode::TYPE type, CMemory::CStage* stage)
{
	(void)stage;
	void* modelRef = *(void**)((u8*)model + 0xA4);
	u16 idx = *(u16*)((u8*)modelRef + 8);
	void* nodeRefBase = *(void**)((u8*)modelRef + 0xC);
	u8* nodeRef = reinterpret_cast<u8*>((u8*)nodeRefBase + (idx * 0x94));
	*(void**)this = nodeRef;
	*reinterpret_cast<u16*>(nodeRef + 0x0) = idx;
	*(nodeRef + 0x2) = static_cast<u8>(type);
	*(nodeRef + 0x4) = 0xFF;
	*(nodeRef + 0x64) = 0;

	CChunkFile::CChunk chunkInfo;
	chunk.PushChunk();
	while (chunk.GetNextChunk(chunkInfo)) {
		switch (chunkInfo.m_id) {
		case 0x494E464F:
			*reinterpret_cast<u16*>(nodeRef + 0x68) = static_cast<u16>(chunk.Get4());
			*(nodeRef + 0x6A) = static_cast<u8>(chunk.Get4());
			*reinterpret_cast<u16*>(nodeRef + 0x6C) = static_cast<u16>(chunk.Get4());
			*(nodeRef + 0x6E) = static_cast<u8>(chunk.Get4());
			break;
		case 0x42494E46:
			*(nodeRef + 0x64) = static_cast<u8>(chunk.Get4());
			*reinterpret_cast<float*>(nodeRef + 0x70) = chunk.GetF4();
			break;
		case 0x4E414D45:
			strcpy(reinterpret_cast<char*>(nodeRef + 0x74), chunk.GetString());
			break;
		case 0x4E414D32:
			strcpy(reinterpret_cast<char*>(nodeRef + 0x84), chunk.GetString());
			break;
		case 0x5446524D:
			chunk.Get(nodeRef + 0xC, 0x30);
			if (*reinterpret_cast<u16*>(nodeRef + 0x68) == 0xFFFF) {
				float baseScale = *reinterpret_cast<float*>(reinterpret_cast<u8*>(modelRef) + 0x28);
				PSMTXScaleApply(reinterpret_cast<float(*)[4]>(nodeRef + 0xC), reinterpret_cast<float(*)[4]>(nodeRef + 0xC),
				               baseScale, baseScale, baseScale);
			}
			break;
		case 0x4D494458:
			*(nodeRef + 0x90) = static_cast<u8>(chunk.Get4());
			break;
		}
	}
	chunk.PopChunk();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CNode::Duplicate(CChara::CNode* src, CMemory::CStage* stage)
{
	(void)stage;
	CopyDuplicatedNodeState(this, src);
}

/*
 * --INFO--
 * PAL Address: 0x8006fc98
 * PAL Size: 600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CNode::CalcBind(CChara::CModel* model)
{
	CalcOneBindNode(this, model);

	u8 childCount = NodeChildCount(this);
	for (int i = 0; i < childCount; i++) {
		CNode* child = GetBindChildNode(model, this, i);
		CalcOneBindNode(child, model);

		u8 grandChildCount = NodeChildCount(child);
		for (int j = 0; j < grandChildCount; j++) {
			CNode* grandChild = GetBindChildNode(model, child, j);
			CalcOneBindNode(grandChild, model);

			u8 greatGrandChildCount = NodeChildCount(grandChild);
			for (int k = 0; k < greatGrandChildCount; k++) {
				CNode* greatGrandChild = GetBindChildNode(model, grandChild, k);
				CalcOneBindNode(greatGrandChild, model);

				u8 recursiveChildCount = NodeChildCount(greatGrandChild);
				for (int l = 0; l < recursiveChildCount; l++) {
					GetBindChildNode(model, greatGrandChild, l)->CalcBind(model);
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006fc38
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CNode::CRefData::CRefData()
{
	memset(this, 0, 0x70);
	*(u8*)((u8*)this + 0x4) = 0xFF;
	*(u8*)((u8*)this + 0x64) = 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x8006fbfc
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CNode::CRefData::~CRefData()
{
}

/*
 * --INFO--
 * PAL Address: 0x8006fbb0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CMesh()
{
	memset(this, 0, 0x14);
}

/*
 * --INFO--
 * PAL Address: 0x8006fb50
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::~CMesh()
{
}

/*
 * --INFO--
 * PAL Address: 0x8006f4c4
 * PAL Size: 1676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CMesh::Create(CChara::CModel* model, CChunkFile& chunk, CMemory::CStage* stage)
{
	void* modelRef = *(void**)((u8*)model + 0xA4);
	u16 idx = *(u16*)((u8*)modelRef + 0xA);
	void* meshRefBase = *(void**)((u8*)modelRef + 0x10);
	CCharaMeshRefRaw* meshRef = reinterpret_cast<CCharaMeshRefRaw*>((u8*)meshRefBase + (idx * 0x64));
	*(void**)this = meshRef;
	*(void**)((u8*)this + 4) = 0;
	*(void**)((u8*)this + 8) = 0;

	CChunkFile::CChunk chunkInfo;
	chunk.PushChunk();
	while (chunk.GetNextChunk(chunkInfo)) {
		switch (chunkInfo.m_id) {
		case 0x56455254:
			meshRef->m_vertexCount = chunkInfo.m_size / 6;
			meshRef->m_vertices = static_cast<S16Vec*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x7D6, 0));
			if (meshRef->m_vertices != 0) {
				memcpy(meshRef->m_vertices, chunk.GetAddress(), chunkInfo.m_size);
				DCFlushRange(meshRef->m_vertices, meshRef->m_vertexCount * 6);
			}
			break;
		case 0x4E4F524D:
			meshRef->m_normalCount = chunkInfo.m_size / 6;
			meshRef->m_normals = static_cast<S16Vec*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x7DE, 0));
			if (meshRef->m_normals != 0) {
				memcpy(meshRef->m_normals, chunk.GetAddress(), chunkInfo.m_size);
				DCFlushRange(meshRef->m_normals, meshRef->m_normalCount * 6);
			}
			break;
		case 0x434F4C52:
			meshRef->m_colorCount = chunkInfo.m_size >> 2;
			meshRef->m_colors = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x7E6, 0);
			if (meshRef->m_colors != 0) {
				memcpy(meshRef->m_colors, chunk.GetAddress(), chunkInfo.m_size);
				DCFlushRange(meshRef->m_colors, meshRef->m_colorCount << 2);
			}
			break;
		case 0x55562020:
			meshRef->m_uvCount = chunkInfo.m_size >> 2;
			meshRef->m_uvs = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x7EE, 0);
			if (meshRef->m_uvs != 0) {
				memcpy(meshRef->m_uvs, chunk.GetAddress(), chunkInfo.m_size);
				DCFlushRange(meshRef->m_uvs, meshRef->m_uvCount << 2);
			}
			break;
		case 0x494E464F:
			meshRef->m_infoWord1 = chunk.Get4();
			meshRef->m_nodeIndex = chunk.Get4();
			meshRef->m_flags = static_cast<u8>((meshRef->m_flags & 0x7F) | ((chunk.Get4() != 0) ? 0x80 : 0));
			meshRef->m_flags = static_cast<u8>((meshRef->m_flags & 0xBF) | ((chunk.Get4() != 0) ? 0x40 : 0));
			chunk.Get4();
			chunk.Get4();
			chunk.Get4();
			chunk.Get4();
			break;
		case 0x534B494E: {
			meshRef->m_skinCount = chunkInfo.m_arg0;
			if (meshRef->m_skinCount != 0) {
				meshRef->m_skins = static_cast<CLightPcs::CBumpLight*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
				    &Memory, meshRef->m_skinCount * 0x64, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x7F8, 0));
				if (meshRef->m_skins != 0) {
					memset(meshRef->m_skins, 0, meshRef->m_skinCount * 0x64);
				}
			}

			unsigned int skinIndex = 0;
			chunk.PushChunk();
			while (chunk.GetNextChunk(chunkInfo)) {
				switch (chunkInfo.m_id) {
				case 0x4E4F4445:
					if (meshRef->m_skins != 0 && skinIndex < meshRef->m_skinCount) {
						*reinterpret_cast<u32*>(reinterpret_cast<u8*>(meshRef->m_skins) + skinIndex * 0x64 + 0x60) = chunk.Get4();
					}
					skinIndex++;
					break;
				case 0x4F4E4520:
					meshRef->m_oneWeightCountOrSize = chunkInfo.m_size;
					meshRef->m_oneWeightData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
					    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x808, 0);
					if (meshRef->m_oneWeightData != 0) {
						memcpy(meshRef->m_oneWeightData, chunk.GetAddress(), chunkInfo.m_size);
					}
					break;
				case 0x54574F20:
					meshRef->m_twoWeightCountOrSize = chunkInfo.m_size;
					meshRef->m_twoWeightData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
					    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x80E, 0);
					if (meshRef->m_twoWeightData != 0) {
						memcpy(meshRef->m_twoWeightData, chunk.GetAddress(), chunkInfo.m_size);
					}
					break;
				case 0x524D494E:
					meshRef->m_threeWeightCountOrSize = chunkInfo.m_size;
					meshRef->m_threeWeightData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
					    &Memory, chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x814, 0);
					if (meshRef->m_threeWeightData != 0) {
						memcpy(meshRef->m_threeWeightData, chunk.GetAddress(), chunkInfo.m_size);
					}
					break;
				}
			}
			chunk.PopChunk();
			break;
		}
		case 0x444C4844: {
			meshRef->m_displayListCount = chunkInfo.m_arg0 & 0xFFFF;
			if (meshRef->m_displayListCount != 0) {
				meshRef->m_displayLists = static_cast<CCharaDisplayListRaw*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
				    &Memory, meshRef->m_displayListCount * sizeof(CCharaDisplayListRaw), stage,
				    const_cast<char*>(s_chara_cpp_801d90c8), 0x820, 0));
				if (meshRef->m_displayLists != 0) {
					memset(meshRef->m_displayLists, 0, meshRef->m_displayListCount * sizeof(CCharaDisplayListRaw));
					for (u32 i = 0; i < meshRef->m_displayListCount; i++) {
						meshRef->m_displayLists[i].m_material = 0xFFFF;
					}
				}
			}

			u32 displayIndex = 0;
			chunk.PushChunk();
			while (chunk.GetNextChunk(chunkInfo)) {
				if (chunkInfo.m_id != 0x444C5354 || meshRef->m_displayLists == 0 ||
				    displayIndex >= meshRef->m_displayListCount) {
					continue;
				}

				CCharaDisplayListRaw& displayList = meshRef->m_displayLists[displayIndex++];
				displayList.m_material = chunk.Get2();
				displayList.m_size = static_cast<s32>(chunkInfo.m_arg0);
				chunk.Align(0x20);
				if (displayList.m_size > 0) {
					const unsigned int allocSize = (displayList.m_size + 0x1F) & ~0x1FU;
					displayList.m_data = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
					    &Memory, allocSize, stage, const_cast<char*>(s_chara_cpp_801d90c8), 0x830, 0);
					if (displayList.m_data != 0) {
						chunk.Get(displayList.m_data, displayList.m_size);
						DCFlushRange(displayList.m_data, displayList.m_size);
					}
				}
				chunk.Align(0x20);
			}
			chunk.PopChunk();
			break;
		}
		case 0x4D4E414D:
			strcpy(meshRef->m_name, chunk.GetString());
			break;
		}
	}
	chunk.PopChunk();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CMesh::Duplicate(CChara::CMesh* src, CMemory::CStage* stage)
{
	(void)stage;
	CopyDuplicatedMeshState(this, src);
}

/*
 * --INFO--
 * PAL Address: 0x8006efe8
 * PAL Size: 1244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CMesh::skin(int meshIndex, int start, int count, CChara::CSkin* skinRef, void* srcPos, void* srcNrm, void* srcWgt, S16Vec* dstPos, S16Vec* dstNrm, S16Vec* dstTan, S16Vec* dstBinorm)
{
	u8* oneWeightData = (u8*)srcPos;
	u8* twoWeightData = (u8*)srcNrm;
	u8* threeWeightData = (u8*)srcWgt;
	S16Vec* srcVertices = dstPos;
	S16Vec* outVertices = dstNrm;
	S16Vec* srcNormals = dstTan;
	S16Vec* outNormals = dstBinorm;

	for (int i = 0; i < meshIndex; i++) {
		u32 skinIndex = oneWeightData[0];
		u16 vertexIndex = *(u16*)(oneWeightData + 2);
		u16 normalCount = *(u16*)(oneWeightData + 4);
		float* m = (float*)((u8*)skinRef + (skinIndex * 0x64));

		float x = (float)srcVertices[vertexIndex].x;
		float y = (float)srcVertices[vertexIndex].y;
		float z = (float)srcVertices[vertexIndex].z;
		outVertices[vertexIndex].x = (s16)(m[0] * x + m[1] * y + m[2] * z + m[3]);
		outVertices[vertexIndex].y = (s16)(m[4] * x + m[5] * y + m[6] * z + m[7]);
		outVertices[vertexIndex].z = (s16)(m[8] * x + m[9] * y + m[10] * z + m[11]);

		for (u16 j = 0; j < normalCount; j++) {
			u16 normalIndex = *(u16*)(oneWeightData + 6 + (j * 2));
			float nx = (float)srcNormals[normalIndex].x;
			float ny = (float)srcNormals[normalIndex].y;
			float nz = (float)srcNormals[normalIndex].z;
			outNormals[normalIndex].x = (s16)(m[0] * nx + m[1] * ny + m[2] * nz);
			outNormals[normalIndex].y = (s16)(m[4] * nx + m[5] * ny + m[6] * nz);
			outNormals[normalIndex].z = (s16)(m[8] * nx + m[9] * ny + m[10] * nz);
		}

		oneWeightData += 8 + (normalCount * 2);
	}

	for (int i = 0; i < start; i++) {
		u32 skinIndexA = twoWeightData[0];
		u32 skinIndexB = *(u16*)(twoWeightData + 2);
		u16 wAraw = *(u16*)(twoWeightData + 4);
		u16 wBraw = *(u16*)(twoWeightData + 6);
		u16 vertexIndex = *(u16*)(twoWeightData + 8);
		u16 normalCount = *(u16*)(twoWeightData + 10);
		float totalW = (float)(wAraw + wBraw);
		float wA = totalW > 0.0f ? (float)wAraw / totalW : 1.0f;
		float wB = totalW > 0.0f ? (float)wBraw / totalW : 0.0f;
		float* mA = (float*)((u8*)skinRef + (skinIndexA * 0x64));
		float* mB = (float*)((u8*)skinRef + (skinIndexB * 0x64));

		float x = (float)srcVertices[vertexIndex].x;
		float y = (float)srcVertices[vertexIndex].y;
		float z = (float)srcVertices[vertexIndex].z;
		float pxA = mA[0] * x + mA[1] * y + mA[2] * z + mA[3];
		float pyA = mA[4] * x + mA[5] * y + mA[6] * z + mA[7];
		float pzA = mA[8] * x + mA[9] * y + mA[10] * z + mA[11];
		float pxB = mB[0] * x + mB[1] * y + mB[2] * z + mB[3];
		float pyB = mB[4] * x + mB[5] * y + mB[6] * z + mB[7];
		float pzB = mB[8] * x + mB[9] * y + mB[10] * z + mB[11];
		outVertices[vertexIndex].x = (s16)(pxA * wA + pxB * wB);
		outVertices[vertexIndex].y = (s16)(pyA * wA + pyB * wB);
		outVertices[vertexIndex].z = (s16)(pzA * wA + pzB * wB);

		for (u16 j = 0; j < normalCount; j++) {
			u16 normalIndex = *(u16*)(twoWeightData + 12 + (j * 2));
			float nx = (float)srcNormals[normalIndex].x;
			float ny = (float)srcNormals[normalIndex].y;
			float nz = (float)srcNormals[normalIndex].z;
			float nxa = mA[0] * nx + mA[1] * ny + mA[2] * nz;
			float nya = mA[4] * nx + mA[5] * ny + mA[6] * nz;
			float nza = mA[8] * nx + mA[9] * ny + mA[10] * nz;
			float nxb = mB[0] * nx + mB[1] * ny + mB[2] * nz;
			float nyb = mB[4] * nx + mB[5] * ny + mB[6] * nz;
			float nzb = mB[8] * nx + mB[9] * ny + mB[10] * nz;
			outNormals[normalIndex].x = (s16)(nxa * wA + nxb * wB);
			outNormals[normalIndex].y = (s16)(nya * wA + nyb * wB);
			outNormals[normalIndex].z = (s16)(nza * wA + nzb * wB);
		}

		twoWeightData += 12 + (normalCount * 2);
	}

	for (int i = 0; i < count; i++) {
		u32 skinIndexA = *(u16*)(threeWeightData + 0);
		u32 skinIndexB = *(u16*)(threeWeightData + 2);
		u32 skinIndexC = *(u16*)(threeWeightData + 4);
		u16 wAraw = *(u16*)(threeWeightData + 6);
		u16 wBraw = *(u16*)(threeWeightData + 8);
		u16 wCraw = *(u16*)(threeWeightData + 10);
		u16 vertexIndex = *(u16*)(threeWeightData + 12);
		u16 normalCount = *(u16*)(threeWeightData + 14);
		float totalW = (float)(wAraw + wBraw + wCraw);
		float wA = totalW > 0.0f ? (float)wAraw / totalW : 1.0f;
		float wB = totalW > 0.0f ? (float)wBraw / totalW : 0.0f;
		float wC = totalW > 0.0f ? (float)wCraw / totalW : 0.0f;
		float* mA = (float*)((u8*)skinRef + (skinIndexA * 0x64));
		float* mB = (float*)((u8*)skinRef + (skinIndexB * 0x64));
		float* mC = (float*)((u8*)skinRef + (skinIndexC * 0x64));

		float x = (float)srcVertices[vertexIndex].x;
		float y = (float)srcVertices[vertexIndex].y;
		float z = (float)srcVertices[vertexIndex].z;
		float pxA = mA[0] * x + mA[1] * y + mA[2] * z + mA[3];
		float pyA = mA[4] * x + mA[5] * y + mA[6] * z + mA[7];
		float pzA = mA[8] * x + mA[9] * y + mA[10] * z + mA[11];
		float pxB = mB[0] * x + mB[1] * y + mB[2] * z + mB[3];
		float pyB = mB[4] * x + mB[5] * y + mB[6] * z + mB[7];
		float pzB = mB[8] * x + mB[9] * y + mB[10] * z + mB[11];
		float pxC = mC[0] * x + mC[1] * y + mC[2] * z + mC[3];
		float pyC = mC[4] * x + mC[5] * y + mC[6] * z + mC[7];
		float pzC = mC[8] * x + mC[9] * y + mC[10] * z + mC[11];
		outVertices[vertexIndex].x = (s16)(pxA * wA + pxB * wB + pxC * wC);
		outVertices[vertexIndex].y = (s16)(pyA * wA + pyB * wB + pyC * wC);
		outVertices[vertexIndex].z = (s16)(pzA * wA + pzB * wB + pzC * wC);

		for (u16 j = 0; j < normalCount; j++) {
			u16 normalIndex = *(u16*)(threeWeightData + 16 + (j * 2));
			float nx = (float)srcNormals[normalIndex].x;
			float ny = (float)srcNormals[normalIndex].y;
			float nz = (float)srcNormals[normalIndex].z;
			float nxa = mA[0] * nx + mA[1] * ny + mA[2] * nz;
			float nya = mA[4] * nx + mA[5] * ny + mA[6] * nz;
			float nza = mA[8] * nx + mA[9] * ny + mA[10] * nz;
			float nxb = mB[0] * nx + mB[1] * ny + mB[2] * nz;
			float nyb = mB[4] * nx + mB[5] * ny + mB[6] * nz;
			float nzb = mB[8] * nx + mB[9] * ny + mB[10] * nz;
			float nxc = mC[0] * nx + mC[1] * ny + mC[2] * nz;
			float nyc = mC[4] * nx + mC[5] * ny + mC[6] * nz;
			float nzc = mC[8] * nx + mC[9] * ny + mC[10] * nz;
			outNormals[normalIndex].x = (s16)(nxa * wA + nxb * wB + nxc * wC);
			outNormals[normalIndex].y = (s16)(nya * wA + nyb * wB + nyc * wC);
			outNormals[normalIndex].z = (s16)(nza * wA + nzb * wB + nzc * wC);
		}

		threeWeightData += 16 + (normalCount * 2);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006ed5c
 * PAL Size: 652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CMesh::Calc(CChara::CModel* model)
{
	CCharaMeshRaw* mesh = reinterpret_cast<CCharaMeshRaw*>(this);
	CCharaMeshRefRaw* meshRef = mesh->m_data;

	if (meshRef->m_skinCount == 0) {
		mesh->m_workPositions = meshRef->m_vertices;
		mesh->m_workNormals = meshRef->m_normals;
		return;
	}

	int bufferIndex = CharaDrawBufferIndex();
	u32& cursor = CharaDrawBufferCursor(bufferIndex);
	u32 needed = (meshRef->m_vertexCount + meshRef->m_normalCount) * 6 + 0x40;
	if (0x58000u - cursor < needed) {
		mesh->m_workPositions = 0;
		mesh->m_workNormals = 0;

		if (!s_charaMeshWorkOverflowSeen) {
			s_charaMeshWorkWarnArmed = 1;
			s_charaMeshWorkOverflowSeen = true;
		}

		if ((s_charaMeshWorkWarnArmed != 0) && (System.m_execParam > 1)) {
			s_charaMeshWorkWarnArmed = 0;
			Printf__7CSystemFPce(&System, s_charaMeshWorkOverflow);
		}
		return;
	}

	u8* workBase = CharaDrawBufferBase(bufferIndex);
	mesh->m_workPositions = reinterpret_cast<S16Vec*>(workBase + cursor);
	cursor += AlignCharaWorkBytes(meshRef->m_vertexCount * 6);
	mesh->m_workNormals = reinterpret_cast<S16Vec*>(workBase + cursor);
	cursor += AlignCharaWorkBytes(meshRef->m_normalCount * 6);

	float* skinData = reinterpret_cast<float*>(meshRef->m_skins);
	for (u32 i = 0; i < meshRef->m_skinCount; i++) {
		int nodeIndex = static_cast<int>(reinterpret_cast<float(*)[4]>(skinData + 0x18)[0][0]);
		PSMTXConcat(
		    reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(&ModelNodes(model)[nodeIndex]) + 0x44),
		    reinterpret_cast<float(*)[4]>(skinData + 0x0C),
		    reinterpret_cast<float(*)[4]>(skinData));
		skinData += 0x19;
	}

	if (meshRef->m_infoWord1 != 0) {
		S16Vec* srcNormals = meshRef->m_normals;
		S16Vec* dstNormals = mesh->m_workNormals;
		for (u32 i = 0; i < meshRef->m_infoWord1; i++) {
			dstNormals[1] = srcNormals[1];
			dstNormals[2] = srcNormals[2];
			srcNormals += 3;
			dstNormals += 3;
		}
	}

	skin(
	    meshRef->m_oneWeightCountOrSize,
	    meshRef->m_twoWeightCountOrSize,
	    meshRef->m_threeWeightCountOrSize,
	    reinterpret_cast<CChara::CSkin*>(meshRef->m_skins),
	    meshRef->m_oneWeightData,
	    meshRef->m_twoWeightData,
	    meshRef->m_threeWeightData,
	    meshRef->m_vertices,
	    mesh->m_workPositions,
	    meshRef->m_normals,
	    mesh->m_workNormals);

	DCFlushRange(mesh->m_workPositions, meshRef->m_vertexCount * 6);
	DCFlushRange(mesh->m_workNormals, meshRef->m_normalCount * 6);
}

/*
 * --INFO--
 * PAL Address: 0x8006ed08
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CRefData::CRefData()
{
	*(u32*)((u8*)this + 0x00) = 0;
	*(u32*)((u8*)this + 0x04) = 0;
	*(u32*)((u8*)this + 0x08) = 0;
	*(u32*)((u8*)this + 0x0C) = 0;
	*(u32*)((u8*)this + 0x10) = 0;
	*(u32*)((u8*)this + 0x14) = 0;
	*(u32*)((u8*)this + 0x18) = 0;
	*(u32*)((u8*)this + 0x1C) = 0;
	*(u32*)((u8*)this + 0x20) = 0;
	*(u32*)((u8*)this + 0x24) = 0;
	*(u32*)((u8*)this + 0x28) = 0;
	*(u32*)((u8*)this + 0x2C) = 0;
	*(u32*)((u8*)this + 0x30) = 0;
	*(u32*)((u8*)this + 0x34) = 0;
	*(u32*)((u8*)this + 0x38) = 0;
	*(u32*)((u8*)this + 0x3C) = 0;
	*(u32*)((u8*)this + 0x40) = 0;
	*(u32*)((u8*)this + 0x44) = 0;
	*(u32*)((u8*)this + 0x48) = 0;
	*(u32*)((u8*)this + 0x4C) = 0;
	*(u32*)((u8*)this + 0x50) = 0;
	*(u32*)((u8*)this + 0x54) = 0;
	*(u32*)((u8*)this + 0x58) = 0;
	*(u32*)((u8*)this + 0x5C) = 0;
	*(u32*)((u8*)this + 0x60) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006ebd4
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CRefData::~CRefData()
{
	void** ptrs = (void**)this;
	for (int i = 0; i < 7; i++) {
		if (ptrs[i] != 0) {
			__dla__FPv(ptrs[i]);
			ptrs[i] = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006ebb8
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CDisplayList::CDisplayList()
{
	*(void**)this = 0;
	*(s32*)((u8*)this + 4) = 0;
	*(u16*)((u8*)this + 8) = 0xFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x8006eb54
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CDisplayList::~CDisplayList()
{
	void** data = (void**)((u8*)this + 4);
	if (data[0] != 0) {
		__dla__FPv(data[0]);
		data[0] = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006eb50
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CSkin::CSkin()
{
}

/*
 * --INFO--
 * PAL Address: 0x8006eb14
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CSkin::~CSkin()
{
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CSkin::Create(CChunkFile& chunk, CMemory::CStage* stage)
{
	(void)chunk;
	(void)stage;
	memset(this, 0, 0x64);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CAnimNode::IsScale()
{
	*(u8*)this |= 0x80;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcNodeWorldMatrix(float (*outMtx)[4], CChara::CNode* node)
{
	if (node != 0) {
		PSMTXCopy((float(*)[4])((u8*)node + 0x44), outMtx);
	} else {
		PSMTXIdentity(outMtx);
	}
}

CChara Chara;
CChara& gChara = Chara;
