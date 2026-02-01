// Function: SIGetResponseRaw
// Entry: 80184e18
// Size: 212 bytes

bool SIGetResponseRaw(int param_1)

{
  bool bVar1;
  uint uVar2;
  
  OSDisableInterrupts();
  uVar2 = DAT_cc006438;
  uVar2 = uVar2 >> (3 - param_1) * 8;
  if (((uVar2 & 8) != 0) && ((*(uint *)(&DAT_80217318 + param_1 * 4) & 0x80) == 0)) {
    *(uint *)(&DAT_80217318 + param_1 * 4) = 8;
  }
  OSRestoreInterrupts();
  bVar1 = (uVar2 & 0x20) != 0;
  if (bVar1) {
    *(undefined4 *)(&DAT_8030c910 + param_1 * 8) = *(undefined4 *)(&DAT_cc006404 + param_1 * 0xc);
    *(undefined4 *)(&DAT_8030c914 + param_1 * 8) = *(undefined4 *)(&DAT_cc006408 + param_1 * 0xc);
    *(undefined4 *)(&DAT_8030c900 + param_1 * 4) = 1;
  }
  return bVar1;
}

