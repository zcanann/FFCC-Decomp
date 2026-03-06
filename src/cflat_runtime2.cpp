#include "ffcc/cflat_runtime2.h"
#include "ffcc/astar.h"
#include "ffcc/baseobj.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/monobj.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include "ffcc/ptrarray.h"
#include "ffcc/stopwatch.h"
#include "ffcc/textureman.h"
#include <math.h>
#include <string.h>

class CFont;

extern "C" void reset__6CAStarFv(void*);
extern "C" void drawAStar__6CAStarFv(void*);
extern "C" int printf(const char*, ...);
extern "C" int sprintf(char*, const char*, ...);
extern "C" int __cntlzw(unsigned int);
extern "C" void StaticFrame__10CGCharaObjFv();
extern "C" void CheckGameOver__10CGPartyObjFv();
extern "C" void DrawDebug__8CGObjectFP5CFont(CGObject*, CFont*);
extern "C" void DrawOmoideName__9CGItemObjFP5CFont(CGItemObj*, CFont*);
extern "C" void Create__9CGBaseObjFv(CGBaseObj*);
extern "C" void Destroy__9CGBaseObjFv(CGBaseObj*);
extern "C" void Frame__9CGBaseObjFv(CGBaseObj*);
extern "C" void Draw__9CGBaseObjFv(CGBaseObj*);
extern "C" void Frame__12CFlatRuntimeFii(CFlatRuntime*, int, int);
extern "C" void Create__12CFlatRuntimeFPv(CFlatRuntime*, void*);
extern "C" int CreateDebug__12CFlatRuntimeFPvi(CFlatRuntime*, void*, int);
extern "C" void Destroy__12CFlatRuntimeFv(CFlatRuntime*);
extern "C" void Destroy__9CFlatDataFv(void*);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void AfterFrame__12CFlatRuntimeFi(CFlatRuntime*, int);
extern "C" void __dt__9CFlatDataFv(void*, int);
extern "C" void __dt__12CFlatRuntimeFv(CFlatRuntime*, int);
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
extern "C" void Printf__7CSystemFPce(CSystem*, const char*, ...);
extern "C" void ClrBattleItem__8CMenuPcsFv(void*);
extern "C" void ChangeMogMode__6CCharaFi(void*, int);
extern "C" void TimeMogFur__6CCharaFv(void*);
extern "C" void LoadLogoWaitingData__5CGameFv(void*);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetZMode__5CFontFii(CFont*, int, int);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" void SetPosZ__5CFontFf(float, CFont*);
extern "C" int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic*, int&, int&, int&, int&, int);

extern unsigned char Pad[];
extern unsigned char MenuPcs[];
extern unsigned char Chara[];
extern unsigned char GraphicsPcs[];
extern unsigned char CameraPcs[];
extern unsigned char DbgMenuPcs[];
extern unsigned char MiniGamePcs[];
extern unsigned char CFlat[];
extern unsigned char m_objItem[];
extern unsigned char m_objParty[];
extern unsigned char m_objMon[];
extern CTextureMan TextureMan;
extern CTextureMan TextureMan;
extern "C" void* __vt__Q212CFlatRuntime7CObject[];
extern "C" void* __vt__9CGBaseObj[];
extern "C" void* __vt__9CGQuadObj[];
extern "C" void* __vt__8CGObject[];
extern "C" void* __vt__8CGPrgObj[];
extern "C" void* __vt__9CGItemObj[];
extern "C" void* __vt__10CGCharaObj[];
extern "C" void* __vt__8CGMonObj[];
extern "C" void* __vt__10CGPartyObj[];
extern "C" void move__8CGObjectFv(CGObject*);
extern "C" void objectCollision__8CGObjectFv(CGObject*);
extern "C" void bgCollision__8CGObjectFv(CGObject*);
extern "C" void update__8CGObjectFv(CGObject*);
extern "C" void hit__8CGObjectFv(CGObject*);
extern "C" void copy__8CGObjectFv(CGObject*);

static CGBaseObj* FindNextGBaseObjByCidMask(CFlatRuntime2* runtime, CFlatRuntime::CObject* object, unsigned int cidMask)
{
	typedef int (*GetCIDFn)(CFlatRuntime::CObject*);
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(runtime) + 0x1204);

	while (object != root) {
		if (object->m_classIndex >= 0) {
			const unsigned int flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				GetCIDFn getCID = reinterpret_cast<GetCIDFn>((*reinterpret_cast<void***>(object))[3]);
				if ((getCID(object) & cidMask) == cidMask) {
					return reinterpret_cast<CGBaseObj*>(object);
				}
			}
		}
		object = object->m_next;
	}

	return 0;
}

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

	u8* baseObj = runtime + 0x10440;
	for (int i = 0; i < 0x28; i++) {
		baseObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(baseObj + 0x30) = static_cast<u16>(i + 1);
		baseObj += 0x50;
	}

	u8* quadObj = runtime + 0x110C0;
	for (int i = 0; i < 0x18; i++) {
		quadObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(quadObj + 0x30) = static_cast<u16>((i + 1) | 0x100);
		quadObj += 0xAC;
	}

	u8* gObj = runtime + 0x120E0;
	for (int i = 0; i < 0x38; i++) {
		gObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(gObj + 0x30) = static_cast<u16>((i + 1) | 0x200);
		gObj += 0x518;
	}

	u8* partyObj = reinterpret_cast<u8*>(m_objParty);
	for (int i = 0; i < 4; i++) {
		partyObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(partyObj + 0x30) = static_cast<u16>((i + 1) | 0x300);
		partyObj += 0x6F8;
	}

	u8* monObj = reinterpret_cast<u8*>(m_objMon);
	for (int i = 0; i < 0x40; i++) {
		monObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(monObj + 0x30) = static_cast<u16>((i + 1) | 0x400);
		monObj += 0x740;
	}

	u8* itemObj = reinterpret_cast<u8*>(m_objItem);
	for (int i = 0; i < 0x20; i++) {
		itemObj[0x4C] &= 0x7F;
		*reinterpret_cast<u16*>(itemObj + 0x30) = static_cast<u16>((i + 1) | 0x500);
		itemObj += 0x57C;
	}
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
	if (classType == 3) {
		signed char* obj = reinterpret_cast<signed char*>(m_objParty);
		if (obj[0x4C] >= 0) {
			count++;
		}
		if (obj[0x744] >= 0) {
			count++;
		}
		if (obj[0xE3C] >= 0) {
			count++;
		}
		if (obj[0x1534] >= 0) {
			count++;
		}
		return count;
	}

	if (classType < 3) {
		if (classType == 1) {
			signed char* obj = reinterpret_cast<signed char*>(CFlat + 0x110C0);
			for (int i = 0; i < 3; i++) {
				if (obj[0x4C] >= 0) {
					count++;
				}
				if (obj[0xF8] >= 0) {
					count++;
				}
				if (obj[0x1A4] >= 0) {
					count++;
				}
				if (obj[0x250] >= 0) {
					count++;
				}
				if (obj[0x2FC] >= 0) {
					count++;
				}
				if (obj[0x3A8] >= 0) {
					count++;
				}
				if (obj[0x454] >= 0) {
					count++;
				}
				if (obj[0x500] >= 0) {
					count++;
				}
				obj += 0x560;
			}
			return count;
		}

		if (classType < 1) {
			if (classType < 0) {
				return count;
			}

			signed char* obj = reinterpret_cast<signed char*>(CFlat + 0x10440);
			for (int i = 0; i < 5; i++) {
				if (obj[0x4C] >= 0) {
					count++;
				}
				if (obj[0x9C] >= 0) {
					count++;
				}
				if (obj[0xEC] >= 0) {
					count++;
				}
				if (obj[0x13C] >= 0) {
					count++;
				}
				if (obj[0x18C] >= 0) {
					count++;
				}
				if (obj[0x1DC] >= 0) {
					count++;
				}
				if (obj[0x22C] >= 0) {
					count++;
				}
				if (obj[0x27C] >= 0) {
					count++;
				}
				obj += 0x280;
			}
			return count;
		}

		signed char* obj = reinterpret_cast<signed char*>(CFlat + 0x120E0);
		for (int i = 0; i < 7; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			if (obj[0x564] >= 0) {
				count++;
			}
			if (obj[0xA7C] >= 0) {
				count++;
			}
			if (obj[0xF94] >= 0) {
				count++;
			}
			if (obj[0x14AC] >= 0) {
				count++;
			}
			if (obj[0x19C4] >= 0) {
				count++;
			}
			if (obj[0x1EDC] >= 0) {
				count++;
			}
			if (obj[0x23F4] >= 0) {
				count++;
			}
			obj += 0x28C0;
		}
		return count;
	}

	if (classType == 5) {
		signed char* obj = reinterpret_cast<signed char*>(m_objItem);
		for (int i = 0; i < 4; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			if (obj[0x5C8] >= 0) {
				count++;
			}
			if (obj[0xB44] >= 0) {
				count++;
			}
			if (obj[0x10C0] >= 0) {
				count++;
			}
			if (obj[0x163C] >= 0) {
				count++;
			}
			if (obj[0x1BB8] >= 0) {
				count++;
			}
			if (obj[0x2134] >= 0) {
				count++;
			}
			if (obj[0x26B0] >= 0) {
				count++;
			}
			obj += 0x2BE0;
		}
		return count;
	}

	if (classType > 4) {
		return count;
	}

	signed char* obj = reinterpret_cast<signed char*>(m_objMon);
	for (int i = 0; i < 8; i++) {
		if (obj[0x4C] >= 0) {
			count++;
		}
		if (obj[0x78C] >= 0) {
			count++;
		}
		if (obj[0xECC] >= 0) {
			count++;
		}
		if (obj[0x160C] >= 0) {
			count++;
		}
		if (obj[0x1D4C] >= 0) {
			count++;
		}
		if (obj[0x248C] >= 0) {
			count++;
		}
		if (obj[0x2BCC] >= 0) {
			count++;
		}
		if (obj[0x330C] >= 0) {
			count++;
		}
		obj += 0x3A00;
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
	int classType = classId >> 8;
	unsigned int slot = static_cast<unsigned int>(classId) & 0xFF;

	if (classType == 3) {
		return m_objParty + (slot - 1) * 0x6F8;
	}

	if (classType > 2) {
		if (classType == 5) {
			return m_objItem + (slot - 1) * 0x57C;
		}
		if (classType > 4) {
			return this;
		}
		return m_objMon + (slot - 1) * 0x740;
	}

	if (classType == 1) {
		return CFlat + 0x110C0 + (slot - 1) * 0xAC;
	}

	if (classType < 1) {
		if (classType < 0) {
			return this;
		}
		return CFlat + 0x10440 + (slot - 1) * 0x50;
	}

	return CFlat + 0x120E0 + (slot - 1) * 0x518;
}

/*
 * --INFO--
 * PAL Address: 0x8006CD40
 * PAL Size: 2652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::Frame(int arg0, int mode)
{
	CStopWatch watch((char*)-1);
	System.DumpMapFile(&watch);

	if (mode == 0) {
		StaticFrame__10CGCharaObjFv();
		CheckGameOver__10CGPartyObjFv();
		Frame__12CFlatRuntimeFii(reinterpret_cast<CFlatRuntime*>(this), arg0, mode);

		CFlatRuntime::CObject* const root =
			reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
		for (CGBaseObj* obj = FindNextGBaseObjByCidMask(this, root->m_next->m_next, 5); obj != 0;
			 obj = FindNextGBaseObjByCidMask(this, reinterpret_cast<CFlatRuntime::CObject*>(obj)->m_next, 5)) {
			Frame__9CGBaseObjFv(obj);
		}
		return;
	}

	if (mode == 1) {
		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			move__8CGObjectFv(object);
		}
		watch.Stop();
		*reinterpret_cast<float*>(CFlat + 0x1338) += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			objectCollision__8CGObjectFv(object);
		}
		watch.Stop();
		*reinterpret_cast<float*>(CFlat + 0x1340) += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			bgCollision__8CGObjectFv(object);
		}
		watch.Stop();
		*reinterpret_cast<float*>(CFlat + 0x133C) += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			update__8CGObjectFv(object);
		}
		watch.Stop();
		*reinterpret_cast<float*>(CFlat + 0x1344) += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			hit__8CGObjectFv(object);
		}
		watch.Stop();
		*reinterpret_cast<float*>(CFlat + 0x1348) += watch.Get();

		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			copy__8CGObjectFv(object);
		}
		return;
	}

	_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
	GXSetZCompLoc(GX_FALSE);
	_GXSetAlphaCompare((_GXCompare)6, 1, (_GXAlphaOp)0, (_GXCompare)7, 0);
	GXSetZMode(GX_TRUE, (_GXCompare)3, GX_TRUE);
	GXSetCullMode(GX_CULL_BACK);
	GXSetNumTevStages(1);
	_GXSetTevOp((_GXTevStageID)0, (_GXTevMode)4);
	_GXSetTevOrder((_GXTevStageID)0, (_GXTexCoordID)0xFF, (_GXTexMapID)0xFF, (_GXChannelID)4);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	GXSetChanCtrl(
		GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	drawAStar__6CAStarFv(DbgMenuPcs + 0x2A5C);

	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	for (CGBaseObj* obj = FindNextGBaseObjByCidMask(this, root->m_next->m_next, 1); obj != 0;
		 obj = FindNextGBaseObjByCidMask(this, reinterpret_cast<CFlatRuntime::CObject*>(obj)->m_next, 1)) {
		Draw__9CGBaseObjFv(obj);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006CB84
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime2::Load(char* fileName)
{
	char path[0x100];
	sprintf(path, "dvd:/%s.cft", fileName);

	CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	if (fileHandle == 0) {
		return 0;
	}

	File.Read(fileHandle);
	File.SyncCompleted(fileHandle);
	Create__12CFlatRuntimeFPv(reinterpret_cast<CFlatRuntime*>(this), File.m_readBuffer);
	File.Close(fileHandle);

	typedef int (*NeedDebugDataFn)(CFlatRuntime2*);
	NeedDebugDataFn needDebugData = reinterpret_cast<NeedDebugDataFn>((*reinterpret_cast<void***>(this))[0x12]);

	if (needDebugData(this) != 0) {
		int debugChunk = 0;
		for (int debugIndex = 0;; debugIndex++) {
			sprintf(path, "dvd:/%s.cft_dbg", fileName);
			if (debugIndex != 0) {
				sprintf(path, "%s%d", path, debugIndex);
			}

			fileHandle = File.Open(path, 0, CFile::PRI_LOW);
			if (fileHandle == 0) {
				return 0;
			}

			File.Read(fileHandle);
			File.SyncCompleted(fileHandle);
			debugChunk = CreateDebug__12CFlatRuntimeFPvi(
				reinterpret_cast<CFlatRuntime*>(this), File.m_readBuffer, debugChunk);
			File.Close(fileHandle);

			if (debugChunk == -1) {
				break;
			}
		}
	}

	resetChangeScript();
	if (System.m_execParam > 2) {
		Printf__7CSystemFPce(&System, "CFlatRuntime2::Load\n");
	}
	return 1;
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
		CFile::CHandle* fileHandle = *reinterpret_cast<CFile::CHandle**>(layer + 8);
		if (fileHandle != 0) {
			File.Close(fileHandle);
			*reinterpret_cast<CFile::CHandle**>(layer + 8) = 0;
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
 * PAL Address: 0x8006C004
 * PAL Size: 1464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::Calc()
{
	u8* runtime = reinterpret_cast<u8*>(this);

	for (int i = 0; i < 8; i++) {
		u8* layer = runtime + 0x1770 + i * 0xC;
		CFile::CHandle* fileHandle = *reinterpret_cast<CFile::CHandle**>(layer + 8);
		if (fileHandle == 0) {
			continue;
		}

		if (File.IsCompleted(fileHandle)) {
			CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(layer + 4);
			if (textureSet != 0) {
				(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
				*reinterpret_cast<CTextureSet**>(layer + 4) = 0;
			}

			textureSet = new (Game.game.m_mainStage, "cflat_runtime2.cpp", 0x335) CTextureSet;
			*reinterpret_cast<CTextureSet**>(layer + 4) = textureSet;
			if (textureSet != 0) {
				textureSet->Create(File.m_readBuffer, Game.game.m_mainStage, 0, 0, 0, 0);
			}

			File.Close(fileHandle);
			*reinterpret_cast<CFile::CHandle**>(layer + 8) = 0;
		}
	}

	*reinterpret_cast<int*>(runtime + 0xCD1C) = 0;
	memset(runtime + 0x1338, 0, 0x14);
}

/*
 * --INFO--
 * PAL Address: 0x8006B7B8
 * PAL Size: 2124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::Draw()
{
	CFont* font = *reinterpret_cast<CFont**>(MenuPcs + 0x248);
	SetScale__5CFontFf(1.0f, font);
	SetShadow__5CFontFi(font, 1);
	SetMargin__5CFontFf(0.0f, font);
	SetZMode__5CFontFii(font, 0, 0);
	DrawInit__5CFontFv(font);
	SetTlut__5CFontFi(font, 7);
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	SetColor__5CFontF8_GXColor(font, &color);

	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	for (CGObject* object = reinterpret_cast<CGObject*>(
			 FindNextGBaseObjByCidMask(this, root->m_next->m_next, 5));
		 object != 0;
		 object = reinterpret_cast<CGObject*>(FindNextGBaseObjByCidMask(
			 this, reinterpret_cast<CFlatRuntime::CObject*>(object)->m_next, 5))) {
		DrawDebug__8CGObjectFP5CFont(object, font);
	}

	SetZMode__5CFontFii(font, 0, 0);
	SetPosZ__5CFontFf(1.0f, font);
	Mtx44 projection;
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcs + 0x40), projection);
	GXSetProjection(projection, GX_PERSPECTIVE);

	SetScale__5CFontFf(0.875f, font);
	SetShadow__5CFontFi(font, 1);
	SetMargin__5CFontFf(0.0f, font);
	SetZMode__5CFontFii(font, 1, 1);
	DrawInit__5CFontFv(font);

	for (CGItemObj* item = reinterpret_cast<CGItemObj*>(
			 FindNextGBaseObjByCidMask(this, root->m_next->m_next, 0x1D));
		 item != 0;
		 item = reinterpret_cast<CGItemObj*>(FindNextGBaseObjByCidMask(
			 this, reinterpret_cast<CFlatRuntime::CObject*>(item)->m_next, 0x1D))) {
		DrawOmoideName__9CGItemObjFP5CFont(item, font);
	}

	SetZMode__5CFontFii(font, 0, 0);
	SetPosZ__5CFontFf(1.0f, font);
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcs + 0x40), projection);
	GXSetProjection(projection, GX_PERSPECTIVE);

	Mtx cameraMtx;
	PSMTXCopy(*reinterpret_cast<Mtx*>(CameraPcs + 0x10), cameraMtx);

	_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
	GXSetZCompLoc(GX_FALSE);
	_GXSetAlphaCompare((_GXCompare)6, 1, (_GXAlphaOp)0, (_GXCompare)7, 0);
	GXSetZMode(GX_TRUE, (_GXCompare)3, GX_TRUE);
	GXSetCullMode(GX_CULL_BACK);
	GXSetNumTevStages(1);
	_GXSetTevOp((_GXTevStageID)0, (_GXTevMode)4);
	_GXSetTevOrder((_GXTevStageID)0, (_GXTexCoordID)0xFF, (_GXTexMapID)0xFF, (_GXChannelID)4);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	GXSetChanCtrl(
		GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

	u8* runtime = reinterpret_cast<u8*>(this);
	if ((*reinterpret_cast<u32*>(runtime + 0x129C) & 0x20000) != 0) {
		GXColor lineColor = {0xFF, 0x80, 0x80, 0xFF};
		GXSetChanMatColor(GX_COLOR0A0, lineColor);
		GXLoadPosMtxImm(cameraMtx, GX_PNMTX0);

		CLine<64>* line = reinterpret_cast<CLine<64>*>(runtime + 0x1BDC);
		for (int i = 0; i < 0x10; i++) {
			line->Draw();
			line = reinterpret_cast<CLine<64>*>(reinterpret_cast<u8*>(line) + 0x17C);
		}
	}

	const bool showDebugCC =
		((*reinterpret_cast<u32*>(runtime + 0x129C) & 0x200000) != 0) || ((MiniGamePcs[0x25732] & 0x80) != 0);
	const int debugCount = *reinterpret_cast<int*>(runtime + 0xCD1C);
	if (showDebugCC && debugCount != 0) {
		GXColor greenColor = {0x80, 0xFF, 0x80, 0xFF};
		GXColor blueColor = {0x80, 0x80, 0xFF, 0xFF};
		GXColor redColor = {0xFF, 0x00, 0x00, 0xFF};
		Vec worldUp = {0.0f, 1.0f, 0.0f};
		float ringVerts[8][3];

		u8* entry = runtime + 0xCD20;
		for (int i = 0; i < debugCount; i++) {
			const u8 flags = entry[0];
			GXColor* drawColor = &greenColor;
			if ((flags & 0x80) != 0) {
				drawColor = &redColor;
			} else if ((flags & 0x40) != 0) {
				drawColor = &blueColor;
			}
			GXSetChanMatColor(GX_COLOR0A0, *drawColor);

			Vec* start = reinterpret_cast<Vec*>(entry + 0x04);
			Vec* end = reinterpret_cast<Vec*>(entry + 0x10);
			float length = PSVECMag(end);

			Mtx orientMtx;
			PSMTXIdentity(orientMtx);
			Vec dir = *end;
			PSVECNormalize(&dir, &dir);

			const float dot = PSVECDotProduct(&worldUp, &dir);
			if (dot < 0.9999f) {
				if (dot >= -0.9999f) {
					Vec axis;
					PSVECCrossProduct(&dir, &worldUp, &axis);
					PSMTXRotAxisRad(orientMtx, &axis, -acosf(dot));
				} else {
					length = -length;
				}
			}

			orientMtx[0][3] = start->x;
			orientMtx[1][3] = start->y;
			orientMtx[2][3] = start->z;
			PSMTXConcat(cameraMtx, orientMtx, orientMtx);
			GXLoadPosMtxImm(orientMtx, GX_PNMTX0);

			const float radius = *reinterpret_cast<float*>(entry + 0x1C);
			GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 0x20);
			for (int j = 0; j < 8; j++) {
				const float angle = static_cast<float>(j) * 0.7853982f;
				ringVerts[j][0] = radius * sinf(angle);
				ringVerts[j][1] = radius * cosf(angle);
				ringVerts[j][2] = length;
				if ((flags & 0x40) != 0) {
					GXWGFifo.f32 = ringVerts[j][0];
					GXWGFifo.f32 = ringVerts[j][1];
					GXWGFifo.f32 = 1.0f;
				} else {
					GXWGFifo.f32 = 1.0f;
					GXWGFifo.f32 = 1.0f;
					GXWGFifo.f32 = 1.0f;
				}
				GXWGFifo.f32 = ringVerts[j][0];
				GXWGFifo.f32 = ringVerts[j][1];
				GXWGFifo.f32 = ringVerts[j][2];
			}

			for (int j = 0; j < 8; j++) {
				const int next = (j + 1) & 7;
				GXWGFifo.f32 = ringVerts[j][0];
				GXWGFifo.f32 = ringVerts[j][1];
				GXWGFifo.f32 = ringVerts[j][2];
				GXWGFifo.f32 = ringVerts[next][0];
				GXWGFifo.f32 = ringVerts[next][1];
				GXWGFifo.f32 = ringVerts[next][2];
			}

			entry += 0x20;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006B688
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::AddDebugDrawCC(Vec* from, Vec* to, float radius, int bit7, int bit6)
{
	u8* runtime = reinterpret_cast<u8*>(this);
	int& count = *reinterpret_cast<int*>(runtime + 0xCD1C);

	if (static_cast<unsigned int>(count) < 0x10U) {
		const int slotOffset = count * 0x20;
		u8* slot = runtime + 0xCD20 + slotOffset;

		*reinterpret_cast<float*>(slot + 0x04) = from->x;
		*reinterpret_cast<float*>(slot + 0x08) = from->y;
		*reinterpret_cast<float*>(slot + 0x0C) = from->z;
		*reinterpret_cast<float*>(slot + 0x10) = to->x;
		*reinterpret_cast<float*>(slot + 0x14) = to->y;
		*reinterpret_cast<float*>(slot + 0x18) = to->z;

		slot[0] = static_cast<u8>((bit7 << 7) | (slot[0] & 0x7F));
		slot[0] = static_cast<u8>(((bit6 << 6) & 0x40) | (slot[0] & 0xBF));

		const int index = count;
		count = index + 1;
		*reinterpret_cast<float*>(runtime + 0xCD3C + index * 0x20) = radius;
		return;
	}

	if (gCFlatRuntime2DebugDrawOverflowInit == 0) {
		gCFlatRuntime2DebugDrawOverflowFrame = 0;
		gCFlatRuntime2DebugDrawOverflowInit = 1;
	}

	if (gCFlatRuntime2DebugDrawOverflowFrame != static_cast<int>(System.m_frameCounter)) {
		printf(&sCFlatRuntime2DebugDrawOverflowMsg[0]);
		gCFlatRuntime2DebugDrawOverflowFrame = System.m_frameCounter;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8006B1DC
 * PAL Size: 1196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime2::CcClass2D(int flags, int classMask, Vec* center, float radius, float angle, int maxCount, CGObject** objects)
{
	if (maxCount <= 0 || objects == 0) {
		return 0;
	}

	const float radiusSq = radius * radius;
	CFlatRuntime::CObject* root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x1204);
	CGBaseObj* baseObj = FindNextGBaseObjByCidMask(this, root->m_next->m_next, 5);
	int count = 0;

	while (baseObj != 0) {
		CGObject* object = reinterpret_cast<CGObject*>(baseObj);
		const bool passesClassMask = (object->m_attrFlags & static_cast<unsigned int>(classMask)) != 0;
		const bool passesScriptFilter =
			((flags & 1) == 0) ||
			((object->m_scriptHandle != 0) && (*reinterpret_cast<short*>(reinterpret_cast<u8*>(object->m_scriptHandle) + 0x1C) != 0));

		if (passesClassMask && passesScriptFilter) {
			if ((object->m_worldPosition.x != center->x) || (object->m_worldPosition.z != center->z)) {
				if ((center->x - radius <= object->m_worldPosition.x) &&
				    (center->z - radius <= object->m_worldPosition.z) &&
				    (object->m_worldPosition.x <= center->x + radius) &&
				    (object->m_worldPosition.z <= center->z + radius)) {
					Vec offset;
					PSVECSubtract(&object->m_worldPosition, center, &offset);
					offset.y = 0.0f;

					const float distanceSq = PSVECSquareMag(&offset);
					if ((0.0f < distanceSq) && (distanceSq < radiusSq)) {
						const float distance = sqrtf(distanceSq);
						if (distance < radius) {
							if ((flags & 2) != 0) {
								Vec facing;
								PSVECScale(&offset, &offset, 1.0f / distance);
								facing.x = sin(angle);
								facing.y = 0.0f;
								facing.z = cos(angle);
								if (PSVECDotProduct(&offset, &facing) <= 0.0f) {
									baseObj = FindNextGBaseObjByCidMask(
										this, reinterpret_cast<CFlatRuntime::CObject*>(object)->m_next, 5);
									continue;
								}
							}

							if ((flags & 4) != 0) {
								objects[count] = object;
								count++;
								if (count == maxCount) {
									return count;
								}
							} else {
								int insertIndex = 0;
								for (; insertIndex < count; insertIndex++) {
									if (distance < *reinterpret_cast<float*>(&objects[insertIndex]->m_0x44)) {
										break;
									}
								}

								const int endIndex = (count < (maxCount - 1)) ? count : (maxCount - 1);
								for (int i = endIndex; i > insertIndex; i--) {
									objects[i] = objects[i - 1];
								}

								*reinterpret_cast<float*>(&object->m_0x44) = distance;
								objects[insertIndex] = object;
								if (count < maxCount) {
									count++;
								}
							}
						}
					}
				}
			}
		}

		baseObj = FindNextGBaseObjByCidMask(this, reinterpret_cast<CFlatRuntime::CObject*>(object)->m_next, 5);
	}

	return count;
}

/*
 * --INFO--
 * PAL Address: 0x8006B068
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::loadLayer(int layerNo, char* fileName)
{
	const int layerOffset = layerNo * 0xC;
	u8* layer = reinterpret_cast<u8*>(this) + 0x1770 + layerOffset;

	CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(layer + 4);
	if (textureSet != 0) {
		(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
		*reinterpret_cast<CTextureSet**>(layer + 4) = 0;
	}

	char path[0x104];
	sprintf(path, "dvd:/%s/%s.tex", GetLangString__5CGameFv(&Game.game), fileName);

	CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	if (fileHandle != 0) {
		File.Read(fileHandle);
		File.SyncCompleted(fileHandle);

		textureSet = new (Game.game.m_mainStage, "cflat_runtime2.cpp", 0x4F4) CTextureSet;
		*reinterpret_cast<CTextureSet**>(layer + 4) = textureSet;
		if (textureSet != 0) {
			textureSet->Create(File.m_readBuffer, Game.game.m_mainStage, 0, 0, 0, 0);
		}

		File.Close(fileHandle);
	}
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

	CFile::CHandle* fileHandle = *reinterpret_cast<CFile::CHandle**>(layer + 8);
	if (fileHandle != 0) {
		File.Close(fileHandle);
		*reinterpret_cast<CFile::CHandle**>(layer + 8) = 0;
	}

	void* textureSet = *reinterpret_cast<void**>(layer + 4);
	if (textureSet != 0) {
		(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
		*reinterpret_cast<void**>(layer + 4) = 0;
	}

	char path[0x104];
	sprintf(path, "dvd:/%s/%s.tex", GetLangString__5CGameFv(&Game.game), fileName);

	fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	*reinterpret_cast<CFile::CHandle**>(layer + 8) = fileHandle;
	if (fileHandle != 0) {
		File.ReadASync(fileHandle);
	}

	*reinterpret_cast<int*>(layer) = *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0xE4);
}

/*
 * --INFO--
 * PAL Address: 0x8006A764
 * PAL Size: 2040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::drawLayer(
	int layerNo, char* textureName, int x, int y, int width, int height, int texU, int texV, float scaleX,
	float scaleY, _GXColor* color, int flags)
{
	CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(reinterpret_cast<u8*>(this) + 0x1774 + layerNo * 0xC);
	if (textureSet == 0) {
		return;
	}

	int textureIndex = textureSet->Find(textureName);
	if (textureIndex < 0) {
		return;
	}

	CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8);
	CTexture* texture = (*textureArray)[static_cast<unsigned long>(textureIndex)];

	GXSetNumChans(1);
	GXSetChanCtrl(
		GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
	GXSetChanMatColor(GX_COLOR0A0, *color);

	Mtx44 ortho;
	C_MTXOrtho(ortho, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
	GXSetProjection(ortho, GX_ORTHOGRAPHIC);

	Mtx identity;
	PSMTXIdentity(identity);
	GXLoadPosMtxImm(identity, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);

	const unsigned int blendMode = static_cast<unsigned int>(flags >> 1) & 2;
	if (blendMode == 1) {
		_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
	} else if (blendMode == 2) {
		_GXSetBlendMode((_GXBlendMode)3, (_GXBlendFactor)4, (_GXBlendFactor)1, (_GXLogicOp)5);
	} else {
		_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
	}

	GXSetZMode(GX_FALSE, (_GXCompare)7, GX_FALSE);
	PSMTXIdentity(identity);
	GXLoadPosMtxImm(identity, GX_PNMTX0);
	GXSetCullMode(GX_CULL_NONE);

	TextureMan.SetTexture(GX_TEXMAP0, texture);

	Mtx texMtx;
	const float texW = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x64));
	const float texH = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x68));
	PSMTXScale(texMtx, 1.0f / texW, 1.0f / texH, 1.0f);
	GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(
		GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);

	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
	int tevStage = TextureMan.SetTextureTev(texture);

	const float scaledWidth = static_cast<float>(width) * scaleX;
	const float scaledHeight = static_cast<float>(height) * scaleY;
	const float xAnchor = (flags & 1) != 0 ? scaledWidth * 0.5f : 0.0f;
	const float yAnchor = (flags & 1) != 0 ? scaledHeight * 0.5f : 0.0f;
	const float x0 = static_cast<float>(x) - xAnchor;
	const float y0 = static_cast<float>(y) - yAnchor;
	const float x1 = x0 + scaledWidth;
	const float y1 = y0 + scaledHeight;
	short u0 = static_cast<short>(texU);
	short v0 = static_cast<short>(texV);
	short u1 = static_cast<short>(texU + width);
	short v1 = static_cast<short>(texV + height);

	if (blendMode == 3) {
		GXSetNumTexGens(2);
		GXSetTexCoordGen2(
			GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
		GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_S16, 1);
		GXSetNumTevStages(static_cast<u8>(tevStage + 1));
		_GXSetTevOrder(
			(_GXTevStageID)tevStage, (_GXTexCoordID)GX_TEXCOORD1, (_GXTexMapID)GX_TEXMAP1, (_GXChannelID)0xFF);
		_GXSetTevColorIn((_GXTevStageID)tevStage, (_GXTevColorArg)0xF, (_GXTevColorArg)8, (_GXTevColorArg)0, (_GXTevColorArg)0xF);
		_GXSetTevColorOp((_GXTevStageID)tevStage, (_GXTevOp)0, (_GXTevBias)0, (_GXTevScale)2, 1, (_GXTevRegID)0);
		_GXSetTevAlphaIn((_GXTevStageID)tevStage, (_GXTevAlphaArg)7, (_GXTevAlphaArg)4, (_GXTevAlphaArg)0, (_GXTevAlphaArg)7);
		_GXSetTevAlphaOp((_GXTevStageID)tevStage, (_GXTevOp)0, (_GXTevBias)0, (_GXTevScale)0, 1, (_GXTevRegID)0);

		const int pixelWidth = static_cast<int>(scaledWidth * 0.5f);
		const int pixelHeight = static_cast<int>(scaledHeight * 0.5f);

		for (int quad = 0; quad < 4; quad++) {
			int bx = static_cast<int>(x0);
			int by = static_cast<int>(y0);
			int bw = pixelWidth;
			int bh = pixelHeight;

			if ((quad & 1) != 0) {
				bx += pixelWidth;
			}
			if ((quad & 2) != 0) {
				by += pixelHeight;
			}

			short quadU0 = u0;
			short quadV0 = v0;
			short quadU1 = static_cast<short>(quadU0 + bw);
			short quadV1 = static_cast<short>(quadV0 + bh);
			if ((quad & 1) != 0) {
				quadU0 = static_cast<short>(quadU0 + pixelWidth);
				quadU1 = static_cast<short>(quadU0 + bw);
			}
			if ((quad & 2) != 0) {
				quadV0 = static_cast<short>(quadV0 + pixelHeight);
				quadV1 = static_cast<short>(quadV0 + bh);
			}

			int rectX = bx;
			int rectY = by;
			int rectW = bw;
			int rectH = bh;
			int backTex =
				GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, rectX, rectY, rectW, rectH, 0);
			GXLoadTexObj(reinterpret_cast<_GXTexObj*>(backTex), GX_TEXMAP1);

			const float fx0 = static_cast<float>(rectX);
			const float fy0 = static_cast<float>(rectY);
			const float fx1 = static_cast<float>(rectX + rectW);
			const float fy1 = static_cast<float>(rectY + rectH);

			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			GXPosition3f32(fx0, fy0, 0.0f);
			GXTexCoord2s16(quadU0, quadV0);
			GXTexCoord2s16(0, 0);

			GXPosition3f32(fx1, fy0, 0.0f);
			GXTexCoord2s16(quadU1, quadV0);
			GXTexCoord2s16(2, 0);

			GXPosition3f32(fx1, fy1, 0.0f);
			GXTexCoord2s16(quadU1, quadV1);
			GXTexCoord2s16(2, 2);

			GXPosition3f32(fx0, fy1, 0.0f);
			GXTexCoord2s16(quadU0, quadV1);
			GXTexCoord2s16(0, 2);
		}
	} else {
		GXBegin(GX_QUADS, GX_VTXFMT0, 4);
		GXPosition3f32(x0, y0, 0.0f);
		GXTexCoord2s16(u0, v0);

		GXPosition3f32(x1, y0, 0.0f);
		GXTexCoord2s16(u1, v0);

		GXPosition3f32(x1, y1, 0.0f);
		GXTexCoord2s16(u1, v1);

		GXPosition3f32(x0, y1, 0.0f);
		GXTexCoord2s16(u0, v1);
	}

	Mtx44 projection;
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcs + 0x40), projection);
	GXSetProjection(projection, GX_PERSPECTIVE);
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
	float one = 1.0f;
	u8 clear3[3] = { 0, 0, 0 };
	int seNo = -1;
	int sePacked = 0x00000100;
	int seParam = 0;
	int seDelay = 0x1E;
	int seFrame = -1;
	int paramNo = 0;
	int paramId = 0;
	int ex0 = 0;
	int ex1 = 0;
	int ex2 = 0;
	int ex3 = 0;
	int ex4 = 0;
	int ex5 = 0;
	int ex6 = 0;
	int ex7 = 0;

	ParticleWorkPosPtr(this) = 0;
	ParticleWorkPosVecPtr(this) = 0;
	ParticleWorkScalePtr(this) = 0;
	ParticleWorkTargetPtr(this) = 0;
	*reinterpret_cast<int*>(runtime + 0x16DC) = 0;
	ParticleWorkBind(this) = 0;
	ParticleWorkTrace(this) = 0;
	ParticleWorkColor0(this) = 0;
	ParticleWorkColor1(this) = 0;
	ParticleWorkSpeed(this) = one;
	ParticleWorkColorLerp(this) = one;
	runtime[0x16F8] = 0;
	memcpy(runtime + 0x16F9, clear3, sizeof(clear3));

	*reinterpret_cast<int*>(runtime + 0x16FC) = seNo;
	*reinterpret_cast<int*>(runtime + 0x1700) = sePacked;
	*reinterpret_cast<int*>(runtime + 0x1704) = seParam;
	*reinterpret_cast<int*>(runtime + 0x1708) = seDelay;
	*reinterpret_cast<int*>(runtime + 0x170C) = seFrame;
	*reinterpret_cast<int*>(runtime + 0x1710) = paramNo;
	*reinterpret_cast<int*>(runtime + 0x1714) = paramId;
	*reinterpret_cast<int*>(runtime + 0x1718) = ex0;
	*reinterpret_cast<int*>(runtime + 0x171C) = ex1;
	*reinterpret_cast<int*>(runtime + 0x1720) = ex2;
	*reinterpret_cast<int*>(runtime + 0x1724) = ex3;
	*reinterpret_cast<int*>(runtime + 0x1728) = ex4;
	*reinterpret_cast<int*>(runtime + 0x172C) = ex5;
	*reinterpret_cast<int*>(runtime + 0x1730) = ex6;
	*reinterpret_cast<int*>(runtime + 0x1734) = ex7;

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
	struct RuntimeSysControlView {
		u8 m_padding[0x12E8];
		int m_control;
	};

	if (controlNo == 3) {
		return reinterpret_cast<RuntimeSysControlView*>(this)->m_control;
	}

	return 0;
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
