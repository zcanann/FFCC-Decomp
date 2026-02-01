// Function: ReverbSTDModify
// Entry: 80195340
// Size: 488 bytes

undefined4
ReverbSTDModify(double param_1,double param_2,double param_3,double param_4,double param_5,
               int param_6)

{
  undefined4 uVar1;
  byte bVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  dVar5 = (double)FLOAT_80333798;
  if ((((((param_1 < dVar5) || (dVar4 = (double)FLOAT_8033379c, dVar4 < param_1)) ||
        (param_2 < (double)FLOAT_803337a0)) ||
       (((double)FLOAT_803337a4 < param_2 || (param_3 < dVar5)))) ||
      ((dVar4 < param_3 || ((param_4 < dVar5 || (dVar4 < param_4)))))) ||
     ((param_5 < dVar5 || ((double)FLOAT_803337c0 < param_5)))) {
    uVar1 = 0;
  }
  else {
    *(float *)(param_6 + 0xf0) = (float)param_1;
    *(float *)(param_6 + 0x118) = (float)param_3;
    *(float *)(param_6 + 0x11c) = (float)param_4;
    if (*(float *)(param_6 + 0x11c) < FLOAT_803337b0) {
      *(float *)(param_6 + 0x11c) = FLOAT_803337b0;
    }
    *(float *)(param_6 + 0x11c) =
         FLOAT_8033379c - (FLOAT_803337b0 + FLOAT_803337b4 * *(float *)(param_6 + 0x11c));
    iVar3 = param_6;
    for (bVar2 = 0; bVar2 < 6; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0xc));
      iVar3 = iVar3 + 0x14;
    }
    iVar3 = param_6;
    for (bVar2 = 0; bVar2 < 6; bVar2 = bVar2 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0x84));
      iVar3 = iVar3 + 0x14;
    }
    if (*(int *)(param_6 + 0x120) != 0) {
      iVar3 = param_6;
      for (bVar2 = 0; bVar2 < 3; bVar2 = bVar2 + 1) {
        (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar3 + 0x124));
        iVar3 = iVar3 + 4;
      }
    }
    uVar1 = ReverbSTDCreate(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  return uVar1;
}

