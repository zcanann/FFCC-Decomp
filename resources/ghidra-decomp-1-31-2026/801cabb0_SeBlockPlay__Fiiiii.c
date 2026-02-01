// Function: SeBlockPlay__Fiiiii
// Entry: 801cabb0
// Size: 264 bytes

uint SeBlockPlay__Fiiiii(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4,
                        undefined4 param_5)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  param_2 = param_2 & 3;
  param_3 = param_3 & 0x1ff;
  if ((&DAT_8032e12c)[param_2] != 0) {
    iVar2 = (&DAT_8032e12c)[param_2];
    if (((int)param_3 < (int)*(short *)(iVar2 + 10)) &&
       (iVar3 = iVar2 + 0x10, *(int *)(iVar3 + param_3 * 4) != -1)) {
      pbVar1 = (byte *)(iVar3 + *(short *)(iVar2 + 10) * 4 +
                                (*(uint *)(iVar3 + param_3 * 4) & 0x7fffffff));
      if ((*(uint *)(iVar3 + param_3 * 4) & 0x80000000) != 0) {
        *pbVar1 = *pbVar1 | 0x80;
      }
      iVar2 = _SePlayStart__FP9RedSeINFOiiii
                        (pbVar1,param_1,param_3 + param_2 * 0x200 | 0x80000000,param_4,param_5);
      if (iVar2 != 0) {
        return param_3;
      }
    }
  }
  return 0xffffffff;
}

