#include "ffcc/chara.h"
#include "ffcc/cflat_runtime.h"

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
	// TODO
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
	// TODO
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

extern "C" void* __vt__8CManager;
extern "C" void* lbl_801FCD24;

/*
 * --INFO--
 * PAL Address: 80073ad4
 * PAL Size: 32b
 */
extern "C" void __sinit_chara_cpp(void)
{
	u32* charaBase = (u32*)&Chara;
	*charaBase = (u32)&__vt__8CManager;
	*charaBase = (u32)&lbl_801FCD24;
}
