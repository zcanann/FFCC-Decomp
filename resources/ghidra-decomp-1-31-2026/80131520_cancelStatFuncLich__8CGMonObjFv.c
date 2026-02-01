// Function: cancelStatFuncLich__8CGMonObjFv
// Entry: 80131520
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void cancelStatFuncLich__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (*(int *)&gMonObj->field_0x520 == 100) {
    endPSlotBit__10CGCharaObjFi(gMonObj,0x400);
  }
  return;
}

