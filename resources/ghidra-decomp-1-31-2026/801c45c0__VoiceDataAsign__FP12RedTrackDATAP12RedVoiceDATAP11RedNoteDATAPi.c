// Function: _VoiceDataAsign__FP12RedTrackDATAP12RedVoiceDATAP11RedNoteDATAPi
// Entry: 801c45c0
// Size: 1568 bytes

void _VoiceDataAsign__FP12RedTrackDATAP12RedVoiceDATAP11RedNoteDATAPi
               (int param_1,int *param_2,int *param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  char cVar4;
  ushort uVar3;
  int iVar5;
  uint uVar6;
  int local_38 [4];
  
  *param_2 = param_1;
  param_2[0x23] = 1;
  if ((*(int *)(param_1 + 0x118) == 0) || (*(int *)(param_1 + 0x120) < 0)) {
    *(int *)(param_1 + 0x120) = (int)*(char *)param_3 << 0x14;
    if (param_2[1] != 0) {
      if ((*(uint *)param_2[1] & 0x20000) == 0) {
        param_2[0x28] = (int)*(char *)param_3 << 0x14;
        if (*(int *)(*param_2 + 0x20) != 0) {
          iVar5 = param_2[0x28] >> 0x14;
          iVar1 = iVar5 / 0xc + (param_2[0x28] >> 0x1f);
          local_38[0] = (int)*(char *)(*(int *)(*param_2 + 0x20) +
                                      iVar5 + (iVar1 - (iVar1 >> 0x1f)) * -0xc);
          param_2[0x28] = param_2[0x28] + local_38[0] * 0x100000;
        }
      }
      else {
        param_2[0x28] = (int)*(char *)(param_2[1] + 0x18) << 0x14;
      }
    }
  }
  else {
    *(uint *)(param_1 + 0x120) = *(uint *)(param_1 + 0x120) & 0xfffff000;
    param_2[0x28] = *(int *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_1 + 0x118);
    local_38[0] = 0;
    uVar2 = DataAddCompute__FPiiPi
                      (local_38,*(char *)param_3 * 0x100 - (*(int *)(param_1 + 0x120) >> 0xc),
                       param_1 + 0x110);
    *(undefined4 *)(param_1 + 0x114) = uVar2;
  }
  param_2[6] = *param_3;
  param_2[2] = param_1 + 0x28;
  param_2[3] = param_1 + 0x34;
  param_2[4] = param_1 + 0x40;
  if (param_2[1] == 0) {
    memset(param_2 + 0x14,0,0xc);
  }
  else {
    memcpy(param_2 + 0x14,*(int *)(param_1 + 0x1c) + 0x50,0xc);
  }
  param_2[0x25] = *(int *)(param_1 + 0xfc);
  if (param_2[1] != 0) {
    if (*(char *)(param_2[1] + 0x1c) != '\0') {
      param_2[0x25] = param_2[0x25] & 0xffffc3ff;
      if (*(char *)(param_2[1] + 0x1c) == '\x01') {
        uVar6 = 0x3c00;
      }
      else {
        uVar6 = 0xc00;
      }
      param_2[0x25] = param_2[0x25] | uVar6;
    }
  }
  local_38[0] = (int)*(short *)(param_1 + 0x142) + (int)*(short *)(param_1 + 0x13e);
  if ((*(byte *)((int)param_2 + 0x1a) & 3) == 0) {
    iVar5 = param_2[0x28] + *DAT_8032f420;
  }
  else {
    iVar5 = param_2[0x28] + *(int *)(param_1 + 0x5c);
  }
  if (param_2[1] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = PitchCompute__Fiiii(iVar5,local_38[0],*(undefined4 *)(param_2[1] + 0x14),
                                (int)*(char *)(param_1 + 0x148));
  }
  param_2[0x26] = iVar5;
  if ((*(uint *)(param_1 + 0x104) & 0x100000) != 0) {
    if (((*(byte *)(param_1 + 0x26) & 5) == 0) || ((*(uint *)(param_1 + 0x104) & 0x280000) != 0)) {
      if (((*(byte *)(param_1 + 0x26) & 5) != 0) || ((*(uint *)(param_1 + 0x104) & 0x80000) != 0))
      goto LAB_801c4970;
    }
  }
  if (*(int *)(*param_2 + 0x74) != 0) {
    *(undefined2 *)(param_2 + 10) = *(undefined2 *)(param_1 + 0x90);
    local_38[0] = 0x100;
    if (*(int *)(param_1 + 0x78) >> 0xc != 0) {
      local_38[0] = 0x100 / (*(int *)(param_1 + 0x78) >> 0xc);
    }
    if (*(short *)(param_1 + 0x92) == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = (int)*(short *)(param_1 + 0x92) * local_38[0] * 4;
    }
    param_2[8] = iVar5;
    param_2[9] = 0;
    param_2[7] = 0;
  }
  if (*(int *)(*param_2 + 0x94) != 0) {
    *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_1 + 0xb0);
    local_38[0] = 0x100;
    if (*(int *)(param_1 + 0x98) >> 0xc != 0) {
      local_38[0] = 0x100 / (*(int *)(param_1 + 0x98) >> 0xc);
    }
    if (*(short *)(param_1 + 0xb2) == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = (int)*(short *)(param_1 + 0xb2) * local_38[0] * 4;
    }
    param_2[0xc] = iVar5;
    param_2[0xd] = 0;
    param_2[0xb] = 0;
  }
LAB_801c4970:
  if ((param_2[0x25] & 0x4000U) == 0) {
    param_2[0xf] = 0;
  }
  else {
    uVar6 = GetRandomData__Fv();
    iVar5 = ((uVar6 & 0xff) + 1) * param_2[0x26] * *(int *)(*param_2 + 0xe0);
    local_38[0] = iVar5 >> 0xf;
    if ((uVar6 & 0x80) == 0) {
      param_2[0xf] = local_38[0];
    }
    else {
      param_2[0xf] = -(iVar5 >> 0x10);
    }
  }
  if ((param_2[0x25] & 0x8000U) == 0) {
    param_2[0x10] = 0;
  }
  else {
    cVar4 = GetRandomData__Fv();
    param_2[0x10] = *(int *)(param_1 + 0xe4) * (int)cVar4 >> 8;
  }
  if ((param_2[0x25] & 0x10000U) == 0) {
    param_2[0x11] = 0;
  }
  else {
    cVar4 = GetRandomData__Fv();
    param_2[0x11] = *(int *)(param_1 + 0xe8) * (int)cVar4 >> 8;
  }
  if (param_2[1] == 0) {
    memset(param_2 + 0x14,0,0xc);
  }
  else {
    memcpy(param_2 + 0x14,param_2[1] + 0x50,0xc);
    if (*(char *)(param_1 + 0xdc) != -1) {
      *(undefined *)(param_2 + 0x16) = *(undefined *)(param_1 + 0xdc);
    }
    if (*(short *)(param_1 + 0xd4) != -1) {
      *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(param_1 + 0xd4);
    }
    if (*(char *)(param_1 + 0xdd) != -1) {
      *(undefined *)((int)param_2 + 0x59) = *(undefined *)(param_1 + 0xdd);
    }
    if (*(short *)(param_1 + 0xd6) != -1) {
      *(undefined2 *)((int)param_2 + 0x52) = *(undefined2 *)(param_1 + 0xd6);
    }
    if (*(char *)(param_1 + 0xde) != -1) {
      *(undefined *)((int)param_2 + 0x5a) = *(undefined *)(param_1 + 0xde);
    }
    if (*(short *)(param_1 + 0xd8) != -1) {
      *(undefined2 *)(param_2 + 0x15) = *(undefined2 *)(param_1 + 0xd8);
    }
    if (*(char *)(param_1 + 0xdf) != -1) {
      *(undefined *)((int)param_2 + 0x5b) = *(undefined *)(param_1 + 0xdf);
    }
    if (*(short *)(param_1 + 0xda) != -1) {
      *(undefined2 *)((int)param_2 + 0x56) = *(undefined2 *)(param_1 + 0xda);
    }
    if ((param_2[0x25] & 0x40000U) != 0) {
      uVar3 = GetRandomData__Fv();
      *(ushort *)(param_2 + 0x14) = (short)*(undefined4 *)(param_1 + 0xf0) * (uVar3 & 0xff);
    }
  }
  iVar5 = ((int)param_2 - DAT_8032f444) / 0xc0 + ((int)param_2 - DAT_8032f444 >> 0x1f);
  if (0x1f < iVar5 - (iVar5 >> 0x1f)) {
    param_4 = param_4 + 1;
  }
  if (((*(uint *)(param_1 + 0x104) & 0x80000) == 0) ||
     ((*(uint *)(param_1 + 0x104) & 0x100000) == 0)) {
    *(uint *)(param_1 + 0x104) = *(uint *)(param_1 + 0x104) | 0x100000;
    *param_4 = *param_4 | 1 << param_2[0x2a];
  }
  param_2[0x2e] = param_2[0x2e] | 3;
  return;
}

