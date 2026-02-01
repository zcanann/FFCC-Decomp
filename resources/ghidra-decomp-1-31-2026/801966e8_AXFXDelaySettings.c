// Function: AXFXDelaySettings
// Entry: 801966e8
// Size: 516 bytes

undefined4 AXFXDelaySettings(uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  AXFXDelayShutdown();
  uVar1 = OSDisableInterrupts();
  *param_1 = ((param_1[0xf] - 5) * 0x20 + 0x9f) / 0xa0;
  param_1[3] = 0;
  param_1[6] = (param_1[0x12] << 7) / 100;
  param_1[9] = (param_1[0x15] << 7) / 100;
  param_1[1] = ((param_1[0x10] - 5) * 0x20 + 0x9f) / 0xa0;
  param_1[4] = 0;
  param_1[7] = (param_1[0x13] << 7) / 100;
  param_1[10] = (param_1[0x16] << 7) / 100;
  param_1[2] = ((param_1[0x11] - 5) * 0x20 + 0x9f) / 0xa0;
  param_1[5] = 0;
  param_1[8] = (param_1[0x14] << 7) / 100;
  param_1[0xb] = (param_1[0x17] << 7) / 100;
  uVar2 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(*param_1 * 0x280);
  param_1[0xc] = uVar2;
  uVar2 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(param_1[1] * 0x280);
  param_1[0xd] = uVar2;
  uVar2 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(param_1[2] * 0x280);
  param_1[0xe] = uVar2;
  puVar3 = (undefined4 *)param_1[0xc];
  puVar4 = (undefined4 *)param_1[0xd];
  puVar5 = (undefined4 *)param_1[0xe];
  for (uVar2 = 0; uVar2 < *param_1 * 0xa0; uVar2 = uVar2 + 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (uVar2 = 0; uVar2 < param_1[1] * 0xa0; uVar2 = uVar2 + 1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = 0; uVar2 < param_1[2] * 0xa0; uVar2 = uVar2 + 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  OSRestoreInterrupts(uVar1);
  return 1;
}

