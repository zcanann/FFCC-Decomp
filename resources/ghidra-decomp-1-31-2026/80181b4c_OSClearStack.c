// Function: OSClearStack
// Entry: 80181b4c
// Size: 172 bytes

void OSClearStack(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  uVar5 = param_1 & 0xff | (param_1 & 0xff) << 8 | param_1 << 0x18 | (param_1 & 0xff) << 0x10;
  puVar1 = (uint *)OSGetStackPointer();
  puVar4 = (uint *)(*(int *)(DAT_800000e4 + 0x308) + 4);
  uVar2 = (int)puVar1 + (3 - (int)puVar4);
  uVar3 = uVar2 >> 2;
  if (puVar4 < puVar1) {
    uVar2 = uVar2 >> 5;
    if (uVar2 != 0) {
      do {
        *puVar4 = uVar5;
        puVar4[1] = uVar5;
        puVar4[2] = uVar5;
        puVar4[3] = uVar5;
        puVar4[4] = uVar5;
        puVar4[5] = uVar5;
        puVar4[6] = uVar5;
        puVar4[7] = uVar5;
        puVar4 = puVar4 + 8;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) {
        return;
      }
    }
    do {
      *puVar4 = uVar5;
      puVar4 = puVar4 + 1;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  return;
}

