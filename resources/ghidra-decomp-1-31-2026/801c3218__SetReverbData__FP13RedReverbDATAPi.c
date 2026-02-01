// Function: _SetReverbData__FP13RedReverbDATAPi
// Entry: 801c3218
// Size: 1040 bytes

void _SetReverbData__FP13RedReverbDATAPi(int param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  int unaff_r28;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 3) {
    iVar1 = *(int *)(param_1 + 4);
    uVar2 = *param_2;
    *(uint *)(iVar1 + 0x44) = uVar2;
    *(uint *)(iVar1 + 0x40) = uVar2;
    *(uint *)(iVar1 + 0x3c) = uVar2;
    uVar2 = param_2[1];
    *(uint *)(iVar1 + 0x50) = uVar2;
    *(uint *)(iVar1 + 0x4c) = uVar2;
    *(uint *)(iVar1 + 0x48) = uVar2;
    uVar2 = param_2[2];
    *(uint *)(iVar1 + 0x5c) = uVar2;
    *(uint *)(iVar1 + 0x58) = uVar2;
    *(uint *)(iVar1 + 0x54) = uVar2;
    unaff_r28 = AXFXDelaySettings(iVar1);
  }
  else if (iVar1 < 3) {
    if (iVar1 == 1) {
      iVar1 = *(int *)(param_1 + 4);
      *(undefined *)(iVar1 + 0x13c) = 0;
      *(float *)(iVar1 + 0x150) =
           (float)((double)CONCAT44(0x43300000,*param_2 ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d58;
      *(float *)(iVar1 + 0x148) =
           (float)((double)CONCAT44(0x43300000,param_2[1] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d58;
      *(float *)(iVar1 + 0x140) =
           (float)((double)CONCAT44(0x43300000,param_2[2] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      *(float *)(iVar1 + 0x14c) =
           (float)((double)CONCAT44(0x43300000,param_2[3] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      *(float *)(iVar1 + 0x144) =
           (float)((double)CONCAT44(0x43300000,param_2[4] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      unaff_r28 = AXFXReverbStdSettings(iVar1);
    }
    else if (0 < iVar1) {
      iVar1 = *(int *)(param_1 + 4);
      *(undefined *)(iVar1 + 0x1c4) = 0;
      *(float *)(iVar1 + 0x1d8) =
           (float)((double)CONCAT44(0x43300000,*param_2 ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d58;
      *(float *)(iVar1 + 0x1d0) =
           (float)((double)CONCAT44(0x43300000,param_2[1] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d58;
      *(float *)(iVar1 + 0x1c8) =
           (float)((double)CONCAT44(0x43300000,param_2[2] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      *(float *)(iVar1 + 0x1d4) =
           (float)((double)CONCAT44(0x43300000,param_2[3] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      *(float *)(iVar1 + 0x1cc) =
           (float)((double)CONCAT44(0x43300000,param_2[4] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      *(float *)(iVar1 + 0x1dc) =
           (float)((double)CONCAT44(0x43300000,param_2[5] ^ 0x80000000) - DOUBLE_80333d60) /
           FLOAT_80333d5c;
      unaff_r28 = AXFXReverbHiSettings(iVar1);
    }
  }
  else if (iVar1 == 5) {
    iVar1 = *(int *)(param_1 + 4);
    *(undefined *)(iVar1 + 0x254) = 0;
    *(float *)(iVar1 + 0x268) =
         (float)((double)CONCAT44(0x43300000,*param_2 ^ 0x80000000) - DOUBLE_80333d60) /
         FLOAT_80333d58;
    *(float *)(iVar1 + 0x260) =
         (float)((double)CONCAT44(0x43300000,param_2[1] ^ 0x80000000) - DOUBLE_80333d60) /
         FLOAT_80333d58;
    *(float *)(iVar1 + 600) =
         (float)((double)CONCAT44(0x43300000,param_2[2] ^ 0x80000000) - DOUBLE_80333d60) /
         FLOAT_80333d5c;
    *(float *)(iVar1 + 0x264) =
         (float)((double)CONCAT44(0x43300000,param_2[3] ^ 0x80000000) - DOUBLE_80333d60) /
         FLOAT_80333d5c;
    *(float *)(iVar1 + 0x25c) =
         (float)((double)CONCAT44(0x43300000,param_2[4] ^ 0x80000000) - DOUBLE_80333d60) /
         FLOAT_80333d5c;
    unaff_r28 = AXFXReverbHiSettingsDpl2(iVar1);
  }
  else if (iVar1 < 5) {
    iVar1 = *(int *)(param_1 + 4);
    *(uint *)(iVar1 + 0x90) = *param_2;
    *(uint *)(iVar1 + 0x94) = param_2[1];
    *(uint *)(iVar1 + 0x98) = param_2[2];
    unaff_r28 = AXFXChorusSettings(iVar1);
  }
  if (unaff_r28 != 1) {
    DAT_8032f4b0[1] = 0;
    *DAT_8032f4b0 = 0;
  }
  return;
}

