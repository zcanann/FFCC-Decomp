// Function: ClassControl__8CGPrgObjFii
// Entry: 80127084
// Size: 348 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ClassControl__8CGPrgObjFii(CGPrgObj *gPrgObj,undefined4 param_2,uint32_t *param_3)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    ChangeCommandMode__10CGPartyObjFi((CGPartyObj *)gPrgObj,param_3);
    break;
  case 1:
    changeMotionMode__10CGPartyObjFi((CGPartyObj *)gPrgObj,param_3);
    break;
  case 2:
    if ((uint32_t *)((int)((uint)*(byte *)&(gPrgObj->object).m_weaponNodeFlags << 0x18) >> 0x1f) !=
        param_3) {
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x70))(gPrgObj,param_3);
      *(byte *)&(gPrgObj->object).m_weaponNodeFlags =
           (byte)((int)(char)param_3 << 7) | *(byte *)&(gPrgObj->object).m_weaponNodeFlags & 0x7f;
    }
    break;
  case 3:
    *(byte *)&gPrgObj[1].object.unk_0x168 =
         (byte)((int)(char)param_3 << 3) & 8 | *(byte *)&gPrgObj[1].object.unk_0x168 & 0xf7;
    break;
  case 4:
    iVar1 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x50))
                      (gPrgObj,param_3);
    if (iVar1 != -1) {
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x54))(gPrgObj,param_3);
      gPrgObj->m_stateArg = 0;
      (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x58))(gPrgObj,param_3);
      gPrgObj->m_lastStateId = iVar1;
      gPrgObj->m_stateFrame = 0;
      gPrgObj->m_stateFrameGate = 1;
      gPrgObj->m_subState = 0;
      gPrgObj->m_subFrame = 0;
      gPrgObj->m_subFrameGate = 1;
    }
    break;
  case 5:
    ClearAllSta__10CGCharaObjFv();
    break;
  case 6:
    gPrgObj[1].object.base_object.object.m_thisBase = param_3;
    break;
  case 7:
    setAlive__10CGPartyObjFii(gPrgObj,1,0);
  }
  return;
}

