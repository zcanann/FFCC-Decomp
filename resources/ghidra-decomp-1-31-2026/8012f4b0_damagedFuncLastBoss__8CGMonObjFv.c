// Function: damagedFuncLastBoss__8CGMonObjFv
// Entry: 8012f4b0
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncLastBoss__8CGMonObjFv(CGMonObj *gMonObj)

{
  if ((99 < (int)m_boss__8CGMonObj._4_4_) && (gMonObj->_bossBranchRelated == 0)) {
    gMonObj->_bossBranchRelated = 1;
    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,100,0,0);
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
    m_boss__8CGMonObj._4_4_ = 0;
  }
  return;
}

