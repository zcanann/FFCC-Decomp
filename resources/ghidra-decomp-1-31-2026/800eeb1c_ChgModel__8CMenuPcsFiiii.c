// Function: ChgModel__8CMenuPcsFiiii
// Entry: 800eeb1c
// Size: 128 bytes

void ChgModel__8CMenuPcsFiiii(CMenuPcs *menuPcs,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)&menuPcs->field_0x824 + param_2 * 0x34;
  if (param_3 < 0) {
    uVar2 = 3;
    *(undefined *)(iVar3 + 0xc) = 0;
    iVar1 = 0x43;
  }
  else {
    uVar2 = 0;
    iVar1 = param_3 * 200 + 100;
    if (param_5 != 0) {
      iVar1 = param_3 * 200 + 200;
    }
    iVar1 = iVar1 + param_4;
    *(undefined *)(iVar3 + 0xc) = 1;
  }
  LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
            (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + param_2 * 4),uVar2,iVar1,0);
  return;
}

