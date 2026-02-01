// Function: cancelStatFuncLastBoss__8CGMonObjFv
// Entry: 8012f3e8
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void cancelStatFuncLastBoss__8CGMonObjFv(CGMonObj *gMonObj)

{
  CGPrgObj *gPrgObj;
  int iVar1;
  int iVar2;
  
  if (*(int *)&gMonObj->field_0x520 == 0x66) {
    iVar1 = 0;
    iVar2 = -0x7fcffeb4;
    do {
      gPrgObj = *(CGPrgObj **)(iVar2 + 8);
      if ((gPrgObj != (CGPrgObj *)0x0) && (gPrgObj->m_lastStateId == 0x25)) {
        changeStat__8CGPrgObjFiii(gPrgObj,0x24,0,0);
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 4;
    } while (iVar1 < 4);
    endPSlotBit__10CGCharaObjFi(gMonObj,0x400);
  }
  return;
}

