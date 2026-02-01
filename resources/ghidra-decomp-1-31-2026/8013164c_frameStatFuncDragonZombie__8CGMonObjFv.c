// Function: frameStatFuncDragonZombie__8CGMonObjFv
// Entry: 8013164c
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncDragonZombie__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 0x65) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xf,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x987a,0x32,0x96,0,0);
    }
    iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar1 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
  }
  else if ((iVar1 < 0x65) && (99 < iVar1)) {
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  return;
}

