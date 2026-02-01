// Function: flyDown__8CGMonObjFv
// Entry: 8011a248
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void flyDown__8CGMonObjFv(CGMonObj *gMonObj)

{
  changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x17,0,0);
  gMonObj->field_0x6b9 = 1;
  damageDelete__10CGCharaObjFv(gMonObj);
  return;
}

