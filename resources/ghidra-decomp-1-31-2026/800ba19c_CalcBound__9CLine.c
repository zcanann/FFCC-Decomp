// Function: CalcBound__9CLine
// Entry: 800ba19c
// Size: 352 bytes

void CalcBound__9CLine(float *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  Vec *outVec;
  float *pfVar5;
  float *pfVar6;
  double dVar7;
  
  fVar2 = FLOAT_80330bc0;
  fVar1 = FLOAT_80330b5c;
  fVar4 = FLOAT_80330b30;
  *param_1 = FLOAT_80330b5c;
  param_1[1] = fVar1;
  param_1[2] = fVar1;
  param_1[3] = fVar2;
  param_1[4] = fVar2;
  param_1[5] = fVar2;
  param_1[0x2c4] = fVar4;
  pfVar5 = param_1;
  pfVar6 = param_1;
  for (fVar4 = 0.0; (uint)fVar4 < (uint)param_1[6]; fVar4 = (float)((int)fVar4 + 1)) {
    if (pfVar6[0xc] < *param_1) {
      *param_1 = pfVar6[0xc];
    }
    if (pfVar6[0xd] < param_1[1]) {
      param_1[1] = pfVar6[0xd];
    }
    if (pfVar6[0xe] < param_1[2]) {
      param_1[2] = pfVar6[0xe];
    }
    if (param_1[3] < pfVar6[0xc]) {
      param_1[3] = pfVar6[0xc];
    }
    if (param_1[4] < pfVar6[0xd]) {
      param_1[4] = pfVar6[0xd];
    }
    if (param_1[5] < pfVar6[0xe]) {
      param_1[5] = pfVar6[0xe];
    }
    if (fVar4 != 0.0) {
      iVar3 = (int)fVar4 + -1;
      outVec = (Vec *)(param_1 + iVar3 * 8 + 0xcc);
      PSVECSubtract((Vec *)(pfVar6 + 0xc),(Vec *)(param_1 + iVar3 * 3 + 0xc),outVec);
      dVar7 = (double)PSVECMag(outVec);
      pfVar5[0xca] = (float)dVar7;
      fVar1 = FLOAT_80330b30;
      pfVar5[0xcb] = param_1[0x2c4];
      param_1[0x2c4] = param_1[0x2c4] + pfVar5[0xca];
      if (fVar1 != pfVar5[0xca]) {
        PSVECNormalize(outVec,(Vec *)(param_1 + iVar3 * 8 + 0xcf));
      }
    }
    pfVar6 = pfVar6 + 3;
    pfVar5 = pfVar5 + 8;
  }
  return;
}

