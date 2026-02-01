// Function: Calc__9CLine
// Entry: 800c8280
// Size: 1144 bytes

/* WARNING: Removing unreachable block (ram,0x800c86dc) */
/* WARNING: Removing unreachable block (ram,0x800c86d4) */
/* WARNING: Removing unreachable block (ram,0x800c86cc) */
/* WARNING: Removing unreachable block (ram,0x800c86c4) */
/* WARNING: Removing unreachable block (ram,0x800c86bc) */
/* WARNING: Removing unreachable block (ram,0x800c86b4) */
/* WARNING: Removing unreachable block (ram,0x800c86ac) */
/* WARNING: Removing unreachable block (ram,0x800c86a4) */
/* WARNING: Removing unreachable block (ram,0x800c82c8) */
/* WARNING: Removing unreachable block (ram,0x800c82c0) */
/* WARNING: Removing unreachable block (ram,0x800c82b8) */
/* WARNING: Removing unreachable block (ram,0x800c82b0) */
/* WARNING: Removing unreachable block (ram,0x800c82a8) */
/* WARNING: Removing unreachable block (ram,0x800c82a0) */
/* WARNING: Removing unreachable block (ram,0x800c8298) */
/* WARNING: Removing unreachable block (ram,0x800c8290) */

int Calc__9CLine(double param_1,int param_2,float *param_3,float *param_4,uint *param_5,
                float *param_6,Vec *param_7)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint unaff_r28;
  int iVar6;
  int iVar7;
  bool bVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double in_f26;
  double dVar12;
  double dVar13;
  double in_f29;
  double in_f30;
  double in_f31;
  Vec VStack_d0;
  Vec local_c4;
  
  bVar8 = (double)FLOAT_80330cec == param_1;
  dVar13 = param_1;
  if (bVar8) {
    dVar13 = (double)FLOAT_80330d10;
  }
  dVar12 = (double)(float)(param_1 * param_1);
  dVar11 = (double)FLOAT_80330cec;
  iVar5 = 0;
  iVar6 = param_2;
  iVar7 = param_2;
  for (uVar4 = 0; uVar4 < *(int *)(param_2 + 0x18) - 1U; uVar4 = uVar4 + 1) {
    dVar9 = (double)PSVECSquareDistance((Vec *)(iVar7 + 0x30),param_7);
    if ((dVar9 < dVar12) || (bVar8)) {
      local_c4.x = *(float *)(iVar7 + 0x30);
      local_c4.y = *(float *)(iVar7 + 0x34);
      local_c4.z = *(float *)(iVar7 + 0x38);
      if (dVar9 <= (double)FLOAT_80330cec) {
        if (DOUBLE_80330d28 <= dVar9) {
          fVar1 = (float)dVar9;
          uVar2 = (uint)fVar1 & 0x7f800000;
          if (uVar2 == 0x7f800000) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar3 = 2;
            }
            else {
              iVar3 = 1;
            }
          }
          else if ((uVar2 < 0x7f800000) && (uVar2 == 0)) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar3 = 3;
            }
            else {
              iVar3 = 5;
            }
          }
          else {
            iVar3 = 4;
          }
          if (iVar3 == 1) {
            dVar9 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar9 = (double)DAT_8032ec20;
        }
      }
      else {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_80330d18 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20);
        dVar10 = DOUBLE_80330d18 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20);
        dVar9 = (double)(float)(dVar9 * DOUBLE_80330d18 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20));
      }
      if (dVar9 < dVar13) {
        in_f31 = (double)local_c4.x;
        in_f30 = (double)local_c4.y;
        in_f29 = (double)local_c4.z;
        iVar5 = 1;
        in_f26 = (double)FLOAT_80330cec;
        unaff_r28 = uVar4;
        dVar13 = dVar9;
      }
    }
    if ((uVar4 == *(int *)(param_2 + 0x18) - 2U) &&
       ((dVar9 = (double)PSVECSquareDistance((Vec *)(param_2 + (uVar4 + 1) * 0xc + 0x30),param_7),
        dVar9 < dVar12 || (bVar8)))) {
      local_c4.x = *(float *)(iVar7 + 0x3c);
      local_c4.y = *(float *)(iVar7 + 0x40);
      local_c4.z = *(float *)(iVar7 + 0x44);
      if (dVar9 <= (double)FLOAT_80330cec) {
        if (DOUBLE_80330d28 <= dVar9) {
          fVar1 = (float)dVar9;
          uVar2 = (uint)fVar1 & 0x7f800000;
          if (uVar2 == 0x7f800000) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar3 = 2;
            }
            else {
              iVar3 = 1;
            }
          }
          else if ((uVar2 < 0x7f800000) && (uVar2 == 0)) {
            if (((uint)fVar1 & 0x7fffff) == 0) {
              iVar3 = 3;
            }
            else {
              iVar3 = 5;
            }
          }
          else {
            iVar3 = 4;
          }
          if (iVar3 == 1) {
            dVar9 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar9 = (double)DAT_8032ec20;
        }
      }
      else {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_80330d18 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20);
        dVar10 = DOUBLE_80330d18 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20);
        dVar9 = (double)(float)(dVar9 * DOUBLE_80330d18 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_80330d20));
      }
      if (dVar9 < dVar13) {
        in_f31 = (double)local_c4.x;
        in_f30 = (double)local_c4.y;
        in_f29 = (double)local_c4.z;
        iVar5 = 1;
        in_f26 = (double)FLOAT_80330cf0;
        unaff_r28 = uVar4;
        dVar13 = dVar9;
      }
    }
    dVar9 = (double)PSVECDotProduct(param_7,(Vec *)(iVar6 + 0xa8));
    dVar10 = (double)PSVECDotProduct((Vec *)(iVar7 + 0x30),(Vec *)(iVar6 + 0xa8));
    fVar1 = (float)(-dVar10 + dVar9) / (*(float *)(iVar6 + 0xc0) * *(float *)(iVar6 + 0xc0));
    dVar9 = (double)fVar1;
    if (((dVar11 <= dVar9) && (dVar9 <= (double)FLOAT_80330cf0)) || (bVar8)) {
      PSVECScale(fVar1,(Vec *)(iVar6 + 0xa8),&VStack_d0);
      PSVECAdd((Vec *)(iVar7 + 0x30),&VStack_d0,&local_c4);
      dVar10 = (double)PSVECDistance(param_7,&local_c4);
      if (dVar10 < dVar13) {
        in_f31 = (double)local_c4.x;
        in_f30 = (double)local_c4.y;
        in_f29 = (double)local_c4.z;
        iVar5 = 1;
        unaff_r28 = uVar4;
        in_f26 = dVar9;
        dVar13 = dVar10;
      }
    }
    iVar7 = iVar7 + 0xc;
    iVar6 = iVar6 + 0x20;
  }
  if (iVar5 != 0) {
    if (param_3 != (float *)0x0) {
      *param_3 = (float)in_f31;
      param_3[1] = (float)in_f30;
      param_3[2] = (float)in_f29;
    }
    if (param_4 != (float *)0x0) {
      *param_4 = (float)dVar13;
    }
    if (param_5 != (uint *)0x0) {
      *param_5 = unaff_r28;
    }
    if (param_6 != (float *)0x0) {
      *param_6 = (float)in_f26;
    }
  }
  return iVar5;
}

