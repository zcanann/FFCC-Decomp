#include "ffcc/cflat_r2class.h"
#include "ffcc/charaobj.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gobject.h"
#include "ffcc/joybus.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/pad.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/ringmenu.h"
#include "ffcc/system.h"

#include <math.h>

extern "C" int IsAnimFinished__8CGObjectFi(CGObject*, int);
extern "C" void push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(CFlatRuntime2*, CFlatRuntime::CObject*, int);

namespace {

typedef unsigned char u8;

static inline unsigned int& LastResult(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x96C);
}

static inline unsigned int CallEngineFlags(void* engineObject)
{
	typedef unsigned int (*EngineFn)(void*);
	void** vtable = *reinterpret_cast<void***>(reinterpret_cast<u8*>(engineObject) + 0x48);
	EngineFn fn = reinterpret_cast<EngineFn>(vtable[3]);
	return fn(engineObject);
}

static inline unsigned int CallEngineFunc48Arg(void* engineObject, unsigned int arg0)
{
	typedef unsigned int (*EngineFn)(void*, unsigned int);
	void** vtable = *reinterpret_cast<void***>(reinterpret_cast<u8*>(engineObject) + 0x48);
	EngineFn fn = reinterpret_cast<EngineFn>(vtable[2]);
	return fn(engineObject, arg0);
}

static inline CGObject* FindRuntimeObject(CFlatRuntime2* runtime, unsigned int objectId)
{
	typedef CGObject* (*RuntimeFn)(CFlatRuntime2*, unsigned int);
	void** vtable = *reinterpret_cast<void***>(runtime);
	RuntimeFn fn = reinterpret_cast<RuntimeFn>(vtable[15]);
	return fn(runtime, objectId);
}

static inline unsigned int& RuntimeWorkAssignIndex(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x1040C);
}

static inline unsigned int& RuntimePartyAssignIndex(CFlatRuntime2* runtime)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(runtime) + 0x10410);
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
	return *reinterpret_cast<CRingMenu**>(reinterpret_cast<u8*>(&MenuPcs) + 0x13C + playerIndex * 4);
}

static inline void PushF32(CFlatRuntime2* runtime, CFlatRuntime::CObject* object, float value)
{
	push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(runtime, object, *reinterpret_cast<int*>(&value));
}

static inline void StoreU16(CFlatRuntime::CStack* stack, unsigned short* value, int setMode)
{
	stack[-1].m_word = static_cast<unsigned int>(*value);

	if (setMode == 0) {
		*value = static_cast<unsigned short>(stack->m_word);
	} else if (setMode < 0) {
		if (setMode > -2) {
			*value = static_cast<unsigned short>(*value - static_cast<unsigned short>(stack->m_word));
		}
	} else if (setMode < 2) {
		*value = static_cast<unsigned short>(*value + static_cast<unsigned short>(stack->m_word));
	}
}

static inline void StoreS16(CFlatRuntime::CStack* stack, short* value, int setMode)
{
	stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(*value));

	if (setMode == 0) {
		*value = static_cast<short>(stack->m_word);
	} else if (setMode < 0) {
		if (setMode > -2) {
			*value = static_cast<short>(*value - static_cast<short>(stack->m_word));
		}
	} else if (setMode < 2) {
		*value = static_cast<short>(*value + static_cast<short>(stack->m_word));
	}
}

static inline void StoreU32(CFlatRuntime::CStack* stack, unsigned int* value, int setMode)
{
	stack[-1].m_word = *value;

	if (setMode == 0) {
		*value = stack->m_word;
	} else if (setMode < 0) {
		if (setMode > -2) {
			*value -= stack->m_word;
		}
	} else if (setMode < 2) {
		*value += stack->m_word;
	}
}

static inline void StoreF32(CFlatRuntime::CStack* stack, float* value, int setMode)
{
	stack[-1].m_word = *reinterpret_cast<unsigned int*>(value);

	if (setMode == 0) {
		*value = static_cast<float>(stack->m_word);
	} else if (setMode < 0) {
		if (setMode > -2) {
			*value -= static_cast<float>(stack->m_word);
		}
	} else if (setMode < 2) {
		*value += static_cast<float>(stack->m_word);
	}
}

} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SAFE_CAST_MON_WORK(CGObjWork*)
{
	// TODO
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
void CFlatRuntime2::onClassSystemFunc(CFlatRuntime::CObject* object, int, int command, int& outResult)
{
	CGObject* engineObject = reinterpret_cast<CGObject*>(object->m_engineObject);
	CGCharaObj* charaObject = reinterpret_cast<CGCharaObj*>(object->m_engineObject);
	CGPartyObj* partyObject = reinterpret_cast<CGPartyObj*>(object->m_engineObject);
	unsigned int* localBase = object->m_localBase;

	switch (command) {
		case -0x9F: {
			unsigned int finished = static_cast<unsigned int>(IsAnimFinished__8CGObjectFi(engineObject, 0));
			int topBit = __cntlzw(finished);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, (topBit >> 5) & 0xFF);
			outResult = 0;
			break;
		}
		case -0x9E:
			engineObject->m_groundHitOffset.x += static_cast<float>(localBase[0]);
			engineObject->m_groundHitOffset.y += static_cast<float>(localBase[1]);
			engineObject->m_groundHitOffset.z += static_cast<float>(localBase[2]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x9D:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(
			    this, object, static_cast<int>(CallEngineFunc48Arg(engineObject, localBase[0])));
			outResult = 0;
			break;
		case -0x9C:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, static_cast<int>(engineObject->m_bgColMask));
			outResult = 0;
			break;
		case -0x93: {
			Vec moveTarget;
			moveTarget.x = static_cast<float>(localBase[0]);
			moveTarget.y = static_cast<float>(localBase[1]);
			moveTarget.z = static_cast<float>(localBase[2]);
			engineObject->Move(&moveTarget, static_cast<float>(localBase[3]), static_cast<int>(localBase[4]), 1, 0, 1, 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x92:
			engineObject->PutDropItem();
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x90:
			engineObject->m_lookAtAccumYaw = static_cast<float>(localBase[0]);
			engineObject->m_lookAtAccumPitch = static_cast<float>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x8B:
			engineObject->m_moveModePrevious = static_cast<unsigned char>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x89: {
			Vec moveTarget;
			moveTarget.x = static_cast<float>(localBase[0]);
			moveTarget.y = static_cast<float>(localBase[1]);
			moveTarget.z = static_cast<float>(localBase[2]);
			engineObject->Move(&moveTarget, static_cast<float>(localBase[3]), static_cast<int>(localBase[4]), 1, 1, 1, 1);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x88: {
			Vec nearPos;
			engineObject->CalcSphereNearPos(static_cast<float>(localBase[0]), static_cast<float>(localBase[1]), nearPos);
			*reinterpret_cast<unsigned int*>(localBase[2]) = *reinterpret_cast<unsigned int*>(&nearPos.x);
			*reinterpret_cast<unsigned int*>(localBase[3]) = *reinterpret_cast<unsigned int*>(&nearPos.y);
			*reinterpret_cast<unsigned int*>(localBase[4]) = *reinterpret_cast<unsigned int*>(&nearPos.z);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7D:
			if (localBase[0] == 1) {
				engineObject->m_bodyEllipsoidAspect = static_cast<float>(localBase[1]);
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x7A:
			engineObject->PlayAnim(
			    static_cast<int>(localBase[0]), 1, 0, static_cast<short>(localBase[1]), static_cast<short>(localBase[2]), 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x78:
			engineObject->PlayAnim(
			    static_cast<int>(localBase[0]), 0, 0, static_cast<short>(localBase[1]), static_cast<short>(localBase[2]), 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x72:
			engineObject->SetDispItemName(static_cast<signed char>(localBase[0]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x71:
			engineObject->m_jumpLandingDampening = static_cast<float>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x70:
			engineObject->m_stateFlags0 =
			    static_cast<unsigned char>((static_cast<signed char>(localBase[0]) << 4) & 0x10) |
			    (engineObject->m_stateFlags0 & 0xEF);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x6F:
			engineObject->m_moveOffset.x = static_cast<float>(localBase[0]);
			engineObject->m_moveOffset.y = static_cast<float>(localBase[1]);
			engineObject->m_moveOffset.z = static_cast<float>(localBase[0]);
			engineObject->m_bounceFactor = static_cast<float>(localBase[2]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x6E:
			*reinterpret_cast<unsigned int*>(engineObject->m_lastBgAttr) = localBase[0];
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x6D:
		case -0x6C:
		case -0x6A:
		case -0x63:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x9A:
			engineObject->PlayAnim(
			    static_cast<int>(localBase[0]), 1, 1, static_cast<short>(localBase[1]), static_cast<short>(localBase[2]), 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x99:
			engineObject->PlayAnim(
			    static_cast<int>(localBase[0]), 0, 1, static_cast<short>(localBase[1]), static_cast<short>(localBase[2]), 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x97:
			GbaQue.OpenMenu(ScriptPlayerIndex(engineObject), static_cast<int>(localBase[0]), 1);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x96:
			charaObject->addHp(static_cast<int>(localBase[0]), 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x94:
			ScriptCaravan(engineObject)->SetArtifact(static_cast<int>(localBase[0]), static_cast<int>(localBase[1]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x8E:
			partyObject->carry(static_cast<int>(localBase[0]), FindRuntimeObject(this, localBase[1]), static_cast<int>(localBase[2]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x8D:
			partyObject->commandFinished();
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x85:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(
			    this,
			    object,
			    ScriptCaravan(engineObject)->ShopRequest(
			        static_cast<int>(localBase[0]),
			        static_cast<int>(localBase[1]),
			        static_cast<int>(localBase[2]),
			        static_cast<int>(localBase[3]),
			        static_cast<int>(localBase[4]),
			        static_cast<int>(localBase[5]),
			        static_cast<int>(static_cast<signed char>(localBase[6]))));
			outResult = 0;
			break;
		case -0x7F: {
			unsigned int partyIndex = RuntimePartyAssignIndex(this);
			RuntimePartyAssignIndex(this) = partyIndex + 1;
			if (Game.m_gameWork.m_wmBackupParams[partyIndex] >= 0) {
				engineObject->SetClassWork(0, static_cast<int>(partyIndex));
				ScriptCaravan(engineObject)->m_joybusCaravanId = static_cast<int>(partyIndex);
				Game.m_partyObjArr[partyIndex] = partyObject;
				Joybus.SendAllStat(static_cast<int>(partyIndex));
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7E: {
			unsigned int workIndex = RuntimeWorkAssignIndex(this);
			RuntimeWorkAssignIndex(this) = workIndex + 1;
			engineObject->SetClassWork(1, static_cast<int>(workIndex));
			engineObject->InitWork(static_cast<int>(localBase[0]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x7C:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(
			    this, object, ScriptCaravan(engineObject)->GetFoodRank(static_cast<int>(localBase[0])));
			outResult = 0;
			break;
		case -0x79: {
			signed char animList[8];
			int animCount = 0;
			int argCount = object->m_argCount - 1;
			if (argCount > 0) {
				animList[0] = static_cast<signed char>(localBase[1]);
				animCount = 1;
				if (argCount > 1) {
					animList[1] = static_cast<signed char>(localBase[2]);
					animCount = 2;
					if (argCount > 2) {
						animList[2] = static_cast<signed char>(localBase[3]);
						animCount = 3;
						if (argCount > 3) {
							animList[3] = static_cast<signed char>(localBase[4]);
							animCount = 4;
						}
					}
				}
			}
			animList[animCount] = static_cast<signed char>(0xFF);
			engineObject->PlayAnim(static_cast<int>(localBase[0]), 0, 0, -1, -1, animList);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x77: {
			CCaravanWork* caravanWork = ScriptCaravan(engineObject);
			unsigned int mode = localBase[0];
			int index = static_cast<int>(localBase[1]);
			if (mode != 2) {
				if (static_cast<int>(mode) < 2) {
					if (static_cast<int>(mode) > 0) {
						caravanWork->DeleteItemIdx(index, 1);
					}
				} else if (static_cast<int>(mode) < 4) {
					caravanWork->DeleteCmdList(index, 1);
				}
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x76:
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, static_cast<int>(ScriptCaravan(engineObject)->m_evtState1));
			outResult = 0;
			break;
		case -0x75: {
			CCaravanWork* caravanWork = ScriptCaravan(engineObject);
			if (caravanWork->m_evtState0 != localBase[0]) {
				caravanWork->m_evtState0 = localBase[0];
				caravanWork->m_evtState1 = 0;
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x74: {
			Vec moveVector;
			moveVector.x = static_cast<float>(localBase[0]);
			moveVector.y = static_cast<float>(localBase[1]);
			moveVector.z = static_cast<float>(localBase[2]);
			float magnitude = PSVECMag(&moveVector);
			if (magnitude == 0.0f) {
				moveVector.x = 0.0f;
				moveVector.y = 0.0f;
				moveVector.z = 0.0f;
			} else {
				PSVECScale(&moveVector, &moveVector, 0.5f / magnitude);
			}
			engineObject->MoveVector(&moveVector, static_cast<float>(localBase[3]), static_cast<int>(localBase[4]), 1, 1, 1);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x73: {
			unsigned int buttons = 0;
			int playerIndex = ScriptPlayerIndex(engineObject);
			bool useDebugPad = (Pad._452_4_ != 0) || ((playerIndex == 0) && (Pad._448_4_ != -1));
			if (!useDebugPad) {
				unsigned int slot = static_cast<unsigned int>(playerIndex)
				    & ~((static_cast<int>(~(Pad._448_4_ - playerIndex | playerIndex - Pad._448_4_)) >> 31));
				buttons = *reinterpret_cast<unsigned short*>(reinterpret_cast<u8*>(&Pad) + 4 + slot * 0x54);
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, static_cast<int>(buttons));
			outResult = 0;
			break;
		}
		case -0x69:
			BattleRingMenu(ScriptPlayerIndex(engineObject))
			    ->SetBattleCommand(static_cast<int>(localBase[0]), static_cast<int>(localBase[1]), -1);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x68:
			BattleRingMenu(ScriptPlayerIndex(engineObject))
			    ->SetBattleButton(static_cast<int>(localBase[0]), static_cast<int>(localBase[1]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x64:
			ScriptCaravan(engineObject)->unk_0x3e6 = static_cast<unsigned short>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x62: {
			unsigned int changed = static_cast<unsigned int>(Joybus.ChgCtrlMode(ScriptPlayerIndex(engineObject)));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, (__cntlzw(changed) >> 5) & 0xFF);
			outResult = 0;
			break;
		}
		case -0x61:
			ScriptCaravan(engineObject)->AddLetter(
			    static_cast<int>(localBase[0]),
			    static_cast<int>(localBase[1]),
			    static_cast<int>(localBase[2]),
			    static_cast<int>(localBase[3]),
			    static_cast<int>(localBase[4]),
			    static_cast<short>(localBase[5]),
			    static_cast<short>(localBase[6]),
			    static_cast<short>(localBase[7]),
			    static_cast<short>(localBase[8]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x60: {
			Vec safePos;
			float safeDist = engineObject->CalcSafePos(static_cast<int>(localBase[0]), FindRuntimeObject(this, localBase[1]), &safePos);
			*reinterpret_cast<unsigned int*>(localBase[2]) = *reinterpret_cast<unsigned int*>(&safePos.x);
			*reinterpret_cast<unsigned int*>(localBase[3]) = *reinterpret_cast<unsigned int*>(&safePos.y);
			*reinterpret_cast<unsigned int*>(localBase[4]) = *reinterpret_cast<unsigned int*>(&safePos.z);
			PushF32(this, object, safeDist);
			outResult = 0;
			break;
		}
		case -0x5D:
			ScriptMonWork(engineObject)->unk_0xf0[localBase[0]] = static_cast<unsigned short>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x5C:
			ScriptMonWork(engineObject)->unk_0xd0[localBase[0]] = static_cast<unsigned short>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x5A:
			ScriptWork(engineObject)->m_statusValues[localBase[0]] = static_cast<unsigned short>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x56:
			ScriptWork(engineObject)->m_maxHp = static_cast<unsigned short>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x55:
			ScriptWork(engineObject)->m_hp = static_cast<unsigned short>(localBase[1]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x54: {
			Vec moveVector;
			float rotX = static_cast<float>(localBase[0]);
			float rotY = static_cast<float>(localBase[1]);
			moveVector.x = static_cast<float>(sin(rotX) * cos(rotY));
			moveVector.y = static_cast<float>(sin(rotY));
			moveVector.z = static_cast<float>(cos(rotX) * cos(rotY));
			engineObject->MoveVector(&moveVector, static_cast<float>(localBase[2]), static_cast<int>(localBase[3]), 0, 0, 1);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x53:
			ScriptCaravan(engineObject)->m_gil = static_cast<int>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x52: {
			unsigned int result = 0;
			if ((localBase[0] & 2) != 0 && ScriptCaravan(engineObject)->FindItem(static_cast<int>(localBase[1])) >= 0) {
				result = 2;
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, static_cast<int>(result));
			outResult = 0;
			break;
		}
		case -0x4F: {
			CCaravanWork* caravanWork = ScriptCaravan(engineObject);
			unsigned int mode = localBase[0];
			int slot = -1;
			if (mode != 2) {
				int itemId = static_cast<unsigned short>(localBase[1]);
				if (static_cast<int>(mode) < 2) {
					if (static_cast<int>(mode) > 0) {
						caravanWork->AddItem(itemId, &slot);
					}
				} else if (static_cast<int>(mode) < 4) {
					caravanWork->AddComList(itemId, &slot);
				}
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, slot);
			outResult = 0;
			break;
		}
		case -0x4B:
			engineObject->ResetDynamics();
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x4A:
			engineObject->m_hitNormal.x = static_cast<float>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x48:
			engineObject->m_stepSlopeLimit = static_cast<float>(localBase[1]);
			if (localBase[0] != 0) {
				engineObject->m_lookAtTimer = engineObject->m_stepSlopeLimit;
			}
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x46:
			engineObject->LookAt(localBase[0] != 0 ? FindRuntimeObject(this, localBase[0]) : 0, 0);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		case -0x44: {
			float* params = reinterpret_cast<float*>(localBase);
			engineObject->moveVectorHRot(params[0], params[1], params[2], static_cast<int>(params[3]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x43: {
			float* params = reinterpret_cast<float*>(localBase);
			engineObject->moveVectorRot(params[0], params[1], params[2], static_cast<int>(params[3]));
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		}
		case -0x41:
			engineObject->m_bgDownDist = 0.5f / static_cast<float>(localBase[0]);
			push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(this, object, 0);
			outResult = 0;
			break;
		default:
			break;
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
	unsigned int value = 0;

	if (((CallEngineFlags(engineObject) & 5) == 5) || (systemVal != -0x1B)) {
		if (systemVal < -0x3F) {
			u8* const classData = *reinterpret_cast<u8**>(engineObject + 0x58);

			if (systemVal < -0xD7F) {
				if (systemVal < -0xD97) {
					if (systemVal < -0xDB7) {
						if (systemVal == -0xDBA) {
							value = *reinterpret_cast<unsigned int*>(engineObject + 0x6EC);
						}
					} else if (systemVal < -0xDA7) {
						value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0xDB7) * 2 + 0xF0);
					} else {
						value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0xDA7) * 2 + 0xD0);
					}
				} else if (systemVal < -0xD83) {
					if (systemVal == -0xD92) {
						u8* p = *reinterpret_cast<u8**>(engineObject + 0xF8);
						if (p == 0) {
							value = static_cast<unsigned int>(-1);
						} else {
							p = *reinterpret_cast<u8**>(p + 0x178);
							value = (p == 0) ? static_cast<unsigned int>(-1) : *reinterpret_cast<unsigned int*>(p + 0x14);
						}
					} else if (systemVal > -0xD93) {
						value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0xD91) * 2 + 0xB4);
					}
				} else {
					value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0xD83) * 2 + 0xAC);
				}
			} else if (systemVal < -399) {
				if (systemVal < -999 && systemVal > -0xBE8) {
					const unsigned int bit = static_cast<unsigned int>(systemVal + 0xBE7);
					const int shiftSign = static_cast<int>(bit) >> 0x1F;
					const unsigned int rounded = static_cast<unsigned int>((static_cast<int>(bit) < 0) && ((bit & 7) != 0));
					const u8 byteValue = *(classData + (static_cast<int>(bit) >> 3) + rounded + 0x8A4);
					const unsigned int mask = 1U << ((shiftSign * 8 | bit * 0x20000000U + shiftSign >> 0x1D) - shiftSign);
					value = static_cast<unsigned int>(-((byteValue & mask) != 0));
				} else if (systemVal < -499 && systemVal > -0x2F4) {
					value = static_cast<unsigned int>(*reinterpret_cast<short*>(classData + (systemVal + 0x2F3) * 2 + 0x9A4));
				} else if (systemVal == -0x1AA) {
					value = *reinterpret_cast<unsigned short*>(classData + 0xB4);
				} else if (systemVal < -0x1AA) {
					if (systemVal == -0x1C8) {
						u8* const p = *reinterpret_cast<u8**>(engineObject + 0x6F0);
						value = (p == 0) ? 0 : static_cast<unsigned int>(*reinterpret_cast<short*>(p + 0x30));
					} else if (systemVal > -0x1CA) {
						value = *reinterpret_cast<unsigned short*>(classData + 0xBC8);
					} else if (systemVal == -0x1B6) {
						value = *reinterpret_cast<unsigned short*>(classData + 0x3DE);
					}
				} else if (systemVal == -0x19C) {
					value = *reinterpret_cast<unsigned int*>(classData + 0x200);
				} else if (systemVal < -0x19C) {
					if (systemVal < -0x1A5) {
						value = static_cast<unsigned int>(*reinterpret_cast<short*>(classData + (systemVal + 0x1A9) * 2 + 0xAC));
					} else if (systemVal == -0x19D) {
						value = *reinterpret_cast<unsigned short*>(classData + 0x3C8);
					}
				} else if (systemVal < -0x191 && systemVal > -0x19A) {
					value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0x199) * 2 + 0x3B8);
				}
			} else if (systemVal < -0x95 && systemVal > -0x176) {
				u8* itemTable = *reinterpret_cast<u8**>(classData + 0x24);
				value = *reinterpret_cast<unsigned short*>(itemTable + (systemVal + 0x175) * 2);
			} else if (systemVal == -0x45) {
				value = *reinterpret_cast<unsigned short*>(classData + 0x22);
			} else if (systemVal < -0x45) {
				if (systemVal == -0x82) {
					value = *reinterpret_cast<unsigned short*>(classData + 0x14);
				} else if (systemVal < -0x82) {
					if (systemVal == -0x84) {
						value = *reinterpret_cast<unsigned short*>(classData + 0x18);
					} else if (systemVal > -0x95) {
						value = *reinterpret_cast<unsigned short*>(classData + (systemVal + 0x94) * 2 + 0x8C);
					}
				} else if (systemVal < -0x52 && systemVal > -0x7A) {
					value = *reinterpret_cast<unsigned short*>(classData + (-0x53 - systemVal) * 2 + 0x3E);
				}
			} else if (systemVal == -0x41) {
				value = *reinterpret_cast<unsigned short*>(classData + 0x1C);
			} else if (systemVal < -0x41) {
				if (systemVal == -0x43) {
					value = *reinterpret_cast<unsigned short*>(classData + 0x1E);
				} else if (systemVal < -0x43) {
					value = *reinterpret_cast<unsigned short*>(classData + 0x20);
				}
			} else {
				value = *reinterpret_cast<unsigned short*>(classData + 0x1A);
			}

			LastResult(this) = value;
		} else {
			switch (systemVal) {
				case -0x1B:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x60);
					break;
				case -0x19:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x520);
					break;
				case -0x18:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x1BC);
					break;
				case -0x17:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x170);
					break;
				case -0x16:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x16C);
					break;
				case -0x15:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x168);
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11:
					LastResult(this) = static_cast<unsigned int>(*reinterpret_cast<short*>(engineObject + (systemVal + 0x14) * 2 + 0x510));
					break;
				case -0x10:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x504);
					break;
				case -0xF:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x500);
					break;
				case -0xD:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x188);
					break;
				case -0xC: {
					u8 bits = *(engineObject + 0x50);
					LastResult(this) = static_cast<unsigned int>(static_cast<int>((static_cast<unsigned int>(bits) << 0x19 | static_cast<unsigned int>(bits >> 7))) >> 0x1F);
					break;
				}
				case -0xB:
					LastResult(this) = static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<signed char*>(engineObject + 0x53)));
					break;
				case -0xA: {
					u8 bits = *(engineObject + 0x50);
					LastResult(this) = static_cast<unsigned int>(static_cast<int>((static_cast<unsigned int>(bits) << 0x1C | static_cast<unsigned int>(bits >> 4))) >> 0x1F);
					break;
				}
				case -9:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x94);
					break;
				case -8:
					LastResult(this) = (*reinterpret_cast<unsigned int*>(engineObject + 0x4CC) >> 0x17) & 0xF;
					break;
				case -7:
					LastResult(this) = static_cast<unsigned int>(static_cast<int>(static_cast<unsigned int>(*(engineObject + 0x50)) << 0x18) >> 0x1F);
					break;
				case -6:
					LastResult(this) = static_cast<unsigned int>(*reinterpret_cast<short*>(engineObject + 0x30));
					break;
				case -5:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x184);
					break;
				case -4:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x1B4);
					break;
				case -3:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x164);
					break;
				case -2:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x160);
					break;
				case -1:
					LastResult(this) = *reinterpret_cast<unsigned int*>(engineObject + 0x15C);
					break;
				default:
					break;
			}
		}
	} else {
		LastResult(this) = 0;
	}

	return reinterpret_cast<CFlatRuntime::CVal*>(&LastResult(this));
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
void CFlatRuntime2::onSetClassSystemVal(int, CFlatRuntime::CObject* object, CFlatRuntime::CStack* stack, int setMode)
{
	u8* const engineObject = reinterpret_cast<u8*>(object->m_engineObject);
	const unsigned int engineFlags = CallEngineFlags(engineObject);
	const int systemVal = static_cast<int>(object->m_localBase[0]);

	if ((engineFlags & 5) == 5 || systemVal != -0x1B) {
		if (systemVal < -0x3F) {
			u8* const classData = *reinterpret_cast<u8**>(engineObject + 0x58);

			if (systemVal < -0xD7F) {
				if (systemVal == -0xDB8) {
					StoreU16(stack, reinterpret_cast<unsigned short*>(engineObject + 0x6D4), setMode);
				} else if (systemVal < -0xDB8) {
					if (systemVal == -0xDBA) {
						StoreU32(stack, reinterpret_cast<unsigned int*>(engineObject + 0x6EC), setMode);
					} else if (systemVal > -0xDBB) {
						StoreU16(stack, reinterpret_cast<unsigned short*>(engineObject + 0x6D6), setMode);
					}
				} else if (systemVal < -0xD97) {
					if (systemVal < -0xDA7) {
						StoreU16(stack, reinterpret_cast<unsigned short*>(classData + (systemVal + 0xDB7) * 2 + 0xF0), setMode);
					} else {
						StoreU16(stack, reinterpret_cast<unsigned short*>(classData + (systemVal + 0xDA7) * 2 + 0xD0), setMode);
					}
				}
			} else if (systemVal < -399) {
				if (systemVal < -999 && systemVal > -0xBE8) {
					const unsigned int bit = static_cast<unsigned int>(systemVal + 0xBE7);
					const int sign = static_cast<int>(bit) >> 0x1F;
					const int rounded = static_cast<int>(bit >> 3) + static_cast<int>((static_cast<int>(bit) < 0) && ((bit & 7) != 0));
					const unsigned int mask = 1U << (((sign * 8) | ((bit * 0x20000000U + static_cast<unsigned int>(sign)) >> 0x1D)) - sign);
					u8* const byteRef = classData + rounded + 0x8A4;
					const unsigned int oldValue = static_cast<unsigned int>(-((*byteRef & static_cast<u8>(mask)) != 0));

					stack[-1].m_word = oldValue;
					unsigned int newValue = oldValue;

					if (setMode == 0) {
						newValue = stack->m_word;
					} else if (setMode == 1) {
						newValue += stack->m_word;
					} else if (setMode == -1) {
						newValue -= stack->m_word;
					}

					if (newValue == 0) {
						*byteRef &= static_cast<u8>(~mask);
					} else {
						*byteRef |= static_cast<u8>(mask);
					}
				} else if (systemVal < -499 && systemVal > -0x2F4) {
					StoreS16(stack, reinterpret_cast<short*>(classData + (systemVal + 0x2F3) * 2 + 0x9A4), setMode);
				} else if (systemVal == -0x19D) {
					StoreU16(stack, reinterpret_cast<unsigned short*>(classData + 0x3C8), setMode);
				} else if (systemVal < -0x19D) {
					if (systemVal == -0x1B6) {
						StoreU16(stack, reinterpret_cast<unsigned short*>(classData + 0x3DE), setMode);
					} else if (systemVal < -0x1A5 && systemVal >= -0x1A9) {
						StoreS16(stack, reinterpret_cast<short*>(classData + (systemVal + 0x1A9) * 2 + 0xAC), setMode);
					}
				} else if (systemVal < -0x199) {
					if (systemVal < -0x19B) {
						StoreU32(stack, reinterpret_cast<unsigned int*>(classData + 0x200), setMode);
					}
				} else if (systemVal < -0x191) {
					StoreU16(stack, reinterpret_cast<unsigned short*>(classData + (systemVal + 0x199) * 2 + 0x3B8), setMode);
				}
			} else if (systemVal < -0x95 && systemVal > -0x176) {
				u8* const itemTable = *reinterpret_cast<u8**>(classData + 0x24);
				StoreU16(stack, reinterpret_cast<unsigned short*>(itemTable + (systemVal + 0x175) * 2), setMode);
			} else if (systemVal < -0x52) {
				if (systemVal < -0x84) {
					if (systemVal > -0x95) {
						StoreU16(stack, reinterpret_cast<unsigned short*>(classData + (systemVal + 0x94) * 2 + 0x8C), setMode);
					}
				} else if (systemVal > -0x7A) {
					StoreU16(stack, reinterpret_cast<unsigned short*>(classData + (-0x53 - systemVal) * 2 + 0x3E), setMode);
				}
			} else if (systemVal == -0x40) {
				StoreU16(stack, reinterpret_cast<unsigned short*>(classData + 0x1A), setMode);
			} else if (systemVal < -0x40 && systemVal > -0x42) {
				StoreU16(stack, reinterpret_cast<unsigned short*>(classData + 0x1C), setMode);
			}

			LastResult(this) = 0;
		} else {
			switch (systemVal) {
				case -0x1B:
					StoreU32(stack, reinterpret_cast<unsigned int*>(engineObject + 0x60), setMode);
					break;
				case -0x1A: {
					stack[-1].m_word = static_cast<unsigned int>(static_cast<signed char>(*(engineObject + 0x56)));
					signed char value = static_cast<signed char>(stack[-1].m_word);
					if (setMode == 0) {
						value = static_cast<signed char>(stack->m_word);
					} else if (setMode == 1) {
						value = static_cast<signed char>(value + static_cast<signed char>(stack->m_word));
					} else if (setMode == -1) {
						value = static_cast<signed char>(value - static_cast<signed char>(stack->m_word));
					}
					*(engineObject + 0x56) = static_cast<u8>(value);
					break;
				}
				case -0x18:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x1BC), setMode);
					break;
				case -0x17:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x170), setMode);
					break;
				case -0x16:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x16C), setMode);
					break;
				case -0x15:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x168), setMode);
					break;
				case -0x14:
				case -0x13:
				case -0x12:
				case -0x11:
					StoreS16(stack, reinterpret_cast<short*>(engineObject + (systemVal + 0x14) * 2 + 0x510), setMode);
					break;
				case -0x10:
					StoreU32(stack, reinterpret_cast<unsigned int*>(engineObject + 0x504), setMode);
					break;
				case -0xF:
					StoreU32(stack, reinterpret_cast<unsigned int*>(engineObject + 0x500), setMode);
					break;
				case -0xD:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x188), setMode);
					break;
				case -0xB: {
					signed char* value = reinterpret_cast<signed char*>(engineObject + 0x53);
					stack[-1].m_word = static_cast<unsigned int>(static_cast<int>(*value));
					if (setMode == 0) {
						*value = static_cast<signed char>(stack->m_word);
					} else if (setMode == 1) {
						*value = static_cast<signed char>(*value + static_cast<signed char>(stack->m_word));
					} else if (setMode == -1) {
						*value = static_cast<signed char>(*value - static_cast<signed char>(stack->m_word));
					}
					break;
				}
				case -0xA: {
					const int oldBit = static_cast<int>((static_cast<unsigned int>(*(engineObject + 0x50)) << 0x1C) >> 0x1F);
					stack[-1].m_word = static_cast<unsigned int>(oldBit);
					int bitValue = oldBit;
					if (setMode == 0) {
						bitValue = static_cast<int>(static_cast<signed char>(stack->m_word));
					} else if (setMode == 1) {
						bitValue += static_cast<int>(static_cast<signed char>(stack->m_word));
					} else if (setMode == -1) {
						bitValue -= static_cast<int>(static_cast<signed char>(stack->m_word));
					}
					*(engineObject + 0x50) =
					    static_cast<u8>((static_cast<unsigned int>(bitValue) << 3) & 8) | (*(engineObject + 0x50) & 0xF7);
					break;
				}
				case -9:
					StoreU32(stack, reinterpret_cast<unsigned int*>(engineObject + 0x94), setMode);
					break;
				case -5:
					StoreF32(stack, reinterpret_cast<float*>(engineObject + 0x184), setMode);
					break;
				default:
					break;
			}
		}
	} else if (System.m_execParam > 1) {
	}
}
