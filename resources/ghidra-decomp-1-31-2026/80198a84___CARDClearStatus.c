// Function: __CARDClearStatus
// Entry: 80198a84
// Size: 172 bytes

undefined4 __CARDClearStatus(undefined4 chan)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_c;
  
  iVar4 = EXISelect(chan,0,4);
  if (iVar4 == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    local_c = 0x89000000;
    uVar5 = EXIImm(chan,&local_c,1,1,0);
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

