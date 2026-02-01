// Function: __CARDTxHandler
// Entry: 801987a8
// Size: 168 bytes

void __CARDTxHandler(int chan)

{
  bool bVar1;
  uint uVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar4 = EXIDeselect(chan);
  uVar2 = countLeadingZeros(uVar4);
  EXIUnlock(chan);
  pcVar3 = *(code **)(&DAT_80327608 + chan * 0x110);
  if (pcVar3 != (code *)0x0) {
    bVar1 = false;
    *(undefined4 *)(&DAT_80327608 + chan * 0x110) = 0;
    if ((uVar2 >> 5 == 0) && (iVar5 = EXIProbe(chan), iVar5 != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0xfffffffd;
    }
    (*pcVar3)(chan,uVar4);
  }
  return;
}

