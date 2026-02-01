// Function: Printf__8CGraphicFUlUlPce
// Entry: 80019000
// Size: 248 bytes

void Printf__8CGraphicFUlUlPce
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  byte in_cr1;
  int local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined4 local_128;
  undefined *local_124;
  int *local_120;
  undefined auStack_11c [272];
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_168 = param_1;
    local_160 = param_2;
    local_158 = param_3;
    local_150 = param_4;
    local_148 = param_5;
    local_140 = param_6;
    local_138 = param_7;
    local_130 = param_8;
  }
  if (*(uint *)(param_9 + 0x14) < 0x70) {
    local_124 = &stack0x00000008;
    local_120 = &local_188;
    local_128 = 0x4000000;
    local_188 = param_9;
    local_184 = param_10;
    local_180 = param_11;
    local_17c = param_12;
    local_178 = param_13;
    local_174 = param_14;
    local_170 = param_15;
    local_16c = param_16;
    vsprintf(auStack_11c,param_12,&local_128);
    *(short *)(param_9 + *(int *)(param_9 + 0x14) * 4 + 0x18) = (short)param_10;
    *(short *)(param_9 + *(int *)(param_9 + 0x14) * 4 + 0x1a) = (short)param_11;
    iVar1 = *(int *)(param_9 + 0x14);
    *(int *)(param_9 + 0x14) = iVar1 + 1;
    strcpy(param_9 + iVar1 * 0x70 + 0x1e0,auStack_11c);
  }
  return;
}

