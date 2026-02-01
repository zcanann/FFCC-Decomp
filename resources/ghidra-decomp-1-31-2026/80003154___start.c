// Function: __start
// Entry: 80003154
// Size: 348 bytes

void __start(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  
  __init_registers();
  __init_hardware();
  uVar8 = _0003340();
  uVar1 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_80000044 = 0;
  if (DAT_800000f4 == 0) {
    iVar2 = DAT_800030e8;
    if (DAT_80000034 != 0) goto LAB_800031bc;
  }
  else {
    iVar2 = *(int *)(DAT_800000f4 + 0xc);
LAB_800031bc:
    uVar3 = 0;
    if ((iVar2 == 2) || (uVar3 = 1, iVar2 == 3)) {
      InitMetroTRK(uVar1,(int)uVar8,uVar3);
    }
    else if (iVar2 == 4) {
      __set_debug_bba(uVar1,(int)uVar8,2);
    }
  }
  iVar2 = DAT_800000f4;
  if ((DAT_800000f4 != 0) && (*(int *)(DAT_800000f4 + 8) != 0)) {
    piVar4 = (int *)(DAT_800000f4 + *(int *)(DAT_800000f4 + 8));
    iVar5 = *piVar4;
    if (iVar5 != 0) {
      piVar6 = piVar4 + 1;
      iVar7 = iVar5;
      do {
        piVar4 = piVar4 + 1;
        *piVar4 = *piVar4 + iVar2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      DAT_80000034 = (uint)piVar6 & 0xffffffe0;
      goto LAB_80003260;
    }
  }
  iVar5 = 0;
  piVar6 = (int *)0x0;
LAB_80003260:
  DBInit();
  OSInit();
  if (((DAT_800030e6 & 0x8000) == 0) || ((DAT_800030e6 & 0x7fff) == 1)) {
    __check_pad3();
  }
  iVar2 = __get_debug_bba();
  if (iVar2 == 1) {
    InitMetroTRK_BBA();
  }
  __init_user();
  main(iVar5,piVar6);
  exit();
  return;
}

