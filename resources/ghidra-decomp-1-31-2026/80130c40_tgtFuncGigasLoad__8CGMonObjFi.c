// Function: tgtFuncGigasLoad__8CGMonObjFi
// Entry: 80130c40
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 tgtFuncGigasLoad__8CGMonObjFi(CGMonObj *gMonObj)

{
  aiTargetAttackRomMon__8CGMonObjFi(gMonObj,0x3b);
  if (*(int *)&gMonObj->field_0x6c4 < 0) {
    aiTarget__8CGMonObjFv(gMonObj);
  }
  return *(undefined4 *)&gMonObj->field_0x6c4;
}

