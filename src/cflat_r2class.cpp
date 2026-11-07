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

namespace {

typedef unsigned char u8;

static inline unsigned short EngineClassId(void* engineObject)
{
	return static_cast<unsigned short>(reinterpret_cast<CGObject*>(engineObject)->GetCID());
}

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

static inline void StoreS32Value(CFlatRuntime::CStack* stack, int& value, int setMode)
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

static inline void StoreF32Value(CFlatRuntime::CStack* stack, float& value, int setMode)
{
	stack[-1].m_float = value;

	switch (setMode) {
	case -1:
		value -= stack->m_float;
		break;
	case 0:
		value = stack->m_float;
		break;
	case 1:
		value += stack->m_float;
		break;
	}
}

} // namespace

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CGObject::IsFall(int, int)
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
	CGObject* const engineObject = static_cast<CGObject*>(object);
	const unsigned short engineFlags = EngineClassId(engineObject);

	if ((engineFlags & 5) != 5 && systemVal == -0x1B) {
		if (static_cast<unsigned int>(System.m_execParam) >= 2) {
			System.Printf("!!!!!!!!!!!!!!!charUpdate"
					"\202\252\203x\201[\203X\203N\203\211\203X\202\310\202\307\202\305\216g\227p\202\263\202\352\202\304\202\334\202\267\201B"
					"!!!!!!!!!!!!!!!!!!!!\n");
		}
		return;
	}

	{
		if (systemVal <= -0x40) {
			CGObjWork* const work = engineObject->m_scriptHandle;

			if (systemVal <= -0xD80) {
				CMonWork* const monWork = static_cast<CMonWork*>(work);
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
				case -0xD98: {
					int index = systemVal + 0xDA7;
					StoreU16Value(stack, monWork->m_actionItems[index], setMode);
					break;
				}
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
				case -0xDA8: {
					int index = systemVal + 0xDB7;
					StoreU16Value(stack, monWork->m_actionAnimations[index], setMode);
					break;
				}
				case -0xDB8:
					StoreU16Value(stack, static_cast<CGMonObj*>(engineObject)->m_groupTag, setMode);
					break;
				case -0xDB9:
					StoreU16Value(stack, static_cast<CGMonObj*>(engineObject)->m_repop.delay, setMode);
					break;
				case -0xDBA:
					StoreU32Value(stack, static_cast<CGMonObj*>(engineObject)->m_controlMask, setMode);
					break;
				default:
					break;
				}
			} else if (systemVal <= -0x190) {
				CCaravanWork* const caravanWork = static_cast<CCaravanWork*>(work);
				if (systemVal <= -1000 && systemVal >= -0xBE7) {
					const int bit = systemVal + 0xBE7;
					const int oldValue = caravanWork->GetEvtFlag(bit);

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

					caravanWork->SetEvtFlag(bit, newValue);
				} else if (systemVal <= -0x1F4 && systemVal >= -0x2F3) {
					int index = systemVal + 0x2F3;
					StoreS16Value(stack, caravanWork->m_evtWordArr[index], setMode);
				} else {
					switch (systemVal) {
					case -0x199:
					case -0x198:
					case -0x197:
					case -0x196:
					case -0x195:
					case -0x194:
					case -0x193:
					case -0x192: {
						int index = systemVal + 0x199;
						StoreU16Value(stack, caravanWork->m_letterMeta[index], setMode);
						break;
					}
					case -0x19C:
						StoreS32Value(stack, caravanWork->m_gil, setMode);
						break;
					case -0x19D:
						StoreU16Value(stack, caravanWork->unk_0x3c8, setMode);
						break;
					case -0x1A9:
					case -0x1A8:
					case -0x1A7:
					case -0x1A6: {
						int index = systemVal + 0x1A9;
						StoreS16Value(stack, caravanWork->m_equipment[index], setMode);
						break;
					}
					case -0x1B6:
						StoreU16Value(stack, caravanWork->m_progressValue, setMode);
						break;
					default:
						break;
					}
				}
			} else {
				if (systemVal <= -0x96 && systemVal >= -0x175) {
					const int index = systemVal + 0x175;
					stack[-1].m_word = work->m_romWork[index];
					switch (setMode) {
					case -1:
						work->m_romWork[index] -= stack->m_word;
						break;
					case 0:
						work->m_romWork[index] = stack->m_word;
						break;
					case 1:
						work->m_romWork[index] += stack->m_word;
						break;
					}
				} else {
					switch (systemVal) {
					case -0x40:
						StoreU16Value(stack, work->m_maxHp, setMode);
						break;
					case -0x41:
						StoreU16Value(stack, work->m_hp, setMode);
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
					case -0x53: {
						int index = -0x53 - systemVal;
						StoreU16Value(stack, work->m_statusTimers[index], setMode);
						break;
					}
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
					case -0x85: {
						int index = systemVal + 0x94;
						StoreU16Value(stack, work->m_statusValues[index], setMode);
						break;
					}
					default:
						break;
					}
				}
			}

			m_nullVal.m_word = 0;
		} else {
			switch (systemVal) {
				case -5:
					StoreF32Value(stack, engineObject->unk_0x184, setMode);
					break;
				case -9:
					StoreS32Value(stack, engineObject->m_lifeTimer, setMode);
					break;
				case -0xA: {
					stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(engineObject->m_stateFlags0Bits.unk4));
					switch (setMode) {
					case -1:
						engineObject->m_stateFlags0Bits.unk4 = static_cast<signed char>(
						    engineObject->m_stateFlags0Bits.unk4 - static_cast<int>(stack->m_word));
						break;
					case 0:
						engineObject->m_stateFlags0Bits.unk4 = static_cast<signed char>(static_cast<signed char>(stack->m_word));
						break;
					case 1:
						engineObject->m_stateFlags0Bits.unk4 = static_cast<signed char>(
						    engineObject->m_stateFlags0Bits.unk4 + static_cast<int>(stack->m_word));
						break;
					}
					break;
				}
				case -0xB: {
					signed char* value = &engineObject->m_ownerSlot;
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
					StoreF32Value(stack, engineObject->unk_0x188, setMode);
					break;
				case -0xF:
					StoreS32Value(stack, engineObject->m_worldParamA, setMode);
					break;
				case -0x10:
					StoreS32Value(stack, engineObject->m_worldParamB, setMode);
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11: {
					int index = systemVal + 0x14;
					StoreS16Value(stack, engineObject->m_dropItemCodes[index], setMode);
					break;
				}
				case -0x15:
					StoreF32Value(stack, engineObject->unk_0x168, setMode);
					break;
				case -0x16:
					StoreF32Value(stack, engineObject->unk_0x16C, setMode);
					break;
				case -0x17:
					StoreF32Value(stack, engineObject->unk_0x170, setMode);
					break;
				case -0x18:
					StoreF32Value(stack, engineObject->m_homeRotY, setMode);
					break;
				case -0x1A: {
					int value = 0;
					stack[-1].m_float = 0.0f;
					switch (setMode) {
					case -1:
						value -= stack->m_float;
						break;
					case 0:
						value = static_cast<int>(stack->m_float);
						break;
					case 1:
						value += stack->m_float;
						break;
					}
					engineObject->m_field_0x56 =
					    static_cast<u8>(static_cast<int>(1000.0f * static_cast<float>(value)));
					break;
				}
				case -0x1B:
					StoreU32Value(stack, engineObject->m_displayFlags, setMode);
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
CFlatRuntime::CStack* CFlatRuntime2::onClassSystemVal(CFlatRuntime::CObject* object, int systemVal)
{
	CGObject* const engineObject = reinterpret_cast<CGObject*>(object->m_engineObject);
	const unsigned short engineFlags = EngineClassId(engineObject);

	if (((engineFlags & 5) != 5) && (systemVal == -0x1B)) {
		if (static_cast<unsigned int>(System.m_execParam) >= 2) {
			System.Printf("!!!!!!!!!!!!!!!charUpdate"
					"\202\252\203x\201[\203X\203N\203\211\203X\202\310\202\307\202\305\216g\227p\202\263\202\352\202\304\202\334\202\267\201B"
					"!!!!!!!!!!!!!!!!!!!!\n");
		}
		m_nullVal.m_word = 0;
		return &m_nullVal;
	} else {
		if (systemVal <= -0x40) {
			CGObjWork* const work = engineObject->m_scriptHandle;
			unsigned int value = 0;

			if (systemVal <= -0xD80) {
				CMonWork* const monWork = static_cast<CMonWork*>(work);
				switch (systemVal) {
				case -0xD83:
				case -0xD82:
				case -0xD81:
				case -0xD80: {
					int index = systemVal + 0xD83;
					value = monWork->unk_0xac[index];
					break;
				}
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
				case -0xD84: {
					int index = systemVal + 0xD91;
					value = monWork->unk_0xb4[index];
					break;
				}
				case -0xD92: {
					CCharaPcs::CHandle* handle = engineObject->m_charaModelHandle;
					if (handle != 0) {
						CCharaPcs::CLoadPdt* pdt = handle->m_pdtLoadRef;
						if (pdt != 0) {
							value = pdt->m_pdtSlot;
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
				case -0xD98: {
					int index = systemVal + 0xDA7;
					value = monWork->m_actionItems[index];
					break;
				}
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
				case -0xDA8: {
					int index = systemVal + 0xDB7;
					value = monWork->m_actionAnimations[index];
					break;
				}
				case -0xDBA:
					value = static_cast<CGMonObj*>(engineObject)->m_controlMask;
					break;
				default:
					break;
				}
			} else if (systemVal <= -0x190) {
				CCaravanWork* const caravanWork = static_cast<CCaravanWork*>(work);
				if (systemVal <= -1000 && systemVal >= -0xBE7) {
					const int bit = systemVal + 0xBE7;
					const u8 byteValue = caravanWork->m_evtFlags[bit / 8];
					const unsigned int mask = 1U << (bit % 8);
					value = static_cast<unsigned int>((byteValue & mask) != 0);
				} else if (systemVal <= -500 && systemVal >= -0x2F3) {
					int index = systemVal + 0x2F3;
					value = caravanWork->m_evtWordArr[index];
				} else {
					switch (systemVal) {
					case -0x199:
					case -0x198:
					case -0x197:
					case -0x196:
					case -0x195:
					case -0x194:
					case -0x193:
					case -0x192: {
						int index = systemVal + 0x199;
						value = caravanWork->m_letterMeta[index];
						break;
					}
					case -0x19C:
						value = caravanWork->m_gil;
						break;
					case -0x19D:
						value = caravanWork->unk_0x3c8;
						break;
					case -0x1A9:
					case -0x1A8:
					case -0x1A7:
					case -0x1A6: {
						int index = systemVal + 0x1A9;
						value = caravanWork->m_equipment[index];
						break;
					}
					case -0x1AA:
						value = caravanWork->m_inventoryItemCount;
						break;
					case -0x1B6:
						value = caravanWork->m_progressValue;
						break;
					case -0x1C8: {
						CGObject* const carryObject = static_cast<CGPartyObj*>(engineObject)->m_partyData.carryObject;
						if (carryObject != 0) {
							value = static_cast<unsigned int>(carryObject->m_particleId);
						} else {
							value = 0;
						}
						break;
					}
					case -0x1C9:
						value = caravanWork->m_artifactRelated[2];
						break;
					default:
						break;
					}
				}
			} else {
				if (systemVal <= -0x96 && systemVal >= -0x175) {
					int index = systemVal + 0x175;
					value = work->m_romWork[index];
				} else {
					switch (systemVal) {
					case -0x82:
						value = work->m_id;
						break;
					case -0x83:
						value = work->m_param1;
						break;
					case -0x84:
						value = work->m_param2;
						break;
					case -0x40:
						value = work->m_maxHp;
						break;
					case -0x41:
						value = work->m_hp;
						break;
					case -0x43:
						value = work->m_strength;
						break;
					case -0x44:
						value = work->m_magic;
						break;
					case -0x45:
						value = work->m_defense;
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
					case -0x53: {
						int index = -0x53 - systemVal;
						value = work->m_statusTimers[index];
						break;
					}
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
					case -0x85: {
						int index = systemVal + 0x94;
						value = work->m_statusValues[index];
						break;
					}
					default:
						break;
					}
				}
			}

			m_nullVal.m_word = value;
		} else {
			switch (systemVal) {
				case -1:
					m_nullVal.m_float = engineObject->m_worldPosition.x;
					break;
				case -2:
					m_nullVal.m_float = engineObject->m_worldPosition.y;
					break;
				case -3:
					m_nullVal.m_float = engineObject->m_worldPosition.z;
					break;
				case -4:
					m_nullVal.m_float = engineObject->m_rotTargetY;
					break;
				case -5:
					m_nullVal.m_float = engineObject->unk_0x184;
					break;
				case -6:
					m_nullVal.m_word = static_cast<unsigned int>(engineObject->m_particleId);
					break;
				case -7:
					m_nullVal.m_word = engineObject->m_stateFlags0Bits.unk0;
					break;
				case -8:
					m_nullVal.m_word = (engineObject->m_bgGroupMask >> 0x17) & 0xF;
					break;
				case -9:
					m_nullVal.m_word = engineObject->m_lifeTimer;
					break;
				case -0xA:
					m_nullVal.m_word = engineObject->m_stateFlags0Bits.unk4;
					break;
				case -0xB:
					m_nullVal.m_word = engineObject->m_ownerSlot;
					break;
				case -0xC:
					m_nullVal.m_word = engineObject->m_stateFlags0Bits.unk1;
					break;
				case -0xD:
					m_nullVal.m_float = engineObject->unk_0x188;
					break;
				case -0xF:
					m_nullVal.m_word = engineObject->m_worldParamA;
					break;
				case -0x10:
					m_nullVal.m_word = engineObject->m_worldParamB;
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11: {
					int index = systemVal + 0x14;
					m_nullVal.m_word = engineObject->m_dropItemCodes[index];
					break;
				}
				case -0x15:
					m_nullVal.m_float = engineObject->unk_0x168;
					break;
				case -0x16:
					m_nullVal.m_float = engineObject->unk_0x16C;
					break;
				case -0x17:
					m_nullVal.m_float = engineObject->unk_0x170;
					break;
				case -0x18:
					m_nullVal.m_float = engineObject->m_homeRotY;
					break;
				case -0x19:
					m_nullVal.m_word = static_cast<CGPrgObj*>(engineObject)->m_lastStateId;
					break;
				case -0x1B:
					m_nullVal.m_word = engineObject->m_displayFlags;
					break;
				default:
					break;
			}
		}
	}

	return &m_nullVal;
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
			push(object, 0);
			outResult = 0;
			break;
		case -6: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->SetPosBG(CVector(params[0], params[1], params[2]), 1);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -7:
			engineObject->m_animStateMisc = static_cast<unsigned char>(object->m_localBase[0]);
			{
				signed char animState = static_cast<signed char>(engineObject->m_animStateMisc);
				if (((animState < 0) || (animState >= 4)) && static_cast<unsigned int>(System.m_execParam) >= 2) {
					System.Printf("\203|\201[\203g\224\324\215\206\202\252\210\331\217\355\202\305\202\267\201B");
				}
			}
			push(object, 0);
			outResult = 0;
			break;
		case -8:
			engineObject->m_weaponNodeFlagAll.m_bits1.m_shield = static_cast<signed char>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -9:
			engineObject->m_moveBaseSpeed = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0xA:
			engineObject->m_rotTargetY = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
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
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x13:
			engineObject->m_bgColMask = object->m_localBase[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x9C:
			push(object, static_cast<int>(engineObject->m_bgColMask));
			outResult = 0;
			break;
		case -0xE:
			engineObject->LoadAnim(
			    m_strBlob + m_strOffsets[object->m_localBase[0]],
			    static_cast<int>(object->m_localBase[1]),
			    static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]),
			    object->m_localBase[4]);
			push(object, 0);
			outResult = 0;
			break;
		case -0xF:
			engineObject->SetAnimSlot(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x10:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 0, -1, -1, 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x11:
			if (engineObject->IsAnimFinished(0) != 0) {
				push(object, 0);
				outResult = 0;
			}
			break;
		case -0x12:
			engineObject->CancelAnim(1);
			push(object, 0);
			outResult = 0;
			break;
		case -0x14: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 0, 1, 0, 1);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x15:
			engineObject->m_weaponNodeFlagBits.m_unk10 = static_cast<signed char>(object->m_localBase[0]);
			engineObject->m_groundHitOffset.x = engineObject->m_groundHitOffset.y = engineObject->m_groundHitOffset.z = 0.0f;
			push(object, 0);
			outResult = 0;
			break;
		case -0x16:
			engineObject->m_objectFlags = object->m_localBase[0];
			if ((engineObject->m_objectFlags & 0x10) != 0) {
				Game.m_chaliceObject = engineObject;
			}
			push(object, 0);
			outResult = 0;
			break;
		case -0x17:
			engineObject->m_displayFlags = object->m_localBase[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x18:
			engineObject->m_rotationX = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_rotationY = reinterpret_cast<float*>(object->m_localBase)[1];
			engineObject->m_rotationZ = reinterpret_cast<float*>(object->m_localBase)[2];
			push(object, 0);
			outResult = 0;
			break;
		case -0x19: {
			CGQuadObj* quad = reinterpret_cast<CGQuadObj*>(engineObject);
			if (static_cast<int>(object->m_localBase[0]) == 1) {
				quad->Reset(reinterpret_cast<float*>(object->m_localBase)[1], reinterpret_cast<float*>(object->m_localBase)[2]);
			}
			quad->Add(reinterpret_cast<float*>(object->m_localBase)[3], reinterpret_cast<float*>(object->m_localBase)[4]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x1D: {
			engineObject->moveVector(
			    CVector(reinterpret_cast<float*>(object->m_localBase)[0], reinterpret_cast<float*>(object->m_localBase)[1],
			            reinterpret_cast<float*>(object->m_localBase)[2]),
			    reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x1F:
			engineObject->m_attrFlags = object->m_localBase[0];
			push(object, 0);
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
				    hit->m_particleId;
			}
			push(object, hit != 0);
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
			push(object, hit);
			outResult = 0;
			break;
		}
		case -0x22:
			engineObject->unk_0x184 = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x23: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			CGObject* result = engineObject->CCClassRot(
			    static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), params[2], params[3],
			    params[4], params[5]);
			if (result != 0) {
				*reinterpret_cast<int*>(object->m_localBase[6]) =
				    result->m_particleId;
			}
			push(object, result != 0);
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
			hitMove.y = 0.0f;
			hitMove.z = static_cast<float>(cos(angle)) * length;
			int hit = MapPcs.CheckHitCylinderNear(&hitStart, &hitMove, radius, object->m_localBase[0]);
			AddDebugDrawCC(&hitStart, &hitMove, radius, 1, 0);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[5]) = 0;
			}
			push(object, hit);
			outResult = 0;
			break;
		}
		case -0x25: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->SetPosBG(CVector(params[0], params[1], params[2]), 0);
			push(object, 0);
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
			push(object, 0);
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
				engineObject->Attach(target, m_strBlob + m_strOffsets[object->m_localBase[1]], &attachPos);
			}
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x28:
			engineObject->Detach();
			push(object, 0);
			outResult = 0;
			break;
		case -0x29:
			engineObject->DispCharaParts(static_cast<int>(object->m_localBase[0]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x2A:
			push(object, 0);
			outResult = 0;
			break;
		case -0x2B:
			push(object, 0);
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
			hitMove.x = 0.0f;
			hitMove.y = -height;
			hitMove.z = 0.0f;
			int hit = MapPcs.CheckHitCylinderNear(&hitStart, &hitMove, radius, object->m_localBase[0]);
			AddDebugDrawCC(&hitStart, &hitMove, radius, 1, 0);
			if (hit != 0) {
				*reinterpret_cast<int*>(object->m_localBase[6]) = 0;
			}
			push(object, hit);
			outResult = 0;
			break;
		}
		case -0x2D: {
			engineObject->SetAttackCol(
			    static_cast<int>(object->m_localBase[0]),
			    m_strBlob + m_strOffsets[object->m_localBase[1]],
			    reinterpret_cast<float*>(object->m_localBase)[2],
			    CVector(reinterpret_cast<float*>(object->m_localBase)[3], reinterpret_cast<float*>(object->m_localBase)[4],
			            reinterpret_cast<float*>(object->m_localBase)[5]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x2E: {
			engineObject->SetAttackColMask(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x2F: {
			engineObject->SetDamageCol(
			    static_cast<int>(object->m_localBase[0]),
			    m_strBlob + m_strOffsets[object->m_localBase[1]],
			    reinterpret_cast<float*>(object->m_localBase)[2],
			    reinterpret_cast<float*>(object->m_localBase)[3],
			    CVector(reinterpret_cast<float*>(object->m_localBase)[4], reinterpret_cast<float*>(object->m_localBase)[5],
			            reinterpret_cast<float*>(object->m_localBase)[6]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x30: {
			engineObject->SetDamageColMask(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x31:
			engineObject->m_bgHitMask = object->m_localBase[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x33: {
			float rotY = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_rotTargetY = rotY;
			engineObject->m_rotBaseY = rotY;
			push(object, 0);
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
			push(object, 0);
			outResult = 0;
			break;
		case -0x35: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 0, 0, 0, 0);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x36:
			engineObject->moveVectorH(
			    CVector(reinterpret_cast<float*>(object->m_localBase)[0], reinterpret_cast<float*>(object->m_localBase)[1],
			            reinterpret_cast<float*>(object->m_localBase)[2]),
			    reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x37: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, params[3], static_cast<int>(object->m_localBase[4]), 1, 0, 0, 0);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x38:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 1, 0, -1, -1, 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x39:
			engineObject->m_pushParamA = static_cast<unsigned char>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x3A:
			engineObject->FreeAnim(static_cast<int>(object->m_localBase[0]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x1A:
			engineObject->Turn(reinterpret_cast<float*>(object->m_localBase)[0], static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x1B: {
			if (engineObject->m_weaponNodeFlagAll.m_bits1.m_bit20 == 0) {
				push(object, 0);
				outResult = 0;
			}
			break;
		}
		case -0x1C:
			engineObject->CancelMove(1);
			push(object, 0);
			outResult = 0;
			break;
		case -0x3B: {
			GraphicPcs.m_screenFade[2].m_invert = static_cast<int>(object->m_localBase[0]);
			GraphicPcs.m_screenFade[2].m_mode = 1;
			GraphicPcs.m_screenFade[2].m_targetObj = engineObject;
			GraphicPcs.m_screenFade[2].m_targetYOffs = reinterpret_cast<float*>(object->m_localBase)[1];
			GraphicPcs.m_screenFade[2].m_colorA.r = static_cast<unsigned char>(object->m_localBase[2]);
			GraphicPcs.m_screenFade[2].m_colorA.g = static_cast<unsigned char>(object->m_localBase[3]);
			GraphicPcs.m_screenFade[2].m_colorA.b = static_cast<unsigned char>(object->m_localBase[4]);
			GraphicPcs.m_screenFade[2].m_colorA.a = 0xFF;
			GraphicPcs.m_screenFade[2].m_timer = static_cast<int>(object->m_localBase[5]);
			GraphicPcs.m_screenFade[2].m_duration = static_cast<int>(object->m_localBase[5]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x3C:
			engineObject->m_frontHitAngle = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x43: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->moveVectorRot(params[0], params[1], params[2], object->m_localBase[3]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x44: {
			float* params = reinterpret_cast<float*>(object->m_localBase);
			engineObject->moveVectorHRot(params[0], params[1], params[2], object->m_localBase[3]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x45:
			engineObject->SetTexAnim(m_strBlob + m_strOffsets[object->m_localBase[0]]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x46: {
			CGObject* target = 0;
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				target = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[0])));
			}
			engineObject->LookAt(target, 0);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x8C: {
			CGObject* target = 0;
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				target = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[0])));
			}
			engineObject->LookAt(target, m_strBlob + m_strOffsets[object->m_localBase[1]]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x48:
			engineObject->m_alphaTarget = reinterpret_cast<float*>(object->m_localBase)[1];
			if (static_cast<int>(object->m_localBase[0]) != 0) {
				engineObject->m_currentAlpha = engineObject->m_alphaTarget;
			}
			push(object, 0);
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
			push(object, slot);
			outResult = 0;
			break;
		}
		case -0x52: {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			int findItemId = static_cast<int>(object->m_localBase[1]);
			unsigned int result = 0;
			if ((object->m_localBase[0] & 2) != 0) {
				result = caravanWork->FindItem(findItemId) >= 0 ? 2 : 0;
			}
			push(object, static_cast<int>(result));
			outResult = 0;
			break;
		}
		case -0x53:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_gil = static_cast<int>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x55:
			engineObject->m_scriptHandle->m_hp = static_cast<unsigned short>(object->m_localBase[1]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x56:
			engineObject->m_scriptHandle->m_maxHp = static_cast<unsigned short>(object->m_localBase[1]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x5A: {
			CGObjWork* const work = engineObject->m_scriptHandle;
			work->m_statusValues[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x5C: {
			CMonWork* work = reinterpret_cast<CMonWork*>(engineObject->m_scriptHandle);
			work->m_actionItems[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x5D: {
			CMonWork* work = reinterpret_cast<CMonWork*>(engineObject->m_scriptHandle);
			work->m_actionAnimations[object->m_localBase[0]] = static_cast<unsigned short>(object->m_localBase[1]);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x5F:
			if (engineObject->m_charaModelHandle != 0) {
				if (PartMng.pppIsDeadCHandle(engineObject->m_charaModelHandle) != 0) {
					push(object, 0);
					outResult = 0;
				}
			} else {
				push(object, 0);
				outResult = 0;
			}
			break;
		case -0x60: {
			Vec safePos;
			float safeDist = engineObject->CalcSafePos(static_cast<int>(object->m_localBase[0]), static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[1]))), &safePos);
			*reinterpret_cast<float*>(object->m_localBase[2]) = safePos.x;
			*reinterpret_cast<float*>(object->m_localBase[3]) = safePos.y;
			*reinterpret_cast<float*>(object->m_localBase[4]) = safePos.z;
			push(object, *reinterpret_cast<int*>(&safeDist));
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
			push(object, 0);
			outResult = 0;
			break;
		case -0x62: {
			push(object, !Joybus.ChgCtrlMode(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId));
			outResult = 0;
			break;
		}
		case -0x63:
			push(object, 0);
			outResult = 0;
			break;
		case -0x64:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->unk_0x3e6 = static_cast<unsigned short>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x68:
			MenuPcs.GetRingMenu(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId)
			    ->SetBattleButton(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x69:
			MenuPcs.GetRingMenu(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId)
			    ->SetBattleCommand(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), -1);
			push(object, 0);
			outResult = 0;
			break;
		case -0x6A:
			push(object, 0);
			outResult = 0;
			break;
		case -0x6C:
			push(object, 0);
			outResult = 0;
			break;
		case -0x6D:
			push(object, 0);
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
			push(object, 0);
			outResult = 0;
			break;
		case -0x70:
			engineObject->m_stateFlags0Bits.unk3 = static_cast<signed char>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x71:
			engineObject->m_jumpLandingDampening = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x72:
			engineObject->SetDispItemName(static_cast<int>(object->m_localBase[0]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x73: {
			push(object, Pad.IsGba(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId));
			outResult = 0;
			break;
		}
		case -0x74: {
			Vec moveVector;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveVector.x = params[0];
			moveVector.y = params[1];
			moveVector.z = params[2];
			VECNormalizeZero(&moveVector, &moveVector);
			engineObject->MoveVector(&moveVector, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]), 1, 1, 1);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x75: {
			int state = static_cast<int>(object->m_localBase[0]);
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle);
			if (static_cast<int>(caravanWork->m_evtState0) != state) {
				caravanWork->m_evtState0 = state;
				caravanWork->m_evtState1 = 0;
			}
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x6E:
			engineObject->m_lastBgAttr = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x76:
			push(object, static_cast<int>(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_evtState1));
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
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x78:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 0, 0, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x79: {
			signed char animList[8];
			int argCount = reinterpret_cast<CFlatRuntime::CObject*>(engineObject)->m_argCount - 1;
			int animCount;
			for (animCount = 0; animCount < 4; animCount++) {
				if (argCount <= animCount) {
					break;
				}
				animList[animCount] = static_cast<signed char>(object->m_localBase[animCount + 1]);
			}
			animList[animCount] = static_cast<signed char>(0xFF);
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 0, -1, -1, animList);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x7A:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 1, 0, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x7C:
			push(
			    object, reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->GetFoodRank(static_cast<int>(object->m_localBase[0])));
			outResult = 0;
			break;
		case -0x7D: {
			float aspect = reinterpret_cast<float*>(object->m_localBase)[1];
			switch (static_cast<int>(object->m_localBase[0])) {
			case 1:
				engineObject->m_bodyEllipsoidAspect = aspect;
				break;
			}
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x7E: {
			int initArg = static_cast<int>(object->m_localBase[0]);
			unsigned int workIndex = this->m_workAssignIndex;
			this->m_workAssignIndex = workIndex + 1;
			engineObject->SetClassWork(1, static_cast<int>(workIndex));
			engineObject->InitWork(initArg);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x7F: {
			int partyIndex = m_partyAssignIndex++;
			if (Game.m_gameWork.m_wmBackupParams[partyIndex] >= 0) {
				engineObject->SetClassWork(0, partyIndex);
				reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId = static_cast<unsigned int>(partyIndex);
				Game.m_partyObjArr[partyIndex] = reinterpret_cast<CGPartyObj*>(engineObject);
				Joybus.SendAllStat(static_cast<int>(partyIndex));
			}
			push(object, 0);
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
			engineObject->MoveVector(&moveVector, reinterpret_cast<float*>(object->m_localBase)[2], static_cast<int>(object->m_localBase[3]), 0, 0, 1);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x4A:
			engineObject->m_turnFactor = reinterpret_cast<float*>(object->m_localBase)[0];
			push(object, 0);
			outResult = 0;
			break;
		case -0x4B:
			engineObject->ResetDynamics();
			push(object, 0);
			outResult = 0;
			break;
		case -0x41:
			engineObject->m_alphaStep = 1.0f / static_cast<float>(static_cast<int>(object->m_localBase[0]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x82:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 0, 1, -1, -1, 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x83:
			engineObject->PlayAnim(static_cast<int>(object->m_localBase[0]), 1, 1, -1, -1, 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x85: {
			int shopResult = reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->ShopRequest(
			    static_cast<int>(object->m_localBase[0]),
			    static_cast<int>(object->m_localBase[1]),
			    static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]),
			    static_cast<int>(object->m_localBase[4]),
			    static_cast<int>(object->m_localBase[5]),
			    static_cast<int>(object->m_localBase[6]));
			push(object, shopResult);
			outResult = 0;
			break;
		}
		case -0x86:
			engineObject->m_charaModelHandle->m_model->SetFur(static_cast<int>(object->m_localBase[0]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x87:
			engineObject->m_charaModelHandle->m_model->SetFurParam(
			    reinterpret_cast<float*>(object->m_localBase)[0], reinterpret_cast<float*>(object->m_localBase)[1]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x88: {
			Vec nearPos;
			engineObject->CalcSphereNearPos(reinterpret_cast<float*>(object->m_localBase)[0], reinterpret_cast<float*>(object->m_localBase)[1], nearPos);
			*reinterpret_cast<float*>(object->m_localBase[2]) = nearPos.x;
			*reinterpret_cast<float*>(object->m_localBase[3]) = nearPos.y;
			*reinterpret_cast<float*>(object->m_localBase[4]) = nearPos.z;
			push(object, 0);
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
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x8B:
			engineObject->m_moveModePrevious = static_cast<unsigned char>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x8E: {
			int carryIndex = static_cast<int>(object->m_localBase[0]);
			CGObject* carried = static_cast<CGObject*>(this->intToClass(static_cast<int>(object->m_localBase[1])));
			reinterpret_cast<CGPartyObj*>(engineObject)->carry(carryIndex, carried, static_cast<int>(object->m_localBase[2]));
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x8D:
			reinterpret_cast<CGPartyObj*>(engineObject)->commandFinished();
			push(object, 0);
			outResult = 0;
			break;
		case -0x8F:
			reinterpret_cast<CGPrgObj*>(engineObject)->ClassControl(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x90:
			engineObject->m_lookAtAccumYaw = reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_lookAtAccumPitch = reinterpret_cast<float*>(object->m_localBase)[1];
			push(object, 0);
			outResult = 0;
			break;
		case -0x91:
			engineObject->m_charaModelHandle->m_model->SetFurColor(
			    reinterpret_cast<float*>(object->m_localBase)[0], static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x92:
			engineObject->PutDropItem();
			push(object, 0);
			outResult = 0;
			break;
		case -0x93: {
			Vec moveTarget;
			float* params = reinterpret_cast<float*>(object->m_localBase);
			moveTarget.x = params[0];
			moveTarget.y = params[1];
			moveTarget.z = params[2];
			engineObject->Move(&moveTarget, reinterpret_cast<float*>(object->m_localBase)[3], static_cast<int>(object->m_localBase[4]), 1, 0, 1, 0);
			push(object, 0);
			outResult = 0;
			break;
		}
		case -0x94:
			reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->SetArtifact(static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]));
			push(object, 0);
			outResult = 0;
			break;
		case -0x95:
			reinterpret_cast<CGPartyObj*>(engineObject)->PutMemoryCapsule(
			    static_cast<int>(object->m_localBase[0]), static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]),
			    static_cast<int>(object->m_localBase[3]), m_strBlob + m_strOffsets[object->m_localBase[4]]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x96:
			engineObject->addHp(static_cast<int>(object->m_localBase[0]), 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x97:
			GbaQue.OpenMenu(reinterpret_cast<CCaravanWork*>(engineObject->m_scriptHandle)->m_joybusCaravanId, static_cast<int>(object->m_localBase[0]), 1);
			push(object, 0);
			outResult = 0;
			break;
		case -0x9A:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 1, 1, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x99:
			engineObject->PlayAnim(
			    static_cast<int>(object->m_localBase[0]), 0, 1, static_cast<int>(object->m_localBase[1]), static_cast<int>(object->m_localBase[2]), 0);
			push(object, 0);
			outResult = 0;
			break;
		case -0x9B:
			engineObject->m_charaModelHandle->m_model->m_attachMode = static_cast<unsigned char>(object->m_localBase[0]);
			push(object, 0);
			outResult = 0;
			break;
		case -0x9D: {
			unsigned int classControl = static_cast<unsigned int>(reinterpret_cast<CGPrgObj*>(engineObject)->GetClassControl(static_cast<int>(object->m_localBase[0])));
			push(object, classControl);
			outResult = 0;
			break;
		}
		case -0x9E:
			engineObject->m_groundHitOffset.x += reinterpret_cast<float*>(object->m_localBase)[0];
			engineObject->m_groundHitOffset.y += reinterpret_cast<float*>(object->m_localBase)[1];
			engineObject->m_groundHitOffset.z += reinterpret_cast<float*>(object->m_localBase)[2];
			push(object, 0);
			outResult = 0;
			break;
		case -0x9F: {
			push(object, !engineObject->IsAnimFinished(0));
			outResult = 0;
			break;
		}
		default:
			return 0;
	}

	return 1;
}
