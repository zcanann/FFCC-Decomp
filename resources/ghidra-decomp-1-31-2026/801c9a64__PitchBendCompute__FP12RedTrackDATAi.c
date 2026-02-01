// Function: _PitchBendCompute__FP12RedTrackDATAi
// Entry: 801c9a64
// Size: 216 bytes

void _PitchBendCompute__FP12RedTrackDATAi(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = DAT_8032f444;
  do {
    if (*piVar2 == param_1) {
      if (piVar2[1] != 0) {
        if ((*(byte *)((int)piVar2 + 0x1a) & 3) == 0) {
          iVar1 = piVar2[0x28] + *DAT_8032f420;
        }
        else {
          iVar1 = piVar2[0x28] + *(int *)(param_1 + 0x5c);
        }
        iVar1 = PitchCompute__Fiiii(iVar1,*(short *)(param_1 + 0x142) + param_2,
                                    *(undefined4 *)(piVar2[1] + 0x14),
                                    (int)*(char *)(param_1 + 0x148));
        piVar2[0x26] = iVar1;
        piVar2[0x2e] = piVar2[0x2e] | 1;
      }
    }
    piVar2 = piVar2 + 0x30;
  } while (piVar2 < DAT_8032f444 + 0xc00);
  return;
}

