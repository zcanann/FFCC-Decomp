// Function: __GBASync
// Entry: 801a8b74
// Size: 108 bytes

undefined4 __GBASync(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  param_1 = param_1 * 0x100;
  uVar1 = OSDisableInterrupts();
  while (*(int *)(&DAT_8032833c + param_1) != 0) {
    OSSleepThread(&DAT_80328344 + param_1);
  }
  uVar2 = *(undefined4 *)(&DAT_80328340 + param_1);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

