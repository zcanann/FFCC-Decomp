#include "ffcc/cflat_runtime2.h"
#include "ffcc/baseobj.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include <math.h>
#include <string.h>

extern "C" void reset__6CAStarFv(void*);
extern "C" int __cntlzw(unsigned int);
extern "C" void Create__9CGBaseObjFv(CGBaseObj*);
extern "C" void Destroy__9CGBaseObjFv(CGBaseObj*);

extern unsigned char Pad[];
extern unsigned char GraphicsPcs[];
extern unsigned char CameraPcs[];
extern unsigned char DbgMenuPcs[];
extern CPartMng PartMng;

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
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime2::CFlatRuntime2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime2::~CFlatRuntime2()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::getNumFreeObject(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::getFreeObject(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::intToClass(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGObjFirst()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGObjNext(CGObject*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGQuadObjFirst()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGQuadObjNext(CGQuadObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGMonObjFirst()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGMonObjNext(CGMonObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGItemObjFirst()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::FindGItemObjNext(CGItemObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::Destroy()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::loadLayerASync(int, char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::PutParticle(int, Vec&, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::PutParticleWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::ResetParticleWork(int, int)
{
	// TODO
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
void CFlatRuntime2::SysControl(int, int)
{
	// TODO
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
