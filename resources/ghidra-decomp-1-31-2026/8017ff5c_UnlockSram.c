// Function: UnlockSram
// Entry: 8017ff5c
// Size: 776 bytes

/* WARNING: Removing unreachable block (ram,0x8017ffd0) */
/* WARNING: Removing unreachable block (ram,0x801800f8) */

uint UnlockSram(int param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  ushort *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint local_20 [3];
  
  if (param_1 != 0) {
    if (param_2 == 0) {
      if (2 < ((byte)FatalContext[7] & 3)) {
        FatalContext[7]._3_1_ = (byte)FatalContext[7] & 0xfc;
      }
      FatalContext[3]._2_2_ = 0;
      FatalContext[3]._0_2_ = 0;
      puVar7 = (ushort *)(FatalContext + 6);
      iVar10 = 4;
      do {
        FatalContext[3]._0_2_ = FatalContext[3]._0_2_ + *puVar7;
        uVar1 = *puVar7;
        puVar7 = puVar7 + 1;
        FatalContext[3]._2_2_ = FatalContext[3]._2_2_ + ~uVar1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    if (param_2 < FatalContext[0x13]) {
      FatalContext[0x13] = param_2;
    }
    uVar2 = FatalContext[0x13];
    iVar8 = 0x40 - FatalContext[0x13];
    iVar9 = FatalContext[0x13] + 0x8030bc40;
    iVar10 = EXILock(0,1,WriteSramCallback);
    if (iVar10 == 0) {
      FatalContext[0x16] = 0;
    }
    else {
      iVar10 = EXISelect(0,1,3);
      if (iVar10 == 0) {
        EXIUnlock(0);
        FatalContext[0x16] = 0;
      }
      else {
        local_20[0] = uVar2 * 0x40 + 0x100 | 0xa0000000;
        uVar6 = EXIImm(0,local_20,4,1,0);
        uVar2 = countLeadingZeros(uVar6);
        uVar6 = EXISync(0);
        uVar3 = countLeadingZeros(uVar6);
        uVar6 = EXIImmEx(0,iVar9,iVar8,1);
        uVar4 = countLeadingZeros(uVar6);
        uVar6 = EXIDeselect(0);
        uVar5 = countLeadingZeros(uVar6);
        EXIUnlock(0);
        uVar2 = countLeadingZeros((uVar2 | uVar3 | uVar4 | uVar5) >> 5);
        FatalContext[0x16] = uVar2 >> 5;
      }
    }
    if (FatalContext[0x16] != 0) {
      FatalContext[0x13] = 0x40;
    }
  }
  FatalContext[0x15] = 0;
  OSRestoreInterrupts(FatalContext[0x14]);
  return FatalContext[0x16];
}

