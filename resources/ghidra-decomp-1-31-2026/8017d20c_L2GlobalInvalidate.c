// Function: L2GlobalInvalidate
// Entry: 8017d20c
// Size: 152 bytes

void L2GlobalInvalidate(void)

{
  uint uVar1;
  
  sync(0);
  uVar1 = PPCMfl2cr();
  PPCMtl2cr(uVar1 & 0x7fffffff);
  sync(0);
  uVar1 = PPCMfl2cr();
  PPCMtl2cr(uVar1 | 0x200000);
  do {
    uVar1 = PPCMfl2cr();
  } while ((uVar1 & 1) != 0);
  uVar1 = PPCMfl2cr();
  PPCMtl2cr(uVar1 & 0xffdfffff);
  while (uVar1 = PPCMfl2cr(), (uVar1 & 1) != 0) {
    DBPrintf(s_>>>_L2_INVALIDATE___SHOULD_NEVER_802169e8);
  }
  return;
}

