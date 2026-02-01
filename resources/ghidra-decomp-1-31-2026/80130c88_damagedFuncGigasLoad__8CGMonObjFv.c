// Function: damagedFuncGigasLoad__8CGMonObjFv
// Entry: 80130c88
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncGigasLoad__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (gMonObj->_bossBranchRelated == 0) {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,4,0,0);
    gMonObj->_bossBranchRelated = 1;
    CFlat._4840_4_ = 1;
  }
  return;
}

