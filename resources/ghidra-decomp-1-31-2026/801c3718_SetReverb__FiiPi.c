// Function: SetReverb__FiiPi
// Entry: 801c3718
// Size: 1324 bytes

undefined4 * SetReverb__FiiPi(uint param_1,int param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int unaff_r28;
  int *piVar4;
  
  DAT_8032f4b0[1] = 0;
  *DAT_8032f4b0 = 0;
  if (param_2 == 0) {
    _ClearReverb__Fi(param_1);
    puVar3 = DAT_8032f4b0;
  }
  else if (param_2 == 5) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    piVar4 = (int *)(DAT_8032f4ac + (param_1 & 1) * 0xc);
    if ((*piVar4 == 0) || (piVar4[2] != param_2)) {
      _ClearReverb__Fi(param_1);
      if (param_2 == 5) {
        _ClearReverb__Fi(1);
      }
      piVar4[2] = param_2;
      if (param_2 == 3) {
        iVar2 = RedNew__Fi(0x60);
        piVar4[1] = iVar2;
        *piVar4 = (int)AXFXDelayCallback;
        iVar2 = piVar4[1];
        uVar1 = *param_3;
        *(uint *)(iVar2 + 0x44) = uVar1;
        *(uint *)(iVar2 + 0x40) = uVar1;
        *(uint *)(iVar2 + 0x3c) = uVar1;
        uVar1 = param_3[1];
        *(uint *)(iVar2 + 0x50) = uVar1;
        *(uint *)(iVar2 + 0x4c) = uVar1;
        *(uint *)(iVar2 + 0x48) = uVar1;
        uVar1 = param_3[2];
        *(uint *)(iVar2 + 0x5c) = uVar1;
        *(uint *)(iVar2 + 0x58) = uVar1;
        *(uint *)(iVar2 + 0x54) = uVar1;
        unaff_r28 = AXFXDelayInit(iVar2);
      }
      else if (param_2 < 3) {
        if (param_2 == 1) {
          iVar2 = RedNew__Fi(0x154);
          piVar4[1] = iVar2;
          *piVar4 = (int)AXFXReverbStdCallback;
          iVar2 = piVar4[1];
          *(undefined *)(iVar2 + 0x13c) = 0;
          *(float *)(iVar2 + 0x150) =
               (float)((double)CONCAT44(0x43300000,*param_3 ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d58;
          *(float *)(iVar2 + 0x148) =
               (float)((double)CONCAT44(0x43300000,param_3[1] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d58;
          *(float *)(iVar2 + 0x140) =
               (float)((double)CONCAT44(0x43300000,param_3[2] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          *(float *)(iVar2 + 0x14c) =
               (float)((double)CONCAT44(0x43300000,param_3[3] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          *(float *)(iVar2 + 0x144) =
               (float)((double)CONCAT44(0x43300000,param_3[4] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          unaff_r28 = AXFXReverbStdInit(iVar2);
        }
        else if (0 < param_2) {
          iVar2 = RedNew__Fi(0x1e0);
          piVar4[1] = iVar2;
          *piVar4 = (int)AXFXReverbHiCallback;
          iVar2 = piVar4[1];
          *(undefined *)(iVar2 + 0x1c4) = 0;
          *(float *)(iVar2 + 0x1d8) =
               (float)((double)CONCAT44(0x43300000,*param_3 ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d58;
          *(float *)(iVar2 + 0x1d0) =
               (float)((double)CONCAT44(0x43300000,param_3[1] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d58;
          *(float *)(iVar2 + 0x1c8) =
               (float)((double)CONCAT44(0x43300000,param_3[2] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          *(float *)(iVar2 + 0x1d4) =
               (float)((double)CONCAT44(0x43300000,param_3[3] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          *(float *)(iVar2 + 0x1cc) =
               (float)((double)CONCAT44(0x43300000,param_3[4] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          *(float *)(iVar2 + 0x1dc) =
               (float)((double)CONCAT44(0x43300000,param_3[5] ^ 0x80000000) - DOUBLE_80333d60) /
               FLOAT_80333d5c;
          unaff_r28 = AXFXReverbHiInit(iVar2);
        }
      }
      else if (param_2 == 5) {
        iVar2 = RedNew__Fi(0x26c);
        piVar4[1] = iVar2;
        *piVar4 = (int)AXFXReverbHiCallbackDpl2;
        iVar2 = piVar4[1];
        *(undefined *)(iVar2 + 0x254) = 0;
        *(float *)(iVar2 + 0x268) =
             (float)((double)CONCAT44(0x43300000,*param_3 ^ 0x80000000) - DOUBLE_80333d60) /
             FLOAT_80333d58;
        *(float *)(iVar2 + 0x260) =
             (float)((double)CONCAT44(0x43300000,param_3[1] ^ 0x80000000) - DOUBLE_80333d60) /
             FLOAT_80333d58;
        *(float *)(iVar2 + 600) =
             (float)((double)CONCAT44(0x43300000,param_3[2] ^ 0x80000000) - DOUBLE_80333d60) /
             FLOAT_80333d5c;
        *(float *)(iVar2 + 0x264) =
             (float)((double)CONCAT44(0x43300000,param_3[3] ^ 0x80000000) - DOUBLE_80333d60) /
             FLOAT_80333d5c;
        *(float *)(iVar2 + 0x25c) =
             (float)((double)CONCAT44(0x43300000,param_3[4] ^ 0x80000000) - DOUBLE_80333d60) /
             FLOAT_80333d5c;
        unaff_r28 = AXFXReverbHiInitDpl2(iVar2);
      }
      else if (param_2 < 5) {
        iVar2 = RedNew__Fi(0x9c);
        piVar4[1] = iVar2;
        *piVar4 = (int)AXFXChorusCallback;
        iVar2 = piVar4[1];
        *(uint *)(iVar2 + 0x90) = *param_3;
        *(uint *)(iVar2 + 0x94) = param_3[1];
        *(uint *)(iVar2 + 0x98) = param_3[2];
        unaff_r28 = AXFXChorusInit(iVar2);
      }
      if (unaff_r28 == 1) {
        if (param_1 == 0) {
          AXRegisterAuxACallback(*piVar4,piVar4[1]);
          puVar3 = DAT_8032f4b0;
        }
        else {
          AXRegisterAuxBCallback(*piVar4,piVar4[1]);
          puVar3 = DAT_8032f4b0;
        }
      }
      else {
        DAT_8032f4b0[1] = 0;
        *DAT_8032f4b0 = 0;
        puVar3 = DAT_8032f4b0;
      }
    }
    else {
      _SetReverbData__FP13RedReverbDATAPi(piVar4,param_3);
      puVar3 = DAT_8032f4b0;
    }
  }
  return puVar3;
}

