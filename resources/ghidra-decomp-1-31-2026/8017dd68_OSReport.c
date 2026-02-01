// Function: OSReport
// Entry: 8017dd68
// Size: 128 bytes

void OSReport(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
             undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
             undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte in_cr1;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined4 local_c;
  undefined *local_8;
  undefined4 *local_4;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_50 = param_1;
    local_48 = param_2;
    local_40 = param_3;
    local_38 = param_4;
    local_30 = param_5;
    local_28 = param_6;
    local_20 = param_7;
    local_18 = param_8;
  }
  local_c = 0x1000000;
  local_8 = &stack0x00000008;
  local_4 = &local_70;
  local_70 = param_9;
  local_6c = param_10;
  local_68 = param_11;
  local_64 = param_12;
  local_60 = param_13;
  local_5c = param_14;
  local_58 = param_15;
  local_54 = param_16;
  vprintf(param_9,&local_c);
  return;
}

