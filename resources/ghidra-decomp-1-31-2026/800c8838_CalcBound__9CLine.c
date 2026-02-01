// Function: CalcBound__9CLine
// Entry: 800c8838
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
  
  fVar2 = FLOAT_80330d30;
  fVar1 = FLOAT_80330d10;
  fVar4 = FLOAT_80330cec;
  *param_1 = FLOAT_80330d10;
  param_1[1] = fVar1;
  param_1[2] = fVar1;
  param_1[3] = fVar2;
  param_1[4] = fVar2;
  param_1[5] = fVar2;
  param_1[0x72] = fVar4;
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
      outVec = (Vec *)(param_1 + iVar3 * 8 + 0x2a);
      PSVECSubtract((Vec *)(pfVar6 + 0xc),(Vec *)(param_1 + iVar3 * 3 + 0xc),outVec);
      dVar7 = (double)PSVECMag(outVec);
      pfVar5[0x28] = (float)dVar7;
      fVar1 = FLOAT_80330cec;
      pfVar5[0x29] = param_1[0x72];
      param_1[0x72] = param_1[0x72] + pfVar5[0x28];
      if (fVar1 != pfVar5[0x28]) {
        PSVECNormalize(outVec,(Vec *)(param_1 + iVar3 * 8 + 0x2d));
      }
    }
    pfVar6 = pfVar6 + 3;
    pfVar5 = pfVar5 + 8;
  }
  return;
}

