// Function: DBRead
// Entry: 801bc6f4
// Size: 140 bytes

undefined4 DBRead(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = OSDisableInterrupts();
  if ((DAT_8032f3a8 & 0x10000) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0x1000;
  }
  DBGRead(iVar2 + 0x1e000,param_1,param_2 + 3U & 0xfffffffc);
  DAT_8032f3ac = 0;
  DAT_8032f3b4 = 0;
  OSRestoreInterrupts(uVar1);
  return 0;
}

