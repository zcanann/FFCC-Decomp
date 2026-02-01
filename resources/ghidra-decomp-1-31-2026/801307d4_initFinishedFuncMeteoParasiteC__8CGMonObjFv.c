// Function: initFinishedFuncMeteoParasiteC__8CGMonObjFv
// Entry: 801307d4
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void initFinishedFuncMeteoParasiteC__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  initFinishedFuncDefault__8CGMonObjFv(gMonObj);
  m_boss__8CGMonObj._84_4_ = gMonObj;
  iVar1 = strcmp(0x8022b6b4,&DAT_80331d64);
  if (iVar1 == 0) {
    m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0xbf | 0x40;
    m_boss__8CGMonObj._88_4_ = 3;
    *(undefined2 *)((gMonObj->gObject).m_scriptHandle + 7) = 1;
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x35,0);
    reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x35,1,0);
    PlayAnim__8CGObjectFiiiiiPSc(&gMonObj->gObject,0x35,1,0,0xffff,0xffff,0);
  }
  return;
}

