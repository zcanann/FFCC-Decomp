// Function: __CARDUnlockedHandler
// Entry: 80198850
// Size: 132 bytes

void __CARDUnlockedHandler(int chan)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = *(code **)(&DAT_8032761c + chan * 0x110);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_8032761c + chan * 0x110) = 0;
    iVar2 = EXIProbe(chan);
    if (iVar2 == 0) {
      uVar3 = 0xfffffffd;
    }
    else {
      uVar3 = 1;
    }
    (*pcVar1)(chan,uVar3);
  }
  return;
}

