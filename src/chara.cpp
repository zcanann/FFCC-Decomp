#include "ffcc/chara.h"
#include "ffcc/cflat_runtime.h"

#include <math.h>
#include <string.h>

extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, void*);
extern "C" void freeFurTex__6CCharaFv();
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);
extern "C" void Calc__Q26CChara5CMeshFPQ26CChara6CModel(void*, void*);
extern "C" void __dla__FPv(void*);
extern "C" void __ct__7CVectorFv(void*);
extern "C" void SetTextureSet__12CMaterialSetFP11CTextureSet(CMaterialSet*, CTextureSet*);

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
 * PAL Address: 0x80072ea8
 * PAL Size: 1496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::Create(void* fileData, CMemory::CStage* stage)
{
	(void)fileData;
	(void)stage;
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
	setup();
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
	(void)dynData;
	(void)stage;
	void* ref = *(void**)((u8*)this + 0xA4);
	if (ref == 0) {
		return;
	}
	void** dynParams = (void**)((u8*)ref + 0x34);
	if (*dynParams != 0) {
		__dla__FPv(*dynParams);
		*dynParams = 0;
	}
	*(u32*)((u8*)ref + 0x38) = 0;
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
	void* ref = *(void**)((u8*)this + 0xA4);
	CNode* node = *(CNode**)((u8*)this + 0xA8);
	CMesh* mesh = *(CMesh**)((u8*)this + 0xAC);
	u32 nodeCount = *(u16*)((u8*)ref + 8);
	u32 meshCount = *(u16*)((u8*)ref + 0xA);
	for (u32 i = 0; i < nodeCount; i++) {
		s8 disp = *(s8*)((u8*)*(void**)node + 4);
		if (disp >= 0 && static_cast<u32>(disp) < meshCount) {
			*(void**)((u8*)node + 4) = (u8*)mesh + (disp * 0x14);
		}
		node = (CNode*)((u8*)node + 0xC0);
	}
	calcBindMatrix();
	AttachAnim(*(CAnim**)((u8*)this + 0xD0), -1, -1, 0);
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
void CChara::CModel::Duplicate(CMemory::CStage* stage)
{
	(void)stage;
	void* ref = *(void**)((u8*)this + 0xA4);
	if (ref == 0) {
		return;
	}
	u16 nodeCount = *(u16*)((u8*)ref + 8);
	u16 meshCount = *(u16*)((u8*)ref + 0xA);
	if (nodeCount != 0 && *(void**)((u8*)this + 0xA8) == 0) {
		*(void**)((u8*)this + 0xA8) = new u8[nodeCount * 0xC0];
		memset(*(void**)((u8*)this + 0xA8), 0, nodeCount * 0xC0);
	}
	if (meshCount != 0 && *(void**)((u8*)this + 0xAC) == 0) {
		*(void**)((u8*)this + 0xAC) = new u8[meshCount * 0x14];
		memset(*(void**)((u8*)this + 0xAC), 0, meshCount * 0x14);
	}
	setup();
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
	CNode* nodes = *(CNode**)((u8*)this + 0xA8);
	void* ref = *(void**)((u8*)this + 0xA4);
	u16 nodeCount = ref ? *(u16*)((u8*)ref + 8) : 0;
	for (u32 i = 0; i < nodeCount; i++) {
		CNode* node = (CNode*)((u8*)nodes + (i * 0xC0));
		void* nodeRef = *(void**)node;
		s16 parent = *(s16*)((u8*)nodeRef + 0x68);
		if (parent < 0) {
			PSMTXConcat((float(*)[4])((u8*)this + 0x44), (float(*)[4])((u8*)nodeRef + 0xC),
			            (float(*)[4])((u8*)node + 0x44));
		} else {
			CNode* parentNode = (CNode*)((u8*)nodes + (parent * 0xC0));
			PSMTXConcat((float(*)[4])((u8*)parentNode + 0x44), (float(*)[4])((u8*)nodeRef + 0xC),
			            (float(*)[4])((u8*)node + 0x44));
		}
		if (*(s8*)((u8*)nodeRef + 0x64) >= 0) {
			dynamics(node, 0);
		}
	}
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
	(void)frame;
	PSMTXIdentity(out);
	CNode* cur = node;
	while (cur != 0) {
		PSMTXConcat((float(*)[4])((u8*)cur + 0x44), out, out);
		s16 parent = *(s16*)((u8*)*(void**)cur + 0x68);
		if (parent < 0) {
			break;
		}
		cur = (CNode*)((u8*)*(void**)((u8*)this + 0xA8) + (parent * 0xC0));
	}
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
	if (node == 0) {
		return;
	}
	float* dynPos = (float*)((u8*)node + 0x84);
	float* worldPos = (float*)((u8*)node + 0x50);
	dynPos[0] += (worldPos[0] - dynPos[0]) * 0.5f;
	dynPos[1] += (worldPos[1] - dynPos[1]) * 0.5f;
	dynPos[2] += (worldPos[2] - dynPos[2]) * 0.5f;
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
	(void)view;
	(void)flags;
	(void)pass;
	calcSkin();
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
	(void)view;
	(void)zMode;
	calcSkin();
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
	m_anim = anim;
	m_animStart = static_cast<float>(startFrame < 0 ? 0 : startFrame);
	if (anim == 0) {
		m_animEnd = m_animStart;
	} else {
		m_animEnd = static_cast<float>(endFrame < 0 ? startFrame : endFrame);
	}
	*(u8*)((u8*)this + 0xA1) = static_cast<u8>(blendMode);
	m_time = m_animStart;
	m_curFrame = m_animStart;
	*(u16*)((u8*)this + 0xDA) = *(u16*)((u8*)this + 0xD8);
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
	(void)chunk;
	(void)type;
	(void)stage;
	void* modelRef = *(void**)((u8*)model + 0xA4);
	u16 idx = *(u16*)((u8*)modelRef + 8);
	void* nodeRefBase = *(void**)((u8*)modelRef + 0xC);
	void* nodeRef = (u8*)nodeRefBase + (idx * 0x94);
	*(void**)this = nodeRef;
	*(u16*)((u8*)nodeRef + 0) = idx;
	*(u8*)((u8*)nodeRef + 4) = 0xFF;
	*(u8*)((u8*)nodeRef + 0x64) = 0xFF;
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
	*(void**)this = *(void**)src;
	PSMTXCopy((float(*)[4])((u8*)src + 8), (float(*)[4])((u8*)this + 8));
	PSMTXCopy((float(*)[4])((u8*)src + 0x44), (float(*)[4])((u8*)this + 0x44));
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
	void* ref = *(void**)this;
	s16 parent = *(s16*)((u8*)ref + 0x68);
	if (parent < 0) {
		PSMTXCopy((float(*)[4])((u8*)ref + 0xC), (float(*)[4])((u8*)ref + 0x3C));
	} else {
		CNode* nodes = *(CNode**)((u8*)model + 0xA8);
		CNode* parentNode = (CNode*)((u8*)nodes + (parent * 0xC0));
		PSMTXConcat((float(*)[4])((u8*)*(void**)parentNode + 0x3C), (float(*)[4])((u8*)ref + 0xC),
		            (float(*)[4])((u8*)ref + 0x3C));
	}
	PSMTXCopy((float(*)[4])((u8*)ref + 0x3C), (float(*)[4])((u8*)this + 0x44));
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
	(void)chunk;
	(void)stage;
	void* modelRef = *(void**)((u8*)model + 0xA4);
	u16 idx = *(u16*)((u8*)modelRef + 0xA);
	void* meshRefBase = *(void**)((u8*)modelRef + 0x10);
	*(void**)this = (u8*)meshRefBase + (idx * 0x64);
	*(void**)((u8*)this + 4) = 0;
	*(void**)((u8*)this + 8) = 0;
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
	*(void**)this = *(void**)src;
	*(void**)((u8*)this + 4) = 0;
	*(void**)((u8*)this + 8) = 0;
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
	(void)model;
	void* ref = *(void**)this;
	u16 skinCount = *(u16*)((u8*)ref + 0x0A);
	if (skinCount == 0) {
		*(void**)((u8*)this + 4) = *(void**)((u8*)ref + 0x10);
		*(void**)((u8*)this + 8) = *(void**)((u8*)ref + 0x20);
	} else {
		*(void**)((u8*)this + 4) = 0;
		*(void**)((u8*)this + 8) = 0;
	}
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
