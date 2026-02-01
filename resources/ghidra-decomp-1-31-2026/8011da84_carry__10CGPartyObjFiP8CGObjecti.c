// Function: carry__10CGPartyObjFiP8CGObjecti
// Entry: 8011da84
// Size: 1620 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void carry__10CGPartyObjFiP8CGObjecti
               (CGPartyObj *gPartyObj,int param_2,CGObject *gObject,int param_4)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  ushort uVar8;
  bool bVar9;
  uint uVar10;
  bool bVar11;
  void **ppvVar12;
  
  if (param_2 == 0) {
    bVar1 = *(int *)&gPartyObj->field_0x6f0 != 0;
    if ((bVar1) && (bVar1)) {
      if ((gPartyObj->gCharaObj).gPrgObj.m_lastStateId == 0xb) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)gPartyObj,0,0,0);
      }
      carry__9CGItemObjFP10CGPartyObjii(*(CGItemObj **)&gPartyObj->field_0x6f0,gPartyObj,1,0);
      *(undefined4 *)&gPartyObj->field_0x6f0 = 0;
      setIdleMotion__10CGPartyObjFv(gPartyObj);
    }
    if (param_4 == 0) {
      *(CGObject **)&gPartyObj->field_0x6f0 = gObject;
      rotTarget__8CGPrgObjFP8CGPrgObj((CGPrgObj *)gPartyObj,*(CGPrgObj **)&gPartyObj->field_0x6f0);
      changeStat__8CGPrgObjFiii((CGPrgObj *)gPartyObj,0xb,0,0);
      bVar9 = false;
      bVar1 = false;
      bVar11 = false;
      if (Game.game.m_gameWork.m_menuStageMode != '\0') {
        if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
          bVar11 = true;
        }
      }
      if (bVar11) {
        uVar10 = (**(code **)((int)(gPartyObj->gCharaObj).gPrgObj.object.base_object.object.m_vtable
                             + 0xc))(gPartyObj);
        uVar10 = countLeadingZeros(0x6d - (uVar10 & 0x6d));
        if ((uVar10 >> 5 & 0xff) != 0) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        if ((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] != (void *)0x0) {
          bVar9 = true;
        }
      }
      if (bVar9) {
        uVar10 = 5;
      }
      else {
        if (CFlat._4780_4_ == 1) {
          ppvVar12 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
          uVar8 = *(ushort *)
                   (Game.game.unk_flat3_field_30_0xc7e0 +
                    ((uint)*(ushort *)((int)ppvVar12 + 0x3e2) +
                    (uint)*(ushort *)(ppvVar12 + 0xf8) * 2) * 0x1ca + 0x1c6);
        }
        else {
          ppvVar12 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
          uVar8 = *(ushort *)
                   (Game.game.unk_flat3_field_30_0xc7e0 +
                    ((uint)*(ushort *)((int)ppvVar12 + 0x3e2) +
                    (uint)*(ushort *)(ppvVar12 + 0xf8) * 2) * 0x1ca + 0x1c2);
        }
        uVar10 = (uint)uVar8;
      }
      carry__9CGItemObjFP10CGPartyObjii(*(CGItemObj **)&gPartyObj->field_0x6f0,gPartyObj,0,uVar10);
    }
    else {
      *(CGObject **)&gPartyObj->field_0x6f0 = gObject;
      if (*(int *)&gPartyObj->field_0x6f0 == 0) {
        if (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) {
          sVar4._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
          sVar4._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
          if (sVar4 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x24,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x24,1);
          }
        }
        else {
          sVar3._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
          sVar3._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
          if (sVar3 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,1,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x30,1);
          }
        }
      }
      else if (CFlat._4780_4_ == 0) {
        sVar2._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar2._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar2 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xc,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,2,1);
        }
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xc,1);
      }
      carry__9CGItemObjFP10CGPartyObjii(*(CGItemObj **)&gPartyObj->field_0x6f0,gPartyObj,0,0);
    }
  }
  else if (((param_2 == 1) || (param_2 == 2)) && (*(int *)&gPartyObj->field_0x6f0 != 0)) {
    if (param_4 == 0) {
      changeStat__8CGPrgObjFiii
                ((CGPrgObj *)gPartyObj,((int)~(param_2 - 1U | 1U - param_2) >> 0x1f) + 0xd,0,0);
      bVar9 = false;
      bVar1 = false;
      bVar11 = false;
      if (Game.game.m_gameWork.m_menuStageMode != '\0') {
        if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
          bVar11 = true;
        }
      }
      if (bVar11) {
        uVar10 = (**(code **)((int)(gPartyObj->gCharaObj).gPrgObj.object.base_object.object.m_vtable
                             + 0xc))(gPartyObj);
        uVar10 = countLeadingZeros(0x6d - (uVar10 & 0x6d));
        if ((uVar10 >> 5 & 0xff) != 0) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        if ((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] != (void *)0x0) {
          bVar9 = true;
        }
      }
      if (bVar9) {
        uVar10 = 5;
      }
      else {
        if (CFlat._4780_4_ == 1) {
          ppvVar12 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
          uVar8 = *(ushort *)
                   (Game.game.unk_flat3_field_30_0xc7e0 +
                    ((uint)*(ushort *)((int)ppvVar12 + 0x3e2) +
                    (uint)*(ushort *)(ppvVar12 + 0xf8) * 2) * 0x1ca + 0x1c8);
        }
        else {
          ppvVar12 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
          uVar8 = *(ushort *)
                   (Game.game.unk_flat3_field_30_0xc7e0 +
                    ((uint)*(ushort *)((int)ppvVar12 + 0x3e2) +
                    (uint)*(ushort *)(ppvVar12 + 0xf8) * 2) * 0x1ca + 0x1c4);
        }
        uVar10 = (uint)uVar8;
      }
      carry__9CGItemObjFP10CGPartyObjii
                (*(CGItemObj **)&gPartyObj->field_0x6f0,gPartyObj,param_2,uVar10);
      *(undefined4 *)&gPartyObj->field_0x6f0 = 0;
    }
    else {
      if ((gPartyObj->gCharaObj).gPrgObj.m_lastStateId == 0xb) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)gPartyObj,0,0,0);
      }
      carry__9CGItemObjFP10CGPartyObjii(*(CGItemObj **)&gPartyObj->field_0x6f0,gPartyObj,param_2,0);
      *(undefined4 *)&gPartyObj->field_0x6f0 = 0;
      if (*(int *)&gPartyObj->field_0x6f0 == 0) {
        if (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) {
          sVar7._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
          sVar7._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
          if (sVar7 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x24,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x24,1);
          }
        }
        else {
          sVar6._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
          sVar6._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
          if (sVar6 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,1,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0x30,1);
          }
        }
      }
      else if (CFlat._4780_4_ == 0) {
        sVar5._0_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar5._1_1_ = (gPartyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar5 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xc,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,2,1);
        }
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)gPartyObj,0xc,1);
      }
    }
  }
  return;
}

