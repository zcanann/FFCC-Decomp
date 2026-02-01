// Function: destroyBonus__8CMenuPcsFv
// Entry: 8013d410
// Size: 396 bytes

void destroyBonus__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int *piVar1;
  int iVar2;
  CMenuPcs *pCVar3;
  
  Pad._456_4_ = 1;
  piVar1 = *(int **)&menuPcs->field_0xfc;
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&menuPcs->field_0xfc = 0;
  }
  iVar2 = 0;
  pCVar3 = menuPcs;
  do {
    if (*(int *)&pCVar3->field_0x774 != 0) {
      __dt__Q29CCharaPcs7CHandleFv(*(int *)&pCVar3->field_0x774,1);
      *(undefined4 *)&pCVar3->field_0x774 = 0;
    }
    iVar2 = iVar2 + 1;
    pCVar3 = (CMenuPcs *)&pCVar3->field_0x4;
  } while (iVar2 < 0x18);
  iVar2 = *(int *)&menuPcs->field_0x840;
  if (iVar2 != 0) {
    if (iVar2 != 0) {
      __dla__FPv((void *)(iVar2 + -0x10));
    }
    *(undefined4 *)&menuPcs->field_0x840 = 0;
  }
  if (DAT_8032eea8 != 0) {
    __dl__FPv();
    DAT_8032eea8 = 0;
  }
  if (*(int *)&menuPcs->field_0x82c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x82c = 0;
  }
  if (*(int *)&menuPcs->field_0x84c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x84c = 0;
  }
  if (DAT_8032eeb0 != 0) {
    __dl__FPv();
    DAT_8032eeb0 = 0;
  }
  if (*(void **)&menuPcs->field_0x814 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x814);
    *(undefined4 *)&menuPcs->field_0x814 = 0;
  }
  if (*(int *)&menuPcs->field_0x848 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x848 = 0;
  }
  freeTexture__8CMenuPcsFiiii(menuPcs,2,1,0x16,0x12);
  return;
}

