// Function: Init__10CRedDriverFv
// Entry: 801be654
// Size: 1316 bytes

void Init__10CRedDriverFv(CRedDriver *redDriver)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  DAT_8032f3c4 = 0;
  DAT_8032f3c0 = 1;
  DAT_8032f408 = 1;
  DAT_8032f3c8 = 0;
  GetSoundMode__10CRedDriverFv(redDriver);
  if (DAT_8032f400 == 2) {
    AXSetMode(2);
  }
  else {
    AXSetMode(0);
  }
  DAT_8032f3cc = RedNew__Fi(400);
  memset(DAT_8032f3cc,0,400);
  AXSetCompressor(0);
  DAT_8032f414 = 0;
  DAT_8032f404 = 0;
  DAT_8032f410 = 0;
  DAT_8032f40c = 0;
  DAT_8032f468 = 0;
  DAT_8032f42c = 0;
  DAT_8032f434 = 0x1ff;
  DAT_8032f430 = 0x1ff;
  iVar6 = 0;
  do {
    iVar5 = iVar6 + 1;
    (&DAT_8032e12c)[iVar6] = 0;
    iVar6 = iVar5;
  } while (iVar5 < 4);
  DAT_8032f3d0 = RedNew__Fi(0x1000);
  memset(DAT_8032f3d0,0,0x1000);
  DAT_8032f418 = RedNew__Fi(0x400);
  memset(DAT_8032f418,0,0x400);
  DAT_8032f41c = RedNew__Fi(0xc);
  memset(DAT_8032f41c,0,0xc);
  DAT_8032f420 = RedNew__Fi(0xc);
  memset(DAT_8032f420,0,0xc);
  DAT_8032f3d4 = RedNew__Fi(0x2000);
  DAT_8032f3d8 = DAT_8032f3d4;
  DAT_8032f3dc = DAT_8032f3d4;
  memset(DAT_8032f3d4,0,0x2000);
  DAT_8032f3f0 = RedNew__Fi(0x1250);
  DAT_8032f3f4 = DAT_8032f3f0;
  memset(DAT_8032f3f0,0,0x1250);
  *(undefined4 *)(DAT_8032f3f4 + 0xdd8) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x944) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x4b0) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x1c) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x1210) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0xd7c) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x8e8) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0x454) = 0x1ff000;
  *(undefined4 *)(DAT_8032f3f4 + 0xd98) = 0xffffffff;
  *(undefined4 *)(DAT_8032f3f4 + 0x904) = 0xffffffff;
  *(undefined4 *)(DAT_8032f3f4 + 0x470) = 0xffffffff;
  DAT_8032f3fc = RedNew__Fi(0x600);
  memset(DAT_8032f3fc,0,0x600);
  DAT_8032f444 = RedNew__Fi(0x3000);
  memset(DAT_8032f444,0,0x3000);
  iVar6 = 0;
  do {
    iVar2 = iVar6 * 0xc0;
    iVar5 = iVar6 * 0x8000000;
    iVar4 = iVar6 >> 0x1f;
    iVar6 = iVar6 + 1;
    *(uint *)(DAT_8032f444 + iVar2 + 0xa8) = (iVar4 * 0x20 | (uint)(iVar5 + iVar4) >> 0x1b) - iVar4;
  } while (iVar6 < 0x40);
  uRam8032f44c = 0;
  DAT_8032f448 = 0;
  uVar3 = RedNew__Fi(0x2a80);
  *(undefined4 *)(DAT_8032f3f0 + 0xdbc) = uVar3;
  memset(*(undefined4 *)(DAT_8032f3f0 + 0xdbc),0,0x2a80);
  iVar5 = 0;
  iVar6 = *(int *)(DAT_8032f3f0 + 0xdbc);
  do {
    iVar4 = iVar5 * 0x154;
    cVar1 = (char)iVar5;
    iVar5 = iVar5 + 1;
    *(char *)(iVar6 + iVar4 + 0x14e) = cVar1 + ' ';
  } while (iVar5 < 0x20);
  DAT_8032f450 = RedNew__Fi(0x154);
  memset(DAT_8032f450,0,0x154);
  DAT_8032f474 = RedNew__Fi(0x18);
  memset(DAT_8032f474,0,0x18);
  uRam8032f47c = 0;
  DAT_8032f478 = 0;
  DAT_8032f428 = (undefined4 *)RedNew__Fi(0x10);
  *DAT_8032f428 = 0xffffffff;
  DAT_8032f424 = 0;
  DAT_8032f438 = RedNew__Fi(0x4c0);
  memset(DAT_8032f438,0,0x4c0);
  DAT_8032f43c = 0;
  memset(&DAT_8032b860,0,0x1c00);
  DAT_8032f3e0 = &DAT_8032b860;
  DAT_8032f3e8 = &DAT_8032b860;
  puRam8032f3e4 = &DAT_8032c660;
  puRam8032f3ec = &DAT_8032c660;
  DAT_8032f3b8 = 0;
  AXRegisterCallback(_RedAXCallback__Fv);
  AXFXSetHooks(ReverbAreaAlloc__FUl,ReverbAreaFree__FPv);
  InitReverb__Fv();
  OSInitSemaphore((OSSemaphore *)&DAT_8032ddd8,0);
  DAT_8032f464 = RedNew__Fi(0x1000);
  OSCreateThread(&DAT_8032dac0,_DmaExecuteThread__FPv,0,DAT_8032f464 + 0x1000,0x1000,3,1);
  OSResumeThread(&DAT_8032dac0);
  OSInitSemaphore((OSSemaphore *)&DAT_8032daa0,0);
  DAT_8032f45c = RedNew__Fi(0x1000);
  OSCreateThread(&DAT_8032d788,_WaveSettingThread__FPv,&DAT_8032daac,DAT_8032f45c + 0x1000,0x1000,4,
                 1);
  OSResumeThread(&DAT_8032d788);
  OSInitSemaphore((OSSemaphore *)&DAT_8032e120,0);
  DAT_8032f46c = RedNew__Fi(0x1000);
  OSCreateThread(&DAT_8032de08,_MusicSkipThread__FPv,0,DAT_8032f46c + 0x1000,0x1000,4,1);
  OSResumeThread(&DAT_8032de08);
  OSInitSemaphore((OSSemaphore *)&DAT_8032d778,0);
  DAT_8032f458 = 0;
  DAT_8032f454 = RedNew__Fi(0x1000);
  OSCreateThread(&DAT_8032d460,_MainThread__FPv,0,DAT_8032f454 + 0x1000,0x1000,4,1);
  OSResumeThread(&DAT_8032d460);
  return;
}

