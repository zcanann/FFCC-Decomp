// Function: GXAdjustForOverscan
// Entry: 801a27d4
// Size: 288 bytes

void GXAdjustForOverscan(uint *param_1,uint *param_2,int param_3,uint param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  
  sVar2 = (short)(param_3 << 1);
  iVar3 = (param_4 & 0x7fff) * 2;
  if (param_1 != param_2) {
    uVar4 = param_1[1];
    *param_2 = *param_1;
    param_2[1] = uVar4;
    uVar4 = param_1[3];
    param_2[2] = param_1[2];
    param_2[3] = uVar4;
    uVar4 = param_1[5];
    param_2[4] = param_1[4];
    param_2[5] = uVar4;
    uVar4 = param_1[7];
    param_2[6] = param_1[6];
    param_2[7] = uVar4;
    uVar4 = param_1[9];
    param_2[8] = param_1[8];
    param_2[9] = uVar4;
    uVar4 = param_1[0xb];
    param_2[10] = param_1[10];
    param_2[0xb] = uVar4;
    uVar4 = param_1[0xd];
    param_2[0xc] = param_1[0xc];
    param_2[0xd] = uVar4;
    param_2[0xe] = param_1[0xe];
  }
  *(short *)(param_2 + 1) = *(short *)(param_1 + 1) - sVar2;
  *(ushort *)((int)param_2 + 6) =
       *(ushort *)((int)param_1 + 6) -
       (short)((iVar3 * (uint)*(ushort *)((int)param_1 + 6)) / (uint)*(ushort *)(param_1 + 2));
  sVar1 = (short)iVar3;
  if ((param_1[5] == 0) && ((*param_1 & 2) != 2)) {
    *(short *)(param_2 + 2) = *(short *)(param_1 + 2) - (short)param_4;
  }
  else {
    *(short *)(param_2 + 2) = *(short *)(param_1 + 2) - sVar1;
  }
  *(short *)((int)param_2 + 0xe) = *(short *)((int)param_1 + 0xe) - sVar2;
  *(short *)(param_2 + 4) = *(short *)(param_1 + 4) - sVar1;
  *(short *)((int)param_2 + 10) = *(short *)((int)param_1 + 10) + (short)param_3;
  *(short *)(param_2 + 3) = *(short *)(param_1 + 3) + (short)param_4;
  return;
}

