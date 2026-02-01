// Function: __copy_longs_aligned
// Entry: 801b6934
// Size: 188 bytes

void __copy_longs_aligned(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  puVar4 = (undefined *)(param_2 + -1);
  uVar6 = -param_1 & 3;
  puVar2 = (undefined *)(param_1 + -1);
  if (uVar6 != 0) {
    param_3 = param_3 - uVar6;
    do {
      puVar4 = puVar4 + 1;
      uVar6 = uVar6 - 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar4;
    } while (uVar6 != 0);
  }
  puVar7 = (undefined4 *)(puVar4 + -3);
  puVar5 = (undefined4 *)(puVar2 + -3);
  for (uVar6 = param_3 >> 5; uVar6 != 0; uVar6 = uVar6 - 1) {
    uVar1 = puVar7[2];
    puVar5[1] = puVar7[1];
    uVar3 = puVar7[3];
    puVar5[2] = uVar1;
    uVar1 = puVar7[4];
    puVar5[3] = uVar3;
    uVar3 = puVar7[5];
    puVar5[4] = uVar1;
    uVar1 = puVar7[6];
    puVar5[5] = uVar3;
    uVar3 = puVar7[7];
    puVar5[6] = uVar1;
    puVar7 = puVar7 + 8;
    uVar1 = *puVar7;
    puVar5[7] = uVar3;
    puVar5 = puVar5 + 8;
    *puVar5 = uVar1;
  }
  for (uVar6 = param_3 >> 2 & 7; uVar6 != 0; uVar6 = uVar6 - 1) {
    puVar7 = puVar7 + 1;
    puVar5 = puVar5 + 1;
    *puVar5 = *puVar7;
  }
  param_3 = param_3 & 3;
  puVar4 = (undefined *)((int)puVar7 + 3);
  puVar2 = (undefined *)((int)puVar5 + 3);
  if (param_3 != 0) {
    do {
      puVar4 = puVar4 + 1;
      param_3 = param_3 - 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar4;
    } while (param_3 != 0);
    return;
  }
  return;
}

