// Function: carry__9CGItemObjFP10CGPartyObjii
// Entry: 80125650
// Size: 916 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void carry__9CGItemObjFP10CGPartyObjii(CGItemObj *gItemObj,int param_2,uint param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  float fVar3;
  uint uVar4;
  Vec *vec;
  bool bVar5;
  bool bVar6;
  char *pcVar7;
  int unaff_r28;
  double dVar8;
  float local_48;
  float local_44;
  float local_40;
  CVector CStack_3c;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  
  if (param_3 == 0) {
    unaff_r28 = 0;
    bVar6 = false;
    bVar1 = false;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
        bVar1 = true;
      }
    }
    if (bVar1) {
      uVar4 = (**(code **)(*(int *)(param_2 + 0x48) + 0xc))(param_2);
      uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
      if ((uVar4 >> 5 & 0xff) != 0) {
        bVar6 = true;
      }
    }
    if ((bVar6) && (*(int *)(*(int *)(param_2 + 0x58) + 0x3b4) != 0)) {
      unaff_r28 = 1;
    }
    *(int *)&gItemObj->field_0x550 = param_2;
    *(int *)&gItemObj->field_0x554 = param_4;
    if (param_4 == 0) {
      vec = (Vec *)__ct__7CVectorFfff(FLOAT_80331b20,FLOAT_80331b20,FLOAT_80331b20,&CStack_3c);
      bVar1 = false;
      if (Game.game.m_gameWork.m_menuStageMode != '\0') {
        bVar2 = false;
        bVar6 = false;
        bVar5 = false;
        if (Game.game.m_gameWork.m_menuStageMode != '\0') {
          if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
            bVar5 = true;
          }
        }
        if (bVar5) {
          uVar4 = (**(code **)(*(int *)(param_2 + 0x48) + 0xc))(param_2);
          uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
          if ((uVar4 >> 5 & 0xff) != 0) {
            bVar6 = true;
          }
        }
        if (bVar6) {
          if (*(int *)(*(int *)(param_2 + 0x58) + 0x3b4) != 0) {
            bVar2 = true;
          }
        }
        if (bVar2) {
          bVar1 = true;
        }
      }
      pcVar7 = &DAT_80331b84;
      if (bVar1) {
        pcVar7 = &DAT_80331b7c;
      }
      Attach__8CGObjectFP8CGObjectPcP3Vec((CGObject *)gItemObj,param_2,pcVar7,vec);
      changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0,0,0);
      (gItemObj->prgObj).object.m_bodyEllipsoidRadius = FLOAT_80331b20;
    }
    else {
      changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0xb,0,0);
    }
  }
  else if ((param_3 == 1) || (param_3 == 2)) {
    unaff_r28 = 0;
    bVar1 = false;
    bVar6 = false;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
        bVar6 = true;
      }
    }
    if (bVar6) {
      uVar4 = (**(code **)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x48) + 0xc))();
      uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
      if ((uVar4 >> 5 & 0xff) != 0) {
        bVar1 = true;
      }
    }
    if ((bVar1) && (*(int *)(*(int *)(*(int *)&gItemObj->field_0x550 + 0x58) + 0x3b4) != 0)) {
      unaff_r28 = 1;
    }
    *(int *)&gItemObj->field_0x554 = param_4;
    if (param_4 == 0) {
      dVar8 = (double)CalcSafePos__8CGObjectFiP8CGObjectP3Vec
                                ((CGObject *)gItemObj,0x41,*(CGObject **)&gItemObj->field_0x550,
                                 &local_48);
      if ((double)FLOAT_80331b20 < dVar8) {
        moveVectorHRot__8CGObjectFfffi
                  ((double)(FLOAT_80331b8c + (*(CGObject **)&gItemObj->field_0x550)->m_rotBaseY),
                   (double)FLOAT_80331b20,(double)(float)(dVar8 / (double)FLOAT_80331b90),
                   *(CGObject **)&gItemObj->field_0x550,3);
      }
      Detach__8CGObjectFv((CGObject *)gItemObj);
      (gItemObj->prgObj).object.m_worldPosition.x = local_48;
      (gItemObj->prgObj).object.m_worldPosition.y = local_44;
      (gItemObj->prgObj).object.m_worldPosition.z = local_40;
      *(undefined4 *)&gItemObj->field_0x550 = 0;
      changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0,0,0);
      fVar3 = FLOAT_80331b20;
      *(undefined4 *)&gItemObj->field_0x56c = 8;
      (gItemObj->prgObj).object.m_bodyEllipsoidRadius = fVar3;
    }
    else {
      changeStat__8CGPrgObjFiii
                (&gItemObj->prgObj,((int)~(param_3 - 1 | 1 - param_3) >> 0x1f) + 0xd,0,0);
    }
    (gItemObj->prgObj).object.m_moveAnimState = '\0';
    (gItemObj->prgObj).object.m_moveAnimSubState = '\0';
    (gItemObj->prgObj).object.m_randSeedLo = '\x11';
    (gItemObj->prgObj).object.m_randSeedHi = 0x94;
  }
  if ((((gItemObj->prgObj).object.m_objectFlags & 0x10) != 0) && (unaff_r28 != 0)) {
    local_30 = 3;
    local_2c = (-param_3 | param_3) >> 0x1f;
    local_28 = 0;
    SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
              (&CFlat,0,1,9,3,&local_30,(CStack *)0x0);
  }
  return;
}

