#include "ffcc/cflat_r2class.h"
#include "ffcc/gobject.h"

extern "C" int __cntlzw(unsigned int);
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
void CFlatRuntime2::onClassSystemVal(CFlatRuntime::CObject* object, int systemVal)
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime2::onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int)
{
	// TODO
}
