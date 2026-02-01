// Function: _PitchExecute__FP12RedVoiceDATA
// Entry: 801c4360
// Size: 428 bytes

void _PitchExecute__FP12RedVoiceDATA(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = 0;
  if ((*(int *)(*param_1 + 0x74) != 0) && (*(short *)(param_1 + 10) == 0)) {
    uVar4 = *(int *)(*param_1 + 0x80) >> 0xc;
    if ((int)uVar4 < 0x80) {
      iVar3 = (uVar4 + 1) * 2;
    }
    else {
      iVar3 = ((uVar4 & 0x7f) + 1) * 0x18;
    }
    if ((*(byte *)((int)param_1 + 0x1a) & 3) == 0) {
      iVar2 = param_1[0x28] + *DAT_8032f420;
    }
    else {
      iVar2 = param_1[0x28] + *(int *)(*param_1 + 0x5c);
    }
    iVar3 = PitchCompute__Fiiii(iVar2,(int)*(short *)(*param_1 + 0x142) +
                                      *(short *)(*param_1 + 0x13e) + iVar3,
                                *(undefined4 *)(param_1[1] + 0x14),(int)*(char *)(*param_1 + 0x148))
    ;
    iVar1 = param_1[0x26];
    iVar2 = (**(code **)(*param_1 + 0x74))((uint)param_1[7] >> 0xc);
    iVar3 = (iVar3 - iVar1) * (iVar2 >> 4) >> 0xc;
    if (param_1[8] != 0) {
      iVar2 = param_1[9];
      param_1[9] = param_1[9] + 1;
      iVar3 = (iVar3 * iVar2) / param_1[8];
      if (param_1[8] <= param_1[9]) {
        param_1[8] = 0;
      }
    }
    if (iVar3 < 0) {
      iVar3 = iVar3 >> 1;
    }
    param_1[7] = param_1[7] + *(int *)(*param_1 + 0x78);
  }
  param_1[0x27] = iVar3 + param_1[0x26] + param_1[0xf];
  param_1[0x24] = param_1[0x24] | 0x10;
  return;
}

