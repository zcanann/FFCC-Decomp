// Function: MakeSpline1Dtable__5CMathFiPfPfPf
// Entry: 8001a708
// Size: 2328 bytes

/* WARNING: Type propagation algorithm not settling */

void MakeSpline1Dtable__5CMathFiPfPfPf
               (undefined4 param_1,int count,float *x_arr,float *y_arr,float *outSecondDerivatives)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  Spline *pSVar12;
  float *pfVar13;
  float *pfVar14;
  Spline *pSVar15;
  int iVar16;
  float *pfVar17;
  uint uVar18;
  uint uVar19;
  
  iVar16 = 0;
  if (0 < count) {
    if (8 < count) {
      uVar18 = count - 1U >> 3;
      pSVar12 = &h_spline;
      pSVar15 = &w_spline;
      pfVar9 = x_arr;
      pfVar10 = y_arr;
      if (0 < count + -8) {
        do {
          iVar16 = iVar16 + 8;
          pSVar12->field0_0x0 = (int)(pfVar9[1] - *pfVar9);
          pSVar15->field0_0x0 = (int)((pfVar10[1] - *pfVar10) / (float)pSVar12->field0_0x0);
          pSVar12->field1_0x4[0] = pfVar9[2] - pfVar9[1];
          pSVar15->field1_0x4[0] = (pfVar10[2] - pfVar10[1]) / pSVar12->field1_0x4[0];
          pSVar12->field1_0x4[1] = pfVar9[3] - pfVar9[2];
          pSVar15->field1_0x4[1] = (pfVar10[3] - pfVar10[2]) / pSVar12->field1_0x4[1];
          pSVar12->field1_0x4[2] = pfVar9[4] - pfVar9[3];
          pSVar15->field1_0x4[2] = (pfVar10[4] - pfVar10[3]) / pSVar12->field1_0x4[2];
          pSVar12->field1_0x4[3] = pfVar9[5] - pfVar9[4];
          pSVar15->field1_0x4[3] = (pfVar10[5] - pfVar10[4]) / pSVar12->field1_0x4[3];
          pSVar12->field1_0x4[4] = pfVar9[6] - pfVar9[5];
          pSVar15->field1_0x4[4] = (pfVar10[6] - pfVar10[5]) / pSVar12->field1_0x4[4];
          pSVar12->field1_0x4[5] = pfVar9[7] - pfVar9[6];
          pSVar15->field1_0x4[5] = (pfVar10[7] - pfVar10[6]) / pSVar12->field1_0x4[5];
          pfVar11 = pfVar9 + 8;
          pfVar17 = pfVar9 + 7;
          pfVar9 = pfVar9 + 8;
          pSVar12->field1_0x4[6] = *pfVar11 - *pfVar17;
          pfVar13 = pSVar12->field1_0x4;
          pSVar12 = (Spline *)(pSVar12->field1_0x4 + 7);
          pfVar11 = pfVar10 + 8;
          pfVar17 = pfVar10 + 7;
          pfVar10 = pfVar10 + 8;
          pSVar15->field1_0x4[6] = (*pfVar11 - *pfVar17) / pfVar13[6];
          pSVar15 = (Spline *)(pSVar15->field1_0x4 + 7);
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    iVar8 = count - iVar16;
    pfVar9 = x_arr + iVar16;
    pfVar10 = h_spline.field1_0x4 + iVar16 + -1;
    y_arr = y_arr + iVar16;
    pfVar11 = w_spline.field1_0x4 + iVar16 + -1;
    if (iVar16 < count) {
      do {
        pfVar17 = pfVar9 + 1;
        fVar3 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        *pfVar10 = *pfVar17 - fVar3;
        pfVar17 = y_arr + 1;
        fVar3 = *y_arr;
        y_arr = y_arr + 1;
        fVar4 = *pfVar10;
        pfVar10 = pfVar10 + 1;
        *pfVar11 = (*pfVar17 - fVar3) / fVar4;
        pfVar11 = pfVar11 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  w_spline.field1_0x4[count + -1] = (float)w_spline.field0_0x0;
  fVar3 = FLOAT_8032f75c;
  iVar16 = 1;
  if (1 < count) {
    if (8 < count + -1) {
      uVar18 = count - 2U >> 3;
      pfVar9 = x_arr + 1;
      pfVar10 = d_spline.field1_0x4;
      if (1 < count + -8) {
        do {
          iVar16 = iVar16 + 8;
          *pfVar10 = fVar3 * (pfVar9[1] - pfVar9[-1]);
          pfVar10[1] = fVar3 * (pfVar9[2] - *pfVar9);
          pfVar10[2] = fVar3 * (pfVar9[3] - pfVar9[1]);
          pfVar10[3] = fVar3 * (pfVar9[4] - pfVar9[2]);
          pfVar10[4] = fVar3 * (pfVar9[5] - pfVar9[3]);
          pfVar10[5] = fVar3 * (pfVar9[6] - pfVar9[4]);
          pfVar10[6] = fVar3 * (pfVar9[7] - pfVar9[5]);
          pfVar11 = pfVar9 + 8;
          pfVar17 = pfVar9 + 6;
          pfVar9 = pfVar9 + 8;
          pfVar10[7] = fVar3 * (*pfVar11 - *pfVar17);
          pfVar10 = pfVar10 + 8;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    fVar3 = FLOAT_8032f75c;
    iVar8 = count - iVar16;
    x_arr = x_arr + iVar16;
    pfVar9 = d_spline.field1_0x4 + iVar16 + -1;
    if (iVar16 < count) {
      do {
        pfVar10 = x_arr + 1;
        pfVar11 = x_arr + -1;
        x_arr = x_arr + 1;
        *pfVar9 = fVar3 * (*pfVar10 - *pfVar11);
        pfVar9 = pfVar9 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  pfVar9 = s_f_lvmtx.value[2] + count + 3;
  iVar16 = 1;
  d_spline.field1_0x4[count + -1] = FLOAT_8032f75c * ((float)h_spline.field0_0x0 + *pfVar9);
  if (0 < count) {
    if (8 < count) {
      uVar18 = count - 1U >> 3;
      pfVar11 = outSecondDerivatives + 1;
      pfVar10 = w_spline.field1_0x4;
      if (0 < count + -8) {
        do {
          iVar16 = iVar16 + 8;
          *pfVar11 = *pfVar10 - (float)((Spline *)(pfVar10 + -1))->field0_0x0;
          pfVar11[1] = pfVar10[1] - *pfVar10;
          pfVar11[2] = pfVar10[2] - pfVar10[1];
          pfVar11[3] = pfVar10[3] - pfVar10[2];
          pfVar11[4] = pfVar10[4] - pfVar10[3];
          pfVar11[5] = pfVar10[5] - pfVar10[4];
          pfVar11[6] = pfVar10[6] - pfVar10[5];
          pfVar17 = pfVar10 + 7;
          pfVar13 = pfVar10 + 6;
          pfVar10 = pfVar10 + 8;
          pfVar11[7] = *pfVar17 - *pfVar13;
          pfVar11 = pfVar11 + 8;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    iVar8 = (count + 1) - iVar16;
    pfVar11 = outSecondDerivatives + iVar16;
    pfVar10 = w_spline.field1_0x4 + iVar16 + -1;
    if (iVar16 <= count) {
      do {
        fVar3 = *pfVar10;
        pSVar12 = (Spline *)(pfVar10 + -1);
        pfVar10 = pfVar10 + 1;
        *pfVar11 = fVar3 - (float)pSVar12->field0_0x0;
        pfVar11 = pfVar11 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  w_spline.field1_0x4[0] = (float)h_spline.field0_0x0;
  fVar3 = d_spline.field1_0x4[count + -1];
  d_spline.field1_0x4[count + 0x3f] = *pfVar9;
  iVar16 = 2;
  pfVar9 = w_spline.field1_0x4;
  w_spline.field1_0x4[count + -1] = fVar3;
  fVar3 = FLOAT_8032f740;
  if (2 < count + -1) {
    if (8 < count + -3) {
      pfVar10 = w_spline.field1_0x4 + 1;
      uVar18 = count - 4U >> 3;
      if (2 < count + -9) {
        do {
          *pfVar10 = fVar3;
          iVar16 = iVar16 + 8;
          pfVar10[1] = fVar3;
          pfVar10[2] = fVar3;
          pfVar10[3] = fVar3;
          pfVar10[4] = fVar3;
          pfVar10[5] = fVar3;
          pfVar10[6] = fVar3;
          pfVar10[7] = fVar3;
          pfVar10 = pfVar10 + 8;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    fVar3 = FLOAT_8032f740;
    iVar8 = (count + -1) - iVar16;
    pfVar10 = w_spline.field1_0x4 + iVar16 + -1;
    if (iVar16 < count + -1) {
      do {
        *pfVar10 = fVar3;
        pfVar10 = pfVar10 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  pfVar17 = d_spline.field1_0x4;
  pfVar10 = outSecondDerivatives + 1;
  uVar18 = count - 1;
  pfVar11 = h_spline.field1_0x4;
  if (1 < count) {
    uVar19 = uVar18 >> 1;
    pfVar13 = pfVar17;
    pfVar14 = pfVar9;
    if (uVar19 != 0) {
      do {
        fVar7 = *pfVar11 / *pfVar13;
        pfVar10[1] = -(fVar7 * *pfVar10 - pfVar10[1]);
        fVar3 = *pfVar14;
        fVar4 = pfVar14[1];
        fVar5 = pfVar11[1];
        pfVar13[1] = -(fVar7 * *pfVar11 - pfVar13[1]);
        fVar6 = pfVar13[1];
        pfVar14[1] = -(fVar7 * fVar3 - fVar4);
        fVar5 = fVar5 / fVar6;
        pfVar1 = pfVar10 + 1;
        pfVar2 = pfVar10 + 2;
        pfVar10 = pfVar10 + 2;
        *pfVar10 = -(fVar5 * *pfVar1 - *pfVar2);
        pfVar1 = pfVar11 + 1;
        pfVar11 = pfVar11 + 2;
        pfVar2 = pfVar13 + 2;
        fVar3 = pfVar14[1];
        fVar4 = pfVar14[2];
        pfVar13 = pfVar13 + 2;
        *pfVar13 = -(fVar5 * *pfVar1 - *pfVar2);
        pfVar14 = pfVar14 + 2;
        *pfVar14 = -(fVar5 * fVar3 - fVar4);
        uVar19 = uVar19 - 1;
      } while (uVar19 != 0);
      uVar18 = uVar18 & 1;
      if (uVar18 == 0) goto LAB_8001ad4c;
    }
    do {
      fVar3 = *pfVar10;
      fVar6 = *pfVar11 / *pfVar13;
      pfVar1 = pfVar10 + 1;
      pfVar10 = pfVar10 + 1;
      *pfVar10 = -(fVar6 * fVar3 - *pfVar1);
      fVar3 = *pfVar11;
      pfVar11 = pfVar11 + 1;
      fVar4 = *pfVar14;
      fVar5 = pfVar14[1];
      pfVar13[1] = -(fVar6 * fVar3 - pfVar13[1]);
      pfVar14[1] = -(fVar6 * fVar4 - fVar5);
      uVar18 = uVar18 - 1;
      pfVar13 = pfVar13 + 1;
      pfVar14 = pfVar14 + 1;
    } while (uVar18 != 0);
  }
LAB_8001ad4c:
  w_spline.field0_0x0 = (int)w_spline.field1_0x4[count + -1];
  uVar18 = count - 1;
  pfVar10 = h_spline.field1_0x4 + count + 0x3e;
  pfVar13 = s_f_lvmtx.value[2] + count + 2;
  pfVar14 = outSecondDerivatives + count + -2;
  *outSecondDerivatives = outSecondDerivatives[count];
  pfVar11 = d_spline.field1_0x4 + count + 0x3e;
  if (-1 < count + -2) {
    uVar19 = uVar18 >> 2;
    if (uVar19 != 0) {
      do {
        fVar3 = *pfVar13;
        fVar4 = pfVar10[1];
        *pfVar14 = -((fVar3 / fVar4) * pfVar14[1] - *pfVar14);
        fVar5 = pfVar13[-1];
        fVar6 = *pfVar10;
        *pfVar11 = -((fVar3 / fVar4) * pfVar11[1] - *pfVar11);
        pfVar14[-1] = -((fVar5 / fVar6) * *pfVar14 - pfVar14[-1]);
        fVar3 = pfVar13[-2];
        fVar4 = pfVar10[0xffffffff];
        pfVar11[0xffffffff] = -((fVar5 / fVar6) * *pfVar11 - pfVar11[0xffffffff]);
        pfVar14[-2] = -((fVar3 / fVar4) * pfVar14[-1] - pfVar14[-2]);
        fVar5 = pfVar13[-3];
        pfVar13 = pfVar13 + -4;
        fVar6 = pfVar10[0xfffffffe];
        pfVar10 = pfVar10 + 0xfffffffc;
        pfVar11[0xfffffffe] = -((fVar3 / fVar4) * pfVar11[0xffffffff] - pfVar11[0xfffffffe]);
        pfVar14[-3] = -((fVar5 / fVar6) * pfVar14[-2] - pfVar14[-3]);
        pfVar14 = pfVar14 + -4;
        pfVar11[0xfffffffd] = -((fVar5 / fVar6) * pfVar11[0xfffffffe] - pfVar11[0xfffffffd]);
        pfVar11 = pfVar11 + 0xfffffffc;
        uVar19 = uVar19 - 1;
      } while (uVar19 != 0);
      uVar18 = uVar18 & 3;
      if (uVar18 == 0) goto LAB_8001aea4;
    }
    do {
      fVar3 = *pfVar13;
      pfVar13 = pfVar13 + -1;
      fVar4 = pfVar10[1];
      pfVar10 = pfVar10 + 0xffffffff;
      *pfVar14 = -((fVar3 / fVar4) * pfVar14[1] - *pfVar14);
      pfVar14 = pfVar14 + -1;
      *pfVar11 = -((fVar3 / fVar4) * pfVar11[1] - *pfVar11);
      pfVar11 = pfVar11 + 0xffffffff;
      uVar18 = uVar18 - 1;
    } while (uVar18 != 0);
  }
LAB_8001aea4:
  iVar16 = 1;
  fVar3 = *outSecondDerivatives / (float)w_spline.field0_0x0;
  *outSecondDerivatives = fVar3;
  outSecondDerivatives[count] = fVar3;
  if (1 < count) {
    if (8 < count + -1) {
      pfVar10 = outSecondDerivatives + 1;
      uVar18 = count - 2U >> 3;
      if (1 < count + -8) {
        do {
          iVar16 = iVar16 + 8;
          *pfVar10 = -(fVar3 * *pfVar9 - *pfVar10) / *pfVar17;
          pfVar10[1] = -(fVar3 * pfVar9[1] - pfVar10[1]) / pfVar17[1];
          pfVar10[2] = -(fVar3 * pfVar9[2] - pfVar10[2]) / pfVar17[2];
          pfVar10[3] = -(fVar3 * pfVar9[3] - pfVar10[3]) / pfVar17[3];
          pfVar10[4] = -(fVar3 * pfVar9[4] - pfVar10[4]) / pfVar17[4];
          pfVar10[5] = -(fVar3 * pfVar9[5] - pfVar10[5]) / pfVar17[5];
          pfVar10[6] = -(fVar3 * pfVar9[6] - pfVar10[6]) / pfVar17[6];
          pfVar11 = pfVar9 + 7;
          pfVar9 = pfVar9 + 8;
          pfVar13 = pfVar17 + 7;
          pfVar17 = pfVar17 + 8;
          pfVar10[7] = -(fVar3 * *pfVar11 - pfVar10[7]) / *pfVar13;
          pfVar10 = pfVar10 + 8;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    iVar8 = count - iVar16;
    pfVar9 = w_spline.field1_0x4 + iVar16 + -1;
    outSecondDerivatives = outSecondDerivatives + iVar16;
    pfVar10 = d_spline.field1_0x4 + iVar16 + -1;
    if (iVar16 < count) {
      do {
        fVar4 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        fVar5 = *pfVar10;
        pfVar10 = pfVar10 + 1;
        *outSecondDerivatives = -(fVar3 * fVar4 - *outSecondDerivatives) / fVar5;
        outSecondDerivatives = outSecondDerivatives + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  return;
}

