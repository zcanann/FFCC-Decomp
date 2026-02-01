// Function: __ieee754_pow
// Entry: 801b9a18
// Size: 2096 bytes

/* WARNING: Removing unreachable block (ram,0x801ba230) */
/* WARNING: Removing unreachable block (ram,0x801ba228) */
/* WARNING: Removing unreachable block (ram,0x801ba220) */
/* WARNING: Removing unreachable block (ram,0x801ba218) */
/* WARNING: Removing unreachable block (ram,0x801ba210) */
/* WARNING: Removing unreachable block (ram,0x801b9a48) */
/* WARNING: Removing unreachable block (ram,0x801b9a40) */
/* WARNING: Removing unreachable block (ram,0x801b9a38) */
/* WARNING: Removing unreachable block (ram,0x801b9a30) */
/* WARNING: Removing unreachable block (ram,0x801b9a28) */

double __ieee754_pow(double param_1,double param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  uint local_a8;
  int iStack_a4;
  uint local_a0;
  uint uStack_9c;
  undefined8 local_98;
  double local_90;
  undefined8 local_88;
  double local_80;
  double local_78;
  double local_70;
  double local_68;
  undefined8 local_60;
  
  local_a0 = (uint)((ulonglong)param_2 >> 0x20);
  uStack_9c = SUB84(param_2,0);
  uVar3 = local_a0 & 0x7fffffff;
  local_a8 = (uint)((ulonglong)param_1 >> 0x20);
  iStack_a4 = SUB84(param_1,0);
  local_a8 = local_a8 & 0x7fffffff;
  local_60 = DOUBLE_80333a28;
  if (((ulonglong)param_2 & 0x7fffffff00000000) != 0 || uStack_9c != 0) {
    if (((local_a8 < 0x7ff00001) &&
        (((local_a8 != 0x7ff00000 || (iStack_a4 == 0)) && (uVar3 < 0x7ff00001)))) &&
       ((uVar3 != 0x7ff00000 || (uStack_9c == 0)))) {
      iVar2 = 0;
      if ((longlong)param_1 < 0) {
        if (uVar3 < 0x43400000) {
          if (0x3fefffff < uVar3) {
            iVar5 = ((int)uVar3 >> 0x14) + -0x3ff;
            if (iVar5 < 0x15) {
              if ((uStack_9c == 0) &&
                 (uVar4 = (int)uVar3 >> (0x14U - iVar5 & 0x3f), uVar3 == uVar4 << 0x14U - iVar5)) {
                iVar2 = 2 - (uVar4 & 1);
              }
            }
            else {
              uVar4 = uStack_9c >> 0x34 - iVar5;
              if (uStack_9c == uVar4 << 0x34 - iVar5) {
                iVar2 = 2 - (uVar4 & 1);
              }
            }
          }
        }
        else {
          iVar2 = 2;
        }
      }
      if (uStack_9c == 0) {
        if (uVar3 == 0x7ff00000) {
          if (local_a8 == 0x3ff00000 && iStack_a4 == 0) {
            return param_2 - param_2;
          }
          if (0x3fefffff < local_a8) {
            if ((longlong)param_2 < 0) {
              return DOUBLE_80333a30;
            }
            return param_2;
          }
          if (-1 < (longlong)param_2) {
            return DOUBLE_80333a30;
          }
          return -param_2;
        }
        if (uVar3 == 0x3ff00000) {
          if (-1 < (longlong)param_2) {
            return param_1;
          }
          return DOUBLE_80333a28 / param_1;
        }
        if (local_a0 == 0x40000000) {
          return param_1 * param_1;
        }
        if ((local_a0 == 0x3fe00000) && (-1 < (longlong)param_1)) {
          dVar8 = (double)sqrt(param_1);
          return dVar8;
        }
      }
      local_60 = ABS(param_1);
      if ((iStack_a4 == 0) &&
         (((local_a8 == 0x7ff00000 || (((ulonglong)param_1 & 0x7fffffff00000000) == 0)) ||
          (local_a8 == 0x3ff00000)))) {
        if ((longlong)param_2 < 0) {
          local_60 = DOUBLE_80333a28 / local_60;
        }
        if ((longlong)param_1 < 0) {
          if (local_a8 == 0x3ff00000 && iVar2 == 0) {
            local_60 = (local_60 - local_60) / (local_60 - local_60);
          }
          else if (iVar2 == 1) {
            local_60 = -local_60;
          }
        }
      }
      else if ((longlong)param_1 < 0 && iVar2 == 0) {
        DAT_8032f390 = 0x21;
        local_60 = (double)DAT_8032ec20;
      }
      else {
        local_98._4_4_ = SUB84(DOUBLE_80333a30,0);
        uVar1 = local_98._4_4_;
        if (uVar3 < 0x41e00001) {
          iVar5 = 0;
          local_68 = local_60;
          if (local_a8 < 0x100000) {
            iVar5 = -0x35;
            local_68._0_4_ = (uint)((ulonglong)(local_60 * DOUBLE_80333a70) >> 0x20);
            local_a8 = local_68._0_4_;
            local_68 = local_60 * DOUBLE_80333a70;
          }
          uVar3 = local_a8 & 0xfffff;
          uVar4 = uVar3 | 0x3ff00000;
          iVar5 = ((int)local_a8 >> 0x14) + iVar5;
          uVar6 = iVar5 - 0x3ff;
          if (uVar3 < 0x3988f) {
            iVar7 = 0;
          }
          else if (uVar3 < 0xbb67a) {
            iVar7 = 1;
          }
          else {
            uVar4 = uVar4 - 0x100000;
            iVar7 = 0;
            uVar6 = iVar5 - 0x3fe;
          }
          local_68 = (double)CONCAT44(uVar4,local_68._4_4_);
          dVar9 = (double)(&DAT_801e7480)[iVar7];
          dVar10 = DOUBLE_80333a28 / (local_68 + dVar9);
          dVar8 = (local_68 - dVar9) * dVar10;
          local_98 = (double)CONCAT44(((int)uVar4 >> 1 | 0x20000000U) + 0x80000 + iVar7 * 0x40000,
                                      local_98._4_4_);
          dVar11 = dVar8 * dVar8;
          local_90 = (double)((ulonglong)dVar8 & 0xffffffff00000000);
          dVar10 = dVar10 * -(local_90 * (local_68 - (local_98 - dVar9)) -
                             -(local_90 * local_98 - (local_68 - dVar9)));
          dVar9 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DOUBLE_80333b30;
          dVar11 = dVar10 * (local_90 + dVar8) +
                   dVar11 * dVar11 *
                   (dVar11 * (dVar11 * (dVar11 * (dVar11 * (DOUBLE_80333aa0 * dVar11 +
                                                           DOUBLE_80333a98) + DOUBLE_80333a90) +
                                       DOUBLE_80333a88) + DOUBLE_80333a80) + DOUBLE_80333a78);
          local_98 = (double)((ulonglong)(DOUBLE_80333aa8 + local_90 * local_90 + dVar11) &
                             0xffffffff00000000);
          dVar8 = dVar10 * local_98 +
                  (dVar11 - ((local_98 - DOUBLE_80333aa8) - local_90 * local_90)) * dVar8;
          local_70 = (double)((ulonglong)(local_90 * local_98 + dVar8) & 0xffffffff00000000);
          dVar8 = (double)(&DAT_801e74a0)[iVar7] +
                  DOUBLE_80333ab8 * local_70 +
                  DOUBLE_80333ac0 * (dVar8 - (local_70 - local_90 * local_98));
          local_80 = (double)((ulonglong)
                              (dVar9 + DOUBLE_80333ab0 * local_70 + dVar8 +
                                       (double)(&DAT_801e7490)[iVar7]) & 0xffffffff00000000);
          dVar8 = dVar8 - (((local_80 - dVar9) - (double)(&DAT_801e7490)[iVar7]) -
                          DOUBLE_80333ab0 * local_70);
        }
        else {
          if (0x43f00000 < uVar3) {
            if (local_a8 < 0x3ff00000) {
              if (-1 < (longlong)param_2) {
                return DOUBLE_80333a30;
              }
              return DOUBLE_80333a38;
            }
            if (0x3fefffff < local_a8) {
              if ((int)local_a0 < 1) {
                return DOUBLE_80333a30;
              }
              return DOUBLE_80333a38;
            }
          }
          if (local_a8 < 0x3fefffff) {
            if (-1 < (longlong)param_2) {
              return DOUBLE_80333a30;
            }
            return DOUBLE_80333a38;
          }
          if (0x3ff00000 < local_a8) {
            if ((int)local_a0 < 1) {
              return DOUBLE_80333a30;
            }
            return DOUBLE_80333a38;
          }
          dVar9 = param_1 - DOUBLE_80333a28;
          dVar8 = DOUBLE_80333a60 * dVar9 -
                  DOUBLE_80333a68 *
                  dVar9 * dVar9 *
                  -(dVar9 * -(DOUBLE_80333a50 * dVar9 - DOUBLE_80333a48) - DOUBLE_80333a40);
          local_80 = (double)((ulonglong)(DOUBLE_80333a58 * dVar9 + dVar8) & 0xffffffff00000000);
          dVar8 = dVar8 - (local_80 - DOUBLE_80333a58 * dVar9);
        }
        dVar9 = DOUBLE_80333a28;
        if ((longlong)param_1 < 0 && iVar2 == 1) {
          dVar9 = DOUBLE_80333ac8;
        }
        local_78 = (double)((ulonglong)param_2 & 0xffffffff00000000);
        local_70 = local_78 * local_80;
        dVar11 = local_80 * (param_2 - local_78) + param_2 * dVar8;
        dVar8 = dVar11 + local_70;
        local_60._0_4_ = (uint)((ulonglong)dVar8 >> 0x20);
        if ((longlong)dVar8 < 0x4090000000000000) {
          if (0x4090cbff < (local_60._0_4_ & 0x7fffffff)) {
            if (dVar8 != -1075.0) {
              return DOUBLE_80333ae0 * DOUBLE_80333ae0 * dVar9;
            }
            if (dVar11 <= -1075.0 - local_70) {
              return DOUBLE_80333ae0 * DOUBLE_80333ae0 * dVar9;
            }
          }
        }
        else {
          if (dVar8 != 1024.0) {
            return DOUBLE_80333ad0 * DOUBLE_80333ad0 * dVar9;
          }
          if (1024.0 - local_70 < DOUBLE_80333ad8 + dVar11) {
            return DOUBLE_80333ad0 * DOUBLE_80333ad0 * dVar9;
          }
        }
        iVar2 = 0;
        if (0x3fe00000 < (local_60._0_4_ & 0x7fffffff)) {
          local_60._0_4_ =
               local_60._0_4_ + (0x100000 >> ((local_60._0_4_ >> 0x14 & 0x7ff) - 0x3fe & 0x3f));
          uVar3 = ((int)(local_60._0_4_ & 0x7fffffff) >> 0x14) - 0x3ff;
          local_88 = (double)CONCAT44(local_60._0_4_ & ~(0xfffff >> (uVar3 & 0x3f)),uVar1);
          iVar2 = (int)(local_60._0_4_ & 0xfffff | 0x100000) >> (0x14 - uVar3 & 0x3f);
          if ((longlong)dVar8 < 0) {
            iVar2 = -iVar2;
          }
          local_70 = local_70 - local_88;
        }
        local_88 = (double)((ulonglong)(dVar11 + local_70) & 0xffffffff00000000);
        dVar11 = DOUBLE_80333af0 * (dVar11 - (local_88 - local_70)) + DOUBLE_80333af8 * local_88;
        dVar10 = DOUBLE_80333ae8 * local_88 + dVar11;
        dVar8 = dVar10 * dVar10;
        dVar11 = dVar11 - (dVar10 - DOUBLE_80333ae8 * local_88);
        dVar8 = dVar10 - dVar8 * (dVar8 * (dVar8 * (dVar8 * (DOUBLE_80333b20 * dVar8 +
                                                            DOUBLE_80333b18) + DOUBLE_80333b10) +
                                          DOUBLE_80333b08) + DOUBLE_80333b00);
        dVar8 = DOUBLE_80333a28 -
                (((dVar10 * dVar8) / (dVar8 - DOUBLE_80333b28) - (dVar10 * dVar11 + dVar11)) -
                dVar10);
        local_60._0_4_ = (uint)((ulonglong)dVar8 >> 0x20);
        if ((int)(local_60._0_4_ + iVar2 * 0x100000) >> 0x14 < 1) {
          local_60 = (double)ldexp();
        }
        else {
          local_60 = (double)CONCAT44(local_60._0_4_ + iVar2 * 0x100000,SUB84(dVar8,0));
        }
        local_60 = dVar9 * local_60;
      }
    }
    else {
      local_60 = param_1 + param_2;
    }
  }
  return local_60;
}

