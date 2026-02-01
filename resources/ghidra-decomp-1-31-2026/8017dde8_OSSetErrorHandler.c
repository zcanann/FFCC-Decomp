// Function: OSSetErrorHandler
// Entry: 8017dde8
// Size: 536 bytes

int OSSetErrorHandler(ushort param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = OSDisableInterrupts();
  iVar6 = *(int *)(__OSErrorTable + (uint)param_1 * 4);
  *(int *)(__OSErrorTable + (uint)param_1 * 4) = param_2;
  if (param_1 == 0x10) {
    uVar2 = PPCMfmsr();
    PPCMtmsr(uVar2 | 0x2000);
    uVar3 = PPCMffpscr();
    iVar5 = DAT_800000dc;
    if (param_2 == 0) {
      for (; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x2fc)) {
        *(uint *)(iVar5 + 0x19c) = *(uint *)(iVar5 + 0x19c) & 0xfffff6ff;
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffffff07;
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0x6005f8ff;
      }
      uVar3 = uVar3 & 0xffffff07;
      uVar2 = uVar2 & 0xfffff6ff;
    }
    else {
      for (; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x2fc)) {
        *(uint *)(iVar5 + 0x19c) = *(uint *)(iVar5 + 0x19c) | 0x900;
        if ((*(ushort *)(iVar5 + 0x1a2) & 1) == 0) {
          *(ushort *)(iVar5 + 0x1a2) = *(ushort *)(iVar5 + 0x1a2) | 1;
          iVar7 = 4;
          iVar4 = iVar5;
          do {
            *(undefined4 *)(iVar4 + 0x94) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x90) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1cc) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1c8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x9c) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x98) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1d4) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1d0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xa4) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xa0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1dc) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1d8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xac) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xa8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1e4) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1e0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xb4) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xb0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1ec) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1e8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xbc) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xb8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 500) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1f0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xc4) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xc0) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1fc) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x1f8) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0xcc) = 0xffffffff;
            *(undefined4 *)(iVar4 + 200) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x204) = 0xffffffff;
            *(undefined4 *)(iVar4 + 0x200) = 0xffffffff;
            iVar4 = iVar4 + 0x40;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
          *(undefined4 *)(iVar5 + 0x194) = 4;
        }
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | DAT_8032eaa0 & 0xf8;
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0x6005f8ff;
      }
      uVar2 = uVar2 | 0x900;
      uVar3 = uVar3 | DAT_8032eaa0 & 0xf8;
    }
    PPCMtfpscr(uVar3 & 0x6005f8ff);
    PPCMtmsr(uVar2);
  }
  OSRestoreInterrupts(uVar1);
  return iVar6;
}

