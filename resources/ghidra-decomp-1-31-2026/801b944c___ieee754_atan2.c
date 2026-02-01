// Function: __ieee754_atan2
// Entry: 801b944c
// Size: 652 bytes

/* WARNING: Removing unreachable block (ram,0x801b95b8) */
/* WARNING: Removing unreachable block (ram,0x801b9570) */
/* WARNING: Removing unreachable block (ram,0x801b9670) */
/* WARNING: Removing unreachable block (ram,0x801b94fc) */

double __ieee754_atan2(double param_1,double param_2)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  int iVar4;
  uint uVar5;
  uint local_28;
  uint uStack_24;
  uint local_20;
  uint uStack_1c;
  double local_18;
  
  uStack_1c = SUB84(param_2,0);
  local_20 = (uint)((ulonglong)param_2 >> 0x20);
  uVar1 = local_20 & 0x7fffffff;
  local_28 = (uint)((ulonglong)param_1 >> 0x20);
  uStack_24 = SUB84(param_1,0);
  uVar2 = local_28 & 0x7fffffff;
  if (((uVar1 | (uStack_1c | -uStack_1c) >> 0x1f) < 0x7ff00001) &&
     ((uVar2 | (uStack_24 | -uStack_24) >> 0x1f) < 0x7ff00001)) {
    if (local_20 == 0x3ff00000 && uStack_1c == 0) {
      local_18 = (double)atan();
    }
    else {
      uVar5 = local_28 >> 0x1f | local_20 >> 0x1e & 2;
      if ((((ulonglong)param_1 & 0x7fffffff00000000) != 0 || uStack_24 != 0) ||
         (((local_18 = DOUBLE_803339d0, uVar5 != 2 && (local_18 = param_1, 1 < uVar5)) &&
          (local_18 = DOUBLE_803339d8, 3 < uVar5)))) {
        local_18 = DOUBLE_803339e8;
        if (((ulonglong)param_2 & 0x7fffffff00000000) == 0 && uStack_1c == 0) {
          if ((longlong)param_1 < 0) {
            local_18 = DOUBLE_803339e0;
          }
        }
        else {
          if (uVar1 == 0x7ff00000) {
            if (uVar2 == 0x7ff00000) {
              if (uVar5 == 2) {
                return DOUBLE_80333a00;
              }
              dVar3 = DOUBLE_80333a08;
              if (uVar5 < 2) {
                if (uVar5 == 0) {
                  return DOUBLE_803339f0;
                }
                return DOUBLE_803339f8;
              }
            }
            else {
              if (uVar5 == 2) {
                return DOUBLE_803339d0;
              }
              dVar3 = DOUBLE_803339d8;
              if (uVar5 < 2) {
                if (uVar5 == 0) {
                  return DOUBLE_80333a10;
                }
                return DOUBLE_80333a18;
              }
            }
            if (uVar5 < 4) {
              return dVar3;
            }
          }
          if (uVar2 == 0x7ff00000) {
            if ((longlong)param_1 < 0) {
              local_18 = DOUBLE_803339e0;
            }
          }
          else {
            iVar4 = (int)(uVar2 - uVar1) >> 0x14;
            if (iVar4 < 0x3d) {
              if (((longlong)param_2 < 0) && (iVar4 < -0x3c)) {
                local_18 = DOUBLE_80333a10;
              }
              else {
                local_18 = (double)atan(ABS(param_1 / param_2));
              }
            }
            else {
            }
            if (uVar5 == 1) {
              local_18 = -local_18;
            }
            else if (uVar5 != 0) {
              if (uVar5 < 3) {
                local_18 = DOUBLE_803339d0 - (local_18 - DOUBLE_80333a20);
              }
              else {
                local_18 = (local_18 - DOUBLE_80333a20) - DOUBLE_803339d0;
              }
            }
          }
        }
      }
    }
  }
  else {
    local_18 = param_2 + param_1;
  }
  return local_18;
}

