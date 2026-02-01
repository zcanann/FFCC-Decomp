// Function: ReverbSTDCreate
// Entry: 80194f34
// Size: 1036 bytes

undefined4
ReverbSTDCreate(double param_1,double param_2,double param_3,double param_4,double param_5,
               int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  undefined8 local_78;
  
  dVar15 = (double)FLOAT_80333798;
  if ((((((param_1 < dVar15) || (dVar13 = (double)FLOAT_8033379c, dVar13 < param_1)) ||
        (param_2 < (double)FLOAT_803337a0)) ||
       (((double)FLOAT_803337a4 < param_2 || (param_3 < dVar15)))) ||
      ((dVar13 < param_3 || ((param_4 < dVar15 || (dVar13 < param_4)))))) ||
     ((param_5 < dVar15 || ((double)FLOAT_803337a8 < param_5)))) {
    uVar1 = 0;
  }
  else {
    memset(param_6,0,0x13c);
    dVar16 = (double)FLOAT_80333798;
    dVar13 = (double)(float)((double)FLOAT_803337ac * param_2);
    iVar11 = 0;
    iVar4 = param_6;
    dVar15 = DOUBLE_803337b8;
    for (bVar7 = 0; bVar7 < 3; bVar7 = bVar7 + 1) {
      iVar5 = iVar11 * 0x14;
      iVar6 = iVar11 << 2;
      piVar12 = &DAT_8021b780;
      for (bVar8 = 0; bVar8 < 2; bVar8 = bVar8 + 1) {
        iVar3 = *piVar12;
        iVar9 = param_6 + iVar5;
        iVar2 = (iVar3 + 2) * 4;
        *(int *)(iVar9 + 0x80) = iVar2;
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar2);
        *(undefined4 *)(iVar9 + 0x84) = uVar1;
        memset(*(undefined4 *)(iVar9 + 0x84),0,iVar2);
        *(float *)(iVar9 + 0x88) = (float)dVar16;
        *(int *)(iVar9 + 0x7c) = *(int *)(iVar9 + 0x78) + (iVar3 + 2 >> 1) * -4;
        while (*(int *)(iVar9 + 0x7c) < 0) {
          *(int *)(iVar9 + 0x7c) = *(int *)(iVar9 + 0x7c) + *(int *)(iVar9 + 0x80);
        }
        *(int *)(iVar9 + 0x78) = 0;
        *(int *)(iVar9 + 0x7c) = 0;
        *(int *)(iVar9 + 0x7c) = *(int *)(iVar9 + 0x78) + *piVar12 * -4;
        while (*(int *)(iVar9 + 0x7c) < 0) {
          *(int *)(iVar9 + 0x7c) = *(int *)(iVar9 + 0x7c) + *(int *)(iVar9 + 0x80);
        }
        local_78 = (double)CONCAT44(0x43300000,*piVar12 * -3 ^ 0x80000000);
        dVar14 = (double)powf((double)FLOAT_803337a4,
                              (double)(float)((double)(float)(local_78 - dVar15) / dVar13));
        *(float *)(param_6 + iVar6 + 0xf4) = (float)dVar14;
        piVar12 = piVar12 + 1;
        iVar6 = iVar6 + 4;
        iVar5 = iVar5 + 0x14;
      }
      iVar6 = iVar11 * 0x14;
      piVar12 = &DAT_8021b780;
      for (bVar8 = 0; bVar8 < 2; bVar8 = bVar8 + 1) {
        iVar2 = piVar12[2];
        piVar10 = (int *)(param_6 + iVar6);
        iVar5 = (iVar2 + 2) * 4;
        piVar10[2] = iVar5;
        iVar3 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(iVar5);
        piVar10[3] = iVar3;
        memset(piVar10[3],0,iVar5);
        piVar10[4] = (int)(float)dVar16;
        piVar10[1] = *piVar10 + (iVar2 + 2 >> 1) * -4;
        while (piVar10[1] < 0) {
          piVar10[1] = piVar10[1] + piVar10[2];
        }
        *piVar10 = 0;
        piVar10[1] = 0;
        piVar10[1] = *piVar10 + piVar12[2] * -4;
        while (piVar10[1] < 0) {
          piVar10[1] = piVar10[1] + piVar10[2];
        }
        piVar12 = piVar12 + 1;
        iVar6 = iVar6 + 0x14;
      }
      *(float *)(iVar4 + 0x10c) = (float)dVar16;
      iVar11 = iVar11 + 2;
      iVar4 = iVar4 + 4;
    }
    *(float *)(param_6 + 0xf0) = (float)param_1;
    *(float *)(param_6 + 0x118) = (float)param_3;
    *(float *)(param_6 + 0x11c) = (float)param_4;
    if (*(float *)(param_6 + 0x11c) < FLOAT_803337b0) {
      *(float *)(param_6 + 0x11c) = FLOAT_803337b0;
    }
    *(float *)(param_6 + 0x11c) =
         FLOAT_8033379c - (FLOAT_803337b0 + FLOAT_803337b4 * *(float *)(param_6 + 0x11c));
    if ((double)FLOAT_80333798 == param_5) {
      *(undefined4 *)(param_6 + 0x120) = 0;
      *(undefined4 *)(param_6 + 0x130) = 0;
      *(undefined4 *)(param_6 + 0x124) = 0;
      *(undefined4 *)(param_6 + 0x134) = 0;
      *(undefined4 *)(param_6 + 0x128) = 0;
      *(undefined4 *)(param_6 + 0x138) = 0;
      *(undefined4 *)(param_6 + 300) = 0;
    }
    else {
      *(int *)(param_6 + 0x120) = (int)((double)FLOAT_803337ac * param_5);
      iVar4 = param_6;
      for (bVar7 = 0; bVar7 < 3; bVar7 = bVar7 + 1) {
        uVar1 = (*(code *)PTR___AXFXAllocFunction_8032eb60)(*(int *)(param_6 + 0x120) << 2);
        *(undefined4 *)(iVar4 + 0x124) = uVar1;
        memset(*(undefined4 *)(iVar4 + 0x124),0,*(int *)(param_6 + 0x120) << 2);
        *(undefined4 *)(iVar4 + 0x130) = *(undefined4 *)(iVar4 + 0x124);
        iVar4 = iVar4 + 4;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

