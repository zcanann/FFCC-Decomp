// Function: _VolumeExecute__FP12RedVoiceDATAi
// Entry: 801c40c8
// Size: 664 bytes

void _VolumeExecute__FP12RedVoiceDATAi(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (param_2 != 0) {
    param_2 = param_2 + 1;
  }
  iVar4 = param_2 * ((*(int *)param_1[3] >> 0xc) + 1) >> 7;
  if (*(char *)((int)param_1 + 0x19) != '\0') {
    if (*(char *)((int)param_1 + 0x19) == '\0') {
      iVar2 = 0;
    }
    else {
      iVar2 = *(char *)((int)param_1 + 0x19) + 1;
    }
    iVar4 = iVar4 * iVar2 >> 7;
  }
  iVar2 = *(int *)(*param_1 + 0x4c) >> 0xc;
  if (iVar2 != 0) {
    iVar2 = iVar2 + 1;
  }
  uVar3 = *(byte *)(param_1[1] + 0x1a) & 0x7f;
  if ((*(byte *)(param_1[1] + 0x1a) & 0x7f) != 0) {
    uVar3 = uVar3 + 1;
  }
  iVar4 = (int)(((iVar4 * iVar2 >> 7) * (*(int *)param_1[2] >> 0xc) >> 9) * uVar3) >> 7;
  if (*(int *)(*param_1 + 0x94) != 0) {
    if (*(short *)(param_1 + 0xe) == 0) {
      iVar2 = *(int *)(*param_1 + 0xa0) >> 0xc;
      if (iVar2 != 0) {
        iVar2 = iVar2 + 1;
      }
      iVar1 = (**(code **)(*param_1 + 0x94))((uint)param_1[0xb] >> 0xc);
      iVar2 = (iVar4 * iVar2 >> 8) * (iVar1 >> 4) >> 0xc;
      if (param_1[0xc] != 0) {
        iVar1 = param_1[0xd];
        param_1[0xd] = param_1[0xd] + 1;
        iVar2 = (iVar2 * iVar1) / param_1[0xc];
        if (param_1[0xc] <= param_1[0xd]) {
          param_1[0xc] = 0;
        }
      }
      iVar4 = iVar4 + iVar2;
      param_1[0xb] = param_1[0xb] + *(int *)(*param_1 + 0x98);
      if (iVar4 < 0x8000) {
        if (iVar4 < 0) {
          iVar4 = 0;
        }
      }
      else {
        iVar4 = 0x7fff;
      }
    }
  }
  if (DAT_8032f400 == 1) {
    uVar3 = 0x40;
  }
  else if ((param_1[0x25] & 0xc0U) == 0) {
    if ((*(byte *)(param_1[1] + 0x1b) & 0x80) == 0) {
      uVar3 = *(int *)param_1[4] >> 0xc;
    }
    else {
      uVar3 = *(byte *)(param_1[1] + 0x1b) & 0x7f;
      if ((*(byte *)(param_1[1] + 0x1b) & 0x7f) == 0) {
        uVar3 = 0x40;
      }
    }
    if (param_1[0x11] != 0) {
      uVar3 = uVar3 + ((int)(uVar3 * param_1[0x11]) >> 7);
    }
    uVar3 = uVar3 + *(int *)(*param_1 + 0xcc) & 0xff;
  }
  else if ((param_1[0x25] & 0x40U) == 0) {
    uVar3 = 0x7f;
  }
  else {
    uVar3 = 0;
  }
  if (param_1[0x10] != 0) {
    iVar4 = iVar4 + (iVar4 * param_1[0x10] >> 7);
    if (iVar4 < 0x8000) {
      if (iVar4 < 0) {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 0x7fff;
    }
  }
  SetVoiceVolumeMix__FP12RedVoiceDATAii(param_1,uVar3,iVar4);
  param_1[0x24] = param_1[0x24] | 8;
  return;
}

