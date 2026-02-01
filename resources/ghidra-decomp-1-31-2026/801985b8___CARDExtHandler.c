// Function: __CARDExtHandler
// Entry: 801985b8
// Size: 216 bytes

void __CARDExtHandler(int chan)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] != 0) {
    (&DAT_80327540)[chan * 0x44] = 0;
    EXISetExiCallback(chan,0);
    OSCancelAlarm(&DAT_80327620 + iVar2);
    pcVar1 = *(code **)(&DAT_8032760c + iVar2);
    if (pcVar1 != (code *)0x0) {
      *(undefined4 *)(&DAT_8032760c + iVar2) = 0;
      (*pcVar1)(chan,0xfffffffd);
    }
    if ((&DAT_80327544)[chan * 0x44] != -1) {
      (&DAT_80327544)[chan * 0x44] = 0xfffffffd;
    }
    pcVar1 = *(code **)(&DAT_80327604 + iVar2);
    if ((pcVar1 != (code *)0x0) && (6 < *(int *)(&DAT_80327564 + iVar2))) {
      *(undefined4 *)(&DAT_80327604 + iVar2) = 0;
      (*pcVar1)(chan,0xfffffffd);
    }
  }
  return;
}

