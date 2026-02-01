// Function: SIGetResponse
// Entry: 80184eec
// Size: 196 bytes

int SIGetResponse(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = OSDisableInterrupts();
  uVar2 = SIGetStatus(param_1);
  if ((uVar2 & 0x20) != 0) {
    *(undefined4 *)(&DAT_8030c910 + param_1 * 8) = *(undefined4 *)(&DAT_cc006404 + param_1 * 0xc);
    *(undefined4 *)(&DAT_8030c914 + param_1 * 8) = *(undefined4 *)(&DAT_cc006408 + param_1 * 0xc);
    *(undefined4 *)(&DAT_8030c900 + param_1 * 4) = 1;
  }
  iVar3 = *(int *)(&DAT_8030c900 + param_1 * 4);
  *(undefined4 *)(&DAT_8030c900 + param_1 * 4) = 0;
  if (iVar3 != 0) {
    *param_2 = *(undefined4 *)(&DAT_8030c910 + param_1 * 8);
    param_2[1] = *(undefined4 *)(&DAT_8030c914 + param_1 * 8);
  }
  OSRestoreInterrupts(uVar1);
  return iVar3;
}

