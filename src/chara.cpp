#include "ffcc/chara.h"
#include "ffcc/cflat_runtime.h"

#include <math.h>
#include <string.h>

extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, void*);
extern "C" void freeFurTex__6CCharaFv();
extern "C" void InitFurTexBuffer__6CCharaFv(CChara*);
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);
extern "C" void Calc__Q26CChara5CMeshFPQ26CChara6CModel(void*, void*);
extern "C" void __dla__FPv(void*);

struct CharaGlobal;
extern CharaGlobal Chara;

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
	InitFurTexBuffer__6CCharaFv(this);
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
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CChara::CModel::CRefData::CRefData()
{
	// TODO
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
	void** data = (void**)((u8*)this + 0xA4);
	if (data[0] != 0) {
		__dla__FPv(data[0]);
		data[0] = 0;
	}
	if (data[1] != 0) {
		__dla__FPv(data[1]);
		data[1] = 0;
	}
	if (data[2] != 0) {
		__dla__FPv(data[2]);
		data[2] = 0;
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

	worldBaseMtx[0][0] = localMtx[0][0];
	worldBaseMtx[1][0] = localMtx[1][0];
	worldBaseMtx[2][0] = localMtx[2][0];
	worldBaseMtx[0][1] = localMtx[0][1];
	worldBaseMtx[1][1] = localMtx[1][1];
	worldBaseMtx[2][1] = localMtx[2][1];
	worldBaseMtx[0][2] = localMtx[0][2];
	worldBaseMtx[1][2] = localMtx[1][2];
	worldBaseMtx[2][2] = localMtx[2][2];
	worldBaseMtx[0][3] = 0.0f;
	worldBaseMtx[1][3] = 0.0f;
	worldBaseMtx[2][3] = 0.0f;

	PSMTXIdentity(drawMtx);
	drawMtx[0][3] = localMtx[0][3];
	drawMtx[1][3] = localMtx[1][3];
	drawMtx[2][3] = localMtx[2][3];

	calcMatrix();
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
	void* refData = *(void**)((u8*)this + 0xA4);
	void* mesh = *(void**)((u8*)this + 0xAC);
	u32 posQuant = *(u32*)((u8*)refData + 0x28);
	u32 normQuant = *(u32*)((u8*)refData + 0x2C);
	u16 meshCount = *(u16*)((u8*)refData + 0xA);
	u32 i = 0;

	gqrInit__6CCharaFUlUlUl(&Chara, (posQuant << 24) | 0x70000 | (posQuant << 8) | 7,
	                        (normQuant << 24) | 0x70000 | (normQuant << 8) | 7, 0x0C070C07);

	while (i < meshCount) {
		Calc__Q26CChara5CMeshFPQ26CChara6CModel(mesh, this);
		mesh = (u8*)mesh + 0x14;
		i++;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * PAL Address: 0x8007104c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::SetMatrix(float (*mtx) [4])
{
	PSMTXCopy(mtx, (float(*)[4])((u8*)this + 0x14));
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
void CChara::CModel::SearchNode(char*)
{
	// Return type is unknown in this decomp state.
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
void CChara::CModel::SearchNodeSk(char*)
{
	// Return type is unknown in this decomp state.
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
void CChara::CModel::GetDispIndex(CChara::CNode*)
{
	// Return type is unknown in this decomp state.
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
	memset(this, 0, 0xC0);
	*(u8*)((u8*)this + 0x80) = (*(u8*)((u8*)this + 0x80) & 0x7F) | 0x80;
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
 * PAL Address: 0x8006ed08
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CMesh::CRefData::CRefData()
{
	memset(this, 0, 0x64);
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
	u8* const bytes = reinterpret_cast<u8*>(this);

	*reinterpret_cast<void**>(bytes + 0) = 0;
	*reinterpret_cast<s32*>(bytes + 4) = 0;
	*reinterpret_cast<s16*>(bytes + 8) = -1;
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
	void** data = (void**)this;
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

struct CharaGlobal {
	void* vtable;
	u8 padding[0x264];
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
