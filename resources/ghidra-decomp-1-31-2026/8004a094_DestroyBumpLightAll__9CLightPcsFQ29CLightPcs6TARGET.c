// Function: DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET
// Entry: 8004a094
// Size: 136 bytes

void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  
  param_1 = param_1 + param_2 * 0x9c0;
  uVar2 = 0;
  do {
    bVar1 = *(int *)(param_1 + 0x1cf0) != 0;
    if (bVar1) {
      if (bVar1) {
        Free__7CMemoryFPv(&Memory);
        *(undefined4 *)(param_1 + 0x1cf0) = 0;
      }
      *(undefined *)(param_1 + 0x1cec) = 0;
      *(undefined *)(param_1 + 0x1ced) = 0;
    }
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 0x138;
  } while (uVar2 < 8);
  return;
}

