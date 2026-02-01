// Function: onStatShield__8CGMonObjFv
// Entry: 801179bc
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatShield__8CGMonObjFv(CGMonObj *gMonObj)

{
  if ((*(int *)&gMonObj->field_0x52c == 1) &&
     (*(uint *)&gMonObj->field_0x530 ==
      (uint)*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 0x2e)))
  {
    changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,3);
  }
  return;
}

