// Function: OSInitAlloc
// Entry: 8017cb1c
// Size: 112 bytes

void OSInitAlloc(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = 0;
  OSAlarm_8032ef60.fire._0_4_ = param_1;
  OSAlarm_8032ef60.fire._4_4_ = param_3;
  for (iVar2 = 0; iVar2 < OSAlarm_8032ef60.fire._4_4_; iVar2 = iVar2 + 1) {
    puVar3 = (undefined4 *)(OSAlarm_8032ef60.fire._0_4_ + iVar1);
    *puVar3 = 0xffffffff;
    iVar1 = iVar1 + 0xc;
    puVar3[2] = 0;
    puVar3[1] = 0;
  }
  OSAlarm_8032ef60.next = (OSAlarm *)(param_2 & 0xffffffe0);
  DAT_8032ea90 = 0xffffffff;
  OSAlarm_8032ef60.prev =
       (OSAlarm *)(OSAlarm_8032ef60.fire._0_4_ + param_3 * 0xc + 0x1fU & 0xffffffe0);
  return;
}

