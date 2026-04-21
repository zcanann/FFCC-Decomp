#include "ffcc/monobj_boss.h"
#include "ffcc/prgobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/vector.h"

#include <math.h>

extern "C" int Rand__5CMathFUl(CMath*, unsigned long);
extern "C" void setAttackAfter__8CGMonObjFi(CGMonObj*, int);
extern "C" void setActionParam__8CGMonObjFi(CGMonObj*, int);
extern "C" void logicFuncDefault__8CGMonObjFv(CGMonObj*);
extern "C" void initFinishedFuncDefault__8CGMonObjFv(CGMonObj*);
extern "C" int calcBranchFuncDefault__8CGMonObjFi(CGMonObj*, int);
extern "C" void aiTargetAttackRomMon__8CGMonObjFi(CGMonObj*, int);
extern "C" void aiTarget__8CGMonObjFv(CGMonObj*);
extern "C" void _aiSeq__8CGMonObjFiiiiii(CGMonObj*, int, int, int, int, int, int);
extern "C" void reqAnim__8CGPrgObjFiii(void*, int, int, int);
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
extern float FLOAT_80331d84;
extern float FLOAT_80331d90;
extern float FLOAT_80331d94;
extern float FLOAT_80331d98;
extern float FLOAT_80331d9c;
extern float FLOAT_80331dac;
extern float FLOAT_80331db0;
extern float FLOAT_80331db4;
extern float FLOAT_80331dd8;
extern float FLOAT_80331d60;
extern float FLOAT_80331db8;
extern double DOUBLE_80331d00;
extern double DOUBLE_80331d08;
extern double DOUBLE_80331d10;
extern double DOUBLE_80331d38;
extern double DOUBLE_80331dc0;
extern char SoundBuffer[];
extern char SoundBuffer_1260_[];
extern "C" unsigned char m_boss__8CGMonObj[];

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
	if (script != 0 && script[7] == 0) {
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
	if (stat == 0x65) {
		setActionParam__8CGMonObjFi(this, -9);
	} else if (stat > 99 && stat < 0x65) {
		setActionParam__8CGMonObjFi(this, -10);
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
	int branch = 0;
	if (*reinterpret_cast<int*>(mon + 0x6D0) == 1) {
		branch = 2;
	} else {
		unsigned short* script = reinterpret_cast<unsigned short*>(object->m_scriptHandle);
		if (script != 0 && ((script[0x1A / 2] >> 1) <= script[0x1C / 2])) {
			branch = 1;
		}
	}
	return branch;
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
	#if 0
	// Function: frameStatFuncGolem__8CGMonObjFv
	// Entry: 80132670
	// Size: 700 bytes
	
	/* WARNING: Removing unreachable block (ram,0x80132910) */
	/* WARNING: Removing unreachable block (ram,0x80132680) */
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncGolem__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  byte bVar1;
	  int iVar2;
	  double dVar3;
	  double in_f31;
	  
	  iVar2 = *(int *)&gMonObj->field_0x520;
	  if (iVar2 != 0x66) {
	    if (iVar2 < 0x66) {
	      if (iVar2 == 100) {
	        if (*(int *)&gMonObj->field_0x528 == 0) {
	          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa17,0x32,0x96,0,0);
	        }
	        else if (*(int *)&gMonObj->field_0x528 == 0x14) {
	          DispCharaParts__8CGObjectFi(&gMonObj->gObject,1);
	          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa18,0x32,0x96,0,0);
	          gMonObj->_bossBranchRelated = 1;
	        }
	        _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	        return;
	      }
	      if (iVar2 < 100) {
	        return;
	      }
	      iVar2 = *(int *)&gMonObj->field_0x528;
	      if (iVar2 == 0) {
	        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa1a,0x32,0x96,0,0);
	      }
	      else if (iVar2 == 4) {
	        DispCharaParts__8CGObjectFi(&gMonObj->gObject,3);
	        gMonObj->_bossBranchRelated = 0;
	      }
	      else if (iVar2 == 5) {
	        DispCharaParts__8CGObjectFi(&gMonObj->gObject,7);
	      }
	      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	      return;
	    }
	    if (iVar2 != 0x68) {
	      if (0x67 < iVar2) {
	        return;
	      }
	      if (*(int *)&gMonObj->field_0x528 != 0x32) {
	        return;
	      }
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	      return;
	    }
	  }
	  if (((*(int *)&gMonObj->field_0x528 == 0x14) ||
	      (bVar1 = (gMonObj->gObject).m_stateFlags0, (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0
	      )) || ((iVar2 == 0x66 &&
	             (*(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x6c4 * 4) <
	              FLOAT_80331d58 * (gMonObj->gObject).m_bodyEllipsoidRadius)))) {
	    dVar3 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
	                              ((CGPrgObj *)gMonObj,
	                               Game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
	    (gMonObj->gObject).m_rotTargetY = (float)dVar3;
	    setAttackAfter__8CGMonObjFi(gMonObj,*(undefined4 *)&gMonObj->field_0x560);
	  }
	  else {
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      if (iVar2 != 0x67) {
	        if (iVar2 < 0x67) {
	          if (0x65 < iVar2) {
	            in_f31 = (double)FLOAT_80331cf8;
	          }
	        }
	        else if (iVar2 < 0x69) {
	          in_f31 = (double)FLOAT_80331d2c;
	        }
	      }
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,1,1,0);
	      dVar3 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
	                                ((CGPrgObj *)gMonObj,
	                                 Game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
	      (gMonObj->gObject).m_rotTargetY = (float)dVar3;
	      SoundBuffer._1276_4_ = (undefined4)((double)(gMonObj->gObject).m_rotTargetY + in_f31);
	    }
	    moveVectorHRot__8CGObjectFfffi
	              ((double)(float)SoundBuffer._1276_4_,(double)FLOAT_80331cf8,
	               (double)(*(float *)&gMonObj->field_0x690 *
	                       (FLOAT_80331d60 *
	                        (float)((double)CONCAT44(0x43300000,
	                                                 (uint)*(ushort *)
	                                                        ((int)(gMonObj->gObject).m_scriptHandle[9] +
	                                                        0xd4)) - DOUBLE_80331dc0) + FLOAT_80331db8))
	               ,&gMonObj->gObject,1);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	#if 0
	// Function: frameStatFuncArmstrong__8CGMonObjFv
	// Entry: 8013256c
	// Size: 148 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncArmstrong__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  undefined4 in_r4;
	  
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  if (iVar1 == 100) {
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,0);
	    }
	    else if (*(int *)&gMonObj->field_0x528 == 0x29) {
	      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
	    }
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  else if ((99 < iVar1) && (iVar1 < 0x69)) {
	    frameStatFuncGiantCrab__8CGMonObjFv(gMonObj,in_r4);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0xC00);
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
	#if 0
	// Function: frameStatFuncOrcKing__8CGMonObjFv
	// Entry: 801322dc
	// Size: 604 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncOrcKing__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  CRef *pCVar2;
	  CGMonObj *monObj;
	  
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    iVar1 = gMonObj->_bossBranchRelated;
	    if (iVar1 == 0) {
	      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	      if (pCVar2 == (CRef *)0x0) {
	        iVar1 = -1;
	      }
	      else {
	        iVar1 = pCVar2[2].refCount;
	      }
	      putParticle__8CGPrgObjFiiP8CGObjectfi
	                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x18,
	                 *(int *)&gMonObj->field_0x58c,&gMonObj->gObject,0x8cc0);
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xf,0,0);
	      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x10,0);
	      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x15,4);
	    }
	    else if (iVar1 == 0x96) {
	      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	      if (pCVar2 == (CRef *)0x0) {
	        iVar1 = -1;
	      }
	      else {
	        iVar1 = pCVar2[2].refCount;
	      }
	      putParticle__8CGPrgObjFiiP8CGObjectfi
	                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x19,
	                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc1);
	    }
	    else if (iVar1 == 300) {
	      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	      if (pCVar2 == (CRef *)0x0) {
	        iVar1 = -1;
	      }
	      else {
	        iVar1 = pCVar2[2].refCount;
	      }
	      putParticle__8CGPrgObjFiiP8CGObjectfi
	                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1a,
	                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc2);
	    }
	    else if (iVar1 == 0x1c2) {
	      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	      if (pCVar2 == (CRef *)0x0) {
	        iVar1 = -1;
	      }
	      else {
	        iVar1 = pCVar2[2].refCount;
	      }
	      putParticle__8CGPrgObjFiiP8CGObjectfi
	                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1b,
	                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc3);
	    }
	    else if (iVar1 == 600) {
	      endPSlotBit__10CGCharaObjFi(gMonObj,0xc00);
	      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xfffffff7,0,0);
	      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
	      for (monObj = (CGMonObj *)FindGMonObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
	          monObj != (CGMonObj *)0x0;
	          monObj = (CGMonObj *)
	                   FindGMonObjNext__13CFlatRuntime2FP8CGMonObj((CFlatRuntime2 *)&CFlat,monObj)) {
	        if (monObj != gMonObj) {
	          addHp__10CGCharaObjFiP8CGPrgObj
	                    ((CGCharaObj *)monObj,
	                     -(uint)*(ushort *)((int)(monObj->gObject).m_scriptHandle + 0x1a),
	                     (CGPrgObj *)0x0);
	        }
	      }
	      SoundBuffer._1260_4_ = 1;
	    }
	    gMonObj->_bossBranchRelated = gMonObj->_bossBranchRelated + 1;
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
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
	#if 0
	// Function: frameStatFuncGoblinKing__8CGMonObjFv
	// Entry: 8013204c
	// Size: 128 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncGoblinKing__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec
	              (gMonObj,0,0xd,8,0x42,0xa03e,0xa03f,3,4,5,&DAT_802127c0,0x8030014c,0x80300150);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
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
	#if 0
	// Function: frameStatFuncSaw__8CGMonObjFv
	// Entry: 80131dd8
	// Size: 560 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncSaw__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  CRef *pCVar2;
	  
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
	    iVar1 = *(int *)&gMonObj->field_0x52c;
	    if (iVar1 == 0) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,10,0,0);
	        pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	        if (pCVar2 == (CRef *)0x0) {
	          iVar1 = -1;
	        }
	        else {
	          iVar1 = pCVar2[2].refCount;
	        }
	        putParticle__8CGPrgObjFiiP8CGObjectfi
	                  ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8,
	                   *(int *)&gMonObj->field_0x564,&gMonObj->gObject,0x1c52c);
	        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1c52b,0x32,0x96,0,0);
	        memset(&gMonObj->field_0x70c,0,0x34);
	        *(undefined4 *)&gMonObj->field_0x70c = 0x1402;
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        }
	      }
	    }
	    else if (iVar1 == 1) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        *(undefined4 *)&gMonObj->field_0x560 = 0x495;
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,1,1,0);
	      }
	      if (*(int *)&gMonObj->field_0x530 == 0x19) {
	        resetIgnoreHit__10CGCharaObjFv(gMonObj);
	        (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,1,0,0);
	        gMonObj->field_0x6c0 = 0;
	      }
	      if ((0x19 < *(int *)&gMonObj->field_0x530) && (gMonObj->field_0x6c0 != '\0')) {
	        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
	      }
	    }
	    else if (iVar1 == 2) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,0,0,0);
	        gMonObj->field_0x6c0 = 0;
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xb,0,0);
	        endPSlotBit__10CGCharaObjFi(gMonObj,1);
	        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1c52d,0x32,0x96,0,0);
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	        }
	      }
	    }
	    moveFrame__8CGMonObjFv(gMonObj);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	if ((*reinterpret_cast<int*>(CFlat + 4840) == 0) || (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x6D4) & 0x80)) {
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
		*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x6D4) |= 0x80;
		*reinterpret_cast<int*>(SoundBuffer + 1268) = 0xFA;
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
void CGMonObj::attackCheckFuncLKShooter(int)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int result = -1;
	if (*reinterpret_cast<int*>(SoundBuffer + 1268) == 0) {
		Vec left = {FLOAT_80331d90, FLOAT_80331cf8, FLOAT_80331d94};
		Vec right = {FLOAT_80331d9c, FLOAT_80331cf8, FLOAT_80331d9c};
		if (PSVECDistance(&left, &object->m_worldPosition) < FLOAT_80331d98 && *reinterpret_cast<int*>(SoundBuffer + 1272) == 0) {
			*reinterpret_cast<int*>(SoundBuffer + 1272) = 300;
			*reinterpret_cast<int*>(mon + 0x6B4) = 2;
			result = 100;
		} else if (PSVECDistance(&right, &object->m_worldPosition) < FLOAT_80331d98 && *reinterpret_cast<int*>(SoundBuffer + 1276) == 0) {
			*reinterpret_cast<int*>(mon + 0x6B4) = 1;
			result = 100;
		}
	}
	*reinterpret_cast<int*>(mon + 0x6C4) = result;
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
	if (stat == 100) {
		setActionParam__8CGMonObjFi(this, -11);
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
	#if 0
	// Function: frameStatFuncDragonZombie__8CGMonObjFv
	// Entry: 8013164c
	// Size: 172 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncDragonZombie__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  if (iVar1 == 0x65) {
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xf,0,0);
	      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x987a,0x32,0x96,0,0);
	    }
	    iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	    if (iVar1 != 0) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	    }
	  }
	  else if ((iVar1 < 0x65) && (99 < iVar1)) {
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
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
	#if 0
	// Function: frameStatFuncCaveWorm__8CGMonObjFv
	// Entry: 8013159c
	// Size: 56 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncCaveWorm__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    suikomi__8CGMonObjFif((double)FLOAT_80331d8c,gMonObj,0x6c);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	if (stat == 0x65) {
		setActionParam__8CGMonObjFi(this, -14);
	} else if (stat > 99 && stat < 0x65) {
		setActionParam__8CGMonObjFi(this, -10);
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
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
	#if 0
	// Function: frameStatFuncLich__8CGMonObjFv
	// Entry: 80131294
	// Size: 652 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncLich__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  CRef *pCVar2;
	  undefined4 local_20;
	  undefined4 local_1c;
	  undefined4 local_18;
	  
	  if (((CFlat._4840_4_ & 1) == 0) && ((int)((uint)SoundBuffer[0x4fc] << 0x18) < 0)) {
	    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0x3f | 0x40;
	    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1157c,0x32,0x96,0,0);
	  }
	  else if (((CFlat._4840_4_ & 1) != 0) && (-1 < (int)((uint)SoundBuffer[0x4fc] << 0x18))) {
	    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0x3f | 0xc0;
	    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
	    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1157d,0x32,0x96,0,0);
	  }
	  if ((int)((uint)SoundBuffer[0x4fc] << 0x19 | (uint)(SoundBuffer[0x4fc] >> 7)) < 0) {
	    endPSlotBit__10CGCharaObjFi(gMonObj,0x800);
	    if ((int)((uint)SoundBuffer[0x4fc] << 0x18) < 0) {
	      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
	      if (pCVar2 == (CRef *)0x0) {
	        iVar1 = -1;
	      }
	      else {
	        iVar1 = pCVar2[2].refCount;
	      }
	      putParticle__8CGPrgObjFiiP8CGObjectfi
	                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1d,
	                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0);
	    }
	    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0xbf;
	  }
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  if (iVar1 == 0x65) {
	    if ((*(int *)&gMonObj->field_0x528 == 0) && (CFlat._4840_4_ == 3)) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	    }
	    else {
	      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	      if (*(int *)&gMonObj->field_0x528 == 0x29) {
	        local_20 = 10;
	        local_1c = 1;
	        local_18 = 0;
	        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
	                  (&CFlat,0,1,9,3,&local_20,(CStack *)0x0);
	      }
	    }
	  }
	  else if ((iVar1 < 0x65) && (99 < iVar1)) {
	    teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec
	              (gMonObj,1,0xe,0x29,100,0x11578,0x11579,0x2d,0x2b,0x2c,&DAT_802127f0,0x8030014c,
	               0x80300150);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	if (stat == 0x65) {
		setActionParam__8CGMonObjFi(this, -14);
		*reinterpret_cast<int*>(SoundBuffer + 1260) += 1;
	} else if (stat == -0xD) {
		*reinterpret_cast<int*>(SoundBuffer + 1260) += 1;
	} else if (stat == 0x67) {
		setActionParam__8CGMonObjFi(this, -12);
	}
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
	if (state == 0x66) {
		object->m_bgColMask |= 0xC0002;
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
	if (prgObj->m_lastStateId >= 100) {
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
	const int branch = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6B4);
	if (branch > 0) {
		return 1;
	}
	if (branch < 0) {
		return -1;
	}
	return 0;
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
void CGMonObj::tgtFuncGigasLoad(int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	aiTargetAttackRomMon__8CGMonObjFi(this, 0x3B);
	if (*reinterpret_cast<int*>(mon + 0x6C4) < 0) {
		aiTarget__8CGMonObjFv(this);
	}
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
	#if 0
	// Function: frameStatFuncWifeLamia__8CGMonObjFv
	// Entry: 80130ac8
	// Size: 300 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncWifeLamia__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  float fVar1;
	  float y;
	  int iVar2;
	  undefined4 *puVar3;
	  CVector CStack_18;
	  
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    iVar2 = *(int *)&gMonObj->field_0x52c;
	    if (iVar2 == 0) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        memset(&gMonObj->field_0x70c,0,0x34);
	        y = FLOAT_80331d70;
	        fVar1 = FLOAT_80331d6c;
	        *(undefined4 *)&gMonObj->field_0x70c = 0x10022;
	        puVar3 = (undefined4 *)__ct__7CVectorFfff(fVar1,y,FLOAT_80331d74,&CStack_18);
	        fVar1 = FLOAT_80331d78;
	        *(undefined4 *)&gMonObj->field_0x718 = *puVar3;
	        *(undefined4 *)&gMonObj->field_0x71c = puVar3[1];
	        *(undefined4 *)&gMonObj->field_0x720 = puVar3[2];
	        *(float *)&gMonObj->field_0x724 = fVar1;
	        *(float *)&gMonObj->field_0x728 = (gMonObj->gObject).m_bodyEllipsoidRadius;
	      }
	      moveFrame__8CGMonObjFv(gMonObj);
	      if ((*(uint *)&gMonObj->field_0x710 & 1) != 0) {
	        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
	      }
	    }
	    else if (iVar2 == 1) {
	      if (*(int *)&gMonObj->field_0x530 == 0) {
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x1a,0,0);
	      }
	      else {
	        iVar2 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar2 != 0) {
	          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        }
	      }
	    }
	    else if ((iVar2 == 2) && (*(int *)&gMonObj->field_0x530 == 0)) {
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x1b,1,0);
	    }
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	if (stat == 0x65) {
		setActionParam__8CGMonObjFi(this, -14);
	} else if (stat > 99 && stat < 0x65) {
		setActionParam__8CGMonObjFi(this, -13);
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
	if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == 100) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
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
	#if 0
	// Function: frameStatFuncMolbol__8CGMonObjFv
	// Entry: 80130898
	// Size: 336 bytes
	
	/* WARNING: Type propagation algorithm not settling */
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncMolbol__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  uint uVar2;
	  double dVar3;
	  CVector local_28;
	  undefined4 local_18;
	  uint uStack_14;
	  undefined4 local_10;
	  uint uStack_c;
	  
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  if (iVar1 == 0x65) {
	    iVar1 = *(int *)&gMonObj->field_0x528;
	    if (((iVar1 == 0) || (iVar1 == 5)) || (iVar1 == 10)) {
	      __ct__7CVectorFRC3Vec
	                (&local_28,
	                 &(Game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).gPrgObj.object
	                  .m_worldPosition);
	      local_18 = 0x43300000;
	      uVar2 = countLeadingZeros(*(undefined4 *)&gMonObj->field_0x528);
	      uStack_14 = ~-(uVar2 >> 5 & 1) & 0x28 ^ 0x80000000;
	      dVar3 = (double)RandFPM__5CMathFf((double)(float)((double)CONCAT44(0x43300000,uStack_14) -
	                                                       DOUBLE_80331d38),&Math);
	      local_10 = 0x43300000;
	      local_28.x = (float)((double)local_28.x + dVar3);
	      uVar2 = countLeadingZeros(*(undefined4 *)&gMonObj->field_0x528);
	      uStack_c = ~-(uVar2 >> 5 & 1) & 0x28 ^ 0x80000000;
	      dVar3 = (double)RandFPM__5CMathFf((double)(float)((double)CONCAT44(0x43300000,uStack_c) -
	                                                       DOUBLE_80331d38),&Math);
	      local_28.z = (float)((double)local_28.z + dVar3);
	      putParticleFromItem__10CGCharaObjFiiiP3Vec
	                (gMonObj,*(undefined4 *)&gMonObj->field_0x560,3,*(undefined4 *)&gMonObj->field_0x564
	                 ,&local_28);
	    }
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  else if ((iVar1 < 0x65) && (99 < iVar1)) {
	    suikomi__8CGMonObjFif((double)FLOAT_80331cf8,gMonObj,0x53);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
	}
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
	*reinterpret_cast<CGMonObj**>(SoundBuffer + 1344) = this;
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
	int& timer = *reinterpret_cast<int*>(SoundBuffer + 1360);
	if (*reinterpret_cast<unsigned char*>(SoundBuffer + 1356) & 0x80) {
		nextState = 0x68;
	} else {
		timer = (timer - 1) & ~((timer - 1) >> 31);
		if (*reinterpret_cast<int*>(mon + 0x6B4) == 0) {
			if (timer != 0) {
				return;
			}
			nextState = 0x65;
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
 * PAL Address: 0x80130208
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::attackCheckFuncMeteoParasiteC(int)
{
	int branch = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6B4);
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C4) =
	    (((branch - 1U) | (1U - branch)) >> 31) - 1;
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
	#if 0
	// Function: alwaysFuncMeteoParasite__8CGMonObjFv
	// Entry: 8012fcc8
	// Size: 796 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void alwaysFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int *piVar1;
	  float fVar2;
	  double dVar3;
	  float fVar4;
	  float fVar5;
	  uint uVar6;
	  uint uVar7;
	  uint uVar8;
	  uint uVar9;
	  uint uVar10;
	  uint uVar11;
	  int iVar12;
	  int iVar13;
	  void *pvVar14;
	  int iVar15;
	  
	  pvVar14 = (gMonObj->gObject).m_scriptHandle[4];
	  if ((pvVar14 == (void *)0x85) &&
	     (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
	                (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)))) {
	    if (DAT_8032eea4 == '\0') {
	      DAT_8032eea4 = '\x01';
	      FLOAT_8032eea0 = FLOAT_80331cf8;
	    }
	    PSMTXRotRad(FLOAT_8032eea0,SoundBuffer._1260_4_ + 0x14,0x78);
	    PSMTXRotRad(-FLOAT_8032eea0,SoundBuffer._1264_4_ + 0x14,0x78);
	    fVar5 = FLOAT_80331d5c;
	    fVar4 = FLOAT_80331d58;
	    dVar3 = DOUBLE_80331d38;
	    fVar2 = FLOAT_80331d2c;
	    iVar12 = -0x7fcffeb4;
	    iVar13 = 0;
	    iVar15 = 2;
	    do {
	      uVar6 = iVar13 + 3;
	      uVar10 = iVar13 + 4;
	      uVar7 = iVar13 + 5;
	      uVar11 = iVar13 + 7;
	      uVar8 = iVar13 + 6;
	      uVar9 = iVar13 + 8;
	      iVar13 = iVar13 + 6;
	      *(float *)(*(int *)(iVar12 + 0x38) + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      *(float *)(*(int *)(iVar12 + 0x3c) + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      *(float *)(*(int *)(iVar12 + 0x40) + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      *(float *)(*(int *)(iVar12 + 0x44) + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      *(float *)(*(int *)(iVar12 + 0x48) + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar11 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      piVar1 = (int *)(iVar12 + 0x4c);
	      iVar12 = iVar12 + 0x18;
	      *(float *)(*piVar1 + 0x1b4) =
	           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - dVar3)) /
	           fVar5 + FLOAT_8032eea0;
	      iVar15 = iVar15 + -1;
	    } while (iVar15 != 0);
	    FLOAT_8032eea0 = FLOAT_8032eea0 + FLOAT_80331d60;
	  }
	  if (((((int)pvVar14 < 0x88) && (0x84 < (int)pvVar14)) &&
	      (m_boss__8CGMonObj._88_4_ == (int)pvVar14 + -0x85)) &&
	     (((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18) < 0 &&
	      (iVar12 = _getItemPdt__10CGCharaObjFiiRiRiRi(gMonObj), iVar12 != 0)))) {
	    if (m_boss__8CGMonObj._96_4_ == 0) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,100,0,0);
	      gMonObj->_bossBranchRelated = 0;
	    }
	    if (m_boss__8CGMonObj._96_4_ == 2) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x65,0,0);
	      gMonObj->_bossBranchRelated = 2;
	    }
	    if (m_boss__8CGMonObj._96_4_ == 1) {
	      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x66,0,0);
	      gMonObj->_bossBranchRelated = 1;
	    }
	    m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f;
	  }
	  return;
	}
	
	#endif
	CGObject* object = reinterpret_cast<CGObject*>(this);
	if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x85) && ((*reinterpret_cast<unsigned char*>(SoundBuffer + 1356) & 0x40) == 0)) {
		*reinterpret_cast<float*>(SoundBuffer + 1260) += FLOAT_80331d60;
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
	#if 0
	// Function: frameStatFuncMeteoParasite__8CGMonObjFv
	// Entry: 8012fad0
	// Size: 504 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  void *pvVar2;
	  
	  iVar1 = *(int *)&gMonObj->field_0x520;
	  pvVar2 = (gMonObj->gObject).m_scriptHandle[4];
	  if (iVar1 == 0x66) {
	    if (*(int *)&gMonObj->field_0x528 == 0) {
	      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xc,0,0);
	    }
	    else {
	      iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	      if (iVar1 != 0) {
	        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
	        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	      }
	    }
	  }
	  else if (iVar1 < 0x66) {
	    if (iVar1 == 100) {
	      if (*(int *)&gMonObj->field_0x528 == 0) {
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,10,0,0);
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0xb,0);
	          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	        }
	      }
	    }
	    else if (99 < iVar1) {
	      if (*(int *)&gMonObj->field_0x528 == 0) {
	        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xd,0,0);
	      }
	      else {
	        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
	        if (iVar1 != 0) {
	          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0xe,0);
	          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
	        }
	      }
	    }
	  }
	  if ((pvVar2 == (void *)0x87) && (*(int *)&gMonObj->field_0x520 == 0x67)) {
	    iVar1 = *(int *)&gMonObj->field_0x528;
	    if ((0x18 < iVar1) && (iVar1 < 0x32)) {
	      if (iVar1 == 0x19) {
	        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x11d5b,0x32,0x96,0,0);
	      }
	      if (*(int *)&gMonObj->field_0x528 == (*(int *)&gMonObj->field_0x528 / 3) * 3) {
	        putParticleFromItem__10CGCharaObjFiiiP3Vec
	                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,2,
	                   *(undefined4 *)&gMonObj->field_0x564,0);
	      }
	    }
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
		reinterpret_cast<CGCharaObj*>(this)->statAttack();
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
	#if 0
	// Function: logicFuncMeteoParasite__8CGMonObjFv
	// Entry: 8012fa20
	// Size: 176 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void logicFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  int iVar1;
	  
	  iVar1 = -1;
	  if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
	           (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)) < 0) {
	    iVar1 = 0x68;
	  }
	  else if ((((gMonObj->gObject).m_scriptHandle[4] == (void *)0x87) &&
	           (m_boss__8CGMonObj._88_4_ == 2)) && (gMonObj->_bossBranchRelated < 2)) {
	    if (99 < *(int *)(m_boss__8CGMonObj._84_4_ + 0x520)) {
	      return;
	    }
	    if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18) < 0) {
	      return;
	    }
	  }
	  if (iVar1 == -1) {
	    logicFuncDefault__8CGMonObjFv(gMonObj);
	  }
	  else {
	    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar1,0,0);
	  }
	  return;
	}
	
	#endif
	if (*reinterpret_cast<unsigned char*>(SoundBuffer + 1356) & 0x80) {
		changeStat__8CGPrgObjFiii(reinterpret_cast<CGPrgObj*>(this), 0x68, 0, 0);
		return;
	}
	logicFuncDefault__8CGMonObjFv(this);
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
void CGMonObj::attackCheckFuncMeteoParasite(int)
{
	#if 0
	// Function: attackCheckFuncMeteoParasite__8CGMonObjFi
	// Entry: 8012f984
	// Size: 156 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	undefined4 attackCheckFuncMeteoParasite__8CGMonObjFi(CGMonObj *gMonObj)
	
	{
	  void *pvVar1;
	  
	  pvVar1 = (gMonObj->gObject).m_scriptHandle[4];
	  if (pvVar1 == (void *)0x86) {
	    if ((m_boss__8CGMonObj._88_4_ == 1) && (gMonObj->_bossBranchRelated == 1)) {
	      return 0xffffffff;
	    }
	    return 0xfffffffe;
	  }
	  if ((int)pvVar1 < 0x86) {
	    if (0x84 < (int)pvVar1) {
	      return 0xfffffffe;
	    }
	  }
	  else if ((int)pvVar1 < 0x88) {
	    if ((m_boss__8CGMonObj._88_4_ == 2) && (gMonObj->_bossBranchRelated < 2)) {
	      return 0xffffffff;
	    }
	    return 0xfffffffe;
	  }
	  return 0xffffffff;
	}
	
	#endif
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int result = -1;
	if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x86)) {
		result = (*reinterpret_cast<int*>(SoundBuffer + 1348) == 1 && *reinterpret_cast<int*>(mon + 0x6B4) == 1) ? -1 : -2;
	} else if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x85) || object->m_scriptHandle[4] == reinterpret_cast<void*>(0x87)) {
		result = (*reinterpret_cast<int*>(SoundBuffer + 1348) == 2 && *reinterpret_cast<int*>(mon + 0x6B4) < 2) ? -1 : -2;
	}
	*reinterpret_cast<int*>(mon + 0x6C4) = result;
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
void CGMonObj::aiAddDuct(int&)
{
	int seq = 0;
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
	if (slot >= 0 && slot < 8) {
		reinterpret_cast<CGMonObj**>(SoundBuffer + 1400)[slot] = this;
	}
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
	int nextState = -1;
	if (Rand__5CMathFUl(&Math, 3) == 0) {
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
	#if 0
	// Function: frameStatFuncRamoe__8CGMonObjFv
	// Entry: 8012f598
	// Size: 172 bytes
	
	/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */
	
	void frameStatFuncRamoe__8CGMonObjFv(CGMonObj *gMonObj)
	
	{
	  CGMonObj *gMonObj_00;
	  int iVar1;
	  int iVar2;
	  
	  if (*(int *)&gMonObj->field_0x520 == 100) {
	    if (*(int *)&gMonObj->field_0x528 == 0x3a) {
	      iVar1 = 1;
	      iVar2 = -0x7fde113c;
	      do {
	        gMonObj_00 = *(CGMonObj **)(iVar2 + 0xc5d0);
	        if (((gMonObj_00 != (CGMonObj *)0x0) && (*(int *)&gMonObj_00->field_0x520 == 9)) &&
	           (*(int *)&gMonObj_00->field_0x52c == 2)) {
	          setRepop__8CGMonObjFi(gMonObj_00,0);
	        }
	        iVar1 = iVar1 + 1;
	        iVar2 = iVar2 + 4;
	      } while (iVar1 < 0x40);
	    }
	    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
	  }
	  return;
	}
	
	#endif
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	if (prgObj->m_lastStateId >= 100) {
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
	if (prgObj->m_lastStateId == 0x66) {
		for (int i = 0; i < 4; i++) {
			CGPartyObj* party = Game.m_partyObjArr[i];
			if (party != 0) {
				CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
				if (partyPrg->m_lastStateId == 0x25) {
					changeStat__8CGPrgObjFiii(partyPrg, 0x24, 0, 0);
				}
			}
		}
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x400);
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
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = Game.m_partyObjArr[i];
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
			for (int i = 0; i < 4; i++) {
				CGPartyObj* party = Game.m_partyObjArr[i];
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
					dist = (double)(float)(dist * DOUBLE_80331d00 * inv *
					                       -(dist * inv * inv - DOUBLE_80331d08));
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
				dist = (double)(float)(dist * DOUBLE_80331d00 * inv *
				                       -(dist * inv * inv - DOUBLE_80331d08));
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
