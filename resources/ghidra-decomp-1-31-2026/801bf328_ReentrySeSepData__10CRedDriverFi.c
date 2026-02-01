// Function: ReentrySeSepData__10CRedDriverFi
// Entry: 801bf328
// Size: 92 bytes

undefined4 ReentrySeSepData__10CRedDriverFi(CRedDriver *redDriver,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  uVar2 = ReentrySeSepData__9CRedEntryFi(&DAT_8032e154,param_2);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

