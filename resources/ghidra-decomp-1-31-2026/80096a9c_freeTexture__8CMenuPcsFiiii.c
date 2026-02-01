// Function: freeTexture__8CMenuPcsFiiii
// Entry: 80096a9c
// Size: 248 bytes

void freeTexture__8CMenuPcsFiiii(CMenuPcs *menuPcs,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  for (iVar4 = 0; iVar4 < param_5; iVar4 = iVar4 + 1) {
    iVar1 = (iVar4 + param_4) * 4;
    piVar2 = *(int **)(&menuPcs->field_0x18c + iVar1);
    if (piVar2 != (int *)0x0) {
      iVar3 = piVar2[1];
      piVar2[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
        (**(code **)(*piVar2 + 8))(piVar2,1);
      }
      *(undefined4 *)(&menuPcs->field_0x18c + iVar1) = 0;
    }
  }
  for (iVar4 = 0; iVar4 < param_3; iVar4 = iVar4 + 1) {
    iVar1 = (iVar4 + param_2) * 4;
    piVar2 = *(int **)(&menuPcs->field_0x14c + iVar1);
    if (piVar2 != (int *)0x0) {
      iVar3 = piVar2[1];
      piVar2[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
        (**(code **)(*piVar2 + 8))(piVar2,1);
      }
      *(undefined4 *)(&menuPcs->field_0x14c + iVar1) = 0;
    }
  }
  return;
}

