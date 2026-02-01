// Function: sprintf
// Entry: 801b6a10
// Size: 224 bytes

void sprintf(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  byte in_cr1;
  int local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  int local_38 [4];
  undefined *local_28;
  int *local_24;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_78 = param_1;
    local_70 = param_2;
    local_68 = param_3;
    local_60 = param_4;
    local_58 = param_5;
    local_50 = param_6;
    local_48 = param_7;
    local_40 = param_8;
  }
  local_28 = &stack0x00000008;
  local_24 = &local_98;
  local_38[3] = 0x2000000;
  local_38[1] = 0xffffffff;
  local_38[2] = 0;
  local_98 = param_9;
  local_94 = param_10;
  local_90 = param_11;
  local_8c = param_12;
  local_88 = param_13;
  local_84 = param_14;
  local_80 = param_15;
  local_7c = param_16;
  local_38[0] = param_9;
  iVar1 = __pformatter(__StringWrite,local_38,param_10,local_38 + 3);
  if (param_9 != 0) {
    iVar2 = -2;
    if (iVar1 != -1) {
      iVar2 = iVar1;
    }
    *(undefined *)(param_9 + iVar2) = 0;
  }
  return;
}

