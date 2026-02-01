// Function: DrawRect__8CMenuPcsFUlfffffffff
// Entry: 800958fc
// Size: 724 bytes

/* WARNING: Removing unreachable block (ram,0x80095bb8) */
/* WARNING: Removing unreachable block (ram,0x80095bb0) */
/* WARNING: Removing unreachable block (ram,0x80095ba8) */
/* WARNING: Removing unreachable block (ram,0x80095ba0) */
/* WARNING: Removing unreachable block (ram,0x80095b98) */
/* WARNING: Removing unreachable block (ram,0x80095b90) */
/* WARNING: Removing unreachable block (ram,0x80095b88) */
/* WARNING: Removing unreachable block (ram,0x80095b80) */
/* WARNING: Removing unreachable block (ram,0x80095b78) */
/* WARNING: Removing unreachable block (ram,0x80095b70) */
/* WARNING: Removing unreachable block (ram,0x80095b68) */
/* WARNING: Removing unreachable block (ram,0x80095b60) */
/* WARNING: Removing unreachable block (ram,0x80095964) */
/* WARNING: Removing unreachable block (ram,0x8009595c) */
/* WARNING: Removing unreachable block (ram,0x80095954) */
/* WARNING: Removing unreachable block (ram,0x8009594c) */
/* WARNING: Removing unreachable block (ram,0x80095944) */
/* WARNING: Removing unreachable block (ram,0x8009593c) */
/* WARNING: Removing unreachable block (ram,0x80095934) */
/* WARNING: Removing unreachable block (ram,0x8009592c) */
/* WARNING: Removing unreachable block (ram,0x80095924) */
/* WARNING: Removing unreachable block (ram,0x8009591c) */
/* WARNING: Removing unreachable block (ram,0x80095914) */
/* WARNING: Removing unreachable block (ram,0x8009590c) */

void DrawRect__8CMenuPcsFUlfffffffff
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9_00,uint param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  float param_9;
  
  dVar12 = (double)param_9;
  if (((double)FLOAT_8033080c < param_3) && ((double)FLOAT_8033080c < param_4)) {
    if ((param_10 & 8) == 0) {
      dVar16 = param_5 + (double)FLOAT_8033084c;
      dVar10 = (double)(float)(param_5 + param_3) - (double)FLOAT_8033084c;
    }
    else {
      dVar10 = (double)FLOAT_8033084c + param_5;
      dVar16 = (double)(float)(param_5 + param_3) - (double)FLOAT_8033084c;
    }
    dVar18 = (double)(float)dVar10;
    dVar10 = (double)(float)dVar16;
    if ((param_10 & 4) == 0) {
      dVar16 = param_6 + (double)FLOAT_8033084c;
      dVar17 = (double)(float)((double)(float)(param_6 + param_4) - (double)FLOAT_8033084c);
    }
    else {
      dVar17 = (double)(float)((double)FLOAT_8033084c + param_6);
      dVar16 = (double)(float)(dVar17 + param_4) - (double)FLOAT_8033084c;
    }
    dVar11 = (double)(float)dVar16;
    dVar16 = param_1;
    if ((param_10 & 1) != 0) {
      dVar16 = -(double)(float)((double)FLOAT_8033084c * (double)(float)(param_3 * param_7) -
                               param_1);
    }
    dVar15 = param_2;
    if ((param_10 & 2) != 0) {
      dVar15 = -(double)(float)((double)FLOAT_8033084c * (double)(float)(param_4 * param_8) -
                               param_2);
    }
    dVar14 = (double)(float)(dVar16 + (double)(float)(param_3 * param_7));
    dVar13 = (double)(float)(dVar15 + (double)(float)(param_4 * param_8));
    GXBegin(0x98,0,4);
    if ((double)FLOAT_8033080c == dVar12) {
      DAT_cc008000 = (float)dVar16;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar10;
      DAT_cc008000 = (float)dVar11;
      DAT_cc008000 = (float)dVar14;
      DAT_cc008000 = (float)dVar15;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = (float)dVar11;
      DAT_cc008000 = (float)dVar16;
      DAT_cc008000 = (float)dVar13;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar10;
      DAT_cc008000 = (float)dVar17;
      DAT_cc008000 = (float)dVar14;
      DAT_cc008000 = (float)dVar13;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = (float)dVar17;
    }
    else {
      dVar9 = (double)sin(dVar12);
      dVar9 = (double)(float)dVar9;
      dVar12 = (double)cos(dVar12);
      dVar12 = (double)(float)dVar12;
      fVar1 = (float)((double)(float)(dVar16 - param_1) * dVar12 + param_1);
      fVar5 = (float)((double)(float)(dVar15 - param_2) * dVar9);
      fVar2 = (float)((double)(float)(dVar16 - param_1) * dVar9 + param_2);
      fVar6 = (float)((double)(float)(dVar15 - param_2) * dVar12);
      DAT_cc008000 = fVar1 - fVar5;
      fVar3 = (float)((double)(float)(dVar14 - param_1) * dVar12 + param_1);
      fVar7 = (float)((double)(float)(dVar13 - param_2) * dVar9);
      DAT_cc008000 = fVar2 + fVar6;
      fVar4 = (float)((double)(float)(dVar14 - param_1) * dVar9 + param_2);
      fVar8 = (float)((double)(float)(dVar13 - param_2) * dVar12);
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar10;
      DAT_cc008000 = (float)dVar11;
      DAT_cc008000 = fVar3 - fVar5;
      DAT_cc008000 = fVar4 + fVar6;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = (float)dVar11;
      DAT_cc008000 = fVar1 - fVar7;
      DAT_cc008000 = fVar2 + fVar8;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar10;
      DAT_cc008000 = (float)dVar17;
      DAT_cc008000 = fVar3 - fVar7;
      DAT_cc008000 = fVar4 + fVar8;
      DAT_cc008000 = FLOAT_8033080c;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = (float)dVar17;
    }
  }
  return;
}

