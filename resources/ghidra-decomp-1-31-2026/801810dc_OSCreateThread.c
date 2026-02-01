// Function: OSCreateThread
// Entry: 801810dc
// Size: 488 bytes

undefined4
OSCreateThread(int param_1,undefined4 param_2,undefined4 param_3,uint param_4,int param_5,
              int param_6,ushort param_7)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if ((param_6 < 0) || (0x1f < param_6)) {
    uVar2 = 0;
  }
  else {
    *(undefined2 *)(param_1 + 0x2c8) = 1;
    uVar1 = param_4 & 0xfffffff8;
    *(ushort *)(param_1 + 0x2ca) = param_7 & 1;
    *(int *)(param_1 + 0x2d4) = param_6;
    *(int *)(param_1 + 0x2d0) = param_6;
    *(undefined4 *)(param_1 + 0x2cc) = 1;
    *(undefined4 *)(param_1 + 0x2d8) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x2f0) = 0;
    *(undefined4 *)(param_1 + 0x2ec) = 0;
    *(undefined4 *)(param_1 + 0x2e8) = 0;
    *(undefined4 *)(param_1 + 0x2f8) = 0;
    *(undefined4 *)(param_1 + 0x2f4) = 0;
    *(undefined4 *)(uVar1 - 8) = 0;
    *(undefined4 *)(uVar1 - 4) = 0;
    OSInitContext(param_1,param_2,uVar1 - 8);
    *(code **)(param_1 + 0x84) = OSExitThread;
    *(undefined4 *)(param_1 + 0xc) = param_3;
    *(uint *)(param_1 + 0x304) = param_4;
    *(uint *)(param_1 + 0x308) = param_4 - param_5;
    **(undefined4 **)(param_1 + 0x308) = 0xdeadbabe;
    *(undefined4 *)(param_1 + 0x30c) = 0;
    *(undefined4 *)(param_1 + 0x310) = 0;
    *(undefined4 *)(param_1 + 0x314) = 0;
    OSDisableInterrupts();
    if (__OSErrorTable._64_4_ != 0) {
      iVar4 = 4;
      *(uint *)(param_1 + 0x19c) = *(uint *)(param_1 + 0x19c) | 0x900;
      *(ushort *)(param_1 + 0x1a2) = *(ushort *)(param_1 + 0x1a2) | 1;
      *(uint *)(param_1 + 0x194) = DAT_8032eaa0 & 0xf8 | 4;
      iVar3 = param_1;
      do {
        *(undefined4 *)(iVar3 + 0x94) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x90) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1cc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1c8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x9c) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x98) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1dc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xac) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1ec) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xbc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 500) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1f0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xc4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xc0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1fc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1f8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xcc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 200) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x204) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x200) = 0xffffffff;
        iVar3 = iVar3 + 0x40;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar3 = param_1;
    if (DAT_800000e0 != 0) {
      *(int *)(DAT_800000e0 + 0x2fc) = param_1;
      iVar3 = DAT_800000dc;
    }
    DAT_800000dc = iVar3;
    *(int *)(param_1 + 0x300) = DAT_800000e0;
    *(undefined4 *)(param_1 + 0x2fc) = 0;
    DAT_800000e0 = param_1;
    OSRestoreInterrupts();
    uVar2 = 1;
  }
  return uVar2;
}

