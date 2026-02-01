// Function: logicFuncMeteoParasite__8CGMonObjFv
// Entry: 8012fa20
// Size: 176 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = -1;
  if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
           (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)) < 0) {
    iVar1 = 0x68;
  }
  else if ((((gMonObj->gObject).m_scriptHandle[4] == (void *)0x87) &&
           (m_boss__8CGMonObj._88_4_ == 2)) && (gMonObj->_bossBranchRelated < 2)) {
    if (99 < *(int *)(m_boss__8CGMonObj._84_4_ + 0x520)) {
      return;
    }
    if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18) < 0) {
      return;
    }
  }
  if (iVar1 == -1) {
    logicFuncDefault__8CGMonObjFv(gMonObj);
  }
  else {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar1,0,0);
  }
  return;
}

