#include "ffcc/cflat_runtime2.h"
#include "ffcc/astar.h"
#include "ffcc/baseobj.h"
#include "ffcc/cflat_data.h"
#include "ffcc/goout.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/itemobj.h"
#include "ffcc/linkage.h"
#include "ffcc/monobj.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_game.h"
#include "ffcc/ptrarray.h"
#include "ffcc/quadobj.h"
#include "ffcc/stopwatch.h"
#include "ffcc/textureman.h"
#include <math.h>
#include <string.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <PowerPC_EABI_Support/Runtime/NMWException.h>

class CFont;

inline void* operator new(unsigned long, void* ptr)
{
	return ptr;
}

extern "C" void StaticFrame__10CGCharaObjFv();
extern "C" void* __vt__13CFlatRuntime2[];
extern "C" void __dt__13CFlatRuntime2Fv(void*);
extern "C" void __dt__12CFlatRuntimeFv(CFlatRuntime*, short);
extern "C" void __ct__8CGMonObjFv(CGMonObj*);
extern "C" void __ct__10CGPartyObjFv(CGPartyObj*);
extern "C" void __ct__9CGItemObjFv(CGItemObj*);
extern "C" void __ct__8CGObjectFv(CGObject*);
extern "C" void __ct__9CGQuadObjFv(CGQuadObj*);
extern "C" void __ct__9CGBaseObjFv(CGBaseObj*);
extern const float FLOAT_80330138;
extern const float FLOAT_8033013C;

// Linkage definitions from config/GCCP01/symbols.txt.
// Keeping these as raw byte buffers matches current decomp access patterns.
unsigned char CFlat_guard[0xC];
unsigned char CFlat[0x10440] ATTRIBUTE_ALIGN(32);
CFlatRuntime2& gCFlatRuntime2 = *reinterpret_cast<CFlatRuntime2*>(CFlat);
unsigned char m_objBase[0xC80];
unsigned char m_objQuad[0x1020];
unsigned char m_obj[0x11D40];
unsigned char m_objItem[0xAF80];
unsigned char m_objParty[0x1BE0];
unsigned char m_objMon[0x1D000];
u32 CFlatFlags;

enum {
	kFlatBaseObjCount = sizeof(m_objBase) / sizeof(CGBaseObj),
	kFlatQuadObjCount = sizeof(m_objQuad) / sizeof(CGQuadObj),
	kFlatObjectCount = sizeof(m_obj) / sizeof(CGObject),
	kFlatItemObjCount = sizeof(m_objItem) / sizeof(CGItemObj),
	kFlatLayerResourceCount = 8,
	kFlatSpawnBitCount = 9,
};

STATIC_ASSERT(sizeof(m_objBase) == sizeof(CGBaseObj) * kFlatBaseObjCount);
STATIC_ASSERT(sizeof(m_objQuad) == sizeof(CGQuadObj) * kFlatQuadObjCount);
STATIC_ASSERT(sizeof(m_obj) == sizeof(CGObject) * kFlatObjectCount);
STATIC_ASSERT(sizeof(m_objItem) == sizeof(CGItemObj) * kFlatItemObjCount);

extern "C" void* __vt__Q212CFlatRuntime7CObject[];
extern "C" void* __vt__9CGBaseObj[];
extern "C" void* __vt__8CGObject[];
extern "C" void* __vt__8CGPrgObj[];
extern "C" void* __vt__10CGCharaObj[];
extern "C" void* __vt__8CGMonObj[];
extern "C" void* __vt__10CGPartyObj[];
int gCFlatRuntime2DebugDrawOverflowFrame = 0;
unsigned char gCFlatRuntime2DebugDrawOverflowInit = 0;
const char sCFlatRuntime2DebugDrawOverflowMsg[] =
	"CFlatRuntime2.AddDebugDrawCC: "
	"\x8e\x8b\x90\xfc\x83\x60\x83\x46\x83\x62\x83\x4e\x83\x66\x83\x6f\x83\x62\x83\x4f"
	"\x95\x8e\xa6\x82\xf0\x82\xb1\x82\xea\x88\xc8\x8f\xe3\x92\xc7\x89\xc1\x82\xc5"
	"\x82\xab\x82\xdc\x82\xb9\x82\xf1\x81\x42\n";
static const char sCFlatRuntime2SaveSceneMsg[] = "SAVE SCENE";
static const char sCFlatRuntime2FileNameFmt[] = "dvd/cft/%s.cft";
static const char sCFlatRuntime2DebugFileNameFmt[] = "dvd/cft/%s.cft.dbg";
static const char sCFlatRuntime2LoadMsg[] = "CFlatRuntime2::Load\n";
static const char sCFlatRuntime2FileTag[] = "cflat_runtime2.cpp";
static const char sCFlatRuntime2TexturePathFmt[] = "dvd/%s%s.tex";

struct CFlatDebugDrawCC {
	u8 m_flags;
	u8 m_pad[3];
	Vec m_from;
	Vec m_to;
	float m_radius;
};

struct CFlatLayerResource {
	int m_allocStage;
	CTextureSet* m_textureSet;
	CFile::CHandle* m_fileHandle;
};

STATIC_ASSERT(sizeof(CFlatLayerResource) * kFlatLayerResourceCount == 0x60);

static inline void InitFlatObjectSlot(CGBaseObj* object, u16 particleId)
{
	object->m_isActive &= 0x7F;
	object->m_particleId = particleId;
}

static CGBaseObj* FindNextGBaseObjByCidMask(CFlatRuntime2* runtime, CFlatRuntime::CObject* object, unsigned int cidMask)
{
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(runtime) + 0x8CC);

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & cidMask) == cidMask) {
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
	while (i < m_numPoints) {
		GXWGFifo.f32 = m_points[i].x;
		GXWGFifo.f32 = m_points[i].y;
		GXWGFifo.f32 = m_points[i].z;
		i++;
	}

	const float yOffset = 1.0f;
	GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(m_numPoints & 0xFFFF));
	i = 0;
	while (i < m_numPoints) {
		GXWGFifo.f32 = m_points[i].x;
		GXWGFifo.f32 = yOffset + m_points[i].y;
		GXWGFifo.f32 = m_points[i].z;
		i++;
	}

	GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, (u16)((m_numPoints & 0x7FFF) << 1));
	i = 0;
	while (i < m_numPoints) {
		GXWGFifo.f32 = m_points[i].x;
		GXWGFifo.f32 = m_points[i].y;
		GXWGFifo.f32 = m_points[i].z;
		GXWGFifo.f32 = m_points[i].x;
		GXWGFifo.f32 = yOffset + m_points[i].y;
		GXWGFifo.f32 = m_points[i].z;
		i++;
	}
}

namespace {

typedef unsigned char u8;

static inline u8* PadRaw()
{
	return reinterpret_cast<u8*>(&Pad);
}

static inline u8* MenuPcsRaw()
{
	return reinterpret_cast<u8*>(&MenuPcs);
}

static inline u8* GraphicPcsRaw()
{
	return reinterpret_cast<u8*>(&GraphicPcs);
}

static inline u8* CameraPcsRaw()
{
	return reinterpret_cast<u8*>(&CameraPcs);
}

static inline u8* DbgMenuPcsRaw()
{
	return reinterpret_cast<u8*>(&DbgMenuPcs);
}

static inline u8* MiniGamePcsRaw()
{
	return reinterpret_cast<u8*>(&MiniGamePcs);
}

static inline u32& RuntimeDebugFlags(u8* runtime)
{
	return *reinterpret_cast<u32*>(runtime + 0x129C);
}

static inline int& DebugDrawCCCount(u8* runtime)
{
	return *reinterpret_cast<int*>(runtime + 0xCD1C);
}

static inline CFlatDebugDrawCC* DebugDrawCCEntries(u8* runtime)
{
	return reinterpret_cast<CFlatDebugDrawCC*>(runtime + 0xCD20);
}

static inline CFlatLayerResource* LayerResources(CFlatRuntime2* runtime)
{
	return reinterpret_cast<CFlatLayerResource*>(reinterpret_cast<u8*>(runtime) + 0x1770);
}

static inline CFlatRuntime2::CParticleWork& ParticleWork(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<CFlatRuntime2::CParticleWork*>(reinterpret_cast<u8*>(runtime) + 0x16CC);
}

static inline float& ParticleWorkSpeed(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_speed;
}

static inline float* &ParticleWorkScalePtr(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_scale;
}

static inline float& ParticleWorkScaleX(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1758);
}

static inline float* ParticleWorkScaleValues(CFlatRuntime2* runtime)
{
	return reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1758);
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
	return ParticleWork(runtime).m_target;
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
	return ParticleWork(runtime).m_pos;
}

static inline float*& ParticleWorkPosVecPtr(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_posVec;
}

static inline float& ParticleWorkPosX(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1740);
}

static inline float* ParticleWorkPosValues(CFlatRuntime2* runtime)
{
	return reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x1740);
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

static inline float* ParticleWorkPosVecValues(CFlatRuntime2* runtime)
{
	return reinterpret_cast<float*>(reinterpret_cast<u8*>(runtime) + 0x174C);
}

static inline CFlatRuntime::CObject*& ParticleWorkBind(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_bind;
}

static inline CFlatRuntime::CObject*& ParticleWorkTrace(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_trace;
}

static inline int& ParticleWorkColor0(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_color0;
}

static inline int& ParticleWorkColor1(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_color1;
}

static inline float& ParticleWorkColorLerp(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_colorLerp;
}

static inline int& ParticleWorkSeNo(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_seNo;
}

static inline u8& ParticleWorkSeKind(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_seKind;
}

static inline int& ParticleWorkSeParam(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_seParam;
}

static inline int& ParticleWorkParamNo(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_paramNo;
}

static inline short& ParticleWorkParamId(CFlatRuntime2* runtime)
{
	return ParticleWork(runtime).m_paramId;
}

static inline int& ParticleWorkNoHi(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<int*>(reinterpret_cast<u8*>(runtime) + 0x1738);
}

static inline unsigned int& ParticleWorkNoLo(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x173C);
}

static inline u32 Swap32(u32 value)
{
	return __lwbrx(&value, 0);
}

static inline u32 SwapF32(float value)
{
	return __lwbrx(&value, 0);
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

	new (reinterpret_cast<CFlatRuntime*>(this)) CFlatRuntime;
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

	new (runtime + 0xCF20) CFlatData;
	CFlatSaveSceneEnabled() = 0;
	RuntimeDebugFlags(runtime) = 0;
	*reinterpret_cast<int*>(runtime + 0x12A0) = 0;
	*reinterpret_cast<int*>(runtime + 0x12A4) = -1;
	runtime[0x12E4] = (runtime[0x12E4] & 0xFB) | 4;
	*reinterpret_cast<int*>(runtime + 0x10400) = 0;
	*reinterpret_cast<int*>(runtime + 0x10408) = 0;
	memset(runtime + 0x15CC, 0, 0x100);
	memset(LayerResources(this), 0, sizeof(CFlatLayerResource) * kFlatLayerResourceCount);

	resetChangeScript();
	memset(runtime + 0x12F0, 0, sizeof(u32) * 2 * kFlatSpawnBitCount);

	CGBaseObj* baseObj = reinterpret_cast<CGBaseObj*>(m_objBase);
	for (int i = 0; i < 0x28; i++) {
		InitFlatObjectSlot(baseObj, static_cast<u16>(i + 1));
		baseObj++;
	}

	CGQuadObj* quadObj = reinterpret_cast<CGQuadObj*>(m_objQuad);
	for (int i = 0; i < 0x18; i++) {
		InitFlatObjectSlot(quadObj, static_cast<u16>((i + 1) | 0x100));
		quadObj++;
	}

	CGObject* gObj = reinterpret_cast<CGObject*>(m_obj);
	for (int i = 0; i < 0x38; i++) {
		InitFlatObjectSlot(gObj, static_cast<u16>((i + 1) | 0x200));
		gObj++;
	}

	u8* partyObjBytes = reinterpret_cast<u8*>(m_objParty);
	for (int i = 0; i < 4; i++) {
		InitFlatObjectSlot(reinterpret_cast<CGPartyObj*>(partyObjBytes), static_cast<u16>((i + 1) | 0x300));
		partyObjBytes += 0x6F8;
	}

	u8* monObjBytes = reinterpret_cast<u8*>(m_objMon);
	for (int i = 0; i < 0x40; i++) {
		InitFlatObjectSlot(reinterpret_cast<CGMonObj*>(monObjBytes), static_cast<u16>((i + 1) | 0x400));
		monObjBytes += 0x740;
	}

	u8* itemObjBytes = reinterpret_cast<u8*>(m_objItem);
	for (int i = 0; i < 0x20; i++) {
		InitFlatObjectSlot(reinterpret_cast<CGItemObj*>(itemObjBytes), static_cast<u16>((i + 1) | 0x500));
		itemObjBytes += 0x57C;
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
	reinterpret_cast<CFlatRuntime*>(this)->AfterFrame(1);
	reinterpret_cast<CFlatData*>(runtime + 0xCF20)->~CFlatData();
	__dt__12CFlatRuntimeFv(reinterpret_cast<CFlatRuntime*>(this), 0);
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
    // NOTE: This __sinit is compiler-generated. To match, move the vtable setup
    // (and any sub-construction) into the class constructor, then delete this
    // function. The compiler will auto-generate __sinit from the global object.

	new (CFlat) CFlatRuntime2;
	__register_global_object(CFlat, reinterpret_cast<void*>(__dt__13CFlatRuntime2Fv), CFlat_guard);

	__construct_array(m_objBase, reinterpret_cast<ConstructorDestructor>(__ct__9CGBaseObjFv), 0, sizeof(CGBaseObj), kFlatBaseObjCount);
	__construct_array(m_objQuad, reinterpret_cast<ConstructorDestructor>(__ct__9CGQuadObjFv), 0, sizeof(CGQuadObj), kFlatQuadObjCount);
	__construct_array(m_obj, reinterpret_cast<ConstructorDestructor>(__ct__8CGObjectFv), 0, sizeof(CGObject), kFlatObjectCount);
	__construct_array(m_objItem, reinterpret_cast<ConstructorDestructor>(__ct__9CGItemObjFv), 0, sizeof(CGItemObj), kFlatItemObjCount);
	__construct_array(m_objParty, reinterpret_cast<ConstructorDestructor>(__ct__10CGPartyObjFv), 0, 0x6F8, 4);
	__construct_array(m_objMon, reinterpret_cast<ConstructorDestructor>(__ct__8CGMonObjFv), 0, 0x740, 0x40);
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
	static_cast<CFlatRuntime::CObject*>(obj)->m_flagBits.m_constructFlag = 0;
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
	static_cast<CFlatRuntime::CObject*>(obj)->m_flagBits.m_constructFlag = 0;
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
CGItemObj::CGItemObj()
{
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
CGPrgObj::CGPrgObj()
{
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
CGObject::CGObject()
{
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
CGQuadObj::CGQuadObj()
{
}

CGBaseObj::CGBaseObj()
{
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
	return Game.m_mainStage;
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
	return Game.m_debugStage;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onNewObject(CFlatRuntime::CObject* object)
{
	CGBaseObj* baseObj = reinterpret_cast<CGBaseObj*>(object);
	baseObj->m_isActiveBits.active = 1;
	baseObj->Create();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onDeleteObject(CFlatRuntime::CObject* object)
{
	CGBaseObj* baseObj = reinterpret_cast<CGBaseObj*>(object);
	baseObj->Destroy();
	baseObj->m_isActiveBits.active = 0;
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

	switch (classType) {
	case 0: {
		signed char* obj = reinterpret_cast<signed char*>(m_objBase);
		for (int i = 0; i < 40; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0x50;
		}
		return count;
	}
	case 1: {
		signed char* obj = reinterpret_cast<signed char*>(m_objQuad);
		for (int i = 0; i < 24; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0xAC;
		}
		return count;
	}
	case 2: {
		signed char* obj = reinterpret_cast<signed char*>(m_obj);
		for (int i = 0; i < 56; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0x518;
		}
		return count;
	}
	case 3: {
		signed char* obj = reinterpret_cast<signed char*>(m_objParty);
		for (int i = 0; i < 4; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0x6F8;
		}
		return count;
	}
	case 4: {
		signed char* obj = reinterpret_cast<signed char*>(m_objMon);
		for (int i = 0; i < 64; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0x740;
		}
		return count;
	}
	case 5: {
		signed char* obj = reinterpret_cast<signed char*>(m_objItem);
		for (int i = 0; i < 32; i++) {
			if (obj[0x4C] >= 0) {
				count++;
			}
			obj += 0x57C;
		}
		return count;
	}
	default:
		return count;
	}
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
	switch (classType) {
	case 0: {
		unsigned char* obj = m_objBase;
		for (int i = 0; i < 0x28; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_objBase + i * 0x50);
			}
			obj += 0x50;
		}
		return 0;
	}
	case 1: {
		unsigned char* obj = m_objQuad;
		for (int i = 0; i < 0x18; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_objQuad + i * 0xAC);
			}
			obj += 0xAC;
		}
		return 0;
	}
	case 2: {
		unsigned char* obj = m_obj;
		for (int i = 0; i < 0x38; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_obj + i * 0x518);
			}
			obj += 0x518;
		}
		return 0;
	}
	case 3: {
		unsigned char* obj = m_objParty;
		for (int i = 0; i < 4; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_objParty + i * 0x6F8);
			}
			obj += 0x6F8;
		}
		return 0;
	}
	case 4: {
		unsigned char* obj = m_objMon;
		for (int i = 0; i < 0x40; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_objMon + i * 0x740);
			}
			obj += 0x740;
		}
		return 0;
	}
	case 5: {
		unsigned char* obj = m_objItem;
		for (int i = 0; i < 0x20; i++) {
			if (static_cast<signed char>(obj[0x4C]) >= 0) {
				return reinterpret_cast<CGObject*>(m_objItem + i * 0x57C);
			}
			obj += 0x57C;
		}
		return 0;
	}
	default:
		return 0;
	}
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

	switch (classType) {
	case 0:
		return m_objBase + (slot - 1) * 0x50;
	case 1:
		return m_objQuad + (slot - 1) * 0xAC;
	case 2:
		return m_obj + (slot - 1) * 0x518;
	case 3:
		return m_objParty + (slot - 1) * 0x6F8;
	case 4:
		return m_objMon + (slot - 1) * 0x740;
	case 5:
		return m_objItem + (slot - 1) * 0x57C;
	default:
		return this;
	}
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

	if (mode == 0) {
		StaticFrame__10CGCharaObjFv();
		CGPartyObj::CheckGameOver();
		reinterpret_cast<CFlatRuntime*>(this)->Frame(arg0, mode);

		CFlatRuntime::CObject* const root =
			reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
		for (CGBaseObj* obj = FindNextGBaseObjByCidMask(this, root->m_next->m_next, 5); obj != 0;
			 obj = FindNextGBaseObjByCidMask(this, reinterpret_cast<CFlatRuntime::CObject*>(obj)->m_next, 5)) {
			obj->Frame();
		}
		return;
	}

	if (mode == 1) {
		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->move();
		}
		watch.Stop();
		CFlatMoveTime() += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->objectCollision();
		}
		watch.Stop();
		CFlatObjectCollisionTime() += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->bgCollision();
		}
		watch.Stop();
		CFlatBgCollisionTime() += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->update();
		}
		watch.Stop();
		CFlatUpdateTime() += watch.Get();

		watch.Reset();
		watch.Start();
		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->hit();
		}
		watch.Stop();
		CFlatHitTime() += watch.Get();

		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			object->copy();
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
	AStar.drawAStar();

	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	for (CGBaseObj* obj = FindNextGBaseObjByCidMask(this, root->m_next->m_next, 1); obj != 0;
		 obj = FindNextGBaseObjByCidMask(this, reinterpret_cast<CFlatRuntime::CObject*>(obj)->m_next, 1)) {
		obj->Draw();
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
	sprintf(path, sCFlatRuntime2FileNameFmt, fileName);

	CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	if (fileHandle == 0) {
		return 0;
	}

	File.Read(fileHandle);
	File.SyncCompleted(fileHandle);
	reinterpret_cast<CFlatRuntime*>(this)->Create(File.m_readBuffer);
	File.Close(fileHandle);

	typedef int (*NeedDebugDataFn)(CFlatRuntime2*);
	NeedDebugDataFn needDebugData = reinterpret_cast<NeedDebugDataFn>((*reinterpret_cast<void***>(this))[0x12]);

	if (needDebugData(this) != 0) {
		int debugChunk = 0;
		for (int debugIndex = 0;; debugIndex++) {
			sprintf(path, sCFlatRuntime2DebugFileNameFmt, fileName);
			if (debugIndex != 0) {
				sprintf(path, "%s%d", path, debugIndex);
			}

			fileHandle = File.Open(path, 0, CFile::PRI_LOW);
			if (fileHandle == 0) {
				return 0;
			}

			File.Read(fileHandle);
			File.SyncCompleted(fileHandle);
			debugChunk = reinterpret_cast<CFlatRuntime*>(this)->CreateDebug(File.m_readBuffer, debugChunk);
			File.Close(fileHandle);

			if (debugChunk == -1) {
				break;
			}
		}
	}

	resetChangeScript();
	if (System.m_execParam > 2) {
		System.Printf(const_cast<char*>(sCFlatRuntime2LoadMsg));
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 5) == 5) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gObject)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 5) == 5) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 3) == 3) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gQuadObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 3) == 3) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 0xAD) == 0xAD) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gMonObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 0xAD) == 0xAD) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = root->m_next->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 0x1D) == 0x1D) {
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
	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	CFlatRuntime::CObject* object = reinterpret_cast<CFlatRuntime::CObject*>(gItemObj)->m_next;

	while (object != root) {
		if (object->m_classIndex >= 0) {
			u8 flags = object->m_flags;
			if ((int)(flags << 24) >= 0 && (int)((flags << 25) | (flags >> 7)) >= 0) {
				if ((static_cast<u16>(reinterpret_cast<CGBaseObj*>(object)->GetCID()) & 0x1D) == 0x1D) {
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
	reinterpret_cast<CFlatRuntime*>(this)->Destroy();
	reinterpret_cast<CFlatData*>(reinterpret_cast<u8*>(this) + 0xCF20)->Destroy();

	CFlatLayerResource* layer = LayerResources(this);
	int zero = 0;
	for (int i = 0; i < 8; i++, layer++) {
		CFile::CHandle* fileHandle = layer->m_fileHandle;
		if (fileHandle != 0) {
			File.Close(fileHandle);
			layer->m_fileHandle = reinterpret_cast<CFile::CHandle*>(zero);
		}

		CTextureSet* textureSet = layer->m_textureSet;
		if (textureSet != 0) {
			delete textureSet;
			layer->m_textureSet = reinterpret_cast<CTextureSet*>(zero);
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
		CFlatLayerResource* layer = &LayerResources(this)[i];
		CFile::CHandle* fileHandle = layer->m_fileHandle;
		if (fileHandle == 0) {
			continue;
		}

		if (File.IsCompleted(fileHandle)) {
			CTextureSet* textureSet = layer->m_textureSet;
			if (textureSet != 0) {
				(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
				layer->m_textureSet = 0;
			}

			textureSet = new (getStage(), const_cast<char*>(sCFlatRuntime2FileTag), 0x335) CTextureSet;
			layer->m_textureSet = textureSet;
			if (textureSet != 0) {
				textureSet->Create(
					File.m_readBuffer,
					GET_CHARA_ALLOC_STAGE_S(layer->m_allocStage, Game.m_mainStage),
					0, 0, 0, 0);
			}

			File.Close(fileHandle);
			layer->m_fileHandle = 0;
		}
	}

	u16 button = 0;
	if (Pad._452_4_ == 0) {
		const u32 padIndex = static_cast<u32>((1 - Pad._448_4_) | (Pad._448_4_ - 1)) >> 31;
		button = *reinterpret_cast<u16*>(PadRaw() + padIndex * 0x54 + 0x36);
	}

	if (((button & 0x400) != 0) && (CFlatSaveSceneEnabled() != 0)) {
		CFlatSaveSceneEnabled() = 0;
	}

	if (CFlatSaveSceneEnabled() != 0) {
		Graphic.Printf(2, 3, const_cast<char*>(sCFlatRuntime2SaveSceneMsg));

		u32* saveData = new (getStage(), const_cast<char*>(sCFlatRuntime2FileTag), 0x36F) u32[0x3FF];
		u32* objectData = saveData + 8;

		saveData[0] = SwapF32(CameraPcs.m_positionX);
		saveData[1] = SwapF32(CameraPcs.m_positionY);
		saveData[2] = SwapF32(CameraPcs.m_positionZ);
		saveData[3] = SwapF32(CameraPcs.m_targetX);
		saveData[4] = SwapF32(CameraPcs.m_targetY);
		saveData[5] = SwapF32(CameraPcs.m_targetZ);
		saveData[6] = SwapF32(CameraPcs.m_fov);
		saveData[7] = SwapF32((FLOAT_80330138 * *reinterpret_cast<float*>(CameraPcsRaw() + 0x108)) / FLOAT_8033013C);

		u32 lastX = 0;
		u32 lastY = 0;
		u32 lastZ = 0;
		u32 lastRotY = 0;
		u32 lastUnknown188 = 0;
		u32 lastBodyRadius = 0;

		for (CGObject* object = FindGObjFirst(); object != 0; object = FindGObjNext(object)) {
			if (object->m_charaModelHandle == 0) {
				continue;
			}

			Vec pos = object->m_worldPosition;
			if ((object->m_weaponNodeFlags & 1) != 0) {
				PSVECAdd(&pos, &object->m_attachOwner->m_worldPosition, &pos);
			}

			objectData[0] = Swap32(static_cast<u32>(static_cast<int>(object->m_particleId)));
			lastX = SwapF32(pos.x);
			lastY = SwapF32(pos.y);
			lastZ = SwapF32(pos.z);
			lastRotY = SwapF32(object->m_rotBaseY);
			lastUnknown188 = SwapF32(object->unk_0x188);
			lastBodyRadius = SwapF32(object->m_bodyEllipsoidRadius);
			objectData[1] = lastX;
			objectData[2] = lastY;
			objectData[3] = lastZ;
			objectData[4] = lastRotY;
			objectData[5] = lastUnknown188;
			objectData[6] = lastBodyRadius;
			objectData += 7;
		}

		objectData[0] = Swap32(0xFFFFFFFF);
		objectData[1] = lastX;
		objectData[2] = lastY;
		objectData[3] = lastZ;
		objectData[4] = lastRotY;
		objectData[5] = lastUnknown188;
		objectData[6] = lastBodyRadius;
		delete[] saveData;
	}

	DebugDrawCCCount(runtime) = 0;
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
	CFont* font = *reinterpret_cast<CFont**>(MenuPcsRaw() + 0x248);
	font->SetScale(1.0f);
	font->SetShadow(1);
	font->SetMargin(0.0f);
	font->SetZMode(0, 0);
	font->DrawInit();
	font->SetTlut(7);
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	font->SetColor(color);

	CFlatRuntime::CObject* const root =
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
	for (CGObject* object = reinterpret_cast<CGObject*>(
			 FindNextGBaseObjByCidMask(this, root->m_next->m_next, 5));
		 object != 0;
		 object = reinterpret_cast<CGObject*>(FindNextGBaseObjByCidMask(
			 this, reinterpret_cast<CFlatRuntime::CObject*>(object)->m_next, 5))) {
		object->DrawDebug(font);
	}

	font->SetZMode(0, 0);
	font->SetPosZ(1.0f);
	Mtx44 projection;
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcsRaw() + 0x40), projection);
	GXSetProjection(projection, GX_PERSPECTIVE);

	font->SetScale(0.875f);
	font->SetShadow(1);
	font->SetMargin(0.0f);
	font->SetZMode(1, 1);
	font->DrawInit();

	for (CGItemObj* item = reinterpret_cast<CGItemObj*>(
			 FindNextGBaseObjByCidMask(this, root->m_next->m_next, 0x1D));
		 item != 0;
		 item = reinterpret_cast<CGItemObj*>(FindNextGBaseObjByCidMask(
			 this, reinterpret_cast<CFlatRuntime::CObject*>(item)->m_next, 0x1D))) {
		item->DrawOmoideName(font);
	}

	font->SetZMode(0, 0);
	font->SetPosZ(1.0f);
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcsRaw() + 0x40), projection);
	GXSetProjection(projection, GX_PERSPECTIVE);

	Mtx cameraMtx;
	PSMTXCopy(*reinterpret_cast<Mtx*>(CameraPcsRaw() + 0x10), cameraMtx);

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
	if ((RuntimeDebugFlags(runtime) & CFlatRuntimeDebugFlag_ParticleLines) != 0) {
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
		((RuntimeDebugFlags(runtime) & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) ||
		((MiniGamePcsRaw()[0x25732] & 0x80) != 0);
	const int debugCount = DebugDrawCCCount(runtime);
	if (showDebugCC && debugCount != 0) {
		GXColor greenColor = {0x80, 0xFF, 0x80, 0xFF};
		GXColor blueColor = {0x80, 0x80, 0xFF, 0xFF};
		GXColor redColor = {0xFF, 0x00, 0x00, 0xFF};
		Vec worldUp = {0.0f, 1.0f, 0.0f};
		float ringVerts[8][3];

		CFlatDebugDrawCC* entry = DebugDrawCCEntries(runtime);
		for (int i = 0; i < debugCount; i++) {
			const u8 flags = entry->m_flags;
			GXColor* drawColor = &greenColor;
			if ((flags & 0x80) != 0) {
				drawColor = &redColor;
			} else if ((flags & 0x40) != 0) {
				drawColor = &blueColor;
			}
			GXSetChanMatColor(GX_COLOR0A0, *drawColor);

			Vec* start = &entry->m_from;
			Vec* end = &entry->m_to;
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

			const float radius = entry->m_radius;
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

			entry++;
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
	int& count = DebugDrawCCCount(runtime);

	if (static_cast<unsigned int>(count) < 0x10U) {
		CFlatDebugDrawCC* slot = &DebugDrawCCEntries(runtime)[count];
		slot->m_from = *from;
		slot->m_to = *to;

		slot->m_flags = static_cast<u8>((bit7 << 7) | (slot->m_flags & 0x7F));
		slot->m_flags = static_cast<u8>(((bit6 << 6) & 0x40) | (slot->m_flags & 0xBF));

		const int index = count;
		count = index + 1;
		slot->m_radius = radius;
		return;
	}

	if (gCFlatRuntime2DebugDrawOverflowInit == 0) {
		gCFlatRuntime2DebugDrawOverflowFrame = 0;
		gCFlatRuntime2DebugDrawOverflowInit = 1;
	}

	if (gCFlatRuntime2DebugDrawOverflowFrame != static_cast<int>(System.m_frameCounter)) {
		printf(sCFlatRuntime2DebugDrawOverflowMsg);
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
		reinterpret_cast<CFlatRuntime::CObject*>(reinterpret_cast<u8*>(this) + 0x8CC);
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
	CFlatLayerResource* layer = &LayerResources(this)[layerNo];

	CTextureSet* textureSet = layer->m_textureSet;
	if (textureSet != 0) {
		(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
		layer->m_textureSet = 0;
	}

	char path[0x104];
	sprintf(path, sCFlatRuntime2TexturePathFmt, Game.GetLangString(), fileName);

	CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	if (fileHandle != 0) {
		File.Read(fileHandle);
		File.SyncCompleted(fileHandle);

		textureSet = new (Game.m_mainStage, const_cast<char*>(sCFlatRuntime2FileTag), 0x4F4) CTextureSet;
		layer->m_textureSet = textureSet;
		if (textureSet != 0) {
			textureSet->Create(File.m_readBuffer, Game.m_mainStage, 0, 0, 0, 0);
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
	return static_cast<unsigned int>(__cntlzw(reinterpret_cast<int>(LayerResources(this)[layerNo].m_fileHandle))) >> 5;
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
	CFlatLayerResource* layer = &LayerResources(this)[layerNo];

	CFile::CHandle* fileHandle = layer->m_fileHandle;
	if (fileHandle != 0) {
		File.Close(fileHandle);
		layer->m_fileHandle = 0;
	}

	void* textureSet = layer->m_textureSet;
	if (textureSet != 0) {
		(*(void (**)(void*, int))(*reinterpret_cast<int*>(textureSet) + 8))(textureSet, 1);
		layer->m_textureSet = 0;
	}

	char path[0x104];
	sprintf(path, sCFlatRuntime2TexturePathFmt, Game.GetLangString(), fileName);

	fileHandle = File.Open(path, 0, CFile::PRI_LOW);
	layer->m_fileHandle = fileHandle;
	if (fileHandle != 0) {
		File.ReadASync(fileHandle);
	}

	layer->m_allocStage = *reinterpret_cast<int*>(reinterpret_cast<u8*>(&CharaPcs) + 0xE4);
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
	CTextureSet* textureSet = LayerResources(this)[layerNo].m_textureSet;
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
			_GXTexObj* backTex = Graphic.GetBackBufferRect(rectX, rectY, rectW, rectH, 0);
			GXLoadTexObj(backTex, GX_TEXMAP1);

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
	PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcsRaw() + 0x40), projection);
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
	ParticleWork(this) = CParticleWork();

	ParticleWork(this).m_enable = 1;
	*reinterpret_cast<int*>(runtime + 0x1738) = workNo >> 8;
	ParticleWork(this).m_arg = 0;
	*reinterpret_cast<unsigned int*>(runtime + 0x173C) = static_cast<unsigned int>(workNo) & 0xFF;
	*reinterpret_cast<float*>(runtime + 0x1740) = pos.x;
	*reinterpret_cast<float*>(runtime + 0x1744) = pos.y;
	*reinterpret_cast<float*>(runtime + 0x1748) = pos.z;
	*reinterpret_cast<float*>(runtime + 0x1750) = 0.0f;
	ParticleWorkPosPtr(this) = ParticleWorkPosValues(this);
	ParticleWorkPosVecPtr(this) = ParticleWorkPosVecValues(this);
	*reinterpret_cast<float*>(runtime + 0x1760) = scale;
	*reinterpret_cast<float*>(runtime + 0x175C) = scale;
	*reinterpret_cast<float*>(runtime + 0x1758) = scale;
	ParticleWorkScalePtr(this) = ParticleWorkScaleValues(this);

	PartMng.pppCreate(
		*reinterpret_cast<int*>(runtime + 0x1738), *reinterpret_cast<unsigned int*>(runtime + 0x173C),
		reinterpret_cast<PPPCREATEPARAM*>(runtime + 0x16CC), 1);
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
	PartMng.pppCreate(
		ParticleWorkNoHi(this), ParticleWorkNoLo(this),
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
	ParticleWork(this) = CParticleWork();

	ParticleWork(this).m_enable = 1;
	ParticleWorkNoHi(this) = workNo >> 8;
	ParticleWork(this).m_arg = arg;
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
	ParticleWorkPosAngle(this) = FLOAT_80330138 * angle / FLOAT_8033013C;
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
	u8* runtime = reinterpret_cast<u8*>(this);
	ParticleWorkTargetX(this) = vec.x;
	ParticleWorkTargetY(this) = vec.y;
	ParticleWorkTargetZ(this) = vec.z;
	*reinterpret_cast<float**>(runtime + 0x16D8) = reinterpret_cast<float*>(runtime + 0x1764);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::SetParticleWorkVector(float angle1, float angle2)
{
	u8* runtime = reinterpret_cast<u8*>(this);
	float* target = reinterpret_cast<float*>(runtime + 0x1764);
	float cosAngle2 = static_cast<float>(cos(angle2));
	float sinAngle1 = static_cast<float>(sin(angle1));
	*reinterpret_cast<float*>(runtime + 0x1764) =
		sinAngle1 * cosAngle2 + *reinterpret_cast<float*>(runtime + 0x1740);

	float sinAngle2 = static_cast<float>(sin(angle2));
	*reinterpret_cast<float*>(runtime + 0x1768) =
		*reinterpret_cast<float*>(runtime + 0x1744) + sinAngle2;

	cosAngle2 = static_cast<float>(cos(angle2));
	float cosAngle1 = static_cast<float>(cos(angle1));
	*reinterpret_cast<float*>(runtime + 0x176C) =
		cosAngle1 * cosAngle2 + *reinterpret_cast<float*>(runtime + 0x1748);
	*reinterpret_cast<float**>(runtime + 0x16D8) = target;
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
	u8* runtime = reinterpret_cast<u8*>(this);
	ParticleWorkScaleZ(this) = scale;
	ParticleWorkScaleY(this) = scale;
	ParticleWorkScaleX(this) = scale;
	*reinterpret_cast<float**>(runtime + 0x16D4) = reinterpret_cast<float*>(runtime + 0x1758);
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
	short paramId;

	ParticleWorkParamNo(this) = paramNo;
	if (object != 0) {
		paramId = *reinterpret_cast<short*>(reinterpret_cast<u8*>(object) + 0x30);
	} else {
		paramId = 0;
	}
	ParticleWorkParamId(this) = paramId;
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
int CFlatRuntime2::GetFreeParticleSlot()
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
	memset(CGPartyObj::m_ghostWork, 0, sizeof(CGPartyObj::m_ghostWork));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::reqFinished(int reqNo, CFlatRuntime::CObject* object)
{
	if (reqNo == 0xF) {
		reinterpret_cast<CGBaseObj*>(object)->InitFinished();
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
		Game.m_gameWork.m_radarType = value8;
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
		MenuPcs.ClrBattleItem();
		break;

	case 0xA:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xEF) | ((value8 & 1) << 4));
		break;

	case 0xB:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xDF) | ((value8 & 1) << 5));
		break;

	case 0xE:
		runtime[0x12E4] = static_cast<u8>((runtime[0x12E4] & 0xFD) | ((value8 & 1) << 1));
		gChara.ChangeMogMode(controlValue);
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
		gChara.TimeMogFur();
		break;

	case 0x17:
	*reinterpret_cast<unsigned int*>(PadRaw() + 0x1C8) = static_cast<unsigned int>(controlValue);
		break;

	case 0x18:
		Game.LoadLogoWaitingData();
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

	switch (controlNo) {
	case 3:
		return reinterpret_cast<RuntimeSysControlView*>(CFlat)->m_control;
	default:
		return 0;
	}
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
		memset(reinterpret_cast<u8*>(this) + 0x12F0, 0, sizeof(u32) * 2 * kFlatSpawnBitCount);
		return;
	}

	if (spawnBit < 0) {
		return;
	}

	if (spawnBit <= 8) {
		spawnBit <<= 3;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + spawnBit + 0x12F4) = 0;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + spawnBit + 0x12F0) = 0;
	}
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
	u8* runtime = reinterpret_cast<u8*>(this);

	*reinterpret_cast<u32*>(runtime + 0x10404) = 0;
	*reinterpret_cast<u32*>(runtime + 0x12A8) = 0;
	*reinterpret_cast<u32*>(runtime + 0x12AC) = 0;
	*reinterpret_cast<u32*>(runtime + 0x1BF4) = 0;
	*reinterpret_cast<u32*>(runtime + 0x2708) = 0;
	*reinterpret_cast<u32*>(runtime + 0x321C) = 0;
	*reinterpret_cast<u32*>(runtime + 0x3D30) = 0;
	*reinterpret_cast<u32*>(runtime + 0x4844) = 0;
	*reinterpret_cast<u32*>(runtime + 0x5358) = 0;
	*reinterpret_cast<u32*>(runtime + 0x5E6C) = 0;
	*reinterpret_cast<u32*>(runtime + 0x6980) = 0;
	*reinterpret_cast<u32*>(runtime + 0x7494) = 0;
	*reinterpret_cast<u32*>(runtime + 0x7FA8) = 0;
	*reinterpret_cast<u32*>(runtime + 0x8ABC) = 0;
	*reinterpret_cast<u32*>(runtime + 0x95D0) = 0;
	*reinterpret_cast<u32*>(runtime + 0xA0E4) = 0;
	*reinterpret_cast<u32*>(runtime + 0xABF8) = 0;
	*reinterpret_cast<u32*>(runtime + 0xB70C) = 0;
	*reinterpret_cast<u32*>(runtime + 0xC220) = 0;

	int count = 2;
	u8* block = runtime;
	do {
		block[0x134D] = 0;
		block[0x134C] = 0xFF;
		block[0x1361] = 0;
		block[0x1360] = 0xFF;
		block[0x1375] = 0;
		block[0x1374] = 0xFF;
		block[0x1389] = 0;
		block[0x1388] = 0xFF;
		block[0x139D] = 0;
		block[0x139C] = 0xFF;
		block[0x13B1] = 0;
		block[0x13B0] = 0xFF;
		block[0x13C5] = 0;
		block[0x13C4] = 0xFF;
		block[0x13D9] = 0;
		block[0x13D8] = 0xFF;
		block[0x13ED] = 0;
		block[0x13EC] = 0xFF;
		block[0x1401] = 0;
		block[0x1400] = 0xFF;
		block[0x1415] = 0;
		block[0x1414] = 0xFF;
		block[0x1429] = 0;
		block[0x1428] = 0xFF;
		block[0x143D] = 0;
		block[0x143C] = 0xFF;
		block[0x1451] = 0;
		block[0x1450] = 0xFF;
		block[0x1465] = 0;
		block[0x1464] = 0xFF;
		block[0x1479] = 0;
		block[0x1478] = 0xFF;

		block += 0xF8;
		count--;
	} while (count != 0);

	*reinterpret_cast<u32*>(runtime + 0x1040C) = 0;
	*reinterpret_cast<u32*>(runtime + 0x10410) = 0;
	*reinterpret_cast<u32*>(runtime + 0x10414) = 0;
	runtime[0x12E4] = (runtime[0x12E4] & 0x7F) | 0x80;
	runtime[0x12E4] &= 0xDF;
	runtime[0x12E4] &= 0xEF;
	*reinterpret_cast<u32*>(runtime + 0x12E8) = 0;
	*reinterpret_cast<u32*>(runtime + 0x12EC) = 0;
	memset(&CFlatPartyTraceParticleSlot(0), 0, sizeof(int) * 5);
	memset(m_boss__8CGMonObj, 0, sizeof(m_boss__8CGMonObj));
	runtime[0x12E4] &= 0xFD;
	runtime[0x12E4] &= 0xF7;
	runtime[0x12E4] &= 0xFE;
	*reinterpret_cast<u32*>(PadRaw() + 0x1C8) = 1;
	*reinterpret_cast<u32*>(GraphicPcsRaw() + 0x44) = 0;
	*reinterpret_cast<u32*>(CameraPcsRaw() + 0x434) = 1;
	AStar.reset();
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
	memset(reinterpret_cast<u8*>(this) + 0x12F0, 0, sizeof(u32) * 2 * kFlatSpawnBitCount);
}
