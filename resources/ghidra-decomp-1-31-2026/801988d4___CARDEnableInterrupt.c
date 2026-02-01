// Function: __CARDEnableInterrupt
// Entry: 801988d4
// Size: 192 bytes

undefined4 __CARDEnableInterrupt(int chan,int enable)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_10 [2];
  
  iVar4 = EXISelect(chan,0,4);
  if (iVar4 == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    if (enable == 0) {
      local_10[0] = 0x81000000;
    }
    else {
      local_10[0] = 0x81010000;
    }
    uVar5 = EXIImm(chan,local_10,2,1,0);
    uVar1 = countLeadingZeros(uVar5);
    uVar5 = EXISync(chan);
    uVar2 = countLeadingZeros(uVar5);
    uVar5 = EXIDeselect(chan);
    uVar3 = countLeadingZeros(uVar5);
    if ((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0xfffffffd;
    }
  }
  return uVar5;
}

