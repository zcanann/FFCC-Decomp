// Function: effective__10CGCharaObjFiiP8CGPrgObjRi
// Entry: 8010fd54
// Size: 2172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void effective__10CGCharaObjFiiP8CGPrgObjRi
               (CGCharaObj *gCharaObj,int param_2,int param_3,CGPrgObj *gPrgObj,undefined4 *param_5)

{
  uint uVar1;
  Vec *vecA;
  void **ppvVar2;
  undefined4 uVar3;
  CGCharaObj *pCVar4;
  int iVar5;
  double dVar6;
  Vec local_48;
  CVector CStack_3c;
  CVector CStack_30;
  float local_24;
  float local_20;
  float local_1c;
  
  if (param_2 == 0x1c) {
    uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,0x1c,param_3,gPrgObj);
    setSta__10CGCharaObjFii(gCharaObj,0x1c,uVar3);
  }
  else if (param_2 < 0x1c) {
    if (param_2 != 5) {
      if (param_2 < 5) {
        if (param_2 == 2) {
          uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,2,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,2,uVar3);
        }
        else if (param_2 < 2) {
          if (param_2 == 0) {
            if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x10) == 0) {
              uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,0,param_3,gPrgObj);
              setSta__10CGCharaObjFii(gCharaObj,0,uVar3);
              setSta__10CGCharaObjFii(gCharaObj,4,0);
              StopSe3DGroup__6CSoundFi
                        (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
              iVar5 = 0;
              pCVar4 = gCharaObj;
              do {
                if ((1 << iVar5 & 0x3bU) != 0) {
                  DeleteParticleSlot__13CFlatRuntime2Fii
                            ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar4->field_0x564);
                }
                iVar5 = iVar5 + 1;
                pCVar4 = (CGCharaObj *)&(pCVar4->gPrgObj).object.base_object.object.m_freeListNode;
              } while (iVar5 < 0x16);
              changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
            }
            else {
              setSta__10CGCharaObjFii(gCharaObj,0,0);
              setSta__10CGCharaObjFii(gCharaObj,1,0);
              *param_5 = 0;
            }
          }
          else if (-1 < param_2) {
            if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) == 0) {
              uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,1,param_3,gPrgObj);
              setSta__10CGCharaObjFii(gCharaObj,1,uVar3);
              setSta__10CGCharaObjFii(gCharaObj,4,0);
            }
            else {
              setSta__10CGCharaObjFii(gCharaObj,0,0);
              setSta__10CGCharaObjFii(gCharaObj,1,0);
              *param_5 = 0;
            }
          }
        }
        else if (param_2 < 4) {
          setSta__10CGCharaObjFii(gCharaObj,1,0);
          setSta__10CGCharaObjFii(gCharaObj,0,0);
          setSta__10CGCharaObjFii(gCharaObj,4,0);
          setSta__10CGCharaObjFii(gCharaObj,9,0);
          setSta__10CGCharaObjFii(gCharaObj,7,0);
          setSta__10CGCharaObjFii(gCharaObj,8,0);
          uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,3,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,3,uVar3);
          *param_5 = 0;
          putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
          StopSe3DGroup__6CSoundFi
                    (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
          iVar5 = 0;
          pCVar4 = gCharaObj;
          do {
            if ((1 << iVar5 & 0x3bU) != 0) {
              DeleteParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar4->field_0x564);
            }
            iVar5 = iVar5 + 1;
            pCVar4 = (CGCharaObj *)&(pCVar4->gPrgObj).object.base_object.object.m_freeListNode;
          } while (iVar5 < 0x16);
          changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
        }
        else {
          uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,4,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,4,uVar3);
          setSta__10CGCharaObjFii(gCharaObj,0,0);
          setSta__10CGCharaObjFii(gCharaObj,1,0);
          changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,10,0,0);
        }
      }
      else if (param_2 == 8) {
        if (*(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0x13) == 0) {
          uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,8,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,8,uVar3);
          putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
        }
        else {
          setSta__10CGCharaObjFii(gCharaObj,7,0);
          setSta__10CGCharaObjFii(gCharaObj,8,0);
        }
        *param_5 = 0;
      }
      else if (param_2 < 8) {
        if (param_2 < 7) {
          uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,6,param_3,gPrgObj);
          setSta__10CGCharaObjFii(gCharaObj,6,uVar3);
          *param_5 = 0;
          putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
        }
        else {
          if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x4e) == 0) {
            uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,7,param_3,gPrgObj);
            setSta__10CGCharaObjFii(gCharaObj,7,uVar3);
            putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
          }
          else {
            setSta__10CGCharaObjFii(gCharaObj,7,0);
            setSta__10CGCharaObjFii(gCharaObj,8,0);
          }
          *param_5 = 0;
        }
      }
      else if (param_2 < 10) {
        setSta__10CGCharaObjFii(gCharaObj,7,0);
        setSta__10CGCharaObjFii(gCharaObj,8,0);
        uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,9,param_3,gPrgObj);
        setSta__10CGCharaObjFii(gCharaObj,9,uVar3);
        *param_5 = 0;
        putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
        StopSe3DGroup__6CSoundFi
                  (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
        iVar5 = 0;
        pCVar4 = gCharaObj;
        do {
          if ((1 << iVar5 & 0x3bU) != 0) {
            DeleteParticleSlot__13CFlatRuntime2Fii
                      ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar4->field_0x564);
          }
          iVar5 = iVar5 + 1;
          pCVar4 = (CGCharaObj *)&(pCVar4->gPrgObj).object.base_object.object.m_freeListNode;
        } while (iVar5 < 0x16);
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
      }
    }
  }
  else if (param_2 == 0x66) {
    addHp__10CGCharaObjFiP8CGPrgObj
              (gCharaObj,(uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x1a),
               (CGPrgObj *)0x0);
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x4c))
              (gPrgObj,0x16,param_3,gCharaObj);
    *param_5 = 0;
    putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
  }
  else if (param_2 < 0x66) {
    if (param_2 == 0x25) {
      if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) != 0) {
        setSta__10CGCharaObjFii(gCharaObj,0,0);
      }
      uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                        (gCharaObj);
      if (((uVar1 & 0xad) != 0xad) ||
         ((*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle[9] + 0xfe) & 8) == 0)) {
        __ct__7CVectorFRC3Vec(&CStack_3c,&(gPrgObj->object).m_worldPosition);
        vecA = (Vec *)__ct__7CVectorFRC3Vec(&CStack_30,&(gCharaObj->gPrgObj).object.m_worldPosition)
        ;
        __ct__7CVectorFv(&local_48);
        PSVECSubtract(vecA,(Vec *)&CStack_3c,&local_48);
        local_24 = local_48.x;
        local_20 = local_48.y;
        local_1c = local_48.z;
        moveVectorH__8CGObjectFP3Vecfi((double)FLOAT_803319a8,(CGObject *)gCharaObj,&local_24,8);
        dVar6 = (double)atan2(-(double)local_24,-(double)local_1c);
        (gCharaObj->gPrgObj).object.m_rotTargetY = (float)dVar6;
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x19,0,0);
      }
    }
    else if (param_2 < 0x25) {
      if ((0x23 < param_2) &&
         (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) != 0)) {
        setSta__10CGCharaObjFii(gCharaObj,0,0);
      }
    }
    else if (param_2 == 100) {
      if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) != 0) {
        setSta__10CGCharaObjFii(gCharaObj,0,0);
      }
    }
    else if (99 < param_2) {
      if (Game.game.m_gameWork.m_gameOverFlag == '\0') {
        if (param_3 == 0x225) {
          addHp__10CGCharaObjFiP8CGPrgObj
                    (gCharaObj,
                     (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x1a),
                     (CGPrgObj *)0x0);
        }
        else {
          addHp__10CGCharaObjFiP8CGPrgObj(gCharaObj,8,(CGPrgObj *)0x0);
        }
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x22,0,0);
        putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
      }
      else {
        Printf__7CSystemFPce(&System,&DAT_801dc908);
      }
      *param_5 = 0;
    }
  }
  else if (param_2 == 0x6a) {
    uVar3 = calcSta__10CGCharaObjFiiP8CGObject(gCharaObj,4,param_3,gPrgObj);
    setSta__10CGCharaObjFii(gCharaObj,4,uVar3);
    setSta__10CGCharaObjFii(gCharaObj,0,0);
    setSta__10CGCharaObjFii(gCharaObj,1,0);
    changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,10,0,0);
  }
  else if (param_2 < 0x6a) {
    if (param_2 != 0x68) {
      if (param_2 < 0x68) {
        iVar5 = 0;
        do {
          setSta__10CGCharaObjFii(gCharaObj,iVar5,0);
          iVar5 = iVar5 + 1;
        } while (iVar5 < 0x27);
        (gCharaObj->gPrgObj).object.m_displayFlags = (gCharaObj->gPrgObj).object.m_displayFlags | 2;
        putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(gCharaObj,gPrgObj,param_3);
      }
      else {
        if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e) != 0) {
          setSta__10CGCharaObjFii(gCharaObj,0,0);
        }
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,4,0,0);
      }
    }
  }
  else if (param_2 < 0x6c) {
    if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x46) != 0) {
      setSta__10CGCharaObjFii(gCharaObj,4,0);
    }
    ppvVar2 = (gCharaObj->gPrgObj).object.m_scriptHandle;
    if (((*(short *)((int)ppvVar2 + 0x3e) == 0) && (*(short *)(ppvVar2 + 0x14) == 0)) &&
       (*(short *)(ppvVar2 + 0x11) == 0)) {
      changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1a,0,0);
    }
  }
  return;
}

