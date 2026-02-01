// Function: Printf__8CGraphicFPce
// Entry: 800190f8
// Size: 224 bytes

void Printf__8CGraphicFPce
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  byte in_cr1;
  int local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined4 local_118;
  undefined *local_114;
  int *local_110;
  undefined auStack_10c [264];
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_158 = param_1;
    local_150 = param_2;
    local_148 = param_3;
    local_140 = param_4;
    local_138 = param_5;
    local_130 = param_6;
    local_128 = param_7;
    local_120 = param_8;
  }
  if (*(uint *)(param_9 + 0x14) < 0x70) {
    local_114 = &stack0x00000008;
    local_110 = &local_178;
    local_118 = 0x2000000;
    local_178 = param_9;
    local_174 = param_10;
    local_170 = param_11;
    local_16c = param_12;
    local_168 = param_13;
    local_164 = param_14;
    local_160 = param_15;
    local_15c = param_16;
    vsprintf(auStack_10c,param_10,&local_118);
    *(undefined2 *)(param_9 + *(int *)(param_9 + 0x14) * 4 + 0x18) = 0xffff;
    *(undefined2 *)(param_9 + *(int *)(param_9 + 0x14) * 4 + 0x1a) = 0xffff;
    iVar1 = *(int *)(param_9 + 0x14);
    *(int *)(param_9 + 0x14) = iVar1 + 1;
    strcpy(param_9 + iVar1 * 0x70 + 0x1e0,auStack_10c);
  }
  return;
}

