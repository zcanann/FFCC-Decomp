// Function: SetViewerSRT__10CCameraPcsFPC3SRT
// Entry: 80038f60
// Size: 84 bytes

void SetViewerSRT__10CCameraPcsFPC3SRT(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1];
  *(undefined4 *)(param_1 + 0x448) = *param_2;
  uVar2 = param_2[2];
  *(undefined4 *)(param_1 + 0x44c) = uVar1;
  uVar1 = param_2[3];
  *(undefined4 *)(param_1 + 0x450) = uVar2;
  uVar2 = param_2[4];
  *(undefined4 *)(param_1 + 0x454) = uVar1;
  uVar1 = param_2[5];
  *(undefined4 *)(param_1 + 0x458) = uVar2;
  uVar3 = param_2[6];
  *(undefined4 *)(param_1 + 0x45c) = uVar1;
  uVar2 = param_2[7];
  *(undefined4 *)(param_1 + 0x460) = uVar3;
  uVar1 = param_2[8];
  *(undefined4 *)(param_1 + 0x464) = uVar2;
  *(undefined4 *)(param_1 + 0x468) = uVar1;
  *(undefined4 *)(param_1 + 0x46c) = 1;
  return;
}

