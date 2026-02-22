#include "ffcc/cflat_runtime2.h"
#include "ffcc/baseobj.h"
#include "ffcc/monobj.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include <math.h>
#include <string.h>

extern "C" void reset__6CAStarFv(void*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" int __cntlzw(unsigned int);
extern "C" void Create__9CGBaseObjFv(CGBaseObj*);
extern "C" void Destroy__9CGBaseObjFv(CGBaseObj*);
extern "C" void Destroy__12CFlatRuntimeFv(CFlatRuntime*);
extern "C" void Destroy__9CFlatDataFv(void*);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void AfterFrame__12CFlatRuntimeFi(CFlatRuntime*, int);
extern "C" void __dt__9CFlatDataFv(void*, int);
extern "C" void __dt__12CFlatRuntimeFv(CFlatRuntime*, int);
extern "C" void Close__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void* __vt__13CFlatRuntime2[];
extern "C" CFlatRuntime2* __ct__13CFlatRuntime2Fv(CFlatRuntime2*);
extern "C" void __dt__13CFlatRuntime2Fv(void*);
extern "C" CFlatRuntime* __ct__12CFlatRuntimeFv(CFlatRuntime*);
extern "C" void __ct__9CFlatDataFv(void*);
extern "C" void __ct__8CGMonObjFv(CGMonObj*);
extern "C" void __ct__10CGPartyObjFv(CGPartyObj*);
extern "C" void __ct__9CGItemObjFv(CGItemObj*);
extern "C" void __ct__8CGObjectFv(CGObject*);
extern "C" void __ct__9CGQuadObjFv(CGQuadObj*);
extern "C" void __ct__9CGBaseObjFv(CGBaseObj*);
extern "C" void pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(CPartMng*, int, int, PPPCREATEPARAM*, int);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void* Open__5CFileFPcUlQ25CFile3PRI(void*, char*, unsigned long, int);
extern "C" void ReadASync__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void ClrBattleItem__8CMenuPcsFv(void*);
extern "C" void ChangeMogMode__6CCharaFi(void*, int);
extern "C" void TimeMogFur__6CCharaFv(void*);
extern "C" void LoadLogoWaitingData__5CGameFv(void*);

extern unsigned char Pad[];
extern unsigned char MenuPcs[];
extern unsigned char Chara[];
extern unsigned char GraphicsPcs[];
extern unsigned char CameraPcs[];
extern unsigned char DbgMenuPcs[];
extern unsigned char CFlat[];
extern unsigned char m_objItem[];
extern unsigned char m_objParty[];
extern unsigned char m_objMon[];
extern CPartMng PartMng;
extern "C" void* __vt__Q212CFlatRuntime7CObject[];
extern "C" void* __vt__9CGBaseObj[];
extern "C" void* __vt__9CGQuadObj[];
extern "C" void* __vt__8CGObject[];
extern "C" void* __vt__8CGPrgObj[];
extern "C" void* __vt__9CGItemObj[];
extern "C" void* __vt__10CGCharaObj[];
extern "C" void* __vt__8CGMonObj[];
extern "C" void* __vt__10CGPartyObj[];

template <int count>
class CLine;

template <>
class CLine<64>
{
public:
	CLine();
	void Draw();

private:
	u8 m_0x00[0x18];
	u32 m_numPoints;
	u8 m_0x1C[0x14];
	Vec m_points[64];
};

CLine<64>::CLine()
{
	m_numPoints = 0;
}

void CLine<64>::Draw()
{
	if (m_numPoints == 0) {
		return;
	}

	GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(m_numPoints & 0xFFFF));
	u32 i = 0;
	u8* it = reinterpret_cast<u8*>(this);
	while (i < m_numPoints) {
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x30);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x34);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x38);
		it += 0xC;
		i++;
	}

	const float yOffset = 1.0f;
	GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(m_numPoints & 0xFFFF));
	i = 0;
	it = reinterpret_cast<u8*>(this);
	while (i < m_numPoints) {
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x30);
		GXWGFifo.f32 = yOffset + *reinterpret_cast<float*>(it + 0x34);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x38);
		it += 0xC;
		i++;
	}

	GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, (u16)((m_numPoints & 0x7FFF) << 1));
	i = 0;
	it = reinterpret_cast<u8*>(this);
	while (i < m_numPoints) {
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x30);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x34);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x38);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x30);
		GXWGFifo.f32 = yOffset + *reinterpret_cast<float*>(it + 0x34);
		GXWGFifo.f32 = *reinterpret_cast<float*>(it + 0x38);
		it += 0xC;
		i++;
	}
}

namespace {

typedef unsigned char u8;

static inline float& ParticleWorkSpeed(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x16F0);
}

static inline float* &ParticleWorkScalePtr(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float**>(reinterpret_cast<u8*>(runtime) + 0x16D4);
}

static inline float& ParticleWorkScaleX(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1758);
}

static inline float& ParticleWorkScaleY(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x175C);
}

static inline float& ParticleWorkScaleZ(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1760);
}

static inline float* &ParticleWorkTargetPtr(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float**>(reinterpret_cast<u8*>(runtime) + 0x16D8);
}

static inline float& ParticleWorkTargetX(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1764);
}

static inline float& ParticleWorkTargetY(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1768);
}

static inline float& ParticleWorkTargetZ(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x176C);
}

static inline float*& ParticleWorkPosPtr(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float**>(reinterpret_cast<u8*>(runtime) + 0x16CC);
}

static inline float*& ParticleWorkPosVecPtr(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float**>(reinterpret_cast<u8*>(runtime) + 0x16D0);
}

static inline float& ParticleWorkPosX(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1740);
}

static inline float& ParticleWorkPosY(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1744);
}

static inline float& ParticleWorkPosZ(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1748);
}

static inline float& ParticleWorkPosAngle(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1750);
}

static inline float& ParticleWorkPosVecBase(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x174C);
}

static inline CFlatRuntime::CObject*& ParticleWorkBind(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<CFlatRuntime::CObject**>(reinterpret_cast<u8*>(runtime) + 0x16E0);
}

static inline CFlatRuntime::CObject*& ParticleWorkTrace(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<CFlatRuntime::CObject**>(reinterpret_cast<u8*>(runtime) + 0x16E4);
}

static inline int& ParticleWorkColor0(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x16E8);
}

static inline int& ParticleWorkColor1(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x16EC);
}

static inline float& ParticleWorkColorLerp(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x16F4);
}

static inline int& ParticleWorkSeNo(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x16FC);
}

static inline u8& ParticleWorkSeKind(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(runtime) + 0x1701);
}

static inline int& ParticleWorkSeParam(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x1704);
}

static inline int& ParticleWorkParamNo(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x1710);
}

static inline short& ParticleWorkParamId(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<short*>(reinterpret_cast<u8*>(runtime) + 0x1714);
}

static inline int& ParticleWorkNoHi(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x1738);
}

static inline unsigned int& ParticleWorkNoLo(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x173C);
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x8006a058
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGBaseObj::InitFinished()
{
}

/*
 * --INFO--
 * PAL Address: 0x8006E12C
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime2::CFlatRuntime2()
{
	u8* runtime = reinterpret_cast<u8*>(this);

	__ct__12CFlatRuntimeFv(reinterpret_cast<CFlatRuntime*>(this));
	*reinterpret_cast<void***>(runtime) = __vt__13CFlatRuntime2;

	*reinterpret_cast<int*>(runtime + 0x170C) = -1;
	*reinterpret_cast<int*>(runtime + 0x16FC) = -1;
	runtime[0x1700] = 0;
	runtime[0x1701] = 1;
	*reinterpret_cast<int*>(runtime + 0x1704) = 0;
	runtime[0x1702] = 0;
	*reinterpret_cast<int*>(runtime + 0x1708) = 0x1E;
	*reinterpret_cast<int*>(runtime + 0x1710) = 0;
	*reinterpret_cast<short*>(runtime + 0x1714) = 0;
	runtime[0x1716] = 0;
	runtime[0x1717] = 0;
	*reinterpret_cast<int*>(runtime + 0x16CC) = 0;
	*reinterpret_cast<int*>(runtime + 0x16D0) = 0;
	*reinterpret_cast<int*>(runtime + 0x16D4) = 0;
	*reinterpret_cast<int*>(runtime + 0x16D8) = 0;
	*reinterpret_cast<int*>(runtime + 0x16DC) = 0;
	*reinterpret_cast<int*>(runtime + 0x16E0) = 0;
	*reinterpret_cast<int*>(runtime + 0x16E4) = 0;
	*reinterpret_cast<int*>(runtime + 0x16E8) = 0;
	*reinterpret_cast<int*>(runtime + 0x16EC) = 0;
	*reinterpret_cast<float*>(runtime + 0x16F0) = 1.0f;
	*reinterpret_cast<float*>(runtime + 0x16F4) = 1.0f;
	runtime[0x16F8] = 0;

	for (int i = 0; i < 16; i++) {
		*reinterpret_cast<u32*>(runtime + 0x1BDC + i * 0xB14 + 0x18) = 0;
	}

	__ct__9CFlatDataFv(runtime + 0xCF20);
	*reinterpret_cast<int*>(runtime + 0x10418) = 0;
	*reinterpret_cast<int*>(runtime + 0x129C) = 0;
	*reinterpret_cast<int*>(runtime + 0x12A0) = 0;
	*reinterpret_cast<int*>(runtime + 0x12A4) = -1;
	runtime[0x12E4] = (runtime[0x12E4] & 0xFB) | 4;
	*reinterpret_cast<int*>(runtime + 0x10400) = 0;
	*reinterpret_cast<int*>(runtime + 0x10408) = 0;
	memset(runtime + 0x15CC, 0, 0x100);
	memset(runtime + 0x1770, 0, 0x60);

	resetChangeScript();
	memset(runtime + 0x12F0, 0, 0x48);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime2::~CFlatRuntime2()
{
	u8* runtime = reinterpret_cast<u8*>(this);
	*reinterpret_cast<void***>(runtime) = __vt__13CFlatRuntime2;
	AfterFrame__12CFlatRuntimeFi(reinterpret_cast<CFlatRuntime*>(this), 1);
	__dt__9CFlatDataFv(runtime + 0xCF20, -1);
	__dt__12CFlatRuntimeFv(reinterpret_cast<CFlatRuntime*>(this), 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime2::CParticleWork::CParticleWork()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8006E864
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_cflat_runtime2_cpp(void)
{
	__ct__13CFlatRuntime2Fv(reinterpret_cast<CFlatRuntime2*>(CFlat));
	__register_global_object(CFlat, reinterpret_cast<void*>(__dt__13CFlatRuntime2Fv), CFlat - 0x20);

	__construct_array(CFlat + 0x10440, reinterpret_cast<void (*)(void*)>(__ct__9CGBaseObjFv), 0, 0x50, 0x28);
	__construct_array(CFlat + 0x110C0, reinterpret_cast<void (*)(void*)>(__ct__9CGQuadObjFv), 0, 0x18, 0xAC);
	__construct_array(CFlat + 0x120E0, reinterpret_cast<void (*)(void*)>(__ct__8CGObjectFv), 0, 0x38, 0x518);
	__construct_array(m_objItem, reinterpret_cast<void (*)(void*)>(__ct__9CGItemObjFv), 0, 0x20, 0x57C);
	__construct_array(m_objParty, reinterpret_cast<void (*)(void*)>(__ct__10CGPartyObjFv), 0, 4, 0x6F8);
	__construct_array(m_objMon, reinterpret_cast<void (*)(void*)>(__ct__8CGMonObjFv), 0, 0x40, 0x740);
}

/*
 * --INFO--
 * PAL Address: 0x8006E960
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__8CGMonObjFv(CGMonObj* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGObject;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGPrgObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__10CGCharaObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGMonObj;
}

/*
 * --INFO--
 * PAL Address: 0x8006E9BC
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__10CGPartyObjFv(CGPartyObj* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGObject;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGPrgObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__10CGCharaObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__10CGPartyObj;
}

/*
 * --INFO--
 * PAL Address: 0x8006EA18
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__9CGItemObjFv(CGItemObj* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGObject;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGPrgObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGItemObj;
}

/*
 * --INFO--
 * PAL Address: 0x8006EA68
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__8CGObjectFv(CGObject* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__8CGObject;
}

/*
 * --INFO--
 * PAL Address: 0x8006EAA0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__9CGQuadObjFv(CGQuadObj* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGQuadObj;
}

/*
 * --INFO--
 * PAL Address: 0x8006EAD8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__9CGBaseObjFv(CGBaseObj* obj)
{
	u8* self = reinterpret_cast<u8*>(obj);
	*reinterpret_cast<void***>(self + 0x48) = __vt__Q212CFlatRuntime7CObject;
	self[0x38] &= 0xEF;
	*reinterpret_cast<void***>(self + 0x48) = __vt__9CGBaseObj;
}

/*
 * --INFO--
 * PAL Address: 0x8006E09C
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMemory::CStage* CFlatRuntime2::getStage()
{
	return Game.game.m_mainStage;
}

/*
 * --INFO--
 * PAL Address: 0x8006E088
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMemory::CStage* CFlatRuntime2::getDebugStage()
{
	return Game.game.m_debugStage;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onNewObject(CFlatRuntime::CObject* object)
{
	CGBaseObj* baseObj = reinterpret_cast<CGBaseObj*>(object);
	u8& isActive = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(baseObj) + 0x4C);
	isActive = (isActive & 0x7F) | 0x80;
	Create__9CGBaseObjFv(baseObj);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onDeleteObject(CFlatRuntime::CObject* object)
{
	CGBaseObj* baseObj = reinterpret_cast<CGBaseObj*>(object);
	Destroy__9CGBaseObjFv(baseObj);
	u8& isActive = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(baseObj) + 0x4C);
	isActive &= 0x7F;
}

/*
 * --INFO--
 * PAL Address: 0x8006DA68
 * PAL Size: 1452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CFlatRuntime2::getNumFreeObject(int classType)
{
	unsigned int count = 0;
	unsigned char* objects;
	int stride;
	int objectCount;

	if (classType == 3) {
		objects = m_objParty;
		stride = 0x6F8;
		objectCount = 4;
	} else if (classType < 3) {
		if (classType == 1) {
			objects = CFlat + 0x110C0;
			stride = 0xAC;
			objectCount = 0x18;
		} else if (classType < 1) {
			if (classType < 0) {
				return 0;
			}
			objects = CFlat + 0x10440;
			stride = 0x50;
			objectCount = 0x28;
		} else {
			objects = CFlat + 0x120E0;
			stride = 0x518;
			objectCount = 0x38;
		}
	} else if (classType == 5) {
		objects = m_objItem;
		stride = 0x57C;
		objectCount = 0x20;
	} else if (classType < 5) {
		objects = m_objMon;
		stride = 0x740;
		objectCount = 0x40;
	} else {
		return 0;
	}

	for (int i = 0; i < objectCount; i++) {
		if (*reinterpret_cast<signed char*>(objects + 0x4C) >= 0) {
			count++;
		}
		objects += stride;
	}

	return count;
}

/*
 * --INFO--
 * PAL Address: 0x8006D868
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObject* CFlatRuntime2::getFreeObject(int classType)
{
	unsigned char* objects;
	int stride;
	int objectCount;

	if (classType == 3) {
		objects = m_objParty;
		stride = 0x6F8;
		objectCount = 4;
	} else if (classType < 3) {
		if (classType == 1) {
			objects = CFlat + 0x110C0;
			stride = 0xAC;
			objectCount = 0x18;
		} else if (classType < 1) {
			if (classType < 0) {
				return 0;
			}
			objects = CFlat + 0x10440;
			stride = 0x50;
			objectCount = 0x28;
		} else {
			objects = CFlat + 0x120E0;
			stride = 0x518;
			objectCount = 0x38;
		}
	} else if (classType == 5) {
		objects = m_objItem;
		stride = 0x57C;
		objectCount = 0x20;
	} else if (classType < 5) {
		objects = m_objMon;
		stride = 0x740;
		objectCount = 0x40;
	} else {
		return 0;
	}

	for (int i = 0; i < objectCount; i++) {
		if (*reinterpret_cast<signed char*>(objects + 0x4C) >= 0) {
			return reinterpret_cast<CGObject*>(objects);
		}
		objects += stride;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006D79C
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CFlatRuntime2::intToClass(int classId)
{
	const int classType = classId >> 8;
	const unsigned int objectIndex = static_cast<unsigned int>(classId) & 0xFF;
	const int slot = static_cast<int>(objectIndex) - 1;

	if (classType == 3) {
		return m_objParty + slot * 0x6F8;
	}

	if (classType > 2) {
		if (classType == 5) {
			return m_objItem + slot * 0x57C;
		}
		if (classType > 4) {
			return this;
		}
		return m_objMon + slot * 0x740;
	}

	if (classType == 1) {
		return CFlat + 0x110C0 + slot * 0xAC;
	}
	if (classType < 1) {
		if (classType < 0) {
			return this;
		}
		return CFlat + 0x10440 + slot * 0x50;
	}

	return CFlat + 0x120E0 + slot * 0x518;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::Frame(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::Load(char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8006CADC
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObject* CFlatRuntime2::FindGObjFirst()
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 5) == 5) {
					return reinterpret_cast<CGObject*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006CA38
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGObject* CFlatRuntime2::FindGObjNext(CGObject* gObject)
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gObject)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 5) == 5) {
					return reinterpret_cast<CGObject*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGBaseObjFirst()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGBaseObjNext(CGBaseObj*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8006C994
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGQuadObj* CFlatRuntime2::FindGQuadObjFirst()
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 3) == 3) {
					return reinterpret_cast<CGQuadObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C8F4
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGQuadObj* CFlatRuntime2::FindGQuadObjNext(CGQuadObj* gQuadObj)
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gQuadObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 3) == 3) {
					return reinterpret_cast<CGQuadObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C84C
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGMonObj* CFlatRuntime2::FindGMonObjFirst()
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 0xAD) == 0xAD) {
					return reinterpret_cast<CGMonObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C7A8
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGMonObj* CFlatRuntime2::FindGMonObjNext(CGMonObj* gMonObj)
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gMonObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 0xAD) == 0xAD) {
					return reinterpret_cast<CGMonObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C700
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGItemObj* CFlatRuntime2::FindGItemObjFirst()
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 0x1D) == 0x1D) {
					return reinterpret_cast<CGItemObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C65C
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGItemObj* CFlatRuntime2::FindGItemObjNext(CGItemObj* gItemObj)
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gItemObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & 0x1D) == 0x1D) {
					return reinterpret_cast<CGItemObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006C5BC
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::Destroy()
{
	Destroy__12CFlatRuntimeFv(reinterpret_cast<CFlatRuntime*>(this));
	Destroy__9CFlatDataFv(reinterpret_cast<u8*>(this) + 0xCF20);

	u8* layer = reinterpret_cast<u8*>(this) + 0x1770;
	for (int i = 0; i < 8; i++, layer += 0xC) {
		void* fileHandle = *reinterpret_cast<void**>(layer + 8);
		if (fileHandle != 0) {
			Close__5CFileFPQ25CFile7CHandle(&File, fileHandle);
			*reinterpret_cast<void**>(layer + 8) = 0;
		}

		void* textureSet = *reinterpret_cast<void**>(layer + 4);
		if (textureSet != 0) {
			(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
			*reinterpret_cast<void**>(layer + 4) = 0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::AddDebugDrawCC(Vec*, Vec*, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::CcClass2D(int, int, Vec*, float, float, int, CGObject **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::loadLayer(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CFlatRuntime2::isLoadLayerASyncCompleted(int layerNo)
{
	unsigned int state = *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x1778 + layerNo * 0xC);
	return static_cast<unsigned int>(__cntlzw(state)) >> 5;
}

/*
 * --INFO--
 * PAL Address: 0x8006AF5C
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::loadLayerASync(int layerNo, char* fileName)
{
	const int layerOffset = layerNo * 0xC;
	u8* layer = reinterpret_cast<u8*>(this) + 0x1770 + layerOffset;

	void* fileHandle = *reinterpret_cast<void**>(layer + 8);
	if (fileHandle != 0) {
		Close__5CFileFPQ25CFile7CHandle(&File, fileHandle);
		*reinterpret_cast<void**>(layer + 8) = 0;
	}

	void* textureSet = *reinterpret_cast<void**>(layer + 4);
	if (textureSet != 0) {
		(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
		*reinterpret_cast<void**>(layer + 4) = 0;
	}

	char path[0x104];
	sprintf(path, "dvd:/%s/%s.tex", GetLangString__5CGameFv(&Game.game), fileName);

	fileHandle = Open__5CFileFPcUlQ25CFile3PRI(&File, path, 0, 0);
	*reinterpret_cast<void**>(layer + 8) = fileHandle;
	if (fileHandle != 0) {
		ReadASync__5CFileFPQ25CFile7CHandle(&File, fileHandle);
	}

	*reinterpret_cast<int*>(layer) = *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0xE4);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::drawLayer(int, char*, int, int, int, int, int, int, float, float, _GXColor*, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8006A53C
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::PutParticle(int workNo, Vec& pos, float scale)
{
	u8* runtime = reinterpret_cast<u8*>(this);

	ParticleWorkPosPtr(this) = 0;
	ParticleWorkPosVecPtr(this) = 0;
	ParticleWorkScalePtr(this) = 0;
	ParticleWorkTargetPtr(this) = 0;
	*reinterpret_cast<int*>(runtime + 0x16DC) = 0;
	ParticleWorkBind(this) = 0;
	ParticleWorkTrace(this) = 0;
	ParticleWorkColor0(this) = 0;
	ParticleWorkColor1(this) = 0;
	ParticleWorkSpeed(this) = 1.0f;
	ParticleWorkColorLerp(this) = 1.0f;
	runtime[0x16F8] = 0;
	memset(runtime + 0x16F9, 0, 3);

	ParticleWorkSeNo(this) = -1;
	runtime[0x1700] = 0;
	ParticleWorkSeKind(this) = 1;
	runtime[0x1702] = 0;
	runtime[0x1703] = 0;
	ParticleWorkSeParam(this) = 0;
	*reinterpret_cast<int*>(runtime + 0x1708) = 0x1E;
	*reinterpret_cast<int*>(runtime + 0x170C) = -1;
	ParticleWorkParamNo(this) = 0;
	ParticleWorkParamId(this) = 0;
	runtime[0x1716] = 0;
	runtime[0x1717] = 0;
	memset(runtime + 0x1718, 0, 0x20);

	runtime[0x16F8] = 1;
	ParticleWorkNoHi(this) = workNo >> 8;
	*reinterpret_cast<int*>(runtime + 0x16DC) = 0;
	ParticleWorkNoLo(this) = static_cast<unsigned int>(workNo) & 0xFF;

	ParticleWorkPosX(this) = pos.x;
	ParticleWorkPosY(this) = pos.y;
	ParticleWorkPosZ(this) = pos.z;
	ParticleWorkPosAngle(this) = 0.0f;
	ParticleWorkPosPtr(this) = &ParticleWorkPosX(this);
	ParticleWorkPosVecPtr(this) = &ParticleWorkPosVecBase(this);

	ParticleWorkScaleX(this) = scale;
	ParticleWorkScaleY(this) = scale;
	ParticleWorkScaleZ(this) = scale;
	ParticleWorkScalePtr(this) = &ParticleWorkScaleX(this);

	pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(
		&PartMng, ParticleWorkNoHi(this), ParticleWorkNoLo(this),
		reinterpret_cast<PPPCREATEPARAM*>(reinterpret_cast<u8*>(this) + 0x16CC), 1);
}

/*
 * --INFO--
 * PAL Address: 0x8006A500
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::PutParticleWork()
{
	pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(
		&PartMng, ParticleWorkNoHi(this), ParticleWorkNoLo(this),
		reinterpret_cast<PPPCREATEPARAM*>(reinterpret_cast<u8*>(this) + 0x16CC), 1);
}

/*
 * --INFO--
 * PAL Address: 0x8006A350
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::ResetParticleWork(int workNo, int arg)
{
	u8* runtime = reinterpret_cast<u8*>(this);

	ParticleWorkPosPtr(this) = 0;
	ParticleWorkPosVecPtr(this) = 0;
	ParticleWorkScalePtr(this) = 0;
	ParticleWorkTargetPtr(this) = 0;
	*reinterpret_cast<int*>(runtime + 0x16DC) = 0;
	ParticleWorkBind(this) = 0;
	ParticleWorkTrace(this) = 0;
	ParticleWorkColor0(this) = 0;
	ParticleWorkColor1(this) = 0;
	ParticleWorkSpeed(this) = 1.0f;
	ParticleWorkColorLerp(this) = 1.0f;
	runtime[0x16F8] = 0;
	memset(runtime + 0x16F9, 0, 3);

	ParticleWorkSeNo(this) = -1;
	runtime[0x1700] = 0;
	ParticleWorkSeKind(this) = 1;
	runtime[0x1702] = 0;
	runtime[0x1703] = 0;
	ParticleWorkSeParam(this) = 0;
	*reinterpret_cast<int*>(runtime + 0x1708) = 0x1E;
	*reinterpret_cast<int*>(runtime + 0x170C) = -1;
	ParticleWorkParamNo(this) = 0;
	ParticleWorkParamId(this) = 0;
	runtime[0x1716] = 0;
	runtime[0x1717] = 0;
	memset(runtime + 0x1718, 0, 0x20);

	runtime[0x16F8] = 1;
	ParticleWorkNoHi(this) = workNo >> 8;
	*reinterpret_cast<int*>(runtime + 0x16DC) = arg;
	ParticleWorkNoLo(this) = static_cast<unsigned int>(workNo) & 0xFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::SetParticleWorkNo(int workNo)
{
	ParticleWorkNoHi(this) = workNo >> 8;
	ParticleWorkNoLo(this) = static_cast<unsigned int>(workNo) & 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x8006A2FC
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkPos(Vec& vec, float angle)
{
	ParticleWorkPosX(this) = vec.x;
	ParticleWorkPosY(this) = vec.y;
	ParticleWorkPosZ(this) = vec.z;
	ParticleWorkPosAngle(this) = 180.0f * angle / 3.1415927f;
	ParticleWorkPosPtr(this) = &ParticleWorkPosX(this);
	ParticleWorkPosVecPtr(this) = &ParticleWorkPosVecBase(this);
}

/*
 * --INFO--
 * PAL Address: 0x8006A2D8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkTarget(Vec& vec)
{
	ParticleWorkTargetX(this) = vec.x;
	ParticleWorkTargetY(this) = vec.y;
	ParticleWorkTargetZ(this) = vec.z;
	ParticleWorkTargetPtr(this) = &ParticleWorkTargetX(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::SetParticleWorkVector(float angle1, float angle2)
{
	double cosAngle2 = cos(angle2);
	double sinAngle1 = sin(angle1);
	ParticleWorkTargetX(this) = static_cast<float>(sinAngle1 * static_cast<double>(static_cast<float>(cosAngle2))) + ParticleWorkPosX(this);

	double sinAngle2 = sin(angle2);
	ParticleWorkTargetY(this) = ParticleWorkPosY(this) + static_cast<float>(sinAngle2);

	cosAngle2 = cos(angle2);
	double cosAngle1 = cos(angle1);
	ParticleWorkTargetZ(this) = static_cast<float>(cosAngle1 * static_cast<double>(static_cast<float>(cosAngle2))) + ParticleWorkPosZ(this);
	ParticleWorkTargetPtr(this) = &ParticleWorkTargetX(this);
}

/*
 * --INFO--
 * PAL Address: 0x8006A1F8
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkScale(float scale)
{
	ParticleWorkScaleZ(this) = scale;
	ParticleWorkScaleY(this) = scale;
	ParticleWorkScaleX(this) = scale;
	ParticleWorkScalePtr(this) = &ParticleWorkScaleX(this);
}

/*
 * --INFO--
 * PAL Address: 0x8006A1E8
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkCol(int color0, int color1, float lerp)
{
	ParticleWorkColor0(this) = color0;
	ParticleWorkColor1(this) = color1;
	ParticleWorkColorLerp(this) = lerp;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::SetParticleWorkTrace(CFlatRuntime::CObject* object)
{
	ParticleWorkTrace(this) = object;
}

/*
 * --INFO--
 * PAL Address: 0x8006A1D8
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkSpeed(float speed)
{
	ParticleWorkSpeed(this) = speed;
}

/*
 * --INFO--
 * PAL Address: 0x8006A1D0
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkBind(CFlatRuntime::CObject* object)
{
	ParticleWorkBind(this) = object;
}

/*
 * --INFO--
 * PAL Address: 0x8006A1B0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkParam(int paramNo, CFlatRuntime::CObject* object)
{
	ParticleWorkParamNo(this) = paramNo;
	if (object != 0) {
		ParticleWorkParamId(this) = *reinterpret_cast<short*>(reinterpret_cast<u8*>(object) + 0x30);
	} else {
		ParticleWorkParamId(this) = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006A1A0
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SetParticleWorkSe(int seNo, int seKind, int seParam)
{
	ParticleWorkSeNo(this) = seNo;
	ParticleWorkSeKind(this) = static_cast<u8>(seKind);
	ParticleWorkSeParam(this) = seParam;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::GetFreeParticleSlot()
{
	PartMng.pppGetFreeSlot();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::EndParticleSlot(int slotNo, int forceEnd)
{
	if (slotNo != 0) {
		PartMng.pppEndSlot(slotNo, forceEnd);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::EndParticle(CCharaPcs::CHandle* handle)
{
	if (handle != 0) {
		PartMng.pppEndCHandle(handle);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::DeleteParticleSlot(int slotNo, int forceDelete)
{
	if (slotNo != 0) {
		PartMng.pppDeleteSlot(slotNo, forceDelete);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::IgnoreParticle(int slotNo, CFlatRuntime::CObject* object)
{
	u8* ifDt = reinterpret_cast<u8*>(PartMng.pppGetIfDt(static_cast<short>(slotNo)));
	u8 count = ifDt[6];
	if (count < 0x10) {
		ifDt[6] = static_cast<u8>(count + 1);
		*reinterpret_cast<short*>(ifDt + 8 + count * 2) = object->m_particleId;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::initAllFinished()
{
	memset(reinterpret_cast<void*>(0x803001D8), 0, 0x90);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::reqFinished(int reqNo, CFlatRuntime::CObject* object)
{
	if (reqNo == 0xF) {
		typedef void (*ReqFinishFn)(CFlatRuntime::CObject*);
		ReqFinishFn fn = *reinterpret_cast<ReqFinishFn*>(*reinterpret_cast<u8**>(object) + 0x10);
		fn(object);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006FAE8
 * PAL Size: 640b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::SysControl(int controlNo, int controlValue)
{
	u8* runtime = reinterpret_cast<u8*>(this);
	const u8 value8 = static_cast<u8>(controlValue);

	switch (controlNo) {
	case 0:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0x7F) | ((value8 & 1) << 7));
		break;

	case 2:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xF7) | ((value8 & 1) << 3));
		break;

	case 3:
		*reinterpret_cast<unsigned int*>(runtime + 0x12E8) = static_cast<unsigned int>(controlValue);
		break;

	case 4:
		Game.game.m_gameWork.m_radarType = value8;
		break;

	case 5:
		*reinterpret_cast<unsigned int*>(runtime + 0x12EC) = static_cast<unsigned int>(controlValue);
		break;

	case 6:
	case 7:
	case 8:
	case 0xC:
	case 0xD:
	case 0xF:
	case 0x10:
	case 0x11:
	case 0x15:
	case 0x16: {
		u8* mon = m_objMon;
		for (int i = 0; i < 0x40; i++, mon += 0x740) {
			if ((*reinterpret_cast<unsigned int*>(mon) != 0) &&
			    ((controlValue == 0) || ((*reinterpret_cast<unsigned int*>(mon + 0x6EC) & static_cast<unsigned int>(controlValue)) != 0))) {
				reinterpret_cast<CGMonObj*>(mon)->sysControl(controlNo);
			}
		}
		break;
	}

	case 9:
		ClrBattleItem__8CMenuPcsFv(MenuPcs);
		break;

	case 0xA:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xEF) | ((value8 & 1) << 4));
		break;

	case 0xB:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xDF) | ((value8 & 1) << 5));
		break;

	case 0xE:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xFD) | ((value8 & 1) << 1));
		ChangeMogMode__6CCharaFi(Chara, controlValue);
		break;

	case 0x12:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xFE) | (value8 & 1));
		break;

	case 0x13: {
		u8* party = m_objParty;
		for (int i = 0; i < 4; i++, party += 0x6F8) {
			if (*reinterpret_cast<unsigned int*>(party) != 0) {
				reinterpret_cast<CGPartyObj*>(party)->sysControl(controlNo, controlValue);
			}
		}
		break;
	}

	case 0x14:
		TimeMogFur__6CCharaFv(Chara);
		break;

	case 0x17:
		*reinterpret_cast<unsigned int*>(Pad + 0x1C8) = static_cast<unsigned int>(controlValue);
		break;

	case 0x18:
		LoadLogoWaitingData__5CGameFv(&Game.game);
		break;

	case 0x19: {
		u8* party = m_objParty;
		for (int i = 0; i < 4; i++, party += 0x6F8) {
			if (*reinterpret_cast<unsigned int*>(party) != 0) {
				reinterpret_cast<CGCharaObj*>(party)->damageDelete();
			}
		}

		u8* mon = m_objMon;
		for (int i = 0; i < 0x40; i++, mon += 0x740) {
			if (*reinterpret_cast<unsigned int*>(mon) != 0) {
				reinterpret_cast<CGCharaObj*>(mon)->damageDelete();
			}
		}
		break;
	}

	case 0x1A:
		PartMng.pppDumpMngSt();
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006FAC4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime2::GetSysControl(int controlNo)
{
	if (controlNo != 3) {
		return 0;
	}

	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x12E8);
}

/*
 * --INFO--
 * PAL Address: 0x8006FA68
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::resetSpawnBit(int spawnBit)
{
	if (spawnBit == -1) {
		memset(reinterpret_cast<u8*>(this) + 0x12F0, 0, 0x48);
		return;
	}
	if (spawnBit < 0 || spawnBit > 8) {
		return;
	}

	u8* ptr = reinterpret_cast<u8*>(this) + (spawnBit << 3);
	*reinterpret_cast<int*>(ptr + 0x12F4) = 0;
	*reinterpret_cast<int*>(ptr + 0x12F0) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8006F88C
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::resetChangeScript()
{
	static const int clearDwordOffsets[] = {
		0x10404, 0x12A8, 0x12AC, 0x1BF4, 0x2708, 0x321C, 0x3D30, 0x4844, 0x5358, 0x5E6C,
		0x6980,  0x7494, 0x7FA8, 0x8ABC, 0x95D0, 0xA0E4, 0xABF8, 0xB70C, 0xC220,
	};

	u8* runtime = reinterpret_cast<u8*>(this);
	for (u32 i = 0; i < sizeof(clearDwordOffsets) / sizeof(clearDwordOffsets[0]); i++) {
		*reinterpret_cast<u32*>(runtime + clearDwordOffsets[i]) = 0;
	}

	for (int i = 0; i < 2; i++) {
		u8* block = runtime + i * 0xF8;
		for (int j = 0; j < 16; j++) {
			block[0x134C + j * 0x14] = 0xFF;
			block[0x134D + j * 0x14] = 0;
		}
	}

	*reinterpret_cast<u32*>(runtime + 0x1040C) = 0;
	*reinterpret_cast<u32*>(runtime + 0x10410) = 0;
	*reinterpret_cast<u32*>(runtime + 0x10414) = 0;

	runtime[0x12E4] |= 0x80;
	runtime[0x12E4] &= 0xDF;
	runtime[0x12E4] &= 0xEF;

	*reinterpret_cast<u32*>(runtime + 0x12E8) = 0;
	*reinterpret_cast<u32*>(runtime + 0x12EC) = 0;

	memset(runtime + 0x1041C, 0, 0x14);
	memset(reinterpret_cast<void*>(0x8030014C), 0, 0x8C);

	runtime[0x12E4] &= 0xFD;
	runtime[0x12E4] &= 0xF7;
	runtime[0x12E4] &= 0xFE;

	*reinterpret_cast<u32*>(Pad + 0x1C8) = 1;
	*reinterpret_cast<u32*>(GraphicsPcs + 0x44) = 0;
	*reinterpret_cast<u32*>(CameraPcs + 0x434) = 1;
	reset__6CAStarFv(DbgMenuPcs + 0x2A5C);
}

/*
 * --INFO--
 * PAL Address: 0x8006F850
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::ResetNewGame()
{
	resetChangeScript();
	memset(reinterpret_cast<u8*>(this) + 0x12F0, 0, 0x48);
}
