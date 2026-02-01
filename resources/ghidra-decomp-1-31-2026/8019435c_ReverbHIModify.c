// Function: ReverbHIModify
// Entry: 8019435c
// Size: 524 bytes

undefined4
ReverbHIModify(double param_1,double param_2,double param_3,double param_4,double param_5,
              double param_6,int param_7)

{
  undefined4 uVar1;
  byte bVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = (double)FLOAT_80333750;
  if (((((param_1 < dVar5) || (dVar4 = (double)FLOAT_80333754, dVar4 < param_1)) ||
       (param_2 < (double)FLOAT_80333758)) ||
      (((((double)FLOAT_8033375c < param_2 || (param_3 < dVar5)) ||
        ((dVar4 < param_3 || ((param_6 < dVar5 || (dVar4 < param_6)))))) || (param_4 < dVar5)))) ||
     (((dVar4 < param_4 || (param_5 < dVar5)) || ((double)FLOAT_80333778 < param_5)))) {
    uVar1 = 0;
  }
  else {
    *(float *)(param_7 + 0x168) = (float)param_1;
    *(float *)(param_7 + 0x19c) = (float)param_3;
    *(float *)(param_7 + 0x1a8) = (float)param_6;
    *(float *)(param_7 + 0x1a0) = (float)param_4;
    if (*(float *)(param_7 + 0x1a0) < FLOAT_80333768) {
      *(float *)(param_7 + 0x1a0) = FLOAT_80333768;
    }
    *(float *)(param_7 + 0x1a0) =
         FLOAT_80333754 - (FLOAT_80333768 + FLOAT_8033376c * *(float *)(param_7 + 0x1a0));
    iVar3 = param_7;
    for (bVar2 = 0; bVar2 < 9; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0xc));
      iVar3 = iVar3 + 0x14;
    }
    iVar3 = param_7;
    for (bVar2 = 0; bVar2 < 9; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0xc0));
      iVar3 = iVar3 + 0x14;
    }
    if (*(int *)(param_7 + 0x1a4) != 0) {
      iVar3 = param_7;
      for (bVar2 = 0; bVar2 < 3; bVar2 = bVar2 + 1) {
        (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0x1ac));
        iVar3 = iVar3 + 4;
      }
    }
    uVar1 = ReverbHICreate(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  return uVar1;
}

