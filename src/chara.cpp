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

#if defined(VERSION_GCCJGC)
#define CHARA_LINE(line, usLine, jpLine) (jpLine)
#elif defined(VERSION_GCCE01)
#define CHARA_LINE(line, usLine, jpLine) (usLine)
#else
#define CHARA_LINE(line, usLine, jpLine) (line)
#endif

inline int CSystem::GetErrorLevel()
{
	return m_execParam;
}

namespace {

typedef CChara::CMesh::CDisplayList CCharaDisplayListRaw;

typedef CChara::CMesh::CRefData CCharaMeshRefRaw;
typedef CChara::CMesh CCharaMeshRaw;

STATIC_ASSERT(sizeof(_GXColor) == 4);
STATIC_ASSERT(sizeof(S16Vec2d) == 4);
STATIC_ASSERT(offsetof(CChara::CMesh::CRefData, m_colors) == 0x28);
STATIC_ASSERT(offsetof(CChara::CMesh::CRefData, m_uvs) == 0x30);
STATIC_ASSERT(sizeof(CChara::CSkin) == 0x64);
STATIC_ASSERT(offsetof(CChara::CSkin, m_matrix) == 0x00);
STATIC_ASSERT(offsetof(CChara::CSkin, m_bindMtx) == 0x30);
STATIC_ASSERT(offsetof(CChara::CSkin, m_nodeIndex) == 0x60);
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

STATIC_ASSERT(sizeof(CChara::CModel::CRefData) == 0x44);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_nodeCount) == 0x08);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_meshCount) == 0x0C);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_nodeRefData) == 0x10);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_meshRefData) == 0x14);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_bank) == 0x18);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CChara::CModel::CRefData, m_posQuant) == 0x34);
STATIC_ASSERT(sizeof(CChara::CNode) == 0xC0);
STATIC_ASSERT(offsetof(CChara::CNode, m_refData) == 0x00);
STATIC_ASSERT(offsetof(CChara::CNode, m_localRuntimeMtx) == 0x14);
STATIC_ASSERT(offsetof(CChara::CNode, m_previousQuat) == 0x44);
STATIC_ASSERT(offsetof(CChara::CNode, m_mtx) == 0x6C);
STATIC_ASSERT(offsetof(CChara::CNode, m_animNodes[0]) == 0x9C);
STATIC_ASSERT(offsetof(CChara::CNode, m_animNodes[1]) == 0xA0);
STATIC_ASSERT(offsetof(CChara::CNode, m_dynPosition) == 0xA4);
STATIC_ASSERT(offsetof(CChara::CNode, m_flags) == 0xBC);
STATIC_ASSERT(sizeof(CChara::CNode::CRefData) == 0x94);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_localMtx) == 0x00);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_bindMtx) == 0x30);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_boneLen) == 0x60);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_childBankOffset) == 0x64);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_index) == 0x66);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_parentIndex) == 0x68);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_names[0]) == 0x6A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_names[1]) == 0x7A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_childCount) == 0x8A);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_type) == 0x8B);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_bindFlags) == 0x8C);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_displayIndex) == 0x8D);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_miscFlags) == 0x8E);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_usesParentLenX) == 0x8F);
STATIC_ASSERT(offsetof(CChara::CNode::CRefData, m_dynParamIndex) == 0x90);

STATIC_ASSERT(offsetof(CChara::CModel, m_beforeCalcMatrixCallback) == 0xec);
STATIC_ASSERT(offsetof(CChara::CModel, m_beforeDrawModelCallback) == 0xf0);
STATIC_ASSERT(offsetof(CChara::CModel, m_beforeMeshLockEnvCallback) == 0xf4);
STATIC_ASSERT(offsetof(CChara::CModel, m_beforeDrawShadowLockEnvCallback) == 0xf8);
STATIC_ASSERT(offsetof(CChara::CModel, m_drawMeshDLCallback) == 0xfc);
STATIC_ASSERT(offsetof(CChara::CModel, m_drawShadowMeshDLCallback) == 0x100);
STATIC_ASSERT(offsetof(CChara::CModel, m_afterDrawMeshCallback) == 0x104);
STATIC_ASSERT(offsetof(CChara::CModel, m_afterDrawModelCallback) == 0x108);

static inline CChara::CModel::CRefData* ModelRef(CChara::CModel* model)
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

static inline u8& ModelFlags10C(CChara::CModel* model)
{
	return model->m_flags10C;
}

static inline s8 ModelFlag10C_80(CChara::CModel* model)
{
	return model->m_flags10CBits.m_flag10C_80;
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

static inline void* ModelCalcCbUser0(CChara::CModel* model)
{
	return model->m_callbackContext;
}

static inline void* ModelCalcCbUser1(CChara::CModel* model)
{
	return model->m_callbackParam;
}

static inline void* ModelCbUser0(CChara::CModel* model)
{
	return model->m_callbackContext;
}

static inline void* ModelCbUser1(CChara::CModel* model)
{
	return model->m_callbackParam;
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

static inline u32 CharaFourCC(char a, char b, char c, char d)
{
	return (static_cast<u32>(a) << 24) | (static_cast<u32>(b) << 16) | (static_cast<u32>(c) << 8) | static_cast<u32>(d);
}

static inline char* NodeRefName(CChara::CNode* node)
{
	return node->m_refData->m_names[0];
}

static inline char* NodeRefAltName(CChara::CNode* node)
{
	return node->m_refData->m_names[1];
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
	return node->m_animNodes[0];
}

static inline CChara::CAnimNode*& NodeAnimNode1(CChara::CNode* node)
{
	return node->m_animNodes[1];
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

static inline u8 ModelAttachMode(CChara::CModel* model)
{
	return model->m_attachMode;
}

struct CDynParam
{
	float m_velScale;
	float m_damp;
	float m_wind;
	int m_enable[2];
	float m_min[2];
	float m_max[2];
};


} // namespace

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void D3DXMatrixMultiplyRotate(float (*out)[4], float (*a)[4], float (*b)[4])
{
	Mtx rotA;
	Mtx rotB;
	Mtx result;

	PSMTXCopy(a, rotA);
	PSMTXCopy(b, rotB);
	rotA[0][3] = CVector(0.0f, 0.0f, 0.0f).x;
	rotA[1][3] = CVector(0.0f, 0.0f, 0.0f).y;
	rotA[2][3] = CVector(0.0f, 0.0f, 0.0f).z;
	rotB[0][3] = CVector(0.0f, 0.0f, 0.0f).x;
	rotB[1][3] = CVector(0.0f, 0.0f, 0.0f).y;
	rotB[2][3] = CVector(0.0f, 0.0f, 0.0f).z;
	PSMTXConcat(rotB, rotA, result);
	out[0][0] = result[0][0];
	out[1][0] = result[1][0];
	out[2][0] = result[2][0];
	out[0][1] = result[0][1];
	out[1][1] = result[1][1];
	out[2][1] = result[2][1];
	out[0][2] = result[0][2];
	out[1][2] = result[1][2];
	out[2][2] = result[2][2];
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
inline void VECLerp(Vec* a, Vec* b, Vec* out, float t)
{
	Vec scaledA;
	Vec scaledB;

	PSVECScale(a, &scaledA, 1.0f - t);
	PSVECScale(b, &scaledB, t);
	PSVECAdd(&scaledA, &scaledB, out);
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
	m_amemStage = Memory.CreateStage(0xc0000, "CChara", 0);
	m_amemLoadStage = 0;
	m_drawBuffers[0].m_base = new (Chara.GetMemoryStage(), "chara.cpp", 0x3f) u8[0x58000];
	m_drawBuffers[1].m_base = new (Chara.GetMemoryStage(), "chara.cpp", 0x40) u8[0x58000];
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
asm void CChara::gqrInit(register unsigned long posGqr, register unsigned long normGqr,
                        register unsigned long texGqr)
{
	nofralloc
	mtspr GQR5, posGqr
	mtspr GQR6, normGqr
	mtspr GQR7, texGqr
	blr
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CChara::CModel::CRefData::CRefData()
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
	if (m_dynParams != 0) {
		delete[] static_cast<u8*>(m_dynParams);
		m_dynParams = 0;
	}
	if (m_nodeRefData != 0) {
		delete[] m_nodeRefData;
		m_nodeRefData = 0;
	}
	if (m_meshRefData != 0) {
		delete[] m_meshRefData;
		m_meshRefData = 0;
	}
	if (m_bank != 0) {
		delete[] static_cast<u8*>(m_bank);
		m_bank = 0;
	}
	CMaterialSet* materialSet = m_materialSet;
	if (materialSet != 0) {
		if (materialSet->DecRef() == 0) {
			delete materialSet;
		}
		m_materialSet = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800736e4
 * PAL Size: 308b
 * EN Address: 0x8007ecb8
 * EN Size: 152b
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
	Init();
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
	CTextureSet* texSet = m_texSet;
	if (texSet != 0) {
		if (texSet->DecRef() == 0) {
			delete texSet;
		}
		m_texSet = 0;
	}

	CAnim* anim = m_anim;
	if (anim != 0) {
		if (anim->DecRef() == 0) {
			delete anim;
		}
		m_anim = 0;
	}

	CTexAnimSet* texAnimSet = m_texAnimSet;
	if (texAnimSet != 0) {
		if (texAnimSet->DecRef() == 0) {
			delete texAnimSet;
		}
		m_texAnimSet = 0;
	}

	CRefData* refData = m_data;
	if (refData != 0) {
		if (refData->DecRef() == 0) {
			delete refData;
		}
		m_data = 0;
	}

	if (m_nodes != 0) {
		delete[] m_nodes;
		m_nodes = 0;
	}

	if (m_meshes != 0) {
		delete[] m_meshes;
		m_meshes = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80073480
 * PAL Size: 192b
 * EN Address: 0x80072DE8
 * EN Size: 192b
 * JP Address: 0x8007285C
 * JP Size: 228b
 */
void CChara::CModel::Init()
{
	m_time = 0.0f;
	m_curFrame = 0.0f;
	m_dynJitter.x = 0.0f;
	m_dynJitter.y = 0.0f;
	m_dynJitter.z = 0.0f;
	m_blendMax = m_blendCur = 0;
	m_meshVisibleMask = 0xFFFFFFFF;
	m_animStart = 0.0f;
	m_animEnd = 0.0f;
	m_chestTilt = m_chestAmp = 0.0f;
	m_lightAlpha = 1.0f;
	m_callbackContext = 0;
	m_callbackParam = 0;
	m_beforeDrawModelCallback = 0;
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
	m_furCur = m_furTarget = 1.0f;
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
	m_data = new (stage, "chara.cpp", 0x111) CRefData;

	CChunkFile chunkFile(fileData);
	CChunkFile::CChunk chunk;
	CChara* charaPtr = &Chara;

	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != CharaFourCC('C', 'H', 'M', ' ')) {
			continue;
		}
		if (chunk.m_version < 5) {
			if (System.GetErrorLevel() >= 2U) {
				System.Printf("古いモデル形式です。\n");
			}
			return;
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
				    new(charaPtr->GetMemoryStage(), "chara.cpp", 0x132) CMaterialSet();
				m_data->m_materialSet = materialSet;
				CMaterialSet* createdSet = m_data->m_materialSet;
				createdSet->m_materials.SetDefaultSize(0x20);
				createdSet->m_materials.SetGrow(0);
				m_data->m_materialSet->Create(chunkFile, 0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0), g_pLight);
			} else if (chunk.m_id == 0x54415354) {
				if (chunk.m_arg0 != 0) {
					CTexAnimSet* texAnimSet =
					    new(charaPtr->GetMemoryStage(), "chara.cpp", 0x13A) CTexAnimSet();
					m_texAnimSet = texAnimSet;
					m_texAnimSet->Create(chunkFile, stage);
				}
			} else if (chunk.m_id == 0x4E534554) {
				m_data->m_nodeCount = 0;
				CChara::CNode::CRefData* nodeRefs =
				    new (stage, "chara.cpp", 0x143) CChara::CNode::CRefData[chunk.m_arg0];
				m_data->m_nodeRefData = nodeRefs;
				CChara::CNode* nodes =
				    new (stage, "chara.cpp", 0x145) CChara::CNode[chunk.m_arg0];
				m_nodes = nodes;

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == 0x4E4F4445) {
						CNode* node = &m_nodes[m_data->m_nodeCount];
						node->Create(chunkFile, this, static_cast<CChara::CNode::TYPE>(chunk.m_arg0), stage);
						if (strcmp(NodeRefName(node), "chest1") == 0) {
							m_data->m_headNodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), "chest2") == 0) {
							m_data->m_chest3NodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), "head") == 0) {
							m_data->m_chest2NodeIndex = node->m_refData->m_index;
						} else if (strcmp(NodeRefName(node), "chin") == 0) {
							m_data->m_chest1NodeIndex = node->m_refData->m_index;
						}
						m_data->m_nodeCount = m_data->m_nodeCount + 1;
					}
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == 0x4D535354) {
				m_data->m_meshCount = 0;
				CChara::CMesh::CRefData* meshRefs =
				    new (stage, "chara.cpp", 0x171) CChara::CMesh::CRefData[chunk.m_arg0];
				m_data->m_meshRefData = meshRefs;
				CChara::CMesh* meshes =
				    new (stage, "chara.cpp", 0x173) CChara::CMesh[chunk.m_arg0];
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
				void* bank = new(stage, "chara.cpp", 0x187) u8[chunk.m_size];
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
				void* dynParams = static_cast<void*>(new (stage, "chara.cpp", 0x1E7) u8[chunk.m_arg0 * 0x24]);
				ModelDynParams(this) = dynParams;

				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == CharaFourCC('D', 'Y', 'N', ' ')) {
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
					}
					ModelDynCount(this)++;
				}
				chunkFile.PopChunk();
			} else if (chunk.m_id == CharaFourCC('N', 'S', 'E', 'T')) {
				chunkFile.PushChunk();
				u32 currentNode = 0;
				while (chunkFile.GetNextChunk(chunk)) {
					if (chunk.m_id == CharaFourCC('N', 'A', 'M', 'E')) {
						currentNode = SearchNode(chunkFile.GetString());
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
		for (u32 j = 0; j < meshRaw->m_data->m_skinCount; j++) {
			CSkin* skin = &meshRaw->m_data->m_skins[j];
			u32 skinNodeIndex = skin->m_nodeIndex;
			PSMTXInverse(NodeRefBindMtx(&ModelNodes(this)[skinNodeIndex]), skin->m_bindMtx);
			PSMTXConcat(skin->m_bindMtx, NodeRefBindMtx(&ModelNodes(this)[meshRaw->m_data->m_nodeIndex]), skin->m_bindMtx);
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
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CNode::Duplicate(CChara::CNode* src, CMemory::CStage*)
{
	m_refData = src->m_refData;
	PSMTXCopy(src->m_localRuntimeMtx, m_localRuntimeMtx);
	PSMTXCopy(src->m_mtx, m_mtx);
	m_previousQuat = src->m_previousQuat;
	m_previousPosition = src->m_previousPosition;
	m_previousScale = src->m_previousScale;
	m_flagsBits.m_flag_80 = src->m_flagsBits.m_flag_80;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CMesh::Duplicate(CChara::CMesh* src, CMemory::CStage*)
{
	m_data = src->m_data;
	m_workPositions = 0;
	m_workNormals = 0;
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
	CModel* clone = new (stage, "chara.cpp", 0x25A) CModel;

	clone->m_data = m_data;
	m_data->AddRef();

	clone->m_nodes = new (stage, "chara.cpp", 0x263) CNode[m_data->m_nodeCount];
	for (u32 i = 0; i < m_data->m_nodeCount; i++) {
		clone->m_nodes[i].Duplicate(&m_nodes[i], stage);
	}

	clone->m_meshes = new (stage, "chara.cpp", 0x26C) CMesh[m_data->m_meshCount];
	for (u32 i = 0; i < m_data->m_meshCount; i++) {
		clone->m_meshes[i].Duplicate(&m_meshes[i], stage);
	}

	if (m_texSet != 0) {
		clone->m_texSet = m_texSet;
		clone->m_texSet->AddRef();
	}
	if (ModelTexAnimSet(this) != 0) {
		clone->m_texAnimSet = ModelTexAnimSet(this)->Duplicate(stage);
	}

	clone->Init();

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
 * EN Address: 0x8007FDCC
 * EN Size: 392b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::CalcMatrix()
{
	m_worldBaseMtx[0][0] = m_matrix[0][0];
	m_worldBaseMtx[1][0] = m_matrix[1][0];
	m_worldBaseMtx[2][0] = m_matrix[2][0];
	m_worldBaseMtx[0][1] = m_matrix[0][1];
	m_worldBaseMtx[1][1] = m_matrix[1][1];
	m_worldBaseMtx[2][1] = m_matrix[2][1];
	m_worldBaseMtx[0][2] = m_matrix[0][2];
	m_worldBaseMtx[1][2] = m_matrix[1][2];
	m_worldBaseMtx[2][2] = m_matrix[2][2];
	m_worldBaseMtx[0][3] = 0.0f;
	m_worldBaseMtx[1][3] = 0.0f;
	m_worldBaseMtx[2][3] = 0.0f;

	m_drawMtx[0][0] = 1.0f;
	m_drawMtx[1][0] = 0.0f;
	m_drawMtx[2][0] = 0.0f;
	m_drawMtx[0][1] = 0.0f;
	m_drawMtx[1][1] = 1.0f;
	m_drawMtx[2][1] = 0.0f;
	m_drawMtx[0][2] = 0.0f;
	m_drawMtx[1][2] = 0.0f;
	m_drawMtx[2][2] = 1.0f;
	m_drawMtx[0][3] = m_matrix[0][3];
	m_drawMtx[1][3] = m_matrix[1][3];
	m_drawMtx[2][3] = m_matrix[2][3];

	if (m_blendCur != 0) {
		m_blendCur--;
	}

	BeforeCalcMatrixCallback beforeCalcMatrix = m_beforeCalcMatrixCallback;
	if (beforeCalcMatrix == 0 || beforeCalcMatrix(this, m_callbackContext, m_callbackParam) != 0) {
		calcMatrix();

		CTexAnimSet* texAnimSet = m_texAnimSet;
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
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CChara::CModel::calcNowFrame()
{
	float frame;
	if (m_anim != 0) {
		float total = 1.0f + (m_animEnd - m_animStart);
		if (((AnimFlags(m_anim) >> 6) & 1) != 0) {
			if (m_time < 0.0f) {
				frame = ((m_animStart + total) - 1.0f) - ((-m_time < total - 1.0f) ? -m_time : total - 1.0f);
			} else {
				float limit = total - 1.0f;
				float clamped = (m_time < limit) ? m_time : limit;
				frame = m_animStart + clamped;
			}
		} else if (m_time < 0.0f) {
			frame = ((m_animStart + total) - 1.0f) - static_cast<float>(fmod(-m_time, total));
		} else {
			frame = m_animStart + static_cast<float>(fmod(m_time, total));
		}
	} else {
		frame = 0.0f;
	}
	m_curFrame = frame;
	return frame;
}

/*
 * --INFO--
 * PAL Address: 0x80071B64
 * PAL Size: 1936b
 * EN Address: 0x800800F8
 * EN Size: 1636b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::calcMatrix()
{
	float frame = calcNowFrame();
	if (m_anim != 0) {
		m_anim->InitQuantize();
	}

	CNode* node = ModelNodes(this);
	u32 nodeCount = ModelNodeCount(this);
	for (u32 i = 0; i < nodeCount; i++, node++) {
		CChara::CNode::CRefData* ref = node->m_refData;
		CNode* parentNode = (ref->m_parentIndex < 0) ? 0 : &m_nodes[ref->m_parentIndex];

		SRT srt;
		Mtx animMtx;

		if (NodeAnimNode0(node) != 0 || NodeAnimNode1(node) != 0) {
			if (parentNode != 0 && NodeAnimNode0(parentNode) != 0 && NodeAnimNode0(parentNode)->IsScale()) {
				if (NodeRuntimeFlag80(node)) {
					float* parentScale = NodeRuntimeScale(parentNode);
					PSMTXScale(NodeLocalRuntimeMtx(node),
					           1.0f / parentScale[0],
					           1.0f / parentScale[1],
					           1.0f / parentScale[2]);
				}
			} else if (NodeRuntimeFlag80(node)) {
				float baseScale;
				if (parentNode != 0 || (baseScale = ModelBaseScale(this)) == 1.0f) {
					PSMTXIdentity(NodeLocalRuntimeMtx(node));
				} else {
					PSMTXScale(NodeLocalRuntimeMtx(node), baseScale, baseScale, baseScale);
				}
			}

			if (ref->m_usesParentLenX != 0) {
				NodeLocalRuntimeMtx(node)[0][3] = NodeBoneLen(parentNode);
			}

			if (NodeAnimNode1(node) != 0) {
				NodeAnimNode1(node)->Interp(m_anim, &srt, frame);
				if (NodeAnimNode1(node)->IsScale()) {
					Math.SRTToMatrix(animMtx, &srt);
				} else {
					Math.SRTToMatrixRT(animMtx, &srt);
				}
				PSMTXConcat(NodeLocalRuntimeMtx(node), animMtx, NodeLocalRuntimeMtx(node));
				PSMTXScale(animMtx,
				           1.0f / srt.m_scale.x,
				           1.0f / srt.m_scale.y,
				           1.0f / srt.m_scale.z);
				PSMTXConcat(NodeLocalRuntimeMtx(node), animMtx, NodeLocalRuntimeMtx(node));
			}

			if (NodeAnimNode0(node) != 0) {
				NodeAnimNode0(node)->Interp(m_anim, &srt, frame);
				s16 nodeIndex = ref->m_index;
				if (nodeIndex == ModelHeadIndex(this) || nodeIndex == ModelChest3Index(this) ||
				    nodeIndex == ModelChest2Index(this)) {
					float tiltScale;
					if (nodeIndex == ModelChest2Index(this)) {
						tiltScale = 0.5f;
						srt.m_rotation.y -= m_chestTilt * tiltScale;
					} else {
						tiltScale = 0.25f;
						srt.m_rotation.x += m_chestTilt * tiltScale;
					}
					srt.m_rotation.z += m_chestAmp * tiltScale;
				} else if (nodeIndex == ModelChest1Index(this) && ModelTexAnimSet(this) != 0) {
					srt.m_rotation.z += TexAnimSetChin(ModelTexAnimSet(this));
				}
				if (NodeAnimNode0(node)->IsScale()) {
					Math.SRTToMatrix(animMtx, &srt);
				} else {
					Math.SRTToMatrixRT(animMtx, &srt);
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
				runtimeScale[0] = runtimeScale[1] = runtimeScale[2] = 0.0f;
			}
		} else {
			if (NodeRuntimeFlag80(node)) {
				PSMTXCopy(ref->m_localMtx, NodeLocalRuntimeMtx(node));
			}
		}

		u16 blendCur = ModelBlendCur(this);
		if (blendCur != 0) {
			u16 blendMax = ModelBlendMax(this);
			float alpha = 1.0f - (static_cast<float>(blendCur) * (1.0f / static_cast<float>(blendMax)));
			Quaternion quat;
			Vec pos;
			Vec scale;
			Mtx scaleMtx;
			pos.x = NodeLocalRuntimeMtx(node)[0][3];
			pos.y = NodeLocalRuntimeMtx(node)[1][3];
			pos.z = NodeLocalRuntimeMtx(node)[2][3];

			Math.MTXGetScale(NodeLocalRuntimeMtx(node), &scale);
			if (scale.x < 0.2f) {
				scale.y = 0.1f;
				scale.z = 0.1f;
			} else {
				VECLerp(&NodePreviousScale(node), &scale, &scale, alpha);
			}
			VECLerp(&NodePreviousPosition(node), &pos, &pos, alpha);
			C_QUATMtx(&quat, NodeLocalRuntimeMtx(node));
			C_QUATSlerp(&NodePreviousQuat(node), &quat, &quat, alpha);
			PSMTXScale(scaleMtx, scale.x, scale.y, scale.z);
			PSMTXQuat(NodeLocalRuntimeMtx(node), &quat);
			PSMTXConcat(NodeLocalRuntimeMtx(node), scaleMtx, NodeLocalRuntimeMtx(node));
			NodeLocalRuntimeMtx(node)[0][3] = pos.x;
			NodeLocalRuntimeMtx(node)[1][3] = pos.y;
			NodeLocalRuntimeMtx(node)[2][3] = pos.z;
		}

		if (parentNode != 0) {
			PSMTXConcat(NodeWorldMtx(parentNode), NodeLocalRuntimeMtx(node), NodeWorldMtx(node));
		} else {
			PSMTXConcat(ModelWorldBaseMtx(this), NodeLocalRuntimeMtx(node), NodeWorldMtx(node));
		}

		if (ref->m_dynParamIndex >= 0) {
			dynamics(node, parentNode);
		}

		if (ref->m_index == ModelHeadIndex(this) && ModelTwistAngle(this) != 0.0f) {
			Vec twistAxis = {1.0f, 0.0f, 0.0f};
			Mtx twistRotate;
			PSMTXMultVecSR(ModelWorldBaseMtx(this), &twistAxis, &twistAxis);
			PSMTXRotAxisRad(twistRotate, &twistAxis, ModelTwistAngle(this));
			D3DXMatrixMultiplyRotate(node->m_mtx, node->m_mtx, twistRotate);
		}
	}

	this->m_flags10CBits.m_flag10C_80 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800716C4
 * PAL Size: 1184b
 * EN Address: 0x8008075C
 * EN Size: 1140b
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
	SRT parentScaleSrt;
	while (node != 0) {
		int curReuseAnimNode0Srt;
		CChara::CNode::CRefData* ref = node->m_refData;
		CNode* parentNode = (ref->m_parentIndex < 0) ? 0 : &m_nodes[ref->m_parentIndex];

		curReuseAnimNode0Srt = reuseAnimNode0Srt;
		reuseAnimNode0Srt = 0;
		SRT cachedParentScaleSrt = parentScaleSrt;
		SRT srt;
		Mtx animMtx;
		Mtx localMtx;

		if (NodeAnimNode0(node) != 0 || NodeAnimNode1(node) != 0) {
			if (parentNode != 0 && NodeAnimNode0(parentNode) != 0 &&
			    NodeAnimNode0(parentNode)->IsScale()) {
				NodeAnimNode0(parentNode)->Interp(m_anim, &parentScaleSrt, frame);
				reuseAnimNode0Srt = 1;
				PSMTXScale(localMtx,
				           1.0f / parentScaleSrt.m_scale.x,
				           1.0f / parentScaleSrt.m_scale.y,
				           1.0f / parentScaleSrt.m_scale.z);
			} else {
				if (parentNode != 0 || 1.0f == ModelBaseScale(this)) {
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
				NodeAnimNode1(node)->Interp(m_anim, &srt, frame);
				if (NodeAnimNode1(node)->IsScale()) {
					Math.SRTToMatrix(animMtx, &srt);
				} else {
					Math.SRTToMatrixRT(animMtx, &srt);
				}
				PSMTXConcat(localMtx, animMtx, localMtx);

				PSMTXScale(animMtx,
				           1.0f / srt.m_scale.x,
				           1.0f / srt.m_scale.y,
				           1.0f / srt.m_scale.z);
				PSMTXConcat(localMtx, animMtx, localMtx);
			}

			if (NodeAnimNode0(node) != 0) {
				if (curReuseAnimNode0Srt) {
					srt = cachedParentScaleSrt;
				} else {
					NodeAnimNode0(node)->Interp(m_anim, &srt, frame);
				}
				if (NodeAnimNode0(node)->IsScale()) {
					Math.SRTToMatrix(animMtx, &srt);
				} else {
					Math.SRTToMatrixRT(animMtx, &srt);
				}
				PSMTXConcat(localMtx, animMtx, localMtx);
			}
		} else {
			PSMTXCopy(ref->m_localMtx, localMtx);
		}

		u16 blendCur = ModelBlendCur(this);
		if (blendCur != 0) {
			u16 blendMax = ModelBlendMax(this);
			float alpha = 1.0f - (static_cast<float>(blendCur) * (1.0f / static_cast<float>(blendMax)));
			Quaternion quat;
			Vec pos;
			Vec scale;
			Mtx scaleMtx;
			pos.x = localMtx[0][3];
			pos.y = localMtx[1][3];
			pos.z = localMtx[2][3];

			Math.MTXGetScale(localMtx, &scale);
			if (scale.x < 0.2f) {
				scale.y = 0.1f;
				scale.z = 0.1f;
			} else {
				VECLerp(&NodePreviousScale(node), &scale, &scale, alpha);
			}
			VECLerp(&NodePreviousPosition(node), &pos, &pos, alpha);
			C_QUATMtx(&quat, localMtx);
			C_QUATSlerp(&NodePreviousQuat(node), &quat, &quat, alpha);
			PSMTXScale(scaleMtx, scale.x, scale.y, scale.z);
			PSMTXQuat(localMtx, &quat);
			PSMTXConcat(localMtx, scaleMtx, localMtx);
			localMtx[0][3] = pos.x;
			localMtx[1][3] = pos.y;
			localMtx[2][3] = pos.z;
		}

		PSMTXConcat(localMtx, out, out);

		node = parentNode;
	}

	PSMTXConcat(m_matrix, out, out);
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
	CDynParam* dynParam = &reinterpret_cast<CDynParam*>(m_data->m_dynParams)[node->m_refData->m_dynParamIndex];

	CVector forward = CVector(node->m_mtx[0][0], node->m_mtx[1][0], node->m_mtx[2][0]);
	CVector right = CVector(node->m_mtx[0][1], node->m_mtx[1][1], node->m_mtx[2][1]);
	CVector up = CVector(node->m_mtx[0][2], node->m_mtx[1][2], node->m_mtx[2][2]);
	forward.Normalize();
	CVector origin = CVector(node->m_mtx[0][3], node->m_mtx[1][3], node->m_mtx[2][3]);
	float boneLen = NodeBoneLen(node);
	CVector target = origin + forward * boneLen;

	if (ModelFlag10C_80(this)) {
		node->m_dynPosition = target;
		node->m_dynVel.Identity();
		return;
	}

	float randomScale = 0.5f * Math.RandF() + 0.5f;
	CVector accel = (target - node->m_dynPosition) + m_dynJitter * randomScale * dynParam->m_wind;
	node->m_dynVel += accel;
	CVector predicted = node->m_dynPosition + node->m_dynVel * dynParam->m_velScale;
	node->m_dynVel *= dynParam->m_damp;
	CVector direction = predicted - origin;

	for (int axis = 0; axis < 2; axis++) {
		if (dynParam->m_enable[axis] != 0) {
			float angle;
			if (axis == 0) {
				float dotForward = PSVECDotProduct(forward, direction);
				float dotSide = PSVECDotProduct(up, direction);
				angle = -atan2f(dotSide, dotForward);
			} else {
				float dotForward = PSVECDotProduct(forward, direction);
				float dotSide = PSVECDotProduct(right, direction);
				angle = atan2f(dotSide, dotForward);
			}
			if (angle <= 0.017453292f * dynParam->m_min[axis] || 0.017453292f * dynParam->m_max[axis] <= angle) {
				float rot;
				if (angle <= 0.017453292f * dynParam->m_min[axis]) {
					rot = 0.017453292f * dynParam->m_min[axis] - angle;
				} else {
					rot = 0.017453292f * dynParam->m_max[axis] - angle;
				}

				Mtx rotate;
				if (axis == 0) {
					PSMTXRotAxisRad(rotate, right, rot);
				} else {
					PSMTXRotAxisRad(rotate, up, rot);
				}
				PSMTXMultVecSR(rotate, direction, direction);
			}
		}
	}

	direction.Normalize();
	float align = PSVECDotProduct(forward, direction);
	if (!(align > 0.99999f)) {
		float rotateAngle;
		if (align < -0.99999f) {
			rotateAngle = 3.1415927f;
		} else {
			rotateAngle = acosf(align);
		}

		CVector axis;
		PSVECCrossProduct(forward, direction, axis);
		Mtx rotate;
		PSMTXRotAxisRad(rotate, axis, rotateAngle);
		D3DXMatrixMultiplyRotate(node->m_mtx, node->m_mtx, rotate);
	}

	node->m_dynPosition = origin + direction * boneLen;
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
	PSMTXCopy(mtx, m_matrix);
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
	switch (*name) {
	case '_':
		if (name[1] == 's' && name[2] == 'k') {
			CNode* node = ModelNodes(this);
			u32 i = 0;
			for (; i < ModelNodeCount(this); i++, node++) {
				int tail = strlen(NodeRefName(node)) - 3;
				if (tail > 0 && strcmp(&node->m_refData->m_names[0][tail], name) == 0) {
					return (int)i;
				}
			}
		} else if (name[1] == 'r' && name[2] == 'o' && name[3] == 'o' && name[4] == 't') {
			CNode* node = ModelNodes(this);
			u32 i = 0;
			for (; i < ModelNodeCount(this); i++, node++) {
				int tail = strlen(NodeRefName(node)) - 5;
				if (tail > 0 && strcmp(&node->m_refData->m_names[0][tail], name) == 0) {
					return (int)i;
				}
			}
		}
		break;
	default:
		return SearchNode(name);
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8007096c
 * PAL Size: 1192b
 * EN Address: 0x800702D4
 * EN Size: 1192b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::Draw(float (*view)[4], int flags, int pass)
{
	if (ModelLightAlpha(this) == 0.0f) {
		return;
	}

	const int cullFlag = flags & 1;
	const int shadowDisabled = ((flags >> 1) & 1) ^ 1;
	const int materialAlpha = (flags >> 2) & 1;
	const int shadowCullEnabled = (flags >> 3) & 1;
	const int skipShadowPosition = ((flags >> 4) & 1) ^ 1;
	BeforeDrawModelCallback beforeDrawModel = m_beforeDrawModelCallback;
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

	for (int meshIndex = 0; meshIndex < ModelMeshCount(this); meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (meshIndex < 0x20 && ((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		MaterialMan.InitEnv();

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
			MaterialMan.SetPosition(static_cast<CMapShadow::TARGET>(0), &position, 100.0f, 10.0f, meshMtx,
			                        m_flagsA0Bits.m_flagA0_80);
		}

		const int lightEnable = static_cast<int>(static_cast<u32>(mesh->m_data->m_flags & 0xC0) << 24) >> 31;
		if (lastLightEnable != lightEnable) {
			lastLightEnable = lightEnable;
			LightPcs.EnableLight(lightEnable == 0, 0);
		}

		const int zWriteEnable = static_cast<int>(static_cast<u32>(mesh->m_data->m_flags & 0x60) << 25) >> 31;
		if (lastZWrite != zWriteEnable) {
			lastZWrite = zWriteEnable;
			GXSetZMode((u8)1, (GXCompare)3, (zWriteEnable == 0) ? GX_TRUE : GX_FALSE);
		}

		if (m_beforeMeshLockEnvCallback != 0) {
			m_beforeMeshLockEnvCallback(this, m_callbackContext, m_callbackParam, meshIndex);
		}

		MaterialMan.LockEnv();
		if (mesh->m_data->m_infoWord1 != 0) {
			LightPcs.SetBumpTexMatirx(meshMtx, g_pLight, 0, 0);
		}
		MaterialMan.SetObjMatrix(view, meshMtx);
		GXSetArray((GXAttr)9, mesh->m_workPositions, 6);
		MaterialMan.SetNRM(mesh->m_workNormals);
		GXSetArray((GXAttr)0xB, mesh->m_data->m_colors, sizeof(_GXColor));
		GXSetArray((GXAttr)0xD, mesh->m_data->m_uvs, sizeof(S16Vec2d));
		GXSetArray((GXAttr)0xE, mesh->m_data->m_uvs, sizeof(S16Vec2d));

		CCharaDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (int displayListIndex = static_cast<int>(mesh->m_data->m_displayListCount) - 1; displayListIndex >= 0; displayListIndex--, displayList++) {
			if (m_drawMeshDLCallback != 0) {
				m_drawMeshDLCallback(this, m_callbackContext, m_callbackParam, meshIndex, displayListIndex, meshMtx);
			} else {
				MaterialMan.SetMaterial(ModelMaterialSet(this), displayList->m_material, materialAlpha, (_GXTevScale)0);
				GXCallDisplayList(displayList->m_data, displayList->m_size);
			}
		}

		if (m_afterDrawMeshCallback != 0) {
			m_afterDrawMeshCallback(this, m_callbackContext, m_callbackParam, meshIndex, meshMtx);
		}
	}

	AfterDrawModelCallback afterDrawModel = m_afterDrawModelCallback;
	if (afterDrawModel != 0) {
		afterDrawModel(this, m_callbackContext, m_callbackParam);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80070690
 * PAL Size: 732b
 * EN Address: 0x8006FFF8
 * EN Size: 732b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::DrawShadow(float (*view)[4], int zMode)
{
	if (1.0f != ModelLightAlpha(this)) {
		return;
	}

	ModelMaterialSet(this)->SetTextureSet(m_texSet);
	LightPcs.SetAmbientAlpha(1.0f);
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

		MaterialMan.InitEnv();

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		} else {
			PSMTXConcat(ModelDrawMtx(this), ModelNodes(this)[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		if (m_beforeDrawShadowLockEnvCallback != 0) {
			m_beforeDrawShadowLockEnvCallback(this, ModelCbUser0(this), ModelCbUser1(this), meshIndex);
		}

		MaterialMan.LockEnv();
		MaterialMan.SetObjMatrix(view, meshMtx);
		GXSetArray((GXAttr)9, mesh->m_workPositions, 6);
		MaterialMan.SetNRM(mesh->m_workNormals);
		GXSetArray((GXAttr)0xB, mesh->m_data->m_colors, sizeof(_GXColor));
		GXSetArray((GXAttr)0xD, mesh->m_data->m_uvs, sizeof(S16Vec2d));
		GXSetArray((GXAttr)0xE, mesh->m_data->m_uvs, sizeof(S16Vec2d));

		CCharaDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (int displayListIndex = static_cast<int>(mesh->m_data->m_displayListCount) - 1; displayListIndex >= 0; displayListIndex--, displayList++) {
			if (m_drawShadowMeshDLCallback != 0) {
				m_drawShadowMeshDLCallback(this, ModelCalcCbUser0(this), ModelCalcCbUser1(this), meshIndex, displayListIndex, meshMtx);
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
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CChara::CModel::CalcInterpFrame()
{
	CAnim* currentAnim = m_anim;
	int resolvedBlend;
	if (currentAnim != 0 && AnimInterpCount(currentAnim) != 0 && AnimBank(currentAnim) != 0) {
		u8 interpCount = AnimInterpCount(currentAnim);
		resolvedBlend = 4;

		int frame = static_cast<int>(m_curFrame);
		int i;
		u16* interpTable = reinterpret_cast<u16*>(AnimInterpOffset(currentAnim) + reinterpret_cast<u32>(AnimBank(currentAnim)));

		for (i = 0; i < static_cast<int>(interpCount); i++) {
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
	return resolvedBlend;
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
	if (m_flagsA0Bits.m_flagA0_20) {
		CalcNodeWorldMatrix(outMtx, node);
	} else {
		PSMTXCopy(m_matrix, outMtx);
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
		blendMode = CalcInterpFrame();
	}

	if (anim != m_anim) {
		CAnim* oldAnim = m_anim;
		if (oldAnim != 0) {
			if (oldAnim->DecRef() == 0) {
				delete oldAnim;
			}
			m_anim = 0;
		}
		m_anim = anim;
		if (m_anim != 0) {
			m_anim->AddRef();
		}
	}

	CNode* node = ModelNodes(this);
	for (u32 i = 0; i < ModelNodeCount(this); i++, node++) {
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

			for (unsigned int slot = 0; slot < 2; slot++) {
				char* name = node->m_refData->m_names[slot];
				if (name[0] != '\0' && strcmp(AnimNodeName(animNode), name) == 0) {
					node->m_animNodes[slot] = animNode;
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
		m_time = m_curFrame = 0.0f;
		m_animStart = m_animEnd = 0.0f;
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
	m_furCur += delta < -0.033f ? -0.033f :
	    0.033f < delta ? 0.033f : delta;
	m_furCur = m_furCur < 0.0f ? 0.0f : 1.0f < m_furCur ? 1.0f : m_furCur;
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
	return node->m_refData->m_displayIndex;
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
	m_refData = 0;
	m_displayMesh = 0;
	m_animNodes[0] = 0;
	m_animNodes[1] = 0;
	m_flagsBits.m_flag_80 = 1;
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
	m_refData = &model->m_data->m_nodeRefData[model->m_data->m_nodeCount];
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
			strcpy(m_refData->m_names[0], chunk.GetString());
		} else if (chunkInfo.m_id == 0x4E414D32) {
			strcpy(m_refData->m_names[1], chunk.GetString());
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
 * PAL Address: 0x8006fc98
 * PAL Size: 600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CNode::CalcBind(CChara::CModel* model)
{
	s16 parent = m_refData->m_parentIndex;
	if (parent >= 0) {
		PSMTXConcat(model->m_nodes[parent].m_refData->m_bindMtx, m_refData->m_localMtx, m_refData->m_bindMtx);
	} else {
		PSMTXCopy(m_refData->m_localMtx, m_refData->m_bindMtx);
	}
	PSMTXCopy(m_refData->m_bindMtx, m_mtx);
	for (u32 i = 0; i < m_refData->m_childCount; i++) {
		u16 nodeIndex = *reinterpret_cast<u16*>(
		    reinterpret_cast<u8*>(model->m_data->m_bank) + m_refData->m_childBankOffset + i * 2);
		CNode* child = &model->m_nodes[nodeIndex];
		child->CalcBind(model);
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
	m_displayIndex = -1;
	m_miscFlags = 0;
	m_childCount = 0;
	memset(m_names, 0, sizeof(m_names));
	m_boneLen = 0.0f;
	m_dynParamIndex = -1;
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
	CCharaMeshRefRaw* meshRef = &model->m_data->m_meshRefData[model->m_data->m_meshCount];
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
			    Memory._Alloc(chunkInfo.m_size, stage, "chara.cpp", CHARA_LINE(0x7D6, 0x7D1, 0x7C8), 0));
			m_data->m_vertices = verts;
			memcpy(m_data->m_vertices, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_vertices, m_data->m_vertexCount * 6);
			break;
		}
		case 0x4E4F524D: {
			m_data->m_normalCount = chunkInfo.m_size / 6;
			S16Vec* normals = static_cast<S16Vec*>(
			    Memory._Alloc(chunkInfo.m_size, stage, "chara.cpp", CHARA_LINE(0x7DE, 0x7D9, 0x7D0), 0));
			m_data->m_normals = normals;
			memcpy(m_data->m_normals, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_normals, m_data->m_normalCount * 6);
			break;
		}
		case 0x434F4C52: {
			m_data->m_colorCount = chunkInfo.m_size / sizeof(_GXColor);
			_GXColor* colors = static_cast<_GXColor*>(
			    Memory._Alloc(chunkInfo.m_size, stage, "chara.cpp", CHARA_LINE(0x7E6, 0x7E1, 0x7D8), 0));
			m_data->m_colors = colors;
			memcpy(m_data->m_colors, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_colors, m_data->m_colorCount * sizeof(_GXColor));
			break;
		}
		case 0x55562020: {
			m_data->m_uvCount = chunkInfo.m_size / sizeof(S16Vec2d);
			S16Vec2d* uvs = static_cast<S16Vec2d*>(
			    Memory._Alloc(chunkInfo.m_size, stage, "chara.cpp", CHARA_LINE(0x7EE, 0x7E9, 0x7E0), 0));
			m_data->m_uvs = uvs;
			memcpy(m_data->m_uvs, chunk.GetAddress(), chunkInfo.m_size);
			DCFlushRange(m_data->m_uvs, m_data->m_uvCount * sizeof(S16Vec2d));
			break;
		}
		case 0x534B494E: {
			m_data->m_skinCount = chunkInfo.m_arg0;
			m_data->m_skins =
			    new (stage, "chara.cpp", CHARA_LINE(0x7F8, 0x7F3, 0x7EA)) CChara::CSkin[m_data->m_skinCount];

			chunk.PushChunk();
			unsigned int skinIndex = 0;
			while (chunk.GetNextChunk(chunkInfo)) {
				if (chunkInfo.m_id == 0x4E4F4445) {
					m_data->m_skins[skinIndex++].Create(chunk, stage);
				} else if (chunkInfo.m_id == 0x4F4E4520) {
					m_data->m_oneWeightCountOrSize = chunkInfo.m_size;
					m_data->m_oneWeightData =
					    Memory._Alloc(m_data->m_oneWeightCountOrSize, stage, "chara.cpp", CHARA_LINE(0x808, 0x803, 0x7FA), 0);
					memcpy(m_data->m_oneWeightData, chunk.GetAddress(), chunkInfo.m_size);
				} else if (chunkInfo.m_id == 0x54574F20) {
					m_data->m_twoWeightCountOrSize = chunkInfo.m_size;
					m_data->m_twoWeightData =
					    Memory._Alloc(m_data->m_twoWeightCountOrSize, stage, "chara.cpp", CHARA_LINE(0x80E, 0x809, 0x800), 0);
					memcpy(m_data->m_twoWeightData, chunk.GetAddress(), chunkInfo.m_size);
				} else if (chunkInfo.m_id == 0x524D494E) {
					m_data->m_threeWeightCountOrSize = chunkInfo.m_size;
					m_data->m_threeWeightData =
					    Memory._Alloc(m_data->m_threeWeightCountOrSize, stage, "chara.cpp", CHARA_LINE(0x814, 0x80F, 0x806), 0);
					memcpy(m_data->m_threeWeightData, chunk.GetAddress(), chunkInfo.m_size);
				}
			}
			chunk.PopChunk();
			break;
		}
		case 0x444C4844: {
			m_data->m_displayListCount = chunkInfo.m_arg0 & 0xFFFF;
			m_data->m_displayLists = reinterpret_cast<CCharaDisplayListRaw*>(
			    new (stage, "chara.cpp", CHARA_LINE(0x820, 0x81B, 0x812)) CChara::CMesh::CDisplayList[m_data->m_displayListCount]);

			CCharaDisplayListRaw* displayList = m_data->m_displayLists;
			chunk.PushChunk();
			while (chunk.GetNextChunk(chunkInfo)) {
				switch (chunkInfo.m_id) {
				case 0x444C5354:
					displayList->m_material = chunk.Get2();
					displayList->m_size = static_cast<s32>(chunkInfo.m_arg0);
					chunk.Align(0x20);
					if (static_cast<u32>(displayList->m_size) != 0) {
						const unsigned int allocSize = (displayList->m_size + 0x1F) & ~0x1FU;
						displayList->m_data =
						    Memory._Alloc(allocSize, stage, "chara.cpp", CHARA_LINE(0x830, 0x82B, 0x822), 0);
						chunk.Get(displayList->m_data, displayList->m_size);
						DCFlushRange(displayList->m_data, displayList->m_size);
					}
					chunk.Align(0x20);
					displayList++;
					break;
				}
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
 * PAL Address: 0x8006efe8
 * PAL Size: 1244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CMesh::skin(register int oneWeightSize, register int twoWeightSize, register int threeWeightSize,
                        register CChara::CSkin* skinRef, register void* oneWeightData,
                        register void* twoWeightData, register void* threeWeightData,
                        S16Vec* srcPositions, S16Vec* dstPositions, S16Vec* srcNormals, S16Vec* dstNormals)
{
	struct {
		int sizes[3];
		CChara::CSkin* skin;
		void* streams[3];
	} saved;
	asm {
		mr. r3, oneWeightSize
		stw oneWeightSize, saved.sizes[0]
		stw twoWeightSize, saved.sizes[1]
		stw threeWeightSize, saved.sizes[2]
		stw skinRef, saved.skin
		stw oneWeightData, saved.streams[0]
		stw twoWeightData, saved.streams[1]
		stw threeWeightData, saved.streams[2]
		beq _chk2
		mr r4, r7
		mr r5, r8
		lwz r6, srcPositions
		lwz r7, dstPositions
		lwz r8, srcNormals
		lwz r9, dstNormals
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
		lwz r3, saved.sizes[1]
		cmpwi r3, 0x0
		beq _chk3
		lwz r5, saved.streams[1]
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
		lwz r3, saved.sizes[2]
		cmpwi r3, 0x0
		beq _end
		lwz r5, saved.streams[2]
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

		static int bFirst = 1;

		if (bFirst != 0) {
			bFirst = 0;
			if (System.GetErrorLevel() >= 2U) {
				System.Printf("CChara.CMesh.Calc: 描画バッファがあふれました。\n");
			}
		}
		return;
	}

	mesh->m_workPositions = reinterpret_cast<S16Vec*>(drawBuffer.m_base + cursor);
	cursor += AlignCharaWorkBytes(mesh->m_data->m_vertexCount * 6);
	mesh->m_workNormals = reinterpret_cast<S16Vec*>(drawBuffer.m_base + cursor);
	cursor += AlignCharaWorkBytes(mesh->m_data->m_normalCount * 6);

	CSkin* skinData = mesh->m_data->m_skins;
	for (u32 i = 0; i < mesh->m_data->m_skinCount; i++, skinData++) {
		u32 nodeIndex = skinData->m_nodeIndex;
		PSMTXConcat(
		    ModelNodes(model)[nodeIndex].m_mtx,
		    skinData->m_bindMtx,
		    skinData->m_matrix);
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
	    meshRef->m_skins,
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
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CChara::CSkin::Create(CChunkFile& chunk, CMemory::CStage* stage)
{
	m_nodeIndex = chunk.Get4();
}

CChara Chara;
