// Function: Frame__5CWindFv
// Entry: 800d9d60
// Size: 764 bytes

void Frame__5CWindFv(byte *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  
  iVar5 = 0;
  do {
    if ((int)((uint)*param_1 << 0x18) < 0) {
      iVar4 = Rand__5CMathFUl(&Math,10);
      if (iVar4 == 0) {
        iVar4 = Rand__5CMathFUl(&Math,3);
        fVar2 = FLOAT_80330ef0;
        fVar1 = FLOAT_80330f24;
        if (iVar4 == 0) {
          fVar1 = FLOAT_80330f20;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x4c) * fVar1 + *(float *)(param_1 + 0x54)
        ;
        fVar1 = *(float *)(param_1 + 0x54);
        if ((fVar2 <= fVar1) && (fVar2 = fVar1, *(float *)(param_1 + 0x4c) < fVar1)) {
          fVar2 = *(float *)(param_1 + 0x4c);
        }
        *(float *)(param_1 + 0x54) = fVar2;
      }
      if ((((*(int *)(param_1 + 0x1c) == 0) || (*(int *)(param_1 + 0x1c) == 1)) &&
          (iVar4 = Rand__5CMathFUl(&Math,0x1e), iVar4 == 0)) &&
         (*(float *)(param_1 + 0x50) < FLOAT_80330f28 * *(float *)(param_1 + 0x4c))) {
        iVar4 = Rand__5CMathFUl(&Math,3);
        fVar1 = FLOAT_80330f30;
        if (iVar4 == 0) {
          fVar1 = FLOAT_80330f2c;
        }
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x40) * fVar1 + *(float *)(param_1 + 0x48)
        ;
        fVar1 = *(float *)(param_1 + 0x48);
        fVar2 = *(float *)(param_1 + 0x40);
        if ((fVar2 <= fVar1) && (fVar3 = FLOAT_80330f34 + fVar2, fVar2 = fVar1, fVar3 < fVar1)) {
          fVar2 = fVar3;
        }
        *(float *)(param_1 + 0x48) = fVar2;
      }
      if (*(int *)(param_1 + 0x1c) == 2) {
        *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
        if ((int)*(uint *)(param_1 + 0x24) <= (int)*(uint *)(param_1 + 0x28)) {
          *param_1 = *param_1 & 0x7f;
          goto LAB_800da034;
        }
        *(float *)(param_1 + 0x38) =
             (float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x28) ^ 0x80000000) -
                    DOUBLE_80330f40) /
             (float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x24) ^ 0x80000000) -
                    DOUBLE_80330f40);
        *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x2c) * *(float *)(param_1 + 0x38);
        *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x30) * *(float *)(param_1 + 0x30);
        *(float *)(param_1 + 0xc) = *(float *)(param_1 + 4) - *(float *)(param_1 + 0x30);
        *(float *)(param_1 + 0x10) = *(float *)(param_1 + 8) - *(float *)(param_1 + 0x30);
        *(float *)(param_1 + 0x14) = *(float *)(param_1 + 4) + *(float *)(param_1 + 0x30);
        *(float *)(param_1 + 0x18) = *(float *)(param_1 + 8) + *(float *)(param_1 + 0x30);
      }
      *(float *)(param_1 + 0x50) =
           FLOAT_80330f38 * (*(float *)(param_1 + 0x54) - *(float *)(param_1 + 0x50)) +
           *(float *)(param_1 + 0x50);
      dVar6 = (double)RandF__5CMathFv(&Math);
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x44) +
           (float)((double)FLOAT_80330f2c * dVar6 +
                  (double)(FLOAT_80330f38 *
                           (*(float *)(param_1 + 0x48) - *(float *)(param_1 + 0x44)) -
                          FLOAT_80330f28));
      if ((*(int *)(param_1 + 0x1c) == 0) || (*(int *)(param_1 + 0x1c) == 1)) {
        dVar6 = (double)sin((double)*(float *)(param_1 + 0x44));
        *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x50) * (float)dVar6;
        dVar6 = (double)RandF__5CMathFv(&Math);
        *(float *)(param_1 + 0x5c) =
             *(float *)(param_1 + 0x50) *
             (float)((double)FLOAT_80330f20 * dVar6 + (double)FLOAT_80330f24);
        dVar6 = (double)cos((double)*(float *)(param_1 + 0x44));
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x50) * (float)dVar6;
      }
    }
LAB_800da034:
    iVar5 = iVar5 + 1;
    param_1 = param_1 + 100;
    if (0x1f < iVar5) {
      return;
    }
  } while( true );
}

