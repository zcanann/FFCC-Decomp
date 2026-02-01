// Function: setAlive__10CGPartyObjFii
// Entry: 8011bd30
// Size: 764 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setAlive__10CGPartyObjFii(CGCharaObj *param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  short sVar3;
  void **ppvVar4;
  void *pvVar5;
  
  if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1d | (uint)((byte)param_1->field_0x6b8 >> 3)) < 0)
  {
    ppvVar4 = (param_1->gPrgObj).object.m_scriptHandle;
    if (*(short *)(ppvVar4 + 7) == 0) {
      addHp__10CGCharaObjFiP8CGPrgObj
                (param_1,(uint)*(ushort *)((int)ppvVar4 + 0x1a),(CGPrgObj *)0x0);
    }
    param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
  }
  (**(code **)((int)(param_1->gPrgObj).object.base_object.object.m_vtable + 0x94))(param_1,1);
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
  if (param_2 == 0) {
    if ((param_1->gPrgObj).object.m_currentAnimSlot == '\x06') {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x26,0,0);
    }
    else {
      reqAnim__8CGPrgObjFiii(&param_1->gPrgObj,0x27,0,0);
    }
  }
  if (*(short *)((param_1->gPrgObj).object.m_scriptHandle + 7) == 0) {
    *(float *)&param_1->field_0x694 = FLOAT_80331a7c;
    (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask & 0xfffefff1;
    pvVar5 = (param_1->gPrgObj).object.m_scriptHandle[0xed];
    if ((param_2 == 0) || (param_3 != 0)) {
      endPSlotBit__10CGCharaObjFi(param_1,0x10000);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331a54,&param_1->gPrgObj,(int)pvVar5 + 3U | 0x100,
                 *(int *)&param_1->field_0x5a4,(CGObject *)param_1,0);
    }
    if (param_2 == 0) {
      playSe3D__8CGPrgObjFiiiiP3Vec(&param_1->gPrgObj,0x2d,0x32,0x96,0,0);
    }
  }
  else {
    endPSlotBit__10CGCharaObjFi(param_1,0x10000);
    *(float *)&param_1->field_0x694 = FLOAT_80331a54;
    (param_1->gPrgObj).object.m_bgColMask = (param_1->gPrgObj).object.m_bgColMask | 0x1000e;
    if (param_2 == 0) {
      *(undefined2 *)((param_1->gPrgObj).object.m_scriptHandle + 0x12) = 0x5a;
    }
  }
  return;
}

