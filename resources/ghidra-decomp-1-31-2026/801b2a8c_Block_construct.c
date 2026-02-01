// Function: Block_construct
// Entry: 801b2a8c
// Size: 568 bytes

void Block_construct(uint param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  
  iVar6 = param_1 + 0x10;
  *(uint *)(param_1 + 0xc) = param_2 | 3;
  iVar1 = param_2 - 0x18;
  *(undefined4 *)(param_1 + (param_2 - 8)) = *(undefined4 *)(param_1 + 0xc);
  *(uint *)(param_1 + 0x14) = param_1 | 1;
  *(int *)(param_1 + 0x10) = iVar1;
  *(int *)(param_2 + iVar6 + -0x1c) = iVar1;
  *(int *)(param_1 + 8) = iVar1;
  *(undefined4 *)(param_1 + ((*(uint *)(param_1 + 0xc) & 0xfffffff8) - 4)) = 0;
  uVar4 = *(uint *)(param_1 + 0x10) & 0xfffffff8;
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & 0xfffffffd;
  puVar2 = (uint *)(iVar6 + uVar4);
  *puVar2 = *puVar2 & 0xfffffffb;
  puVar2[-1] = uVar4;
  iVar1 = (*(uint *)(param_1 + 0xc) & 0xfffffff8) - 4;
  if (*(int *)(param_1 + iVar1) == 0) {
    *(int *)(param_1 + iVar1) = iVar6;
    *(int *)(param_1 + 0x18) = iVar6;
    *(int *)(param_1 + 0x1c) = iVar6;
  }
  else {
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(*(int *)(param_1 + iVar1) + 8);
    *(int *)(*(int *)(param_1 + 0x18) + 0xc) = iVar6;
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + iVar1);
    *(int *)(*(int *)(param_1 + iVar1) + 8) = iVar6;
    *(int *)(param_1 + iVar1) = iVar6;
    puVar2 = *(uint **)(param_1 + iVar1);
    if (((*puVar2 & 4) == 0) && (uVar4 = puVar2[-1], (uVar4 & 2) == 0)) {
      puVar5 = (uint *)((int)puVar2 - uVar4);
      *puVar5 = *puVar5 & 7;
      *puVar5 = *puVar5 | uVar4 + (*puVar2 & 0xfffffff8) & 0xfffffff8;
      if ((*puVar5 & 2) == 0) {
        iVar6 = uVar4 + (*puVar2 & 0xfffffff8);
        *(int *)((int)puVar5 + iVar6 + -4) = iVar6;
      }
      if (*(uint **)(param_1 + iVar1) == puVar2) {
        *(uint *)(param_1 + iVar1) = (*(uint **)(param_1 + iVar1))[3];
      }
      *(uint *)(puVar2[3] + 8) = puVar2[2];
      *(uint *)(*(int *)(puVar2[3] + 8) + 0xc) = puVar2[3];
      puVar2 = puVar5;
    }
    *(uint **)(param_1 + iVar1) = puVar2;
    puVar5 = *(uint **)(param_1 + iVar1);
    uVar4 = *puVar5 & 0xfffffff8;
    puVar2 = (uint *)((int)puVar5 + uVar4);
    uVar3 = *puVar2;
    if ((uVar3 & 2) == 0) {
      *puVar5 = *puVar5 & 7;
      uVar4 = uVar4 + (uVar3 & 0xfffffff8);
      *puVar5 = *puVar5 | uVar4;
      if ((*puVar5 & 2) == 0) {
        *(uint *)((int)puVar5 + (uVar4 - 4)) = uVar4;
      }
      if ((*puVar5 & 2) == 0) {
        *(uint *)((int)puVar5 + uVar4) = *(uint *)((int)puVar5 + uVar4) & 0xfffffffb;
      }
      else {
        *(uint *)((int)puVar5 + uVar4) = *(uint *)((int)puVar5 + uVar4) | 4;
      }
      if (*(uint **)(param_1 + iVar1) == puVar2) {
        *(uint *)(param_1 + iVar1) = (*(uint **)(param_1 + iVar1))[3];
      }
      if (*(uint **)(param_1 + iVar1) == puVar2) {
        *(undefined4 *)(param_1 + iVar1) = 0;
      }
      *(uint *)(puVar2[3] + 8) = puVar2[2];
      *(uint *)(puVar2[2] + 0xc) = puVar2[3];
    }
  }
  uVar4 = **(uint **)(param_1 + iVar1) & 0xfffffff8;
  if (*(uint *)(param_1 + 8) < uVar4) {
    *(uint *)(param_1 + 8) = uVar4;
    return;
  }
  return;
}

