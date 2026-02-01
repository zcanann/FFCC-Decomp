// Function: changeStat__8CGPrgObjFiii
// Entry: 80127838
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeStat__8CGPrgObjFiii
               (CGPrgObj *gPrgObj,undefined4 param_2,int32_t param_3,int32_t stateArg)

{
  int iVar1;
  
  iVar1 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x50))();
  if (iVar1 != -1) {
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x54))(gPrgObj,param_2);
    gPrgObj->m_stateArg = stateArg;
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x58))(gPrgObj,param_2);
    gPrgObj->m_lastStateId = iVar1;
    gPrgObj->m_stateFrame = 0;
    gPrgObj->m_stateFrameGate = 1;
    gPrgObj->m_subState = param_3;
    gPrgObj->m_subFrame = 0;
    gPrgObj->m_subFrameGate = 1;
  }
  return;
}

