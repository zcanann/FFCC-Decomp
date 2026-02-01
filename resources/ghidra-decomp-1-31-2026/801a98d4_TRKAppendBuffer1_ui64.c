// Function: TRKAppendBuffer1_ui64
// Entry: 801a98d4
// Size: 252 bytes

undefined4
TRKAppendBuffer1_ui64(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 local_28;
  undefined4 local_24;
  undefined local_20;
  undefined local_1f;
  undefined local_1e;
  undefined local_1d;
  undefined local_1c;
  undefined local_1b;
  undefined local_1a;
  undefined local_19;
  
  local_28 = param_3;
  uVar1 = local_28;
  local_24 = param_4;
  uVar2 = local_24;
  if (DAT_80328748 == 0) {
    local_24._3_1_ = (undefined)param_4;
    puVar4 = (undefined4 *)&local_20;
    local_24._2_1_ = (undefined)((uint)param_4 >> 8);
    local_24._1_1_ = (undefined)((uint)param_4 >> 0x10);
    local_24._0_1_ = (undefined)((uint)param_4 >> 0x18);
    local_28._3_1_ = (undefined)param_3;
    local_28._2_1_ = (undefined)((uint)param_3 >> 8);
    local_28._1_1_ = (undefined)((uint)param_3 >> 0x10);
    local_28._0_1_ = (undefined)((uint)param_3 >> 0x18);
    local_20 = (undefined)local_24;
    local_1f = local_24._2_1_;
    local_1e = local_24._1_1_;
    local_1d = local_24._0_1_;
    local_1c = (undefined)local_28;
    local_1b = local_28._2_1_;
    local_1a = local_28._1_1_;
    local_19 = local_28._0_1_;
  }
  else {
    puVar4 = &local_28;
  }
  iVar3 = *(int *)(param_1 + 0xc);
  uVar6 = 0;
  uVar5 = 8;
  if (0x880U - iVar3 < 8) {
    uVar6 = 0x301;
    uVar5 = 0x880U - iVar3;
  }
  if (uVar5 == 1) {
    *(undefined *)(param_1 + iVar3 + 0x10) = *(undefined *)puVar4;
  }
  else {
    local_28 = uVar1;
    local_24 = uVar2;
    TRK_memcpy(param_1 + iVar3 + 0x10,puVar4,uVar5);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar5;
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0xc);
  return uVar6;
}

