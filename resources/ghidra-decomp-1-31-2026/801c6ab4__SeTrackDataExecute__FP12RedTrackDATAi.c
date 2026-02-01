// Function: _SeTrackDataExecute__FP12RedTrackDATAi
// Entry: 801c6ab4
// Size: 1416 bytes

void _SeTrackDataExecute__FP12RedTrackDATAi(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  
  if ((*(byte *)((int)param_1 + 0x26) & 2) == 0) {
    iVar4 = DAT_8032f444 + *(char *)((int)param_1 + 0x14e) * 0xc0;
    if (0 < param_2) {
      param_1[0x43] = param_1[0x43] + param_2;
    }
    if (param_1[0xc] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0xc] <= param_2) {
        iVar3 = param_1[0xc];
      }
      param_1[0xc] = param_1[0xc] - iVar3;
      param_1[10] = param_1[10] + param_1[0xb] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 2;
    }
    if (param_1[0xf] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0xf] <= param_2) {
        iVar3 = param_1[0xf];
      }
      param_1[0xf] = param_1[0xf] - iVar3;
      param_1[0xd] = param_1[0xd] + param_1[0xe] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 2;
    }
    if (param_1[0x12] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0x12] <= param_2) {
        iVar3 = param_1[0x12];
      }
      param_1[0x12] = param_1[0x12] - iVar3;
      param_1[0x10] = param_1[0x10] + param_1[0x11] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 2;
    }
    if (param_1[0x1c] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0x1c] <= param_2) {
        iVar3 = param_1[0x1c];
      }
      param_1[0x1c] = param_1[0x1c] - iVar3;
      param_1[0x1a] = param_1[0x1a] + param_1[0x1b] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 2;
    }
    if (param_1[0x15] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0x15] <= param_2) {
        iVar3 = param_1[0x15];
      }
      param_1[0x15] = param_1[0x15] - iVar3;
      if ((param_1[0x15] == 0) && (param_1[0x16] == 1)) {
        *param_1 = &DAT_8032ec30;
        param_1[0x42] = 1;
      }
      param_1[0x13] = param_1[0x13] + param_1[0x14] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 2;
    }
    if (param_1[0x19] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0x19] <= param_2) {
        iVar3 = param_1[0x19];
      }
      param_1[0x19] = param_1[0x19] - iVar3;
      param_1[0x17] = param_1[0x17] + param_1[0x18] * iVar3;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 1;
    }
    if (param_1[0x44] != 0) {
      iVar3 = param_2;
      if ((int)param_1[0x44] <= param_2) {
        iVar3 = param_1[0x44];
      }
      param_1[0x44] = param_1[0x44] - iVar3;
      iVar1 = param_1[0x45];
      param_1[0x48] = param_1[0x48] + iVar3 * iVar1;
      *(uint *)(iVar4 + 0xb8) = *(uint *)(iVar4 + 0xb8) | 1;
      *(int *)(iVar4 + 0xa0) = *(int *)(iVar4 + 0xa0) + iVar3 * iVar1;
    }
    if (((*(uint *)(iVar4 + 0xb8) & 1) != 0) && (*(int *)(iVar4 + 4) != 0)) {
      uVar2 = PitchCompute__Fiiii(*(int *)(iVar4 + 0xa0) + param_1[0x17],
                                  (int)*(short *)((int)param_1 + 0x142) +
                                  (int)*(short *)((int)param_1 + 0x13e),
                                  *(undefined4 *)(*(int *)(iVar4 + 4) + 0x14),
                                  (int)*(char *)(param_1 + 0x52));
      *(undefined4 *)(iVar4 + 0x98) = uVar2;
    }
    if (param_1[0x1d] != 0) {
      if (*(short *)(param_1 + 0x23) != 0) {
        iVar3 = param_2;
        if (*(short *)(param_1 + 0x23) <= param_2) {
          iVar3 = (int)*(short *)(param_1 + 0x23);
        }
        *(short *)(param_1 + 0x23) = *(short *)(param_1 + 0x23) - (short)iVar3;
        param_1[0x1e] = param_1[0x1e] + param_1[0x1f] * iVar3;
      }
      if (*(short *)((int)param_1 + 0x8e) != 0) {
        iVar3 = param_2;
        if (*(short *)((int)param_1 + 0x8e) <= param_2) {
          iVar3 = (int)*(short *)((int)param_1 + 0x8e);
        }
        *(short *)((int)param_1 + 0x8e) = *(short *)((int)param_1 + 0x8e) - (short)iVar3;
        param_1[0x20] = param_1[0x20] + param_1[0x21] * iVar3;
      }
    }
    if (param_1[0x25] != 0) {
      if (*(short *)(param_1 + 0x2b) != 0) {
        iVar3 = param_2;
        if (*(short *)(param_1 + 0x2b) <= param_2) {
          iVar3 = (int)*(short *)(param_1 + 0x2b);
        }
        *(short *)(param_1 + 0x2b) = *(short *)(param_1 + 0x2b) - (short)iVar3;
        param_1[0x26] = param_1[0x26] + param_1[0x27] * iVar3;
      }
      if (*(short *)((int)param_1 + 0xae) != 0) {
        iVar3 = param_2;
        if (*(short *)((int)param_1 + 0xae) <= param_2) {
          iVar3 = (int)*(short *)((int)param_1 + 0xae);
        }
        *(short *)((int)param_1 + 0xae) = *(short *)((int)param_1 + 0xae) - (short)iVar3;
        param_1[0x28] = param_1[0x28] + param_1[0x29] * iVar3;
      }
    }
    if (param_1[0x2d] != 0) {
      if (*(short *)(param_1 + 0x34) != 0) {
        local_4c = param_2;
        if (*(short *)(param_1 + 0x34) <= param_2) {
          local_4c = (int)*(short *)(param_1 + 0x34);
        }
        *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) - (short)local_4c;
        param_1[0x2e] = param_1[0x2e] + param_1[0x2f] * local_4c;
      }
      if (*(short *)((int)param_1 + 0xd2) != 0) {
        local_50 = param_2;
        if (*(short *)((int)param_1 + 0xd2) <= param_2) {
          local_50 = (int)*(short *)((int)param_1 + 0xd2);
        }
        *(short *)((int)param_1 + 0xd2) = *(short *)((int)param_1 + 0xd2) - (short)local_50;
        param_1[0x30] = param_1[0x30] + param_1[0x31] * local_50;
      }
    }
    if (*(short *)(iVar4 + 0x28) != 0) {
      local_54 = param_2;
      if (*(short *)(iVar4 + 0x28) <= param_2) {
        local_54 = (int)*(short *)(iVar4 + 0x28);
      }
      *(short *)(iVar4 + 0x28) = *(short *)(iVar4 + 0x28) - (short)local_54;
    }
    if (*(short *)(iVar4 + 0x38) != 0) {
      local_58 = param_2;
      if (*(short *)(iVar4 + 0x38) <= param_2) {
        local_58 = (int)*(short *)(iVar4 + 0x38);
      }
      *(short *)(iVar4 + 0x38) = *(short *)(iVar4 + 0x38) - (short)local_58;
    }
  }
  return;
}

