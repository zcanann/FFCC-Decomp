// Function: changeStatFuncMeteoParasite__8CGMonObjFi
// Entry: 8012ffe4
// Size: 104 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeStatFuncMeteoParasite__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  if (((gMonObj->gObject).m_scriptHandle[4] == (void *)0x87) && (param_2 == 0x67)) {
    if (*(int *)(m_boss__8CGMonObj._84_4_ + 0x6d0) == 1) {
      setActionParam__8CGMonObjFi(gMonObj,0xfffffff3);
    }
    else {
      setActionParam__8CGMonObjFi(gMonObj,0xfffffff2);
    }
  }
  return;
}

