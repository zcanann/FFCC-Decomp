// Function: Block_subBlock
// Entry: 801b28a8
// Size: 484 bytes

uint * Block_subBlock(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  puVar3 = *(uint **)(param_1 + ((*(uint *)(param_1 + 0xc) & 0xfffffff8) - 4));
  if (puVar3 == (uint *)0x0) {
    *(undefined4 *)(param_1 + 8) = 0;
    return (uint *)0x0;
  }
  uVar1 = *puVar3 & 0xfffffff8;
  puVar4 = puVar3;
  uVar5 = uVar1;
  do {
    if (param_2 <= uVar1) {
      if (0x4f < uVar1 - param_2) {
        puVar3 = (uint *)((int)puVar4 + param_2);
        uVar6 = *puVar4;
        uVar7 = puVar4[1] & 0xfffffffe | 1;
        puVar4[1] = uVar7;
        uVar5 = countLeadingZeros(uVar6 & 2);
        *puVar4 = param_2;
        uVar1 = countLeadingZeros(uVar5 >> 5);
        if ((uVar6 & 4) != 0) {
          *puVar4 = *puVar4 | 4;
        }
        if (uVar1 >> 5 == 0) {
          puVar3[-1] = param_2;
        }
        else {
          *puVar4 = *puVar4 | 2;
          *puVar3 = *puVar3 | 4;
        }
        puVar3[1] = uVar7;
        param_2 = (uVar6 & 0xfffffff8) - param_2;
        *puVar3 = param_2;
        if (uVar1 >> 5 == 0) {
          *(uint *)((int)puVar3 + (param_2 - 4)) = param_2;
        }
        else {
          *puVar3 = *puVar3 | 4;
          *puVar3 = *puVar3 | 2;
          *(uint *)((int)puVar3 + param_2) = *(uint *)((int)puVar3 + param_2) | 4;
        }
        if (uVar5 >> 5 != 0) {
          puVar3[3] = puVar4[3];
          *(uint **)(puVar3[3] + 8) = puVar3;
          puVar3[2] = (uint)puVar4;
          puVar4[3] = (uint)puVar3;
        }
      }
      *(uint *)(param_1 + ((*(uint *)(param_1 + 0xc) & 0xfffffff8) - 4)) = puVar4[3];
      uVar1 = *puVar4 & 0xfffffff8;
      *puVar4 = *puVar4 | 2;
      *(uint *)((int)puVar4 + uVar1) = *(uint *)((int)puVar4 + uVar1) | 4;
      iVar2 = (*(uint *)(param_1 + 0xc) & 0xfffffff8) - 4;
      if (*(uint **)(param_1 + iVar2) == puVar4) {
        *(uint *)(param_1 + iVar2) = puVar4[3];
      }
      if (*(uint **)(param_1 + iVar2) == puVar4) {
        *(undefined4 *)(param_1 + iVar2) = 0;
        *(undefined4 *)(param_1 + 8) = 0;
      }
      else {
        *(uint *)(puVar4[3] + 8) = puVar4[2];
        *(uint *)(puVar4[2] + 0xc) = puVar4[3];
      }
      return puVar4;
    }
    puVar4 = (uint *)puVar4[3];
    uVar1 = *puVar4 & 0xfffffff8;
    if (uVar5 < uVar1) {
      uVar5 = uVar1;
    }
  } while (puVar4 != puVar3);
  *(uint *)(param_1 + 8) = uVar5;
  return (uint *)0x0;
}

