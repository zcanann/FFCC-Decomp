// Function: McChkConnect__14CMemoryCardManFi
// Entry: 800c20bc
// Size: 132 bytes

undefined4 McChkConnect__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,int chan)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  undefined auStack_4 [4];
  
  iVar1 = CARDProbeEx(chan,auStack_4,&local_8);
  if (iVar1 == -1) {
    uVar2 = 1;
  }
  else if (iVar1 == 0) {
    if (local_8 == 0x2000) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xfffffffe;
    }
  }
  else if (iVar1 == -2) {
    uVar2 = 0xfffffffd;
  }
  else if (iVar1 == -5) {
    uVar2 = 0xfffffffc;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

