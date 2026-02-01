// Function: __OSMaskInterrupts
// Entry: 8017e708
// Size: 136 bytes

uint __OSMaskInterrupts(uint param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = OSDisableInterrupts();
  uVar1 = DAT_800000c4;
  uVar2 = DAT_800000c4 | DAT_800000c8;
  DAT_800000c4 = param_1 | DAT_800000c4;
  uVar4 = DAT_800000c4 | DAT_800000c8;
  for (param_1 = param_1 & ~uVar2; param_1 != 0; param_1 = SetInterruptMask(param_1,uVar4)) {
  }
  OSRestoreInterrupts(uVar3);
  return uVar1;
}

