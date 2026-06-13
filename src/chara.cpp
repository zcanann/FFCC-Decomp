#include "ffcc/ptrarray.h"
#include "ffcc/chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_light.h"
#include "ffcc/texanim.h"
#include "ffcc/textureman.h"
#include "ffcc/vector.h"

#include <PowerPC_EABI_Support/Runtime/New.h>
#include <math.h>
#include <string.h>

extern "C" float FLOAT_803301b0;
extern "C" float FLOAT_803301B4;
extern "C" float FLOAT_803301B8;
extern "C" float FLOAT_803301BC;
extern "C" float FLOAT_803301C8;
extern "C" float FLOAT_803301CC;
extern "C" float FLOAT_803301D0;
extern "C" float FLOAT_803301D4;
extern "C" float FLOAT_803301D8;
extern "C" float FLOAT_803301DC;
extern "C" float FLOAT_803301E0;
extern "C" float FLOAT_803301E4;
extern "C" float FLOAT_803301E8;
extern "C" float FLOAT_803301F8;
extern const char sCharaStageName[7];

extern const char lbl_80330200[7];
extern const char lbl_80330208[7];
extern const char lbl_80330210[5];
extern const char lbl_80330218[5];
extern "C" const char lbl_801D90D4[];
extern const Vec DAT_801D9078;

inline void* operator new(unsigned long, void* ptr)
{
	return ptr;
}

extern "C" const char s_chara_cpp[];

namespace {

typedef CChara::CMesh::CDisplayList CCharaDisplayListRaw;

struct SRTView
{
	Vec m_position;
	Vec m_rotation;
	Vec m_scale;
};

typedef CChara::CMesh::CRefData CCharaMeshRefRaw;
typedef CChara::CMesh CCharaMeshRaw;

STATIC_ASSERT(sizeof(CCharaDisplayListRaw) == 0xC);
STATIC_ASSERT(offsetof(CCharaDisplayListRaw, m_size) == 0x00);
STATIC_ASSERT(offsetof(CCharaDisplayListRaw, m_data) == 0x04);
STATIC_ASSERT(offsetof(CCharaDisplayListRaw, m_material) == 0x08);
STATIC_ASSERT(sizeof(CCharaMeshRefRaw) == 0x64);
STATIC_ASSERT(offsetof(CChara::CMesh::CRefData, m_nodeIndex) == 0x5C);
STATIC_ASSERT(offsetof(CChara::CMesh::CRefData, m_infoWord1) == 0x60);
STATIC_ASSERT(sizeof(CCharaMeshRaw) == 0x14);
STATIC_ASSERT(offsetof(CCharaMeshRaw, m_data) == 0x8);
STATIC_ASSERT(offsetof(CCharaMeshRaw, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(CCharaMeshRaw, m_workNormals) == 0x10);
STATIC_ASSERT(offsetof(CChara::CAnim, m_flags) == 0x08);
STATIC_ASSERT(offsetof(CChara::CAnim, m_interp) == 0x09);
STATIC_ASSERT(offsetof(CChara::CAnim, m_nodeCount) == 0x0E);
STATIC_ASSERT(offsetof(CChara::CAnim, m_frameCount) == 0x10);
STATIC_ASSERT(offsetof(CChara::CAnim, m_nodes) == 0x14);
STATIC_ASSERT(offsetof(CChara::CAnim, m_interpOffset) == 0x18);
STATIC_ASSERT(offsetof(CChara::CAnim, m_bank) == 0x20);
STATIC_ASSERT(sizeof(CChara::CAnimNode) == 0x18);
STATIC_ASSERT(offsetof(CChara::CAnimNode, m_name) == 0x00);
STATIC_ASSERT(offsetof(CChara::CAnimNode, m_dataOffset) == 0x10);
STATIC_ASSERT(offsetof(CChara::CAnimNode, m_flags) == 0x14);

typedef CCharaModelData CCharaModelRefRaw;

STATIC_ASSERT(sizeof(CCharaModelRefRaw) == 0x44);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_nodeCount) == 0x08);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_meshCount) == 0x0C);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_nodeRefData) == 0x10);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_meshRefData) == 0x14);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_bank) == 0x18);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CCharaModelRefRaw, m_posQuant) == 0x34);
STATIC_ASSERT(sizeof(CChara::CNode) == 0xC0);
STATIC_ASSERT(offsetof(CChara::CNode, m_refData) == 0x00);
STATIC_ASSERT(offsetof(CChara::CNode, m_localRuntimeMtx) == 0x14);
STATIC_ASSERT(offsetof(CChara::CNode, m_previousQuat) == 0x44);
STATIC_ASSERT(offsetof(CChara::CNode, m_mtx) == 0x6C);
STATIC_ASSERT(offsetof(CChara::CNode, m_dynPosition) == 0xA4);
STATIC_ASSERT(offsetof(CChara::CNode, m_flags) == 0xBC);
STATIC_ASSERT(sizeof(CChara::CNode::CRefData) == 0x94);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_localMtx) == 0x00);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_bindMtx) == 0x30);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_boneLen) == 0x60);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_childBankOffset) == 0x64);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_index) == 0x66);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_parentIndex) == 0x68);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_name) == 0x6A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_altName) == 0x7A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_childCount) == 0x8A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_type) == 0x8B);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_bindFlags) == 0x8C);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_displayIndex) == 0x8D);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_miscFlags) == 0x8E);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_usesParentLenX) == 0x8F);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_dynParamIndex) == 0x90);

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

static inline CCharaModelRefRaw* ModelRef(CChara::CModel* model)
{
	return model->m_data;
}

static inline u32 ModelMeshCount(CChara::CModel* model)
{
	return model->m_data->m_meshCount;
}

static inline u32 ModelNodeCount(CChara::CModel* model)
{
	return model->m_data->m_nodeCount;
}

static inline CMaterialSet* ModelMaterialSet(CChara::CModel* model)
{
	return model->m_data->m_materialSet;
}

static inline int ModelPosQuant(CChara::CModel* model)
{
	return model->m_data->m_posQuant;
}

static inline int ModelNormQuant(CChara::CModel* model)
{
	return model->m_data->m_normQuant;
}

static inline CCharaMeshRaw* ModelMeshes(CChara::CModel* model)
{
	return model->m_meshes;
}

static inline CChara::CNode* ModelNodes(CChara::CModel* model)
{
	return model->m_nodes;
}

static inline void* ModelBank(CChara::CModel* model)
{
	return ModelRef(model)->m_bank;
}

static inline float (*ModelDrawMtx(CChara::CModel* model))[4]
{
	return model->m_drawMtx;
}

static inline float (*ModelWorldBaseMtx(CChara::CModel* model))[4]
{
	return model->m_worldBaseMtx;
}

static inline float ModelLightAlpha(CChara::CModel* model)
{
	return model->m_lightAlpha;
}

static inline u32 ModelMeshVisibleMask(CChara::CModel* model)
{
	return model->m_meshVisibleMask;
}

static inline void*& ModelDynParams(CChara::CModel* model)
{
	return model->m_data->m_dynParams;
}

static inline u32& ModelDynCount(CChara::CModel* model)
{
	return model->m_data->m_dynCount;
}

static inline u8 ModelFlagsA0(CChara::CModel* model)
{
	return model->m_flagsA0;
}

static inline u8& ModelFlags10C(CChara::CModel* model)
{
	return model->m_flags10C;
}

static inline s8 ModelFlag10C_80(CChara::CModel* model)
{
	return model->m_flags10CBits.m_flag10C_80;
}

static inline Vec& ModelDynJitter(CChara::CModel* model)
{
	return reinterpret_cast<Vec&>(model->m_dynJitter);
}

static inline CTexAnimSet* ModelTexAnimSet(CChara::CModel* model)
{
	return model->m_texAnimSet;
}

static inline u16& ModelBlendCur(CChara::CModel* model)
{
	return model->m_blendCur;
}

static inline u16& ModelBlendMax(CChara::CModel* model)
{
	return model->m_blendMax;
}

static inline float& ModelChestTilt(CChara::CModel* model)
{
	return model->m_chestTilt;
}

static inline float& ModelChestAmp(CChara::CModel* model)
{
	return model->m_chestAmp;
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
	return *reinterpret_cast<BeforeDrawModelCallback*>(ModelRaw(model) + 0xF0);
}

static inline AfterDrawModelCallback ModelAfterDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterDrawModelCallback*>(ModelRaw(model) + 0x108);
}

static inline BeforeMeshCallback ModelBeforeMeshCallback(CChara::CModel* model)
{
	return *reinterpret_cast<BeforeMeshCallback*>(ModelRaw(model) + 0xF4);
}

static inline AfterMeshDrawCallback ModelAfterMeshDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshDrawCallback*>(ModelRaw(model) + 0xFC);
}

static inline AfterMeshEnvCallback ModelAfterMeshEnvCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshEnvCallback*>(ModelRaw(model) + 0x104);
}

static inline CustomMeshDrawCallback ModelCustomMeshDrawCallback(CChara::CModel* model)
{
	return *reinterpret_cast<CustomMeshDrawCallback*>(ModelRaw(model) + 0xF8);
}

static inline AfterMeshDrawCallback ModelShadowDisplayListCallback(CChara::CModel* model)
{
	return *reinterpret_cast<AfterMeshDrawCallback*>(ModelRaw(model) + 0x100);
}

static inline void* ModelCbUser0(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0xE4);
}

static inline void* ModelCbUser1(CChara::CModel* model)
{
	return *reinterpret_cast<void**>(ModelRaw(model) + 0xE8);
}

static inline float& ModelTwistAngle(CChara::CModel* model)
{
	return model->m_twistAngle;
}

static inline int CharaDrawBufferIndex()
{
	return Chara.GetDrawBufferIndex();
}

static inline u32& CharaDrawBufferCursor(int bufferIndex)
{
	return Chara.GetDrawBufferCursor(bufferIndex);
}

static inline u8* CharaDrawBufferBase(int bufferIndex)
{
	return Chara.GetDrawBufferBase(bufferIndex);
}

static inline u32 AlignCharaWorkBytes(u32 size)
{
	return (size + 0x1F) & ~0x1Fu;
}

static inline void InitCharaMaterialState()
{
	MaterialMan.SetDefaultDrawEnv(0x000ACE0F);
}

static inline void CopyCharaMaterialEnv()
{
	MaterialMan.SaveCurrentEnvAsStd();
}

static inline void SetMaterialManNormalArray(void* normals)
{
	MaterialMan.SetGeometryArraySource(normals);
}

static inline u32 CharaFourCC(char a, char b, char c, char d)
{
	return (static_cast<u32>(a) << 24) | (static_cast<u32>(b) << 16) | (static_cast<u32>(c) << 8) | static_cast<u32>(d);
}

static inline char* NodeRefName(CChara::CNode* node)
{
	return node->m_refData->m_name;
}

static inline char* NodeRefAltName(CChara::CNode* node)
{
	return node->m_refData->m_altName;
}

static inline s8& NodeDynParamIndex(CChara::CNode* node)
{
	return node->m_refData->m_dynParamIndex;
}

static inline u16 NodeRefIndex(CChara::CNode* node)
{
	return node->m_refData->m_index;
}

static inline s16 NodeParentIndex(CChara::CNode* node)
{
	return node->m_refData->m_parentIndex;
}

static inline u8 NodeChildCount(CChara::CNode* node)
{
	return node->m_refData->m_childCount;
}

static inline s16 NodeChildBankOffset(CChara::CNode* node)
{
	return node->m_refData->m_childBankOffset;
}

static inline u8 NodeUsesParentLenX(CChara::CNode* node)
{
	return node->m_refData->m_usesParentLenX;
}

static inline float NodeBoneLen(CChara::CNode* node)
{
	return node->m_refData->m_boneLen;
}

static inline MtxPtr NodeWorldMtx(CChara::CNode* node)
{
	return node->m_mtx;
}

static inline MtxPtr NodeLocalRuntimeMtx(CChara::CNode* node)
{
	return node->m_localRuntimeMtx;
}

static inline float* NodeRuntimeScale(CChara::CNode* node)
{
	return reinterpret_cast<float*>(reinterpret_cast<u8*>(node) + 0x8);
}

static inline Vec& NodeDynPosition(CChara::CNode* node)
{
	return reinterpret_cast<Vec&>(node->m_dynPosition);
}

static inline Vec& NodeDynVelocity(CChara::CNode* node)
{
	return reinterpret_cast<Vec&>(node->m_dynVel);
}

static inline MtxPtr NodeRefLocalMtx(CChara::CNode* node)
{
	return node->m_refData->m_localMtx;
}

static inline MtxPtr NodeRefBindMtx(CChara::CNode* node)
{
	return node->m_refData->m_bindMtx;
}

static inline float ModelBaseScale(CChara::CModel* model)
{
	return model->m_data->m_baseScale;
}

static inline s16& ModelHeadIndex(CChara::CModel* model)
{
	return model->m_data->m_headNodeIndex;
}

static inline s16& ModelChest3Index(CChara::CModel* model)
{
	return model->m_data->m_chest3NodeIndex;
}

static inline s16& ModelChest2Index(CChara::CModel* model)
{
	return model->m_data->m_chest2NodeIndex;
}

static inline s16& ModelChest1Index(CChara::CModel* model)
{
	return model->m_data->m_chest1NodeIndex;
}

static inline float TexAnimSetChin(CTexAnimSet* texAnimSet)
{
	return texAnimSet->GetChin();
}

static inline Quaternion& NodePreviousQuat(CChara::CNode* node)
{
	return node->m_previousQuat;
}

static inline Vec& NodePreviousPosition(CChara::CNode* node)
{
	return node->m_previousPosition;
}

static inline Vec& NodePreviousScale(CChara::CNode* node)
{
	return node->m_previousScale;
}

static inline CChara::CAnimNode*& NodeAnimNode0(CChara::CNode* node)
{
	return node->m_animNode0;
}

static inline CChara::CAnimNode*& NodeAnimNode1(CChara::CNode* node)
{
	return node->m_animNode1;
}

static inline u8& NodeRuntimeFlags(CChara::CNode* node)
{
	return node->m_flags;
}

static inline s8 NodeRuntimeFlag80(CChara::CNode* node)
{
	return node->m_flagsBits.m_flag_80;
}

static inline u8 AnimFlags(CChara::CAnim* anim)
{
	return anim->m_flags;
}

static inline u8 AnimInterpCount(CChara::CAnim* anim)
{
	return reinterpret_cast<u8*>(anim)[0x9];
}

static inline u16 AnimNodeCount(CChara::CAnim* anim)
{
	return anim->m_nodeCount;
}

static inline u16 AnimFrameCount(CChara::CAnim* anim)
{
	return anim->m_frameCount;
}

static inline CChara::CAnimNode* AnimNodes(CChara::CAnim* anim)
{
	return anim->m_nodes;
}

static inline u32 AnimInterpOffset(CChara::CAnim* anim)
{
	return anim->m_interpOffset;
}

static inline void* AnimBank(CChara::CAnim* anim)
{
	return anim->m_bank;
}

static inline char* AnimNodeName(CChara::CAnimNode* node)
{
	return node->m_name;
}

static inline bool AnimNodeUsesScale(CChara::CAnimNode* node)
{
	return ((*reinterpret_cast<u8*>(&node->m_flags) >> 7) & 1) != 0;
}

static inline u8 ModelAttachMode(CChara::CModel* model)
{
	return *(reinterpret_cast<u8*>(model) + 0xA1);
}

static inline void ReleaseRefCountedNonNull(void* refObject)
{
	CRef* ref = reinterpret_cast<CRef*>(refObject);
	if (ref->DecRef() == 0) {
		delete ref;
	}
}

static inline void ReleaseRefCounted(void* refObject)
{
	if (refObject == 0) {
		return;
	}

	ReleaseRefCountedNonNull(refObject);
}

static inline void RetainRefCounted(void* refObject)
{
	if (refObject != 0) {
		reinterpret_cast<CRef*>(refObject)->AddRef();
	}
}

static inline void CopyDuplicatedNodeState(CChara::CNode* dst, CChara::CNode* src)
{
	dst->m_refData = src->m_refData;
	PSMTXCopy(NodeLocalRuntimeMtx(src), NodeLocalRuntimeMtx(dst));
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
	s16 parent = NodeParentIndex(node);
	if (parent >= 0) {
		CChara::CNode* parentNode = ModelNodes(model) + parent;
		PSMTXConcat(NodeRefBindMtx(parentNode), NodeRefLocalMtx(node), NodeRefBindMtx(node));
	} else {
		PSMTXCopy(NodeRefLocalMtx(node), NodeRefBindMtx(node));
	}
	PSMTXCopy(NodeRefBindMtx(node), NodeWorldMtx(node));
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

static const char s_charaMeshWorkOverflow[] = "chara mesh work buffer overflow\n";
static int s_charaMeshWorkWarnArmed;
static char s_charaMeshWorkOverflowSeen;

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
inline void D3DXMatrixMultiplyRotate(float (*out)[4], float (*a)[4], float (*b)[4])
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
	m_amemStage = Memory.CreateStage(0xc0000, const_cast<char*>(sCharaStageName), 0);
	m_amemLoadStage = 0;
	m_drawBuffers[0].m_base = new (Chara.GetMemoryStage(), const_cast<char*>(s_chara_cpp), 0x3f) u8[0x58000];
	m_drawBuffers[1].m_base = new (Chara.GetMemoryStage(), const_cast<char*>(s_chara_cpp), 0x40) u8[0x58000];
	m_drawBufferIndex = 1;
	m_drawBufferIndex = 1 - m_drawBufferIndex;
	m_drawBuffers[m_drawBufferIndex].m_cursor = 0;
	m_amemAnimSize = 0;
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
	if (m_drawBuffers[0].m_base != 0) {
		delete[] m_drawBuffers[0].m_base;
		m_drawBuffers[0].m_base = 0;
	}
	if (m_drawBuffers[1].m_base != 0) {
		delete[] m_drawBuffers[1].m_base;
		m_drawBuffers[1].m_base = 0;
	}
	Memory.DestroyStage(m_amemStage);
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
	makeFurTex();
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
	freeFurTex();
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
	m_drawBufferIndex = 1 - m_drawBufferIndex;
	m_drawBuffers[m_drawBufferIndex].m_cursor = 0;
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
#pragma dont_inline on
void CChara::gqrInit(unsigned long, unsigned long, unsigned long)
{
	asm {
		mtspr GQR5, r4
		mtspr GQR6, r5
		mtspr GQR7, r6
	}
}
#pragma dont_inline reset

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
	m_nodeCount = 0;
	m_meshCount = 0;
	m_nodeRefData = 0;
	m_meshRefData = 0;
	m_bank = 0;
	m_chest1NodeIndex = -1;
	m_chest2NodeIndex = -1;
	m_chest3NodeIndex = -1;
	m_headNodeIndex = -1;
	m_materialSet = 0;
	m_baseScale = 1.0f;
	m_posQuant = 7;
	m_normQuant = 0xC;
	m_dynParams = 0;
	m_dynCount = 0;
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
	u8* raw = reinterpret_cast<u8*>(this);
	void** ptr;

	ptr = reinterpret_cast<void**>(raw + 0x40);
	if (*ptr != 0) {
		delete[] static_cast<u8*>(*ptr);
		*ptr = 0;
	}
	ptr = reinterpret_cast<void**>(raw + 0x10);
	if (*ptr != 0) {
		delete[] reinterpret_cast<CChara::CNode::CRefData*>(*ptr);
		*ptr = 0;
	}
	ptr = reinterpret_cast<void**>(raw + 0x14);
	if (*ptr != 0) {
		delete[] reinterpret_cast<CChara::CMesh::CRefData*>(*ptr);
		*ptr = 0;
	}
	ptr = reinterpret_cast<void**>(raw + 0x18);
	if (*ptr != 0) {
		delete[] static_cast<u8*>(*ptr);
		*ptr = 0;
	}
	ptr = reinterpret_cast<void**>(raw + 0x24);
	if (*ptr != 0) {
		ReleaseRefCountedNonNull(*ptr);
		*ptr = 0;
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
	m_data = 0;
	m_texSet = 0;
	m_anim = 0;
	m_texAnimSet = 0;
	m_nodes = 0;
	m_meshes = 0;

	PSMTXIdentity(m_matrix);

	m_furLenScale = 0.2f;
	m_furStep = 3.0f;
	m_time = 0.0f;
	m_curFrame = 0.0f;
	m_dynJitter.x = 0.0f;
	m_dynJitter.y = 0.0f;
	m_dynJitter.z = 0.0f;
	m_blendCur = 0;
	m_blendMax = 0;
	m_meshVisibleMask = 0xFFFFFFFF;
	m_animStart = 0.0f;
	m_animEnd = 0.0f;
	m_chestAmp = 0.0f;
	m_chestTilt = 0.0f;
	m_lightAlpha = 1.0f;
	m_callbackContext = 0;
	m_callbackParam = 0;
	m_afterMeshDrawCallback = 0;
	m_beforeCalcMatrixCallback = 0;
	m_beforeMeshLockEnvCallback = 0;
	m_beforeDrawShadowLockEnvCallback = 0;
	m_drawMeshDLCallback = 0;
	m_drawShadowMeshDLCallback = 0;
	m_afterDrawMeshCallback = 0;
	m_afterDrawModelCallback = 0;

	m_flags10CBits.m_flag10C_80 = 1;
	m_flagsA0Bits.m_flagA0_80 = 0;
	m_flagsA0Bits.m_flagA0_40 = 0;
	m_flagsA0Bits.m_flagA0_20 = 1;
	m_flags10CBits.m_flag10C_40 = 0;

	m_furTarget = 1.0f;
	m_furCur = 1.0f;
	m_attachMode = 0;
	m_twistAngle = 0.0f;
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
	void*& texSet = reinterpret_cast<void*&>(m_texSet);
	if (texSet != 0) {
		ReleaseRefCountedNonNull(texSet);
		texSet = 0;
	}

	void*& anim = reinterpret_cast<void*&>(m_anim);
	if (anim != 0) {
		ReleaseRefCountedNonNull(anim);
		anim = 0;
	}

	void*& texAnimSet = reinterpret_cast<void*&>(m_texAnimSet);
	if (texAnimSet != 0) {
		ReleaseRefCountedNonNull(texAnimSet);
		texAnimSet = 0;
	}

	void*& refData = reinterpret_cast<void*&>(m_data);
	if (refData != 0) {
		ReleaseRefCountedNonNull(refData);
		refData = 0;
	}

	void*& nodes = reinterpret_cast<void*&>(m_nodes);
	if (nodes != 0) {
		delete[] static_cast<CChara::CNode*>(nodes);
		nodes = 0;
	}

	void*& meshes = reinterpret_cast<void*&>(m_meshes);
	if (meshes != 0) {
		delete[] static_cast<CChara::CMesh*>(meshes);
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
	m_time = 0.0f;
	m_curFrame = 0.0f;
	m_dynJitter.x = 0.0f;
	m_dynJitter.y = 0.0f;
	m_dynJitter.z = 0.0f;
	m_blendCur = 0;
	m_blendMax = 0;
	m_meshVisibleMask = 0xFFFFFFFF;
	m_animStart = 0.0f;
	m_animEnd = 0.0f;
	m_chestAmp = 0.0f;
	m_chestTilt = 0.0f;
	m_lightAlpha = 1.0f;
	m_callbackContext = 0;
	m_callbackParam = 0;
	m_afterMeshDrawCallback = 0;
	m_beforeCalcMatrixCallback = 0;
	m_beforeMeshLockEnvCallback = 0;
	m_beforeDrawShadowLockEnvCallback = 0;
	m_drawMeshDLCallback = 0;
	m_drawShadowMeshDLCallback = 0;
	m_afterDrawMeshCallback = 0;
	m_afterDrawModelCallback = 0;
	m_flags10CBits.m_flag10C_80 = 1;
	m_flagsA0Bits.m_flagA0_80 = 0;
	m_flagsA0Bits.m_flagA0_40 = 0;
	m_flagsA0Bits.m_flagA0_20 = 1;
	m_flags10CBits.m_flag10C_40 = 0;
	m_furTarget = 1.0f;
	m_furCur = 1.0f;
	m_attachMode = 0;
	m_twistAngle = 0.0f;
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
	CCharaModelRefRaw* ref = reinterpret_cast<CCharaModelRefRaw*>(
	    new (stage, const_cast<char*>(s_chara_cpp), 0x111) CChara::CModel::CRefData());
	m_data = ref;

	CChunkFile chunkFile(fileData);
	CChunkFile::CChunk chunk;
	CChara* charaPtr = &Chara;

	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != CharaFourCC('C', 'H', 'M', ' ')) {
			continue;
		}
		if (chunk.m_version < 5) {
			if (2 <= static_cast<u32>(System.m_execParam)) {
				System.Printf(const_cast<char*>(lbl_801D90D4));
			}
			break;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			if (chunk.m_id == 0x494E464F) {
				m_data->m_baseScale = chunkFile.GetF4();
				m_furLenScale = chunkFile.GetF4();
				m_furStep = chunkFile.GetF4();
			} else if (chunk.m_id == 0x5155414E) {
				m_data->m_posQuant = chunkFile.Get4();
				m_data->m_normQuant = chunkFile.Get4();
			} else if (chunk.m_id == 0x4D534554) {
				CMaterialSet* materialSet =
				    new(charaPtr->GetMemoryStage(), const_cast<char*>(s_chara_cpp), 0x132) CMaterialSet();
				m_data->m_materialSet = materialSet;
				CMaterialSet* createdSet = m_data->m_materialSet;
				createdSet->m_materials.SetDefaultSize(0x20);
				createdSet->m_materials.SetGrow(0);
				m_data->m_materialSet->Create(chunkFile, 0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0), gCharaPartWorkPtr);
			} else if (chunk.m_id == 0x54415354) {
				if (chunk.m_arg0 != 0) {
					CTexAnimSet* texAnimSet =
					    new(charaPtr->GetMemoryStage(), const_cast<char*>(s_chara_cpp), 0x13A) CTexAnimSet();
					m_texAnimSet = texAnimSet;
					m_texAnimSet->Create(chunkFile, stage);
				}
			} else if (chunk.m_id == 0x4E534554) {
				m_data->m_nodeCount = 0;
				CChara::CNode::CRefData* nodeRefs =
				    new (stage, const_cast<char*>(s_chara_cpp), 0x143) CChara::CNode::CRefData[chunk.m_arg0];
				m_data->m_nodeRefData = nodeRefs;
				CChara::CNode* nodes =
				    new (stage, const_cast<char*>(s_chara_cpp), 0x145) CChara::CNode[chunk.m_arg0];
				m_nodes = nodes;

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x4E4F4445) {
						CNode* node = &m_nodes[m_data->m_nodeCount];
						node->Create(chunkFile, this, static_cast<CChara::CNode::TYPE>(chunk.m_arg0), stage);
						if (strcmp(NodeRefName(node), lbl_80330200) == 0) {
							m_data->m_headNodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), lbl_80330208) == 0) {
							m_data->m_chest3NodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), lbl_80330210) == 0) {
							m_data->m_chest2NodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), lbl_80330218) == 0) {
							m_data->m_chest1NodeIndex = node->m_refData->m_index;
						}
						m_data->m_nodeCount = m_data->m_nodeCount + 1;
					}
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == 0x4D535354) {
				m_data->m_meshCount = 0;
				CChara::CMesh::CRefData* meshRefs =
				    new (stage, const_cast<char*>(s_chara_cpp), 0x171) CChara::CMesh::CRefData[chunk.m_arg0];
				m_data->m_meshRefData = meshRefs;
				CChara::CMesh* meshes =
				    new (stage, const_cast<char*>(s_chara_cpp), 0x173) CChara::CMesh[chunk.m_arg0];
				m_meshes = meshes;

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x4D455348) {
						CMesh* mesh = &m_meshes[m_data->m_meshCount];
						mesh->Create(this, chunkFile, stage);
						m_data->m_meshCount = m_data->m_meshCount + 1;
					}
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == 0x42414E4B) {
				void* bank = new(stage, const_cast<char*>(s_chara_cpp), 0x187) u8[chunk.m_size];
				m_data->m_bank = bank;
				memcpy(m_data->m_bank, chunkFile.GetAddress(), chunk.m_size);
			}
		}
		chunkFile.PopChunk();
	}

	setup();
	if (m_texAnimSet != 0) {
		m_texAnimSet->AttachMaterialSet(m_data->m_materialSet);
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
	CChunkFile chunkFile(dynData);
	CChunkFile::CChunk chunk;
	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != CharaFourCC('C', 'H', 'D', ' ')) {
			continue;
		}

		if (ModelDynParams(this) != 0) {
			operator delete[](ModelDynParams(this));
			ModelDynParams(this) = 0;
		}
		ModelDynCount(this) = 0;

		CNode* node = ModelNodes(this);
		for (u32 i = 0; i < ModelNodeCount(this); i++, node++) {
			NodeDynParamIndex(node) = -1;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			if (chunk.m_id == CharaFourCC('D', 'G', 'R', 'P')) {
				if (chunk.m_arg0 == 0) {
					continue;
				}

				ModelDynCount(this) = 0;
				void* dynParams = static_cast<void*>(new (stage, const_cast<char*>(s_chara_cpp), 0x1E7) u8[chunk.m_arg0 * 0x24]);
				ModelDynParams(this) = dynParams;

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id != CharaFourCC('D', 'Y', 'N', ' ')) {
						continue;
					}

					chunkFile.PushChunk();
					while (chunkFile.GetNextChunk(chunk)) {
						if (chunk.m_id == CharaFourCC('P', 'A', 'R', 'M')) {
							float v0 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24) = v0;
							float v1 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 4) = v1;
							float v2 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 8) = v2;
							u32 v3 = chunkFile.Get4();
							*reinterpret_cast<u32*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0xC) = v3;
							u32 v4 = chunkFile.Get4();
							*reinterpret_cast<u32*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0x10) = v4;
							float v5 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0x14) = v5;
							float v6 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0x1C) = v6;
							float v7 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0x18) = v7;
							float v8 = chunkFile.GetF4();
							*reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + ModelDynCount(this) * 0x24 + 0x20) = v8;
						}
					}
					chunkFile.PopChunk();
					ModelDynCount(this)++;
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == CharaFourCC('N', 'S', 'E', 'T')) {
				chunkFile.PushChunk();
				u32 currentNode = 0;
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == CharaFourCC('N', 'A', 'M', 'E')) {
						char* name = chunkFile.GetString();
						CNode* searchNode = ModelNodes(this);
						for (currentNode = 0; currentNode < ModelNodeCount(this); currentNode++, searchNode++) {
							if (strcmp(NodeRefName(searchNode), name) == 0) {
								goto nextNsetChunk;
							}
						}
						currentNode = 0xFFFFFFFF;
					} else if (chunk.m_id == CharaFourCC('D', 'Y', 'N', ' ')) {
						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(chunk)) {
							if (chunk.m_id == CharaFourCC('P', 'A', 'R', 'M')) {
								s8 paramIndex = static_cast<s8>(chunkFile.Get4());
								NodeDynParamIndex(&ModelNodes(this)[currentNode]) = paramIndex;
							}
						}
						chunkFile.PopChunk();
					}
				nextNsetChunk:;
				}
				chunkFile.PopChunk();
			}
		}
		chunkFile.PopChunk();
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
	for (u32 i = 0; i < ModelNodeCount(this); i++, node++) {
		PSMTXCopy(NodeRefLocalMtx(node), NodeLocalRuntimeMtx(node));
		s8 disp = node->m_refData->m_displayIndex;
		if (disp >= 0 && static_cast<u32>(disp) < ModelRef(this)->m_meshCount) {
			node->m_displayMesh = reinterpret_cast<CMesh*>(ModelMeshes(this)) + disp;
		}
	}

	calcBindMatrix();

	CCharaMeshRaw* meshRaw = ModelMeshes(this);
	for (u32 i = 0; i < ModelRef(this)->m_meshCount; i++, meshRaw++) {
		int skinOffset;
		u32 j = 0;
		skinOffset = 0;
		for (; j < meshRaw->m_data->m_skinCount; j++) {
			u8* skin = reinterpret_cast<u8*>(meshRaw->m_data->m_skins) + skinOffset;
			u32 skinNodeIndex = *reinterpret_cast<u32*>(skin + 0x60);
			PSMTXInverse(NodeRefBindMtx(&ModelNodes(this)[skinNodeIndex]), reinterpret_cast<MtxPtr>(skin + 0x30));
			PSMTXConcat(reinterpret_cast<MtxPtr>(skin + 0x30), NodeRefBindMtx(&ModelNodes(this)[meshRaw->m_data->m_nodeIndex]), reinterpret_cast<MtxPtr>(skin + 0x30));
			skinOffset += 100;
		}
	}

	AttachAnim(m_anim, -1, -1, 0);

	CTextureSet* texSet = m_texSet;
	CTextureSet* oldTexSet = m_texSet;
	if (texSet != oldTexSet) {
		if (oldTexSet != 0) {
			if (oldTexSet->DecRef() == 0) {
				delete oldTexSet;
			}
			m_texSet = 0;
		}
		m_texSet = texSet;
		if (m_texSet != 0) {
			m_texSet->AddRef();
		}
	}
	if (m_data->m_materialSet != 0) {
		m_data->m_materialSet->SetTextureSet(m_texSet);
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
	void* cloneMem = operator new(sizeof(CModel), stage, const_cast<char*>(s_chara_cpp), 0x25A);
	CModel* clone = cloneMem != 0 ? new (cloneMem) CModel() : 0;

	clone->m_data = ModelRef(this);
	++*reinterpret_cast<int*>(reinterpret_cast<u8*>(ModelRef(this)) + 4);

	clone->m_nodes = new (stage, const_cast<char*>(s_chara_cpp), 0x263) CChara::CNode[ModelNodeCount(this)];
	{
		u32 i = 0;
		u32 byteOff = 0;
		for (; i < ModelNodeCount(this); byteOff += 0xc0, i++) {
			CChara::CNode* src = reinterpret_cast<CChara::CNode*>(reinterpret_cast<u8*>(ModelNodes(this)) + byteOff);
			CChara::CNode* dst = reinterpret_cast<CChara::CNode*>(reinterpret_cast<u8*>(clone->m_nodes) + byteOff);
			dst->m_refData = src->m_refData;
			PSMTXCopy(NodeLocalRuntimeMtx(src), NodeLocalRuntimeMtx(dst));
			PSMTXCopy(NodeWorldMtx(src), NodeWorldMtx(dst));
			NodePreviousQuat(dst) = NodePreviousQuat(src);
			NodePreviousPosition(dst) = NodePreviousPosition(src);
			NodePreviousScale(dst) = NodePreviousScale(src);
			dst->m_flagsBits.m_flag_80 = src->m_flagsBits.m_flag_80;
		}
	}

	CChara::CMesh* cloneMeshes = new (stage, const_cast<char*>(s_chara_cpp), 0x26C) CChara::CMesh[ModelMeshCount(this)];
	clone->m_meshes = cloneMeshes;
	for (u32 i = 0; i < ModelMeshCount(this); i++) {
		CChara::CMesh* dst = &reinterpret_cast<CChara::CMesh*>(clone->m_meshes)[i];
		CChara::CMesh* src = &reinterpret_cast<CChara::CMesh*>(ModelMeshes(this))[i];
		u8* dstRaw = reinterpret_cast<u8*>(dst);
		u8* srcRaw = reinterpret_cast<u8*>(src);
		*reinterpret_cast<void**>(dstRaw + 8) = *reinterpret_cast<void**>(srcRaw + 8);
		*reinterpret_cast<void**>(dstRaw + 0xc) = 0;
		*reinterpret_cast<void**>(dstRaw + 0x10) = 0;
	}

	if (m_texSet != 0) {
		clone->m_texSet = m_texSet;
		clone->m_texSet->AddRef();
	}
	if (ModelTexAnimSet(this) != 0) {
		clone->m_texAnimSet = ModelTexAnimSet(this)->Duplicate(stage);
	}

	clone->m_time = 0.0f;
	clone->m_curFrame = 0.0f;
	clone->m_dynJitter.x = 0.0f;
	clone->m_dynJitter.y = 0.0f;
	clone->m_dynJitter.z = 0.0f;
	clone->m_blendCur = 0;
	clone->m_blendMax = 0;
	clone->m_meshVisibleMask = 0xFFFFFFFF;
	clone->m_animStart = 0.0f;
	clone->m_animEnd = 0.0f;
	clone->m_chestAmp = 0.0f;
	clone->m_chestTilt = 0.0f;
	clone->m_lightAlpha = 1.0f;
	clone->m_callbackContext = 0;
	clone->m_callbackParam = 0;
	clone->m_afterMeshDrawCallback = 0;
	clone->m_beforeCalcMatrixCallback = 0;
	clone->m_beforeMeshLockEnvCallback = 0;
	clone->m_beforeDrawShadowLockEnvCallback = 0;
	clone->m_drawMeshDLCallback = 0;
	clone->m_drawShadowMeshDLCallback = 0;
	clone->m_afterDrawMeshCallback = 0;
	clone->m_afterDrawModelCallback = 0;
	clone->m_flags10CBits.m_flag10C_80 = 1;
	clone->m_flagsA0Bits.m_flagA0_80 = 0;
	clone->m_flagsA0Bits.m_flagA0_40 = 0;
	clone->m_flagsA0Bits.m_flagA0_20 = 1;
	clone->m_flags10CBits.m_flag10C_40 = 0;
	clone->m_furTarget = 1.0f;
	clone->m_furCur = 1.0f;
	clone->m_attachMode = 0;
	clone->m_twistAngle = 0.0f;

	clone->setup();
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
	CNode* node = ModelNodes(this);
	u32 i = 0;

	while (i < ModelNodeCount(this)) {
		if (NodeParentIndex(node) < 0) {
			node->CalcBind(this);
		}
		i++;
		node++;
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
	float(*localMtx)[4] = (float(*)[4])((u8*)this + 0x08);
	float(*worldBaseMtx)[4] = (float(*)[4])((u8*)this + 0x38);
	float(*drawMtx)[4] = (float(*)[4])((u8*)this + 0x68);
	const float zero = FLOAT_803301b0;
	const float one = FLOAT_803301BC;

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
	u32 normQuant;
	u32 posQuant = ModelPosQuant(this);
	normQuant = ModelNormQuant(this);

	u32 posGqr = (posQuant << 24) | 0x70000 | (posQuant << 8) | 7;
	u32 normGqr = (normQuant << 24) | 0x70000 | (normQuant << 8) | 7;
	Chara.gqrInit(posGqr, normGqr, 0x0C070C07);

	u32 i = 0;
	CMesh* mesh = ModelMeshes(this);
	for (; i < this->m_data->m_meshCount; i++, mesh++) {
		mesh->Calc(this);
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
	if (((AnimFlags(m_anim) >> 6) & 1) == 0) {
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
	float frame;
	if (m_anim != 0) {
		float total = FLOAT_803301BC + (m_animEnd - m_animStart);
		if (((AnimFlags(m_anim) >> 6) & 1) != 0) {
			if (m_time < FLOAT_803301b0) {
				float negTime = -m_time;
				float limit = total - FLOAT_803301BC;
				float clamped = (negTime < limit) ? negTime : limit;
				frame = ((m_animStart + total) - *(volatile float*)&FLOAT_803301BC) - clamped;
			} else {
				float limit = total - FLOAT_803301BC;
				float clamped = (m_time < limit) ? m_time : limit;
				frame = m_animStart + clamped;
			}
		} else if (m_time < FLOAT_803301b0) {
			frame = ((m_animStart + total) - FLOAT_803301BC) - static_cast<float>(fmod(-m_time, total));
		} else {
			frame = m_animStart + static_cast<float>(fmod(m_time, total));
		}
	} else {
		frame = FLOAT_803301b0;
	}
	m_curFrame = frame;
	if (m_anim != 0) {
		m_anim->InitQuantize();
	}

	CNode* node = ModelNodes(this);
	u32 nodeCount = ModelNodeCount(this);
	for (u32 i = 0; i < nodeCount; i++, node++) {
		CChara::CNode::CRefData* ref = node->m_refData;
		CNode* parentNode;
		if (ref->m_parentIndex < 0) {
			parentNode = 0;
		} else {
			parentNode = ModelNodes(this) + ref->m_parentIndex;
		}

		SRTView srt;
		Mtx animMtx;

		if (NodeAnimNode0(node) != 0 || NodeAnimNode1(node) != 0) {
			if (parentNode != 0 && NodeAnimNode0(parentNode) != 0 && AnimNodeUsesScale(NodeAnimNode0(parentNode))) {
				if (NodeRuntimeFlag80(node)) {
					float* parentScale = NodeRuntimeScale(parentNode);
					PSMTXScale(NodeLocalRuntimeMtx(node),
					           FLOAT_803301BC / parentScale[0],
					           FLOAT_803301BC / parentScale[1],
					           FLOAT_803301BC / parentScale[2]);
				}
			} else if (NodeRuntimeFlag80(node)) {
				float baseScale;
				if (parentNode != 0 || (baseScale = ModelBaseScale(this)) == FLOAT_803301BC) {
					PSMTXIdentity(NodeLocalRuntimeMtx(node));
				} else {
					PSMTXScale(NodeLocalRuntimeMtx(node), baseScale, baseScale, baseScale);
				}
			}

			if (ref->m_usesParentLenX != 0) {
				NodeLocalRuntimeMtx(node)[0][3] = NodeBoneLen(parentNode);
			}

			if (NodeAnimNode1(node) != 0) {
				NodeAnimNode1(node)->Interp(m_anim, reinterpret_cast<SRT*>(&srt), frame);
				if (AnimNodeUsesScale(NodeAnimNode1(node))) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt));
				}
				PSMTXConcat(NodeLocalRuntimeMtx(node), animMtx, NodeLocalRuntimeMtx(node));
				PSMTXScale(animMtx,
				           FLOAT_803301BC / srt.m_scale.x,
				           FLOAT_803301BC / srt.m_scale.y,
				           FLOAT_803301BC / srt.m_scale.z);
				PSMTXConcat(NodeLocalRuntimeMtx(node), animMtx, NodeLocalRuntimeMtx(node));
			}

			if (NodeAnimNode0(node) != 0) {
				NodeAnimNode0(node)->Interp(m_anim, reinterpret_cast<SRT*>(&srt), frame);
				s16 nodeIndex = ref->m_index;
				if (nodeIndex == ModelHeadIndex(this) || nodeIndex == ModelChest3Index(this) ||
				    nodeIndex == ModelChest2Index(this)) {
					float tiltScale;
					if (nodeIndex == ModelChest2Index(this)) {
						srt.m_rotation.y = -(ModelChestTilt(this) * FLOAT_803301D0 - srt.m_rotation.y);
						tiltScale = FLOAT_803301D0;
					} else {
						srt.m_rotation.x = ModelChestTilt(this) * FLOAT_803301F8 + srt.m_rotation.x;
						tiltScale = FLOAT_803301F8;
					}
					srt.m_rotation.z = ModelChestAmp(this) * tiltScale + srt.m_rotation.z;
				} else if (nodeIndex == ModelChest1Index(this) && ModelTexAnimSet(this) != 0) {
					srt.m_rotation.z += TexAnimSetChin(ModelTexAnimSet(this));
				}
				if (AnimNodeUsesScale(NodeAnimNode0(node))) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt));
				}
				if (NodeRuntimeFlag80(node)) {
					PSMTXConcat(NodeLocalRuntimeMtx(node), animMtx, NodeLocalRuntimeMtx(node));
				}
				float* runtimeScale = NodeRuntimeScale(node);
				runtimeScale[0] = srt.m_scale.x;
				runtimeScale[1] = srt.m_scale.y;
				runtimeScale[2] = srt.m_scale.z;
			} else {
				float* runtimeScale = NodeRuntimeScale(node);
				float zero = FLOAT_803301b0;
				runtimeScale[2] = zero;
				runtimeScale[1] = zero;
				runtimeScale[0] = zero;
			}
		} else {
			if (NodeRuntimeFlag80(node)) {
				PSMTXCopy(ref->m_localMtx, NodeLocalRuntimeMtx(node));
			}
		}

		u16 blendCur = ModelBlendCur(this);
		if (blendCur != 0) {
			u16 blendMax = ModelBlendMax(this);
			float alpha = FLOAT_803301BC - (static_cast<float>(blendCur) * (FLOAT_803301BC / static_cast<float>(blendMax)));
			Vec targetPos;
			Vec targetScale;
			Quaternion targetQuat;
			Vec positionScaleA;
			Vec positionScaleB;
			Vec blendedPos;
			Mtx quatMtx;
			Mtx scaleMtx;
			targetPos.x = NodeLocalRuntimeMtx(node)[0][3];
			targetPos.y = NodeLocalRuntimeMtx(node)[1][3];
			targetPos.z = NodeLocalRuntimeMtx(node)[2][3];

			Math.MTXGetScale(NodeLocalRuntimeMtx(node), &targetScale);
			if (targetScale.x < FLOAT_803301E4) {
				targetScale.y = FLOAT_803301E8;
				targetScale.z = FLOAT_803301E8;
			} else {
				PSVECScale(&NodePreviousScale(node), &positionScaleA, FLOAT_803301BC - alpha);
				PSVECScale(&targetScale, &positionScaleB, alpha);
				PSVECAdd(&positionScaleA, &positionScaleB, &targetScale);
			}
			Vec positionScaleA2;
			PSVECScale(&NodePreviousPosition(node), &positionScaleA2, FLOAT_803301BC - alpha);
			PSVECScale(&targetPos, &positionScaleB, alpha);
			PSVECAdd(&positionScaleA2, &positionScaleB, &blendedPos);
			C_QUATMtx(&targetQuat, NodeLocalRuntimeMtx(node));
			C_QUATSlerp(&NodePreviousQuat(node), &targetQuat, &targetQuat, alpha);
			PSMTXScale(scaleMtx, targetScale.x, targetScale.y, targetScale.z);
			PSMTXQuat(quatMtx, &targetQuat);
			PSMTXConcat(quatMtx, scaleMtx, NodeLocalRuntimeMtx(node));
			NodeLocalRuntimeMtx(node)[0][3] = blendedPos.x;
			NodeLocalRuntimeMtx(node)[1][3] = blendedPos.y;
			NodeLocalRuntimeMtx(node)[2][3] = blendedPos.z;
		}

		if (parentNode == 0) {
			PSMTXConcat(ModelWorldBaseMtx(this), NodeLocalRuntimeMtx(node), NodeWorldMtx(node));
		} else {
			PSMTXConcat(NodeWorldMtx(parentNode), NodeLocalRuntimeMtx(node), NodeWorldMtx(node));
		}

		if (ref->m_dynParamIndex >= 0) {
			dynamics(node, parentNode);
		}

		if (ref->m_index == ModelHeadIndex(this) && ModelTwistAngle(this) != FLOAT_803301b0) {
			Vec twistAxis = DAT_801D9078;
			Mtx twistRotate;
			Mtx nodeBase;
			Mtx axisBase;
			PSMTXMultVecSR(ModelWorldBaseMtx(this), &twistAxis, &twistAxis);
			PSMTXRotAxisRad(twistRotate, &twistAxis, ModelTwistAngle(this));
			PSMTXCopy(NodeWorldMtx(node), nodeBase);
			PSMTXCopy(twistRotate, axisBase);
			nodeBase[0][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).x;
			nodeBase[1][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).y;
			nodeBase[2][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).z;
			axisBase[0][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).x;
			axisBase[1][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).y;
			axisBase[2][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).z;
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

	this->m_flags10CBits.m_flag10C_80 = 0;
}

#pragma push
#pragma opt_common_subs off
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
		m_anim->InitQuantize();
	}

	PSMTXIdentity(out);

	int reuseAnimNode0Srt = 0;
	SRTView parentScaleSrt;
	while (node != 0) {
		CNode* parentNode = 0;
		CChara::CNode::CRefData* ref = node->m_refData;
		s16 parent = ref->m_parentIndex;
		if (parent < 0) {
			parentNode = 0;
		} else {
			parentNode = reinterpret_cast<CNode*>(reinterpret_cast<u8*>(ModelNodes(this)) + parent * 0xC0);
		}

		int curReuseAnimNode0Srt = reuseAnimNode0Srt;
		reuseAnimNode0Srt = 0;
		SRTView cachedParentScaleSrt = parentScaleSrt;
		SRTView srt;
		Mtx animMtx;
		Mtx localMtx;

		if (NodeAnimNode0(node) != 0 || NodeAnimNode1(node) != 0) {
			if (parentNode != 0 && NodeAnimNode0(parentNode) != 0 &&
			    AnimNodeUsesScale(NodeAnimNode0(parentNode))) {
				NodeAnimNode0(parentNode)->Interp(m_anim, reinterpret_cast<SRT*>(&parentScaleSrt), frame);
				reuseAnimNode0Srt = 1;
				PSMTXScale(localMtx,
				           FLOAT_803301BC / parentScaleSrt.m_scale.x,
				           FLOAT_803301BC / parentScaleSrt.m_scale.y,
				           FLOAT_803301BC / parentScaleSrt.m_scale.z);
			} else {
				if (parentNode != 0 || FLOAT_803301BC == ModelBaseScale(this)) {
					PSMTXIdentity(localMtx);
				} else {
					float baseScale = ModelBaseScale(this);
					PSMTXScale(localMtx, baseScale, baseScale, baseScale);
				}
			}

			if (ref->m_usesParentLenX != 0) {
				localMtx[0][3] = NodeBoneLen(parentNode);
			}

			if (NodeAnimNode1(node) != 0) {
				NodeAnimNode1(node)->Interp(m_anim, reinterpret_cast<SRT*>(&srt), frame);
				if (AnimNodeUsesScale(NodeAnimNode1(node))) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt));
				}
				PSMTXConcat(localMtx, animMtx, localMtx);

				PSMTXScale(animMtx,
				           FLOAT_803301BC / srt.m_scale.x,
				           FLOAT_803301BC / srt.m_scale.y,
				           FLOAT_803301BC / srt.m_scale.z);
				PSMTXConcat(localMtx, animMtx, localMtx);
			}

			if (NodeAnimNode0(node) != 0) {
				if (curReuseAnimNode0Srt) {
					srt = cachedParentScaleSrt;
				} else {
					NodeAnimNode0(node)->Interp(m_anim, reinterpret_cast<SRT*>(&srt), frame);
				}
				if (AnimNodeUsesScale(NodeAnimNode0(node))) {
					Math.SRTToMatrix(animMtx, reinterpret_cast<SRT*>(&srt));
				} else {
					Math.SRTToMatrixRT(animMtx, reinterpret_cast<SRT*>(&srt));
				}
				PSMTXConcat(localMtx, animMtx, localMtx);
			}
		} else {
			PSMTXCopy(ref->m_localMtx, localMtx);
		}

		u16 blendCur = ModelBlendCur(this);
		if (blendCur != 0) {
			u16 blendMax = ModelBlendMax(this);
			float alpha = FLOAT_803301BC - (static_cast<float>(blendCur) * (FLOAT_803301BC / static_cast<float>(blendMax)));
			Vec targetScale;
			Quaternion targetQuat;
			Vec positionScaleA;
			Vec positionScaleB;
			Vec blendedPos;
			Mtx scaleMtx;
			Vec targetPos;
			targetPos.x = localMtx[0][3];
			targetPos.y = localMtx[1][3];
			targetPos.z = localMtx[2][3];

			Math.MTXGetScale(localMtx, &targetScale);
			if (targetScale.x < FLOAT_803301E4) {
				targetScale.y = FLOAT_803301E8;
				targetScale.z = FLOAT_803301E8;
			} else {
				PSVECScale(&NodePreviousScale(node), &positionScaleA, FLOAT_803301BC - alpha);
				PSVECScale(&targetScale, &positionScaleB, alpha);
				PSVECAdd(&positionScaleA, &positionScaleB, &targetScale);
			}
			Vec positionScaleA2;
			PSVECScale(&NodePreviousPosition(node), &positionScaleA2, FLOAT_803301BC - alpha);
			PSVECScale(&targetPos, &positionScaleB, alpha);
			PSVECAdd(&positionScaleA2, &positionScaleB, &blendedPos);
			C_QUATMtx(&targetQuat, localMtx);
			C_QUATSlerp(&NodePreviousQuat(node), &targetQuat, &targetQuat, alpha);
			PSMTXScale(scaleMtx, targetScale.x, targetScale.y, targetScale.z);
			PSMTXQuat(localMtx, &targetQuat);
			PSMTXConcat(localMtx, scaleMtx, localMtx);
			localMtx[0][3] = blendedPos.x;
			localMtx[1][3] = blendedPos.y;
			localMtx[2][3] = blendedPos.z;
		}

		PSMTXConcat(localMtx, out, out);

		node = parentNode;
	}

	PSMTXConcat(reinterpret_cast<float(*)[4]>(reinterpret_cast<u8*>(this) + 0x08), out, out);
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
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
	float* dynParam = reinterpret_cast<float*>(reinterpret_cast<u8*>(ModelDynParams(this)) + NodeDynParamIndex(node) * 0x24);

	Vec forward;
	Vec right;
	Vec up;
	Vec origin;
	Vec target;
	Vec accel;
	Vec predicted;
	Vec direction;
	{
		CVector tmp(NodeWorldMtx(node)[0][0], NodeWorldMtx(node)[1][0], NodeWorldMtx(node)[2][0]);
		forward.x = tmp.x;
		forward.y = tmp.y;
		forward.z = tmp.z;
	}
	{
		CVector tmp(NodeWorldMtx(node)[0][1], NodeWorldMtx(node)[1][1], NodeWorldMtx(node)[2][1]);
		right.x = tmp.x;
		right.y = tmp.y;
		right.z = tmp.z;
	}
	{
		CVector tmp(NodeWorldMtx(node)[0][2], NodeWorldMtx(node)[1][2], NodeWorldMtx(node)[2][2]);
		up.x = tmp.x;
		up.y = tmp.y;
		up.z = tmp.z;
	}
	reinterpret_cast<CVector&>(forward).Normalize();
	{
		CVector tmp(NodeWorldMtx(node)[0][3], NodeWorldMtx(node)[1][3], NodeWorldMtx(node)[2][3]);
		origin.x = tmp.x;
		origin.y = tmp.y;
		origin.z = tmp.z;
	}
	float boneLen = NodeBoneLen(node);

	{
		CVector tmp;
		PSVECScale(&forward, reinterpret_cast<Vec*>(&tmp), boneLen);
		Vec scaled;
		scaled.x = tmp.x;
		scaled.y = tmp.y;
		scaled.z = tmp.z;
		CVector tmp2;
		PSVECAdd(&origin, &scaled, reinterpret_cast<Vec*>(&tmp2));
		target.x = tmp2.x;
		target.y = tmp2.y;
		target.z = tmp2.z;
	}

	if (ModelFlag10C_80(this)) {
		NodeDynPosition(node).x = target.x;
		NodeDynPosition(node).y = target.y;
		NodeDynPosition(node).z = target.z;
		reinterpret_cast<CVector&>(NodeDynVelocity(node)).Identity();
		return;
	}

	float randomScale = FLOAT_803301D0 * Math.RandF() + FLOAT_803301D0;
	Vec windImpulse;
	{
		float windScale = dynParam[2];
		CVector tmp;
		PSVECScale(&ModelDynJitter(this), reinterpret_cast<Vec*>(&tmp), randomScale);
		Vec windForce;
		windForce.x = tmp.x;
		windForce.y = tmp.y;
		windForce.z = tmp.z;
		CVector tmp2;
		PSVECScale(&windForce, reinterpret_cast<Vec*>(&tmp2), windScale);
		windImpulse.x = tmp2.x;
		windImpulse.y = tmp2.y;
		windImpulse.z = tmp2.z;
	}

	{
		CVector tmp;
		PSVECSubtract(&target, &NodeDynPosition(node), reinterpret_cast<Vec*>(&tmp));
		Vec targetDelta;
		targetDelta.x = tmp.x;
		targetDelta.y = tmp.y;
		targetDelta.z = tmp.z;
		CVector tmp2;
		PSVECAdd(&targetDelta, &windImpulse, reinterpret_cast<Vec*>(&tmp2));
		accel.x = tmp2.x;
		accel.y = tmp2.y;
		accel.z = tmp2.z;
	}
	PSVECAdd(&NodeDynVelocity(node), &accel, &NodeDynVelocity(node));

	{
		float velScale = dynParam[0];
		CVector tmp;
		PSVECScale(&NodeDynVelocity(node), reinterpret_cast<Vec*>(&tmp), velScale);
		Vec step;
		step.x = tmp.x;
		step.y = tmp.y;
		step.z = tmp.z;
		CVector tmp2;
		PSVECAdd(&NodeDynPosition(node), &step, reinterpret_cast<Vec*>(&tmp2));
		predicted.x = tmp2.x;
		predicted.y = tmp2.y;
		predicted.z = tmp2.z;
	}
	PSVECScale(&NodeDynVelocity(node), &NodeDynVelocity(node), dynParam[1]);

	{
		CVector tmp;
		PSVECSubtract(&predicted, &origin, reinterpret_cast<Vec*>(&tmp));
		direction.x = tmp.x;
		direction.y = tmp.y;
		direction.z = tmp.z;
	}
	for (int axis = 0; axis < 2; axis++, dynParam++) {
		if (*reinterpret_cast<int*>(&dynParam[3]) != 0) {
			float angle;
			if (axis == 0) {
				float dotForward = PSVECDotProduct(&forward, &direction);
				float dotSide = PSVECDotProduct(&up, &direction);
				angle = -atan2f(dotSide, dotForward);
			} else {
				float dotForward = PSVECDotProduct(&forward, &direction);
				float dotSide = PSVECDotProduct(&right, &direction);
				angle = atan2f(dotSide, dotForward);
			}
			float limit = FLOAT_803301D4 * dynParam[5];
			if (angle <= limit || FLOAT_803301D4 * dynParam[7] <= angle) {
				float rot;
				if (angle <= limit) {
					rot = limit - angle;
				} else {
					rot = FLOAT_803301D4 * dynParam[7] - angle;
				}

				Mtx rotate;
				if (axis == 0) {
					PSMTXRotAxisRad(rotate, &right, rot);
				} else {
					PSMTXRotAxisRad(rotate, &up, rot);
				}
				PSMTXMultVecSR(rotate, &direction, &direction);
			}
		}
	}

	reinterpret_cast<CVector&>(direction).Normalize();
	float align = PSVECDotProduct(&forward, &direction);
	if (!(align > FLOAT_803301D8)) {
		float rotateAngle;
		if (align < FLOAT_803301DC) {
			rotateAngle = FLOAT_803301E0;
		} else {
			rotateAngle = acosf(align);
		}

		CVector axis;
		PSVECCrossProduct(&forward, &direction, reinterpret_cast<Vec*>(&axis));
		Mtx rotate;
		Mtx base;
		Mtx axisBase;
		Mtx combined;
		PSMTXRotAxisRad(rotate, reinterpret_cast<Vec*>(&axis), rotateAngle);
		PSMTXCopy(NodeWorldMtx(node), base);
		PSMTXCopy(rotate, axisBase);
		base[0][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).x;
		base[1][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).y;
		base[2][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).z;
		axisBase[0][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).x;
		axisBase[1][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).y;
		axisBase[2][3] = CVector(FLOAT_803301b0, FLOAT_803301b0, FLOAT_803301b0).z;
		PSMTXConcat(axisBase, base, combined);
		NodeWorldMtx(node)[0][0] = combined[0][0];
		NodeWorldMtx(node)[1][0] = combined[1][0];
		NodeWorldMtx(node)[2][0] = combined[2][0];
		NodeWorldMtx(node)[0][1] = combined[0][1];
		NodeWorldMtx(node)[1][1] = combined[1][1];
		NodeWorldMtx(node)[2][1] = combined[2][1];
		NodeWorldMtx(node)[0][2] = combined[0][2];
		NodeWorldMtx(node)[1][2] = combined[1][2];
		NodeWorldMtx(node)[2][2] = combined[2][2];
	}

	{
		CVector tmp;
		PSVECScale(&direction, reinterpret_cast<Vec*>(&tmp), boneLen);
		Vec dynOffset;
		dynOffset.x = tmp.x;
		dynOffset.y = tmp.y;
		dynOffset.z = tmp.z;
		CVector tmp2;
		PSVECAdd(&origin, &dynOffset, reinterpret_cast<Vec*>(&tmp2));
		float py = tmp2.y;
		float pz = tmp2.z;
		NodeDynPosition(node).x = tmp2.x;
		NodeDynPosition(node).y = py;
		NodeDynPosition(node).z = pz;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 0b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CModel::calcSkin()
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
	CNode* node = ModelNodes(this);
	u32 index = 0;

	while (index < ModelNodeCount(this)) {
		if (strcmp(NodeRefName(node), name) == 0) {
			return (int)index;
		}
		index++;
		node++;
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
			u32 i = 0;
			CNode* node = ModelNodes(this);
			for (; i < ModelNodeCount(this); i++, node++) {
				int tail = strlen(NodeRefName(node)) - 3;
				if (tail > 0 && strcmp(&node->m_refData->m_name[tail], name) == 0) {
					return (int)i;
				}
			}
		} else if (name[1] == 'r' && name[2] == 'o' && name[3] == 'o' && name[4] == 't') {
			CNode* node = ModelNodes(this);
			u32 i = 0;
			for (; i < ModelNodeCount(this); i++, node++) {
				int tail = strlen(NodeRefName(node)) - 5;
				if (tail > 0 && strcmp(&node->m_refData->m_name[tail], name) == 0) {
					return (int)i;
				}
			}
		}
	} else {
		CNode* node = ModelNodes(this);
		u32 i = 0;
		for (; i < ModelNodeCount(this); i++, node++) {
			if (strcmp(NodeRefName(node), name) == 0) {
				goto foundPlain;
			}
		}
		i = (u32)-1;
foundPlain:
		return (int)i;
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
	if (ModelLightAlpha(this) == FLOAT_803301b0) {
		return;
	}

	const int cullFlag = flags & 1;
	const int shadowDisabled = ((flags >> 1) & 1) ^ 1;
	const int materialAlpha = (flags >> 2) & 1;
	const int shadowCullEnabled = (flags >> 3) & 1;
	const int skipShadowPosition = ((flags >> 4) & 1) ^ 1;
	BeforeDrawModelCallback beforeDrawModel = ModelBeforeDrawCallback(this);
	if (beforeDrawModel != 0 && pass == 0) {
		beforeDrawModel(this, m_callbackContext, m_callbackParam, view, cullFlag);
	}

	ModelMaterialSet(this)->SetTextureSet(m_texSet);
	CTexAnimSet* texAnimSet = ModelTexAnimSet(this);
	if (texAnimSet != 0) {
		texAnimSet->SetTexGen();
	}

	const int posQuant = ModelPosQuant(this);
	const int normQuant = ModelNormQuant(this);
	MaterialMan.InitVtxFmt(-1, (_GXCompType)3, posQuant, (_GXCompType)3, normQuant, (_GXCompType)3, 0xC);
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode((u8)1, (GXCompare)3, (u8)1);
	int cullMode = 1;
	if (cullFlag != 0) {
		cullMode = 2;
	}
	GXSetCullMode(static_cast<GXCullMode>(cullMode));
	LightPcs.SetAmbientAlpha(ModelLightAlpha(this));

	CCharaMeshRaw* mesh = ModelMeshes(this);
	int lastLightEnable = 0;
	int lastZWrite = 0;

	for (u32 meshIndex = 0; meshIndex < ModelMeshCount(this); meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (static_cast<int>(meshIndex) < 0x20 && ((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		InitCharaMaterialState();

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		} else {
			PSMTXConcat(ModelDrawMtx(this), ModelNodes(this)[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		if (((cullFlag == 0) && shadowDisabled) || ((cullFlag != 0) && (shadowCullEnabled != 0))) {
			CameraPcs.SetFullScreenShadow(meshMtx, 0);
		}

		if (skipShadowPosition) {
			Vec position;
			position.x = ModelDrawMtx(this)[0][3];
			position.y = ModelDrawMtx(this)[1][3];
			position.z = ModelDrawMtx(this)[2][3];
			MaterialMan.SetPosition(static_cast<CMapShadow::TARGET>(0), &position, FLOAT_803301C8, FLOAT_803301CC, meshMtx,
			                        static_cast<int>(static_cast<u32>(ModelFlagsA0(this) & 0xC0) << 24) >> 31);
		}

		const int lightEnable = static_cast<int>(static_cast<u32>(mesh->m_data->m_flags & 0xC0) << 24) >> 31;
		if (lastLightEnable != lightEnable) {
			lastLightEnable = lightEnable;
			LightPcs.EnableLight(lightEnable == 0, 0);
		}

		const int zWriteEnable = static_cast<int>(static_cast<u32>(mesh->m_data->m_flags & 0x60) << 25) >> 31;
		if (lastZWrite != zWriteEnable) {
			lastZWrite = zWriteEnable;
			int zOff = zWriteEnable == 0;
			GXSetZMode((u8)1, (GXCompare)3, (GXBool)zOff);
		}

		if (ModelBeforeMeshCallback(this) != 0) {
			ModelBeforeMeshCallback(this)(this, m_callbackContext, m_callbackParam, meshIndex);
		}

		CopyCharaMaterialEnv();
		if (mesh->m_data->m_infoWord1 != 0) {
			LightPcs.SetBumpTexMatirx(meshMtx, gCharaPartWorkPtr, 0, 0);
		}
		MaterialMan.SetObjMatrix(view, meshMtx);
		GXSetArray((GXAttr)9, mesh->m_workPositions, 6);
		SetMaterialManNormalArray(mesh->m_workNormals);
		GXSetArray((GXAttr)0xB, mesh->m_data->m_colors, 4);
		GXSetArray((GXAttr)0xD, mesh->m_data->m_uvs, 4);
		GXSetArray((GXAttr)0xE, mesh->m_data->m_uvs, 4);

		CCharaDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (int displayListIndex = static_cast<int>(mesh->m_data->m_displayListCount) - 1; displayListIndex >= 0; displayListIndex--, displayList++) {
			if (ModelAfterMeshDrawCallback(this) != 0) {
				ModelAfterMeshDrawCallback(this)(this, m_callbackContext, m_callbackParam, meshIndex, static_cast<unsigned int>(displayListIndex), meshMtx);
			} else {
				MaterialMan.SetMaterial(ModelMaterialSet(this), displayList->m_material, materialAlpha, (_GXTevScale)0);
				GXCallDisplayList(displayList->m_data, displayList->m_size);
			}
		}

		if (ModelAfterMeshEnvCallback(this) != 0) {
			ModelAfterMeshEnvCallback(this)(this, m_callbackContext, m_callbackParam, meshIndex, meshMtx);
		}
	}

	AfterDrawModelCallback afterDrawModel = ModelAfterDrawCallback(this);
	if (afterDrawModel != 0) {
		afterDrawModel(this, m_callbackContext, m_callbackParam);
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
	if (FLOAT_803301BC != ModelLightAlpha(this)) {
		return;
	}

	ModelMaterialSet(this)->SetTextureSet(m_texSet);
	LightPcs.SetAmbientAlpha(FLOAT_803301BC);
	MaterialMan.InitVtxFmt(-1, (_GXCompType)3, ModelPosQuant(this), (_GXCompType)3, ModelNormQuant(this), (_GXCompType)3, 0xC);
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode((u8)zMode, (GXCompare)3, (u8)zMode);
	GXSetCullMode((GXCullMode)1);

	CCharaMeshRaw* mesh = ModelMeshes(this);

	for (u32 meshIndex = 0; meshIndex < this->m_data->m_meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0 || ((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		InitCharaMaterialState();

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		} else {
			PSMTXConcat(ModelDrawMtx(this), ModelNodes(this)[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		if (ModelCustomMeshDrawCallback(this) != 0) {
			ModelCustomMeshDrawCallback(this)(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex);
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
			if (ModelShadowDisplayListCallback(this) != 0) {
				ModelShadowDisplayListCallback(this)(this, ModelCalcCbUser0(this), ModelCalcCbUser1(this), meshIndex, static_cast<unsigned int>(displayListIndex), meshMtx);
			} else {
				MaterialMan.SetMaterial(ModelMaterialSet(this), displayList->m_material, 1, (_GXTevScale)0);
				GXCallDisplayList(displayList->m_data, displayList->m_size);
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
	u16* blendCur = &m_blendCur;
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
	s8 safeNodeFlag = static_cast<s32>((static_cast<u32>(flags) << 26) & 0xC0000000) >> 31;
	if (safeNodeFlag != 0) {
		PSMTXCopy(node->m_mtx, outMtx);
		outMtx[0][3] += *(float*)((u8*)this + 0x74);
		outMtx[1][3] += *(float*)((u8*)this + 0x84);
		outMtx[2][3] += *(float*)((u8*)this + 0x94);
	} else {
		PSMTXCopy((float(*)[4])((u8*)this + 0x08), outMtx);
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
	if (blendMode == -1) {
		CAnim* currentAnim = m_anim;
		u8 interpCount;
		int resolvedBlend;
		if (currentAnim != 0 && (interpCount = AnimInterpCount(currentAnim)) != 0 && AnimBank(currentAnim) != 0) {
			resolvedBlend = 4;

			u16* interpTable = reinterpret_cast<u16*>(reinterpret_cast<u8*>(AnimBank(currentAnim)) + AnimInterpOffset(currentAnim));
			int frame = static_cast<int>(m_curFrame);

			for (int i = 0; i < static_cast<int>(interpCount); i++) {
				int start = (i == 0) ? 0 : interpTable[i * 2];
				int end = (i + 1 < static_cast<int>(interpCount)) ? interpTable[i * 2 + 2] : 10000000;
				if (start <= frame && frame < end) {
					resolvedBlend = interpTable[i * 2 + 1];
					break;
				}
			}
		} else if (currentAnim != 0) {
			resolvedBlend = 4;
		} else {
			resolvedBlend = 0;
		}
		blendMode = resolvedBlend;
	}

	if (anim != m_anim) {
		ReleaseRefCounted(m_anim);
		m_anim = 0;
		m_anim = anim;
		RetainRefCounted(m_anim);
	}

	CNode* nodes = ModelNodes(this);
	for (u32 i = 0; i < ModelNodeCount(this); i++) {
		CNode* node = reinterpret_cast<CNode*>(reinterpret_cast<u8*>(nodes) + i * 0xC0);

		NodeAnimNode0(node) = 0;
		NodeAnimNode1(node) = 0;

		C_QUATMtx(&NodePreviousQuat(node), NodeLocalRuntimeMtx(node));
		NodePreviousPosition(node).x = NodeLocalRuntimeMtx(node)[0][3];
		NodePreviousPosition(node).y = NodeLocalRuntimeMtx(node)[1][3];
		NodePreviousPosition(node).z = NodeLocalRuntimeMtx(node)[2][3];
		Math.MTXGetScale(NodeLocalRuntimeMtx(node), &NodePreviousScale(node));

		if (m_anim == 0) {
			continue;
		}

		for (u32 animIndex = 0; animIndex < AnimNodeCount(m_anim); animIndex++) {
			CAnimNode* animNode = &AnimNodes(m_anim)[animIndex];
			char* animName = AnimNodeName(animNode);

			for (unsigned int slot = 0; slot < 2; slot++) {
				char* name = node->m_refData->m_name + slot * 0x10;
				if (name[0] != '\0' && strcmp(animName, name) == 0) {
					(&NodeAnimNode0(node))[slot] = animNode;
					break;
				}
			}
		}
	}

	if (m_anim != 0) {
		if (ModelAttachMode(this) == 0) {
			int flagBit = (AnimFlags(m_anim) >> 7) & 1;
			int flagMask = ((-flagBit) | flagBit) >> 31;
			m_blendCur = static_cast<u16>(blendMode & flagMask);
		} else if (ModelAttachMode(this) == 1) {
			m_blendCur = static_cast<u16>(blendMode);
		} else {
			m_blendCur = 0;
		}
		m_blendMax = m_blendCur;

		int frameStart = (startFrame == -1) ? 0 : startFrame;

		m_animStart = static_cast<float>(frameStart);
		float startF = m_animStart;
		m_curFrame = startF;
		m_time = startF;

		int frameEnd;
		if (endFrame == -1) {
			frameEnd = static_cast<int>(AnimFrameCount(m_anim)) - 1;
		} else {
			frameEnd = endFrame;
		}

		m_animEnd = static_cast<float>(frameEnd);
	} else {
		m_curFrame = 0.0f;
		m_time = 0.0f;
		m_animEnd = 0.0f;
		m_animStart = 0.0f;
	}
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
			if (oldTexSet->DecRef() == 0) {
				delete oldTexSet;
			}
			m_texSet = 0;
		}
		m_texSet = texSet;
		if (m_texSet != 0) {
			m_texSet->AddRef();
		}
	}
	if (m_data->m_materialSet != 0) {
		m_data->m_materialSet->SetTextureSet(m_texSet);
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
	m_time += frame;
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
	m_time = frame;
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
	float delta = m_furTarget - m_furCur;
	float step;
	if (delta < FLOAT_803301B4) {
		step = FLOAT_803301B4;
	} else if (FLOAT_803301B8 < delta) {
		step = FLOAT_803301B8;
	} else {
		step = delta;
	}
	m_furCur += step;
	float furColor;
	if (m_furCur < 0.0f) {
		furColor = 0.0f;
	} else if (1.0f < m_furCur) {
		furColor = 1.0f;
	} else {
		furColor = m_furCur;
	}
	m_furCur = furColor;
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
	struct Flags {
		u8 active : 1;
		u8 _pad : 7;
	};
	int active = 1;

	m_refData = 0;
	m_displayMesh = 0;
	m_animNode0 = 0;
	m_animNode1 = 0;
	reinterpret_cast<Flags*>(&m_flags)->active = active;
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
	m_refData = reinterpret_cast<CChara::CNode::CRefData*>(
	    reinterpret_cast<u8*>(model->m_data->m_nodeRefData) + model->m_data->m_nodeCount * 0x94);
	m_refData->m_index = static_cast<u16>(model->m_data->m_nodeCount);
	m_refData->m_type = static_cast<u8>(type);
	m_refData->m_dynParamIndex = -1;
	m_refData->m_bindFlags = 0;

	CChunkFile::CChunk chunkInfo;
	chunk.PushChunk();
	while (chunk.GetNextChunk(chunkInfo)) {
		if (chunkInfo.m_id == 0x494E464F) {
			m_refData->m_parentIndex = static_cast<s16>(chunk.Get4());
			m_refData->m_childCount = static_cast<u8>(chunk.Get4());
			m_refData->m_childBankOffset = static_cast<s16>(chunk.Get4());
			m_refData->m_usesParentLenX = static_cast<u8>(chunk.Get4());
		} else if (chunkInfo.m_id == 0x42494E46) {
			m_refData->m_bindFlags = static_cast<u8>(chunk.Get4());
			m_refData->m_boneLen = chunk.GetF4();
		} else if (chunkInfo.m_id == 0x4E414D45) {
			strcpy(m_refData->m_name, chunk.GetString());
		} else if (chunkInfo.m_id == 0x4E414D32) {
			strcpy(m_refData->m_altName, chunk.GetString());
		} else if (chunkInfo.m_id == 0x5446524D) {
			chunk.Get(m_refData->m_localMtx, 0x30);
			if (m_refData->m_parentIndex == -1) {
				float baseScale = model->m_data->m_baseScale;
				PSMTXScaleApply(m_refData->m_localMtx, m_refData->m_localMtx, baseScale, baseScale, baseScale);
			}
		} else if (chunkInfo.m_id == 0x4D494458) {
			m_refData->m_displayIndex = static_cast<s8>(chunk.Get4());
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

	for (u32 i = 0; i < NodeChildCount(this); i++) {
		CNode* child = GetBindChildNode(model, this, i);
		CalcOneBindNode(child, model);

		for (u32 j = 0; j < NodeChildCount(child); j++) {
			CNode* grandChild = GetBindChildNode(model, child, j);
			CalcOneBindNode(grandChild, model);

			for (u32 k = 0; k < NodeChildCount(grandChild); k++) {
				CNode* greatGrandChild = GetBindChildNode(model, grandChild, k);
				CalcOneBindNode(greatGrandChild, model);

				for (u32 l = 0; l < NodeChildCount(greatGrandChild); l++) {
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
	u8* raw = reinterpret_cast<u8*>(this);
	s8* signedRaw = reinterpret_cast<s8*>(this);
	s32 invalidIndex = -1;

	signedRaw[0x8D] = invalidIndex;
	raw[0x8E] = 0;
	raw[0x8A] = 0;
	memset(raw + 0x6A, 0, 0x20);
	*reinterpret_cast<float*>(raw + 0x60) = FLOAT_803301b0;
	signedRaw[0x90] = invalidIndex;
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
	m_data = 0;
	m_workPositions = 0;
	m_workNormals = 0;
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
	CCharaMeshRefRaw* meshRef = reinterpret_cast<CCharaMeshRefRaw*>(
	    reinterpret_cast<u8*>(model->m_data->m_meshRefData) + model->m_data->m_meshCount * 0x64);
	m_data = meshRef;

	CChunkFile::CChunk chunkInfo;
	chunk.PushChunk();
	while (chunk.GetNextChunk(chunkInfo)) {
		switch (chunkInfo.m_id) {
		case 0x4D4E414D:
			strcpy(m_data->m_name, chunk.GetString());
			break;
		case 0x494E464F:
			m_data->m_nodeIndex = chunk.Get4();
			m_data->m_infoWord1 = chunk.Get4();
			m_data->m_flagsBits.m_flag_80 = static_cast<s8>(chunk.Get4());
			m_data->m_flagsBits.m_flag_40 = static_cast<s8>(chunk.Get4());
			chunk.Get4();
			chunk.Get4();
			chunk.Get4();
			chunk.Get4();
			break;
		case 0x56455254: {
			m_data->m_vertexCount = chunkInfo.m_size / 6;
			S16Vec* verts = static_cast<S16Vec*>(
			    Memory._Alloc(chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp), 0x7D6, 0));
			m_data->m_vertices = verts;
			memcpy(m_data->m_vertices, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_vertices, m_data->m_vertexCount * 6);
			break;
		}
		case 0x4E4F524D: {
			m_data->m_normalCount = chunkInfo.m_size / 6;
			S16Vec* normals = static_cast<S16Vec*>(
			    Memory._Alloc(chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp), 0x7DE, 0));
			m_data->m_normals = normals;
			memcpy(m_data->m_normals, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_normals, m_data->m_normalCount * 6);
			break;
		}
		case 0x434F4C52: {
			m_data->m_colorCount = chunkInfo.m_size >> 2;
			u8* colors = static_cast<u8*>(
			    Memory._Alloc(chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp), 0x7E6, 0));
			m_data->m_colors = colors;
			memcpy(m_data->m_colors, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_colors, m_data->m_colorCount << 2);
			break;
		}
		case 0x55562020: {
			m_data->m_uvCount = chunkInfo.m_size >> 2;
			u8* uvs = static_cast<u8*>(
			    Memory._Alloc(chunkInfo.m_size, stage, const_cast<char*>(s_chara_cpp), 0x7EE, 0));
			m_data->m_uvs = uvs;
			memcpy(m_data->m_uvs, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_uvs, m_data->m_uvCount << 2);
			break;
		}
		case 0x534B494E: {
			m_data->m_skinCount = chunkInfo.m_arg0;
			m_data->m_skins =
			    new (stage, const_cast<char*>(s_chara_cpp), 0x7F8) CChara::CSkin[m_data->m_skinCount];

			chunk.PushChunk();
			unsigned int skinOffset = 0;
			while (chunk.GetNextChunk(chunkInfo)) {
				if (chunkInfo.m_id == 0x4E4F4445) {
					u8* skinEntry = reinterpret_cast<u8*>(m_data->m_skins) + skinOffset;
					skinOffset += 0x64;
					*reinterpret_cast<u32*>(skinEntry + 0x60) = chunk.Get4();
				} else if (chunkInfo.m_id == 0x4F4E4520) {
					m_data->m_oneWeightCountOrSize = chunkInfo.m_size;
					m_data->m_oneWeightData =
					    Memory._Alloc(m_data->m_oneWeightCountOrSize, stage, const_cast<char*>(s_chara_cpp), 0x808, 0);
					memcpy(m_data->m_oneWeightData, chunk.GetAddress(), chunkInfo.m_size);
				} else if (chunkInfo.m_id == 0x54574F20) {
					m_data->m_twoWeightCountOrSize = chunkInfo.m_size;
					m_data->m_twoWeightData =
					    Memory._Alloc(m_data->m_twoWeightCountOrSize, stage, const_cast<char*>(s_chara_cpp), 0x80E, 0);
					memcpy(m_data->m_twoWeightData, chunk.GetAddress(), chunkInfo.m_size);
				} else if (chunkInfo.m_id == 0x524D494E) {
					m_data->m_threeWeightCountOrSize = chunkInfo.m_size;
					m_data->m_threeWeightData =
					    Memory._Alloc(m_data->m_threeWeightCountOrSize, stage, const_cast<char*>(s_chara_cpp), 0x814, 0);
					memcpy(m_data->m_threeWeightData, chunk.GetAddress(), chunkInfo.m_size);
				}
			}
			chunk.PopChunk();
			break;
		}
		case 0x444C4844: {
			m_data->m_displayListCount = chunkInfo.m_arg0 & 0xFFFF;
			m_data->m_displayLists = reinterpret_cast<CCharaDisplayListRaw*>(
			    new (stage, const_cast<char*>(s_chara_cpp), 0x820) CChara::CMesh::CDisplayList[m_data->m_displayListCount]);

			CCharaDisplayListRaw* displayList = m_data->m_displayLists;
			chunk.PushChunk();
			while (chunk.GetNextChunk(chunkInfo)) {
				if (chunkInfo.m_id != 0x444C5354) {
					continue;
				}

				displayList->m_material = chunk.Get2();
				displayList->m_size = static_cast<s32>(chunkInfo.m_arg0);
				chunk.Align(0x20);
				if (static_cast<u32>(displayList->m_size) != 0) {
					const unsigned int allocSize = (displayList->m_size + 0x1F) & ~0x1FU;
					displayList->m_data =
					    Memory._Alloc(allocSize, stage, const_cast<char*>(s_chara_cpp), 0x830, 0);
					chunk.Get(displayList->m_data, displayList->m_size);
					DCFlushRange(displayList->m_data, displayList->m_size);
				}
				chunk.Align(0x20);
				displayList++;
			}
			chunk.PopChunk();
			break;
		}
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

#pragma push
#pragma scheduling off
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
	u8 framePad[0x20];
	asm {
		lwz r0, framePad
		mr. r3, r4
		stw r4, 0x8(r1)
		stw r5, 0xc(r1)
		stw r6, 0x10(r1)
		stw r7, 0x14(r1)
		stw r8, 0x18(r1)
		stw r9, 0x1c(r1)
		stw r10, 0x20(r1)
		beq _chk2
		mr r4, r7
		mr r5, r8
		lwz r6, 0x158(r1)
		lwz r7, 0x15c(r1)
		lwz r8, 0x160(r1)
		lwz r9, 0x164(r1)
	_loop1:
		lhz r10, 0x0(r5)
		lhz r11, 0x2(r5)
		mulli r10, r10, 0x64
		mulli r11, r11, 0x6
		add r10, r10, r4
		add r12, r11, r6
		add r11, r11, r7
		psq_l f0, 0x0(r12), 0, 5
		psq_l f1, 0x4(r12), 1, 5
		psq_l f2, 0x0(r10), 0, 0
		psq_l f4, 0x10(r10), 0, 0
		psq_l f6, 0x20(r10), 0, 0
		ps_mul f10, f2, f0
		psq_l f3, 0x8(r10), 0, 0
		ps_mul f11, f4, f0
		psq_l f5, 0x18(r10), 0, 0
		ps_mul f12, f6, f0
		ps_madd f10, f3, f1, f10
		psq_l f7, 0x28(r10), 0, 0
		ps_madd f11, f5, f1, f11
		ps_madd f12, f7, f1, f12
		ps_sum0 f10, f10, f10, f10
		ps_sum0 f11, f11, f11, f11
		ps_sum0 f12, f12, f12, f12
		psq_st f10, 0x0(r11), 1, 5
		psq_st f11, 0x2(r11), 1, 5
		psq_st f12, 0x4(r11), 1, 5
		lhz r10, 0x4(r5)
	_loop1i:
		lhz r11, 0x6(r5)
		mulli r11, r11, 0x6
		add r12, r11, r8
		add r11, r11, r9
		psq_l f0, 0x0(r12), 0, 6
		psq_l f1, 0x4(r12), 1, 6
		ps_mul f10, f2, f0
		ps_mul f11, f4, f0
		ps_mul f12, f6, f0
		ps_sum0 f10, f10, f10, f10
		ps_sum0 f11, f11, f11, f11
		ps_sum0 f12, f12, f12, f12
		ps_madd f10, f3, f1, f10
		ps_madd f11, f5, f1, f11
		ps_madd f12, f7, f1, f12
		psq_st f10, 0x0(r11), 1, 6
		psq_st f11, 0x2(r11), 1, 6
		psq_st f12, 0x4(r11), 1, 6
		subic. r10, r10, 0x1
		addi r5, r5, 0x2
		subi r3, r3, 0x2
		bne _loop1i
		subic. r3, r3, 0x6
		addi r5, r5, 0x6
		bne _loop1
	_chk2:
		lwz r3, 0xc(r1)
		cmpwi r3, 0x0
		beq _chk3
		lwz r5, 0x1c(r1)
	_loop2:
		lhz r10, 0x0(r5)
		mulli r10, r10, 0x64
		add r10, r10, r4
		psq_l f13, 0x4(r5), 1, 7
		psq_l f14, 0x6(r5), 1, 7
		lhz r11, 0x8(r5)
		mulli r11, r11, 0x6
		add r12, r11, r6
		add r11, r11, r7
		psq_l f0, 0x0(r12), 0, 5
		psq_l f1, 0x4(r12), 1, 5
		psq_l f2, 0x0(r10), 0, 0
		psq_l f4, 0x10(r10), 0, 0
		psq_l f6, 0x20(r10), 0, 0
		ps_mul f10, f2, f0
		psq_l f3, 0x8(r10), 0, 0
		ps_mul f11, f4, f0
		psq_l f5, 0x18(r10), 0, 0
		ps_mul f12, f6, f0
		psq_l f7, 0x28(r10), 0, 0
		lhz r10, 0x2(r5)
		ps_madd f10, f3, f1, f10
		ps_madd f11, f5, f1, f11
		mulli r10, r10, 0x64
		ps_madd f12, f7, f1, f12
		ps_sum0 f10, f10, f10, f10
		ps_sum0 f11, f11, f11, f11
		add r10, r10, r4
		ps_sum0 f12, f12, f12, f12
		psq_l f15, 0x0(r10), 0, 0
		ps_mul f10, f10, f13
		psq_l f17, 0x10(r10), 0, 0
		psq_l f19, 0x20(r10), 0, 0
		ps_mul f21, f15, f0
		psq_l f16, 0x8(r10), 0, 0
		ps_mul f22, f17, f0
		psq_l f18, 0x18(r10), 0, 0
		ps_mul f23, f19, f0
		ps_madd f21, f16, f1, f21
		psq_l f20, 0x28(r10), 0, 0
		ps_madd f22, f18, f1, f22
		ps_mul f11, f11, f13
		ps_madd f23, f20, f1, f23
		ps_sum0 f21, f21, f21, f21
		ps_sum0 f22, f22, f22, f22
		ps_sum0 f23, f23, f23, f23
		ps_mul f12, f12, f13
		ps_madd f10, f21, f14, f10
		ps_madd f11, f22, f14, f11
		ps_madd f12, f23, f14, f12
		psq_st f10, 0x0(r11), 1, 5
		psq_st f11, 0x2(r11), 1, 5
		psq_st f12, 0x4(r11), 1, 5
		lhz r10, 0xa(r5)
	_loop2i:
		lhz r11, 0xc(r5)
		mulli r11, r11, 0x6
		add r12, r11, r8
		add r11, r11, r9
		psq_l f0, 0x0(r12), 0, 6
		psq_l f1, 0x4(r12), 1, 6
		ps_mul f10, f2, f0
		ps_mul f11, f4, f0
		ps_mul f12, f6, f0
		ps_sum0 f10, f10, f10, f10
		ps_mul f21, f15, f0
		ps_sum0 f11, f11, f11, f11
		ps_mul f22, f17, f0
		ps_sum0 f12, f12, f12, f12
		ps_madd f10, f3, f1, f10
		ps_mul f23, f19, f0
		ps_sum0 f21, f21, f21, f21
		ps_madd f11, f5, f1, f11
		ps_sum0 f22, f22, f22, f22
		ps_madd f12, f7, f1, f12
		ps_sum0 f23, f23, f23, f23
		ps_madd f21, f16, f1, f21
		ps_mul f10, f10, f13
		ps_madd f22, f18, f1, f22
		ps_mul f11, f11, f13
		ps_madd f23, f20, f1, f23
		ps_mul f12, f12, f13
		ps_madd f10, f21, f14, f10
		ps_madd f11, f22, f14, f11
		ps_madd f12, f23, f14, f12
		psq_st f10, 0x0(r11), 1, 6
		psq_st f11, 0x2(r11), 1, 6
		psq_st f12, 0x4(r11), 1, 6
		subic. r10, r10, 0x1
		addi r5, r5, 0x2
		subi r3, r3, 0x2
		bne _loop2i
		subic. r3, r3, 0xc
		addi r5, r5, 0xc
		bne _loop2
	_chk3:
		lwz r3, 0x10(r1)
		cmpwi r3, 0x0
		beq _end
		lwz r5, 0x20(r1)
	_loop3:
		lhz r10, 0x0(r5)
		mulli r10, r10, 0x64
		add r10, r10, r4
		psq_l f13, 0x2(r5), 1, 7
		lhz r11, 0x4(r5)
		mulli r11, r11, 0x6
		add r12, r11, r6
		add r11, r11, r7
		psq_l f0, 0x0(r12), 0, 5
		psq_l f1, 0x4(r12), 1, 5
		psq_l f2, 0x0(r10), 0, 0
		psq_l f4, 0x10(r10), 0, 0
		psq_l f6, 0x20(r10), 0, 0
		ps_mul f10, f2, f0
		psq_l f3, 0x8(r10), 0, 0
		ps_mul f11, f4, f0
		psq_l f5, 0x18(r10), 0, 0
		ps_mul f12, f6, f0
		ps_madd f10, f3, f1, f10
		psq_l f7, 0x28(r10), 0, 0
		ps_madd f11, f5, f1, f11
		psq_l f14, 0x0(r11), 1, 5
		ps_madd f12, f7, f1, f12
		psq_l f15, 0x2(r11), 1, 5
		ps_sum0 f10, f10, f10, f10
		psq_l f16, 0x4(r11), 1, 5
		ps_sum0 f11, f11, f11, f11
		ps_sum0 f12, f12, f12, f12
		ps_madd f10, f10, f13, f14
		ps_madd f11, f11, f13, f15
		ps_madd f12, f12, f13, f16
		psq_st f10, 0x0(r11), 1, 5
		psq_st f11, 0x2(r11), 1, 5
		psq_st f12, 0x4(r11), 1, 5
		lhz r10, 0x6(r5)
	_loop3i:
		lhz r11, 0x8(r5)
		mulli r11, r11, 0x6
		add r12, r11, r8
		add r11, r11, r9
		psq_l f0, 0x0(r12), 0, 6
		psq_l f1, 0x4(r12), 1, 6
		psq_l f14, 0x0(r11), 1, 6
		psq_l f15, 0x2(r11), 1, 6
		psq_l f16, 0x4(r11), 1, 6
		ps_mul f10, f2, f0
		ps_mul f11, f4, f0
		ps_mul f12, f6, f0
		ps_sum0 f10, f10, f10, f10
		ps_sum0 f11, f11, f11, f11
		ps_sum0 f12, f12, f12, f12
		ps_madd f10, f3, f1, f10
		ps_madd f11, f5, f1, f11
		ps_madd f12, f7, f1, f12
		ps_madd f10, f10, f13, f14
		ps_madd f11, f11, f13, f15
		ps_madd f12, f12, f13, f16
		psq_st f10, 0x0(r11), 1, 6
		psq_st f11, 0x2(r11), 1, 6
		psq_st f12, 0x4(r11), 1, 6
		subic. r10, r10, 0x1
		addi r5, r5, 0x2
		subi r3, r3, 0x2
		bne _loop3i
		subic. r3, r3, 0x8
		addi r5, r5, 0x8
		bne _loop3
	_end:
	}
}
#pragma pop

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
		mesh->m_workNormals = mesh->m_data->m_normals;
		return;
	}

	int bufferIndex = CharaDrawBufferIndex();
	CChara::CDrawBuffer& drawBuffer = Chara.GetDrawBuffer(bufferIndex);
	u32& cursor = drawBuffer.m_cursor;
	u32 needed = (meshRef->m_vertexCount + meshRef->m_normalCount) * 6 + 0x40;
	if (0x58000u - cursor < needed) {
		mesh->m_workPositions = 0;
		mesh->m_workNormals = 0;

		if (!s_charaMeshWorkOverflowSeen) {
			s_charaMeshWorkWarnArmed = 1;
			s_charaMeshWorkOverflowSeen = 1;
		}

		if ((s_charaMeshWorkWarnArmed != 0) && (s_charaMeshWorkWarnArmed = 0, 2 <= static_cast<u32>(System.m_execParam))) {
			System.Printf(const_cast<char*>(s_charaMeshWorkOverflow));
		}
		return;
	}

	mesh->m_workPositions = reinterpret_cast<S16Vec*>(drawBuffer.m_base + cursor);
	cursor += AlignCharaWorkBytes(mesh->m_data->m_vertexCount * 6);
	mesh->m_workNormals = reinterpret_cast<S16Vec*>(drawBuffer.m_base + cursor);
	cursor += AlignCharaWorkBytes(mesh->m_data->m_normalCount * 6);

	float* skinData = reinterpret_cast<float*>(mesh->m_data->m_skins);
	for (u32 i = 0; i < mesh->m_data->m_skinCount; i++, skinData += 0x19) {
		int nodeIndex = reinterpret_cast<int*>(skinData + 0x18)[0];
		PSMTXConcat(
		    ModelNodes(model)[nodeIndex].m_mtx,
		    reinterpret_cast<float(*)[4]>(skinData + 0x0C),
		    reinterpret_cast<float(*)[4]>(skinData));
	}

	if (mesh->m_data->m_infoWord1 != 0) {
		S16Vec* srcNormals = mesh->m_data->m_normals;
		S16Vec* dstNormals = mesh->m_workNormals;
		for (u32 i = 0; i < mesh->m_data->m_infoWord1; i++) {
			dstNormals[1] = srcNormals[1];
			dstNormals[2] = srcNormals[2];
			srcNormals += 3;
			dstNormals += 3;
		}
	}

	meshRef = mesh->m_data;
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

	DCFlushRange(mesh->m_workPositions, mesh->m_data->m_vertexCount * 6);
	DCFlushRange(mesh->m_workNormals, mesh->m_data->m_normalCount * 6);
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
	CCharaMeshRefRaw* ref = reinterpret_cast<CCharaMeshRefRaw*>(this);

	ref->m_vertices = 0;
	ref->m_normals = 0;
	ref->m_colors = 0;
	ref->m_uvs = 0;
	ref->m_oneWeightData = 0;
	ref->m_twoWeightData = 0;
	ref->m_threeWeightData = 0;
	ref->m_displayLists = 0;
	ref->m_skins = 0;
	ref->m_vertexCount = 0;
	ref->m_normalCount = 0;
	ref->m_colorCount = 0;
	ref->m_uvCount = 0;
	ref->m_oneWeightCountOrSize = 0;
	ref->m_twoWeightCountOrSize = 0;
	ref->m_threeWeightCountOrSize = 0;
	ref->m_displayListCount = 0;
	ref->m_skinCount = 0;
	ref->m_infoWord1 = 0;
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
	CCharaMeshRefRaw* ref = reinterpret_cast<CCharaMeshRefRaw*>(this);

	if (ref->m_vertices != 0) {
		operator delete[](ref->m_vertices);
		ref->m_vertices = 0;
	}
	if (ref->m_normals != 0) {
		operator delete[](ref->m_normals);
		ref->m_normals = 0;
	}
	if (ref->m_colors != 0) {
		operator delete[](ref->m_colors);
		ref->m_colors = 0;
	}
	if (ref->m_uvs != 0) {
		operator delete[](ref->m_uvs);
		ref->m_uvs = 0;
	}
	if (ref->m_oneWeightData != 0) {
		operator delete[](ref->m_oneWeightData);
		ref->m_oneWeightData = 0;
	}
	if (ref->m_twoWeightData != 0) {
		operator delete[](ref->m_twoWeightData);
		ref->m_twoWeightData = 0;
	}
	if (ref->m_threeWeightData != 0) {
		operator delete[](ref->m_threeWeightData);
		ref->m_threeWeightData = 0;
	}
	if (ref->m_displayLists != 0) {
		delete[] ref->m_displayLists;
		ref->m_displayLists = 0;
	}
	if (ref->m_skins != 0) {
		delete[] ref->m_skins;
		ref->m_skins = 0;
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
	m_size = 0;
	m_data = 0;
	m_material = 0xFFFF;
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
	if (m_data != 0) {
		operator delete[](m_data);
		m_data = 0;
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
	*reinterpret_cast<u8*>(&m_flags) |= 0x80;
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
		PSMTXCopy(node->m_mtx, outMtx);
	} else {
		PSMTXIdentity(outMtx);
	}
}

CChara Chara;
