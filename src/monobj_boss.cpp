#include "ffcc/monobj_boss.h"
#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/partyobj.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/game.h"
#include "ffcc/vector.h"
#include "ffcc/cflat_runtime2.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void CGMonObj_ResetActionState(CGMonObj*);
extern float FLOAT_80331dd0;
extern const float FLOAT_80331cf8 = 0.0f;
extern float FLOAT_80331dcc;
extern float FLOAT_80331dc8;
extern float FLOAT_80331d18;
extern float FLOAT_80331d1c;
extern float FLOAT_80331d20;
extern float FLOAT_80331dd4;
extern float FLOAT_80331d24;
extern float FLOAT_80331d28;
extern float FLOAT_80331d2c;
extern float FLOAT_80331d30;
extern float FLOAT_80331d58;
extern float FLOAT_80331d5c;
extern float FLOAT_80331d6c;
extern float FLOAT_80331d70;
extern float FLOAT_80331d74;
extern float FLOAT_80331d7c;
extern float FLOAT_80331d80;
extern float FLOAT_80331d78;
extern float FLOAT_80331d84;
extern float FLOAT_80331d88;
extern float FLOAT_80331d8c;
extern float FLOAT_80331d90;
extern float FLOAT_80331d94;
extern float FLOAT_80331d98;
extern float FLOAT_80331d9c;
extern float FLOAT_80331da0;
extern float FLOAT_80331da4;
extern float FLOAT_80331da8;
extern float FLOAT_80331dac;
extern float FLOAT_80331db0;
extern float FLOAT_80331db4;
extern float FLOAT_80331dd8;
extern float FLOAT_80331d60;
extern float FLOAT_80331db8;
extern double DOUBLE_80331d00 = 0.5;
extern double DOUBLE_80331d08 = 3.0;
extern double DOUBLE_80331d10;
extern double DOUBLE_80331d38;
extern double DOUBLE_80331dc0;
extern "C" char s_meteo_3_80331D64[8];
extern char SoundBuffer[];
extern char SoundBuffer_1260_[];
extern "C" float MG_GBA_THREAD_MSG_SETPORT_ct;
extern "C" char g_errCt;
extern "C" Vec gGoblinKingTeleportPoints[] = {
    {-1.5f, -5.989999771118164f, -44.279998779296875f},
    {-85.16000366210938f, -5.949999809265137f, 41.400001525878906f},
    {83.87999725341797f, -5.739999771118164f, 43.209999084472656f},
    {-1.6399999856948853f, 13.739999771118164f, -141.4499969482422f},
};

extern "C" Vec gLichTeleportPoints[] = {
    {0.0f, 25.360000610351562f, -137.0f},
    {0.0f, 0.0f, -38.0f},
    {-132.0f, 0.0f, -38.0f},
    {132.0f, 0.0f, -38.0f},
};

static const char s_to_a_obj_801dd4e8[] = "to_a_obj";
static const char s_to_b_obj_801dd4f4[] = "to_b_obj";
static const char s_to_02d_obj_801dd500[] = "to_%02d_obj";

typedef void (*MonObjSawCallback)(CGMonObj*, int, int, int);

struct MeteoParasiteCBossWork {
    int m_lichTeleportIndex;
    Vec m_lichTeleportVec;
    union {
        u8 m_lichFlags;
        struct {
            u8 m_lichBit80 : 1;
            u8 m_lichBit40 : 1;
            u8 m_lichRest : 6;
        } lichBits;
    };
    u8 m_pad11[0x37];
    CGPrgObj* m_objs[4];
    int m_coreIndex;
    u8 m_coreFlags;
    u8 m_pad5D[3];
    int m_coreMode;
    int m_coreWait;
    u8 m_pad68[0x0C];
    CGMonObj* m_obj;
    int m_index;
    union {
        u8 m_flags;
        struct {
            u8 m_bit80 : 1;
            s8 m_meteo3 : 1;
            u8 m_rest : 6;
        } bits;
    };
    u8 m_pad7D[7];
    int m_wait;
};

struct DuctBossWork {
    u8 m_pad00[0x38];
    CGMonObj* m_objs[3];
};

struct MonObjSawBossAiFlags {
    u8 m_bit80 : 1;
    u8 m_rest : 7;
};

/*
 * --INFO--
 * PAL Address: 0x80132f68
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGiantCrab()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<int*>(SoundBuffer + 1260) = 1;

	const int branch = *reinterpret_cast<int*>(mon + 0x6B4);
	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	if (script == 0) {
		return;
	}

	if (branch == 1) {
		if ((script[0x1A / 2] / 3) <= script[7]) {
			return;
		}
		object->DispCharaParts(1);
		int pdtNo = -1;
		if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		}
		prgObj->putParticle((pdtNo << 8) | 0x0D, 0, object, FLOAT_80331d18, 0);
		prgObj->playSe3D(0x4E37, 0x32, 500, 0, 0);
	} else {
		if (branch != 0) {
			return;
		}
		if (((script[0x1A / 2] * 2) / 3) <= script[7]) {
			return;
		}
		object->DispCharaParts(3);
		int pdtNo = -1;
		if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		}
		prgObj->putParticle((pdtNo << 8) | 0x0C, 0, object, FLOAT_80331d18, 0);
		prgObj->playSe3D(0x4E36, 0x32, 500, 0, 0);
	}

	prgObj->changeStat(4, 0, 0);
	*reinterpret_cast<int*>(mon + 0x6B4) = branch + 1;
	*reinterpret_cast<int*>(mon + 0x6C8) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80132e80
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncGiantCrab()
{
	int nextState = -1;
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (*reinterpret_cast<int*>(m_boss__8CGMonObj) != 0) {
		*reinterpret_cast<int*>(m_boss__8CGMonObj) = 0;
		if ((*reinterpret_cast<int*>(mon + 0x6D0) == 0 && static_cast<unsigned int>(Math.Rand(10)) < 1) ||
		    (*reinterpret_cast<int*>(mon + 0x6D0) == 1 && static_cast<unsigned int>(Math.Rand(10)) < 2) ||
		    (*reinterpret_cast<int*>(mon + 0x6D0) == 2 && static_cast<unsigned int>(Math.Rand(10)) < 3)) {
			nextState = 100;
		}
	}

	if (nextState != -1) {
		prgObj->changeStat(nextState, 0, 0);
	} else {
		logicFuncDefault();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80132e78
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncGiantCrab(int)
{
	u8* mon = reinterpret_cast<u8*>(this);
	return *reinterpret_cast<int*>(mon + 0x6D0);
}

/*
 * --INFO--
 * PAL Address: 0x801329e8
 * PAL Size: 1168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGiantCrab()
{
	u8* self = (u8*)this;
	int state = *(int*)(self + 0x520);

	if (state == 100) {
		if (*(int*)(self + 0x528) == 0) {
			int soundStep = *(int*)(SoundBuffer + 0x4f0);
			if (soundStep == 2) {
				*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dd0;
				*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
				*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dcc;
			} else if (soundStep < 2) {
				if (soundStep == 0) {
					*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dc8;
					*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
					*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dcc;
				} else if (soundStep > -1) {
					*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dc8;
					*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
					*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dc8;
				}
			} else if (soundStep < 4) {
				*(float*)(SoundBuffer + 0x4f4) = FLOAT_80331dd0;
				*(float*)(SoundBuffer + 0x4f8) = FLOAT_80331cf8;
				*(float*)(SoundBuffer + 0x4fc) = FLOAT_80331dc8;
			}

			*(int*)(SoundBuffer + 0x4f0) = (soundStep + 1) & 3;
			reinterpret_cast<CGPrgObj*>(self)->reqAnim(0xc, 0, 0);

			int pdtIndex = -1;
			u8* charaModelHandle = *(u8**)(self + 0xf8);
			if (charaModelHandle != 0) {
				u8* pdtLoadRef = *(u8**)(charaModelHandle + 0x178);
				if (pdtLoadRef != 0) {
					pdtIndex = *(int*)(pdtLoadRef + 0x14);
				}
			}
			reinterpret_cast<CGPrgObj*>(self)->putParticle(
				(pdtIndex << 8) | 6, 0, reinterpret_cast<CGObject*>(self), FLOAT_80331d18, 0);
			reinterpret_cast<CGPrgObj*>(self)->putParticle(
				(pdtIndex << 8) | 7, 0, reinterpret_cast<CGObject*>(self), FLOAT_80331d18, 0);
		}

		int frame = *(int*)(self + 0x528);
		if (frame > 0x20) {
			if (frame == 0x21) {
				reinterpret_cast<CGPrgObj*>(self)->playSe3D(0x4e30, 0x32, 0x1c2, 0, 0);
			} else if (frame == 0x32) {
				reinterpret_cast<CGPrgObj*>(self)->playSe3D(0x4e35, 0x32, 0x1c2, 0, 0);
			}

			*(u32*)(self + 0x1c0) &= 0xfff7fffd;
			float moveScale = PSVECDistance((Vec*)(SoundBuffer + 0x4f4), (Vec*)(self + 0x15c)) * FLOAT_80331dd4;
			Vec moveDir = { 0.0f, 0.0f, 0.0f };
			reinterpret_cast<CGObject*>(self)->Move(&moveDir, moveScale, 0x10, 1, 0, 0, 0);

			int targetIdx = *(int*)(self + 0x6c4);
			if (targetIdx > -1) {
				u8* target = (u8*)Game.m_partyObjArr[targetIdx];
				if (target != 0) {
					*(float*)(self + 0x1b4) = (float)atan2(
					    (double)(*(float*)(target + 0x15c) - *(float*)(self + 0x15c)),
					    (double)(*(float*)(target + 0x164) - *(float*)(self + 0x164)));
				}
			}
		}

		if (reinterpret_cast<CGPrgObj*>(self)->isLoopAnim() != 0) {
			reinterpret_cast<CGPrgObj*>(self)->changeStat(0, 0, 0);
			*(u32*)(self + 0x1c0) |= 0x80002;
		}
	} else if (state > 99 && state < 0x69) {
		if (*(int*)(self + 0x528) == 0) {
			float turnOffset = FLOAT_80331d2c;
			int animId = 1;
			if (state == 0x67) {
				turnOffset = FLOAT_80331d24;
				animId = 0x12;
			} else if (state >= 0x68) {
				turnOffset = FLOAT_80331dd8;
				animId = 0x13;
			}

			reinterpret_cast<CGPrgObj*>(self)->reqAnim(animId, 0, 0);
			u16 scriptScale = *(u16*)(*(u8**)(self + 0x7c) + 0xd4);
			float moveMagnitude =
			    *(float*)(self + 0x690) *
			    (FLOAT_80331d60 * (float)((double)scriptScale - DOUBLE_80331dc0) + FLOAT_80331db8);
			reinterpret_cast<CGObject*>(self)->moveVectorHRot(
				*(float*)(self + 0x1b4) + turnOffset, FLOAT_80331cf8, moveMagnitude, 0x1e);

			int targetIdx = *(int*)(self + 0x6c4);
			if (targetIdx > -1) {
				u8* target = (u8*)Game.m_partyObjArr[targetIdx];
				if (target != 0) {
					*(float*)(self + 0x1b4) = (float)atan2(
					    (double)(*(float*)(target + 0x15c) - *(float*)(self + 0x15c)),
					    (double)(*(float*)(target + 0x164) - *(float*)(self + 0x164)));
				}
			}

			u32 action = (u32) * (void**)(self + 0x68);
			if (action == 0x63) {
				reinterpret_cast<CGPrgObj*>(self)->playSe3D(0x8cab, 0x32, 0x1c2, 0, 0);
			} else if (action < 99) {
				if (action == 0x5b) {
					reinterpret_cast<CGPrgObj*>(self)->playSe3D(0x4e2a, 0x32, 0x1c2, 0, 0);
				}
			} else if (action == 0x6b) {
				reinterpret_cast<CGPrgObj*>(self)->playSe3D(0xfdf3, 0x32, 0x1c2, 0, 0);
			}
		}

		if (*(int*)(self + 0x528) == 0x19) {
			reinterpret_cast<CGPrgObj*>(self)->changeStat(0, 0, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801329b4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGolem()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	if (script[0x1C / 2] == 0) {
		object->DispCharaParts(7);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013296c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncGolem(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-10);
		break;
	case 101:
		setActionParam(-9);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013292c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncGolem(int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	if (*reinterpret_cast<int*>(mon + 0x6D0) == 1) {
		return 2;
	}

	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	return static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(script[0x1C / 2] >= (script[0x1A / 2] >> 1)))) >> 5;
}

/*
 * --INFO--
 * PAL Address: 0x80132670
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGolem()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int state = reinterpret_cast<CGPrgObj*>(this)->m_lastStateId;

	if (state != 0x66) {
		if (state < 0x66) {
			if (state == 100) {
				if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0) {
					reinterpret_cast<CGPrgObj*>(this)->playSe3D(0xFA17, 0x32, 0x96, 0, 0);
				} else if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0x14) {
					reinterpret_cast<CGObject*>(this)->DispCharaParts(1);
					reinterpret_cast<CGPrgObj*>(this)->playSe3D(0xFA18, 0x32, 0x96, 0, 0);
					*reinterpret_cast<int*>(self + 0x6D0) = 1;
				}
				reinterpret_cast<CGCharaObj*>(this)->statAttack();
				return;
			}
			if (state < 100) {
				return;
			}
			int frame = reinterpret_cast<CGPrgObj*>(this)->m_stateFrame;
			if (frame == 0) {
				reinterpret_cast<CGPrgObj*>(this)->playSe3D(0xFA1A, 0x32, 0x96, 0, 0);
			} else if (frame == 4) {
				reinterpret_cast<CGObject*>(this)->DispCharaParts(3);
				*reinterpret_cast<int*>(self + 0x6D0) = 0;
			} else if (frame == 5) {
				reinterpret_cast<CGObject*>(this)->DispCharaParts(7);
			}
			reinterpret_cast<CGCharaObj*>(this)->statAttack();
			return;
		}
		if (state != 0x68) {
			if (0x67 < state) {
				return;
			}
			if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame != 0x32) {
				return;
			}
			reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
			return;
		}
	}

	if ((reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0x14) ||
	    ((reinterpret_cast<CGObject*>(this)->m_stateFlags0 & 0x40) != 0) ||
	    ((state == 0x66) &&
	     (*reinterpret_cast<float*>(self + 0x5D0 + *reinterpret_cast<int*>(self + 0x6C4) * 4) <
	      FLOAT_80331d58 * reinterpret_cast<CGObject*>(this)->m_bodyEllipsoidRadius))) {
		reinterpret_cast<CGObject*>(this)->m_rotTargetY =
		    reinterpret_cast<CGPrgObj*>(this)->getTargetRot(
		        reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[*reinterpret_cast<int*>(self + 0x6C4)]));
		setAttackAfter(*reinterpret_cast<int*>(self + 0x560));
	} else {
		if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0) {
			float turnOffset = FLOAT_80331cf8;
			if (state == 0x68) {
				turnOffset = FLOAT_80331d2c;
			}
			reinterpret_cast<CGPrgObj*>(this)->reqAnim(1, 1, 0);
			reinterpret_cast<CGObject*>(this)->m_rotTargetY =
			    reinterpret_cast<CGPrgObj*>(this)->getTargetRot(
			        reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[*reinterpret_cast<int*>(self + 0x6C4)]));
			*reinterpret_cast<float*>(SoundBuffer + 0x4FC) = reinterpret_cast<CGObject*>(this)->m_rotTargetY + turnOffset;
		}
		unsigned short scriptScale =
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(reinterpret_cast<CGObject*>(this)->m_scriptHandle[9]) + 0xD4);
		float moveSpeed =
		    *reinterpret_cast<float*>(self + 0x690) *
		    (FLOAT_80331d60 * (static_cast<float>(static_cast<double>(scriptScale) - DOUBLE_80331dc0)) + FLOAT_80331db8);
		reinterpret_cast<CGObject*>(this)->moveVectorHRot(*reinterpret_cast<float*>(SoundBuffer + 0x4FC), FLOAT_80331cf8,
		                                                  moveSpeed, 1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80132640
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncArmstrong(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-14);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80132600
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncArmstrong()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId == 100) {
		enableDamageCol(1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013256c
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncArmstrong()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	int state = prgObj->m_lastStateId;
	if (state == 100) {
		if (prgObj->m_stateFrame == 0) {
			charaObj->enableDamageCol(0);
		} else if (prgObj->m_stateFrame == 0x29) {
			charaObj->enableDamageCol(1);
		}
		charaObj->statAttack();
	} else if (state > 99 && state < 0x69) {
		frameStatFuncGiantCrab();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80132538
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncOrcKing()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0xC00);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801322dc
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncOrcKing()
{
	u8* self = reinterpret_cast<u8*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);

	if (prgObj->m_lastStateId != 100) {
		return;
	}

	int branch = *reinterpret_cast<int*>(self + 0x6D0);
	if (branch == 0) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		prgObj->putParticle((pdtNo << 8) | 0x18, *reinterpret_cast<int*>(self + 0x58C), object, FLOAT_80331d18, 0x8CC0);
		prgObj->reqAnim(0xF, 0, 0);
		object->SetAnimSlot(0x10, 0);
		object->SetAnimSlot(0x15, 4);
	} else if (branch == 0x96) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		prgObj->putParticle((pdtNo << 8) | 0x19, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC1);
	} else if (branch == 300) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		prgObj->putParticle((pdtNo << 8) | 0x1A, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC2);
	} else if (branch == 0x1C2) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		prgObj->putParticle((pdtNo << 8) | 0x1B, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC3);
	} else if (branch == 600) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0xC00);
		object->m_bgColMask &= 0xFFF7FFFF;
		prgObj->changeStat(-9, 0, 0);
		object->SetAnimSlot(0, 0);

		CGMonObj* monObj = gCFlatRuntime2.FindGMonObjFirst();
		while (monObj != 0) {
			if (monObj != this) {
				u8* monBytes = reinterpret_cast<u8*>(monObj);
				u16* script = *reinterpret_cast<u16**>(monBytes + 0x58);
				reinterpret_cast<CGCharaObj*>(monObj)->addHp(-script[0x1A / 2], 0);
			}
			monObj = gCFlatRuntime2.FindGMonObjNext(monObj);
		}
		*reinterpret_cast<int*>(SoundBuffer + 1260) = 1;
	}

	*reinterpret_cast<int*>(self + 0x6D0) = branch + 1;
}

/*
 * --INFO--
 * PAL Address: 0x80132160
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::alwaysFuncOrcKing()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	int& active = *reinterpret_cast<int*>(SoundBuffer + 1260);
	int& timer = *reinterpret_cast<int*>(SoundBuffer + 1264);
	if (active == 0) {
		return;
	}

	if (timer == 0x3C && object->m_charaModelHandle != 0) {
		object->m_charaModelHandle->ChangeTexture(1, 0x39, 1, 0xFFFFFFFF, 0);
		int pdtNo = -1;
		if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		}
		prgObj->putParticle(
			(pdtNo << 8) | 0x1D, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x590), object,
			FLOAT_80331d18, 0);
	} else if (timer == 300 && Game.m_gameWork.m_gameOverFlag == 0) {
		prgObj->playSe3D(0x8CBF, 0x32, 0x96, 0, 0);
		active = 0;
		CFlatBossState() = 1;
	}

	if (active != 0) {
		timer += 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013215c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncOrcKing()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80132158
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncOrcKing()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80132100
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncOrcKing(int)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	int branch = 0;
	if (script != 0 && script[7] < (script[0x1A / 2] / 5)) {
		branch = 2;
	} else {
		branch = calcBranchFuncDefault(1);
	}
	return branch;
}

/*
 * --INFO--
 * PAL Address: 0x801320cc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncGoblinKing()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013204c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGoblinKing()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	switch (prgObj->m_lastStateId) {
	case 100:
		teleport(0, 0xd, 8, 0x42, 0xa03e, 0xa03f, 3, 4, 5, gGoblinKingTeleportPoints,
		         *reinterpret_cast<int*>(m_boss__8CGMonObj), *reinterpret_cast<Vec*>(m_boss__8CGMonObj + 4));
		break;
	}
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8013203c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncGoblinKing(int)
{
	return CFlatBossState();
}

/*
 * --INFO--
 * PAL Address: 0x80132008
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncSaw()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131dd8
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncSaw()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (prgObj->m_lastStateId == 100) {
		mon[0x63C] = mon[0x63C] & 0x7F | 0x80;

		if (prgObj->m_subState == 0) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(10, 0, 0);

				CRef* pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
				int pdtNo;
				if (pdtLoadRef == 0) {
					pdtNo = -1;
				} else {
					pdtNo = reinterpret_cast<int*>(pdtLoadRef)[5];
				}

				prgObj->putParticle(pdtNo << 8, *reinterpret_cast<int*>(mon + 0x564), object, FLOAT_80331d18, 0x1C52C);
				prgObj->playSe3D(0x1C52B, 0x32, 0x96, 0, 0);
				memset(mon + 0x70C, 0, 0x34);
				*reinterpret_cast<int*>(mon + 0x70C) = 0x1402;
			} else if (prgObj->isLoopAnim() != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				*reinterpret_cast<int*>(mon + 0x560) = 0x495;
				prgObj->reqAnim(1, 1, 0);
			}

			if (prgObj->m_subFrame == 0x19) {
				reinterpret_cast<CGCharaObj*>(this)->resetIgnoreHit();
				(*reinterpret_cast<MonObjSawCallback*>(*reinterpret_cast<int*>(this) + 0x90))(this, 1, 0, 0);
				mon[0x6C0] = 0;
			}

			if (prgObj->m_subFrame > 0x19 && mon[0x6C0] != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 2) {
			if (prgObj->m_subFrame == 0) {
				(*reinterpret_cast<MonObjSawCallback*>(*reinterpret_cast<int*>(this) + 0x90))(this, 0, 0, 0);
				mon[0x6C0] = 0;
				prgObj->reqAnim(0xB, 0, 0);
				reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
				prgObj->playSe3D(0x1C52D, 0x32, 0x96, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				prgObj->changeStat(0, 0, 0);
			}
		}

		moveFrame();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131d04
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncSaw()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	int bossState = CFlatBossState();

	if (bossState == 0 &&
	    static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(m_boss__8CGMonObj[0x14]) << 24) & 0xC0000000) >> 31) != 0) {
		reinterpret_cast<MonObjSawBossAiFlags*>(m_boss__8CGMonObj + 0x14)->m_bit80 = 0;
	}

	if (bossState != 0 &&
	    static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(m_boss__8CGMonObj[0x14]) << 24) & 0xC0000000) >> 31) == 0) {
		if (prgObj->m_lastStateId != 100) {
			prgObj->changeStat(100, 0, 0);
		}
	} else {
		if (prgObj->m_lastStateId == 100 && prgObj->m_subState == 1) {
			prgObj->addSubStat();
		}
	}
	int& cooldown = *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x8);
	cooldown = (cooldown - 1) & ~((cooldown - 1) >> 31);
}

/*
 * --INFO--
 * PAL Address: 0x80131c24
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncSaw()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	float& phase0 = *reinterpret_cast<float*>(SoundBuffer + 1260);
	float& phase1 = *reinterpret_cast<float*>(SoundBuffer + 1264);
	const float wave = FLOAT_80331d1c * (FLOAT_80331d18 + sinf(phase1)) + FLOAT_80331d30;
	*reinterpret_cast<float*>(mon + 0x718) = wave * (FLOAT_80331dac * sinf(phase0));
	*reinterpret_cast<float*>(mon + 0x720) = wave * (FLOAT_80331d84 * cosf(phase0));
	phase0 = phase0 + FLOAT_80331db0 * (FLOAT_80331d30 - (wave - FLOAT_80331d30)) + FLOAT_80331d60;
	phase1 = phase1 + FLOAT_80331db4;
}

/*
 * --INFO--
 * PAL Address: 0x80131bd8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackedFuncSaw()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId == 100) {
		prgObj->addSubStat();
		*reinterpret_cast<unsigned char*>(SoundBuffer_1260_ + 0x14) |= 0x80;
		*reinterpret_cast<int*>(SoundBuffer_1260_ + 0x8) = 0xFA;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013197c
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLKShooter()
{
	u8* self = reinterpret_cast<u8*>(this);

	int cooldown0 = *reinterpret_cast<int*>(SoundBuffer_1260_ + 0xC) - 1;
	int cooldown1 = *reinterpret_cast<int*>(SoundBuffer_1260_ + 0x10) - 1;
	*reinterpret_cast<int*>(SoundBuffer_1260_ + 0xC) = cooldown0 & ~(cooldown0 >> 31);
	*reinterpret_cast<int*>(SoundBuffer_1260_ + 0x10) = cooldown1 & ~(cooldown1 >> 31);

	const int state = *reinterpret_cast<int*>(self + 0x520);
	if (state == 0x65) {
		goto state101;
	}
	if (state >= 0x65) {
		goto resetBranch;
	}
	if (state >= 100) {
		goto state100;
	}
	goto resetBranch;

state100:
	self[0x63C] = (self[0x63C] & 0x7F) | 0x80;
	if (*reinterpret_cast<int*>(self + 0x528) == 0) {
		memset(self + 0x70C, 0, 0x34);
		*reinterpret_cast<int*>(self + 0x70C) = 0x322;

		if (*reinterpret_cast<int*>(self + 0x6D0) == 1) {
			CVector targetPos(FLOAT_80331d9c, FLOAT_80331cf8, FLOAT_80331d9c);
			*reinterpret_cast<float*>(self + 0x718) = targetPos.x;
			*reinterpret_cast<float*>(self + 0x71C) = targetPos.y;
			*reinterpret_cast<float*>(self + 0x720) = targetPos.z;
		} else {
			CVector targetPos(FLOAT_80331d90, FLOAT_80331cf8, FLOAT_80331d94);
			*reinterpret_cast<float*>(self + 0x718) = targetPos.x;
			*reinterpret_cast<float*>(self + 0x71C) = targetPos.y;
			*reinterpret_cast<float*>(self + 0x720) = targetPos.z;
		}
		*reinterpret_cast<float*>(self + 0x728) = FLOAT_80331da0;
		*reinterpret_cast<int*>(self + 0x738) = 0x65;
	}

	moveFrame();
	const int branch = *reinterpret_cast<int*>(self + 0x6D0);
	const int flatFlags = CFlatBossState();
	if ((*reinterpret_cast<volatile signed char*>(SoundBuffer_1260_ + 0x14) < 0) ||
	    ((branch == 1) && ((flatFlags & 1) != 0)) || ((branch == 2) && ((flatFlags & 2) != 0))) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
	}
	return;

state101:
	if (*reinterpret_cast<int*>(self + 0x528) == 0) {
		reinterpret_cast<CGPrgObj*>(this)->reqAnim(-1, 0, 0);
		rotTarget(*reinterpret_cast<int*>(self + 0x6C4), FLOAT_80331da4);
	}
	if ((*reinterpret_cast<volatile signed char*>(SoundBuffer_1260_ + 0x14) < 0) ||
	    (*reinterpret_cast<float*>(self + 0x5D0 + *reinterpret_cast<int*>(self + 0x620) * 4) < FLOAT_80331da8)) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
	}
	return;

resetBranch:
	if (*reinterpret_cast<int*>(self + 0x6D0) == 1) {
		*reinterpret_cast<int*>(self + 0x6D0) = 0;
		*reinterpret_cast<volatile unsigned char*>(SoundBuffer_1260_ + 0x14) &= 0xDF;
		*reinterpret_cast<int*>(SoundBuffer_1260_ + 0x10) = 0xFA;
	}
	if (*reinterpret_cast<int*>(self + 0x6D0) == 2) {
		*reinterpret_cast<int*>(self + 0x6D0) = 0;
		*reinterpret_cast<volatile unsigned char*>(SoundBuffer_1260_ + 0x14) &= 0xBF;
		*reinterpret_cast<int*>(SoundBuffer_1260_ + 0xC) = 0xFA;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131828
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::attackCheckFuncLKShooter(int)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	unsigned char* work = reinterpret_cast<unsigned char*>(SoundBuffer_1260_);

	if (*reinterpret_cast<int*>(work + 8) == 0) {
		if ((work[0x14] & 0x40) == 0 && (CFlatBossState() & 2) == 0) {
			CVector left(FLOAT_80331d90, FLOAT_80331cf8, FLOAT_80331d94);
			if (PSVECDistance(reinterpret_cast<Vec*>(&left), &object->m_worldPosition) < FLOAT_80331d98 &&
			    *reinterpret_cast<int*>(work + 0xC) == 0) {
				work[0x14] |= 0x40;
				*reinterpret_cast<int*>(work + 0xC) = 300;
				*reinterpret_cast<int*>(mon + 0x6D0) = 2;
				return 100;
			}
		}
		if ((work[0x14] & 0x20) == 0 && (CFlatBossState() & 1) == 0) {
			CVector right(FLOAT_80331d9c, FLOAT_80331cf8, FLOAT_80331d9c);
			if (PSVECDistance(reinterpret_cast<Vec*>(&right), &object->m_worldPosition) < FLOAT_80331d98 &&
			    *reinterpret_cast<int*>(work + 0x10) == 0) {
				work[0x14] |= 0x20;
				*reinterpret_cast<int*>(mon + 0x6D0) = 1;
				return 100;
			}
		}
	}
	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x801317f8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncDragonZombie(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-11);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801316f8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncDragonZombie()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	const int state = prgObj->m_lastStateId;
	if (state == 100) {
		object->SetAnimSlot(0x0E, 0);
		object->SetAnimSlot(0x13, 4);
		object->SetAnimSlot(0x16, 0x1A);
		object->SetAnimSlot(0x17, 0x1B);
		object->SetAnimSlot(0x18, 0x1C);
		*reinterpret_cast<int*>(mon + 0x6B4) = 1;
		return;
	}
	if (state == 4 || (state > 99 && state < 0x66)) {
		object->SetAnimSlot(0, 0);
		object->SetAnimSlot(4, 4);
		object->SetAnimSlot(0x1A, 0x1A);
		object->SetAnimSlot(0x1B, 0x1B);
		object->SetAnimSlot(0x1C, 0x1C);
		*reinterpret_cast<int*>(mon + 0x6B4) = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013164c
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncDragonZombie()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	int state = prgObj->m_lastStateId;

	if (state == 0x65) {
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(0xF, 0, 0);
			prgObj->playSe3D(0x987A, 0x32, 0x96, 0, 0);
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
		}
	} else if (state < 0x65 && state > 99) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131638
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncDragonZombie(int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	return (*reinterpret_cast<int*>(mon + 0x6D0) != 0) ? 1 : 0;
}

/*
 * --INFO--
 * PAL Address: 0x80131608
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncCaveWorm(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-8);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801315d4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncCaveWorm()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013159c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncCaveWorm()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	switch (prgObj->m_lastStateId) {
	case 100:
		suikomi(0x6c, FLOAT_80331d8c);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131554
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncLich(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-10);
		break;
	case 101:
		setActionParam(-14);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131520
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncLich()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80131294
 * PAL Size: 652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLich()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	const int flatFlags = CFlatBossState();

	if (((flatFlags & 1) == 0) && (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit80 != 0)) {
		reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit80 = 0;
		reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit40 = 1;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x6C8) = 0;
		prgObj->playSe3D(0x1157C, 0x32, 0x96, 0, 0);
	} else if (((flatFlags & 1) != 0) && (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit80 == 0)) {
		reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit80 = 1;
		reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit40 = 1;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x6C8) = 0;
		prgObj->playSe3D(0x1157D, 0x32, 0x96, 0, 0);
	}

	if (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit40 != 0) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x800);
		if (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit80 != 0) {
			int pdtNo = -1;
			if (reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<u8*>(reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			}
			prgObj->putParticle((pdtNo << 8) | 0x1D, *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x590),
			                    reinterpret_cast<CGObject*>(this), FLOAT_80331d18, 0);
		}
		reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->lichBits.m_lichBit40 = 0;
	}

	const int stat = prgObj->m_lastStateId;
	if (stat < 0x65) {
		if (stat >= 100) {
			teleport(1, 0x0E, 0x29, 100, 0x11578, 0x11579, 0x2D, 0x2B, 0x2C, gLichTeleportPoints,
			         reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_lichTeleportIndex,
			         reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_lichTeleportVec);
		}
	} else if (stat == 0x65) {
		if (prgObj->m_stateFrame == 0 && flatFlags == 3) {
			prgObj->changeStat(0, 0, 0);
		} else {
			reinterpret_cast<CGCharaObj*>(this)->statAttack();
			if (prgObj->m_stateFrame == 0x29) {
				CFlatRuntime::CStack stack[3];
				stack[0].m_word = 10;
				stack[1].m_word = 1;
				stack[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 9, 3, stack, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013127c
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncLich(int)
{
	const int flatFlags = CFlatBossState();
	return ((flatFlags >> 1) & 1) ^ 1;
}

/*
 * --INFO--
 * PAL Address: 0x801311fc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncTetsukyojin(int stat)
{
	if (stat != 0x65) {
		if (stat < 0x65) {
			if (stat != -0xD) {
				return;
			}
		} else if (stat == 0x67) {
			setActionParam(-12);
			return;
		} else {
			return;
		}
	} else {
		setActionParam(-14);
	}

	reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_lichTeleportIndex++;
}

/*
 * --INFO--
 * PAL Address: 0x801311a0
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncTetsukyojin()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	const int state = prgObj->m_lastStateId;
	switch (state) {
	case 0x66:
		object->m_bgColMask |= 0xC0002;
		return;
	case 100:
	case 0x67:
		CGMonObj_ResetActionState(this);
		return;
	default:
		return;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130d00
 * PAL Size: 1184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncTetsukyojin()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	u8* self = reinterpret_cast<u8*>(this);
	const int state = prgObj->m_lastStateId;

	if (state == 0x66) {
		if (CFlatBossState() < 1) {
			prgObj->changeStat(0, 0, 0);
		} else {
			if ((*reinterpret_cast<int*>(self + 0x6B4) == 1) && (prgObj->m_stateFrame == 0)) {
				CFlatRuntime::CStack stack[3];

				object->m_bgColMask &= 0xFFF3FFFD;
				*reinterpret_cast<int*>(self + 0x6B4) = 2;
				CFlatBossSubState() = 1;
				stack[0].m_word = 10;
				stack[1].m_word = 0;
				stack[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 9, 3, stack, 0);
			}

			if (CFlatBossSubState() == 0) {
				*reinterpret_cast<int*>(self + 0x6B4) = 0;
				*reinterpret_cast<int*>(self + 0x6C8) = 0;
				prgObj->changeStat(0, 0, 0);
			}
		}
	} else if (state == 100) {
		if (prgObj->m_stateFrame == 0) {
			CVector partyPos(Game.m_partyObjArr[*reinterpret_cast<int*>(self + 0x6C4)]->m_worldPosition);
			CVector attackDir(-partyPos.x, -partyPos.y, -partyPos.z);
			Vec attackVec;
			attackVec.x = attackDir.x;
			attackVec.y = FLOAT_80331cf8;
			attackVec.z = attackDir.z;

			if (PSVECMag(&attackVec) < FLOAT_80331d7c) {
				CVector fallback(FLOAT_80331cf8, FLOAT_80331cf8, FLOAT_80331d80);
				attackVec.x = fallback.x;
				attackVec.y = fallback.y;
				attackVec.z = fallback.z;
			}

			PSVECNormalize(&attackVec, &attackVec);
			PSVECScale(&attackVec, &attackVec, FLOAT_80331d84 - object->m_capsuleHalfHeight);
			*reinterpret_cast<Vec*>(SoundBuffer + 0x4F0) = attackVec;

			CVector objectPos(object->m_worldPosition);
			Vec delta;
			PSVECSubtract(&attackVec, reinterpret_cast<Vec*>(&objectPos), &delta);
			float distance = PSVECDistance(&delta, &object->m_worldPosition);
			float cappedDistance = FLOAT_80331d88;
			if (distance < FLOAT_80331d88) {
				cappedDistance = distance;
			}

			memset(self + 0x70C, 0, 0x34);
			*reinterpret_cast<int*>(self + 0x70C) = 0x2114;
			*reinterpret_cast<float*>(self + 0x718) = delta.x;
			*reinterpret_cast<float*>(self + 0x71C) = delta.y;
			*reinterpret_cast<float*>(self + 0x720) = delta.z;
			*reinterpret_cast<float*>(self + 0x724) = FLOAT_80331d58;
			*reinterpret_cast<int*>(self + 0x72C) = static_cast<int>(cappedDistance * FLOAT_80331d30);
			*reinterpret_cast<int*>(self + 0x738) = 0x67;
		}
		moveFrame();
	} else if (state == 0x67) {
		if (prgObj->m_stateFrame == 0x10) {
			memset(self + 0x70C, 0, 0x34);
			*reinterpret_cast<int*>(self + 0x70C) = 0x2410;

			CVector storedVec(*reinterpret_cast<Vec*>(SoundBuffer + 0x4F0));
			CVector attackDir(-storedVec.x, -storedVec.y, -storedVec.z);
			*reinterpret_cast<float*>(self + 0x718) = attackDir.x;
			*reinterpret_cast<float*>(self + 0x71C) = attackDir.y;
			*reinterpret_cast<float*>(self + 0x720) = attackDir.z;
			*reinterpret_cast<float*>(self + 0x724) = FLOAT_80331d78;
			*reinterpret_cast<int*>(self + 0x72C) =
			    static_cast<int>((FLOAT_80331d58 * (FLOAT_80331d84 - object->m_capsuleHalfHeight)) / FLOAT_80331d78);
		}
		if (prgObj->m_stateFrame > 0xF) {
			moveFrame();
		}
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	} else if (state > 99) {
		if ((CFlatBossState() != 0) && (prgObj->m_stateFrame == 0x25)) {
			int flatCount = CFlatBossState();
			if (flatCount < 1) {
				CFlatBossState() = 0;
			} else if (((flatCount == 1) && (*reinterpret_cast<int*>(SoundBuffer + 0x4EC) > 0x13)) ||
			           ((flatCount > 1) && (*reinterpret_cast<int*>(SoundBuffer + 0x4EC) > 4))) {
				*reinterpret_cast<int*>(SoundBuffer + 0x4EC) = 0;
				object->DispCharaParts(1);

				int pdtNo = -1;
				if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
					pdtNo = *reinterpret_cast<int*>(reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
				}
				prgObj->putParticle((pdtNo << 8) | 0x2D, 0, object, FLOAT_80331d18, 0x101E4);

				if (*reinterpret_cast<int*>(self + 0x6B4) == 0) {
					CFlatBossState() = CFlatBossState() - 1;
				}
				*reinterpret_cast<int*>(self + 0x6B4) = 1;
				*reinterpret_cast<int*>(self + 0x6C8) = 0;
			}
		}
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130ce4
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncTetsukyojin(int)
{
	const int branch = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D0);
	int positive;
	if (branch >= 1) {
		positive = 1;
	} else {
		positive = 0;
	}
	return positive;
}

/*
 * --INFO--
 * PAL Address: 0x80130c88
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncGigasLoad()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	switch (*reinterpret_cast<int*>(mon + 0x6D0)) {
	case 0:
		reinterpret_cast<CGPrgObj*>(this)->changeStat(4, 0, 0);
		*reinterpret_cast<int*>(mon + 0x6D0) = 1;
		CFlatBossState() = 1;
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130c40
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::tgtFuncGigasLoad(int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	aiTargetAttackRomMon(0x3B);
	if (*reinterpret_cast<int*>(mon + 0x6C4) < 0) {
		aiTarget();
	}
	return *reinterpret_cast<int*>(mon + 0x6C4);
}

/*
 * --INFO--
 * PAL Address: 0x80130bf4
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncGigasLoad(int)
{
	CGame* game = &Game;
	if (((game->m_scriptWork[0][0][1] != 0) &&
	     (1 < *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(game->m_scriptWork[0][0][1] + 0x58) + 0x1C))) &&
	    (CFlatBossState() == 1)) {
		return 0;
	}
	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80130ac8
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncWifeLamia()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	u8* mon = reinterpret_cast<u8*>(this);

	if (prgObj->m_lastStateId == 100) {
		if (prgObj->m_subState == 0) {
			if (prgObj->m_subFrame == 0) {
				memset(mon + 0x70C, 0, 0x34);
				*reinterpret_cast<u32*>(mon + 0x70C) = 0x10022;

				CVector attackOffset(FLOAT_80331d6c, FLOAT_80331d70, FLOAT_80331d74);
				*reinterpret_cast<float*>(mon + 0x718) = attackOffset.x;
				*reinterpret_cast<float*>(mon + 0x71C) = attackOffset.y;
				*reinterpret_cast<float*>(mon + 0x720) = attackOffset.z;
				*reinterpret_cast<float*>(mon + 0x724) = FLOAT_80331d78;
				*reinterpret_cast<float*>(mon + 0x728) = reinterpret_cast<CGObject*>(this)->m_bodyEllipsoidRadius;
			}
			moveFrame();
			if ((*reinterpret_cast<u32*>(mon + 0x710) & 1) != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(0x1A, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 2 && prgObj->m_subFrame == 0) {
			prgObj->reqAnim(0x1B, 1, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130a64
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncWifeLamia()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	if (script[14] <= 1) {
		reinterpret_cast<CGCharaObj*>(this)->ClearAllSta();
		object->m_bgColMask &= 0xFFF7FFFF;
		reinterpret_cast<CGPrgObj*>(this)->changeStat(100, 0, 0);
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D0) = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130a1c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncMolbol(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-13);
		break;
	case 101:
		setActionParam(-14);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801309e8
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncMolbol()
{
	switch (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
	case 100:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130898
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMolbol()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	u8* self = reinterpret_cast<u8*>(this);
	int state = prgObj->m_lastStateId;

	if (state != 0x65) {
		if (state < 0x65) {
			if (state > 99) {
				suikomi(0x53, FLOAT_80331cf8);
			}
		}
		return;
	}

	if (prgObj->m_stateFrame == 0 || prgObj->m_stateFrame == 5 || prgObj->m_stateFrame == 10) {
		CVector pos(Game.m_partyObjArr[*reinterpret_cast<int*>(self + 0x6C4)]->m_worldPosition);
		pos.x += Math.RandFPM(static_cast<float>((prgObj->m_stateFrame == 0) ? 0 : 40));
		pos.z += Math.RandFPM(static_cast<float>((prgObj->m_stateFrame == 0) ? 0 : 40));
		charaObj->putParticleFromItem(charaObj->m_itemId, 3, charaObj->m_particleSlots[0], reinterpret_cast<Vec*>(&pos));
	}
	charaObj->statAttack();
}

/*
 * --INFO--
 * PAL Address: 0x801307d4
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncMeteoParasiteC()
{
	initFinishedFuncDefault();
	*reinterpret_cast<CGMonObj**>(m_boss__8CGMonObj + 0x74) = this;

	if (strcmp(Game.m_currentScriptName, s_meteo_3_80331D64) == 0) {
		MeteoParasiteCBossWork* work = reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj);
		CGObject* object = reinterpret_cast<CGObject*>(this);
		work->bits.m_meteo3 = 1;
		work->m_index = 3;
		*reinterpret_cast<u16*>(reinterpret_cast<u8*>(object->m_scriptHandle) + 0x1C) = 1;
		object->SetAnimSlot(0x35, 0);
		reinterpret_cast<CGPrgObj*>(this)->reqAnim(0x35, 1, 0);
		object->PlayAnim(0x35, 1, 0, -1, -1, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801306b8
 * PAL Size: 284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncMeteoParasiteC()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
	int& timer = *reinterpret_cast<int*>(SoundBuffer + 1364);
	if (script == 0) {
		return;
	}

	if (script[7] < ((script[0x1A / 2] * 2) / 3)) {
		timer = 0;
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0x66, 0, 0);
		object->m_bgColMask &= 0xFFF7FFFF;
	} else if (timer > 0x31) {
		timer = 0;
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0x67, 0, 0);
		object->m_bgColMask &= 0xFFF7FFFF;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801302c8
 * PAL Size: 1008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMeteoParasiteC()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	u8* mon = reinterpret_cast<u8*>(this);

	int state = prgObj->m_lastStateId;
	if (state == 0x67) {
		int subState = prgObj->m_subState;
		if (subState == 0) {
			if (prgObj->m_subFrame == 0) {
				reinterpret_cast<CGCharaObj*>(this)->damageDelete();
				prgObj->reqAnim(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex * 3 + 0x1C, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				prgObj->changeSubStat(1);
			}
		} else if (subState == 1) {
			if (prgObj->m_subFrame == 0) {
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags =
				    (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags & 0x7F) | 0x80;
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreMode = 1;
				prgObj->reqAnim(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex * 3 + 0x1D, 1, 0);
			} else if (((reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags & 0x80) == 0)) {
				prgObj->changeSubStat(2);
			}
		} else if (subState == 2) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex * 3 + 0x1E, 0, 0);
				prgObj->playSe3D(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex * 2 + 0x11D34, 0x32, 0x96, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				reinterpret_cast<CGObject*>(this)->SetAnimSlot(0, 0);
				prgObj->changeStat(0, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 0;
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreWait = 0x177;
				*reinterpret_cast<int*>(mon + 0x6C8) = 0;
			}
		}
	} else if (state < 0x67) {
		if (state == 0x65) {
			if (prgObj->m_subState == 0) {
				if (prgObj->m_subFrame == 0) {
					reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags =
					    (reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags & 0x7F) | 0x80;
					reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreMode = 0;
				} else if (((reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreFlags & 0x80) == 0)) {
					prgObj->addSubStat();
				}
			} else if (prgObj->m_subState == 1) {
				if (prgObj->m_subFrame == 0) {
					prgObj->reqAnim(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex + 0x16, 0, 0);
					prgObj->playSe3D(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex * 2 + 0x11D35, 0x32, 0x96, 0, 0);
				} else if (prgObj->isLoopAnim() != 0) {
					reinterpret_cast<CGObject*>(this)->SetAnimSlot(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex + 0x19, 0);
					prgObj->changeStat(0, 0, 0);
					*reinterpret_cast<int*>(mon + 0x6B4) = 1;
					reinterpret_cast<CGObject*>(this)->m_bgColMask |= 0x80000;
				}
			}
		} else if (state > 100) {
			if (prgObj->m_stateFrame == 0) {
				reinterpret_cast<CGCharaObj*>(this)->damageDelete();
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)
				    ->m_objs[reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex]
				    ->changeStat(0x65, 0, 0);
				prgObj->reqAnim(reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex + 0x25, 0, 0);
				CFlatGameFlags() = static_cast<u8>((CFlatGameFlags() & ~CFlatGameFlag_Bit5) | CFlatGameFlag_Bit5);
				CFlatBossState() = CFlatBossState() + 1;
			} else if (prgObj->isLoopAnim() != 0) {
				reinterpret_cast<CGObject*>(this)->SetAnimSlot(0, 0);
				prgObj->changeStat(0, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 0;
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreWait = 0x177;
				reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex =
				    reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex + 1;
				if (2 < reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex) {
					reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj)->m_coreIndex = 0;
				}
				*reinterpret_cast<int*>(mon + 0x6C8) = 0;
			}
		}
	} else if (state < 0x69 && prgObj->m_stateFrame == 0) {
		prgObj->reqAnim(0x35, 1, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801302b8
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncMeteoParasiteC(int)
{
	return *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x78);
}

/*
 * --INFO--
 * PAL Address: 0x80130224
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncMeteoParasiteC()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int nextState = -1;
	MeteoParasiteCBossWork* work = reinterpret_cast<MeteoParasiteCBossWork*>(m_boss__8CGMonObj);
	if (work->bits.m_meteo3 != 0) {
		nextState = 0x68;
	} else {
		work->m_wait = (work->m_wait - 1) & ~((work->m_wait - 1) >> 31);
		if (*reinterpret_cast<int*>(mon + 0x6D0) == 0) {
			if (work->m_wait != 0) {
				return;
			}
			nextState = 0x65;
		}
	}
	if (nextState != -1) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(nextState, 0, 0);
	} else {
		logicFuncDefault();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80130208
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::attackCheckFuncMeteoParasiteC(int)
{
	const int branch = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D0);
	return (((branch - 1) | (1 - branch)) >> 31) - 1;
}

/*
 * --INFO--
 * PAL Address: 0x8013004c
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncMeteoParasite()
{
	initFinishedFuncDefault();

	const int scriptKind = reinterpret_cast<int>(reinterpret_cast<CGObject*>(this)->m_scriptHandle[4]);
	if (scriptKind == 0x85) {
		CGObject* object = reinterpret_cast<CGObject*>(this);
		CChara::CModel* model = object->m_charaModelHandle->m_model;
		CChara::CNode** nodes = reinterpret_cast<CChara::CNode**>(m_boss__8CGMonObj);
		int nodeIndex = model->SearchNode(const_cast<char*>(s_to_a_obj_801dd4e8));
		nodes[0] = model->m_nodes + nodeIndex;
		nodes[0]->m_flags &= 0x7F;

		nodeIndex = model->SearchNode(const_cast<char*>(s_to_b_obj_801dd4f4));
		nodes[1] = model->m_nodes + nodeIndex;
		nodes[1]->m_flags &= 0x7F;

		char nodeName[256];
		for (int i = 0; i < 12; i++) {
			sprintf(nodeName, s_to_02d_obj_801dd500, i + 1);
			nodeIndex = model->SearchNode(nodeName);
			nodes[i + 2] = model->m_nodes + nodeIndex;
			if ((m_boss__8CGMonObj[0x5C] & 0x40) != 0) {
				int dispIndex = model->GetDispIndex(nodes[i + 2]);
				model->m_meshVisibleMask &= ~(1 << dispIndex);
			}
		}
	}

	CGMonObj** bossObjArr = reinterpret_cast<CGMonObj**>(m_boss__8CGMonObj + 0x48);
	bossObjArr[scriptKind - 0x85] = this;

	if ((m_boss__8CGMonObj[0x5C] & 0x40) != 0) {
		reinterpret_cast<CGObject*>(this)->SetAnimSlot(scriptKind == 0x87 ? 0x0D : 0x0E, 0);
		reinterpret_cast<CGPrgObj*>(this)->reqAnim(0, 1, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012ffe4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncMeteoParasite(int stat)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	int scriptKind = reinterpret_cast<int>(object->m_scriptHandle[4]);
	if (scriptKind == 0x87) {
		if (stat == 0x67) {
			CGMonObj* meteoC = *reinterpret_cast<CGMonObj**>(m_boss__8CGMonObj + 0x74);
			if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(meteoC) + 0x6D0) == 1) {
				setActionParam(-13);
			} else {
				setActionParam(-14);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012fcc8
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::alwaysFuncMeteoParasite()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	CGCharaObj* chara = reinterpret_cast<CGCharaObj*>(this);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	u8* mon = reinterpret_cast<u8*>(this);
	const int scriptKind = reinterpret_cast<int>(object->m_scriptHandle[4]);

	if (scriptKind == 0x85 && ((m_boss__8CGMonObj[0x7C] & 0x40) == 0)) {
		if (g_errCt == 0) {
			g_errCt = 1;
			MG_GBA_THREAD_MSG_SETPORT_ct = FLOAT_80331cf8;
		}

		PSMTXRotRad(reinterpret_cast<CChara::CNode**>(m_boss__8CGMonObj)[0]->m_localRuntimeMtx, 'x',
		            MG_GBA_THREAD_MSG_SETPORT_ct);
		PSMTXRotRad(reinterpret_cast<CChara::CNode**>(m_boss__8CGMonObj)[1]->m_localRuntimeMtx, 'x',
		            -MG_GBA_THREAD_MSG_SETPORT_ct);

		float rotBase = FLOAT_80331d58;
		float rotStep = FLOAT_80331d2c;
		float rotDivisor = FLOAT_80331d5c;
		CGObject** rotObjects = reinterpret_cast<CGObject**>(m_boss__8CGMonObj + 0x38);
		for (int i = 0; i < 12; i++) {
			rotObjects[i]->m_rotTargetY =
			    (rotBase * rotStep * static_cast<float>(i + 3)) / rotDivisor + MG_GBA_THREAD_MSG_SETPORT_ct;
		}

		MG_GBA_THREAD_MSG_SETPORT_ct += FLOAT_80331d60;
	}

	if (scriptKind < 0x88 && scriptKind > 0x84 &&
	    *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x78) == scriptKind - 0x85 && (m_boss__8CGMonObj[0x7C] & 0x80) != 0) {
		int effect;
		int arg0;
		int arg1;
		if (chara->getItemPdt(0, 0, effect, arg0, arg1) != 0) {
			if (*reinterpret_cast<int*>(m_boss__8CGMonObj + 0x80) == 0) {
				prgObj->changeStat(100, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6D0) = 0;
			}
			if (*reinterpret_cast<int*>(m_boss__8CGMonObj + 0x80) == 2) {
				prgObj->changeStat(0x65, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6D0) = 2;
			}
			if (*reinterpret_cast<int*>(m_boss__8CGMonObj + 0x80) == 1) {
				prgObj->changeStat(0x66, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6D0) = 1;
			}
			m_boss__8CGMonObj[0x7C] &= 0x7F;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012fad0
 * PAL Size: 504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncMeteoParasite()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	CGCharaObj* chara = reinterpret_cast<CGCharaObj*>(this);
	int state = prgObj->m_lastStateId;
	void* scriptKind = object->m_scriptHandle[4];

	if (state == 0x66) {
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(0xC, 0, 0);
		} else if (prgObj->isLoopAnim() != 0) {
			object->SetAnimSlot(0, 0);
			prgObj->changeStat(0, 0, 0);
		}
	} else if (state < 0x66) {
		if (state == 100) {
			if (prgObj->m_stateFrame == 0) {
				prgObj->reqAnim(10, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				object->SetAnimSlot(0xB, 0);
				prgObj->changeStat(0, 0, 0);
			}
		} else if (state > 99) {
			if (prgObj->m_stateFrame == 0) {
				prgObj->reqAnim(0xD, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				object->SetAnimSlot(0xE, 0);
				prgObj->changeStat(0, 0, 0);
			}
		}
	}

	if (scriptKind == reinterpret_cast<void*>(0x87) && prgObj->m_lastStateId == 0x67) {
		int frame = prgObj->m_stateFrame;
		if (frame > 0x18 && frame < 0x32) {
			if (frame == 0x19) {
				prgObj->playSe3D(0x11D5B, 0x32, 0x96, 0, 0);
			}
			if (prgObj->m_stateFrame == (prgObj->m_stateFrame / 3) * 3) {
				chara->putParticleFromItem(chara->m_itemId, 2, chara->m_particleSlots[0], 0);
			}
		}
		chara->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012fa20
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncMeteoParasite()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	u8* mon = reinterpret_cast<u8*>(this);
	u8 flags = m_boss__8CGMonObj[0x5C];
	int nextState = -1;

	if ((flags & 0x40) != 0) {
		nextState = 0x68;
	} else if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x87) &&
	           *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x58) == 2 &&
	           *reinterpret_cast<int*>(mon + 0x6B4) < 2) {
		CGPrgObj* bossObj = *reinterpret_cast<CGPrgObj**>(m_boss__8CGMonObj + 0x54);
		if (bossObj->m_lastStateId > 99) {
			return;
		}
		if ((flags & 0x80) != 0) {
			return;
		}
	}

	if (nextState == -1) {
		logicFuncDefault();
	} else {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(nextState, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f984
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::attackCheckFuncMeteoParasite(int)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int scriptState = reinterpret_cast<int>(object->m_scriptHandle[4]);

	switch (scriptState) {
	case 0x85:
		return -2;
	case 0x86:
		if (*reinterpret_cast<int*>(m_boss__8CGMonObj + 0x78) == 1 && *reinterpret_cast<int*>(mon + 0x6D0) == 1) {
			return -1;
		}
		return -2;
	case 0x87:
		if (*reinterpret_cast<int*>(m_boss__8CGMonObj + 0x78) == 2 && *reinterpret_cast<int*>(mon + 0x6D0) < 2) {
			return -1;
		}
		return -2;
	default:
		return -1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f8bc
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::aiAddDuct(int& seq)
{
	if (Math.Rand(300) == 0) {
		aiTarget();
		aiSeq(-14, seq, 0, 1, 100, -1);
		aiSeq(-13, seq, 1, 0, 100, -1);
		const int seOffset = Math.Rand(3);
		reinterpret_cast<CGPrgObj*>(this)->playSe3D(seOffset + 0x11D40, 0x32, 0x96, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f870
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncDuct()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	initFinishedFuncDefault();
	const int slot = static_cast<int>(reinterpret_cast<long>(object->m_scriptHandle[4])) - 0x8E;
	reinterpret_cast<CGMonObj**>(m_boss__8CGMonObj + 0x38)[slot] = this;
}

/*
 * --INFO--
 * PAL Address: 0x8012f7ac
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncDuct()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	int pdtNo = -1;
	CRef* pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
	void* scriptKind = object->m_scriptHandle[4];
	int slot = reinterpret_cast<int>(scriptKind) - 0x8E;
	if (pdtLoadRef != 0) {
		pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(pdtLoadRef) + 0x14);
	}
	reinterpret_cast<CGPrgObj*>(this)->putParticle((pdtNo << 8) | 2, 0, object, FLOAT_80331d18, 0);

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + 0x1C) == 0) {
		CGObject* bossObj = *reinterpret_cast<CGObject**>(m_boss__8CGMonObj + 0x68);
		CChara::CModel* model = bossObj->m_charaModelHandle->m_model;
		CChara::CNode** nodes = reinterpret_cast<CChara::CNode**>(m_boss__8CGMonObj + 0x8);
		int dispIndex = model->GetDispIndex(nodes[slot]);
		model->m_meshVisibleMask &= ~(1 << dispIndex);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f678
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncRamoe()
{
	int activeCount = 0;
	int nextState = -1;

	unsigned int* scriptWork = &Game.m_scriptWork[0][0][1];
	for (int i = 0; i < 0x3F; i++, scriptWork++) {
		CGPrgObj* monObj = reinterpret_cast<CGPrgObj*>(*scriptWork);
		if (monObj != 0 && (monObj->m_lastStateId != 9 || monObj->m_subState != 2)) {
			activeCount++;
		}
	}

	if (activeCount == 0 && Math.Rand(3) == 0) {
		nextState = 100;
	}

	if (nextState == -1) {
		logicFuncDefault();
	} else {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(nextState, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f648
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncRamoe(int stat)
{
	switch (stat) {
	case 100:
		setActionParam(-9);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f644
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncRamoe()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8012f598
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncRamoe()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId == 100) {
		if (prgObj->m_stateFrame == 0x3A) {
			unsigned int* scriptWork = &Game.m_scriptWork[0][0][1];
			for (int i = 1; i < 0x40; i++, scriptWork++) {
				CGMonObj* monObj = reinterpret_cast<CGMonObj*>(*scriptWork);
				CGPrgObj* monPrg = reinterpret_cast<CGPrgObj*>(monObj);
				if (monObj != 0 && monPrg->m_lastStateId == 9 && monPrg->m_subState == 2) {
					monObj->setRepop(0);
				}
			}
		}
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f534
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncLastBoss()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	initFinishedFuncDefault();
	*reinterpret_cast<CGMonObj**>(SoundBuffer + 1260) = this;
	if (object->m_charaModelHandle != 0) {
		*reinterpret_cast<void**>(SoundBuffer + 1264) = object->m_charaModelHandle->m_model;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f4b0
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::damagedFuncLastBoss()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int& timer = *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x24);
	if (timer >= 100 && *reinterpret_cast<int*>(mon + 0x6D0) == 0) {
		*reinterpret_cast<int*>(mon + 0x6D0) = 1;
		*reinterpret_cast<int*>(mon + 0x6C8) = 0;
		prgObj->changeStat(100, 0, 0);
		object->m_bgColMask &= 0xFFF7FFFF;
		timer = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f480
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncLastBoss(int stat)
{
	switch (stat) {
	case 0x66:
		setActionParam(-7);
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012f3e8
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncLastBoss()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	switch (prgObj->m_lastStateId) {
	case 0x66: {
		CGPartyObj** work = reinterpret_cast<CGPartyObj**>(m_boss__8CGMonObj);
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = work[i + 2];
			if (party != 0) {
				CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
				if (partyPrg->m_lastStateId == 0x25) {
					partyPrg->changeStat(0x24, 0, 0);
				}
			}
		}
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		break;
	}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012efa8
 * PAL Size: 1088b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLastBoss()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	const int state = prgObj->m_lastStateId;
	const int stateFrame = prgObj->m_stateFrame;

	if (state == 0x65) {
		if (stateFrame == 0) {
			object->m_bgColMask &= 0xFFF7FFFF;
			prgObj->reqAnim(0x19, 0, 0);

			int pdtNo = -1;
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}

			prgObj->putParticle((pdtNo << 8) | 0x11, 0, object, 1.0f, 0);
			prgObj->putParticle((pdtNo << 8) | 0x12, 0, object, 1.0f, 0);
			prgObj->playSe3D(0x12913, 0x32, 0x96, 0, 0);
		} else if (stateFrame == 0x29) {
			object->m_bodyEllipsoidRadius = FLOAT_80331d20;
		} else if (prgObj->isLoopAnim() != 0) {
			object->m_bgColMask |= 0x80000;
			prgObj->changeStat(0, 0, 0);
			object->SetAnimSlot(0x13, 0);
			object->SetAnimSlot(0x15, 1);
			object->SetAnimSlot(0x17, 4);
			mon[0x6B4] = 0;
		}
	} else if (state < 0x65) {
		if (99 < state) {
			if (stateFrame == 0) {
				reinterpret_cast<CGCharaObj*>(this)->damageDelete();
				object->m_bgColMask &= 0xFFF7FFFF;
				prgObj->reqAnim(0x18, 0, 0);

				int pdtNo = -1;
				if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
					pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
				}

				prgObj->putParticle((pdtNo << 8) | 0x10, 0, object, 1.0f, 0);
				prgObj->playSe3D(0x12912, 0x32, 0x96, 0, 0);
			} else if (stateFrame == 0x7D) {
				object->m_bodyEllipsoidRadius = FLOAT_80331d1c;
			} else if (prgObj->isLoopAnim() != 0) {
				object->m_bgColMask |= 0x80000;
				object->SetAnimSlot(0x12, 0);
				object->SetAnimSlot(0x14, 1);
				object->SetAnimSlot(0x16, 4);
				prgObj->changeStat(0, 0, 0);
				mon[0x6B4] = 2;
			}
		}
	} else if (state < 0x67) {
		if (stateFrame == 0) {
			int pdtNo = -1;
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}
			prgObj->putParticle((pdtNo << 8) | 5, *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0x12902);
		} else if (stateFrame == 0x4B) {
			CGPartyObj** work = reinterpret_cast<CGPartyObj**>(m_boss__8CGMonObj);
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = work[i + 2];
				if (party != 0) {
					CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
					if (partyPrg->m_lastStateId == 0x24) {
						if (fabs(prgObj->getTargetRot(partyPrg)) < 0.5235987755982988) {
							partyPrg->changeStat(0x25, 0, 0);
						}
					}
				}
			}
		} else if (stateFrame == 200) {
			CGPartyObj** work = reinterpret_cast<CGPartyObj**>(m_boss__8CGMonObj);
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = work[i + 2];
				if (party != 0) {
					CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
					if (partyPrg->m_lastStateId == 0x25) {
						partyPrg->changeStat(0x24, 0, 0);
					}
				}
			}
			reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
		}

		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012ef94
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncLastBoss(int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	return (*reinterpret_cast<int*>(mon + 0x6D0) != 0) ? 1 : 0;
}

/*
 * --INFO--
 * PAL Address: 0x8012ef0c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncLastBoss()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int nextState = -1;

	if (*reinterpret_cast<int*>(mon + 0x6D0) == 2) {
		int& timer = *reinterpret_cast<int*>(m_boss__8CGMonObj + 0x24);
		timer += 1;
		if (timer >= 10) {
			*reinterpret_cast<int*>(mon + 0x6D0) = 3;
			nextState = 0x65;
			*reinterpret_cast<int*>(mon + 0x6C8) = 0;
			object->m_bgColMask &= 0xFFF7FFFF;
			timer = 0;
		}
	}

	if (nextState != -1) {
		prgObj->changeStat(nextState, 0, 0);
	} else {
		logicFuncDefault();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012e9bc
 * PAL Size: 1360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::teleport(
	int mode, int animId, int startFrame, int blendEndFrame, int seStart, int seEnd, int particleStart, int particleBlend, int particleEnd,
	Vec* teleportPoints, int& teleportIndex, Vec& startPos
)
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	const int blendStartFrame = startFrame + 8;
	const int blendEndPlusFrame = blendEndFrame + 8;
	const int blendFrameCount = blendEndFrame - blendStartFrame;

	if (prgObj->m_stateFrame == 0) {
		int pdtNo;
		object->m_bgColMask &= 0xFFF3FFFC;
		*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) &= 0xEF;
		object->m_groundHitOffset.z = FLOAT_80331cf8;
		object->m_groundHitOffset.y = FLOAT_80331cf8;
		object->m_groundHitOffset.x = FLOAT_80331cf8;

		prgObj->reqAnim(animId, 0, 0);
		prgObj->playSe3D(seStart, 0x32, 0x1C2, 0, 0);

		if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		} else {
			pdtNo = -1;
		}
		prgObj->putParticle(particleStart | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, FLOAT_80331d18, 0);

		if (mode == 0) {
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			} else {
				pdtNo = -1;
			}
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, FLOAT_80331d18, 0);
		} else {
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			} else {
				pdtNo = -1;
			}
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, FLOAT_80331d18, 0);
		}
	}

	const int stateFrame = prgObj->m_stateFrame;

	if (stateFrame <= blendStartFrame) {
		if (startFrame <= stateFrame) {
			const float angle = FLOAT_80331d24 * static_cast<float>(stateFrame - startFrame) * FLOAT_80331d28;
			const float wave = static_cast<float>(cos(angle));
			object->m_rotationZ = wave;
			object->m_rotationX = wave;
			object->m_rotationY = FLOAT_80331d18 + static_cast<float>(sin(angle));
		}
	} else {
		if (stateFrame <= blendEndFrame) {
			if (stateFrame == blendStartFrame + 1) {
				int nextIndex;
				do {
					nextIndex = Math.Rand(4);
				} while (nextIndex == teleportIndex);

				teleportIndex = nextIndex;
				startPos = object->m_worldPosition;

				if (mode == 1) {
					object->m_displayFlags &= 0xFFFFFFFE;
				}
			}

			const float ratio = static_cast<float>(stateFrame - blendStartFrame) / static_cast<float>(blendFrameCount);
			const float blend = FLOAT_80331d30 * (FLOAT_80331d18 + static_cast<float>(cos(FLOAT_80331d2c * ratio)));
			CVector point(teleportPoints[teleportIndex]);
			CVector scaledPoint;
			PSVECScale(reinterpret_cast<Vec*>(&point), reinterpret_cast<Vec*>(&scaledPoint), FLOAT_80331d18 - blend);

			CVector scaledPointCopy(scaledPoint);
			CVector current(object->m_worldPosition);
			CVector scaledCurrent;
			PSVECScale(reinterpret_cast<Vec*>(&current), reinterpret_cast<Vec*>(&scaledCurrent), blend);

			CVector scaledCurrentCopy(scaledCurrent);
			CVector blended;
			PSVECAdd(reinterpret_cast<Vec*>(&scaledCurrentCopy), reinterpret_cast<Vec*>(&scaledPointCopy), reinterpret_cast<Vec*>(&blended));
			object->m_worldPosition.x = blended.x;
			object->m_worldPosition.y = blended.y;
			object->m_worldPosition.z = blended.z;

			if (mode == 1 && stateFrame == blendEndFrame - 0x2A) {
				int pdtNo;
				if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
					pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
				} else {
					pdtNo = -1;
				}
				prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &teleportPoints[teleportIndex], FLOAT_80331d18, 0);
				prgObj->playSe3D(seEnd, 0x32, 0x1C2, 0, 0);
			}
		} else if (stateFrame <= blendEndPlusFrame) {
			if (stateFrame == blendEndFrame + 1) {
				if (mode == 0) {
					int pdtNo;
					if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
						pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
					} else {
						pdtNo = -1;
					}
					prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, FLOAT_80331d18, 0);
					prgObj->playSe3D(seEnd, 0x32, 0x1C2, 0, 0);
				}

				object->m_bgColMask |= 3;
				*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) =
					(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) & 0xEF) | 0x10;
				object->m_groundHitOffset.z = FLOAT_80331cf8;
				object->m_groundHitOffset.y = FLOAT_80331cf8;
				object->m_groundHitOffset.x = FLOAT_80331cf8;

				if (mode == 1) {
					object->m_displayFlags |= 1;
				}
			}

			const float angle = FLOAT_80331d24 * (FLOAT_80331d18 - static_cast<float>(stateFrame - blendEndFrame) * FLOAT_80331d28);
			const float wave = static_cast<float>(cos(angle));
			object->m_rotationZ = wave;
			object->m_rotationX = wave;
			object->m_rotationY = FLOAT_80331d18 + static_cast<float>(sin(angle));

			if (stateFrame == blendEndPlusFrame) {
				object->m_bgColMask |= 0xC0000;
				setAttackAfter(*reinterpret_cast<int*>(mon + 0x560));
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::suikomiSub(CGObject*, float)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned char* target = reinterpret_cast<unsigned char*>(Game.unk_flat3_0xc7d0);
	if (target == 0) {
		return;
	}

	float dx = *(float*)(self + 0x15c) - *(float*)(target + 0x15c);
	float dz = *(float*)(self + 0x164) - *(float*)(target + 0x164);
	float distSq = dx * dx + dz * dz;
	double dist = (double)distSq;

	if (dist <= (double)FLOAT_80331cf8) {
		if (DOUBLE_80331d10 <= dist) {
			unsigned int exp = (unsigned int)distSq & 0x7f800000;
			int fpClass;
			if (exp == 0x7f800000) {
				fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 2 : 1;
			} else if ((exp < 0x7f800000) && (exp == 0)) {
				fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 3 : 5;
			} else {
				fpClass = 4;
			}
			if (fpClass == 1) {
				dist = NAN;
			}
		} else {
			dist = NAN;
		}
	} else {
		double inv = (double)FLOAT_80331d18 / sqrt(dist);
		inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
		inv = DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08);
		dist = (double)(float)(dist * DOUBLE_80331d00 * inv * -(dist * inv * inv - DOUBLE_80331d08));
	}

	if ((double)FLOAT_80331cf8 < dist) {
		float accel = (float)((double)FLOAT_80331d18 / dist) * FLOAT_80331d1c *
		              (float)(dist / (double)FLOAT_80331d20);
		*(float*)(target + 0x104) += dx * accel;
		*(float*)(target + 0x10c) += dz * accel;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012e5dc
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::suikomi(int endFrame, float zOffset)
{
	CGCharaObj* chara = reinterpret_cast<CGCharaObj*>(this);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	if (prgObj->m_stateFrame == 0) {
		prgObj->playSe3D(0xdec0, 0x32, 0x1c2, 0, 0);
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.m_partyObjArr[i];
			if (party != 0) {
				gCFlatRuntime2.ResetParticleWork(0x26, *(int*)(self + 0x58c));
				gCFlatRuntime2.SetParticleWorkTrace(this);
				gCFlatRuntime2.SetParticleWorkBind(party);
				gCFlatRuntime2.PutParticleWork();
			}
		}
	}

	if (prgObj->m_stateFrame <= endFrame) {
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.m_partyObjArr[i];
			if (party != 0) {
				float dx = *(float*)(self + 0x15c) - *(float*)((unsigned char*)party + 0x15c);
				float dz =
				    zOffset + (*(float*)(self + 0x164) - *(float*)((unsigned char*)party + 0x164));
				float distSq = dx * dx + dz * dz;
				double dist = (double)distSq;

				if (distSq <= FLOAT_80331cf8) {
					if (DOUBLE_80331d10 <= dist) {
						unsigned int exp = (unsigned int)distSq & 0x7f800000;
						int fpClass;
						if (exp == 0x7f800000) {
							fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 2 : 1;
						} else if ((exp < 0x7f800000) && (exp == 0)) {
							fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 3 : 5;
						} else {
							fpClass = 4;
						}
						if (fpClass == 1) {
							dist = NAN;
						}
					} else {
						dist = NAN;
					}
				} else {
					dist = sqrtf(distSq);
				}

				if ((double)FLOAT_80331cf8 < dist) {
					float accel = (float)((double)FLOAT_80331d18 / dist) * FLOAT_80331d1c *
					              (float)(dist / (double)FLOAT_80331d20);
					*(float*)((unsigned char*)party + 0x104) += dx * accel;
					*(float*)((unsigned char*)party + 0x10c) += dz * accel;
				}
			}
		}

		if ((Game.unk_flat3_0xc7d0 != 0) && (*(int*)(Game.unk_flat3_0xc7d0 + 0x550) == 0)) {
			unsigned int target = Game.unk_flat3_0xc7d0;
			float dx = *(float*)(self + 0x15c) - *(float*)(target + 0x15c);
			float dz = zOffset + (*(float*)(self + 0x164) - *(float*)(target + 0x164));
			float distSq = dx * dx + dz * dz;
			double dist = (double)distSq;

			if (distSq <= FLOAT_80331cf8) {
				if (DOUBLE_80331d10 <= dist) {
					unsigned int exp = (unsigned int)distSq & 0x7f800000;
					int fpClass;
					if (exp == 0x7f800000) {
						fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 2 : 1;
					} else if ((exp < 0x7f800000) && (exp == 0)) {
						fpClass = (((unsigned int)distSq & 0x7fffff) == 0) ? 3 : 5;
					} else {
						fpClass = 4;
					}
					if (fpClass == 1) {
						dist = NAN;
					}
				} else {
					dist = NAN;
				}
			} else {
				dist = sqrtf(distSq);
			}

			if ((double)FLOAT_80331cf8 < dist) {
				float accel = (float)((double)FLOAT_80331d18 / dist) * FLOAT_80331d1c *
				              (float)(dist / (double)FLOAT_80331d20);
				*(float*)(target + 0x104) += dx * accel;
				*(float*)(target + 0x10c) += dz * accel;
			}
		}

		if (prgObj->m_stateFrame == endFrame) {
			chara->endPSlotBit(0x400);
		}
	}

	chara->statAttack();
}
