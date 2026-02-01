// Function: GetFcvValue__8CMenuPcsFQ28CMenuPcs3FCVf
// Entry: 800f69a8
// Size: 264 bytes

double GetFcvValue__8CMenuPcsFQ28CMenuPcs3FCVf(double param_1,CMenuPcs *menuPcs,int *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  
  iVar8 = *param_3;
  fVar1 = (float)(param_1 / (double)FLOAT_803314c0);
  pfVar7 = (float *)param_3[1];
  if (pfVar7[iVar8 * 4 + -4] <= fVar1) {
    return (double)pfVar7[iVar8 * 4 + -3];
  }
  iVar6 = 0;
  pfVar5 = pfVar7;
  if (iVar8 < 1) {
    return (double)FLOAT_803313dc;
  }
  while (*pfVar5 < fVar1) {
    pfVar5 = pfVar5 + 4;
    iVar6 = iVar6 + 1;
    iVar8 = iVar8 + -1;
    if (iVar8 == 0) {
      return (double)FLOAT_803313dc;
    }
  }
  if (iVar6 == 0) {
    return (double)pfVar7[1];
  }
  pfVar5 = pfVar7 + iVar6 * 4;
  pfVar7 = pfVar7 + (iVar6 + -1) * 4;
  fVar2 = *pfVar5 - *pfVar7;
  fVar4 = (fVar1 - *pfVar7) / fVar2;
  fVar3 = fVar4 * fVar4;
  fVar1 = fVar3 * fVar4;
  return (double)(fVar2 * (pfVar7[3] * (fVar4 + -(FLOAT_803314c8 * fVar3 - fVar1)) +
                          pfVar5[2] * (fVar1 - fVar3)) +
                 pfVar7[1] * (FLOAT_803313e8 + (FLOAT_803314c8 * fVar1 - FLOAT_803314c4 * fVar3)) +
                 pfVar5[1] * (FLOAT_803314cc * fVar1 + FLOAT_803314c4 * fVar3));
}

