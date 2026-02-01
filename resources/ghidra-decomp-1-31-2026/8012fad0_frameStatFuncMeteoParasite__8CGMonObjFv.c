// Function: frameStatFuncMeteoParasite__8CGMonObjFv
// Entry: 8012fad0
// Size: 504 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  pvVar2 = (gMonObj->gObject).m_scriptHandle[4];
  if (iVar1 == 0x66) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xc,0,0);
    }
    else {
      iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
      if (iVar1 != 0) {
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
    }
  }
  else if (iVar1 < 0x66) {
    if (iVar1 == 100) {
      if (*(int *)&gMonObj->field_0x528 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,10,0,0);
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0xb,0);
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
        }
      }
    }
    else if (99 < iVar1) {
      if (*(int *)&gMonObj->field_0x528 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xd,0,0);
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0xe,0);
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
        }
      }
    }
  }
  if ((pvVar2 == (void *)0x87) && (*(int *)&gMonObj->field_0x520 == 0x67)) {
    iVar1 = *(int *)&gMonObj->field_0x528;
    if ((0x18 < iVar1) && (iVar1 < 0x32)) {
      if (iVar1 == 0x19) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x11d5b,0x32,0x96,0,0);
      }
      if (*(int *)&gMonObj->field_0x528 == (*(int *)&gMonObj->field_0x528 / 3) * 3) {
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,2,
                   *(undefined4 *)&gMonObj->field_0x564,0);
      }
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  return;
}

