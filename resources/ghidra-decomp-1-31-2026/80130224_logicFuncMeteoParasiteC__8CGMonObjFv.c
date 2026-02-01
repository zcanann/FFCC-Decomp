// Function: logicFuncMeteoParasiteC__8CGMonObjFv
// Entry: 80130224
// Size: 144 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncMeteoParasiteC__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = -1;
  if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
           (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)) < 0) {
    iVar1 = 0x68;
  }
  else {
    m_boss__8CGMonObj._100_4_ =
         m_boss__8CGMonObj._100_4_ - 1 & ~((int)(m_boss__8CGMonObj._100_4_ - 1) >> 0x1f);
    if (gMonObj->_bossBranchRelated == 0) {
      if (m_boss__8CGMonObj._100_4_ != 0) {
        return;
      }
      iVar1 = 0x65;
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

