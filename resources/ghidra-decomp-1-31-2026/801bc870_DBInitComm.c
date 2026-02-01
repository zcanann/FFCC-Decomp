// Function: DBInitComm
// Entry: 801bc870
// Size: 120 bytes

void DBInitComm(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8032f3b0 = &DAT_8032f3b4;
  *param_1 = &DAT_8032f3b4;
  DAT_8032f3a0 = param_2;
  __OSMaskInterrupts(0x18000);
  DAT_cc006828 = 0;
  OSRestoreInterrupts(uVar1);
  return;
}

