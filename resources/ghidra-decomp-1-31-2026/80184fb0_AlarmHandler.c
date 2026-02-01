// Function: AlarmHandler
// Entry: 80184fb0
// Size: 140 bytes

void AlarmHandler(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (param_1 + 0x7fcf3830) / 0x28 + (param_1 + 0x7fcf3830 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  iVar2 = FatalContext[iVar1 * 8 + 0x2c7];
  if ((iVar2 != -1) &&
     (iVar2 = __SITransfer(iVar2,(&DAT_8030c754)[iVar1 * 8],(&DAT_8030c758)[iVar1 * 8],
                           (&DAT_8030c75c)[iVar1 * 8],(&DAT_8030c760)[iVar1 * 8],
                           (&DAT_8030c764)[iVar1 * 8]), iVar2 != 0)) {
    FatalContext[iVar1 * 8 + 0x2c7] = -1;
  }
  return;
}

