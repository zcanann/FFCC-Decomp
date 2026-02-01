// Function: ReverbHIModifyDpl2
// Entry: 80196ef4
// Size: 488 bytes

undefined4
ReverbHIModifyDpl2(double param_1,double param_2,double param_3,double param_4,double param_5,
                  int param_6)

{
  undefined4 uVar1;
  byte bVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = (double)FLOAT_803337e0;
  if ((((((param_1 < dVar5) || (dVar4 = (double)FLOAT_803337e4, dVar4 < param_1)) ||
        (param_2 < (double)FLOAT_803337e8)) ||
       (((double)FLOAT_803337ec < param_2 || (param_3 < dVar5)))) ||
      ((dVar4 < param_3 || ((param_4 < dVar5 || (dVar4 < param_4)))))) ||
     ((param_5 < dVar5 || ((double)FLOAT_80333808 < param_5)))) {
    uVar1 = 0;
  }
  else {
    *(float *)(param_6 + 0x1e0) = (float)param_1;
    *(float *)(param_6 + 0x224) = (float)param_3;
    *(float *)(param_6 + 0x228) = (float)param_4;
    if (*(float *)(param_6 + 0x228) < FLOAT_803337f8) {
      *(float *)(param_6 + 0x228) = FLOAT_803337f8;
    }
    *(float *)(param_6 + 0x228) =
         FLOAT_803337e4 - (FLOAT_803337f8 + FLOAT_803337fc * *(float *)(param_6 + 0x228));
    iVar3 = param_6;
    for (bVar2 = 0; bVar2 < 0xc; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0xc));
      iVar3 = iVar3 + 0x14;
    }
    iVar3 = param_6;
    for (bVar2 = 0; bVar2 < 0xc; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0xfc));
      iVar3 = iVar3 + 0x14;
    }
    if (*(int *)(param_6 + 0x22c) != 0) {
      iVar3 = param_6;
      for (bVar2 = 0; bVar2 < 4; bVar2 = bVar2 + 1) {
        (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0x234));
        iVar3 = iVar3 + 4;
      }
    }
    uVar1 = ReverbHICreateDpl2(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  return uVar1;
}

