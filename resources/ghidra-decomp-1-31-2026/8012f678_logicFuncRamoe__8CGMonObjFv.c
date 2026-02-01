// Function: logicFuncRamoe__8CGMonObjFv
// Entry: 8012f678
// Size: 308 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncRamoe__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = 0;
  iVar4 = 1;
  iVar2 = -0x7fde113c;
  iVar5 = -1;
  iVar6 = 0x15;
  do {
    iVar1 = *(int *)(iVar2 + 0xc5d0);
    if ((iVar1 != 0) && ((*(int *)(iVar1 + 0x520) != 9 || (*(int *)(iVar1 + 0x52c) != 2)))) {
      iVar3 = iVar3 + 1;
    }
    iVar1 = *(int *)(iVar2 + 0xc5d4);
    if ((iVar1 != 0) && ((*(int *)(iVar1 + 0x520) != 9 || (*(int *)(iVar1 + 0x52c) != 2)))) {
      iVar3 = iVar3 + 1;
    }
    iVar1 = *(int *)(iVar2 + 0xc5d8);
    if ((iVar1 != 0) && ((*(int *)(iVar1 + 0x520) != 9 || (*(int *)(iVar1 + 0x52c) != 2)))) {
      iVar3 = iVar3 + 1;
    }
    iVar2 = iVar2 + 0xc;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if ((iVar3 == 0) && (iVar2 = Rand__5CMathFUl(&Math,3,0,iVar4), iVar2 == 0)) {
    iVar5 = 100;
  }
  if (iVar5 == -1) {
    logicFuncDefault__8CGMonObjFv(gMonObj);
  }
  else {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar5,0,0);
  }
  return;
}

