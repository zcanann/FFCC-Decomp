// Function: ChkConnect__6McCtrlFi
// Entry: 800e7d4c
// Size: 124 bytes

int ChkConnect__6McCtrlFi(McCtrl *mcCtrl,int chan)

{
  int iVar1;
  
  iVar1 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,chan);
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == -1) {
    iVar1 = -3;
  }
  else if (iVar1 == -2) {
    iVar1 = -6;
  }
  else if (iVar1 == -3) {
    iVar1 = -2;
  }
  else if (iVar1 == -4) {
    iVar1 = -5;
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}

