// Function: onFrame__8CGPrgObjFv
// Entry: 801278dc
// Size: 500 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrame__8CGPrgObjFv(CGPrgObj *gPrgObj)

{
  byte bVar1;
  uint uVar2;
  
  (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x68))();
  if ((int)((uint)*(byte *)&(gPrgObj->object).m_weaponNodeFlags << 0x18) < 0) {
    uVar2 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
    if (((uVar2 & 0x2d) == 0x2d) && (PartPcs.m_usbStreamData.m_blockOnFrame != '\0')) {
      return;
    }
    gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0x7f;
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x5c))(gPrgObj);
    if (gPrgObj->m_stateFrameGate == 0) {
      gPrgObj->m_stateFrame = gPrgObj->m_stateFrame + 1;
    }
    else {
      gPrgObj->m_stateFrameGate = 0;
    }
    if (gPrgObj->m_subFrameGate == 0) {
      gPrgObj->m_subFrame = gPrgObj->m_subFrame + 1;
    }
    else {
      gPrgObj->m_subFrameGate = 0;
    }
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 100))(gPrgObj);
    (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x60))(gPrgObj);
    bVar1 = gPrgObj->m_animFlags;
    if ((int)((uint)bVar1 << 0x18) < 0) {
      if (gPrgObj->m_reqAnimId == -1) {
        if (-1 < (gPrgObj->object).m_currentAnimSlot) {
          *(float *)(gPrgObj->object).m_lastBgAttr = FLOAT_80331bd0;
          CancelAnim__8CGObjectFi(&gPrgObj->object,0);
        }
      }
      else if ((int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0) {
        *(float *)(gPrgObj->object).m_lastBgAttr = FLOAT_80331be8;
        PlayAnim__8CGObjectFiiiiiPSc
                  (&gPrgObj->object,gPrgObj->m_reqAnimId,
                   (char)((int)((uint)gPrgObj->m_animFlags << 0x19) >> 0x1f),0,0xffff,0xffff,0);
      }
      else {
        *(float *)(gPrgObj->object).m_lastBgAttr = FLOAT_80331bd0;
        PlayAnim__8CGObjectFiiiiiPSc
                  (&gPrgObj->object,gPrgObj->m_reqAnimId,
                   (char)((int)((uint)gPrgObj->m_animFlags << 0x19) >> 0x1f),0,0xffff,0xffff,0);
      }
      gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0x7f;
    }
  }
  (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0x6c))(gPrgObj);
  return;
}

