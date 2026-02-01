// Function: statPut__10CGPartyObjFv
// Entry: 8011d710
// Size: 884 bytes

/* WARNING: Removing unreachable block (ram,0x8011da5c) */
/* WARNING: Removing unreachable block (ram,0x8011d720) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void statPut__10CGPartyObjFv(CGPrgObj *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  uint32_t uVar5;
  int iVar6;
  uint uVar7;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  double dVar8;
  double dVar9;
  double dVar10;
  
  if ((((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
      (uVar7 = (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0xc))(),
      uVar5 = Game.game.unk_flat3_0xc7d0, (uVar7 & 0x6d) == 0x6d)) &&
     ((param_1->object).m_scriptHandle[0xed] != (void *)0x0)) {
    if (param_1->m_stateFrame == 0) {
      CancelMove__8CGObjectFi(&param_1->object,1);
      FLOAT_8032ee80 = FLOAT_80331ab0;
      FLOAT_8032ee84 = *(float *)(uVar5 + 0x160) - (param_1->object).m_worldPosition.y;
    }
    if (param_1->m_stateFrame < 0xc) {
      dVar8 = (double)sin((double)((FLOAT_80331ab8 *
                                   (float)((double)CONCAT44(0x43300000,
                                                            param_1->m_stateFrame ^ 0x80000000) -
                                          DOUBLE_80331a60)) / FLOAT_80331ac0));
      dVar10 = (double)(float)dVar8;
      dVar8 = (double)sin((double)(param_1->object).m_rotBaseY);
      (param_1->object).m_extraMoveVec.x = FLOAT_8032ee80 * (float)(dVar10 * (double)(float)dVar8);
      dVar9 = (double)cos((double)(param_1->object).m_rotBaseY);
      dVar8 = (double)FLOAT_80331a98;
      (param_1->object).m_extraMoveVec.z = FLOAT_8032ee80 * (float)(dVar10 * (double)(float)dVar9);
      (param_1->object).m_extraMoveVec.y = (float)((double)FLOAT_8032ee84 * dVar10 + dVar8);
    }
  }
  if (param_1->m_stateFrame == 0) {
    iVar6 = param_1->m_lastStateId;
    if (iVar6 == 0xd) {
      unaff_r30 = 0x19;
      unaff_r31 = 0x24;
    }
    else if (iVar6 < 0xd) {
      if (0xb < iVar6) {
        unaff_r30 = 0xe;
        unaff_r31 = 0x23;
      }
    }
    else if (iVar6 == 0x1b) {
      sVar1._0_1_ = (param_1->object).m_lastMapIdHit;
      sVar1._1_1_ = (param_1->object).m_lastMapIdExtra;
      unaff_r30 = 9;
      if (sVar1 == 1) {
        unaff_r30 = 0x28;
      }
      unaff_r31 = 0x24;
    }
    reqAnim__8CGPrgObjFiii(param_1,unaff_r30,0,0);
    playSe3D__8CGPrgObjFiiiiP3Vec(param_1,unaff_r31,0x32,0x96,0,0);
  }
  iVar6 = isLoopAnim__8CGPrgObjFv(param_1);
  if (iVar6 != 0) {
    if (param_1[1].object.m_moveBaseSpeed == 0.0) {
      if (*(short *)((param_1->object).m_scriptHandle + 7) == 0) {
        sVar4._0_1_ = (param_1->object).m_lastMapIdHit;
        sVar4._1_1_ = (param_1->object).m_lastMapIdExtra;
        if (sVar4 == 1) {
          SetAnimSlot__8CGObjectFii(&param_1->object,0x25,0);
          SetAnimSlot__8CGObjectFii(&param_1->object,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii(&param_1->object,0x25,0);
          SetAnimSlot__8CGObjectFii(&param_1->object,0x24,1);
        }
      }
      else {
        sVar3._0_1_ = (param_1->object).m_lastMapIdHit;
        sVar3._1_1_ = (param_1->object).m_lastMapIdExtra;
        if (sVar3 == 1) {
          SetAnimSlot__8CGObjectFii(&param_1->object,0,0);
          SetAnimSlot__8CGObjectFii(&param_1->object,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii(&param_1->object,0x25,0);
          SetAnimSlot__8CGObjectFii(&param_1->object,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar2._0_1_ = (param_1->object).m_lastMapIdHit;
      sVar2._1_1_ = (param_1->object).m_lastMapIdExtra;
      if (sVar2 == 1) {
        SetAnimSlot__8CGObjectFii(&param_1->object,0xb,0);
        SetAnimSlot__8CGObjectFii(&param_1->object,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii(&param_1->object,0xb,0);
        SetAnimSlot__8CGObjectFii(&param_1->object,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii(&param_1->object,0xb,0);
      SetAnimSlot__8CGObjectFii(&param_1->object,0xc,1);
    }
    changeStat__8CGPrgObjFiii(param_1,0,0,0);
  }
  return;
}

