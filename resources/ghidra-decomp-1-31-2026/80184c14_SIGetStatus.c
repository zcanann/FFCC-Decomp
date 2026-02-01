// Function: SIGetStatus
// Entry: 80184c14
// Size: 124 bytes

uint SIGetStatus(int param_1)

{
  uint uVar1;
  
  OSDisableInterrupts();
  uVar1 = DAT_cc006438;
  uVar1 = uVar1 >> (3 - param_1) * 8;
  if (((uVar1 & 8) != 0) && ((*(uint *)(&DAT_80217318 + param_1 * 4) & 0x80) == 0)) {
    *(uint *)(&DAT_80217318 + param_1 * 4) = 8;
  }
  OSRestoreInterrupts();
  return uVar1;
}

