// Function: logicFuncLastBoss__8CGMonObjFv
// Entry: 8012ef0c
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncLastBoss__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = -1;
  if ((gMonObj->_bossBranchRelated == 2) &&
     (m_boss__8CGMonObj._4_4_ = m_boss__8CGMonObj._4_4_ + 1, 9 < (int)m_boss__8CGMonObj._4_4_)) {
    gMonObj->_bossBranchRelated = 3;
    iVar1 = 0x65;
    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
    m_boss__8CGMonObj._4_4_ = 0;
  }
  if (iVar1 == -1) {
    logicFuncDefault__8CGMonObjFv(gMonObj);
  }
  else {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar1,0,0);
  }
  return;
}

