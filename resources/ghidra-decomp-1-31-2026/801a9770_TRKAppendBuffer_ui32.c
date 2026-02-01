// Function: TRKAppendBuffer_ui32
// Entry: 801a9770
// Size: 252 bytes

void TRKAppendBuffer_ui32(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_28;
  undefined local_24;
  undefined local_23;
  undefined local_22;
  undefined local_21;
  
  iVar1 = 0;
  for (iVar6 = 0; (iVar1 == 0 && (iVar6 < param_3)); iVar6 = iVar6 + 1) {
    uVar2 = *param_2;
    local_28 = uVar2;
    uVar2 = local_28;
    if (DAT_80328748 == 0) {
      local_28._3_1_ = (undefined)uVar2;
      puVar3 = (undefined4 *)&local_24;
      local_28._2_1_ = (undefined)((uint)uVar2 >> 8);
      local_28._1_1_ = (undefined)((uint)uVar2 >> 0x10);
      local_28._0_1_ = (undefined)((uint)uVar2 >> 0x18);
      local_24 = (undefined)local_28;
      local_23 = local_28._2_1_;
      local_22 = local_28._1_1_;
      local_21 = local_28._0_1_;
    }
    else {
      puVar3 = &local_28;
    }
    iVar4 = *(int *)(param_1 + 0xc);
    iVar1 = 0;
    uVar5 = 4;
    if (0x880U - iVar4 < 4) {
      iVar1 = 0x301;
      uVar5 = 0x880U - iVar4;
    }
    if (uVar5 == 1) {
      *(undefined *)(param_1 + iVar4 + 0x10) = *(undefined *)puVar3;
    }
    else {
      local_28 = uVar2;
      TRK_memcpy(param_1 + iVar4 + 0x10,puVar3,uVar5);
    }
    param_2 = param_2 + 1;
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar5;
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0xc);
  }
  return;
}

