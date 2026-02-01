// Function: FindIntersection__FRC3VecRC3VecRC12CMapCylinderRf
// Entry: 80026e24
// Size: 2308 bytes

/* WARNING: Removing unreachable block (ram,0x80027700) */
/* WARNING: Removing unreachable block (ram,0x800276f8) */
/* WARNING: Removing unreachable block (ram,0x800276f0) */
/* WARNING: Removing unreachable block (ram,0x800276e8) */
/* WARNING: Removing unreachable block (ram,0x80026e4c) */
/* WARNING: Removing unreachable block (ram,0x80026e44) */
/* WARNING: Removing unreachable block (ram,0x80026e3c) */
/* WARNING: Removing unreachable block (ram,0x80026e34) */

undefined4
FindIntersection__FRC3VecRC3VecRC12CMapCylinderRf
          (Vec *param_1,Vec *param_2,Vec *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  Vec VStack_98;
  Vec local_8c;
  Vec local_80;
  Vec VStack_74;
  Vec local_68 [2];
  
  local_80.x = param_3[2].x;
  local_80.y = param_3[2].y;
  local_80.z = param_3[2].z;
  dVar6 = (double)PSVECMag(&local_80);
  PSVECScale((float)((double)FLOAT_8032f8cc / dVar6),&local_80,&local_80);
  if ((ABS(local_80.x) < ABS(local_80.y)) || (ABS(local_80.x) < ABS(local_80.z))) {
    local_68[0].z = -local_80.y;
    local_68[0].x = FLOAT_8032f8d0;
    local_68[0].y = local_80.z;
  }
  else {
    local_68[0].x = -local_80.y;
    local_68[0].y = local_80.x;
    local_68[0].z = FLOAT_8032f8d0;
  }
  PSVECNormalize(local_68,local_68);
  PSVECCrossProduct(&local_80,local_68,&VStack_74);
  dVar7 = (double)PSVECDotProduct(local_68,param_2);
  local_8c.x = (float)dVar7;
  dVar7 = (double)PSVECDotProduct(&VStack_74,param_2);
  local_8c.y = (float)dVar7;
  dVar7 = (double)PSVECDotProduct(&local_80,param_2);
  local_8c.z = (float)dVar7;
  dVar7 = (double)PSVECMag(&local_8c);
  dVar13 = (double)(float)((double)FLOAT_8032f8cc / dVar7);
  PSVECScale((float)((double)FLOAT_8032f8cc / dVar7),&local_8c,&local_8c);
  PSVECSubtract(param_1,param_3,&VStack_98);
  dVar7 = (double)PSVECDotProduct(local_68,&VStack_98);
  dVar8 = (double)PSVECDotProduct(&VStack_74,&VStack_98);
  dVar9 = (double)PSVECDotProduct(&local_80,&VStack_98);
  fVar2 = FLOAT_8032f8d0;
  dVar12 = (double)(param_3[3].x * param_3[3].x);
  if (ABS((double)local_8c.z) < DOUBLE_8032f908) {
    dVar10 = (double)local_8c.y;
    dVar11 = (double)local_8c.x;
    dVar12 = (double)(float)((double)(float)(dVar7 * dVar7 + (double)(float)(dVar8 * dVar8)) -
                            dVar12);
    dVar7 = (double)(float)(dVar7 * dVar11 + (double)(float)(dVar8 * dVar10));
    dVar10 = (double)((float)(dVar11 * dVar11) + (float)(dVar10 * dVar10));
    fVar1 = (float)(dVar7 * dVar7 - (double)(float)(dVar10 * dVar12));
    dVar8 = (double)fVar1;
    if (dVar8 < DOUBLE_8032f910) {
      uVar5 = 0;
    }
    else {
      if (dVar8 <= DOUBLE_8032f910) {
        dVar8 = (double)(float)((double)(float)(-dVar7 / dVar10) * (double)local_8c.z + dVar9);
        if ((DOUBLE_8032f910 <= dVar8) && (dVar8 <= dVar6)) {
          *param_4 = (float)((double)(float)(-dVar7 / dVar10) * dVar13);
          if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
            return 1;
          }
          return 0;
        }
      }
      else {
        if (dVar8 <= (double)FLOAT_8032f8d0) {
          if (DOUBLE_8032f910 <= dVar8) {
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
              dVar8 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar8 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar11 = 1.0 / SQRT(dVar8);
          dVar11 = DOUBLE_8032f918 * dVar11 * -(dVar8 * dVar11 * dVar11 - DOUBLE_8032f920);
          dVar11 = DOUBLE_8032f918 * dVar11 * -(dVar8 * dVar11 * dVar11 - DOUBLE_8032f920);
          dVar8 = (double)(float)(dVar8 * DOUBLE_8032f918 * dVar11 *
                                          -(dVar8 * dVar11 * dVar11 - DOUBLE_8032f920));
        }
        dVar10 = (double)((float)(DOUBLE_8032f8e0 / dVar10) * (float)(-dVar7 - dVar8));
        dVar8 = (double)(float)(dVar10 * (double)local_8c.z + dVar9);
        if ((DOUBLE_8032f910 <= dVar8) && (dVar8 <= dVar6)) {
          *param_4 = (float)(dVar10 * dVar13);
          if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
            return 1;
          }
          return 0;
        }
      }
      if (*(char *)(DAT_8032ec8c + 0x45) == '\x01') {
        dVar8 = (double)(float)(dVar9 * dVar9 + dVar12);
        dVar7 = (double)(float)(dVar9 * (double)local_8c.z + dVar7);
        fVar1 = (float)(dVar7 * dVar7 - dVar8);
        dVar12 = (double)fVar1;
        if (dVar12 <= DOUBLE_8032f910) {
          if ((DOUBLE_8032f910 == dVar12) &&
             ((double)(float)(-dVar7 * (double)local_8c.z + dVar9) <= DOUBLE_8032f910)) {
            *param_4 = (float)(-dVar7 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
        }
        else {
          if (dVar12 <= (double)FLOAT_8032f8d0) {
            if (DOUBLE_8032f910 <= dVar12) {
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
                dVar12 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar12 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar10 = 1.0 / SQRT(dVar12);
            dVar10 = DOUBLE_8032f918 * dVar10 * -(dVar12 * dVar10 * dVar10 - DOUBLE_8032f920);
            dVar10 = DOUBLE_8032f918 * dVar10 * -(dVar12 * dVar10 * dVar10 - DOUBLE_8032f920);
            dVar12 = (double)(float)(dVar12 * DOUBLE_8032f918 * dVar10 *
                                              -(dVar12 * dVar10 * dVar10 - DOUBLE_8032f920));
          }
          dVar10 = (double)(float)(-dVar7 - dVar12);
          if ((double)(float)(dVar10 * (double)local_8c.z + dVar9) <= DOUBLE_8032f910) {
            *param_4 = (float)(dVar10 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
          dVar12 = (double)(float)(-dVar7 + dVar12);
          if ((double)(float)(dVar12 * (double)local_8c.z + dVar9) <= DOUBLE_8032f910) {
            *param_4 = (float)(dVar12 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
        }
        dVar7 = -(double)(float)((double)local_8c.z * dVar6 - dVar7);
        fVar1 = (float)(dVar7 * dVar7 -
                       (double)(float)(dVar6 * -(DOUBLE_8032f928 * dVar9 - dVar6) + dVar8));
        dVar8 = (double)fVar1;
        if (dVar8 <= DOUBLE_8032f910) {
          if ((DOUBLE_8032f910 == dVar8) &&
             (dVar6 <= (double)(float)(-dVar7 * (double)local_8c.z + dVar9))) {
            *param_4 = (float)(-dVar7 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
        }
        else {
          if (dVar8 <= (double)FLOAT_8032f8d0) {
            if (DOUBLE_8032f910 <= dVar8) {
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
                dVar8 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar8 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar12 = 1.0 / SQRT(dVar8);
            dVar12 = DOUBLE_8032f918 * dVar12 * -(dVar8 * dVar12 * dVar12 - DOUBLE_8032f920);
            dVar12 = DOUBLE_8032f918 * dVar12 * -(dVar8 * dVar12 * dVar12 - DOUBLE_8032f920);
            dVar8 = (double)(float)(dVar8 * DOUBLE_8032f918 * dVar12 *
                                            -(dVar8 * dVar12 * dVar12 - DOUBLE_8032f920));
          }
          dVar12 = (double)(float)(-dVar7 - dVar8);
          if (dVar6 <= (double)(float)(dVar12 * (double)local_8c.z + dVar9)) {
            *param_4 = (float)(dVar12 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
          dVar7 = (double)(float)(-dVar7 + dVar8);
          if (dVar6 <= (double)(float)(dVar7 * (double)local_8c.z + dVar9)) {
            *param_4 = (float)(dVar7 * dVar13);
            if ((fVar2 <= *param_4) && (*param_4 <= FLOAT_8032f8cc)) {
              return 1;
            }
            return 0;
          }
        }
        uVar5 = 0;
      }
      else {
        uVar5 = 0;
      }
    }
  }
  else {
    dVar6 = -(double)(float)(dVar8 * dVar8 - -(double)(float)(dVar7 * dVar7 - dVar12));
    if (dVar6 < DOUBLE_8032f910) {
      uVar5 = 0;
    }
    else {
      if (dVar6 <= (double)FLOAT_8032f8d0) {
        if (DOUBLE_8032f910 <= dVar6) {
          fVar2 = (float)dVar6;
          uVar3 = (uint)fVar2 & 0x7f800000;
          if (uVar3 == 0x7f800000) {
            if (((uint)fVar2 & 0x7fffff) == 0) {
              iVar4 = 2;
            }
            else {
              iVar4 = 1;
            }
          }
          else if ((uVar3 < 0x7f800000) && (uVar3 == 0)) {
            if (((uint)fVar2 & 0x7fffff) == 0) {
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
        dVar7 = DOUBLE_8032f918 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8032f920);
        dVar7 = DOUBLE_8032f918 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8032f920);
        dVar6 = (double)(float)(dVar6 * DOUBLE_8032f918 * dVar7 *
                                        -(dVar6 * dVar7 * dVar7 - DOUBLE_8032f920));
      }
      uVar5 = 1;
      *param_4 = (float)(dVar13 * -(double)(float)(dVar9 + dVar6));
    }
  }
  return uVar5;
}

