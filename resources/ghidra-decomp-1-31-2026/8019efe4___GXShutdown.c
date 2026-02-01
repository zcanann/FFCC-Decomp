// Function: __GXShutdown
// Entry: 8019efe4
// Size: 400 bytes

undefined4 __GXShutdown(int param_1)

{
  bool bVar1;
  int iVar2;
  short sVar4;
  uint uVar3;
  short *psVar5;
  int *piVar6;
  undefined8 uVar7;
  
  if (param_1 == 0) {
    if (DAT_8032f308 == 0) {
      psVar5 = (short *)(DAT_8032f2f4 + 0x4e);
      sVar4 = *psVar5;
      do {
        DAT_8032f2f8 = *(int *)psVar5;
        bVar1 = *psVar5 != sVar4;
        sVar4 = *psVar5;
      } while (bVar1);
      uVar7 = OSGetTime();
      DAT_8032f300 = (int)((ulonglong)uVar7 >> 0x20);
      DAT_8032f304 = (int)uVar7;
      DAT_8032f308 = 1;
      return 0;
    }
    uVar7 = OSGetTime();
    iVar2 = (int)((ulonglong)uVar7 >> 0x20);
    uVar3 = (uint)uVar7;
    piVar6 = (int *)(DAT_8032f2f4 + 0x4e);
    sVar4 = *(short *)piVar6;
    do {
      bVar1 = *(short *)piVar6 != sVar4;
      sVar4 = *(short *)piVar6;
    } while (bVar1);
    if ((iVar2 - ((uint)(uVar3 < DAT_8032f304) + DAT_8032f300) ^ 0x80000000) <
        (uVar3 - DAT_8032f304 < 10) + 0x80000000) {
      return 0;
    }
    if (*piVar6 != DAT_8032f2f8) {
      DAT_8032f2f8 = *piVar6;
      DAT_8032f300 = iVar2;
      DAT_8032f304 = uVar3;
      return 0;
    }
  }
  else {
    GXSetBreakPtCallback(0);
    GXSetDrawSyncCallback(0);
    GXSetDrawDoneCallback(0);
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    PPCSync();
    *(undefined2 *)(DAT_8032f2ec + 2) = 0;
    *(undefined2 *)(DAT_8032f2ec + 4) = 3;
    *(undefined *)(DAT_80333828 + 0x4f2) = 1;
    __GXAbort();
  }
  return 1;
}

