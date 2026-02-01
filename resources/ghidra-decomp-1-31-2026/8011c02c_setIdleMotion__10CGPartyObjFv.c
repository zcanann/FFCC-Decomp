// Function: setIdleMotion__10CGPartyObjFv
// Entry: 8011c02c
// Size: 344 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setIdleMotion__10CGPartyObjFv(CGObject *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  
  if (param_1[1].m_turnFrames == 0) {
    if (*(short *)(param_1->m_scriptHandle + 7) == 0) {
      sVar3._0_1_ = param_1->m_lastMapIdHit;
      sVar3._1_1_ = param_1->m_lastMapIdExtra;
      if (sVar3 == 1) {
        SetAnimSlot__8CGObjectFii(param_1,0x25,0);
        SetAnimSlot__8CGObjectFii(param_1,0x24,1);
      }
      else {
        SetAnimSlot__8CGObjectFii(param_1,0x25,0);
        SetAnimSlot__8CGObjectFii(param_1,0x24,1);
      }
    }
    else {
      sVar2._0_1_ = param_1->m_lastMapIdHit;
      sVar2._1_1_ = param_1->m_lastMapIdExtra;
      if (sVar2 == 1) {
        SetAnimSlot__8CGObjectFii(param_1,0,0);
        SetAnimSlot__8CGObjectFii(param_1,1,1);
      }
      else {
        SetAnimSlot__8CGObjectFii(param_1,0x25,0);
        SetAnimSlot__8CGObjectFii(param_1,0x30,1);
      }
    }
  }
  else if (CFlat._4780_4_ == 0) {
    sVar1._0_1_ = param_1->m_lastMapIdHit;
    sVar1._1_1_ = param_1->m_lastMapIdExtra;
    if (sVar1 == 1) {
      SetAnimSlot__8CGObjectFii(param_1,0xb,0);
      SetAnimSlot__8CGObjectFii(param_1,0xc,1);
    }
    else {
      SetAnimSlot__8CGObjectFii(param_1,0xb,0);
      SetAnimSlot__8CGObjectFii(param_1,2,1);
    }
  }
  else {
    SetAnimSlot__8CGObjectFii(param_1,0xb,0);
    SetAnimSlot__8CGObjectFii(param_1,0xc,1);
  }
  return;
}

