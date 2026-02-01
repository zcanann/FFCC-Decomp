// Function: __MidiCtrl_WholeLoopStart__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7bcc
// Size: 628 bytes

void __MidiCtrl_WholeLoopStart__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int local_34 [3];
  
  iVar4 = param_1[0x121];
  param_1[0x11b] = param_1[0x11b] | 1;
  iVar5 = 1 - param_3[0x42];
  iVar6 = 0;
  for (piVar7 = (int *)*param_1; piVar7 < param_3; piVar7 = piVar7 + 0x55) {
    param_1[iVar6 + 10] = *piVar7;
    param_1[iVar6 + 0x4a] = piVar7[0x42] + iVar5;
    param_1[iVar6 + 0x8a] = piVar7[0x41];
    param_1[iVar6 + 0xca] = piVar7[9];
    iVar6 = iVar6 + 1;
  }
  local_34[0] = *piVar7;
  iVar1 = DeltaTimeSumup__FPPUc(local_34);
  param_1[iVar6 + 10] = local_34[0];
  param_1[iVar6 + 0x4a] = piVar7[0x42] + iVar1 + iVar5;
  param_1[iVar6 + 0x8a] = piVar7[0x41];
  piVar8 = piVar7 + 0x55;
  param_1[iVar6 + 0xca] = piVar7[9];
  iVar1 = ((int)piVar8 - *param_1) / 0x154 + ((int)piVar8 - *param_1 >> 0x1f);
  if (iVar1 - (iVar1 >> 0x1f) < (int)(uint)*(byte *)((int)param_1 + 0x491)) {
    for (; piVar8 < (int *)(*param_1 + (uint)*(byte *)((int)param_1 + 0x491) * 0x154);
        piVar8 = piVar8 + 0x55) {
      iVar1 = iVar5 + (piVar8[0x42] - iVar4);
      while ((iVar1 < 1 && (*piVar8 != 0))) {
        pbVar3 = (byte *)*piVar8;
        *piVar8 = (int)(pbVar3 + 1);
        (*(code *)(&PTR___MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA_8021ea10)
                  [*pbVar3])(param_1,param_2,piVar8);
        if (*piVar8 != 0) {
          iVar2 = DeltaTimeSumup__FPPUc(piVar8);
          iVar1 = iVar1 + iVar2;
          piVar8[0x42] = piVar8[0x42] + iVar2;
        }
      }
      param_1[iVar6 + 0xb] = *piVar8;
      param_1[iVar6 + 0x4b] = iVar1;
      param_1[iVar6 + 0x8b] = piVar8[0x41];
      param_1[iVar6 + 0xcb] = piVar8[9];
      iVar6 = iVar6 + 1;
    }
  }
  param_1[0x10d] = (int)*(short *)((int)param_1 + 0x48e);
  memmove(param_1 + 0x10e,param_1 + 3,0x10);
  param_1[0x10f] = param_1[0x10f] - iVar5;
  if (param_1[0x10f] < 0) {
    param_1[0x10f] = param_1[0x10f] + param_1[0x110];
    param_1[0x10e] = param_1[0x10e] + -1;
  }
  memmove(param_1 + 0x10a,param_1 + 0x112,0xc);
  return;
}

