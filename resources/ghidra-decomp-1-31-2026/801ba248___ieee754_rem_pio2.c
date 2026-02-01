// Function: __ieee754_rem_pio2
// Entry: 801ba248
// Size: 924 bytes

/* WARNING: Type propagation algorithm not settling */

int __ieee754_rem_pio2(double param_1,double *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  double *pdVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  uint local_58;
  double local_48;
  double local_40;
  double local_38 [3];
  longlong local_20;
  undefined4 local_18;
  uint uStack_14;
  
  dVar6 = DOUBLE_80333b58;
  dVar7 = DOUBLE_80333b48;
  local_58 = (uint)((ulonglong)param_1 >> 0x20);
  uVar1 = local_58 & 0x7fffffff;
  if (uVar1 < 0x3fe921fc) {
    *param_2 = param_1;
    iVar2 = 0;
    param_2[1] = DOUBLE_80333b38;
  }
  else if (uVar1 < 0x4002d97c) {
    if ((int)local_58 < 1) {
      param_1 = DOUBLE_80333b40 + param_1;
      if (uVar1 == 0x3ff921fb) {
        param_1 = param_1 + DOUBLE_80333b50;
        *param_2 = DOUBLE_80333b58 + param_1;
        param_2[1] = dVar6 + (param_1 - *param_2);
      }
      else {
        *param_2 = DOUBLE_80333b48 + param_1;
        param_2[1] = dVar7 + (param_1 - *param_2);
      }
      iVar2 = -1;
    }
    else {
      param_1 = param_1 - DOUBLE_80333b40;
      if (uVar1 == 0x3ff921fb) {
        param_1 = param_1 - DOUBLE_80333b50;
        *param_2 = param_1 - DOUBLE_80333b58;
        param_2[1] = (param_1 - *param_2) - dVar6;
      }
      else {
        *param_2 = param_1 - DOUBLE_80333b48;
        param_2[1] = (param_1 - *param_2) - dVar7;
      }
      iVar2 = 1;
    }
  }
  else {
    iVar3 = (int)uVar1 >> 0x14;
    if (uVar1 < 0x413921fc) {
      iVar2 = (int)(DOUBLE_80333b68 * ABS(param_1) + DOUBLE_80333b60);
      local_38[2] = (double)(CONCAT44(0x43300000,iVar2) ^ 0x80000000);
      local_38[2] = local_38[2] - DOUBLE_80333b88;
      dVar7 = -(DOUBLE_80333b40 * local_38[2] - ABS(param_1));
      dVar6 = DOUBLE_80333b48 * local_38[2];
      if ((iVar2 < 0x20) && (uVar1 != *(uint *)(&DAT_801e75b4 + iVar2 * 4))) {
        *param_2 = dVar7 - dVar6;
      }
      else {
        *param_2 = dVar7 - dVar6;
        if (0x10 < (int)(iVar3 - (*(uint *)param_2 >> 0x14 & 0x7ff))) {
          dVar8 = dVar7 - DOUBLE_80333b50 * local_38[2];
          dVar6 = DOUBLE_80333b58 * local_38[2] - ((dVar7 - dVar8) - DOUBLE_80333b50 * local_38[2]);
          *param_2 = dVar8 - dVar6;
          dVar7 = dVar8;
          if (0x31 < (int)(iVar3 - (*(uint *)param_2 >> 0x14 & 0x7ff))) {
            dVar7 = dVar8 - DOUBLE_80333b70 * local_38[2];
            dVar6 = DOUBLE_80333b78 * local_38[2] -
                    ((dVar8 - dVar7) - DOUBLE_80333b70 * local_38[2]);
            *param_2 = dVar7 - dVar6;
          }
        }
      }
      param_2[1] = (dVar7 - *param_2) - dVar6;
      if ((longlong)param_1 < 0) {
        iVar2 = -iVar2;
        *param_2 = -*param_2;
        param_2[1] = -param_2[1];
      }
    }
    else if (uVar1 < 0x7ff00000) {
      iVar5 = 3;
      dVar7 = (double)CONCAT44(uVar1 + (iVar3 + -0x416) * -0x100000,SUB84(param_1,0));
      local_18 = 0x43300000;
      iVar2 = (int)dVar7;
      local_38[2] = (double)(longlong)iVar2;
      local_38[1] = (double)(CONCAT44(0x43300000,iVar2) ^ 0x80000000);
      local_48 = local_38[1] - DOUBLE_80333b88;
      dVar7 = DOUBLE_80333b80 * (dVar7 - local_48);
      uStack_14 = (uint)dVar7;
      local_20 = (longlong)(int)uStack_14;
      uStack_14 = uStack_14 ^ 0x80000000;
      local_40 = (double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80333b88;
      local_38[0] = DOUBLE_80333b80 * (dVar7 - local_40);
      for (pdVar4 = local_38 + 1; DOUBLE_80333b38 == pdVar4[0xffffffff];
          pdVar4 = pdVar4 + 0xffffffff) {
        iVar5 = iVar5 + -1;
      }
      iVar2 = __kernel_rem_pio2(&local_48,param_2,iVar3 + -0x416,iVar5,2,&DAT_801e74b0);
      if ((longlong)param_1 < 0) {
        iVar2 = -iVar2;
        *param_2 = -*param_2;
        param_2[1] = -param_2[1];
      }
    }
    else {
      iVar2 = 0;
      param_2[1] = param_1 - param_1;
      *param_2 = param_1 - param_1;
    }
  }
  return iVar2;
}

