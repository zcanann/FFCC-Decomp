// Function: EXIImm
// Entry: 801821a4
// Size: 604 bytes

undefined4 EXIImm(int param_1,byte *param_2,int param_3,int param_4,undefined4 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar2 = OSDisableInterrupts();
  if (((FatalContext[param_1 * 0x10 + 0x29a] & 3) == 0) &&
     ((FatalContext[param_1 * 0x10 + 0x29a] & 4) != 0)) {
    FatalContext[param_1 * 0x10 + 0x298] = param_5;
    if (FatalContext[param_1 * 0x10 + 0x298] != 0) {
      EXIClearInterrupts(param_1,0,1,0);
      __OSUnmaskInterrupts(0x200000 >> param_1 * 3);
    }
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 2;
    if (param_4 != 0) {
      uVar1 = 0;
      iVar5 = 0;
      if (0 < param_3) {
        if ((8 < param_3) && (uVar6 = param_3 - 1U >> 3, pbVar3 = param_2, 0 < param_3 + -8)) {
          do {
            uVar1 = uVar1 | (uint)*pbVar3 << (3 - iVar5) * 8 |
                    (uint)pbVar3[1] << (3 - (iVar5 + 1)) * 8 |
                    (uint)pbVar3[2] << (3 - (iVar5 + 2)) * 8 | (uint)pbVar3[3] << iVar5 * -8 |
                    (uint)pbVar3[4] << (3 - (iVar5 + 4)) * 8 |
                    (uint)pbVar3[5] << (3 - (iVar5 + 5)) * 8 |
                    (uint)pbVar3[6] << (3 - (iVar5 + 6)) * 8 |
                    (uint)pbVar3[7] << (3 - (iVar5 + 7)) * 8;
            pbVar3 = pbVar3 + 8;
            iVar5 = iVar5 + 8;
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0);
        }
        pbVar3 = param_2 + iVar5;
        iVar4 = param_3 - iVar5;
        if (iVar5 < param_3) {
          do {
            uVar1 = uVar1 | (uint)*pbVar3 << (3 - iVar5) * 8;
            pbVar3 = pbVar3 + 1;
            iVar5 = iVar5 + 1;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
      }
      *(uint *)(&DAT_cc006810 + param_1 * 0x14) = uVar1;
    }
    FatalContext[param_1 * 0x10 + 0x29c] = param_2;
    iVar5 = param_3;
    if (param_4 == 1) {
      iVar5 = 0;
    }
    FatalContext[param_1 * 0x10 + 0x29b] = iVar5;
    (&DAT_cc00680c)[param_1 * 5] = param_4 << 2 | 1U | (param_3 + -1) * 0x10;
    OSRestoreInterrupts(uVar2);
    uVar2 = 1;
  }
  else {
    OSRestoreInterrupts(uVar2);
    uVar2 = 0;
  }
  return uVar2;
}

