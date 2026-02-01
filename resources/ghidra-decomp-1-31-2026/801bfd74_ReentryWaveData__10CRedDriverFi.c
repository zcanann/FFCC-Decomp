// Function: ReentryWaveData__10CRedDriverFi
// Entry: 801bfd74
// Size: 92 bytes

undefined4 ReentryWaveData__10CRedDriverFi(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  uVar2 = ReentryWaveData__9CRedEntryFi(&DAT_8032e154,param_2);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

