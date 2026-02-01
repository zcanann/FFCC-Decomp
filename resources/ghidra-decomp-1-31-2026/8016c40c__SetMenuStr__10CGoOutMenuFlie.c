// Function: ?SetMenuStr__10CGoOutMenuFlie
// Entry: 8016c40c
// Size: 344 bytes

void _SetMenuStr__10CGoOutMenuFlie
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,int param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  byte in_cr1;
  int local_88;
  undefined4 local_84;
  int local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined4 local_28;
  undefined *local_24;
  int *local_20;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  *(ushort *)(param_9 + 0x38) = *(ushort *)(param_9 + 0x38) ^ 1;
  local_88 = param_9;
  local_84 = param_10;
  local_80 = param_11;
  local_7c = param_12;
  local_78 = param_13;
  local_74 = param_14;
  local_70 = param_15;
  local_6c = param_16;
  piVar2 = (int *)GetWinMess__8CMenuPcsFi(&MenuPcs,*(short *)(param_9 + 0x38) + 0x22);
  *piVar2 = param_11;
  local_24 = &stack0x00000008;
  local_20 = &local_88;
  uVar5 = countLeadingZeros((int)*(short *)(param_9 + 0x38));
  local_28 = 0x3000000;
  iVar3 = GetMcWinMessBuff__8CMenuPcsFi(&MenuPcs,2);
  for (iVar6 = 0; iVar6 < param_11; iVar6 = iVar6 + 1) {
    puVar4 = (undefined4 *)__va_arg(&local_28,1);
    *(undefined4 *)(iVar3 + ((~-(uVar5 >> 5 & 1) & 10) + iVar6) * 4) = *puVar4;
  }
  sVar1 = *(short *)(param_9 + 0x38);
  if (-1 < *(short *)(param_9 + 0x36)) {
    *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
  }
  *(undefined *)(param_9 + 0x45) = 0;
  *(short *)(param_9 + 0x34) = sVar1 + 0x22;
  *(undefined *)(param_9 + 0x48) = 0;
  *(undefined4 *)(param_9 + 0x3c) = param_10;
  return;
}

