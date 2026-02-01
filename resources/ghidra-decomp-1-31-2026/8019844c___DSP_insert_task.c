// Function: __DSP_insert_task
// Entry: 8019844c
// Size: 160 bytes

void __DSP_insert_task(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_8032f2d8;
  if (DAT_8032f2d8 == 0) {
    DAT_8032f2d4 = param_1;
    DAT_8032f2d8 = param_1;
    DAT_8032f2dc = param_1;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    return;
  }
  do {
    iVar1 = DAT_8032f2d8;
    if (iVar2 == 0) {
LAB_801984c4:
      DAT_8032f2d8 = iVar1;
      if (iVar2 == 0) {
        *(int *)(DAT_8032f2d4 + 0x38) = param_1;
        *(undefined4 *)(param_1 + 0x38) = 0;
        *(int *)(param_1 + 0x3c) = DAT_8032f2d4;
        DAT_8032f2d4 = param_1;
        return;
      }
      return;
    }
    if (*(uint *)(param_1 + 4) < *(uint *)(iVar2 + 4)) {
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x3c);
      *(int *)(iVar2 + 0x3c) = param_1;
      *(int *)(param_1 + 0x38) = iVar2;
      iVar1 = param_1;
      if (*(int *)(param_1 + 0x3c) != 0) {
        *(int *)(*(int *)(param_1 + 0x3c) + 0x38) = param_1;
        iVar1 = DAT_8032f2d8;
      }
      goto LAB_801984c4;
    }
    iVar2 = *(int *)(iVar2 + 0x38);
  } while( true );
}

