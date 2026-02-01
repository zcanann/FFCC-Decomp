// Function: C_QUATMtx
// Entry: 80187060
// Size: 600 bytes

void C_QUATMtx(Quat *outQuat,Mtx *inMatrix)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_18 [3];
  int local_c [3];
  
  local_c[0] = DAT_801e6600;
  local_c[1] = DAT_801e6604;
  local_c[2] = DAT_801e6608;
  fVar1 = inMatrix->value[0][0];
  fVar2 = inMatrix->value[1][1];
  fVar3 = inMatrix->value[2][2];
  dVar8 = (double)(fVar3 + fVar1 + fVar2);
  if (dVar8 <= (double)FLOAT_8033372c) {
    uVar4 = (uint)(fVar1 < fVar2);
    if (*(float *)((int)inMatrix->value + uVar4 * 0x14) < fVar3) {
      uVar4 = 2;
    }
    iVar5 = local_c[uVar4];
    iVar6 = local_c[iVar5];
    dVar8 = (double)(FLOAT_80333740 +
                    (*(float *)((int)inMatrix->value + uVar4 * 0x14) -
                    (*(float *)((int)inMatrix->value + iVar5 * 0x14) +
                    *(float *)((int)inMatrix->value + iVar6 * 0x14))));
    if ((double)FLOAT_8033372c < dVar8) {
      dVar7 = 1.0 / SQRT(dVar8);
      dVar7 = DOUBLE_80333730 * dVar7 * (DOUBLE_80333738 - dVar8 * dVar7 * dVar7);
      dVar7 = DOUBLE_80333730 * dVar7 * (DOUBLE_80333738 - dVar8 * dVar7 * dVar7);
      dVar8 = (double)(float)(dVar8 * DOUBLE_80333730 * dVar7 *
                                      (DOUBLE_80333738 - dVar8 * dVar7 * dVar7));
    }
    local_18[uVar4] = (float)((double)FLOAT_80333744 * dVar8);
    if ((double)FLOAT_8033372c != dVar8) {
      dVar8 = (double)(float)((double)FLOAT_80333744 / dVar8);
    }
    outQuat->w = (float)(dVar8 * (double)(inMatrix->value[iVar6][iVar5] -
                                         inMatrix->value[iVar5][iVar6]));
    local_18[iVar5] =
         (float)(dVar8 * (double)(inMatrix->value[uVar4][iVar5] + inMatrix->value[iVar5][uVar4]));
    local_18[iVar6] =
         (float)(dVar8 * (double)(inMatrix->value[uVar4][iVar6] + inMatrix->value[iVar6][uVar4]));
    outQuat->x = local_18[0];
    outQuat->y = local_18[1];
    outQuat->z = local_18[2];
  }
  else {
    dVar8 = (double)(float)((double)FLOAT_80333740 + dVar8);
    if ((double)FLOAT_8033372c < dVar8) {
      dVar7 = 1.0 / SQRT(dVar8);
      dVar7 = DOUBLE_80333730 * dVar7 * (DOUBLE_80333738 - dVar8 * dVar7 * dVar7);
      dVar7 = DOUBLE_80333730 * dVar7 * (DOUBLE_80333738 - dVar8 * dVar7 * dVar7);
      dVar8 = (double)(float)(dVar8 * DOUBLE_80333730 * dVar7 *
                                      (DOUBLE_80333738 - dVar8 * dVar7 * dVar7));
    }
    fVar1 = (float)((double)FLOAT_80333744 / dVar8);
    outQuat->w = (float)((double)FLOAT_80333744 * dVar8);
    outQuat->x = fVar1 * (inMatrix->value[2][1] - inMatrix->value[1][2]);
    outQuat->y = fVar1 * (inMatrix->value[0][2] - inMatrix->value[2][0]);
    outQuat->z = fVar1 * (inMatrix->value[1][0] - inMatrix->value[0][1]);
  }
  return;
}

