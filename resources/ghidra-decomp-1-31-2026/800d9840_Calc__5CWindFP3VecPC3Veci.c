// Function: Calc__5CWindFP3VecPC3Veci
// Entry: 800d9840
// Size: 748 bytes

/* WARNING: Removing unreachable block (ram,0x800d9b10) */
/* WARNING: Removing unreachable block (ram,0x800d9b08) */
/* WARNING: Removing unreachable block (ram,0x800d9b00) */
/* WARNING: Removing unreachable block (ram,0x800d9860) */
/* WARNING: Removing unreachable block (ram,0x800d9858) */
/* WARNING: Removing unreachable block (ram,0x800d9850) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__5CWindFP3VecPC3Veci(byte *param_1,Vec *param_2,float *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  Vec VStack_64;
  Vec VStack_58;
  
  fVar1 = FLOAT_80330ef0;
  param_2->z = FLOAT_80330ef0;
  param_2->y = fVar1;
  param_2->x = fVar1;
  if ((MenuPcs._1856_4_ != 2) && (Game.game.m_gameWork.m_gamePaused == '\0')) {
    iVar5 = 0;
    do {
      if ((int)((uint)*param_1 << 0x18) < 0) {
        if (*(int *)(param_1 + 0x1c) == 0) {
          if (param_4 == 0) {
            PSVECAdd(param_2,(Vec *)(param_1 + 0x58),param_2);
          }
          else {
            dVar6 = (double)RandF__5CMathFv(&Math);
            PSVECScale((float)dVar6,(Vec *)(param_1 + 0x58),&VStack_58);
            PSVECAdd(param_2,&VStack_58,param_2);
          }
        }
        else {
          fVar1 = *param_3;
          if ((((*(float *)(param_1 + 0xc) < fVar1) &&
               (fVar2 = param_3[2], *(float *)(param_1 + 0x10) < fVar2)) &&
              (fVar1 < *(float *)(param_1 + 0x14))) && (fVar2 < *(float *)(param_1 + 0x18))) {
            dVar10 = (double)(fVar2 - *(float *)(param_1 + 8));
            dVar8 = (double)(fVar1 - *(float *)(param_1 + 4));
            dVar6 = (double)(float)(dVar8 * dVar8 + (double)(float)(dVar10 * dVar10));
            if (dVar6 < (double)FLOAT_80330ef4) {
              dVar6 = (double)FLOAT_80330ef4;
            }
            if (*(int *)(param_1 + 0x1c) == 2) {
              if (dVar6 < (double)*(float *)(param_1 + 0x34)) {
                dVar9 = (double)(FLOAT_80330ef8 -
                                *(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x38));
                if (dVar6 <= (double)FLOAT_80330ef0) {
                  if (DOUBLE_80330f10 <= dVar6) {
                    fVar1 = (float)dVar6;
                    uVar3 = (uint)fVar1 & 0x7f800000;
                    if (uVar3 == 0x7f800000) {
                      if (((uint)fVar1 & 0x7fffff) == 0) {
                        iVar4 = 2;
                      }
                      else {
                        iVar4 = 1;
                      }
                    }
                    else if ((uVar3 < 0x7f800000) && (uVar3 == 0)) {
                      if (((uint)fVar1 & 0x7fffff) == 0) {
                        iVar4 = 3;
                      }
                      else {
                        iVar4 = 5;
                      }
                    }
                    else {
                      iVar4 = 4;
                    }
                    if (iVar4 == 1) {
                      dVar6 = (double)DAT_8032ec20;
                    }
                  }
                  else {
                    dVar6 = (double)DAT_8032ec20;
                  }
                }
                else {
                  dVar7 = 1.0 / SQRT(dVar6);
                  dVar7 = DOUBLE_80330f00 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80330f08);
                  dVar7 = DOUBLE_80330f00 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80330f08);
                  dVar6 = (double)(float)(dVar6 * DOUBLE_80330f00 * dVar7 *
                                                  -(dVar6 * dVar7 * dVar7 - DOUBLE_80330f08));
                }
                dVar7 = (double)(float)(dVar9 / dVar6);
                param_2->x = (float)(dVar8 * dVar7 + (double)param_2->x);
                dVar6 = (double)RandF__5CMathFv(&Math);
                param_2->y = (float)(dVar9 * (double)(float)((double)FLOAT_80330f18 + dVar6) +
                                    (double)param_2->y);
                param_2->z = (float)(dVar10 * dVar7 + (double)param_2->z);
              }
            }
            else {
              PSVECScale(FLOAT_80330ef8 - (float)(dVar6 / (double)*(float *)(param_1 + 0x34)),
                         (Vec *)(param_1 + 0x58),&VStack_64);
              PSVECAdd(param_2,&VStack_64,param_2);
            }
          }
        }
      }
      iVar5 = iVar5 + 1;
      param_1 = param_1 + 100;
    } while (iVar5 < 0x20);
  }
  return;
}

