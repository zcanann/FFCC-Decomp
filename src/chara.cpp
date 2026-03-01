#include "ffcc/chara.h"
#include "ffcc/cflat_runtime.h"

extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, void*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void D3DXMatrixMultiplyRotate(float (*) [4], float (*) [4], float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CChara()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::FlipDBuffer()
{
	s32* dbufferIndex = (s32*)((u8*)this + 0x2060);
	*dbufferIndex = 1 - *dbufferIndex;

	u8* bufferPtr = (u8*)this + (*dbufferIndex << 3);
	u32 zero = 0;
	*(u32*)(bufferPtr + 0x2064) = zero;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CChara::CModel::CRefData::CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CModel::CRefData::~CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CModel::CModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CModel::~CModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::Create(void*, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CreateDynamics(void*, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::setup()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::Duplicate(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcMatrix()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcSkin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::calcNowFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::calcMatrix()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcFrameMatrix(float, CChara::CNode*, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::dynamics(CChara::CNode*, CChara::CNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::calcSkin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::SetMatrix(float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::SearchNode(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::SearchNodeSk(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::Draw(float (*) [4], int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::DrawShadow(float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcInterpFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcSafeNodeWorldMatrix(float (*) [4], CChara::CNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::AttachAnim(CChara::CAnim*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::AttachTextureSet(CTextureSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::AddFrame(float frame)
{
	m_curFrame += frame;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::SetFrame(float frame)
{
	m_curFrame = frame;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcFurColor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::GetDispIndex(CChara::CNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CNode::CNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CNode::~CNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CNode::Create(CChunkFile&, CChara::CModel*, CChara::CNode::TYPE, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CNode::Duplicate(CChara::CNode*, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CNode::CalcBind(CChara::CModel*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CNode::CRefData::CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CNode::CRefData::~CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::CMesh()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::~CMesh()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CMesh::Create(CChara::CModel*, CChunkFile&, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CMesh::Duplicate(CChara::CMesh*, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CMesh::skin(int, int, int, CChara::CSkin*, void*, void*, void*, S16Vec*, S16Vec*, S16Vec*, S16Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CMesh::Calc(CChara::CModel*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::CRefData::CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::CRefData::~CRefData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::CDisplayList::CDisplayList()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CMesh::CDisplayList::~CDisplayList()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CSkin::CSkin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CSkin::~CSkin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CSkin::Create(CChunkFile&, CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnimNode::IsScale()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CModel::CalcNodeWorldMatrix(float (*) [4], CChara::CNode*)
{
	// TODO
}

// Global Chara object - composite structure with nested base objects
struct CharaGlobal {
	struct Field0 {
		struct Object {
			struct BaseObject {
				CFlatRuntime::CObject object;
			} base_object;
		} object;
	} field0_0x0;
} Chara;

extern "C" char __vt__8CManager[];
extern "C" char lbl_801FCD24[];

/*
 * --INFO--
 * PAL Address: 0x80073ad4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_chara_cpp(void)
{
	*(void**)&Chara = __vt__8CManager;
	*(void**)&Chara = lbl_801FCD24;
}
