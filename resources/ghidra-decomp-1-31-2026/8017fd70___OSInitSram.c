// Function: __OSInitSram
// Entry: 8017fd70
// Size: 308 bytes

void __OSInitSram(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 local_10 [2];
  
  uVar7 = 0;
  FatalContext[0x14] = 0;
  FatalContext[0x15] = 0;
  DCInvalidateRange(0x8030bc40,0x40);
  iVar5 = EXILock(0,1,0);
  if (iVar5 != 0) {
    iVar5 = EXISelect(0,1,3);
    if (iVar5 == 0) {
      EXIUnlock(0);
    }
    else {
      local_10[0] = 0x20000100;
      uVar6 = EXIImm(0,local_10,4,1,0);
      uVar7 = countLeadingZeros(uVar6);
      uVar6 = EXISync(0);
      uVar1 = countLeadingZeros(uVar6);
      uVar6 = EXIDma(0,0x8030bc40,0x40,0,0);
      uVar2 = countLeadingZeros(uVar6);
      uVar6 = EXISync(0);
      uVar3 = countLeadingZeros(uVar6);
      uVar6 = EXIDeselect(0);
      uVar4 = countLeadingZeros(uVar6);
      EXIUnlock(0);
      uVar7 = countLeadingZeros((uVar7 | uVar1 | uVar2 | uVar3 | uVar4) >> 5);
      uVar7 = uVar7 >> 5;
    }
  }
  FatalContext[0x16] = uVar7;
  FatalContext[0x13] = 0x40;
  return;
}

