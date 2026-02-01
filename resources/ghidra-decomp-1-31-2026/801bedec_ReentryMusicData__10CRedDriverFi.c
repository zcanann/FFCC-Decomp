// Function: ReentryMusicData__10CRedDriverFi
// Entry: 801bedec
// Size: 92 bytes

undefined4 ReentryMusicData__10CRedDriverFi(CRedDriver *redDriver,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  uVar2 = ReentryMusicData__9CRedEntryFi(&DAT_8032e154,param_2);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

