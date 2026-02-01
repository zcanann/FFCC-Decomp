// Function: OSCreateHeap
// Entry: 8017cb8c
// Size: 108 bytes

int OSCreateHeap(int param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)(param_1 + 0x1fU & 0xffffffe0);
  iVar2 = 0;
  piVar3 = OSAlarm_8032ef60.fire._0_4_;
  iVar4 = OSAlarm_8032ef60.fire._4_4_;
  if (0 < OSAlarm_8032ef60.fire._4_4_) {
    do {
      if (*piVar3 < 0) {
        *piVar3 = (param_2 & 0xffffffe0) - (int)puVar1;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = *piVar3;
        piVar3[1] = (int)puVar1;
        piVar3[2] = 0;
        return iVar2;
      }
      piVar3 = piVar3 + 3;
      iVar2 = iVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return -1;
}

