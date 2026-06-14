#include "ffcc/cflat_r2class.h"
#include "ffcc/charaobj.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gobject.h"
#include "ffcc/joybus.h"
#include "ffcc/game.h"
#include "ffcc/monobj.h"
#include "ffcc/p_graphic.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_map.h"
#include "ffcc/pad.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/quadobj.h"
#include "ffcc/ringmenu.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"

#include <dolphin/mtx.h>
#include <math.h>

extern const char sCFlatRuntime2SetClassSystemValWarn[];
extern const char sCFlatRuntime2AnimStateWarn[];
extern const float kCFlatRuntime2Zero;
extern const float kCFlatRuntime2SystemValScale;

extern "C" const double kCharaViewerColorCenterBias = 4503601774854144.0;
extern "C" const float kCharaViewerZero = 0.0f;
extern "C" const float kCharaViewerBackOrthoRight = 448.0f;
extern "C" const float kCharaViewerBackOrthoBottom = 640.0f;
extern "C" const float kCharaViewerGridMax = -100.0f;

namespace {

typedef unsigned char u8;

static inline unsigned int& LastResult(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x96C);
}

static inline unsigned short EngineClassId(void* engineObject)
{
	return static_cast<unsigned short>(reinterpret_cast<CGObject*>(engineObject)->GetCID());
}

static inline unsigned int EngineGetClassControl(void* engineObject, unsigned int arg0)
{
	return static_cast<unsigned int>(
	    reinterpret_cast<CGPrgObj*>(engineObject)->GetClassControl(static_cast<int>(arg0)));
}

static inline void EngineClassControl(void* engineObject, unsigned int arg0, unsigned int arg1)
{
	reinterpret_cast<CGPrgObj*>(engineObject)->ClassControl(static_cast<int>(arg0), static_cast<int>(arg1));
}

static inline CGObject* FindRuntimeObject(CFlatRuntime2* runtime, unsigned int objectId)
{
	return static_cast<CGObject*>(runtime->intToClass(static_cast<int>(objectId)));
}

#define RuntimeString(runtime, index)                                                                         \
	(*reinterpret_cast<char**>(reinterpret_cast<u8*>(runtime) + 0x28) +                                        \
	 (*reinterpret_cast<unsigned short**>(reinterpret_cast<u8*>(runtime) + 0x2C))[index])

static inline unsigned int& RuntimeWorkAssignIndex(CFlatRuntime2* runtime)
{
	return runtime->m_workAssignIndex;
}

static inline unsigned int& RuntimePartyAssignIndex(CFlatRuntime2* runtime)
{
	return runtime->m_partyAssignIndex;
}

static inline CCaravanWork* ScriptCaravan(CGObject* engineObject)
{
	return reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
}

static inline CGObjWork* ScriptWork(CGObject* engineObject)
{
	return reinterpret_cast<CGObjWork*>(engineObject->m_scriptHandle);
}

static inline CMonWork* ScriptMonWork(CGObject* engineObject)
{
	return reinterpret_cast<CMonWork*>(engineObject->m_scriptHandle);
}

static inline int ScriptPlayerIndex(CGObject* engineObject)
{
	return ScriptCaravan(engineObject)->m_joybusCaravanId;
}

static inline CRingMenu* BattleRingMenu(int playerIndex)
{
	return MenuPcs.m_battleRingMenus[playerIndex];
}

#define PushValue(runtime, object, value) reinterpret_cast<CFlatRuntime*>(runtime)->push((object), (value))

static inline void StoreU16Value(CFlatRuntime::CStack* stack, unsigned short& value, int setMode)
{
	stack[-1].m_word = value;

	switch (setMode) {
	case -1:
		value = value - stack->m_word;
		break;
	case 0:
		value = stack->m_word;
		break;
	case 1:
		value = value + stack->m_word;
		break;
	}
}

static inline void StoreU16(CFlatRuntime::CStack* stack, u8* base, int offset, int setMode)
{
	StoreU16Value(stack, *reinterpret_cast<unsigned short*>(base + offset), setMode);
}

template <int disp>
static inline void StoreU16Idx(CFlatRuntime::CStack* stack, u8* base, int index, int setMode)
{
	base = base + index;
	StoreU16Value(stack, *reinterpret_cast<unsigned short*>(base + disp), setMode);
}

static inline void StoreS16Value(CFlatRuntime::CStack* stack, short& value, int setMode)
{
	stack[-1].m_word = value;

	switch (setMode) {
	case -1:
		value = value - stack->m_word;
		break;
	case 0:
		value = stack->m_word;
		break;
	case 1:
		value = value + stack->m_word;
		break;
	}
}

static inline void StoreS16(CFlatRuntime::CStack* stack, u8* base, int offset, int setMode)
{
	StoreS16Value(stack, *reinterpret_cast<short*>(base + offset), setMode);
}

template <int disp>
static inline void StoreS16Idx(CFlatRuntime::CStack* stack, u8* base, int index, int setMode)
{
	base = base + index;
	StoreS16Value(stack, *reinterpret_cast<short*>(base + disp), setMode);
}

static inline void StoreU32Value(CFlatRuntime::CStack* stack, unsigned int& value, int setMode)
{
	stack[-1].m_word = value;

	switch (setMode) {
	case -1:
		value -= stack->m_word;
		break;
	case 0:
		value = stack->m_word;
		break;
	case 1:
		value += stack->m_word;
		break;
	}
}

static inline void StoreU32(CFlatRuntime::CStack* stack, u8* base, int offset, int setMode)
{
	StoreU32Value(stack, *reinterpret_cast<unsigned int*>(base + offset), setMode);
}

static inline void StoreF32(CFlatRuntime::CStack* stack, u8* base, int offset, int setMode)
{
	float* value = reinterpret_cast<float*>(base + offset);
	*reinterpret_cast<float*>(&stack[-1].m_word) = *value;

	switch (setMode) {
	case -1:
		*value -= *reinterpret_cast<float*>(&stack->m_word);
		break;
	case 0:
		*value = *reinterpret_cast<float*>(&stack->m_word);
		break;
	case 1:
		*value += *reinterpret_cast<float*>(&stack->m_word);
		break;
	}
}

static inline unsigned int LoadU16(u8* base, int offset)
{
	return *reinterpret_cast<unsigned short*>(base + offset);
}

template <int disp>
static inline unsigned int LoadU16Idx(u8* base, int index)
{
	base = base + index;
	return *reinterpret_cast<unsigned short*>(base + disp);
}

static inline unsigned int LoadS16(u8* base, int offset)
{
	return static_cast<unsigned int>(*reinterpret_cast<short*>(base + offset));
}

template <int disp>
static inline unsigned int LoadS16Idx(u8* base, int index)
{
	base = base + index;
	return static_cast<unsigned int>(*reinterpret_cast<short*>(base + disp));
}

static inline unsigned int LoadU32(u8* base, int offset)
{
	return *reinterpret_cast<unsigned int*>(base + offset);
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x800C7FE8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void VECNormalizeZero(Vec* src, Vec* dst)
{
	float magnitude = PSVECMag(src);
	if (magnitude == 0.0f) {
		dst->x = 0.0f;
		dst->y = 0.0f;
		dst->z = 0.0f;
	} else {
		PSVECScale(src, dst, 1.0f / magnitude);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C8050
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPad::IsGba(long padNo)
{
	if (padNo < 0 || padNo >= 4) {
		return 0;
	}
	return m_padInputs[padNo].gbaMode != 0;
}

/*
 * --INFO--
 * PAL Address: 0x800C80B0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMonWork* SAFE_CAST_MON_WORK(CGObjWork* work)
{
	if (work == 0 || work->m_objType != 1) {
		return 0;
	}
	return static_cast<CMonWork*>(work);
}

/*
 * --INFO--
 * PAL Address: 0x800C812C
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCaravanWork* SAFE_CAST_CARAVAN_WORK(CGObjWork* work)
{
	if (work == 0 || work->m_objType != 0) {
		return 0;
	}
	return static_cast<CCaravanWork*>(work);
}

/*
 * --INFO--
 * PAL Address: 0x800C81A8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetDamageColMask(int index, int mask)
{
	if (index < 0) {
		for (int i = 0; i < 8; ++i) {
			m_damageColliders[i].m_hitMask = mask;
		}
	} else if (index < 8) {
		m_damageColliders[index].m_hitMask = mask;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C81E4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGObject::SetAttackColMask(int index, int mask)
{
	if (index < 0) {
		for (int i = 0; i < 8; ++i) {
			m_attackColliders[i].m_hitMask = mask;
		}
	} else if (index < 8) {
		m_attackColliders[index].m_hitMask = mask;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800C8220
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGObject::IsFall(int, int)
{
	return (m_stateFlags0 & 0x80) != 0;
}

/*
 * --INFO--
 * PAL Address: 0x800BA2FC
 * PAL Size: 3800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime2::onSetClassSystemVal(int systemVal, CFlatRuntime::CObject* object, CFlatRuntime::CStack* stack, int setMode)
{
	u8* const engineObject = reinterpret_cast<u8*>(object);
	const unsigned short engineFlags = EngineClassId(engineObject);

	if ((engineFlags & 5) != 5 && systemVal == -0x1B) {
		if (static_cast<unsigned int>(System.m_execParam) >= 2) {
			System.Printf(const_cast<char*>(sCFlatRuntime2SetClassSystemValWarn));
		}
		return;
	}

	{
		if (systemVal <= -0x40) {
			u8* const classData = *reinterpret_cast<u8**>(engineObject + 0x58);

				switch (systemVal) {
				case -0xDA7:
				case -0xDA6:
				case -0xDA5:
				case -0xDA4:
				case -0xDA3:
				case -0xDA2:
				case -0xDA1:
				case -0xDA0:
				case -0xD9F:
				case -0xD9E:
				case -0xD9D:
				case -0xD9C:
				case -0xD9B:
				case -0xD9A:
				case -0xD99:
				case -0xD98:
					StoreU16Idx<0xD0>(stack, classData, (systemVal + 0xDA7) * 2, setMode);
					break;
				case -0xDB7:
				case -0xDB6:
				case -0xDB5:
				case -0xDB4:
				case -0xDB3:
				case -0xDB2:
				case -0xDB1:
				case -0xDB0:
				case -0xDAF:
				case -0xDAE:
				case -0xDAD:
				case -0xDAC:
				case -0xDAB:
				case -0xDAA:
				case -0xDA9:
				case -0xDA8:
					StoreU16Idx<0xF0>(stack, classData, (systemVal + 0xDB7) * 2, setMode);
					break;
				case -0xDB8:
					StoreU16Value(stack, reinterpret_cast<CGMonObj*>(engineObject)->m_groupTag, setMode);
					break;
				case -0xDB9:
					StoreU16Value(stack, reinterpret_cast<CGMonObj*>(engineObject)->m_repop.delay, setMode);
					break;
				case -0xDBA:
					StoreU32Value(stack, reinterpret_cast<CGMonObj*>(engineObject)->m_controlMask, setMode);
					break;
				default:
					if (systemVal <= -1000 && systemVal >= -0xBE7) {
						const int bit = systemVal + 0xBE7;
						u8* const byteRef = classData + (bit / 8);
						const int mask = 1 << (bit % 8);
						const int oldValue = (byteRef[0x8A4] & mask) != 0;

						stack[-1].m_word = oldValue;
						int newValue = oldValue;

						switch (setMode) {
						case -1:
							newValue -= stack->m_word;
							break;
						case 0:
							newValue = stack->m_word;
							break;
						case 1:
							newValue += stack->m_word;
							break;
						}

						if (newValue != 0) {
							byteRef[0x8A4] |= mask;
						} else {
							byteRef[0x8A4] &= ~mask;
						}
					} else if (systemVal <= -0x1F4 && systemVal >= -0x2F3) {
						StoreS16Idx<0x9A4>(stack, classData, (systemVal + 0x2F3) * 2, setMode);
					} else {
						switch (systemVal) {
						case -0x199:
						case -0x198:
						case -0x197:
						case -0x196:
						case -0x195:
						case -0x194:
						case -0x193:
						case -0x192:
							StoreU16Idx<0x3B8>(stack, classData, (systemVal + 0x199) * 2, setMode);
							break;
						case -0x19C:
							StoreU32(stack, classData, 0x200, setMode);
							break;
						case -0x19D:
							StoreU16(stack, classData, 0x3C8, setMode);
							break;
						case -0x1A9:
						case -0x1A8:
						case -0x1A7:
						case -0x1A6:
							StoreS16Idx<0xAC>(stack, classData, (systemVal + 0x1A9) * 2, setMode);
							break;
						case -0x1B6:
							StoreU16(stack, classData, 0x3DE, setMode);
							break;
						default:
							if (systemVal <= -0x96 && systemVal >= -0x175) {
								const int itemOffset = (systemVal + 0x175) * 2;
								stack[-1].m_word =
								    *reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset);
								switch (setMode) {
								case -1:
									*reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset) =
									    *reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset) -
									    stack->m_word;
									break;
								case 0:
									*reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset) =
									    stack->m_word;
									break;
								case 1:
									*reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset) =
									    *reinterpret_cast<unsigned short*>(*reinterpret_cast<u8**>(classData + 0x24) + itemOffset) +
									    stack->m_word;
									break;
								}
							} else {
								switch (systemVal) {
								case -0x40:
									StoreU16(stack, classData, 0x1A, setMode);
									break;
								case -0x41:
									StoreU16(stack, classData, 0x1C, setMode);
									break;
								case -0x79:
								case -0x78:
								case -0x77:
								case -0x76:
								case -0x75:
								case -0x74:
								case -0x73:
								case -0x72:
								case -0x71:
								case -0x70:
								case -0x6F:
								case -0x6E:
								case -0x6D:
								case -0x6C:
								case -0x6B:
								case -0x6A:
								case -0x69:
								case -0x68:
								case -0x67:
								case -0x66:
								case -0x65:
								case -0x64:
								case -0x63:
								case -0x62:
								case -0x61:
								case -0x60:
								case -0x5F:
								case -0x5E:
								case -0x5D:
								case -0x5C:
								case -0x5B:
								case -0x5A:
								case -0x59:
								case -0x58:
								case -0x57:
								case -0x56:
								case -0x55:
								case -0x54:
								case -0x53:
									StoreU16Idx<0x3E>(stack, classData, (-0x53 - systemVal) * 2, setMode);
									break;
								case -0x94:
								case -0x93:
								case -0x92:
								case -0x91:
								case -0x90:
								case -0x8F:
								case -0x8E:
								case -0x8D:
								case -0x8C:
								case -0x8B:
								case -0x8A:
								case -0x89:
								case -0x88:
								case -0x87:
								case -0x86:
								case -0x85:
									StoreU16Idx<0x8C>(stack, classData, (systemVal + 0x94) * 2, setMode);
									break;
								default:
									break;
								}
							}
							break;
						}
					}
					break;
				}

			LastResult(this) = 0;
		} else {
			switch (systemVal) {
				case -5:
					StoreF32(stack, engineObject, 0x184, setMode);
					break;
				case -9:
					StoreU32(stack, engineObject, 0x94, setMode);
					break;
				case -0xA: {
					CGObject* obj = reinterpret_cast<CGObject*>(engineObject);
					stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(obj->m_stateFlags0Bits.unk4));
					switch (setMode) {
					case -1:
						obj->m_stateFlags0Bits.unk4 = static_cast<signed char>(
						    obj->m_stateFlags0Bits.unk4 - static_cast<int>(stack->m_word));
						break;
					case 0:
						obj->m_stateFlags0Bits.unk4 = static_cast<signed char>(static_cast<signed char>(stack->m_word));
						break;
					case 1:
						obj->m_stateFlags0Bits.unk4 = static_cast<signed char>(
						    obj->m_stateFlags0Bits.unk4 + static_cast<int>(stack->m_word));
						break;
					}
					break;
				}
				case -0xB: {
					signed char* value = reinterpret_cast<signed char*>(engineObject + 0x53);
					stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(*value));
					switch (setMode) {
					case -1:
						*value = static_cast<unsigned char>(*value - static_cast<int>(stack->m_word));
						break;
					case 0:
						*value = static_cast<signed char>(stack->m_word);
						break;
					case 1:
						*value = static_cast<signed char>(*value + static_cast<int>(stack->m_word));
						break;
					}
					break;
				}
				case -0xD:
					StoreF32(stack, engineObject, 0x188, setMode);
					break;
				case -0xF:
					StoreU32(stack, engineObject, 0x500, setMode);
					break;
				case -0x10:
					StoreU32(stack, engineObject, 0x504, setMode);
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11:
					StoreS16Idx<0x510>(stack, engineObject, (systemVal + 0x14) * 2, setMode);
					break;
				case -0x15:
					StoreF32(stack, engineObject, 0x168, setMode);
					break;
				case -0x16:
					StoreF32(stack, engineObject, 0x16C, setMode);
					break;
				case -0x17:
					StoreF32(stack, engineObject, 0x170, setMode);
					break;
				case -0x18:
					StoreF32(stack, engineObject, 0x1BC, setMode);
					break;
					case -0x1A: {
						int value = 0;
						*reinterpret_cast<float*>(&stack[-1].m_word) = kCFlatRuntime2Zero;
						switch (setMode) {
						case -1:
							value = static_cast<int>(kCFlatRuntime2Zero - static_cast<float>(stack->m_word));
							break;
						case 0:
							value = static_cast<int>(*reinterpret_cast<float*>(&stack->m_word));
							break;
						case 1:
							value = static_cast<int>(kCFlatRuntime2Zero + static_cast<float>(stack->m_word));
							break;
						}
						*(engineObject + 0x56) = static_cast<u8>(static_cast<int>(kCFlatRuntime2SystemValScale * static_cast<float>(value)));
						break;
					}
				case -0x1B:
					StoreU32(stack, engineObject, 0x60, setMode);
					break;
				default:
					break;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800BB1D4
 * PAL Size: 1324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CVal* CFlatRuntime2::onClassSystemVal(CFlatRuntime::CObject* object, int systemVal)
{
	u8* const engineObject = reinterpret_cast<u8*>(object->m_engineObject);
	const unsigned short engineFlags = EngineClassId(engineObject);

	if (((engineFlags & 5) != 5) && (systemVal == -0x1B)) {
		if (static_cast<unsigned int>(System.m_execParam) >= 2) {
			System.Printf(const_cast<char*>(sCFlatRuntime2SetClassSystemValWarn));
		}
		LastResult(this) = 0;
		return reinterpret_cast<CFlatRuntime::CVal*>(&LastResult(this));
	} else {
		if (systemVal <= -0x40) {
			u8* const classData = *reinterpret_cast<u8**>(engineObject + 0x58);
			unsigned int value = 0;

			switch (systemVal) {
			case -0xD83:
			case -0xD82:
			case -0xD81:
			case -0xD80:
				value = LoadU16Idx<0xAC>(classData, (systemVal + 0xD83) * 2);
				break;
			case -0xD91:
			case -0xD90:
			case -0xD8F:
			case -0xD8E:
			case -0xD8D:
			case -0xD8C:
			case -0xD8B:
			case -0xD8A:
			case -0xD89:
			case -0xD88:
			case -0xD87:
			case -0xD86:
			case -0xD85:
			case -0xD84:
				value = LoadU16Idx<0xB4>(classData, (systemVal + 0xD91) * 2);
				break;
			case -0xD92: {
				u8* p = *reinterpret_cast<u8**>(engineObject + 0xF8);
				if (p != 0) {
					p = *reinterpret_cast<u8**>(p + 0x178);
					if (p != 0) {
						value = *reinterpret_cast<unsigned int*>(p + 0x14);
					} else {
						value = static_cast<unsigned int>(-1);
					}
				} else {
					value = static_cast<unsigned int>(-1);
				}
				break;
			}
			case -0xDA7:
			case -0xDA6:
			case -0xDA5:
			case -0xDA4:
			case -0xDA3:
			case -0xDA2:
			case -0xDA1:
			case -0xDA0:
			case -0xD9F:
			case -0xD9E:
			case -0xD9D:
			case -0xD9C:
			case -0xD9B:
			case -0xD9A:
			case -0xD99:
			case -0xD98:
				value = LoadU16Idx<0xD0>(classData, (systemVal + 0xDA7) * 2);
				break;
			case -0xDB7:
			case -0xDB6:
			case -0xDB5:
			case -0xDB4:
			case -0xDB3:
			case -0xDB2:
			case -0xDB1:
			case -0xDB0:
			case -0xDAF:
			case -0xDAE:
			case -0xDAD:
			case -0xDAC:
			case -0xDAB:
			case -0xDAA:
			case -0xDA9:
			case -0xDA8:
				value = LoadU16Idx<0xF0>(classData, (systemVal + 0xDB7) * 2);
				break;
			case -0xDBA:
				value = reinterpret_cast<CGMonObj*>(engineObject)->m_controlMask;
				break;
			default:
				if (systemVal <= -1000 && systemVal >= -0xBE7) {
					const int bit = systemVal + 0xBE7;
					const u8 byteValue = *(classData + (bit / 8) + 0x8A4);
					const unsigned int mask = 1U << (bit % 8);
					value = static_cast<unsigned int>((byteValue & mask) != 0);
				} else if (systemVal <= -500 && systemVal >= -0x2F3) {
					value = LoadS16Idx<0x9A4>(classData, (systemVal + 0x2F3) * 2);
				} else {
					switch (systemVal) {
					case -0x199:
					case -0x198:
					case -0x197:
					case -0x196:
					case -0x195:
					case -0x194:
					case -0x193:
					case -0x192:
						value = LoadU16Idx<0x3B8>(classData, (systemVal + 0x199) * 2);
						break;
					case -0x19C:
						value = LoadU32(classData, 0x200);
						break;
					case -0x19D:
						value = LoadU16(classData, 0x3C8);
						break;
					case -0x1A9:
					case -0x1A8:
					case -0x1A7:
					case -0x1A6:
						value = LoadS16Idx<0xAC>(classData, (systemVal + 0x1A9) * 2);
						break;
					case -0x1AA:
						value = LoadU16(classData, 0xB4);
						break;
					case -0x1B6:
						value = LoadU16(classData, 0x3DE);
						break;
					case -0x1C8: {
						CGObject* const carryObject = reinterpret_cast<CGPartyObj*>(engineObject)->m_partyData.carryObject;
						if (carryObject != 0) {
							value = static_cast<unsigned int>(*reinterpret_cast<short*>(reinterpret_cast<u8*>(carryObject) + 0x30));
						} else {
							value = 0;
						}
						break;
					}
					case -0x1C9:
						value = LoadU16(classData, 0xBC8);
						break;
					default:
						if (systemVal <= -0x96 && systemVal >= -0x175) {
							u8* itemTable = *reinterpret_cast<u8**>(classData + 0x24);
							value = LoadU16(itemTable, (systemVal + 0x175) * 2);
						} else {
							switch (systemVal) {
							case -0x82:
								value = LoadU16(classData, 0x14);
								break;
							case -0x83:
								value = LoadU16(classData, 0x16);
								break;
							case -0x84:
								value = LoadU16(classData, 0x18);
								break;
							case -0x40:
								value = LoadU16(classData, 0x1A);
								break;
							case -0x41:
								value = LoadU16(classData, 0x1C);
								break;
							case -0x43:
								value = LoadU16(classData, 0x1E);
								break;
							case -0x44:
								value = LoadU16(classData, 0x20);
								break;
							case -0x45:
								value = LoadU16(classData, 0x22);
								break;
							case -0x79:
							case -0x78:
							case -0x77:
							case -0x76:
							case -0x75:
							case -0x74:
							case -0x73:
							case -0x72:
							case -0x71:
							case -0x70:
							case -0x6F:
							case -0x6E:
							case -0x6D:
							case -0x6C:
							case -0x6B:
							case -0x6A:
							case -0x69:
							case -0x68:
							case -0x67:
							case -0x66:
							case -0x65:
							case -0x64:
							case -0x63:
							case -0x62:
							case -0x61:
							case -0x60:
							case -0x5F:
							case -0x5E:
							case -0x5D:
							case -0x5C:
							case -0x5B:
							case -0x5A:
							case -0x59:
							case -0x58:
							case -0x57:
							case -0x56:
							case -0x55:
							case -0x54:
							case -0x53:
								value = LoadU16Idx<0x3E>(classData, (-0x53 - systemVal) * 2);
								break;
							case -0x94:
							case -0x93:
							case -0x92:
							case -0x91:
							case -0x90:
							case -0x8F:
							case -0x8E:
							case -0x8D:
							case -0x8C:
							case -0x8B:
							case -0x8A:
							case -0x89:
							case -0x88:
							case -0x87:
							case -0x86:
							case -0x85:
								value = LoadU16Idx<0x8C>(classData, (systemVal + 0x94) * 2);
								break;
							default:
								break;
							}
						}
						break;
					}
				}
				break;
			}

			LastResult(this) = value;
		} else {
			switch (systemVal) {
				case -1:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x15C);
					break;
				case -2:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x160);
					break;
				case -3:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x164);
					break;
				case -4:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x1B4);
					break;
				case -5:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x184);
					break;
				case -6:
					LastResult(this) = static_cast<unsigned int>(*reinterpret_cast<short*>(engineObject + 0x30));
					break;
				case -7:
					LastResult(this) =
					    static_cast<unsigned int>(static_cast<int>((*(engineObject + 0x50) & 0xC0) << 0x18) >> 0x1F);
					break;
				case -8:
					LastResult(this) = (*reinterpret_cast<unsigned int*>(engineObject + 0x4CC) >> 0x17) & 0xF;
					break;
				case -9:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x94);
					break;
				case -0xA: {
					u8 bits = *(engineObject + 0x50);
					LastResult(this) = static_cast<unsigned int>(static_cast<int>((bits & 0xC) << 0x1C) >> 0x1F);
					break;
				}
				case -0xB:
					LastResult(this) = static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<signed char*>(engineObject + 0x53)));
					break;
				case -0xC: {
					u8 bits = *(engineObject + 0x50);
					LastResult(this) = static_cast<unsigned int>(static_cast<int>((bits & 0x60) << 0x19) >> 0x1F);
					break;
				}
				case -0xD:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x188);
					break;
				case -0xF:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x500);
					break;
				case -0x10:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x504);
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11: {
					LastResult(this) = LoadS16Idx<0x510>(engineObject, (systemVal + 0x14) * 2);
					break;
				}
				case -0x15:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x168);
					break;
				case -0x16:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x16C);
					break;
				case -0x17:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x170);
					break;
				case -0x18:
					*reinterpret_cast<float*>(&LastResult(this)) = *reinterpret_cast<float*>(engineObject + 0x1BC);
					break;
				case -0x19:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x520);
					break;
				case -0x1B:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x60);
					break;
				default:
					break;
			}
		}
	}

	return reinterpret_cast<CFlatRuntime::CVal*>(&LastResult(this));
}

/*
 * --INFO--
 * PAL Address: 0x800bb700
 * PAL Size: 8520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime2::onClassSystemFunc(CFlatRuntime::CObject* object, int, int command, int& outResult)
{
	CGCharaObj* engineObject = reinterpret_cast<CGCharaObj*>(object->m_engineObject);

	switch (command) {
		case -5:
			engineObject->LoadModel(
			    static_cast<int>(object->m_localBase[0]), object->m_localBase[1], object->m_localBase[2], 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -6: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->SetPosBG(CVector(params[0], params[1], params[2]), 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -7:
			engineObject->m_animStateMisc = static_cast<unsigned char>(object->m_localBase[0]);
			{
				signed char animState = static_cast<signed char>(engineObject->m_animStateMisc);
				if (((animState < 0) || (animState >= 4)) && static_cast<unsigned int>(System.m_execParam) >= 2) {
					System.Printf(const_cast<char*>(sCFlatRuntime2AnimStateWarn));
				}
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -8:
			engineObject->m_weaponNodeFlagAll.m_bits1.m_shield = static_cast<signed char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -9:
			engineObject->m_moveBaseSpeed = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0xA:
			engineObject->m_rotTargetY = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0xD: {
			int mode = static_cast<int>(object->m_localBase[0]);
			float* params = reinterpret_cast<float*>(object->m_localBase);
			float radius = params[1];
			float offset = params[4];
			switch (mode) {
			case 0:
				engineObject->m_capsuleHalfHeight = radius;
				break;
			case 1:
				engineObject->m_bodyEllipsoidRadius = radius;
				engineObject->m_bodyEllipsoidOffset = offset;
				break;
			case 3:
				engineObject->m_attackColRadius = radius;
				break;
			case 2:
				engineObject->m_bodyColRadius = radius;
				break;
			case 4:
				engineObject->m_nearColRadius = radius;
				break;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x13:
			engineObject->m_bgColMask = object->m_localBase[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x9C:
			PushValue(this, object, static_cast<int>(engineObject->m_bgColMask));
			outResult = 0;
			break;
		case -0xE:
			engineObject->LoadAnim(
			    RuntimeString(this, object->m_localBase[0]),
			    static_cast<int>(object->m_localBase[1]),
			    static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]),
			    object->m_localBase[4]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0xF:
			engineObject->SetAnimSlot(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x10:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 0, -1, -1, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x11:
			if (engineObject->IsAnimFinished(0) != 0) {
				PushValue(this, object, 0);
				outResult = 0;
			}
			break;
		case -0x12:
			engineObject->CancelAnim(1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x14: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 0, 1, 0, 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x15:
			engineObject->m_weaponNodeFlagBits.m_unk10 = static_cast<signed char>(object->m_localBase[0]);
			engineObject->m_groundHitOffset.z = kCFlatRuntime2Zero;
			engineObject->m_groundHitOffset.y = kCFlatRuntime2Zero;
			engineObject->m_groundHitOffset.x = kCFlatRuntime2Zero;
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x16:
			engineObject->m_objectFlags = object->m_localBase[0];
			if ((engineObject->m_objectFlags & 0x10) != 0) {
				Game.unk_flat3_0xc7d0 = reinterpret_cast<unsigned int>(engineObject);
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x17:
			engineObject->m_displayFlags = object->m_localBase[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x18:
			engineObject->m_rotationX = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_rotationY = reinterpret_cast<float*>(object->m_localBase)[1];
			engineObject->m_rotationZ = reinterpret_cast<float*>(object->m_localBase)[2];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x19: {
			CGQuadObj* quad = reinterpret_cast<CGQuadObj*>(engineObject);
			if (static_cast<int>(object->m_localBase[0]) == 1) {
				quad->Reset(reinterpret_cast<float*>(object->m_localBase)[1], reinterpret_cast<float*>(object->m_localBase)[2]);
			}
			quad->Add(reinterpret_cast<float*>(object->m_localBase)[3], reinterpret_cast<float*>(object->m_localBase)[4]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x1D: {
			CVector moveDir(reinterpret_cast<float*>(object->m_localBase)[0],
			                reinterpret_cast<float*>(object->m_localBase)[1],
			                reinterpret_cast<float*>(object->m_localBase)[2]);
			engineObject->moveVector(
			    moveDir, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x1F:
			engineObject->m_attrFlags = object->m_localBase[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x20: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			Vec target;
			target.x = params[3];
			target.y = params[4];
			target.z = params[5];
			CGObject* hit = engineObject->CCClass(
			    static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), params[2], &target, params[6]);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[7]) =
				    *reinterpret_cast<short*>(reinterpret_cast<u8*>(hit) + 0x30);
			}
			PushValue(this, object, hit != 0);
			outResult = 0;
			break;
		}
		case -0x21: {
			Vec hitStart;
			Vec hitTarget;
			Vec hitMove;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			float radius = params[5];
			hitStart.x = engineObject->m_worldPosition.x;
			hitStart.y = engineObject->m_worldPosition.y + params[1];
			hitStart.z = engineObject->m_worldPosition.z;
			hitTarget.x = params[2];
			hitTarget.y = params[3];
			hitTarget.z = params[4];
			PSVECSubtract(&hitTarget, &hitStart, &hitMove);
			int hit = MapPcs.CheckHitCylinderNear(&hitStart, &hitMove, radius, object->m_localBase[0]);
			AddDebugDrawCC(&hitStart, &hitMove, radius, 1, 0);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[6]) = 0;
			}
			PushValue(this, object, hit);
			outResult = 0;
			break;
		}
		case -0x22:
			engineObject->unk_0x184 = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x23: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			CGObject* result = engineObject->CCClassRot(
			    static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), params[2], params[3],
			    params[4], params[5]);
			if (result != 0) {
				*reinterpret_cast<int*>(object->m_localBase[6]) =
				    *reinterpret_cast<short*>(reinterpret_cast<u8*>(result) + 0x30);
			}
			PushValue(this, object, result != 0);
			outResult = 0;
			break;
		}
		case -0x24: {
			Vec hitStart;
			Vec hitMove;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			float angle = params[2];
			float length = params[3];
			float radius = params[4];
			hitStart.x = engineObject->m_worldPosition.x;
			hitStart.y = engineObject->m_worldPosition.y + params[1];
			hitStart.z = engineObject->m_worldPosition.z;
			hitMove.x = static_cast<float>(sin(angle)) * length;
			hitMove.y = kCFlatRuntime2Zero;
			hitMove.z = static_cast<float>(cos(angle)) * length;
			int hit = MapPcs.CheckHitCylinderNear(&hitStart, &hitMove, radius, object->m_localBase[0]);
			AddDebugDrawCC(&hitStart, &hitMove, radius, 1, 0);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[5]) = 0;
			}
			PushValue(this, object, hit);
			outResult = 0;
			break;
		}
		case -0x25: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->SetPosBG(CVector(params[0], params[1], params[2]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x26: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 1, 1, 0, 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x27: {
			CGObject* target = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[0])));
			if (target != 0) {
				Vec attachPos;
				float* params = reinterpret_cast<float*>(object->m_localBase);
				attachPos.x = params[2];
				attachPos.y = params[3];
				attachPos.z = params[4];
				engineObject->Attach(target, RuntimeString(this, object->m_localBase[1]), &attachPos);
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x28:
			engineObject->Detach();
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x29:
			engineObject->DispCharaParts(static_cast<int>(object->m_localBase[0]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x2A:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x2B:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x2C: {
			Vec hitStart;
			Vec hitMove;
			float angle = reinterpret_cast<float*>(object->m_localBase)[2];
			float height = reinterpret_cast<float*>(object->m_localBase)[4];
			float distance = reinterpret_cast<float*>(object->m_localBase)[3];
			float radius = reinterpret_cast<float*>(object->m_localBase)[5];
			hitStart.x = engineObject->m_worldPosition.x + static_cast<float>(sin(angle)) * distance;
			hitStart.y = engineObject->m_worldPosition.y + reinterpret_cast<float*>(object->m_localBase)[1];
			hitStart.z = engineObject->m_worldPosition.z + static_cast<float>(cos(angle)) * distance;
			hitMove.x = kCFlatRuntime2Zero;
			hitMove.y = -height;
			hitMove.z = kCFlatRuntime2Zero;
			int hit = MapPcs.CheckHitCylinderNear(&hitStart, &hitMove, radius, object->m_localBase[0]);
			AddDebugDrawCC(&hitStart, &hitMove, radius, 1, 0);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[6]) = 0;
			}
			PushValue(this, object, hit);
			outResult = 0;
			break;
		}
		case -0x2D: {
			CVector attackOffset(reinterpret_cast<float*>(object->m_localBase)[3],
			                     reinterpret_cast<float*>(object->m_localBase)[4],
			                     reinterpret_cast<float*>(object->m_localBase)[5]);
			engineObject->SetAttackCol(
			    static_cast<int>(object->m_localBase[0]),
			    RuntimeString(this, object->m_localBase[1]),
			    reinterpret_cast<float*>(object->m_localBase)[2],
			    reinterpret_cast<Vec*>(&attackOffset));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x2E: {
			int index = static_cast<int>(object->m_localBase[0]);
			int x = static_cast<int>(object->m_localBase[1]);
			if (index == -1) {
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[1].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[2].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[3].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[4].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[5].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[6].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_attackColliders[7].m_localStart.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[0].m_localPosition.x) = x;
			} else {
				*reinterpret_cast<int*>(
				    reinterpret_cast<u8*>(&engineObject->m_attackColliders[1].m_localStart.x) + index * 0x30) = x;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x2F: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->SetDamageCol(
			    static_cast<int>(object->m_localBase[0]),
			    RuntimeString(this, object->m_localBase[1]),
			    params[2],
			    params[3],
			    CVector(params[4], params[5], params[6]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x30: {
			int index = static_cast<int>(object->m_localBase[0]);
			int x = static_cast<int>(object->m_localBase[1]);
			if (index == -1) {
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[1].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[2].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[3].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[4].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[5].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[6].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_damageColliders[7].m_localPosition.x) = x;
				*reinterpret_cast<int*>(&engineObject->m_animPhase) = x;
			} else {
				*reinterpret_cast<int*>(
				    reinterpret_cast<u8*>(&engineObject->m_damageColliders[1].m_localPosition.x) + index * 0x28) = x;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x31:
			engineObject->m_bgHitMask = object->m_localBase[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x33: {
			float rotY = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_rotTargetY = rotY;
			engineObject->m_rotBaseY = rotY;
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x34:
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				engineObject->ResetAnimPoint(static_cast<int>(object->m_localBase[1]));
			}
			engineObject->AddAnimPoint(
			    static_cast<int>(object->m_localBase[1]),
			    static_cast<int>(object->m_localBase[3]),
			    static_cast<int>(object->m_localBase[2]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x35: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 0, 0, 0, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x36: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			CVector moveDir(params[0], params[1], params[2]);
			engineObject->moveVectorH(moveDir, params[3], static_cast<int>(object->m_localBase[4]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x37: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 1, 0, 0, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x38:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 1, 0, -1, -1, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x39:
			engineObject->m_pushParamA = static_cast<unsigned char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x3A:
			engineObject->FreeAnim(static_cast<int>(object->m_localBase[0]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x1A:
			engineObject->Turn(reinterpret_cast<float*>(object->m_localBase)[0], static_cast<int>(object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x1B: {
			if (engineObject->m_weaponNodeFlagAll.m_bits1.m_bit20 == 0) {
				PushValue(this, object, 0);
				outResult = 0;
			}
			break;
		}
		case -0x1C:
			engineObject->CancelMove(1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x3B: {
			CGraphicPcs::ScreenFadeSlot* slot = &GraphicPcs.m_screenFade[2];
			slot->m_invert = static_cast<int>(object->m_localBase[0]);
			slot->m_mode = 1;
			slot->m_targetObj = engineObject;
			slot->m_targetYOffs = reinterpret_cast<float*>(object->m_localBase)[1];
			slot->m_colorA.r = static_cast<unsigned char>(object->m_localBase[2]);
			slot->m_colorA.g = static_cast<unsigned char>(object->m_localBase[3]);
			slot->m_colorA.b = static_cast<unsigned char>(object->m_localBase[4]);
			slot->m_colorA.a = 0xFF;
			slot->m_timer = static_cast<int>(object->m_localBase[5]);
			slot->m_duration = static_cast<int>(object->m_localBase[5]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x3C:
			engineObject->m_frontHitAngle = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x43: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->moveVectorRot(params[0], params[1], params[2], object->m_localBase[3]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x44: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->moveVectorHRot(params[0], params[1], params[2], object->m_localBase[3]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x45:
			engineObject->SetTexAnim(RuntimeString(this, object->m_localBase[0]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x46: {
			CGObject* target = 0;
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				target = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[0])));
			}
			engineObject->LookAt(target, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x8C: {
			CGObject* target = 0;
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				target = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[0])));
			}
			engineObject->LookAt(target, RuntimeString(this, object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x48:
			engineObject->m_stepSlopeLimit = reinterpret_cast<float*>(object->m_localBase)[1];
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				engineObject->m_lookAtTimer = engineObject->m_stepSlopeLimit;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x4F: {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			int mode = static_cast<int>(object->m_localBase[0]);
			int itemId = static_cast<int>(object->m_localBase[1]);
			int slot = -1;
			switch (mode) {
				case 1:
					caravanWork->AddItem(itemId, &slot);
					break;
				case 3:
					caravanWork->AddComList(itemId, &slot);
					break;
			}
			PushValue(this, object, slot);
			outResult = 0;
			break;
		}
		case -0x52: {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			unsigned int result = 0;
			if ((object->m_localBase[0] & 2) != 0) {
				result = caravanWork->FindItem(static_cast<int>(object->m_localBase[1])) >= 0 ? 2 : 0;
			}
			PushValue(this, object, static_cast<int>(result));
			outResult = 0;
			break;
		}
		case -0x53:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_gil = static_cast<int>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x55:
			reinterpret_cast<CGObjWork*>(engineObject->m_scriptHandle)->m_hp = static_cast<unsigned short>(object->m_localBase[1]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x56:
			reinterpret_cast<CGObjWork*>(engineObject->m_scriptHandle)->m_maxHp = static_cast<unsigned short>(object->m_localBase[1]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x5A:
			reinterpret_cast<CGObjWork*>(engineObject->m_scriptHandle)->m_statusValues[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x5C:
			reinterpret_cast<CMonWork*>(engineObject->m_scriptHandle)->unk_0xd0[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x5D:
			reinterpret_cast<CMonWork*>(engineObject->m_scriptHandle)->unk_0xf0[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x5F:
			if (engineObject->m_charaModelHandle != 0 && PartMng.pppIsDeadCHandle(engineObject->m_charaModelHandle) != 0) {
				PushValue(this, object, 0);
				outResult = 0;
			}
			break;
		case -0x60: {
			Vec safePos;
			float safeDist = engineObject->CalcSafePos(static_cast<int>(object->m_localBase[0]), static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[1]))), &safePos);
			*reinterpret_cast<float*>(object->m_localBase[2]) = safePos.x;
			*reinterpret_cast<float*>(object->m_localBase[3]) = safePos.y;
			*reinterpret_cast<float*>(object->m_localBase[4]) = safePos.z;
			PushValue(this, object, *reinterpret_cast<int*>(&safeDist));
			outResult = 0;
			break;
		}
		case -0x61:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->AddLetter(
			    static_cast<int>(object->m_localBase[0]),
			    static_cast<int>(object->m_localBase[1]),
			    static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]),
			    static_cast<int>(object->m_localBase[4]),
			    static_cast<int>(object->m_localBase[5]),
			    static_cast<int>(object->m_localBase[6]),
			    static_cast<int>(object->m_localBase[7]),
			    static_cast<int>(object->m_localBase[8]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x62: {
			unsigned int changed = static_cast<unsigned int>(Joybus.ChgCtrlMode(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId));
			unsigned int topBit = __cntlzw(changed);
			PushValue(this, object, (topBit >> 5) & 0xFF);
			outResult = 0;
			break;
		}
		case -0x63:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x64:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->unk_0x3e6 = static_cast<unsigned short>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x68:
			MenuPcs.m_battleRingMenus[reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId]
			    ->SetBattleButton(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x69:
			MenuPcs.m_battleRingMenus[reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId]
			    ->SetBattleCommand(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), -1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x6A:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x6C:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x6D:
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x6F:
			{
				float horizontal = reinterpret_cast<float*>(object->m_localBase)[0];
				engineObject->m_moveOffset.z = horizontal;
				engineObject->m_moveOffset.x = horizontal;
			}
			engineObject->m_moveOffset.y = reinterpret_cast<float*>(object->m_localBase)[1];
			engineObject->m_bounceFactor = reinterpret_cast<float*>(object->m_localBase)[2];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x70:
			engineObject->m_stateFlags0Bits.unk3 = static_cast<signed char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x71:
			engineObject->m_jumpLandingDampening = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x72:
			engineObject->SetDispItemName(static_cast<int>(object->m_localBase[0]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x73: {
			unsigned int buttons;
			int playerIndex = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId;
			bool useDebugPad = (Pad.m_debugPadLock != 0) || ((playerIndex == 0) && (Pad.m_debugPadPort != -1));
			if (useDebugPad) {
				buttons = 0;
			} else {
				unsigned int slot = static_cast<unsigned int>(playerIndex)
				    & ~((static_cast<int>(~(Pad.m_debugPadPort - playerIndex | playerIndex - Pad.m_debugPadPort)) >> 31));
				buttons = *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(&Pad) + 0x54 + slot * 0x54);
			}
			PushValue(this, object, static_cast<int>(buttons));
			outResult = 0;
			break;
		}
		case -0x74: {
			Vec moveVector;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveVector.x = params[0];
			moveVector.y = params[1];
			moveVector.z = params[2];
			float magnitude = PSVECMag(&moveVector);
			if (magnitude == 0.0f) {
				moveVector.x = 0.0f;
				moveVector.y = 0.0f;
				moveVector.z = 0.0f;
			} else {
				PSVECScale(&moveVector, &moveVector, 0.5f / magnitude);
			}
			engineObject->MoveVector(&moveVector, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]), 1, 1, 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x75: {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			if (static_cast<int>(caravanWork->m_evtState0) != static_cast<int>(object->m_localBase[0])) {
				caravanWork->m_evtState0 = object->m_localBase[0];
				caravanWork->m_evtState1 = 0;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x6E:
			engineObject->m_lastBgAttr = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x76:
			PushValue(this, object, static_cast<int>(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_evtState1));
			outResult = 0;
			break;
		case -0x77: {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			int mode = static_cast<int>(object->m_localBase[0]);
			int index = static_cast<int>(object->m_localBase[1]);
			switch (mode) {
				case 1:
					caravanWork->DeleteItemIdx(index, 1);
					break;
				case 3:
					caravanWork->DeleteCmdList(index, 1);
					break;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x78:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 0, 0, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x79: {
			signed char animList[8];
			int animCount = 0;
			int argCount = object->m_argCount - 1;
			if (argCount > 0) {
				animList[0] = static_cast<signed char>(object->m_localBase[1]);
				animCount = 1;
				if (argCount > 1) {
					animList[1] = static_cast<signed char>(object->m_localBase[2]);
					animCount = 2;
					if (argCount > 2) {
						animList[2] = static_cast<signed char>(object->m_localBase[3]);
						animCount = 3;
						if (argCount > 3) {
							animList[3] = static_cast<signed char>(object->m_localBase[4]);
							animCount = 4;
						}
					}
				}
			}
			animList[animCount] = static_cast<signed char>(0xFF);
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 0, -1, -1, animList);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7A:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 1, 0, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x7C:
			PushValue(
			    this, object, reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->GetFoodRank(static_cast<int>(object->m_localBase[0])));
			outResult = 0;
			break;
		case -0x7D: {
			float aspect = reinterpret_cast<float*>(object->m_localBase)[1];
			if (static_cast<int>(object->m_localBase[0]) == 1) {
				engineObject->m_bodyEllipsoidAspect = aspect;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7E: {
			int initArg = static_cast<int>(object->m_localBase[0]);
			unsigned int workIndex = this->m_workAssignIndex;
			this->m_workAssignIndex = workIndex + 1;
			engineObject->SetClassWork(1, static_cast<int>(workIndex));
			engineObject->InitWork(initArg);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7F: {
			unsigned int partyIndex = this->m_partyAssignIndex;
			this->m_partyAssignIndex = partyIndex + 1;
			if (Game.m_gameWork.m_wmBackupParams[partyIndex] >= 0) {
				engineObject->SetClassWork(0, static_cast<int>(partyIndex));
				reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId = static_cast<unsigned int>(partyIndex);
				Game.m_partyObjArr[partyIndex] = reinterpret_cast<CGPartyObj*>(engineObject);
				Joybus.SendAllStat(static_cast<int>(partyIndex));
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x54: {
			Vec moveVector;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			float rotX = params[0];
			float rotY = params[1];
			moveVector.x = static_cast<float>(sin(rotX)) * static_cast<float>(cos(rotY));
			moveVector.y = static_cast<float>(sin(rotY));
			moveVector.z = static_cast<float>(cos(rotX)) * static_cast<float>(cos(rotY));
			engineObject->MoveVector(&moveVector, params[2], static_cast<int>(object->m_localBase[3]), 0, 0, 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x4A:
			engineObject->m_hitNormal.x = reinterpret_cast<float*>(object->m_localBase)[0];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x4B:
			engineObject->ResetDynamics();
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x41:
			engineObject->m_bgDownDist = 0.5f / static_cast<float>(static_cast<int>(object->m_localBase[0]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x82:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 1, -1, -1, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x83:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 1, 1, -1, -1, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x85:
			PushValue(
			    this,
			    object,
			    reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->ShopRequest(
			        static_cast<int>(object->m_localBase[0]),
			        static_cast<int>(object->m_localBase[1]),
			        static_cast<int>(object->m_localBase[2]),
			        static_cast<int>(object->m_localBase[3]),
			        static_cast<int>(object->m_localBase[4]),
			        static_cast<int>(object->m_localBase[5]),
			        static_cast<int>(object->m_localBase[6])));
			outResult = 0;
			break;
		case -0x86: {
			CChara::CModel* model = engineObject->m_charaModelHandle->m_model;
			model->m_flags10CBits.m_flag10C_40 = static_cast<signed char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x87: {
			CChara::CModel* model = engineObject->m_charaModelHandle->m_model;
			float furLenScale = reinterpret_cast<float*>(object->m_localBase)[0];
			float furStep = reinterpret_cast<float*>(object->m_localBase)[1];
			model->m_furLenScale = furLenScale;
			model->m_furStep = furStep;
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x88: {
			Vec nearPos;
			engineObject->CalcSphereNearPos(reinterpret_cast<float*>(object->m_localBase)[0], reinterpret_cast<float*>(object->m_localBase)[1], nearPos);
			*reinterpret_cast<float*>(object->m_localBase[2]) = nearPos.x;
			*reinterpret_cast<float*>(object->m_localBase[3]) = nearPos.y;
			*reinterpret_cast<float*>(object->m_localBase[4]) = nearPos.z;
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x89: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]), 1, 1, 1, 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x8B:
			engineObject->m_moveModePrevious = static_cast<unsigned char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x8E:
			reinterpret_cast<CGPartyObj*>(engineObject)
			    ->carry(static_cast<int>(object->m_localBase[0]), static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[1]))), static_cast<int>(object->m_localBase[2]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x8D:
			reinterpret_cast<CGPartyObj*>(engineObject)->commandFinished();
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x8F:
			reinterpret_cast<CGPrgObj*>(engineObject)->ClassControl(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x90:
			engineObject->m_lookAtAccumYaw = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_lookAtAccumPitch = reinterpret_cast<float*>(object->m_localBase)[1];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x91: {
			float furTarget = reinterpret_cast<float*>(object->m_localBase)[0];
			int furSetCur = static_cast<int>(object->m_localBase[1]);
			CChara::CModel* model = engineObject->m_charaModelHandle->m_model;
			model->m_furTarget = furTarget;
			if (furSetCur != 0) {
				model->m_furCur = furTarget;
			}
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x92:
			engineObject->PutDropItem();
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x93: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]), 1, 0, 1, 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x94:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->SetArtifact(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x95:
			reinterpret_cast<CGPartyObj*>(engineObject)->PutMemoryCapsule(
			    static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]), RuntimeString(this, object->m_localBase[4]));
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x96:
			engineObject->addHp(static_cast<int>(object->m_localBase[0]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x97:
			GbaQue.OpenMenu(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId, static_cast<int>(object->m_localBase[0]), 1);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x9A:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 1, 1, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x99:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 0, 1, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x9B:
			engineObject->m_charaModelHandle->m_model->m_attachMode = static_cast<unsigned char>(object->m_localBase[0]);
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x9D:
			PushValue(
			    this, object, static_cast<unsigned int>(reinterpret_cast<CGPrgObj*>(engineObject)->GetClassControl(static_cast<int>(object->m_localBase[0]))));
			outResult = 0;
			break;
		case -0x9E:
			engineObject->m_groundHitOffset.x += reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_groundHitOffset.y += reinterpret_cast<float*>(object->m_localBase)[1];
			engineObject->m_groundHitOffset.z += reinterpret_cast<float*>(object->m_localBase)[2];
			PushValue(this, object, 0);
			outResult = 0;
			break;
		case -0x9F: {
			unsigned int finished = static_cast<unsigned int>(engineObject->IsAnimFinished(0));
			int topBit = __cntlzw(finished);
			PushValue(this, object, (topBit >> 5) & 0xFF);
			outResult = 0;
			break;
		}
		default:
			return 0;
	}

	return 1;
}
