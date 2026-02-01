// Function: damagedFuncWifeLamia__8CGMonObjFv
// Entry: 80130a64
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncWifeLamia__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (*(ushort *)((gMonObj->gObject).m_scriptHandle + 7) < 2) {
    ClearAllSta__10CGCharaObjFv();
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,100,0,0);
    gMonObj->_bossBranchRelated = 1;
  }
  return;
}

