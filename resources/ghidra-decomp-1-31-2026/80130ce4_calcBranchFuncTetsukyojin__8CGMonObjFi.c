// Function: calcBranchFuncTetsukyojin__8CGMonObjFi
// Entry: 80130ce4
// Size: 28 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int calcBranchFuncTetsukyojin__8CGMonObjFi(CGMonObj *gMonObj)

{
  return (gMonObj->_bossBranchRelated >> 0x1f) + (uint)(gMonObj->_bossBranchRelated != 0);
}

