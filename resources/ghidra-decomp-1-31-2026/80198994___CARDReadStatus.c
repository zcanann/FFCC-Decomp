// Function: __CARDReadStatus
// Entry: 80198994
// Size: 240 bytes

undefined4 __CARDReadStatus(undefined4 chan,char *status)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_18 [3];
  
  iVar6 = EXISelect(chan,0,4);
  if (iVar6 == 0) {
    uVar7 = 0xfffffffd;
  }
  else {
    local_18[0] = 0x83000000;
    uVar7 = EXIImm(chan,local_18,2,1,0);
    uVar1 = countLeadingZeros(uVar7);
    uVar7 = EXISync(chan);
    uVar2 = countLeadingZeros(uVar7);
    uVar7 = EXIImm(chan,status,1,0,0);
    uVar3 = countLeadingZeros(uVar7);
    uVar7 = EXISync(chan);
    uVar4 = countLeadingZeros(uVar7);
    uVar7 = EXIDeselect(chan);
    uVar5 = countLeadingZeros(uVar7);
    if ((((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) && uVar4 >> 5 == 0) &&
        uVar5 >> 5 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 0xfffffffd;
    }
  }
  return uVar7;
}

