// Function: changeMotionMode__10CGPartyObjFi
// Entry: 8011c184
// Size: 1048 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeMotionMode__10CGPartyObjFi(CGPartyObj *partyObj,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  void **ppvVar9;
  void *pvVar10;
  
  sVar2._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
  sVar2._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
  if (sVar2 != param_2) {
    (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit = (char)((ushort)(short)param_2 >> 8);
    (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra = (char)(short)param_2;
    changeStat__8CGPrgObjFiii((CGPrgObj *)partyObj,0,0,0);
    if (*(int *)&partyObj->field_0x6f0 == 0) {
      if (*(short *)((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) {
        sVar5._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar5._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar5 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x24,1);
        }
      }
      else {
        sVar4._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar4._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar4 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar3._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
      sVar3._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
      if (sVar3 == 1) {
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
      SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xc,1);
    }
    CancelAnim__8CGObjectFi((CGObject *)partyObj,1);
    bVar1 = (partyObj->gCharaObj).field_0x6b8;
    if ((int)((uint)bVar1 << 0x1d | (uint)(bVar1 >> 3)) < 0) {
      ppvVar9 = (partyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
      if (*(short *)(ppvVar9 + 7) == 0) {
        addHp__10CGCharaObjFiP8CGPrgObj
                  (&partyObj->gCharaObj,(uint)*(ushort *)((int)ppvVar9 + 0x1a),(CGPrgObj *)0x0);
      }
      (partyObj->gCharaObj).field_0x6b8 = (partyObj->gCharaObj).field_0x6b8 & 0xfb;
    }
    (**(code **)((int)(partyObj->gCharaObj).gPrgObj.object.base_object.object.m_vtable + 0x94))
              (partyObj,1);
    if (*(int *)&partyObj->field_0x6f0 == 0) {
      if (*(short *)((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) {
        sVar8._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar8._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar8 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x24,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x24,1);
        }
      }
      else {
        sVar7._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
        sVar7._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
        if (sVar7 == 1) {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,1,1);
        }
        else {
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x25,0);
          SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0x30,1);
        }
      }
    }
    else if (CFlat._4780_4_ == 0) {
      sVar6._0_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdHit;
      sVar6._1_1_ = (partyObj->gCharaObj).gPrgObj.object.m_lastMapIdExtra;
      if (sVar6 == 1) {
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xc,1);
      }
      else {
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
        SetAnimSlot__8CGObjectFii((CGObject *)partyObj,2,1);
      }
    }
    else {
      SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xb,0);
      SetAnimSlot__8CGObjectFii((CGObject *)partyObj,0xc,1);
    }
    if (*(short *)((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) {
      *(float *)&(partyObj->gCharaObj).field_0x694 = FLOAT_80331a7c;
      (partyObj->gCharaObj).gPrgObj.object.m_bgColMask =
           (partyObj->gCharaObj).gPrgObj.object.m_bgColMask & 0xfffefff1;
      pvVar10 = (partyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed];
      endPSlotBit__10CGCharaObjFi(partyObj,0x10000);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331a54,(CGPrgObj *)partyObj,(int)pvVar10 + 3U | 0x100,
                 *(int *)&(partyObj->gCharaObj).field_0x5a4,(CGObject *)partyObj,0);
    }
    else {
      endPSlotBit__10CGCharaObjFi(partyObj,0x10000);
      *(float *)&(partyObj->gCharaObj).field_0x694 = FLOAT_80331a54;
      (partyObj->gCharaObj).gPrgObj.object.m_bgColMask =
           (partyObj->gCharaObj).gPrgObj.object.m_bgColMask | 0x1000e;
    }
    if (((param_2 == 1) && (*(int *)&partyObj->field_0x6f0 == 0)) &&
       (*(short *)((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)) {
      (partyObj->gCharaObj).field_0x6b8 = (partyObj->gCharaObj).field_0x6b8 & 0xfd | 2;
    }
  }
  return;
}

