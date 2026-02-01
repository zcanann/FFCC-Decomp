// Function: WriteSram
// Entry: 8017fc58
// Size: 280 bytes

uint WriteSram(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint local_14 [2];
  
  iVar4 = EXILock(0,1,WriteSramCallback);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    iVar4 = EXISelect(0,1,3);
    if (iVar4 == 0) {
      EXIUnlock(0);
      uVar5 = 0;
    }
    else {
      local_14[0] = param_2 * 0x40 + 0x100U | 0xa0000000;
      uVar6 = EXIImm(0,local_14,4,1,0);
      uVar5 = countLeadingZeros(uVar6);
      uVar6 = EXISync(0);
      uVar1 = countLeadingZeros(uVar6);
      uVar6 = EXIImmEx(0,param_1,param_3,1);
      uVar2 = countLeadingZeros(uVar6);
      uVar6 = EXIDeselect(0);
      uVar3 = countLeadingZeros(uVar6);
      EXIUnlock(0);
      uVar5 = countLeadingZeros((uVar5 | uVar1 | uVar2 | uVar3) >> 5);
      uVar5 = uVar5 >> 5;
    }
  }
  return uVar5;
}

