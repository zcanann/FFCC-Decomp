// Function: changeStatFuncMolbol__8CGMonObjFi
// Entry: 80130a1c
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeStatFuncMolbol__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  if (param_2 == 0x65) {
    setActionParam__8CGMonObjFi(gMonObj,0xfffffff2);
  }
  else if ((param_2 < 0x65) && (99 < param_2)) {
    setActionParam__8CGMonObjFi(gMonObj,0xfffffff3);
  }
  return;
}

