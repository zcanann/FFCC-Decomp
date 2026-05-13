#include "ffcc/monobj_boss.h"
#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/partyobj.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/game.h"
#include "ffcc/vector.h"

#include <math.h>
#include <string.h>

extern "C" int Rand__5CMathFUl(CMath*, unsigned long);
extern "C" float RandFPM__5CMathFf(float, CMath*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void setAttackAfter__8CGMonObjFi(CGMonObj*, int);
extern "C" void setActionParam__8CGMonObjFi(CGMonObj*, int);
extern "C" void setRepop__8CGMonObjFi(CGMonObj*, int);
extern "C" void logicFuncDefault__8CGMonObjFv(CGMonObj*);
extern "C" void initFinishedFuncDefault__8CGMonObjFv(CGMonObj*);
extern "C" int calcBranchFuncDefault__8CGMonObjFi(CGMonObj*, int);
extern "C" void aiTargetAttackRomMon__8CGMonObjFi(CGMonObj*, int);
extern "C" void aiTarget__8CGMonObjFv(CGMonObj*);
extern "C" void _aiSeq__8CGMonObjFiiiiii(CGMonObj*, int, int, int, int, int, int);
extern "C" void reqAnim__8CGPrgObjFiii(void*, int, int, int);
extern "C" void addSubStat__8CGPrgObjFv(void*);
extern "C" void putParticle__8CGPrgObjFiiP8CGObjectfi(void*, int, int, void*, float, int);
extern "C" void playSe3D__8CGPrgObjFiiiiP3Vec(void*, int, int, int, int, Vec*);
extern "C" int isLoopAnim__8CGPrgObjFv(void*);
extern "C" void changeStat__8CGPrgObjFiii(void*, int, int, int);
extern "C" void Move__8CGObjectFP3Vecfiiiii(void*, Vec*, float, int, int, int, int, int);
extern "C" void moveVectorHRot__8CGObjectFfffi(void*, float, float, float, int);
extern "C" void ResetParticleWork__13CFlatRuntime2Fii(void*, int, int);
extern "C" void SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void PutParticleWork__13CFlatRuntime2Fv(void*);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, void*, int, int, int, void*, void*);
extern "C" void moveFrame__8CGMonObjFv(CGMonObj*);
extern "C" void rotTarget__8CGMonObjFif(CGMonObj*, int, float);
extern "C" void CGMonObj_ResetActionState(CGMonObj*);
extern "C" CGMonObj* FindGMonObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGMonObj* FindGMonObjNext__13CFlatRuntime2FP8CGMonObj(void*, CGMonObj*);
extern "C" void teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec(CGMonObj*, int, int, int, int, int, int, int, int, int,
                                                           Vec*, int&, Vec&);
extern "C" int SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" int GetDispIndex__Q26CChara6CModelFPQ26CChara5CNode(CChara::CModel*, CChara::CNode*);
extern float FLOAT_80331dd0;
extern float FLOAT_80331cf8;
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
extern float FLOAT_80331d6c;
extern float FLOAT_80331d70;
extern float FLOAT_80331d74;
extern float FLOAT_80331d78;
extern float FLOAT_80331d84;
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
extern "C" unsigned char m_boss__8CGMonObj[];
extern "C" Vec DAT_802127c0;
extern "C" Vec DAT_802127f0[];

static const char s_to_a_obj_801dd4e8[] = "to_a_obj";
static const char s_to_b_obj_801dd4f4[] = "to_b_obj";
static const char s_to_02d_obj_801dd500[] = "to_%02d_obj";

typedef void (*MonObjSawCallback)(CGMonObj*, int, int, int);

struct MeteoParasiteCBossWork {
    u8 m_pad00[0x74];
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
		if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		}
		putParticle__8CGPrgObjFiiP8CGObjectfi(prgObj, (pdtNo << 8) | 0x0D, 0, object, FLOAT_80331d18, 0);
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x4E37, 0x32, 500, 0, 0);
	} else {
		if (branch != 0) {
			return;
		}
		if (((script[0x1A / 2] * 2) / 3) <= script[7]) {
			return;
		}
		object->DispCharaParts(3);
		int pdtNo = -1;
		if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
			pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
		}
		putParticle__8CGPrgObjFiiP8CGObjectfi(prgObj, (pdtNo << 8) | 0x0C, 0, object, FLOAT_80331d18, 0);
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x4E36, 0x32, 500, 0, 0);
	}

	changeStat__8CGPrgObjFiii(prgObj, 4, 0, 0);
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int nextState = -1;

	if (*reinterpret_cast<int*>(SoundBuffer + 1260) != 0) {
		*reinterpret_cast<int*>(SoundBuffer + 1260) = 0;
		const int branch = *reinterpret_cast<int*>(mon + 0x6B4);
		const unsigned int roll = Rand__5CMathFUl(&Math, 10);
		if ((branch == 0 && roll == 0) || (branch == 1 && roll < 2) || (branch == 2 && roll < 3)) {
			nextState = 100;
		}
	}

	if (nextState == -1) {
		logicFuncDefault__8CGMonObjFv(this);
	} else {
		changeStat__8CGPrgObjFiii(prgObj, nextState, 0, 0);
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
			reqAnim__8CGPrgObjFiii(self, 0xc, 0, 0);

			int pdtIndex = -1;
			u8* charaModelHandle = *(u8**)(self + 0xf8);
			if (charaModelHandle != 0) {
				u8* pdtLoadRef = *(u8**)(charaModelHandle + 0x178);
				if (pdtLoadRef != 0) {
					pdtIndex = *(int*)(pdtLoadRef + 0x14);
				}
			}
			putParticle__8CGPrgObjFiiP8CGObjectfi(self, (pdtIndex << 8) | 6, 0, self, FLOAT_80331d18, 0);
			putParticle__8CGPrgObjFiiP8CGObjectfi(self, (pdtIndex << 8) | 7, 0, self, FLOAT_80331d18, 0);
		}

		int frame = *(int*)(self + 0x528);
		if (frame > 0x20) {
			if (frame == 0x21) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e30, 0x32, 0x1c2, 0, 0);
			} else if (frame == 0x32) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e35, 0x32, 0x1c2, 0, 0);
			}

			*(u32*)(self + 0x1c0) &= 0xfff7fffd;
			float moveScale = PSVECDistance((Vec*)(SoundBuffer + 0x4f4), (Vec*)(self + 0x15c)) * FLOAT_80331dd4;
			Vec moveDir = { 0.0f, 0.0f, 0.0f };
			Move__8CGObjectFP3Vecfiiiii(self, &moveDir, moveScale, 0x10, 1, 0, 0, 0);

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

		if (isLoopAnim__8CGPrgObjFv(self) != 0) {
			changeStat__8CGPrgObjFiii(self, 0, 0, 0);
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

			reqAnim__8CGPrgObjFiii(self, animId, 0, 0);
			u16 scriptScale = *(u16*)(*(u8**)(self + 0x7c) + 0xd4);
			float moveMagnitude =
			    *(float*)(self + 0x690) *
			    (FLOAT_80331d60 * (float)((double)scriptScale - DOUBLE_80331dc0) + FLOAT_80331db8);
			moveVectorHRot__8CGObjectFfffi(self, *(float*)(self + 0x1b4) + turnOffset, FLOAT_80331cf8, moveMagnitude, 0x1e);

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
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x8cab, 0x32, 0x1c2, 0, 0);
			} else if (action < 99) {
				if (action == 0x5b) {
					playSe3D__8CGPrgObjFiiiiP3Vec(self, 0x4e2a, 0x32, 0x1c2, 0, 0);
				}
			} else if (action == 0x6b) {
				playSe3D__8CGPrgObjFiiiiP3Vec(self, 0xfdf3, 0x32, 0x1c2, 0, 0);
			}
		}

		if (*(int*)(self + 0x528) == 0x19) {
			changeStat__8CGPrgObjFiii(self, 0, 0, 0);
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
		setActionParam__8CGMonObjFi(this, -10);
		break;
	case 101:
		setActionParam__8CGMonObjFi(this, -9);
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
					playSe3D__8CGPrgObjFiiiiP3Vec(reinterpret_cast<CGPrgObj*>(this), 0xFA17, 0x32, 0x96, 0, 0);
				} else if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0x14) {
					reinterpret_cast<CGObject*>(this)->DispCharaParts(1);
					playSe3D__8CGPrgObjFiiiiP3Vec(reinterpret_cast<CGPrgObj*>(this), 0xFA18, 0x32, 0x96, 0, 0);
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
				playSe3D__8CGPrgObjFiiiiP3Vec(reinterpret_cast<CGPrgObj*>(this), 0xFA1A, 0x32, 0x96, 0, 0);
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
			changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 0, 0, 0);
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
		setAttackAfter__8CGMonObjFi(this, *reinterpret_cast<int*>(self + 0x560));
	} else {
		if (reinterpret_cast<CGPrgObj*>(this)->m_stateFrame == 0) {
			float turnOffset = FLOAT_80331cf8;
			if (state == 0x68) {
				turnOffset = FLOAT_80331d2c;
			}
			reqAnim__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 1, 1, 0);
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
		moveVectorHRot__8CGObjectFfffi(reinterpret_cast<CGObject*>(this), *reinterpret_cast<float*>(SoundBuffer + 0x4FC),
		                               FLOAT_80331cf8, moveSpeed, 1);
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
		setActionParam__8CGMonObjFi(this, -14);
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
		reinterpret_cast<CGCharaObj*>(this)->enableDamageCol(1);
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

		putParticle__8CGPrgObjFiiP8CGObjectfi(
			prgObj, (pdtNo << 8) | 0x18, *reinterpret_cast<int*>(self + 0x58C), object, FLOAT_80331d18, 0x8CC0);
		reqAnim__8CGPrgObjFiii(prgObj, 0xF, 0, 0);
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

		putParticle__8CGPrgObjFiiP8CGObjectfi(
			prgObj, (pdtNo << 8) | 0x19, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC1);
	} else if (branch == 300) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		putParticle__8CGPrgObjFiiP8CGObjectfi(
			prgObj, (pdtNo << 8) | 0x1A, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC2);
	} else if (branch == 0x1C2) {
		int pdtNo;
		u8* pdtRef = reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef);
		if (pdtRef != 0) {
			pdtNo = *reinterpret_cast<int*>(pdtRef + 0x14);
		} else {
			pdtNo = -1;
		}

		putParticle__8CGPrgObjFiiP8CGObjectfi(
			prgObj, (pdtNo << 8) | 0x1B, *reinterpret_cast<int*>(self + 0x590), object, FLOAT_80331d18, 0x8CC3);
	} else if (branch == 600) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0xC00);
		object->m_bgColMask &= 0xFFF7FFFF;
		changeStat__8CGPrgObjFiii(prgObj, -9, 0, 0);
		object->SetAnimSlot(0, 0);

		CGMonObj* monObj = FindGMonObjFirst__13CFlatRuntime2Fv(CFlat);
		while (monObj != 0) {
			if (monObj != this) {
				u8* monBytes = reinterpret_cast<u8*>(monObj);
				u16* script = *reinterpret_cast<u16**>(monBytes + 0x58);
				reinterpret_cast<CGCharaObj*>(monObj)->addHp(-script[0x1A / 2], 0);
			}
			monObj = FindGMonObjNext__13CFlatRuntime2FP8CGMonObj(CFlat, monObj);
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
		putParticle__8CGPrgObjFiiP8CGObjectfi(prgObj, (pdtNo << 8) | 0x1D, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x590), object, FLOAT_80331d18, 0);
	} else if (timer == 300 && Game.m_gameWork.m_gameOverFlag == 0) {
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x8CBF, 0x32, 0x96, 0, 0);
		active = 0;
		*reinterpret_cast<int*>(CFlat + 4840) = 1;
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
		branch = calcBranchFuncDefault__8CGMonObjFi(this, 1);
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
		teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec(
		    this, 0, 0xd, 8, 0x42, 0xa03e, 0xa03f, 3, 4, 5, &DAT_802127c0,
		    *reinterpret_cast<int*>(SoundBuffer_1260_), *reinterpret_cast<Vec*>(SoundBuffer_1260_ + 4));
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
	return *reinterpret_cast<int*>(CFlat + 4840);
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
				reqAnim__8CGPrgObjFiii(prgObj, 10, 0, 0);

				CRef* pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
				int pdtNo;
				if (pdtLoadRef == 0) {
					pdtNo = -1;
				} else {
					pdtNo = reinterpret_cast<int*>(pdtLoadRef)[5];
				}

				putParticle__8CGPrgObjFiiP8CGObjectfi(
				    prgObj, pdtNo << 8, *reinterpret_cast<int*>(mon + 0x564), object, FLOAT_80331d18, 0x1C52C);
				playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x1C52B, 0x32, 0x96, 0, 0);
				memset(mon + 0x70C, 0, 0x34);
				*reinterpret_cast<int*>(mon + 0x70C) = 0x1402;
			} else if (isLoopAnim__8CGPrgObjFv(prgObj) != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				*reinterpret_cast<int*>(mon + 0x560) = 0x495;
				reqAnim__8CGPrgObjFiii(prgObj, 1, 1, 0);
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
				reqAnim__8CGPrgObjFiii(prgObj, 0xB, 0, 0);
				reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
				playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x1C52D, 0x32, 0x96, 0, 0);
			} else if (isLoopAnim__8CGPrgObjFv(prgObj) != 0) {
				changeStat__8CGPrgObjFiii(prgObj, 0, 0, 0);
			}
		}

		moveFrame__8CGMonObjFv(this);
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
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int& bossState = *reinterpret_cast<int*>(CFlat + 4840);
	unsigned char& aiWork = mon[0x6D4];

	if (bossState == 0 && (aiWork & 0x80) != 0) {
		aiWork &= 0x7F;
	}

	if ((bossState == 0) || ((aiWork & 0x80) != 0)) {
		if (prgObj->m_lastStateId == 100 && prgObj->m_subState == 1) {
			prgObj->addSubStat();
		}
	} else if (prgObj->m_lastStateId != 100) {
		changeStat__8CGPrgObjFiii(prgObj, 100, 0, 0);
	}
	int& cooldown = *reinterpret_cast<int*>(SoundBuffer + 1268);
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
	#if 0
	// Function: frameStatFuncLKShooter__8CGMonObjFv
	// Entry: 8013197c
	// Size: 604 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncLKShooter__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  float fVar1;
	  int iVar2;
	  undefined4 *puVar3;
	  CVector CStack_28;
	  CVector aCStack_1c [2];
	  
	  SoundBuffer._1272_4_ = SoundBuffer._1272_4_ - 1 & ~((int)(SoundBuffer._1272_4_ - 1) >> 0x1f);
	  SoundBuffer._1276_4_ = SoundBuffer._1276_4_ - 1 & ~((int)(SoundBuffer._1276_4_ - 1) >> 0x1f);
	  iVar2 = *(int *)&gMonObj->field_0x520;
	  if (iVar2 == 0x65) {
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
	      rotTarget__8CGMonObjFif((double)FLOAT_80331da4,gMonObj,*(undefined4 *)&gMonObj->field_0x6c4);
	    }
	    if (((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0) ||
	       (*(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x620 * 4) < FLOAT_80331da8)) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	    }
	  }
	  else if ((iVar2 < 0x65) && (99 < iVar2)) {
	    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      memset(&gMonObj->field_0x70c,0,0x34);
	      *(undefined4 *)&gMonObj->field_0x70c = 0x322;
	      if (gMonObj->_bossBranchRelated == 1) {
	        puVar3 = (undefined4 *)
	                 __ct__7CVectorFfff(FLOAT_80331d9c,FLOAT_80331cf8,FLOAT_80331d9c,aCStack_1c);
	      }
	      else {
	        puVar3 = (undefined4 *)
	                 __ct__7CVectorFfff(FLOAT_80331d90,FLOAT_80331cf8,FLOAT_80331d94,&CStack_28);
	      }
	      fVar1 = FLOAT_80331da0;
	      *(undefined4 *)&gMonObj->field_0x718 = *puVar3;
	      *(undefined4 *)&gMonObj->field_0x71c = puVar3[1];
	      *(undefined4 *)&gMonObj->field_0x720 = puVar3[2];
	      *(float *)&gMonObj->field_0x728 = fVar1;
	      *(undefined4 *)&gMonObj->field_0x738 = 0x65;
	    }
	    moveFrame__8CGMonObjFv(gMonObj);
	    if ((((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0) ||
	        ((gMonObj->_bossBranchRelated == 1 && ((CFlat._4840_4_ & 1) != 0)))) ||
	       ((gMonObj->_bossBranchRelated == 2 && ((CFlat._4840_4_ & 2) != 0)))) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	    }
	  }
	  else {
	    if (gMonObj->_bossBranchRelated == 1) {
	      gMonObj->_bossBranchRelated = 0;
	      m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xdf;
	      SoundBuffer._1276_4_ = 0xfa;
	    }
	    if (gMonObj->_bossBranchRelated == 2) {
	      gMonObj->_bossBranchRelated = 0;
	      m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xbf;
	      SoundBuffer._1272_4_ = 0xfa;
	    }
	  }
	  return;
	}
	
	#endif
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

	moveFrame__8CGMonObjFv(this);
	const int branch = *reinterpret_cast<int*>(self + 0x6D0);
	const int flatFlags = *reinterpret_cast<int*>(CFlat + 0x12E8);
	if ((*reinterpret_cast<volatile signed char*>(SoundBuffer_1260_ + 0x14) < 0) ||
	    ((branch == 1) && ((flatFlags & 1) != 0)) || ((branch == 2) && ((flatFlags & 2) != 0))) {
		changeStat__8CGPrgObjFiii(this, 0, 0, 0);
	}
	return;

state101:
	if (*reinterpret_cast<int*>(self + 0x528) == 0) {
		reqAnim__8CGPrgObjFiii(this, -1, 0, 0);
		rotTarget__8CGMonObjFif(this, *reinterpret_cast<int*>(self + 0x6C4), FLOAT_80331da4);
	}
	if ((*reinterpret_cast<volatile signed char*>(SoundBuffer_1260_ + 0x14) < 0) ||
	    (*reinterpret_cast<float*>(self + 0x5D0 + *reinterpret_cast<int*>(self + 0x620) * 4) < FLOAT_80331da8)) {
		changeStat__8CGPrgObjFiii(this, 0, 0, 0);
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
		if ((work[0x14] & 0x40) == 0 && (*reinterpret_cast<int*>(CFlat + 0x12E8) & 2) == 0) {
			CVector left(FLOAT_80331d90, FLOAT_80331cf8, FLOAT_80331d94);
			if (PSVECDistance(reinterpret_cast<Vec*>(&left), &object->m_worldPosition) < FLOAT_80331d98 &&
			    *reinterpret_cast<int*>(work + 0xC) == 0) {
				work[0x14] |= 0x40;
				*reinterpret_cast<int*>(work + 0xC) = 300;
				*reinterpret_cast<int*>(mon + 0x6D0) = 2;
				return 100;
			}
		}
		if ((work[0x14] & 0x20) == 0 && (*reinterpret_cast<int*>(CFlat + 0x12E8) & 1) == 0) {
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
		setActionParam__8CGMonObjFi(this, -11);
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
		setActionParam__8CGMonObjFi(this, -8);
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
		setActionParam__8CGMonObjFi(this, -10);
		break;
	case 101:
		setActionParam__8CGMonObjFi(this, -14);
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
	CGObject* object = reinterpret_cast<CGObject*>(this);
	CGCharaObj* chara = reinterpret_cast<CGCharaObj*>(this);
	u8& lichFlags = *reinterpret_cast<u8*>(SoundBuffer + 0x4FC);
	const int flatFlags = *reinterpret_cast<int*>(CFlat + 4840);

	if (((flatFlags & 1) == 0) && (static_cast<s8>(lichFlags) < 0)) {
		lichFlags = (lichFlags & 0x3F) | 0x40;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x6C8) = 0;
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x1157C, 0x32, 0x96, 0, 0);
	} else if (((flatFlags & 1) != 0) && (static_cast<s8>(lichFlags) >= 0)) {
		lichFlags = (lichFlags & 0x3F) | 0xC0;
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x6C8) = 0;
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0x1157D, 0x32, 0x96, 0, 0);
	}

	if ((lichFlags & 0x40) != 0) {
		chara->endPSlotBit(0x800);
		if (static_cast<s8>(lichFlags) < 0) {
			int pdtNo = -1;
			if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<u8*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			}
			putParticle__8CGPrgObjFiiP8CGObjectfi(prgObj, (pdtNo << 8) | 0x1D,
			                                      *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x590), object,
			                                      FLOAT_80331d18, 0);
		}
		lichFlags &= 0xBF;
	}

	const int stat = prgObj->m_lastStateId;
	if (stat == 0x65) {
		if (prgObj->m_stateFrame == 0 && flatFlags == 3) {
			changeStat__8CGPrgObjFiii(prgObj, 0, 0, 0);
		} else {
			chara->statAttack();
			if (prgObj->m_stateFrame == 0x29) {
				int stack[3] = {10, 1, 0};
				SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				    CFlat, 0, 1, 9, 3, stack, 0);
			}
		}
	} else if (stat < 0x65 && stat > 99) {
		teleport(1, 0x0E, 0x29, 100, 0x11578, 0x11579, 0x2D, 0x2B, 0x2C, DAT_802127f0,
		         *reinterpret_cast<int*>(SoundBuffer_1260_), *reinterpret_cast<Vec*>(SoundBuffer_1260_ + 4));
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
	const int flatFlags = *reinterpret_cast<int*>(CFlat + 4840);
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
			setActionParam__8CGMonObjFi(this, -12);
			return;
		} else {
			return;
		}
	} else {
		setActionParam__8CGMonObjFi(this, -14);
	}

	*reinterpret_cast<int*>(SoundBuffer_1260_) += 1;
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
	#if 0
	// Function: frameStatFuncTetsukyojin__8CGMonObjFv
	// Entry: 80130d00
	// Size: 1184 bytes
	
	/* WARNING: Removing unreachable block (ram,0x80131180) */
	/* WARNING: Removing unreachable block (ram,0x80130d10) */
	/* WARNING: Type propagation algorithm not settling */
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncTetsukyojin__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  float fVar1;
	  float fVar2;
	  float fVar3;
	  int iVar4;
	  float *pfVar5;
	  CRef *pCVar6;
	  double dVar7;
	  double dVar8;
	  Vec local_98;
	  CVector CStack_8c;
	  CVector local_80;
	  CVector CStack_74;
	  CVector local_68;
	  CVector local_5c;
	  CVector local_50;
	  undefined4 local_44;
	  undefined4 local_40;
	  undefined4 local_3c;
	  Vec local_38;
	  longlong local_28;
	  
	  iVar4 = *(int *)&gMonObj->field_0x520;
	  if (iVar4 == 0x66) {
	    if ((int)CFlat._4840_4_ < 1) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	    }
	    else {
	      if ((gMonObj->_bossBranchRelated == 1) && (*(int *)&gMonObj->field_0x528 == 0)) {
	        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff3fffd;
	        gMonObj->_bossBranchRelated = 2;
	        CFlat._4844_4_ = 1;
	        local_44 = 10;
	        local_40 = 0;
	        local_3c = 0;
	        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
	                  (&CFlat,0,1,9,3,&local_44,(CStack *)0x0);
	      }
	      if (CFlat._4844_4_ == 0) {
	        gMonObj->_bossBranchRelated = 0;
	        *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	      }
	    }
	  }
	  else if (iVar4 < 0x66) {
	    if (iVar4 == 100) {
	      if (*(int *)&gMonObj->field_0x528 == 0) {
	        __ct__7CVectorFRC3Vec
	                  (&local_50,
	                   &(Game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).gPrgObj.
	                    object.m_worldPosition);
	        __ct__7CVectorFfff(-local_50.x,-local_50.y,-local_50.z,&local_5c);
	        local_38.x = local_5c.x;
	        local_38.z = local_5c.z;
	        local_38.y = FLOAT_80331cf8;
	        dVar7 = (double)PSVECMag(&local_38);
	        if (dVar7 < (double)FLOAT_80331d7c) {
	          __ct__7CVectorFfff(FLOAT_80331cf8,FLOAT_80331cf8,FLOAT_80331d80,&local_68);
	          local_38.x = local_68.x;
	          local_38.y = local_68.y;
	          local_38.z = local_68.z;
	        }
	        PSVECNormalize(&local_38,&local_38);
	        PSVECScale(FLOAT_80331d84 - (gMonObj->gObject).m_capsuleHalfHeight,&local_38,&local_38);
	        SoundBuffer._1264_4_ = local_38.x;
	        SoundBuffer._1268_4_ = local_38.y;
	        SoundBuffer._1272_4_ = local_38.z;
	        __ct__7CVectorFRC3Vec(&CStack_74,&(gMonObj->gObject).m_worldPosition);
	        __ct__7CVectorFv(&local_98);
	        PSVECSubtract(&local_38,(Vec *)&CStack_74,&local_98);
	        local_38.x = local_98.x;
	        local_38.y = local_98.y;
	        local_38.z = local_98.z;
	        dVar8 = (double)PSVECDistance(&local_38,&(gMonObj->gObject).m_worldPosition);
	        dVar7 = (double)FLOAT_80331d88;
	        if (dVar8 < (double)FLOAT_80331d88) {
	          dVar7 = dVar8;
	        }
	        memset(&gMonObj->field_0x70c,0,0x34);
	        dVar8 = (double)FLOAT_80331d30;
	        *(undefined4 *)&gMonObj->field_0x70c = 0x2114;
	        fVar1 = FLOAT_80331d58;
	        *(float *)&gMonObj->field_0x718 = local_38.x;
	        local_28 = (longlong)(int)(dVar7 * dVar8);
	        *(float *)&gMonObj->field_0x71c = local_38.y;
	        *(float *)&gMonObj->field_0x720 = local_38.z;
	        *(float *)&gMonObj->field_0x724 = fVar1;
	        *(int *)&gMonObj->field_0x72c = (int)(dVar7 * dVar8);
	        *(undefined4 *)&gMonObj->field_0x738 = 0x67;
	      }
	      moveFrame__8CGMonObjFv(gMonObj);
	    }
	    else if (99 < iVar4) {
	      if ((CFlat._4840_4_ != 0) && (*(int *)&gMonObj->field_0x528 == 0x25)) {
	        if ((int)CFlat._4840_4_ < 1) {
	          CFlat._4840_4_ = 0;
	        }
	        else if (((CFlat._4840_4_ == 1) && (0x13 < (int)SoundBuffer._1260_4_)) ||
	                ((1 < (int)CFlat._4840_4_ && (4 < (int)SoundBuffer._1260_4_)))) {
	          SoundBuffer._1260_4_ = 0;
	          DispCharaParts__8CGObjectFi(&gMonObj->gObject,1);
	          pCVar6 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	          if (pCVar6 == (CRef *)0x0) {
	            iVar4 = -1;
	          }
	          else {
	            iVar4 = pCVar6[2].refCount;
	          }
	          putParticle__8CGPrgObjFiiP8CGObjectfi
	                    ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar4 << 8 | 0x2d,0,
	                     &gMonObj->gObject,0x101e4);
	          if (gMonObj->_bossBranchRelated == 0) {
	            CFlat._4840_4_ = CFlat._4840_4_ + -1;
	          }
	          gMonObj->_bossBranchRelated = 1;
	          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	        }
	      }
	      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	    }
	  }
	  else if (iVar4 < 0x68) {
	    if (*(int *)&gMonObj->field_0x528 == 0x10) {
	      memset(&gMonObj->field_0x70c,0,0x34);
	      *(undefined4 *)&gMonObj->field_0x70c = 0x2410;
	      pfVar5 = (float *)__ct__7CVectorFRC3Vec(&CStack_8c,(Vec *)(SoundBuffer + 0x4f0));
	      __ct__7CVectorFfff(-*pfVar5,-pfVar5[1],-pfVar5[2],&local_80);
	      fVar2 = FLOAT_80331d78;
	      *(float *)&gMonObj->field_0x718 = local_80.x;
	      fVar3 = FLOAT_80331d84;
	      fVar1 = FLOAT_80331d58;
	      *(float *)&gMonObj->field_0x71c = local_80.y;
	      *(float *)&gMonObj->field_0x720 = local_80.z;
	      *(float *)&gMonObj->field_0x724 = fVar2;
	      iVar4 = (int)((fVar1 * (fVar3 - (gMonObj->gObject).m_capsuleHalfHeight)) / fVar2);
	      local_28 = (longlong)iVar4;
	      *(int *)&gMonObj->field_0x72c = iVar4;
	    }
	    if (0xf < *(int *)&gMonObj->field_0x528) {
	      moveFrame__8CGMonObjFv(gMonObj);
	    }
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	u8* self = reinterpret_cast<u8*>(this);
	const int state = prgObj->m_lastStateId;

	if (state == 0x66) {
		if (*reinterpret_cast<int*>(CFlat + 4840) < 1) {
			changeStat__8CGPrgObjFiii(prgObj, 0, 0, 0);
		} else {
			if ((*reinterpret_cast<int*>(self + 0x6B4) == 1) && (prgObj->m_stateFrame == 0)) {
				int stack[3];

				object->m_bgColMask &= 0xFFF3FFFD;
				*reinterpret_cast<int*>(self + 0x6B4) = 2;
				*reinterpret_cast<int*>(CFlat + 4844) = 1;
				stack[0] = 10;
				stack[1] = 0;
				stack[2] = 0;
				SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				    CFlat, 0, 1, 9, 3, stack, 0);
			}

			if (*reinterpret_cast<int*>(CFlat + 4844) == 0) {
				*reinterpret_cast<int*>(self + 0x6B4) = 0;
				*reinterpret_cast<int*>(self + 0x6C8) = 0;
				changeStat__8CGPrgObjFiii(prgObj, 0, 0, 0);
			}
		}
	} else if (state == 100) {
		moveFrame__8CGMonObjFv(this);
	} else if (state > 99) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	} else if (state == 0x67) {
		if (prgObj->m_stateFrame > 0xF) {
			moveFrame__8CGMonObjFv(this);
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
	if (*reinterpret_cast<int*>(mon + 0x6D0) == 0) {
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 4, 0, 0);
		*reinterpret_cast<int*>(mon + 0x6D0) = 1;
		*reinterpret_cast<int*>(CFlat + 4840) = 1;
	} else {
		return;
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
	aiTargetAttackRomMon__8CGMonObjFi(this, 0x3B);
	if (*reinterpret_cast<int*>(mon + 0x6C4) < 0) {
		aiTarget__8CGMonObjFv(this);
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
	    (*reinterpret_cast<int*>(CFlat + 4840) == 1)) {
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
			moveFrame__8CGMonObjFv(this);
			if ((*reinterpret_cast<u32*>(mon + 0x710) & 1) != 0) {
				addSubStat__8CGPrgObjFv(prgObj);
			}
		} else if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				reqAnim__8CGPrgObjFiii(prgObj, 0x1A, 0, 0);
			} else if (isLoopAnim__8CGPrgObjFv(prgObj) != 0) {
				addSubStat__8CGPrgObjFv(prgObj);
			}
		} else if (prgObj->m_subState == 2 && prgObj->m_subFrame == 0) {
			reqAnim__8CGPrgObjFiii(prgObj, 0x1B, 1, 0);
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
	if (script != 0 && script[7] < 2) {
		reinterpret_cast<CGCharaObj*>(this)->ClearAllSta();
		object->m_bgColMask &= 0xFFF7FFFF;
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 100, 0, 0);
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6B4) = 1;
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
		setActionParam__8CGMonObjFi(this, -13);
		break;
	case 101:
		setActionParam__8CGMonObjFi(this, -14);
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
		pos.x += RandFPM__5CMathFf(static_cast<float>((prgObj->m_stateFrame == 0) ? 0 : 40), &Math);
		pos.z += RandFPM__5CMathFf(static_cast<float>((prgObj->m_stateFrame == 0) ? 0 : 40), &Math);
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
	initFinishedFuncDefault__8CGMonObjFv(this);
	*reinterpret_cast<CGMonObj**>(SoundBuffer_1260_ + 0x74) = this;

	if (strcmp(Game.m_currentScriptName, s_meteo_3_80331D64) == 0) {
		CGObject* object = reinterpret_cast<CGObject*>(this);
		MeteoParasiteCBossWork* work = reinterpret_cast<MeteoParasiteCBossWork*>(SoundBuffer_1260_);
		work->bits.m_meteo3 = 1;
		work->m_index = 3;
		*reinterpret_cast<u16*>(reinterpret_cast<u8*>(object->m_scriptHandle) + 0x1C) = 1;
		object->SetAnimSlot(0x35, 0);
		reqAnim__8CGPrgObjFiii(this, 0x35, 1, 0);
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
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 0x66, 0, 0);
		object->m_bgColMask &= 0xFFF7FFFF;
	} else if (timer > 0x31) {
		timer = 0;
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 0x67, 0, 0);
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
	#if 0
	// Function: frameStatFuncMeteoParasiteC__8CGMonObjFv
	// Entry: 801302c8
	// Size: 1008 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncMeteoParasiteC__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  if (iVar1 == 0x67) {
	    iVar1 = *(int *)&gMonObj->field_0x52c;
	    if (iVar1 == 0) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        damageDelete__10CGCharaObjFv();
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1c,0,0);
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,1);
	        }
	      }
	    }
	    else if (iVar1 == 1) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f | 0x80;
	        m_boss__8CGMonObj._96_4_ = 1;
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1d,1,0);
	      }
	      else if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18)) {
	        changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,2);
	      }
	    }
	    else if (iVar1 == 2) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1e,0,0);
	        playSe3D__8CGPrgObjFiiiiP3Vec
	                  ((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 2 + 0x11d34,0x32,0x96,0,0);
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
	          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	          gMonObj->_bossBranchRelated = 0;
	          m_boss__8CGMonObj._100_4_ = 0x177;
	          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	        }
	      }
	    }
	  }
	  else if (iVar1 < 0x67) {
	    if (iVar1 == 0x65) {
	      if (*(int *)&gMonObj->field_0x52c == 0) {
	        if (*(int *)&gMonObj->field_0x530 == 0) {
	          m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f | 0x80;
	          m_boss__8CGMonObj._96_4_ = 0;
	        }
	        else if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18)) {
	          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        }
	      }
	      else if (*(int *)&gMonObj->field_0x52c == 1) {
	        if (*(int *)&gMonObj->field_0x530 == 0) {
	          reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ + 0x16,0,0);
	          playSe3D__8CGPrgObjFiiiiP3Vec
	                    ((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 2 + 0x11d35,0x32,0x96,0,0);
	        }
	        else {
	          iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	          if (iVar1 != 0) {
	            SetAnimSlot__8CGObjectFii(&gMonObj->gObject,m_boss__8CGMonObj._88_4_ + 0x19,0);
	            changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	            gMonObj->_bossBranchRelated = 1;
	            (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x80000;
	          }
	        }
	      }
	    }
	    else if (100 < iVar1) {
	      if (*(int *)&gMonObj->field_0x528 == 0) {
	        damageDelete__10CGCharaObjFv();
	        changeStat__8CGPrgObjFiii
	                  (*(CGPrgObj **)(&m_boss__8CGMonObj.field_0x48 + m_boss__8CGMonObj._88_4_ * 4),0x65
	                   ,0,0);
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ + 0x25,0,0);
	        CFlat._4836_1_ = CFlat._4836_1_ & 0xdf | 0x20;
	        CFlat._4840_4_ = CFlat._4840_4_ + 1;
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
	          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	          gMonObj->_bossBranchRelated = 0;
	          m_boss__8CGMonObj._100_4_ = 0x177;
	          m_boss__8CGMonObj._88_4_ = m_boss__8CGMonObj._88_4_ + 1;
	          if (2 < (int)m_boss__8CGMonObj._88_4_) {
	            m_boss__8CGMonObj._88_4_ = 0;
	          }
	          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	        }
	      }
	    }
	  }
	  else if ((iVar1 < 0x69) && (*(int *)&gMonObj->field_0x528 == 0)) {
	    reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x35,1,0);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	u8* mon = reinterpret_cast<u8*>(this);
	int* bossIndex = reinterpret_cast<int*>(m_boss__8CGMonObj + 0x58);
	u8* bossFlags = m_boss__8CGMonObj + 0x5C;
	int* bossMode = reinterpret_cast<int*>(m_boss__8CGMonObj + 0x60);
	int* bossWait = reinterpret_cast<int*>(m_boss__8CGMonObj + 0x64);
	CGPrgObj** bossObjArr = reinterpret_cast<CGPrgObj**>(m_boss__8CGMonObj + 0x48);

	int state = prgObj->m_lastStateId;
	if (state == 0x67) {
		int subState = prgObj->m_subState;
		if (subState == 0) {
			if (prgObj->m_subFrame == 0) {
				charaObj->damageDelete();
				prgObj->reqAnim(*bossIndex * 3 + 0x1C, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				prgObj->changeSubStat(1);
			}
		} else if (subState == 1) {
			if (prgObj->m_subFrame == 0) {
				*bossFlags = (*bossFlags & 0x7F) | 0x80;
				*bossMode = 1;
				prgObj->reqAnim(*bossIndex * 3 + 0x1D, 1, 0);
			} else if (((*bossFlags & 0x80) == 0)) {
				prgObj->changeSubStat(2);
			}
		} else if (subState == 2) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(*bossIndex * 3 + 0x1E, 0, 0);
				prgObj->playSe3D(*bossIndex * 2 + 0x11D34, 0x32, 0x96, 0, 0);
			} else if (prgObj->isLoopAnim() != 0) {
				object->SetAnimSlot(0, 0);
				prgObj->changeStat(0, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 0;
				*bossWait = 0x177;
				*reinterpret_cast<int*>(mon + 0x6C8) = 0;
			}
		}
	} else if (state < 0x67) {
		if (state == 0x65) {
			if (prgObj->m_subState == 0) {
				if (prgObj->m_subFrame == 0) {
					*bossFlags = (*bossFlags & 0x7F) | 0x80;
					*bossMode = 0;
				} else if (((*bossFlags & 0x80) == 0)) {
					prgObj->addSubStat();
				}
			} else if (prgObj->m_subState == 1) {
				if (prgObj->m_subFrame == 0) {
					prgObj->reqAnim(*bossIndex + 0x16, 0, 0);
					prgObj->playSe3D(*bossIndex * 2 + 0x11D35, 0x32, 0x96, 0, 0);
				} else if (prgObj->isLoopAnim() != 0) {
					object->SetAnimSlot(*bossIndex + 0x19, 0);
					prgObj->changeStat(0, 0, 0);
					*reinterpret_cast<int*>(mon + 0x6B4) = 1;
					object->m_bgColMask |= 0x80000;
				}
			}
		} else if (state > 100) {
			if (prgObj->m_stateFrame == 0) {
				charaObj->damageDelete();
				bossObjArr[*bossIndex]->changeStat(0x65, 0, 0);
				prgObj->reqAnim(*bossIndex + 0x25, 0, 0);
				CFlat[4836] = static_cast<u8>((CFlat[4836] & 0xDF) | 0x20);
				*reinterpret_cast<int*>(CFlat + 4840) = *reinterpret_cast<int*>(CFlat + 4840) + 1;
			} else if (prgObj->isLoopAnim() != 0) {
				object->SetAnimSlot(0, 0);
				prgObj->changeStat(0, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 0;
				*bossWait = 0x177;
				*bossIndex = *bossIndex + 1;
				if (2 < *bossIndex) {
					*bossIndex = 0;
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
	return *reinterpret_cast<int*>(SoundBuffer_1260_ + 0x78);
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
	MeteoParasiteCBossWork* work = reinterpret_cast<MeteoParasiteCBossWork*>(SoundBuffer_1260_);
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
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), nextState, 0, 0);
	} else {
		logicFuncDefault__8CGMonObjFv(this);
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
	initFinishedFuncDefault__8CGMonObjFv(this);

	const int scriptKind = reinterpret_cast<int>(reinterpret_cast<CGObject*>(this)->m_scriptHandle[4]);
	if (scriptKind == 0x85) {
		CChara::CNode** nodes = reinterpret_cast<CChara::CNode**>(SoundBuffer_1260_);
		int nodeIndex =
		    SearchNode__Q26CChara6CModelFPc(reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model,
		                                    const_cast<char*>(s_to_a_obj_801dd4e8));
		nodes[0] = reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model->m_nodes + nodeIndex;
		nodes[0]->m_flags &= 0x7F;

		nodeIndex =
		    SearchNode__Q26CChara6CModelFPc(reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model,
		                                    const_cast<char*>(s_to_b_obj_801dd4f4));
		nodes[1] = reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model->m_nodes + nodeIndex;
		nodes[1]->m_flags &= 0x7F;

		char nodeName[256];
		for (int i = 0; i < 12; i++) {
			sprintf(nodeName, s_to_02d_obj_801dd500, i + 1);
			nodeIndex = SearchNode__Q26CChara6CModelFPc(reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model,
			                                            nodeName);
			nodes[i + 2] = reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model->m_nodes + nodeIndex;
			if ((m_boss__8CGMonObj[0x5C] & 0x40) != 0) {
				int dispIndex =
				    GetDispIndex__Q26CChara6CModelFPQ26CChara5CNode(
				        reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model, nodes[i + 2]);
				reinterpret_cast<CGObject*>(this)->m_charaModelHandle->m_model->m_meshVisibleMask &= ~(1 << dispIndex);
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
	if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x87) && stat == 0x67) {
		setActionParam__8CGMonObjFi(this, -13);
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
	u8* bossFlags = m_boss__8CGMonObj + 0x5C;
	int* bossIndex = reinterpret_cast<int*>(m_boss__8CGMonObj + 0x58);
	int* bossMode = reinterpret_cast<int*>(m_boss__8CGMonObj + 0x60);
	u8* mon = reinterpret_cast<u8*>(this);
	const int scriptKind = reinterpret_cast<int>(object->m_scriptHandle[4]);

	if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x85) && ((*reinterpret_cast<unsigned char*>(SoundBuffer + 1356) & 0x40) == 0)) {
		*reinterpret_cast<float*>(SoundBuffer + 1260) += FLOAT_80331d60;
	}

	if (scriptKind < 0x88 && scriptKind > 0x84 && *bossIndex == scriptKind - 0x85 && (*bossFlags & 0x80) != 0) {
		int effect;
		int arg0;
		int arg1;
		if (chara->getItemPdt(0, 0, effect, arg0, arg1) != 0) {
			if (*bossMode == 0) {
				changeStat__8CGPrgObjFiii(prgObj, 100, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 0;
			}
			if (*bossMode == 2) {
				changeStat__8CGPrgObjFiii(prgObj, 0x65, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 2;
			}
			if (*bossMode == 1) {
				changeStat__8CGPrgObjFiii(prgObj, 0x66, 0, 0);
				*reinterpret_cast<int*>(mon + 0x6B4) = 1;
			}
			*bossFlags &= 0x7F;
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
		logicFuncDefault__8CGMonObjFv(this);
	} else {
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), nextState, 0, 0);
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
		if (*reinterpret_cast<int*>(SoundBuffer_1260_ + 0x78) == 1 && *reinterpret_cast<int*>(mon + 0x6D0) == 1) {
			return -1;
		}
		return -2;
	case 0x87:
		if (*reinterpret_cast<int*>(SoundBuffer_1260_ + 0x78) == 2 && *reinterpret_cast<int*>(mon + 0x6D0) < 2) {
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
	if (Rand__5CMathFUl(&Math, 300) == 0) {
		aiTarget__8CGMonObjFv(this);
		_aiSeq__8CGMonObjFiiiiii(this, -14, seq, 0, 1, 100, -1);
		_aiSeq__8CGMonObjFiiiiii(this, -13, seq, 1, 0, 100, -1);
		const int seOffset = Rand__5CMathFUl(&Math, 3);
		playSe3D__8CGPrgObjFiiiiP3Vec(reinterpret_cast<CGPrgObj*>(this), seOffset + 0x11D40, 0x32, 0x96, 0, 0);
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
	initFinishedFuncDefault__8CGMonObjFv(this);
	const int slot = static_cast<int>(reinterpret_cast<long>(object->m_scriptHandle[4])) - 0x8E;
	reinterpret_cast<CGMonObj**>(m_boss__8CGMonObj + 0x18)[slot] = this;
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
	if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
		pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
	}
	putParticle__8CGPrgObjFiiP8CGObjectfi(reinterpret_cast<CGPrgObj*>(this), (pdtNo << 8) | 2, 0, object, FLOAT_80331d18, 0);
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

	if (activeCount == 0 && Rand__5CMathFUl(&Math, 3) == 0) {
		nextState = 100;
	}

	if (nextState == -1) {
		logicFuncDefault__8CGMonObjFv(this);
	} else {
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), nextState, 0, 0);
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
		setActionParam__8CGMonObjFi(this, -9);
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
					setRepop__8CGMonObjFi(monObj, 0);
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
	initFinishedFuncDefault__8CGMonObjFv(this);
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
	int& timer = *reinterpret_cast<int*>(SoundBuffer_1260_ + 0x24);
	if (timer >= 100 && *reinterpret_cast<int*>(mon + 0x6D0) == 0) {
		*reinterpret_cast<int*>(mon + 0x6D0) = 1;
		*reinterpret_cast<int*>(mon + 0x6C8) = 0;
		changeStat__8CGPrgObjFiii(prgObj, 100, 0, 0);
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
		setActionParam__8CGMonObjFi(this, -7);
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
		CGPartyObj** work = reinterpret_cast<CGPartyObj**>(SoundBuffer_1260_);
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = work[i + 2];
			if (party != 0) {
				CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
				if (partyPrg->m_lastStateId == 0x25) {
					changeStat__8CGPrgObjFiii(partyPrg, 0x24, 0, 0);
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
			if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}

			prgObj->putParticle((pdtNo << 8) | 0x11, 0, object, 1.0f, 0);
			prgObj->putParticle((pdtNo << 8) | 0x12, 0, object, 1.0f, 0);
			prgObj->playSe3D(0x12913, 0x32, 0x96, 0, 0);
		} else if (stateFrame == 0x29) {
			object->m_bodyEllipsoidRadius = 7.0f;
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
				if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
					pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
				}

				prgObj->putParticle((pdtNo << 8) | 0x10, 0, object, 1.0f, 0);
				prgObj->playSe3D(0x12912, 0x32, 0x96, 0, 0);
			} else if (stateFrame == 0x7D) {
				object->m_bodyEllipsoidRadius = 2.0f;
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
			if (object->m_charaModelHandle != 0 && object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = reinterpret_cast<int*>(object->m_charaModelHandle->m_pdtLoadRef)[2];
			}
			prgObj->putParticle((pdtNo << 8) | 5, *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0x12902);
		} else if (stateFrame == 0x4B) {
			CGPartyObj** work = reinterpret_cast<CGPartyObj**>(SoundBuffer_1260_);
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
			CGPartyObj** work = reinterpret_cast<CGPartyObj**>(SoundBuffer_1260_);
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
	int& timer = *reinterpret_cast<int*>(SoundBuffer + 1272);

	if (*reinterpret_cast<int*>(mon + 0x6B4) == 2) {
		timer += 1;
		if (timer > 9) {
			*reinterpret_cast<int*>(mon + 0x6B4) = 3;
			nextState = 0x65;
			*reinterpret_cast<int*>(mon + 0x6C8) = 0;
			object->m_bgColMask &= 0xFFF7FFFF;
			timer = 0;
		}
	}

	if (nextState == -1) {
		logicFuncDefault__8CGMonObjFv(this);
	} else {
		changeStat__8CGPrgObjFiii(prgObj, nextState, 0, 0);
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
		prgObj->putParticle(particleStart | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0);

		if (mode == 0) {
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			} else {
				pdtNo = -1;
			}
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, 1.0f, 0);
		} else {
			if (object->m_charaModelHandle->m_pdtLoadRef != 0) {
				pdtNo = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_pdtLoadRef) + 0x14);
			} else {
				pdtNo = -1;
			}
			prgObj->putParticle(particleBlend | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), object, 1.0f, 0);
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
					nextIndex = Rand__5CMathFUl(&Math, 4);
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
				prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &teleportPoints[teleportIndex], 1.0f, 0);
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
					prgObj->putParticle(particleEnd | (pdtNo << 8), *reinterpret_cast<int*>(mon + 0x58C), &object->m_worldPosition, 1.0f, 0);
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
				setAttackAfter__8CGMonObjFi(this, *reinterpret_cast<int*>(mon + 0x560));
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
		double inv = 1.0 / sqrt(dist);
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
		playSe3D__8CGPrgObjFiiiiP3Vec(prgObj, 0xdec0, 0x32, 0x1c2, 0, 0);
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.m_partyObjArr[i];
			if (party != 0) {
				ResetParticleWork__13CFlatRuntime2Fii(CFlat, 0x26, *(int*)(self + 0x58c));
				SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
				SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, party);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
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
