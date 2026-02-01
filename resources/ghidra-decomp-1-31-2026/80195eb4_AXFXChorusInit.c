// Function: AXFXChorusInit
// Entry: 80195eb4
// Size: 512 bytes

undefined4 AXFXChorusInit(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  uVar1 = OSDisableInterrupts();
  iVar2 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(0x1680);
  *param_1 = iVar2;
  if (*param_1 == 0) {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  else {
    param_1[3] = *param_1 + 0x780;
    param_1[6] = param_1[3] + 0x780;
    param_1[1] = *param_1 + 0x280;
    param_1[4] = param_1[3] + 0x280;
    param_1[7] = param_1[6] + 0x280;
    param_1[2] = *param_1 + 0x500;
    param_1[5] = param_1[3] + 0x500;
    param_1[8] = param_1[6] + 0x500;
    puVar3 = (undefined4 *)*param_1;
    puVar4 = (undefined4 *)param_1[3];
    puVar5 = (undefined4 *)param_1[6];
    iVar2 = 0x28;
    do {
      *puVar3 = 0;
      *puVar4 = 0;
      *puVar5 = 0;
      puVar3[1] = 0;
      puVar4[1] = 0;
      puVar5[1] = 0;
      puVar3[2] = 0;
      puVar4[2] = 0;
      puVar5[2] = 0;
      puVar3[3] = 0;
      puVar4[3] = 0;
      puVar5[3] = 0;
      puVar3[4] = 0;
      puVar4[4] = 0;
      puVar5[4] = 0;
      puVar3[5] = 0;
      puVar4[5] = 0;
      puVar5[5] = 0;
      puVar3[6] = 0;
      puVar4[6] = 0;
      puVar5[6] = 0;
      puVar3[7] = 0;
      puVar3 = puVar3 + 8;
      puVar4[7] = 0;
      puVar4 = puVar4 + 8;
      puVar5[7] = 0;
      puVar5 = puVar5 + 8;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    *(undefined *)(param_1 + 9) = 1;
    param_1[0xd] = 0;
    param_1[0xc] = 0;
    param_1[0xb] = 0;
    param_1[10] = 0;
    param_1[0x11] = 0;
    param_1[0x10] = 0;
    param_1[0xf] = 0;
    param_1[0xe] = 0;
    param_1[0x15] = 0;
    param_1[0x14] = 0;
    param_1[0x13] = 0;
    param_1[0x12] = 0;
    param_1[0x22] = 0x1e0;
    param_1[0x23] = 0;
    OSRestoreInterrupts(uVar1);
    uVar1 = AXFXChorusSettings(param_1);
  }
  return uVar1;
}

