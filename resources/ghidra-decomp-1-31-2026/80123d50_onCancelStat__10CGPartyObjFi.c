// Function: onCancelStat__10CGPartyObjFi
// Entry: 80123d50
// Size: 2032 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCancelStat__10CGPartyObjFi(CGCharaObj *param_1,int param_2)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  ushort uVar13;
  void **ppvVar14;
  uint32_t *puVar15;
  
  switch((param_1->gPrgObj).m_lastStateId) {
  case 2:
    param_1->field_0x6b8 = param_1->field_0x6b8 & 0xbf;
    param_1->field_0x6b8 = param_1->field_0x6b8 & 0xdf;
    endPSlotBit__10CGCharaObjFi(param_1,0x10);
    endPSlotBit__10CGCharaObjFi(param_1,0x100);
    break;
  case 6:
    *(float *)(param_1->gPrgObj).object.m_worldMode = FLOAT_80331a78;
    break;
  case 9:
    if (param_2 != 0x22) {
      if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1d | (uint)((byte)param_1->field_0x6b8 >> 3))
          < 0) {
        ppvVar14 = (param_1->gPrgObj).object.m_scriptHandle;
        if (*(short *)(ppvVar14 + 7) == 0) {
          addHp__10CGCharaObjFiP8CGPrgObj
                    (param_1,(uint)*(ushort *)((int)ppvVar14 + 0x1a),(CGPrgObj *)0x0);
        }
        param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
      }
      (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
      if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
        if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
          sVar9._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar9._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar9 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
          }
        }
        else {
          sVar8._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
          sVar8._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
          if (sVar8 == 1) {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
          }
          else {
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
            SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
          }
        }
      }
      else if (CFlat._4780_4_ == 0) {
        sVar7._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar7._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar7 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
        }
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
        *(float *)&param_1->field_0x694 = FLOAT_80331a7c;
        (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask & 0xfffefff1;
      }
      else {
        endPSlotBit__10CGCharaObjFi(param_1,0x10000);
        *(float *)&param_1->field_0x694 = FLOAT_80331a54;
        (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask | 0x1000e;
      }
    }
    break;
  case 0xb:
    if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
      if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
        sVar3._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar3._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar3 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
      }
      else {
        sVar2._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar2._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar2 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar1._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
      sVar1._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
      if (sVar1 == 1) {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
    }
    break;
  case 0xc:
  case 0xd:
    if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
      if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
        sVar6._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar6._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar6 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
      }
      else {
        sVar5._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar5._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar5 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar4._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
      sVar4._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
      if (sVar4 == 1) {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
    }
    break;
  case 0xf:
    if ((int)((uint)(byte)param_1->field_0x6c4 << 0x1a | (uint)((byte)param_1->field_0x6c4 >> 6)) <
        0) {
      ppvVar14 = param_1[1].gPrgObj.object.base_object.object.m_freeListNode;
      puVar15 = (uint32_t *)param_1[1].gPrgObj.object.base_object.object.m_id;
      if ((int)ppvVar14 < 1) {
        LoadWeapon__8CGObjectFii((CGObject *)param_1,0xffffffff,0);
      }
      else {
        uVar13 = *(ushort *)(Game.game.unkCFlatData0[2] + (int)ppvVar14 * 0x48 + 2);
        LoadWeapon__8CGObjectFii((CGObject *)param_1,uVar13 & 0xfff,(int)(uint)uVar13 >> 0xc);
      }
      param_1[1].gPrgObj.object.base_object.object.m_stackPointer = puVar15;
      param_1[1].gPrgObj.object.base_object.object.m_localBase = (uint32_t *)ppvVar14;
      SetCurrentWeaponIdx__12CCaravanWorkFi
                ((CCaravanWork *)(param_1->gPrgObj).object.m_scriptHandle,
                 (int)param_1[1].gPrgObj.object.base_object.object.m_stackPointer);
      param_1->field_0x6c4 = param_1->field_0x6c4 & 0xdf;
    }
    break;
  case 0x14:
    *(float *)&param_1->field_0x694 = FLOAT_80331a54;
    (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
    break;
  case 0x15:
    (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
    break;
  case 0x22:
    if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1d | (uint)((byte)param_1->field_0x6b8 >> 3)) <
        0) {
      ppvVar14 = (param_1->gPrgObj).object.m_scriptHandle;
      if (*(short *)(ppvVar14 + 7) == 0) {
        addHp__10CGCharaObjFiP8CGPrgObj
                  (param_1,(uint)*(ushort *)((int)ppvVar14 + 0x1a),(CGPrgObj *)0x0);
      }
      param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
    }
    (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
    if (param_1[1].gPrgObj.object.base_object.object.m_codePos == 0) {
      if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
        sVar12._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar12._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar12 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x24,1);
        }
      }
      else {
        sVar11._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
        sVar11._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
        if (sVar11 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)param_1,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar10._0_1_ = (param_1->gPrgObj).object.m_lastMapIdHit;
      sVar10._1_1_ = (param_1->gPrgObj).object.m_lastMapIdExtra;
      if (sVar10 == 1) {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)param_1,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xb,0);
      SetAnimSlot__8CGObjectFii((CGObject *)param_1,0xc,1);
    }
    if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
      *(float *)&param_1->field_0x694 = FLOAT_80331a7c;
      (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask & 0xfffefff1;
    }
    else {
      endPSlotBit__10CGCharaObjFi(param_1,0x10000);
      *(float *)&param_1->field_0x694 = FLOAT_80331a54;
      (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask | 0x1000e;
    }
  }
  onCancelStat__10CGCharaObjFi(param_1,param_2);
  return;
}

