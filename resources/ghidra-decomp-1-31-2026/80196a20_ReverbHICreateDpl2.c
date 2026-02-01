// Function: ReverbHICreateDpl2
// Entry: 80196a20
// Size: 1236 bytes

undefined4
ReverbHICreateDpl2(double param_1,double param_2,double param_3,double param_4,double param_5,
                  int param_6)

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
  undefined8 local_80;
  
  dVar17 = (double)FLOAT_803337e0;
  if ((((((param_1 < dVar17) || (dVar15 = (double)FLOAT_803337e4, dVar15 < param_1)) ||
        (param_2 < (double)FLOAT_803337e8)) ||
       (((double)FLOAT_803337ec < param_2 || (param_3 < dVar17)))) ||
      ((dVar15 < param_3 || ((param_4 < dVar17 || (dVar15 < param_4)))))) ||
     ((param_5 < dVar17 || ((double)FLOAT_803337f0 < param_5)))) {
    uVar1 = 0;
  }
  else {
    memset(param_6,0,0x254);
    dVar18 = (double)FLOAT_803337e0;
    dVar15 = (double)(float)((double)FLOAT_803337f4 * param_2);
    iVar12 = 0;
    iVar4 = param_6;
    iVar10 = param_6;
    piVar11 = &DAT_8021bf90;
    dVar17 = DOUBLE_80333800;
    for (bVar14 = 0; bVar14 < 4; bVar14 = bVar14 + 1) {
      iVar5 = iVar12 * 0x14;
      iVar6 = iVar12 << 2;
      piVar13 = &DAT_8021bf90;
      for (bVar7 = 0; bVar7 < 3; bVar7 = bVar7 + 1) {
        iVar3 = *piVar13;
        iVar8 = param_6 + iVar5;
        iVar2 = (iVar3 + 2) * 4;
        *(int *)(iVar8 + 0xf8) = iVar2;
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar2);
        *(undefined4 *)(iVar8 + 0xfc) = uVar1;
        memset(*(undefined4 *)(iVar8 + 0xfc),0,iVar2);
        *(float *)(iVar8 + 0x100) = (float)dVar18;
        *(int *)(iVar8 + 0xf4) = *(int *)(iVar8 + 0xf0) + (iVar3 + 2 >> 1) * -4;
        while (*(int *)(iVar8 + 0xf4) < 0) {
          *(int *)(iVar8 + 0xf4) = *(int *)(iVar8 + 0xf4) + *(int *)(iVar8 + 0xf8);
        }
        *(int *)(iVar8 + 0xf0) = 0;
        *(int *)(iVar8 + 0xf4) = 0;
        *(int *)(iVar8 + 0xf4) = *(int *)(iVar8 + 0xf0) + *piVar13 * -4;
        while (*(int *)(iVar8 + 0xf4) < 0) {
          *(int *)(iVar8 + 0xf4) = *(int *)(iVar8 + 0xf4) + *(int *)(iVar8 + 0xf8);
        }
        local_80 = (double)CONCAT44(0x43300000,*piVar13 * -3 ^ 0x80000000);
        dVar16 = (double)powf((double)FLOAT_803337ec,
                              (double)(float)((double)(float)(local_80 - dVar17) / dVar15));
        *(float *)(param_6 + iVar6 + 0x1e4) = (float)dVar16;
        piVar13 = piVar13 + 1;
        iVar6 = iVar6 + 4;
        iVar5 = iVar5 + 0x14;
      }
      iVar6 = iVar12 * 0x14;
      piVar13 = &DAT_8021bf90;
      for (bVar7 = 0; bVar7 < 2; bVar7 = bVar7 + 1) {
        iVar2 = piVar13[3];
        piVar9 = (int *)(param_6 + iVar6);
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
      *(float *)(iVar4 + 0x214) = (float)dVar18;
      iVar12 = iVar12 + 3;
      piVar11 = piVar11 + 1;
      iVar10 = iVar10 + 0x3c;
      iVar4 = iVar4 + 4;
    }
    *(float *)(param_6 + 0x1e0) = (float)param_1;
    *(float *)(param_6 + 0x224) = (float)param_3;
    *(float *)(param_6 + 0x228) = (float)param_4;
    if (*(float *)(param_6 + 0x228) < FLOAT_803337f8) {
      *(float *)(param_6 + 0x228) = FLOAT_803337f8;
    }
    *(float *)(param_6 + 0x228) =
         FLOAT_803337e4 - (FLOAT_803337f8 + FLOAT_803337fc * *(float *)(param_6 + 0x228));
    if ((double)FLOAT_803337e0 == param_5) {
      *(undefined4 *)(param_6 + 0x22c) = 0;
      *(undefined4 *)(param_6 + 0x244) = 0;
      *(undefined4 *)(param_6 + 0x234) = 0;
      *(undefined4 *)(param_6 + 0x248) = 0;
      *(undefined4 *)(param_6 + 0x238) = 0;
      *(undefined4 *)(param_6 + 0x24c) = 0;
      *(undefined4 *)(param_6 + 0x23c) = 0;
      *(undefined4 *)(param_6 + 0x250) = 0;
      *(undefined4 *)(param_6 + 0x240) = 0;
    }
    else {
      *(int *)(param_6 + 0x22c) = (int)((double)FLOAT_803337f4 * param_5);
      iVar4 = param_6;
      for (bVar14 = 0; bVar14 < 4; bVar14 = bVar14 + 1) {
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(*(int *)(param_6 + 0x22c) << 2);
        *(undefined4 *)(iVar4 + 0x234) = uVar1;
        memset(*(undefined4 *)(iVar4 + 0x234),0,*(int *)(param_6 + 0x22c) << 2);
        *(undefined4 *)(iVar4 + 0x244) = *(undefined4 *)(iVar4 + 0x234);
        iVar4 = iVar4 + 4;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

