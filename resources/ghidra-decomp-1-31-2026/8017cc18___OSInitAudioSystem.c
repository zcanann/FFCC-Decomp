// Function: __OSInitAudioSystem
// Entry: 8017cc18
// Size: 444 bytes

void __OSInitAudioSystem(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = OSGetArenaHi();
  memcpy((void *)(iVar5 + -0x80),0x81000000,0x80);
  memcpy((void *)0x81000000,&DAT_80216968,0x80);
  DCFlushRange(0x81000000,0x80);
  DAT_cc005012 = 0x43;
  DAT_cc00500a = 0x8ac;
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 | 1;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 1) != 0);
  DAT_cc005000 = 0;
  do {
    uVar1 = DAT_cc005004;
  } while ((uVar1 & 0x8000) != 0);
  Ramcc005020 = 0x1000000;
  DAT_cc005024 = 0;
  DAT_cc005028 = 0x20;
  uVar1 = DAT_cc00500a;
  while( true ) {
    if ((uVar1 & 0x20) != 0) break;
    uVar1 = DAT_cc00500a;
  }
  DAT_cc00500a = uVar1;
  iVar5 = OSGetTick();
  do {
    iVar6 = OSGetTick();
  } while (iVar6 - iVar5 < 0x892);
  Ramcc005020 = 0x1000000;
  DAT_cc005024 = 0;
  DAT_cc005028 = 0x20;
  uVar1 = DAT_cc00500a;
  while( true ) {
    if ((uVar1 & 0x20) != 0) break;
    uVar1 = DAT_cc00500a;
  }
  DAT_cc00500a = uVar1;
  uVar2 = DAT_cc00500a;
  DAT_cc00500a = uVar2 & 0xf7ff;
  do {
    uVar2 = DAT_cc00500a;
  } while ((uVar2 & 0x400) != 0);
  uVar2 = DAT_cc00500a;
  DAT_cc00500a = uVar2 & 0xfffb;
  uVar2 = DAT_cc005004;
  while( true ) {
    if ((uVar2 & 0x8000) != 0) break;
    uVar2 = DAT_cc005004;
  }
  uVar4 = DAT_cc00500a;
  uVar3 = DAT_cc005006;
  DAT_cc00500a = uVar4 | 4;
  DAT_cc00500a = 0x8ac;
  uVar4 = DAT_cc00500a;
  DAT_cc00500a = uVar4 | 1;
  do {
    uVar4 = DAT_cc00500a;
  } while ((uVar4 & 1) != 0);
  iVar5 = OSGetArenaHi(uVar1,uVar3,uVar2);
  memcpy((void *)0x81000000,iVar5 + -0x80,0x80);
  return;
}

