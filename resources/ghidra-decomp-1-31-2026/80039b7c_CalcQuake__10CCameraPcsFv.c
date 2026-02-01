// Function: CalcQuake__10CCameraPcsFv
// Entry: 80039b7c
// Size: 1060 bytes

/* WARNING: Removing unreachable block (ram,0x80039bcc) */
/* WARNING: Removing unreachable block (ram,0x80039bd4) */

void CalcQuake__10CCameraPcsFv(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  double dVar9;
  Vec local_38;
  Vec local_2c;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  if ((System.m_scenegraphStepMode != 2) &&
     ((*(char *)(param_1 + 0x490) != '\x02' || (*(int *)(param_1 + 0x494) != 0)))) {
    uVar6 = rand();
    sVar4 = (short)((int)uVar6 >> 0x1f);
    *(ushort *)(param_1 + 0x49c) = ((ushort)uVar6 & 1 ^ -sVar4) + sVar4;
    *(short *)(param_1 + 0x49e) = 1 - *(short *)(param_1 + 0x49e);
    uVar6 = rand();
    sVar4 = (short)((int)uVar6 >> 0x1f);
    *(ushort *)(param_1 + 0x4a0) = ((ushort)uVar6 & 1 ^ -sVar4) + sVar4;
    if (*(short *)(param_1 + 0x49c) == 0) {
      local_2c.x = -*(float *)(param_1 + 0x4a4);
    }
    else {
      local_2c.x = *(float *)(param_1 + 0x4a4);
    }
    if (*(short *)(param_1 + 0x49e) == 0) {
      local_2c.y = -*(float *)(param_1 + 0x4a8);
    }
    else {
      local_2c.y = *(float *)(param_1 + 0x4a8);
    }
    if (*(short *)(param_1 + 0x4a0) == 0) {
      local_2c.z = -*(float *)(param_1 + 0x4ac);
    }
    else {
      local_2c.z = *(float *)(param_1 + 0x4ac);
    }
    local_38.z = FLOAT_8032fa34;
    local_38.y = FLOAT_8032fa34;
    local_38.x = FLOAT_8032fa34;
    uVar6 = rand();
    uVar1 = (ushort)((uint)uVar6 >> 0x1f);
    uVar7 = rand();
    uVar2 = (ushort)((uint)uVar7 >> 0x1f);
    uVar8 = rand();
    uVar3 = (ushort)((uint)uVar8 >> 0x1f);
    if (((ushort)uVar6 & 1 ^ uVar1) == uVar1) {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b0),&Math);
    }
    else {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b0),&Math);
      dVar9 = -dVar9;
    }
    local_38.x = (float)dVar9;
    if (((ushort)uVar7 & 1 ^ uVar2) == uVar2) {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b4),&Math);
    }
    else {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b4),&Math);
      dVar9 = -dVar9;
    }
    local_38.y = (float)dVar9;
    if (((ushort)uVar8 & 1 ^ uVar3) == uVar3) {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b8),&Math);
    }
    else {
      dVar9 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x4b8),&Math);
      dVar9 = -dVar9;
    }
    fVar5 = FLOAT_8032fa34;
    local_38.z = (float)dVar9;
    if (*(char *)(param_1 + 0x490) == '\x02') {
      PSVECAdd(&local_2c,&local_38,&local_2c);
      PSVECAdd(&local_2c,(Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xe0));
      local_2c.z = FLOAT_8032fa34;
      PSVECAdd(&local_2c,(Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xd4));
    }
    else if (*(char *)(param_1 + 0x490) == '\x01') {
      if (*(short *)(param_1 + 0x4bc) < 1) {
        if (*(int *)(param_1 + 0x494) == 0) {
          if (*(short *)(param_1 + 0x4c0) < 1) {
            *(undefined4 *)(param_1 + 0x494) = 0;
            *(undefined2 *)(param_1 + 0x4bc) = 0;
            *(undefined2 *)(param_1 + 0x4be) = 0;
            *(undefined2 *)(param_1 + 0x4c0) = 0;
            *(undefined2 *)(param_1 + 0x4c2) = 0;
            *(float *)(param_1 + 0x4ac) = fVar5;
            *(float *)(param_1 + 0x4a8) = fVar5;
            *(float *)(param_1 + 0x4a4) = fVar5;
            *(float *)(param_1 + 0x4b8) = fVar5;
            *(float *)(param_1 + 0x4b4) = fVar5;
            *(float *)(param_1 + 0x4b0) = fVar5;
          }
          else {
            uStack_14 = (int)*(short *)(param_1 + 0x4c0) ^ 0x80000000;
            uStack_1c = (int)*(short *)(param_1 + 0x4c2) ^ 0x80000000;
            local_18 = 0x43300000;
            local_20 = 0x43300000;
            PSVECScale((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032fa28) /
                       (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8032fa28),&local_2c,
                       &local_2c);
            PSVECSubtract(&local_2c,&local_38,&local_2c);
            PSVECAdd(&local_2c,(Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xe0));
            PSVECAdd(&local_2c,(Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xd4));
            *(short *)(param_1 + 0x4c0) = *(short *)(param_1 + 0x4c0) + -1;
          }
        }
        else {
          PSVECAdd(&local_2c,&local_38,&local_2c);
          PSVECAdd(&local_2c,(Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xe0));
          PSVECAdd(&local_2c,(Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xd4));
        }
      }
      else {
        uStack_1c = (int)*(short *)(param_1 + 0x4bc) ^ 0x80000000;
        uStack_14 = (int)*(short *)(param_1 + 0x4be) ^ 0x80000000;
        local_20 = 0x43300000;
        local_18 = 0x43300000;
        PSVECScale((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8032fa28) /
                   (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032fa28),&local_2c,
                   &local_2c);
        PSVECAdd(&local_2c,&local_38,&local_2c);
        PSVECAdd(&local_2c,(Vec *)(param_1 + 0xe0),(Vec *)(param_1 + 0xe0));
        PSVECAdd(&local_2c,(Vec *)(param_1 + 0xd4),(Vec *)(param_1 + 0xd4));
        *(short *)(param_1 + 0x4bc) = *(short *)(param_1 + 0x4bc) + -1;
        if ((*(short *)(param_1 + 0x4bc) == 0) && (*(int *)(param_1 + 0x498) == 0)) {
          *(undefined4 *)(param_1 + 0x494) = 0;
        }
      }
    }
  }
  return;
}

