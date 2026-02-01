// Function: EXISync
// Entry: 8018258c
// Size: 588 bytes

undefined4 EXISync(int param_1)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  
  uVar8 = 0;
  do {
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 4) == 0) {
      return 0;
    }
  } while (((&DAT_cc00680c)[param_1 * 5] & 1) != 0);
  uVar3 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 0x10 + 0x29a] & 4) != 0) {
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 3) != 0) {
      if ((FatalContext[param_1 * 0x10 + 0x29a] & 2) != 0) {
        iVar4 = FatalContext[param_1 * 0x10 + 0x29b];
        if (iVar4 != 0) {
          puVar6 = (undefined *)FatalContext[param_1 * 0x10 + 0x29c];
          uVar2 = *(uint *)(&DAT_cc006810 + param_1 * 0x14);
          iVar5 = 0;
          if (0 < iVar4) {
            if ((8 < iVar4) && (uVar9 = iVar4 - 1U >> 3, 0 < iVar4 + -8)) {
              do {
                *puVar6 = (char)(uVar2 >> (3 - iVar5) * 8);
                puVar6[1] = (char)(uVar2 >> (3 - (iVar5 + 1)) * 8);
                puVar6[2] = (char)(uVar2 >> (3 - (iVar5 + 2)) * 8);
                puVar6[3] = (char)(uVar2 >> iVar5 * -8);
                puVar6[4] = (char)(uVar2 >> (3 - (iVar5 + 4)) * 8);
                puVar6[5] = (char)(uVar2 >> (3 - (iVar5 + 5)) * 8);
                puVar6[6] = (char)(uVar2 >> (3 - (iVar5 + 6)) * 8);
                puVar6[7] = (char)(uVar2 >> (3 - (iVar5 + 7)) * 8);
                puVar6 = puVar6 + 8;
                iVar5 = iVar5 + 8;
                uVar9 = uVar9 - 1;
              } while (uVar9 != 0);
            }
            iVar7 = iVar4 - iVar5;
            if (iVar5 < iVar4) {
              do {
                *puVar6 = (char)(uVar2 >> (3 - iVar5) * 8);
                puVar6 = puVar6 + 1;
                iVar5 = iVar5 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
        }
      }
      FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xfffffffc;
    }
    iVar4 = __OSGetDIConfig();
    if (((((iVar4 != 0xff) || (uVar2 = OSGetConsoleType(), (uVar2 & 0xf0000000) == 0x20000000)) ||
         (FatalContext[param_1 * 0x10 + 0x29b] != 4)) ||
        ((((&DAT_cc006800)[param_1 * 5] & 0x70) != 0 ||
         (((piVar1 = (int *)(&DAT_cc006810 + param_1 * 0x14), *piVar1 != 0x1010000 &&
           (*piVar1 != 0x5070000)) && (*piVar1 != 0x4220001)))))) || (DAT_800030e6 == -0x7e00)) {
      uVar8 = 1;
    }
  }
  OSRestoreInterrupts(uVar3);
  return uVar8;
}

