// Function: __OSThreadInit
// Entry: 801809f8
// Size: 344 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __OSThreadInit(void)

{
  int iVar1;
  int iVar2;
  
  FatalContext[0x1d1]._0_2_ = 2;
  FatalContext[0x1d1]._2_2_ = 1;
  FatalContext[0x1d4] = 0x10;
  FatalContext[0x1d3] = 0x10;
  FatalContext[0x1d2] = 0;
  FatalContext[0x1d5] = 0xffffffff;
  FatalContext[0x1db] = 0;
  OSInitThreadQueue(0x8030c398);
  FatalContext[0x1dd] = 0;
  FatalContext[0x1dc] = 0;
  DAT_800000d8 = 0x8030c0b0;
  OSClearContext(0x8030c0b0);
  OSSetCurrentContext(0x8030c0b0);
  FatalContext[0x1e0] = 0x80373e08;
  FatalContext[0x1e1] = &DAT_80333e04;
  _DAT_80333e04 = 0xdeadbabe;
  (*DAT_8032eab0)(DAT_800000e4,0x8030c0b0);
  DAT_800000e4 = 0x8030c0b0;
  OSClearStack(0);
  DAT_8032efd0 = 0;
  iVar2 = 0;
  DAT_8032efd4 = 0;
  iVar1 = -0x7fcf4368;
  do {
    OSInitThreadQueue(iVar1);
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 8;
  } while (iVar2 < 0x20);
  OSInitThreadQueue(&DAT_800000dc);
  if (DAT_800000e0 == 0) {
    DAT_800000dc = 0x8030c0b0;
  }
  else {
    *(undefined4 *)(DAT_800000e0 + 0x2fc) = 0x8030c0b0;
  }
  FatalContext[0x1df] = DAT_800000e0;
  FatalContext[0x1de] = 0;
  DAT_800000e0 = 0x8030c0b0;
  OSClearContext(0x8030c3c8);
  DAT_8032efd8 = 0;
  return;
}

