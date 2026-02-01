// Function: frameStatFuncRamoe__8CGMonObjFv
// Entry: 8012f598
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncRamoe__8CGMonObjFv(CGMonObj *gMonObj)

{
  CGMonObj *gMonObj_00;
  int iVar1;
  int iVar2;
  
  if (*(int *)&gMonObj->field_0x520 == 100) {
    if (*(int *)&gMonObj->field_0x528 == 0x3a) {
      iVar1 = 1;
      iVar2 = -0x7fde113c;
      do {
        gMonObj_00 = *(CGMonObj **)(iVar2 + 0xc5d0);
        if (((gMonObj_00 != (CGMonObj *)0x0) && (*(int *)&gMonObj_00->field_0x520 == 9)) &&
           (*(int *)&gMonObj_00->field_0x52c == 2)) {
          setRepop__8CGMonObjFi(gMonObj_00,0);
        }
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 4;
      } while (iVar1 < 0x40);
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  return;
}

