// Function: __CARDGetControlBlock
// Entry: 801994e0
// Size: 184 bytes

undefined4 __CARDGetControlBlock(int chan,CARDControl **pcard)

{
  undefined4 uVar1;
  
  if (((chan < 0) || (1 < chan)) || ((&DAT_8032764c)[chan * 0x44] == 0)) {
    uVar1 = 0xffffff80;
  }
  else {
    OSDisableInterrupts();
    if (((CARDControl *)(&DAT_80327540 + chan * 0x44))->attached == 0) {
      uVar1 = 0xfffffffd;
    }
    else if ((&DAT_80327544)[chan * 0x44] == -1) {
      uVar1 = 0xffffffff;
    }
    else {
      (&DAT_80327544)[chan * 0x44] = 0xffffffff;
      uVar1 = 0;
      *(undefined4 *)(&DAT_80327610 + chan * 0x110) = 0;
      *pcard = (CARDControl *)(&DAT_80327540 + chan * 0x44);
    }
    OSRestoreInterrupts();
  }
  return uVar1;
}

