// Function: SelectThread
// Entry: 80180e84
// Size: 552 bytes

int SelectThread(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if (DAT_8032efd8 < 1) {
    iVar2 = OSGetCurrentContext();
    iVar1 = DAT_800000e4;
    if (iVar2 == DAT_800000e4) {
      if (DAT_800000e4 != 0) {
        if (*(short *)(DAT_800000e4 + 0x2c8) == 2) {
          if ((param_1 == 0) &&
             (iVar2 = countLeadingZeros(DAT_8032efd0), *(int *)(DAT_800000e4 + 0x2d0) <= iVar2)) {
            return 0;
          }
          *(undefined2 *)(DAT_800000e4 + 0x2c8) = 1;
          *(int *)(iVar1 + 0x2dc) = *(int *)(iVar1 + 0x2d0) * 8 + -0x7fcf4368;
          iVar2 = (*(int **)(iVar1 + 0x2dc))[1];
          if (iVar2 == 0) {
            **(int **)(iVar1 + 0x2dc) = iVar1;
          }
          else {
            *(int *)(iVar2 + 0x2e0) = iVar1;
          }
          *(int *)(iVar1 + 0x2e4) = iVar2;
          *(undefined4 *)(iVar1 + 0x2e0) = 0;
          *(int *)(*(int *)(iVar1 + 0x2dc) + 4) = iVar1;
          DAT_8032efd0 = DAT_8032efd0 | 1 << 0x1f - *(int *)(iVar1 + 0x2d0);
          DAT_8032efd4 = 1;
        }
        if (((*(ushort *)(iVar1 + 0x1a2) & 2) == 0) && (iVar1 = OSSaveContext(iVar1), iVar1 != 0)) {
          return 0;
        }
      }
      if (DAT_8032efd0 == 0) {
        (*DAT_8032eab0)(DAT_800000e4,0);
        DAT_800000e4 = 0;
        OSSetCurrentContext(0x8030c3c8);
        do {
          OSEnableInterrupts();
          do {
          } while (DAT_8032efd0 == 0);
          OSDisableInterrupts();
        } while (DAT_8032efd0 == 0);
        OSClearContext(0x8030c3c8);
      }
      DAT_8032efd4 = 0;
      iVar4 = countLeadingZeros(DAT_8032efd0);
      piVar3 = FatalContext + iVar4 * 2 + 0x19;
      iVar1 = *piVar3;
      iVar2 = *(int *)(iVar1 + 0x2e0);
      if (iVar2 == 0) {
        FatalContext[iVar4 * 2 + 0x1a] = 0;
      }
      else {
        *(undefined4 *)(iVar2 + 0x2e4) = 0;
      }
      *piVar3 = iVar2;
      if (*piVar3 == 0) {
        DAT_8032efd0 = DAT_8032efd0 & ~(1 << 0x1f - iVar4);
      }
      *(undefined4 *)(iVar1 + 0x2dc) = 0;
      *(undefined2 *)(iVar1 + 0x2c8) = 2;
      (*DAT_8032eab0)(DAT_800000e4,iVar1);
      DAT_800000e4 = iVar1;
      OSSetCurrentContext(iVar1);
      OSLoadContext(iVar1);
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

