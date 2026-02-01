// Function: TCIntrruptHandler
// Entry: 80183010
// Size: 536 bytes

void TCIntrruptHandler(short param_1,undefined4 param_2)

{
  int iVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  uint uVar8;
  undefined auStack_2d8 [712];
  
  iVar1 = (param_1 + -10) / 3;
  __OSMaskInterrupts(0x80000000 >> (int)param_1);
  (&DAT_cc006800)[iVar1 * 5] = (&DAT_cc006800)[iVar1 * 5] & 0x7f5 | 8;
  pcVar2 = (code *)FatalContext[iVar1 * 0x10 + 0x298];
  if (pcVar2 != (code *)0x0) {
    iVar5 = 0;
    FatalContext[iVar1 * 0x10 + 0x298] = 0;
    if ((FatalContext[iVar1 * 0x10 + 0x29a] & 3) != 0) {
      if ((FatalContext[iVar1 * 0x10 + 0x29a] & 2) != 0) {
        iVar4 = FatalContext[iVar1 * 0x10 + 0x29b];
        if (iVar4 != 0) {
          puVar6 = (undefined *)FatalContext[iVar1 * 0x10 + 0x29c];
          uVar3 = *(uint *)(&DAT_cc006810 + iVar1 * 0x14);
          if (0 < iVar4) {
            if ((8 < iVar4) && (uVar8 = iVar4 - 1U >> 3, 0 < iVar4 + -8)) {
              do {
                *puVar6 = (char)(uVar3 >> (3 - iVar5) * 8);
                puVar6[1] = (char)(uVar3 >> (3 - (iVar5 + 1)) * 8);
                puVar6[2] = (char)(uVar3 >> (3 - (iVar5 + 2)) * 8);
                puVar6[3] = (char)(uVar3 >> iVar5 * -8);
                puVar6[4] = (char)(uVar3 >> (3 - (iVar5 + 4)) * 8);
                puVar6[5] = (char)(uVar3 >> (3 - (iVar5 + 5)) * 8);
                puVar6[6] = (char)(uVar3 >> (3 - (iVar5 + 6)) * 8);
                puVar6[7] = (char)(uVar3 >> (3 - (iVar5 + 7)) * 8);
                puVar6 = puVar6 + 8;
                iVar5 = iVar5 + 8;
                uVar8 = uVar8 - 1;
              } while (uVar8 != 0);
            }
            iVar7 = iVar4 - iVar5;
            if (iVar5 < iVar4) {
              do {
                *puVar6 = (char)(uVar3 >> (3 - iVar5) * 8);
                puVar6 = puVar6 + 1;
                iVar5 = iVar5 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
        }
      }
      FatalContext[iVar1 * 0x10 + 0x29a] = FatalContext[iVar1 * 0x10 + 0x29a] & 0xfffffffc;
    }
    OSClearContext(auStack_2d8);
    OSSetCurrentContext(auStack_2d8);
    (*pcVar2)(iVar1,param_2);
    OSClearContext(auStack_2d8);
    OSSetCurrentContext(param_2);
  }
  return;
}

