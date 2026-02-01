// Function: __copy_longs_rev_aligned
// Entry: 801b688c
// Size: 168 bytes

void __copy_longs_rev_aligned(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)(param_1 + param_3);
  puVar4 = (undefined4 *)(param_2 + param_3);
  uVar2 = (uint)puVar5 & 3;
  if (uVar2 != 0) {
    param_3 = param_3 - uVar2;
    do {
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      uVar2 = uVar2 - 1;
      puVar5 = (undefined4 *)((int)puVar5 + -1);
      *(undefined *)puVar5 = *(undefined *)puVar4;
    } while (uVar2 != 0);
  }
  for (uVar2 = param_3 >> 5; uVar2 != 0; uVar2 = uVar2 - 1) {
    uVar1 = puVar4[-2];
    puVar5[-1] = puVar4[-1];
    uVar3 = puVar4[-3];
    puVar5[-2] = uVar1;
    uVar1 = puVar4[-4];
    puVar5[-3] = uVar3;
    uVar3 = puVar4[-5];
    puVar5[-4] = uVar1;
    uVar1 = puVar4[-6];
    puVar5[-5] = uVar3;
    uVar3 = puVar4[-7];
    puVar5[-6] = uVar1;
    puVar4 = puVar4 + -8;
    uVar1 = *puVar4;
    puVar5[-7] = uVar3;
    puVar5 = puVar5 + -8;
    *puVar5 = uVar1;
  }
  for (uVar2 = param_3 >> 2 & 7; uVar2 != 0; uVar2 = uVar2 - 1) {
    puVar4 = puVar4 + -1;
    puVar5 = puVar5 + -1;
    *puVar5 = *puVar4;
  }
  param_3 = param_3 & 3;
  if (param_3 != 0) {
    do {
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      param_3 = param_3 - 1;
      puVar5 = (undefined4 *)((int)puVar5 + -1);
      *(undefined *)puVar5 = *(undefined *)puVar4;
    } while (param_3 != 0);
    return;
  }
  return;
}

