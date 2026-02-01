// Function: _MusicTrackDataExecute__FP12RedTrackDATAi
// Entry: 801c5cec
// Size: 1200 bytes

void _MusicTrackDataExecute__FP12RedTrackDATAi(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int local_58;
  int local_54;
  int local_50;
  
  uVar2 = 0;
  *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x10c) + param_2;
  if (*(int *)(param_1 + 0x30) != 0) {
    iVar3 = param_2;
    if (*(int *)(param_1 + 0x30) <= param_2) {
      iVar3 = *(int *)(param_1 + 0x30);
    }
    uVar2 = 2;
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - iVar3;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c) * iVar3;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    iVar3 = param_2;
    if (*(int *)(param_1 + 0x3c) <= param_2) {
      iVar3 = *(int *)(param_1 + 0x3c);
    }
    uVar2 = 2;
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) - iVar3;
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x38) * iVar3;
  }
  if (*(int *)(param_1 + 0x48) != 0) {
    iVar3 = param_2;
    if (*(int *)(param_1 + 0x48) <= param_2) {
      iVar3 = *(int *)(param_1 + 0x48);
    }
    uVar2 = 2;
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) - iVar3;
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44) * iVar3;
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    iVar3 = param_2;
    if (*(int *)(param_1 + 0x70) <= param_2) {
      iVar3 = *(int *)(param_1 + 0x70);
    }
    uVar2 = 2;
    *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) - iVar3;
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + *(int *)(param_1 + 0x6c) * iVar3;
  }
  if (*(int *)(param_1 + 0x110) != 0) {
    iVar3 = param_2;
    if (*(int *)(param_1 + 0x110) <= param_2) {
      iVar3 = *(int *)(param_1 + 0x110);
    }
    uVar2 = uVar2 | 1;
    *(int *)(param_1 + 0x110) = *(int *)(param_1 + 0x110) - iVar3;
    iVar3 = iVar3 * *(int *)(param_1 + 0x114);
    *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + iVar3;
    piVar4 = DAT_8032f444;
    do {
      if ((*piVar4 == param_1) && (piVar4[0x28] = piVar4[0x28] + iVar3, piVar4[1] != 0)) {
        iVar1 = PitchCompute__Fiiii(piVar4[0x28] + *DAT_8032f420,
                                    (int)*(short *)(param_1 + 0x142) +
                                    (int)*(short *)(param_1 + 0x13e),
                                    *(undefined4 *)(piVar4[1] + 0x14),
                                    (int)*(char *)(param_1 + 0x148));
        piVar4[0x26] = iVar1;
      }
      piVar4 = piVar4 + 0x30;
    } while (piVar4 < DAT_8032f444 + 0xc00);
  }
  if (*(int *)(param_1 + 0x74) != 0) {
    if (*(short *)(param_1 + 0x8c) != 0) {
      iVar3 = param_2;
      if (*(short *)(param_1 + 0x8c) <= param_2) {
        iVar3 = (int)*(short *)(param_1 + 0x8c);
      }
      *(short *)(param_1 + 0x8c) = *(short *)(param_1 + 0x8c) - (short)iVar3;
      *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + *(int *)(param_1 + 0x7c) * iVar3;
    }
    if (*(short *)(param_1 + 0x8e) != 0) {
      iVar3 = param_2;
      if (*(short *)(param_1 + 0x8e) <= param_2) {
        iVar3 = (int)*(short *)(param_1 + 0x8e);
      }
      *(short *)(param_1 + 0x8e) = *(short *)(param_1 + 0x8e) - (short)iVar3;
      *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + *(int *)(param_1 + 0x84) * iVar3;
    }
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    if (*(short *)(param_1 + 0xac) != 0) {
      iVar3 = param_2;
      if (*(short *)(param_1 + 0xac) <= param_2) {
        iVar3 = (int)*(short *)(param_1 + 0xac);
      }
      *(short *)(param_1 + 0xac) = *(short *)(param_1 + 0xac) - (short)iVar3;
      *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + *(int *)(param_1 + 0x9c) * iVar3;
    }
    if (*(short *)(param_1 + 0xae) != 0) {
      iVar3 = param_2;
      if (*(short *)(param_1 + 0xae) <= param_2) {
        iVar3 = (int)*(short *)(param_1 + 0xae);
      }
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) - (short)iVar3;
      *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + *(int *)(param_1 + 0xa4) * iVar3;
    }
  }
  piVar4 = DAT_8032f444;
  if (*(int *)(param_1 + 0xb4) != 0) {
    if (*(short *)(param_1 + 0xd0) != 0) {
      iVar3 = param_2;
      if (*(short *)(param_1 + 0xd0) <= param_2) {
        iVar3 = (int)*(short *)(param_1 + 0xd0);
      }
      *(short *)(param_1 + 0xd0) = *(short *)(param_1 + 0xd0) - (short)iVar3;
      *(int *)(param_1 + 0xb8) = *(int *)(param_1 + 0xb8) + *(int *)(param_1 + 0xbc) * iVar3;
    }
    piVar4 = DAT_8032f444;
    if (*(short *)(param_1 + 0xd2) != 0) {
      local_50 = param_2;
      if (*(short *)(param_1 + 0xd2) <= param_2) {
        local_50 = (int)*(short *)(param_1 + 0xd2);
      }
      *(short *)(param_1 + 0xd2) = *(short *)(param_1 + 0xd2) - (short)local_50;
      *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xc0) + *(int *)(param_1 + 0xc4) * local_50;
      piVar4 = DAT_8032f444;
    }
  }
  do {
    if (*piVar4 == param_1) {
      if (*(short *)(piVar4 + 10) != 0) {
        local_54 = param_2;
        if (*(short *)(piVar4 + 10) <= param_2) {
          local_54 = (int)*(short *)(piVar4 + 10);
        }
        *(short *)(piVar4 + 10) = *(short *)(piVar4 + 10) - (short)local_54;
      }
      if (*(short *)(piVar4 + 0xe) != 0) {
        local_58 = param_2;
        if (*(short *)(piVar4 + 0xe) <= param_2) {
          local_58 = (int)*(short *)(piVar4 + 0xe);
        }
        *(short *)(piVar4 + 0xe) = *(short *)(piVar4 + 0xe) - (short)local_58;
      }
      piVar4[0x2e] = piVar4[0x2e] | uVar2;
    }
    piVar4 = piVar4 + 0x30;
  } while (piVar4 < DAT_8032f444 + 0xc00);
  return;
}

