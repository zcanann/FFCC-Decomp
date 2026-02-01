// Function: ReverbHICreate
// Entry: 80193e70
// Size: 1260 bytes

undefined4
ReverbHICreate(double param_1,double param_2,double param_3,double param_4,double param_5,
              double param_6,int param_7)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  byte bVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  undefined8 local_88;
  
  dVar17 = (double)FLOAT_80333750;
  if (((((param_1 < dVar17) || (dVar15 = (double)FLOAT_80333754, dVar15 < param_1)) ||
       (param_2 < (double)FLOAT_80333758)) ||
      (((((double)FLOAT_8033375c < param_2 || (param_3 < dVar17)) ||
        ((dVar15 < param_3 || ((param_6 < dVar17 || (dVar15 < param_6)))))) || (param_4 < dVar17))))
     || (((dVar15 < param_4 || (param_5 < dVar17)) || ((double)FLOAT_80333760 < param_5)))) {
    uVar1 = 0;
  }
  else {
    memset(param_7,0,0x1c4);
    dVar18 = (double)FLOAT_80333750;
    dVar15 = (double)(float)((double)FLOAT_80333764 * param_2);
    iVar12 = 0;
    iVar4 = param_7;
    iVar10 = param_7;
    piVar11 = &DAT_8021b760;
    dVar17 = DOUBLE_80333770;
    for (bVar14 = 0; bVar14 < 3; bVar14 = bVar14 + 1) {
      iVar5 = iVar12 * 0x14;
      iVar6 = iVar12 << 2;
      piVar13 = &DAT_8021b760;
      for (bVar7 = 0; bVar7 < 3; bVar7 = bVar7 + 1) {
        iVar3 = *piVar13;
        iVar8 = param_7 + iVar5;
        iVar2 = (iVar3 + 2) * 4;
        *(int *)(iVar8 + 0xbc) = iVar2;
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar2);
        *(undefined4 *)(iVar8 + 0xc0) = uVar1;
        memset(*(undefined4 *)(iVar8 + 0xc0),0,iVar2);
        *(float *)(iVar8 + 0xc4) = (float)dVar18;
        *(int *)(iVar8 + 0xb8) = *(int *)(iVar8 + 0xb4) + (iVar3 + 2 >> 1) * -4;
        while (*(int *)(iVar8 + 0xb8) < 0) {
          *(int *)(iVar8 + 0xb8) = *(int *)(iVar8 + 0xb8) + *(int *)(iVar8 + 0xbc);
        }
        *(int *)(iVar8 + 0xb4) = 0;
        *(int *)(iVar8 + 0xb8) = 0;
        *(int *)(iVar8 + 0xb8) = *(int *)(iVar8 + 0xb4) + *piVar13 * -4;
        while (*(int *)(iVar8 + 0xb8) < 0) {
          *(int *)(iVar8 + 0xb8) = *(int *)(iVar8 + 0xb8) + *(int *)(iVar8 + 0xbc);
        }
        local_88 = (double)CONCAT44(0x43300000,*piVar13 * -3 ^ 0x80000000);
        dVar16 = (double)powf((double)FLOAT_8033375c,
                              (double)(float)((double)(float)(local_88 - dVar17) / dVar15));
        *(float *)(param_7 + iVar6 + 0x16c) = (float)dVar16;
        piVar13 = piVar13 + 1;
        iVar6 = iVar6 + 4;
        iVar5 = iVar5 + 0x14;
      }
      iVar6 = iVar12 * 0x14;
      piVar13 = &DAT_8021b760;
      for (bVar7 = 0; bVar7 < 2; bVar7 = bVar7 + 1) {
        iVar2 = piVar13[3];
        piVar9 = (int *)(param_7 + iVar6);
        iVar5 = (iVar2 + 2) * 4;
        piVar9[2] = iVar5;
        iVar3 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar5);
        piVar9[3] = iVar3;
        memset(piVar9[3],0,iVar5);
        piVar9[4] = (int)(float)dVar18;
        piVar9[1] = *piVar9 + (iVar2 + 2 >> 1) * -4;
        while (piVar9[1] < 0) {
          piVar9[1] = piVar9[1] + piVar9[2];
        }
        *piVar9 = 0;
        piVar9[1] = 0;
        piVar9[1] = *piVar9 + piVar13[3] * -4;
        while (piVar9[1] < 0) {
          piVar9[1] = piVar9[1] + piVar9[2];
        }
        piVar13 = piVar13 + 1;
        iVar6 = iVar6 + 0x14;
      }
      iVar5 = piVar11[5];
      iVar6 = (iVar5 + 2) * 4;
      *(int *)(iVar10 + 0x30) = iVar6;
      uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar6);
      *(undefined4 *)(iVar10 + 0x34) = uVar1;
      memset(*(undefined4 *)(iVar10 + 0x34),0,iVar6);
      *(float *)(iVar10 + 0x38) = (float)dVar18;
      *(int *)(iVar10 + 0x2c) = *(int *)(iVar10 + 0x28) + (iVar5 + 2 >> 1) * -4;
      while (*(int *)(iVar10 + 0x2c) < 0) {
        *(int *)(iVar10 + 0x2c) = *(int *)(iVar10 + 0x2c) + *(int *)(iVar10 + 0x30);
      }
      *(undefined4 *)(iVar10 + 0x28) = 0;
      *(undefined4 *)(iVar10 + 0x2c) = 0;
      *(int *)(iVar10 + 0x2c) = *(int *)(iVar10 + 0x28) + piVar11[5] * -4;
      while (*(int *)(iVar10 + 0x2c) < 0) {
        *(int *)(iVar10 + 0x2c) = *(int *)(iVar10 + 0x2c) + *(int *)(iVar10 + 0x30);
      }
      *(float *)(iVar4 + 400) = (float)dVar18;
      iVar12 = iVar12 + 3;
      piVar11 = piVar11 + 1;
      iVar10 = iVar10 + 0x3c;
      iVar4 = iVar4 + 4;
    }
    *(float *)(param_7 + 0x168) = (float)param_1;
    *(float *)(param_7 + 0x19c) = (float)param_3;
    *(float *)(param_7 + 0x1a8) = (float)param_6;
    *(float *)(param_7 + 0x1a0) = (float)param_4;
    if (*(float *)(param_7 + 0x1a0) < FLOAT_80333768) {
      *(float *)(param_7 + 0x1a0) = FLOAT_80333768;
    }
    *(float *)(param_7 + 0x1a0) =
         FLOAT_80333754 - (FLOAT_80333768 + FLOAT_8033376c * *(float *)(param_7 + 0x1a0));
    if ((double)FLOAT_80333750 == param_5) {
      *(undefined4 *)(param_7 + 0x1a4) = 0;
      *(undefined4 *)(param_7 + 0x1b8) = 0;
      *(undefined4 *)(param_7 + 0x1ac) = 0;
      *(undefined4 *)(param_7 + 0x1bc) = 0;
      *(undefined4 *)(param_7 + 0x1b0) = 0;
      *(undefined4 *)(param_7 + 0x1c0) = 0;
      *(undefined4 *)(param_7 + 0x1b4) = 0;
    }
    else {
      *(int *)(param_7 + 0x1a4) = (int)((double)FLOAT_80333764 * param_5);
      iVar4 = param_7;
      for (bVar14 = 0; bVar14 < 3; bVar14 = bVar14 + 1) {
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(*(int *)(param_7 + 0x1a4) << 2);
        *(undefined4 *)(iVar4 + 0x1ac) = uVar1;
        memset(*(undefined4 *)(iVar4 + 0x1ac),0,*(int *)(param_7 + 0x1a4) << 2);
        *(undefined4 *)(iVar4 + 0x1b8) = *(undefined4 *)(iVar4 + 0x1ac);
        iVar4 = iVar4 + 4;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

