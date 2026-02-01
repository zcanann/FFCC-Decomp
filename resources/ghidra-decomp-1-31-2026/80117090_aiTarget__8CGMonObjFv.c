// Function: aiTarget__8CGMonObjFv
// Entry: 80117090
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void aiTarget__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = getNearParty__8CGMonObjFiiffi
                    ((double)FLOAT_803319d8,(double)DAT_8032ec24,gMonObj,0,7,0xffffffff);
  if (-1 < iVar1) {
    *(int *)&gMonObj->field_0x6c4 = iVar1;
  }
  return;
}

